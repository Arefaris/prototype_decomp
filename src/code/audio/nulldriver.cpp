// The driver that renders to no device (0x10AB72B0 - 0x10AB76F0).
#include "code/audio/nulldriver.h"
#include "code/core/time.h"

namespace audio
{
	// FUNCTION: ENGINE 0x10AB72B0
	NullRendererDriverModel::NullRendererDriverModel() :
		RendererDriverModel(om::String::Wrap("Null"))
	{
	}

	// FUNCTION: ENGINE 0x10AB76B0
	void NullRendererDriverModel::CreateDriver(RenderDriverModelHarness* harness)
	{
		harness->AddDriver(new NullRendererDriver);
	}

	// FUNCTION: ENGINE 0x10AB72F0
	void NullRendererDriverModel::Slot1()
	{
	}

	// FUNCTION: ENGINE 0x10AB7410
	NullRendererDriver::RendererThread::RendererThread(NullRendererDriver* newDriver) :
		Thread("audio::NullRendererDriverThread", &om::ThreadSettings(-1), om::gThreadEntryCallback),
		driver(newDriver)
	{
	}

	// FUNCTION: ENGINE 0x10AB7450
	// NONMATCHING: the loop's registers (58.3 %)
#ifdef NONMATCHING
	void NullRendererDriver::RendererThread::Run()
	{
		unsigned int last = core::GetMilliseconds();
		unsigned int remainder = 0;
		while (!IsStopping())
		{
			om::SleepMilliseconds(4);
			driver->GetLatency();
			unsigned int now = core::GetMilliseconds();
			unsigned int samples = driver->GetSampleRate() * (now - last) / 1000 + remainder;
			unsigned int blocks = samples / 256;
			remainder = samples - blocks * 256;
			for (; blocks != 0; blocks--)
			{
				RendererUser* user = reinterpret_cast<RendererUser*>(driver->GetUserData());
				user->Render(driver->channels, driver->GetNumberOfChannels());
			}
			last = now;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10AB7590
	// NONMATCHING: the engine stores the vftable before the buffer pointer (94.1 %)
#ifdef NONMATCHING
	NullRendererDriver::NullRendererDriver() :
		RendererDriver(om::String::Wrap("No Driver")),
		alignedBuffer(reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(buffer) & 0xFFFFFFF0)),
		thread(this)
	{
		SetLatencyRange(GetMinLatency(), 0x1400);
		SetLatency(10);
		SetSampleRateRange(48000, 48000);
		SetSampleRate(48000);
		for (unsigned int i = 0; i < 8; i++)
		{
			channels[i] = alignedBuffer;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10AB7320
	NullRendererDriver::~NullRendererDriver()
	{
	}

	// FUNCTION: ENGINE 0x10AB7550
	const char* NullRendererDriver::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10AB7370
	const char* NullRendererDriver::Slot1()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10AB7380
	void NullRendererDriver::SetUserData(unsigned int newUserData)
	{
		RendererDriver::SetUserData(newUserData);
		thread.SetPriority(5);
		thread.Start();
		SetDescription(om::String::Wrap("Ok (Emulating Sound Card)"), true);
	}

	// FUNCTION: ENGINE 0x10AB73E0
	void NullRendererDriver::ClearUserData()
	{
		thread.stopping = true;
		thread.Stop();
		RendererDriver::ClearUserData();
	}

	// FUNCTION: ENGINE 0x10AB7400
	bool NullRendererDriver::Slot5()
	{
		return thread.IsCurrentThread();
	}
}
