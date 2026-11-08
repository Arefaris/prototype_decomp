#include "code/proto/ai/factioncheck.h"

namespace proto
{
	namespace ai
	{
		// FUNCTION: ENGINE 0x103B9F20
		bool FactionCheck_Military::Check(const Faction* faction)
		{
			return faction->IsMilitary();
		}

		// FUNCTION: ENGINE 0x103B9F30
		bool FactionCheck_HumanMilitary::Check(const Faction* faction)
		{
			return faction->IsHumanMilitary();
		}

		// FUNCTION: ENGINE 0x103B9F40
		bool FactionCheck_Infected::Check(const Faction* faction)
		{
			return faction->IsInfected();
		}

		// FUNCTION: ENGINE 0x103B9F50
		bool FactionCheck_Ally::Check(const Faction* faction)
		{
			if (faction->GetRelation(name) == 1)
			{
				return true;
			}
			return false;
		}

		// FUNCTION: ENGINE 0x103B9F70
		bool FactionCheck_Enemy::Check(const Faction* faction)
		{
			if (faction->GetRelation(name) == 0)
			{
				return true;
			}
			return false;
		}

		// FUNCTION: ENGINE 0x103BD410
		bool FactionCheck_ExactFaction::Check(const Faction* faction)
		{
			return faction->name == name;
		}
	}
}
