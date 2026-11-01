// The actions of the effect level-of-detail tracks (unit 0x108B95D0 - 0x108BA6F0, no assert path; file name guessed).
#include "code/engine/fight/lodactions.h"
#include "code/core/refptr.h"
#include "code/engine/effectparams.h"
#include "code/engine/render/effectlod.h"
#include "code/engine/render/effectmanager.h"
#include "code/engine/system/enginememory.h"

namespace engine
{
	// What the tracks run for, seen the way the bias and disable actions test it: an IRefCount-derived object whose
	// kind says where its owner is kept (the engine's class is not named)
	struct LodOwner : core::IRefCount
	{
		int unknown4;
		int kind;  // +0x8
	};

	// The owner when it is a set of effect parameters (a kind in 0x30000 - 0x3FFFF), else none
	inline core::IRefCount* AsParamsOwner(core::IRefCount* owner)
	{
		LodOwner* lodOwner = (LodOwner*)owner;
		if (lodOwner == 0)
		{
			return 0;
		}
		int kind = lodOwner->kind;
		return (kind >= 0x30000 && kind < 0x40000) ? owner : 0;
	}

	// FUNCTION: ENGINE 0x108B9700
	EffectLODDisableAction::EffectLODDisableAction(fight::Track* listener, EffectLODDisableTrack* newTrack, core::IRefCount* owner)
		: fight::Action(0xE00), watch(listener), link(newTrack), unknown34(0)
	{
		AssignSharedRef(&unknown34, AsParamsOwner(owner));
	}

	// FUNCTION: ENGINE 0x108B9660
	EffectLODDisableAction::~EffectLODDisableAction()
	{
		ReleaseSharedRef(unknown34);
		sequencer.End();
	}

	// FUNCTION: ENGINE 0x108B95D0
	void EffectLODDisableAction::Slot6()
	{
		sequencer.Reset();
	}

	// FUNCTION: ENGINE 0x108B97D0
	// EQUIVALENT: stack slots: the engine keeps the effect handle in the slot of the elapsed time (frame of 8 bytes), ours uses a third slot (96.7 %)
	bool EffectLODDisableAction::Slot5(int arg, float value)
	{
		if (unknown34 != 0)
		{
			float elapsed = ((EffectParams*)unknown34)->unknown10;
			float start = link.object->lodStartDistance;
			EffectLOD* lod = new (10) EffectLODDisable(start + elapsed);
			unsigned int effect = ((EffectParams*)unknown34)->unknownC;
			render::GetEffectManager()->AddLOD(&effect, lod);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x108B98C0
	void EffectLODSwitchAction::Slot6()
	{
	}

	// FUNCTION: ENGINE 0x108B9FA0
	void EffectLODBiasAction::Slot6()
	{
	}

	// FUNCTION: ENGINE 0x108B9A10
	EffectLODSwitchAction::EffectLODSwitchAction(EffectLODSwitchTrack* newTrack, core::IRefCount* owner)
		: fight::Action(0xE00), link(newTrack), unknown28(0), unknown2c(0)
	{
		AssignRefCounted(&unknown28, owner);
	}

	// FUNCTION: ENGINE 0x108B9980
	EffectLODSwitchAction::~EffectLODSwitchAction()
	{
		core::SafeReleaseRef(unknown28);
		ReleaseSharedRef(unknown2c);
	}

	// FUNCTION: ENGINE 0x108BA0B0
	EffectLODBiasAction::EffectLODBiasAction(EffectLODBiasTrack* newTrack, core::IRefCount* owner)
		: fight::Action(0xE00), link(newTrack), unknown28(0)
	{
		AssignSharedRef(&unknown28, AsParamsOwner(owner));
	}

	// FUNCTION: ENGINE 0x108BA030
	EffectLODBiasAction::~EffectLODBiasAction()
	{
		ReleaseSharedRef(unknown28);
	}

	// FUNCTION: ENGINE 0x108B9850
	fight::Action* EffectLODDisableTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new EffectLODDisableAction(listener, this, owner);
	}

	// FUNCTION: ENGINE 0x108B9BA0
	fight::Action* EffectLODSwitchTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new EffectLODSwitchAction(this, owner);
	}

	// FUNCTION: ENGINE 0x108BA500
	fight::Action* EffectLODBiasTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return new EffectLODBiasAction(this, owner);
	}
}
