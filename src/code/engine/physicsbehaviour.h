// engine::PhysicsBehaviour (RTTI and reflection names; bases engine::Behaviour and ravenphysics::BroadPhaseObjectNotifier
// at +0xC): keeps the physics object of a game object. The factories ("physicsObject", "physicsObjectFactory") make
// it, the per-part masses ("properties"), the override material and intersection properties, and three flags are
// reflected. Unit 0x10921620 - 0x10924AFE (path "..\..\..\code\engine\physics\behaviours\physicsbehaviour.cpp" in an
// assert). The reflected names are original; the rest is guessed. Only the reflection, its accessors and the
// element access of the "properties" array are reconstructed.
#ifndef ENGINE_PHYSICSBEHAVIOUR_H
#define ENGINE_PHYSICSBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/math/vector.h"
#include "code/ravenphysics/context.h"
#include "code/ravenphysics/material.h"
#include "code/ravenphysics/physicsobjectfactory.h"

namespace proto
{
	struct PartLookup;
}

namespace ravenphysics
{
	// RTTI ravenphysics::BroadPhaseObjectNotifier (one vftable pointer); the second base of the physics behaviour
	class BroadPhaseObjectNotifier
	{
	public:
		virtual ~BroadPhaseObjectNotifier();
	};
}

namespace engine
{
	class PhysicsBehaviour : public Behaviour, public ravenphysics::BroadPhaseObjectNotifier
	{
	public:
		// RTTI engine::PhysicsBehaviour::PhysicsProperties (struct, 0x10 bytes): the mass of the part of that name
		struct PhysicsProperties
		{
			// 0x109219D0 / 0x10923160
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x10922F20 / 0x10922F00 / 0x10923140: the engine's copies leave the word behind the mass alone
			PhysicsProperties() : mass(0.0f)
			{
			}
			PhysicsProperties(const PhysicsProperties& other) : objectName(other.objectName), mass(other.mass)
			{
			}
			PhysicsProperties& operator=(const PhysicsProperties& other)
			{
				objectName = other.objectName;
				mass = other.mass;
				return *this;
			}

			core::Name<core::CaseSensitiveKey> objectName;  // +0
			float mass;  // +8
			int unknownC;  // padding: the names are 8-byte aligned in the engine
		};

		typedef container::ArrayDynamic<PhysicsProperties, container::AllocatorNew> PropertiesArray;

		// The part the physics-to-pose blend factor is kept in (12 bytes, the factor twice and a zero; 0x108D4410 /
		// 0x108D4450 belong to another unit)
		struct BlendFactor
		{
			float Get() const;
			void Set(float value);

			float x;
			float y;
			float z;
		};

		// 0x10924520
		explicit PhysicsBehaviour(GameObject* newOwner);

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The accessors the reflection reaches the members through
		// 0x109219B0 / 0x10922C20
		ravenphysics::AbstractPhysicsObjectFactory* GetPhysicsObject() const;
		void SetPhysicsObject(ravenphysics::AbstractPhysicsObjectFactory* factory);
		// 0x109219C0 / 0x10922C40
		ravenphysics::AbstractPhysicsObjectFactory* GetPhysicsObjectFactory() const;
		void SetPhysicsObjectFactory(ravenphysics::AbstractPhysicsObjectFactory* factory);
		// 0x10921980 / 0x10921990
		float GetPhysicsToPoseBlendFactor() const;
		void SetPhysicsToPoseBlendFactor(float value);
		// 0x10921960 / 0x10921970: the property is obsolete (always true, ignores the value)
		bool GetAutoPoseSync() const;
		void SetAutoPoseSync(bool value);

		// vftable slot 3 (0x10923EE0)
		virtual void OnActiveChanged(bool active);

		// 0x10923380: puts the physics object where the owner is
		void UpdatePhysicsTransform();
		// 0x10923BF0: wakes the physics object or puts it to sleep, and tells the owner
		void SetAwake(bool awake);
		// 0x10923CC0: works out whether the object is awake and which updates the behaviour listens to
		void UpdateAwake();
		// 0x10921EA0: lets the physics object follow the animation (the collision objects are cleared and the mode is 1) or the
		// simulation (the mode is 2)
		void SetKeyframedCollision(bool keyframed);
		// 0x10924310: turns the behaviour on
		void Enable();

		ravenphysics::ObjectHandle physicsObjectHandle;  // +0x10
		ravenphysics::ObjectHandle unknown14;
		ravenphysics::AbstractPhysicsObjectFactory* physicsObject;  // +0x18
		ravenphysics::AbstractPhysicsObjectFactory* physicsObjectFactory;  // +0x1C
		BlendFactor physicsToPoseBlendFactor;  // +0x20
		PropertiesArray properties;  // +0x2C
		int unknown38;  // behind the array: its allocator word
		bool manualVelocities;  // +0x3C
		bool disablePhysicsObjectSelfCollisions;  // +0x3D
		Attribute<proto::PartLookup*>* drawable;  // +0x40
		ravenphysics::MaterialLoader* overrideMaterial;  // +0x44
		ravenphysics::IntersectionPropertiesLoader* overrideIntersectionProperties;  // +0x48
		bool preserveJointAnimation;  // +0x4C
		bool hasScale;  // +0x4D
		math::Vector scale;  // +0x50
		bool enabled;  // +0x5C
		bool unknown5D;
		bool unknown5E;
		int unknown60;
		int unknown64;
	};
}

namespace container
{
	template<> struct ArrayEraseInline<engine::PhysicsBehaviour::PhysicsProperties>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	// The element access of the "properties" array for its meta type: the default element is kept in a static of the helper
	template<> class ArrayDynamicHelper<engine::PhysicsBehaviour::PropertiesArray> : public ArrayDynamicHelperBase
	{
	public:
		typedef engine::PhysicsBehaviour::PropertiesArray A;
		typedef A::Element T;

		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
		virtual void* GetConst(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
		virtual void Insert(void* array, int index, int unused)
		{
			A* a = (A*)array;
			if (a->Size() >= a->Capacity())
			{
				a->Reserve(a->Size() + 1);
			}
			T* position = a->begin + index;
			a->Insert(position, Default());
		}
		virtual void Erase(void* array, int index, int unused)
		{
			A* a = (A*)array;
			a->Erase(a->begin + index);
		}
		virtual int Capacity(void* array)
		{
			return ((A*)array)->Capacity();
		}
		virtual void Expand(void* array, unsigned int count)
		{
			A* a = (A*)array;
			if (a->Capacity() == 0)
			{
				a->Allocate(count);
			}
			else if (count + a->Size() > a->Capacity())
			{
				a->Reserve(count + a->Size());
			}
		}
	};
}

#endif
