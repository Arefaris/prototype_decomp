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
#include "code/engine/driving/carattributes.h"
#include "code/proto/audio/soundplayers.h"

#pragma warning(disable: 4661 4345)

namespace ravenphysics
{
	extern const float gDefaultMaxForce;
}

namespace proto
{
	extern const float gHundred;
}

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

	// Calls every posting member once, with inlining off, so that the unit has the out-of-line copy of each that the engine's unit has
	// (this function is not the engine's)
#pragma inline_depth(0)
	void ReferencePosters(const RemotePlayerHandle& player, const dsp::MixVoiceChannelBinVolumes& volumes, const om::Vector& vector, const om::String& text,
		const om::DynamicArray<om::String, unsigned short>& names)
	{
		RemotePlayerTable* table = gRemotePlayers;
		table->Start(player);
		table->SetLoop(player, true);
		table->SetFilename(player, text);
		table->SetVolumes(player, volumes);
		table->SetChannelVolume(player, 0, 0.0f);
		table->Stop(player);
		table->SetPosition(player, vector);
		table->SetVelocity(player, vector);
		table->SetUnknown474(player, 0.0f);
		table->SetUnknown478(player, 0.0f);
		table->SetUnknown498(player, 0.0f);
		table->SetUnknown49C(player, 0.0f);
		table->SetUnknown51C(player, 0.0f);
		table->SetUnknown530(player, 0.0f);
		table->SetUnknown484(player, 0.0f);
		table->SetNames(player, names);
	}
#pragma inline_depth()

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

namespace proto
{
	using audio::RemotePlayer;
	using audio::RemotePlayerEvent_Param1;

	// A new voice for a player of the class: the table makes it and answers the handle
	unsigned int SoundPlayerHelicopter::CreatePlayer()
	{
		return audio::gRemotePlayers->Create(audio::RemotePlayerParams(6), 1, 1, 0, &typeid(SoundPlayerHelicopter), 1);
	}

	// FUNCTION: ENGINE 0x104A66B0
	// NONMATCHING: 93.9 %, the engine stores the vftable later, between the stores of the members
#ifdef NONMATCHING
	SoundPlayerHelicopter::SoundPlayerHelicopter()
	{
		float half = engine::driving::gHalf;
		float zero = 0.0f;
		unknown28 = half;
		unknown2C = half;
		unknown30 = zero;
		unknown34 = zero;
		unknown48 = false;
		unknown49 = false;
		unknown4A = false;
		unknown4C = 0;
		unknown50 = 0;
		player0C = CreatePlayer();
		player10 = CreatePlayer();
		player18 = CreatePlayer();
		player14 = CreatePlayer();
		player1C = CreatePlayer();
		player20 = CreatePlayer();
		player24 = CreatePlayer();
		new RemotePlayerEvent_Param1<bool>(player0C, &RemotePlayer::SetLoop, true);
		new RemotePlayerEvent_Param1<bool>(player18, &RemotePlayer::SetLoop, true);
		new RemotePlayerEvent_Param1<bool>(player1C, &RemotePlayer::SetLoop, true);
		new RemotePlayerEvent_Param1<bool>(player0C, &RemotePlayer::SetLoop, true);
		new RemotePlayerEvent_Param1<bool>(player20, &RemotePlayer::SetLoop, true);
		new RemotePlayerEvent_Param1<bool>(player24, &RemotePlayer::SetLoop, true);
	}
#endif

	SoundPlayerHelicopter::~SoundPlayerHelicopter()
	{
		audio::gRemotePlayers->Release(player1C);
		audio::gRemotePlayers->Release(player14);
		audio::gRemotePlayers->Release(player18);
		audio::gRemotePlayers->Release(player0C);
		audio::gRemotePlayers->Release(player10);
		audio::gRemotePlayers->Release(player20);
		audio::gRemotePlayers->Release(player24);
	}

	void SoundPlayerHelicopter::Slot4()
	{
		audio::RemotePlayerTable* table = audio::gRemotePlayers;
		table->Stop(player14);
		table->Stop(player18);
		table->Stop(player0C);
		table->Stop(player1C);
		table->Stop(player10);
		table->Stop(player20);
		table->Stop(player24);
	}

	bool SoundPlayerHelicopter::Slot5()
	{
		audio::RemotePlayerEntry* entries = audio::gRemotePlayers->entries;
		if (entries[player14.index].ready && entries[player18.index].ready && entries[player0C.index].ready && entries[player1C.index].ready
			&& entries[player10.index].ready && entries[player20.index].ready && entries[player24.index].ready)
		{
			return true;
		}
		return false;
	}

	void SoundPlayerHelicopter::SetUnknown49C(float value)
	{
		audio::RemotePlayerTable* table = audio::gRemotePlayers;
		table->SetUnknown49C(player1C, value);
		table->SetUnknown49C(player0C, value);
		table->SetUnknown49C(player18, value);
		table->SetUnknown49C(player14, value);
		table->SetUnknown49C(player24, value);
		table->SetUnknown49C(player20, value);
	}

	bool SoundPlayerHelicopter::Slot1(core::Name<core::CaseSensitiveKey>* name)
	{
		if (*name == engine::gPlay3)
		{
			unknown48 = true;
			audio::gRemotePlayers->Start(player14);
			audio::gRemotePlayers->Start(player18);
			audio::gRemotePlayers->Start(player0C);
			audio::gRemotePlayers->Start(player1C);
			if (unknown49)
			{
				audio::gRemotePlayers->Start(player20);
			}
			if (unknown4A)
			{
				audio::gRemotePlayers->Start(player24);
			}
		}
		else if (*name == engine::gStop2)
		{
			unknown48 = false;
			audio::gRemotePlayers->Stop(player1C);
			audio::gRemotePlayers->Stop(player14);
			audio::gRemotePlayers->Stop(player18);
			audio::gRemotePlayers->Stop(player0C);
			audio::gRemotePlayers->Start(player10);
			audio::gRemotePlayers->Stop(player20);
			audio::gRemotePlayers->Stop(player24);
		}
		else if (*name == engine::gWinddown2)
		{
			audio::gRemotePlayers->SetUnknown49C(player10, ravenphysics::gDefaultMaxForce);
			audio::gRemotePlayers->Start(player10);
		}
		return true;
	}

	unsigned int SoundPlayerVehicle::CreatePlayer()
	{
		return audio::gRemotePlayers->Create(audio::RemotePlayerParams(6), 1, 1, 0, &typeid(SoundPlayerVehicle), 1);
	}

	// FUNCTION: ENGINE 0x104A89E0
	// NONMATCHING: 81.5 %, the engine stores the vftable later, between the stores of the members
#ifdef NONMATCHING
	SoundPlayerVehicle::SoundPlayerVehicle()
	{
		unknown1C = 0.0f;
		unknown20 = 0.0f;
		float hundred = gHundred;
		unknown24 = hundred;
		unknown28 = hundred;
		unknown2C = hundred;
		unknown30 = hundred;
		float one = engine::driving::gOne;
		unknown34 = one;
		unknown38 = one;
		unknown3C = 0;
		unknown40 = 0;
		playerC = CreatePlayer();
		player10 = CreatePlayer();
		player14 = CreatePlayer();
		player18 = CreatePlayer();
		new RemotePlayerEvent_Param1<bool>(playerC, &RemotePlayer::SetLoop, true);
		new RemotePlayerEvent_Param1<bool>(player18, &RemotePlayer::SetLoop, true);
	}
#endif

	SoundPlayerVehicle::~SoundPlayerVehicle()
	{
		audio::gRemotePlayers->Release(player18);
		audio::gRemotePlayers->Release(playerC);
		audio::gRemotePlayers->Release(player14);
		audio::gRemotePlayers->Release(player10);
	}

	bool SoundPlayerVehicle::Slot1(core::Name<core::CaseSensitiveKey>* name)
	{
		if (*name == engine::gStartup2)
		{
			audio::gRemotePlayers->Start(playerC);
			audio::gRemotePlayers->Start(player18);
			audio::gRemotePlayers->Start(player14);
		}
		else if (*name == engine::gStop3)
		{
			audio::gRemotePlayers->Stop(playerC);
			audio::gRemotePlayers->Stop(player18);
			audio::gRemotePlayers->Stop(player14);
			audio::gRemotePlayers->Stop(player10);
		}
		else if (*name == engine::gWinddown3)
		{
			audio::gRemotePlayers->Start(player10);
			audio::gRemotePlayers->Start(playerC);
			audio::gRemotePlayers->Stop(player18);
		}
		else if (*name == engine::gIdle2)
		{
			audio::gRemotePlayers->Start(playerC);
			audio::gRemotePlayers->Stop(player18);
		}
		return true;
	}

	void SoundPlayerVehicle::Slot4()
	{
		audio::gRemotePlayers->Stop(playerC);
		audio::gRemotePlayers->Stop(player18);
		audio::gRemotePlayers->Stop(player14);
		audio::gRemotePlayers->Stop(player10);
	}

	bool SoundPlayerVehicle::Slot5()
	{
		audio::RemotePlayerEntry* entries = audio::gRemotePlayers->entries;
		if (entries[playerC.index].ready && entries[player18.index].ready && entries[player14.index].ready && entries[player10.index].ready)
		{
			return true;
		}
		return false;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104A5F70
// FUNCTION: ENGINE 0x104A6010
// FUNCTION: ENGINE 0x104A68A0
// FUNCTION: ENGINE 0x104A68D0
// FUNCTION: ENGINE 0x104A6C40
// FUNCTION: ENGINE 0x104A6DC0
// FUNCTION: ENGINE 0x104A71F0
// FUNCTION: ENGINE 0x104A8840
// FUNCTION: ENGINE 0x104A88A0
// FUNCTION: ENGINE 0x104A8AF0
// FUNCTION: ENGINE 0x104A8B20
// FUNCTION: ENGINE 0x104A8F00
// FUNCTION: ENGINE 0x104A8FF0
