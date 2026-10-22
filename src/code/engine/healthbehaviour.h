// engine::HealthBehaviour (RTTI name; reflected as "HealthBehaviour"; base engine::Behaviour): the health of a game
// object, the base of proto::HealthBehaviour and its relatives. Messages of type 0x14 set and ask for the health, its
// limits and the damage scale, a damage message lowers the health (down to the minimum) unless the object is
// undamageable, and a health that reaches zero marks the object dead. Unit 0x10847E70 - 0x10848820 (no assert path;
// the directory and file name are guesses). The reflected member names are original; the rest is guessed.
#ifndef ENGINE_HEALTHBEHAVIOUR_H
#define ENGINE_HEALTHBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/engine/healthmessages.h"
#include "code/engine/message.h"

namespace engine
{
	class HealthBehaviour : public Behaviour
	{
	public:
		explicit HealthBehaviour(GameObject* newOwner);

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10847FB0): the health becomes the initial one
		virtual void Slot1();
		// vftable slot 5 (0x10848080): the questions about the health
		virtual void OnPostedMessage(Message* message);
		// vftable slot 6 (0x10848410): the commands
		virtual void OnMessage(Message* message);
		// vftable slot 8 (0x10848100): kills the object when the health is used up
		virtual void CheckDeath(Message* cause);
		// vftable slot 9 (0x10848130): does nothing here
		virtual void OnDeath(Message* cause);

		float GetDamageScale() const
		{
			return damageScale;
		}
		void SetDamageScale(float newScale)
		{
			damageScale = newScale;
		}
		bool IsUndamageable() const
		{
			return undamageable > 0;
		}
		// 0x108480D0
		void SetHealth(float newHealth);

		float health;  // +0xC
		float initialHealth;  // +0x10
		float maxHealth;  // +0x14
		float minHealth;  // +0x18
		float damageScale;  // +0x1C
		int undamageable;  // +0x20
		bool dead;  // +0x24

	private:
		void GetHealth(GetHealthMessage* message);  // 0x10847FC0
		void ResetHealth(Message* message);  // 0x10847FE0 (the message is not used)
		void SetMaxHealth(SetMaxHealthMessage* message);  // 0x10848010
		void GetMinHealth(GetMinHealthMessage* message);  // 0x10848020
		void SetMinHealth(SetMinHealthMessage* message);  // 0x10848030
		void GetDamageScale(GetDamageScaleMessage* message);  // 0x10848040
		void SetDamageScale(SetDamageScaleMessage* message);  // 0x10848050
		void SetUndamageable(SetUndamageableMessage* message);  // 0x10848060
		void ApplyDamage(ApplyDamageMessage* message);  // 0x108481C0
		void SetHealthFromMessage(SetHealthMessage* message);  // 0x10848270
		void OnPhysicsFilterOn(PhysicsFilterMessage* message);  // 0x108482D0
		void OnPhysicsFilterSwitch(PhysicsFilterMessage* message);  // 0x10848330
	};
}

#endif
