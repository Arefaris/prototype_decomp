// engine::GameState, engine::PauseState and engine::IRealTimeTask (RTTI names). A game state is a numbered mode of the
// game (the start-up registers them with engine::AddGameState); the base has two pure virtual functions. The pause
// state (0x108822F0 - 0x10882700) adds four more and the fields 0x54 - 0x68. A real time task has one virtual function,
// called every frame by the task manager. Names other than the RTTI ones are guesses.
#ifndef ENGINE_GAMESTATE_H
#define ENGINE_GAMESTATE_H

namespace engine
{
	class GameState
	{
	public:
		// The state is entered / left (vftable slots 0 and 1)
		virtual void Enter() = 0;
		virtual void Leave() = 0;

		unsigned char unknown4[0x54 - 4];
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
