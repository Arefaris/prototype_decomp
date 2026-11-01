// proto::AdvancedHitReactionBehaviour (RTTI and reflection names; base proto::HitReactionBehaviour): the hit reaction
// with a table of impulse scales and interruptibility flags for each type of attack (the names after the underscore are
// the attack types) and an override for the impulse of the hydra's point hits. Unit 0x102B8550 - 0x102BA9F0 (no assert
// path; the file name is a guess). The reflected names are original, the rest is guessed; only the construction and the
// reflection are reconstructed.
#ifndef PROTO_BEHAVIOURS_ADVANCEDHITREACTIONBEHAVIOUR_H
#define PROTO_BEHAVIOURS_ADVANCEDHITREACTIONBEHAVIOUR_H

#include "code/proto/behaviours/hitreactionbehaviour.h"

namespace proto
{
	class AdvancedHitReactionBehaviour : public HitReactionBehaviour
	{
	public:
		enum
		{
			ATTACK_TYPE_COUNT = 34
		};

		// 0x102BA930
		explicit AdvancedHitReactionBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 6 and 9 - 11 (0x102B8680, 0x102B85A0, 0x102B85C0, 0x102B86B0)
		virtual void OnMessage(engine::Message* message);
		virtual float GetImpulseScale(const void* hit);
		virtual bool IsInterruptible(const void* hit);
		virtual void ApplyImpulse(void* object, void* velocity, void* position, void* hit);

		// The impulse scale of each attack type, in the order of proto::AttackType (impulseScale_None first)
		float impulseScale[ATTACK_TYPE_COUNT];  // +0x18
		int unknownA0;
		// Whether each attack type interrupts the reaction (interruptible_None first)
		bool interruptible[ATTACK_TYPE_COUNT];  // +0xA4
		float hydraImpulsePointScaleOverride;  // +0xC8
	};
}

#endif
