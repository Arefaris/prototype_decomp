// The simulation driver (unit 0x108366C0 - 0x108391C0, with the game states; no assert path names it, the file name
// and every name that RTTI does not give are guesses). The game states (engine::GameState, RTTI, two pure slots) sit in
// a table by id; the flow goes through requests (engine::GameStateRequest, a SyncCommands::SyncCallback) that the
// per-frame update (0x10838ED0) works off in a small state machine, stopping or starting the states on the state
// stack. The simulation driver (engine::ISimulationDriver, RTTI, ten slots, base SimulationDriverTimeData) keeps the
// times of the simulation steps.
#ifndef ENGINE_SYSTEM_SIMULATIONDRIVER_H
#define ENGINE_SYSTEM_SIMULATIONDRIVER_H

#include "code/core/time.h"

namespace engine
{
	// The times a simulation driver keeps (RTTI: engine::SimulationDriverTimeData; the member names are guesses)
	class SimulationDriverTimeData
	{
	public:
		// 0x108367E0 (the drivers' constructors inline it)
		SimulationDriverTimeData() : time0(0, 0), time1(0, 0), time2(0, 0), time3(0, 0), time4(0, 0)
		{
		}
		// 0x10836700: sums the step time into time3 and time4, scaled by the two factors when they are not 1
		void AddStep();

		core::Time time0;                // +0x00
		core::Time time1;                // +0x0C
		core::Time time2;                // +0x18
		core::Time time3;                // +0x24
		core::Time time4;                // +0x30
		float scaleA;                    // +0x3C
		float scaleB;                    // +0x40
	};

	// The driver of the simulation (RTTI: engine::ISimulationDriver): the base is at +4
	class ISimulationDriver : public SimulationDriverTimeData
	{
	public:
		// 0x108372E0
		ISimulationDriver();
		// 0x10837370 (the deleting destructor; the body is 0x10836820)
		virtual ~ISimulationDriver();
		virtual void Slot1() = 0;
		virtual void Slot2() = 0;
		virtual void Slot3() = 0;
		virtual bool Slot4() = 0;
		virtual void Slot5() = 0;
		// 0x108368B0 / 0x108368E0 / 0x10836970 / 0x10836990
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();

		// 0x10836850 / 0x10836870 / 0x10836890 / 0x108368A0: set the time fields as they are
		void SetTime1Raw(unsigned int a, unsigned int b, unsigned int c);
		void SetTime4Raw(unsigned int a, unsigned int b, unsigned int c);
		void SetScaleA(float value);
		void SetScaleB(float value);
		// 0x10836650: the time at +0x48
		core::Time GetTime5();

		core::Time time5;                // +0x48
		core::Time time6;                // +0x54
		core::Time time7;                // +0x60
		bool unknown6C;
		bool variablesRegistered;        // +0x6D
	};

	// The driver the game runs (RTTI: engine::SimulationDriver, 0x90 bytes): steps the simulation at a fixed rate (30 steps a
	// second at the start), or once per frame while the rate is 0. Unit 0x10897AC0 - 0x10897E60 (names other than the
	// RTTI ones are guesses).
	class SimulationDriver : public ISimulationDriver
	{
	public:
		// 0x10897AC0
		SimulationDriver();
		// 0x10897B00 (deleting destructor 0x10897E40)
		virtual ~SimulationDriver();

		// vftable slot 1 (0x10897B10): adds the time since the last call to time6 and sets time5 to it
		virtual void Slot1();
		// vftable slot 2 (0x10897B60): does nothing
		virtual void Slot2();
		// vftable slot 3 (0x10897B70): counts the steps due since the last call
		virtual void Slot3();
		// vftable slot 4 (0x10897D00): takes one due step off the count and adds the step time to time1
		virtual bool Slot4();
		// vftable slot 5 (0x10897D30)
		virtual void Slot5();
		// vftable slot 6 (0x10897C80), slot 7 (0x10897CD0), slot 9 (0x10897D80); slot 8 is the base's
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot9();

		// 0x10897D60: sets the rate and starts over
		void SetUnknown70(int value);
		// 0x10897DB0 / 0x10897DC0 / 0x10897DD0 / 0x10897DE0
		bool Unknown10897DB0();
		void Unknown10897DC0(bool value);
		void Unknown10897DD0(int value);
		void Unknown10897DE0(int rate);

		unsigned int rate;  // +0x70: steps a second, 0 for one per frame
		unsigned int pendingSteps;  // +0x74
		unsigned __int64 lastStepTime;  // +0x78
		unsigned __int64 lastTime;  // +0x80
		bool running;  // +0x88
		unsigned char unknown89;
		bool resuming;  // +0x8A
		bool resumePending;  // +0x8B
	};

	// 0x10836AD0: the simulation driver in force
	ISimulationDriver* GetSimulationDriver();
}

#endif
