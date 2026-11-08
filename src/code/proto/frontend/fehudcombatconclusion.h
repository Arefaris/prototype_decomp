// proto::FEHudCombatConclusion (RTTI name; base proto::FEHudElement): the summary the head-up display shows when a fight
// ends. The scripts show and hide it (fehudcombatconclusion_Show, _Hide) and tell when the movie finished hiding it
// (_OnHideComplete). The movie paths and script names are original, the member names are guessed. Unit 0x104CF320 -
// 0x104CF760 (no assert path; the file name is a guess).
#ifndef PROTO_FRONTEND_FEHUDCOMBATCONCLUSION_H
#define PROTO_FRONTEND_FEHUDCOMBATCONCLUSION_H

#include "code/proto/frontend/fehudelement.h"

namespace proto
{
	class FEHudCombatConclusion : public FEHudElement
	{
	public:
		// 0x104CF680
		FEHudCombatConclusion();
		// 0x104CF520
		~FEHudCombatConclusion();

		// vftable slots 0 and 1 (0x104CF320, 0x104CF460)
		virtual void Update(bool force);
		virtual void OnShow(bool shown);

		// 0x104CF480
		void SetVisible(bool newVisible);
		// 0x104CF450
		void Reset();
		// 0x104CF330 / 0x104CF3C0 / 0x104CF420: the scripts' fehudcombatconclusion_Show, _Hide and _OnHideComplete
		void Show();
		void Hide();
		void OnHideComplete();

		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> visible;  // +0x10
		int state;  // +0xB8: 0 hidden, 1 shown, 2 hiding
	};
}

#endif
