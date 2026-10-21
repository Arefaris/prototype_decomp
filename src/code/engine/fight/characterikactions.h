// The actions of the character inverse kinematics and jump tracks (the code sits in 0x10930870 - 0x10931980, no assert
// path; file name guessed). The tracks are in characterik.cpp.
#ifndef ENGINE_FIGHT_CHARACTERIKACTIONS_H
#define ENGINE_FIGHT_CHARACTERIKACTIONS_H

#include "code/choreo/drivers.h"
#include "code/core/linklist.h"
#include "code/engine/fight/characterik.h"
#include "code/engine/fight/effecttrack.h"

namespace engine
{
	// RTTI: engine::CharacterIKAction (9 vftable slots, size 0x34): bends a limb of the character towards a target with an IK
	// driver
	class CharacterIKAction : public fight::Action
	{
	public:
		// 0x10930E60
		CharacterIKAction(CharacterIKTrack* newTrack, GameObjectHandle newTarget);
		// 0x10930CC0
		virtual ~CharacterIKAction();

		// vftable slot 5 (0x10930EE0), 6 (0x10931150) and 7 (0x10930970)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		// 0x10930CF0: turns the limb inverse kinematics of the character on or off
		void SetLimbIKEnabled(bool enabled);

		core::Link<CharacterIKTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		choreo::IKDriver* driver;  // +0x2C
		bool disabledLimbIK;  // +0x30
	};

	// RTTI: engine::CharacterEnableLimbIKAction (9 vftable slots, size 0x30): turns the limb inverse kinematics of the
	// character on or off while it runs
	class CharacterEnableLimbIKAction : public fight::Action
	{
	public:
		// 0x109311D0
		CharacterEnableLimbIKAction(CharacterEnableLimbIKTrack* newTrack, GameObjectHandle newTarget);
		// 0x10930D70
		virtual ~CharacterEnableLimbIKAction();

		// vftable slot 5 (0x10931240), 6 (0x10931320) and 7 (0x10930980)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<CharacterEnableLimbIKTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		bool previousEnabled;  // +0x2C
	};

	// RTTI: engine::CharacterJumpAction (9 vftable slots, size 0x40): makes the character jump with a root driver
	class CharacterJumpAction : public fight::Action
	{
	public:
		// 0x10931640
		CharacterJumpAction(CharacterJumpTrack* newTrack, GameObjectHandle newTarget);
		// 0x10931550
		virtual ~CharacterJumpAction();

		// vftable slot 5 (0x109316D0), 6 (0x10931580) and 7 (0x10931880)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();
		virtual bool Slot7(int arg, float value);

		core::Link<CharacterJumpTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
		choreo::RootDriver* driver;  // +0x2C
		math::Vector velocity;  // +0x30
		bool landed;  // +0x3C
	};
}

#endif
