// proto::TargetableBehaviour (RTTI and reflection names; base engine::Behaviour): makes an object a target of the
// automatic and the lock-on targeting. It says which class of target the object is (targetClass), how far from its
// centre it can be targeted (targetRadius, lineOfSightRadius) and where on the object the target points lie (the
// targetPoints, each with the kinds of targeting it takes). The behaviour keeps a list of all targetable behaviours and a
// list of the targeters that aim at it. proto::PropTargetableByAIBehaviour adds the registration of the object with the
// AI system. Unit 0x102B1280 - 0x102B4500 (no assert path; the file name is a guess). The reflected names are original,
// the rest is guessed; the reflection, the construction and the lists are reconstructed.
#ifndef PROTO_BEHAVIOURS_TARGETABLEBEHAVIOUR_H
#define PROTO_BEHAVIOURS_TARGETABLEBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/container/doublelist.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/math/vector.h"
#include "code/proto/autotargetprioritylist.h"
#include "code/proto/fightitems/ai/aicodemessages.h"

namespace proto
{
	// RTTI proto::RegisterAIMsg: tells the object's AI behaviours to register with or leave the AI system (name of the
	// member guessed)
	struct RegisterAIMsg : public AIMessage
	{
		explicit RegisterAIMsg(bool newRegister) : AIMessage(0), registerObject(newRegister)
		{
		}
		virtual ~RegisterAIMsg()
		{
		}

		bool registerObject;  // +0xC
	};

	class TargetableBehaviour : public engine::Behaviour
	{
	public:
		// One place on the object a targeter can aim at (RTTI proto::TargetableBehaviour::TargetPoint; 0x20 bytes)
		struct TargetPoint
		{
			// 0x102B1AE0
			TargetPoint();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x102B1570 / 0x102B15B0: whether a kind of targeting is set, and sets or clears one
			bool TestFilter(unsigned int filter) const;
			void SetFilter(unsigned int filter, bool on);

			// The kinds of targeting the point takes, each a bit of the filters (0x102B1980 - 0x102B1A80)
			bool GetTargetFilterLockOn() const;
			void SetTargetFilterLockOn(bool on);
			bool GetTargetFilterAttackMelee() const;
			void SetTargetFilterAttackMelee(bool on);
			bool GetTargetFilterAttackRanged() const;
			void SetTargetFilterAttackRanged(bool on);
			bool GetTargetFilterGrab() const;
			void SetTargetFilterGrab(bool on);
			bool GetTargetFilterFeet() const;
			void SetTargetFilterFeet(bool on);
			bool GetTargetFilterAlertObject() const;
			void SetTargetFilterAlertObject(bool on);

			int jointIndex;  // +0x0 (0xFFFF: none)
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> jointName;  // +0x8
			math::Vector offset;  // +0x10
			unsigned int filters;  // +0x1C
		};

		// A targeter that aims at the object (a link of the list at +0x44; the object is the targeted one)
		struct Targeter
		{
			engine::GameObject* target;
			Targeter* next;
		};

		typedef container::ArrayDynamic<TargetPoint, container::AllocatorNew> TargetPointArray;

		// 0x102B4030 (the destructor is 0x102B40F0, the deleting destructor 0x102B41E0)
		explicit TargetableBehaviour(engine::GameObject* newOwner);
		virtual ~TargetableBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1, 3 and 6 (0x102B3970, 0x102B1B20, 0x102B3990)
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void OnMessage(engine::Message* message);

		// 0x102B1610 / 0x102B1680 / 0x102B16F0: puts a chain of targeters on the list, takes one off, empties the list
		bool AddTargeters(Targeter* targeter);
		bool RemoveTargeter(Targeter* targeter);
		void ClearTargeters();
		// 0x102B15E0 / 0x102B15F0: whether the root target takes no kind of targeting at all
		bool GetRootTargetFilterClear() const;
		void SetRootTargetFilterClear(bool clear);
		// 0x102B1B50: starts over with the targeters of the class of the object
		void ResetTargeters();
		// 0x102B4450 / 0x102B4480: puts the behaviour on the list of all targetable behaviours, takes it off again
		static void AddToAll(TargetableBehaviour* behaviour);
		// 0x102B43B0 / 0x102B43C0 (names guessed): the first and the end position of the list of all targetable behaviours
		static void GetAllBegin(container::DoubleListBase::Node** position);
		static container::DoubleListBase::Node** GetAllEnd(container::DoubleListBase::Node** position);
		static void RemoveFromAll(TargetableBehaviour* behaviour);
		// 0x102B24F0 (name guess): builds the target points from the object's drawable
		void RebuildTargetPoints();
		// 0x102B1E60: tells what the object can be targeted as (the message with id 2)
		void GetTargetableInfo(GetTargetableInfoMessage* message);
		// 0x102B1EC0: hands the targeters over to another object (the message with id 9; none: they are dropped)
		void TransferTargetLocks(engine::GameObject* newTarget);
		// 0x102B25A0 / 0x102B2B40 (not reconstructed; names guessed): the messages with ids 0 and 1 find a target point
		void HandleTargetPointMessage0(engine::Message* message);
		void HandleTargetPointMessage1(engine::Message* message);

		bool isTargetable;  // +0xC
		bool canCauseStrikeTeamCall;  // +0xD
		bool targetableEvenWhenAttached;  // +0xE
		bool targetableWhenAttachedToTargeter;  // +0xF
		int targetClass;  // +0x10
		int currentTargetClass;  // +0x14
		float targetRadius;  // +0x18
		float lineOfSightRadius;  // +0x1C
		int rootTargetFilter;  // +0x20 (-1: all kinds of targeting)
		math::Vector rootTargetOffset;  // +0x24
		TargetPointArray targetPoints;  // +0x30
		int unknown3C;
		unsigned int combinedFilters;  // +0x40 (the point filters and what is left of the root filter)
		Targeter* firstTargeter;  // +0x44
		Targeter* lastTargeter;  // +0x48

		// A node of the list of all targetable behaviours
		struct Node : public container::DoubleListBase::Node
		{
			TargetableBehaviour* behaviour;
		};
		// 0x1125B114
		static container::DoubleListBase sAll;
	};

	// proto::PropTargetableByAIBehaviour (RTTI and reflection names; base proto::TargetableBehaviour): tells the AI system
	// about the object while the object has a name for it to know
	class PropTargetableByAIBehaviour : public TargetableBehaviour
	{
	public:
		// 0x102B12C0 (the destructor is 0x102B1300, the deleting destructor 0x102B13E0)
		explicit PropTargetableByAIBehaviour(engine::GameObject* newOwner);
		virtual ~PropTargetableByAIBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1 and 6 (0x102B1410, 0x102B1330)
		virtual void Slot1();
		virtual void OnMessage(engine::Message* message);

		bool registered;  // +0x4C
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::TargetableBehaviour::TargetPoint>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	template<> class ArrayDynamicHelper<proto::TargetableBehaviour::TargetPointArray> : public ArrayDynamicHelperBase
	{
	public:
		typedef proto::TargetableBehaviour::TargetPointArray A;
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
