// Fight items of the motion group: JumpAnimationTrack (unit 0x10184DF0 - 0x10185900; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_JUMPANIMATION_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_JUMPANIMATION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/engine/fight/effecttrack.h"

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

				float GetEndFrameClimb() const { return endFrameClimb; }
				float GetStartFramePeak() const { return startFramePeak; }
				float GetEndFramePeak() const { return endFramePeak; }
				float GetStartFrameFall() const { return startFrameFall; }
				float GetEndFrameFall() const { return endFrameFall; }
				bool GetSpew() const { return spew; }
				bool GetHasRootTranslation() const { return hasRootTranslation; }
				bool GetHasRootRotation() const { return hasRootRotation; }
				const fight::Name& GetPartition() const { return partition; }
				int GetPriority() const { return priority; }
				float GetBlendInTime() const { return blendInTime; }
				float GetBlendOutTime() const { return blendOutTime; }
				float GetGravity() const { return gravity; }
				float GetPeakVerticalVelocity() const { return peakVerticalVelocity; }
				float GetStartFrameClimb() const { return startFrameClimb; }

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

			// ---- actions begin
			// RTTI: proto::fightitems::motion::JumpAnimationAction (9 vftable slots, 0x48 bytes)
			class JumpAnimationAction : public fight::Action
			{
			public:
				// 0x100E03B0
				JumpAnimationAction(fight::Track* listener, JumpAnimationTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100E0250
				virtual ~JumpAnimationAction();

				// vftable slot 5 (0x100E06B0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100E02A0)
				virtual void Slot6();
				// vftable slot 7 (0x100E0A50)
				virtual bool Slot7(int arg, float value);

				// 0x100E00D0: the vertical velocity of an object; the engine's copy is a member that never reads its object (name guess)
				float GetVerticalVelocity(engine::GameObject* object);
				// 0x100E05B0: moves the driver to the phase the vertical velocity of the object is in (name guess)
				float UpdatePhase(engine::GameObject* object);
				// 0x100E0130 / 0x100E0480 / 0x100E04C0 / 0x100E0500: the frames each phase plays (names guess)
				void SetRange(float duration, float start, float end);
				void SetClimbRange(float height, float peak);
				void SetPeakRange(float height, float peak);
				void SetFallRange();

				engine::TrackWatch watch;  // +0x1C
				core::Link<JumpAnimationTrack> link;  // +0x28
				engine::GameObjectHandle target;  // +0x34
				choreo::Driver* driver;  // +0x38
				float unknown3C;  // +0x3C
				int phase;  // +0x40
				int unknown44;  // +0x44
			};

			// ---- actions end

		}
	}
}

#endif
