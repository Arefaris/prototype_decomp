// The actions of the expression, joint lock, puppet move and undamageable tracks (unit 0x108F4630 - 0x108F6660, no
// assert path; file name guessed). The tracks are in expressiontracks.cpp.
#ifndef ENGINE_FIGHT_EXPRESSIONACTIONS_H
#define ENGINE_FIGHT_EXPRESSIONACTIONS_H

#include "code/choreo/drivers.h"
#include "code/choreo/puppet.h"
#include "code/choreo/rootdriver.h"
#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/expressiontracks.h"

namespace engine
{
	// 0x10098FB0: another unit's copy of the helper that releases a driver and clears the pointer
	void ReleaseDriverCopy2(choreo::Driver** driver);
	// 0x107F2010: the puppet of an object (the value of its puppet attribute), or null
	choreo::Puppet* GetPuppet(GameObject* object);

	// 0x108F5CD0: the part lookup the drawable attribute of an object holds, or null (name guessed)
	proto::PartLookup* GetPartLookup(GameObject* object);

	namespace animation
	{
		// 0x108F5B00: this unit's copy of the helper that releases a driver and clears the pointer
		void ReleaseJointDriver(choreo::Driver** driver);
	}

	namespace animation
	{
		// RTTI: engine::animation::EnableMotionTrackedExpressionAction (9 vftable slots, size 0x2C)
		class EnableMotionTrackedExpressionAction : public fight::Action
		{
		public:
			// 0x108F48C0
			EnableMotionTrackedExpressionAction(EnableMotionTrackedExpressionTrack* newTrack, GameObjectHandle newTarget);
			// 0x108F4790
			virtual ~EnableMotionTrackedExpressionAction();

			// vftable slot 5 (0x108F4950)
			virtual bool Slot5(int arg, float value);

			core::Link<EnableMotionTrackedExpressionTrack> link;  // +0x1C
			GameObjectHandle target;  // +0x28
		};

		// RTTI: engine::animation::DisableMotionTrackedExpressionAction (9 vftable slots, size 0x2C)
		class DisableMotionTrackedExpressionAction : public fight::Action
		{
		public:
			// 0x108F49F0
			DisableMotionTrackedExpressionAction(DisableMotionTrackedExpressionTrack* newTrack, GameObjectHandle newTarget);
			// 0x108F47D0
			virtual ~DisableMotionTrackedExpressionAction();

			// vftable slot 5 (0x108F4A80)
			virtual bool Slot5(int arg, float value);

			core::Link<DisableMotionTrackedExpressionTrack> link;  // +0x1C
			GameObjectHandle target;  // +0x28
		};

		// RTTI: engine::animation::ExpressionAnimationAction (9 vftable slots, size 0x2C)
		class ExpressionAnimationAction : public fight::Action
		{
		public:
			// 0x108F4D50
			ExpressionAnimationAction(ExpressionAnimationTrack* newTrack, GameObjectHandle newTarget);
			// 0x108F4C90
			virtual ~ExpressionAnimationAction();

			// vftable slot 5 (0x108F4DE0), slot 6 (0x108F4C00) and slot 7 (0x108F4CC0)
			virtual bool Slot5(int arg, float value);
			virtual void Slot6();
			virtual bool Slot7(int arg, float value);

			core::Link<ExpressionAnimationTrack> link;  // +0x1C
			GameObjectHandle target;  // +0x28
		};

		// RTTI: engine::animation::PuppetMoveAction (9 vftable slots, size 0x3C)
		class PuppetMoveAction : public fight::Action
		{
		public:
			// 0x108F5E20
			PuppetMoveAction(PuppetMoveTrack* newTrack, GameObjectHandle newTarget);
			// 0x108F5BF0
			virtual ~PuppetMoveAction();

			// vftable slot 5 (0x108F5EB0), slot 6 (0x108F5C20) and slot 7 (0x108F5FE0)
			virtual bool Slot5(int arg, float value);
			virtual void Slot6();
			virtual bool Slot7(int arg, float value);

			core::Link<PuppetMoveTrack> link;  // +0x1C
			GameObjectHandle target;  // +0x28
			// What is left of the track's distance to move
			math::Vector remaining;  // +0x2C
			choreo::RootDriver* driver;  // +0x38
		};

		// RTTI: engine::animation::JointLockAction (9 vftable slots, size 0x30)
		class JointLockAction : public fight::Action
		{
		public:
			// 0x108F6150
			JointLockAction(JointLockTrack* newTrack, GameObjectHandle newTarget);
			// 0x108F5CA0
			virtual ~JointLockAction();

			// vftable slot 5 (0x108F61C0), slot 6 (0x108F5D00) and slot 7 (0x108F6400)
			virtual bool Slot5(int arg, float value);
			virtual void Slot6();
			virtual bool Slot7(int arg, float value);

			core::Link<JointLockTrack> link;  // +0x1C
			GameObjectHandle target;  // +0x28
			choreo::JointLockDriver* driver;  // +0x2C
		};
	}

	// RTTI: engine::UndamageableAction (9 vftable slots, size 0x20): makes an object undamageable while it runs
	class UndamageableAction : public fight::Action
	{
	public:
		// 0x108F64F0
		explicit UndamageableAction(GameObjectHandle newTarget);
		// 0x108F6510
		virtual ~UndamageableAction();

		// vftable slot 5 (0x108F6590) and slot 6 (0x108F6600)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		GameObjectHandle target;  // +0x1C
	};
}

#endif
