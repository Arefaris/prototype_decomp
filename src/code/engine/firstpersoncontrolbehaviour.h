// engine::FirstPersonControlBehaviour (RTTI and reflection names; base engine::Behaviour): lets the player look
// around from the eyes of its owner. Every update pass 4 turns the owner's eyepoint by the player's look input
// (scaled by the horizontal and vertical sensitivity, with a dead zone for the vertical axis, inverted when asked)
// and moves the owner along the view at the reflected speed. Unit 0x1091DF60 - 0x1091EC70 (no assert path; the
// directory and file name are guesses). The reflected member names are original; the rest is guessed.
#ifndef ENGINE_FIRSTPERSONCONTROLBEHAVIOUR_H
#define ENGINE_FIRSTPERSONCONTROLBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"

namespace engine
{
	// 0x1131C888 (another unit): the name "EYEPOINT"
	extern core::Name<core::CaseSensitiveKey> gEyePointName;

	class FirstPersonControlBehaviour : public Behaviour
	{
	public:
		// 0x1091EBD0
		explicit FirstPersonControlBehaviour(GameObject* newOwner);
		// 0x1091DFA0 (deleting destructor 0x1091E050)
		virtual ~FirstPersonControlBehaviour()
		{
		}

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x1091DFB0): hands the camera of the controlling player to the owner's first person view
		virtual void Slot1();
		// vftable slot 4 (0x1091E360)
		virtual void Update(float dt, unsigned short mask);

		bool invert;  // +0xC
		float horizSensitivity;  // +0x10
		float vertSensitivity;  // +0x14
		float vertDeadZone;  // +0x18
		float speed;  // +0x1C
		float unknown20;  // +0x20
		float unknown24;  // +0x24
		Attribute<math::Matrix>* eyeTransform;  // +0x28
		GameObject* controlled;  // +0x2C
		float unknown30;  // +0x30
	};
}

#endif
