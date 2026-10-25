// The audio renderer drivers (RTTI: audio::RendererDriver and the drivers derived from it: Null, Mme, Asio, WdmKs,
// DirectSound and XAudio2): the device layer the mixer renders to. The base class keeps the ranges of sample rate,
// latency and channel count a device supports, the values in use, the channel map and the way more channels fold down
// to fewer; its accessors are virtual and reflected under the names the registration uses.
#ifndef AUDIO_RENDERERDRIVER_H
#define AUDIO_RENDERERDRIVER_H

#include "code/om/fixedarray.h"
#include "code/om/metaproperty.h"
#include "code/om/metatype.h"
#include "code/om/string.h"

namespace om
{
	// 0x105BA610 (name guessed): the value rounded up to a multiple of the alignment
	unsigned int AlignUp(unsigned int value, unsigned int alignment);
	// 0x105B3E70 (name guessed): a string formatted like printf does (the first argument is not known)
	String Format(int unknown, const char* format, ...);

	// The text and binary forms of the channel map (0x105E6410 / 0x105E6500 / 0x105E61A0 / 0x105E61E0)
	bool ReadText(const TextValue* text, FixedArray<unsigned int, 8>* value);
	void WriteText(TextValue* text, const FixedArray<unsigned int, 8>& value);
	bool ReadBinary(BinaryStream* stream, FixedArray<unsigned int, 8>* value);
	void WriteBinary(BinaryStream* stream, const FixedArray<unsigned int, 8>& value);
}

namespace audio
{
	enum FoldDownType
	{
		FoldDownTypeOff,
		FoldDownType2,
		FoldDownType2_1,
		FoldDownType4,
		FoldDownType5_0,
		FoldDownType5_1,
		FoldDownType6_1,
		FoldDownType7_1
	};

	// The wave format a device is opened with
	enum WAVEFORMAT
	{
		WAVEFORMAT_EX,
		WAVEFORMAT_EXTENSIBLE
	};

	class RendererDriver
	{
	public:
		// 0x105E65E0: a driver of the name
		explicit RendererDriver(const om::String& newName);
		// Slot 0 (0x105E6670 is the body, the deleting destructor 0x105E66A0)
		virtual ~RendererDriver()
		{
		}
		virtual void Slot1() = 0;
		// Slot 2 (0x105E66D0): the description of the class
		virtual om::MetaTypeBase* GetMetaType();
		// Slots 3 and 4 (0x105E66F0 / 0x105E6700)
		virtual void SetUserData(unsigned int newUserData);
		virtual void ClearUserData();
		virtual void Slot5() = 0;
		// Slots 6 to 11 (0x105E57F0 / 0x105E4F30, 0x105E5820 / 0x105E4F40, 0x105E5860 / 0x105E4F50): the value in use is
		// kept inside the supported range
		virtual void SetSampleRate(unsigned int newSampleRate);
		virtual unsigned int GetSampleRate() const;
		virtual void SetLatency(unsigned int newLatency);
		virtual unsigned int GetLatency() const;
		virtual void SetNumberOfChannels(unsigned int newNumberOfChannels);
		virtual unsigned int GetNumberOfChannels() const;
		// Slot 12 (0x105E4F60)
		virtual om::String GetChannelName(int channel) const;
		// Slots 13 and 14 (0x105E5680 / 0x105E4E80)
		virtual void SetSurroundChannelMap(const om::FixedArray<unsigned int, 8>& newSurroundChannelMap);
		virtual const om::FixedArray<unsigned int, 8>& GetSurroundChannelMap() const;
		// Slots 15 and 16 (0x105E4E60 / 0x105E4E70)
		virtual void SetFoldDownType(FoldDownType newFoldDownType);
		virtual FoldDownType GetFoldDownType() const;
		virtual int Slot17();

		// 0x105E4E90 - 0x105E4EE0
		unsigned int GetMinLatency() const;
		unsigned int GetMaxLatency() const;
		unsigned int GetMinSampleRate() const;
		unsigned int GetMaxSampleRate() const;
		unsigned int GetMinNumberOfChannels() const;
		unsigned int GetMaxNumberOfChannels() const;
		// 0x105E5710 / 0x105E5770 / 0x105E57B0: set a range and bring the value in use inside it
		void SetLatencyRange(unsigned int newMinLatency, unsigned int newMaxLatency);
		void SetSampleRateRange(unsigned int newMinSampleRate, unsigned int newMaxSampleRate);
		void SetNumberOfChannelsRange(unsigned int newMinNumberOfChannels, unsigned int newMaxNumberOfChannels);
		// 0x105E4EF0 / 0x105E4F10
		void SetDescription(const om::String& newDescription, bool newAvailable);
		bool GetDescription(om::String* description) const;
		// 0x105E5890
		unsigned int GetUserData() const;

		unsigned int minLatency;  // 4
		unsigned int maxLatency;  // 8
		unsigned int minSampleRate;  // 0xC
		unsigned int maxSampleRate;  // 0x10
		unsigned int minNumberOfChannels;  // 0x14
		unsigned int maxNumberOfChannels;  // 0x18
		unsigned int sampleRate;  // 0x1C
		unsigned int latency;  // 0x20
		unsigned int numberOfChannels;  // 0x24
		om::FixedArray<unsigned int, 8> surroundChannelMap;  // 0x28
		om::String name;  // 0x48
		unsigned int userData;  // 0x54
		bool available;  // 0x58
		om::String description;  // 0x5C
		FoldDownType foldDownType;  // 0x68
	};
}

#endif
