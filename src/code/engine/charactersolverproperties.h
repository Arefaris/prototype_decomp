// engine::CharacterSolverProperties (RTTI and reflection names): a content library object with the limits of the
// character solver, the physics that moves a character: how hard it may accelerate and turn, how fast it may be
// pushed, and how it behaves on a moving platform. Part of the unit 0x10907E90 - 0x1090C110 (it shares it with the
// character solver behaviour, which is not reconstructed; no assert path, the directory and file name are guesses).
// The reflected member names are original; the rest is guessed.
#ifndef ENGINE_CHARACTERSOLVERPROPERTIES_H
#define ENGINE_CHARACTERSOLVERPROPERTIES_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"

namespace engine
{
	struct CharacterSolverProperties : public content::MetaLoadObject
	{
	public:
		// 0x109084D0
		CharacterSolverProperties();
		// 0x10908540 (deleting destructor 0x10908590)
		virtual ~CharacterSolverProperties()
		{
		}

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		float maxLinearAcceleration;  // +8
		float maxSteeringAngularForce;  // +0xC
		float maxPushVelocity;  // +0x10
		bool platformingEnabled;  // +0x14
		float effectiveCharacterMassOnPlatform;  // +0x18
		float minMassRatioForPlatforming;  // +0x1C
		float maxVelocityGainedFromPlatform;  // +0x20
	};
}

#endif
