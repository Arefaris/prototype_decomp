// proto::FEHudPopup (RTTI name; base proto::FEHudElement): the pop-ups of the head-up display. It keeps four slots, one for
// each kind of pop-up (the passive pop-up of the smart hints, the hint pop-up, the mission pop-up and the objective pop-up;
// the names are guesses from the movie functions): a slot says whether its pop-up is open (state 0), closing (1) or
// closed (2) and keeps up to four texts. The movie paths and function names are original, the member names are guessed.
// Unit 0x104D1430 - 0x104D3000 (no assert path; the file name is a guess).
#ifndef PROTO_FRONTEND_FEHUDPOPUP_H
#define PROTO_FRONTEND_FEHUDPOPUP_H

#include "code/proto/frontend/fehudelement.h"

namespace proto
{
	class FEHudPopup : public FEHudElement
	{
	public:
		// One kind of pop-up (0x1C bytes)
		class Slot
		{
		public:
			// 0x104D1550: closed, no texts
			Slot();
			// 0x104D1580: lets go of the four text buffers
			~Slot();
			// 0x104D15C0 / 0x104D15E0 / 0x104D15F0: opens the pop-up, starts closing it, sets it closed
			void Open(bool newFlag);
			void StartClosing();
			void SetClosed();

			int state;  // +0
			bool flag;  // +4
			char* texts[4];  // +8
			bool unknown18;
		};

		// 0x104D25F0
		FEHudPopup();
		// 0x104D1660
		~FEHudPopup();

		// vftable slots 0 and 1 (0x104D2010, 0x104D1B80, which jumps to ShowPopups)
		virtual void Update(bool force);
		virtual void OnShow(bool shown);

		// 0x104D1500: tells the movie whether the pop-ups show
		void ShowPopups(bool show);
		// 0x104D17A0 / 0x104D1940 / 0x104D1820: open the hint, objective and mission pop-ups
		void ShowHintPopup(bool newFlag, const char* text);
		void ShowObjectivePopup(const char* title, const char* text);
		void ShowMissionPopup(bool newFlag, bool newUnknown18, const char* text0, const char* text1, const char* text2,
			const char* text3);
		// 0x104D19C0 / 0x104D1A50 / 0x104D1A10 / 0x104D1AA0 / 0x104D1AF0: close the pop-ups
		void ClosePassivePopup();
		void ClosePassivePopupUnflagged();
		void CloseHintPopup();
		void CloseMissionPopup();
		void CloseAll();
		// 0x104D1B20 / 0x104D1B40 / 0x104D1B50 / 0x104D1B60: set the slots closed
		void ResetPassive();
		void ResetHint();
		void ResetMission();
		void ResetObjective();
		// 0x104D1430 / 0x104D1440 / 0x104D1450 / 0x104D1460: whether the slot's pop-up is open
		bool IsPassiveOpen();
		bool IsHintOpen();
		bool IsMissionOpen();
		bool IsObjectiveOpen();
		// 0x104D1470 / 0x104D1480
		bool GetPassiveFlag();
		bool GetHintFlag();
		// 0x104D14E0 / 0x104D14F0: the scripts' fe_SetMissionIdle and fe_IsMissionIdle
		void SetMissionIdle(bool value);
		bool GetMissionIdle();
		// 0x104D1490 (another unit's NONMATCHING caller names it): fades the pop-up out (or back in)
		void Unknown104D1490(bool faded);
		// 0x104D16C0 (not reconstructed)
		void ShowPassivePopup(bool newFlag, const char* text);

		bool popupsShown;  // +0xC
		bool missionIdle;  // +0xD
		Slot slots[4];  // +0x10
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> alpha;  // +0x80 (the movie's _alpha of the pop-ups)
	};
}

#endif
