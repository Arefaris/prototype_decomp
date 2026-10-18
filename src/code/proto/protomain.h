// proto::GameEngine (RTTI, base engine::IGame, vftable 0x10E19CB0, 11 slots): the game the engine's main loop
// drives. Slot 1 (0x104E1ED0) makes the heaps, slot 9 (0x104E3840) starts the game up. No assert path names the unit
// (0x104E1440 - 0x104E7xxx), so the file name, the member names and the names of the other slots are guesses.
#ifndef PROTO_PROTOMAIN_H
#define PROTO_PROTOMAIN_H

namespace engine
{
	// The interface the main loop calls the game through (RTTI engine::IGame: eleven pure virtual functions)
	class IGame
	{
	public:
		virtual void Slot0() = 0;
		virtual void Slot1() = 0;
		virtual void Slot2() = 0;
		virtual void Slot3() = 0;
		virtual void Slot4() = 0;
		virtual void Slot5() = 0;
		virtual void Slot6() = 0;
		virtual void Slot7() = 0;
		virtual void Slot8() = 0;
		virtual void Initialize(int unused) = 0;
		virtual void Slot10() = 0;
	};

	class SimulationDriver;
}

namespace proto
{
	// The game states the engine switches between (RTTI proto::InGameState 0x12C bytes, proto::FrontEndState 0xA8,
	// proto::GamePauseState 0x94); their constructors are all that start-up needs
	class InGameState
	{
	public:
		// 0x104E6790
		InGameState();
		unsigned char unknown0[0x12C];
	};

	class FrontEndState
	{
	public:
		// 0x104DE970
		FrontEndState();
		unsigned char unknown0[0xA8];
	};

	class GamePauseState
	{
	public:
		// 0x104E7710
		GamePauseState();
		unsigned char unknown0[0x94];
	};

	class GameEngine : public engine::IGame
	{
	public:
		// The vftable (0x10E19CB0). The first function is declared and never defined, so the vftable stays with the
		// engine's copy of the unit.
		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot8();
		// 0x104E3840: builds the managers and states of the game, the stream slot groups and the front end
		virtual void Initialize(int unused);
		virtual void Slot10();

		// 0x104E2540: applies the options of the command line to the state the game starts in (name guess)
		void Launch();

		InGameState* inGameState;
		FrontEndState* frontEndState;
		GamePauseState* pauseState;
		engine::SimulationDriver* simulationDriver;
	};
}

#endif
