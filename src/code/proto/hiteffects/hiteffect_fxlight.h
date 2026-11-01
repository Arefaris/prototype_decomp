// Fight items of the hit effects: FXLight_PointTrack (unit 0x10505220 - 0x1050DEE0; no assert path, the file name is a guess).
#ifndef PROTO_HITEFFECTMANAGER_HITEFFECT_FXLIGHT_H
#define PROTO_HITEFFECTMANAGER_HITEFFECT_FXLIGHT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/hiteffects/hiteffectdata.h"

namespace proto
{
	namespace HitEffectManager
	{
		// RTTI: proto::HitEffectManager::FXLight_PointTrack (16 vftable slots, 0xC8 bytes)
		class FXLight_PointTrack : public fight::Track
		{
		public:
			// 0x10508AC0
			FXLight_PointTrack();
			virtual ~FXLight_PointTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x10501390, another unit)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float newValue);
			bool SetTimeEnd(float newValue);
			bool SetEmitSpace(int newValue);
			bool SetEmitJoint(const fight::Name& newValue);
			bool SetBlendFromImpulseToHit(float newValue);
			bool SetAttachTo(int newValue);
			bool SetAttachSpace(int newValue);
			bool SetAttachJoint(const fight::Name& newValue);
			bool SetOffset(const math::Vector& newValue);
			bool SetOrientation(const math::Vector& newValue);
			bool SetRunTillInterrupted(bool newValue);
			bool SetWait(float newValue);
			bool SetFadeIn(float newValue);
			bool SetDuration(float newValue);
			bool SetFadeOut(float newValue);
			bool SetWaitRand(float newValue);
			bool SetFadeInRand(float newValue);
			bool SetDurationRand(float newValue);
			bool SetFadeOutRand(float newValue);
			bool SetIntensity(float newValue);
			bool SetRadius(float newValue);
			bool SetIntensityRand(float newValue);
			bool SetRadiusRand(float newValue);
			bool SetFlickerIntensityFreq(float newValue);
			bool SetFlickerIntensityFreqRand(float newValue);
			bool SetFlickerIntensityMag(float newValue);
			bool SetFlickerIntensityMagRand(float newValue);
			bool SetFlickerRadiusFreq(float newValue);
			bool SetFlickerRadiusFreqRand(float newValue);
			bool SetFlickerRadiusMag(float newValue);
			bool SetFlickerRadiusMagRand(float newValue);
			bool SetStartColour(const math::Colour128& newValue);
			bool SetEndColour(const math::Colour128& newValue);
			bool SetFalloff(bool newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			fight::Name attachJoint;  // +0x10
			fight::Name emitJoint;  // +0x18
			math::Colour128 endColour;  // +0x20
			math::Colour128 startColour;  // +0x30
			math::Vector offset;  // +0x40
			math::Vector orientation;  // +0x4C
			float blendFromImpulseToHit;  // +0x58
			float duration;  // +0x5C
			float durationRand;  // +0x60
			float fadeIn;  // +0x64
			float fadeInRand;  // +0x68
			float fadeOut;  // +0x6C
			float fadeOutRand;  // +0x70
			float flickerIntensityFreq;  // +0x74
			float flickerIntensityFreqRand;  // +0x78
			float flickerIntensityMag;  // +0x7C
			float flickerIntensityMagRand;  // +0x80
			float flickerRadiusFreq;  // +0x84
			float flickerRadiusFreqRand;  // +0x88
			float flickerRadiusMag;  // +0x8C
			float flickerRadiusMagRand;  // +0x90
			float intensity;  // +0x94
			float intensityRand;  // +0x98
			float radius;  // +0x9C
			float radiusRand;  // +0xA0
			float timeBegin;  // +0xA4
			float timeEnd;  // +0xA8
			float wait;  // +0xAC
			float waitRand;  // +0xB0
			int attachSpace;  // +0xB4
			int attachTo;  // +0xB8
			int emitSpace;  // +0xBC
			bool falloff;  // +0xC0
			bool runTillInterrupted;  // +0xC1
			unsigned char unknownC2[0x6];
		};

		extern fight::Property** gFXLight_PointTrackProperties;
		fight::TrackFactory* CreateFXLight_PointTrackFactory(const char* name);
		void RegisterFXLight_PointTrackFactory(fight::TrackRegistry* registry, const char* name);

	}
}

#endif
