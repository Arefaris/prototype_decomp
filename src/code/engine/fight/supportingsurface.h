// The fight conditions that ask a character about its supporting surface and limb (units 0x10809A40 - 0x1080A600 and 0x108A9100 - 0x108AAC50)
#ifndef ENGINE_FIGHT_SUPPORTINGSURFACE_H
#define ENGINE_FIGHT_SUPPORTINGSURFACE_H

#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/engine/physics/supportinglimb.h"
#include "code/math/vector.h"
#include "code/math/worldbounds.h"

namespace math
{
	// 0x11283234: the zero vector
	extern const Vector kZeroVector;
}

namespace fight
{
	// 0x1009E120 (another unit): compares two floats with one of the compare operators (0 less, 1 less or equal, 2
	// equal, 3 not equal, 4 greater or equal, 5 greater): lhs op rhs
	bool CompareFloats(int op, const float* lhs, const float* rhs);
}

namespace engine
{
	// RTTI: engine::CharacterQueryCollisionStateMessage (a character answers with its current support, null when it
	// has none)
	struct CharacterQueryCollisionStateMessage : public IntrusiveMessage
	{
		CharacterQueryCollisionStateMessage() : IntrusiveMessage(0x10, 2)
		{
			support = 0;
		}
		virtual ~CharacterQueryCollisionStateMessage()
		{
		}

		const SupportingLimb::Support* support;
	};

	// RTTI: engine::SupportingLimbGetActiveMessageConst (a character answers with its active supporting limb)
	struct SupportingLimbGetActiveMessageConst : public NonintrusiveMessage
	{
		SupportingLimbGetActiveMessageConst() : NonintrusiveMessage(0x11, 4)
		{
			limb = 0;
		}
		virtual ~SupportingLimbGetActiveMessageConst()
		{
		}

		const SupportingLimb* limb;
	};

	// 0x107FC7A0 (another unit): the handle of the game object an owner pointer stands for
	GameObjectHandle GetObjectHandle(core::IRefCount* object);

	// 0x107F19D0 (another unit): the velocity of an object (type 0 linear, 1 angular), false when the
	// type is unknown
	bool GetObjectVelocity(GameObject* object, int type, math::Vector* velocity);

	// RTTI: engine::SupportingSurfaceAgeCondition (10 vftable slots, 0x14 bytes)
	class SupportingSurfaceAgeCondition : public fight::Condition
	{
	public:
		// 0x108A9280
		SupportingSurfaceAgeCondition();
		virtual ~SupportingSurfaceAgeCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1080A600)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties read
		int GetCompare() const;
		float GetAge() const;

		// The members the properties write
		bool SetCompare(int value);
		bool SetAge(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float age;  // +0xC
		int compare;  // +0x10
	};

	extern fight::Property** gSupportingSurfaceAgeConditionProperties;
	// 0x108A9E80
	// 0x108AA490
	fight::ConditionFactory* CreateSupportingSurfaceAgeConditionFactory(const char* name);

	// RTTI: engine::SupportingSurfaceCondition (10 vftable slots, 0x10 bytes)
	class SupportingSurfaceCondition : public fight::Condition
	{
	public:
		// 0x108A92E0
		SupportingSurfaceCondition();
		virtual ~SupportingSurfaceCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x10809C00)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties read
		bool GetOnSupportingSurface() const;

		// The members the properties write
		bool SetOnSupportingSurface(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		bool onSupportingSurface;  // +0xC
	};

	extern fight::Property** gSupportingSurfaceConditionProperties;
	// 0x108A9EA0
	// 0x108AA4C0
	fight::ConditionFactory* CreateSupportingSurfaceConditionFactory(const char* name);

	// RTTI: engine::SupportingSurfaceVelocityAngleCondition (10 vftable slots, 0x24 bytes)
	class SupportingSurfaceVelocityAngleCondition : public fight::Condition
	{
	public:
		// 0x108A9330
		SupportingSurfaceVelocityAngleCondition();
		virtual ~SupportingSurfaceVelocityAngleCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x10809DA0)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties read
		int GetVelocityType() const;
		math::Vector GetZeroVector() const;
		float GetAngle() const;
		float GetArc() const;

		// The members the properties write
		bool SetVelocityType(int value);
		bool SetZeroVector(const math::Vector& value);
		bool SetAngle(float value);
		bool SetArc(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		math::Vector zeroVector;  // +0xC
		float angle;  // +0x18
		float arc;  // +0x1C
		int velocityType;  // +0x20
	};

	extern fight::Property** gSupportingSurfaceVelocityAngleConditionProperties;
	// 0x108A9EC0
	// 0x108AA4F0
	fight::ConditionFactory* CreateSupportingSurfaceVelocityAngleConditionFactory(const char* name);

	// RTTI: engine::SupportingSurfaceDistanceCondition (10 vftable slots, 0x14 bytes)
	class SupportingSurfaceDistanceCondition : public fight::Condition
	{
	public:
		// 0x108A93A0
		SupportingSurfaceDistanceCondition();
		virtual ~SupportingSurfaceDistanceCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1080A170)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties read
		int GetCompare() const;
		float GetDistance() const;

		// The members the properties write
		bool SetCompare(int value);
		bool SetDistance(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float distance;  // +0xC
		int compare;  // +0x10
	};

	extern fight::Property** gSupportingSurfaceDistanceConditionProperties;
	// 0x108A9EE0
	// 0x108AA520
	fight::ConditionFactory* CreateSupportingSurfaceDistanceConditionFactory(const char* name);

	// RTTI: engine::SupportingSurfaceTimeToImpactCondition (10 vftable slots, 0x18 bytes)
	class SupportingSurfaceTimeToImpactCondition : public fight::Condition
	{
	public:
		// 0x108A9420
		SupportingSurfaceTimeToImpactCondition();
		virtual ~SupportingSurfaceTimeToImpactCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1080A290)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties read
		int GetVelocityType() const;
		int GetCompare() const;
		float GetTimeToImpact() const;

		// The members the properties write
		bool SetVelocityType(int value);
		bool SetCompare(int value);
		bool SetTimeToImpact(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float timeToImpact;  // +0xC
		int compare;  // +0x10
		int velocityType;  // +0x14
	};

	extern fight::Property** gSupportingSurfaceTimeToImpactConditionProperties;
	// 0x108A9F20
	// 0x108AA580
	fight::ConditionFactory* CreateSupportingSurfaceTimeToImpactConditionFactory(const char* name);

	// RTTI: engine::SupportingSurfaceNormalAngleCondition (10 vftable slots, 0x20 bytes)
	class SupportingSurfaceNormalAngleCondition : public fight::Condition
	{
	public:
		// 0x108A94A0
		SupportingSurfaceNormalAngleCondition();
		virtual ~SupportingSurfaceNormalAngleCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x10809CA0)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties read
		math::Vector GetNormal() const;
		int GetCompare() const;
		float GetAngle() const;

		// The members the properties write
		bool SetNormal(const math::Vector& value);
		bool SetCompare(int value);
		bool SetAngle(float value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		math::Vector normal;  // +0xC
		float angle;  // +0x18
		int compare;  // +0x1C
	};

	extern fight::Property** gSupportingSurfaceNormalAngleConditionProperties;
	// 0x108A9F60
	// 0x108AA5E0
	fight::ConditionFactory* CreateSupportingSurfaceNormalAngleConditionFactory(const char* name);

	// RTTI: engine::SupportingSurfaceSupportingLimbCondition (10 vftable slots, 0x20 bytes)
	class SupportingSurfaceSupportingLimbCondition : public fight::Condition
	{
	public:
		// 0x108A95B0
		SupportingSurfaceSupportingLimbCondition();
		virtual ~SupportingSurfaceSupportingLimbCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1080A520)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties read
		const fight::Name& GetSupportingLimb() const;
		bool GetIsSupportingLimb() const;

		// The members the properties write
		bool SetSupportingLimb(const fight::Name& value);
		bool SetIsSupportingLimb(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		int unknownc;
		fight::Name supportingLimb;  // +0x10
		bool isSupportingLimb;  // +0x18
		int unknown1c;
	};

	extern fight::Property** gSupportingSurfaceSupportingLimbConditionProperties;
	// 0x108A9F00
	// 0x108AA550
	fight::ConditionFactory* CreateSupportingSurfaceSupportingLimbConditionFactory(const char* name);

	// RTTI: engine::SupportingLimbIsActiveCondition (10 vftable slots, 0x20 bytes)
	class SupportingLimbIsActiveCondition : public fight::Condition
	{
	public:
		// 0x108A9600
		SupportingLimbIsActiveCondition();
		virtual ~SupportingLimbIsActiveCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1080A0A0)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties read
		const fight::Name& GetSupportingLimb() const;
		bool GetIsActive() const;

		// The members the properties write
		bool SetSupportingLimb(const fight::Name& value);
		bool SetIsActive(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		int unknownc;
		fight::Name supportingLimb;  // +0x10
		bool isActive;  // +0x18
		int unknown1c;
	};

	extern fight::Property** gSupportingLimbIsActiveConditionProperties;
	// 0x108A9F40
	// 0x108AA5B0
	fight::ConditionFactory* CreateSupportingLimbIsActiveConditionFactory(const char* name);

	// 0x10809B90: registers the eight conditions under their names
	void RegisterSupportingSurfaceConditionFactories(fight::TrackRegistry* registry);
}

#endif
