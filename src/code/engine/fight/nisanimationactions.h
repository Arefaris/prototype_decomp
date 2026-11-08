// The actions of the non-interactive sequence animation, sequence node and light animation tracks (unit 0x108F0C10 -
// 0x108F2000, no assert path; file name guessed). The tracks are in cameratracks.cpp.
#ifndef ENGINE_FIGHT_NISANIMATIONACTIONS_H
#define ENGINE_FIGHT_NISANIMATIONACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/cameratracks.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/nisactions.h"

#include "code/engine/message.h"
#include "code/engine/fight/nisspawnaction.h"

namespace content
{
	class LoadInventory;
}
namespace pure3d
{
	class Animation;
}

namespace engine
{
	// What an owner that is a game object keeps the sequences it plays in (another unit; names guessed)
	class NISHandler
	{
	public:
		// 0x108A7450: takes a sequence node
		void Unknown108A7450(fight::Branch* node);
	};

	// 0x108A8210: the inventory of an owner that is a game object (null for any other owner)
	content::LoadInventory* GetOwnerInventory(core::IRefCount* owner);

	// RTTI: engine::SetAnimationMessage (type 10, id 0, size 0x28): tells the pose animation behaviour of an object to play
	// an animation (all zero stops it); the member names are guesses
	struct SetAnimationMessage : public IntrusiveMessage
	{
		SetAnimationMessage() : IntrusiveMessage(10, 0)
		{
			animation = 0;
			speed = 0.0f;
			frame = 0.0f;
			startFrame = 0.0f;
			endFrame = 0.0f;
			cyclic = 0;
			numCycles = 0;
		}
		virtual ~SetAnimationMessage()
		{
		}

		pure3d::Animation* animation;  // +0xC
		float speed;  // +0x10
		float frame;  // +0x14
		float startFrame;  // +0x18
		float endFrame;  // +0x1C
		int cyclic;  // +0x20
		int numCycles;  // +0x24
	};

	// What the animation actions hand the object's behaviours to make them stop (type 0x17; a plain struct whose first
	// word is the type, built by 0x108A08D0; the member names are guesses)
	struct StopSignal
	{
		// 0x108A08D0 (another unit)
		StopSignal();

		int type;
		int unknown4;
		unsigned char unknown8;
		bool unknown9;
		bool unknownA;
		bool unknownB;
	};

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
