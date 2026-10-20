// The fight conditions that ask a character about its supporting surface and limb (units 0x10809A40 - 0x1080A600 and 0x108A9100 - 0x108AAC50)
#include "code/engine/fight/supportingsurface.h"
#include "code/choreo/deltatransform.h"
#include "code/ravenphysics/physicsobject.h"
#include <float.h>
#include <math.h>

namespace engine
{
	extern fight::EnumEntry gCompareOperatorTable[];
	extern const int gCompareOperatorCount;

	fight::Property** gSupportingSurfaceAgeConditionProperties;  // 0x11318190

	// FUNCTION: ENGINE 0x108A9100
	bool SupportingSurfaceAgeCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A9110
	bool SupportingSurfaceAgeCondition::SetAge(float newValue)
	{
		age = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10809A40
	int SupportingSurfaceAgeCondition::GetCompare() const
	{
		return compare;
	}

	// FUNCTION: ENGINE 0x10809A50
	float SupportingSurfaceAgeCondition::GetAge() const
	{
		return age;
	}

	// FUNCTION: ENGINE 0x108A9260
	fight::Property* SupportingSurfaceAgeCondition::GetProperty(int index)
	{
		return gSupportingSurfaceAgeConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108A9270
	void SupportingSurfaceAgeCondition::ClearProperties()
	{
		fight::FreePropertyList(&gSupportingSurfaceAgeConditionProperties);
	}

	// FUNCTION: ENGINE 0x108A9280
	// ctor stores: [('mov', 'dword', 0, '0x10e79734'), ('movss', 'dword', 12, '0.0f'), ('mov', 'dword', 16, '0')]
	SupportingSurfaceAgeCondition::SupportingSurfaceAgeCondition() : fight::Condition(0), age(0.0f), compare(0)
	{
	}

	// FUNCTION: ENGINE 0x1080A600
	bool SupportingSurfaceAgeCondition::Evaluate(int a, int b, int c, int d)
	{
		GameObjectHandle handle = GetObjectHandle((core::IRefCount*)c);
		GameObject* object = handle.Get();
		if (object == 0)
		{
			return false;
		}
		CharacterQueryCollisionStateMessage message;
		object->SendMessage(&message);
		const SupportingLimb::Support* support = message.support;
		if (support == 0)
		{
			return false;
		}
		float value = age;
		int op = compare;
		return fight::CompareFloats(op, &support->unsupportedTime, &value);
	}

	// FUNCTION: ENGINE 0x108A92B0
	SupportingSurfaceAgeCondition::~SupportingSurfaceAgeCondition()
	{
	}

	// FUNCTION: ENGINE 0x108A9F80
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SupportingSurfaceAgeCondition::RegisterProperties()
	{
		if (gSupportingSurfaceAgeConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnumConstList<SupportingSurfaceAgeCondition>("compare", gCompareOperatorTable, gCompareOperatorCount, &SupportingSurfaceAgeCondition::SetCompare);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<SupportingSurfaceAgeCondition>("age", &SupportingSurfaceAgeCondition::SetAge);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gSupportingSurfaceAgeConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108A9E80
	fight::ConditionFactory* CreateSupportingSurfaceAgeConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceAgeCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AA490
	void RegisterSupportingSurfaceAgeConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceAgeCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<SupportingSurfaceAgeCondition>;
	template class fight::PropertyFloatConstRange<SupportingSurfaceAgeCondition>;
	template class fight::ConditionFactoryTemplate<SupportingSurfaceAgeCondition>;
	template class fight::ConditionFactoryCasterTemplate<SupportingSurfaceAgeCondition>;

	fight::Property** gSupportingSurfaceConditionProperties;  // 0x11318194

	// FUNCTION: ENGINE 0x108A9120
	bool SupportingSurfaceCondition::SetOnSupportingSurface(bool newValue)
	{
		onSupportingSurface = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10809A60
	bool SupportingSurfaceCondition::GetOnSupportingSurface() const
	{
		return onSupportingSurface;
	}

	// FUNCTION: ENGINE 0x108A92C0
	fight::Property* SupportingSurfaceCondition::GetProperty(int index)
	{
		return gSupportingSurfaceConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108A92D0
	void SupportingSurfaceCondition::ClearProperties()
	{
		fight::FreePropertyList(&gSupportingSurfaceConditionProperties);
	}

	// FUNCTION: ENGINE 0x108A92E0
	// ctor stores: [('mov', 'dword', 0, '0x10e79760'), ('mov', 'byte', 12, '1')]
	SupportingSurfaceCondition::SupportingSurfaceCondition() : fight::Condition(0), onSupportingSurface(1)
	{
	}

	// FUNCTION: ENGINE 0x10809C00
	bool SupportingSurfaceCondition::Evaluate(int a, int b, int c, int d)
	{
		GameObjectHandle handle = GetObjectHandle((core::IRefCount*)c);
		GameObject* object = handle.Get();
		if (object == 0)
		{
			return false;
		}
		CharacterQueryCollisionStateMessage message;
		object->SendMessage(&message);
		return (message.support != 0 ? message.support->supported : false) == onSupportingSurface;
	}

	// FUNCTION: ENGINE 0x108A9300
	SupportingSurfaceCondition::~SupportingSurfaceCondition()
	{
	}

	// FUNCTION: ENGINE 0x108AA040
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SupportingSurfaceCondition::RegisterProperties()
	{
		if (gSupportingSurfaceConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyBool<SupportingSurfaceCondition>("onSupportingSurface", &SupportingSurfaceCondition::SetOnSupportingSurface);
			properties[0] = property;
			fight::RegisterPropertyList(properties, &gSupportingSurfaceConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108A9EA0
	fight::ConditionFactory* CreateSupportingSurfaceConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AA4C0
	void RegisterSupportingSurfaceConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyBool<SupportingSurfaceCondition>;
	template class fight::ConditionFactoryTemplate<SupportingSurfaceCondition>;
	template class fight::ConditionFactoryCasterTemplate<SupportingSurfaceCondition>;

	namespace animation
	{
		extern fight::EnumEntry gVelocityTypeTable[];
		extern const int gVelocityTypeCount;
	}

	fight::Property** gSupportingSurfaceVelocityAngleConditionProperties;  // 0x11318198

	// FUNCTION: ENGINE 0x108A9130
	bool SupportingSurfaceVelocityAngleCondition::SetVelocityType(int newValue)
	{
		velocityType = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A9140
	bool SupportingSurfaceVelocityAngleCondition::SetZeroVector(const math::Vector& newValue)
	{
		zeroVector.x = newValue.x;
		zeroVector.y = newValue.y;
		zeroVector.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108A9160
	bool SupportingSurfaceVelocityAngleCondition::SetAngle(float newValue)
	{
		angle = newValue * 0.01745329238474369f;
		return true;
	}

	// FUNCTION: ENGINE 0x108A9180
	bool SupportingSurfaceVelocityAngleCondition::SetArc(float newValue)
	{
		arc = newValue * 0.01745329238474369f;
		return true;
	}

	// FUNCTION: ENGINE 0x10809A70
	int SupportingSurfaceVelocityAngleCondition::GetVelocityType() const
	{
		return velocityType;
	}

	// FUNCTION: ENGINE 0x10809A80
	math::Vector SupportingSurfaceVelocityAngleCondition::GetZeroVector() const
	{
		return zeroVector;
	}

	// FUNCTION: ENGINE 0x10809AA0
	float SupportingSurfaceVelocityAngleCondition::GetAngle() const
	{
		return angle;
	}

	// FUNCTION: ENGINE 0x10809AB0
	float SupportingSurfaceVelocityAngleCondition::GetArc() const
	{
		return arc;
	}

	// FUNCTION: ENGINE 0x108A9310
	fight::Property* SupportingSurfaceVelocityAngleCondition::GetProperty(int index)
	{
		return gSupportingSurfaceVelocityAngleConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108A9320
	void SupportingSurfaceVelocityAngleCondition::ClearProperties()
	{
		fight::FreePropertyList(&gSupportingSurfaceVelocityAngleConditionProperties);
	}

	// FUNCTION: ENGINE 0x108A9330
	// ctor stores: [('mov', 'dword', 0, '0x10e7978c'), ('movss', 'dword', 12, '0.0f'), ('movss', 'dword', 16, '1.0f'), ('movss', 'dword', 20, '0.0f'), ('movss', 'dword', 24, '0.0f'), ('movss', 'dword', 28, '0.0f'), ('mov', 'dword', 32, '0')]
	SupportingSurfaceVelocityAngleCondition::SupportingSurfaceVelocityAngleCondition() : fight::Condition(0), zeroVector(0.0f, 1.0f, 0.0f), angle(0.0f), arc(0.0f), velocityType(0)
	{
	}

	// FUNCTION: ENGINE 0x10809DA0
	// NONMATCHING: the arithmetic is right, the instruction scheduling and the constant folding of the angle test differ (the engine keeps 1.0f and 0.5f as memory operands), best 36.0 %
#ifdef NONMATCHING
	bool SupportingSurfaceVelocityAngleCondition::Evaluate(int a, int b, int c, int d)
	{
		GameObjectHandle handle = GetObjectHandle((core::IRefCount*)c);
		GameObject* object = handle.Get();
		if (object == 0)
		{
			return false;
		}
		CharacterQueryCollisionStateMessage message;
		object->SendMessage(&message);
		const SupportingLimb::Support* support = message.support;
		if (support == 0)
		{
			return false;
		}
		math::Vector surfaceNormal;
		surfaceNormal.x = support->normal.x;
		surfaceNormal.y = support->normal.y;
		surfaceNormal.z = support->normal.z;
		float dot = zeroVector.z * surfaceNormal.z + zeroVector.y * surfaceNormal.y + zeroVector.x * surfaceNormal.x;
		float scale = math::WORLD_MIN - dot;
		math::Vector reference;
		reference.x = surfaceNormal.x * scale + zeroVector.x;
		reference.y = surfaceNormal.y * scale + zeroVector.y;
		reference.z = surfaceNormal.z * scale + zeroVector.z;
		if (!(reference.Normalize() > 0.0f))
		{
			return false;
		}
		math::Vector velocity;
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		velocity.z = 0.0f;
		if (!GetObjectVelocity(object, velocityType, &velocity))
		{
			return false;
		}
		float velocityDot = velocity.z * surfaceNormal.z + velocity.y * surfaceNormal.y + velocity.x * surfaceNormal.x;
		float velocityScale = math::WORLD_MIN - velocityDot;
		velocity.x = surfaceNormal.x * velocityScale + velocity.x;
		velocity.y = surfaceNormal.y * velocityScale + velocity.y;
		velocity.z = surfaceNormal.z * velocityScale + velocity.z;
		velocity.Normalize();
		float cosine = velocity.z * reference.z + velocity.y * reference.y + velocity.x * reference.x;
		float measured = acosf(cosine);
		if (1e-5f < fabsf(fabsf(cosine) - 1.0f))
		{
			float side = (velocity.y * reference.z - velocity.z * reference.y) * surfaceNormal.x + (reference.y * velocity.x - velocity.y * reference.x) * surfaceNormal.z + (velocity.z * reference.x - reference.z * velocity.x) * surfaceNormal.y;
			if (side < 0.0f)
			{
				measured = math::WORLD_MIN - measured;
			}
		}
		return fabsf(choreo::AngleDifference(measured, angle)) < arc * 0.5f;
	}
#endif

	// FUNCTION: ENGINE 0x108A9370
	SupportingSurfaceVelocityAngleCondition::~SupportingSurfaceVelocityAngleCondition()
	{
	}

	// FUNCTION: ENGINE 0x108AA0C0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SupportingSurfaceVelocityAngleCondition::RegisterProperties()
	{
		if (gSupportingSurfaceVelocityAngleConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnumConstList<SupportingSurfaceVelocityAngleCondition>("velocityType", animation::gVelocityTypeTable, animation::gVelocityTypeCount, &SupportingSurfaceVelocityAngleCondition::SetVelocityType);
			properties[0] = property;
			property = new fight::PropertyVector<SupportingSurfaceVelocityAngleCondition>("zeroVector", &SupportingSurfaceVelocityAngleCondition::SetZeroVector);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<SupportingSurfaceVelocityAngleCondition>("angle", &SupportingSurfaceVelocityAngleCondition::SetAngle);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<SupportingSurfaceVelocityAngleCondition>("arc", &SupportingSurfaceVelocityAngleCondition::SetArc);
			properties[3] = property;
			fight::RegisterPropertyList(properties, &gSupportingSurfaceVelocityAngleConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108A9EC0
	fight::ConditionFactory* CreateSupportingSurfaceVelocityAngleConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceVelocityAngleCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AA4F0
	void RegisterSupportingSurfaceVelocityAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceVelocityAngleCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<SupportingSurfaceVelocityAngleCondition>;
	template class fight::PropertyFloatConstRange<SupportingSurfaceVelocityAngleCondition>;
	template class fight::PropertyVector<SupportingSurfaceVelocityAngleCondition>;
	template class fight::ConditionFactoryTemplate<SupportingSurfaceVelocityAngleCondition>;
	template class fight::ConditionFactoryCasterTemplate<SupportingSurfaceVelocityAngleCondition>;

	extern fight::EnumEntry gCompareOperatorTable[];
	extern const int gCompareOperatorCount;

	fight::Property** gSupportingSurfaceDistanceConditionProperties;  // 0x1131819C

	// FUNCTION: ENGINE 0x108A91A0
	bool SupportingSurfaceDistanceCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A91B0
	bool SupportingSurfaceDistanceCondition::SetDistance(float newValue)
	{
		distance = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10809AC0
	int SupportingSurfaceDistanceCondition::GetCompare() const
	{
		return compare;
	}

	// FUNCTION: ENGINE 0x10809AD0
	float SupportingSurfaceDistanceCondition::GetDistance() const
	{
		return distance;
	}

	// FUNCTION: ENGINE 0x108A9380
	fight::Property* SupportingSurfaceDistanceCondition::GetProperty(int index)
	{
		return gSupportingSurfaceDistanceConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108A9390
	void SupportingSurfaceDistanceCondition::ClearProperties()
	{
		fight::FreePropertyList(&gSupportingSurfaceDistanceConditionProperties);
	}

	// FUNCTION: ENGINE 0x108A93A0
	// ctor stores: [('mov', 'dword', 0, '0x10e797b8'), ('movss', 'dword', 12, '0.0f'), ('mov', 'dword', 16, '0')]
	SupportingSurfaceDistanceCondition::SupportingSurfaceDistanceCondition() : fight::Condition(0), distance(0.0f), compare(0)
	{
	}

	// FUNCTION: ENGINE 0x1080A170
	// NONMATCHING: the same operations, but the compiler associates the two dot products the other way round (x, y, z for the engine's z, y, x) and schedules the loads differently, best 64.7 %
#ifdef NONMATCHING
	bool SupportingSurfaceDistanceCondition::Evaluate(int a, int b, int c, int d)
	{
		GameObjectHandle handle = GetObjectHandle((core::IRefCount*)c);
		GameObject* object = handle.Get();
		if (object == 0)
		{
			return false;
		}
		CharacterQueryCollisionStateMessage message;
		object->SendMessage(&message);
		const SupportingLimb::Support* support = message.support;
		if (support == 0)
		{
			return false;
		}
		float planeDistance = math::WORLD_MIN - (support->normal.x * support->position.x + support->normal.y * support->position.y + support->normal.z * support->position.z);
		math::Matrix& matrix = object->transform->value;
		float distanceValue = matrix.m[3][0] * support->normal.x + matrix.m[3][1] * support->normal.y + matrix.m[3][2] * support->normal.z + planeDistance;
		float value = distance;
		int op = compare;
		return fight::CompareFloats(op, &distanceValue, &value);
	}
#endif

	// FUNCTION: ENGINE 0x108A93D0
	SupportingSurfaceDistanceCondition::~SupportingSurfaceDistanceCondition()
	{
	}

	// FUNCTION: ENGINE 0x108AA1E0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SupportingSurfaceDistanceCondition::RegisterProperties()
	{
		if (gSupportingSurfaceDistanceConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnumConstList<SupportingSurfaceDistanceCondition>("compare", gCompareOperatorTable, gCompareOperatorCount, &SupportingSurfaceDistanceCondition::SetCompare);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<SupportingSurfaceDistanceCondition>("distance", &SupportingSurfaceDistanceCondition::SetDistance);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gSupportingSurfaceDistanceConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108A9EE0
	fight::ConditionFactory* CreateSupportingSurfaceDistanceConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceDistanceCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AA520
	void RegisterSupportingSurfaceDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceDistanceCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<SupportingSurfaceDistanceCondition>;
	template class fight::PropertyFloatConstRange<SupportingSurfaceDistanceCondition>;
	template class fight::ConditionFactoryTemplate<SupportingSurfaceDistanceCondition>;
	template class fight::ConditionFactoryCasterTemplate<SupportingSurfaceDistanceCondition>;

	namespace animation
	{
		extern fight::EnumEntry gVelocityTypeTable[];
		extern const int gVelocityTypeCount;
	}
	extern fight::EnumEntry gCompareOperatorTable[];
	extern const int gCompareOperatorCount;

	fight::Property** gSupportingSurfaceTimeToImpactConditionProperties;  // 0x113181A4

	// FUNCTION: ENGINE 0x108A91D0
	bool SupportingSurfaceTimeToImpactCondition::SetVelocityType(int newValue)
	{
		velocityType = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A91E0
	bool SupportingSurfaceTimeToImpactCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A91F0
	bool SupportingSurfaceTimeToImpactCondition::SetTimeToImpact(float newValue)
	{
		timeToImpact = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10809B00
	int SupportingSurfaceTimeToImpactCondition::GetVelocityType() const
	{
		return velocityType;
	}

	// FUNCTION: ENGINE 0x10809B10
	int SupportingSurfaceTimeToImpactCondition::GetCompare() const
	{
		return compare;
	}

	// FUNCTION: ENGINE 0x10809B20
	float SupportingSurfaceTimeToImpactCondition::GetTimeToImpact() const
	{
		return timeToImpact;
	}

	// FUNCTION: ENGINE 0x108A9400
	fight::Property* SupportingSurfaceTimeToImpactCondition::GetProperty(int index)
	{
		return gSupportingSurfaceTimeToImpactConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108A9410
	void SupportingSurfaceTimeToImpactCondition::ClearProperties()
	{
		fight::FreePropertyList(&gSupportingSurfaceTimeToImpactConditionProperties);
	}

	// FUNCTION: ENGINE 0x108A9420
	// ctor stores: [('mov', 'dword', 0, '0x10e797e4'), ('movss', 'dword', 12, '0.0f'), ('mov', 'dword', 16, '0'), ('mov', 'dword', 20, '0')]
	SupportingSurfaceTimeToImpactCondition::SupportingSurfaceTimeToImpactCondition() : fight::Condition(0), timeToImpact(0.0f), compare(0), velocityType(0)
	{
	}

	// FUNCTION: ENGINE 0x1080A290
	// NONMATCHING: the arithmetic is right; the engine builds the two velocity vectors on the stack before it reads the surface and schedules the dot products later, best 41.9 %
#ifdef NONMATCHING
	bool SupportingSurfaceTimeToImpactCondition::Evaluate(int a, int b, int c, int d)
	{
		GameObjectHandle handle = GetObjectHandle((core::IRefCount*)c);
		GameObject* object = handle.Get();
		if (object == 0)
		{
			return false;
		}
		CharacterQueryCollisionStateMessage message;
		object->SendMessage(&message);
		const SupportingLimb::Support* support = message.support;
		if (support == 0)
		{
			return false;
		}
		math::Vector velocity;
		velocity.x = math::kZeroVector.x;
		velocity.y = math::kZeroVector.y;
		velocity.z = math::kZeroVector.z;
		GetObjectVelocity(object, velocityType, &velocity);
		float planeDistance = math::WORLD_MIN - (support->position.z * support->normal.z + support->position.y * support->normal.y + support->position.x * support->normal.x);
		float closing = math::WORLD_MIN - (support->normal.z * velocity.z + support->normal.y * velocity.y + support->normal.x * velocity.x);
		math::Vector surfaceVelocity;
		surfaceVelocity.x = math::kZeroVector.x;
		surfaceVelocity.y = math::kZeroVector.y;
		surfaceVelocity.z = math::kZeroVector.z;
		ravenphysics::ObjectHandle physicsHandle;
		physicsHandle.value = support->unknown20;
		if (physicsHandle.IsValid())
		{
			ravenphysics::PhysicsObject* physicsObject = physicsHandle.GetObject();
			if (physicsObject != 0)
			{
				GetObjectVelocity((GameObject*)physicsObject->GetUnknown48(), 1, &surfaceVelocity);
			}
		}
		closing = surfaceVelocity.z * support->normal.z + surfaceVelocity.y * support->normal.y + surfaceVelocity.x * support->normal.x + closing;
		float timeToImpactValue = FLT_MAX;
		if (closing > 0.0f)
		{
			math::Matrix& matrix = object->transform->value;
			timeToImpactValue = (matrix.m[3][2] * support->normal.z + matrix.m[3][1] * support->normal.y + matrix.m[3][0] * support->normal.x + planeDistance) / closing;
		}
		float value = timeToImpact;
		return fight::CompareFloats(compare, &timeToImpactValue, &value);
	}
#endif

	// FUNCTION: ENGINE 0x108A9450
	SupportingSurfaceTimeToImpactCondition::~SupportingSurfaceTimeToImpactCondition()
	{
	}

	// FUNCTION: ENGINE 0x108AA2A0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SupportingSurfaceTimeToImpactCondition::RegisterProperties()
	{
		if (gSupportingSurfaceTimeToImpactConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnumConstList<SupportingSurfaceTimeToImpactCondition>("velocityType", animation::gVelocityTypeTable, animation::gVelocityTypeCount, &SupportingSurfaceTimeToImpactCondition::SetVelocityType);
			properties[0] = property;
			property = new fight::PropertyEnumConstList<SupportingSurfaceTimeToImpactCondition>("compare", gCompareOperatorTable, gCompareOperatorCount, &SupportingSurfaceTimeToImpactCondition::SetCompare);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<SupportingSurfaceTimeToImpactCondition>("timeToImpact", &SupportingSurfaceTimeToImpactCondition::SetTimeToImpact);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gSupportingSurfaceTimeToImpactConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108A9F20
	fight::ConditionFactory* CreateSupportingSurfaceTimeToImpactConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceTimeToImpactCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AA580
	void RegisterSupportingSurfaceTimeToImpactConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceTimeToImpactCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<SupportingSurfaceTimeToImpactCondition>;
	template class fight::PropertyFloatConstRange<SupportingSurfaceTimeToImpactCondition>;
	template class fight::ConditionFactoryTemplate<SupportingSurfaceTimeToImpactCondition>;
	template class fight::ConditionFactoryCasterTemplate<SupportingSurfaceTimeToImpactCondition>;

	extern fight::EnumEntry gCompareOperatorTable[];
	extern const int gCompareOperatorCount;

	fight::Property** gSupportingSurfaceNormalAngleConditionProperties;  // 0x113181AC

	// FUNCTION: ENGINE 0x108A9210
	bool SupportingSurfaceNormalAngleCondition::SetNormal(const math::Vector& newValue)
	{
		normal.x = newValue.x;
		normal.y = newValue.y;
		normal.z = newValue.z;
		return true;
	}

	// FUNCTION: ENGINE 0x108A9230
	bool SupportingSurfaceNormalAngleCondition::SetCompare(int newValue)
	{
		compare = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A9240
	bool SupportingSurfaceNormalAngleCondition::SetAngle(float newValue)
	{
		angle = newValue * 0.01745329238474369f;
		return true;
	}

	// FUNCTION: ENGINE 0x10809B50
	math::Vector SupportingSurfaceNormalAngleCondition::GetNormal() const
	{
		return normal;
	}

	// FUNCTION: ENGINE 0x10809B70
	int SupportingSurfaceNormalAngleCondition::GetCompare() const
	{
		return compare;
	}

	// FUNCTION: ENGINE 0x10809B80
	float SupportingSurfaceNormalAngleCondition::GetAngle() const
	{
		return angle;
	}

	// FUNCTION: ENGINE 0x108A9480
	fight::Property* SupportingSurfaceNormalAngleCondition::GetProperty(int index)
	{
		return gSupportingSurfaceNormalAngleConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108A9490
	void SupportingSurfaceNormalAngleCondition::ClearProperties()
	{
		fight::FreePropertyList(&gSupportingSurfaceNormalAngleConditionProperties);
	}

	// FUNCTION: ENGINE 0x108A94A0
	// ctor stores: [('mov', 'dword', 0, '0x10e79810'), ('movss', 'dword', 12, '0.0f'), ('movss', 'dword', 16, '1.0f'), ('movss', 'dword', 20, '0.0f'), ('movss', 'dword', 24, '0.0f'), ('mov', 'dword', 28, '0')]
	SupportingSurfaceNormalAngleCondition::SupportingSurfaceNormalAngleCondition() : fight::Condition(0), normal(0.0f, 1.0f, 0.0f), angle(0.0f), compare(0)
	{
	}

	// FUNCTION: ENGINE 0x10809CA0
	bool SupportingSurfaceNormalAngleCondition::Evaluate(int a, int b, int c, int d)
	{
		GameObjectHandle handle = GetObjectHandle((core::IRefCount*)c);
		GameObject* object = handle.Get();
		if (object == 0)
		{
			return false;
		}
		CharacterQueryCollisionStateMessage message;
		object->SendMessage(&message);
		const SupportingLimb::Support* support = message.support;
		if (support == 0)
		{
			return false;
		}
		math::Vector direction;
		direction.x = normal.x;
		direction.y = normal.y;
		direction.z = normal.z;
		direction.Normalize();
		float cosine = support->normal.z * direction.z + support->normal.y * direction.y + support->normal.x * direction.x;
		float measured = acosf(cosine);
		float value = angle;
		int op = compare;
		return fight::CompareFloats(op, &measured, &value);
	}

	// FUNCTION: ENGINE 0x108A94E0
	SupportingSurfaceNormalAngleCondition::~SupportingSurfaceNormalAngleCondition()
	{
	}

	// FUNCTION: ENGINE 0x108AA3A0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SupportingSurfaceNormalAngleCondition::RegisterProperties()
	{
		if (gSupportingSurfaceNormalAngleConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyVector<SupportingSurfaceNormalAngleCondition>("normal", &SupportingSurfaceNormalAngleCondition::SetNormal);
			properties[0] = property;
			property = new fight::PropertyEnumConstList<SupportingSurfaceNormalAngleCondition>("compare", gCompareOperatorTable, gCompareOperatorCount, &SupportingSurfaceNormalAngleCondition::SetCompare);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<SupportingSurfaceNormalAngleCondition>("angle", &SupportingSurfaceNormalAngleCondition::SetAngle);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gSupportingSurfaceNormalAngleConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108A9F60
	fight::ConditionFactory* CreateSupportingSurfaceNormalAngleConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceNormalAngleCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AA5E0
	void RegisterSupportingSurfaceNormalAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceNormalAngleCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<SupportingSurfaceNormalAngleCondition>;
	template class fight::PropertyFloatConstRange<SupportingSurfaceNormalAngleCondition>;
	template class fight::PropertyVector<SupportingSurfaceNormalAngleCondition>;
	template class fight::ConditionFactoryTemplate<SupportingSurfaceNormalAngleCondition>;
	template class fight::ConditionFactoryCasterTemplate<SupportingSurfaceNormalAngleCondition>;

	fight::Property** gSupportingSurfaceSupportingLimbConditionProperties;  // 0x113181A0

	// FUNCTION: ENGINE 0x108A91C0
	bool SupportingSurfaceSupportingLimbCondition::SetIsSupportingLimb(bool newValue)
	{
		isSupportingLimb = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A94F0
	bool SupportingSurfaceSupportingLimbCondition::SetSupportingLimb(const fight::Name& newValue)
	{
		supportingLimb = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10809AE0
	const fight::Name& SupportingSurfaceSupportingLimbCondition::GetSupportingLimb() const
	{
		return supportingLimb;
	}

	// FUNCTION: ENGINE 0x10809AF0
	bool SupportingSurfaceSupportingLimbCondition::GetIsSupportingLimb() const
	{
		return isSupportingLimb;
	}

	// FUNCTION: ENGINE 0x108A93E0
	fight::Property* SupportingSurfaceSupportingLimbCondition::GetProperty(int index)
	{
		return gSupportingSurfaceSupportingLimbConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108A93F0
	void SupportingSurfaceSupportingLimbCondition::ClearProperties()
	{
		fight::FreePropertyList(&gSupportingSurfaceSupportingLimbConditionProperties);
	}

	// FUNCTION: ENGINE 0x108A95B0
	// ctor stores: [('mov', 'dword', 0, '0x10e7983c'), ('mov', 'byte', 24, '1')]
	SupportingSurfaceSupportingLimbCondition::SupportingSurfaceSupportingLimbCondition() : fight::Condition(0), isSupportingLimb(1)
	{
	}

	// FUNCTION: ENGINE 0x1080A520
	bool SupportingSurfaceSupportingLimbCondition::Evaluate(int a, int b, int c, int d)
	{
		GameObjectHandle handle = GetObjectHandle((core::IRefCount*)c);
		GameObject* object = handle.Get();
		if (object == 0)
		{
			return false;
		}
		CharacterQueryCollisionStateMessage message;
		object->SendMessage(&message);
		const SupportingLimb::Support* support = message.support;
		if (support == 0)
		{
			return false;
		}
		unsigned __int64 hash = 0;
		if (support->limb != 0)
		{
			SupportingLimbDefinition* definition = support->limb->limbDef;
			if (definition != 0)
			{
				hash = definition->name.GetHash();
			}
		}
		bool match = hash == supportingLimb.GetHash();
		return match == isSupportingLimb;
	}

	// FUNCTION: ENGINE 0x108A95D0
	SupportingSurfaceSupportingLimbCondition::~SupportingSurfaceSupportingLimbCondition()
	{
	}

	// FUNCTION: ENGINE 0x108AA890
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SupportingSurfaceSupportingLimbCondition::RegisterProperties()
	{
		if (gSupportingSurfaceSupportingLimbConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyNameList<SupportingSurfaceSupportingLimbCondition>("supportingLimb", &SupportingSurfaceSupportingLimbCondition::SetSupportingLimb);
			properties[0] = property;
			property = new fight::PropertyBool<SupportingSurfaceSupportingLimbCondition>("isSupportingLimb", &SupportingSurfaceSupportingLimbCondition::SetIsSupportingLimb);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gSupportingSurfaceSupportingLimbConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108A9F00
	fight::ConditionFactory* CreateSupportingSurfaceSupportingLimbConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceSupportingLimbCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AA550
	void RegisterSupportingSurfaceSupportingLimbConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingSurfaceSupportingLimbCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyBool<SupportingSurfaceSupportingLimbCondition>;
	template class fight::PropertyNameList<SupportingSurfaceSupportingLimbCondition>;
	template class fight::ConditionFactoryTemplate<SupportingSurfaceSupportingLimbCondition>;
	template class fight::ConditionFactoryCasterTemplate<SupportingSurfaceSupportingLimbCondition>;

	fight::Property** gSupportingLimbIsActiveConditionProperties;  // 0x113181A8

	// FUNCTION: ENGINE 0x108A9200
	bool SupportingLimbIsActiveCondition::SetIsActive(bool newValue)
	{
		isActive = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108A9510
	bool SupportingLimbIsActiveCondition::SetSupportingLimb(const fight::Name& newValue)
	{
		supportingLimb = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x10809B30
	const fight::Name& SupportingLimbIsActiveCondition::GetSupportingLimb() const
	{
		return supportingLimb;
	}

	// FUNCTION: ENGINE 0x10809B40
	bool SupportingLimbIsActiveCondition::GetIsActive() const
	{
		return isActive;
	}

	// FUNCTION: ENGINE 0x108A9460
	fight::Property* SupportingLimbIsActiveCondition::GetProperty(int index)
	{
		return gSupportingLimbIsActiveConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108A9470
	void SupportingLimbIsActiveCondition::ClearProperties()
	{
		fight::FreePropertyList(&gSupportingLimbIsActiveConditionProperties);
	}

	// FUNCTION: ENGINE 0x108A9600
	// ctor stores: [('mov', 'dword', 0, '0x10e79868'), ('mov', 'byte', 24, '1')]
	SupportingLimbIsActiveCondition::SupportingLimbIsActiveCondition() : fight::Condition(0), isActive(1)
	{
	}

	// FUNCTION: ENGINE 0x1080A0A0
	bool SupportingLimbIsActiveCondition::Evaluate(int a, int b, int c, int d)
	{
		GameObjectHandle handle = GetObjectHandle((core::IRefCount*)c);
		GameObject* object = handle.Get();
		if (object == 0)
		{
			return false;
		}
		SupportingLimbGetActiveMessageConst message;
		object->PostMessage(&message);
		unsigned __int64 hash = 0;
		if (message.limb != 0 && message.limb->limbDef != 0)
		{
			hash = message.limb->limbDef->name.GetHash();
		}
		bool match = hash == supportingLimb.GetHash();
		return match == isActive;
	}

	// FUNCTION: ENGINE 0x108A9620
	SupportingLimbIsActiveCondition::~SupportingLimbIsActiveCondition()
	{
	}

	// FUNCTION: ENGINE 0x108AA940
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's
	void SupportingLimbIsActiveCondition::RegisterProperties()
	{
		if (gSupportingLimbIsActiveConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyNameList<SupportingLimbIsActiveCondition>("supportingLimb", &SupportingLimbIsActiveCondition::SetSupportingLimb);
			properties[0] = property;
			property = new fight::PropertyBool<SupportingLimbIsActiveCondition>("isActive", &SupportingLimbIsActiveCondition::SetIsActive);
			properties[1] = property;
			fight::RegisterPropertyList(properties, &gSupportingLimbIsActiveConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108A9F40
	fight::ConditionFactory* CreateSupportingLimbIsActiveConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingLimbIsActiveCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108AA5B0
	void RegisterSupportingLimbIsActiveConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<SupportingLimbIsActiveCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyBool<SupportingLimbIsActiveCondition>;
	template class fight::PropertyNameList<SupportingLimbIsActiveCondition>;
	template class fight::ConditionFactoryTemplate<SupportingLimbIsActiveCondition>;
	template class fight::ConditionFactoryCasterTemplate<SupportingLimbIsActiveCondition>;

	// FUNCTION: ENGINE 0x10809B90
	void RegisterSupportingSurfaceConditionFactories(fight::TrackRegistry* registry)
	{
		RegisterSupportingSurfaceConditionFactory(registry, "supportingSurface");
		RegisterSupportingSurfaceNormalAngleConditionFactory(registry, "supportingSurfaceNormalAngle");
		RegisterSupportingSurfaceVelocityAngleConditionFactory(registry, "supportingSurfaceVelocityAngle");
		RegisterSupportingLimbIsActiveConditionFactory(registry, "supportingLimbIsActive");
		RegisterSupportingSurfaceDistanceConditionFactory(registry, "supportingSurfaceDistance");
		RegisterSupportingSurfaceTimeToImpactConditionFactory(registry, "supportingSurfaceTimeToImpact");
		RegisterSupportingSurfaceSupportingLimbConditionFactory(registry, "supportingSurfaceSupportingLimb");
		RegisterSupportingSurfaceAgeConditionFactory(registry, "supportingSurfaceAge");
	}
}
