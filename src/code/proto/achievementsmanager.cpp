#include "code/proto/achievementsmanager.h"

#include "code/content/metafactory.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/online/ols.h"
#include "code/engine/online/olsprofile.h"
#include "code/proto/statsmanager.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10593940
	content::ClassInfo* AchievementsManager::Requisite::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AchievementsManager::Requisite";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10593980
	content::ClassInfo* AchievementsManager::Achievement::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AchievementsManager::Achievement";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x105939C0
	content::ClassInfo* AchievementsManager::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::AchievementsManager";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10595450
	AchievementsManager::Achievement::Achievement() : id(0), awarded(false)
	{
	}

	// FUNCTION: ENGINE 0x10593A30
	bool AchievementsManager::Requisite::IsSatisfied()
	{
		int value = gStatsManager->GetValue(&stat);
		if (goal >= 0)
		{
			return value >= goal;
		}
		return value <= -goal;
	}

	// FUNCTION: ENGINE 0x10593A70
	// NONMATCHING: the engine keeps the profile manager in ecx for the call and loads the id behind it, ours keeps it
	// in eax and moves it, 68 %
#ifdef NONMATCHING
	void AchievementsManager::Achievement::Award()
	{
		if (!awarded)
		{
			int profile = engine::OLS::Get()->profile->currentProfile;
			engine::OLS::Get()->profile->Slot11(profile, id);
			awarded = true;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10593E20
	bool AchievementsManager::Achievement::Update()
	{
		for (unsigned int i = 0; i < requisites.Size(); i++)
		{
			if (!requisites[i].IsSatisfied())
			{
				return false;
			}
		}
		Award();
		return true;
	}

	// FUNCTION: ENGINE 0x10593A20
	void AchievementsManager::DisableUpdates(bool disabled)
	{
		updatesDisabled = disabled;
	}

	// FUNCTION: ENGINE 0x10593A00
	void AchievementsManager::UnregisterNatives()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->Unregister(this);
	}

	// FUNCTION: ENGINE 0x10593D50
	bool AchievementsManager::IsReady()
	{
		UnregisterNatives();
		gAchievementsManager = 0;
		return true;
	}

	// FUNCTION: ENGINE 0x10593D70
	void AchievementsManager::SetAchievement(const core::Name<core::CaseSensitiveKey>& name)
	{
		if (!updatesDisabled)
		{
			unsigned int i = 0;
			if (achievements.Size() > 0)
			{
				Achievement* achievement = achievements.begin;
				do
				{
					if (achievement->name == name)
					{
						achievement->Award();
						return;
					}
					i++;
					achievement++;
				}
				while (i < achievements.Size());
			}
		}
	}

	// FUNCTION: ENGINE 0x10593DE0
	void AchievementsManager::Reset()
	{
		for (unsigned int i = 0; i < achievements.Size(); i++)
		{
			achievements[i].awarded = false;
		}
	}

	// FUNCTION: ENGINE 0x105944A0
	void AchievementsManager::SetAchievementByText(const char* name)
	{
		SetAchievement(core::Name<core::CaseSensitiveKey>(name, 1));
	}

	// FUNCTION: ENGINE 0x105945A0
	void AchievementsManager::UpdateAllAchievements()
	{
		if (!updatesDisabled)
		{
			for (unsigned int i = 0; i < achievements.Size(); i++)
			{
				achievements[i].Update();
			}
		}
	}

	// FUNCTION: ENGINE 0x10594600
	void AchievementsManager::UpdateForStat(const core::Name<core::CaseSensitiveKey>& stat)
	{
		for (unsigned int i = 0; i < achievements.Size(); i++)
		{
			Achievement* achievement = &achievements[i];
			unsigned int j = 0;
			if (achievement->requisites.Size() > 0)
			{
				Requisite* requisite = achievement->requisites.begin;
				do
				{
					if (requisite->stat == stat)
					{
						achievement->Update();
						break;
					}
					j++;
					requisite++;
				}
				while (j < achievement->requisites.Size());
			}
		}
	}

	// FUNCTION: ENGINE 0x105944D0
	content::MemberList* AchievementsManager::Requisite::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<Requisite>(true, true, "p"), PROTO_NAME_OFFSET(Requisite, stat), "stat" },
			{ content::GetMemberPrimitiveMetaType<Requisite, int, 0>("p"), PROTO_OFFSET(Requisite, goal), "goal" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10594C50
	content::MemberList* AchievementsManager::Achievement::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<Achievement>(true, true, "p"), PROTO_NAME_OFFSET(Achievement, name), "name" },
			{ content::GetArrayDynamicMetaType<Achievement, RequisiteArray>(
				content::GetClassMetaType<Requisite>(), "p"), PROTO_OFFSET(Achievement, requisites), "requisites" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10595020
	content::MemberList* AchievementsManager::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<AchievementsManager, AchievementArray>(
				content::GetClassMetaType<Achievement>(), "p"), PROTO_OFFSET(AchievementsManager, achievements),
				"achievements" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10595AF0
	AchievementsManager::AchievementsManager()
	{
	}

	// FUNCTION: ENGINE 0x10595B20
	AchievementsManager::~AchievementsManager()
	{
	}

	// FUNCTION: ENGINE 0x105953F0
	void AchievementsManager::Slot3(int unused)
	{
		gAchievementsManager = this;
		RegisterNatives();
		for (unsigned int i = 0; i < achievements.Size(); i++)
		{
			achievements[i].id = i;
		}
		updatesDisabled = false;
	}

	// FUNCTION: ENGINE 0x105950D0
	void AchievementsManager::RegisterNatives()
	{
		engine::LuaScriptManager* manager = engine::GetScriptManager();
		manager->SetOwner(this);
		manager->RegisterMethod("ach_Reset", this, &AchievementsManager::Reset);
		manager->RegisterMethod("ach_SetAchievement", this, &AchievementsManager::SetAchievementByText);
		manager->RegisterMethod("ach_UpdateAllAchievements", this, &AchievementsManager::UpdateAllAchievements);
		manager->RegisterMethod("ach_DisableUpdates", this, &AchievementsManager::DisableUpdates);
		manager->ClearOwner();
	}

	AchievementsManager* gAchievementsManager = 0;
}

namespace content
{
	template ClassMetaType* GetClassMetaType<proto::AchievementsManager::Requisite>();
	template ClassMetaType* GetClassMetaType<proto::AchievementsManager::Achievement>();
	template ClassMetaType* GetClassMetaType<proto::AchievementsManager>();
	template class MetaObjectFactory<proto::AchievementsManager, 1>;
	template void RegisterMetaObjectFactory<proto::AchievementsManager>();
}

namespace container
{
	// The members of the element arrays the unit uses besides the ones its code reaches
	template proto::AchievementsManager::Requisite* ArrayDynamic<proto::AchievementsManager::Requisite, AllocatorNew>::Begin();
	template proto::AchievementsManager::Requisite* ArrayDynamic<proto::AchievementsManager::Requisite, AllocatorNew>::End();
	template void ArrayDynamic<proto::AchievementsManager::Requisite, AllocatorNew>::Free();
	template const proto::AchievementsManager::Requisite& ArrayDynamic<proto::AchievementsManager::Requisite, AllocatorNew>::operator[](int) const;
	template proto::AchievementsManager::Requisite* ArrayDynamic<proto::AchievementsManager::Requisite, AllocatorNew>::Insert(
		proto::AchievementsManager::Requisite*, unsigned int, const proto::AchievementsManager::Requisite&);
	template proto::AchievementsManager::Achievement* ArrayDynamic<proto::AchievementsManager::Achievement, AllocatorNew>::Begin();
	template proto::AchievementsManager::Achievement* ArrayDynamic<proto::AchievementsManager::Achievement, AllocatorNew>::End();
	template bool ArrayDynamic<proto::AchievementsManager::Achievement, AllocatorNew>::Create(unsigned int);
	template void ArrayDynamic<proto::AchievementsManager::Achievement, AllocatorNew>::Free();
	template void ArrayDynamic<proto::AchievementsManager::Achievement, AllocatorNew>::Clear();
	template const proto::AchievementsManager::Achievement& ArrayDynamic<proto::AchievementsManager::Achievement, AllocatorNew>::operator[](int) const;
	template proto::AchievementsManager::Achievement* ArrayDynamic<proto::AchievementsManager::Achievement, AllocatorNew>::Insert(
		proto::AchievementsManager::Achievement*, const proto::AchievementsManager::Achievement&);
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10593AB0
// FUNCTION: ENGINE 0x10593AC0
// FUNCTION: ENGINE 0x10593AD0
// FUNCTION: ENGINE 0x10593AE0
// FUNCTION: ENGINE 0x10593AF0
// FUNCTION: ENGINE 0x10593B50
// FUNCTION: ENGINE 0x10593B60
// FUNCTION: ENGINE 0x10593B70
// FUNCTION: ENGINE 0x10593BE0
// FUNCTION: ENGINE 0x10593BF0
// FUNCTION: ENGINE 0x10593C30
// FUNCTION: ENGINE 0x10593C70
// FUNCTION: ENGINE 0x10593C80
// FUNCTION: ENGINE 0x10593C90
// FUNCTION: ENGINE 0x10593D20
// FUNCTION: ENGINE 0x10593D30
// FUNCTION: ENGINE 0x10593E80
// FUNCTION: ENGINE 0x10593E90
// FUNCTION: ENGINE 0x10593EA0
// FUNCTION: ENGINE 0x10593EE0
// FUNCTION: ENGINE 0x10593EF0
// FUNCTION: ENGINE 0x10593F10
// FUNCTION: ENGINE 0x10593F30
// FUNCTION: ENGINE 0x10593F90
// FUNCTION: ENGINE 0x10593FA0
// FUNCTION: ENGINE 0x10593FB0
// FUNCTION: ENGINE 0x10593FC0
// FUNCTION: ENGINE 0x10593FD0
// FUNCTION: ENGINE 0x10594000
// FUNCTION: ENGINE 0x10594010
// FUNCTION: ENGINE 0x10594030
// FUNCTION: ENGINE 0x10594050
// FUNCTION: ENGINE 0x105940B0
// FUNCTION: ENGINE 0x105940C0
// FUNCTION: ENGINE 0x105940D0
// FUNCTION: ENGINE 0x105940F0
// FUNCTION: ENGINE 0x10594100
// FUNCTION: ENGINE 0x10594120
// FUNCTION: ENGINE 0x10594140
// FUNCTION: ENGINE 0x10594160
// FUNCTION: ENGINE 0x10594350
// FUNCTION: ENGINE 0x10594380
// FUNCTION: ENGINE 0x105943D0
// FUNCTION: ENGINE 0x10594400
// FUNCTION: ENGINE 0x10594450
// FUNCTION: ENGINE 0x105946B0
// FUNCTION: ENGINE 0x10594710
// FUNCTION: ENGINE 0x10594770
// FUNCTION: ENGINE 0x105949E0
// FUNCTION: ENGINE 0x10594A20
// FUNCTION: ENGINE 0x10594A70
// FUNCTION: ENGINE 0x10594AC0
// FUNCTION: ENGINE 0x10594B50
// FUNCTION: ENGINE 0x10594D30
// FUNCTION: ENGINE 0x10594E60
// FUNCTION: ENGINE 0x10594F60
// FUNCTION: ENGINE 0x10594F90
// FUNCTION: ENGINE 0x10594FE0
// FUNCTION: ENGINE 0x105951A0
// FUNCTION: ENGINE 0x105951C0
// FUNCTION: ENGINE 0x10595220
// FUNCTION: ENGINE 0x10595250
// FUNCTION: ENGINE 0x105952A0
// FUNCTION: ENGINE 0x105952F0
// FUNCTION: ENGINE 0x10595310
// FUNCTION: ENGINE 0x10595370
// FUNCTION: ENGINE 0x105953B0
// FUNCTION: ENGINE 0x10595480
// FUNCTION: ENGINE 0x105954E0
// FUNCTION: ENGINE 0x10595590
// FUNCTION: ENGINE 0x105955B0
// FUNCTION: ENGINE 0x105955F0
// FUNCTION: ENGINE 0x105956B0
// FUNCTION: ENGINE 0x105956F0
// FUNCTION: ENGINE 0x10595780
// FUNCTION: ENGINE 0x105957D0
// FUNCTION: ENGINE 0x10595850
// FUNCTION: ENGINE 0x10595870
// FUNCTION: ENGINE 0x105958C0
// FUNCTION: ENGINE 0x105959E0
// FUNCTION: ENGINE 0x10595A30
// FUNCTION: ENGINE 0x10595A60
// FUNCTION: ENGINE 0x10595B70
// FUNCTION: ENGINE 0x10595C20
// FUNCTION: ENGINE 0x10595C40
