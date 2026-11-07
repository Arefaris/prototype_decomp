// The audio renderer driver of the XAudio2 device (0x10AC2080 - 0x10AC3400): converts what the mixer renders to 16 bit
// samples on a thread of its own and submits them to a source voice.
#include "code/audio/drivers.h"
#include "code/core/criticalsection.h"
#include <new>
#include <string.h>

#pragma function(memcpy)

namespace audio
{
	// The settings of a thread that may run on any processor
	struct AnyProcessorSettings : om::ThreadSettings
	{
		AnyProcessorSettings()
		{
			processor = -1;
		}
	};

	// The name of a driver: the prefix and the name of the device
	static __forceinline om::String JoinName(const om::String& prefix, const om::String& name)
	{
		return prefix + name;
	}

	// FUNCTION: ENGINE 0x10AC2810
	XAudio2RendererDriver::Thread::Thread(XAudio2RendererDriver* newDriver) :
		om::Thread("audio::XAudio2RendererDriver", &AnyProcessorSettings(), om::gThreadEntryCallback),
		driver(newDriver)
	{
	}

	// FUNCTION: ENGINE 0x10AC2C90
	void XAudio2RendererDriver::Thread::Run()
	{
		unsigned short index = 0;
		core::SemaphoreWait(&driver->semaphore);
		while (!IsStopping())
		{
			RenderCallback* callback = reinterpret_cast<RenderCallback*>(driver->GetUserData());
			callback->Render(driver->mixBins, driver->GetNumberOfChannels(), 0x100);
			XAudioBuffer* buffer = &driver->buffers[index];
			short* samples = static_cast<short*>(buffer->audioData);
			for (unsigned int sample = 0; sample < 0x100; sample++)
			{
				for (unsigned int channel = 0; channel < driver->GetNumberOfChannels(); channel++)
				{
					*samples++ = static_cast<short>(driver->mixBins[channel][sample] * 32767.0f);
				}
			}
			om::ThreadSafeRefCount::Release(&driver->queuedBuffers);
			driver->sourceVoice->lpVtbl->SubmitSourceBuffer(driver->sourceVoice, buffer, 0);
			index = (index + 1) % driver->numberOfBuffers;
			core::SemaphoreWait(&driver->semaphore);
		}
	}

	// FUNCTION: ENGINE 0x10AC21A0
	XAudio2RendererDriver::~XAudio2RendererDriver()
	{
	}

	// FUNCTION: ENGINE 0x10AC2230
	void __stdcall XAudio2RendererDriver::OnVoiceProcessingPassStart(unsigned int bytesRequired)
	{
	}

	// FUNCTION: ENGINE 0x10AC2220
	void __stdcall XAudio2RendererDriver::OnVoiceProcessingPassEnd()
	{
	}

	// FUNCTION: ENGINE 0x10AC2210
	void __stdcall XAudio2RendererDriver::OnStreamEnd()
	{
	}

	// FUNCTION: ENGINE 0x10AC2240
	void __stdcall XAudio2RendererDriver::OnBufferStart(void* bufferContext)
	{
	}

	// FUNCTION: ENGINE 0x10AC2250
	void __stdcall XAudio2RendererDriver::OnLoopEnd(void* bufferContext)
	{
	}

	// FUNCTION: ENGINE 0x10AC2C40
	void __stdcall XAudio2RendererDriver::OnBufferEnd(void* bufferContext)
	{
		core::SemaphoreRelease(&semaphore, 1);
		int queued = om::ThreadSafeRefCount::AddRef(&queuedBuffers);
		if (Equal(&queued, reinterpret_cast<const int*>(&numberOfBuffers)))
		{
			playedBuffers++;
		}
	}

	// FUNCTION: ENGINE 0x10AC2260
	void __stdcall XAudio2RendererDriver::OnVoiceError(void* bufferContext, long error)
	{
	}

	// FUNCTION: ENGINE 0x10AC2E90
	om::MetaTypeBase* XAudio2RendererDriver::GetMetaType()
	{
		om::MetaTypeBase*& cache = om::MetaTypeCache<XAudio2RendererDriver>::type;
		if (cache == 0)
		{
			cache = om::FindMetaType(typeid(XAudio2RendererDriver));
		}
		return cache;
	}

	// 0x113276EC
	int XAudio2RendererDriver::unknownStatic;

	// FUNCTION: ENGINE 0x10AC2270
	void* XAudio2RendererDriver::Slot1()
	{
		return &unknownStatic;
	}

	// FUNCTION: ENGINE 0x10AC2700
	bool XAudio2RendererDriver::Slot5()
	{
		return thread.IsCurrentThread();
	}

	// FUNCTION: ENGINE 0x10AC2C30
	int XAudio2RendererDriver::Slot17()
	{
		return AtomicRead(&playedBuffers);
	}

	// FUNCTION: ENGINE 0x10AC2280
	// NONMATCHING: the engine loads the vtable slot of the engine call before the arguments and builds the status text in every branch (61.7 %)
#ifdef NONMATCHING
	void XAudio2RendererDriver::SetUserData(unsigned int newUserData)
	{
		RendererDriver::SetUserData(newUserData);
		open = false;
		queuedBuffers = 0;
		playedBuffers = 0;
		mixBins = static_cast<float**>(om::Allocate("XAudio2RendererDriver::mppMixBins", RendererDriver::GetNumberOfChannels() * 4, 4));
		for (unsigned int channel = 0; channel < RendererDriver::GetNumberOfChannels(); channel++)
		{
			mixBins[channel] = static_cast<float*>(om::Allocate("XAudio2RendererDriver::mppMixBin", 0x400, 0x80));
		}
		buffers = static_cast<XAudioBuffer*>(om::Allocate("XAudio2RendererDriver::mXAudioBuffers", numberOfBuffers * sizeof(XAudioBuffer), 4));
		for (unsigned int i = 0; i < numberOfBuffers; i++)
		{
			memset(&buffers[i], 0, sizeof(XAudioBuffer));
			unsigned int size = RendererDriver::GetNumberOfChannels() << 9;
			buffers[i].audioData = om::Allocate("XAudioBuffer data", size, 0x80);
			buffers[i].flags = 0;
			buffers[i].playBegin = 0;
			buffers[i].playLength = 0;
			buffers[i].loopBegin = 0;
			buffers[i].loopLength = 0;
			buffers[i].loopCount = 0;
			buffers[i].context = 0;
			buffers[i].audioBytes = size;
			void* data = buffers[i].audioData;
			if (size > 0)
			{
				memset(data, 0, size);
			}
		}
		if (gXAudio2->lpVtbl->CreateMasteringVoice(gXAudio2, &masteringVoice, 0, 0, 0, deviceIndex, 0) < 0)
		{
			{
					om::String message("Failed creating mastering voice.", false);
					SetDescription(message, false);
				}
		}
		else
		{
			XAudioWaveFormat format = deviceDetails.outputFormat;
			format.bitsPerSample = 16;
			format.validBitsPerSample = 16;
			format.samplesPerSec = RendererDriver::GetSampleRate();
			format.blockAlign = format.channels * 16 / 8;
			format.avgBytesPerSec = format.samplesPerSec * format.blockAlign;
			if (gXAudio2->lpVtbl->CreateSourceVoice(gXAudio2, &sourceVoice, &format, 0, 1.0f, this, 0, 0) < 0)
			{
				{
					om::String message("Failed creating source voice.", false);
					SetDescription(message, false);
				}
			}
			else
			{
				thread.SetPriority(5);
				thread.Start();
				for (unsigned int i = 0; i < numberOfBuffers; i++)
				{
					sourceVoice->lpVtbl->SubmitSourceBuffer(sourceVoice, &buffers[i], 0);
				}
				sourceVoice->lpVtbl->Start(sourceVoice, 0, 0);
				if (deviceSampleRate == 48000)
				{
					{
					om::String message("Ok", false);
					SetDescription(message, true);
				}
				}
				else
				{
					{
					om::String message("The sample rate set in your Control Panel, Sound Settings is not optimal.  48000kHz is recommended.", false);
					SetDescription(message, true);
				}
				}
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x10AC25A0
	void XAudio2RendererDriver::ClearUserData()
	{
		if (sourceVoice != 0)
		{
			open = true;
			sourceVoice->lpVtbl->Stop(sourceVoice, 0, 0);
			thread.stopping = true;
			core::SemaphoreRelease(&semaphore, 1);
			thread.Stop();
			core::SemaphoreDestroy(&semaphore);
			core::SemaphoreCreate(&semaphore, 0);
			sourceVoice->lpVtbl->DestroyVoice(sourceVoice);
			sourceVoice = 0;
		}
		if (masteringVoice != 0)
		{
			masteringVoice->lpVtbl->DestroyVoice(masteringVoice);
			masteringVoice = 0;
		}
		for (unsigned int i = 0; i < numberOfBuffers; i++)
		{
			unsigned int size = RendererDriver::GetNumberOfChannels() << 9;
			om::Release(buffers[i].audioData, size, 0x80);
			buffers[i].audioData = 0;
		}
		om::Release(buffers, numberOfBuffers * sizeof(XAudioBuffer), 4);
		buffers = 0;
		for (unsigned int channel = 0; channel < RendererDriver::GetNumberOfChannels(); channel++)
		{
			om::Release(mixBins[channel], 0x400, 0x80);
		}
		om::Release(mixBins, RendererDriver::GetNumberOfChannels() * 4, 4);
		mixBins = 0;
		RendererDriver::ClearUserData();
	}

	// FUNCTION: ENGINE 0x10AC2940
	// NONMATCHING: the order and stack slots of the name's string temporaries differ (32.8 %)
#ifdef NONMATCHING
	XAudio2RendererDriver::XAudio2RendererDriver(unsigned int newDeviceIndex, const XAudioDeviceDetails* newDeviceDetails, const char* deviceName) :
		RendererDriver(om::String("[XAudio2] ", false) + om::String(deviceName, true)),
		deviceIndex(newDeviceIndex),
		thread(this),
		sourceVoice(0)
	{
		memcpy(&deviceDetails, newDeviceDetails, sizeof(XAudioDeviceDetails));
		deviceSampleRate = deviceDetails.outputFormat.samplesPerSec;
		deviceChannels = deviceDetails.outputFormat.channels;
		SetNumberOfChannelsRange(deviceChannels, 8);
		RendererDriver::SetNumberOfChannels(deviceChannels);
		SetSampleRateRange(deviceSampleRate, 48000);
		RendererDriver::SetSampleRate(deviceSampleRate);
		SetLatencyRange(0x200, 0x1400);
		RendererDriver::SetLatency(0xA00);
		numberOfBuffers = 10;
		om::FixedArray<unsigned int, 8> map;
		map.items[0] = 0;
		map.items[1] = 1;
		map.items[2] = 2;
		map.items[3] = 3;
		map.items[4] = 4;
		map.items[5] = 5;
		map.items[6] = 6;
		map.items[7] = 7;
		switch (deviceChannels)
		{
		case 2:
			RendererDriver::SetFoldDownType(FoldDownType2);
			map.items[3] = 9;
			map.items[4] = 9;
			map.items[5] = 9;
			map.items[2] = 9;
			map.items[6] = 9;
			map.items[7] = 9;
			break;
		case 3:
			RendererDriver::SetFoldDownType(FoldDownType2_1);
			map.items[3] = 2;
			map.items[4] = 9;
			map.items[5] = 9;
			map.items[2] = 9;
			map.items[6] = 9;
			map.items[7] = 9;
			break;
		case 4:
			RendererDriver::SetFoldDownType(FoldDownType4);
			map.items[3] = 9;
			map.items[4] = 2;
			map.items[5] = 3;
			map.items[2] = 9;
			map.items[6] = 9;
			map.items[7] = 9;
			break;
		case 5:
			RendererDriver::SetFoldDownType(FoldDownType5_0);
			map.items[3] = 9;
			map.items[6] = 9;
			map.items[7] = 9;
			break;
		case 6:
			RendererDriver::SetFoldDownType(FoldDownType5_1);
			map.items[6] = 9;
			map.items[7] = 9;
			break;
		case 7:
			RendererDriver::SetFoldDownType(FoldDownType5_1);
			map.items[6] = 4;
			map.items[4] = 5;
			map.items[5] = 6;
			map.items[7] = 9;
			break;
		case 8:
			RendererDriver::SetFoldDownType(FoldDownType7_1);
			map.items[4] = 6;
			map.items[5] = 7;
			map.items[6] = 4;
			map.items[7] = 5;
			break;
		default:
			RendererDriver::SetFoldDownType(FoldDownTypeOff);
		}
		RendererDriver::SetSurroundChannelMap(map);
		mixBins = 0;
		buffers = 0;
	}
#endif

	// FUNCTION: ENGINE 0x10AC2740
	void XAudio2RendererDriver::SetSampleRate(unsigned int newSampleRate)
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

	// FUNCTION: ENGINE 0x10AC2780
	void XAudio2RendererDriver::SetNumberOfChannels(unsigned int newNumberOfChannels)
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

	// FUNCTION: ENGINE 0x10AC27C0
	void XAudio2RendererDriver::SetLatency(unsigned int newLatency)
	{
		unsigned int data = GetUserData();
		if (data != 0)
		{
			ClearUserData();
		}
		RendererDriver::SetLatency(newLatency);
		numberOfBuffers = RendererDriver::GetLatency() >> 8;
		if (data != 0)
		{
			SetUserData(data);
		}
	}
}
