// engine::OLSGame (RTTI name; bases OLS::Callback and GameFlowManager::StateRequestCallback): what the online services
// run on this machine to take the game from one state to the next (the platform layers derive from it and implement
// the slots behind the common ones). The OLS singleton keeps the games at +0x8C. Unit 0x10887D20 - 0x1088831E (no
// assert path; the file name is a guess). Names other than the RTTI ones are guesses.
#ifndef ENGINE_ONLINE_OLSGAME_H
#define ENGINE_ONLINE_OLSGAME_H

#include "code/engine/gameflowmanager.h"
#include "code/engine/online/ols.h"

namespace engine
{
	class OLSGame : public OLS::Callback, public GameFlowManager::StateRequestCallback
	{
	public:
		// One setting of the game (0x10 bytes; names guessed)
		struct Setting
		{
			int value;
			int unknown4;
			int key;  // +8
			int unknownC;
		};

		// vftable slots 0 - 10 (0x10887FC0, the deleting destructor 0x108881F0, 0x10887DE0, 0x10887DF0, 0x10887E00,
		// 0x10888490, 0x10888280, 0x10888840, 0x10888210, 0x10887F60, 0x10887FB0)
		virtual void OnMessage(OLSMessage* message);
		virtual ~OLSGame();
		// slot 2: the state request in flight is cancelled
		virtual void CancelState();
		// slot 3: the game goes over to its state
		virtual void RequestTransitionState();
		virtual void Slot4();
		virtual void Slot5();
		// slot 6: sends the pending request when there is one
		virtual void Update();
		virtual void Slot7();
		virtual void Shutdown();
		virtual void Slot9();
		virtual void Slot10();
		// the callback's slot 0 (0x108880C0)
		virtual void OnFinished(int state, bool aborted);

		// 0x10887DA0: sends the pending request once the user table allows it
		void TryRequestState();
		// 0x10888080: sets the value of the setting with that key
		void SetSetting(int key, int value);
		// 0x10888290: a request for the state is pending
		void RequestState(bool flag);
		// 0x10887EF0 / 0x108882C0
		bool Unknown10887EF0();
		bool Unknown108882C0();

		int settingCount;  // +0xC
		Setting* settings;  // +0x10
		int unknown14;
		unsigned int flags;  // +0x18: 1 for a request pending
		bool unknown1C;
		int state;  // +0x20
	};
}

#endif
