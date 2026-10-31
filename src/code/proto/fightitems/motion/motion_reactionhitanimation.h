// Fight items of the motion group: ReactionHitAnimationTrack (unit 0x101A9500 - 0x101A9F10; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONHITANIMATION_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONHITANIMATION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ReactionHitAnimationTrack (16 vftable slots, 0x58 bytes)
			class ReactionHitAnimationTrack : public fight::Track
			{
			public:
				// 0x101A96F0
				ReactionHitAnimationTrack();
				virtual ~ReactionHitAnimationTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1010D560, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeScale(float newValue);
				bool SetTimeEndMin(float newValue);
				bool SetAnimation(const fight::Name& newValue);
				bool SetSpeed(float newValue);
				bool SetSpeedMax(float newValue);
				bool SetInitFrame(float newValue);
				bool SetRandomFrame(float newValue);
				bool SetStartFrame(float newValue);
				bool SetEndFrame(float newValue);
				bool SetCyclic(int newValue);
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
					float endFrame;  // +0x28
					float initFrame;  // +0x2C
					float randomFrame;  // +0x30
					float speed;  // +0x34
					float speedMax;  // +0x38
					float startFrame;  // +0x3C
					float timeBegin;  // +0x40
					float timeEndMin;  // +0x44
					float timeScale;  // +0x48
					int cyclic;  // +0x4C
					int priority;  // +0x50
					unsigned char unknown54[0x4];
			};

			extern fight::Property** gReactionHitAnimationTrackProperties;
			fight::TrackFactory* CreateReactionHitAnimationTrackFactory(const char* name);
			void RegisterReactionHitAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
