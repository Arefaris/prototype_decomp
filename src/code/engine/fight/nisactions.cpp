// The actions of the non-interactive sequence, subtitle and object light group tracks (unit 0x108EF6E0 - 0x108F0240,
// no assert path; file name guessed). The tracks are in nistracks.cpp.
#include "code/engine/fight/nisactions.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/nismessages.h"
#include "code/engine/subtitleoptions.h"

namespace engine
{
	// What the owner is seen as: an IRefCount-derived object whose kind says whether it is a game object
	struct NISOwner : core::IRefCount
	{
		int unknown4;
		unsigned int kind;  // +0x8
	};

	// FUNCTION: ENGINE 0x108EF6F0
	void AssignNISRef(core::IRefCount** slot, core::IRefCount* value)
	{
		if (value != 0)
		{
			value->AddRef();
		}
		if (*slot != 0)
		{
			(*slot)->Release();
		}
		*slot = value;
	}

	// FUNCTION: ENGINE 0x108EF720
	void ReleaseNISRef(core::IRefCount** slot)
	{
		if (*slot != 0)
		{
			(*slot)->Release();
			*slot = 0;
		}
	}

	// FUNCTION: ENGINE 0x108EF840
	// EQUIVALENT: the engine tests the owner's kind with add eax, 0xFFFEFFFB where ours has sub eax, 0x10005 (the same value);
	// every other instruction is the engine's
	NISExecuteAction::NISExecuteAction(NISExecuteTrack* newTrack, core::IRefCount* newOwner, fight::Name objectName)
		: fight::Action(0x200), link(newTrack), owner(0)
	{
		target = FindGameObject(objectName, *(const content::ObjectName*)"");
		NISOwner* object = (NISOwner*)newOwner;
		AssignNISRef(&owner, object == 0 ? 0 : (object->kind + 0xfffefffb > 0xfffa ? 0 : newOwner));
	}

	// FUNCTION: ENGINE 0x108EF7B0
	NISExecuteAction::~NISExecuteAction()
	{
		ReleaseNISRef(&owner);
	}

	// FUNCTION: ENGINE 0x108EF920
	bool NISExecuteAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		GameObject* object = target.Get();
		if (object == 0)
		{
			return false;
		}
		fight::Branch* branch = link.object->receiverBranch.GetBranch();
		if (branch != 0)
		{
			PlayBranchMessage message(branch, link.object->interruptPriority);
			object->SendMessage(&message);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108EF9D0
	fight::Action* NISExecuteTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new NISExecuteAction(this, owner, objectName);
	}

	// FUNCTION: ENGINE 0x108EFB60
	SubTitleAction::SubTitleAction(SubTitleTrack* newTrack, core::IRefCount* owner)
		: fight::Action(0xE00), link(newTrack), subtitle(0)
	{
	}

	// FUNCTION: ENGINE 0x108EFAD0
	SubTitleAction::~SubTitleAction()
	{
	}

	// FUNCTION: ENGINE 0x108EFBD0
	bool SubTitleAction::Slot5(int arg, float value)
	{
		if (link.object == 0)
		{
			return false;
		}
		core::Name<core::CaseSensitiveKey> speaker(link.object->speaker, 1);
		core::Name<core::CaseSensitiveKey> type(link.object->subTitleType, 1);
		const char* text = link.object->subTitle;
		subtitle = gSubtitleOptions->Show(text, type, speaker, false);
		return true;
	}

	// FUNCTION: ENGINE 0x108EFA40
	void SubTitleAction::Slot6()
	{
		gSubtitleOptions->Stop(subtitle);
	}

	// FUNCTION: ENGINE 0x108EFC40
	fight::Action* SubTitleTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new SubTitleAction(this, owner);
	}

	// FUNCTION: ENGINE 0x108EFEA0
	SetObjectLightGroupAction::SetObjectLightGroupAction(SetObjectLightGroupTrack* newTrack, GameObjectHandle newTarget)
		: fight::Action(0xE00), link(newTrack), target(newTarget)
	{
	}

	// FUNCTION: ENGINE 0x108EFF30
	SetObjectLightGroupAction::SetObjectLightGroupAction(SetObjectLightGroupTrack* newTrack, fight::Name objectName)
		: fight::Action(0xE00), link(newTrack)
	{
		target = FindGameObject(objectName, *(const content::ObjectName*)"");
	}

	// FUNCTION: ENGINE 0x108EFD70
	SetObjectLightGroupAction::~SetObjectLightGroupAction()
	{
	}

	// FUNCTION: ENGINE 0x108EFFA0
	// EQUIVALENT: the engine keeps the master table pointer in edi across the name copy and the second lookup, ours loads the
	// global again for each lookup; every other operation is the engine's
	bool SetObjectLightGroupAction::Slot5(int arg, float value)
	{
		if (target.IsValid())
		{
			SetLightGroupMessage message(link.object->groupName);
			target.Get()->SendMessage(&message);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108EFDA0
	// EQUIVALENT: the engine keeps the master table pointer in edi across the name copy and the second lookup, ours loads the
	// global again for each lookup; every other operation is the engine's
	void SetObjectLightGroupAction::Slot6()
	{
		if (target.IsValid())
		{
			fight::Name empty;
			SetLightGroupMessage message(empty);
			target.Get()->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x108F0040
	fight::Action* SetObjectLightGroupTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		GameObjectHandle handle = GetObjectHandle(owner);
		return new SetObjectLightGroupAction(this, handle);
	}

	// FUNCTION: ENGINE 0x108F0080
	fight::Action* ExplicitSetObjectLightGroupTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new SetObjectLightGroupAction(this, object);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108EF900
// FUNCTION: ENGINE 0x108EFBB0
// FUNCTION: ENGINE 0x108EFCA0
// FUNCTION: ENGINE 0x108EFD40
// FUNCTION: ENGINE 0x108EFF10
// FUNCTION: ENGINE 0x108EF740
// FUNCTION: ENGINE 0x108EF760
// FUNCTION: ENGINE 0x108EFA60
// FUNCTION: ENGINE 0x108EFA80
