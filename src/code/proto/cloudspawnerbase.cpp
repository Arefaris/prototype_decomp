#include "code/proto/cloudspawnerbase.h"

#include "code/content/enummetatype.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/proto/fightitems/motion/motionmessages2.h"
#include <new>

namespace choreo
{
	// 0x10D94FF8 (symbols.txt)
	extern const float gMinusOne;
}

namespace engine
{
	namespace driving
	{
		// 0x10D946E0 (symbols.txt)
		extern const float gOne;
	}
}

namespace content
{
	static const EnumValue sPriorityValues[] =
	{
		{ "Priority_Force_Active", 0 },
		{ "Priority_Force_Active_Far", 1 },
		{ "Priority_Force_Active_Near", 2 },
		{ "Priority_Force_Active_Far_Camera", 3 },
		{ "Priority_Force_Active_Near_Camera", 4 },
		{ "Priority_Force_Active_Camera", 5 },
		{ "Priority_Normal", 6 },
		{ "Priority_Normal_Ignore_Camera", 7 },
		{ "Priority_Low", 8 },
		{ "Priority_Very_Low", 9 },
		{ "Priority_Ultra_Low", 10 }
	};

	static const EnumValue sDecayStateValues[] =
	{
		{ "DecayState_Default", 0 },
		{ "DecayState_Pristine", 1 },
		{ "DecayState_Military", 2 },
		{ "DecayState_Infected", 3 },
		{ "DecayState_Before", 4 },
		{ "DecayState_During", 5 },
		{ "DecayState_After", 6 }
	};

	// FUNCTION: ENGINE 0x104F0590
	template<> void EnumInfo<proto::CloudSpawnerBase::Priority>::Get(const char** name, const EnumValue** values,
		int* count, const char** code)
	{
		*name = "proto::CloudSpawnerBase::Priority";
		*code = "pn";
		*values = sPriorityValues;
		*count = 11;
	}

	// FUNCTION: ENGINE 0x104F05D0
	template<> void EnumInfo<proto::CityManager::DecayState>::Get(const char** name, const EnumValue** values,
		int* count, const char** code)
	{
		*name = "proto::CityManager::DecayState";
		*code = "pn";
		*values = sDecayStateValues;
		*count = 7;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x104F0610
	content::ClassInfo* CloudSpawnerBase::TagWrapper::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CloudSpawnerBase::TagWrapper";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104F0650
	content::ClassInfo* CloudSpawnerBase::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CloudSpawnerBase";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104F0690
	content::ClassInfo* CloudSpawner::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CloudSpawner";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x104F04B0
	CloudSpawnerBase::Priority CloudSpawnerBase::GetPriority() const
	{
		return (Priority)priority;
	}

	// FUNCTION: ENGINE 0x104F04C0
	void CloudSpawnerBase::SetPriority(Priority newPriority)
	{
		priority = newPriority;
		startPriority = priority;
	}

	// FUNCTION: ENGINE 0x104F0510
	CityManager::DecayState CloudSpawnerBase::GetDecayState() const
	{
		return (CityManager::DecayState)decayState;
	}

	// FUNCTION: ENGINE 0x104F0520
	void CloudSpawnerBase::SetDecayState(CityManager::DecayState newState)
	{
		decayState = newState;
	}

	// FUNCTION: ENGINE 0x104E7CD0
	bool CloudSpawnerBase::GetSpawnActive() const
	{
		return spawnActive;
	}

	// FUNCTION: ENGINE 0x104F04F0
	void CloudSpawnerBase::SetSpawnActive(bool active)
	{
		spawnActive = active;
	}

	// FUNCTION: ENGINE 0x104F06D0
	bool CloudSpawnerBase::Slot5()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x104F0A30
	content::MemberList* CloudSpawnerBase::TagWrapper::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<TagWrapper>(true, true, "pn"), PROTO_NAME_OFFSET(TagWrapper, name), "tag" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104F2610
	content::MemberList* CloudSpawnerBase::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::PropSpawner>();
		static content::BaseClassCasterImpl<engine::PropSpawner, CloudSpawnerBase> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberEnumMetaType(&CloudSpawnerBase::GetPriority, &CloudSpawnerBase::SetPriority), 0,
				"priority" },
			{ content::GetArrayDynamicMetaType<CloudSpawnerBase, TagArray>(content::GetClassMetaType<TagWrapper>(),
				"pn"), PROTO_OFFSET(CloudSpawnerBase, tags), "tags" },
			{ content::GetMemberEnumMetaType(&CloudSpawnerBase::GetDecayState, &CloudSpawnerBase::SetDecayState), 0,
				"decayState" },
			{ content::GetMemberMetaType(&CloudSpawnerBase::GetSpawnActive, &CloudSpawnerBase::SetSpawnActive, "p"), 0,
				"spawnActive" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104F2A60
	content::MemberList* CloudSpawner::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<CloudSpawnerBase>();
		static content::BaseClassCasterImpl<CloudSpawnerBase, CloudSpawner> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x104F3310
	// NONMATCHING: the engine loads both pooled floats before the vftable store and keeps the stores in another order (78.0 %)
#ifdef NONMATCHING
	CloudSpawnerBase::CloudSpawnerBase()
	{
		float one = engine::driving::gOne;
		float minusOne = choreo::gMinusOne;
		unknownB4 = 0;
		unknownAC = one;
		decayState = 0;
		visible = 0;
		pending = 1;
		sentFade = minusOne;
		unknownA4 = 0.0f;
		unknownA8 = 0.0f;
		parts = 0;
		unknownBB0 = 0;
		fade = one;
		priority = PRIORITY_NORMAL;
		unknownB0 = 5.0f;
		unknownB8 = 0xff;
		spawnActive = 1;
		startPriority = PRIORITY_NORMAL;
		unknownBB5 = 0;
		unknownBB6 = 0;
	}
#endif

	// FUNCTION: ENGINE 0x104F06E0
	float CloudSpawnerBase::GetHealth() const
	{
		if (parts & PART_HEALTH)
		{
			return health.value;
		}
		return choreo::gMinusOne;
	}

	// FUNCTION: ENGINE 0x104F0700
	void CloudSpawnerBase::SetHealth(float newHealth)
	{
		parts |= PART_HEALTH;
		health.value = newHealth;
	}

	// FUNCTION: ENGINE 0x104F0B50
	bool CloudSpawnerBase::HasTag(const core::Name<core::CaseSensitiveKey>& tag) const
	{
		const TagWrapper* current = tags.begin;
		const TagWrapper* last = tags.end;
		while (current != last)
		{
			if (current->name == tag)
			{
				return true;
			}
			current++;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x104F0BA0
	const core::Name<core::CaseSensitiveKey>* CloudSpawnerBase::FindOtherTag(
		const core::Name<core::CaseSensitiveKey>& tag) const
	{
		const TagWrapper* current = tags.begin;
		const TagWrapper* last = tags.end;
		while (current != last)
		{
			if (!(current->name == tag))
			{
				return &current->name;
			}
			current++;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x104F1AA0
	void CloudSpawnerBase::SetBroadcastStateChanges(bool broadcast)
	{
		engine::GameObject* object = spawned.Get();
		if (object != 0)
		{
			engine::SetBroadcastStateChangesMessage message(broadcast);
			object->SendMessage(&message);
			return;
		}
		trees.broadcast = broadcast;
	}

	// FUNCTION: ENGINE 0x104F1B30
	bool CloudSpawnerBase::FadeIn(float amount, bool force, float rate)
	{
		engine::GameObject* object = spawned.Get();
		if (object != 0)
		{
			float value;
			if (hysteresis == 0 && !force && startPriority != 0)
			{
				value = amount * rate + fade;
				float limit = engine::driving::gOne;
				fade = value;
				if (!(limit > value))
				{
					value = limit;
				}
			}
			else
			{
				value = engine::driving::gOne;
			}
			fade = value;
			if (value != sentFade)
			{
				engine::SetCloudFade message(value);
				spawned.Get()->SendMessage(&message);
				sentFade = fade;
			}
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x104F2790
	bool CloudSpawnerBase::FadeOut(float amount, bool force, float rate)
	{
		engine::GameObject* object = spawned.Get();
		if (object != 0)
		{
			float value = fade - amount * rate;
			fade = value;
			if (force || amount <= 0.0f)
			{
				value = 0.0f;
			}
			fade = value;
			if (value < 0.0f)
			{
				value = 0.0f;
			}
			fade = value;
			if (value != sentFade)
			{
				engine::SetCloudFade message(value);
				spawned.Get()->SendMessage(&message);
				sentFade = fade;
			}
			if (!force && !(0.0f >= fade))
			{
				return true;
			}
			SaveState();
			pending = 1;
			PropSpawner::IsReady();
		}
		return false;
	}

	// FUNCTION: ENGINE 0x104F1C90
	void CloudSpawnerBase::SaveState()
	{
		engine::GameObject* object = spawned.Get();
		if (object != 0)
		{
			SetTransform(object->transform->value);
			engine::PlaybackTreePackStateMessage treeMessage(&trees.names);
			object->SendMessage(&treeMessage);
			engine::HealthPackStateMessage healthMessage(&health.value);
			object->PostMessage(&healthMessage);
			engine::GenericBytePackStateMessage byteMessage(&unknownB8);
			unknownB8 = 0;
			object->PostMessage(&byteMessage);
			parts = PART_TREE_NAMES | PART_HEALTH | PART_GENERIC_BYTE;
		}
	}

	// FUNCTION: ENGINE 0x104F2AE0
	// NONMATCHING: the handle given to SetReservedHandle and the table index of the first lookup take other registers (all other instructions equal, 36.7 %)
#ifdef NONMATCHING
	bool CloudSpawnerBase::Slot15(bool force)
	{
		if (pending && !unknownBB6)
		{
			if (!spawned.Exists())
			{
				if (engine::IsReservedHandle(spawned))
				{
					engine::SetReservedHandle(spawned);
				}
				PropSpawner::Slot3(unknownB4);
				engine::ClearReservedHandle();
			}
			pending = 0;
			engine::GameObject* object = spawned.Get();
			if (object != 0)
			{
				object->SetTransform(transform);
				if (parts & PART_TREE_NAMES)
				{
					engine::PlaybackTreeUnPackStateMessage treeMessage(&trees.names);
					object->SendMessage(&treeMessage);
					engine::PropLogicTreeClearMessage clearMessage;
					object->SendMessage(&clearMessage);
				}
				if (parts & PART_HEALTH)
				{
					engine::HealthUnPackStateMessage healthMessage(&health.value);
					object->SendMessage(&healthMessage);
				}
				if (parts & PART_GENERIC_BYTE)
				{
					engine::GenericByteUnPackStateMessage byteMessage(unknownB8);
					object->SendMessage(&byteMessage);
				}
				trees.names.Reset();
			}
			else
			{
				pending = 1;
			}
		}
		if (spawned.Get() != 0)
		{
			float value;
			if (hysteresis == 0 && !force && startPriority != 0)
			{
				value = 0.0f;
			}
			else
			{
				value = engine::driving::gOne;
			}
			fade = value;
			engine::SetCloudFade message(value);
			spawned.Get()->SendMessage(&message);
			sentFade = fade;
			return true;
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x104F2DC0
	void CloudSpawnerBase::Unpack(const CloudSpawnState* state)
	{
		parts = state->parts;
		startPriority = state->startPriority;
		pending = state->pending;
		SetTransform(*(const math::Matrix*)&state->transform);
		if (parts & PART_TREE_NAMES)
		{
			trees = state->trees;
		}
		if (parts & PART_HEALTH)
		{
			health = state->health;
		}
		if (parts & PART_GENERIC_BYTE)
		{
			unknownB8 = state->genericByte;
		}
	}

	// FUNCTION: ENGINE 0x104F2F50
	CloudSpawnerBase::~CloudSpawnerBase()
	{
	}
}

// The default element of the tag array, kept as the engine kept it
template proto::CloudSpawnerBase::TagWrapper& content::ArrayDynamicHelper<proto::CloudSpawnerBase::TagArray>::Default();

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104F03D0
// FUNCTION: ENGINE 0x104F0790
// FUNCTION: ENGINE 0x104F0850
// FUNCTION: ENGINE 0x104F0860
// FUNCTION: ENGINE 0x104F0870
// FUNCTION: ENGINE 0x104F08B0
// FUNCTION: ENGINE 0x104F08C0
// FUNCTION: ENGINE 0x104F08D0
// FUNCTION: ENGINE 0x104F08E0
// FUNCTION: ENGINE 0x104F0AD0
// FUNCTION: ENGINE 0x104F0AE0
// FUNCTION: ENGINE 0x104F0B10
// FUNCTION: ENGINE 0x104F0B20
// FUNCTION: ENGINE 0x104F16E0
// FUNCTION: ENGINE 0x104F1740
// FUNCTION: ENGINE 0x104F1750
// FUNCTION: ENGINE 0x104F17B0
// FUNCTION: ENGINE 0x104F17C0
// FUNCTION: ENGINE 0x104F17F0
// FUNCTION: ENGINE 0x104F1810
// FUNCTION: ENGINE 0x104F1830
// FUNCTION: ENGINE 0x104F1840
// FUNCTION: ENGINE 0x104F1860
// FUNCTION: ENGINE 0x104F1880
// FUNCTION: ENGINE 0x104F18A0
// FUNCTION: ENGINE 0x104F18C0
// FUNCTION: ENGINE 0x104F18E0
// FUNCTION: ENGINE 0x104F1900
// FUNCTION: ENGINE 0x104F1920
// FUNCTION: ENGINE 0x104F1940
// FUNCTION: ENGINE 0x104F1960
// FUNCTION: ENGINE 0x104F1980
// FUNCTION: ENGINE 0x104F19A0
// FUNCTION: ENGINE 0x104F19C0
// FUNCTION: ENGINE 0x104F19E0
// FUNCTION: ENGINE 0x104F19F0
// FUNCTION: ENGINE 0x104F1A10
// FUNCTION: ENGINE 0x104F22A0
// FUNCTION: ENGINE 0x104F2360
// FUNCTION: ENGINE 0x104F23C0
// FUNCTION: ENGINE 0x104F2480
// FUNCTION: ENGINE 0x104F2510
// FUNCTION: ENGINE 0x104F25C0
// FUNCTION: ENGINE 0x104F2920
// FUNCTION: ENGINE 0x104F2950
// FUNCTION: ENGINE 0x104F2EA0
// FUNCTION: ENGINE 0x104F2EC0
// FUNCTION: ENGINE 0x104F2F10
// FUNCTION: ENGINE 0x104F3260
// FUNCTION: ENGINE 0x104F33F0
// FUNCTION: ENGINE 0x104F2540
// FUNCTION: ENGINE 0x104E4420
// FUNCTION: ENGINE 0x104F0350
// FUNCTION: ENGINE 0x104F0960
// FUNCTION: ENGINE 0x104E7EF0
// FUNCTION: ENGINE 0x104ED9D0
// FUNCTION: ENGINE 0x104F0300
// FUNCTION: ENGINE 0x104F0340
// FUNCTION: ENGINE 0x104F0380
// FUNCTION: ENGINE 0x104F0900
// FUNCTION: ENGINE 0x104FF600
