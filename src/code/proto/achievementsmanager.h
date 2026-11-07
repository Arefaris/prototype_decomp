// proto::AchievementsManager (RTTI and reflection names; a content library object): the achievements of the game, each
// a name and the statistics ("requisites", each a statistic's name and the goal it has to reach) that award it when
// they are all met. It registers the `ach_` script natives and is kept in a global (0x112753A8) while it is loaded.
// Unit 0x10593940 - 0x10596000 (no assert path; the file name is a guess). The reflected names are original, the rest
// is guessed.
#ifndef PROTO_ACHIEVEMENTSMANAGER_H
#define PROTO_ACHIEVEMENTSMANAGER_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/proto/arraypad.h"

namespace proto
{
	class AchievementsManager : public content::MetaLoadObject
	{
	public:
		// What an achievement waits for: a statistic and its goal (negative: the statistic may not be above its
		// absolute value)
		struct __declspec(align(8)) Requisite
		{
			Requisite()
			{
			}
			// 0x10593A30: whether the statistic has reached the goal
			bool IsSatisfied();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			core::Name<core::CaseSensitiveKey> stat;  // +0
			int goal;  // +8
		};

		typedef container::ArrayDynamic<Requisite, container::AllocatorNew> RequisiteArray;

		struct __declspec(align(8)) Achievement
		{
			// 0x10595450
			Achievement();
			// 0x10593A70: tells the online services about the achievement, once
			void Award();
			// 0x10593E20: awards the achievement when all its requisites are met
			bool Update();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			core::Name<core::CaseSensitiveKey> name;  // +0
			int id;  // +8: the index in the manager's list
			bool awarded;  // +0xC
			RequisiteArray requisites;  // +0x10
			ElementArrayPad unknown1C;
		};

		typedef container::ArrayDynamic<Achievement, container::AllocatorNew> AchievementArray;

		// 0x10595AF0 / 0x10595B20 (the deleting destructor is 0x10595C40)
		AchievementsManager();
		virtual ~AchievementsManager();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x105953F0): takes the global, registers the natives and numbers the achievements
		virtual void Slot3(int unused);
		// vftable slot 4 (0x10593D50): takes the natives back
		virtual bool IsReady();

		// 0x105950D0: registers the `ach_` natives
		void RegisterNatives();
		// 0x10593A00: takes them back
		void UnregisterNatives();
		// ach_Reset (0x10593DE0): takes every award back (the online services keep theirs)
		void Reset();
		// ach_SetAchievement (0x105944A0): awards the achievement with the name
		void SetAchievementByText(const char* name);
		// 0x10593D70
		void SetAchievement(const core::Name<core::CaseSensitiveKey>& name);
		// ach_UpdateAllAchievements (0x105945A0)
		void UpdateAllAchievements();
		// 0x10594600: re-checks the achievements that wait for a statistic
		void UpdateForStat(const core::Name<core::CaseSensitiveKey>& stat);
		// ach_DisableUpdates (0x10593A20)
		void DisableUpdates(bool disabled);

		AchievementArray achievements;  // +8
		ElementArrayPad unknown14;
		bool updatesDisabled;  // +0x18
	};

	// The loaded manager (0x112753A8)
	extern AchievementsManager* gAchievementsManager;
}

namespace container
{
	template<> struct ArrayEraseInline<proto::AchievementsManager::Requisite>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::AchievementsManager::Achievement>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	// The engine's insertion of a default achievement makes room with the count version of Insert
	template<> class ArrayDynamicHelper<proto::AchievementsManager::AchievementArray> : public ArrayDynamicHelperBase
	{
	public:
		typedef proto::AchievementsManager::AchievementArray A;
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
		virtual void Insert(void* array, int index, int unused)
		{
			A* a = (A*)array;
			if (a->Size() >= a->Capacity())
			{
				a->Reserve(a->Size() + 1);
			}
			T* position = a->begin + index;
			static T sDefault;
			a->Insert(position, 1, sDefault);
		}
		virtual void Erase(void* array, int index, int unused)
		{
			A* a = (A*)array;
			a->Erase(a->begin + index);
		}
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
