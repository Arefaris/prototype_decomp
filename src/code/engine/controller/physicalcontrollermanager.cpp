// The manager of the physical controllers (engine::controller::PhysicalControllerManager, code/engine/controller/
// physicalcontrollermanager.cpp; the file name is a guess, the unit starts at 0x108A0970 and has no assert path) and the
// snapshot of packed player state it keeps (0x108A2790 - 0x108A2860). Names are guesses unless the RTTI gives them.
#include "code/engine/controller/inputsystem.h"
#include "code/engine/controller/physicalcontroller.h"
#include <new>

namespace engine
{
	namespace controller
	{
		// FUNCTION: ENGINE 0x108A0970
		PhysicalControllerManager::~PhysicalControllerManager()
		{
			delete[] controllers;
		}

		// FUNCTION: ENGINE 0x108A0990
		void PhysicalControllerManager::SetController(unsigned int id, PhysicalController* controller)
		{
			controllers[(unsigned char)id] = controller;
			if (callback != 0)
			{
				InputSystem::Get()->SetPlayerFlags(id, controller->GetBoundCount() | 1);
			}
		}

		// FUNCTION: ENGINE 0x108A09D0
		void PhysicalControllerManager::RemoveController(unsigned int id)
		{
			if (callback != 0)
			{
				InputSystem::Get()->ClearPlayerFlags(id, controllers[(unsigned char)id]->GetBoundCount() | 1);
			}
			controllers[(unsigned char)id] = 0;
		}

		// FUNCTION: ENGINE 0x108A0A20
		// NONMATCHING: the arguments stay on the x87 stack across the first test and the engine reaches the controller table through one address (28.1 %)
#ifdef NONMATCHING
		void PhysicalControllerManager::SetVibration(unsigned int id, int motor, float a, float b, float c, float d)
		{
			if (controllers[(unsigned char)id] != 0)
			{
				controllers[(unsigned char)id]->SetRumble(motor, a, b, c, d);
			}
			if (selected != 0xffffffff)
			{
				if (selected != id)
				{
					return;
				}
				unsigned int other = secondary;
				if (other != 0xffffffff)
				{
					if (other != 0xfe00 && other != 0xfe01 && other != id)
					{
						if (controllers[(unsigned char)other] == 0)
						{
							return;
						}
						controllers[(unsigned char)other]->SetRumble(motor, a, b, c, d);
						return;
					}
					if (other != 0xffffffff)
					{
						return;
					}
				}
				if ((unsigned char)selected != 2 && controllers[2] != 0)
				{
					controllers[2]->SetRumble(motor, a, b, c, d);
				}
			}
		}
#endif

		// FUNCTION: ENGINE 0x108A0B40
		void PhysicalControllerManager::Select(int newSecondary, unsigned int primary)
		{
			secondary = newSecondary;
			selected = primary;
		}

		// FUNCTION: ENGINE 0x108A0B60
		void PhysicalControllerManager::SetFlags(unsigned int id, unsigned int flags, bool set)
		{
			callback->OnFlags(id, flags, set, 0);
		}

		// FUNCTION: ENGINE 0x108A0B80
		void PhysicalControllerManager::SetValue(unsigned int id, int value)
		{
			callback->OnValue(id, value);
		}

		// FUNCTION: ENGINE 0x108A0B90
		void PhysicalControllerManager::Release(unsigned int id, int slot)
		{
			callback->OnRelease(id, slot);
		}

		// FUNCTION: ENGINE 0x108A0BB0
		PhysicalControllerManager::PhysicalControllerManager(int count)
			: controllerCount(count), snapshot(0), selected(0xffffffff), secondary(0xffffffff), unknown34(false)
		{
			controllers = new PhysicalController*[controllerCount];
			for (int index = 0; index < controllerCount; index++)
			{
				controllers[index] = 0;
			}
		}

		// FUNCTION: ENGINE 0x108A0C20
		// NONMATCHING: the engine takes the list head of the received list in ecx / edx (93.8 %)
#ifdef NONMATCHING
		void PhysicalControllerManager::Collect(container::SListBase* players)
		{
			PlayerInput* active = (PlayerInput*)InputSystem::Get()->active.head;
			snapshot.Capture(active, 2);
			snapshot.Restore((PlayerInput*)players->head);
			unknown34 = true;
		}
#endif

		// FUNCTION: ENGINE 0x108A2790
		ControllerSnapshot::ControllerSnapshot(ControllerPacker* newPacker)
			: unknown0(0), unknown4(true), time(0, 0), packer(newPacker)
		{
			if (packer == 0)
			{
				packer = InputSystem::Get()->config.helperB;
			}
			int size = packer->bufferSize;
			data = new unsigned char[size];
		}

		// FUNCTION: ENGINE 0x108A27E0
		ControllerSnapshot::~ControllerSnapshot()
		{
			delete[] data;
		}

		// FUNCTION: ENGINE 0x108A27F0
		int ControllerSnapshot::Capture(PlayerInput* players, unsigned int flags)
		{
			return packer->PackAll(players, data, packer->bufferSize, true, 2);
		}

		// FUNCTION: ENGINE 0x108A2820
		void ControllerSnapshot::Restore(PlayerInput* players)
		{
			packer->UnpackAll(players, data, packer->bufferSize);
		}

		// FUNCTION: ENGINE 0x108A2840
		bool ControllerSnapshot::Check(PlayerInput* players)
		{
			int size = packer->bufferSize;
			return packer->VerifyAll(players, data, size);
		}
	}
}
