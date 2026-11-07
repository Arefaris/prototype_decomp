#include "code/engine/online/replay.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10900260
	ReplaySimDriver::ReplaySimDriver() : eventReader(0), eventWriter(0), inputReader(0), inputWriter(0), checksumReader(0),
		checksumWriter(0), hunter(0), inner(0), playbackFlagA4(false), playbackFlagA5(false), flagA6(false),
		unknownA7(false), unknownA8(false), flagA9(false), stepCount(0), extra(0)
	{
		for (int i = 0; i < 5; i++)
		{
			listeners[i] = 0;
		}
	}

	// FUNCTION: ENGINE 0x109002F0
	void ReplaySimDriver::Slot1()
	{
		inner->Slot1();
		time6 = inner->time6;
		time5 = inner->time5;
	}

	// FUNCTION: ENGINE 0x10900340
	void ReplaySimDriver::Slot2()
	{
		inner->Slot2();
	}

	// FUNCTION: ENGINE 0x109003F0
	void ReplaySimDriver::Slot5()
	{
		inner->Slot5();
		flagA9 = false;
	}

	// FUNCTION: ENGINE 0x10900D40
	void ReplaySimDriver::Stop()
	{
		if (inner != 0)
		{
			SetSimulationDriver(inner);
			inner = 0;
		}
		if (eventReader != 0)
		{
			delete eventReader;
			eventReader = 0;
		}
		if (eventWriter != 0)
		{
			eventWriter->Flush();
			delete eventWriter;
			eventWriter = 0;
		}
		if (inputReader != 0)
		{
			delete inputReader;
			inputReader = 0;
		}
		if (inputWriter != 0)
		{
			inputWriter->Flush();
			delete inputWriter;
			inputWriter = 0;
		}
		if (checksumReader != 0)
		{
			delete checksumReader;
			checksumReader = 0;
		}
		if (checksumWriter != 0)
		{
			checksumWriter->Flush();
			delete checksumWriter;
			checksumWriter = 0;
		}
		if (extra != 0)
		{
			delete extra;
			extra = 0;
		}
		playbackFlagA4 = false;
		playbackFlagA5 = false;
	}

	// FUNCTION: ENGINE 0x10900E80
	ReplaySimDriver::~ReplaySimDriver()
	{
		Stop();
		if (hunter != 0)
		{
			delete hunter;
			DesyncHunter::SetInstance(0);
			hunter = 0;
		}
	}

	// FUNCTION: ENGINE 0x10900350
	bool ReplaySimDriver::Slot4()
	{
		if (inputReader == 0 || RecordedInputsReady())
		{
			if (eventReader == 0 || stepCount < 1)
			{
				if (eventReader == 0)
				{
					unknownA8 = inner->Slot4();
				}
				if (unknownA8)
				{
					core::Time* step = &time0;
					time1.AddMicroseconds((unsigned __int64)step->milliseconds * 1000 + step->microseconds);
					step->SetSeconds(1.0f / 30.0f);
					stepCount++;
					unknownA8 = false;
					return true;
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10900410
	void ReplaySimDriver::Slot9()
	{
		ISimulationDriver::Slot9();
		inner->Slot9();
		for (int i = 0; i < 5; i++)
		{
			if (listeners[i] != 0)
			{
				listeners[i]->OnReset();
			}
		}
	}

	// FUNCTION: ENGINE 0x109005D0
	void ReplaySimDriver::NotifyListeners()
	{
		if (!flagA6)
		{
			for (int i = 0; i < 5; i++)
			{
				if (listeners[i] != 0)
				{
					listeners[i]->OnStep(eventWriter);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10900610
	void ReplaySimDriver::PollListeners()
	{
		if (!flagA6)
		{
			for (int i = 0; i < 5; i++)
			{
				if (listeners[i] != 0)
				{
					playbackFlagA5 = playbackFlagA5 || listeners[i]->CheckStep(eventReader);
				}
			}
			if (playbackFlagA5)
			{
				if (inputWriter != 0)
				{
					inputWriter->Flush();
				}
				if (checksumWriter != 0)
				{
					checksumWriter->Flush();
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10900860
	void ReplaySimDriver::Slot3()
	{
		stepCount = 0;
		inner->Slot3();
		unknownA8 = false;
		if (eventReader != 0)
		{
			while (inner->Slot4())
			{
				unknownA8 = true;
			}
		}
		if (unknownA7 && !flagA6 && eventReader != 0)
		{
			PollListeners();
			if (inputReader != 0)
			{
				LoadRecordedInputs(inputReader);
			}
			unknownA7 = false;
		}
		flagA9 = true;
	}

	// FUNCTION: ENGINE 0x10900900
	void ReplaySimDriver::Slot6()
	{
		ISimulationDriver::Slot6();
		if (eventWriter != 0)
		{
			NotifyListeners();
		}
		if (inputWriter != 0)
		{
			SaveRecordedInputs(inputWriter);
		}
		if (hunter != 0 && !flagA6)
		{
			VerifyChecksum();
			RecordChecksum();
		}
		unknownA7 = true;
	}

	// FUNCTION: ENGINE 0x10900450
	void ReplaySimDriver::AddListener(IReplayListener* listener)
	{
		for (int i = 0; i < 5; i++)
		{
			if (listeners[i] == 0)
			{
				listeners[i] = listener;
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x10900480
	void ReplaySimDriver::RemoveListener(IReplayListener* listener)
	{
		for (int i = 0; i < 5; i++)
		{
			if (listeners[i] == listener)
			{
				listeners[i] = 0;
				return;
			}
		}
	}
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10900EC0
