// proto::IKBehaviour (RTTI and reflection names; base engine::Behaviour) with its two element structs
// proto::IKSupportingLimbInfo and proto::IKLimbInfo: the inverse kinematics of a character's limbs: which supporting
// limbs fix the body to the surface (balance root) and which limbs follow it. Unit 0x10071000 - 0x10075450 (no
// assert path; the file name is a guess). The reflected names are original, the rest is guessed; only the
// reflection and the elements' default values are reconstructed.
#ifndef PROTO_BEHAVIOURS_IKBEHAVIOUR_H
#define PROTO_BEHAVIOURS_IKBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/proto/fightitems/motion/motionmessages3.h"
#include "code/engine/message.h"

namespace engine
{
	namespace driving
	{
		extern const float gOne;
		extern const float gHalf;
		extern const float gTwo;
	}
}

namespace proto
{
	// A limb that follows the surface (RTTI proto::IKLimbInfo; 0x20 bytes)
	struct IKLimbInfo
	{
		// 0x10071830
		IKLimbInfo();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> limbName;  // +0
		bool enabled;  // +8
		bool surfaceFixup;  // +9
		bool endEffectorRotation;  // +0xA
		bool endEffectorFollowSurfaceNormal;  // +0xB
		float velocity;  // +0xC
		float positionOffsetMin;  // +0x10
		float positionOffsetMax;  // +0x14
		float surfaceNormalAngularVelocity;  // +0x18
		float surfaceNormalMaxAngle;  // +0x1C
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::IKLimbInfo>
	{
		enum
		{
			value = 0
		};
	};
}

namespace proto
{
	// The word behind an array that the engine's elements keep (the allocator object of the array, 16 bytes with the
	// array's pointers): a copy of the element does not copy it
	struct ArrayPad
	{
		ArrayPad()
		{
		}
		ArrayPad(const ArrayPad& other)
		{
		}
		ArrayPad& operator=(const ArrayPad& other)
		{
			return *this;
		}

		int unused;
	};

	// A supporting limb (RTTI proto::IKSupportingLimbInfo; 0x38 bytes)
	struct __declspec(align(8)) IKSupportingLimbInfo
	{
		typedef container::ArrayDynamic<IKLimbInfo, container::AllocatorNew> LimbArray;

		// 0x10074B60
		IKSupportingLimbInfo();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> supportingLimbName;  // +0
		bool enabled;  // +8
		bool surfaceFixup;  // +9
		float balanceRootVelocity;  // +0xC
		float balanceRootCorrectionFraction;  // +0x10
		float balanceRootPositionOffsetMin;  // +0x14
		float balanceRootPositionOffsetMax;  // +0x18
		float balanceRootDistanceToMinLimb;  // +0x1C
		float balanceRootDistanceToMaxLimb;  // +0x20
		LimbArray ikLimbInfoList;  // +0x24
		ArrayPad unknown30;
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::IKSupportingLimbInfo>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	// The element access of the limb arrays: the engine's insertion makes room with the count version of Insert
	template<> class ArrayDynamicHelper<proto::IKSupportingLimbInfo::LimbArray> : public ArrayDynamicHelperBase
	{
	public:
		typedef proto::IKSupportingLimbInfo::LimbArray A;
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
	// The query for the state of the surface fixup (id 0 of the IK messages; the engine's name for it is not known): the
	// behaviour answers in enabled
	struct IKSurfaceFixupQueryMessage : public IKMessage
	{
		IKSurfaceFixupQueryMessage() : IKMessage(0), enabled(false)
		{
		}

		bool enabled;  // +0xC
	};

	class IKBehaviour : public engine::Behaviour
	{
	public:
		typedef container::ArrayDynamic<IKSupportingLimbInfo, container::AllocatorNew> SupportingLimbArray;

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 5 (0x10071150): answers the query message of type 0xF, id 0xB with true
		virtual void OnPostedMessage(engine::Message* message);
		// vftable slot 6 (0x10071B50)
		virtual void OnMessage(engine::Message* message);

		// 0x10071950 (name guess): forgets the pose of the limbs
		void ResetPose();
		// 0x10071110 / 0x10071130 (name guesses): answers whether the surface fixup is on / turns it on or off
		void GetSurfaceFixupEnabled(IKSurfaceFixupQueryMessage* message);
		void SetSurfaceFixupEnabled(SetIKSurfaceFixupEnabledMessage* message);

		unsigned char unknownC[4];
		int surfaceFixup;  // +0x10
		unsigned int balanceRootJointIndex;  // +0x14
		SupportingLimbArray ikSupportingLimbInfoList;  // +0x18
	};
}

namespace content
{
	template<> class ArrayDynamicHelper<proto::IKBehaviour::SupportingLimbArray> : public ArrayDynamicHelperBase
	{
	public:
		typedef proto::IKBehaviour::SupportingLimbArray A;
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
