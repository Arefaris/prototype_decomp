// proto::HitReactionBehaviour (RTTI and reflection names; base engine::HitReactionBehaviour): how an object reacts to
// being hit. Reflected: applyImpulse and uninterruptible. The base of the advanced hit reaction behaviour. Unit
// 0x102BEAE0 - 0x102BF8B0 (no assert path; the file name is a guess). The reflected names are original, the rest is
// guessed; only the construction and the reflection are reconstructed.
#ifndef PROTO_BEHAVIOURS_HITREACTIONBEHAVIOUR_H
#define PROTO_BEHAVIOURS_HITREACTIONBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/hitreactionbehaviour.h"

namespace proto
{
	class HitReactionBehaviour : public engine::HitReactionBehaviour
	{
	public:
		// 0x102BEBD0
		explicit HitReactionBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 6 (0x102BF810): the hit messages (type 0x14) of the reaction
		virtual void OnMessage(engine::Message* message);
		// vftable slots 9 - 11 (0x102BEB20, 0x102BEB30, 0x102BF110): the impulse scale of a hit, whether it interrupts the
		// reaction and the impulse it applies (names guessed)
		virtual float GetImpulseScale(const void* hit);
		virtual bool IsInterruptible(const void* hit);
		virtual void ApplyImpulse(void* object, void* velocity, void* position, void* hit);

		int uninterruptible;  // +0x10
		bool applyImpulse;  // +0x14
	};
}

#endif
