// Fight items of the motion group: JointAnchorToAnimationTrack (unit 0x10182180 - 0x101827B0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_JOINTANCHORTOANIMATION_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_JOINTANCHORTOANIMATION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::JointAnchorToAnimationTrack (16 vftable slots, 0x30 bytes)
			class JointAnchorToAnimationTrack : public fight::Track
			{
			public:
				// 0x10182260
				JointAnchorToAnimationTrack();
				virtual ~JointAnchorToAnimationTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100DD100, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetAnimation(const fight::Name& newValue);
				bool SetFrame(float newValue);
				bool SetPriority(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animation;  // +0x10
					fight::Name joint;  // +0x18
					float frame;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					int priority;  // +0x2C
			};

			extern fight::Property** gJointAnchorToAnimationTrackProperties;
			fight::TrackFactory* CreateJointAnchorToAnimationTrackFactory(const char* name);
			void RegisterJointAnchorToAnimationTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
