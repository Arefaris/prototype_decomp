#include "code/proto/statsmanager.h"

#include "code/content/metafactory.h"
#include "code/content/stringmetatype.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/proto/achievementsmanager.h"

namespace proto
{
	// 0x110B2BE0: the name of the script enumeration
	const char* gStatVisualizationTypeName = "StatVisualizationType";
}

namespace content
{
	// 0x110B2BF0
	EnumValue gVisualizationValues[] =
	{
		{ "None", 0 },
		{ "Number", 1 },
		{ "Percentage", 2 },
		{ "ValueAndMax", 3 },
		{ "IndexedString", 4 },
		{ "ArrayMode", 5 },
		{ "Time", 6 },
		{ "Count", 7 }
	};

	// FUNCTION: ENGINE 0x10595CC0
	template<> void EnumInfo<proto::StatsManager::VisualizationType>::Get(const char** name, const EnumValue** values,
		int* count, const char** code)
	{
		*name = "proto::StatsManager::VisualizationType";
		*code = "p";
		*values = gVisualizationValues;
		*count = 8;
	}
}

namespace proto
{
	extern core::Name<core::CaseSensitiveKey> gSmartHintSettingName;
	// 0x10575B30: the game mode (a word behind the answered pointer)
	int* GetGameMode();

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	StatsManager* gStatsManager = 0;

	// FUNCTION: ENGINE 0x10595C80
	content::ClassInfo* StatsManager::StringEntry::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::StatsManager::StringEntry";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10595D00
	content::ClassInfo* StatsManager::PrimitiveStat::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::StatsManager::PrimitiveStat";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10595D40
	content::ClassInfo* StatsManager::StatDefinition::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::StatsManager::StatDefinition";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10595D80
	content::ClassInfo* StatsManager::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::StatsManager";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10598E90
	StatsManager::PrimitiveStat::PrimitiveStat() : type(0), numEntries(0), max(0)
	{
		description[0] = 0;
	}

	// FUNCTION: ENGINE 0x1059A150
	StatsManager::StatDefinition::StatDefinition()
	{
	}

	// FUNCTION: ENGINE 0x10596290
	int StatsManager::PrimitiveStat::GetValue()
	{
		int value = 0;
		if (numEntries <= 1)
		{
			value = engine::gGameDatabase->GetInt(stat, 0, 0);
		}
		else if (type == VISUALIZATION_TIME)
		{
			long long high = engine::gGameDatabase->GetInt(stat, 0, 0);
			long long low = engine::gGameDatabase->GetInt(stat, 0, 1);
			value = (int)((unsigned long long)(high * 0x100000000LL + low) / 1000);
		}
		else
		{
			for (int i = 0; i < numEntries; i++)
			{
				value += (engine::gGameDatabase->GetInt(stat, 0, i) != 0);
			}
		}
		if (max > 0 && value > max)
		{
			value = max;
		}
		if (type == VISUALIZATION_PERCENTAGE)
		{
			return (value * 100) / max;
		}
		if (type == VISUALIZATION_INDEXED_STRING)
		{
			return ((int)strings.Size() * value) / max;
		}
		return value;
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x105963B0
	// NONMATCHING: the engine's clamp of the index takes the first text through a register it does not fold and
	// lays out the non-negative case first, 66 %
#ifdef NONMATCHING
	const char* StatsManager::PrimitiveStat::GetStringValue()
	{
		if (!(strings.Size() > 0))
		{
			return "Error";
		}
		int index = GetValue();
		int last = strings.Size() - 1;
		if (index < 0)
		{
			if (index <= last)
			{
				return strings.begin[0].entry;
			}
		}
		else if (index <= last)
		{
			return strings.begin[index].entry;
		}
		return strings.begin[last].entry;
	}
#endif

	// FUNCTION: ENGINE 0x10596420
	bool StatsManager::IsReady()
	{
		UnregisterNatives();
		gStatsManager = 0;
		return true;
	}

	// FUNCTION: ENGINE 0x10596440
	void StatsManager::Reset()
	{
		for (unsigned int i = 0; i < definitions.Size(); i++)
		{
			StatDefinition* definition = &definitions[i];
			for (unsigned int j = 0; j < definition->stats.Size(); j++)
			{
				PrimitiveStat* stat = &definition->stats[j];
				for (int k = 0; k < stat->numEntries; k++)
				{
					engine::gGameDatabase->SetInt(stat->stat, 0, 0, k);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10596560
	int StatsManager::GetNumVisibleStats()
	{
		return definitions.Size();
	}

	// FUNCTION: ENGINE 0x10596580
	const char* StatsManager::GetVisibleStatDescription(int definition)
	{
		if ((unsigned int)definition >= definitions.Size())
		{
			return "Error";
		}
		return definitions[definition].description;
	}

	// FUNCTION: ENGINE 0x105965D0
	int StatsManager::GetNumPrimitiveStats(int definition)
	{
		if ((unsigned int)definition >= definitions.Size())
		{
			return 0;
		}
		return definitions[definition].stats.Size();
	}

	// FUNCTION: ENGINE 0x10596630
	int StatsManager::GetPrimitiveStatValue(int definition, int index)
	{
		if (definition < definitions.Size() && index < definitions[definition].stats.Size())
		{
			return definitions[definition].stats[index].GetValue();
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x105966B0
	int StatsManager::GetPrimitiveStatVisualizationType(int definition, int index)
	{
		if ((unsigned int)definition < definitions.Size())
		{
			if ((unsigned int)index < definitions[definition].stats.Size())
			{
				return definitions[definition].stats[index].type;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10596730
	int StatsManager::GetPrimitiveStatMax(int definition, int index)
	{
		if ((unsigned int)definition < definitions.Size())
		{
			if ((unsigned int)index < definitions[definition].stats.Size())
			{
				return definitions[definition].stats[index].max;
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x105967B0
	const char* StatsManager::GetPrimitiveStatDescription(int definition, int index)
	{
		if ((unsigned int)definition < definitions.Size())
		{
			if ((unsigned int)index < definitions[definition].stats.Size())
			{
				return definitions[definition].stats[index].description;
			}
		}
		return "Error";
	}

	// FUNCTION: ENGINE 0x10596830
	const char* StatsManager::GetPrimitiveStatStringValue(int definition, int index)
	{
		if (definition < definitions.Size() && index < definitions[definition].stats.Size())
		{
			return definitions[definition].stats[index].GetStringValue();
		}
		return "Error";
	}

	// FUNCTION: ENGINE 0x105968B0
	StatsManager::PrimitiveStat* StatsManager::FindStat(const core::Name<core::CaseSensitiveKey>* name)
	{
		unsigned int i = 0;
		if (definitions.Size() > 0)
		{
			StatDefinition* definition = definitions.begin;
			do
			{
				unsigned int j = 0;
				unsigned int count = definition->stats.Size();
				if (count != 0)
				{
					PrimitiveStat* stat = definition->stats.begin;
					do
					{
						if (stat->stat == *name)
						{
							return stat;
						}
						j++;
						stat++;
					}
					while (j < count);
				}
				i++;
				definition++;
			}
			while (i < definitions.Size());
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10597AB0
	void StatsManager::SetStat(const core::Name<core::CaseSensitiveKey>& name, int value)
	{
		if (!updatesDisabled)
		{
			PrimitiveStat* stat = FindStat(&name);
			if (stat != 0)
			{
				if (stat->type == StatsManager::VISUALIZATION_TIME)
				{
					engine::gGameDatabase->SetInt(stat->stat, 0, 0, 0);
					engine::gGameDatabase->SetInt(stat->stat, 0, value, 1);
				}
				else
				{
					engine::gGameDatabase->SetInt(stat->stat, 0, value, 0);
				}
				gAchievementsManager->UpdateForStat(name);
			}
		}
	}

	// FUNCTION: ENGINE 0x10597B30
	void StatsManager::AddStat(const core::Name<core::CaseSensitiveKey>& name, int delta)
	{
		if (!updatesDisabled)
		{
			PrimitiveStat* stat = FindStat(&name);
			if (stat != 0)
			{
				if (stat->type == StatsManager::VISUALIZATION_TIME)
				{
					long long high = engine::gGameDatabase->GetInt(stat->stat, 0, 0);
					long long low = engine::gGameDatabase->GetInt(stat->stat, 0, 1);
					long long total = high * 0x100000000LL + low;
					total += delta;
					engine::gGameDatabase->SetInt(stat->stat, 0, (int)((unsigned long long)total >> 32), 0);
					engine::gGameDatabase->SetInt(stat->stat, 0, (unsigned int)total, 1);
				}
				else
				{
					int value = engine::gGameDatabase->GetInt(stat->stat, 0, 0);
					value += delta;
					engine::gGameDatabase->SetInt(stat->stat, 0, value, 0);
				}
				gAchievementsManager->UpdateForStat(name);
			}
		}
	}

	// FUNCTION: ENGINE 0x10597C40
	void StatsManager::SetArrayStat(const core::Name<core::CaseSensitiveKey>& name, int index, int value)
	{
		if (!updatesDisabled)
		{
			PrimitiveStat* stat = FindStat(&name);
			if (stat != 0 && index < stat->numEntries)
			{
				engine::gGameDatabase->SetInt(stat->stat, 0, value, index);
				gAchievementsManager->UpdateForStat(name);
			}
		}
	}

	// FUNCTION: ENGINE 0x10597CA0
	int StatsManager::GetValue(const core::Name<core::CaseSensitiveKey>* name)
	{
		PrimitiveStat* stat = FindStat(name);
		if (stat != 0)
		{
			return stat->GetValue();
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x10597CD0
	int StatsManager::GetValueByText(const char* name)
	{
		core::Name<core::CaseSensitiveKey> key(name, 1);
		return GetValue(&key);
	}

	// FUNCTION: ENGINE 0x10597D10
	void StatsManager::AddTimePlayed(int a, int amount, int c)
	{
		if (!updatesDisabled && inGameplay)
		{
			if (*GetGameMode() == 0 && amount > 0)
			{
				AddStat(gStatTimePlayed, amount);
			}
		}
	}

	// FUNCTION: ENGINE 0x10597D50
	void StatsManager::OnDBSlot0(int a, int b)
	{
		SetStat(gStatCurrentEvolutionPoints, *(int*)(b + 8));
	}

	// FUNCTION: ENGINE 0x10598790
	void StatsManager::SetStatByText(const char* name, int value)
	{
		SetStat(core::Name<core::CaseSensitiveKey>(name, 1), value);
	}

	// FUNCTION: ENGINE 0x105987D0
	void StatsManager::AddStatByText(const char* name, int delta)
	{
		AddStat(core::Name<core::CaseSensitiveKey>(name, 1), delta);
	}

	// FUNCTION: ENGINE 0x10598810
	void StatsManager::SetArrayStatByText(const char* name, int index, int value)
	{
		SetArrayStat(core::Name<core::CaseSensitiveKey>(name, 1), index, value);
	}

	// FUNCTION: ENGINE 0x10595C70
	void StatsManager::SetInGameplay(bool newInGameplay)
	{
		inGameplay = newInGameplay;
	}

	// FUNCTION: ENGINE 0x10595DE0
	void StatsManager::DisableUpdates(bool disabled)
	{
		updatesDisabled = disabled;
	}

	// FUNCTION: ENGINE 0x10595DC0
	void StatsManager::UnregisterNatives()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
	}

	// FUNCTION: ENGINE 0x1059A8F0
	StatsManager::StatsManager() : inGameplay(true)
	{
	}

	// FUNCTION: ENGINE 0x1059A930
	StatsManager::~StatsManager()
	{
	}

	// FUNCTION: ENGINE 0x105996F0
	void StatsManager::Slot3(int unused)
	{
		gStatsManager = this;
		RegisterNatives();
		for (unsigned int i = 0; i < definitions.Size(); i++)
		{
			StatDefinition* definition = &definitions[i];
			for (unsigned int j = 0; j < definition->stats.Size(); j++)
			{
				PrimitiveStat* stat = &definition->stats[j];
				if (stat->numEntries <= 0)
				{
					stat->numEntries = 1;
				}
				if (stat->type == VISUALIZATION_TIME)
				{
					stat->numEntries = 2;
				}
				engine::GameDatabase* database = engine::gGameDatabase;
				database->AddIntSubject(stat->stat, 0, 0, engine::DBSubjectInfo(true, stat->numEntries, -1));
			}
		}
		engine::gGameDatabase->AddObserver(gSmartHintSettingName, this, 0, 0);
		updatesDisabled = false;
		Reset();
	}
}

namespace proto
{
	// The meta type of a string member of capacity characters: the engine keeps one function (and static) per member
	template<int Id> content::StringMetaType* GetStatsStringMetaType(int capacity, const char* code)
	{
		static content::StringMetaType sType(capacity, code);
		return &sType;
	}

	// FUNCTION: ENGINE 0x105961F0
	content::MemberList* StatsManager::StringEntry::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ GetStatsStringMetaType<0>(0x20, "p"), content::MemberOffset(&((StringEntry*)0)->entry, 0), "entry" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x105985F0
	content::MemberList* StatsManager::PrimitiveStat::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<PrimitiveStat>(true, true, "p"), PROTO_NAME_OFFSET(PrimitiveStat, stat),
				"name" },
			{ content::GetEnumMetaType<VisualizationType>(), 8, "type" },
			{ content::GetMemberPrimitiveMetaType<PrimitiveStat, int, 0>("p"), PROTO_OFFSET(PrimitiveStat, numEntries),
				"numEntries" },
			{ GetStatsStringMetaType<1>(0x20, "p"), content::MemberOffset(&((PrimitiveStat*)0)->description, 0x10),
				"description" },
			{ content::GetMemberPrimitiveMetaType<PrimitiveStat, int, 1>("p"), PROTO_OFFSET(PrimitiveStat, max),
				"max" },
			{ content::GetArrayDynamicMetaType<PrimitiveStat, StringArray>(
				content::GetClassMetaType<StringEntry>(), "p"), PROTO_OFFSET(PrimitiveStat, strings), "strings" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10598EC0
	content::MemberList* StatsManager::StatDefinition::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ GetStatsStringMetaType<2>(0x20, "p"), content::MemberOffset(&((StatDefinition*)0)->description, 0),
				"description" },
			{ content::GetArrayDynamicMetaType<StatDefinition, PrimitiveStatArray>(
				content::GetClassMetaType<PrimitiveStat>(), "p"), PROTO_OFFSET(StatDefinition, stats), "stats" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10599640
	content::MemberList* StatsManager::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<StatsManager, StatDefinitionArray>(
				content::GetClassMetaType<StatDefinition>(), "p"), PROTO_OFFSET(StatsManager, definitions), "stats" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

namespace content
{
	template ClassMetaType* GetClassMetaType<proto::StatsManager::StringEntry>();
	template ClassMetaType* GetClassMetaType<proto::StatsManager::PrimitiveStat>();
	template ClassMetaType* GetClassMetaType<proto::StatsManager::StatDefinition>();
	template ClassMetaType* GetClassMetaType<proto::StatsManager>();
	template class MetaObjectFactory<proto::StatsManager, 1>;
	template void RegisterMetaObjectFactory<proto::StatsManager>();
}

namespace proto
{
	// FUNCTION: ENGINE 0x10598FA0
	void StatsManager::RegisterNatives()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("stats_Reset", this, &StatsManager::Reset);
		manager->RegisterMethod("stats_SetStat", this, &StatsManager::SetStatByText);
		manager->RegisterMethod("stats_AddStat", this, &StatsManager::AddStatByText);
		manager->RegisterMethod("stats_SetArrayStat", this, &StatsManager::SetArrayStatByText);
		manager->RegisterMethod("stats_GetNumVisibleStats", this, &StatsManager::GetNumVisibleStats);
		manager->RegisterMethod("stats_GetVisibleStatDescription", this, &StatsManager::GetVisibleStatDescription);
		manager->RegisterMethod("stats_GetNumPrimitiveStats", this, &StatsManager::GetNumPrimitiveStats);
		manager->RegisterMethod("stats_GetPrimitiveStatValue", this, &StatsManager::GetPrimitiveStatValue);
		manager->RegisterMethod("stats_GetPrimitiveStatValueByName", this, &StatsManager::GetValueByText);
		manager->RegisterMethod("stats_GetPrimitiveStatVisualizationType", this,
			&StatsManager::GetPrimitiveStatVisualizationType);
		manager->RegisterMethod("stats_GetPrimitiveStatMax", this, &StatsManager::GetPrimitiveStatMax);
		manager->RegisterMethod("stats_GetPrimitiveStatDescription", this, &StatsManager::GetPrimitiveStatDescription);
		manager->RegisterMethod("stats_GetPrimitiveStatStringValue", this, &StatsManager::GetPrimitiveStatStringValue);
		manager->RegisterMethod("stats_SetInGameplay", this, &StatsManager::SetInGameplay);
		manager->RegisterMethod("stats_DisableUpdates", this, &StatsManager::DisableUpdates);
		manager->ClearOwner();
		manager->CreateEnum(gStatVisualizationTypeName);
		manager->AddEnumValue(gStatVisualizationTypeName, "None", 0);
		manager->AddEnumValue(gStatVisualizationTypeName, "Number", 1);
		manager->AddEnumValue(gStatVisualizationTypeName, "Percentage", 2);
		manager->AddEnumValue(gStatVisualizationTypeName, "ValueAndMax", 3);
		manager->AddEnumValue(gStatVisualizationTypeName, "IndexedString", 4);
		manager->AddEnumValue(gStatVisualizationTypeName, "ArrayMode", 5);
		manager->AddEnumValue(gStatVisualizationTypeName, "Time", 6);
		manager->AddEnumValue(gStatVisualizationTypeName, "Count", 7);
	}
}

namespace container
{
	// The members of the element arrays the unit uses besides the ones its code reaches
	typedef proto::StatsManager::StringEntry StringEntry;
	typedef proto::StatsManager::PrimitiveStat PrimitiveStat;
	typedef proto::StatsManager::StatDefinition StatDefinition;
	template bool ArrayDynamic<StringEntry, AllocatorNew>::Create(unsigned int);
	template ArrayDynamic<StringEntry, AllocatorNew>& ArrayDynamic<StringEntry, AllocatorNew>::operator=(
		const ArrayDynamic<StringEntry, AllocatorNew>&);
	template bool ArrayDynamic<PrimitiveStat, AllocatorNew>::Create(unsigned int);
	template PrimitiveStat* ArrayDynamic<PrimitiveStat, AllocatorNew>::Erase(PrimitiveStat*);
	template void ArrayDynamic<PrimitiveStat, AllocatorNew>::ShiftUp(PrimitiveStat*, int);
	template StatDefinition* ArrayDynamic<StatDefinition, AllocatorNew>::Erase(StatDefinition*);
	template void ArrayDynamic<StatDefinition, AllocatorNew>::ShiftUp(StatDefinition*, int);
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10595DF0
// FUNCTION: ENGINE 0x10595E10
// FUNCTION: ENGINE 0x10595E30
// FUNCTION: ENGINE 0x10595E70
// FUNCTION: ENGINE 0x10595E90
// FUNCTION: ENGINE 0x10595ED0
// FUNCTION: ENGINE 0x10595F50
// FUNCTION: ENGINE 0x10595FD0
// FUNCTION: ENGINE 0x10595FE0
// FUNCTION: ENGINE 0x10596020
// FUNCTION: ENGINE 0x10596030
// FUNCTION: ENGINE 0x10596080
// FUNCTION: ENGINE 0x105960C0
// FUNCTION: ENGINE 0x105960D0
// FUNCTION: ENGINE 0x10596110
// FUNCTION: ENGINE 0x10596120
// FUNCTION: ENGINE 0x10596130
// FUNCTION: ENGINE 0x10596990
// FUNCTION: ENGINE 0x105969A0
// FUNCTION: ENGINE 0x10596A00
// FUNCTION: ENGINE 0x10596A40
// FUNCTION: ENGINE 0x10596A90
// FUNCTION: ENGINE 0x10596AA0
// FUNCTION: ENGINE 0x10596B00
// FUNCTION: ENGINE 0x10596B20
// FUNCTION: ENGINE 0x10596B40
// FUNCTION: ENGINE 0x10596BA0
// FUNCTION: ENGINE 0x10596BE0
// FUNCTION: ENGINE 0x10596C00
// FUNCTION: ENGINE 0x10596C80
// FUNCTION: ENGINE 0x10596CA0
// FUNCTION: ENGINE 0x10596CD0
// FUNCTION: ENGINE 0x10596CF0
// FUNCTION: ENGINE 0x10596D10
// FUNCTION: ENGINE 0x10596D40
// FUNCTION: ENGINE 0x10596DD0
// FUNCTION: ENGINE 0x10596E10
// FUNCTION: ENGINE 0x10596E50
// FUNCTION: ENGINE 0x10596E60
// FUNCTION: ENGINE 0x10596E70
// FUNCTION: ENGINE 0x10596EA0
// FUNCTION: ENGINE 0x10596EC0
// FUNCTION: ENGINE 0x10596EE0
// FUNCTION: ENGINE 0x10596F40
// FUNCTION: ENGINE 0x10596FA0
// FUNCTION: ENGINE 0x10596FC0
// FUNCTION: ENGINE 0x10596FE0
// FUNCTION: ENGINE 0x10597010
// FUNCTION: ENGINE 0x105970C0
// FUNCTION: ENGINE 0x10597120
// FUNCTION: ENGINE 0x105978B0
// FUNCTION: ENGINE 0x105978C0
// FUNCTION: ENGINE 0x10597910
// FUNCTION: ENGINE 0x105979A0
// FUNCTION: ENGINE 0x10597D90
// FUNCTION: ENGINE 0x10597DF0
// FUNCTION: ENGINE 0x10597E50
// FUNCTION: ENGINE 0x10597F50
// FUNCTION: ENGINE 0x10598460
// FUNCTION: ENGINE 0x10598580
// FUNCTION: ENGINE 0x10598850
// FUNCTION: ENGINE 0x10598870
// FUNCTION: ENGINE 0x10598CB0
// FUNCTION: ENGINE 0x10598D00
// FUNCTION: ENGINE 0x10598D40
// FUNCTION: ENGINE 0x10598D60
// FUNCTION: ENGINE 0x10598DF0
// FUNCTION: ENGINE 0x10598E50
// FUNCTION: ENGINE 0x10599310
// FUNCTION: ENGINE 0x10599370
// FUNCTION: ENGINE 0x10599440
// FUNCTION: ENGINE 0x10599460
// FUNCTION: ENGINE 0x10599520
// FUNCTION: ENGINE 0x105995B0
// FUNCTION: ENGINE 0x10599880
// FUNCTION: ENGINE 0x105998E0
// FUNCTION: ENGINE 0x10599A10
// FUNCTION: ENGINE 0x10599D00
// FUNCTION: ENGINE 0x10599F30
// FUNCTION: ENGINE 0x10599FB0
// FUNCTION: ENGINE 0x10599FF0
// FUNCTION: ENGINE 0x1059A0A0
// FUNCTION: ENGINE 0x1059A170
// FUNCTION: ENGINE 0x1059A1A0
// FUNCTION: ENGINE 0x1059A1E0
// FUNCTION: ENGINE 0x1059A2B0
// FUNCTION: ENGINE 0x1059A3A0
// FUNCTION: ENGINE 0x1059A3E0
// FUNCTION: ENGINE 0x1059A550
// FUNCTION: ENGINE 0x1059A680
// FUNCTION: ENGINE 0x1059A810
// FUNCTION: ENGINE 0x1059A840
// FUNCTION: ENGINE 0x1059AA50
// FUNCTION: ENGINE 0x1059AA70
