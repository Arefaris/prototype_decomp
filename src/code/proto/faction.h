// proto::Faction (RTTI and reflection names, "Faction"): a faction of the game, kept as its name. The reflection
// (0x1047B8D0 / 0x1047B9B0), the constructors and the empty destructor are out of line in another unit (0x1047B8D0 -
// 0x1047BAC0); the copy is the name's.
#ifndef PROTO_FACTION_H
#define PROTO_FACTION_H

#include "code/content/metatype.h"
#include "code/core/name.h"

namespace proto
{
	class Faction
	{
	public:
		// 0x1047BA90
		Faction();
		// 0x1047BAA0
		explicit Faction(core::Name<core::CaseSensitiveKey> newName);
		// 0x1047BAC0 (an empty function)
		~Faction();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x1047BAD0 / 0x1047BAE0 / 0x1047BB80 (another unit): the faction is the infected / one of the military ones /
		// one of the human military ones (name guesses)
		bool IsInfected() const;
		bool IsMilitary() const;
		bool IsHumanMilitary() const;
		// 0x1047B950 (another unit): how the faction stands to another one, 0 when they are enemies, 1 when they are
		// allies (name guess)
		int GetRelationTo(const Faction& other) const;

		core::Name<core::CaseSensitiveKey> name;
	};
}

#endif
