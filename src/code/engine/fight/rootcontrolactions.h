// The actions of the root control, strafe adjust and steering tracks (the code sits in 0x10931C30 - 0x109337A0, no
// assert path; file name guessed). The tracks are in rootcontrol.cpp.
#ifndef ENGINE_FIGHT_ROOTCONTROLACTIONS_H
#define ENGINE_FIGHT_ROOTCONTROLACTIONS_H

#include "code/choreo/drivers.h"
#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/rootcontrol.h"

namespace engine
{
	// RTTI: engine::CharacterSteerAction (9 vftable slots, size 0x34): steers the character with a locomotion driver
	class CharacterSteerAction : public fight::Action
	{
	public:
		// 0x10932510
		CharacterSteerAction(CharacterSteerTrack* newTrack, GameObjectHandle newTarget);
		// 0x109320B0
		virtual ~CharacterSteerAction();

		// vftable slot 5 (0x10932590), 6 (0x109320E0) and 7 (0x10932930)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<CharacterSteerTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		choreo::LocomotionSteerDriver* driver;  // +0x2C
		float unknown30;
	};

	// RTTI: engine::ControlRootAction (9 vftable slots, size 0x30): controls the root of the character with a root driver
	class ControlRootAction : public fight::Action
	{
	public:
		// 0x10932CB0
		ControlRootAction(ControlRootTrack* newTrack, GameObjectHandle newTarget);
		// 0x10932170
		virtual ~ControlRootAction();

		// vftable slot 5 (0x10932D20), 6 (0x109321A0) and 7 (0x10932E30)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<ControlRootTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		choreo::RootDriver* driver;  // +0x2C
	};

	// RTTI: engine::StrafeAdjustRootAction (9 vftable slots, size 0x30)
	class StrafeAdjustRootAction : public fight::Action
	{
	public:
		// 0x109330A0
		StrafeAdjustRootAction(StrafeAdjustRootTrack* newTrack, GameObjectHandle newTarget);
		// 0x10932210
		virtual ~StrafeAdjustRootAction();

		// vftable slot 5 (0x10933110), 6 (0x10932240) and 7 (0x109332B0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<StrafeAdjustRootTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		choreo::StrafeAdjustRootDriver* driver;  // +0x2C
	};

	// RTTI: engine::ChoreoTestsAction (9 vftable slots, size 0x38): puts test drivers into the puppet of the character
	class ChoreoTestsAction : public fight::Action
	{
	public:
		// 0x10933320
		ChoreoTestsAction(ChoreoTestsTrack* newTrack, GameObjectHandle newTarget);
		// 0x109322B0
		virtual ~ChoreoTestsAction();

		// vftable slot 5 (0x109333A0), 6 (0x10932300) and 7 (0x10933510)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<ChoreoTestsTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		choreo::PoseDriver* poseDriver;  // +0x2C
		choreo::RestPoseDriver* restPoseDriver;  // +0x30
		choreo::Driver* copyDriver;  // +0x34
	};
}

#endif
