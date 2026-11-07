// proto::MissileSpawnerBehaviour (RTTI and reflection names; base proto::WeaponBehaviour) and the records around it:
// proto::MissileSpawnProfile (where a missile appears relative to the spawner), proto::MissileSpawnDrawSwap (a
// drawable and joint to show and spawn from) and the lists of them. A weapon that makes a game object from a template
// and shoots it as a missile. Unit 0x1046D330 - 0x1046FC30 (no assert path; the file name is a guess). The reflected
// names are original, the rest is guessed; the reflection, the construction and the destruction are reconstructed,
// the shooting is left to the engine.
#ifndef PROTO_BEHAVIOURS_MISSILESPAWNERBEHAVIOUR_H
#define PROTO_BEHAVIOURS_MISSILESPAWNERBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/engine/gameobject/gameobjectspawner.h"
#include "code/proto/behaviours/missilebehaviour.h"

namespace proto
{
	// Where a missile appears (RTTI proto::MissileSpawnProfile; 0x20 bytes)
	struct MissileSpawnProfile : public content::MetaLoadObject
	{
		// 0x1046DA40
		MissileSpawnProfile();
		// 0x1046DAC0 (the deleting destructor is 0x1046DAD0)
		virtual ~MissileSpawnProfile()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		math::Vector spawnPositionOffset;  // +8
		math::Vector spawnRotationOffset;  // +0x14
	};

	// A drawable to show when the spawner shoots and the joint it shoots from (RTTI proto::MissileSpawnDrawSwap; 0x28
	// bytes)
	struct MissileSpawnDrawSwap
	{
		// 0x1046D9C0
		MissileSpawnDrawSwap();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		core::Name<core::CaseSensitiveKey> drawable;  // +0
		core::Name<core::CaseSensitiveKey> spawnJoint;  // +8
		math::Vector spawnPositionOffset;  // +0x10
		math::Vector spawnRotationOffset;  // +0x1C
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::MissileSpawnDrawSwap>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	template<> class ArrayDynamicHelper<container::ArrayDynamic<proto::MissileSpawnDrawSwap, container::AllocatorNew> >
		: public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<proto::MissileSpawnDrawSwap, container::AllocatorNew> A;
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
	class MissileSpawnerBehaviour : public WeaponBehaviour
	{
	public:
		typedef container::ArrayDynamic<MissileSpawnDrawSwap, container::AllocatorNew> DrawSwapArray;

		// 0x1046F9F0
		explicit MissileSpawnerBehaviour(engine::GameObject* newOwner);
		// 0x1046FA50 (the deleting destructor is 0x1046FB70)
		virtual ~MissileSpawnerBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x1046D3F0): the clip starts full
		virtual void Slot1();
		// vftable slot 6 (0x1046D410)
		virtual void OnMessage(engine::Message* message);
		// vftable slot 8 (0x1046F060) / 10 (0x1046EE20) / 11 (0x1046E280), left to the engine
		virtual void Slot8(int a, int b, float c);
		virtual void Slot10(int unused);
		virtual void Slot11(int a);
		// vftable slot 12 (0x1046D420) / 13 (0x1046DB00)
		virtual AmmoProfileBase* GetAmmoProfile();
		virtual void SetAmmoProfile(AmmoProfileBase* profile);

		DrawSwapArray drawSwapList;  // +0x68
		// The word behind the array
		int unknown74;
		int unknown78;
		content::MetaObjectTemplate* missileTemplate;  // +0x7C
		MissileProfile* ammoProfile;  // +0x80
		MissileSpawnProfile* missileSpawnProfile;  // +0x84
	};
}

#endif
