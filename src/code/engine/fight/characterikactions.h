// The actions of the character inverse kinematics and jump tracks (the code sits in 0x10930870 - 0x10931980, no assert
// path; file name guessed). The tracks are in characterik.cpp.
#ifndef ENGINE_FIGHT_CHARACTERIKACTIONS_H
#define ENGINE_FIGHT_CHARACTERIKACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/characterik.h"
#include "code/engine/fight/effecttrack.h"

namespace engine
{
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
}

#endif
