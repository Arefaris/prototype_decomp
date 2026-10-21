// The action of the exit track (unit 0x108F44B0 - 0x108F4630, no assert path; file name guessed). The track is in
// exittracks.cpp.
#ifndef ENGINE_FIGHT_EXITACTIONS_H
#define ENGINE_FIGHT_EXITACTIONS_H

#include "code/core/linklist.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/exittracks.h"

namespace engine
{
	// RTTI: engine::ExitAction (9 vftable slots, size 0x3C): ends its sequence when the conditions of the track hold
	class ExitAction : public fight::Action
	{
	public:
		// 0x108F4550
		ExitAction(fight::Track* listener, ExitTrack* newTrack, int newEffect, core::IRefCount* newOwner);
		// 0x108F44B0
		virtual ~ExitAction();

		// vftable slot 7 (0x108F45F0)
		virtual bool Slot7(int arg, float value);

		TrackWatch watch;  // +0x1C
		core::Link<ExitTrack> link;  // +0x28
		int effect;  // +0x34
		core::IRefCount* owner;  // +0x38
	};
}

#endif
