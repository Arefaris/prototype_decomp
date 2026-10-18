// proto::GamePauseState (RTTI name; the pause menu's game state, unit code/proto/architecture/pausestate.cpp from the
// assert paths, 0x104E6730 - 0x104E7E00): a pause state that is also a real time task and a callback of the online
// services. Of the unit this reconstruction covers the functions from the heap lending code to the destructor; the
// slot functions, the constructor and the rest are not part of it. Names other than the RTTI ones are guesses.
#ifndef PROTO_ARCHITECTURE_PAUSESTATE_H
#define PROTO_ARCHITECTURE_PAUSESTATE_H

#include "code/engine/gamestate.h"
#include "code/engine/online/ols.h"
#include "code/engine/system/streampackage.h"

namespace proto
{
	class GamePauseState : public engine::PauseState, public engine::IRealTimeTask, public engine::OLS::Callback
	{
	public:
		// 0x104E7710
		GamePauseState();
		// 0x104E7430
		~GamePauseState();

		// vftable slots 0, 1, 3 and 4 (0x104E6940, 0x104E6C70, 0x104E7100, 0x104E7110)
		virtual void Enter();
		virtual void Leave();
		virtual void Slot3();
		virtual void Slot4();
		// 0x104E6EC0
		virtual void Update(int a, int b, float time);
		// 0x104E7280: the user the event concerns is the current user
		virtual void OnMessage(engine::OLSMessage* message);

		// 0x104E74A0, 0x104E71C0, 0x104E7180, 0x104E71A0: the script functions fe_PauseGame, fe_UnpauseGame,
		// fe_PauseMenuToWOI and fe_WOIToPauseMenu
		void PauseGame();
		void UnpauseGame();
		void PauseMenuToWOI();
		void WOIToPauseMenu();
		// 0x104E74C0: borrows the memory of the shadow maps for the pause menu as a slot group of its own
		void BorrowShadowMapHeap();
		// 0x104E71D0: gives it back
		void ReturnShadowMapHeap();

		// The slot group made over the lent shadow map memory
		engine::StreamSlotGroup* borrowedHeap;
		int unknown7C;
		bool unknown80;
		bool unknown81;
		unsigned char unknown82[2];
		int unknown84;
		bool unknown88;
		bool unknown89;
		bool unknown8A;
		bool unknown8B;
		bool unknown8C;
		bool unknown8D;
		unsigned char unknown8E;
		bool unknown8F;
		bool unknown90;
	};
}

#endif
