// engine::OLSGame and engine::OLSGameSystemLink (RTTI names): the online services' game session. It is told about online
// events as an OLS callback and about carried out state requests as a GameFlowManager callback (the second base, at +8).
// The platform layers (proto::OLSGameProto, OLSGameSystemLinkProto, OLSGameStub) override the slots that start and stop a
// session. Of the classes only what the layers use is declared (their units are 0x10887D20 - 0x10888B00); names other than
// the RTTI ones are guesses.
#ifndef ENGINE_ONLINE_OLSGAME_H
#define ENGINE_ONLINE_OLSGAME_H

#include "code/engine/frontend/privatedialogstate.h"
#include "code/engine/online/ols.h"

namespace engine
{
	class OLSGame : public OLS::Callback, public GameFlowManager::StateRequestCallback
	{
	public:
		// 0x108881B0: the game state the session runs in
		explicit OLSGame(int newState);

		// vftable slot 0 (0x10887FC0), slot 1 (deleting destructor 0x108881F0; the body 0x10887D80) and 2 - 10
		virtual void OnMessage(OLSMessage* message);
		virtual ~OLSGame();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		virtual void Slot10();
		// The state request callback's slot (0x108880C0)
		virtual void OnFinished(int state, bool aborted);

		int unknownC;
		void* unknown10;
		int unknown14;
		unsigned int flags;  // +0x18
		bool unknown1C;
		int state;  // +0x20
	};

	class OLSGameSystemLink : public OLSGame
	{
	public:
		// 0x10888960
		explicit OLSGameSystemLink(int newState);

		// vftable slot 1 (deleting destructor 0x10888A90; the body 0x10888990), 4, 7, 8, 9 and the added slot 11
		virtual ~OLSGameSystemLink();
		virtual void Slot4();
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		virtual void Slot11(int a);
		// The state request callback's slot (0x108889D0)
		virtual void OnFinished(int state, bool aborted);

		int unknown24;
	};
}

#endif
