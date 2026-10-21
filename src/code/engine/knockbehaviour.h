// engine::KnockBehaviour (RTTI and reflection names; base engine::Behaviour): knocks the things around its owner
// away. While its update runs it counts the repeat period down and, when the player's object is in a certain state
// and the period is over, pushes every object of the world in range (a distance and the cosine of half the angle in
// front of the owner) with a strength, and deals damage to the objects that can take it. Unit 0x1091EC70 -
// 0x1091F380 (no assert path; the directory and file name are guesses). The reflected member names are original; the
// rest is guessed.
#ifndef ENGINE_KNOCKBEHAVIOUR_H
#define ENGINE_KNOCKBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"

namespace engine
{
	class KnockBehaviour : public Behaviour
	{
	public:
		// 0x1091ECB0
		explicit KnockBehaviour(GameObject* newOwner);
		// 0x1091ED10 (deleting destructor 0x1091ED80)
		virtual ~KnockBehaviour()
		{
		}

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x1091ED20): does nothing
		virtual void Slot1()
		{
		}
		// vftable slot 4 (0x1091EDA0)
		virtual void Update(float dt, unsigned short mask);

		float strength;  // +0xC
		float rangeDistance;  // +0x10
		float rangeCosHalfAngle;  // +0x14
		float minimumRepeatPeriod;  // +0x18
		float repeatTimer;  // +0x1C
		float damage;  // +0x20
	};
}

#endif
