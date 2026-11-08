// The audio renderer drivers of the platform (RTTI: audio::NullRendererDriver, MmeRendererDriver, AsioRendererDriver,
// WdmKsRendererDriver and DirectSoundRendererDriverImpl) and the enumerations of the mixer and the audio files. Only what
// the reflection of the drivers names is described so far: the accessors of the properties the registration binds.
#ifndef AUDIO_DRIVERS_H
#define AUDIO_DRIVERS_H

#include "code/audio/rendererdriver.h"
#include "code/audio/rendererdrivermodel.h"
#include "code/om/entity.h"
#include "code/core/criticalsection.h"
#include "code/om/thread.h"
#include "code/audio/remoteplayerevent.h"

// The callback interface of the XAudio2 library (RTTI: IXAudio2VoiceCallback, stdcall methods)
struct IXAudio2VoiceCallback
{
	virtual void __stdcall OnVoiceProcessingPassStart(unsigned int bytesRequired) = 0;
	virtual void __stdcall OnVoiceProcessingPassEnd() = 0;
	virtual void __stdcall OnStreamEnd() = 0;
	virtual void __stdcall OnBufferStart(void* bufferContext) = 0;
	virtual void __stdcall OnBufferEnd(void* bufferContext) = 0;
	virtual void __stdcall OnLoopEnd(void* bufferContext) = 0;
	virtual void __stdcall OnVoiceError(void* bufferContext, long error) = 0;
};

// A buffer submitted to a source voice (XAUDIO2_BUFFER)
struct XAudioBuffer
{
	XAudioBuffer() :
		flags(0),
		audioBytes(0),
		audioData(0),
		playBegin(0),
		playLength(0),
		loopBegin(0),
		loopLength(0),
		loopCount(0),
		context(0)
	{
	}

	unsigned int flags;
	unsigned int audioBytes;
	void* audioData;
	unsigned int playBegin;
	unsigned int playLength;
	unsigned int loopBegin;
	unsigned int loopLength;
	unsigned int loopCount;
	void* context;
};

// The format of the samples a voice plays (WAVEFORMATEXTENSIBLE)
struct XAudioWaveFormat
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
	char subFormat[16];
};

// What the library tells about a device (XAUDIO2_DEVICE_DETAILS)
struct XAudioDeviceDetails
{
	wchar_t deviceId[256];
	wchar_t displayName[256];
	unsigned int role;
	XAudioWaveFormat outputFormat;
};

// The voices and the engine of the XAudio2 library, in the library's C form (only the slots the driver calls)
struct IXAudio2Voice;
struct IXAudio2SourceVoice;
struct IXAudio2;

struct IXAudio2VoiceVtbl
{
	void* slots[16];
	void (__stdcall *DestroyVoice)(IXAudio2Voice* voice);
};

struct IXAudio2Voice
{
	const IXAudio2VoiceVtbl* lpVtbl;
};

struct IXAudio2SourceVoiceVtbl
{
	void* slots[16];
	void (__stdcall *DestroyVoice)(IXAudio2SourceVoice* voice);
	long (__stdcall *Start)(IXAudio2SourceVoice* voice, unsigned int flags, unsigned int operationSet);
	long (__stdcall *Stop)(IXAudio2SourceVoice* voice, unsigned int flags, unsigned int operationSet);
	long (__stdcall *SubmitSourceBuffer)(IXAudio2SourceVoice* voice, const XAudioBuffer* buffer, const void* bufferWma);
};

struct IXAudio2SourceVoice
{
	const IXAudio2SourceVoiceVtbl* lpVtbl;
};

struct IXAudio2Vtbl
{
	void* slot0;
	void* slot1;
	unsigned long (__stdcall *Release)(IXAudio2* engine);
	long (__stdcall *GetDeviceCount)(IXAudio2* engine, unsigned int* count);
	long (__stdcall *GetDeviceDetails)(IXAudio2* engine, unsigned int index, XAudioDeviceDetails* details);
	long (__stdcall *Initialize)(IXAudio2* engine, unsigned int flags, unsigned int processor);
	void* slots6[2];
	long (__stdcall *CreateSourceVoice)(IXAudio2* engine, IXAudio2SourceVoice** voice, const XAudioWaveFormat* format,
		unsigned int flags, float maxFrequencyRatio, IXAudio2VoiceCallback* callback, const void* sendList, const void* effectChain);
	void* slot9;
	long (__stdcall *CreateMasteringVoice)(IXAudio2* engine, IXAudio2Voice** voice, unsigned int inputChannels,
		unsigned int inputSampleRate, unsigned int flags, unsigned int deviceIndex, const void* effectChain);
};

struct IXAudio2
{
	const IXAudio2Vtbl* lpVtbl;
};

namespace audio
{
	// 0x113276E8: the XAudio2 engine
	extern IXAudio2* gXAudio2;

	// What the renderer gives the driver as its user data: it mixes a block of samples into the bins (name guessed)
	class RenderCallback
	{
	public:
		virtual void Render(float** bins, unsigned int channels, unsigned int samples) = 0;
	};

	// Where the device's buffer lives (names of the values not recovered)
	enum BufferLocation
	{
		BufferLocationUnknown
	};

	// How the mixer mixes (names of the values not recovered)
	enum MixType
	{
		MixTypeUnknown
	};

	// Which windows' sound plays (names of the values not recovered)
	enum Focus
	{
		FocusUnknown
	};

	// The format of an audio file (names of the values not recovered)
	enum AudioFileType
	{
		AudioFileTypeUnknown
	};

	// A handle on what the content keeps of a file (a pointer that starts empty)
	struct FileHandle
	{
		FileHandle() :
			pointer(0)
		{
		}

		void* pointer;
	};

	// An audio file of the content (RTTI: audio::AudioFile, an entity)
	class AudioFile : public om::Entity
	{
	public:
		// 0x10AB67F0
		explicit AudioFile(const om::ClassName& newName);
		// Slot 0 (0x10AB6860 is the body, the deleting destructor 0x10AB6C70)
		virtual ~AudioFile();
		// Slots 3, 4, 5 and 7 (0x10AB64C0 / 0x10AB64D0 / 0x10AB64E0 / 0x10AB64F0): nothing is done and nothing answered
		virtual bool Slot3(void* argument);
		virtual void Slot4(void* argument);
		virtual bool Slot5(void* argument);
		// Slot 6 (0x10AB7000): reads the file's description from a stream
		virtual bool Slot6(void* argument);
		virtual bool Slot7(void* argument);
		// Slot 9 (0x10AB6850)
		virtual om::EntityTypeBase* GetEntityType();
		OM_ENTITY_ALLOCATION(AudioFile);

		AudioFileType fileType;  // 0x20
		FileHandle file;  // 0x24: what the content keeps of the file (a counted handle; meaning not recovered)
		om::String unknown28;  // 0x28
		om::String path;  // 0x34
	};

	// A counting semaphore of the core module, created with the object and destroyed with it
	class DriverSemaphore
	{
	public:
		DriverSemaphore()
		{
			core::SemaphoreCreate(&handle, 0);
		}
		~DriverSemaphore()
		{
			core::SemaphoreDestroy(&handle);
		}

		void* handle;
	};

	// What the multimedia library tells about an output device (WAVEOUTCAPS, 0x34 bytes)
	struct WaveOutCaps
	{
		unsigned short manufacturerId;
		unsigned short productId;
		unsigned int driverVersion;
		char name[32];
		unsigned int formats;
		unsigned short channels;
		unsigned short reserved;
		unsigned int support;
	};

	// A block of samples handed to the multimedia library (WAVEHDR, 0x20 bytes)
	struct WaveHeader
	{
		char* data;
		unsigned int bufferLength;
		unsigned int bytesRecorded;
		unsigned int user;
		unsigned int flags;
		unsigned int loops;
		WaveHeader* next;
		unsigned int reserved;
	};

	// The multimedia extension driver (names of the accessors guessed)
	class MmeRendererDriver : public RendererDriver
	{
	public:
		// The thread that mixes the next block of samples and hands it to the device
		class Thread : public om::Thread
		{
		public:
			// 0x10AB7980
			explicit Thread(MmeRendererDriver* newDriver);
			// 0x10AB8080
			virtual void Run();

			MmeRendererDriver* driver;  // 0xCC
		};

		// 0x10AB7CB0
		MmeRendererDriver(unsigned int newDeviceId, const WaveOutCaps* newCaps);
		// 0x10AB7770 (the deleting destructor is 0x10AB7E00)
		virtual ~MmeRendererDriver();
		virtual const char* Slot1();
		// Slot 2 (0x10AB85C0): the description of the class
		virtual om::MetaTypeBase* GetMetaType();
		// Slots 3 and 4: the device is opened with the user data and closed again
		virtual void SetUserData(unsigned int newUserData);
		virtual void ClearUserData();
		// Slot 5 (0x10AB77E0): true on the driver's own thread
		virtual bool Slot5();
		// Slots 6, 8 and 10: the value is set with the device closed
		virtual void SetSampleRate(unsigned int newSampleRate);
		virtual void SetLatency(unsigned int newLatency);
		virtual void SetNumberOfChannels(unsigned int newNumberOfChannels);
		void SetWaveFormat(WAVEFORMAT newWaveFormat);
		WAVEFORMAT GetWaveFormat() const;
		OM_ALLOCATION(MmeRendererDriver);

		// 0x1132767C (name guessed)
		static char unknownStatic;

		float** mixBins;  // 0x7C
		unsigned int deviceId;  // 0x80
		WaveOutCaps caps;  // 0x84
		void* device;  // 0xB8: the open device, null while it is closed
		WaveHeader headers[2];  // 0xBC
		WAVEFORMAT waveFormat;  // 0xFC
		Thread thread;  // 0x100
		DriverSemaphore semaphore;  // 0x1D0
		bool closing;  // 0x1D4
	};

	// The driver of an ASIO device (RTTI: audio::AsioRendererDriver); only the parts the slots below use are described
	class AsioRendererDriver : public RendererDriver
	{
	public:
		virtual const char* Slot1();
		// Slot 5 (0x10AB9340): true on the thread the device calls back on
		virtual bool Slot5();
		// Slots 6, 8 and 10: the value is set with the device closed (the latency and the channels follow the buffers)
		virtual void SetSampleRate(unsigned int newSampleRate);
		virtual void SetLatency(unsigned int newLatency);
		virtual void SetNumberOfChannels(unsigned int newNumberOfChannels);
		// 0x10AB9360: the device changed its sample rate (a callback of the device library)
		static void __cdecl SampleRateDidChange(double newSampleRate);

		// 0x11327690 (name guessed): the driver the device calls back
		static AsioRendererDriver* current;
		// 0x11327694 (name guessed)
		static char unknownStatic;

		char unknown7C[0x10];
		void* device;  // 0x8C
		int state;  // 0x90
		float** buffers;  // 0x94
		char unknown98[0x3C];
		int bufferSize;  // 0xD4
		char unknownD8[8];
		int outputChannels;  // 0xE0
		char unknownE4[4];
		double deviceSampleRate;  // 0xE8
		char unknownF0[8];
		unsigned long threadId;  // 0xF8
	};

	// The driver of the kernel streaming devices (names of the accessors guessed)
	class WdmKsRendererDriver : public RendererDriver
	{
	public:
		// The thread that mixes into the device's events (its body is not recovered)
		class Thread : public om::Thread
		{
		public:
			virtual void Run();

			WdmKsRendererDriver* driver;  // 0xCC
		};

		virtual const char* Slot1();
		// Slot 2 (0x10ABB8E0): the description of the class
		virtual om::MetaTypeBase* GetMetaType();
		// Slot 5 (0x10ABA740): true on the driver's own thread
		virtual bool Slot5();
		// Slots 6, 8 and 10: the value is set with the device closed
		virtual void SetSampleRate(unsigned int newSampleRate);
		virtual void SetLatency(unsigned int newLatency);
		virtual void SetNumberOfChannels(unsigned int newNumberOfChannels);
		void SetWaveFormat(WAVEFORMAT newWaveFormat);
		WAVEFORMAT GetWaveFormat() const;

		// 0x113276B0 (name guessed)
		static char unknownStatic;

		void* unknown7C;
		char unknown80[8];
		Thread thread;  // 0x88
		void* mixEvents;  // 0x158
		unsigned int numberOfMixEvents;  // 0x15C
		WAVEFORMAT waveFormat;  // 0x160
	};

	// The interface the DirectSound driver implements besides the driver base (at 0x7C of the object; RTTI:
	// audio::DirectSoundRendererDriver, four slots not recovered)
	class DirectSoundRendererDriver
	{
	public:
		virtual void InterfaceSlot0() = 0;
		virtual void InterfaceSlot1() = 0;
		virtual void InterfaceSlot2() = 0;
		virtual void InterfaceSlot3() = 0;
	};

	class DirectSoundRendererDriverImpl : public RendererDriver, public DirectSoundRendererDriver
	{
	public:
		// The thread that fills the device's buffer (its body is not recovered)
		class Thread : public om::Thread
		{
		public:
			virtual void Run();

			DirectSoundRendererDriverImpl* driver;  // 0xCC
		};

		virtual const char* Slot1();
		// Slot 2 (0x10ABEF40): the description of the class
		virtual om::MetaTypeBase* GetMetaType();
		// Slot 5 (0x10ABCFC0): true on the driver's own thread
		virtual bool Slot5();
		// Slot 17 (0x10ABCFE0)
		virtual int Slot17();

		// 0x113276D4 (name guessed)
		static char unknownStatic;

		char unknown80[0xE8];
		Thread thread;  // 0x168
		char unknown238[0x1C];
		int unknown254;  // 0x254
		void SetBufferLocation(BufferLocation newBufferLocation);
		BufferLocation GetBufferLocation() const;
		void SetMixType(MixType newMixType);
		MixType GetMixType() const;
		void SetFocus(Focus newFocus);
		Focus GetFocus() const;
		void SetWaveFormat(WAVEFORMAT newWaveFormat);
		WAVEFORMAT GetWaveFormat() const;
	};

	// The base of the models of the platform's drivers (RTTI: audio::RendererDriverModel): finds the devices of a platform and
	// makes a driver of each, and lets go of the platform again
	// The XAudio2 platform (RTTI: audio::XAudio2RendererDriverModel)
	class XAudio2RendererDriverModel : public RendererDriverModel
	{
	public:
		// 0x10AC2140
		XAudio2RendererDriverModel();
		// Slot 0 (0x10AC2F70): opens the XAudio2 engine and makes a driver of every device (not reconstructed)
		virtual void CreateDriver(RenderDriverModelHarness* harness);
		// Slot 1 (0x10AC31B0): lets go of the reflection of the driver and of the engine
		virtual void Slot1();
	};

	// 0x105C6E60 (name guessed): whether two counters hold the same value
	bool Equal(const int* first, const int* second);

	// The driver of the XAudio2 device (RTTI: audio::XAudio2RendererDriver, also a voice callback of the device library)
	class XAudio2RendererDriver : public RendererDriver, public IXAudio2VoiceCallback
	{
	public:
		// The thread that converts the mixed floats to 16 bit samples and submits them to the source voice
		class Thread : public om::Thread
		{
		public:
			// 0x10AC2810
			explicit Thread(XAudio2RendererDriver* newDriver);
			// 0x10AC2C90
			virtual void Run();

			XAudio2RendererDriver* driver;  // 0xCC
		};

		// 0x10AC2940
		XAudio2RendererDriver(unsigned int newDeviceIndex, const XAudioDeviceDetails* newDeviceDetails, const char* deviceName);
		// 0x10AC21A0 (the deleting destructor is 0x10AC2C00)
		virtual ~XAudio2RendererDriver();
		virtual const char* Slot1();
		// Slot 2 (0x10AC2E90): the description of the class
		virtual om::MetaTypeBase* GetMetaType();
		// Slots 3 and 4: the device is opened with the user data and closed again (the base class keeps the data)
		virtual void SetUserData(unsigned int newUserData);
		virtual void ClearUserData();
		// Slot 5 (0x10AC2700): true on the driver's own thread
		virtual bool Slot5();
		// Slots 6, 8 and 10: the value is set with the device closed
		virtual void SetSampleRate(unsigned int newSampleRate);
		virtual void SetLatency(unsigned int newLatency);
		virtual void SetNumberOfChannels(unsigned int newNumberOfChannels);
		// Slot 17 (0x10AC2C30)
		virtual int Slot17();
		// The callbacks of the voice
		virtual void __stdcall OnVoiceProcessingPassStart(unsigned int bytesRequired);
		virtual void __stdcall OnVoiceProcessingPassEnd();
		virtual void __stdcall OnStreamEnd();
		virtual void __stdcall OnBufferStart(void* bufferContext);
		virtual void __stdcall OnBufferEnd(void* bufferContext);
		virtual void __stdcall OnLoopEnd(void* bufferContext);
		virtual void __stdcall OnVoiceError(void* bufferContext, long error);
		OM_ALLOCATION(XAudio2RendererDriver);

		// 0x113276EC (name guessed)
		static char unknownStatic;

		float** mixBins;  // 0x80
		unsigned int deviceIndex;  // 0x84
		XAudioDeviceDetails deviceDetails;  // 0x88: the description of the device, copied
		XAudioBuffer* buffers;  // 0x4B4
		IXAudio2Voice* masteringVoice;  // 0x4B8
		IXAudio2SourceVoice* sourceVoice;  // 0x4BC
		unsigned int deviceSampleRate;  // 0x4C0
		unsigned int deviceChannels;  // 0x4C4
		unsigned int numberOfBuffers;  // 0x4C8
		DriverSemaphore semaphore;  // 0x4CC
		int queuedBuffers;  // 0x4D0
		long playedBuffers;  // 0x4D4
		Thread thread;  // 0x4D8
		bool open;  // 0x5A8
	};
}

#endif
