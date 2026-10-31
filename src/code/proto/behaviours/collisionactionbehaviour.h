// proto::CollisionActionBehaviour (RTTI and reflection names; base engine::Behaviour): collects the colliders an object
// touches in the collision messages (type 0x1D) and acts on them. Reflected: the most colliders it keeps and whether it
// warns when there are more. Unit 0x10064A80 - 0x10065D60 (no assert path; the file name is a guess). The reflected names
// are original, the rest is guessed; only the reflection is reconstructed.
#ifndef PROTO_COLLISIONACTIONBEHAVIOUR_H
#define PROTO_COLLISIONACTIONBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/math/vector.h"

namespace proto
{
	class CollisionActionBehaviour : public engine::Behaviour
	{
	public:
		// A collider in the list: the object and the time since the last report
		struct Collider
		{
			int object;
			float time;
		};

		// 0x10065B90
		explicit CollisionActionBehaviour(engine::GameObject* newOwner);
		// 0x10065C30 (deleting destructor 0x10065D30)
		virtual ~CollisionActionBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 (0x10065820), 3 (0x10065B50), 4 (0x10065A90) and 6 (0x10065C60)
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x100659C0: forgets the colliders
		void ClearColliders(engine::Message* message);
		// 0x10065A70: starts again
		void Reset();

		int unknownC;
		bool unknown10;
		float unknown14;
		float unknown18;
		float unknown1C;
		float unknown20;
		float unknown24;
		float unknown28;
		float unknown2C;
		int colliderListCountMax;  // +0x30
		container::ArrayDynamic<Collider, container::AllocatorNew> colliders;  // +0x34
		int unknown40;
		bool noWarningOnTooManyColliders;  // +0x44
	};

}

#endif
