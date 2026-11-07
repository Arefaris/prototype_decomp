// proto::ShoulderConFixupBehaviour (RTTI and reflection names; base engine::Behaviour) with the load object
// proto::ShoulderConFixupProperties and its element proto::ShoulderConFixupPropertiesJointPair: copies the pose of the
// shoulder joints of its object's drawable onto the shoulder constraint joints each update while the fixup is on.
// Unit 0x10076370 - 0x10077830 (no assert path; the file name is a guess). The reflected names are original, the rest
// is guessed.
#ifndef PROTO_BEHAVIOURS_SHOULDERCONFIXUPBEHAVIOUR_H
#define PROTO_BEHAVIOURS_SHOULDERCONFIXUPBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"

namespace proto
{
	// The names of a shoulder joint and of its constraint joint (reflected: shoulderJointName, shoulderConJointName)
	class ShoulderConFixupPropertiesJointPair
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x100767D0
		ShoulderConFixupPropertiesJointPair();

		core::Name<core::CaseSensitiveKey> shoulderJointName;  // +0
		core::Name<core::CaseSensitiveKey> shoulderConJointName;  // +8
	};

	// The joints the fixup works on (reflected: jointPairs)
	class ShoulderConFixupProperties : public content::MetaLoadObject
	{
	public:
		typedef container::ArrayDynamic<ShoulderConFixupPropertiesJointPair, container::AllocatorNew> JointPairArray;

		// 0x10077700
		ShoulderConFixupProperties();
		// 0x10077730 (deleting destructor 0x10077810)
		virtual ~ShoulderConFixupProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		JointPairArray jointPairs;  // +8
		int unknown14;
	};
}

namespace container
{
	// The engine moves the elements down in Erase with a call of CopyRangeEnd
	template<> struct ArrayEraseInline<proto::ShoulderConFixupPropertiesJointPair>
	{
		enum
		{
			value = 4
		};
	};
}

namespace proto
{
	// The indices of the parts a joint pair names (0xFFFF while unresolved)
	struct ShoulderConFixupPartIndices
	{
		ShoulderConFixupPartIndices();

		int shoulderJoint;  // +0
		int shoulderConJoint;  // +4
	};

	class ShoulderConFixupBehaviour : public engine::Behaviour
	{
	public:
		// 0x10076870
		explicit ShoulderConFixupBehaviour(engine::GameObject* newOwner);
		// 0x10076900 (deleting destructor 0x10076E90)
		virtual ~ShoulderConFixupBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x10076240
		bool GetEnabled() const
		{
			return enabled;
		}
		// 0x10076930
		void SetEnabled(bool newEnabled);
		// 0x10076460: listens to the update while the fixup is on
		void UpdateListening();
		// 0x10076950
		void Reset();
		// 0x10076960
		void AddEnabled(bool add);
		// 0x10076EC0: finds the parts the joint names of the properties give
		void FindParts();

		// vftable slots 1 (0x10076F40), 4 (0x10076990) and 6 (0x10076F50)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		engine::BaseAttribute* drawable;  // +0xC (the drawable attribute of the object)
		ShoulderConFixupProperties* properties;  // +0x10
		ShoulderConFixupPartIndices parts[2];  // +0x14
		int enableCount;  // +0x24
		bool enabled;  // +0x28
		bool ragdollEnabled;  // +0x29
	};
}

namespace content
{
	// The element access of the properties' joint pair array: the engine's insertion makes room with the count version of
	// Insert
	template<> class ArrayDynamicHelper<proto::ShoulderConFixupProperties::JointPairArray> : public ArrayDynamicHelperBase
	{
	public:
		typedef proto::ShoulderConFixupProperties::JointPairArray A;
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

#endif
