#include "code/proto/behaviours/collisionactionbehaviour.h"

namespace engine
{
	namespace driving
	{
		extern const float gZero;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10065B90
	// EQUIVALENT: the vftable store and the first float store are scheduled differently (89.4 %)
	CollisionActionBehaviour::CollisionActionBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner),
		unknownC(0), unknown10(false), unknown14(0.0f), unknown18(0.0f), unknown1C(0.0f), unknown20(0.0f), unknown24(0.0f),
		unknown28(0.0f), unknown2C(0.0f), colliderListCountMax(0x20), noWarningOnTooManyColliders(false)
	{
		Listen(0x1d, true);
		Listen(5, true);
		Listen(2, true);
	}

	CollisionActionBehaviour::~CollisionActionBehaviour()
	{
	}

	// FUNCTION: ENGINE 0x10065820
	void CollisionActionBehaviour::Slot1()
	{
		colliders.Allocate(colliderListCountMax);
	}

	// FUNCTION: ENGINE 0x10065B50
	void CollisionActionBehaviour::OnActiveChanged(bool active)
	{
		if (!active)
		{
			colliders.end = colliders.begin;
			unknown10 = false;
		}
		engine::Behaviour::OnActiveChanged(active);
	}

	// FUNCTION: ENGINE 0x10064B20
	void CollisionActionBehaviour::GetCachedWallCollision(GetCachedWallCollisionMessage* message)
	{
		message->found = unknown10;
		message->unknown10 = unknown14;
		message->unknown14 = unknown18;
		message->unknown18 = unknown1C;
		message->unknown1C = unknown20;
		message->unknown20 = unknown24;
		message->unknown24 = unknown28;
		message->unknown28 = unknown2C;
	}

	// FUNCTION: ENGINE 0x10064B70
	void CollisionActionBehaviour::GetBehaviour(GetCollisionActionBehaviourMessage* message)
	{
		message->behaviour = this;
	}

	// FUNCTION: ENGINE 0x10065480
	void CollisionActionBehaviour::SetCollisionActive(SetCollisionActiveMessage* message)
	{
		if (message->active)
		{
			unknownC++;
			return;
		}
		unknownC--;
		if ((int)colliders.Size() <= 0 && unknownC < 0)
		{
			unknownC = 0;
		}
	}

	// FUNCTION: ENGINE 0x10065430
	void CollisionActionBehaviour::FindCachedCollider(FindCachedColliderMessage* message)
	{
		int i = 0;
		int count = colliders.Size();
		if (0 < count)
		{
			Collider* collider = colliders.begin;
			int object = message->object;
			do
			{
				if (collider->object == object)
				{
					message->found = true;
					return;
				}
				i++;
				collider++;
			} while (i < count);
		}
	}

	// FUNCTION: ENGINE 0x100654D0
	// EQUIVALENT: the message is kept in ebx where the engine keeps it in ebp (90.7 %)
	void CollisionActionBehaviour::IsValidCollision(IsValidCollisionMessage* message)
	{
		int i = 0;
		message->valid = false;
		if (0 < unknownC)
		{
			int count = colliders.Size();
			if (0 < count)
			{
				Collider* start = colliders.begin;
				int object = message->object;
				Collider* collider = start;
				do
				{
					if (collider->object == object)
					{
						if (!(message->time >= engine::driving::gZero))
						{
							return;
						}
						if (!(start[i].time >= message->time))
						{
							return;
						}
						break;
					}
					i++;
					collider++;
				} while (i < count);
			}
			message->valid = true;
		}
	}

	// FUNCTION: ENGINE 0x100659D0
	void CollisionActionBehaviour::ValidateCollision(ValidateCollisionMessage* message)
	{
		int i = 0;
		message->valid = false;
		if (0 < unknownC)
		{
			int count = colliders.Size();
			if (0 < count)
			{
				Collider* collider = colliders.begin;
				do
				{
					if (collider->object == message->object)
					{
						if (!(message->time >= 0.0f))
						{
							return;
						}
						if (!(colliders.begin[i].time >= message->time))
						{
							return;
						}
						message->valid = true;
						colliders.begin[i].time = 0.0f;
						return;
					}
					i++;
					collider++;
				} while (i < count);
			}
			InsertCollider(message->object);
			message->valid = true;
		}
	}

	// FUNCTION: ENGINE 0x10065950
	void CollisionActionBehaviour::AddCachedCollider(AddCachedColliderMessage* message)
	{
		int count = colliders.Size();
		int i = 0;
		if (0 < count)
		{
			Collider* collider = colliders.begin;
			do
			{
				if (collider->object == message->object)
				{
					colliders.begin[i].time = 0.0f;
					return;
				}
				i++;
				collider++;
			} while (i < count);
		}
		InsertCollider(message->object);
	}

	// FUNCTION: ENGINE 0x10065880
	// EQUIVALENT: the same test with the operands of the comparison the other way round (98.8 %)
	void CollisionActionBehaviour::InsertCollider(int object)
	{
		if (colliders.Capacity() <= colliders.Size())
		{
			Collider* oldest = colliders.begin;
			Collider* last = colliders.end;
			Collider* collider = oldest;
			while (++collider != last)
			{
				if (collider->time > oldest->time)
				{
					oldest = collider;
				}
			}
			colliders.Erase(oldest);
		}
		colliders.PushBack(Collider(object, 0.0f));
		Listen2(4, true);
	}

	// FUNCTION: ENGINE 0x100659C0
	void CollisionActionBehaviour::ClearColliders(engine::Message* message)
	{
		colliders.end = colliders.begin;
	}

	// FUNCTION: ENGINE 0x10065A70
	// EQUIVALENT: the stores and the pushes of the call's arguments are scheduled differently (39.1 %)
	void CollisionActionBehaviour::Reset()
	{
		unknownC = 0;
		colliders.end = colliders.begin;
		unknown10 = false;
		Listen2(4, false);
	}

	// FUNCTION: ENGINE 0x10065A90
	// EQUIVALENT: the list is tested for being empty with a mask where the engine shifts the byte difference (80.0 %)
	void CollisionActionBehaviour::Update(float dt, unsigned short mask)
	{
		Collider* collider = colliders.begin;
		unknown10 = false;
		float limit = 5.0f;
		if (collider != colliders.end)
		{
			do
			{
				float old = collider->time;
				collider->time = old + dt;
				if (old + dt > limit)
				{
					colliders.Erase(collider);
				}
				else
				{
					collider++;
				}
			} while (collider != colliders.end);
		}
		if (unknownC <= 0 || colliders.end - colliders.begin == 0)
		{
			colliders.end = colliders.begin;
			Listen2(4, false);
		}
	}

	// FUNCTION: ENGINE 0x10065C60
	void CollisionActionBehaviour::OnMessage(engine::Message* message)
	{
		switch (message->type)
		{
		case 2:
			Reset();
			break;
		case 5:
			OnPhysicsMessage(message);
			break;
		case 0x1d:
			switch ((unsigned short)message->id)
			{
			case 6:
				AddCachedCollider(static_cast<AddCachedColliderMessage*>(message));
				break;
			case 5:
				FindCachedCollider(static_cast<FindCachedColliderMessage*>(message));
				break;
			case 1:
				GetCachedWallCollision(static_cast<GetCachedWallCollisionMessage*>(message));
				break;
			case 2:
				SetCollisionActive(static_cast<SetCollisionActiveMessage*>(message));
				break;
			case 3:
				IsValidCollision(static_cast<IsValidCollisionMessage*>(message));
				break;
			case 4:
				ValidateCollision(static_cast<ValidateCollisionMessage*>(message));
				break;
			case 0:
				ClearColliders(message);
				break;
			case 7:
				GetBehaviour(static_cast<GetCollisionActionBehaviourMessage*>(message));
				break;
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x10064AE0
	content::ClassInfo* CollisionActionBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::CollisionActionBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10065710
	content::MemberList* CollisionActionBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, CollisionActionBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<CollisionActionBehaviour, int, 0>("p"),
				PROTO_OFFSET(CollisionActionBehaviour, colliderListCountMax), "colliderListCountMax" },
			{ content::GetMemberPrimitiveMetaType<CollisionActionBehaviour, bool, 0>("p"),
				PROTO_OFFSET(CollisionActionBehaviour, noWarningOnTooManyColliders), "noWarningOnTooManyColliders" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10064C70
// FUNCTION: ENGINE 0x10064CF0
// FUNCTION: ENGINE 0x100650F0
// FUNCTION: ENGINE 0x10065100
// FUNCTION: ENGINE 0x10065650
// FUNCTION: ENGINE 0x10065690

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10064C60
// FUNCTION: ENGINE 0x10064CD0
// FUNCTION: ENGINE 0x10065550
// FUNCTION: ENGINE 0x10065B70
// FUNCTION: ENGINE 0x10065C30
// FUNCTION: ENGINE 0x10065D30

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10065560

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10064B80
// FUNCTION: ENGINE 0x10064BB0
// FUNCTION: ENGINE 0x10064CA0
// FUNCTION: ENGINE 0x100655C0
// FUNCTION: ENGINE 0x10065600
