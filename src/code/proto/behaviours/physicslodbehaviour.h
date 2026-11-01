// proto::PhysicsLODBehaviour (RTTI and reflection names; base engine::Behaviour) and its element class proto::PhysicsLOD:
// the physics objects an object can swap between ("physicsLODTable", each a named level of detail that refers to a
// physics object factory), the one it starts with ("initial") and two flags. Unit 0x102F1AA0 - 0x102F3900 (no assert
// path; the file name is a guess). The reflected names are original, the rest is guessed; the reflection, the
// construction and the destruction are reconstructed, the switching of the levels is left to the engine.
#ifndef PROTO_BEHAVIOURS_PHYSICSLODBEHAVIOUR_H
#define PROTO_BEHAVIOURS_PHYSICSLODBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"
#include "code/ravenphysics/context.h"
#include "code/proto/messages/physicsmessages.h"
#include "code/ravenphysics/physicsobjectfactory.h"

namespace proto
{
	struct SetPhysicsLODMessage;
	struct GetPhysicsLODMessage;
	struct GetPhysicsLODTableMessage;

	// One level of detail (RTTI proto::PhysicsLOD; 0x18 bytes): its name and the factory of the physics object
	class PhysicsLOD
	{
	public:
		// 0x102F1B50
		PhysicsLOD();
		// 0x102F2A10 / 0x102F2A40: the engine's copies leave the words around the name alone
		PhysicsLOD(const PhysicsLOD& other) : name(other.name), physicsObject(other.physicsObject)
		{
		}
		PhysicsLOD& operator=(const PhysicsLOD& other)
		{
			name = other.name;
			physicsObject = other.physicsObject;
			return *this;
		}
		// 0x102F1B80 (the deleting destructor is 0x102F1BE0)
		virtual ~PhysicsLOD();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		int unknown4;
		core::Name<core::CaseSensitiveKey> name;  // +8
		ravenphysics::AbstractPhysicsObjectFactory* physicsObject;  // +0x10
		int unknown14;
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::PhysicsLOD>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	template<> class ArrayDynamicHelper<container::ArrayDynamic<proto::PhysicsLOD, container::AllocatorNew> >
		: public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<proto::PhysicsLOD, container::AllocatorNew> A;
		typedef A::Element T;

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void* GetConst(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void Insert(void* array, int index, int unused)
		{
			A* a = (A*)array;
			if (a->Size() >= a->Capacity())
			{
				a->Reserve(a->Size() + 1);
			}
			T* position = a->begin + index;
			static T sDefault;
			a->Insert(position, 1, sDefault);
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

namespace proto
{
	class PhysicsLODBehaviour : public engine::Behaviour
	{
	public:
		typedef container::ArrayDynamic<PhysicsLOD, container::AllocatorNew> LodArray;

		// 0x102F35E0
		explicit PhysicsLODBehaviour(engine::GameObject* newOwner);
		// 0x102F3660 (the deleting destructor is 0x102F3750)
		virtual ~PhysicsLODBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x102F33D0): switches to the level the object starts with
		virtual void Slot1();
		// vftable slot 6 (0x102F3440)
		virtual void OnMessage(engine::Message* message);

		// 0x102F2C50: switches to the level a message names (left to the engine)
		void SwitchLOD(SetPhysicsLODMessage* message);
		// 0x102F2F80: switches to the level the object starts with
		void SwitchToInitial();
		// 0x102F2820 / 0x102F2540: answers the current level's name / the table of levels
		void GetCurrentLOD(GetPhysicsLODMessage* message);
		void GetTable(GetPhysicsLODTableMessage* message);

		LodArray physicsLODTable;  // +0xC
		unsigned char unknown18[8];
		core::Name<core::CaseSensitiveKey> initial;  // +0x20
		int currentLOD;  // +0x28
		int unknown2C;
		core::Name<core::CaseSensitiveKey> currentName;  // +0x30
		ravenphysics::ObjectHandle physicsObject;  // +0x38
		ravenphysics::ObjectHandle savedPhysicsObject;  // +0x3C
		bool saveInitialPhysicsObject;  // +0x40
		bool isNotAmbientVehicle;  // +0x41
	};
}

#endif
