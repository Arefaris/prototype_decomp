// Fight items of the motion group: LocoSteerTrack, LocoSteerLeanTrack (unit 0x1018AAB0 - 0x1018C680; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_locosteer.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gLocoSteerTrackProperties;  // 0x112547C0

			// FUNCTION: ENGINE 0x1018AAB0
			bool LocoSteerTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AAD0
			bool LocoSteerTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AAF0
			bool LocoSteerTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AB10
			bool LocoSteerTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AB30
			bool LocoSteerTrack::SetVelocityWalk(float newValue)
			{
				velocityWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AB50
			bool LocoSteerTrack::SetVelocityRun(float newValue)
			{
				velocityRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AB70
			bool LocoSteerTrack::SetSmoothSteeringAngle(float newValue)
			{
				smoothSteeringAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AB90
			bool LocoSteerTrack::SetUseWorldCoordinates(bool newValue)
			{
				useWorldCoordinates = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018ABA0
			bool LocoSteerTrack::SetPhase(float newValue)
			{
				phase = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AF80
			bool LocoSteerTrack::SetLocomotion(const fight::Name& newValue)
			{
				locomotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AFA0
			bool LocoSteerTrack::SetAnimIdle(const fight::Name& newValue)
			{
				animIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AFC0
			bool LocoSteerTrack::SetAnimWalk(const fight::Name& newValue)
			{
				animWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AFE0
			bool LocoSteerTrack::SetAnimRun(const fight::Name& newValue)
			{
				animRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018ABC0
			bool LocoSteerTrack::SetSyncFrameIdle(float newValue)
			{
				syncFrameIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018ABE0
			bool LocoSteerTrack::SetSyncFrameWalk(float newValue)
			{
				syncFrameWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AC00
			bool LocoSteerTrack::SetSyncFrameRun(float newValue)
			{
				syncFrameRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018B000
			bool LocoSteerTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AC20
			bool LocoSteerTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AC30
			bool LocoSteerTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AC50
			bool LocoSteerTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AF20
			fight::Property* LocoSteerTrack::GetProperty(int index)
			{
				return gLocoSteerTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1018AF40
			void LocoSteerTrack::ClearProperties()
			{
				fight::FreePropertyList(&gLocoSteerTrackProperties);
			}

			// FUNCTION: ENGINE 0x1018B140
			LocoSteerTrack::LocoSteerTrack() : acceleration(5e+01f), blendInTime(0.0f), blendOutTime(0.0f), phase(-1.0f), smoothSteeringAngle(0.0f), syncFrameIdle(-1.0f), syncFrameRun(-1.0f), syncFrameWalk(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(6.2831855f), velocityRun(-1.0f), velocityWalk(-1.0f), priority(0), useWorldCoordinates(false)
			{
			}

			// FUNCTION: ENGINE 0x1018B210
			float LocoSteerTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1018B220
			float LocoSteerTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1018B230
			LocoSteerTrack::~LocoSteerTrack()
			{
			}

			// FUNCTION: ENGINE 0x1018B870
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void LocoSteerTrack::RegisterProperties()
			{
				if (gLocoSteerTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<LocoSteerTrack>("timeBegin", &LocoSteerTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerTrack>("timeEnd", &LocoSteerTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerTrack>("acceleration", &LocoSteerTrack::SetAcceleration);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerTrack>("turningVelocity", &LocoSteerTrack::SetTurningVelocity);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerTrack>("velocityWalk", &LocoSteerTrack::SetVelocityWalk);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerTrack>("velocityRun", &LocoSteerTrack::SetVelocityRun);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerTrack>("smoothSteeringAngle", &LocoSteerTrack::SetSmoothSteeringAngle);
					properties[6] = property;
					property = new fight::PropertyBool<LocoSteerTrack>("useWorldCoordinates", &LocoSteerTrack::SetUseWorldCoordinates);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerTrack>("phase", &LocoSteerTrack::SetPhase);
					properties[8] = property;
					property = new fight::PropertyName<LocoSteerTrack>("locomotion", &LocoSteerTrack::SetLocomotion);
					properties[9] = property;
					property = new fight::PropertyName<LocoSteerTrack>("animIdle", &LocoSteerTrack::SetAnimIdle);
					properties[10] = property;
					property = new fight::PropertyName<LocoSteerTrack>("animWalk", &LocoSteerTrack::SetAnimWalk);
					properties[11] = property;
					property = new fight::PropertyName<LocoSteerTrack>("animRun", &LocoSteerTrack::SetAnimRun);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerTrack>("syncFrameIdle", &LocoSteerTrack::SetSyncFrameIdle);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerTrack>("syncFrameWalk", &LocoSteerTrack::SetSyncFrameWalk);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerTrack>("syncFrameRun", &LocoSteerTrack::SetSyncFrameRun);
					properties[15] = property;
					property = new fight::PropertyName<LocoSteerTrack>("partition", &LocoSteerTrack::SetPartition);
					properties[16] = property;
					property = new fight::PropertyIntConstRange<LocoSteerTrack>("priority", &LocoSteerTrack::SetPriority);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerTrack>("blendInTime", &LocoSteerTrack::SetBlendInTime);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerTrack>("blendOutTime", &LocoSteerTrack::SetBlendOutTime);
					properties[19] = property;
					fight::RegisterPropertyList(properties, &gLocoSteerTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1018B710
			fight::TrackFactory* CreateLocoSteerTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoSteerTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1018B770
			void RegisterLocoSteerTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoSteerTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gLocoSteerLeanTrackProperties;  // 0x112547C4

			// FUNCTION: ENGINE 0x1018AC70
			bool LocoSteerLeanTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AC90
			bool LocoSteerLeanTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018ACB0
			bool LocoSteerLeanTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018ACD0
			bool LocoSteerLeanTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AD00
			bool LocoSteerLeanTrack::SetVelocityWalk(float newValue)
			{
				velocityWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AD20
			bool LocoSteerLeanTrack::SetVelocityRun(float newValue)
			{
				velocityRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AD40
			bool LocoSteerLeanTrack::SetLeanAngleThreshold(float newValue)
			{
				leanAngleThreshold = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AD60
			bool LocoSteerLeanTrack::SetLeanRateIn(float newValue)
			{
				leanRateIn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AD80
			bool LocoSteerLeanTrack::SetLeanRateOut(float newValue)
			{
				leanRateOut = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018ADA0
			bool LocoSteerLeanTrack::SetUseWorldCoordinates(bool newValue)
			{
				useWorldCoordinates = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018ADC0
			bool LocoSteerLeanTrack::SetPhase(float newValue)
			{
				phase = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018B020
			bool LocoSteerLeanTrack::SetLocomotion(const fight::Name& newValue)
			{
				locomotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018B040
			bool LocoSteerLeanTrack::SetAnimIdle(const fight::Name& newValue)
			{
				animIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018B060
			bool LocoSteerLeanTrack::SetAnimWalk(const fight::Name& newValue)
			{
				animWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018B080
			bool LocoSteerLeanTrack::SetAnimWalkLeanEast(const fight::Name& newValue)
			{
				animWalkLeanEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018B0A0
			bool LocoSteerLeanTrack::SetAnimWalkLeanWest(const fight::Name& newValue)
			{
				animWalkLeanWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018B0C0
			bool LocoSteerLeanTrack::SetAnimRun(const fight::Name& newValue)
			{
				animRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018B0E0
			bool LocoSteerLeanTrack::SetAnimRunLeanEast(const fight::Name& newValue)
			{
				animRunLeanEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018B100
			bool LocoSteerLeanTrack::SetAnimRunLeanWest(const fight::Name& newValue)
			{
				animRunLeanWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018ADE0
			bool LocoSteerLeanTrack::SetSyncFrameIdle(float newValue)
			{
				syncFrameIdle = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AE00
			bool LocoSteerLeanTrack::SetSyncFrameWalk(float newValue)
			{
				syncFrameWalk = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AE20
			bool LocoSteerLeanTrack::SetSyncFrameWalkLeanEast(float newValue)
			{
				syncFrameWalkLeanEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AE40
			bool LocoSteerLeanTrack::SetSyncFrameWalkLeanWest(float newValue)
			{
				syncFrameWalkLeanWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AE60
			bool LocoSteerLeanTrack::SetSyncFrameRun(float newValue)
			{
				syncFrameRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AE80
			bool LocoSteerLeanTrack::SetSyncFrameRunLeanEast(float newValue)
			{
				syncFrameRunLeanEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AEA0
			bool LocoSteerLeanTrack::SetSyncFrameRunLeanWest(float newValue)
			{
				syncFrameRunLeanWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018B120
			bool LocoSteerLeanTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AEC0
			bool LocoSteerLeanTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AEE0
			bool LocoSteerLeanTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AF00
			bool LocoSteerLeanTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1018AF50
			fight::Property* LocoSteerLeanTrack::GetProperty(int index)
			{
				return gLocoSteerLeanTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1018AF70
			void LocoSteerLeanTrack::ClearProperties()
			{
				fight::FreePropertyList(&gLocoSteerLeanTrackProperties);
			}

			// FUNCTION: ENGINE 0x1018B240
			LocoSteerLeanTrack::LocoSteerLeanTrack() : acceleration(5e+01f), blendInTime(0.0f), blendOutTime(0.0f), leanAngleThreshold(0.5235988f), leanRateIn(1e+01f), leanRateOut(1.0f), phase(-1.0f), syncFrameIdle(-1.0f), syncFrameRun(-1.0f), syncFrameRunLeanEast(-1.0f), syncFrameRunLeanWest(-1.0f), syncFrameWalk(-1.0f), syncFrameWalkLeanEast(-1.0f), syncFrameWalkLeanWest(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(6.2831855f), velocityRun(-1.0f), velocityWalk(-1.0f), priority(0), useWorldCoordinates(false)
			{
			}

			// FUNCTION: ENGINE 0x1018B3A0
			float LocoSteerLeanTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1018B3B0
			float LocoSteerLeanTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1018B3C0
			LocoSteerLeanTrack::~LocoSteerLeanTrack()
			{
			}

			// FUNCTION: ENGINE 0x1018BDA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void LocoSteerLeanTrack::RegisterProperties()
			{
				if (gLocoSteerLeanTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("timeBegin", &LocoSteerLeanTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("timeEnd", &LocoSteerLeanTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("acceleration", &LocoSteerLeanTrack::SetAcceleration);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("turningVelocity", &LocoSteerLeanTrack::SetTurningVelocity);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("velocityWalk", &LocoSteerLeanTrack::SetVelocityWalk);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("velocityRun", &LocoSteerLeanTrack::SetVelocityRun);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("leanAngleThreshold", &LocoSteerLeanTrack::SetLeanAngleThreshold);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("leanRateIn", &LocoSteerLeanTrack::SetLeanRateIn);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("leanRateOut", &LocoSteerLeanTrack::SetLeanRateOut);
					properties[8] = property;
					property = new fight::PropertyBool<LocoSteerLeanTrack>("useWorldCoordinates", &LocoSteerLeanTrack::SetUseWorldCoordinates);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("phase", &LocoSteerLeanTrack::SetPhase);
					properties[10] = property;
					property = new fight::PropertyName<LocoSteerLeanTrack>("locomotion", &LocoSteerLeanTrack::SetLocomotion);
					properties[11] = property;
					property = new fight::PropertyName<LocoSteerLeanTrack>("animIdle", &LocoSteerLeanTrack::SetAnimIdle);
					properties[12] = property;
					property = new fight::PropertyName<LocoSteerLeanTrack>("animWalk", &LocoSteerLeanTrack::SetAnimWalk);
					properties[13] = property;
					property = new fight::PropertyName<LocoSteerLeanTrack>("animWalkLeanEast", &LocoSteerLeanTrack::SetAnimWalkLeanEast);
					properties[14] = property;
					property = new fight::PropertyName<LocoSteerLeanTrack>("animWalkLeanWest", &LocoSteerLeanTrack::SetAnimWalkLeanWest);
					properties[15] = property;
					property = new fight::PropertyName<LocoSteerLeanTrack>("animRun", &LocoSteerLeanTrack::SetAnimRun);
					properties[16] = property;
					property = new fight::PropertyName<LocoSteerLeanTrack>("animRunLeanEast", &LocoSteerLeanTrack::SetAnimRunLeanEast);
					properties[17] = property;
					property = new fight::PropertyName<LocoSteerLeanTrack>("animRunLeanWest", &LocoSteerLeanTrack::SetAnimRunLeanWest);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("syncFrameIdle", &LocoSteerLeanTrack::SetSyncFrameIdle);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("syncFrameWalk", &LocoSteerLeanTrack::SetSyncFrameWalk);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("syncFrameWalkLeanEast", &LocoSteerLeanTrack::SetSyncFrameWalkLeanEast);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("syncFrameWalkLeanWest", &LocoSteerLeanTrack::SetSyncFrameWalkLeanWest);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("syncFrameRun", &LocoSteerLeanTrack::SetSyncFrameRun);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("syncFrameRunLeanEast", &LocoSteerLeanTrack::SetSyncFrameRunLeanEast);
					properties[24] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("syncFrameRunLeanWest", &LocoSteerLeanTrack::SetSyncFrameRunLeanWest);
					properties[25] = property;
					property = new fight::PropertyName<LocoSteerLeanTrack>("partition", &LocoSteerLeanTrack::SetPartition);
					properties[26] = property;
					property = new fight::PropertyIntConstRange<LocoSteerLeanTrack>("priority", &LocoSteerLeanTrack::SetPriority);
					properties[27] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("blendInTime", &LocoSteerLeanTrack::SetBlendInTime);
					properties[28] = property;
					property = new fight::PropertyFloatConstRange<LocoSteerLeanTrack>("blendOutTime", &LocoSteerLeanTrack::SetBlendOutTime);
					properties[29] = property;
					fight::RegisterPropertyList(properties, &gLocoSteerLeanTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1018B740
			fight::TrackFactory* CreateLocoSteerLeanTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoSteerLeanTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1018B7A0
			void RegisterLocoSteerLeanTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoSteerLeanTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<LocoSteerTrack>;
			template class fight::PropertyBool<LocoSteerTrack>;
			template class fight::PropertyName<LocoSteerTrack>;
			template class fight::PropertyIntConstRange<LocoSteerTrack>;
			template class fight::TrackFactoryTemplate<LocoSteerTrack>;
			template class fight::TrackFactoryCasterTemplate<LocoSteerTrack>;
			template class fight::PropertyFloatConstRange<LocoSteerLeanTrack>;
			template class fight::PropertyBool<LocoSteerLeanTrack>;
			template class fight::PropertyName<LocoSteerLeanTrack>;
			template class fight::PropertyIntConstRange<LocoSteerLeanTrack>;
			template class fight::TrackFactoryTemplate<LocoSteerLeanTrack>;
			template class fight::TrackFactoryCasterTemplate<LocoSteerLeanTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1018B3D0
// FUNCTION: ENGINE 0x1018B3E0
// FUNCTION: ENGINE 0x1018B410
// FUNCTION: ENGINE 0x1018B420
// FUNCTION: ENGINE 0x1018B450
// FUNCTION: ENGINE 0x1018B480
// FUNCTION: ENGINE 0x1018B4B0
// FUNCTION: ENGINE 0x1018B4E0
// FUNCTION: ENGINE 0x1018B510
// FUNCTION: ENGINE 0x1018B520
// FUNCTION: ENGINE 0x1018B550
// FUNCTION: ENGINE 0x1018B570
// FUNCTION: ENGINE 0x1018B580
// FUNCTION: ENGINE 0x1018B5B0
// FUNCTION: ENGINE 0x1018B5D0
// FUNCTION: ENGINE 0x1018B5E0
// FUNCTION: ENGINE 0x1018B610
// FUNCTION: ENGINE 0x1018B640
// FUNCTION: ENGINE 0x1018B650
// FUNCTION: ENGINE 0x1018B680
// FUNCTION: ENGINE 0x1018B6A0
// FUNCTION: ENGINE 0x1018B6B0
// FUNCTION: ENGINE 0x1018B6E0
// FUNCTION: ENGINE 0x1018B700
// FUNCTION: ENGINE 0x1018B7D0
// FUNCTION: ENGINE 0x1018B800
// FUNCTION: ENGINE 0x1018B820
// FUNCTION: ENGINE 0x1018B850
// FUNCTION: ENGINE 0x1018C530
// FUNCTION: ENGINE 0x1018C560
// FUNCTION: ENGINE 0x1018C580
// FUNCTION: ENGINE 0x1018C5B0
// FUNCTION: ENGINE 0x1018C5E0
// FUNCTION: ENGINE 0x1018C630
