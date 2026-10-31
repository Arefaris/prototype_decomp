// engine::PrivateDialogState (RTTI name): the game state a modal dialog of the front end runs in. It is a game state with
// three more bases: the callback the state requests answer to, a real time task and the callback the dialog's overlay calls
// the engine through. The dialog (engine::DialogState, dialogstate.h) owns it and answers its overlay calls. Unit 0x108E3E00 -
// 0x108E44F0 (no assert path; file name guessed); the member and method names are guesses.
#ifndef ENGINE_FRONTEND_PRIVATEDIALOGSTATE_H
#define ENGINE_FRONTEND_PRIVATEDIALOGSTATE_H

#include "code/engine/gamestate.h"

namespace engine
{
	class DialogState;
	class FEOverlay;

	// RTTI: engine::GameFlowManager::StateRequestCallback (one slot, 4 bytes): told when a state request was carried out
	class GameFlowManager
	{
	public:
		class StateRequestCallback
		{
		public:
			virtual void OnFinished(int state, bool aborted) = 0;
		};
	};

	// RTTI: engine::FEOverlay::Callback (a struct with one slot): what the overlay's movie calls the engine back with
	class FEOverlay
	{
	public:
		struct Callback
		{
			// 0x108E3E00 (the engine's copy of the constructor)
			Callback()
			{
			}
			virtual void OnCall(int call, int a, int b, int c) = 0;
		};
	};

	// The dialog states are numbered; the request functions of the game state table (system/gamestate.cpp)
	GameState* GetGameState(int id);
	void FreeGameState(int id);
	void AddGameState(void* stateObject, int id, int priority, int flag, int mode, int parent);
	int GetGameStateStatus(int id);
	// 0x10838B40 / 0x10838B80: the engine takes the callback as its SyncCommands::SyncCallback base, which this class's
	// callback has the same layout as
	void RequestGameState(int id, int mode, GameFlowManager::StateRequestCallback* callback);
	void RequestGameStateOverlay(int id, int mode, GameFlowManager::StateRequestCallback* callback);

	// RTTI: engine::PrivateDialogState (0xC0 bytes)
	class PrivateDialogState : public GameState, public GameFlowManager::StateRequestCallback, public IRealTimeTask,
		public FEOverlay::Callback
	{
	public:
		// 0x108E42D0
		PrivateDialogState(DialogState* newOwner, int newId, int newPriority, const char* newName, const char* newOverlay);
		// 0x108E3E10
		~PrivateDialogState();

		// vftable slot 0 (0x108E3FE0) and slot 1 (0x108E4100) of the game state
		virtual void Enter();
		virtual void Leave();
		// 0x108E4220 (the state requests): does nothing
		virtual void OnFinished(int state, bool aborted);
		// 0x108E41F0 (the real time task): hands the call to the dialog
		virtual void Update(UpdateContext context);
		// 0x108E4470 (the overlay's calls)
		virtual void OnCall(int call, int a, int b, int c);

		// 0x108E3E50: asks for the state to be entered (as an overlay of the running state unless the flag is set)
		bool Request(int newController, int flag);
		// 0x108E3F60: whether the dialog is up
		bool IsActive();
		// 0x108E3F70: whether the state is over
		bool IsDone();
		// 0x108E3FA0: the icon of the dialog and whether it is shown
		void SetIcon(int newIcon, bool visible);
		// 0x108E4390: closes the dialog
		void Close();
		// 0x108E3FC0 / 0x108E3FD0 / 0x108E4230 (not reconstructed)
		void Unknown108E3FC0();
		void Unknown108E3FD0();
		void Unknown108E4230();

		DialogState* owner;  // +0x60
		int stateId;  // +0x64
		int priority;  // +0x68
		char name[0x20];  // +0x6C
		char overlayName[0x20];  // +0x8C
		int icon;  // +0xAC
		bool iconVisible;  // +0xB0
		bool requested;  // +0xB1
		bool active;  // +0xB2
		bool covered;  // +0xB3
		bool inputPushed;  // +0xB4
		bool mouseVisible;  // +0xB5
		int controller;  // +0xB8
		FEOverlay* overlay;  // +0xBC
	};
}

#endif
