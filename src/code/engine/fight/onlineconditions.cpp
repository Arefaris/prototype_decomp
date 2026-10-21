// The fight conditions on the online session: the player's index and the number of players (unit 0x108B0840 and
// 0x108EEFF0 - 0x108EF780; no assert path, file name guessed).
#include "code/engine/fight/onlineconditions.h"
#include "code/engine/fight/fightsystem.h"

namespace engine
{
	extern fight::EnumEntry gCompareOperatorTable[];
	extern const int gCompareOperatorCount;

	// FUNCTION: ENGINE 0x108B0840
	void RegisterOnlineConditionFactories(fight::TrackRegistry* registry)
	{
		RegisterOnlineNumPlayersConditionFactory(registry, "onlineNumPlayers");
		RegisterOnlinePlayerIndexConditionFactory(registry, "onlinePlayerIndex");
	}

	fight::Property** gOnlinePlayerIndexConditionProperties;  // 0x1131B158
	fight::Property** gOnlineNumPlayersConditionProperties;  // 0x1131B15C

	// FUNCTION: ENGINE 0x108EEFF0
	bool OnlinePlayerIndexCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108EF000
	bool OnlinePlayerIndexCondition::SetIndex(int newValue)
	{
		index = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108EF010
	fight::Property* OnlinePlayerIndexCondition::GetProperty(int index)
	{
		return gOnlinePlayerIndexConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108EF020
	void OnlinePlayerIndexCondition::ClearProperties()
	{
		fight::FreePropertyList(&gOnlinePlayerIndexConditionProperties);
	}

	// FUNCTION: ENGINE 0x108EF030
	OnlinePlayerIndexCondition::OnlinePlayerIndexCondition() : fight::Condition(0), compare(0), index(0)
	{
	}

	// FUNCTION: ENGINE 0x108EF060
	OnlinePlayerIndexCondition::~OnlinePlayerIndexCondition()
	{
	}

	// FUNCTION: ENGINE 0x108EF1D0
	// EQUIVALENT: the engine saves esi and edi in the entry block, before the guard's branch; ours sinks the pushes
	// behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void OnlinePlayerIndexCondition::RegisterProperties()
	{
		if (gOnlinePlayerIndexConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnumConstList<OnlinePlayerIndexCondition>("compare", gCompareOperatorTable, gCompareOperatorCount, &OnlinePlayerIndexCondition::SetCompare);
			properties[0] = property;
			property = new fight::PropertyIntConstRange<OnlinePlayerIndexCondition>("index", &OnlinePlayerIndexCondition::SetIndex);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gOnlinePlayerIndexConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108EF1B0
	fight::ConditionFactory* CreateOnlinePlayerIndexConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<OnlinePlayerIndexCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108EF290
	void RegisterOnlinePlayerIndexConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<OnlinePlayerIndexCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<OnlinePlayerIndexCondition>;
	template class fight::PropertyIntConstRange<OnlinePlayerIndexCondition>;
	template class fight::ConditionFactoryTemplate<OnlinePlayerIndexCondition>;
	template class fight::ConditionFactoryCasterTemplate<OnlinePlayerIndexCondition>;

	// FUNCTION: ENGINE 0x108EF350
	bool OnlineNumPlayersCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108EF360
	bool OnlineNumPlayersCondition::SetCount(int newValue)
	{
		count = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108EF370
	fight::Property* OnlineNumPlayersCondition::GetProperty(int index)
	{
		return gOnlineNumPlayersConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108EF380
	void OnlineNumPlayersCondition::ClearProperties()
	{
		fight::FreePropertyList(&gOnlineNumPlayersConditionProperties);
	}

	// FUNCTION: ENGINE 0x108EF390
	OnlineNumPlayersCondition::OnlineNumPlayersCondition() : fight::Condition(0), compare(0), count(0)
	{
	}

	// FUNCTION: ENGINE 0x108EF3C0
	OnlineNumPlayersCondition::~OnlineNumPlayersCondition()
	{
	}

	// FUNCTION: ENGINE 0x108EF530
	// EQUIVALENT: the engine saves esi and edi in the entry block, before the guard's branch; ours sinks the pushes
	// behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void OnlineNumPlayersCondition::RegisterProperties()
	{
		if (gOnlineNumPlayersConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnumConstList<OnlineNumPlayersCondition>("compare", gCompareOperatorTable, gCompareOperatorCount, &OnlineNumPlayersCondition::SetCompare);
			properties[0] = property;
			property = new fight::PropertyIntConstRange<OnlineNumPlayersCondition>("count", &OnlineNumPlayersCondition::SetCount);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gOnlineNumPlayersConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108EF5F0
	void RegisterOnlineNumPlayersConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<OnlineNumPlayersCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<OnlineNumPlayersCondition>;
	template class fight::PropertyIntConstRange<OnlineNumPlayersCondition>;
	template class fight::ConditionFactoryTemplate<OnlineNumPlayersCondition>;
	template class fight::ConditionFactoryCasterTemplate<OnlineNumPlayersCondition>;
}
