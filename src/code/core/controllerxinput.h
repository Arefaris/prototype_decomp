// XInput controller points (class names from RTTI; member and method names guessed).
#ifndef CORE_CONTROLLERXINPUT_H
#define CORE_CONTROLLERXINPUT_H

#include "code/core/controller.h"

namespace core
{
	// The XInput controller system (not reconstructed; names guessed): 0x106487B0 returns it, 0x10649F00 creates it
	// (its joysticks numbered from firstJoystick on), 0x10649F50 reads the pads, 0x10649910 destroys it
	IControllerSystem* GetXInputSystem();
	void InitXInput(IControllerListener* listener, int heap, unsigned int firstJoystick);
	void UpdateXInput();
	void ShutdownXInput();

	class ControllerOutputPointXInput
	{
	public:
		virtual unsigned int AddRef();
		virtual unsigned int Release();
		virtual void Destroy();
		virtual unsigned int GetControllerType();
		virtual unsigned int GetPointType();
		virtual float GetValue();
		virtual void SetValue(float newValue);

	private:
		void* secondaryVtable;
		void* controller;
		unsigned int unknown0C;
		unsigned int controllerType;
		unsigned int pointIndex;
		float value;
		bool dirty;
		unsigned char padding[3];
		unsigned int mask;
	};

	class ControllerInputPointXInput
	{
	public:
		virtual unsigned int AddRef();
		virtual unsigned int Release();
		virtual void Destroy();
		virtual unsigned int GetControllerType();
		virtual unsigned int GetPointType();
		virtual void SetScale(float newScale);
		virtual float GetScale();
		virtual void SetBinding(void* binding, void* userData);
		virtual void ClearBinding(void* binding);
		virtual float Read(unsigned int* state);
		virtual void SetRange(float minimum, float maximum);
		virtual void GetRange(float* minimum, float* maximum);
		virtual unsigned int GetValueCount();
		virtual unsigned int ReadValues(unsigned int count, float* values);

	private:
		void* secondaryVtable;
		void* controller;
		unsigned int unknown0C;
		unsigned int controllerType;
		unsigned int pointIndex;
		float value;
		float minimum;
		float maximum;
		float scale;
		unsigned int state;
		unsigned int unknown2C;
		unsigned int steps;
		void* binding;
		void* bindingData;
	};
}

#endif
