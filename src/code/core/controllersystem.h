// core::ControllerSystem (RTTI name; vftables 0x10E47150 and, for the RefCount base, 0x10E47148): the controller
// system the engine uses, the DirectInput and the XInput systems behind one interface. Controllers are numbered
// DirectInput first; the XInput pads continue the DirectInput joystick numbers ("JoystickN"). Unit 0x10643840 -
// 0x10643BFE (no assert path; file name controllersystem.cpp and member / function names guessed).
#ifndef CORE_CONTROLLERSYSTEM_H
#define CORE_CONTROLLERSYSTEM_H

#include "code/core/controller.h"
#include "code/core/object.h"

namespace core
{
	class ControllerSystem : public IControllerSystem, public RefCount
	{
	public:
		ControllerSystem(IControllerListener* listener, int heap, unsigned int options);
		virtual ~ControllerSystem();
		virtual void AddRef();
		virtual void Release();
		virtual unsigned int GetControllerCount();
		virtual IController* GetController(unsigned int index);
		virtual IController* FindController(const char* location);
		virtual void SetListener(IControllerListener* listener);
		virtual void ClearListener(IControllerListener* listener);
		virtual void SetEnabled(bool enabled);

		// Reads both systems and counts their connected controllers again
		void Update();

		unsigned int joystickCount;
		unsigned int directInputCount;
		unsigned int xinputCount;
	};

	bool IsControllerSystemCreated();
	IControllerSystem* GetControllerSystem();
	void ShutdownControllers();
	void UpdateControllers();
	// options: InitDirectInput's
	void InitControllers(IControllerListener* listener, int heap, unsigned int options);
}

#endif
