// Fight items of the motion group: MoveAtVelocityTrack (unit 0x10192C50 - 0x10193360; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_MOVEATVELOCITY_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_MOVEATVELOCITY_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::MoveAtVelocityTrack (16 vftable slots, 0x40 bytes)
			class MoveAtVelocityTrack : public fight::Track
			{
			public:
				// 0x10192D60
				MoveAtVelocityTrack();
				virtual ~MoveAtVelocityTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100F5DD0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocityBegin(const math::Vector& newValue);
				bool SetVelocityEnd(const math::Vector& newValue);
				bool SetUseInput(bool newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector velocityBegin;  // +0x10
					math::Vector velocityEnd;  // +0x1C
					float blendInTime;  // +0x28
					float blendOutTime;  // +0x2C
					float timeBegin;  // +0x30
					float timeEnd;  // +0x34
					int priority;  // +0x38
					bool useInput;  // +0x3C
					unsigned char unknown3D[0x3];
			};

			extern fight::Property** gMoveAtVelocityTrackProperties;
			fight::TrackFactory* CreateMoveAtVelocityTrackFactory(const char* name);
			void RegisterMoveAtVelocityTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
