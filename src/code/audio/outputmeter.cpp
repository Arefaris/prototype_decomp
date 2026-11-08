// The meter of the audio output (0x105E47C0 - 0x105E4CC5; the file name is guessed).
#include "code/audio/outputmeter.h"
#include "code/core/criticalsection.h"
#include "code/core/time.h"

namespace audio
{
	static OutputMeter* sOutputMeter;  // 0x112768E0

	// FUNCTION: ENGINE 0x105E47C0
	OutputMeter::OutputMeter()
	{
		startTime = 0;
		core::CriticalSectionInit(section);
		locked = false;
		unsigned int now = static_cast<unsigned int>(core::GetMicroseconds());
		unknownE8 = false;
		for (int i = 0; i < 8; i++)
		{
			heldTime[i] = now;
		}
		for (int i = 0; i < 8; i++)
		{
			peak[i] = 0.0f;
			held[i] = 0.0f;
		}
		firstWord = 0;
		historyIndex = 0;
		unknownE9 = false;
		sOutputMeter = this;
	}

	// FUNCTION: ENGINE 0x105E4880
	OutputMeter::~OutputMeter()
	{
		sOutputMeter = 0;
		core::CriticalSectionDelete(section);
	}

	// FUNCTION: ENGINE 0x105E48F0
	OutputMeter* OutputMeter::Get()
	{
		return sOutputMeter;
	}

	// FUNCTION: ENGINE 0x105E48A0
	void OutputMeter::Lock()
	{
		core::CriticalSectionEnter(section);
		locked = true;
	}

	// FUNCTION: ENGINE 0x105E48C0
	void OutputMeter::Unlock()
	{
		locked = false;
		core::CriticalSectionLeave(section);
	}

	// FUNCTION: ENGINE 0x105E48E0
	bool OutputMeter::IsLocked() const
	{
		return locked;
	}

	// FUNCTION: ENGINE 0x105E4900
	void OutputMeter::Restart()
	{
		startTime = static_cast<unsigned int>(core::GetMicroseconds());
	}
}
