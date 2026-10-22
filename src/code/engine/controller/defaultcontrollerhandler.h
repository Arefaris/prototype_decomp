// engine::controller::DefaultControllerHandler (RTTI name): the input callback the game keeps for the controllers of
// the game's players. It locks the game to the controller of the signed-in user (the front end's fe_LockController
// native), frees all of them again (fe_UnlockAllControllers) and keeps the controllers' flags and slots in line with
// the online services' user. A second instance of the game (the "GymMutex" exists) leaves the physical controllers
// alone. Unit 0x10895BD0 - 0x10896440 (no assert path; the file name is a guess). Names other than the RTTI ones are
// guesses.
#ifndef ENGINE_CONTROLLER_DEFAULTCONTROLLERHANDLER_H
#define ENGINE_CONTROLLER_DEFAULTCONTROLLERHANDLER_H

#include "code/engine/controller/inputsystem.h"
#include "code/engine/online/ols.h"

namespace engine
{
	namespace controller
	{
		class DefaultControllerHandler : public InputSystem::InputCallback, public OLS::Callback
		{
		public:
			// 0x10896340: a negative player count takes the input system's
			explicit DefaultControllerHandler(int newPlayerCount);
			// 0x10895BD0
			~DefaultControllerHandler();

			// vftable slot 0 (0x10895CC0): flag 1 set on the local player's controller
			virtual void OnFlags(unsigned int id, int local, unsigned int flags, bool set);
			// vftable slots 3 - 8 (0x10895CE0, 0x10895D20, 0x10896000, 0x10895D80, 0x10895E10, 0x10895EA0)
			virtual void Slot3();
			virtual void Slot4();
			virtual void Slot5();
			virtual void SetController(unsigned int controller);
			virtual void Slot7();
			virtual void Slot8();
			// 0x10895F90 (the OLS callback's slot): the profile message with id 6 calls slot 3
			virtual void OnMessage(OLSMessage* message);

			// 0x10895BF0 / 0x10895C20: the natives fe_LockController (the argument is ignored) and
			// fe_UnlockAllControllers
			void LockController(unsigned int unused);
			void UnlockAllControllers();

			unsigned int controller;  // +0x10: the controller the game is locked to
			int playerCount;  // +0x14
			bool unknown18;
			bool secondInstance;  // +0x19
		};
	}
}

#endif
