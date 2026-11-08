// The audio renderer driver of the ASIO devices (0x10AB91D0 - 0x10ABA600): the slots of the driver class that follow
// the buffers and the thread the device calls back on.
#include "code/audio/drivers.h"

// The kernel32 import, declared like the SDK does; the relinker's import libraries name the slot without the decoration
extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentThreadId();
#pragma comment(linker, "/alternatename:__imp__GetCurrentThreadId@0=__imp__GetCurrentThreadId")

namespace audio
{
	// 0x11327690
	AsioRendererDriver* AsioRendererDriver::current;

	// 0x11327694
	char AsioRendererDriver::unknownStatic;

	// FUNCTION: ENGINE 0x10AB91E0
	const char* AsioRendererDriver::Slot1()
	{
		return &unknownStatic;
	}

	// FUNCTION: ENGINE 0x10AB9340
	bool AsioRendererDriver::Slot5()
	{
		return threadId == GetCurrentThreadId();
	}

	// FUNCTION: ENGINE 0x10AB9360
	void __cdecl AsioRendererDriver::SampleRateDidChange(double newSampleRate)
	{
		current->deviceSampleRate = newSampleRate;
	}

	// FUNCTION: ENGINE 0x10AB9380
	void AsioRendererDriver::SetLatency(unsigned int newLatency)
	{
		RendererDriver::SetLatency(bufferSize);
	}

	// FUNCTION: ENGINE 0x10AB9390
	void AsioRendererDriver::SetSampleRate(unsigned int newSampleRate)
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

	// FUNCTION: ENGINE 0x10AB93D0
	void AsioRendererDriver::SetNumberOfChannels(unsigned int newNumberOfChannels)
	{
		RendererDriver::SetNumberOfChannels(outputChannels);
	}
}
