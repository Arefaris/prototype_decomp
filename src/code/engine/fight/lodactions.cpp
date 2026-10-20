// The actions of the effect level-of-detail tracks (unit 0x108B95D0 - 0x108BA6F0, no assert path; file name guessed).
#include "code/engine/fight/lodactions.h"
#include "code/core/refptr.h"

namespace engine
{
	// What the tracks run for, seen the way the bias and disable actions test it: an IRefCount-derived object whose
	// kind says where its owner is kept (the engine's class is not named)
	struct LodOwner : core::IRefCount
	{
		int unknown4;
		unsigned int kind;  // +0x8
	};

	// FUNCTION: ENGINE 0x108B9700
	// EQUIVALENT: the engine tests the owner's kind with add eax, 0xFFFD0000 where ours has sub eax, 0x30000 (the same value);
	// every other instruction is the engine's (the register choice of the bias action's copy follows from it)
	EffectLODDisableAction::EffectLODDisableAction(fight::Track* listener, EffectLODDisableTrack* newTrack, core::IRefCount* owner)
		: fight::Action(0xE00), watch(listener), link(newTrack), unknown34(0)
	{
		LodOwner* lodOwner = (LodOwner*)owner;
		AssignSharedRef(&unknown34, lodOwner == 0 ? 0 : (lodOwner->kind - 0x30000 > 0xffff ? 0 : owner));
	}

	// FUNCTION: ENGINE 0x108B9660
	EffectLODDisableAction::~EffectLODDisableAction()
	{
		ReleaseSharedRef(unknown34);
		sequencer.End();
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
	// EQUIVALENT: the engine tests the owner's kind with add eax, 0xFFFD0000 where ours has sub eax, 0x30000 (the same value);
	// every other instruction is the engine's (the register choice of the bias action's copy follows from it)
	EffectLODBiasAction::EffectLODBiasAction(EffectLODBiasTrack* newTrack, core::IRefCount* owner)
		: fight::Action(0xE00), link(newTrack), unknown28(0)
	{
		LodOwner* lodOwner = (LodOwner*)owner;
		AssignSharedRef(&unknown28, lodOwner == 0 ? 0 : (lodOwner->kind - 0x30000 > 0xffff ? 0 : owner));
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
