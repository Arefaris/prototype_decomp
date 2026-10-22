#include "code/engine/system/simulationdriver.h"
#include "code/engine/controller/inputsystem.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10897AC0
	SimulationDriver::SimulationDriver()
	{
		running = false;
		unknown89 = false;
		resuming = false;
		resumePending = false;
		rate = 30;
	}

	// FUNCTION: ENGINE 0x10897B00
	SimulationDriver::~SimulationDriver()
	{
	}

	// FUNCTION: ENGINE 0x10897B10
	void SimulationDriver::Slot1()
	{
		unsigned __int64 now = core::GetElapsedMicroseconds();
		unsigned __int64 delta = now - lastTime;
		time6.AddMicroseconds(delta);
		time5.SetMicroseconds(delta);
		lastTime = now;
	}

	// FUNCTION: ENGINE 0x10897B60
	void SimulationDriver::Slot2()
	{
	}

	// FUNCTION: ENGINE 0x10897B70
	void SimulationDriver::Slot3()
	{
		unsigned __int64 now = core::GetElapsedMicroseconds();
		unsigned __int64 elapsed = now - lastStepTime;
		unsigned __int64 step = rate == 0 ? 66666 : 1000000 / rate;
		if ((rate == 0 && elapsed > step) || elapsed > 250000)
		{
			elapsed = step;
			lastStepTime = now - step;
		}
		if (rate == 0)
		{
			if (elapsed >= 15000)
			{
				pendingSteps = 1;
				lastStepTime = now;
				time0.SetMicroseconds(elapsed);
				time2.SetSeconds(0.0f);
			}
		}
		else
		{
			pendingSteps += (unsigned int)(elapsed / step);
			unsigned __int64 remainder = elapsed % step;
			lastStepTime = now - remainder;
			time2.SetMicroseconds(remainder);
			time0.SetMicroseconds(step);
		}
		if (running && unknown89)
		{
			pendingSteps = 0;
		}
	}

	// FUNCTION: ENGINE 0x10897C80
	void SimulationDriver::Slot6()
	{
		if (running && !resuming)
		{
			time3.Clear();
			controller::InputSystem::Get()->CollectPlayers();
			return;
		}
		ISimulationDriver::Slot6();
		if (resuming)
		{
			resuming = false;
		}
	}

	// FUNCTION: ENGINE 0x10897CD0
	void SimulationDriver::Slot7()
	{
		if (running && !resuming)
		{
			time3.Clear();
			controller::InputSystem::Get()->CollectPlayers();
			return;
		}
		ISimulationDriver::Slot7();
	}

	// FUNCTION: ENGINE 0x10897D00
	bool SimulationDriver::Slot4()
	{
		if (pendingSteps > 0)
		{
			time1.Add(time0.milliseconds, time0.microseconds);
			pendingSteps--;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10897D30
	void SimulationDriver::Slot5()
	{
		if (running && resumePending)
		{
			resumePending = false;
			resuming = true;
		}
	}

	// FUNCTION: ENGINE 0x10897D60
	void SimulationDriver::SetUnknown70(int value)
	{
		rate = value;
		Slot9();
	}

	// FUNCTION: ENGINE 0x10897D80
	void SimulationDriver::Slot9()
	{
		ISimulationDriver::Slot9();
		pendingSteps = 0;
		lastStepTime = core::GetElapsedMicroseconds();
		lastTime = core::GetElapsedMicroseconds();
	}

	// FUNCTION: ENGINE 0x10897DB0
	bool SimulationDriver::Unknown10897DB0()
	{
		return running;
	}

	// FUNCTION: ENGINE 0x10897DC0
	void SimulationDriver::Unknown10897DC0(bool value)
	{
		running = value;
	}

	// FUNCTION: ENGINE 0x10897DD0
	void SimulationDriver::Unknown10897DD0(int value)
	{
		unknown89 = value;
	}

	// FUNCTION: ENGINE 0x10897DE0
	void SimulationDriver::Unknown10897DE0(int newRate)
	{
		if (!running)
		{
			Unknown10897DC0(true);
		}
		if (newRate > 0)
		{
			core::Time period(1000000 / (unsigned int)newRate, 0);
			time3 = period;
		}
		resumePending = true;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10897E40
