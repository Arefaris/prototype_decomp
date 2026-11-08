// proto::DisguiseConfig (RTTI and reflection names; a load object): how suspicious and how alarmed the people around
// the player get while he is disguised: the incident table (one entry per kind of incident), the tables that raise or
// lower the suspicion and the alert for a faction pair, the factions the player may be in the military bases as and
// the delay of the decrease. Unit 0x103D1150 - 0x103D6200 (no assert path; the file name is a guess). The reflected
// names are original, the rest is guessed.
#ifndef PROTO_DISGUISECONFIG_H
#define PROTO_DISGUISECONFIG_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/proto/faction.h"

namespace proto
{
	struct DisguiseConfig : public content::MetaLoadObject
	{
		// How an incident changes the suspicion (0x1C bytes)
		struct Incident
		{
			Incident(); //@0x103D12D0
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float increase;  // +0
			float decrease;
			float maximum;
			float maxFactor;
			bool useDistanceFactor;  // +0x10
			bool delaysDecrease;
			float increaseInSearch;  // +0x14
			float maximumInSearch;
		};

		// The suspicion a faction pair raises from low to high at least minPercent of the way (0x20 bytes)
		struct SuspicionIncrease
		{
			SuspicionIncrease() : suspicionLow(-5.0f), suspicionHigh(10.0f), minPercent(0.3f)
			{
			}
			SuspicionIncrease(Faction newDisguiseType, Faction newEnemyType, float newLow, float newHigh,
				float newMinPercent) : suspicionLow(newLow), suspicionHigh(newHigh), minPercent(newMinPercent),
				disguiseType(newDisguiseType), enemyType(newEnemyType)
			{
			}
			SuspicionIncrease(const SuspicionIncrease& other) : suspicionLow(other.suspicionLow),
				suspicionHigh(other.suspicionHigh), minPercent(other.minPercent), disguiseType(other.disguiseType),
				enemyType(other.enemyType)
			{
			}
			SuspicionIncrease& operator=(const SuspicionIncrease& other)
			{
				suspicionLow = other.suspicionLow;
				suspicionHigh = other.suspicionHigh;
				minPercent = other.minPercent;
				disguiseType.name = other.disguiseType.name;
				enemyType.name = other.enemyType.name;
				return *this;
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float suspicionLow;  // +0
			float suspicionHigh;
			float minPercent;
			int unknownC;
			Faction disguiseType;  // +0x10
			Faction enemyType;  // +0x18
		};

		// The suspicion a faction pair takes away (0x10 bytes)
		struct SuspicionDecrease
		{
			SuspicionDecrease() : suspicion(0.0f)
			{
			}
			SuspicionDecrease(Faction newDisguiseType, float newSuspicion) : suspicion(newSuspicion),
				disguiseType(newDisguiseType)
			{
			}
			SuspicionDecrease(const SuspicionDecrease& other) : suspicion(other.suspicion),
				disguiseType(other.disguiseType)
			{
			}
			SuspicionDecrease& operator=(const SuspicionDecrease& other)
			{
				suspicion = other.suspicion;
				disguiseType.name = other.disguiseType.name;
				return *this;
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float suspicion;  // +0
			int unknown4;
			Faction disguiseType;  // +8
		};

		// The alert a faction pair raises (0x18 bytes)
		struct AlertIncrease
		{
			AlertIncrease() : alert(0.0f), surroundingFunction(0.0f)
			{
			}
			AlertIncrease(Faction newDisguiseType, Faction newEnemyType, float newAlert) : alert(newAlert),
				surroundingFunction(0.0f), disguiseType(newDisguiseType), enemyType(newEnemyType)
			{
			}
			AlertIncrease(const AlertIncrease& other) : alert(other.alert),
				surroundingFunction(other.surroundingFunction), disguiseType(other.disguiseType),
				enemyType(other.enemyType)
			{
			}
			AlertIncrease& operator=(const AlertIncrease& other)
			{
				alert = other.alert;
				surroundingFunction = other.surroundingFunction;
				disguiseType.name = other.disguiseType.name;
				enemyType.name = other.enemyType.name;
				return *this;
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float alert;  // +0
			float surroundingFunction;
			Faction disguiseType;  // +8
			Faction enemyType;  // +0x10
		};

		// The alert a faction pair takes away (0x10 bytes)
		struct AlertDecrease
		{
			AlertDecrease() : alert(0.0f), surroundingFunction(0.0f),
				disguiseType(core::Name<core::CaseSensitiveKey>((const char*)0, 1))
			{
			}
			AlertDecrease(Faction newDisguiseType, float newAlert) : alert(newAlert), surroundingFunction(0.0f),
				disguiseType(newDisguiseType)
			{
			}
			AlertDecrease(const AlertDecrease& other) : alert(other.alert),
				surroundingFunction(other.surroundingFunction), disguiseType(other.disguiseType)
			{
			}
			AlertDecrease& operator=(const AlertDecrease& other)
			{
				alert = other.alert;
				surroundingFunction = other.surroundingFunction;
				disguiseType.name = other.disguiseType.name;
				return *this;
			}
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			float alert;  // +0
			float surroundingFunction;
			Faction disguiseType;  // +8
		};

		typedef container::ArrayDynamic<SuspicionIncrease, container::AllocatorNew> SuspicionIncreaseArray;
		typedef container::ArrayDynamic<SuspicionDecrease, container::AllocatorNew> SuspicionDecreaseArray;
		typedef container::ArrayDynamic<AlertIncrease, container::AllocatorNew> AlertIncreaseArray;
		typedef container::ArrayDynamic<AlertDecrease, container::AllocatorNew> AlertDecreaseArray;
		typedef container::ArrayDynamic<Faction, container::AllocatorNew> FactionArray;

		// 0x103D5A90
		DisguiseConfig();
		// 0x103D5CF0 (deleting destructor 0x103D61D0)
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x103D1850: whether the faction is one the player may be in the bases as
		bool IsAllowedInBase(const core::Name<core::CaseSensitiveKey>& name);
		// 0x103D4F50, 0x103D5130, 0x103D5260 and 0x103D5420 (name guesses): change the entry of the faction pair, or
		// add one when there is room
		void SetSuspicionIncrease(Faction disguiseType, Faction enemyType, float low, float high, float minPercent);
		void SetSuspicionDecrease(Faction disguiseType, float suspicion);
		void SetAlertIncrease(Faction disguiseType, Faction enemyType, float alert);
		void SetAlertDecrease(Faction disguiseType, float alert);

		Incident incidentAttack;  // +8
		Incident incidentFaction;
		Incident incidentConsume;
		Incident incidentShoveSoldier;
		Incident incidentSmallJump;
		Incident incidentLanding;
		Incident incidentShapeshift;
		Incident incidentHolding;
		Incident incidentSprinting;
		Incident incidentWallrunning;
		Incident incidentClimbing;
		Incident incidentInsideBase;
		Incident incidentInsidePerimeter;
		Incident incidentFriendlyFire;
		Incident incidentFriendlyFireDamage;
		Incident incidentCivilianFire;
		Incident incidentInfectedAlly;
		Incident incidentMilitaryAlly;
		Incident incidentLanding2;  // +0x200
		SuspicionIncreaseArray suspicionIncreases;  // +0x21C
		int unknown228;
		SuspicionDecreaseArray suspicionDecreases;  // +0x22C
		int unknown238;
		AlertIncreaseArray alertIncreases;  // +0x23C
		int unknown248;
		AlertDecreaseArray alertDecreases;  // +0x24C
		int unknown258;
		FactionArray allowedInBase;  // +0x25C
		int unknown268;
		bool useDistance;  // +0x26C
		float decreaseDelay;  // +0x270
	};
}

// The engine erases these elements with a call of AssignRange
namespace container
{
	template<> struct ArrayEraseInline<proto::DisguiseConfig::SuspicionIncrease>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::DisguiseConfig::SuspicionDecrease>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::DisguiseConfig::AlertIncrease>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::DisguiseConfig::AlertDecrease>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::Faction>
	{
		enum
		{
			value = 0
		};
	};
}

// The element access of the reflected arrays of this unit: the default element is kept in a static of the helper
// (Default); the insertion copies it with the count form (COUNT) or the single form of Insert
#define PROTO_DISGUISE_HELPER_BODY(ElementType, insertCall) namespace content { 	template<> class ArrayDynamicHelper<container::ArrayDynamic<ElementType, container::AllocatorNew> > 		: public ArrayDynamicHelperBase 	{ 	public: 		typedef container::ArrayDynamic<ElementType, container::AllocatorNew> A; 		typedef A::Element T; 		static T& Default() 		{ 			static T sDefault; 			return sDefault; 		} 		virtual int Size(void* array) 		{ 			return ((A*)array)->Size(); 		} 		virtual void* Get(void* array, int index) 		{ 			return ((A*)array)->begin + index; 		} 		virtual void* GetConst(void* array, int index) 		{ 			return ((A*)array)->begin + index; 		} 		virtual void Insert(void* array, int index, int unused) 		{ 			A* a = (A*)array; 			if (a->Size() >= a->Capacity()) 			{ 				a->Reserve(a->Size() + 1); 			} 			T* position = a->begin + index; 			insertCall; 		} 		virtual void Erase(void* array, int index, int unused) 		{ 			A* a = (A*)array; 			a->Erase(a->begin + index); 		} 		virtual int Capacity(void* array) 		{ 			return ((A*)array)->Capacity(); 		} 		virtual void Expand(void* array, unsigned int count) 		{ 			A* a = (A*)array; 			if (a->Capacity() == 0) 			{ 				a->Allocate(count); 			} 			else if (count + a->Size() > a->Capacity()) 			{ 				a->Reserve(count + a->Size()); 			} 		} 	}; }

PROTO_DISGUISE_HELPER_BODY(proto::DisguiseConfig::SuspicionIncrease, a->Insert(position, 1, Default()))
PROTO_DISGUISE_HELPER_BODY(proto::DisguiseConfig::SuspicionDecrease, a->Insert(position, Default()))
PROTO_DISGUISE_HELPER_BODY(proto::DisguiseConfig::AlertIncrease, a->Insert(position, 1, Default()))
PROTO_DISGUISE_HELPER_BODY(proto::DisguiseConfig::AlertDecrease, a->Insert(position, 1, Default()))
PROTO_DISGUISE_HELPER_BODY(proto::Faction, a->Insert(position, Default()))

#endif
