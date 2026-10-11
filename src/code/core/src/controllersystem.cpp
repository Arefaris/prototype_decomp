#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "code/core/controllerdirectinput.h"
#include "code/core/controllersystem.h"
#include "code/core/controllerxinput.h"

namespace core
{
	const char* CoreName();

	// GLOBAL: ENGINE 0x11279420
	static ControllerSystem* sControllerSystem;

	// FUNCTION: ENGINE 0x10643840
	bool IsControllerSystemCreated()
	{
		return sControllerSystem != 0;
	}

	// FUNCTION: ENGINE 0x10643850
	IControllerSystem* GetControllerSystem()
	{
		return sControllerSystem;
	}

	// FUNCTION: ENGINE 0x10643860
	ControllerSystem::~ControllerSystem()
	{
		ShutdownXInput();
		ShutdownDirectInput();
	}

	// FUNCTION: ENGINE 0x106438D0
	// "JoystickN" past the DirectInput joysticks is an XInput pad
	IController* ControllerSystem::FindController(const char* location)
	{
		bool xinput = false;
		if (strncmp(location, "Joystick", 8) == 0)
		{
			unsigned int index = xinputCount + directInputCount;
			sscanf(location + 8, "%d", &index);
			if (index >= joystickCount)
			{
				xinput = true;
			}
		}
		if (!xinput)
		{
			return GetDirectInputSystem()->FindController(location);
		}
		return GetXInputSystem()->FindController(location);
	}

	// FUNCTION: ENGINE 0x10643940
	IController* ControllerSystem::GetController(unsigned int index)
	{
		if (index >= directInputCount)
		{
			return GetXInputSystem()->GetController(index - directInputCount);
		}
		return GetDirectInputSystem()->GetController(index);
	}

	// FUNCTION: ENGINE 0x10643980
	unsigned int ControllerSystem::GetControllerCount()
	{
		return xinputCount + directInputCount;
	}

	// FUNCTION: ENGINE 0x10643990
	void ControllerSystem::SetListener(IControllerListener* listener)
	{
		GetDirectInputSystem()->SetListener(listener);
		GetXInputSystem()->SetListener(listener);
	}

	// FUNCTION: ENGINE 0x106439C0
	void ControllerSystem::ClearListener(IControllerListener* listener)
	{
		GetXInputSystem()->ClearListener(listener);
		GetDirectInputSystem()->ClearListener(listener);
	}

	// FUNCTION: ENGINE 0x106439F0
	void ControllerSystem::SetEnabled(bool enabled)
	{
		GetXInputSystem()->SetEnabled(enabled);
		GetDirectInputSystem()->SetEnabled(enabled);
	}

	// FUNCTION: ENGINE 0x10643A20
	void ControllerSystem::Update()
	{
		UpdateDirectInput();
		UpdateXInput();
		directInputCount = GetDirectInputSystem()->GetControllerCount();
		xinputCount = GetXInputSystem()->GetControllerCount();
	}

	// FUNCTION: ENGINE 0x10643A70
	void ControllerSystem::AddRef()
	{
		RefCount::AddRef();
	}

	// FUNCTION: ENGINE 0x10643A80
	void ControllerSystem::Release()
	{
		RefCount::Release();
	}

	// FUNCTION: ENGINE 0x10643AB0
	void ShutdownControllers()
	{
		sControllerSystem->Release();
	}

	// FUNCTION: ENGINE 0x10643AC0
	void UpdateControllers()
	{
		sControllerSystem->Update();
	}

	// FUNCTION: ENGINE 0x10643B10
	ControllerSystem::ControllerSystem(IControllerListener* listener, int heap, unsigned int options)
		: RefCount(1), joystickCount(0), directInputCount(0), xinputCount(0)
	{
		CoreName();
		InitDirectInput(listener, heap, options);
		joystickCount = GetDirectInputSystem()->GetJoystickCount();
		InitXInput(listener, heap, joystickCount);
		directInputCount = GetDirectInputSystem()->GetControllerCount();
		xinputCount = GetXInputSystem()->GetControllerCount();
	}

	// FUNCTION: ENGINE 0x10643BC0
	void InitControllers(IControllerListener* listener, int heap, unsigned int options)
	{
		sControllerSystem = new (heap) ControllerSystem(listener, heap, options);
	}
}
