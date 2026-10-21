// The actions of the supporting limb tracks (the code sits in 0x1092FDC0 - 0x10930870, no assert path; file name
// guessed). The tracks are in supportinglimb.cpp and supportingstick.cpp.
#ifndef ENGINE_FIGHT_SUPPORTINGLIMBACTIONS_H
#define ENGINE_FIGHT_SUPPORTINGLIMBACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/supportinglimb.h"
#include "code/engine/fight/supportingstick.h"

namespace engine
{
	class SupportingLimb;

	// RTTI: engine::SupportingLimbAction (9 vftable slots, size 0x2C): makes the named limb the active one and points it
	// along the track's direction
	class SupportingLimbAction : public fight::Action
	{
	public:
		// 0x10930240
		SupportingLimbAction(SupportingLimbTrack* newTrack, GameObjectHandle newTarget);
		// 0x1092FFD0
		virtual ~SupportingLimbAction();

		// vftable slot 5 (0x109302D0)
		virtual bool Slot5(int arg, float value);

		core::Link<SupportingLimbTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};

	// RTTI: engine::SupportingSurfaceStickAction (9 vftable slots, size 0x30)
	class SupportingSurfaceStickAction : public fight::Action
	{
	public:
		// 0x10930440
		SupportingSurfaceStickAction(SupportingSurfaceStickTrack* newTrack, GameObjectHandle newTarget);
		// 0x10930010
		virtual ~SupportingSurfaceStickAction();

		// vftable slot 5 (0x109304D0) and slot 6 (0x109305C0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		core::Link<SupportingSurfaceStickTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		bool previousStick;  // +0x2C
	};

	// RTTI: engine::SupportingLimbExtraLengthAction (9 vftable slots, size 0x40): lengthens a limb while it runs
	class SupportingLimbExtraLengthAction : public fight::Action
	{
	public:
		// 0x10930630
		SupportingLimbExtraLengthAction(SupportingLimbExtraLengthTrack* newTrack, GameObjectHandle newTarget);
		// 0x10930050
		virtual ~SupportingLimbExtraLengthAction();

		// vftable slot 5 (0x109306B0) and slot 6 (0x10930080)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		core::Link<SupportingLimbExtraLengthTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		int unknown2C;
		fight::Name limbName;  // +0x30
		SupportingLimb* limb;  // +0x38
		float appliedLength;  // +0x3C
	};
}

#endif
