// Fight items of the motion group: LaserTrack (unit 0x10187250 - 0x10187C50; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_LASER_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_LASER_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::LaserTrack (16 vftable slots, 0x70 bytes)
			class LaserTrack : public fight::Track
			{
			public:
				// 0x10187450
				LaserTrack();
				virtual ~LaserTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100E44D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetShader(const fight::Name& newValue);
				bool SetThickness(float newValue);
				bool SetColour(const math::Colour128& newValue);
				bool SetMyJoint(const fight::Name& newValue);
				bool SetMyOffset(const math::Vector& newValue);
				bool SetTargetJoint(const fight::Name& newValue);
				bool SetTargetOffset(const math::Vector& newValue);
				bool SetTrackingSpeed(float newValue);
				bool SetLongitudinalOffset(float newValue);
				bool SetPerpendicularOffset(float newValue);
				bool SetPerpendicularFinalOffset(float newValue);
				bool SetPerpendicularFinalTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name myJoint;  // +0x10
					fight::Name shader;  // +0x18
					fight::Name targetJoint;  // +0x20
					math::Colour128 colour;  // +0x28
					math::Vector myOffset;  // +0x38
					math::Vector targetOffset;  // +0x44
					float longitudinalOffset;  // +0x50
					float perpendicularFinalOffset;  // +0x54
					float perpendicularFinalTime;  // +0x58
					float perpendicularOffset;  // +0x5C
					float thickness;  // +0x60
					float timeBegin;  // +0x64
					float timeEnd;  // +0x68
					float trackingSpeed;  // +0x6C
			};

			extern fight::Property** gLaserTrackProperties;
			fight::TrackFactory* CreateLaserTrackFactory(const char* name);
			void RegisterLaserTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
