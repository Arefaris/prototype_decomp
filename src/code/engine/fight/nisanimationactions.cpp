// The actions of the non-interactive sequence animation, sequence node and light animation tracks (unit 0x108F0C10 -
// 0x108F2000, no assert path; file name guessed). The tracks are in cameratracks.cpp.
#include "code/engine/fight/nisanimationactions.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/nismessages.h"
#include "code/core/refptr.h"
#include "code/pure3d/animation.h"
#include "code/pure3d/framecontroller.h"
#include "code/pure3d/primitive.h"

namespace engine
{
	// What the owner is seen as: an IRefCount-derived object whose kind says whether it is a game object
	struct NISOwner : core::IRefCount
	{
		int unknown4;
		int kind;  // +0x8
	};

	class MessageListeners;
	void SendMessage(Message* message, MessageListeners* listeners);
	extern MessageListeners gNISListeners;

	extern content::ObjectName gPoseAnimationControllerName;
	extern content::ObjectName gLightControllerName;

	// FUNCTION: ENGINE 0x108F0D50
	NISAnimationAction::NISAnimationAction(NISAnimationTrack* newTrack, fight::Name newObject, GameObjectHandle newOwner,
		content::LoadInventory* newInventory) : fight::Action(0xE00), link(newTrack), object(newObject), owner(newOwner),
		inventory(newInventory)
	{
	}

	// FUNCTION: ENGINE 0x108F1090
	// NONMATCHING: shrink-wrap (the engine saves esi before the attribute lookup, ours after its tests; 59 %)
#ifdef NONMATCHING
	bool NISAnimationAction::Slot7(int arg, float value)
	{
		GameObject* gameObject = target.Get();
		if (gameObject == 0 || link.object == 0)
		{
			return false;
		}
		pure3d::PoseAnimationController** pointer = 0;
		Attribute<pure3d::PoseAnimationController*>* attribute =
			(Attribute<pure3d::PoseAnimationController*>*)gameObject->FindAttribute(gPoseAnimationControllerName);
		if (attribute != 0)
		{
			pointer = attribute->GetPointer();
		}
		if (pointer == 0)
		{
			return true;
		}
		pure3d::PoseAnimationController* controller = *pointer;
		if (controller == 0 || controller->Unknown20())
		{
			return false;
		}
		const fight::Name& wanted = link.object->animation;
		pure3d::Animation* current = controller->GetAnimation();
		return !(current->mName != wanted);
	}
#endif

	// FUNCTION: ENGINE 0x108F1270
	fight::Action* NISAnimationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new NISAnimationAction(this, object, GetObjectHandle(owner), GetOwnerInventory(owner));
	}

	// FUNCTION: ENGINE 0x108F1C20
	// NONMATCHING: scheduling (the engine writes both words of the owner handle through the register of the constructor call, ours sinks the stores behind the epilogue's pop; 88 %)
#ifdef NONMATCHING
	LightAnimationAction::LightAnimationAction(LightAnimationTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), target(newTarget)
	{
		owner = 0;
		ownerHandle.serial = 0;
		ownerHandle.index = 0xFFFF;
	}
#endif

	// FUNCTION: ENGINE 0x108F1CB0
	// NONMATCHING: the owner's kind test is add eax, 0xFFFEFFFB in the engine and sub edx, 0x10005 in ours (the registers swap); 83.6 %
#ifdef NONMATCHING
	LightAnimationAction::LightAnimationAction(LightAnimationTrack* newTrack, core::IRefCount* newOwner,
		fight::Name objectName) : fight::Action(0xE00), link(newTrack)
	{
		owner = 0;
		target = FindGameObject(objectName, *(const content::ObjectName*)"");
		ownerHandle = GetObjectHandle(newOwner);
		NISOwner* object = (NISOwner*)newOwner;
		AssignNISRef(&owner, object == 0 ? 0 : ((unsigned)(object->kind - 0x10005) > 0xfffa ? 0 : newOwner));
	}
#endif

	// FUNCTION: ENGINE 0x108F1A00
	// NONMATCHING: scheduling (the engine stores the vftable before it pushes the address of the owner, ours after; 95 %)
#ifdef NONMATCHING
	LightAnimationAction::~LightAnimationAction()
	{
		ownerHandle.index = 0xFFFF;
		ownerHandle.serial = 0;
		ReleaseNISRef(&owner);
	}
#endif

	// FUNCTION: ENGINE 0x108F1A40
	// NONMATCHING: shrink-wrap (the engine saves esi before the attribute lookup, ours after its tests; 55 %)
#ifdef NONMATCHING
	bool LightAnimationAction::Slot7(int arg, float value)
	{
		GameObject* gameObject = target.Get();
		if (gameObject == 0)
		{
			return false;
		}
		Attribute<pure3d::SimpleFrameController*>* attribute =
			(Attribute<pure3d::SimpleFrameController*>*)gameObject->FindAttribute(gLightControllerName);
		if (attribute == 0 || attribute->GetPointer() == 0)
		{
			return true;
		}
		pure3d::SimpleFrameController* controller = attribute->value;
		if (controller == 0 || controller->Unknown20())
		{
			return false;
		}
		const fight::Name& wanted = link.object->animation;
		pure3d::Animation* current = controller->GetAnimation();
		return !(current->mName != wanted);
	}
#endif

	// FUNCTION: ENGINE 0x108F1FC0
	fight::Action* ExplicitLightAnimationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new LightAnimationAction(this, owner, object);
	}

	// FUNCTION: ENGINE 0x108F1F80
	fight::Action* LightAnimationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new LightAnimationAction(this, handle);
	}

	// FUNCTION: ENGINE 0x108F13C0
	SequenceNISNodeAction::~SequenceNISNodeAction()
	{
		if (!sequence.IsEmpty())
		{
			NISMessage message(8, sequence);
			SendMessage(&message, &gNISListeners);
		}
		core::SafeReleaseRef(owner);
	}

	// FUNCTION: ENGINE 0x108F1320
	bool SequenceNISNodeAction::Slot7(int arg, float value)
	{
		return Slot5(1, value);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108F0DD0
// FUNCTION: ENGINE 0x108F0DF0
// FUNCTION: ENGINE 0x108F16B0
