#include "code/proto/behaviours/lockontargetingbehaviour.h"
#include "code/engine/audio/audiomanager.h"
#include "code/engine/audio/audiomessage.h"

namespace proto
{
#define PROTO_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102A8350
	content::ClassInfo* AutoTargetingBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AutoTargetingBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102AA300
	content::ClassInfo* LockOnTargetingBehaviour::TargetLockCone::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::LockOnTargetingBehaviour::TargetLockCone";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102AA340
	content::ClassInfo* LockOnTargetingBehaviour::SoundParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::LockOnTargetingBehaviour::SoundParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102AA380
	content::ClassInfo* LockOnTargetingBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::LockOnTargetingBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102AB5E0
	content::MemberList* LockOnTargetingBehaviour::SoundParams::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberNameMetaType<SoundParams, 0>(true, true, "p"), PROTO_OFFSET(SoundParams, targetAquired),
				"targetAquired" },
			{ content::GetMemberNameMetaType<SoundParams, 1>(true, true, "p"),
				PROTO_OFFSET(SoundParams, targetDestroyed), "targetDestroyed" },
			{ content::GetMemberNameMetaType<SoundParams, 2>(true, true, "p"),
				PROTO_OFFSET(SoundParams, targetSustained), "targetSustained" },
			{ content::GetMemberNameMetaType<SoundParams, 3>(true, true, "p"),
				PROTO_OFFSET(SoundParams, targetModeEntered), "targetModeEntered" },
			{ content::GetMemberNameMetaType<SoundParams, 4>(true, true, "p"),
				PROTO_OFFSET(SoundParams, targetModeExited), "targetModeExited" },
			{ content::GetMemberNameMetaType<SoundParams, 5>(true, true, "p"),
				PROTO_OFFSET(SoundParams, targetModeLoop), "targetModeLoop" },
			{ content::GetMemberNameMetaType<SoundParams, 6>(true, true, "p"),
				PROTO_OFFSET(SoundParams, targetAbandoned), "targetAbandoned" }
		};
		sList.members = sMembers;
		sList.count = 7;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102AB810
	LockOnTargetingBehaviour::SoundParams::SoundParams() : enabled(false)
	{
	}

	// FUNCTION: ENGINE 0x102AB870
	void LockOnTargetingBehaviour::SoundParams::PlayName(const core::Name<core::CaseSensitiveKey>& name)
	{
		if (!name.IsEmpty())
		{
			engine::AudioManager::Get()->PlayPatch(name, engine::gAudioPlay, 0, 0);
		}
	}

	// FUNCTION: ENGINE 0x102AB8B0
	void LockOnTargetingBehaviour::SoundParams::StopName(const core::Name<core::CaseSensitiveKey>& name)
	{
		if (!name.IsEmpty())
		{
			engine::AudioManager::Get()->PlayPatch(name, engine::gAudioStop, 0, 0);
		}
	}

	// FUNCTION: ENGINE 0x102AB8F0
	void LockOnTargetingBehaviour::SoundParams::SetEnabled(bool on)
	{
		if (enabled)
		{
			if (!on)
			{
				StopName(targetSustained);
				StopName(targetModeLoop);
			}
		}
		enabled = on;
	}

	// FUNCTION: ENGINE 0x102AB940
	void LockOnTargetingBehaviour::SoundParams::OnTargetAcquired()
	{
		if (enabled)
		{
			PlayName(targetAquired);
			PlayName(targetSustained);
		}
	}

	// FUNCTION: ENGINE 0x102AB970
	void LockOnTargetingBehaviour::SoundParams::OnTargetDestroyed()
	{
		if (enabled)
		{
			PlayName(targetDestroyed);
			StopName(targetSustained);
		}
	}

	// FUNCTION: ENGINE 0x102AB9A0
	void LockOnTargetingBehaviour::SoundParams::OnTargetModeEntered()
	{
		if (enabled)
		{
			PlayName(targetModeEntered);
			PlayName(targetModeLoop);
		}
	}

	// FUNCTION: ENGINE 0x102AB9D0
	void LockOnTargetingBehaviour::SoundParams::OnTargetModeExited()
	{
		if (enabled)
		{
			PlayName(targetModeExited);
			StopName(targetModeLoop);
		}
	}

	// FUNCTION: ENGINE 0x102ABA00
	void LockOnTargetingBehaviour::SoundParams::OnTargetAbandoned()
	{
		if (enabled)
		{
			PlayName(targetAbandoned);
			StopName(targetSustained);
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102AB0F0
// FUNCTION: ENGINE 0x102AB130
// FUNCTION: ENGINE 0x102AB170
// FUNCTION: ENGINE 0x102AB1B0
// FUNCTION: ENGINE 0x102AB1F0
// FUNCTION: ENGINE 0x102AB230
// FUNCTION: ENGINE 0x102AB270
