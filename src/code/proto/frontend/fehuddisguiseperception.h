// proto::FEHudDisguisePerception (RTTI name; base proto::FEHudElement): the indicator of the head-up display that shows
// how close the enemies are to seeing through the player's disguises. It keeps one slot for each of the two disguise
// lanes of the movie and tells the awareness meter and the fight items about the hint state. The movie paths and
// function names are original, the member names are guessed. Unit 0x104CB790 - 0x104CC0A0 (no assert path; the file name is
// a guess).
#ifndef PROTO_FRONTEND_FEHUDDISGUISEPERCEPTION_H
#define PROTO_FRONTEND_FEHUDDISGUISEPERCEPTION_H

#include "code/proto/frontend/fehudelement.h"

namespace proto
{
	class FEHudDisguisePerception : public FEHudElement
	{
	public:
		// One lane of the indicator (0x260 bytes)
		class Slot
		{
		public:
			// 0x104CBF20
			Slot();
			// 0x104CBC50
			void Flush(bool force);
			// 0x104CBF90: the lane's number, which names its movie variables
			void SetIndex(int newIndex);
			// 0x104CBC80: moves the mask by the amount of the disguise that is blown; tells the movie when the alarm changes
			void SetBlown(float amount, bool announce, unsigned char alarmLevel);
			// 0x104CBE30
			void SetMaskVisible(bool visible);
			// 0x104CBE80 / 0x104CBEE0: tells the movie which disguise the lane shows (when it changed / again)
			void SetDisguise(int newDisguise);
			void ResendDisguise();

			FEHudVariableTemplate<SymbolPathStoragePolicy_FixedLength, 0> mask;  // +0
			FEHudVariableTemplate<SymbolPathStoragePolicy_FixedLength, 0> visible;  // +0x128
			int index;  // +0x250
			int disguise;  // +0x254
			bool blown;  // +0x258
			unsigned char alarm;  // +0x259
			bool maskVisible;  // +0x25A
		};

		// 0x104CBB20
		FEHudDisguisePerception();

		// vftable slots 0 and 1 (0x104CB790, 0x104CB900, which jumps to SetVisible)
		virtual void Update(bool force);
		virtual void OnShow(bool shown);

		// 0x104CB7F0
		void SetVisible(bool newVisible);
		// 0x104CB840: sends both lanes' disguises to the movie
		void ResendDisguises();
		// 0x104CB870: whether the hint may show
		bool CanShowHint();
		// 0x104CB910: shows or hides the hint and tells the player's object when it does
		void SetHint(bool shown);
		// 0x104CBA70
		void SetLane(int mode, int newDisguise, float amount, bool lane, unsigned char alarmLevel);

		Slot slots[2];  // +0x10
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> hintVisible;  // +0x4D0
		FEHudVariableTemplate<SymbolPathStoragePolicy_Literal, 0> visible;  // +0x578
		bool disguiseHidden;  // +0x620
	};
}

#endif
