#include "code/proto/behaviours/lockontargetingbehaviour.h"
#include "code/engine/audio/audiomanager.h"
#include "code/engine/audio/audiomessage.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/fight/fighteventmessage.h"
#include "code/engine/online/ols.h"
#include "code/proto/behaviours/targetlockmessages.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/motion/motionmessages5.h"

namespace engine
{
	namespace driving
	{
		extern const float gHalf;
	}
}

namespace proto
{
	extern core::Name<core::CaseSensitiveKey> gProtoProfileTargetToggleEnabled;

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
			case 5:
				OnGetAutoTarget(message);
				break;
			case 6:
				OnSetAutoTarget(message);
				break;
			case 3:
				GetLastTarget((GetAutoTargetMessage*)message);
				break;
			case 4:
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

	// FUNCTION: ENGINE 0x102A9F60
	float LockOnTargetingBehaviour::TargetLockCone::GetArc() const
	{
		return arc * 57.295776f;
	}

	// FUNCTION: ENGINE 0x102A9F70
	void LockOnTargetingBehaviour::TargetLockCone::SetArc(float degrees)
	{
		arc = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x102AA3C0
	LockOnTargetingBehaviour::TargetLockCone::TargetLockCone() : distance(0.0f), arc(0.0f), minTargetCategory(0),
		minTargetPriority(0), maxTargetCategory(0), maxTargetPriority(0), useFacing(false)
	{
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

	// FUNCTION: ENGINE 0x102AECD0
	content::MemberList* LockOnTargetingBehaviour::TargetLockCone::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<TargetLockCone, float, 0>("p"), PROTO_OFFSET(TargetLockCone, distance),
				"distance" },
			{ content::GetMemberMetaType<TargetLockCone, float, 0>(&TargetLockCone::GetArc, &TargetLockCone::SetArc, "p"),
				0, "arc" },
			{ content::GetMemberPrimitiveMetaType<TargetLockCone, unsigned int, 0>("p"),
				PROTO_OFFSET(TargetLockCone, minTargetCategory), "minTargetCategory" },
			{ content::GetMemberPrimitiveMetaType<TargetLockCone, unsigned int, 1>("p"),
				PROTO_OFFSET(TargetLockCone, minTargetPriority), "minTargetPriority" },
			{ content::GetMemberPrimitiveMetaType<TargetLockCone, unsigned int, 2>("p"),
				PROTO_OFFSET(TargetLockCone, maxTargetCategory), "maxTargetCategory" },
			{ content::GetMemberPrimitiveMetaType<TargetLockCone, unsigned int, 3>("p"),
				PROTO_OFFSET(TargetLockCone, maxTargetPriority), "maxTargetPriority" },
			{ content::GetMemberPrimitiveMetaType<TargetLockCone, bool, 0>("p"), PROTO_OFFSET(TargetLockCone, useFacing),
				"useFacing" }
		};
		sList.members = sMembers;
		sList.count = 7;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102AA410
	void LockOnTargetingBehaviour::Slot1()
	{
		AutoTargetingBehaviour::Slot1();
		engine::DBSubject* subject = engine::gGameDatabase->AddObserver(gProtoProfileTargetToggleEnabled,
			static_cast<engine::DBObserver*>(this), 0, 0);
		if (subject != 0)
		{
			unsigned int player = engine::OLS::Get()->currentUser->id;
			toggleToTargetLock = subject->GetInt(player, 0) != 0;
		}
	}

	// FUNCTION: ENGINE 0x102AA480
	void LockOnTargetingBehaviour::OnDBSlot0(int a, int b)
	{
		engine::DBChange* change = (engine::DBChange*)b;
		if (change->player == engine::OLS::Get()->currentUser->id)
		{
			toggleToTargetLock = change->intValue != 0;
		}
	}

	// FUNCTION: ENGINE 0x102AA4C0
	bool LockOnTargetingBehaviour::Slot2()
	{
		if (targetLock.target != 0)
		{
			RemoveTargetLockMessage message(&targetLock.target);
			targetLock.target->SendMessage(&message);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x102AA510
	void LockOnTargetingBehaviour::ResetLockState()
	{
		unknown24 = 0;
		unknown99 = false;
		unknown89 = false;
		unknown98 = false;
		unknown88 = false;
	}

	// FUNCTION: ENGINE 0x102ABA40
	void LockOnTargetingBehaviour::ClearTarget()
	{
		ResetLockState();
		AutoTargetingBehaviour::ClearTarget();
		unknownA4 = false;
		unknownA6 = engine::GameObjectHandle();
	}

	// The messages of type 0x20 the lock-on answers itself (RTTI names unknown; only the fields are used)
	struct LockOnByteMessage : public TargetMessage
	{
		bool value;  // +0xC
	};

	struct LockOnWordMessage : public TargetMessage
	{
		unsigned int value;  // +0xC
		float floatValue;  // +0x10
	};

	struct LockOnHandleMessage : public TargetMessage
	{
		engine::GameObjectHandle handle;  // +0xC
	};

	struct LockOnListMessage : public TargetMessage
	{
		AutoTargetPriorityList* list;  // +0xC
	};

	// FUNCTION: ENGINE 0x102AA540
	void LockOnTargetingBehaviour::OnSetFlag16A(engine::Message* message)
	{
		unknown16A = ((LockOnByteMessage*)message)->value;
	}

	// FUNCTION: ENGINE 0x102AA560
	void LockOnTargetingBehaviour::OnGetPreferredCategory(engine::Message* message)
	{
		((LockOnWordMessage*)message)->value = targetLockPreferredTargetCategory;
	}

	// FUNCTION: ENGINE 0x102AA580
	void LockOnTargetingBehaviour::OnGetUnknown15C(engine::Message* message)
	{
		AutoTargetingBehaviour::OnMessage(message);
		((LockOnWordMessage*)message)->floatValue = unknown15C;
	}

	// FUNCTION: ENGINE 0x102AA5B0
	void LockOnTargetingBehaviour::OnSetLockHandle(const engine::GameObjectHandle* handle)
	{
		unknownA6 = *handle;
		SetTarget(handle);
	}

	// FUNCTION: ENGINE 0x102ABB40
	void LockOnTargetingBehaviour::OnSetPriorityList(engine::Message* message)
	{
		AutoTargetPriorityList* list = ((LockOnListMessage*)message)->list;
		if (list != 0)
		{
			core::RefAssign(currentAutoTargetPriorityList, list);
			unknownA4 = true;
			return;
		}
		core::RefAssign(currentAutoTargetPriorityList, defaultAutoTargetPriorityList);
		unknownA4 = false;
	}

	// FUNCTION: ENGINE 0x102AC4A0
	void LockOnTargetingBehaviour::OnMessage(engine::Message* message)
	{
		if (message->type != 0x20)
		{
			AutoTargetingBehaviour::OnMessage(message);
			return;
		}
		switch ((unsigned short)message->id)
		{
		case 8:
			OnSetFlag16A(message);
			break;
		case 9:
			OnGetPreferredCategory(message);
			break;
		case 0:
			OnGetUnknown15C(message);
			break;
		case 11:
			OnSetLockHandle(&((LockOnHandleMessage*)message)->handle);
			break;
		case 10:
			OnSetPriorityList(message);
			break;
		default:
			AutoTargetingBehaviour::OnMessage(message);
			break;
		}
	}

	// FUNCTION: ENGINE 0x102AC550
	void LockOnTargetingBehaviour::SetTarget(const engine::GameObjectHandle* newTarget)
	{
		AutoTargetingBehaviour::SetTarget(newTarget);
		engine::GameObjectHandle handle = target;
		engine::GameObject* object = handle.Get();
		if (targetLock.target != object)
		{
			if (targetLock.target != 0)
			{
				RemoveTargetLockMessage remove(&targetLock.target);
				targetLock.target->SendMessage(&remove);
			}
			if (object != 0)
			{
				AddTargetLockMessage add(&targetLock.target);
				object->SendMessage(&add);
			}
			engine::FightEventMessage event(0x40);
			owner->SendMessage(&event);
		}
	}

	// FUNCTION: ENGINE 0x102B0510
	LockOnTargetingBehaviour::~LockOnTargetingBehaviour()
	{
		core::SafeRelease(vehicleDisguiseAutoTargetPriorityList);
		core::SafeRelease(disguiseAutoTargetPriorityList);
		engine::gGameDatabase->RemoveObserver(gProtoProfileTargetToggleEnabled, static_cast<engine::DBObserver*>(this));
	}

	// FUNCTION: ENGINE 0x102AFB90
	content::MemberList* LockOnTargetingBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<AutoTargetingBehaviour>();
		static content::BaseClassCasterImpl<AutoTargetingBehaviour, LockOnTargetingBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberReferenceMetaType<LockOnTargetingBehaviour, AutoTargetPriorityList, 0>("pn"),
				PROTO_OFFSET(LockOnTargetingBehaviour, disguiseAutoTargetPriorityList), "disguiseAutoTargetPriorityList" },
			{ content::GetMemberReferenceMetaType<LockOnTargetingBehaviour, AutoTargetPriorityList, 1>("pn"),
				PROTO_OFFSET(LockOnTargetingBehaviour, vehicleDisguiseAutoTargetPriorityList),
				"vehicleDisguiseAutoTargetPriorityList" },
			{ content::GetMemberPrimitiveMetaType<LockOnTargetingBehaviour, bool, 0>("pn"),
				PROTO_OFFSET(LockOnTargetingBehaviour, toggleToTargetLock), "toggleToTargetLock" },
			{ content::GetMemberPrimitiveMetaType<LockOnTargetingBehaviour, float, 0>("p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, targetLockMaxDistance), "targetLockMaxDistance" },
			{ content::GetMemberPrimitiveMetaType<LockOnTargetingBehaviour, unsigned int, 0>("p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, targetLockPreferredTargetCategory),
				"targetLockPreferredTargetCategory" },
			{ content::GetMemberPrimitiveMetaType<LockOnTargetingBehaviour, float, 1>("p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, targetLockDisengageOnDeadTime), "targetLockDisengageOnDeadTime" },
			{ content::GetMemberPrimitiveMetaType<LockOnTargetingBehaviour, unsigned int, 1>("p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, targetSwitchTargetCategoryMax), "targetSwitchTargetCategoryMax" },
			{ content::GetMemberPrimitiveMetaType<LockOnTargetingBehaviour, float, 2>("p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, targetSwitchAxisThreshold), "targetSwitchAxisThreshold" },
			{ content::GetMemberPrimitiveMetaType<LockOnTargetingBehaviour, float, 3>("p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, targetSwitchTime), "targetSwitchTime" },
			{ content::GetMemberPrimitiveMetaType<LockOnTargetingBehaviour, float, 4>("p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, targetSwitchHoldTime), "targetSwitchHoldTime" },
			{ content::GetMemberPrimitiveMetaType<LockOnTargetingBehaviour, float, 5>("p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, timeBubbleSimulationRate), "timeBubbleSimulationRate" },
			{ content::GetMemberPrimitiveMetaType<LockOnTargetingBehaviour, float, 6>("p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, timeBubbleFadeInTime), "timeBubbleFadeInTime" },
			{ content::GetMemberPrimitiveMetaType<LockOnTargetingBehaviour, float, 7>("p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, timeBubbleDuration), "timeBubbleDuration" },
			{ content::GetMemberPrimitiveMetaType<LockOnTargetingBehaviour, float, 8>("p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, timeBubbleFadeOutTime), "timeBubbleFadeOutTime" },
			{ content::GetArrayDynamicMetaType<ConeArrayTag0, TargetLockConeArray>(
				content::GetClassMetaType<TargetLockCone>(), "p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, coneArrays[0].cones), "targetLockCones" },
			{ content::GetArrayDynamicMetaType<ConeArrayTag1, TargetLockConeArray>(
				content::GetClassMetaType<TargetLockCone>(), "p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, coneArrays[1].cones), "helicopterTargetLockCones" },
			{ content::GetArrayDynamicMetaType<ConeArrayTag2, TargetLockConeArray>(
				content::GetClassMetaType<TargetLockCone>(), "p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, coneArrays[2].cones), "tankTargetLockCones" },
			{ content::GetArrayDynamicMetaType<ConeArrayTag3, TargetLockConeArray>(
				content::GetClassMetaType<TargetLockCone>(), "p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, coneArrays[3].cones), "targetLockConesKB" },
			{ content::GetArrayDynamicMetaType<ConeArrayTag4, TargetLockConeArray>(
				content::GetClassMetaType<TargetLockCone>(), "p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, coneArrays[4].cones), "helicopterTargetLockConesKB" },
			{ content::GetArrayDynamicMetaType<ConeArrayTag5, TargetLockConeArray>(
				content::GetClassMetaType<TargetLockCone>(), "p"),
				PROTO_OFFSET(LockOnTargetingBehaviour, coneArrays[5].cones), "tankTargetLockConesKB" },
			{ content::GetClassMetaType<SoundParams>(), PROTO_OFFSET(LockOnTargetingBehaviour, soundParams),
				"soundParams" },
			{ content::GetClassMetaType<SoundParams>(), PROTO_OFFSET(LockOnTargetingBehaviour, helicopterSoundParams),
				"helicopterSoundParams" },
			{ content::GetMemberVectorMetaType<LockOnTargetingBehaviour, 0>("pn"), 0x234, "kbOnFootReferencePoint" }
		};
		sList.members = sMembers;
		sList.count = 23;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102B0180
	// NONMATCHING: the engine loads the 0.5 constant before the first byte store of the group (97.2 %)
#ifdef NONMATCHING
	LockOnTargetingBehaviour::LockOnTargetingBehaviour(engine::GameObject* newOwner) : AutoTargetingBehaviour(newOwner),
		disguiseAutoTargetPriorityList(0), vehicleDisguiseAutoTargetPriorityList(0), unknownA4(false), targetLock(),
		toggleToTargetLock(false), unknownB8(0.0f), unknownBC(false), unknownC0(engine::driving::gHalf),
		targetLockMaxDistance(0.0f), targetLockPreferredTargetCategory(0), targetSwitchTargetCategoryMax(0),
		targetSwitchAxisThreshold(0.0f), targetSwitchTime(0.0f), targetSwitchHoldTime(0.0f), unknownDC(0.0f),
		unknownE0(false), timeBubbleSimulationRate(0.0f), timeBubbleFadeInTime(0.0f), timeBubbleDuration(0.0f),
		timeBubbleFadeOutTime(0.0f), unknown154(0), unknown158(false), unknown15C(0.0f),
		targetLockDisengageOnDeadTime(0.0f), unknown164(0.0f), unknown168(false), unknown169(false), unknown16A(true),
		unknown16B(true), currentSoundParams(&soundParams), unknown240(false)
	{
		Listen(0x10, true);
		Listen(0x100, true);
		unknown1A8 = engine::GameObjectHandle();
		unknown28.x = math::kZeroVector.x;
		unknown28.y = math::kZeroVector.y;
		unknown28.z = math::kZeroVector.z;
		unknown34.x = math::kZeroVector.x;
		unknown34.y = math::kZeroVector.y;
		unknown34.z = math::kZeroVector.z;
		unknown40.x = math::kZeroVector.x;
		unknown40.y = math::kZeroVector.y;
		unknown40.z = math::kZeroVector.z;
		unknown4C = 0.0f;
		unknown50 = 0;
		unknown54 = 0;
		unknown58 = 0;
		unknown7C = engine::GameObjectHandle();
		unknown98 = false;
		unknown78 = 0;
		unknown64 = 6;
		unknown60 = 6;
		unknown5C = 6;
		unknown70 = 0.0f;
		unknown6C = 0.0f;
		unknown68 = 0.0f;
		unknown76 = false;
		unknown75 = false;
		unknown74 = false;
		unknown9A = false;
		ResetLockState();
	}
#endif

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
// FUNCTION: ENGINE 0x102ABC50
// FUNCTION: ENGINE 0x102ABC90
// FUNCTION: ENGINE 0x102ABCD0
// FUNCTION: ENGINE 0x102ABD10
// FUNCTION: ENGINE 0x102ABD50
// FUNCTION: ENGINE 0x102ABD90
// FUNCTION: ENGINE 0x102AB330
// FUNCTION: ENGINE 0x102AB400
// FUNCTION: ENGINE 0x102AC2B0
// FUNCTION: ENGINE 0x102AC2D0
// FUNCTION: ENGINE 0x102AC2F0
// FUNCTION: ENGINE 0x102AE7B0
// FUNCTION: ENGINE 0x102AB2B0
// FUNCTION: ENGINE 0x102AB2C0
// FUNCTION: ENGINE 0x102AB2D0
// FUNCTION: ENGINE 0x102AB7E0
// FUNCTION: ENGINE 0x102ABBF0
// FUNCTION: ENGINE 0x102ABDD0
// FUNCTION: ENGINE 0x102ABE10
// FUNCTION: ENGINE 0x102ABE50
// FUNCTION: ENGINE 0x102ABE90
// FUNCTION: ENGINE 0x102ABED0
// FUNCTION: ENGINE 0x102ABF10
// FUNCTION: ENGINE 0x102ABF50
// FUNCTION: ENGINE 0x102ABF90
// FUNCTION: ENGINE 0x102ABFD0
// FUNCTION: ENGINE 0x102AC010
// FUNCTION: ENGINE 0x102AC050
// FUNCTION: ENGINE 0x102AC090
// FUNCTION: ENGINE 0x102AC130
// FUNCTION: ENGINE 0x102AC170
// FUNCTION: ENGINE 0x102AC210
// FUNCTION: ENGINE 0x102AC230
// FUNCTION: ENGINE 0x102AC270
// FUNCTION: ENGINE 0x102AC310
// FUNCTION: ENGINE 0x102AC340
// FUNCTION: ENGINE 0x102AC360
// FUNCTION: ENGINE 0x102AC380
// FUNCTION: ENGINE 0x102AC410
// FUNCTION: ENGINE 0x102AC450
// FUNCTION: ENGINE 0x102AE7A0
// FUNCTION: ENGINE 0x102AE830
// FUNCTION: ENGINE 0x102AE890
// FUNCTION: ENGINE 0x102AE8F0
// FUNCTION: ENGINE 0x102AE950
// FUNCTION: ENGINE 0x102AE9B0
// FUNCTION: ENGINE 0x102AEA10
// FUNCTION: ENGINE 0x102AEA70
// FUNCTION: ENGINE 0x102AEAD0
// FUNCTION: ENGINE 0x102AEC80
// FUNCTION: ENGINE 0x102AFA40
// FUNCTION: ENGINE 0x102AFA70
// FUNCTION: ENGINE 0x102AFAD0
