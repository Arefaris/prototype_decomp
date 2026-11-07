// The unit of the game's sound players (the ambience, helicopter and vehicle players; 0x104A2D30 - 0x104A9CB0): the
// members of audio::RemotePlayer and the posting members of the player table that the players use, and the instances
// of the om arrays their settings hold. The file name is a guess.
#include "code/audio/remoteplayerevent.h"
#include "code/mgraph/envelope.h"
#include "code/mgraph/nodes.h"
#include "code/om/dynamicarray.h"
#include "code/om/dynamicproperty.h"
#include "code/om/name.h"
#include "code/om/string.h"
#include "code/om/vectort.h"
#include "code/core/hash.h"

#pragma warning(disable: 4661 4345)

namespace audio
{
	void RemotePlayer::Start(unsigned int position)
	{
		stopped = 0;
		startPosition = position & 0xFFFFFFF0;
	}

	void RemotePlayer::Stop(unsigned int unused)
	{
		stopped = 1;
	}

	void RemotePlayer::SetLoop(bool value)
	{
		loop = value;
	}

	void RemotePlayer::SetVolumes(const dsp::MixVoiceChannelBinVolumes& newVolumes)
	{
		volumes = newVolumes;
	}

	void RemotePlayer::SetChannelVolume(unsigned int channel, float volume)
	{
		channelVolumes[channel] = volume;
	}

	void RemotePlayer::SetMixBuses(const om::DynamicArray<om::ClassName, unsigned short>& newBuses)
	{
		mixBuses = newBuses;
	}

	void RemotePlayer::SetPosition(const om::Vector& newPosition)
	{
		position = newPosition;
	}

	void RemotePlayer::SetVelocity(const om::Vector& newVelocity)
	{
		velocity = newVelocity;
	}

	void RemotePlayer::SetUnknown474(float value)
	{
		unknown474 = value;
	}

	void RemotePlayer::SetUnknown478(float value)
	{
		unknown478 = value;
	}

	void RemotePlayer::SetUnknown498(float value)
	{
		unknown498 = value;
	}

	void RemotePlayer::SetUnknown49C(float value)
	{
		unknown49C = value;
	}

	void RemotePlayer::SetUnknown51C(float value)
	{
		unknown51C = value;
	}

	void RemotePlayer::SetUnknown530(float value)
	{
		unknown530 = value;
	}

	void RemotePlayer::SetUnknown484(float value)
	{
		unknown484 = value;
	}

	void RemotePlayerTable::Start(const RemotePlayerHandle& player)
	{
		new RemotePlayerEvent_Param1<unsigned int>(player, &RemotePlayer::Start, 0);
	}

	void RemotePlayerTable::SetLoop(const RemotePlayerHandle& player, bool value)
	{
		new RemotePlayerEvent_Param1<bool>(player, &RemotePlayer::SetLoop, value);
	}

	void RemotePlayerTable::SetFilename(const RemotePlayerHandle& player, const om::String& value)
	{
		new RemotePlayerEvent_Param1<const om::String&>(player, &RemotePlayer::SetFilename, value);
	}

	void RemotePlayerTable::SetVolumes(const RemotePlayerHandle& player, const dsp::MixVoiceChannelBinVolumes& value)
	{
		new RemotePlayerEvent_Param1<const dsp::MixVoiceChannelBinVolumes&>(player, &RemotePlayer::SetVolumes, value);
	}

	void RemotePlayerTable::SetChannelVolume(const RemotePlayerHandle& player, unsigned int channel, float volume)
	{
		new RemotePlayerEvent_Param2<unsigned int, float>(player, &RemotePlayer::SetChannelVolume, channel, volume);
	}

	void RemotePlayerTable::Stop(const RemotePlayerHandle& player)
	{
		new RemotePlayerEvent_Param1<unsigned int>(player, &RemotePlayer::Stop, 0);
	}

	void RemotePlayerTable::SetPosition(const RemotePlayerHandle& player, const om::Vector& value)
	{
		new RemotePlayerEvent_Param1<const om::Vector&>(player, &RemotePlayer::SetPosition, value);
	}

	void RemotePlayerTable::SetVelocity(const RemotePlayerHandle& player, const om::Vector& value)
	{
		new RemotePlayerEvent_Param1<const om::Vector&>(player, &RemotePlayer::SetVelocity, value);
	}

	void RemotePlayerTable::SetUnknown474(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown474, value);
	}

	void RemotePlayerTable::SetUnknown478(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown478, value);
	}

	void RemotePlayerTable::SetUnknown498(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown498, value);
	}

	void RemotePlayerTable::SetUnknown49C(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown49C, value);
	}

	void RemotePlayerTable::SetUnknown51C(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown51C, value);
	}

	void RemotePlayerTable::SetUnknown530(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown530, value);
	}

	void RemotePlayerTable::SetUnknown484(const RemotePlayerHandle& player, float value)
	{
		new RemotePlayerEvent_Param1<float>(player, &RemotePlayer::SetUnknown484, value);
	}

	void RemotePlayerTable::SetNames(const RemotePlayerHandle& player, const om::DynamicArray<om::String, unsigned short>& value)
	{
		new RemotePlayerEvent_Param1<const om::DynamicArray<om::String, unsigned short>&>(player, &RemotePlayer::SetNames, value);
	}

	void RemotePlayerTable::SetMixBuses(const RemotePlayerHandle& player, const om::DynamicArray<om::String, unsigned short>& names)
	{
		om::DynamicArray<om::ClassName, unsigned short> keys(names.size);
		for (unsigned int i = 0; i < names.size; i++)
		{
			om::ClassName key(core::Hash64(names[i].GetText(), 0));
			::new (&keys.Append()) om::ClassName(key);
		}
		new RemotePlayerEvent_Param1<const om::DynamicArray<om::ClassName, unsigned short>&>(player, &RemotePlayer::SetMixBuses, keys);
	}
}

template class om::DynamicArray<om::ClassName, unsigned short>;
template class om::DynamicArray<mgraph::EnvelopeData, unsigned short>;
template class om::DynamicArray<om::VectorT<float, 2>, unsigned short>;
template class om::DynamicArray<float, unsigned short>;
template class om::DynamicArray<om::String, unsigned short>;

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104A2D50
// FUNCTION: ENGINE 0x104A2D90
// FUNCTION: ENGINE 0x104A2DB0
// FUNCTION: ENGINE 0x104A2DC0
// FUNCTION: ENGINE 0x104A2DE0
// FUNCTION: ENGINE 0x104A3830
// FUNCTION: ENGINE 0x104A3870
// FUNCTION: ENGINE 0x104A38F0
// FUNCTION: ENGINE 0x104A3970
// FUNCTION: ENGINE 0x104A3A40
// FUNCTION: ENGINE 0x104A3A90
// FUNCTION: ENGINE 0x104A3B00
// FUNCTION: ENGINE 0x104A3B20
// FUNCTION: ENGINE 0x104A3C40
// FUNCTION: ENGINE 0x104A3C90
// FUNCTION: ENGINE 0x104A3CE0
// FUNCTION: ENGINE 0x104A3D30
// FUNCTION: ENGINE 0x104A3D90
// FUNCTION: ENGINE 0x104A45D0
// FUNCTION: ENGINE 0x104A4630
// FUNCTION: ENGINE 0x104A4A50
// FUNCTION: ENGINE 0x104A4A90
// FUNCTION: ENGINE 0x104A4B20
// FUNCTION: ENGINE 0x104A4BA0
// FUNCTION: ENGINE 0x104A4BE0
// FUNCTION: ENGINE 0x104A4C70
// FUNCTION: ENGINE 0x104A4D50
// FUNCTION: ENGINE 0x104A4DF0
// FUNCTION: ENGINE 0x104A4E80
// FUNCTION: ENGINE 0x104A58D0
// FUNCTION: ENGINE 0x104A5DF0
// FUNCTION: ENGINE 0x104A5E20
// FUNCTION: ENGINE 0x104A5E30
// FUNCTION: ENGINE 0x104A5E60
// FUNCTION: ENGINE 0x104A5E90
// FUNCTION: ENGINE 0x104A5EB0
// FUNCTION: ENGINE 0x104A5ED0
// FUNCTION: ENGINE 0x104A5EF0
// FUNCTION: ENGINE 0x104A5F10
// FUNCTION: ENGINE 0x104A5F30
// FUNCTION: ENGINE 0x104A5F50
// FUNCTION: ENGINE 0x104A62E0
// FUNCTION: ENGINE 0x104A6360
// FUNCTION: ENGINE 0x104A6370
// FUNCTION: ENGINE 0x104A63C0
// FUNCTION: ENGINE 0x104A6420
// FUNCTION: ENGINE 0x104A6480
// FUNCTION: ENGINE 0x104A64D0
// FUNCTION: ENGINE 0x104A6520
// FUNCTION: ENGINE 0x104A6570
// FUNCTION: ENGINE 0x104A65C0
// FUNCTION: ENGINE 0x104A6610
// FUNCTION: ENGINE 0x104A6660
// FUNCTION: ENGINE 0x104A7150
// FUNCTION: ENGINE 0x104A7310
// FUNCTION: ENGINE 0x104A7470

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104A3850
// FUNCTION: ENGINE 0x104A3860
// FUNCTION: ENGINE 0x104A3890
// FUNCTION: ENGINE 0x104A38C0
// FUNCTION: ENGINE 0x104A5460
// FUNCTION: ENGINE 0x104A5800
// FUNCTION: ENGINE 0x104A5820
