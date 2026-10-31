// Fight items of the motion group: FXLight_PointTrack (unit 0x10162970 - 0x10163BA0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_FXLIGHT_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_FXLIGHT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::FXLight_PointTrack (16 vftable slots, 0xB0 bytes)
			class FXLight_PointTrack : public fight::Track
			{
			public:
				// 0x10162DA0
				FXLight_PointTrack();
				virtual ~FXLight_PointTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100C1660, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetAbortWhenInterrupted(bool newValue);
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetParentObjectName(const fight::Name& newValue);
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
				bool SetEmitSpace(int newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetAttachSpace(int newValue);
				bool SetAttachJoint(const fight::Name& newValue);
				bool SetFalloff(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name attachJoint;  // +0x10
					fight::Name parentObjectName;  // +0x18
					math::Colour128 endColour;  // +0x20
					math::Colour128 startColour;  // +0x30
					math::Vector offset;  // +0x40
					float duration;  // +0x4C
					float durationRand;  // +0x50
					float fadeIn;  // +0x54
					float fadeInRand;  // +0x58
					float fadeOut;  // +0x5C
					float fadeOutRand;  // +0x60
					float flickerIntensityFreq;  // +0x64
					float flickerIntensityFreqRand;  // +0x68
					float flickerIntensityMag;  // +0x6C
					float flickerIntensityMagRand;  // +0x70
					float flickerRadiusFreq;  // +0x74
					float flickerRadiusFreqRand;  // +0x78
					float flickerRadiusMag;  // +0x7C
					float flickerRadiusMagRand;  // +0x80
					float intensity;  // +0x84
					float intensityRand;  // +0x88
					float radius;  // +0x8C
					float radiusRand;  // +0x90
					float timeBegin;  // +0x94
					float timeEnd;  // +0x98
					float wait;  // +0x9C
					float waitRand;  // +0xA0
					int attachSpace;  // +0xA4
					int emitSpace;  // +0xA8
					bool abortWhenInterrupted;  // +0xAC
					bool falloff;  // +0xAD
					unsigned char unknownAE[0x2];
			};

			extern fight::Property** gFXLight_PointTrackProperties;
			fight::TrackFactory* CreateFXLight_PointTrackFactory(const char* name);
			void RegisterFXLight_PointTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
