// proto::SensesInfoBehaviour (RTTI and reflection names; base engine::Behaviour): what an object senses of the others
// by its kind (proto::SensesType). Reflected: the kind. Unit 0x10075AC0 - 0x10076370 (no assert path; the file name is
// a guess). The reflected name is original, the rest is guessed; only the reflection is reconstructed.
#ifndef PROTO_BEHAVIOURS_SENSESINFOBEHAVIOUR_H
#define PROTO_BEHAVIOURS_SENSESINFOBEHAVIOUR_H

#include "code/content/enummetatype.h"
#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"

namespace proto
{
	// The kinds of object the senses distinguish (reflected as proto::SensesType)
	enum SensesType
	{
		SENSES_NONE = 0,
		SENSES_PROTOTYPE = 1,
		SENSES_INFECTED0 = 2,
		SENSES_INFECTED1 = 3,
		SENSES_INFECTED2 = 4,
		SENSES_BRAWLER = 5,
		SENSES_STEALTH = 6,
		SENSES_LEADER = 7,
		SENSES_HYDRA = 8,
		SENSES_SOLDIER = 9,
		SENSES_TANK = 10,
		SENSES_HELICOPTER = 11,
		SENSES_UAV = 12,
		SENSES_GENERIC_MILITARY = 13,
		SENSES_HIVE_PROP = 14,
		SENSES_INFECTED_BOSS = 15,
		SENSES_PEDESTRIAN = 16
	};

	class SensesInfoBehaviour : public engine::Behaviour
	{
	public:
		// 0x10075B00
		explicit SensesInfoBehaviour(engine::GameObject* newOwner);
		// 0x10075CE0 (deleting destructor)
		virtual ~SensesInfoBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x10075F70), 3 (0x10075F30), 4 (0x10075FB0) and 6 (0x100760B0)
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		float unknownC;
		float unknown10;
		float unknown14;
		SensesType sensesType;  // +0x18
		bool unknown1C;
		bool unknown1D;
	};
}

#endif
