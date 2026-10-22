// The DirectInput 8 controllers (RTTI names core::ControllerSystemDirectInput, core::ControllerDirectInput,
// core::ControllerInputPointDirectInput, core::ControllerOutputPointDirectInput; vftables 0x10E46F7C, 0x10E46FB4,
// 0x10E46E74, 0x10E4702C and, for their RefCount bases, 0x10E46F74, 0x10E46FA8, 0x10E46E68, 0x10E47024). Unit
// 0x106412C0 - 0x10643835 (no assert path; file name controllerdirectinput.cpp, member and method names guessed).
// The system enumerates the attached devices (XInput pads left out) and keeps one controller per device; a
// controller reads its device's objects into one DWORD each (its own data format) and keeps an input point per
// object and an output point (a constant force effect) per force-feedback actuator.
#ifndef CORE_CONTROLLERDIRECTINPUT_H
#define CORE_CONTROLLERDIRECTINPUT_H

#include "code/core/controller.h"
#include "code/core/directinput.h"
#include "code/core/istring.h"
#include "code/core/object.h"
#include "code/core/refptr.h"

namespace core
{
	class ControllerDirectInput;

	class ControllerInputPointDirectInput : public IControllerInputPoint, public RefCount
	{
	public:
		ControllerInputPointDirectInput(ControllerDirectInput* controller, const DIDEVICEOBJECTINSTANCEA* object,
			int unused);
		virtual ~ControllerInputPointDirectInput();
		virtual void AddRef();
		virtual void Release();
		virtual const char* GetName();
		virtual const char* GetTypeName();
		virtual void SetThreshold(float threshold);
		virtual float GetThreshold();
		virtual void SetBinding(IControllerBinding* binding, void* userData);
		virtual void ClearBinding(IControllerBinding* binding);
		virtual float Read(unsigned int* heldTime);
		virtual void SetRange(float minimum, float maximum);
		virtual void GetRange(float* minimum, float* maximum);
		virtual unsigned int GetValueCount();
		virtual unsigned int ReadValues(unsigned int count, float* values);
		// Takes the object's DWORD of the device state (valid false: the device could not be read)
		virtual void Update(unsigned int time, DWORD raw, bool valid);

		// The raw DWORD as a value in [0, 1] (relative axes: the movement); `previous` is unused
		float ConvertValue(float previous, DWORD raw);
		// The value at rest: 0.5 for absolute axes, 1 for points of view, else 0
		float GetRestValue();
		DWORD GetDataType();
		void Reset(unsigned int time);

		float value;
		unsigned int heldTime;
		unsigned int changeTime;
		float threshold;
		float minimum;
		float maximum;
		DIDEVICEOBJECTINSTANCEA object;
		IControllerBinding* binding;
		void* bindingData;
		ControllerInputPointDirectInput* next;
	};

	class ControllerOutputPointDirectInput : public IControllerOutputPoint, public RefCount
	{
	public:
		ControllerOutputPointDirectInput(const DIDEVICEOBJECTINSTANCEA* object, DWORD offset);
		virtual ~ControllerOutputPointDirectInput();
		virtual void AddRef();
		virtual void Release();
		virtual const char* GetName();
		virtual const char* GetTypeName();
		virtual float GetValue();
		virtual void SetValue(float value);

		bool CreateEffect(IDirectInputDevice8A* device);
		// Starts, changes or stops the effect when the value has changed
		void Update(IDirectInputDevice8A* device);

		DIDEVICEOBJECTINSTANCEA object;
		RefPtr<IDirectInputEffect> effect;
		DICONSTANTFORCE force;
		DIEFFECT parameters;
		DWORD axes[1];
		LONG direction[1];
		float value;
		float appliedValue;
		bool created;
		ControllerOutputPointDirectInput* next;
	};

	class ControllerDirectInput : public IController, public RefCount
	{
	public:
		ControllerDirectInput(const DIDEVICEINSTANCEA* instance, RefPtr<IDirectInput8A> directInput,
			unsigned int* index);
		virtual ~ControllerDirectInput();
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

		// Reads the device (when active, or always for background devices) and updates every point
		void Update(unsigned int time, bool active);

		DIDEVICEINSTANCEA instance;
		RefPtr<IDirectInput8A> directInput;
		RefPtr<IDirectInputDevice8A> device;
		DWORD* state;
		ControllerInputPointDirectInput* inputs;
		ControllerInputPointDirectInput* lastInput;
		unsigned int inputCount;
		ControllerOutputPointDirectInput* outputs;
		ControllerOutputPointDirectInput* lastOutput;
		unsigned int outputCount;
		RefPtr<IString> location;
		ControllerDirectInput* next;
		bool connected;
		DWORD cooperativeLevel;
	};

	class ControllerSystemDirectInput : public IControllerSystem, public RefCount
	{
	public:
		ControllerSystemDirectInput(IControllerConnectionChangeCallback* listener, int heap);
		virtual ~ControllerSystemDirectInput();
		virtual void AddRef();
		virtual void Release();
		virtual unsigned int GetControllerCount();
		virtual IController* GetController(unsigned int index);
		virtual IController* FindController(const char* location);
		virtual void SetListener(IControllerConnectionChangeCallback* listener);
		virtual void ClearListener(IControllerConnectionChangeCallback* listener);
		virtual void SetEnabled(bool enabled);
		virtual void Update();

		bool IsActive();
		void NotifyListener(IController* controller);
		unsigned int GetJoystickCount();

		IControllerConnectionChangeCallback* listener;
		RefPtr<IDirectInput8A> directInput;
		ControllerDirectInput* controllers;
		unsigned int controllerCount;
		unsigned int joystickCount;
		unsigned int unknown24;
		long previousProc;
		bool focused;
		bool enabled;
	};

	// Options of InitDirectInput
	enum
	{
		DIRECTINPUT_NO_MOUSE = 1,
		DIRECTINPUT_NO_KEYBOARD = 2,
		DIRECTINPUT_JOYSTICK_BACKGROUND = 4,
		DIRECTINPUT_EXCLUSIVE_MOUSE = 8,
		DIRECTINPUT_EXCLUSIVE_KEYBOARD = 0x10
	};

	ControllerSystemDirectInput* GetDirectInputSystem();
	void UpdateDirectInput();
	void ShutdownDirectInput();
	void InitDirectInput(IControllerConnectionChangeCallback* listener, int heap, unsigned int options);
	// 0x1063CED0: the performance counter in milliseconds (not reconstructed)
	unsigned int GetMilliseconds();
}

#endif
