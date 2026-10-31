// engine::controller::MonkeyControllerManager (RTTI name; bases ControllerManagerInterface and its Callback): a
// controller manager that stands in for the input system's own and hands every request on to that one (kept at
// +0x14), so that the input a test drives goes through the same paths. The events of the controllers it listens to
// go on to the callback it was given. Unit 0x10890910 - 0x108925B0 (no assert path; the file name is a guess). Names
// other than the RTTI ones are guesses.
#ifndef ENGINE_CONTROLLER_MONKEYCONTROLLERMANAGER_H
#define ENGINE_CONTROLLER_MONKEYCONTROLLERMANAGER_H

#include "code/engine/controller/inputsystem.h"

namespace engine
{
	namespace controller
	{
		class MonkeyControllerManager : public ControllerManagerInterface, public ControllerManagerInterface::Callback
		{
		public:
			// 0x10890950 (deleting destructor 0x10890B20): gives the input system back its own manager
			virtual ~MonkeyControllerManager();

			// vftable slots 0 - 2 and 3 (0x10890980, 0x10890990, 0x108909A0, 0x10890970): handed on
			virtual void SetFlags(unsigned int id, unsigned int flags, bool set);
			virtual void SetValue(unsigned int id, int value);
			virtual void Refresh();
			virtual void Collect(container::SListBase* players);
			// slot 4 (0x10892130)
			virtual void CollectActive(container::SListBase* players, float time);

			// The callback's slots (0x108909B0, 0x108909C0, 0x108909D0): handed on to the callback
			virtual void OnFlags(unsigned int id, unsigned int flags, bool set, int which);
			virtual void OnValue(unsigned int id, int value);
			virtual void OnRelease(unsigned int id, int value);

			int unknownC;
			int unknown10;
			ControllerManagerInterface* inner;  // +0x14
		};
	}
}

#endif
