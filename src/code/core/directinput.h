// The parts of the Windows SDK (guiddef.h, oleauto.h, wbemcli.h) and the DirectX SDK (dinput.h, DirectInput 8)
// that the DirectInput controller unit uses, declared by hand: the toolchain has no SDK headers. Names, layouts,
// values and vtable orders are the SDK's. COM methods are __stdcall virtual functions.
#ifndef CORE_DIRECTINPUT_H
#define CORE_DIRECTINPUT_H

#include <string.h>

typedef struct _GUID
{
	unsigned long Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];
} GUID;

typedef const GUID& REFGUID;

// guiddef.h (C++): out-of-line COMDAT copies at 0x106412C0 / 0x10641360 / 0x10641370
__inline int IsEqualGUID(REFGUID rguid1, REFGUID rguid2)
{
	return !memcmp(&rguid1, &rguid2, sizeof(GUID));
}

__inline int operator==(REFGUID guidOne, REFGUID guidOther)
{
	return IsEqualGUID(guidOne, guidOther);
}

__inline int operator!=(REFGUID guidOne, REFGUID guidOther)
{
	return !(guidOne == guidOther);
}

typedef long HRESULT;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef long LONG;
typedef int BOOL;
typedef wchar_t* BSTR;

// oleauto.h: only the members IsXInputDevice reads
struct VARIANT
{
	unsigned short vt;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned short reserved3;
	union
	{
		BSTR bstrVal;
		long lVal;
		__int64 llVal;
	};
};

#define VT_BSTR 8

struct IUnknown
{
	virtual HRESULT __stdcall QueryInterface(REFGUID riid, void** object) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

// wbemcli.h: the WMI interfaces, unused slots as placeholders
struct IWbemClassObject : IUnknown
{
	virtual HRESULT __stdcall GetQualifierSet(void** qualifierSet) = 0;
	virtual HRESULT __stdcall Get(const wchar_t* name, long flags, VARIANT* value, long* type, long* flavor) = 0;
};

struct IEnumWbemClassObject : IUnknown
{
	virtual HRESULT __stdcall Reset() = 0;
	virtual HRESULT __stdcall Next(long timeout, unsigned long count, IWbemClassObject** objects,
		unsigned long* returned) = 0;
};

struct IWbemServices : IUnknown
{
	virtual HRESULT __stdcall OpenNamespace() = 0;
	virtual HRESULT __stdcall CancelAsyncCall() = 0;
	virtual HRESULT __stdcall QueryObjectSink() = 0;
	virtual HRESULT __stdcall GetObject() = 0;
	virtual HRESULT __stdcall GetObjectAsync() = 0;
	virtual HRESULT __stdcall PutClass() = 0;
	virtual HRESULT __stdcall PutClassAsync() = 0;
	virtual HRESULT __stdcall DeleteClass() = 0;
	virtual HRESULT __stdcall DeleteClassAsync() = 0;
	virtual HRESULT __stdcall CreateClassEnum() = 0;
	virtual HRESULT __stdcall CreateClassEnumAsync() = 0;
	virtual HRESULT __stdcall PutInstance() = 0;
	virtual HRESULT __stdcall PutInstanceAsync() = 0;
	virtual HRESULT __stdcall DeleteInstance() = 0;
	virtual HRESULT __stdcall DeleteInstanceAsync() = 0;
	virtual HRESULT __stdcall CreateInstanceEnum(const BSTR filter, long flags, void* context,
		IEnumWbemClassObject** enumerator) = 0;
};

struct __declspec(uuid("dc12a687-737f-11cf-884d-00aa004b2e24")) IWbemLocator : IUnknown
{
	virtual HRESULT __stdcall ConnectServer(const BSTR networkResource, const BSTR user, const BSTR password,
		const BSTR locale, long securityFlags, const BSTR authority, void* context, IWbemServices** services) = 0;
};

class __declspec(uuid("4590f811-1d3a-11d0-891f-00aa004b2e24")) WbemLocator;

#define CLSCTX_INPROC_SERVER 1
#define RPC_C_AUTHN_WINNT 10
#define RPC_C_AUTHZ_NONE 0
#define RPC_C_AUTHN_LEVEL_CALL 3
#define RPC_C_IMP_LEVEL_IMPERSONATE 3
#define EOAC_NONE 0

// dinput.h (DIRECTINPUT_VERSION 0x0800, ANSI)
#define MAX_PATH 260

struct DIDEVICEINSTANCEA
{
	DWORD dwSize;
	GUID guidInstance;
	GUID guidProduct;
	DWORD dwDevType;
	char tszInstanceName[MAX_PATH];
	char tszProductName[MAX_PATH];
	GUID guidFFDriver;
	WORD wUsagePage;
	WORD wUsage;
};

struct DIDEVICEOBJECTINSTANCEA
{
	DWORD dwSize;
	GUID guidType;
	DWORD dwOfs;
	DWORD dwType;
	DWORD dwFlags;
	char tszName[MAX_PATH];
	DWORD dwFFMaxForce;
	DWORD dwFFForceResolution;
	WORD wCollectionNumber;
	WORD wDesignatorIndex;
	WORD wUsagePage;
	WORD wUsage;
	DWORD dwDimension;
	WORD wExponent;
	WORD wReportId;
};

struct DIPROPHEADER
{
	DWORD dwSize;
	DWORD dwHeaderSize;
	DWORD dwObj;
	DWORD dwHow;
};

struct DIPROPDWORD
{
	DIPROPHEADER diph;
	DWORD dwData;
};

struct DIOBJECTDATAFORMAT
{
	const GUID* pguid;
	DWORD dwOfs;
	DWORD dwType;
	DWORD dwFlags;
};

struct DIDATAFORMAT
{
	DWORD dwSize;
	DWORD dwObjSize;
	DWORD dwFlags;
	DWORD dwDataSize;
	DWORD dwNumObjs;
	DIOBJECTDATAFORMAT* rgodf;
};

struct DICONSTANTFORCE
{
	LONG lMagnitude;
};

struct DIEFFECT
{
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwDuration;
	DWORD dwSamplePeriod;
	DWORD dwGain;
	DWORD dwTriggerButton;
	DWORD dwTriggerRepeatInterval;
	DWORD cAxes;
	DWORD* rgdwAxes;
	LONG* rglDirection;
	void* lpEnvelope;
	DWORD cbTypeSpecificParams;
	void* lpvTypeSpecificParams;
	DWORD dwStartDelay;
};

typedef BOOL (__stdcall* LPDIENUMDEVICESCALLBACKA)(const DIDEVICEINSTANCEA* instance, void* context);
typedef BOOL (__stdcall* LPDIENUMDEVICEOBJECTSCALLBACKA)(const DIDEVICEOBJECTINSTANCEA* object, void* context);

struct IDirectInputEffect : IUnknown
{
	virtual HRESULT __stdcall Initialize() = 0;
	virtual HRESULT __stdcall GetEffectGuid() = 0;
	virtual HRESULT __stdcall GetParameters() = 0;
	virtual HRESULT __stdcall SetParameters(const DIEFFECT* effect, DWORD flags) = 0;
	virtual HRESULT __stdcall Start() = 0;
	virtual HRESULT __stdcall Stop() = 0;
};

struct IDirectInputDevice8A : IUnknown
{
	virtual HRESULT __stdcall GetCapabilities() = 0;
	virtual HRESULT __stdcall EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA callback, void* context, DWORD flags) = 0;
	virtual HRESULT __stdcall GetProperty(const GUID& property, DIPROPHEADER* header) = 0;
	virtual HRESULT __stdcall SetProperty(const GUID& property, const DIPROPHEADER* header) = 0;
	virtual HRESULT __stdcall Acquire() = 0;
	virtual HRESULT __stdcall Unacquire() = 0;
	virtual HRESULT __stdcall GetDeviceState(DWORD size, void* data) = 0;
	virtual HRESULT __stdcall GetDeviceData() = 0;
	virtual HRESULT __stdcall SetDataFormat(const DIDATAFORMAT* format) = 0;
	virtual HRESULT __stdcall SetEventNotification() = 0;
	virtual HRESULT __stdcall SetCooperativeLevel(void* window, DWORD flags) = 0;
	virtual HRESULT __stdcall GetObjectInfo() = 0;
	virtual HRESULT __stdcall GetDeviceInfo() = 0;
	virtual HRESULT __stdcall RunControlPanel() = 0;
	virtual HRESULT __stdcall Initialize() = 0;
	virtual HRESULT __stdcall CreateEffect(REFGUID guid, const DIEFFECT* effect, IDirectInputEffect** out,
		IUnknown* outer) = 0;
	virtual HRESULT __stdcall EnumEffects() = 0;
	virtual HRESULT __stdcall GetEffectInfo() = 0;
	virtual HRESULT __stdcall GetForceFeedbackState() = 0;
	virtual HRESULT __stdcall SendForceFeedbackCommand() = 0;
	virtual HRESULT __stdcall EnumCreatedEffectObjects() = 0;
	virtual HRESULT __stdcall Escape() = 0;
	virtual HRESULT __stdcall Poll() = 0;
};

struct IDirectInput8A : IUnknown
{
	virtual HRESULT __stdcall CreateDevice(REFGUID guid, IDirectInputDevice8A** device, IUnknown* outer) = 0;
	virtual HRESULT __stdcall EnumDevices(DWORD type, LPDIENUMDEVICESCALLBACKA callback, void* context,
		DWORD flags) = 0;
	virtual HRESULT __stdcall GetDeviceStatus(REFGUID guid) = 0;
	virtual HRESULT __stdcall RunControlPanel() = 0;
	virtual HRESULT __stdcall Initialize(void* instance, DWORD version) = 0;
};

// dxguid.lib, statically linked (mapped in symbols.txt)
extern "C"
{
	extern const GUID CLSID_DirectInput8;
	extern const GUID IID_IDirectInput8A;
	extern const GUID GUID_XAxis;
	extern const GUID GUID_YAxis;
	extern const GUID GUID_ZAxis;
	extern const GUID GUID_RxAxis;
	extern const GUID GUID_RyAxis;
	extern const GUID GUID_RzAxis;
	extern const GUID GUID_Slider;
	extern const GUID GUID_Button;
	extern const GUID GUID_Key;
	extern const GUID GUID_POV;
	extern const GUID GUID_Unknown;
	extern const GUID GUID_ConstantForce;
}

#define DIRECTINPUT_VERSION 0x0800
#define DI8DEVCLASS_ALL 0
#define DIEDFL_ATTACHEDONLY 1
#define DIENUM_STOP 0
#define DIENUM_CONTINUE 1
#define DIDFT_ALL 0
#define DIDOI_FFACTUATOR 1

#define DI8DEVTYPE_MOUSE 0x12
#define DI8DEVTYPE_KEYBOARD 0x13
#define DI8DEVTYPE_JOYSTICK 0x14
#define DI8DEVTYPE_GAMEPAD 0x15
#define DI8DEVTYPE_DRIVING 0x16
#define DI8DEVTYPE_FLIGHT 0x17
#define DI8DEVTYPE_1STPERSON 0x18

#define DIDFT_RELAXIS 1
#define DIDFT_ABSAXIS 2
#define DIDFT_PSHBUTTON 4
#define DIDFT_TGLBUTTON 8
#define DIDFT_POV 0x10

#define DIDF_ABSAXIS 1
#define DIDF_RELAXIS 2

#define DISCL_EXCLUSIVE 1
#define DISCL_NONEXCLUSIVE 2
#define DISCL_FOREGROUND 4
#define DISCL_BACKGROUND 8

#define DIPH_DEVICE 0
#define DIPROPAUTOCENTER_OFF 0
// The property GUIDs are small integers (MAKEDIPROP)
#define DIPROP_AUTOCENTER (*(const GUID*)9)
#define DIPROP_JOYSTICKID (*(const GUID*)15)

#define DIEFF_OBJECTOFFSETS 0x02
#define DIEFF_CARTESIAN 0x10
#define DIEB_NOTRIGGER 0xFFFFFFFF
#define DI_FFNOMINALMAX 10000
#define DIEP_TYPESPECIFICPARAMS 0x00000100
#define DIEP_START 0x20000000
#define INFINITE 0xFFFFFFFF
#define DI_OK 0

#endif
