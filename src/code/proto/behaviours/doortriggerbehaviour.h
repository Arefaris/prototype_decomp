// proto::DoorTriggerBehaviour (RTTI and reflection names; base engine::Behaviour): switches the logic state of its
// prop while objects stand in its trigger volume (volume messages of type 0xd with the ids 3 and 4, collision
// messages of type 4) and, optionally, the collision of the objects that enter. Reflected: useFilter,
// filterAttributeKey, filterAttributeValue, inVolumeStateName, outVolumeStateName, toggleCollision,
// forcePropLogicState, useTwoVolumes. Unit 0x10555BA0 - 0x10556AF0 (no assert path; the file name is a guess). The
// reflected names are original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_DOORTRIGGERBEHAVIOUR_H
#define PROTO_BEHAVIOURS_DOORTRIGGERBEHAVIOUR_H

#include "code/container/arrayfixed.h"
#include "code/container/string.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace proto
{
	class DoorTriggerBehaviour : public engine::Behaviour
	{
	public:
		// 0x105566F0
		explicit DoorTriggerBehaviour(engine::GameObject* newOwner);
		// 0x105567E0 (the deleting destructor is 0x10556AD0)
		virtual ~DoorTriggerBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10555C40): nothing to do
		virtual void Slot1()
		{
		}
		// vftable slot 6 (0x10556810)
		virtual void OnMessage(engine::Message* message);

		// 0x10555E50 / 0x10555F10: asks the prop's logic tree to go to the in / out volume state (names guessed)
		void SendInVolumeState();
		void SendOutVolumeState();
		// 0x10556420: forgets the objects in the volume and stops listening to collisions
		void ClearInVolume();
		// 0x10556440 / 0x105564C0: the object enters / is no longer in the volume (names guessed)
		void AddInVolume(const engine::GameObjectHandle& handle);
		void RemoveInVolume(const engine::GameObjectHandle& handle);

		bool useFilter;  // +0xC
		container::StringC<128> filterAttributeKey;  // +0x10
		int unknown94;  // padding: the names are 8-byte aligned in the engine
		core::Name<core::CaseSensitiveKey> filterAttributeValue;  // +0x98
		core::Name<core::CaseSensitiveKey> inVolumeStateName;  // +0xA0
		core::Name<core::CaseSensitiveKey> outVolumeStateName;  // +0xA8
		bool toggleCollision;  // +0xB0
		bool forcePropLogicState;  // +0xB1
		bool useTwoVolumes;  // +0xB2
		container::ArrayFixed<engine::GameObjectHandle, 10> inVolume;  // +0xB4
	};
}

#endif
