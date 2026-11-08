// proto::TimeSliceManager (RTTI class; one vftable slot, the deleting destructor): spreads work over the frames. Two
// fixed lists, eight and 512 entries, behind a flag and a counter; the entries' types are not recovered. Unit
// 0x103B2510 - 0x103B2560 (no assert path; the file name is a guess); member names are guesses.
#ifndef PROTO_TIMESLICEMANAGER_H
#define PROTO_TIMESLICEMANAGER_H

#include "code/container/arrayfixed.h"
#include "code/engine/gameobject/gameobject.h"

namespace proto
{
	class TimeSliceManager
	{
	public:
		// An object that ran at full rate lately and the time it stays so (member names are guesses)
		struct Entry
		{
			// 0x103B1FC0
			Entry();

			engine::GameObject* object;
			float time;
		};

		// 0x103B2510
		TimeSliceManager();
		// 0x103B2540 (deleting destructor 0x103B2560)
		virtual ~TimeSliceManager();

		// 0x103B20D0: whether the object may skip frames: the manager is on and the object is neither the attached one,
		// nor one of the held ones, nor in the list of lately active ones (name guess)
		bool CanSkipFrames(engine::GameObject* object);
		// 0x103B2210: ages the lately active objects and drops the ones whose time ran out (name guess)
		void Update(float timeStep);
		// 0x103B22A0: lets the object run every frame for a while (name guess)
		void KeepActive(engine::GameObject* object);
		// 0x103B2390: takes the object the given one is attached to and the objects its grab slots hold as the objects
		// that run every frame (name guess)
		void Refresh(engine::GameObject* object);

		bool enabled;
		engine::GameObject* attached;
		container::ArrayFixed<engine::GameObject*, 8> held;  // +0xC
		container::ArrayFixed<Entry, 256> active;  // +0x30
	};
}

#endif
