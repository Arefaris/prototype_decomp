// The actions of the attach and detach tracks (unit 0x108F0370 - 0x108F0C00, no assert path; file name guessed). The
// tracks are in nistracks.cpp.
#ifndef ENGINE_FIGHT_ATTACHACTIONS_H
#define ENGINE_FIGHT_ATTACHACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/nistracks.h"

namespace engine
{
	namespace animation
	{
		// RTTI: engine::animation::AttachObjectAction (9 vftable slots, size 0x2C): attaches an object to a parent
		class AttachObjectAction : public fight::Action
		{
		public:
			// 0x108F0580
			AttachObjectAction(AttachObjectTrack* newTrack, GameObjectHandle newTarget);
			// 0x108F0370
			virtual ~AttachObjectAction();

			// vftable slot 5 (0x108F08F0)
			virtual bool Slot5(int arg, float value);

			core::Link<AttachObjectTrack> link;  // +0x1C
			GameObjectHandle target;  // +0x28
		};

		// RTTI: engine::animation::DetachObjectAction (9 vftable slots, size 0x2C): detaches an object from its parent
		class DetachObjectAction : public fight::Action
		{
		public:
			// 0x108F0610
			DetachObjectAction(DetachObjectTrack* newTrack, GameObjectHandle newTarget);
			// 0x108F0400
			virtual ~DetachObjectAction();

			// vftable slot 5 (0x108F06A0)
			virtual bool Slot5(int arg, float value);

			core::Link<DetachObjectTrack> link;  // +0x1C
			GameObjectHandle target;  // +0x28
		};

		// RTTI: engine::animation::DetachFromParentAction (9 vftable slots, size 0x2C): detaches the object it runs on
		class DetachFromParentAction : public fight::Action
		{
		public:
			// 0x108F0700
			DetachFromParentAction(DetachFromParentTrack* newTrack, GameObjectHandle newTarget);
			// 0x108F0440
			virtual ~DetachFromParentAction();

			// vftable slot 5 (0x108F0790)
			virtual bool Slot5(int arg, float value);

			core::Link<DetachFromParentTrack> link;  // +0x1C
			GameObjectHandle target;  // +0x28
		};
	}
}

#endif
