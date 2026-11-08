#include "code/proto/fightitems/ai/aimessages.h"
#include "code/proto/fightitems/ai/aihelpers.h"
#include "code/proto/faction.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/gameobject.h"

namespace proto
{
	// Helpers that ask whether an object counts another one as an enemy (unit 0x103C0040 - 0x103C5D60, no assert path;
	// the file name is a guess)

	engine::GameObject* GetDriverObject(engine::GameObject* object);  // 0x103C0040
	bool IsMilitaryDisguiseNotBlown(engine::GameObject* object);  // 0x103C22A0
	Faction GetObjectFaction(engine::GameObject* object);  // 0x103BE3E0

	// FUNCTION: ENGINE 0x103C4720
	// NONMATCHING: the engine keeps the subject in edi and the target in ebx and repeats the tail of the message branch (55 %)
#ifdef NONMATCHING
	bool Unknown103C4720(engine::GameObject* subject, engine::GameObject* target)
	{
		int state = 0;
		if (IsPlayerObject(subject) && !gAISystem->strafeRunTokens->unknown19F4)
		{
			return false;
		}
		engine::GameObject* driver = GetDriverObject(target);
		if (driver != 0)
		{
			target = driver;
		}
		if (IsPlayerObject(subject))
		{
			Faction faction = GetObjectFaction(target);
			if (faction.IsMilitary() && IsMilitaryDisguiseNotBlown(subject))
			{
				GetTargetMessage message;
				subject->SendMessage(&message);
				state = (message.target.Get() == target) + 1;
			}
			return state == 1;
		}
		if (Unknown103B8B80(subject).Get() != target)
		{
			Faction subjectFaction = GetObjectFaction(subject);
			Faction targetFaction = GetObjectFaction(target);
			state = subjectFaction.GetRelationTo(targetFaction) == 1;
		}
		return state == 1;
	}
#endif
}
