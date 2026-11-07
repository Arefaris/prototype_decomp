// audio::RemotePlayer: a sound player of the audio library as the audio thread sees it (the events of
// remoteplayerevent.h run its members). The game's sound players hold a handle to one and send it their settings
// through the posting members of the table. Only the members the game's players use are described; the names
// of the members are guesses made from what they store.
#ifndef AUDIO_REMOTEPLAYER_H
#define AUDIO_REMOTEPLAYER_H

#include "code/om/dynamicarray.h"
#include "code/om/name.h"
#include "code/om/string.h"
#include "code/om/vector.h"

namespace dsp
{
	// The volumes of a voice for every channel and bin (RTTI: dsp::MixVoiceChannelBinVolumes, 0x240 bytes)
	struct MixVoiceChannelBinVolumes
	{
		float volumes[144];
	};
}

namespace audio
{
	class RemotePlayer
	{
	public:
		// 0x104A2D90: starts the player at a position (rounded down to a multiple of 16)
		void Start(unsigned int position);
		// 0x104A5E20: stops the player
		void Stop(unsigned int unused);
		// 0x104A2DB0
		void SetLoop(bool value);
		// 0x104A2DC0: the volumes of the voice
		void SetVolumes(const dsp::MixVoiceChannelBinVolumes& newVolumes);
		// 0x104A2DE0: the volume of one of the first five channels
		void SetChannelVolume(unsigned int channel, float volume);
		// 0x104A5460: the mix busses the player sends to
		void SetMixBuses(const om::DynamicArray<om::ClassName, unsigned short>& newBuses);
		// 0x104A5E30 / 0x104A5E60: two vectors
		void SetPosition(const om::Vector& newPosition);
		void SetVelocity(const om::Vector& newVelocity);
		// 0x104A5E90 - 0x104A5F50: numbers by their place in the player (the pitch and the filters are among them)
		void SetUnknown474(float value);
		void SetUnknown478(float value);
		void SetUnknown498(float value);
		void SetUnknown49C(float value);
		void SetUnknown51C(float value);
		void SetUnknown530(float value);
		void SetUnknown484(float value);
		// 0x105BE360: the name of the file the player plays (not reconstructed)
		void SetFilename(const om::String& newFilename);
		// 0x105BE320: a list of names (not reconstructed)
		void SetNames(const om::DynamicArray<om::String, unsigned short>& newNames);

		unsigned char unknown0[0x118];
		dsp::MixVoiceChannelBinVolumes volumes;  // 0x118
		unsigned char unknown358[0x3e8 - 0x358];
		float channelVolumes[5];  // 0x3E8
		om::Vector position;  // 0x3FC
		om::Vector velocity;  // 0x408
		unsigned char unknown414[0x474 - 0x414];
		float unknown474;
		float unknown478;
		unsigned char unknown47C[0x484 - 0x47c];
		float unknown484;
		unsigned char unknown488[0x498 - 0x488];
		float unknown498;
		float unknown49C;
		unsigned char unknown4A0[0x4f8 - 0x4a0];
		unsigned int startPosition;  // 0x4F8
		unsigned char unknown4FC[0x510 - 0x4fc];
		bool loop;  // 0x510
		unsigned char unknown511[0x51c - 0x511];
		float unknown51C;
		unsigned char unknown520[0x530 - 0x520];
		float unknown530;
		om::DynamicArray<om::ClassName, unsigned short> mixBuses;  // 0x534
		unsigned char unknown53C[0x548 - 0x53c];
		unsigned int stopped;  // 0x548
	};
}

#endif
