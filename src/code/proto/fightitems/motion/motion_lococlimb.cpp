// Fight items of the motion group: LocoClimbTrack (unit 0x10187C50 - 0x10188680; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_lococlimb.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gLocoClimbTrackProperties;  // 0x112547AC

			// FUNCTION: ENGINE 0x10187C50
			bool LocoClimbTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187C70
			bool LocoClimbTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187C90
			bool LocoClimbTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187CB0
			bool LocoClimbTrack::SetVelocityNorth(float newValue)
			{
				velocityNorth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187CD0
			bool LocoClimbTrack::SetVelocityStrafe(float newValue)
			{
				velocityStrafe = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187CF0
			bool LocoClimbTrack::SetVelocitySouth(float newValue)
			{
				velocitySouth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187D10
			bool LocoClimbTrack::SetPhase(float newValue)
			{
				phase = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187DB0
			bool LocoClimbTrack::SetLocomotion(const fight::Name& newValue)
			{
				locomotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187DD0
			bool LocoClimbTrack::SetAnimIdle(const fight::Name& newValue)
			{
				animIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187DF0
			bool LocoClimbTrack::SetAnimNorth(const fight::Name& newValue)
			{
				animNorth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187E10
			bool LocoClimbTrack::SetAnimEast(const fight::Name& newValue)
			{
				animEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187E30
			bool LocoClimbTrack::SetAnimSouth(const fight::Name& newValue)
			{
				animSouth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187E50
			bool LocoClimbTrack::SetAnimWest(const fight::Name& newValue)
			{
				animWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187E70
			bool LocoClimbTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187D30
			bool LocoClimbTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187D40
			bool LocoClimbTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187D60
			bool LocoClimbTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10187D80
			fight::Property* LocoClimbTrack::GetProperty(int index)
			{
				return gLocoClimbTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10187DA0
			void LocoClimbTrack::ClearProperties()
			{
				fight::FreePropertyList(&gLocoClimbTrackProperties);
			}

			// FUNCTION: ENGINE 0x10187E90
			LocoClimbTrack::LocoClimbTrack() : acceleration(5e+01f), blendInTime(0.0f), blendOutTime(0.0f), phase(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), velocityNorth(-1.0f), velocitySouth(-1.0f), velocityStrafe(-1.0f), priority(0)
			{
			}

			// FUNCTION: ENGINE 0x10187F50
			float LocoClimbTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10187F60
			float LocoClimbTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10187F70
			LocoClimbTrack::~LocoClimbTrack()
			{
			}

			// FUNCTION: ENGINE 0x10188170
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void LocoClimbTrack::RegisterProperties()
			{
				if (gLocoClimbTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<LocoClimbTrack>("timeBegin", &LocoClimbTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<LocoClimbTrack>("timeEnd", &LocoClimbTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<LocoClimbTrack>("acceleration", &LocoClimbTrack::SetAcceleration);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<LocoClimbTrack>("velocityNorth", &LocoClimbTrack::SetVelocityNorth);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<LocoClimbTrack>("velocityStrafe", &LocoClimbTrack::SetVelocityStrafe);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<LocoClimbTrack>("velocitySouth", &LocoClimbTrack::SetVelocitySouth);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<LocoClimbTrack>("phase", &LocoClimbTrack::SetPhase);
					properties[6] = property;
					property = new fight::PropertyName<LocoClimbTrack>("locomotion", &LocoClimbTrack::SetLocomotion);
					properties[7] = property;
					property = new fight::PropertyName<LocoClimbTrack>("animIdle", &LocoClimbTrack::SetAnimIdle);
					properties[8] = property;
					property = new fight::PropertyName<LocoClimbTrack>("animNorth", &LocoClimbTrack::SetAnimNorth);
					properties[9] = property;
					property = new fight::PropertyName<LocoClimbTrack>("animEast", &LocoClimbTrack::SetAnimEast);
					properties[10] = property;
					property = new fight::PropertyName<LocoClimbTrack>("animSouth", &LocoClimbTrack::SetAnimSouth);
					properties[11] = property;
					property = new fight::PropertyName<LocoClimbTrack>("animWest", &LocoClimbTrack::SetAnimWest);
					properties[12] = property;
					property = new fight::PropertyName<LocoClimbTrack>("partition", &LocoClimbTrack::SetPartition);
					properties[13] = property;
					property = new fight::PropertyIntConstRange<LocoClimbTrack>("priority", &LocoClimbTrack::SetPriority);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<LocoClimbTrack>("blendInTime", &LocoClimbTrack::SetBlendInTime);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<LocoClimbTrack>("blendOutTime", &LocoClimbTrack::SetBlendOutTime);
					properties[16] = property;
					fight::RegisterPropertyList(properties, &gLocoClimbTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101880C0
			fight::TrackFactory* CreateLocoClimbTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoClimbTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101880F0
			void RegisterLocoClimbTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoClimbTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<LocoClimbTrack>;
			template class fight::PropertyName<LocoClimbTrack>;
			template class fight::PropertyIntConstRange<LocoClimbTrack>;
			template class fight::TrackFactoryTemplate<LocoClimbTrack>;
			template class fight::TrackFactoryCasterTemplate<LocoClimbTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10187F80
// FUNCTION: ENGINE 0x10187F90
// FUNCTION: ENGINE 0x10187FC0
// FUNCTION: ENGINE 0x10187FF0
// FUNCTION: ENGINE 0x10188020
// FUNCTION: ENGINE 0x10188050
// FUNCTION: ENGINE 0x10188060
// FUNCTION: ENGINE 0x10188090
// FUNCTION: ENGINE 0x101880B0
// FUNCTION: ENGINE 0x10188120
// FUNCTION: ENGINE 0x10188150
// FUNCTION: ENGINE 0x101885E0
// FUNCTION: ENGINE 0x10188610
// FUNCTION: ENGINE 0x10188630
