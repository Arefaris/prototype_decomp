// engine::GameState, engine::PauseState and engine::IRealTimeTask (RTTI names). A game state is a numbered mode of the
// game (the start-up registers them with engine::AddGameState); the base has two pure virtual functions. The pause
// state (0x108822F0 - 0x10882700) adds four more and the fields 0x54 - 0x68. A real time task has one virtual function,
// called every frame by the task manager. Names other than the RTTI ones are guesses.
#ifndef ENGINE_GAMESTATE_H
#define ENGINE_GAMESTATE_H

#include "code/core/thread.h"

namespace engine
{
	class GameState
	{
	public:
		// 0x108366D0 (the unit of the game state table, gamestate.cpp): the id and the size of the fiber's stack
		GameState(int newId, int newStackSize);
		// The state is entered / left (vftable slots 0 and 1)
		virtual void Enter() = 0;
		virtual void Leave() = 0;
		// 0x10837990: runs the state's fiber until it yields; true when it finished
		bool Run(int mode);
		// 0x10837CE0 / 0x10837CF0: Run(1) enters the state, Run(2) leaves it
		bool RunEnter();
		bool RunLeave();

		int id;                // +4
		int running;           // +8: the mode the fiber was started in, 0 when it is not running
		core::Fiber fiber;     // +0xC
		int stackSize;         // +0x50
	};

	class PauseState : public GameState
	{
	public:
		// 0x10882620: the two values are kept at +0x54 and +0x58
		PauseState(int a, int b);
		// 0x108822F0
		~PauseState();

		virtual void Enter();
		virtual void Leave();
		// vftable slots 2 - 5 (0x10882420, 0x10882450, 0x10882470, 0x108823B0)
		virtual void Slot2(int player);
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5(bool enable);

		int unknown54;
		int unknown58;
		int unknown5C;
		int unknown60;
		int unknown64;
		int unknown68;
	};

	struct IRealTimeTask
	{
		virtual void Update(int a, int b, float time) = 0;
	};
}

#endif
