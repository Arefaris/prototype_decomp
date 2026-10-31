// Fight items of the motion group: JumpAnimationTrack (unit 0x10184DF0 - 0x10185900; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_JUMPANIMATION_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_JUMPANIMATION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::JumpAnimationTrack (16 vftable slots, 0x58 bytes)
			class JumpAnimationTrack : public fight::Track
			{
			public:
				// 0x10185020
				JumpAnimationTrack();
				virtual ~JumpAnimationTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100E0560, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAnimation(const fight::Name& newValue);
				bool SetGravity(float newValue);
				bool SetPeakVerticalVelocity(float newValue);
				bool SetStartFrameClimb(float newValue);
				bool SetEndFrameClimb(float newValue);
				bool SetStartFramePeak(float newValue);
				bool SetEndFramePeak(float newValue);
				bool SetStartFrameFall(float newValue);
				bool SetEndFrameFall(float newValue);
				bool SetSpew(bool newValue);
				bool SetHasRootTranslation(bool newValue);
				bool SetHasRootRotation(bool newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animation;  // +0x10
					fight::Name partition;  // +0x18
					float blendInTime;  // +0x20
					float blendOutTime;  // +0x24
					float endFrameClimb;  // +0x28
					float endFrameFall;  // +0x2C
					float endFramePeak;  // +0x30
					float gravity;  // +0x34
					float peakVerticalVelocity;  // +0x38
					float startFrameClimb;  // +0x3C
					float startFrameFall;  // +0x40
					float startFramePeak;  // +0x44
					float timeBegin;  // +0x48
					float timeEnd;  // +0x4C
					int priority;  // +0x50
					bool hasRootRotation;  // +0x54
					bool hasRootTranslation;  // +0x55
					bool spew;  // +0x56
					unsigned char unknown57[0x1];
			};

			extern fight::Property** gJumpAnimationTrackProperties;
			fight::TrackFactory* CreateJumpAnimationTrackFactory(const char* name);
			void RegisterJumpAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
