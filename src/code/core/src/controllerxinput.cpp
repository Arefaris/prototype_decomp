#include <string.h>

#include "code/core/controllerxinput.h"
#include "code/core/platform.h"
#include "code/core/strings.h"

// The user32 imports (see controllerdirectinput.cpp)
extern "C"
{
	__declspec(dllimport) long __stdcall SetWindowLongA(void* window, int index, long value);
	__declspec(dllimport) long __stdcall CallWindowProcA(long procedure, void* window, unsigned int message,
		unsigned int wParam, long lParam);
}
#pragma comment(linker, "/alternatename:__imp__SetWindowLongA@12=__imp__SetWindowLongA")
#pragma comment(linker, "/alternatename:__imp__CallWindowProcA@20=__imp__CallWindowProcA")

namespace core
{
	const char* CoreName();
	unsigned int GetMilliseconds();

	// GLOBAL: ENGINE 0x1127ABEC
	static ControllerSystemXInput* sXInputSystem;

	// FUNCTION: ENGINE 0x10648750
	inline unsigned int ReadField(const XInputField* field, const void* state)
	{
		return *(const unsigned int*)((const char*)state + field->offset) & field->mask;
	}

	// FUNCTION: ENGINE 0x10648770
	inline void WriteField(const XInputField* field, void* state, unsigned int value)
	{
		unsigned int* target = (unsigned int*)((char*)state + field->offset);
		*target &= ~field->mask;
		*target |= field->mask & value;
	}

	// FUNCTION: ENGINE 0x10648790
	bool ControllerSystemXInput::IsActive()
	{
		if (enabled)
		{
			return focused;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106487B0
	IControllerSystem* GetXInputSystem()
	{
		return sXInputSystem;
	}

	// FUNCTION: ENGINE 0x106487C0
	IController* ControllerSystemXInput::FindController(const char* location)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			ControllerXInput* controller = &controllers[i];
			if (controller->IsConnected() && strcmp(controller->GetLocation(), location) == 0)
			{
				return &controllers[i];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10648850
	IController* ControllerSystemXInput::GetController(unsigned int index)
	{
		unsigned int count = 0;
		for (unsigned int i = 0; i < 4; i++)
		{
			ControllerXInput* controller = &controllers[i];
			if (controller->IsConnected())
			{
				if (count == index)
				{
					return &controllers[i];
				}
				count++;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x106488A0
	unsigned int ControllerSystemXInput::GetControllerCount()
	{
		unsigned int count = 0;
		for (unsigned int i = 0; i < 4; i++)
		{
			ControllerXInput* controller = &controllers[i];
			if (controller->IsConnected())
			{
				count++;
			}
		}
		return count;
	}

	// FUNCTION: ENGINE 0x106488D0
	void ControllerSystemXInput::SetListener(IControllerConnectionChangeCallback* newListener)
	{
		if (listener == 0)
		{
			listener = newListener;
		}
	}

	// FUNCTION: ENGINE 0x106488E0
	void ControllerSystemXInput::ClearListener(IControllerConnectionChangeCallback* oldListener)
	{
		if (listener == oldListener)
		{
			listener = 0;
		}
	}

	// FUNCTION: ENGINE 0x10648900
	void ControllerSystemXInput::NotifyListener(IController* controller)
	{
		if (listener != 0)
		{
			listener->OnControllerChanged(controller);
		}
	}

	// FUNCTION: ENGINE 0x10648920
	unsigned int ControllerSystemXInput::GetTime()
	{
		return time;
	}

	// FUNCTION: ENGINE 0x10648930
	// Subclasses the application window: tracks whether it has the focus
	static long __stdcall XInputWindowProc(void* window, unsigned int message, unsigned int wParam, long lParam)
	{
		ControllerSystemXInput* system = sXInputSystem;
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

	// FUNCTION: ENGINE 0x10648990
	ControllerXInput::~ControllerXInput()
	{
	}

	// FUNCTION: ENGINE 0x106489F0
	bool ControllerXInput::Slot7()
	{
		return false;
	}

	// FUNCTION: ENGINE 0x10648A00
	int ControllerXInput::Slot8()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10648A10
	int ControllerXInput::Slot9(int a)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10648A20
	bool ControllerXInput::Slot10(int a, int b)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x10648A30
	int ControllerXInput::Slot11()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10648A40
	int ControllerXInput::Slot12()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10648A50
	int ControllerXInput::Slot13(int a)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10648A60
	int ControllerXInput::Slot14(int a)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10648A70
	int ControllerXInput::Slot15(int a, int b)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10648A80
	int ControllerXInput::Slot16(int a)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10648A90
	bool ControllerXInput::IsConnected()
	{
		return connected;
	}

	// FUNCTION: ENGINE 0x10648AA0
	const char* ControllerXInput::GetName()
	{
		if (connected)
		{
			return gXInputControllers[type].name;
		}
		return "Unknown";
	}

	// FUNCTION: ENGINE 0x10648AC0
	const char* ControllerXInput::GetTypeName()
	{
		if (connected)
		{
			return gXInputTypeNames[gXInputControllers[type].typeName];
		}
		return "Unknown";
	}

	// FUNCTION: ENGINE 0x10648AF0
	const char* ControllerXInput::GetLocation()
	{
		return location;
	}

	// FUNCTION: ENGINE 0x10648B00
	unsigned int ControllerXInput::GetInputCount()
	{
		if (connected)
		{
			return gXInputControllers[type].inputCount;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10648B20
	unsigned int ControllerXInput::CountInputs(const char* typeName)
	{
		unsigned int count = 0;
		unsigned int inputCount = GetInputCount();
		for (unsigned int i = 0; i < inputCount; i++)
		{
			if (strcmp(inputs[i].GetTypeName(), typeName) == 0)
			{
				count++;
			}
		}
		return count;
	}

	// FUNCTION: ENGINE 0x10648BB0
	IControllerInputPoint* ControllerXInput::FindInput(const char* typeName, unsigned int index)
	{
		unsigned int count = 0;
		unsigned int inputCount = GetInputCount();
		for (unsigned int i = 0; i < inputCount; i++)
		{
			if (strcmp(inputs[i].GetTypeName(), typeName) == 0)
			{
				if (count == index)
				{
					return &inputs[i];
				}
				count++;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10648C50
	IControllerInputPoint* ControllerXInput::FindInputByName(const char* name)
	{
		unsigned int inputCount = GetInputCount();
		for (unsigned int i = 0; i < inputCount; i++)
		{
			if (strcmp(inputs[i].GetName(), name) == 0)
			{
				return &inputs[i];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10648CE0
	IControllerInputPoint* ControllerXInput::GetInput(unsigned int index)
	{
		if (index >= GetInputCount())
		{
			return 0;
		}
		return &inputs[index];
	}

	// FUNCTION: ENGINE 0x10648D10
	unsigned int ControllerXInput::GetOutputCount()
	{
		if (type >= 0)
		{
			return gXInputControllers[type].outputCount;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10648D30
	unsigned int ControllerXInput::CountOutputs(const char* typeName)
	{
		unsigned int count = 0;
		unsigned int outputCount = GetOutputCount();
		for (unsigned int i = 0; i < outputCount; i++)
		{
			if (strcmp(outputs[i].GetTypeName(), typeName) == 0)
			{
				count++;
			}
		}
		return count;
	}

	// FUNCTION: ENGINE 0x10648DC0
	IControllerOutputPoint* ControllerXInput::FindOutput(const char* typeName, unsigned int index)
	{
		unsigned int count = 0;
		unsigned int outputCount = GetOutputCount();
		for (unsigned int i = 0; i < outputCount; i++)
		{
			if (strcmp(outputs[i].GetTypeName(), typeName) == 0)
			{
				if (count == index)
				{
					return &outputs[i];
				}
				count++;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10648E60
	IControllerOutputPoint* ControllerXInput::FindOutputByName(const char* name)
	{
		unsigned int outputCount = GetOutputCount();
		for (unsigned int i = 0; i < outputCount; i++)
		{
			if (strcmp(outputs[i].GetName(), name) == 0)
			{
				return &outputs[i];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10648EF0
	IControllerOutputPoint* ControllerXInput::GetOutput(unsigned int index)
	{
		if (index >= GetOutputCount())
		{
			return 0;
		}
		return &outputs[index];
	}

	// FUNCTION: ENGINE 0x10648F20
	void ControllerXInput::DestroyPoints()
	{
		delete[] inputs;
		delete[] outputs;
	}

	// FUNCTION: ENGINE 0x10648F70
	ControllerOutputPointXInput::~ControllerOutputPointXInput()
	{
	}

	// FUNCTION: ENGINE 0x10648FA0
	// The controller's name, not the point's
	const char* ControllerOutputPointXInput::GetName()
	{
		return gXInputControllers[controllerType].name;
	}

	// FUNCTION: ENGINE 0x10648FC0
	const char* ControllerOutputPointXInput::GetTypeName()
	{
		return gXInputOutputKinds[gXInputControllers[controllerType].outputs[index].kind];
	}

	// FUNCTION: ENGINE 0x10648FF0
	float ControllerOutputPointXInput::GetValue()
	{
		return value;
	}

	// FUNCTION: ENGINE 0x10649000
	void ControllerOutputPointXInput::SetValue(float newValue)
	{
		if (newValue == value)
		{
			return;
		}

		dirty = true;
		if (newValue >= 1.0f)
		{
			value = 1.0f;
		}
		else if (newValue <= 0.0f)
		{
			value = 0.0f;
		}
		else
		{
			value = newValue;
		}
	}

	// FUNCTION: ENGINE 0x10649040
	void ControllerOutputPointXInput::Init(unsigned int type, unsigned int newIndex, XINPUT_VIBRATION* vibration,
		float initialValue)
	{
		controllerType = type;
		index = newIndex;
		value = initialValue;
		dirty = true;
		steps = (1 << (gXInputControllers[type].outputs[newIndex].field.size * 8)) - 1;
	}

	// FUNCTION: ENGINE 0x10649090
	bool ControllerOutputPointXInput::Apply(XINPUT_VIBRATION* vibration)
	{
		if (dirty)
		{
			WriteField(&gXInputControllers[controllerType].outputs[index].field, vibration,
				(unsigned int)(steps * value));
			dirty = false;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10649120
	ControllerInputPointXInput::~ControllerInputPointXInput()
	{
	}

	// FUNCTION: ENGINE 0x10649150
	unsigned int ControllerInputPointXInput::GetValueCount()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10649160
	unsigned int ControllerInputPointXInput::ReadValues(unsigned int count, float* values)
	{
		if (count > 0 && values != 0)
		{
			values[0] = Read(0);
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x10649190
	const char* ControllerInputPointXInput::GetName()
	{
		return gXInputControllers[controllerType].inputs[index].name;
	}

	// FUNCTION: ENGINE 0x106491B0
	const char* ControllerInputPointXInput::GetTypeName()
	{
		return gXInputInputKinds[gXInputControllers[controllerType].inputs[index].kind];
	}

	// FUNCTION: ENGINE 0x106491E0
	void ControllerInputPointXInput::SetThreshold(float newThreshold)
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

	// FUNCTION: ENGINE 0x10649210
	float ControllerInputPointXInput::GetThreshold()
	{
		return threshold;
	}

	// FUNCTION: ENGINE 0x10649220
	void ControllerInputPointXInput::SetBinding(IControllerBinding* newBinding, void* userData)
	{
		if (binding == 0)
		{
			bindingData = userData;
			binding = newBinding;
		}
	}

	// FUNCTION: ENGINE 0x10649240
	void ControllerInputPointXInput::ClearBinding(IControllerBinding* oldBinding)
	{
		if (binding == oldBinding)
		{
			binding = 0;
			bindingData = 0;
		}
	}

	// FUNCTION: ENGINE 0x10649260
	float ControllerInputPointXInput::Read(unsigned int* heldTimeOut)
	{
		if (heldTimeOut != 0)
		{
			*heldTimeOut = heldTime;
		}
		return minimum + (maximum - minimum) * value;
	}

	// FUNCTION: ENGINE 0x10649280
	void ControllerInputPointXInput::SetRange(float newMinimum, float newMaximum)
	{
		minimum = newMinimum;
		maximum = newMaximum;
	}

	// FUNCTION: ENGINE 0x106492A0
	void ControllerInputPointXInput::GetRange(float* minimumOut, float* maximumOut)
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

	// FUNCTION: ENGINE 0x106492C0
	float ControllerInputPointXInput::ConvertValue(const XINPUT_GAMEPAD* gamepad)
	{
		const XInputPointDesc* desc = &gXInputControllers[controllerType].inputs[index];
		unsigned int raw = ReadField(&desc->field, gamepad);
		float result = 0.0f;
		switch (desc->kind)
		{
		case 0:
			result = raw != 0 ? 1.0f : 0.0f;
			break;
		case 1:
			return (float)raw / (float)steps;
		case 2:
		case 3:
			{
				unsigned int half = steps >> 1;
				if (raw <= half)
				{
					return (float)raw / (float)(half * 2) + 0.5f;
				}
				return 0.5f - (float)(steps - raw + 1) / (float)(half * 2 + 2);
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x106493E0
	void ControllerXInput::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x106493F0
	void ControllerXInput::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x10649420
	void ControllerOutputPointXInput::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x10649430
	void ControllerOutputPointXInput::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x10649460
	void ControllerInputPointXInput::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x10649470
	void ControllerInputPointXInput::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x106494A0
	ControllerSystemXInput::~ControllerSystemXInput()
	{
	}

	// FUNCTION: ENGINE 0x106494F0
	void ControllerSystemXInput::SetEnabled(bool newEnabled)
	{
		enabled = newEnabled;
	}

	// FUNCTION: ENGINE 0x10649510
	void ControllerSystemXInput::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x10649520
	void ControllerSystemXInput::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x10649550
	void ControllerSystemXInput::DestroyControllers()
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			controllers[i].DestroyPoints();
		}
	}

	// FUNCTION: ENGINE 0x10649580
	ControllerXInput::ControllerXInput()
		: RefCount(1)
	{
		memset(&vibration, 0, sizeof(vibration));
		CoreName();
	}

	// FUNCTION: ENGINE 0x10649730
	ControllerOutputPointXInput::ControllerOutputPointXInput()
		: RefCount(1)
	{
		CoreName();
	}

	// FUNCTION: ENGINE 0x10649780
	ControllerInputPointXInput::ControllerInputPointXInput()
		: RefCount(1)
	{
		CoreName();
	}

	// FUNCTION: ENGINE 0x106497D0
	void ControllerInputPointXInput::Init(unsigned int type, unsigned int newIndex, const XINPUT_GAMEPAD* gamepad)
	{
		controllerType = type;
		index = newIndex;
		minimum = 0.0f;
		maximum = 1.0f;
		threshold = 0.0f;
		heldTime = 0;
		initTime = sXInputSystem->GetTime();
		steps = (1 << (gXInputControllers[type].inputs[newIndex].field.size * 8)) - 1;
		value = ConvertValue(gamepad);
		binding = 0;
		bindingData = 0;
	}

	// FUNCTION: ENGINE 0x10649860
	void ControllerInputPointXInput::Update(const XINPUT_GAMEPAD* gamepad)
	{
		float newValue = ConvertValue(gamepad);
		if (newValue != value)
		{
			if (newValue - value >= threshold || value - newValue >= threshold)
			{
				value = newValue;
				heldTime = sXInputSystem->GetTime() - initTime;
				if (binding != 0)
				{
					binding->OnChange(bindingData, minimum + (maximum - minimum) * newValue);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10649910
	void ShutdownXInput()
	{
		sXInputSystem->DestroyControllers();
		delete sXInputSystem;
		sXInputSystem = 0;
	}

	// FUNCTION: ENGINE 0x10649940
	ControllerSystemXInput::ControllerSystemXInput(unsigned int joystick)
		: RefCount(1), listener(0), firstJoystick(joystick), previousProc(0), focused(true), enabled(true)
	{
		CoreName();
		IPlatformWin32* platform = GetPlatform();
		if (platform != 0)
		{
			platform->AddRef();
			void* window = platform->GetWindow();
			if (window != 0)
			{
				previousProc = SetWindowLongA(window, -4, (long)XInputWindowProc);
			}
			focused = true;
			platform->Release();
		}
	}

	// FUNCTION: ENGINE 0x10649A50
	void ControllerXInput::Init(unsigned int pad, unsigned int joystick, int heap)
	{
		userIndex = pad;
		SNPrintf(location, sizeof(location), "%s%d", "Joystick", joystick);
		unsigned int maxInputs = 0;
		unsigned int maxOutputs = 0;
		for (unsigned int i = 0; i < gXInputControllerCount; i++)
		{
			if (gXInputControllers[i].inputCount > maxInputs)
			{
				maxInputs = gXInputControllers[i].inputCount;
			}
			if (gXInputControllers[i].outputCount > maxOutputs)
			{
				maxOutputs = gXInputControllers[i].outputCount;
			}
		}
		inputs = new (heap) ControllerInputPointXInput[maxInputs];
		outputs = new (heap) ControllerOutputPointXInput[maxOutputs];
		type = -1;
		connected = false;
	}

	// FUNCTION: ENGINE 0x10649BA0
	// Unknown controller types are taken for the first one
	void ControllerXInput::Connect(const XINPUT_CAPABILITIES* capabilities)
	{
		int newType = -1;
		for (unsigned int j = 0; j < gXInputControllerCount; j++)
		{
			if (gXInputControllers[j].subType == capabilities->SubType)
			{
				newType = j;
				break;
			}
		}
		if (newType < 0)
		{
			newType = 0;
		}
		if (type > 0 && newType != type)
		{
			return;
		}
		unsigned int i;
		for (i = 0; i < gXInputControllers[newType].inputCount; i++)
		{
			inputs[i].Init(newType, i, &capabilities->Gamepad);
		}
		for (i = 0; i < gXInputControllers[newType].outputCount; i++)
		{
			outputs[i].Init(newType, i, (XINPUT_VIBRATION*)&capabilities->Vibration, 0.0f);
		}
		type = newType;
		connected = true;
		sXInputSystem->NotifyListener(this);
	}

	// FUNCTION: ENGINE 0x10649C90
	void ControllerXInput::ClearInputs()
	{
		XINPUT_GAMEPAD rest;
		rest.wButtons = 0;
		rest.bLeftTrigger = 0;
		rest.bRightTrigger = 0;
		rest.sThumbLX = 0;
		rest.sThumbLY = 0;
		rest.sThumbRX = 0;
		rest.sThumbRY = 0;
		for (unsigned int i = 0; i < gXInputControllers[type].inputCount; i++)
		{
			inputs[i].Update(&rest);
		}
	}

	// FUNCTION: ENGINE 0x10649D10
	void ControllerSystemXInput::Init(IControllerConnectionChangeCallback* newListener, int heap)
	{
		time = GetTime();
		if (newListener != 0)
		{
			SetListener(newListener);
		}
		for (unsigned int i = 0; i < 4; i++)
		{
			controllers[i].Init(i, firstJoystick + i, heap);
		}
	}

	// FUNCTION: ENGINE 0x10649D70
	void ControllerXInput::Disconnect()
	{
		ClearInputs();
		connected = false;
		sXInputSystem->NotifyListener(this);
	}

	// FUNCTION: ENGINE 0x10649D90
	void ControllerXInput::Update(bool active)
	{
		XINPUT_STATE state;
		XINPUT_CAPABILITIES capabilities;
		unsigned long result = XInputGetCapabilities(userIndex, 0, &capabilities);
		if (result == 0)
		{
			result = XInputGetState(userIndex, &state);
		}
		if (!connected)
		{
			if (result == 0)
			{
				Connect(&capabilities);
			}
			if (!connected)
			{
				return;
			}
		}
		if (result != 0)
		{
			Disconnect();
		}
		if (!connected)
		{
			return;
		}
		if (active)
		{
			unsigned int i;
			for (i = 0; i < gXInputControllers[type].inputCount; i++)
			{
				inputs[i].Update(&state.Gamepad);
			}
			bool changed = false;
			for (i = 0; i < gXInputControllers[type].outputCount; i++)
			{
				changed = outputs[i].Apply(&vibration) || changed;
			}
			if (changed)
			{
				XInputSetState(userIndex, &vibration);
			}
		}
		else
		{
			ClearInputs();
		}
	}

	// FUNCTION: ENGINE 0x10649EC0
	void ControllerSystemXInput::Update()
	{
		time = GetMilliseconds();
		for (unsigned int i = 0; i < 4; i++)
		{
			controllers[i].Update(IsActive());
		}
	}

	// FUNCTION: ENGINE 0x10649F00
	void InitXInput(IControllerConnectionChangeCallback* listener, int heap, unsigned int firstJoystick)
	{
		sXInputSystem = new (heap) ControllerSystemXInput(firstJoystick);
		sXInputSystem->Init(listener, heap);
		sXInputSystem->Update();
	}

	// FUNCTION: ENGINE 0x10649F50
	void UpdateXInput()
	{
		sXInputSystem->Update();
	}
}
