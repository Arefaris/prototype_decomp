// Fight items of the motion group: VehicleReticuleTrack (unit 0x101CAFF0 - 0x101CB300; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_vehiclereticule.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gVehicleReticuleTrackProperties;  // 0x11254C8C

			// FUNCTION: ENGINE 0x101CAFF0
			bool VehicleReticuleTrack::SetReticuleOn(bool newValue)
			{
				reticuleOn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CB000
			fight::Property* VehicleReticuleTrack::GetProperty(int index)
			{
				return gVehicleReticuleTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101CB020
			void VehicleReticuleTrack::ClearProperties()
			{
				fight::FreePropertyList(&gVehicleReticuleTrackProperties);
			}

			// FUNCTION: ENGINE 0x101CB030
			VehicleReticuleTrack::VehicleReticuleTrack() : reticuleOn(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101CB060
			float VehicleReticuleTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101CB070
			float VehicleReticuleTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101CB080
			VehicleReticuleTrack::~VehicleReticuleTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CB190
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void VehicleReticuleTrack::RegisterProperties()
			{
				if (gVehicleReticuleTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<VehicleReticuleTrack>("reticuleOn", &VehicleReticuleTrack::SetReticuleOn);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gVehicleReticuleTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101CB160
			fight::TrackFactory* CreateVehicleReticuleTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<VehicleReticuleTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CB230
			void RegisterVehicleReticuleTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<VehicleReticuleTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyBool<VehicleReticuleTrack>;
			template class fight::TrackFactoryTemplate<VehicleReticuleTrack>;
			template class fight::TrackFactoryCasterTemplate<VehicleReticuleTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101CB090
// FUNCTION: ENGINE 0x101CB0C0
// FUNCTION: ENGINE 0x101CB0D0
// FUNCTION: ENGINE 0x101CB100
// FUNCTION: ENGINE 0x101CB130
// FUNCTION: ENGINE 0x101CB150
// FUNCTION: ENGINE 0x101CB260
// FUNCTION: ENGINE 0x101CB290
// FUNCTION: ENGINE 0x101CB2B0
