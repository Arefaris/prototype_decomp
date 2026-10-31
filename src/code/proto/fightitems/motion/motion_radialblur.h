// Fight items of the motion group: RadialBlurTrack (unit 0x1019F890 - 0x101A0B00; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_RADIALBLUR_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_RADIALBLUR_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::RadialBlurTrack (16 vftable slots, 0xA0 bytes)
			class RadialBlurTrack : public fight::Track
			{
			public:
				// 0x1019FCF0
				RadialBlurTrack();
				virtual ~RadialBlurTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10104DD0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetWait(float newValue);
				bool SetFadeIn(float newValue);
				bool SetDuration(float newValue);
				bool SetFadeOut(float newValue);
				bool SetWaitRand(float newValue);
				bool SetFadeInRand(float newValue);
				bool SetDurationRand(float newValue);
				bool SetFadeOutRand(float newValue);
				bool SetIntensityStart(float newValue);
				bool SetIntensityEnd(float newValue);
				bool SetSizeStart(float newValue);
				bool SetSizeEnd(float newValue);
				bool SetFalloffStart(float newValue);
				bool SetFalloffEnd(float newValue);
				bool SetFlickerIntensityFreq(float newValue);
				bool SetFlickerIntensityFreqRand(float newValue);
				bool SetFlickerIntensityMag(float newValue);
				bool SetFlickerIntensityMagRand(float newValue);
				bool SetFlickerSizeFreq(float newValue);
				bool SetFlickerSizeFreqRand(float newValue);
				bool SetFlickerSizeMag(float newValue);
				bool SetFlickerSizeMagRand(float newValue);
				bool SetFlickerFalloffFreq(float newValue);
				bool SetFlickerFalloffFreqRand(float newValue);
				bool SetFlickerFalloffMag(float newValue);
				bool SetFlickerFalloffMagRand(float newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetAttachSpace(int newValue);
				bool SetAttachJoint(const fight::Name& newValue);
				bool SetPatch(const char* newValue);
				bool SetInGameCameraOnly(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name attachJoint;  // +0x10
					math::Vector offset;  // +0x18
					char* patch;  // +0x24
					float duration;  // +0x28
					float durationRand;  // +0x2C
					float fadeIn;  // +0x30
					float fadeInRand;  // +0x34
					float fadeOut;  // +0x38
					float fadeOutRand;  // +0x3C
					float falloffEnd;  // +0x40
					float falloffStart;  // +0x44
					float flickerFalloffFreq;  // +0x48
					float flickerFalloffFreqRand;  // +0x4C
					float flickerFalloffMag;  // +0x50
					float flickerFalloffMagRand;  // +0x54
					float flickerIntensityFreq;  // +0x58
					float flickerIntensityFreqRand;  // +0x5C
					float flickerIntensityMag;  // +0x60
					float flickerIntensityMagRand;  // +0x64
					float flickerSizeFreq;  // +0x68
					float flickerSizeFreqRand;  // +0x6C
					float flickerSizeMag;  // +0x70
					float flickerSizeMagRand;  // +0x74
					float intensityEnd;  // +0x78
					float intensityStart;  // +0x7C
					float sizeEnd;  // +0x80
					float sizeStart;  // +0x84
					float timeBegin;  // +0x88
					float timeEnd;  // +0x8C
					float wait;  // +0x90
					float waitRand;  // +0x94
					int attachSpace;  // +0x98
					bool inGameCameraOnly;  // +0x9C
					unsigned char unknown9D[0x3];
			};

			extern fight::Property** gRadialBlurTrackProperties;
			fight::TrackFactory* CreateRadialBlurTrackFactory(const char* name);
			void RegisterRadialBlurTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
