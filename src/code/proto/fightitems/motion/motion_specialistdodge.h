// Fight items of the motion group: SpecialistDodgeTrack (unit 0x101B5700 - 0x101B5FB0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_SPECIALISTDODGE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_SPECIALISTDODGE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::SpecialistDodgeTrack (16 vftable slots, 0x44 bytes)
			class SpecialistDodgeTrack : public fight::Track
			{
			public:
				// 0x101B5890
				SpecialistDodgeTrack();
				virtual ~SpecialistDodgeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10119380, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMoveBegin(float newValue);
				bool SetMoveEnd(float newValue);
				bool SetMoveDistance(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);
				bool SetDistanceToAttractorWeight(float newValue);
				bool SetMaxDistanceToAttractor(float newValue);
				fight::TrackGroup* GetLeftAnim();
				fight::TrackGroup* GetRightAnim();
				fight::TrackGroup* GetBackAnim();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::TrackGroup backAnim;  // +0x10
					fight::TrackGroup leftAnim;  // +0x14
					fight::TrackGroup rightAnim;  // +0x18
					float blendInTime;  // +0x1C
					float blendOutTime;  // +0x20
					float distanceToAttractorWeight;  // +0x24
					float maxDistanceToAttractor;  // +0x28
					float moveBegin;  // +0x2C
					float moveDistance;  // +0x30
					float moveEnd;  // +0x34
					float timeBegin;  // +0x38
					float timeEnd;  // +0x3C
					int priority;  // +0x40
			};

			extern fight::Property** gSpecialistDodgeTrackProperties;
			fight::TrackFactory* CreateSpecialistDodgeTrackFactory(const char* name);
			void RegisterSpecialistDodgeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
