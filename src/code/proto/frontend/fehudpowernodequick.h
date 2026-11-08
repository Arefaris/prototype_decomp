// proto::FEHudPowerNodeQuick (RTTI name; base engine::DBObserver): one slot of the quick power select of the head-up display.
// It keeps the power set for the slot, saves it in the game database (Proto_Save_QuickPowerSelect) and follows the power the
// player transformed into (HUDPlayerTransform). Unit 0x104C52F0 - 0x104C5700 (no assert path; the file name is a guess). The
// movie function names are original, the member names are guessed.
#ifndef PROTO_FRONTEND_FEHUDPOWERNODEQUICK_H
#define PROTO_FRONTEND_FEHUDPOWERNODEQUICK_H

#include "code/engine/dbobserver.h"

namespace proto
{
	class FEHudPowerNodeQuick : public engine::DBObserver
	{
	public:
		// 0x104C54E0
		FEHudPowerNodeQuick(int newSlot, int newPower, bool newLocked);
		// 0x104C52F0
		~FEHudPowerNodeQuick();

		// vftable slots 0 and 1 (0x104C55D0, 0x104C5490)
		virtual void OnDBSlot0(int key, int change);
		virtual void OnDBSlot1(int a, int b);

		// 0x104C5330: sets the power of the slot (and saves it, unless silent)
		void SetPower(int newPower, bool silent);
		// 0x104C5380: selects the slot's power as the transformation, or none when it is already the selection
		void Select();
		// 0x104C5440 / 0x104C54A0: tell the movie about the slot
		void ShowQuickSelect(const char* text, bool newShown);
		void SendQuickSelect();
		// 0x104C5560: tells the movie when the selection took effect
		void Update();
		// 0x104C56A0: takes the saved power
		void Reload();

		int slot;  // +4
		int power;  // +8
		bool shown;  // +0xC
		bool selectionPending;  // +0xD
		int selected;  // +0x10
		bool locked;  // +0x14
	};
}

#endif
