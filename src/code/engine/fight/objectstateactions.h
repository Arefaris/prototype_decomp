// The actions of the object state tracks: velocity, simple message, transform and rotation attribute, puppet animation
// (unit 0x108EC9A0 - 0x108EE690, no assert path; file name guessed). The tracks are in objectstatetracks.cpp.
#ifndef ENGINE_FIGHT_OBJECTSTATEACTIONS_H
#define ENGINE_FIGHT_OBJECTSTATEACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/choreo/puppet.h"
#include "code/engine/fight/objectstatetracks.h"

namespace engine
{
	// RTTI: engine::VelocityLinearAction (9 vftable slots, size 0x2C)
	class VelocityLinearAction : public fight::Action
	{
	public:
		// 0x108ECC60
		VelocityLinearAction(VelocityLinearTrack* newTrack, GameObjectHandle newTarget);
		// 0x108ECB30
		virtual ~VelocityLinearAction();

		// vftable slot 5 (0x108ECCE0)
		virtual bool Slot5(int arg, float value);

		GameObjectHandle target;  // +0x1C
		core::Link<VelocityLinearTrack> link;  // +0x20
	};

	// RTTI: engine::VelocityAngularAction (9 vftable slots, size 0x2C)
	class VelocityAngularAction : public fight::Action
	{
	public:
		// 0x108ECE30
		VelocityAngularAction(VelocityAngularTrack* newTrack, GameObjectHandle newTarget);
		// 0x108ECB70
		virtual ~VelocityAngularAction();

		// vftable slot 5 (0x108ECEC0)
		virtual bool Slot5(int arg, float value);

		core::Link<VelocityAngularTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};

	// RTTI: engine::SimpleMessageAction (9 vftable slots, size 0x2C)
	class SimpleMessageAction : public fight::Action
	{
	public:
		// 0x108ED1B0
		SimpleMessageAction(SimpleMessageTrack* newTrack, GameObjectHandle newTarget);
		// 0x108ED120
		virtual ~SimpleMessageAction();

		// vftable slot 5 (0x108ED230)
		virtual bool Slot5(int arg, float value);

		GameObjectHandle target;  // +0x1C
		core::Link<SimpleMessageTrack> link;  // +0x20
	};

	// RTTI: engine::SetRotationAttributeAction (9 vftable slots, size 0x2C)
	class SetRotationAttributeAction : public fight::Action
	{
	public:
		// 0x108ED5D0
		SetRotationAttributeAction(SetRotationAttributeTrack* newTrack, GameObjectHandle newTarget);
		// 0x108ED4A0
		virtual ~SetRotationAttributeAction();

		// vftable slot 5 (0x108ED650)
		virtual bool Slot5(int arg, float value);

		GameObjectHandle target;  // +0x1C
		core::Link<SetRotationAttributeTrack> link;  // +0x20
	};

	// RTTI: engine::SetTransformAttributeAction (9 vftable slots, size 0x2C)
	class SetTransformAttributeAction : public fight::Action
	{
	public:
		// 0x108ED6F0
		SetTransformAttributeAction(SetTransformAttributeTrack* newTrack, GameObjectHandle newTarget);
		// 0x108ED4E0
		virtual ~SetTransformAttributeAction();

		// vftable slot 5 (0x108ED770)
		virtual bool Slot5(int arg, float value);

		GameObjectHandle target;  // +0x1C
		core::Link<SetTransformAttributeTrack> link;  // +0x20
	};

	// 0x100A0C40 (another unit's copy of the helper): releases a driver and clears the pointer
	void ReleaseDriver(choreo::Driver*& driver);
	// 0x100E0190: the same helper's other copy, which the action's stop calls
	void ReleaseDriverCopy(choreo::Driver*& driver);

	// RTTI: engine::PuppetAnimationAction (9 vftable slots, size 0x44): plays the puppet animation of its track on the
	// puppet of an object
	class PuppetAnimationAction : public fight::Action
	{
	public:
		// 0x108EDCE0
		PuppetAnimationAction(fight::Track* listener, PuppetAnimationTrack* newTrack, GameObjectHandle newTarget);
		// 0x108EDB60
		virtual ~PuppetAnimationAction();

		// vftable slot 5 (0x108EDD80), slot 6 (0x108EDBA0) and slot 7 (0x108EE480)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		TrackWatch watch;  // +0x1C
		core::Link<PuppetAnimationTrack> link;  // +0x28
		GameObjectHandle target;  // +0x34
		choreo::Driver* driver;  // +0x38
		float unknown3c;
		int unknown40;
	};
}

#endif
