// proto::FEHudDisguiseActions (RTTI name; base proto::FEHudElement): the pop-up that lists what the player can do while
// disguised (the patsy, the air strike and the stealth kill). The fight items of the AI show and hide it and tell it the
// state of each action. The movie paths and function names are original, the member names are guessed. Unit
// 0x104CF760 - 0x104CFA70 (no assert path; the file name is a guess).
#ifndef PROTO_FRONTEND_FEHUDDISGUISEACTIONS_H
#define PROTO_FRONTEND_FEHUDDISGUISEACTIONS_H

#include "code/proto/frontend/fehudelement.h"

namespace proto
{
	class FEHudDisguiseActions : public FEHudElement
	{
	public:
		// 0x104CFA70
		FEHudDisguiseActions();

		// vftable slots 0 and 1 (0x104CF760, 0x104CFA60, which jumps to SetVisible)
		virtual void Update(bool force);
		virtual void OnShow(bool shown);

		// 0x104CFA20
		void SetVisible(bool newVisible);
		// 0x104CF840 / 0x104CF870: shows or hides the pop-up in the movie
		void Show();
		void Hide();
		// 0x104CF8A0 / 0x104CF930 / 0x104CF9B0: tell the movie the state of an action when it changed
		void SetPatsyState(bool available, bool active, float progress);
		void SetAirStrikeState(bool available, bool active, int a, int b);
		void SetStealthConsumeState(bool available, bool active, bool consuming);

		bool patsyAvailable;  // +0xC
		bool patsyActive;  // +0xD
		int patsyProgress;  // +0x10
		bool airStrikeAvailable;  // +0x14
		bool airStrikeActive;  // +0x15
		int airStrikeA;  // +0x18
		int airStrikeB;  // +0x1C
		bool stealthAvailable;  // +0x20
		bool stealthActive;  // +0x21
		bool stealthConsuming;  // +0x22
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> visible;  // +0x28
		unsigned char unknownD0[8];  // +0xD0 (the engine allocates 0xD8 bytes)
	};
}

#endif
