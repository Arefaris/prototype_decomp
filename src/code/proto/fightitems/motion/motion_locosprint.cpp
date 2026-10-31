// Fight items of the motion group: SprintVelocityClearTrack, LocoSprintTrack, LocoSprintChargeTrack (unit 0x10188680 - 0x1018AAB0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_locosprint.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gSprintVelocityClearTrackProperties;  // 0x112547B0

			// FUNCTION: ENGINE 0x10188680
			bool SprintVelocityClearTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188C40
			fight::Property* SprintVelocityClearTrack::GetProperty(int index)
			{
				return gSprintVelocityClearTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10188C60
			void SprintVelocityClearTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSprintVelocityClearTrackProperties);
			}

			// FUNCTION: ENGINE 0x10188C70
			SprintVelocityClearTrack::SprintVelocityClearTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10188CA0
			float SprintVelocityClearTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10188CB0
			float SprintVelocityClearTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10188CC0
			SprintVelocityClearTrack::~SprintVelocityClearTrack()
			{
			}

			// FUNCTION: ENGINE 0x10189780
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SprintVelocityClearTrack::RegisterProperties()
			{
				if (gSprintVelocityClearTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SprintVelocityClearTrack>("timeBegin", &SprintVelocityClearTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gSprintVelocityClearTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101896F0
			fight::TrackFactory* CreateSprintVelocityClearTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SprintVelocityClearTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10189820
			void RegisterSprintVelocityClearTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SprintVelocityClearTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gLocoSprintTrackProperties;  // 0x112547B4

			// FUNCTION: ENGINE 0x101886A0
			bool LocoSprintTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101886C0
			bool LocoSprintTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101886E0
			bool LocoSprintTrack::SetVelocityMin(float newValue)
			{
				velocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188700
			bool LocoSprintTrack::SetVelocityMid(float newValue)
			{
				velocityMid = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188720
			bool LocoSprintTrack::SetVelocityMax(float newValue)
			{
				velocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188740
			bool LocoSprintTrack::SetAccelerationMin(float newValue)
			{
				accelerationMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188760
			bool LocoSprintTrack::SetAccelerationMid(float newValue)
			{
				accelerationMid = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188780
			bool LocoSprintTrack::SetAccelerationMax(float newValue)
			{
				accelerationMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101887A0
			bool LocoSprintTrack::SetDeceleration(float newValue)
			{
				deceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101887C0
			bool LocoSprintTrack::SetTurnVelocityMin(float newValue)
			{
				turnVelocityMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101887F0
			bool LocoSprintTrack::SetTurnVelocityMax(float newValue)
			{
				turnVelocityMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10188820
			bool LocoSprintTrack::SetTurnAccelerationMin(float newValue)
			{
				turnAccelerationMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10188850
			bool LocoSprintTrack::SetTurnAccelerationMax(float newValue)
			{
				turnAccelerationMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10188880
			bool LocoSprintTrack::SetTurnDeceleration(float newValue)
			{
				turnDeceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101888A0
			bool LocoSprintTrack::SetLeanRate(float newValue)
			{
				leanRate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101888C0
			bool LocoSprintTrack::SetPhase(float newValue)
			{
				phase = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188D30
			bool LocoSprintTrack::SetLocomotion(const fight::Name& newValue)
			{
				locomotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188D50
			bool LocoSprintTrack::SetAnimMin(const fight::Name& newValue)
			{
				animMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188D70
			bool LocoSprintTrack::SetAnimMinLeanEast(const fight::Name& newValue)
			{
				animMinLeanEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188D90
			bool LocoSprintTrack::SetAnimMinLeanWest(const fight::Name& newValue)
			{
				animMinLeanWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188DB0
			bool LocoSprintTrack::SetAnimMid(const fight::Name& newValue)
			{
				animMid = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188DD0
			bool LocoSprintTrack::SetAnimMidLeanEast(const fight::Name& newValue)
			{
				animMidLeanEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188DF0
			bool LocoSprintTrack::SetAnimMidLeanWest(const fight::Name& newValue)
			{
				animMidLeanWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188E10
			bool LocoSprintTrack::SetAnimMax(const fight::Name& newValue)
			{
				animMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188E30
			bool LocoSprintTrack::SetAnimMaxLeanEast(const fight::Name& newValue)
			{
				animMaxLeanEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188E50
			bool LocoSprintTrack::SetAnimMaxLeanWest(const fight::Name& newValue)
			{
				animMaxLeanWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101888E0
			bool LocoSprintTrack::SetForceAnimationVelocities(bool newValue)
			{
				forceAnimationVelocities = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188900
			bool LocoSprintTrack::SetUnlockableVelocityMin(float newValue)
			{
				unlockableVelocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188920
			bool LocoSprintTrack::SetUnlockableFirst(int newValue)
			{
				unlockableFirst = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188940
			bool LocoSprintTrack::SetUnlockableLast(int newValue)
			{
				unlockableLast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188E70
			bool LocoSprintTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188960
			bool LocoSprintTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188980
			bool LocoSprintTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101889A0
			bool LocoSprintTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188CD0
			fight::Property* LocoSprintTrack::GetProperty(int index)
			{
				return gLocoSprintTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10188CF0
			void LocoSprintTrack::ClearProperties()
			{
				fight::FreePropertyList(&gLocoSprintTrackProperties);
			}

			// FUNCTION: ENGINE 0x10188F80
			LocoSprintTrack::LocoSprintTrack() : accelerationMax(2e+01f), accelerationMid(2e+01f), accelerationMin(2e+01f), blendInTime(0.0f), blendOutTime(0.0f), deceleration(2e+01f), leanRate(0.0f), phase(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), turnAccelerationMax(0.0f), turnAccelerationMin(0.0f), turnDeceleration(1e+01f), turnVelocityMax(0.0f), turnVelocityMin(0.0f), unlockableVelocityMin(-1.0f), velocityMax(-1.0f), velocityMid(-1.0f), velocityMin(-1.0f), priority(0), unlockableFirst(0), unlockableLast(0), forceAnimationVelocities(false)
			{
			}

			// FUNCTION: ENGINE 0x101890F0
			float LocoSprintTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10189100
			float LocoSprintTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10189110
			LocoSprintTrack::~LocoSprintTrack()
			{
			}

			// FUNCTION: ENGINE 0x101899A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void LocoSprintTrack::RegisterProperties()
			{
				if (gLocoSprintTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("timeBegin", &LocoSprintTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("timeEnd", &LocoSprintTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("velocityMin", &LocoSprintTrack::SetVelocityMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("velocityMid", &LocoSprintTrack::SetVelocityMid);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("velocityMax", &LocoSprintTrack::SetVelocityMax);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("accelerationMin", &LocoSprintTrack::SetAccelerationMin);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("accelerationMid", &LocoSprintTrack::SetAccelerationMid);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("accelerationMax", &LocoSprintTrack::SetAccelerationMax);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("deceleration", &LocoSprintTrack::SetDeceleration);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("turnVelocityMin", &LocoSprintTrack::SetTurnVelocityMin);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("turnVelocityMax", &LocoSprintTrack::SetTurnVelocityMax);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("turnAccelerationMin", &LocoSprintTrack::SetTurnAccelerationMin);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("turnAccelerationMax", &LocoSprintTrack::SetTurnAccelerationMax);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("turnDeceleration", &LocoSprintTrack::SetTurnDeceleration);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("leanRate", &LocoSprintTrack::SetLeanRate);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("phase", &LocoSprintTrack::SetPhase);
					properties[15] = property;
					property = new fight::PropertyName<LocoSprintTrack>("locomotion", &LocoSprintTrack::SetLocomotion);
					properties[16] = property;
					property = new fight::PropertyName<LocoSprintTrack>("animMin", &LocoSprintTrack::SetAnimMin);
					properties[17] = property;
					property = new fight::PropertyName<LocoSprintTrack>("animMinLeanEast", &LocoSprintTrack::SetAnimMinLeanEast);
					properties[18] = property;
					property = new fight::PropertyName<LocoSprintTrack>("animMinLeanWest", &LocoSprintTrack::SetAnimMinLeanWest);
					properties[19] = property;
					property = new fight::PropertyName<LocoSprintTrack>("animMid", &LocoSprintTrack::SetAnimMid);
					properties[20] = property;
					property = new fight::PropertyName<LocoSprintTrack>("animMidLeanEast", &LocoSprintTrack::SetAnimMidLeanEast);
					properties[21] = property;
					property = new fight::PropertyName<LocoSprintTrack>("animMidLeanWest", &LocoSprintTrack::SetAnimMidLeanWest);
					properties[22] = property;
					property = new fight::PropertyName<LocoSprintTrack>("animMax", &LocoSprintTrack::SetAnimMax);
					properties[23] = property;
					property = new fight::PropertyName<LocoSprintTrack>("animMaxLeanEast", &LocoSprintTrack::SetAnimMaxLeanEast);
					properties[24] = property;
					property = new fight::PropertyName<LocoSprintTrack>("animMaxLeanWest", &LocoSprintTrack::SetAnimMaxLeanWest);
					properties[25] = property;
					property = new fight::PropertyBool<LocoSprintTrack>("forceAnimationVelocities", &LocoSprintTrack::SetForceAnimationVelocities);
					properties[26] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("unlockableVelocityMin", &LocoSprintTrack::SetUnlockableVelocityMin);
					properties[27] = property;
					property = new fight::PropertyEnumConstList<LocoSprintTrack>("unlockableFirst", gJumpTrackUnlockableFirstTable, gJumpTrackUnlockableFirstCount, &LocoSprintTrack::SetUnlockableFirst);
					properties[28] = property;
					property = new fight::PropertyEnumConstList<LocoSprintTrack>("unlockableLast", gJumpTrackUnlockableFirstTable, gJumpTrackUnlockableFirstCount, &LocoSprintTrack::SetUnlockableLast);
					properties[29] = property;
					property = new fight::PropertyName<LocoSprintTrack>("partition", &LocoSprintTrack::SetPartition);
					properties[30] = property;
					property = new fight::PropertyIntConstRange<LocoSprintTrack>("priority", &LocoSprintTrack::SetPriority);
					properties[31] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("blendInTime", &LocoSprintTrack::SetBlendInTime);
					properties[32] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintTrack>("blendOutTime", &LocoSprintTrack::SetBlendOutTime);
					properties[33] = property;
					fight::RegisterPropertyList(properties, &gLocoSprintTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10189720
			fight::TrackFactory* CreateLocoSprintTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoSprintTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10189850
			void RegisterLocoSprintTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoSprintTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gLocoSprintChargeTrackProperties;  // 0x112547B8

			// FUNCTION: ENGINE 0x101889C0
			bool LocoSprintChargeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101889E0
			bool LocoSprintChargeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188A00
			bool LocoSprintChargeTrack::SetVelocityMin(float newValue)
			{
				velocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188A20
			bool LocoSprintChargeTrack::SetVelocityMid(float newValue)
			{
				velocityMid = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188A40
			bool LocoSprintChargeTrack::SetVelocityMax(float newValue)
			{
				velocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188A60
			bool LocoSprintChargeTrack::SetAccelerationMin(float newValue)
			{
				accelerationMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188A80
			bool LocoSprintChargeTrack::SetAccelerationMid(float newValue)
			{
				accelerationMid = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188AA0
			bool LocoSprintChargeTrack::SetAccelerationMax(float newValue)
			{
				accelerationMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188AC0
			bool LocoSprintChargeTrack::SetDeceleration(float newValue)
			{
				deceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188AE0
			bool LocoSprintChargeTrack::SetTurnVelocityMin(float newValue)
			{
				turnVelocityMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10188B00
			bool LocoSprintChargeTrack::SetTurnVelocityMax(float newValue)
			{
				turnVelocityMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10188B20
			bool LocoSprintChargeTrack::SetTurnAccelerationMin(float newValue)
			{
				turnAccelerationMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10188B40
			bool LocoSprintChargeTrack::SetTurnAccelerationMax(float newValue)
			{
				turnAccelerationMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10188B60
			bool LocoSprintChargeTrack::SetTurnDeceleration(float newValue)
			{
				turnDeceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188B80
			bool LocoSprintChargeTrack::SetLeanRate(float newValue)
			{
				leanRate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188BA0
			bool LocoSprintChargeTrack::SetPhase(float newValue)
			{
				phase = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188E90
			bool LocoSprintChargeTrack::SetLocomotion(const fight::Name& newValue)
			{
				locomotion = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188EB0
			bool LocoSprintChargeTrack::SetAnimChargeMin(const fight::Name& newValue)
			{
				animChargeMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188ED0
			bool LocoSprintChargeTrack::SetAnimChargeMax(const fight::Name& newValue)
			{
				animChargeMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188EF0
			bool LocoSprintChargeTrack::SetAnimLeanEast(const fight::Name& newValue)
			{
				animLeanEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188F10
			bool LocoSprintChargeTrack::SetAnimLeanWest(const fight::Name& newValue)
			{
				animLeanWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188BC0
			bool LocoSprintChargeTrack::SetForceAnimationVelocities(bool newValue)
			{
				forceAnimationVelocities = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188F30
			bool LocoSprintChargeTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188BE0
			bool LocoSprintChargeTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188C00
			bool LocoSprintChargeTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188C20
			bool LocoSprintChargeTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10188D00
			fight::Property* LocoSprintChargeTrack::GetProperty(int index)
			{
				return gLocoSprintChargeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10188D20
			void LocoSprintChargeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gLocoSprintChargeTrackProperties);
			}

			// FUNCTION: ENGINE 0x10189120
			LocoSprintChargeTrack::LocoSprintChargeTrack() : accelerationMax(2e+01f), accelerationMid(2e+01f), accelerationMin(2e+01f), blendInTime(0.0f), blendOutTime(0.0f), deceleration(2e+01f), leanRate(0.0f), phase(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), turnAccelerationMax(0.0f), turnAccelerationMin(0.0f), turnDeceleration(1e+01f), turnVelocityMax(0.0f), turnVelocityMin(0.0f), velocityMax(-1.0f), velocityMid(-1.0f), velocityMin(-1.0f), priority(0), forceAnimationVelocities(false)
			{
			}

			// FUNCTION: ENGINE 0x10189220
			float LocoSprintChargeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10189230
			float LocoSprintChargeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10189240
			LocoSprintChargeTrack::~LocoSprintChargeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1018A260
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void LocoSprintChargeTrack::RegisterProperties()
			{
				if (gLocoSprintChargeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("timeBegin", &LocoSprintChargeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("timeEnd", &LocoSprintChargeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("velocityMin", &LocoSprintChargeTrack::SetVelocityMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("velocityMid", &LocoSprintChargeTrack::SetVelocityMid);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("velocityMax", &LocoSprintChargeTrack::SetVelocityMax);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("accelerationMin", &LocoSprintChargeTrack::SetAccelerationMin);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("accelerationMid", &LocoSprintChargeTrack::SetAccelerationMid);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("accelerationMax", &LocoSprintChargeTrack::SetAccelerationMax);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("deceleration", &LocoSprintChargeTrack::SetDeceleration);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("turnVelocityMin", &LocoSprintChargeTrack::SetTurnVelocityMin);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("turnVelocityMax", &LocoSprintChargeTrack::SetTurnVelocityMax);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("turnAccelerationMin", &LocoSprintChargeTrack::SetTurnAccelerationMin);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("turnAccelerationMax", &LocoSprintChargeTrack::SetTurnAccelerationMax);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("turnDeceleration", &LocoSprintChargeTrack::SetTurnDeceleration);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("leanRate", &LocoSprintChargeTrack::SetLeanRate);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("phase", &LocoSprintChargeTrack::SetPhase);
					properties[15] = property;
					property = new fight::PropertyName<LocoSprintChargeTrack>("locomotion", &LocoSprintChargeTrack::SetLocomotion);
					properties[16] = property;
					property = new fight::PropertyName<LocoSprintChargeTrack>("animChargeMin", &LocoSprintChargeTrack::SetAnimChargeMin);
					properties[17] = property;
					property = new fight::PropertyName<LocoSprintChargeTrack>("animChargeMax", &LocoSprintChargeTrack::SetAnimChargeMax);
					properties[18] = property;
					property = new fight::PropertyName<LocoSprintChargeTrack>("animLeanEast", &LocoSprintChargeTrack::SetAnimLeanEast);
					properties[19] = property;
					property = new fight::PropertyName<LocoSprintChargeTrack>("animLeanWest", &LocoSprintChargeTrack::SetAnimLeanWest);
					properties[20] = property;
					property = new fight::PropertyBool<LocoSprintChargeTrack>("forceAnimationVelocities", &LocoSprintChargeTrack::SetForceAnimationVelocities);
					properties[21] = property;
					property = new fight::PropertyName<LocoSprintChargeTrack>("partition", &LocoSprintChargeTrack::SetPartition);
					properties[22] = property;
					property = new fight::PropertyIntConstRange<LocoSprintChargeTrack>("priority", &LocoSprintChargeTrack::SetPriority);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("blendInTime", &LocoSprintChargeTrack::SetBlendInTime);
					properties[24] = property;
					property = new fight::PropertyFloatConstRange<LocoSprintChargeTrack>("blendOutTime", &LocoSprintChargeTrack::SetBlendOutTime);
					properties[25] = property;
					fight::RegisterPropertyList(properties, &gLocoSprintChargeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10189750
			fight::TrackFactory* CreateLocoSprintChargeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoSprintChargeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10189880
			void RegisterLocoSprintChargeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<LocoSprintChargeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<SprintVelocityClearTrack>;
			template class fight::TrackFactoryTemplate<SprintVelocityClearTrack>;
			template class fight::TrackFactoryCasterTemplate<SprintVelocityClearTrack>;
			template class fight::PropertyFloatConstRange<LocoSprintTrack>;
			template class fight::PropertyName<LocoSprintTrack>;
			template class fight::PropertyBool<LocoSprintTrack>;
			template class fight::PropertyEnumConstList<LocoSprintTrack>;
			template class fight::PropertyIntConstRange<LocoSprintTrack>;
			template class fight::TrackFactoryTemplate<LocoSprintTrack>;
			template class fight::TrackFactoryCasterTemplate<LocoSprintTrack>;
			template class fight::PropertyFloatConstRange<LocoSprintChargeTrack>;
			template class fight::PropertyName<LocoSprintChargeTrack>;
			template class fight::PropertyBool<LocoSprintChargeTrack>;
			template class fight::PropertyIntConstRange<LocoSprintChargeTrack>;
			template class fight::TrackFactoryTemplate<LocoSprintChargeTrack>;
			template class fight::TrackFactoryCasterTemplate<LocoSprintChargeTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10188F50
// FUNCTION: ENGINE 0x10189250
// FUNCTION: ENGINE 0x10189260
// FUNCTION: ENGINE 0x10189290
// FUNCTION: ENGINE 0x101892A0
// FUNCTION: ENGINE 0x101892D0
// FUNCTION: ENGINE 0x101892E0
// FUNCTION: ENGINE 0x10189310
// FUNCTION: ENGINE 0x10189340
// FUNCTION: ENGINE 0x10189370
// FUNCTION: ENGINE 0x101893A0
// FUNCTION: ENGINE 0x101893D0
// FUNCTION: ENGINE 0x101893E0
// FUNCTION: ENGINE 0x10189410
// FUNCTION: ENGINE 0x10189440
// FUNCTION: ENGINE 0x10189450
// FUNCTION: ENGINE 0x10189480
// FUNCTION: ENGINE 0x101894A0
// FUNCTION: ENGINE 0x101894B0
// FUNCTION: ENGINE 0x101894F0
// FUNCTION: ENGINE 0x10189500
// FUNCTION: ENGINE 0x10189530
// FUNCTION: ENGINE 0x10189550
// FUNCTION: ENGINE 0x10189560
// FUNCTION: ENGINE 0x10189590
// FUNCTION: ENGINE 0x101895B0
// FUNCTION: ENGINE 0x101895C0
// FUNCTION: ENGINE 0x101895F0
// FUNCTION: ENGINE 0x10189620
// FUNCTION: ENGINE 0x10189630
// FUNCTION: ENGINE 0x10189660
// FUNCTION: ENGINE 0x10189680
// FUNCTION: ENGINE 0x10189690
// FUNCTION: ENGINE 0x101896C0
// FUNCTION: ENGINE 0x101896E0
// FUNCTION: ENGINE 0x101898B0
// FUNCTION: ENGINE 0x101898E0
// FUNCTION: ENGINE 0x10189900
// FUNCTION: ENGINE 0x10189930
// FUNCTION: ENGINE 0x10189950
// FUNCTION: ENGINE 0x10189980
// FUNCTION: ENGINE 0x1018A900
// FUNCTION: ENGINE 0x1018A950
// FUNCTION: ENGINE 0x1018A980
// FUNCTION: ENGINE 0x1018A9B0
// FUNCTION: ENGINE 0x1018A9E0
// FUNCTION: ENGINE 0x1018AA10
// FUNCTION: ENGINE 0x1018AA60
