// engine::CharacterSolverBehaviour (RTTI and reflection names; base engine::Behaviour): unit 0x10907E90 - 0x1090C110
// (no assert path; the file name is a guess). The class information and the reflection are reconstructed so far.
#include "code/engine/charactersolverbehaviour.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10907ED0
	content::ClassInfo* CharacterSolverBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "CharacterSolverBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1090AA30
	content::MemberList* CharacterSolverBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, CharacterSolverBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<CharacterSolverBehaviour, SupportingLimbDefinitionList>("p"),
				ENGINE_OFFSET(CharacterSolverBehaviour, limbDefinitions), "supportingLimbs" },
			{ content::GetMemberPrimitiveMetaType<CharacterSolverBehaviour, bool, 0>("p"),
				ENGINE_OFFSET(CharacterSolverBehaviour, limbIKEnabled), "limbIKEnabled" },
			{ content::GetMemberPrimitiveMetaType<CharacterSolverBehaviour, bool, 1>("p"),
				ENGINE_OFFSET(CharacterSolverBehaviour, sweepAndClipMotion), "sweepAndClipMotion" },
			{ content::GetMemberPrimitiveMetaType<CharacterSolverBehaviour, float, 0>("p"),
				ENGINE_OFFSET(CharacterSolverBehaviour, supportingLimbUpdateInterval),
				"supportingLimbUpdateInterval" },
			{ content::GetReferenceMetaType<CharacterSolverBehaviour, CharacterSolverProperties>("p"),
				ENGINE_OFFSET(CharacterSolverBehaviour, sharedProperties), "sharedProperties" },
			{ content::GetMemberPrimitiveMetaType<CharacterSolverBehaviour, bool, 2>("p"),
				ENGINE_OFFSET(CharacterSolverBehaviour, predictSupportingLimbSurfaceContact),
				"predictSupportingLimbSurfaceContact" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}
}

namespace container
{
	template class ArrayDynamic<engine::SupportingLimb, AllocatorNew>;
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10908210
// FUNCTION: ENGINE 0x10908230
// FUNCTION: ENGINE 0x10908250
// FUNCTION: ENGINE 0x10908260
// FUNCTION: ENGINE 0x10908280
// FUNCTION: ENGINE 0x10908370
// FUNCTION: ENGINE 0x109083D0
// FUNCTION: ENGINE 0x10908450
// FUNCTION: ENGINE 0x109084B0
// FUNCTION: ENGINE 0x10908550
// FUNCTION: ENGINE 0x10908560
// FUNCTION: ENGINE 0x10909300
// FUNCTION: ENGINE 0x10909310
// FUNCTION: ENGINE 0x109095D0
// FUNCTION: ENGINE 0x10909610
// FUNCTION: ENGINE 0x10909650
// FUNCTION: ENGINE 0x10909690
// FUNCTION: ENGINE 0x109096E0
// FUNCTION: ENGINE 0x10909760
// FUNCTION: ENGINE 0x10909770
// FUNCTION: ENGINE 0x10909780
// FUNCTION: ENGINE 0x1090A910
// FUNCTION: ENGINE 0x1090A960
// FUNCTION: ENGINE 0x1090A9B0
// FUNCTION: ENGINE 0x1090AA00
// FUNCTION: ENGINE 0x1090ACD0
// FUNCTION: ENGINE 0x1090ADB0
// FUNCTION: ENGINE 0x1090ADF0
// FUNCTION: ENGINE 0x1090AE40
// FUNCTION: ENGINE 0x1090AF50
