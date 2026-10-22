// engine::HitReactionBehaviour (RTTI and reflection names; base engine::Behaviour): the base of proto::HitReactionBehaviour.
// A hit message (type 0x14, id 10) makes it damage its owner and push the owner's physics object away from the hit,
// the impulse scaled by the reflected "impulseScale". Messages of type 6 switch the physics object of another object.
// Unit 0x10848820 - 0x10848C70 (no assert path; the directory and file name are guesses). The reflected member name
// is original; the rest is guessed.
#ifndef ENGINE_HITREACTIONBEHAVIOUR_H
#define ENGINE_HITREACTIONBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/healthmessages.h"
#include "code/engine/message.h"
#include "code/math/vector.h"

namespace engine
{
	// A hit on the object (type 0x14, id 10; names guessed): whether to damage the owner, where the hit lands, the
	// damage and the direction it comes from
	struct HitMessage : public IntrusiveMessage
	{
		HitMessage(bool newApplyDamage, const math::Vector* newPosition, float newDamage,
			const math::Vector* newDirection) : IntrusiveMessage(0x14, 10)
		{
			applyDamage = newApplyDamage;
			position = newPosition;
			damage = newDamage;
			direction = newDirection;
		}

		bool applyDamage;
		const math::Vector* position;
		float damage;
		const math::Vector* direction;
	};

	class HitReactionBehaviour : public Behaviour
	{
	public:
		explicit HitReactionBehaviour(GameObject* newOwner);

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x108488A0): does nothing here
		virtual void Slot1();
		// vftable slot 8 (0x10848C20): the hit and the physics object messages
		virtual void HandleMessage(Message* message);

		float impulseScale;  // +0xC

	private:
		void OnHit(HitMessage* message);  // 0x108488B0
		void OnPhysicsFilterOn(PhysicsFilterMessage* message);  // 0x108489F0
		void OnPhysicsFilterSwitch(PhysicsFilterMessage* message);  // 0x10848A50
	};
}

#endif
