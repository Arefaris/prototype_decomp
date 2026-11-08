// proto::NPCRenderBehaviour (RTTI and reflection names; base engine::Behaviour): shows a pedestrian: it keeps the
// instance the drawable of the pedestrian is made of, the type that tells what it looks like ("npcRender") and whether it
// starts out visible ("startVisible"). Unit 0x1047A8D0 - 0x1047B000 (no assert path; the file name is a guess). The
// reflected names are original, the rest is guessed; the reflection, the construction and the destruction are
// reconstructed, the handling of the messages is left to the engine.
#ifndef PROTO_NPCRENDERBEHAVIOUR_H
#define PROTO_NPCRENDERBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/proto/npcinstance.h"
#include "code/proto/npctype.h"

namespace proto
{
	class NPCRenderBehaviour : public engine::Behaviour
	{
	public:
		// 0x1047A910
		explicit NPCRenderBehaviour(engine::GameObject* newOwner);
		// 0x1047AA60 (the deleting destructor is 0x1047AB90)
		virtual ~NPCRenderBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x1047A970): gives the instance the owner, the type and the visibility
		virtual void Slot1();
		// vftable slot 3 (0x1047AAD0)
		virtual void OnActiveChanged(bool active);
		// vftable slot 4 (0x1047AA90)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x1047AF00), left to the engine
		virtual void OnMessage(engine::Message* message);

		// 0x1047A9D0 / 0x1047A9E0 / 0x1047A9F0: the instance's drawable
		void SetRegistered(bool registered);
		void DestroyDrawable();
		void SetDrawableValue(float value);

		NPCInstance instance;  // +0xC
		NPCRender* npcRender;  // +0x30
		bool startVisible;  // +0x34
	};
}

#endif
