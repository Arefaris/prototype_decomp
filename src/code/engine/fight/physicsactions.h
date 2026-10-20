// The actions of the physics and collision tracks and the decal and effect timer tracks (unit 0x108AAFB0 - 0x108AD070, no assert path; file name guessed). The tracks are in physicstracks.cpp and effecttimertracks.cpp.
#ifndef ENGINE_FIGHT_PHYSICSACTIONS_H
#define ENGINE_FIGHT_PHYSICSACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/physicstracks.h"
#include "code/engine/fight/effecttimertracks.h"
#include "code/engine/fight/effecttrack.h"

namespace engine
{
	// RTTI: engine::PhysicsEnableAction (9 vftable slots, size 0x30)
	class PhysicsEnableAction : public fight::Action
	{
	public:
		// 0x108ABB90
		PhysicsEnableAction(PhysicsEnableTrack* newTrack, GameObjectHandle newTarget);
		// 0x108AB560
		virtual ~PhysicsEnableAction();

		// vftable slot 5 (0x108ABC00)
		virtual bool Slot5(int arg, float value);
		// vftable slot 6 (0x108ABCE0)
		virtual void Slot6();

		core::Link<PhysicsEnableTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		bool unknown2c;  // +0x2C
	};

	// RTTI: engine::PhysicsDisallowSleepingAction (9 vftable slots, size 0x2C)
	class PhysicsDisallowSleepingAction : public fight::Action
	{
	public:
		// 0x108AC3A0
		PhysicsDisallowSleepingAction(PhysicsDisallowSleepingTrack* newTrack, GameObjectHandle newTarget);
		// 0x108AB910
		virtual ~PhysicsDisallowSleepingAction();

		// vftable slot 5 (0x108AC430)
		virtual bool Slot5(int arg, float value);
		// vftable slot 6 (0x108AC4B0)
		virtual void Slot6();

		core::Link<PhysicsDisallowSleepingTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};

	// RTTI: engine::PhysicsSetKeyframedAction (9 vftable slots, size 0x2C)
	class PhysicsSetKeyframedAction : public fight::Action
	{
	public:
		// 0x108AC200
		PhysicsSetKeyframedAction(PhysicsSetKeyframedTrack* newTrack, GameObjectHandle newTarget);
		// 0x108AB800
		virtual ~PhysicsSetKeyframedAction();

		// vftable slot 5 (0x108AC290)
		virtual bool Slot5(int arg, float value);

		core::Link<PhysicsSetKeyframedTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};

	// RTTI: engine::DeleteAllDecalsAction (9 vftable slots, size 0x28)
	class DeleteAllDecalsAction : public fight::Action
	{
	public:
		// 0x108AC870
		DeleteAllDecalsAction(DeleteAllDecalsTrack* newTrack, core::IRefCount* owner);
		// 0x108AC800
		virtual ~DeleteAllDecalsAction();

		// vftable slot 5 (0x108AC780)
		virtual bool Slot5(int arg, float value);

		core::Link<DeleteAllDecalsTrack> link;  // +0x1C
	};

	// RTTI: engine::SetEffectTimerAction (9 vftable slots, size 0x28)
	class SetEffectTimerAction : public fight::Action
	{
	public:
		// 0x108ACB00
		SetEffectTimerAction(SetEffectTimerTrack* newTrack, core::IRefCount* owner);
		// 0x108ACA80
		virtual ~SetEffectTimerAction();

		// vftable slot 5 (0x108ACB70)
		virtual bool Slot5(int arg, float value);

		core::Link<SetEffectTimerTrack> link;  // +0x1C
	};

	namespace animation
	{
		// RTTI: engine::animation::ShaderAnimationAction (9 vftable slots, size 0x2C)
		class ShaderAnimationAction : public fight::Action
		{
		public:
			// 0x108ACD50
			ShaderAnimationAction(ShaderAnimationTrack* newTrack, GameObjectHandle newTarget);
			// 0x108ACCC0
			virtual ~ShaderAnimationAction();

			// vftable slot 5 (0x108ACDE0)
			virtual bool Slot5(int arg, float value);
			// vftable slot 6 (0x108ACF90)
			virtual void Slot6();

			core::Link<ShaderAnimationTrack> link;  // +0x1C
			GameObjectHandle target;  // +0x28
		};

	}

	// What a collision switch needs of an object it acts on (declared for the lookups the actions make; another unit's)
	// RTTI: engine::CollisionEnableBaseAction (12 vftable slots, size 0x28): the common part of the actions that switch
	// collision objects of a physics object on and off
	class CollisionEnableBaseAction : public fight::Action
	{
	public:
		// 0x108AAFB0
		explicit CollisionEnableBaseAction(GameObjectHandle newTarget);
		// 0x108AAFE0
		virtual ~CollisionEnableBaseAction();

		// vftable slot 5 (0x108AB5E0) and slot 6 (0x108AB6C0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		// vftable slot 9: the index of the collision object the track names on a physics object, or -1
		virtual int FindObject(const void* object) = 0;
		// vftable slot 10 / 11: what the track does when it begins / ends
		virtual int GetActionOnBegin() = 0;
		virtual int GetActionOnEnd() = 0;

		GameObjectHandle target;  // +0x1C
		int unknown20;
		bool unknown24;
	};

	// RTTI: engine::CollisionEnableByNameAction (12 vftable slots, size 0x34)
	class CollisionEnableByNameAction : public CollisionEnableBaseAction
	{
	public:
		// 0x108ABD70
		CollisionEnableByNameAction(CollisionEnableByNameTrack* newTrack, GameObjectHandle newTarget);
		// 0x108AB770
		virtual ~CollisionEnableByNameAction();

		// vftable slot 9 (0x108ABDE0), 10 (0x108ABE50) and 11 (0x108ABE60)
		virtual int FindObject(const void* object);
		virtual int GetActionOnBegin();
		virtual int GetActionOnEnd();

		core::Link<CollisionEnableByNameTrack> link;  // +0x28
	};

	// RTTI: engine::CollisionEnableOnJointAction (12 vftable slots, size 0x34)
	class CollisionEnableOnJointAction : public CollisionEnableBaseAction
	{
	public:
		// 0x108ABE70
		CollisionEnableOnJointAction(CollisionEnableOnJointTrack* newTrack, GameObjectHandle newTarget);
		// 0x108AB7B0
		virtual ~CollisionEnableOnJointAction();

		// vftable slot 9 (0x108ABEE0), 10 (0x108ABF80) and 11 (0x108ABF90)
		virtual int FindObject(const void* object);
		virtual int GetActionOnBegin();
		virtual int GetActionOnEnd();

		core::Link<CollisionEnableOnJointTrack> link;  // +0x28
	};

	// The collision switches an action remembers to undo (an index and the state it had)
	struct CollisionSwitch
	{
		int index;
		bool enabled;
	};

	// The array that holds them (begin, end and capacity; this unit's own copy of the engine's container)
	struct CollisionSwitchList
	{
		CollisionSwitchList() : begin(0), end(0), capacity(0)
		{
		}
		~CollisionSwitchList()
		{
			end = begin;
			if (begin != 0)
			{
				delete[] begin;
			}
		}

		CollisionSwitch* begin;
		CollisionSwitch* end;
		CollisionSwitch* capacity;
	};

	// RTTI: engine::CollisionEnableFromRootJointAction (9 vftable slots, size 0x40)
	class CollisionEnableFromRootJointAction : public fight::Action
	{
	public:
		// 0x108AC600
		CollisionEnableFromRootJointAction(CollisionEnableFromRootJointTrack* newTrack, GameObjectHandle newTarget);
		// 0x108AC660
		virtual ~CollisionEnableFromRootJointAction();

		// vftable slot 5 (0x108ABFA0) and slot 6 (0x108AC140)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		core::Link<CollisionEnableFromRootJointTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		int unknown2c;
		CollisionSwitchList switches;  // +0x30
		int unknown3c;
	};

	// RTTI: engine::PhysicsKeyframedEnableAction (9 vftable slots, size 0x20)
	class PhysicsKeyframedEnableAction : public fight::Action
	{
	public:
		// 0x108AAFF0
		explicit PhysicsKeyframedEnableAction(GameObjectHandle newTarget);
		// 0x108AB010
		virtual ~PhysicsKeyframedEnableAction();

		// vftable slot 5 (0x108AB830) and slot 6 (0x108AB8A0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		GameObjectHandle target;  // +0x1C
	};

}

#endif
