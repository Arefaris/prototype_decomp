// Fight items of the motion group: VehicleReticuleTrack (unit 0x101CAFF0 - 0x101CB300; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_VEHICLERETICULE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_VEHICLERETICULE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::VehicleReticuleTrack (16 vftable slots, 0x14 bytes)
			class VehicleReticuleTrack : public fight::Track
			{
			public:
				// 0x101CB030
				VehicleReticuleTrack();
				virtual ~VehicleReticuleTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1012BA90, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetReticuleOn(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool reticuleOn;  // +0x10
					unsigned char unknown11[0x3];
			};

			extern fight::Property** gVehicleReticuleTrackProperties;
			fight::TrackFactory* CreateVehicleReticuleTrackFactory(const char* name);
			void RegisterVehicleReticuleTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::VehicleReticuleAction (9 vftable slots, 0x2C bytes)
			class VehicleReticuleAction : public fight::Action
			{
			public:
				// 0x1012B9F0
				VehicleReticuleAction(VehicleReticuleTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1012B930
				virtual ~VehicleReticuleAction();

				// vftable slot 5 (0x1012B960)
				virtual bool Slot5(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<VehicleReticuleTrack> link;  // +0x20
			};

			// ---- actions end
		}
	}
}

#endif
