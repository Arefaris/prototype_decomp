#include "code/proto/fightitems/ai/aimessages.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/math/matrix.h"
#include "code/proto/fightitems/ai/aihelpers.h"
#include "code/proto/faction.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/gameobject.h"

namespace proto
{
	// RTTI: proto::GetTargetPointMessage: the object answers the point on it that is aimed at in a mode, starting from its
	// own position
	class GetTargetPointMessage : public TargetableMessage
	{
	public:
		explicit GetTargetPointMessage(int newMode) : TargetableMessage(0), mode(newMode), point(0.0f, 0.0f, 0.0f), unknown1C(false)
		{
		}
		virtual ~GetTargetPointMessage()
		{
		}

		int mode;  // +0xC
		math::Vector point;  // +0x10
		bool unknown1C;
	};

	engine::GameObject* GetLinkedObject(engine::GameObject* object);  // 0x103C01F0

	// Helpers that ask whether an object counts another one as an enemy (unit 0x103C0040 - 0x103C5D60, no assert path;
	// the file name is a guess)

	engine::GameObject* GetDriverObject(engine::GameObject* object);  // 0x103C0040
	bool IsMilitaryDisguiseNotBlown(engine::GameObject* object);  // 0x103C22A0
	Faction GetObjectFaction(engine::GameObject* object);  // 0x103BE3E0

	// FUNCTION: ENGINE 0x103C03F0
	// NONMATCHING: the engine keeps the checked handle's lookup apart from the target and loads the position in the order x, y, z (43 %)
#ifdef NONMATCHING
	bool GetTargetPoint(math::Vector* result, engine::GameObject* subject, engine::GameObject* target, int mode)
	{
		if (target == 0)
		{
			GetTargetMessage message;
			subject->SendMessage(&message);
			target = message.target.Get();
			if (target == 0)
			{
				return false;
			}
		}
		else
		{
			engine::GameObject* linked = GetLinkedObject(target);
			if (linked != 0)
			{
				target = linked;
			}
		}
		GetTargetPointMessage query(mode);
		math::Matrix& matrix = target->transform->value;
		float x = matrix.m[3][0];
		float y = matrix.m[3][1];
		float z = matrix.m[3][2];
		query.point.x = x;
		query.point.y = y;
		query.point.z = z;
		target->SendMessage(&query);
		result->x = query.point.x;
		result->y = query.point.y;
		result->z = query.point.z;
		return true;
	}
#endif

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
