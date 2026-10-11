// The controller interfaces (RTTI names core::IControllerSystem, core::IController, core::IControllerInputPoint,
// core::IControllerOutputPoint; vftables 0x10E46F4C, 0x10E46D8C, 0x10E46E2C, 0x10E46DFC). A controller system finds
// the attached controllers; a controller has input points (axes, buttons) and output points (force feedback).
// Method names and the listener / binding interfaces are guesses from what the DirectInput implementation does.
#ifndef CORE_CONTROLLER_H
#define CORE_CONTROLLER_H

#include "code/core/memory/imemoryallocator.h"

namespace core
{
	struct IController;

	// Told when a controller is connected or disconnected
	struct IControllerListener
	{
		virtual void OnControllerChanged(IController* controller) = 0;
	};

	// Told the scaled value of an input point when it changes
	struct IControllerBinding
	{
		virtual void OnChange(void* userData, float value) = 0;
	};

	struct IControllerOutputPoint : IRefCount
	{
		virtual const char* GetName() = 0;
		virtual const char* GetTypeName() = 0;
		virtual float GetValue() = 0;
		// Clamped to [0, 1]
		virtual void SetValue(float value) = 0;
	};

	struct IControllerInputPoint : IRefCount
	{
		virtual const char* GetName() = 0;
		virtual const char* GetTypeName() = 0;
		// The smallest change of the value that is reported, clamped to [0, 1]
		virtual void SetThreshold(float threshold) = 0;
		virtual float GetThreshold() = 0;
		// One binding at a time: SetBinding does nothing while another is set
		virtual void SetBinding(IControllerBinding* binding, void* userData) = 0;
		virtual void ClearBinding(IControllerBinding* binding) = 0;
		// The value mapped to [minimum, maximum], and how long it has been unchanged (milliseconds)
		virtual float Read(unsigned int* heldTime) = 0;
		virtual void SetRange(float minimum, float maximum) = 0;
		virtual void GetRange(float* minimum, float* maximum) = 0;
		virtual unsigned int GetValueCount() = 0;
		virtual unsigned int ReadValues(unsigned int count, float* values) = 0;
	};

	struct IController : IRefCount
	{
		virtual bool IsConnected() = 0;
		virtual const char* GetName() = 0;
		// "Keyboard", "Mouse", "Joystick"
		virtual const char* GetTypeName() = 0;
		// The type and a number, "Joystick1"
		virtual const char* GetLocation() = 0;
		// Slots 7 - 16: features the DirectInput controllers do not have (they return 0 or false)
		virtual bool Slot7() = 0;
		virtual int Slot8() = 0;
		virtual int Slot9(int a) = 0;
		virtual bool Slot10(int a, int b) = 0;
		virtual int Slot11() = 0;
		virtual int Slot12() = 0;
		virtual int Slot13(int a) = 0;
		virtual int Slot14(int a) = 0;
		virtual int Slot15(int a, int b) = 0;
		virtual int Slot16(int a) = 0;
		virtual unsigned int GetInputCount() = 0;
		// Input points by type name ("XAxis", "Button", ...), by name, and by index
		virtual unsigned int CountInputs(const char* typeName) = 0;
		virtual IControllerInputPoint* FindInput(const char* typeName, unsigned int index) = 0;
		virtual IControllerInputPoint* FindInputByName(const char* name) = 0;
		virtual IControllerInputPoint* GetInput(unsigned int index) = 0;
		virtual unsigned int GetOutputCount() = 0;
		virtual unsigned int CountOutputs(const char* typeName) = 0;
		virtual IControllerOutputPoint* FindOutput(const char* typeName, unsigned int index) = 0;
		virtual IControllerOutputPoint* FindOutputByName(const char* name) = 0;
		virtual IControllerOutputPoint* GetOutput(unsigned int index) = 0;
	};

	struct IControllerSystem : IRefCount
	{
		// The connected controllers, by index and by location
		virtual unsigned int GetControllerCount() = 0;
		virtual IController* GetController(unsigned int index) = 0;
		virtual IController* FindController(const char* location) = 0;
		// One listener at a time: SetListener does nothing while another is set
		virtual void SetListener(IControllerListener* listener) = 0;
		virtual void ClearListener(IControllerListener* listener) = 0;
		// While disabled (or while the window has no focus) the controllers are not read
		virtual void SetEnabled(bool enabled) = 0;
	};
}

#endif
