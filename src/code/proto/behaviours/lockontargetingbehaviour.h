// proto::AutoTargetingBehaviour and proto::LockOnTargetingBehaviour (RTTI and reflection names; bases
// proto::TargetingBehaviour and proto::AutoTargetingBehaviour): the automatic target of an object chosen by the priorities
// of a proto::AutoTargetPriorityList, and the lock-on targeting of the player with its lock cones and sounds. Unit
// 0x102A8350 - 0x102B1280 (no assert path; the file names are guesses). The layouts are not recovered: only the class
// info is reconstructed.
#ifndef PROTO_BEHAVIOURS_LOCKONTARGETINGBEHAVIOUR_H
#define PROTO_BEHAVIOURS_LOCKONTARGETINGBEHAVIOUR_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/proto/autotargetprioritylist.h"
#include "code/proto/behaviours/targetingbehaviour.h"

namespace proto
{
	class GetAutoTargetMessage;
	class SetAutoTargetMessage;

	class AutoTargetingBehaviour : public TargetingBehaviour
	{
	public:
		// 0x102A8390 (the destructor is 0x102A85D0, the deleting destructor 0x102A89C0)
		explicit AutoTargetingBehaviour(engine::GameObject* newOwner);
		virtual ~AutoTargetingBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1, 6 and 8 (0x102A83E0, 0x102A9CA0, 0x102A8610): the target is cleared again
		virtual void Slot1();
		virtual void OnMessage(engine::Message* message);
		virtual void ClearTarget();

		// 0x102A83F0 / 0x102A8400: the messages with ids 5 and 6 carry the last target out, take it in
		void GetLastTarget(GetAutoTargetMessage* message);
		void SetLastTarget(SetAutoTargetMessage* message);
		// 0x102A8650: the entry of the marker list for a target class takes over what is better than the result so far
		void ApplyMarkerEntry(int targetClass, TargetClassPriority* result);
		// 0x102A86E0 (name guess): the priority of a target class for an object (the list of the behaviour, then the one
		// of the object's marker icon)
		void GetTargetClassPriority(engine::GameObject* object, int targetClass, unsigned int flags,
			TargetClassPriority* result);
		// 0x102A91E0 / 0x102A9760 / 0x102A8880 (not reconstructed; names guessed): the messages with ids 3, 4 and 7
		void OnGetAutoTarget(engine::Message* message);
		void OnSetAutoTarget(engine::Message* message);
		void OnMessage7(engine::Message* message);

		AutoTargetPriorityList* defaultAutoTargetPriorityList;  // +0x10
		AutoTargetPriorityList* currentAutoTargetPriorityList;  // +0x14
		AutoTargetPriorityList* markerOverrideAutoTargetPriorityList;  // +0x18
		engine::GameObjectHandle lastTarget;  // +0x1C
	};

	class LockOnTargetingBehaviour : public AutoTargetingBehaviour
	{
	public:
		// The cone the lock-on takes its targets from (RTTI proto::LockOnTargetingBehaviour::TargetLockCone)
		struct TargetLockCone
		{
			// 0x102AA3C0
			TargetLockCone();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x102A9F60 / 0x102A9F70: the arc in degrees (kept in radians)
			float GetArc() const;
			void SetArc(float degrees);

			float distance;  // +0x0
			float arc;  // +0x4 (radians)
			unsigned int minTargetCategory;  // +0x8
			unsigned int minTargetPriority;  // +0xC
			unsigned int maxTargetCategory;  // +0x10
			unsigned int maxTargetPriority;  // +0x14
			bool useFacing;  // +0x18
		};

		// The sounds of the lock-on (RTTI proto::LockOnTargetingBehaviour::SoundParams)
		struct SoundParams
		{
			// 0x102AB810
			SoundParams();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x102AB870 / 0x102AB8B0: plays the sound of a name (an audio patch), stops it
			void PlayName(const core::Name<core::CaseSensitiveKey>& name);
			void StopName(const core::Name<core::CaseSensitiveKey>& name);
			// 0x102AB8F0: switches the sounds on or off (off stops the sustained and the loop)
			void SetEnabled(bool on);
			// 0x102AB940 / 0x102AB970 / 0x102AB9A0 / 0x102AB9D0 / 0x102ABA00: the sound of each lock-on event
			void OnTargetAcquired();
			void OnTargetDestroyed();
			void OnTargetModeEntered();
			void OnTargetModeExited();
			void OnTargetAbandoned();

			bool enabled;  // +0x0
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> targetAquired;  // +0x8
			core::Name<core::CaseSensitiveKey> targetDestroyed;  // +0x10
			core::Name<core::CaseSensitiveKey> targetSustained;  // +0x18
			core::Name<core::CaseSensitiveKey> targetModeEntered;  // +0x20
			core::Name<core::CaseSensitiveKey> targetModeExited;  // +0x28
			core::Name<core::CaseSensitiveKey> targetModeLoop;  // +0x30
			core::Name<core::CaseSensitiveKey> targetAbandoned;  // +0x38
		};

		static content::ClassInfo* GetClassInfo();
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::LockOnTargetingBehaviour::TargetLockCone>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	template<> class ArrayDynamicHelper<container::ArrayDynamic<proto::LockOnTargetingBehaviour::TargetLockCone,
		container::AllocatorNew> > : public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<proto::LockOnTargetingBehaviour::TargetLockCone, container::AllocatorNew> A;
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
