// proto::GrabbableBehaviour (RTTI name; reflected as "GrabbableBehaviour"; base engine::animation::AttachableBehaviour) and
// proto::GrabbableStaticBehaviour (base GrabbableBehaviour): an object the player can grab, the class of grab it takes
// (grabbableClass), whether grabbing it is forbidden and how often it is uninterruptible, and for the static one the
// playback tree and the transitions with which it is held. Unit 0x102C4F30 - 0x102C6800 (no assert path; the file name is
// a guess). The reflected names are original, the rest is guessed; only the reflection is reconstructed.
#ifndef PROTO_BEHAVIOURS_GRABBABLEBEHAVIOUR_H
#define PROTO_BEHAVIOURS_GRABBABLEBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/content/stringmetatype.h"
#include "code/core/name.h"
#include "code/engine/propspawner.h"
#include "code/engine/reflectedclasses2.h"

namespace content
{
	class MetaObjectTemplate;
}

namespace proto
{
	class GrabbableBehaviour : public engine::animation::AttachableBehaviour
	{
	public:
		// 0x102C5410
		explicit GrabbableBehaviour(engine::GameObject* newOwner);
		// 0x102C5480 (the deleting destructor is 0x102C5840)
		virtual ~GrabbableBehaviour();
		// vftable slots 1 (0x102C4FB0), 6 (0x102C6390) and 8 (0x102C5070)
		virtual void Slot1();
		virtual void OnMessage(engine::Message* message);
		virtual void Slot8();
		// 0x102C4F30
		static content::ClassInfo* GetClassInfo();
		// 0x102C5700
		static content::MemberList* GetMembers();

		unsigned char unknown44[4];
		core::Name<core::CaseSensitiveKey> grabbableClass;  // +0x48
		int uninterruptible;  // +0x50
		int unknown54;
		bool grabbingForbidden;  // +0x58
		bool unknown59;
		unsigned char unknown5A[6];
	};

	class GrabbableStaticBehaviour : public GrabbableBehaviour
	{
	public:
		// 0x102C54E0
		explicit GrabbableStaticBehaviour(engine::GameObject* newOwner);
		// 0x102C5540 (the deleting destructor is 0x102C59F0)
		virtual ~GrabbableStaticBehaviour();
		// vftable slots 1 (0x102C5090: the base's), 6 (0x102C6650) and 9 (0x102C66E0)
		virtual void Slot1();
		virtual void OnMessage(engine::Message* message);
		virtual void Slot9();
		// 0x102C4F70
		static content::ClassInfo* GetClassInfo();
		// 0x102C5BA0
		static content::MemberList* GetMembers();

		// 0x102C50D0 / 0x102C50E0: the reflected strings read back as empty
		const char* GetParentTransitionState();
		const char* GetChildTransitionState();
		// 0x102C5580 / 0x102C55B0: the transitions are made from the packed text
		void SetParentTransitionState(const char* packed, content::LoadInventory* inventory);
		void SetChildTransitionState(const char* packed, content::LoadInventory* inventory);

		// 0x102C50A0: the transition states made from the packed text (the inventory is not used)
		static engine::UnpackedInitialState* CreateTransitionState(const char* packed, content::LoadInventory* inventory);

		core::Name<core::CaseSensitiveKey> playbackTreeName;  // +0x60
		core::Name<core::CaseSensitiveKey> playbackTreeState;  // +0x68
		content::MetaObjectTemplate* spawnedObjectTemplate;  // +0x70
		engine::UnpackedInitialState* parentTransitionState;  // +0x74
		engine::UnpackedInitialState* childTransitionState;  // +0x78
		int unknown7C;
	};
}

#endif
