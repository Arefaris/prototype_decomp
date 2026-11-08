// The audio renderer driver of the kernel streaming devices (0x10ABA720 - 0x10ABCF20): the slots of the driver class
// that set a value with the device closed.
#include "code/audio/drivers.h"

namespace audio
{
	// 0x113276B0
	char WdmKsRendererDriver::unknownStatic;

	// FUNCTION: ENGINE 0x10ABA730
	const char* WdmKsRendererDriver::Slot1()
	{
		return &unknownStatic;
	}

	// FUNCTION: ENGINE 0x10ABA740
	bool WdmKsRendererDriver::Slot5()
	{
		return thread.IsCurrentThread();
	}

	// FUNCTION: ENGINE 0x10ABB8E0
	om::MetaTypeBase* WdmKsRendererDriver::GetMetaType()
	{
		om::MetaTypeBase*& cache = om::MetaTypeCache<WdmKsRendererDriver>::type;
		if (cache == 0)
		{
			cache = om::FindMetaType(typeid(WdmKsRendererDriver));
		}
		return cache;
	}

	// FUNCTION: ENGINE 0x10ABA750
	void WdmKsRendererDriver::SetLatency(unsigned int newLatency)
	{
		RendererDriver::SetLatency(newLatency);
	}

	// FUNCTION: ENGINE 0x10ABA760
	void WdmKsRendererDriver::SetSampleRate(unsigned int newSampleRate)
	{
		if (newSampleRate != RendererDriver::GetSampleRate())
		{
			unsigned int data = GetUserData();
			if (data != 0)
			{
				ClearUserData();
			}
			RendererDriver::SetSampleRate(newSampleRate);
			if (data != 0)
			{
				SetUserData(data);
			}
		}
	}

	// FUNCTION: ENGINE 0x10ABA7B0
	void WdmKsRendererDriver::SetNumberOfChannels(unsigned int newNumberOfChannels)
	{
		if (newNumberOfChannels != RendererDriver::GetNumberOfChannels())
		{
			unsigned int data = GetUserData();
			if (data != 0)
			{
				ClearUserData();
			}
			RendererDriver::SetNumberOfChannels(newNumberOfChannels);
			if (data != 0)
			{
				SetUserData(data);
			}
		}
	}

	// FUNCTION: ENGINE 0x10ABA800
	void WdmKsRendererDriver::SetWaveFormat(WAVEFORMAT newWaveFormat)
	{
		unsigned int data = GetUserData();
		if (data != 0)
		{
			ClearUserData();
		}
		waveFormat = newWaveFormat;
		if (data != 0)
		{
			SetUserData(data);
		}
	}

	// FUNCTION: ENGINE 0x10ABA840
	WAVEFORMAT WdmKsRendererDriver::GetWaveFormat() const
	{
		return waveFormat;
	}
}
