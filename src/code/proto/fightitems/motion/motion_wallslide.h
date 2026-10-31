// Fight items of the motion group: WallSlideTrack (unit 0x101D0240 - 0x101D0A00; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_WALLSLIDE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_WALLSLIDE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::WallSlideTrack (16 vftable slots, 0x3C bytes)
			class WallSlideTrack : public fight::Track
			{
			public:
				// 0x101D03B0
				WallSlideTrack();
				virtual ~WallSlideTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10134110, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocityMin(float newValue);
				bool SetVelocityMax(float newValue);
				bool SetFrictionMin(float newValue);
				bool SetFrictionMax(float newValue);
				bool SetContinuous(bool newValue);
				bool SetContinuousGravity(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float continuousGravity;  // +0x18
					float frictionMax;  // +0x1C
					float frictionMin;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					float velocityMax;  // +0x2C
					float velocityMin;  // +0x30
					int priority;  // +0x34
					bool continuous;  // +0x38
					unsigned char unknown39[0x3];
			};

			extern fight::Property** gWallSlideTrackProperties;
			fight::TrackFactory* CreateWallSlideTrackFactory(const char* name);
			void RegisterWallSlideTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
