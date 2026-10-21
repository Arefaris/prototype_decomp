#include "code/engine/charactersolverproperties.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10907E90
	content::ClassInfo* CharacterSolverProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::CharacterSolverProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x109084D0
	// EQUIVALENT: the engine loads each constant right before its store (100.0 twice) and after the base stores, ours loads
	// them up front and keeps 100.0 in a register, 42.7 %
	CharacterSolverProperties::CharacterSolverProperties()
	{
		maxLinearAcceleration = 100.0f;
		maxSteeringAngularForce = 10000.0f;
		maxPushVelocity = 1000.0f;
		platformingEnabled = true;
		effectiveCharacterMassOnPlatform = 100.0f;
		minMassRatioForPlatforming = 0.25f;
		maxVelocityGainedFromPlatform = 50.0f;
	}

	// FUNCTION: ENGINE 0x109097A0
	content::MemberList* CharacterSolverProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<CharacterSolverProperties, float, 0>("p"),
				ENGINE_OFFSET(CharacterSolverProperties, maxLinearAcceleration), "maxLinearAcceleration" },
			{ content::GetMemberPrimitiveMetaType<CharacterSolverProperties, float, 1>("p"),
				ENGINE_OFFSET(CharacterSolverProperties, maxSteeringAngularForce), "maxSteeringAngularForce" },
			{ content::GetMemberPrimitiveMetaType<CharacterSolverProperties, float, 2>("p"),
				ENGINE_OFFSET(CharacterSolverProperties, maxPushVelocity), "maxPushVelocity" },
			{ content::GetMemberPrimitiveMetaType<CharacterSolverProperties, bool, 0>("p"),
				ENGINE_OFFSET(CharacterSolverProperties, platformingEnabled), "platformingEnabled" },
			{ content::GetMemberPrimitiveMetaType<CharacterSolverProperties, float, 3>("p"),
				ENGINE_OFFSET(CharacterSolverProperties, effectiveCharacterMassOnPlatform),
				"effectiveCharacterMassOnPlatform" },
			{ content::GetMemberPrimitiveMetaType<CharacterSolverProperties, float, 4>("p"),
				ENGINE_OFFSET(CharacterSolverProperties, minMassRatioForPlatforming), "minMassRatioForPlatforming" },
			{ content::GetMemberPrimitiveMetaType<CharacterSolverProperties, float, 5>("p"),
				ENGINE_OFFSET(CharacterSolverProperties, maxVelocityGainedFromPlatform),
				"maxVelocityGainedFromPlatform" }
		};
		sList.members = sMembers;
		sList.count = 7;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10908540
// FUNCTION: ENGINE 0x10909410
// FUNCTION: ENGINE 0x10909450
// FUNCTION: ENGINE 0x10909490
// FUNCTION: ENGINE 0x109094D0
// FUNCTION: ENGINE 0x10909510
// FUNCTION: ENGINE 0x10909550
// FUNCTION: ENGINE 0x10909590
