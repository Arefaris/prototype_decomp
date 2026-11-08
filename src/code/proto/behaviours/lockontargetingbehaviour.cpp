#include "code/proto/behaviours/lockontargetingbehaviour.h"
#include "code/engine/audio/audiomanager.h"
#include "code/engine/audio/audiomessage.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/motion/motionmessages5.h"

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

	// FUNCTION: ENGINE 0x102A8390
	AutoTargetingBehaviour::AutoTargetingBehaviour(engine::GameObject* newOwner) : TargetingBehaviour(newOwner),
		defaultAutoTargetPriorityList(0), currentAutoTargetPriorityList(0), markerOverrideAutoTargetPriorityList(0)
	{
	}

	// FUNCTION: ENGINE 0x102A83E0
	void AutoTargetingBehaviour::Slot1()
	{
		ClearTarget();
	}

	// FUNCTION: ENGINE 0x102A83F0
	void AutoTargetingBehaviour::GetLastTarget(GetAutoTargetMessage* message)
	{
		engine::GameObjectHandle value = lastTarget;
		message->target = value;
	}

	// FUNCTION: ENGINE 0x102A8400
	void AutoTargetingBehaviour::SetLastTarget(SetAutoTargetMessage* message)
	{
		lastTarget = message->target;
	}

	// FUNCTION: ENGINE 0x102A85D0
	AutoTargetingBehaviour::~AutoTargetingBehaviour()
	{
		core::SafeRelease(markerOverrideAutoTargetPriorityList);
		core::SafeRelease(currentAutoTargetPriorityList);
		core::SafeRelease(defaultAutoTargetPriorityList);
	}

	// FUNCTION: ENGINE 0x102A8610
	void AutoTargetingBehaviour::ClearTarget()
	{
		core::RefAssign(currentAutoTargetPriorityList, defaultAutoTargetPriorityList);
		lastTarget = engine::GameObjectHandle();
		TargetingBehaviour::ClearTarget();
	}

	// FUNCTION: ENGINE 0x102A8650
	void AutoTargetingBehaviour::ApplyMarkerEntry(int targetClass, TargetClassPriority* result)
	{
		TargetClassPriority* entry = markerOverrideAutoTargetPriorityList->GetEntry(targetClass);
		if (entry == 0)
		{
			return;
		}
		if (result->targetCategory < entry->targetCategory
			|| (result->targetCategory == entry->targetCategory && result->targetPriority < entry->targetPriority))
		{
			result->targetCategory = entry->targetCategory;
			result->targetPriority = entry->targetPriority;
		}
		float distance = result->maxTargetableDistance;
		if (entry->maxTargetableDistance > distance)
		{
			distance = entry->maxTargetableDistance;
		}
		result->maxTargetableDistance = distance;
		float lockOnDistance = result->maxLockOnTargetableDistance;
		if (entry->maxLockOnTargetableDistance > lockOnDistance)
		{
			lockOnDistance = entry->maxLockOnTargetableDistance;
		}
		result->maxLockOnTargetableDistance = lockOnDistance;
		if (entry->isThreat)
		{
			result->isThreat = entry->isThreat;
		}
	}

	// FUNCTION: ENGINE 0x102A86E0
	void AutoTargetingBehaviour::GetTargetClassPriority(engine::GameObject* object, int targetClass, unsigned int flags,
		TargetClassPriority* result)
	{
		if (currentAutoTargetPriorityList != 0)
		{
			TargetClassPriority* entry = currentAutoTargetPriorityList->GetEntry(targetClass);
			if (entry != 0)
			{
				*result = *entry;
			}
		}
		if (markerOverrideAutoTargetPriorityList != 0 && object != 0)
		{
			GetMarkerIconTypeMessage message;
			object->SendMessage(&message);
			switch (message.iconType)
			{
			case 0:
				ApplyMarkerEntry(0x2a, result);
				break;
			case 2:
				if (flags & 8)
				{
					ApplyMarkerEntry(0x2b, result);
				}
				break;
			case 0x24:
				if (flags & 8)
				{
					ApplyMarkerEntry(0x2e, result);
				}
				break;
			case 5:
				if (flags & 8)
				{
					ApplyMarkerEntry(0x2c, result);
				}
				break;
			case 0x10:
				ApplyMarkerEntry(0x2d, result);
				break;
			}
		}
	}

	// FUNCTION: ENGINE 0x102A90D0
	content::MemberList* AutoTargetingBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<TargetingBehaviour>();
		static content::BaseClassCasterImpl<TargetingBehaviour, AutoTargetingBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberReferenceMetaType<AutoTargetingBehaviour, AutoTargetPriorityList, 0>("p"),
				PROTO_OFFSET(AutoTargetingBehaviour, defaultAutoTargetPriorityList), "defaultAutoTargetPriorityList" },
			{ content::GetMemberReferenceMetaType<AutoTargetingBehaviour, AutoTargetPriorityList, 1>("p"),
				PROTO_OFFSET(AutoTargetingBehaviour, markerOverrideAutoTargetPriorityList),
				"markerOverrideAutoTargetPriorityList" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102A9CA0
	void AutoTargetingBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			ClearTarget();
			break;
		case 0x20:
			switch ((unsigned short)message->id)
			{
			case 3:
				OnGetAutoTarget(message);
				break;
			case 4:
				OnSetAutoTarget(message);
				break;
			case 5:
				GetLastTarget((GetAutoTargetMessage*)message);
				break;
			case 6:
				SetLastTarget((SetAutoTargetMessage*)message);
				break;
			case 7:
				OnMessage7(message);
				break;
			default:
				TargetingBehaviour::OnMessage(message);
				break;
			}
			break;
		}
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
// FUNCTION: ENGINE 0x102A8590
// FUNCTION: ENGINE 0x102A85A0
// FUNCTION: ENGINE 0x102A84B0
// FUNCTION: ENGINE 0x102A8FA0
// FUNCTION: ENGINE 0x102A9000
