// Fight items of the motion group: LocoStrafeTrack (unit 0x1018C680 - 0x1018D500; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_locostrafe.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gLocoStrafeTrackProperties;  // 0x112547CC

			// FUNCTION: ENGINE 0x1018C680
			bool LocoStrafeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C6A0
			bool LocoStrafeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C6C0
			bool LocoStrafeTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C6E0
			bool LocoStrafeTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C710
			bool LocoStrafeTrack::SetFixedFacing(bool newValue)
			{
				fixedFacing = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C730
			bool LocoStrafeTrack::SetVelocityWalkNorth(float newValue)
			{
				velocityWalkNorth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C750
			bool LocoStrafeTrack::SetVelocityWalkStrafe(float newValue)
			{
				velocityWalkStrafe = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C770
			bool LocoStrafeTrack::SetVelocityWalkSouth(float newValue)
			{
				velocityWalkSouth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C790
			bool LocoStrafeTrack::SetVelocityRunNorth(float newValue)
			{
				velocityRunNorth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C7B0
			bool LocoStrafeTrack::SetVelocityRunStrafe(float newValue)
			{
				velocityRunStrafe = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C7D0
			bool LocoStrafeTrack::SetVelocityRunSouth(float newValue)
			{
				velocityRunSouth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C7F0
			bool LocoStrafeTrack::SetPhase(float newValue)
			{
				phase = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C8A0
			bool LocoStrafeTrack::SetLocomotion(const fight::Name& newValue)
			{
				locomotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C8C0
			bool LocoStrafeTrack::SetAnimIdle(const fight::Name& newValue)
			{
				animIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C8E0
			bool LocoStrafeTrack::SetAnimWalkNorth(const fight::Name& newValue)
			{
				animWalkNorth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C900
			bool LocoStrafeTrack::SetAnimWalkEast(const fight::Name& newValue)
			{
				animWalkEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C920
			bool LocoStrafeTrack::SetAnimWalkSouth(const fight::Name& newValue)
			{
				animWalkSouth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C940
			bool LocoStrafeTrack::SetAnimWalkWest(const fight::Name& newValue)
			{
				animWalkWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C960
			bool LocoStrafeTrack::SetAnimRunNorth(const fight::Name& newValue)
			{
				animRunNorth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C980
			bool LocoStrafeTrack::SetAnimRunEast(const fight::Name& newValue)
			{
				animRunEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C9A0
			bool LocoStrafeTrack::SetAnimRunSouth(const fight::Name& newValue)
			{
				animRunSouth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C9C0
			bool LocoStrafeTrack::SetAnimRunWest(const fight::Name& newValue)
			{
				animRunWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C9E0
			bool LocoStrafeTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C810
			bool LocoStrafeTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C830
			bool LocoStrafeTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C850
			bool LocoStrafeTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018C870
			fight::Property* LocoStrafeTrack::GetProperty(int index)
			{
				return gLocoStrafeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1018C890
			void LocoStrafeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gLocoStrafeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1018CA00
			LocoStrafeTrack::LocoStrafeTrack() : acceleration(5e+01f), blendInTime(0.1f), blendOutTime(0.1f), phase(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(6.2831855f), velocityRunNorth(-1.0f), velocityRunSouth(-1.0f), velocityRunStrafe(-1.0f), velocityWalkNorth(-1.0f), velocityWalkSouth(-1.0f), velocityWalkStrafe(-1.0f), priority(0), fixedFacing(false)
			{
			}

			// FUNCTION: ENGINE 0x1018CB30
			float LocoStrafeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1018CB40
			float LocoStrafeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1018CB50
			LocoStrafeTrack::~LocoStrafeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1018CDB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void LocoStrafeTrack::RegisterProperties()
			{
				if (gLocoStrafeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<LocoStrafeTrack>("timeBegin", &LocoStrafeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<LocoStrafeTrack>("timeEnd", &LocoStrafeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<LocoStrafeTrack>("acceleration", &LocoStrafeTrack::SetAcceleration);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<LocoStrafeTrack>("turningVelocity", &LocoStrafeTrack::SetTurningVelocity);
					properties[3] = property;
					property = new fight::PropertyBool<LocoStrafeTrack>("fixedFacing", &LocoStrafeTrack::SetFixedFacing);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<LocoStrafeTrack>("velocityWalkNorth", &LocoStrafeTrack::SetVelocityWalkNorth);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<LocoStrafeTrack>("velocityWalkStrafe", &LocoStrafeTrack::SetVelocityWalkStrafe);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<LocoStrafeTrack>("velocityWalkSouth", &LocoStrafeTrack::SetVelocityWalkSouth);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<LocoStrafeTrack>("velocityRunNorth", &LocoStrafeTrack::SetVelocityRunNorth);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<LocoStrafeTrack>("velocityRunStrafe", &LocoStrafeTrack::SetVelocityRunStrafe);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<LocoStrafeTrack>("velocityRunSouth", &LocoStrafeTrack::SetVelocityRunSouth);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<LocoStrafeTrack>("phase", &LocoStrafeTrack::SetPhase);
					properties[11] = property;
					property = new fight::PropertyName<LocoStrafeTrack>("locomotion", &LocoStrafeTrack::SetLocomotion);
					properties[12] = property;
					property = new fight::PropertyName<LocoStrafeTrack>("animIdle", &LocoStrafeTrack::SetAnimIdle);
					properties[13] = property;
					property = new fight::PropertyName<LocoStrafeTrack>("animWalkNorth", &LocoStrafeTrack::SetAnimWalkNorth);
					properties[14] = property;
					property = new fight::PropertyName<LocoStrafeTrack>("animWalkEast", &LocoStrafeTrack::SetAnimWalkEast);
					properties[15] = property;
					property = new fight::PropertyName<LocoStrafeTrack>("animWalkSouth", &LocoStrafeTrack::SetAnimWalkSouth);
					properties[16] = property;
					property = new fight::PropertyName<LocoStrafeTrack>("animWalkWest", &LocoStrafeTrack::SetAnimWalkWest);
					properties[17] = property;
					property = new fight::PropertyName<LocoStrafeTrack>("animRunNorth", &LocoStrafeTrack::SetAnimRunNorth);
					properties[18] = property;
					property = new fight::PropertyName<LocoStrafeTrack>("animRunEast", &LocoStrafeTrack::SetAnimRunEast);
					properties[19] = property;
					property = new fight::PropertyName<LocoStrafeTrack>("animRunSouth", &LocoStrafeTrack::SetAnimRunSouth);
					properties[20] = property;
					property = new fight::PropertyName<LocoStrafeTrack>("animRunWest", &LocoStrafeTrack::SetAnimRunWest);
					properties[21] = property;
					property = new fight::PropertyName<LocoStrafeTrack>("partition", &LocoStrafeTrack::SetPartition);
					properties[22] = property;
					property = new fight::PropertyIntConstRange<LocoStrafeTrack>("priority", &LocoStrafeTrack::SetPriority);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<LocoStrafeTrack>("blendInTime", &LocoStrafeTrack::SetBlendInTime);
					properties[24] = property;
					property = new fight::PropertyFloatConstRange<LocoStrafeTrack>("blendOutTime", &LocoStrafeTrack::SetBlendOutTime);
					properties[25] = property;
					fight::RegisterPropertyList(properties, &gLocoStrafeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1018CD00
			fight::TrackFactory* CreateLocoStrafeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoStrafeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1018CD30
			void RegisterLocoStrafeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoStrafeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<LocoStrafeTrack>;
			template class fight::PropertyBool<LocoStrafeTrack>;
			template class fight::PropertyName<LocoStrafeTrack>;
			template class fight::PropertyIntConstRange<LocoStrafeTrack>;
			template class fight::TrackFactoryTemplate<LocoStrafeTrack>;
			template class fight::TrackFactoryCasterTemplate<LocoStrafeTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1018CB60
// FUNCTION: ENGINE 0x1018CB70
// FUNCTION: ENGINE 0x1018CBA0
// FUNCTION: ENGINE 0x1018CBD0
// FUNCTION: ENGINE 0x1018CC00
// FUNCTION: ENGINE 0x1018CC30
// FUNCTION: ENGINE 0x1018CC40
// FUNCTION: ENGINE 0x1018CC70
// FUNCTION: ENGINE 0x1018CC90
// FUNCTION: ENGINE 0x1018CCA0
// FUNCTION: ENGINE 0x1018CCD0
// FUNCTION: ENGINE 0x1018CCF0
// FUNCTION: ENGINE 0x1018CD60
// FUNCTION: ENGINE 0x1018CD90
// FUNCTION: ENGINE 0x1018D450
// FUNCTION: ENGINE 0x1018D480
// FUNCTION: ENGINE 0x1018D4B0
