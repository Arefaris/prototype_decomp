// proto::FEHudAwareness (RTTI name; base proto::FEHudElement): the awareness indicator of the head-up display, which
// shows whether someone is watching the player and how far the search has gone. It keeps the percentage and the state
// derived from it (not watched, watched, watched completely) and tells the movie when either changed. The movie paths
// are original, the member names are guessed. Unit 0x104CB4D0 - 0x104CB6F0 (no assert path; the file name is a guess).
#ifndef PROTO_FRONTEND_FEHUDAWARENESS_H
#define PROTO_FRONTEND_FEHUDAWARENESS_H

#include "code/proto/frontend/fehudelement.h"

namespace proto
{
	class FEHudAwareness : public FEHudElement
	{
	public:
		// 0x104CB670
		FEHudAwareness();
		// 0x104CB640 (deleting destructor 0x104CB6F0)
		virtual ~FEHudAwareness();

		// vftable slots 0 and 1 (0x104CB4D0, 0x104CB660, which jumps to SetShown)
		virtual void Update(bool force);
		virtual void OnShow(bool shown);

		// 0x104CB600
		void SetShown(bool shown);
		// 0x104CB580: sets the state (not watched, or watched, or watched completely when the percentage is full)
		void SetWatched(bool watched);
		// 0x104CB5C0
		bool IsWatched() const;
		// 0x104CB5D0
		void SetPercent(int newPercent);

		int state;  // +0xC
		int percent;  // +0x10
		int stateChanges;  // +0x14
		int percentChanges;  // +0x18
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> visible;  // +0x20
	};
}

#endif
