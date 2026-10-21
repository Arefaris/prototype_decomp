// The actions of the primitive visibility, destroy and animation control tracks (unit 0x108EE6B0 - 0x108EF020, no
// assert path; file name guessed). The tracks are in primitivetracks.cpp.
#ifndef ENGINE_FIGHT_PRIMITIVEACTIONS_H
#define ENGINE_FIGHT_PRIMITIVEACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/primitivetracks.h"

namespace engine
{
	// RTTI: engine::PrimitiveVisibilityAction (9 vftable slots, size 0x2C): shows or hides one primitive of an object
	// (or all of them when the track names none)
	class PrimitiveVisibilityAction : public fight::Action
	{
	public:
		// 0x108EE7F0
		PrimitiveVisibilityAction(PrimitiveVisibilityTrack* newTrack, GameObjectHandle newTarget);
		// 0x108EE880: the object is looked up by name
		PrimitiveVisibilityAction(PrimitiveVisibilityTrack* newTrack, fight::Name objectName);
		// 0x108EE760
		virtual ~PrimitiveVisibilityAction();

		// vftable slot 5 (0x108EE8F0)
		virtual bool Slot5(int arg, float value);

		core::Link<PrimitiveVisibilityTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};

	// RTTI: engine::DestroyAction (9 vftable slots, size 0x38): puts the object on the deferred update list
	class DestroyAction : public fight::Action
	{
	public:
		// 0x108EEBC0
		DestroyAction(DestroyTrack* newTrack, fight::Track* listener, GameObjectHandle newTarget);
		// 0x108EEB00
		virtual ~DestroyAction();

		// vftable slot 5 (0x108EEB40) and slot 7 (0x108EEA90)
		virtual bool Slot5(int arg, float value);
		virtual bool Slot7(int arg, float value);

		core::Link<DestroyTrack> link;  // +0x1C
		TrackWatch watch;  // +0x28
		GameObjectHandle target;  // +0x34
	};

	// RTTI: engine::AnimationControlAction (9 vftable slots, size 0x2C): sends the track's animation control to the object
	class AnimationControlAction : public fight::Action
	{
	public:
		// 0x108EEE90
		AnimationControlAction(AnimationControlTrack* newTrack, GameObjectHandle newTarget);
		// 0x108EEE00
		virtual ~AnimationControlAction();

		// vftable slot 5 (0x108EEF10)
		virtual bool Slot5(int arg, float value);

		GameObjectHandle target;  // +0x1C
		core::Link<AnimationControlTrack> link;  // +0x20
	};
}

#endif
