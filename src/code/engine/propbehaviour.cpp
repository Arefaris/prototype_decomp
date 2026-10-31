#include "code/engine/propbehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/healthmessages.h"
#include "code/engine/physics/physicsmessages.h"
#include "code/engine/propspawner.h"
#include "code/math/mathconstants.h"
#include <math.h>
#include <new>
#include "code/engine/gameobject/messagerouter.h"

namespace engine
{
	// Whether every component of a differs from b's by at most tolerance (the inlined body of math::Vector::IsNear)
	static inline bool IsNear(const math::Vector& a, const math::Vector& b, float tolerance)
	{
		return fabsf(a.x - b.x) <= tolerance && fabsf(a.y - b.y) <= tolerance && fabsf(a.z - b.z) <= tolerance;
	}

	// The listener list the props leave when they stop (0x1130E5A0; name guessed) and the name of the attribute that
	// holds the spawner (0x11283538; name guessed)
	MessageListeners gPropListeners("Prop", 0);
	extern content::ObjectName gPropSpawnerName;
	extern content::ObjectName gMetaObjectTemplateName;
	extern int gAttributeHeap;

	// The object's PropSpawner attribute, made when the object has none: while the object is being constructed it goes
	// into the static list, else into the dynamic one (0x10841390; the engine keeps this instance in the unit)
	// FUNCTION: ENGINE 0x10841390
	template<> Attribute<PropSpawner*>* GameObject::SetAttributeAndGet<PropSpawner*>(const content::ObjectName& name,
		PropSpawner* const& value, bool overwrite)
	{
		Attribute<PropSpawner*>* attribute = (Attribute<PropSpawner*>*)FindAttribute(name);
		if (attribute == 0)
		{
			if (this == GetConstructingObject())
			{
				core::HeapScope scope(GetConstructionHeap());
				attribute = new Attribute<PropSpawner*>();
				attribute->value = value;
				AddAttribute(name, attribute);
			}
			else
			{
				core::HeapScope scope(gAttributeHeap);
				attribute = new Attribute<PropSpawner*>();
				attribute->value = value;
				if (!AddDynamicAttribute(name, attribute))
				{
					delete attribute;
					return 0;
				}
			}
		}
		else if (overwrite)
		{
			attribute->value = value;
		}
		return attribute;
	}

	// FUNCTION: ENGINE 0x10841490
	template<> Attribute<PropSpawner*>* GameObject::SetAttributeAndGet<PropSpawner*>(const content::ObjectName& name,
		PropSpawner* const& value)
	{
		return SetAttributeAndGet<PropSpawner*>(name, value, false);
	}

	// FUNCTION: ENGINE 0x108414B0
	PropBehaviour::PropBehaviour(GameObject* newOwner) : Behaviour(newOwner)
	{
		PropSpawner* spawner = 0;
		owner->SetAttributeAndGet<PropSpawner*>(gPropSpawnerName, spawner, false);
		content::ObjectName empty(0, 1);
		owner->SetAttribute<content::ObjectName>(gMetaObjectTemplateName, empty, false);
		Listen(6, true);
		Listen(0x18, true);
	}

	// FUNCTION: ENGINE 0x10841060
	content::ClassInfo* PropBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::PropBehaviour";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10841200
	content::MemberList* PropBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, PropBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		return &sList;
	}

	// FUNCTION: ENGINE 0x108410A0
	void PropBehaviour::Slot1()
	{
		GetHandle(owner).RouterRemove(gPropListeners);
	}

	// FUNCTION: ENGINE 0x108410C0
	void PropBehaviour::OnPhysicsFilterOn(PhysicsFilterMessage* message)
	{
		if (message->flag)
		{
			SetIntersectionPropertiesMessage properties(0x40, true, 0, false);
			owner->SendMessage(&properties);
		}
	}

	// FUNCTION: ENGINE 0x10841190
	void PropBehaviour::OnMessage(Message* message)
	{
		if (message->type == 6 && message->id == 0)
		{
			OnPhysicsFilterOn((PhysicsFilterMessage*)message);
		}
	}

	// FUNCTION: ENGINE 0x10841260
	void PropBehaviour::OnMovedQuery(PropMovedMessage* message)
	{
		Attribute<PropSpawner*>* attribute = (Attribute<PropSpawner*>*)owner->FindAttribute(gPropSpawnerName);
		if (attribute != 0)
		{
			PropSpawner* spawner = attribute->value;
			if (spawner != 0)
			{
				message->found = true;
				math::Vector spawnerPosition(spawner->transform.m[3][0], spawner->transform.m[3][1],
					spawner->transform.m[3][2]);
				const math::Matrix& matrix = owner->transform->value;
				math::Vector position(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
				message->moved = !IsNear(spawnerPosition, position, math::EPSILON_SMALL);
			}
		}
	}

	// FUNCTION: ENGINE 0x10841370
	void PropBehaviour::OnPostedMessage(Message* message)
	{
		if (message->type == 0x18 && message->id == 8)
		{
			OnMovedQuery((PropMovedMessage*)message);
		}
	}
}

// Kept copies (inline functions and template instances of this unit):
// FUNCTION: ENGINE 0x10841130
// FUNCTION: ENGINE 0x10841140
// FUNCTION: ENGINE 0x10841150
// FUNCTION: ENGINE 0x10841160
// FUNCTION: ENGINE 0x108411C0
// FUNCTION: ENGINE 0x108411E0
// FUNCTION: ENGINE 0x10841330
// FUNCTION: ENGINE 0x10841350

template class engine::ConstAttribute<engine::PropSpawner*>;

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D750E0
// FUNCTION: ENGINE 0x10D8A2B0

// FUNCTION: ENGINE 0x10841530
