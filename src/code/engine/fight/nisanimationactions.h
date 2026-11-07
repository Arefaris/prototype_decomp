// The actions of the non-interactive sequence animation, sequence node and light animation tracks (unit 0x108F0C10 -
// 0x108F2000, no assert path; file name guessed). The tracks are in cameratracks.cpp.
#ifndef ENGINE_FIGHT_NISANIMATIONACTIONS_H
#define ENGINE_FIGHT_NISANIMATIONACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/cameratracks.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/nisactions.h"

namespace content
{
	class LoadInventory;
}

namespace engine
{
	// 0x108A8210: the inventory of an owner that is a game object (null for any other owner)
	content::LoadInventory* GetOwnerInventory(core::IRefCount* owner);

	// RTTI: engine::NISAnimationAction (9 vftable slots, size 0x40): plays an animation on an object through its pose
	// animation controller
	class NISAnimationAction : public fight::Action
	{
	public:
		// 0x108F0D50 (the destructor 0x108F0DD0 and the deleting destructor 0x108F0DF0 are the compiler's)
		NISAnimationAction(NISAnimationTrack* newTrack, fight::Name newObject, GameObjectHandle newOwner,
			content::LoadInventory* newInventory);

		// vftable slot 5 (0x108F0E30), slot 6 (0x108F1120) and slot 7 (0x108F1090)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<NISAnimationTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		int unknown2C;
		fight::Name object;  // +0x30
		GameObjectHandle owner;  // +0x38
		content::LoadInventory* inventory;  // +0x3C
	};

	// RTTI: engine::LightAnimationAction (9 vftable slots, size 0x34): plays an animation on the light of an object
	class LightAnimationAction : public fight::Action
	{
	public:
		// 0x108F1C20
		LightAnimationAction(LightAnimationTrack* newTrack, GameObjectHandle newTarget);
		// 0x108F1CB0: the object is looked up by name
		LightAnimationAction(LightAnimationTrack* newTrack, core::IRefCount* newOwner, fight::Name objectName);
		// 0x108F1A00 (deleting destructor 0x108F1C90)
		virtual ~LightAnimationAction();

		// vftable slot 5 (0x108F1D80), slot 6 (0x108F1AD0) and slot 7 (0x108F1A40)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<LightAnimationTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		GameObjectHandle ownerHandle;  // +0x2C
		core::IRefCount* owner;  // +0x30
	};

	// RTTI: engine::SequenceNISNodeAction (9 vftable slots, size 0x48): plays a sequence node of the fight tree as a
	// non-interactive sequence
	class SequenceNISNodeAction : public fight::Action
	{
	public:
		// 0x108F14A0
		SequenceNISNodeAction(fight::Track* listener, SequenceNISNodeTrack* newTrack, int newEffect,
			core::IRefCount* newOwner);
		// 0x108F13C0 (deleting destructor 0x108F16B0)
		virtual ~SequenceNISNodeAction();

		// vftable slot 5 (0x108F16D0) and slot 7 (0x108F1320)
		virtual bool Slot5(int arg, float value);
		virtual bool Slot7(int arg, float value);

		core::Link<SequenceNISNodeTrack> link;  // +0x1C
		TrackWatch watch;  // +0x28
		int effect;  // +0x34
		core::IRefCount* owner;  // +0x38
		int unknown3C;
		fight::Name sequence;  // +0x40
	};
}

#endif
