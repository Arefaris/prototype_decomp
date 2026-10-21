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
		virtual void Slot4() = 0;
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

	// 0x10836AD0: the simulation driver in force
	ISimulationDriver* GetSimulationDriver();
}

#endif
