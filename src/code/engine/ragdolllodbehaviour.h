// engine::RagdollLODBehaviour (RTTI name; the reflection name is "engine::RagdollLODBehaviour"; base engine::Behaviour): the
// ragdoll a character gets when it is far away ("lowLODRagdollFactory"). Unit 0x10925050 - 0x10927D40 together with
// RagdollBehaviour (which is still described by reflectedclasses.h); no assert path names it, so the file name is a
// guess. The reflected name is original, the other members are guessed.
#ifndef ENGINE_RAGDOLLLODBEHAVIOUR_H
#define ENGINE_RAGDOLLLODBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/ravenphysics/physicsobjectfactory.h"

namespace engine
{
	class RagdollLODBehaviour : public Behaviour
	{
	public:
		// 0x10926350
		explicit RagdollLODBehaviour(GameObject* newOwner);
		// 0x10927080 (deleting destructor 0x10927990); not reconstructed
		virtual ~RagdollLODBehaviour();

		// 0x10925090 / 0x109274D0
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x109270C0), 2 (0x109263A0), 3 (0x10926440) and 6 (0x10927120); not reconstructed
		virtual void Slot1();
		virtual bool Slot2();
		virtual void OnActiveChanged(bool active);
		virtual void OnMessage(Message* message);

		int unknownC;
		int unknown10;
		ravenphysics::PhysicsObjectFactory* lowLODRagdollFactory;  // +0x14
		int unknown18;
		int unknown1C;
	};
}

#endif
