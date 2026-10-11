#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "code/core/controllerdirectinput.h"
#include "code/core/platform.h"

// The ole32 / oleaut32 / user32 imports. Declared dllimport like the SDK does (repeated calls then load the
// import slot once); the relinker's import libraries name the slots without the __stdcall decoration (see sync.cpp),
// so each decorated name is pointed at the plain one.
extern "C"
{
	__declspec(dllimport) HRESULT __stdcall CoInitialize(void* reserved);
	__declspec(dllimport) void __stdcall CoUninitialize();
	__declspec(dllimport) HRESULT __stdcall CoCreateInstance(REFGUID clsid, IUnknown* outer, DWORD context, REFGUID iid,
		void** object);
	__declspec(dllimport) HRESULT __stdcall CoSetProxyBlanket(IUnknown* proxy, DWORD authentication,
		DWORD authorization, wchar_t* principal, DWORD level, DWORD impersonation, void* identity, DWORD capabilities);
	__declspec(dllimport) BSTR __stdcall SysAllocString(const wchar_t* string);
	__declspec(dllimport) void __stdcall SysFreeString(BSTR string);
	__declspec(dllimport) long __stdcall SetWindowLongA(void* window, int index, long value);
	__declspec(dllimport) long __stdcall CallWindowProcA(long procedure, void* window, unsigned int message,
		unsigned int wParam, long lParam);
}
#pragma comment(linker, "/alternatename:__imp__CoInitialize@4=__imp__CoInitialize")
#pragma comment(linker, "/alternatename:__imp__CoUninitialize@0=__imp__CoUninitialize")
#pragma comment(linker, "/alternatename:__imp__CoCreateInstance@20=__imp__CoCreateInstance")
#pragma comment(linker, "/alternatename:__imp__CoSetProxyBlanket@32=__imp__CoSetProxyBlanket")
#pragma comment(linker, "/alternatename:__imp__SysAllocString@4=__imp__SysAllocString")
#pragma comment(linker, "/alternatename:__imp__SysFreeString@4=__imp__SysFreeString")
#pragma comment(linker, "/alternatename:__imp__SetWindowLongA@12=__imp__SetWindowLongA")
#pragma comment(linker, "/alternatename:__imp__CallWindowProcA@20=__imp__CallWindowProcA")

namespace core
{
	const char* CoreName();

	// The object index of every keyboard key by scan code (minus one), filled while a keyboard enumerates its
	// objects; only declared, so that the test tools that read it at its original address keep working
	extern int gDirectInputKeys[256];
	// GLOBAL: ENGINE 0x11279410
	static ControllerSystemDirectInput* sDirectInputSystem;
	// The heap the system and its controllers come from
	// GLOBAL: ENGINE 0x11279414
	static int sDirectInputHeap;
	// True while a keyboard enumerates its objects
	// GLOBAL: ENGINE 0x11279418
	static bool sDirectInputEnumKeyboard;
	// InitDirectInput's options (DIRECTINPUT_...)
	// GLOBAL: ENGINE 0x1127941C
	unsigned int gDirectInputOptions;

	// FUNCTION: ENGINE 0x106413F0
	bool ControllerSystemDirectInput::IsActive()
	{
		if (enabled)
		{
			return focused;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10641400
	IControllerSystem* GetDirectInputSystem()
	{
		return sDirectInputSystem;
	}

	// FUNCTION: ENGINE 0x10641410
	void UpdateDirectInput()
	{
		if (sDirectInputSystem != 0)
		{
			sDirectInputSystem->Update();
		}
	}

	// FUNCTION: ENGINE 0x10641430
	IController* ControllerSystemDirectInput::FindController(const char* location)
	{
		if (location != 0)
		{
			for (ControllerDirectInput* controller = controllers; controller != 0; controller = controller->next)
			{
				if (controller->IsConnected() && strcmp(controller->GetLocation(), location) == 0)
				{
					return controller;
				}
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x106414B0
	IController* ControllerSystemDirectInput::GetController(unsigned int index)
	{
		unsigned int count = 0;
		for (ControllerDirectInput* controller = controllers; controller != 0; controller = controller->next)
		{
			if (controller->IsConnected())
			{
				if (count == index)
				{
					return controller;
				}
				count++;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x106414F0
	unsigned int ControllerSystemDirectInput::GetControllerCount()
	{
		unsigned int count = 0;
		for (ControllerDirectInput* controller = controllers; controller != 0; controller = controller->next)
		{
			if (controller->IsConnected())
			{
				count++;
			}
		}
		return count;
	}

	// FUNCTION: ENGINE 0x10641520
	void ControllerSystemDirectInput::SetListener(IControllerListener* newListener)
	{
		if (listener == 0)
		{
			listener = newListener;
		}
	}

	// FUNCTION: ENGINE 0x10641530
	void ControllerSystemDirectInput::ClearListener(IControllerListener* oldListener)
	{
		if (listener == oldListener)
		{
			listener = 0;
		}
	}

	// FUNCTION: ENGINE 0x10641550
	void ControllerSystemDirectInput::NotifyListener(IController* controller)
	{
		if (listener != 0)
		{
			listener->OnControllerChanged(controller);
		}
	}

	// FUNCTION: ENGINE 0x10641570
	unsigned int ControllerSystemDirectInput::GetJoystickCount()
	{
		return joystickCount;
	}

	// FUNCTION: ENGINE 0x10641580
	// The DirectX SDK's sample ("XInput and DirectInput"): asks WMI for the plug-and-play devices whose id contains
	// "IG_" (XInput devices) and compares their vendor / product ids with the DirectInput product GUID
	static BOOL __stdcall IsXInputDevice(const GUID* pGuidProductFromDirectInput)
	{
		IWbemLocator* pIWbemLocator = 0;
		IEnumWbemClassObject* pEnumDevices = 0;
		IWbemClassObject* pDevices[20] = {0};
		IWbemServices* pIWbemServices = 0;
		BSTR bstrNamespace = 0;
		BSTR bstrDeviceID = 0;
		BSTR bstrClassName = 0;
		DWORD uReturned = 0;
		bool bIsXinputDevice = false;
		unsigned int iDevice = 0;
		VARIANT var;
		HRESULT hr;

		hr = CoInitialize(0);
		bool bCleanupCOM = hr >= 0;

		hr = CoCreateInstance(__uuidof(WbemLocator), 0, CLSCTX_INPROC_SERVER, __uuidof(IWbemLocator),
			(void**)&pIWbemLocator);
		if (hr < 0 || pIWbemLocator == 0)
		{
			goto LCleanup;
		}

		bstrNamespace = SysAllocString(L"\\\\.\\root\\cimv2");
		if (bstrNamespace == 0)
		{
			goto LCleanup;
		}
		bstrClassName = SysAllocString(L"Win32_PNPEntity");
		if (bstrClassName == 0)
		{
			goto LCleanup;
		}
		bstrDeviceID = SysAllocString(L"DeviceID");
		if (bstrDeviceID == 0)
		{
			goto LCleanup;
		}

		hr = pIWbemLocator->ConnectServer(bstrNamespace, 0, 0, 0, 0, 0, 0, &pIWbemServices);
		if (hr < 0 || pIWbemServices == 0)
		{
			goto LCleanup;
		}

		CoSetProxyBlanket(pIWbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, 0, RPC_C_AUTHN_LEVEL_CALL,
			RPC_C_IMP_LEVEL_IMPERSONATE, 0, EOAC_NONE);

		hr = pIWbemServices->CreateInstanceEnum(bstrClassName, 0, 0, &pEnumDevices);
		if (hr < 0 || pEnumDevices == 0)
		{
			goto LCleanup;
		}

		for (;;)
		{
			hr = pEnumDevices->Next(10000, 20, pDevices, &uReturned);
			if (hr < 0)
			{
				goto LCleanup;
			}
			if (uReturned == 0)
			{
				break;
			}

			for (iDevice = 0; iDevice < uReturned; iDevice++)
			{
				hr = pDevices[iDevice]->Get(bstrDeviceID, 0, &var, 0, 0);
				if (hr >= 0 && var.vt == VT_BSTR && var.bstrVal != 0)
				{
					if (wcsstr(var.bstrVal, L"IG_"))
					{
						DWORD dwPid = 0, dwVid = 0;
						wchar_t* strVid = wcsstr(var.bstrVal, L"VID_");
						if (strVid && swscanf(strVid, L"VID_%4X", &dwVid) != 1)
						{
							dwVid = 0;
						}
						wchar_t* strPid = wcsstr(var.bstrVal, L"PID_");
						if (strPid && swscanf(strPid, L"PID_%4X", &dwPid) != 1)
						{
							dwPid = 0;
						}

						DWORD dwVidPid = (LONG)(((WORD)dwVid) | ((DWORD)((WORD)dwPid)) << 16);
						if (dwVidPid == pGuidProductFromDirectInput->Data1)
						{
							bIsXinputDevice = true;
							goto LCleanup;
						}
					}
				}
				if (pDevices[iDevice])
				{
					pDevices[iDevice]->Release();
					pDevices[iDevice] = 0;
				}
			}
		}

	LCleanup:
		if (bstrNamespace)
		{
			SysFreeString(bstrNamespace);
		}
		if (bstrDeviceID)
		{
			SysFreeString(bstrDeviceID);
		}
		if (bstrClassName)
		{
			SysFreeString(bstrClassName);
		}
		for (iDevice = 0; iDevice < 20; iDevice++)
		{
			if (pDevices[iDevice])
			{
				pDevices[iDevice]->Release();
				pDevices[iDevice] = 0;
			}
		}
		if (pEnumDevices)
		{
			pEnumDevices->Release();
			pEnumDevices = 0;
		}
		if (pIWbemLocator)
		{
			pIWbemLocator->Release();
			pIWbemLocator = 0;
		}
		if (pIWbemServices)
		{
			pIWbemServices->Release();
			pIWbemServices = 0;
		}

		if (bCleanupCOM)
		{
			CoUninitialize();
		}

		return bIsXinputDevice;
	}

	// FUNCTION: ENGINE 0x106418A0
	// Subclasses the application window: tracks whether it has the focus
	static long __stdcall DirectInputWindowProc(void* window, unsigned int message, unsigned int wParam, long lParam)
	{
		ControllerSystemDirectInput* system = sDirectInputSystem;
		switch (message)
		{
		case 7: // WM_SETFOCUS
			system->focused = true;
			break;
		case 8: // WM_KILLFOCUS
			system->focused = false;
			break;
		case 0x1C: // WM_ACTIVATEAPP
			system->focused = wParam != 0;
			break;
		}
		return CallWindowProcA(system->previousProc, window, message, wParam, lParam);
	}

	// FUNCTION: ENGINE 0x10641900
	bool ControllerDirectInput::IsConnected()
	{
		return connected;
	}

	// FUNCTION: ENGINE 0x10641910
	const char* ControllerDirectInput::GetName()
	{
		return instance.tszProductName;
	}

	// FUNCTION: ENGINE 0x10641920
	const char* ControllerDirectInput::GetTypeName()
	{
		switch ((unsigned char)instance.dwDevType)
		{
		case DI8DEVTYPE_MOUSE:
			return "Mouse";
		case DI8DEVTYPE_JOYSTICK:
		case DI8DEVTYPE_GAMEPAD:
		case DI8DEVTYPE_FLIGHT:
		case DI8DEVTYPE_1STPERSON:
			return "Joystick";
		case DI8DEVTYPE_KEYBOARD:
			return "Keyboard";
		}
		return "Unknown Location";
	}

	// FUNCTION: ENGINE 0x10641970
	unsigned int ControllerDirectInput::GetInputCount()
	{
		return inputCount;
	}

	// FUNCTION: ENGINE 0x10641980
	unsigned int ControllerDirectInput::CountInputs(const char* typeName)
	{
		unsigned int count = 0;
		if (typeName != 0)
		{
			for (ControllerInputPointDirectInput* input = inputs; input != 0; input = input->next)
			{
				if (strcmp(typeName, input->GetTypeName()) == 0)
				{
					count++;
				}
			}
		}
		return count;
	}

	// FUNCTION: ENGINE 0x106419F0
	IControllerInputPoint* ControllerDirectInput::FindInput(const char* typeName, unsigned int index)
	{
		if (typeName != 0)
		{
			unsigned int count = 0;
			for (ControllerInputPointDirectInput* input = inputs; input != 0; input = input->next)
			{
				if (strcmp(input->GetTypeName(), typeName) == 0)
				{
					if (count == index)
					{
						return input;
					}
					count++;
				}
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10641A70
	IControllerInputPoint* ControllerDirectInput::FindInputByName(const char* name)
	{
		for (ControllerInputPointDirectInput* input = inputs; input != 0; input = input->next)
		{
			if (strcmp(input->GetName(), name) == 0)
			{
				return input;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10641AE0
	IControllerInputPoint* ControllerDirectInput::GetInput(unsigned int index)
	{
		unsigned int count = 0;
		for (ControllerInputPointDirectInput* input = inputs; input != 0; input = input->next)
		{
			if (count == index)
			{
				return input;
			}
			count++;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10641B10
	unsigned int ControllerDirectInput::GetOutputCount()
	{
		return outputCount;
	}

	// FUNCTION: ENGINE 0x10641B20
	unsigned int ControllerDirectInput::CountOutputs(const char* typeName)
	{
		unsigned int count = 0;
		if (typeName != 0)
		{
			for (ControllerOutputPointDirectInput* output = outputs; output != 0; output = output->next)
			{
				if (strcmp(output->GetTypeName(), typeName) == 0)
				{
					count++;
				}
			}
		}
		return count;
	}

	// FUNCTION: ENGINE 0x10641BA0
	IControllerOutputPoint* ControllerDirectInput::FindOutput(const char* typeName, unsigned int index)
	{
		if (typeName != 0)
		{
			unsigned int count = 0;
			for (ControllerOutputPointDirectInput* output = outputs; output != 0; output = output->next)
			{
				if (strcmp(output->GetTypeName(), typeName) == 0)
				{
					if (count == index)
					{
						return output;
					}
					count++;
				}
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10641C20
	IControllerOutputPoint* ControllerDirectInput::FindOutputByName(const char* name)
	{
		for (ControllerOutputPointDirectInput* output = outputs; output != 0; output = output->next)
		{
			if (strcmp(name, output->GetName()) == 0)
			{
				return output;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10641C90
	IControllerOutputPoint* ControllerDirectInput::GetOutput(unsigned int index)
	{
		unsigned int count = 0;
		for (ControllerOutputPointDirectInput* output = outputs; output != 0; output = output->next)
		{
			if (count == index)
			{
				return output;
			}
			count++;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10641CD0
	const char* ControllerOutputPointDirectInput::GetName()
	{
		return object.tszName;
	}

	// FUNCTION: ENGINE 0x10641CE0
	const char* ControllerOutputPointDirectInput::GetTypeName()
	{
		if (object.dwFFForceResolution == 1)
		{
			return "Digital";
		}
		return "Analog";
	}

	// FUNCTION: ENGINE 0x10641D00
	float ControllerOutputPointDirectInput::GetValue()
	{
		return value;
	}

	// FUNCTION: ENGINE 0x10641D10
	void ControllerOutputPointDirectInput::SetValue(float newValue)
	{
		if (newValue < 0.0f)
		{
			newValue = 0.0f;
		}
		else if (newValue > 1.0f)
		{
			newValue = 1.0f;
		}
		value = newValue;
	}

	// FUNCTION: ENGINE 0x10641D50
	ControllerInputPointDirectInput::~ControllerInputPointDirectInput()
	{
	}

	// FUNCTION: ENGINE 0x10641DB0
	unsigned int ControllerInputPointDirectInput::GetValueCount()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10641DC0
	unsigned int ControllerInputPointDirectInput::ReadValues(unsigned int count, float* values)
	{
		if (count > 0 && values != 0)
		{
			values[0] = Read(0);
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x10641DF0
	const char* ControllerInputPointDirectInput::GetName()
	{
		return object.tszName;
	}

	// FUNCTION: ENGINE 0x10641E00
	const char* ControllerInputPointDirectInput::GetTypeName()
	{
		bool relative = (unsigned char)object.dwType == DIDFT_RELAXIS;
		if (object.guidType == GUID_XAxis)
		{
			return relative ? "RelXAxis" : "XAxis";
		}
		if (object.guidType == GUID_YAxis)
		{
			return relative ? "RelYAxis" : "YAxis";
		}
		if (object.guidType == GUID_ZAxis)
		{
			return relative ? "RelZAxis" : "ZAxis";
		}
		if (object.guidType == GUID_RxAxis)
		{
			return relative ? "RelRxAxis" : "RxAxis";
		}
		if (object.guidType == GUID_RyAxis)
		{
			return relative ? "RelRyAxis" : "RyAxis";
		}
		if (object.guidType == GUID_RzAxis)
		{
			return relative ? "RelRzAxis" : "RzAxis";
		}
		if (object.guidType == GUID_Slider)
		{
			return relative ? "RelSlider" : "Slider";
		}
		if (object.guidType == GUID_Button || object.guidType == GUID_Key)
		{
			return "Button";
		}
		if (object.guidType == GUID_POV)
		{
			return "POV";
		}
		return "Unknown";
	}

	// FUNCTION: ENGINE 0x10641F70
	void ControllerInputPointDirectInput::SetThreshold(float newThreshold)
	{
		if (newThreshold < 0.0f)
		{
			newThreshold = 0.0f;
		}
		else if (newThreshold > 1.0f)
		{
			newThreshold = 1.0f;
		}
		threshold = newThreshold;
	}

	// FUNCTION: ENGINE 0x10641FA0
	float ControllerInputPointDirectInput::GetThreshold()
	{
		return threshold;
	}

	// FUNCTION: ENGINE 0x10641FB0
	void ControllerInputPointDirectInput::SetBinding(IControllerBinding* newBinding, void* userData)
	{
		if (binding == 0)
		{
			bindingData = userData;
			binding = newBinding;
		}
	}

	// FUNCTION: ENGINE 0x10641FD0
	void ControllerInputPointDirectInput::ClearBinding(IControllerBinding* oldBinding)
	{
		if (binding == oldBinding)
		{
			binding = 0;
			bindingData = 0;
		}
	}

	// FUNCTION: ENGINE 0x10641FF0
	float ControllerInputPointDirectInput::Read(unsigned int* heldTimeOut)
	{
		if (heldTimeOut != 0)
		{
			*heldTimeOut = heldTime;
		}
		return minimum + (maximum - minimum) * value;
	}

	// FUNCTION: ENGINE 0x10642010
	void ControllerInputPointDirectInput::GetRange(float* minimumOut, float* maximumOut)
	{
		if (minimumOut != 0)
		{
			*minimumOut = minimum;
		}
		if (maximumOut != 0)
		{
			*maximumOut = maximum;
		}
	}

	// FUNCTION: ENGINE 0x10642030
	void ControllerInputPointDirectInput::SetRange(float newMinimum, float newMaximum)
	{
		minimum = newMinimum;
		maximum = newMaximum;
	}

	// FUNCTION: ENGINE 0x10642050
	float ControllerInputPointDirectInput::ConvertValue(float previous, DWORD raw)
	{
		float result;
		switch ((unsigned char)object.dwType)
		{
		case DIDFT_RELAXIS:
			result = (float)(int)raw;
			break;
		case DIDFT_ABSAXIS:
			result = (float)raw * (1.0f / 65535.0f);
			if (object.guidType == GUID_YAxis || object.guidType == GUID_RyAxis || object.guidType == GUID_RzAxis)
			{
				result = 1.0f - result;
			}
			break;
		case DIDFT_PSHBUTTON:
		case DIDFT_TGLBUTTON:
		case DIDFT_PSHBUTTON | DIDFT_TGLBUTTON:
			if (raw & 0x80)
			{
				result = 1.0f;
			}
			else
			{
				result = 0.0f;
			}
			break;
		case DIDFT_POV:
			if (raw == 0xFFFFFFFF)
			{
				result = 1.0f;
			}
			else
			{
				result = (float)raw * (1.0f / 36000.0f);
			}
			break;
		default:
			result = 0.0f;
			break;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10642170
	float ControllerInputPointDirectInput::GetRestValue()
	{
		float result;
		switch ((unsigned char)object.dwType)
		{
		case DIDFT_ABSAXIS:
			result = 0.5f;
			break;
		case DIDFT_POV:
			result = 1.0f;
			break;
		default:
			result = 0.0f;
			break;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x106421B0
	void ControllerInputPointDirectInput::Update(unsigned int time, DWORD raw, bool valid)
	{
		float newValue = valid ? ConvertValue(value, raw) : GetRestValue();
		float oldValue = value;
		if (newValue != oldValue)
		{
			if (fabs(newValue - oldValue) >= threshold)
			{
				value = newValue;
				heldTime = 0;
				changeTime = time;
				if (binding != 0)
				{
					AddRef();
					binding->OnChange(bindingData, minimum + (maximum - minimum) * value);
					Release();
				}
			}
		}
		else
		{
			heldTime = time - changeTime;
		}
	}

	// FUNCTION: ENGINE 0x10642280
	DWORD ControllerInputPointDirectInput::GetDataType()
	{
		return object.dwType;
	}

	// FUNCTION: ENGINE 0x10642290
	// The rest values are overwritten: every case falls through to 0
	void ControllerInputPointDirectInput::Reset(unsigned int time)
	{
		switch ((unsigned char)object.dwType)
		{
		case DIDFT_ABSAXIS:
			value = 0.5f;
		case DIDFT_POV:
			value = 1.0f;
		}
		value = 0.0f;
		heldTime = 0;
		changeTime = time;
	}

	// FUNCTION: ENGINE 0x106425F0
	void ControllerInputPointDirectInput::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x10642600
	void ControllerInputPointDirectInput::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x10642630
	void ShutdownDirectInput()
	{
		sDirectInputSystem->Release();
	}

	// FUNCTION: ENGINE 0x10642650
	ControllerSystemDirectInput::~ControllerSystemDirectInput()
	{
		if (controllers != 0)
		{
			ControllerDirectInput* controller = controllers;
			ControllerDirectInput* next = controller->next;
			while (next != 0)
			{
				controller->Release();
				controller = next;
				next = next->next;
			}
			controller->Release();
		}
		controllers = 0;
		controllerCount = 0;
		directInput = 0;
		if (previousProc != 0)
		{
			SetWindowLongA(GetPlatform()->GetWindow(), -4, previousProc);
		}
		CoUninitialize();
		sDirectInputHeap = 0;
		sDirectInputSystem = 0;
	}

	// FUNCTION: ENGINE 0x10642710
	void ControllerSystemDirectInput::SetEnabled(bool newEnabled)
	{
		enabled = newEnabled;
	}

	// FUNCTION: ENGINE 0x10642730
	void ControllerSystemDirectInput::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x10642740
	void ControllerSystemDirectInput::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x10642770
	ControllerDirectInput::~ControllerDirectInput()
	{
		if (state != 0)
		{
			HeapFree(sDirectInputHeap, state);
			state = 0;
		}
		if (inputs != 0)
		{
			ControllerInputPointDirectInput* input = inputs;
			ControllerInputPointDirectInput* next = input->next;
			while (next != 0)
			{
				input->Release();
				input = next;
				next = next->next;
			}
			input->Release();
		}
		inputs = 0;
		lastInput = 0;
		inputCount = 0;
		if (outputs != 0)
		{
			ControllerOutputPointDirectInput* output = outputs;
			ControllerOutputPointDirectInput* next = output->next;
			while (next != 0)
			{
				output->Release();
				output = next;
				next = next->next;
			}
			output->Release();
		}
		outputs = 0;
		lastOutput = 0;
		outputCount = 0;
		if (device != 0)
		{
			device->Unacquire();
		}
	}

	// FUNCTION: ENGINE 0x106428A0
	bool ControllerDirectInput::Slot7()
	{
		return false;
	}

	// FUNCTION: ENGINE 0x106428B0
	int ControllerDirectInput::Slot8()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x106428C0
	int ControllerDirectInput::Slot9(int a)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x106428D0
	bool ControllerDirectInput::Slot10(int a, int b)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x106428E0
	int ControllerDirectInput::Slot11()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x106428F0
	int ControllerDirectInput::Slot12()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10642900
	int ControllerDirectInput::Slot13(int a)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10642910
	int ControllerDirectInput::Slot14(int a)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10642920
	int ControllerDirectInput::Slot15(int a, int b)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10642930
	int ControllerDirectInput::Slot16(int a)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10642950
	void ControllerDirectInput::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x10642960
	void ControllerDirectInput::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x10642990
	const char* ControllerDirectInput::GetLocation()
	{
		if (location != 0)
		{
			return location->Get();
		}
		return "Unknown Location";
	}

	// FUNCTION: ENGINE 0x106429B0
	ControllerOutputPointDirectInput::ControllerOutputPointDirectInput(const DIDEVICEOBJECTINSTANCEA* source,
		DWORD offset)
		: object(*source), effect(0), value(0.0f), appliedValue(0.0f), created(false), next(0)
	{
		CoreName();
		axes[0] = offset;
		direction[0] = 0;
		force.lMagnitude = 0;
		memset(&parameters, 0, sizeof(parameters));
		parameters.dwSize = sizeof(DIEFFECT);
		parameters.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
		parameters.dwDuration = INFINITE;
		parameters.dwSamplePeriod = 0;
		parameters.dwGain = DI_FFNOMINALMAX;
		parameters.dwTriggerButton = DIEB_NOTRIGGER;
		parameters.dwTriggerRepeatInterval = 0;
		parameters.cAxes = 1;
		parameters.rgdwAxes = axes;
		parameters.rglDirection = direction;
		parameters.lpEnvelope = 0;
		parameters.cbTypeSpecificParams = sizeof(DICONSTANTFORCE);
		parameters.lpvTypeSpecificParams = &force;
		parameters.dwStartDelay = 0;
	}

	// FUNCTION: ENGINE 0x10642AE0
	void ControllerOutputPointDirectInput::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x10642AF0
	void ControllerOutputPointDirectInput::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x10642B20
	ControllerOutputPointDirectInput::~ControllerOutputPointDirectInput()
	{
		effect = 0;
	}

	// FUNCTION: ENGINE 0x10642B80
	bool ControllerOutputPointDirectInput::CreateEffect(IDirectInputDevice8A* device)
	{
		if (device->CreateEffect(GUID_ConstantForce, &parameters, &effect, 0) >= 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10642BB0
	void ControllerOutputPointDirectInput::Update(IDirectInputDevice8A* device)
	{
		if (!created)
		{
			created = CreateEffect(device);
			if (!created)
			{
				return;
			}
		}
		if (value != appliedValue)
		{
			if (value < 1e-5f)
			{
				effect->Stop();
				appliedValue = value;
				return;
			}
			force.lMagnitude = (LONG)(value * 10000.0f);
			effect->SetParameters(&parameters, DIEP_TYPESPECIFICPARAMS | DIEP_START);
			appliedValue = value;
		}
	}

	// FUNCTION: ENGINE 0x10642C50
	ControllerInputPointDirectInput::ControllerInputPointDirectInput(ControllerDirectInput* controller,
		const DIDEVICEOBJECTINSTANCEA* source, int unused)
		: value(0.0f), heldTime(0), changeTime(0), threshold(0.0f), minimum(0.0f), maximum(1.0f), binding(0),
		bindingData(0), next(0)
	{
		CoreName();
		object = *source;
	}

	// FUNCTION: ENGINE 0x10642DA0
	void ControllerDirectInput::Update(unsigned int time, bool active)
	{
		bool read = false;
		if (!active && cooperativeLevel == DISCL_FOREGROUND)
		{
			if (device != 0)
			{
				device->Unacquire();
			}
		}
		else if (GetCount() > 1 && device != 0 && device->Acquire() >= 0)
		{
			device->Poll();
			if (device->GetDeviceState(inputCount * sizeof(DWORD), state) == DI_OK)
			{
				read = true;
			}
			for (ControllerOutputPointDirectInput* output = outputs; output != 0; output = output->next)
			{
				output->Update(device);
			}
		}
		unsigned int index = 0;
		for (ControllerInputPointDirectInput* input = inputs; input != 0; input = input->next, index++)
		{
			DWORD raw = 0;
			if (read)
			{
				raw = state[index];
			}
			input->Update(time, raw, read);
		}
		if ((instance.dwDevType & 0xFF) >= DI8DEVTYPE_JOYSTICK)
		{
			if (!connected || !read)
			{
				bool nowConnected = directInput->GetDeviceStatus(instance.guidInstance) == DI_OK;
				if (nowConnected != connected)
				{
					connected = nowConnected;
					sDirectInputSystem->NotifyListener(this);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10642EF0
	// Adds an input point per object (and an output point per force-feedback actuator)
	static BOOL __stdcall EnumObjectsCallback(const DIDEVICEOBJECTINSTANCEA* object, void* context)
	{
		ControllerDirectInput* controller = (ControllerDirectInput*)context;
		if (controller != 0)
		{
			unsigned int index = controller->inputCount;
			if (object->guidType != GUID_Unknown)
			{
				ControllerInputPointDirectInput* input = new (sDirectInputHeap) ControllerInputPointDirectInput(
					controller, object, 0);
				if (sDirectInputEnumKeyboard)
				{
					gDirectInputKeys[object->dwOfs - 1] = controller->inputCount;
				}
				if (controller->inputs == 0)
				{
					controller->inputs = input;
				}
				else
				{
					controller->lastInput->next = input;
				}
				input->next = 0;
				controller->lastInput = input;
				input->AddRef();
				controller->inputCount++;
				if (object->dwFlags & DIDOI_FFACTUATOR)
				{
					ControllerOutputPointDirectInput* output = new (sDirectInputHeap)
						ControllerOutputPointDirectInput(object, index * sizeof(DWORD));
					if (controller->outputs == 0)
					{
						controller->outputs = output;
					}
					else
					{
						controller->lastOutput->next = output;
					}
					output->next = 0;
					controller->lastOutput = output;
					output->AddRef();
					controller->outputCount++;
				}
			}
		}
		return DIENUM_CONTINUE;
	}

	// FUNCTION: ENGINE 0x10643070
	void ControllerSystemDirectInput::Update()
	{
		unsigned int time = GetMilliseconds();
		for (ControllerDirectInput* controller = controllers; controller != 0; controller = controller->next)
		{
			controller->Update(time, IsActive());
		}
	}

	// FUNCTION: ENGINE 0x106430B0
	ControllerDirectInput::ControllerDirectInput(const DIDEVICEINSTANCEA* source, RefPtr<IDirectInput8A> input,
		unsigned int* index)
		: directInput(input), state(0), inputs(0), lastInput(0), inputCount(0), outputs(0), lastOutput(0),
		outputCount(0), connected(true), cooperativeLevel(DISCL_FOREGROUND)
	{
		memset(&instance, 0, sizeof(instance));
		if (directInput != 0 && source != 0)
		{
			instance = *source;
			directInput->CreateDevice(source->guidInstance, &device, 0);
			if (device != 0)
			{
				sDirectInputEnumKeyboard = strcmp(GetTypeName(), "Keyboard") == 0;
				HRESULT hr = device->EnumObjects(EnumObjectsCallback, this, DIDFT_ALL);
				sDirectInputEnumKeyboard = false;
				if (hr >= 0)
				{
					DIDATAFORMAT format;
					memset(&format, 0, sizeof(format));
					format.dwSize = sizeof(DIDATAFORMAT);
					format.dwObjSize = sizeof(DIOBJECTDATAFORMAT);
					format.dwFlags = (strcmp(GetTypeName(), "Mouse") == 0) + DIDF_ABSAXIS;
					format.dwNumObjs = inputCount;
					format.dwDataSize = inputCount * sizeof(DWORD);
					format.rgodf = (DIOBJECTDATAFORMAT*)HeapAlloc(1, inputCount * sizeof(DIOBJECTDATAFORMAT));
					unsigned int i = 0;
					for (ControllerInputPointDirectInput* input = inputs; input != 0; input = input->next, i++)
					{
						format.rgodf[i].pguid = 0;
						format.rgodf[i].dwOfs = i * sizeof(DWORD);
						format.rgodf[i].dwFlags = 0;
						format.rgodf[i].dwType = 0;
						format.rgodf[i].dwType = input->GetDataType();
					}
					device->SetDataFormat(&format);
					HeapFree(1, format.rgodf);

					RefPtr<IPlatformWin32> platform;
					platform = GetPlatform();
					if (platform != 0)
					{
						DWORD level = DISCL_FOREGROUND;
						if ((gDirectInputOptions & DIRECTINPUT_JOYSTICK_BACKGROUND) != 0 &&
							strncmp(GetTypeName(), "Joystick", 8) == 0)
						{
							level = DISCL_BACKGROUND;
						}
						bool exclusive = false;
						if (strcmp(GetTypeName(), "Mouse") == 0)
						{
							if ((gDirectInputOptions & DIRECTINPUT_EXCLUSIVE_MOUSE) != 0)
							{
								exclusive = true;
							}
						}
						else if (strcmp(GetTypeName(), "Keyboard") == 0)
						{
							if ((gDirectInputOptions & DIRECTINPUT_EXCLUSIVE_KEYBOARD) != 0)
							{
								exclusive = true;
							}
						}
						else if (outputCount > 0)
						{
							exclusive = true;
						}
						if (exclusive || (hr = device->SetCooperativeLevel(platform->GetWindow(),
							level | DISCL_NONEXCLUSIVE)) < 0)
						{
							hr = device->SetCooperativeLevel(platform->GetWindow(), level | DISCL_EXCLUSIVE);
						}
						cooperativeLevel = level;
						if (hr >= 0)
						{
							if (outputCount > 0)
							{
								DIPROPDWORD autoCenter;
								autoCenter.diph.dwSize = sizeof(DIPROPDWORD);
								autoCenter.diph.dwHeaderSize = sizeof(DIPROPHEADER);
								autoCenter.diph.dwObj = 0;
								autoCenter.diph.dwHow = DIPH_DEVICE;
								autoCenter.dwData = DIPROPAUTOCENTER_OFF;
								device->SetProperty(DIPROP_AUTOCENTER, &autoCenter.diph);
							}
							CreateString(&location, sDirectInputHeap);
							if (location != 0)
							{
								if (strcmp(GetTypeName(), "Joystick") == 0)
								{
									DIPROPDWORD id;
									id.diph.dwSize = sizeof(DIPROPDWORD);
									id.diph.dwHeaderSize = sizeof(DIPROPHEADER);
									id.diph.dwObj = 0;
									id.diph.dwHow = DIPH_DEVICE;
									HRESULT idResult = device->GetProperty(DIPROP_JOYSTICKID, &id.diph);
									location->Append("Joystick");
									if (index == 0)
									{
										if (idResult >= 0)
										{
											location->Append((int)id.dwData);
										}
										else
										{
											location->Append("?");
										}
									}
									else
									{
										location->Append(*index);
									}
								}
								else if (strcmp(GetTypeName(), "Mouse") == 0)
								{
									location->Append("Mouse");
									location->Append("0");
								}
								else if (strcmp(GetTypeName(), "Keyboard") == 0)
								{
									location->Append("Keyboard");
									location->Append("0");
								}
								else
								{
									location->Append("Unknown Location");
								}
							}
						}
					}
					state = (DWORD*)HeapAlloc(sDirectInputHeap, inputCount * sizeof(DWORD));
					unsigned int time = GetMilliseconds();
					for (ControllerInputPointDirectInput* input = inputs; input != 0; input = input->next)
					{
						input->Reset(time);
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10643580
	// Creates a controller per attached device (XInput devices, and mice / keyboards when the options say so, left
	// out); joysticks are numbered
	static BOOL __stdcall EnumDevicesCallback(const DIDEVICEINSTANCEA* instance, void* context)
	{
		ControllerSystemDirectInput* system = (ControllerSystemDirectInput*)context;
		if (instance == 0 || system == 0)
		{
			return DIENUM_STOP;
		}
		if (IsXInputDevice(&instance->guidProduct))
		{
			return DIENUM_CONTINUE;
		}
		if ((gDirectInputOptions & DIRECTINPUT_NO_MOUSE) != 0 && (unsigned char)instance->dwDevType == DI8DEVTYPE_MOUSE)
		{
			return DIENUM_CONTINUE;
		}
		if ((gDirectInputOptions & DIRECTINPUT_NO_KEYBOARD) != 0 &&
			(unsigned char)instance->dwDevType == DI8DEVTYPE_KEYBOARD)
		{
			return DIENUM_CONTINUE;
		}
		ControllerDirectInput* controller;
		switch ((unsigned char)instance->dwDevType)
		{
		case DI8DEVTYPE_JOYSTICK:
		case DI8DEVTYPE_GAMEPAD:
		case DI8DEVTYPE_FLIGHT:
		case DI8DEVTYPE_1STPERSON:
			controller = new (sDirectInputHeap) ControllerDirectInput(instance, system->directInput,
				&system->joystickCount);
			system->joystickCount++;
			break;
		default:
			controller = new (sDirectInputHeap) ControllerDirectInput(instance, system->directInput, 0);
			break;
		}
		controller->next = system->controllers;
		system->controllers = controller;
		controller->AddRef();
		system->controllerCount++;
		return DIENUM_CONTINUE;
	}

	// FUNCTION: ENGINE 0x106436A0
	ControllerSystemDirectInput::ControllerSystemDirectInput(IControllerListener* newListener, int heap)
		: RefCount(1), listener(0), controllers(0), controllerCount(0), joystickCount(0), unknown24(0),
		previousProc(0), focused(true), enabled(true)
	{
		CoreName();
		CoInitialize(0);
		sDirectInputSystem = this;
		sDirectInputHeap = heap;
		IPlatformWin32* platform = GetPlatform();
		if (platform != 0)
		{
			platform->AddRef();
			void* window = platform->GetWindow();
			if (window != 0)
			{
				previousProc = SetWindowLongA(window, -4, (long)DirectInputWindowProc);
			}
			focused = true;
			if (CoCreateInstance(CLSID_DirectInput8, 0, CLSCTX_INPROC_SERVER, IID_IDirectInput8A,
				(void**)&directInput) >= 0)
			{
				directInput->Initialize(platform->GetInstance(), DIRECTINPUT_VERSION);
			}
			if (directInput != 0)
			{
				directInput->EnumDevices(DI8DEVCLASS_ALL, EnumDevicesCallback, this, DIEDFL_ATTACHEDONLY);
			}
			if (newListener != 0)
			{
				SetListener(newListener);
				for (ControllerDirectInput* controller = controllers; controller != 0; controller = controller->next)
				{
					newListener->OnControllerChanged(controller);
				}
			}
			platform->Release();
		}
	}

	// FUNCTION: ENGINE 0x106437F0
	void InitDirectInput(IControllerListener* listener, int heap, unsigned int options)
	{
		for (int i = 0; i < 256; i++)
		{
			gDirectInputKeys[i] = -1;
		}
		gDirectInputOptions = options;
		new (heap) ControllerSystemDirectInput(listener, heap);
		UpdateDirectInput();
	}
}
