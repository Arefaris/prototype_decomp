// proto::SoundPlayerHelicopter and proto::SoundPlayerVehicle (RTTI): the sound players of the helicopters and the
// vehicles. Each keeps a few remote players of the audio library (handles to the voices of its engine: a start-up, an
// idle or rotor loop, a wind-down) and starts, stops and tunes them with the events of the player table. The member
// names are guesses; of the classes only what is reconstructed is declared.
#ifndef PROTO_AUDIO_SOUNDPLAYERS_H
#define PROTO_AUDIO_SOUNDPLAYERS_H

#include "code/audio/remoteplayerevent.h"
#include "code/core/name.h"
#include "code/engine/audio/audioplayer.h"
#include "code/om/allocation.h"

namespace engine
{
	// The names the players answer to (the engine's statics, defined in statics/audiodrivernames.cpp)
	extern core::Name<core::CaseSensitiveKey> gPlay3;
	extern core::Name<core::CaseSensitiveKey> gStop2;
	extern core::Name<core::CaseSensitiveKey> gWinddown2;
	extern core::Name<core::CaseSensitiveKey> gStartup2;
	extern core::Name<core::CaseSensitiveKey> gStop3;
	extern core::Name<core::CaseSensitiveKey> gWinddown3;
	extern core::Name<core::CaseSensitiveKey> gIdle2;
}

namespace mgraph
{
	class EnvelopeData;
}

namespace om
{
	template<class T> class DynamicProperty;
}

namespace proto
{
	// 0x10880610 (another unit; name guess): the value of the curve a parameter source holds, for an input
	float EvaluateEnvelope(om::DynamicProperty<mgraph::EnvelopeData>* curve, float input, float low, float high, float half, float two);

	class SoundPlayerHelicopter : public engine::AudioPlayer
	{
	public:
		SoundPlayerHelicopter();
		virtual ~SoundPlayerHelicopter();
		virtual bool Slot1(core::Name<core::CaseSensitiveKey>* name);
		virtual void Slot2(om::DynamicObject* properties);
		virtual bool Slot3();
		virtual void Slot4();
		virtual bool Slot5();
		virtual void Update(unsigned int elapsed);
		// 0x104A6DC0: sets one number of the voices
		void SetUnknown49C(float value);
		// 0x104A6030: a new voice for the player (the player itself is not read)
		unsigned int CreatePlayer();
		OM_ALLOCATION(SoundPlayerHelicopter);

		unsigned int unknown4;
		unsigned int unknown8;
		audio::RemotePlayerHandle player0C;
		audio::RemotePlayerHandle player10;
		audio::RemotePlayerHandle player14;
		audio::RemotePlayerHandle player18;
		audio::RemotePlayerHandle player1C;
		audio::RemotePlayerHandle player20;
		audio::RemotePlayerHandle player24;
		float unknown28;
		float unknown2C;
		float unknown30;
		float unknown34;
		float unknown38;
		float unknown3C;
		float unknown40;
		float unknown44;
		bool unknown48;
		bool unknown49;
		bool unknown4A;
		om::DynamicProperty<mgraph::EnvelopeData>* unknown4C;
		om::DynamicProperty<mgraph::EnvelopeData>* unknown50;
	};

	class SoundPlayerVehicle : public engine::AudioPlayer
	{
	public:
		SoundPlayerVehicle();
		virtual ~SoundPlayerVehicle();
		virtual bool Slot1(core::Name<core::CaseSensitiveKey>* name);
		virtual void Slot2(om::DynamicObject* properties);
		virtual bool Slot3();
		virtual void Slot4();
		virtual bool Slot5();
		virtual void Update(unsigned int elapsed);
		// 0x104A88C0: a new voice for the player (the player itself is not read)
		unsigned int CreatePlayer();
		OM_ALLOCATION(SoundPlayerVehicle);

		unsigned int unknown4;
		unsigned int unknown8;
		audio::RemotePlayerHandle playerC;
		audio::RemotePlayerHandle player10;
		audio::RemotePlayerHandle player14;
		audio::RemotePlayerHandle player18;
		float unknown1C;
		float unknown20;
		float unknown24;
		float unknown28;
		float unknown2C;
		float unknown30;
		float unknown34;
		float unknown38;
		om::DynamicProperty<mgraph::EnvelopeData>* unknown3C;
		om::DynamicProperty<mgraph::EnvelopeData>* unknown40;
	};

	inline const char* SoundPlayerHelicopter::AllocationTag()
	{
		return "";
	}

	inline const char* SoundPlayerVehicle::AllocationTag()
	{
		return "";
	}
}

#endif
