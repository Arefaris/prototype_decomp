// proto::FEHudTextLog (RTTI name; base proto::FEHudElement): the text box of the head-up display that shows the log of
// messages and, with it, the timer of the missions. The scripts fill them (fehudtextlog_SetText, _Clear, _Add, _Close,
// _Hide and fehudtimer_SetText, _ClearText). The log's text is kept in one buffer of the unit. The movie paths and
// script names are original, the member names are guessed. Unit 0x104D2C70 - 0x104D3700 (no assert path; the file name is
// a guess).
#ifndef PROTO_FRONTEND_FEHUDTEXTLOG_H
#define PROTO_FRONTEND_FEHUDTEXTLOG_H

#include "code/proto/frontend/fehudelement.h"

namespace proto
{
	class FEHudTextLog : public FEHudElement
	{
	public:
		// 0x104D38F0
		FEHudTextLog();
		// 0x104D2F60
		~FEHudTextLog();

		// vftable slots 0 and 1 (0x104D2C70, 0x104D3110, which jumps to SetActive)
		virtual void Update(bool force);
		virtual void OnShow(bool shown);

		// 0x104D2E50
		void SetActive(bool newActive);
		// 0x104D3000 / 0x104D2D00 / 0x104D2D20 / 0x104D3090 / 0x104D2E20: the scripts' fehudtextlog_SetText, _Clear, _Add, _Close
		// and _Hide
		void SetText(const char* text);
		void Clear();
		void Add(const char* text, bool newline);
		void Close();
		void Hide();
		// 0x104D3120 / 0x104D3240: the scripts' fehudtimer_SetText and _ClearText
		void SetTimerText(char* text, char* shadowText);
		void ClearTimerText();

		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> text;  // +0x10
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> logVisible;  // +0xB8
		bool active;  // +0x160
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> timerVisible;  // +0x168
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> timerTextVisible;  // +0x210
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> timerShadowVisible;  // +0x2B8
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> timerBackgroundVisible;  // +0x360
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> timerText;  // +0x408
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> timerShadowText;  // +0x4B0
	};
}

#endif
