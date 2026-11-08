// proto::FEHudEventPopup, proto::FEHudMissionPopup and proto::FEHudOpportunityEventPopup (RTTI names through their script
// wrappers): the three pop-ups of the head-up display that are dialogs of the front end's dialog state. Each keeps its dialog
// at +0 (made with the movie's overlay and name) and asks it to close when the pop-up is hidden; a request that comes while
// the game state is changing waits in a flag until Update repeats it. The script names are original, the member names are
// guessed. Unit 0x104CFB00 - 0x104D1210 (no assert path; the file name is a guess).
#ifndef PROTO_FRONTEND_FEHUDPOPUPS_H
#define PROTO_FRONTEND_FEHUDPOPUPS_H

#include "code/engine/frontend/dialogstate.h"

namespace proto
{
	class FEHudEventPopup
	{
	public:
		// 0x104CFD70
		FEHudEventPopup();
		// 0x104CFB00
		~FEHudEventPopup();

		// 0x104CFAF0: the scripts' feeventpopup_IsPreEvent
		bool IsPreEvent();
		// 0x104CFB30: closes the dialog (or waits for the game state), keeping the two flags it was asked with
		void Hide(bool newPreEvent, bool newFlag);
		// 0x104CFB90: closes the dialog when a request waits and the game state allows it
		void Update();

		engine::DialogState* dialog;  // +0
		bool unknown4;
		bool preEvent;  // +5
		bool hidePending;  // +6
	};

	class FEHudMissionPopup
	{
	public:
		// 0x104D1130
		FEHudMissionPopup();
		// 0x104D0F00
		~FEHudMissionPopup();

		// 0x104D0F30: the scripts' femissionpopup_Show
		void Show();
		// 0x104D0F70
		void Update();

		engine::DialogState* dialog;  // +0
		bool showPending;  // +4
	};

	class FEHudOpportunityEventPopup
	{
	public:
		// 0x104D13A0
		FEHudOpportunityEventPopup();
		// 0x104D11D0
		~FEHudOpportunityEventPopup();

		// 0x104D1200: the scripts' feopportunityeventpopup_Show
		void Show();

		engine::DialogState* dialog;  // +0
	};
}

#endif
