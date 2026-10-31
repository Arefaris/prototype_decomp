// proto::TunnelingBehaviour (RTTI and reflection names; base engine::Behaviour): moves its object under the ground and
// back. Reflected: the depth under the ground and the offset over it. Unit 0x10078A70 - 0x1007A210 (no assert path; the
// file name is a guess). The reflected names are original, the rest is guessed; only the reflection is reconstructed.
#ifndef PROTO_TUNNELINGBEHAVIOUR_H
#define PROTO_TUNNELINGBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"
#include "code/math/vector.h"

namespace proto
{
	class TunnelingBehaviour : public engine::Behaviour
	{
	public:
		// 0x10079130
		explicit TunnelingBehaviour(engine::GameObject* newOwner);
		// 0x10078DD0 (deleting destructor)
		virtual ~TunnelingBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x10079270), 3 (0x10078AC0), 4 (0x100792A0) and 6 (0x10079BD0)
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		int unknownC;
		math::Vector unknown10;
		math::Vector unknown1C;
		math::Vector unknown28;
		float depthUnderground;  // +0x34
		float offsetOverground;  // +0x38
		int unknown3C;
		int unknown40;
		int unknown44;
		engine::BaseAttribute* puppetAttribute;  // +0x48
		bool unknown4C;
		float unknown50;
	};

}

#endif
