// The XInput controllers (RTTI names core::ControllerSystemXInput, core::ControllerXInput,
// core::ControllerInputPointXInput, core::ControllerOutputPointXInput; vftables 0x10E47798, 0x10E476B4, 0x10E47754,
// 0x10E4772C and, for their RefCount bases, 0x10E47790, 0x10E476AC, 0x10E4774C, 0x10E47724). Unit 0x10648750 -
// 0x10649F5A (no assert path; file name controllerxinput.cpp, member and method names guessed). The system holds the
// four pads; a pad's points are arrays sized for the largest controller type and are set up from a static table of
// controller types (one: the XBox 360 controller) when the pad connects.
#ifndef CORE_CONTROLLERXINPUT_H
#define CORE_CONTROLLERXINPUT_H

#include "code/core/controller.h"
#include "code/core/object.h"

// xinput.h (XInput 1.3); the functions are imported by ordinal through the image's own jump thunks
struct XINPUT_GAMEPAD
{
	unsigned short wButtons;
	unsigned char bLeftTrigger;
	unsigned char bRightTrigger;
	short sThumbLX;
	short sThumbLY;
	short sThumbRX;
	short sThumbRY;
};

struct XINPUT_STATE
{
	unsigned long dwPacketNumber;
	XINPUT_GAMEPAD Gamepad;
};

struct XINPUT_VIBRATION
{
	unsigned short wLeftMotorSpeed;
	unsigned short wRightMotorSpeed;
};

struct XINPUT_CAPABILITIES
{
	unsigned char Type;
	unsigned char SubType;
	unsigned short Flags;
	XINPUT_GAMEPAD Gamepad;
	XINPUT_VIBRATION Vibration;
};

extern "C"
{
	unsigned long __stdcall XInputGetState(unsigned long userIndex, XINPUT_STATE* state);
	unsigned long __stdcall XInputSetState(unsigned long userIndex, XINPUT_VIBRATION* vibration);
	unsigned long __stdcall XInputGetCapabilities(unsigned long userIndex, unsigned long flags,
		XINPUT_CAPABILITIES* capabilities);
}

namespace core
{
	// Where a point's value sits in an XINPUT_GAMEPAD / XINPUT_VIBRATION
	struct XInputField
	{
		unsigned int offset;
		unsigned int size;
		unsigned int mask;
	};

	struct XInputPointDesc
	{
		const char* name;
		// Inputs: 0 button, 1 analog button, 2 / 3 axis (gXInputInputKinds); outputs: 0 analog
		unsigned int kind;
		XInputField field;
	};

	struct XInputControllerDesc
	{
		unsigned char subType;
		// Index into gXInputTypeNames
		unsigned int typeName;
		const char* name;
		unsigned int inputCount;
		XInputPointDesc* inputs;
		unsigned int outputCount;
		XInputPointDesc* outputs;
	};

	// 0x110BD178: the controller types and their count (0x110BD194); 0x110BCF9C, 0x110BCFAC, 0x110BCFBC: the type
	// names ("Joystick"), the input kind names ("Button", "AnalogButton", "XAxis", "YAxis") and the output kind
	// names ("Analog")
	extern XInputControllerDesc gXInputControllers[];
	extern unsigned int gXInputControllerCount;
	extern const char* gXInputTypeNames[];
	extern const char* gXInputInputKinds[];
	extern const char* gXInputOutputKinds[];

	class ControllerOutputPointXInput : public IControllerOutputPoint, public RefCount
	{
	public:
		ControllerOutputPointXInput();
		virtual ~ControllerOutputPointXInput();
		virtual void AddRef();
		virtual void Release();
		virtual const char* GetName();
		virtual const char* GetTypeName();
		virtual float GetValue();
		virtual void SetValue(float newValue);

		void Init(unsigned int type, unsigned int index, XINPUT_VIBRATION* vibration, float initialValue);
		// Writes a changed value into the vibration state; false when nothing changed
		bool Apply(XINPUT_VIBRATION* vibration);

		unsigned int controllerType;
		unsigned int index;
		float value;
		bool dirty;
		unsigned int steps;
	};

	class ControllerInputPointXInput : public IControllerInputPoint, public RefCount
	{
	public:
		ControllerInputPointXInput();
		virtual ~ControllerInputPointXInput();
		virtual void AddRef();
		virtual void Release();
		virtual const char* GetName();
		virtual const char* GetTypeName();
		virtual void SetThreshold(float newThreshold);
		virtual float GetThreshold();
		virtual void SetBinding(IControllerBinding* newBinding, void* userData);
		virtual void ClearBinding(IControllerBinding* oldBinding);
		virtual float Read(unsigned int* heldTimeOut);
		virtual void SetRange(float newMinimum, float newMaximum);
		virtual void GetRange(float* minimumOut, float* maximumOut);
		virtual unsigned int GetValueCount();
		virtual unsigned int ReadValues(unsigned int count, float* values);

		void Init(unsigned int type, unsigned int index, const XINPUT_GAMEPAD* gamepad);
		void Update(const XINPUT_GAMEPAD* gamepad);
		// The point's field of the gamepad state as a value in [0, 1] (axes: 0.5 at rest)
		float ConvertValue(const XINPUT_GAMEPAD* gamepad);

		unsigned int controllerType;
		unsigned int index;
		float value;
		float minimum;
		float maximum;
		float threshold;
		// Milliseconds from Init to the last change
		unsigned int heldTime;
		unsigned int initTime;
		unsigned int steps;
		IControllerBinding* binding;
		void* bindingData;
	};

	class ControllerXInput : public IController, public RefCount
	{
	public:
		ControllerXInput();
		virtual ~ControllerXInput();
		virtual void AddRef();
		virtual void Release();
		virtual bool IsConnected();
		virtual const char* GetName();
		virtual const char* GetTypeName();
		virtual const char* GetLocation();
		virtual bool Slot7();
		virtual int Slot8();
		virtual int Slot9(int a);
		virtual bool Slot10(int a, int b);
		virtual int Slot11();
		virtual int Slot12();
		virtual int Slot13(int a);
		virtual int Slot14(int a);
		virtual int Slot15(int a, int b);
		virtual int Slot16(int a);
		virtual unsigned int GetInputCount();
		virtual unsigned int CountInputs(const char* typeName);
		virtual IControllerInputPoint* FindInput(const char* typeName, unsigned int index);
		virtual IControllerInputPoint* FindInputByName(const char* name);
		virtual IControllerInputPoint* GetInput(unsigned int index);
		virtual unsigned int GetOutputCount();
		virtual unsigned int CountOutputs(const char* typeName);
		virtual IControllerOutputPoint* FindOutput(const char* typeName, unsigned int index);
		virtual IControllerOutputPoint* FindOutputByName(const char* name);
		virtual IControllerOutputPoint* GetOutput(unsigned int index);

		void Init(unsigned int pad, unsigned int joystick, int heap);
		void DestroyPoints();
		void Connect(const XINPUT_CAPABILITIES* capabilities);
		// Every input back to its rest value
		void ClearInputs();
		void Disconnect();
		void Update(bool active);

		unsigned int userIndex;
		char location[0x10];
		ControllerInputPointXInput* inputs;
		ControllerOutputPointXInput* outputs;
		int type;
		bool connected;
		XINPUT_VIBRATION vibration;
	};

	class ControllerSystemXInput : public IControllerSystem, public RefCount
	{
	public:
		ControllerSystemXInput(unsigned int joystick);
		virtual ~ControllerSystemXInput();
		virtual void AddRef();
		virtual void Release();
		virtual unsigned int GetControllerCount();
		virtual IController* GetController(unsigned int index);
		virtual IController* FindController(const char* location);
		virtual void SetListener(IControllerListener* newListener);
		virtual void ClearListener(IControllerListener* oldListener);
		virtual void SetEnabled(bool newEnabled);

		bool IsActive();
		void NotifyListener(IController* controller);
		unsigned int GetTime();
		void DestroyControllers();
		void Init(IControllerListener* newListener, int heap);
		void Update();

		IControllerListener* listener;
		ControllerXInput controllers[4];
		unsigned int time;
		unsigned int firstJoystick;
		long previousProc;
		bool focused;
		bool enabled;
	};

	IControllerSystem* GetXInputSystem();
	void InitXInput(IControllerListener* listener, int heap, unsigned int firstJoystick);
	void UpdateXInput();
	void ShutdownXInput();
}

#endif
