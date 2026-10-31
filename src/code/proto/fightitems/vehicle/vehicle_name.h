// Fight items of the vehicle group: VehicleNameCondition (unit 0x1027D9F0 - 0x1027DCE0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_VEHICLE_VEHICLE_NAME_H
#define PROTO_FIGHTITEMS_VEHICLE_VEHICLE_NAME_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/vehicle/vehicledata.h"

namespace proto
{
	namespace fightitems
	{
		namespace vehicle
		{
			// RTTI: proto::fightitems::vehicle::VehicleNameCondition (10 vftable slots, 0x18 bytes)
			class VehicleNameCondition : public fight::Condition
			{
			public:
				// 0x1027DA40
				VehicleNameCondition();
				virtual ~VehicleNameCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1027A130, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetName(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name name;  // +0x10
			};

			extern fight::Property** gVehicleNameConditionProperties;
			fight::ConditionFactory* CreateVehicleNameConditionFactory(const char* name);
			void RegisterVehicleNameConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
