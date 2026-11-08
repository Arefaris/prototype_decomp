// engine::CharacterSolverBehaviour (RTTI and reflection names; base engine::Behaviour): the behaviour that moves a
// character through the physics: the supporting limbs (feet and hands that find the surface the character stands on),
// the shared limits of the solver and the constraints that keep the character on its feet. Part of the unit 0x10907E90 -
// 0x1090C110 (it shares it with the solver properties; no assert path, the directory and file name are guesses). The
// reflected member names are original; the rest is guessed.
#ifndef ENGINE_CHARACTERSOLVERBEHAVIOUR_H
#define ENGINE_CHARACTERSOLVERBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/engine/charactersolverproperties.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/physics/supportinglimb.h"

namespace engine
{
	class CharacterSolverBehaviour : public Behaviour
	{
	public:
		typedef container::ArrayDynamic<SupportingLimb, container::AllocatorNew> LimbArray;

		// 0x1090AFF0
		explicit CharacterSolverBehaviour(GameObject* newOwner);

		// 0x10907ED0 / 0x1090AA30
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknownC[0x44];
		SupportingLimbDefinitionList* limbDefinitions;  // +0x50
		LimbArray supportingLimbs;  // +0x54
		unsigned char unknown60[4];
		SupportingLimb* unknown64;  // +0x64
		float supportingLimbUpdateInterval;  // +0x68
		unsigned char unknown6C[0x10];
		CharacterSolverProperties* sharedProperties;  // +0x7C
		bool limbIKEnabled;  // +0x80
		unsigned char unknown81[0x23];
		bool sweepAndClipMotion;  // +0xA4
		unsigned char unknownA5[0x59];
		bool predictSupportingLimbSurfaceContact;  // +0xFE
		unsigned char unknownFF[1];
	};
}

#endif
