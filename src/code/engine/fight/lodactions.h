// The actions of the effect level-of-detail tracks (unit 0x108B95D0 - 0x108BA6F0, no assert path; file name guessed).
// The tracks are in efflodtracks.cpp.
#ifndef ENGINE_FIGHT_LODACTIONS_H
#define ENGINE_FIGHT_LODACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/efflodtracks.h"
#include "code/engine/fight/effecttrack.h"

namespace engine
{
	// 0x10098F50: stores a reference counted pointer (the engine's copy of core's helper)
	void AssignRefCounted(core::IRefCount** slot, core::IRefCount* value);
	// 0x104FF220: the same helper's other copy, which the level-of-detail actions call for their owner
	void AssignSharedRef(core::IRefCount** slot, core::IRefCount* value);

	// RTTI: engine::EffectLODDisableAction (9 vftable slots, size 0x80): switches the level of detail of an effect off
	// while its own sequencer runs
	class EffectLODDisableAction : public fight::Action
	{
	public:
		// 0x108B9700
		EffectLODDisableAction(fight::Track* listener, EffectLODDisableTrack* newTrack, core::IRefCount* owner);
		// 0x108B9660
		virtual ~EffectLODDisableAction();

		// vftable slot 5 (0x108B97D0) and slot 6 (0x108B95D0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		TrackWatch watch;  // +0x1C
		core::Link<EffectLODDisableTrack> link;  // +0x28
		core::IRefCount* unknown34;
		fight::Sequencer sequencer;  // +0x38
		int unknown7c;
	};

	// RTTI: engine::EffectLODSwitchAction (9 vftable slots, size 0x30)
	class EffectLODSwitchAction : public fight::Action
	{
	public:
		// 0x108B9A10
		EffectLODSwitchAction(EffectLODSwitchTrack* newTrack, core::IRefCount* owner);
		// 0x108B9980
		virtual ~EffectLODSwitchAction();

		// vftable slot 5 (0x108B9A90) and slot 6 (0x108B98C0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		core::Link<EffectLODSwitchTrack> link;  // +0x1C
		core::IRefCount* unknown28;
		core::IRefCount* unknown2c;
	};

	// RTTI: engine::EffectLODBiasAction (9 vftable slots, size 0x2C)
	class EffectLODBiasAction : public fight::Action
	{
	public:
		// 0x108BA0B0
		EffectLODBiasAction(EffectLODBiasTrack* newTrack, core::IRefCount* owner);
		// 0x108BA030
		virtual ~EffectLODBiasAction();

		// vftable slot 5 (0x108BA160) and slot 6 (0x108B9FA0)
		virtual bool Slot5(int arg, float value);
		virtual void Slot6();

		core::Link<EffectLODBiasTrack> link;  // +0x1C
		core::IRefCount* unknown28;
	};
}

#endif
