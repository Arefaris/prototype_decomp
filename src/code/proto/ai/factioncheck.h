// proto::ai::FactionCheck (RTTI names, structs): tests a faction against a condition, one vftable slot. The kinds test
// for the military, the human military and the infected, for the allies and the enemies of a faction and for the
// faction itself. Unit 0x103B9F20 - 0x103BD410 (no assert path; the file name is a guess); the constructors are in
// another unit (0x1020A1D0 - 0x1020A340).
#ifndef PROTO_AI_FACTIONCHECK_H
#define PROTO_AI_FACTIONCHECK_H

#include "code/core/name.h"
#include "code/proto/faction.h"

namespace proto
{
	namespace ai
	{
		struct FactionCheck
		{
			virtual bool Check(const Faction* faction) = 0;
		};

		struct FactionCheck_Military : public FactionCheck
		{
			// 0x103B9F20
			virtual bool Check(const Faction* faction);
		};

		struct FactionCheck_HumanMilitary : public FactionCheck
		{
			// 0x103B9F30
			virtual bool Check(const Faction* faction);
		};

		struct FactionCheck_Infected : public FactionCheck
		{
			// 0x103B9F40
			virtual bool Check(const Faction* faction);
		};

		struct FactionCheck_Ally : public FactionCheck
		{
			// 0x103B9F50
			virtual bool Check(const Faction* faction);

			unsigned char unknown4[4];
			Faction other;  // +8
		};

		struct FactionCheck_Enemy : public FactionCheck
		{
			// 0x103B9F70
			virtual bool Check(const Faction* faction);

			unsigned char unknown4[4];
			Faction other;  // +8
		};

		struct FactionCheck_ExactFaction : public FactionCheck
		{
			// 0x103BD410
			virtual bool Check(const Faction* faction);

			unsigned char unknown4[4];
			core::Name<core::CaseSensitiveKey> name;  // +8
		};
	}
}

#endif
