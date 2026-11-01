// proto::HitEffectBehaviour (RTTI and reflection names; base engine::Behaviour) and the load objects around it:
// proto::AnalyseCollisionParams (the thresholds that decide when a collision makes an impact or slide effect),
// proto::MomentumDamageParams (the table that turns the momentum of a hit into damage) and its element class
// proto::MomentumEntry. Unit 0x10511200 - 0x10513420 (no assert path; the file name is a guess). The reflected names
// are original, the rest is guessed; the reflection, the construction, the destruction and the momentum table's lookup
// are reconstructed, the handling of the hit message is left to the engine.
#ifndef PROTO_BEHAVIOURS_HITEFFECTBEHAVIOUR_H
#define PROTO_BEHAVIOURS_HITEFFECTBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace proto
{
	// One step of the momentum table (RTTI proto::MomentumEntry; 0x18 bytes): the damage and the momentum at that step
	// and the name of the hit effect template it picks
	class MomentumEntry
	{
	public:
		// 0x10511680
		MomentumEntry();
		// 0x10511BD0 / 0x10511C10: the engine's copies leave the word behind the vftable alone
		MomentumEntry(const MomentumEntry& other) : damage(other.damage), momentum(other.momentum), effectTemplate(other.effectTemplate)
		{
		}
		MomentumEntry& operator=(const MomentumEntry& other)
		{
			damage = other.damage;
			momentum = other.momentum;
			effectTemplate = other.effectTemplate;
			return *this;
		}
		// 0x105116B0 (the deleting destructor is 0x105121B0)
		virtual ~MomentumEntry();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		int unknown4;
		float damage;  // +8
		float momentum;  // +0xC
		core::Name<core::CaseSensitiveKey> effectTemplate;  // +0x10
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::MomentumEntry>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	template<> class ArrayDynamicHelper<container::ArrayDynamic<proto::MomentumEntry, container::AllocatorNew> >
		: public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<proto::MomentumEntry, container::AllocatorNew> A;
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
	// The thresholds of the collision effects (RTTI proto::AnalyseCollisionParams; 0x2C bytes); the instance made last is
	// kept in gAnalyseCollisionParams
	class AnalyseCollisionParams : public content::MetaLoadObject
	{
	public:
		// 0x105115D0
		AnalyseCollisionParams();
		// 0x105113E0 (the deleting destructor is 0x10511650)
		virtual ~AnalyseCollisionParams();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		float impactThreshold;  // +8
		float impactMinNormalVelocity;  // +0xC
		unsigned int impactMinIntervalMilliseconds;  // +0x10
		float impactEffectScale;  // +0x14
		float slideThreshold;  // +0x18
		float slideMaxNormalVelocity;  // +0x1C
		float slideMinTangentialVelocity;  // +0x20
		float slideEffectScaleX;  // +0x24
		float slideEffectScaleY;  // +0x28
	};

	// 0x1126F6A0
	extern AnalyseCollisionParams* gAnalyseCollisionParams;

	// The momentum to damage table (RTTI proto::MomentumDamageParams; 0x14 bytes); the instance made last is kept in
	// gMomentumDamageParams
	class MomentumDamageParams : public content::MetaLoadObject
	{
	public:
		typedef container::ArrayDynamic<MomentumEntry, container::AllocatorNew> MomentumArray;

		// 0x10513240
		MomentumDamageParams();
		// 0x10513270 (the deleting destructor is 0x10513320)
		virtual ~MomentumDamageParams();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x105116C0: finds the step a momentum falls in and answers the damage between it and the step before; the entry
		MomentumEntry* Lookup(float value, float* damage);

		MomentumArray momentum;  // +8
		int unknown14;  // behind the array: its allocator word
	};

	// 0x1126F6A4
	extern MomentumDamageParams* gMomentumDamageParams;

	class HitEffectBehaviour : public engine::Behaviour
	{
	public:
		// 0x10511400
		explicit HitEffectBehaviour(engine::GameObject* newOwner);
		// 0x10511440 (the deleting destructor is 0x10511790)
		virtual ~HitEffectBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10511450)
		virtual void Slot1();
		// vftable slot 6 (0x105132C0)
		virtual void OnMessage(engine::Message* message);

		// 0x105125B0: handles the hit message (left to the engine)
		void OnHit(engine::Message* message);

		int unknownC;
	};
}

#endif
