// proto::BloodtoxBehaviour (RTTI and reflection names; base engine::TriggerBehaviour): a poison cloud. Its trigger
// volume grows from the initial to the final scale in scaleTime, lives for lifeTime and then ends; the poisonYDist
// is the height the poison reaches. Unit 0x103C90C0 - 0x103C9E00 (no assert path; the file name is a guess). The
// reflected names are original, the rest is guessed; the slots that scale the volume and answer the messages are left
// to the engine.
#ifndef PROTO_BEHAVIOURS_BLOODTOXBEHAVIOUR_H
#define PROTO_BEHAVIOURS_BLOODTOXBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/engine/reflectedclasses2.h"
#include "code/math/vector.h"

namespace proto
{
	class BloodtoxBehaviour : public engine::TriggerBehaviour
	{
	public:
		// 0x103C9110, 0x103C91B0 (with a volume) and 0x103C9250 (with a volume and a mode)
		explicit BloodtoxBehaviour(engine::GameObject* newOwner);
		BloodtoxBehaviour(engine::GameObject* newOwner, engine::trigger::Volume* newVolume);
		BloodtoxBehaviour(engine::GameObject* newOwner, engine::trigger::Volume* newVolume, engine::TriggerBehaviour::Target newMode);
		// 0x103C92F0 (deleting destructor 0x103C9470)
		virtual ~BloodtoxBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x103C9940), 4 (0x103C99F0) and 6 (0x103C9CA0)
		virtual void Slot1();
		// vftable slot 3 (0x103C9300): the base's
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		math::Vector initialVolumeScale;  // +0xA4
		math::Vector finalVolumeScale;  // +0xB0
		float scaleTime;  // +0xBC
		float lifeTime;  // +0xC0
		float poisonYDist;  // +0xC4
		math::Vector scaleDisplacement;  // +0xC8
		float unknownD4;
		int unknownD8;
		engine::GameObjectHandle unknownDC;
		bool unknownE0;
	};
}

#endif
