// Fight items of the motion group: PushbackVelocityCondition, PushbackDirectionCondition, ReactionHitPushbackAddTrack (unit 0x101AA2B0 - 0x101AADF0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_PUSHBACK_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_PUSHBACK_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::PushbackVelocityCondition (10 vftable slots, 0x14 bytes)
			class PushbackVelocityCondition : public fight::Condition
			{
			public:
				// 0x101AA390
				PushbackVelocityCondition();
				virtual ~PushbackVelocityCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1010DBB0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetVelocity(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float velocity;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gPushbackVelocityConditionProperties;
			fight::ConditionFactory* CreatePushbackVelocityConditionFactory(const char* name);
			void RegisterPushbackVelocityConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PushbackDirectionCondition (10 vftable slots, 0x14 bytes)
			class PushbackDirectionCondition : public fight::Condition
			{
			public:
				// 0x101AA400
				PushbackDirectionCondition();
				virtual ~PushbackDirectionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1010DCC0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDirection(float newValue);
				bool SetArc(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float arc;  // +0xC
					float direction;  // +0x10
			};

			extern fight::Property** gPushbackDirectionConditionProperties;
			fight::ConditionFactory* CreatePushbackDirectionConditionFactory(const char* name);
			void RegisterPushbackDirectionConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitPushbackAddTrack (16 vftable slots, 0x18 bytes)
			class ReactionHitPushbackAddTrack : public fight::Track
			{
			public:
				// 0x101AA480
				ReactionHitPushbackAddTrack();
				virtual ~ReactionHitPushbackAddTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1010E1C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetScale(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float scale;  // +0x10
					float timeBegin;  // +0x14
			};

			extern fight::Property** gReactionHitPushbackAddTrackProperties;
			fight::TrackFactory* CreateReactionHitPushbackAddTrackFactory(const char* name);
			void RegisterReactionHitPushbackAddTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
