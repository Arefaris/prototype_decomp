// Fight items of the motion group: BloodSplatterTrack (unit 0x10143E60 - 0x10144950; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_BLOODSPLATTER_H
#define PROTO_FIGHTITEMS_MOTION_BLOODSPLATTER_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::BloodSplatterTrack (16 vftable slots, 0x68 bytes)
			class BloodSplatterTrack : public fight::Track
			{
			public:
				// 0x10144110
				BloodSplatterTrack();
				virtual ~BloodSplatterTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1009D690, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float value);
				bool SetTimeEnd(float value);
				bool SetShader(const fight::Name& value);
				bool SetWait(float value);
				bool SetDuration(float value);
				bool SetFadeDuration(float value);
				bool SetWaitRand(float value);
				bool SetDurationRand(float value);
				bool SetFadeDurationRand(float value);
				bool SetPositionX(float value);
				bool SetPositionY(float value);
				bool SetPositionXRand(float value);
				bool SetPositionYRand(float value);
				bool SetScaleX(float value);
				bool SetScaleY(float value);
				bool SetScaleXYRand(float value);
				bool SetScaleXRand(float value);
				bool SetScaleYRand(float value);
				bool SetAngle(float value);
				bool SetAngleRand(float value);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name shader;  // +0x10
					float angle;  // +0x18
					float angleRand;  // +0x1C
					float duration;  // +0x20
					float durationRand;  // +0x24
					float fadeDuration;  // +0x28
					float fadeDurationRand;  // +0x2C
					float positionX;  // +0x30
					float positionXRand;  // +0x34
					float positionY;  // +0x38
					float positionYRand;  // +0x3C
					float scaleX;  // +0x40
					float scaleXRand;  // +0x44
					float scaleXYRand;  // +0x48
					float scaleY;  // +0x4C
					float scaleYRand;  // +0x50
					float timeBegin;  // +0x54
					float timeEnd;  // +0x58
					float wait;  // +0x5C
					float waitRand;  // +0x60
					unsigned char unknown64[0x4];
			};

			extern fight::Property** gBloodSplatterTrackProperties;
			fight::TrackFactory* CreateBloodSplatterTrackFactory(const char* name);
			void RegisterBloodSplatterTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
