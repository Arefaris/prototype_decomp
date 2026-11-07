// The actions of the non-interactive sequence animation, sequence node and light animation tracks (unit 0x108F0C10 -
// 0x108F2000, no assert path; file name guessed). The tracks are in cameratracks.cpp.
#include "code/engine/fight/nisanimationactions.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/nismessages.h"
#include "code/core/refptr.h"
#include "code/core/strings.h"
#include "code/math/worldbounds.h"
#include "code/engine/nis/nisnodes.h"
#include "code/engine/system/streampackage.h"
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

	void AssignRefCounted(core::IRefCount** slot, core::IRefCount* value);
	// 0x108A8230: the sequence handler of an owner that is a game object (null for any other owner)
	NISHandler* GetOwnerNISHandler(core::IRefCount* owner);
	extern content::ObjectName gUndefinedSlotGroup85;

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

	// FUNCTION: ENGINE 0x108F1120
	// NONMATCHING: registers (the engine keeps the action in edi and the controller in esi, ours the other way round, and it tests the name comparison with test al, al; 92 %)
#ifdef NONMATCHING
	void NISAnimationAction::Slot6()
	{
		GameObject* object = target.Get();
		if (object != 0 && link.object != 0)
		{
			bool send = !link.object->toBeContinued;
			if (!send)
			{
				Attribute<pure3d::PoseAnimationController*>* attribute =
					(Attribute<pure3d::PoseAnimationController*>*)object->FindAttribute(gPoseAnimationControllerName);
				if (attribute != 0 && attribute->GetPointer() != 0)
				{
					pure3d::PoseAnimationController* controller = attribute->value;
					send = controller == 0 || controller->Unknown20();
					if (!send)
					{
						const fight::Name& wanted = link.object->animation;
						pure3d::Animation* current = controller->GetAnimation();
						send = current->mName == wanted;
					}
				}
			}
			if (send)
			{
				SetAnimationMessage stop;
				object->SendMessage(&stop);
				NISMessage message(6, fight::Name());
				object->SendMessage(&message);
				StopSignal signal;
				signal.type = 0x17;
				signal.unknown8 = 2;
				signal.unknownB = true;
				object->behaviours.HandleMessage((Message*)&signal);
			}
		}
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

	// FUNCTION: ENGINE 0x108F16D0
	// NONMATCHING: block layout (the engine places the shared return-false tail behind the handler call, ours before it; every instruction is the engine's; 35 %)
#ifdef NONMATCHING
	bool SequenceNISNodeAction::Slot5(int arg, float value)
	{
		NISNode* node = (NISNode*)link.Get()->branch.GetBranch();
		if (node == 0)
		{
			return false;
		}
		StreamPackage* package = GetNISNodeStreamPackage(node);
		if (package != 0)
		{
			sequence = fight::Name();
			if (package->instance != 0 && package->instance->IsLoaded())
			{
				if (dynamic_cast<NISRootNode*>(node) != 0)
				{
					NISPlayMessage message(node->name, value, false);
					SendMessage(&message, &gNISListeners);
					return false;
				}
				if (GetOwnerNISHandler(owner) == 0)
				{
					return false;
				}
				node->Unknown108A7CE0(effect, owner, math::WORLD_MIN - value);
				return false;
			}
			else
			{
				GameObject* object = GetObjectHandle(owner).Get();
				if (object != 0)
				{
					fight::Name empty("", 1);
					NISMessage message(2, empty);
					object->SendMessage(&message);
					return true;
				}
			}
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x108F1830
	fight::Action* SequenceNISNodeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new SequenceNISNodeAction(listener, this, (int)effect, owner);
	}

	// FUNCTION: ENGINE 0x108F1AD0
	void LightAnimationAction::Slot6()
	{
		LightAnimationTrack* track = link.object;
		GameObject* object = target.Get();
		if (track != 0 && object != 0)
		{
			bool send = !((ExplicitLightAnimationTrack*)track)->toBeContinued;
			if (!send)
			{
				Attribute<pure3d::SimpleFrameController*>* attribute =
					(Attribute<pure3d::SimpleFrameController*>*)object->FindAttribute(gLightControllerName);
				if (attribute != 0 && attribute->GetPointer() != 0)
				{
					pure3d::SimpleFrameController* controller = attribute->value;
					send = controller == 0 || controller->Unknown20();
				}
			}
			if (send)
			{
				SetAnimationMessage stop;
				object->SendMessage(&stop);
				if (ownerHandle.IsValid())
				{
					NISMessage message(6, fight::Name());
					object->SendMessage(&message);
				}
			}
			ReleaseNISRef(&owner);
		}
	}

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

	// FUNCTION: ENGINE 0x108F12E0
	// Copies the path of a branch holder and answers the part behind its last slash (null for none)
	char* GetLeafName(fight::BranchHolder* holder, char* buffer, unsigned int size)
	{
		holder->CopyPath(buffer, size);
		char* leaf = buffer + core::StrLen(buffer);
		while (leaf > buffer)
		{
			if (*leaf == '/')
			{
				return leaf + 1;
			}
			leaf--;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x108F14A0
	// NONMATCHING: registers (the engine addresses the track's branch holder through eax and reuses edi for its second path copy, ours uses ecx and edx; 94.9 %)
#ifdef NONMATCHING
	SequenceNISNodeAction::SequenceNISNodeAction(fight::Track* listener, SequenceNISNodeTrack* newTrack, int newEffect,
		core::IRefCount* newOwner) : fight::Action(0xA00), link(newTrack), watch(listener), effect(newEffect), owner(0)
	{
		AssignRefCounted(&owner, newOwner);
		NISNode* node = (NISNode*)link.object->branch.GetBranch();
		if (node == 0)
		{
			char path[0x100];
			char* leaf = GetLeafName(&link.object->branch, path, 0x100);
			if (leaf != 0)
			{
				{
					fight::Name name(leaf, 1);
					NISMessage message(0, name);
					SendMessage(&message, &gNISListeners);
				}
				{
					fight::Name name(leaf, 1);
					sequence = name;
				}
			}
			return;
		}
		if (dynamic_cast<NISRootNode*>(node) != 0)
		{
			NISMessage message(0, node->name);
			SendMessage(&message, &gNISListeners);
			sequence = node->name;
			return;
		}
		NISHandler* handler = GetOwnerNISHandler(owner);
		if (handler == 0)
		{
			char path[0x100];
			link.object->branch.CopyPath(path, 0x100);
			return;
		}
		StreamPackage* package = GetNISNodeStreamPackage(node);
		if (package != 0)
		{
			package->Load(0, 0xFFFF, gUndefinedSlotGroup85, false);
			handler->Unknown108A7450(node);
		}
	}
#endif

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
// FUNCTION: ENGINE 0x108F0C80
// FUNCTION: ENGINE 0x108F0C60
// FUNCTION: ENGINE 0x108F13B0
// FUNCTION: ENGINE 0x108EDAB0
