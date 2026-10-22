#include "code/engine/controller/physicalcontrollermapmanager.h"
#include "code/core/heap.h"
#include "code/core/controllersystem.h"
#include "code/core/name.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/controller/physicalcontroller.h"
#include "code/engine/database/gamedatabase.h"
#include <string.h>

namespace engine
{
	namespace controller
	{
		// FUNCTION: ENGINE 0x10880AB0
		void PhysicalControllerMapManager::Start(PhysicalControllerManager* newManager)
		{
			manager = newManager;
			core::InitControllers(this, heap, options);
		}

		// FUNCTION: ENGINE 0x10880AD0
		void PhysicalControllerMapManager::OnControllerChanged(core::IController* changed)
		{
			if (changed->IsConnected())
			{
				OnConnected(changed);
			}
			else
			{
				OnDisconnected(changed);
			}
		}

		// FUNCTION: ENGINE 0x10880B00
		ControllerMap* PhysicalControllerMapManager::CreateMap(const ButtonMapping* buttons, int buttonCount,
			const AxisMapping* axes, int axisCount)
		{
			ControllerMap* map = new ControllerMap(buttonCount, axisCount);
			for (int i = 0; i < buttonCount; i++)
			{
				map->SetButton(i, &buttons[i]);
			}
			for (int i = 0; i < axisCount; i++)
			{
				map->SetAxis(i, &axes[i]);
			}
			return map;
		}

		// FUNCTION: ENGINE 0x10880B70
		int PhysicalControllerMapManager::GetSlot(core::IController* changed)
		{
			int slot = -1;
			const char* location = changed->GetLocation();
			if (strcmp(location, "Keyboard0") == 0)
			{
				slot = 0;
			}
			else if (strcmp(location, "Mouse0") == 0)
			{
				slot = 1;
			}
			else if (strncmp(location, "Joystick", 8) == 0)
			{
				slot = location[8] - '.';
			}
			else if (strncmp(location, "Port", 4) == 0)
			{
				slot = location[4] - '0';
			}
			return slot;
		}

		// FUNCTION: ENGINE 0x10880C10
		void PhysicalControllerMapManager::SetMap(unsigned char slot, ControllerMap* map)
		{
			if (controllers[slot] != 0)
			{
				controllers[slot]->Bind(map->AsMapping());
			}
		}

		// FUNCTION: ENGINE 0x10880C30
		PhysicalController* PhysicalControllerMapManager::GetConnected(unsigned char slot)
		{
			PhysicalController* controller = controllers[slot];
			return controller->controller != 0 ? controller : 0;
		}

		// The word's low byte is the controller's flag (SetRumbleEnabled takes a bool)
		// FUNCTION: ENGINE 0x10880C50
		void PhysicalControllerMapManager::CallController(unsigned char slot, int value)
		{
			if (controllers[slot] != 0)
			{
				PhysicalController* controller = controllers[slot];
				controller->SetRumbleEnabled(*(const bool*)&value);
			}
		}

		// FUNCTION: ENGINE 0x10880C80
		PhysicalControllerMapManager::PhysicalControllerMapManager(int newControllerCount, int a, int b, int newOptions,
			int newHeap, int c)
		{
			controllerCount = newControllerCount;
			options = newOptions;
			manager = 0;
			heap = newHeap;
			core::HeapScope scope(newHeap);
			controllers = new PhysicalController*[controllerCount];
			for (int i = 0; i < controllerCount; i++)
			{
				controllers[i] = new PhysicalController(a, b, 2, c);
			}
			for (int i = 0; i < 11; i++)
			{
				maps[i] = CreateMap(gControllerKinds[i].buttons, gControllerKinds[i].buttonCount, gControllerKinds[i].axes,
					gControllerKinds[i].axisCount);
			}
		}

		// FUNCTION: ENGINE 0x10880D60
		PhysicalControllerMapManager::~PhysicalControllerMapManager()
		{
			for (int i = 0; i < 11; i++)
			{
				if (maps[i] != 0)
				{
					delete maps[i];
				}
			}
			for (int i = 0; i < controllerCount; i++)
			{
				if (controllers != 0)
				{
					delete controllers[i];
				}
			}
			delete[] controllers;
			core::ShutdownControllers();
		}

		// FUNCTION: ENGINE 0x10880DE0
		// EQUIVALENT: the engine loads the slot into ecx, extends its low byte for the id and then loads the controller,
		// ours loads the controller first (scheduling of the last call's arguments), 95.8 %
		void PhysicalControllerMapManager::OnConnected(core::IController* changed)
		{
			int slot = GetSlot(changed);
			if (slot < 0)
			{
				return;
			}
			const char* name = changed->GetName();
			const char* location = changed->GetLocation();
			if (strcmp(location, "Keyboard0") == 0)
			{
				name = "Keyboard";
			}
			if (strcmp(location, "Mouse0") == 0)
			{
				name = "Mouse";
			}
			for (int i = 0; i < 11; i++)
			{
				if (strncmp(name, gControllerKinds[i].name, strlen(gControllerKinds[i].name)) == 0)
				{
					controllers[slot]->SetController(0);
					controllers[slot]->SetController(changed);
					controllers[slot]->Bind(maps[i]->AsMapping());
					if (i == 4 || i == 5)
					{
						GameDatabase* checkDatabase = gGameDatabase;
						if (checkDatabase->Exists(core::Name<core::CaseSensitiveKey>("SettingsDefaultController", 0), 0, 0))
						{
							GameDatabase* writeDatabase = gGameDatabase;
							writeDatabase->SetInt(core::Name<core::CaseSensitiveKey>("SettingsDefaultController", 0), 0, i, 0);
						}
					}
					manager->SetController((unsigned char)slot | 0xFE00, controllers[slot]);
					return;
				}
			}
		}

		// FUNCTION: ENGINE 0x10880F50
		void PhysicalControllerMapManager::OnDisconnected(core::IController* changed)
		{
			int slot = GetSlot(changed);
			if (slot < 0)
			{
				return;
			}
			controllers[slot]->StopRumble();
			changed->GetName();
			changed->GetLocation();
			bool gamepad = false;
			core::IControllerSystem* system = core::GetControllerSystem();
			int count = system->GetControllerCount();
			for (int i = 0; i < count; i++)
			{
				core::IController* other = system->GetController(i);
				if (other != 0 && other->IsConnected())
				{
					if (strncmp(other->GetName(), gControllerKinds[4].name, strlen(gControllerKinds[4].name)) == 0 ||
						strncmp(other->GetName(), gControllerKinds[5].name, strlen(gControllerKinds[5].name)) == 0)
					{
						gamepad = true;
					}
				}
			}
			GameDatabase* database = gGameDatabase;
			if (database->Exists(core::Name<core::CaseSensitiveKey>("SettingsDefaultController", 0), 0, 0))
			{
				int kind = database->GetInt(core::Name<core::CaseSensitiveKey>("SettingsDefaultController", 0), 0, 0);
				if ((kind != 4 && kind != 5) || !gamepad)
				{
					database->SetInt(core::Name<core::CaseSensitiveKey>("SettingsDefaultController", 0), 0, 0, 0);
				}
			}
		}

		// FUNCTION: ENGINE 0x10882140
		ControllerMap::ControllerMap(unsigned int newButtonCount, unsigned int newAxisCount)
		{
			buttonCount = newButtonCount;
			axisCount = newAxisCount;
			buttons = new ButtonMapping[buttonCount];
			axes = new AxisMapping[axisCount];
			for (int i = 0; i < (int)buttonCount; i++)
			{
				buttons[i].unknown0 = 0;
			}
			for (int i = 0; i < (int)axisCount; i++)
			{
				axes[i].unknown0 = 0;
			}
		}

		// FUNCTION: ENGINE 0x108821D0
		ControllerMap::~ControllerMap()
		{
			delete[] buttons;
			delete[] axes;
		}

		// FUNCTION: ENGINE 0x108821F0
		void ControllerMap::SetButton(int index, const ButtonMapping* button)
		{
			ButtonMapping* target = &buttons[index];
			target->unknown0 = button->unknown0;
			target->unknown4 = button->unknown4;
			target->unknown8 = button->unknown8;
			target->unknownC = button->unknownC;
			target->unknown10 = button->unknown10;
		}

		// FUNCTION: ENGINE 0x10882240
		void ControllerMap::SetAxis(int index, const AxisMapping* axis)
		{
			AxisMapping* target = &axes[index];
			target->unknown0 = axis->unknown0;
			target->unknown4 = axis->unknown4;
			target->unknown8 = axis->unknown8;
			target->unknownC = axis->unknownC;
			target->unknown10 = axis->unknown10;
			target->unknown14 = axis->unknown14;
		}

		// FUNCTION: ENGINE 0x10882280
		void ControllerMap::ClearAxis(int index)
		{
			axes[index].unknown0 = 0;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10880AA0
// FUNCTION: ENGINE 0x108810D0
