// proto::ScaryMonsterBehaviour (RTTI and reflection names; base engine::Behaviour): how frightening an object is to
// the people around it (the intensity), which a message can change for a while. Unit 0x103F7F80 - 0x103F82E0 (no
// assert path; the file name is a guess). The reflected name is original, the rest is guessed; the update that
// pushes the object with its own velocity is left to the engine.
#ifndef PROTO_BEHAVIOURS_SCARYMONSTERBEHAVIOUR_H
#define PROTO_BEHAVIOURS_SCARYMONSTERBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"

namespace proto
{
	// Movement messages (type 0x26) the behaviour answers (names guessed): id 0x40 turns it on or off, id 0x41 sets the
	// intensity and the second value for the frame skip in byte 0x14
	struct ScaryMonsterActiveMessage : public engine::Message
	{
		bool active;  // +0xC
	};

	struct ScaryMonsterParamsMessage : public engine::Message
	{
		float intensity;  // +0xC
		float unknown10;
		unsigned char frameSkip;  // +0x14
	};

	class ScaryMonsterBehaviour : public engine::Behaviour
	{
	public:
		// 0x103F7FC0
		explicit ScaryMonsterBehaviour(engine::GameObject* newOwner);
		// 0x103F8010 (deleting destructor 0x103F80E0)
		virtual ~ScaryMonsterBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x103F8020), 4 (0x103F8110, left to the engine) and 6 (0x103F8040)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		float intensity;  // +0xC
		float unknown10;
	};
}

#endif
