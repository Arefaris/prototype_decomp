#include "code/proto/messages/movementmessages.h"
#include "code/proto/fightitems/ai/aihelpers.h"
#include "code/proto/fightitems/ai/aimessages.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/engine/driving/vehicleintentionbehaviour.h"
#include "code/engine/render/renderbehaviour.h"
#include "code/proto/fightitems/motion/motion_patsy.h"
#include "code/proto/messages/statemessages.h"
#include "code/proto/messages/airequestmessages.h"
#include "code/proto/fightitems/motion/motion_boundary.h"
#include "code/proto/fightitems/motion/motionmessages.h"
#include "code/math/matrix.h"
#include <math.h>
#include "code/proto/behaviours/aimbehaviour.h"
#include "code/proto/behaviours/helicoptersolverproperties.h"
#include "code/proto/behaviours/tanksolver.h"

namespace proto
{
	namespace HitEffectManager
	{
		// 0x112562B8: the name of the attribute that holds an object's class name
		extern core::Name<core::CaseSensitiveKey> gClassNameAttributeName;
	}

	// 0x103BDE30 / 0x103BE0E0 (another function of this file): the object turns towards a direction
	void Unknown103BDE30(engine::GameObject* object, const math::Vector* direction, bool flag);
	void Unknown103BE0E0(engine::GameObject* object, const math::Vector* direction);
}

namespace choreo
{
	// 0x10945950: the heading of a direction in the horizontal plane (name guess)
	float HeadingXZ(float x, float z);
	// 0x10D94FF8: -1.0f in the pooled constants
	extern const float gMinusOne;
}

namespace proto
{
	// 0x103B8FF0 (movementsenders.cpp)
	bool Unknown103B8FF0(engine::GameObject* object);
	// 0x103B86E0 (below)
	void Unknown103B86E0(engine::GameObject* object, const math::Vector* direction);
	// 0x103B8E10 (movementsenders.cpp)
	int Unknown103B8E10(engine::GameObject* object);

	// The message that names the target to take (type 0x20, id 2)
	class SetTargetMessage : public TargetMessage
	{
	public:
		explicit SetTargetMessage(engine::GameObjectHandle newTarget) : TargetMessage(2), target(newTarget)
		{
		}
		virtual ~SetTargetMessage()
		{
		}

		engine::GameObjectHandle target;  // +0xC
	};

	// RTTI: proto::GetHelicopterSolverParamsMessage: the helicopter answers the properties of its solver (message type
	// 0x31, id 0)
	struct GetHelicopterSolverParamsMessage : public VehicleMessage
	{
		GetHelicopterSolverParamsMessage() : VehicleMessage(0), unknownC(0), properties(0)
		{
		}
		virtual ~GetHelicopterSolverParamsMessage()
		{
		}

		int unknownC;  // +0xC
		HelicopterSolverProperties* properties;  // +0x10
	};

	// RTTI: proto::GetTankSolverPropertiesVehicleMessage: the tank answers the properties of its solver (message type
	// 0x31, id 2)
	struct GetTankSolverPropertiesVehicleMessage : public VehicleMessage
	{
		GetTankSolverPropertiesVehicleMessage() : VehicleMessage(2), properties(0)
		{
		}
		virtual ~GetTankSolverPropertiesVehicleMessage()
		{
		}

		TankSolverProperties* properties;  // +0xC
	};

	// More helpers that send messages to an object (unit 0x103B81A0 - 0x103BEA10, no assert path; the file name is a
	// guess)

	// FUNCTION: ENGINE 0x103B81A0
	void Unknown103B81A0(engine::GameObject* object)
	{
		engine::CharacterQueryIntentionMessage query;
		object->SendMessage(&query);
		if (query.intention != 0)
		{
			query.intention->Reset();
		}
		ResetAIFrameInfoMovementMessage message;
		object->SendMessage(&message);
	}

	// 0x103B83D0: sends the object along a flight path (name guess)
	struct FlyPathParams
	{
		float speed;
		bool unknown4;
		bool unknown5;
	};

	// FUNCTION: ENGINE 0x103B83D0
	void SendGotoFlyPath(engine::GameObject* object, void* path, const FlyPathParams* params)
	{
		GotoFlyPathMovementMessage message(params->speed, params->unknown4, params->unknown5, path);
		object->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x103B8690
	void SendSetTarget(engine::GameObject* object, engine::GameObjectHandle target)
	{
		SetTargetMessage message(target);
		object->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x103B8860
	// NONMATCHING: the engine selects the value on the x87 stack (fld1 or the pooled constant), ours through SSE (61.7 %)
#ifdef NONMATCHING
	void SendButton19(engine::GameObject* object, bool pressed)
	{
		engine::CharacterQueryIntentionMessage query;
		object->SendMessage(&query);
		engine::CharacterIntentionButton* button = query.intention->GetButtonOther(0x13);
		button->Press(pressed ? 1.0f : choreo::gMinusOne);
	}
#endif

	// FUNCTION: ENGINE 0x103B8C10
	void SendButton6(engine::GameObject* object)
	{
		engine::CharacterQueryIntentionMessage query;
		object->SendMessage(&query);
		query.intention->GetButtonOther(6)->Press(1.0f);
	}

	// 0x103B9050: from here on the render sources of new objects are made later (name guess)
	// FUNCTION: ENGINE 0x103B9050
	void Unknown103B9050()
	{
		engine::RenderBehaviour::SetSourcesDeferred(true);
	}

	// FUNCTION: ENGINE 0x103B9060
	void Unknown103B9060(engine::GameObject* object)
	{
		engine::RenderBehaviour::SetSourcesDeferred(false);
		if (object != 0)
		{
			if (Unknown103B8FF0(object))
			{
				InstantFreezeAIMsg freeze;
				object->SendMessage(&freeze);
			}
			engine::PhysicsWakeUpMessage wake;
			object->SendMessage(&wake);
		}
	}

	// FUNCTION: ENGINE 0x103B9520
	bool Unknown103B9520(engine::GameObject* object)
	{
		engine::CharacterQueryPlayerControlStateMessage message;
		object->SendMessage(&message);
		if (message.info != 0 && message.info->Get() != 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x103B9B00
	float Unknown103B9B00(engine::GameObject* object)
	{
		GetHelicopterSolverParamsMessage message;
		object->SendMessage(&message);
		return message.properties->longitudinalAxisLinearParams.ScaleMaxForwardSpeed(1.0f);
	}

	// FUNCTION: ENGINE 0x103B9B60
	float Unknown103B9B60(engine::GameObject* object)
	{
		GetTankSolverPropertiesVehicleMessage message;
		object->SendMessage(&message);
		return message.properties->thrust.maxForwardSpeed;
	}

	// FUNCTION: ENGINE 0x103B9CF0
	float Unknown103B9CF0(engine::GameObject* object, const math::Vector* point, bool flag)
	{
		HydraEvaluateDestinationMovementMessage message(*point, flag);
		object->SendMessage(&message);
		return message.unknown1C;
	}

	// 0x103BAD20: the object jumps to a place of an object (name guess)
	struct JumpParams
	{
		engine::GameObjectHandle target;
		math::Vector position;
	};

	// FUNCTION: ENGINE 0x103BAD20
	void Unknown103BAD20(engine::GameObject* object, const JumpParams* params)
	{
		JumpToMovementMessage message(params->target, params->position);
		object->SendMessage(&message);
		engine::CharacterQueryIntentionMessage query;
		object->SendMessage(&query);
		if (query.intention != 0)
		{
			query.intention->GetButtonOther(3)->Press(1.0f);
		}
	}

	// FUNCTION: ENGINE 0x103BB410
	bool Unknown103BB410(engine::GameObject* object, int level, bool sustained)
	{
		if (object == 0)
		{
			return false;
		}
		int current;
		if (sustained)
		{
			current = Unknown103B8DC0(object);
		}
		else
		{
			current = Unknown103B8E10(object);
		}
		if (current != level)
		{
			SetGameObjectLODAIMsg message(level, sustained);
			object->SendMessage(&message);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x103BB730
	int Unknown103BB730(engine::GameObject* object)
	{
		GetMotionStateMsg message;
		object->SendMessage(&message);
		return message.state;
	}

	// FUNCTION: ENGINE 0x103BB790
	void Unknown103BB790(engine::GameObject* object, math::Vector* vector)
	{
		math::Matrix inverse = object->transform->value;
		inverse.Invert();
		inverse.Rotate(*vector, *vector);
	}

	// FUNCTION: ENGINE 0x103BB8A0
	void Unknown103BB8A0(engine::GameObject* object, math::Vector* vector)
	{
		math::Matrix world = object->transform->value;
		world.Rotate(*vector, *vector);
	}

	// FUNCTION: ENGINE 0x103BAE00
	void Unknown103BAE00(engine::GameObject* object, JumpDestination* target)
	{
		target->Update();
		math::Vector at;
		object->transform->GetPointer()->GetTranslation(at);
		math::Vector goal = target->position;
		math::Vector direction;
		direction.Sub(goal, at);
		Unknown103B86E0(object, &direction);
	}

	// FUNCTION: ENGINE 0x103BDD00
	void Unknown103BDD00(engine::GameObject* object, engine::GameObjectHandle target)
	{
		JumpDestination aimTarget(target);
		aimTarget.Update();
		Unknown103BAE00(object, &aimTarget);
		engine::CharacterQueryIntentionMessage query;
		object->SendMessage(&query);
		query.intention->GetButtonOther(0)->Press(1.0f);
	}

	// FUNCTION: ENGINE 0x103BDDA0
	void Unknown103BDDA0(engine::GameObject* object, engine::GameObjectHandle target)
	{
		JumpDestination aimTarget(target);
		aimTarget.Update();
		Unknown103BAE00(object, &aimTarget);
		engine::CharacterQueryIntentionMessage query;
		object->SendMessage(&query);
		query.intention->GetButtonOther(1)->Press(1.0f);
	}

	// FUNCTION: ENGINE 0x103B86E0
	// NONMATCHING: the engine keeps the heading and the vertical component in stack slots of their own (28 %)
#ifdef NONMATCHING
	void Unknown103B86E0(engine::GameObject* object, const math::Vector* direction)
	{
		math::Vector normal = *direction;
		normal.Normalize();
		float heading = choreo::HeadingXZ(normal.x, normal.z);
		engine::CharacterQueryIntentionMessage query;
		object->SendMessage(&query);
		float pitch = (float)asin(normal.y);
		query.intention->GetAxisCopy(9)->Set(0.0f, pitch);
		query.intention->GetAxisCopy(10)->Set(0.0f, heading);
	}
#endif

	// FUNCTION: ENGINE 0x103BE050
	void Unknown103BE050(engine::GameObject* object, JumpDestination* target, bool flag)
	{
		target->Update();
		math::Vector at;
		object->transform->GetPointer()->GetTranslation(at);
		math::Vector goal = target->position;
		math::Vector direction;
		direction.Sub(goal, at);
		Unknown103BDE30(object, &direction, flag);
	}

	// FUNCTION: ENGINE 0x103BE300
	// NONMATCHING: the engine copies the target point into the direction before it loads the translation (37.5 %)
#ifdef NONMATCHING
	void Unknown103BE300(engine::GameObject* object, JumpDestination* target)
	{
		target->Update();
		math::Vector at;
		object->transform->GetPointer()->GetTranslation(at);
		math::Vector direction = target->position;
		direction.Sub(direction, at);
		Unknown103BE0E0(object, &direction);
	}
#endif

	// FUNCTION: ENGINE 0x103BE3A0
	int Unknown103BE3A0(engine::GameObject* object)
	{
		if (!IsPlayerObject(object))
		{
			return 0;
		}
		if (fightitems::motion::GetObjectHealth(object) > 0.0f)
		{
			return 1;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x103BE450
	core::Name<core::CaseSensitiveKey> Unknown103BE450(engine::GameObject* object)
	{
		engine::BaseAttribute* attribute = object->FindAttribute(HitEffectManager::gClassNameAttributeName);
		core::Name<core::CaseSensitiveKey>* value = (attribute != 0) ? &((engine::Attribute<core::Name<core::CaseSensitiveKey> >*)attribute)->value : 0;
		if (value != 0)
		{
			core::Name<core::CaseSensitiveKey> local(*value);
			return local;
		}
		return core::Name<core::CaseSensitiveKey>();
	}
}
