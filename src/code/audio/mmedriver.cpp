// The audio renderer driver of the multimedia extensions (0x10AB7770 - 0x10AB8A40): plays what the mixer renders through
// the wave output of the operating system, two blocks of samples at a time.
#include "code/audio/drivers.h"
#include "code/core/criticalsection.h"
#include "code/om/invoke.h"
#include "code/om/metaproperty.h"
#include <string.h>

// The winmm imports, declared like the SDK does; the relinker's import libraries name the slots without the decoration
extern "C"
{
	__declspec(dllimport) unsigned int __stdcall waveOutOpen(void** device, unsigned int deviceId, const void* format,
		unsigned long callback, unsigned long instance, unsigned long flags);
	__declspec(dllimport) unsigned int __stdcall waveOutClose(void* device);
	__declspec(dllimport) unsigned int __stdcall waveOutReset(void* device);
	__declspec(dllimport) unsigned int __stdcall waveOutPrepareHeader(void* device, audio::WaveHeader* header, unsigned int size);
	__declspec(dllimport) unsigned int __stdcall waveOutUnprepareHeader(void* device, audio::WaveHeader* header, unsigned int size);
	__declspec(dllimport) unsigned int __stdcall waveOutWrite(void* device, audio::WaveHeader* header, unsigned int size);
}
#pragma comment(linker, "/alternatename:__imp__waveOutOpen@24=__imp__waveOutOpen")
#pragma comment(linker, "/alternatename:__imp__waveOutClose@4=__imp__waveOutClose")
#pragma comment(linker, "/alternatename:__imp__waveOutReset@4=__imp__waveOutReset")
#pragma comment(linker, "/alternatename:__imp__waveOutPrepareHeader@12=__imp__waveOutPrepareHeader")
#pragma comment(linker, "/alternatename:__imp__waveOutUnprepareHeader@12=__imp__waveOutUnprepareHeader")
#pragma comment(linker, "/alternatename:__imp__waveOutWrite@12=__imp__waveOutWrite")

// The identifier of the sample format of whole numbers (KSDATAFORMAT_SUBTYPE_PCM of the SDK, a GUID)
struct SampleFormatId
{
	unsigned int words[4];
};
extern "C" extern const SampleFormatId KSDATAFORMAT_SUBTYPE_PCM;

namespace audio
{
	// The format of the samples the device is opened with (WAVEFORMATEXTENSIBLE)
	struct DeviceFormat
	{
		unsigned short formatTag;
		unsigned short channels;
		unsigned int samplesPerSec;
		unsigned int avgBytesPerSec;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		unsigned short extraSize;
		unsigned short validBitsPerSample;
		unsigned int channelMask;
		SampleFormatId subFormat;
	};

	// The settings of a thread that may run on any processor
	struct AnyProcessorSettings : om::ThreadSettings
	{
		AnyProcessorSettings()
		{
			processor = -1;
		}
	};

	// The comparisons of the driver's values (out of line in the engine, names guessed)
	// FUNCTION: ENGINE 0x10AB7A60
	bool Equal(const unsigned int* first, const unsigned int* second)
	{
		if (*first == *second)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10AB7A70
	bool Equal(const WAVEFORMAT* first, const WAVEFORMAT* second)
	{
		if (*first == *second)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10AB7BF0
	bool Equal(void* const* first, void* const* second)
	{
		if (*first == *second)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10AB7A90
	void ClearFlags(unsigned int* flags, const unsigned int* mask)
	{
		*flags &= ~*mask;
	}

	// FUNCTION: ENGINE 0x10AB7C90
	bool Succeeded(unsigned int result)
	{
		unsigned int success = 0;
		return Equal(&result, &success);
	}

	// FUNCTION: ENGINE 0x10AB8280
	bool NotEqual(void* const* first, void* const* second)
	{
		if (Equal(first, second))
		{
			return false;
		}
		return true;
	}

	// The functions the driver uses (declared here, their definitions are above)
	bool Succeeded(unsigned int result);
	bool NotEqual(void* const* first, void* const* second);

	// The callback of the device: a block was played (the message is 0x3BD)
	// FUNCTION: ENGINE 0x10AB7950
	static void __stdcall WaveOutProc(void* device, unsigned int message, unsigned long instance, unsigned long parameter1, unsigned long parameter2)
	{
		MmeRendererDriver* driver = reinterpret_cast<MmeRendererDriver*>(instance);
		if (message == 0x3BD && !driver->closing)
		{
			core::SemaphoreRelease(&driver->semaphore, 1);
		}
	}

	// FUNCTION: ENGINE 0x10AB7980
	MmeRendererDriver::Thread::Thread(MmeRendererDriver* newDriver) :
		om::Thread("audio::MmeRendererDriver", &AnyProcessorSettings(), om::gThreadEntryCallback),
		driver(newDriver)
	{
	}

	// FUNCTION: ENGINE 0x10AB8080
	void MmeRendererDriver::Thread::Run()
	{
		core::SemaphoreWait(&driver->semaphore);
		while (!IsStopping())
		{
			unsigned int played = 1;
			RenderCallback* callback = reinterpret_cast<RenderCallback*>(driver->GetUserData());
			callback->Render(driver->mixBins, driver->GetNumberOfChannels(), driver->GetLatency());
			WaveHeader* header;
			if (driver->headers[0].flags & 1)
			{
				header = &driver->headers[0];
			}
			else
			{
				header = &driver->headers[1];
			}
			ClearFlags(&header->flags, &played);
			short* samples = reinterpret_cast<short*>(header->data);
			for (unsigned int sample = 0; sample < driver->GetLatency(); sample++)
			{
				for (unsigned int channel = 0; channel < driver->GetNumberOfChannels(); channel++)
				{
					*samples++ = static_cast<short>(driver->mixBins[channel][sample] * 32767.0f);
				}
			}
			waveOutWrite(driver->device, header, 0x20);
			core::SemaphoreWait(&driver->semaphore);
		}
	}

	// FUNCTION: ENGINE 0x10AB7770
	MmeRendererDriver::~MmeRendererDriver()
	{
	}

	// 0x1132767C
	char MmeRendererDriver::unknownStatic;

	// FUNCTION: ENGINE 0x10AB77D0
	const char* MmeRendererDriver::Slot1()
	{
		return &unknownStatic;
	}

	// FUNCTION: ENGINE 0x10AB77E0
	bool MmeRendererDriver::Slot5()
	{
		return thread.IsCurrentThread();
	}

	// FUNCTION: ENGINE 0x10AB85C0
	om::MetaTypeBase* MmeRendererDriver::GetMetaType()
	{
		om::MetaTypeBase*& cache = om::MetaTypeCache<MmeRendererDriver>::type;
		if (cache == 0)
		{
			cache = om::FindMetaType(typeid(MmeRendererDriver));
		}
		return cache;
	}

	// FUNCTION: ENGINE 0x10AB7840
	void MmeRendererDriver::SetSampleRate(unsigned int newSampleRate)
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

	// FUNCTION: ENGINE 0x10AB78D0
	void MmeRendererDriver::SetNumberOfChannels(unsigned int newNumberOfChannels)
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

	// FUNCTION: ENGINE 0x10AB7910
	void MmeRendererDriver::SetLatency(unsigned int newLatency)
	{
		unsigned int data = GetUserData();
		if (data != 0)
		{
			ClearUserData();
		}
		RendererDriver::SetLatency(newLatency);
		if (data != 0)
		{
			SetUserData(data);
		}
	}

	// FUNCTION: ENGINE 0x10AB7880
	void MmeRendererDriver::SetWaveFormat(WAVEFORMAT newWaveFormat)
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

	// FUNCTION: ENGINE 0x10AB78C0
	WAVEFORMAT MmeRendererDriver::GetWaveFormat() const
	{
		return waveFormat;
	}

	// FUNCTION: ENGINE 0x10AB85E0
	void MmeRendererDriver::ClearUserData()
	{
		void* none = 0;
		if (NotEqual(&none, &device))
		{
			closing = true;
			waveOutReset(device);
			thread.stopping = true;
			core::SemaphoreRelease(&semaphore, 1);
			thread.Stop();
			for (int i = 0; i < 2; i++)
			{
				waveOutUnprepareHeader(device, &headers[i], 0x20);
			}
			waveOutClose(device);
			device = 0;
		}
		for (int i = 0; i < 2; i++)
		{
			unsigned int size = RendererDriver::GetNumberOfChannels() * RendererDriver::GetLatency() * 2;
			om::Release(headers[i].data, size, 0x80);
			headers[i].data = 0;
		}
		for (unsigned int channel = 0; channel < RendererDriver::GetNumberOfChannels(); channel++)
		{
			om::Release(mixBins[channel], RendererDriver::GetLatency() * 4, 0x80);
		}
		om::Release(mixBins, RendererDriver::GetNumberOfChannels() * 4, 4);
		mixBins = 0;
		RendererDriver::ClearUserData();
	}

	// FUNCTION: ENGINE 0x10AB7E30
	void MmeRendererDriver::SetUserData(unsigned int newUserData)
	{
		RendererDriver::SetUserData(newUserData);
		closing = false;
		mixBins = static_cast<float**>(om::Allocate("MmeRendererDriver::mppMixBins", RendererDriver::GetNumberOfChannels() * 4, 4));
		for (unsigned int channel = 0; channel < RendererDriver::GetNumberOfChannels(); channel++)
		{
			mixBins[channel] = static_cast<float*>(om::Allocate("MmeRendererDriver::mppMixBin", RendererDriver::GetLatency() * 4, 0x80));
		}
		for (int i = 0; i < 2; i++)
		{
			WaveHeader& header = headers[i];
			memset(&header, 0, sizeof(WaveHeader));
			unsigned int size = RendererDriver::GetNumberOfChannels() * RendererDriver::GetLatency() * 2;
			void* data = om::Allocate("WaveHdr data", size, 0x80);
			header.data = static_cast<char*>(data);
			header.bufferLength = size;
			if (size > 0)
			{
				memset(data, 0, size);
			}
		}
		DeviceFormat format;
		format.channels = static_cast<unsigned short>(RendererDriver::GetNumberOfChannels());
		format.samplesPerSec = RendererDriver::GetSampleRate();
		format.blockAlign = format.channels * 2;
		format.avgBytesPerSec = format.blockAlign * format.samplesPerSec;
		format.bitsPerSample = 16;
		format.subFormat = KSDATAFORMAT_SUBTYPE_PCM;
		format.channelMask = 0;
		WAVEFORMAT extensible = WAVEFORMAT_EXTENSIBLE;
		if (Equal(&extensible, &waveFormat))
		{
			format.formatTag = 0xFFFE;
			format.extraSize = 0x28;
			format.validBitsPerSample = 0;
		}
		else
		{
			format.formatTag = 1;
			format.extraSize = 0;
		}
		unsigned int result = waveOutOpen(&device, deviceId, &format, reinterpret_cast<unsigned long>(&WaveOutProc), reinterpret_cast<unsigned long>(this), 0x30000);
		if (Succeeded(result))
		{
			thread.SetPriority(5);
			thread.Start();
			for (int i = 0; i < 2; i++)
			{
				waveOutPrepareHeader(device, &headers[i], 0x20);
				waveOutWrite(device, &headers[i], 0x20);
			}
			om::String message("Ok", false);
			SetDescription(message, true);
		}
		else
		{
			om::String message("Format Not Supported", false);
			SetDescription(message, false);
		}
	}

	// FUNCTION: ENGINE 0x10AB7CB0
	// NONMATCHING: the engine builds the two parts of the name before the call that joins them and passes the result in place (91.8 %)
#ifdef NONMATCHING
	// The name of a driver: the prefix and the name of the device
	static __forceinline om::String JoinName(const om::String& prefix, const om::String& name)
	{
		return prefix + name;
	}

	MmeRendererDriver::MmeRendererDriver(unsigned int newDeviceId, const WaveOutCaps* newCaps) :
		RendererDriver(JoinName(om::String("[MME] ", false), om::String(newCaps->name, true))),
		deviceId(newDeviceId),
		waveFormat(WAVEFORMAT_EX),
		thread(this)
	{
		SetNumberOfChannelsRange(1, 16);
		SetSampleRateRange(1, 96000);
		SetLatencyRange(0x200, 0x1400);
		RendererDriver::SetNumberOfChannels(2);
		RendererDriver::SetSampleRate(44100);
		RendererDriver::SetLatency(0xA00);
		om::FixedArray<unsigned int, 8> map;
		map.items[0] = 0;
		map.items[1] = 1;
		map.items[2] = 2;
		map.items[3] = 3;
		map.items[4] = 6;
		map.items[5] = 7;
		map.items[6] = 4;
		map.items[7] = 5;
		RendererDriver::SetSurroundChannelMap(map);
		device = 0;
		caps = *newCaps;
		mixBins = 0;
	}
#endif
}

namespace om
{
	// The forms of the wave format enumeration (the copies of the other drivers are left to the engine)
	// FUNCTION: ENGINE 0x10AB84E0
	template void WriteResult<audio::WAVEFORMAT>(BinaryStream*, const audio::WAVEFORMAT&);
	// FUNCTION: ENGINE 0x10AB8560
	template bool ReadText<audio::WAVEFORMAT>(const TextValue*, audio::WAVEFORMAT*);
	// FUNCTION: ENGINE 0x10AB8590
	template void WriteText<audio::WAVEFORMAT>(TextValue*, const audio::WAVEFORMAT&);
	// FUNCTION: ENGINE 0x10AB88A0
	template bool ReadBinary<audio::WAVEFORMAT>(BinaryStream*, audio::WAVEFORMAT*);
	// FUNCTION: ENGINE 0x10AB88D0
	template bool WriteBinary<audio::WAVEFORMAT>(BinaryStream*, const audio::WAVEFORMAT&);
	// FUNCTION: ENGINE 0x10AB8F80
	template audio::WAVEFORMAT ArgumentReader<audio::WAVEFORMAT>::Read(BinaryStream*, GarbageList*);
}
