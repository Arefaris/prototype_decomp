// proto::CollisionSqueezeBehaviour (RTTI and reflection names; base engine::Behaviour): watches the object's physics
// object for being squeezed between others. Nothing is reflected beyond the base class. Unit 0x102F1D80 - 0x102F2360
// (no assert path; the file name is a guess). The constructor and the message handler are reconstructed; Update
// (slot 4) is left to the engine.
#ifndef PROTO_RENDER_COLLISIONSQUEEZEBEHAVIOUR_H
#define PROTO_RENDER_COLLISIONSQUEEZEBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"

namespace proto
{
	class CollisionSqueezeBehaviour : public engine::Behaviour
	{
	public:
		// 0x102F1EE0
		explicit CollisionSqueezeBehaviour(engine::GameObject* newOwner);
		// 0x102F1DC0 (the deleting destructor is 0x102F1E30)
		virtual ~CollisionSqueezeBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 4 (0x102F1F40)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x102F1DD0): a message of type 0x1A clears the flag
		virtual void OnMessage(engine::Message* message);

		engine::BaseAttribute* physicsObjectAttribute;  // +0xC
		bool unknown10;
		int unknown14;
		unsigned char unknown18[12];
	};
}

#endif
