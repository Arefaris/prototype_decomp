// proto::GameEngine (RTTI, base engine::IGame, vftable 0x10E19CB0, 11 slots): the game the engine's main loop
// drives. Slot 1 (0x104E1ED0) makes the heaps, slot 9 (0x104E3840) starts the game up. No assert path names the unit
// (0x104E1440 - 0x104E7xxx), so the file name, the member names and the names of the other slots are guesses.
#ifndef PROTO_PROTOMAIN_H
#define PROTO_PROTOMAIN_H

namespace engine
{
	// The interface the main loop calls the game through (RTTI engine::IGame: eleven pure virtual functions)
	struct IGame
	{
	public:
		virtual void Slot0(int unused) = 0;
		virtual void Slot1() = 0;
		virtual void Slot2() = 0;
		virtual void Slot3() = 0;
		virtual void Slot4() = 0;
		virtual void Slot5() = 0;
		virtual const char* Slot6() = 0;
		virtual const char* Slot7() = 0;
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
		// 0x104E1EB0
		GameEngine();

		// The vftable (0x10E19CB0). Slot 0 is an empty function (0x104E1620), slot 1 makes the heaps (0x104E1ED0),
		// slot 2 destroys them again (0x104E1630), slots 3 - 5 reset the systems the game states use (0x104E1810,
		// 0x104E19B0, 0x104E19E0), slot 6 answers the registry key the game keeps its settings under and slot 7 the
		// name of the language setting (0x104E1A10, 0x104E1A20); slots 8 (0x104E3000) and 10 (0x104E2620, the
		// shut down) are left to the engine.
		virtual void Slot0(int unused);
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5();
		virtual const char* Slot6();
		virtual const char* Slot7();
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
