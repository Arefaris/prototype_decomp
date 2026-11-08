// proto::FEHudKeyCard (RTTI name; base proto::FEHudElement): the key card icon of the head-up display. Its two
// variables show the element and its icon; the scripts show and hide the icon (fehudkeycard_Show, fehudkeycard_Hide).
// The movie paths are original, the member names are guessed. Unit 0x104D0B10 - 0x104D0F00 (no assert path; the file
// name is a guess).
#ifndef PROTO_FRONTEND_FEHUDKEYCARD_H
#define PROTO_FRONTEND_FEHUDKEYCARD_H

#include "code/proto/frontend/fehudelement.h"

namespace proto
{
	class FEHudKeyCard : public FEHudElement
	{
	public:
		// 0x104D0DF0
		FEHudKeyCard();
		// 0x104D0C70
		~FEHudKeyCard();

		// vftable slot 0 (0x104D0B10) and 1 (0x104D0CC0, which jumps to SetShown)
		virtual void Update(bool force);
		virtual void OnShow(bool shown);

		// 0x104D0BD0
		void SetShown(bool shown);
		// 0x104D0B40 / 0x104D0BA0: the scripts' fehudkeycard_Show and fehudkeycard_Hide
		void ShowIcon();
		void HideIcon();

		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> visible;  // +0x10
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> icon;  // +0xB8
	};
}

#endif
