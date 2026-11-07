// proto::StatsManager (RTTI and reflection names; a content library object that also observes the game database): the
// statistics the game keeps for the player and shows on the statistics screens. A statistic definition is a screen's
// section (a description and its primitive statistics), a primitive statistic is a game database entry (a name, how
// it is shown, how many values it has, an optional maximum and the texts of an indexed string statistic). It registers
// the `stats_` script natives, is kept in a global (0x11275618) while it is loaded, and tells the achievements when a
// statistic changed. Unit 0x10595C70 - 0x1059AAA0 (no assert path; the file name is a guess). The reflected names are
// original, the rest is guessed.
#ifndef PROTO_STATSMANAGER_H
#define PROTO_STATSMANAGER_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/dbobserver.h"
#include "code/proto/arraypad.h"

namespace proto
{
	// The names of the two statistics the manager updates itself (smarthint/smarthintmanager.cpp)
	extern core::Name<core::CaseSensitiveKey> gStatTimePlayed;
	extern core::Name<core::CaseSensitiveKey> gStatCurrentEvolutionPoints;

	class StatsManager : public content::MetaLoadObject, public engine::DBObserver
	{
	public:
		// How a primitive statistic is shown (reflected as StatVisualizationType)
		enum VisualizationType
		{
			VISUALIZATION_NONE = 0,
			VISUALIZATION_NUMBER = 1,
			VISUALIZATION_PERCENTAGE = 2,
			VISUALIZATION_VALUE_AND_MAX = 3,
			VISUALIZATION_INDEXED_STRING = 4,
			VISUALIZATION_ARRAY_MODE = 5,
			VISUALIZATION_TIME = 6,
			VISUALIZATION_COUNT = 7
		};

		// One text of an indexed string statistic (0x20 bytes)
		struct StringEntry
		{
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			char entry[32];
		};

		typedef container::ArrayDynamic<StringEntry, container::AllocatorNew> StringArray;

		// One game database entry (0x48 bytes)
		struct __declspec(align(8)) PrimitiveStat
		{
			// 0x10598E90
			PrimitiveStat();
			// 0x10596290: the value shown (the entry's value, counted, or scaled by the maximum)
			int GetValue();
			// 0x105963B0: the text of an indexed string statistic for the current value
			const char* GetStringValue();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			core::Name<core::CaseSensitiveKey> stat;  // +0: the game database entry
			int type;  // +8: VisualizationType
			int numEntries;  // +0xC
			char description[32];  // +0x10
			int max;  // +0x30
			StringArray strings;  // +0x34
			ElementArrayPad unknown40;
		};

		typedef container::ArrayDynamic<PrimitiveStat, container::AllocatorNew> PrimitiveStatArray;

		// A section of the statistics screens (0x30 bytes)
		struct StatDefinition
		{
			// 0x1059A150
			StatDefinition();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			char description[32];  // +0
			PrimitiveStatArray stats;  // +0x20
			ElementArrayPad unknown2C;
		};

		typedef container::ArrayDynamic<StatDefinition, container::AllocatorNew> StatDefinitionArray;

		// 0x1059A8F0 / 0x1059A930 (the deleting destructor is 0x1059AA70)
		StatsManager();
		virtual ~StatsManager();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x105996F0): takes the global, registers the natives and the database entries
		virtual void Slot3(int unused);
		// vftable slot 4 (0x10596420): takes the natives back
		virtual bool IsReady();
		// DBObserver slot 0 (0x10597D50, this adjusted by the thunk 0x10001735)
		virtual void OnDBSlot0(int a, int b);

		// 0x10598FA0 / 0x10595DC0: the `stats_` natives and the enumeration
		void RegisterNatives();
		void UnregisterNatives();
		// stats_Reset (0x10596440): sets every entry to zero
		void Reset();
		// stats_SetStat (0x10598790) / stats_AddStat (0x105987D0) / stats_SetArrayStat (0x10598810), with the statistic
		// named as text
		void SetStatByText(const char* name, int value);
		void AddStatByText(const char* name, int delta);
		void SetArrayStatByText(const char* name, int index, int value);
		void SetStat(const core::Name<core::CaseSensitiveKey>& name, int value);
		void AddStat(const core::Name<core::CaseSensitiveKey>& name, int delta);
		void SetArrayStat(const core::Name<core::CaseSensitiveKey>& name, int index, int value);
		// 0x10597CA0 / 0x10597CD0: the value of the statistic with the name, -1 without one
		int GetValue(const core::Name<core::CaseSensitiveKey>* name);
		int GetValueByText(const char* name);
		// 0x105968B0: the primitive statistic with the name
		PrimitiveStat* FindStat(const core::Name<core::CaseSensitiveKey>* name);
		// stats_GetNumVisibleStats (0x10596560) and the accessors of the statistics screens
		int GetNumVisibleStats();
		const char* GetVisibleStatDescription(int definition);
		int GetNumPrimitiveStats(int definition);
		int GetPrimitiveStatValue(int definition, int index);
		int GetPrimitiveStatVisualizationType(int definition, int index);
		int GetPrimitiveStatMax(int definition, int index);
		const char* GetPrimitiveStatDescription(int definition, int index);
		const char* GetPrimitiveStatStringValue(int definition, int index);
		int GetPrimitiveStatValueByName(const char* name);
		// 0x10597D10: counts played seconds
		void AddTimePlayed(int a, int amount, int c);
		// stats_SetInGameplay (0x10595C70) / stats_DisableUpdates (0x10595DE0)
		void SetInGameplay(bool inGameplay);
		void DisableUpdates(bool disabled);

		StatDefinitionArray definitions;  // +0xC
		ElementArrayPad unknown18;
		bool inGameplay;  // +0x1C
		bool updatesDisabled;  // +0x1D
	};

	// The loaded manager (0x11275618)
	extern StatsManager* gStatsManager;
}

namespace container
{
	template<> struct ArrayEraseInline<proto::StatsManager::PrimitiveStat>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::StatsManager::StatDefinition>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	// The element access of the primitive statistics: insertion and removal are the engine's code (0x1059A300 / 0x10599D60)
	template<> class ArrayDynamicHelper<proto::StatsManager::PrimitiveStatArray> : public ArrayDynamicHelperBase
	{
	public:
		typedef proto::StatsManager::PrimitiveStatArray A;
		typedef A::Element T;

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void* GetConst(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		// the engine's copies
		virtual void Insert(void* array, int index, int unused);
		virtual void Erase(void* array, int index, int unused);
		virtual int Capacity(void* array)
		{
			return ((A*)array)->Capacity();
		}
		virtual void Expand(void* array, unsigned int count)
		{
			A* a = (A*)array;
			if (a->Capacity() == 0)
			{
				a->Allocate(count);
			}
			else if (count + a->Size() > a->Capacity())
			{
				a->Reserve(count + a->Size());
			}
		}
	};

	// The element access of the sections (0x1059A980 / 0x1059A620)
	template<> class ArrayDynamicHelper<proto::StatsManager::StatDefinitionArray> : public ArrayDynamicHelperBase
	{
	public:
		typedef proto::StatsManager::StatDefinitionArray A;
		typedef A::Element T;

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void* GetConst(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		// the engine's copies
		virtual void Insert(void* array, int index, int unused);
		virtual void Erase(void* array, int index, int unused);
		virtual int Capacity(void* array)
		{
			return ((A*)array)->Capacity();
		}
		virtual void Expand(void* array, unsigned int count)
		{
			A* a = (A*)array;
			if (a->Capacity() == 0)
			{
				a->Allocate(count);
			}
			else if (count + a->Size() > a->Capacity())
			{
				a->Reserve(count + a->Size());
			}
		}
	};
}

#endif
