// Fight items of the motion group: ImpulseTrack (unit 0x10180910 - 0x10180EC0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_IMPULSE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_IMPULSE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ImpulseTrack (16 vftable slots, 0x40 bytes)
			class ImpulseTrack : public fight::Track
			{
			public:
				// 0x101809E0
				ImpulseTrack();
				virtual ~ImpulseTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100DB4D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetImpulse(const math::Vector& newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetOrientation(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name joint;  // +0x10
					math::Vector impulse;  // +0x18
					math::Vector offset;  // +0x24
					math::Vector orientation;  // +0x30
					float timeBegin;  // +0x3C
			};

			extern fight::Property** gImpulseTrackProperties;
			fight::TrackFactory* CreateImpulseTrackFactory(const char* name);
			void RegisterImpulseTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
