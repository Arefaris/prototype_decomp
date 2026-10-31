// The fight condition on a game object's physics and the tracks that blend the physics of a pose or of a joint (unit
// 0x108F4F40 - 0x108F5A00; no assert path, file name guessed).
#include "code/engine/fight/physicsblend.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/ravenphysics/physicsobject.h"

namespace engine
{
	extern content::ObjectName gPhysicsObjectAttributeName;
	GameObjectHandle GetObjectHandle(core::IRefCount* object);
	// The enum tables of the condition's properties (0x1131B270: three entries, 0x1131B250: four)
	extern fight::EnumEntry gHasPhysicsInContextTable[];
	extern fight::EnumEntry gHasPhysicsCollisionObjectsTable[];

	fight::Property** gHasPhysicsConditionProperties;  // 0x1131B248

	// FUNCTION: ENGINE 0x108F4F40
	bool HasPhysicsCondition::SetValidPhysicsObject(bool newValue)
	{
		validPhysicsObject = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F4F50
	bool HasPhysicsCondition::SetInContext(int newValue)
	{
		inContext = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F4F60
	bool HasPhysicsCondition::SetEnabledCollisionObjects(int newValue)
	{
		enabledCollisionObjects = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F4F70
	fight::Property* HasPhysicsCondition::GetProperty(int index)
	{
		return gHasPhysicsConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108F4F80
	void HasPhysicsCondition::ClearProperties()
	{
		fight::FreePropertyList(&gHasPhysicsConditionProperties);
	}

	// FUNCTION: ENGINE 0x108F4F90
	HasPhysicsCondition::HasPhysicsCondition() : fight::Condition(0), enabledCollisionObjects(0), inContext(0), validPhysicsObject(true)
	{
	}

	// FUNCTION: ENGINE 0x108F4FC0
	HasPhysicsCondition::~HasPhysicsCondition()
	{
	}

	// FUNCTION: ENGINE 0x1092D040
	bool HasPhysicsCondition::Evaluate(int a, int b, int c, int d)
	{
		GameObjectHandle handle = GetObjectHandle((core::IRefCount*)c);
		GameObject* object = handle.Get();
		if (object == 0)
		{
			return false;
		}
		BaseAttribute* attribute = object->FindAttribute(gPhysicsObjectAttributeName);
		if (attribute == 0)
		{
			return false;
		}
		ravenphysics::ObjectHandle* value = &((Attribute<ravenphysics::ObjectHandle>*)attribute)->value;
		if (value == 0)
		{
			return false;
		}
		ravenphysics::ObjectHandle physicsHandle = *value;
		if (!physicsHandle.IsValid())
		{
			return false;
		}
		ravenphysics::PhysicsObject* physics = physicsHandle.GetObject();
		int context = inContext;
		bool wantsAsleep = context == 0;
		if (context != 2 && physics->IsAsleep() != wantsAsleep)
		{
			return false;
		}
		int collisionObjects = enabledCollisionObjects;
		if (collisionObjects != 3)
		{
			int active = physics->GetActiveCount();
			if (collisionObjects == 2)
			{
				if (active == 0)
				{
					return false;
				}
			}
			else if (active != (collisionObjects == 0 ? physics->objectCount : 0))
			{
				return false;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108F5110
	fight::ConditionFactory* CreateHasPhysicsConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<HasPhysicsCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F5130
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch; ours sinks the push behind the branch
	// and leaves the early exit without the pop; every other instruction is the engine's
	void HasPhysicsCondition::RegisterProperties()
	{
		if (gHasPhysicsConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyBool<HasPhysicsCondition>("validPhysicsObject", &HasPhysicsCondition::SetValidPhysicsObject);
			properties[0] = property;
			property = new fight::PropertyEnumConstList<HasPhysicsCondition>("inContext", gHasPhysicsInContextTable, 3, &HasPhysicsCondition::SetInContext);
			properties[1] = property;
			property = new fight::PropertyEnumConstList<HasPhysicsCondition>("enabledCollisionObjects", gHasPhysicsCollisionObjectsTable, 4, &HasPhysicsCondition::SetEnabledCollisionObjects);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gHasPhysicsConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108F5230
	void RegisterHasPhysicsConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<HasPhysicsCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyBool<HasPhysicsCondition>;
	template class fight::PropertyEnumConstList<HasPhysicsCondition>;
	template class fight::ConditionFactoryTemplate<HasPhysicsCondition>;
	template class fight::ConditionFactoryCasterTemplate<HasPhysicsCondition>;

	fight::Property** gPhysicsPoseBlendFactorTrackProperties;  // 0x1131B288

	// FUNCTION: ENGINE 0x108F52F0
	bool PhysicsPoseBlendFactorTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F5300
	bool PhysicsPoseBlendFactorTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F5310
	bool PhysicsPoseBlendFactorTrack::SetTargetBlendFactor(float newValue)
	{
		targetBlendFactor = newValue;
		return true;
	}

	fight::Property** gPhysicsJointBlendFactorTrackProperties;  // 0x1131B28C

	// FUNCTION: ENGINE 0x108F5320
	bool PhysicsJointBlendFactorTrack::SetTimeBegin(float newValue)
	{
		timeBegin = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F5330
	bool PhysicsJointBlendFactorTrack::SetTimeEnd(float newValue)
	{
		timeEnd = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F5340
	bool PhysicsJointBlendFactorTrack::SetTargetBlendFactor(float newValue)
	{
		targetBlendFactor = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F5350
	fight::Property* PhysicsPoseBlendFactorTrack::GetProperty(int index)
	{
		return gPhysicsPoseBlendFactorTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F5360
	void PhysicsPoseBlendFactorTrack::ClearProperties()
	{
		fight::FreePropertyList(&gPhysicsPoseBlendFactorTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F5370
	PhysicsPoseBlendFactorTrack::PhysicsPoseBlendFactorTrack() : targetBlendFactor(0.0f), timeBegin(0.0f), timeEnd(0.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x1092D120
	float PhysicsPoseBlendFactorTrack::GetTargetBlendFactor() const
	{
		return targetBlendFactor;
	}

	// FUNCTION: ENGINE 0x108F53A0
	float PhysicsPoseBlendFactorTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F53B0
	float PhysicsPoseBlendFactorTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108F53C0
	PhysicsPoseBlendFactorTrack::~PhysicsPoseBlendFactorTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F53D0
	fight::Property* PhysicsJointBlendFactorTrack::GetProperty(int index)
	{
		return gPhysicsJointBlendFactorTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108F53E0
	void PhysicsJointBlendFactorTrack::ClearProperties()
	{
		fight::FreePropertyList(&gPhysicsJointBlendFactorTrackProperties);
	}

	// FUNCTION: ENGINE 0x108F53F0
	bool PhysicsJointBlendFactorTrack::SetJointName(const fight::Name& newValue)
	{
		jointName = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x1092D130
	float PhysicsJointBlendFactorTrack::GetTargetBlendFactor() const
	{
		return targetBlendFactor;
	}

	// FUNCTION: ENGINE 0x1092D140
	const fight::Name* PhysicsJointBlendFactorTrack::GetJointName() const
	{
		return &jointName;
	}

	// FUNCTION: ENGINE 0x108F5430
	PhysicsJointBlendFactorTrack::PhysicsJointBlendFactorTrack() : targetBlendFactor(0.0f), timeBegin(0.0f), timeEnd(0.0f)
	{
		unknownC = 1;
	}

	// FUNCTION: ENGINE 0x108F5470
	float PhysicsJointBlendFactorTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x108F5480
	float PhysicsJointBlendFactorTrack::Slot10() const
	{
		return timeEnd - timeBegin;
	}

	// FUNCTION: ENGINE 0x108F5490
	PhysicsJointBlendFactorTrack::~PhysicsJointBlendFactorTrack()
	{
	}

	// FUNCTION: ENGINE 0x108F55E0
	fight::TrackFactory* CreatePhysicsPoseBlendFactorTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<PhysicsPoseBlendFactorTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F5600
	fight::TrackFactory* CreatePhysicsJointBlendFactorTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<PhysicsJointBlendFactorTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F5620
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch; ours sinks the push behind the branch
	// and leaves the early exit without the pop; every other instruction is the engine's
	void PhysicsPoseBlendFactorTrack::RegisterProperties()
	{
		if (gPhysicsPoseBlendFactorTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<PhysicsPoseBlendFactorTrack>("timeBegin", &PhysicsPoseBlendFactorTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<PhysicsPoseBlendFactorTrack>("timeEnd", &PhysicsPoseBlendFactorTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<PhysicsPoseBlendFactorTrack>("targetBlendFactor", &PhysicsPoseBlendFactorTrack::SetTargetBlendFactor);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gPhysicsPoseBlendFactorTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x108F5700
	void RegisterPhysicsPoseBlendFactorTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<PhysicsPoseBlendFactorTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x108F5730
	void RegisterPhysicsJointBlendFactorTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<PhysicsJointBlendFactorTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	// FUNCTION: ENGINE 0x108F57F0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch; ours sinks the push behind the branch
	// and leaves the early exit without the pop; every other instruction is the engine's
	void PhysicsJointBlendFactorTrack::RegisterProperties()
	{
		if (gPhysicsJointBlendFactorTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyFloatConstRange<PhysicsJointBlendFactorTrack>("timeBegin", &PhysicsJointBlendFactorTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<PhysicsJointBlendFactorTrack>("timeEnd", &PhysicsJointBlendFactorTrack::SetTimeEnd);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<PhysicsJointBlendFactorTrack>("targetBlendFactor", &PhysicsJointBlendFactorTrack::SetTargetBlendFactor);
			properties[2] = property;
			property = new fight::PropertyName<PhysicsJointBlendFactorTrack>("jointName", &PhysicsJointBlendFactorTrack::SetJointName);
			properties[3] = property;
			fight::RegisterPropertyList(properties, &gPhysicsJointBlendFactorTrackProperties);
		}
	}

	template class fight::PropertyFloatConstRange<PhysicsPoseBlendFactorTrack>;
	template class fight::PropertyFloatConstRange<PhysicsJointBlendFactorTrack>;
	template class fight::PropertyName<PhysicsJointBlendFactorTrack>;
	template class fight::TrackFactoryTemplate<PhysicsPoseBlendFactorTrack>;
	template class fight::TrackFactoryTemplate<PhysicsJointBlendFactorTrack>;
	template class fight::TrackFactoryCasterTemplate<PhysicsPoseBlendFactorTrack>;
	template class fight::TrackFactoryCasterTemplate<PhysicsJointBlendFactorTrack>;
}

namespace engine
{
	core::Name<core::CaseSensitiveKey> gPhysicsObjectAttributeName("physicsObject", 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D73D70
// FUNCTION: ENGINE 0x10D89B70


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108F4FD0
// FUNCTION: ENGINE 0x108F5000
// FUNCTION: ENGINE 0x108F5030
// FUNCTION: ENGINE 0x108F5050
// FUNCTION: ENGINE 0x108F5070
// FUNCTION: ENGINE 0x108F5080
// FUNCTION: ENGINE 0x108F50B0
// FUNCTION: ENGINE 0x108F50C0
// FUNCTION: ENGINE 0x108F50E0
// FUNCTION: ENGINE 0x108F5100
// FUNCTION: ENGINE 0x108F5260
// FUNCTION: ENGINE 0x108F5290
// FUNCTION: ENGINE 0x108F52B0
// FUNCTION: ENGINE 0x108F5410
// FUNCTION: ENGINE 0x108F54B0
// FUNCTION: ENGINE 0x108F54F0
// FUNCTION: ENGINE 0x108F5520
// FUNCTION: ENGINE 0x108F5540
// FUNCTION: ENGINE 0x108F5560
// FUNCTION: ENGINE 0x108F5580
// FUNCTION: ENGINE 0x108F5590
// FUNCTION: ENGINE 0x108F55B0
// FUNCTION: ENGINE 0x108F55D0
// FUNCTION: ENGINE 0x108F5760
// FUNCTION: ENGINE 0x108F5780
// FUNCTION: ENGINE 0x108F57A0
// FUNCTION: ENGINE 0x108F57D0
// FUNCTION: ENGINE 0x108F5900
// FUNCTION: ENGINE 0x108F5940
// FUNCTION: ENGINE 0x108F5970
// FUNCTION: ENGINE 0x108F5990
// FUNCTION: ENGINE 0x108F4FF0
// FUNCTION: ENGINE 0x108F54A0
// FUNCTION: ENGINE 0x108F54E0
