// proto::TankIntentionBehaviour (RTTI and reflection names; base engine::Behaviour): the intention of a tank. It
// reflects no members. Unit 0x10077400 - 0x10078480 (no assert path; the file name is a guess). Only the reflection is
// reconstructed.
#ifndef PROTO_TANKINTENTIONBEHAVIOUR_H
#define PROTO_TANKINTENTIONBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"
#include "code/math/vector.h"

namespace proto
{
	class TankIntentionBehaviour : public engine::Behaviour
	{
	public:
		// 0x100778C0
		explicit TankIntentionBehaviour(engine::GameObject* newOwner);
		// 0x10077AD0
		virtual ~TankIntentionBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x10077B80), 3 (0x10077A80), 4 (0x10077E50) and 6 (0x10077BA0)
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		bool unknownC;
		math::Vector unknown10;
		bool unknown1C;
		math::Vector unknown20;
		bool unknown2C;
		unsigned char unknown2D[3];
		engine::BaseAttribute* physicsObjectAttribute;  // +0x30
		bool unknown34;
	};

}

#endif
