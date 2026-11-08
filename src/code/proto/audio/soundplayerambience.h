// proto::SoundPlayerAmbience (RTTI): the sound player of the city's ambience (the crowds, the traffic, the infected, the
// parks). Its settings are dynamic properties that the game's data sets by name: a table per type of value maps the name of
// a property to the member function that stores it. The member names are made from the property names (guesses).
// Of the class only what is reconstructed is declared.
#ifndef PROTO_AUDIO_SOUNDPLAYERAMBIENCE_H
#define PROTO_AUDIO_SOUNDPLAYERAMBIENCE_H

#include "code/audio/remoteplayerevent.h"
#include "code/engine/audio/audioplayer.h"
#include "code/mgraph/envelope.h"
#include "code/om/dynamicarray.h"
#include "code/om/dynamicobject.h"
#include "code/om/string.h"

namespace proto
{
	// The gains of the four speakers of a group of sounds (left front, right front, left side and right side)
	struct SpeakerGains
	{
		// 0x104A3000: all four start with the value of the last
		SpeakerGains();

		float lf;
		float rf;
		float ls;
		float rs;
	};

	class SoundPlayerAmbience : public engine::AudioPlayer
	{
	public:
		virtual ~SoundPlayerAmbience();
		virtual bool Slot1(core::Name<core::CaseSensitiveKey>* name);
		virtual void Slot2(om::DynamicObject* properties);
		virtual bool Slot3();
		virtual void Slot4();
		virtual bool Slot5();
		virtual void Update(unsigned int elapsed);

		// The setters of the properties: the settings that do nothing (they are kept in the data), the strings,
		// the names of the mix busses, the five envelopes and the numbers
		void SetLoop(bool value);
		void SetSmallSphereMult(float value);
		void SetMedSphereMult(float value);
		void SetMinRadius(float value);
		void SetListenerYOffsetMax(float value);
		void SetListenerMoveConst(float value);
		void SetWorldPointDistance(float value);
		void SetWorldPointRadius(float value);
		void SetRooftopOffset(float value);
		void SetCrowdUp(float value);
		void SetCrowdDown(float value);
		void SetCrowdUpChannel(float value);
		void SetCrowdDownChannel(float value);
		void SetInfUp(float value);
		void SetInfDown(float value);
		void SetInfUpChannel(float value);
		void SetInfDownChannel(float value);
		void SetInfectedZoneMinVolume(float value);
		void SetGroup(const om::String& value);
		void SetInfLocalLfMult(float value);
		void SetInfLocalLsMult(float value);
		void SetInfLocalRsMult(float value);
		void SetInfLocalRfMult(float value);
		void SetInfLfMult(float value);
		void SetInfLsMult(float value);
		void SetInfRsMult(float value);
		void SetInfRfMult(float value);
		void SetCrowdLocalLfMult(float value);
		void SetCrowdLocalLsMult(float value);
		void SetCrowdLocalRsMult(float value);
		void SetCrowdLocalRfMult(float value);
		void SetCrowdLfMult(float value);
		void SetCrowdLsMult(float value);
		void SetCrowdRsMult(float value);
		void SetCrowdRfMult(float value);
		void SetIdleLfMult(float value);
		void SetIdleLsMult(float value);
		void SetIdleRsMult(float value);
		void SetIdleRfMult(float value);
		void SetReverbSend(float value);
		void SetDistanceFilter(float value);
		void SetVolume(float value);
		void SetCityVol(float value);
		void SetCrowdPanicVol(float value);
		void SetTrafficIdleVol(float value);
		void SetTrafficPanicVol(float value);
		void SetRooftopVolume(float value);
		void SetInfectedVol(float value);
		void SetInfectedLocalVol(float value);
		void SetParkVol(float value);
		void SetCrowdLocalVol(float value);
		void SetFilename(const om::String& value);
		void SetMixbus(const om::DynamicArray<om::String, unsigned short>& value);
		void SetTrafficIdleEnv(const mgraph::EnvelopeData& value);
		void SetRofftopEnv(const mgraph::EnvelopeData& value);
		void SetTrafficPanicEnv(const mgraph::EnvelopeData& value);
		void SetCrowdPanicEnv(const mgraph::EnvelopeData& value);
		void SetInfectedEnv(const mgraph::EnvelopeData& value);
		OM_ALLOCATION(SoundPlayerAmbience);

		unsigned int unknown4;
		unsigned int unknown8;
		SpeakerGains infLocal;  // 0xC
		SpeakerGains inf;  // 0x1C
		SpeakerGains crowd;  // 0x2C
		SpeakerGains crowdLocal;  // 0x3C
		SpeakerGains idle;  // 0x4C
		audio::RemotePlayerHandle player;  // 0x5C
		mgraph::EnvelopeData trafficIdleEnv;  // 0x60
		mgraph::EnvelopeData rooftopEnv;  // 0x70
		mgraph::EnvelopeData trafficPanicEnv;  // 0x80
		mgraph::EnvelopeData crowdPanicEnv;  // 0x90
		mgraph::EnvelopeData infectedEnv;  // 0xA0
		float reverbSend;  // 0xB0
		float distanceFilter;  // 0xB4
		float volume;  // 0xB8
		float cityVol;  // 0xBC
		float crowdPanicVol;  // 0xC0
		float trafficIdleVol;  // 0xC4
		float trafficPanicVol;  // 0xC8
		float rooftopVolume;  // 0xCC
		float infectedVol;  // 0xD0
		float infectedLocalVol;  // 0xD4
		float parkVol;  // 0xD8
		float crowdLocalVol;  // 0xDC
	};

	inline const char* SoundPlayerAmbience::AllocationTag()
	{
		return "";
	}
}

#endif
