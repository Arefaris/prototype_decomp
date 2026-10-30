#include "code/engine/animation/behaviours/puppetbehaviour.h"

namespace engine
{
	namespace animation
	{
		// FUNCTION: ENGINE 0x1091B180
		content::ClassInfo* PuppetBehaviour::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "PuppetBehaviour";
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x1091B1D0
		bool PuppetBehaviour::GetIkLimbsEnabled() const
		{
			if (puppet == 0)
			{
				return ikLimbsEnabled;
			}
			return puppet->mUnknown40;
		}

		// FUNCTION: ENGINE 0x1091B1E0
		void PuppetBehaviour::SetIkLimbsEnabled(bool value)
		{
			ikLimbsEnabled = value;
			if (puppet != 0)
			{
				puppet->mUnknown40 = value;
			}
		}

		// FUNCTION: ENGINE 0x1091B200
		bool PuppetBehaviour::GetAutoUpdateLocomotionPhase() const
		{
			if (puppet == 0)
			{
				return autoUpdateLocomotionPhase;
			}
			return puppet->mUnknown15C;
		}

		// FUNCTION: ENGINE 0x1091B220
		void PuppetBehaviour::SetAutoUpdateLocomotionPhase(bool value)
		{
			autoUpdateLocomotionPhase = value;
			if (puppet != 0)
			{
				puppet->mUnknown15C = value;
			}
		}

		// FUNCTION: ENGINE 0x1091B240
		bool PuppetBehaviour::GetDeferredUpdate() const
		{
			return deferredUpdate;
		}

		// FUNCTION: ENGINE 0x1091BF20
		content::MemberList* PuppetBehaviour::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<Behaviour>();
			static content::BaseClassCasterImpl<Behaviour, PuppetBehaviour> sCaster;
			sList.baseCaster = &sCaster;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetMemberMetaType<PuppetBehaviour, bool, 0>(&PuppetBehaviour::GetIkLimbsEnabled,
					&PuppetBehaviour::SetIkLimbsEnabled, "p"), 0, "ikLimbsEnabled" },
				{ content::GetMemberMetaType<PuppetBehaviour, bool, 1>(&PuppetBehaviour::GetAutoUpdateLocomotionPhase,
					&PuppetBehaviour::SetAutoUpdateLocomotionPhase, "p"), 0, "autoUpdateLocomotionPhase" },
				{ content::GetMemberMetaType<PuppetBehaviour, bool, 2>(&PuppetBehaviour::GetDeferredUpdate,
					&PuppetBehaviour::SetDeferredUpdate, "p"), 0, "deferredUpdate" },
				{ content::GetMemberPrimitiveMetaType<PuppetBehaviour, bool, 0>("p"),
					content::MemberOffset(&((PuppetBehaviour*)0)->suppressErrorOnDisableBatching,
					(int)&((PuppetBehaviour*)0)->suppressErrorOnDisableBatching), "suppressErrorOnDisableBatching" }
			};
			sList.members = sMembers;
			sList.count = 4;
			return &sList;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1091B320
// FUNCTION: ENGINE 0x1091B330
// FUNCTION: ENGINE 0x1091B870
// FUNCTION: ENGINE 0x1091B8B0
// FUNCTION: ENGINE 0x1091B8E0
// FUNCTION: ENGINE 0x1091B900
// FUNCTION: ENGINE 0x1091BDA0
// FUNCTION: ENGINE 0x1091BE20
// FUNCTION: ENGINE 0x1091BEA0
