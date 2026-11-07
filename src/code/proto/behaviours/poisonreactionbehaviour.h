// proto::PoisonReactionBehaviour (RTTI and reflection names; base engine::Behaviour): the poison of an object: the list
// of poisons (PoisonInformation: damage rate, spikes, times between hits, the type of attack, and the sources in range
// of which the poison stays active) that the behaviour ticks and answers messages about. Unit 0x102C0B50 - 0x102C2900
// (no assert path; the file name is a guess). The reflected names are original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_POISONREACTIONBEHAVIOUR_H
#define PROTO_BEHAVIOURS_POISONREACTIONBEHAVIOUR_H

#include "code/container/arrayfixed.h"
#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/content/arrayhelpercount.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"

namespace proto
{
	// An object that keeps a poison active while it is within range
	struct PoisonSource
	{
		PoisonSource() : range(0.0f)
		{
		}

		engine::HandleBase handle;  // +0
		float range;  // +4
	};

	// One poison of the behaviour (RTTI none; reflected: damageRate, damageSpikes, timeBetweenHits, poisonType,
	// poisonExpiry, extraRandomTime). 0x40 bytes
	class PoisonInformation
	{
	public:
		// 0x102C0B50
		static content::ClassInfo* GetClassInfo();
		// 0x102C11A0
		static content::MemberList* GetMembers();

		// 0x102C1EE0
		PoisonInformation();
		// 0x102C1F30 (deleting destructor 0x102C1F40)
		~PoisonInformation();

		// 0x102C0BF0: the time to the next hit, randomised
		float GetNextHitTime() const;

		bool active;  // +0
		float damageRate;  // +4
		float damageSpikes;  // +8
		float timeBetweenHits;  // +0xC
		float extraRandomTime;  // +0x10
		float poisonExpiry;  // +0x14
		int poisonType;  // +0x18 (AttackType, BloodtoxPoison by default)
		float hitTimer;  // +0x1C
		float elapsed;  // +0x20
		container::ArrayFixed<PoisonSource, 3> sources;  // +0x24
	};

	class PoisonReactionBehaviour : public engine::Behaviour
	{
	public:
		typedef container::ArrayDynamic<PoisonInformation, container::AllocatorNew> PoisonArray;

		// 0x102C2620
		explicit PoisonReactionBehaviour(engine::GameObject* newOwner);
		// 0x102C2680 (deleting destructor 0x102C2780)
		virtual ~PoisonReactionBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x102C0C70), 4 (0x102C14B0) and 6 (0x102C1800)
		virtual void Slot1()
		{
		}
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x102C1330: the message that clears every poison
		void ClearPoisons(engine::Message* message);

		PoisonArray poisonInformations;  // +0xC
		int unknown18;
	};
}

namespace container
{
	// The engine moves the elements down in Erase with CopyRangeEnd
	template<> struct ArrayEraseInline<proto::PoisonInformation>
	{
		enum
		{
			value = 4
		};
	};
}

namespace content
{
	CONTENT_ARRAY_HELPER_COUNT_INSERT(proto::PoisonReactionBehaviour::PoisonArray);
}

#endif
