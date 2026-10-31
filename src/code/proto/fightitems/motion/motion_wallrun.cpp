// Fight items of the motion group: WallRunTrack, WallOrientTrack, WallRunEnterTrack (unit 0x101CE030 - 0x101D0240; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_wallrun.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gWallRunTrackProperties;  // 0x11254CAC

			// FUNCTION: ENGINE 0x101CE030
			bool WallRunTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE050
			bool WallRunTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE070
			bool WallRunTrack::SetVelocityMin(float newValue)
			{
				velocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE090
			bool WallRunTrack::SetVelocityMax(float newValue)
			{
				velocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE0B0
			bool WallRunTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE0D0
			bool WallRunTrack::SetGravity(float newValue)
			{
				gravity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE0F0
			bool WallRunTrack::SetTurningRate(float newValue)
			{
				turningRate = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE120
			bool WallRunTrack::SetSurfaceAngleThreshold(float newValue)
			{
				surfaceAngleThreshold = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE860
			bool WallRunTrack::SetAnimUp(const fight::Name& newValue)
			{
				animUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE880
			bool WallRunTrack::SetAnimLeft(const fight::Name& newValue)
			{
				animLeft = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE8A0
			bool WallRunTrack::SetAnimRight(const fight::Name& newValue)
			{
				animRight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE8C0
			bool WallRunTrack::SetAnimUpLeft(const fight::Name& newValue)
			{
				animUpLeft = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE8E0
			bool WallRunTrack::SetAnimUpRight(const fight::Name& newValue)
			{
				animUpRight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE900
			bool WallRunTrack::SetAnimDownLeft(const fight::Name& newValue)
			{
				animDownLeft = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE920
			bool WallRunTrack::SetAnimDownRight(const fight::Name& newValue)
			{
				animDownRight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE140
			bool WallRunTrack::SetForceAnimationVelocities(bool newValue)
			{
				forceAnimationVelocities = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE160
			bool WallRunTrack::SetSyncFrameUp(float newValue)
			{
				syncFrameUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE180
			bool WallRunTrack::SetSyncFrameLeft(float newValue)
			{
				syncFrameLeft = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE1A0
			bool WallRunTrack::SetSyncFrameRight(float newValue)
			{
				syncFrameRight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE1C0
			bool WallRunTrack::SetSyncFrameUpLeft(float newValue)
			{
				syncFrameUpLeft = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE1E0
			bool WallRunTrack::SetSyncFrameUpRight(float newValue)
			{
				syncFrameUpRight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE200
			bool WallRunTrack::SetSyncFrameDownLeft(float newValue)
			{
				syncFrameDownLeft = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE220
			bool WallRunTrack::SetSyncFrameDownRight(float newValue)
			{
				syncFrameDownRight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE240
			bool WallRunTrack::SetUnlockableVelocityMin(float newValue)
			{
				unlockableVelocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE260
			bool WallRunTrack::SetUnlockableFirst(int newValue)
			{
				unlockableFirst = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE280
			bool WallRunTrack::SetUnlockableLast(int newValue)
			{
				unlockableLast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE2A0
			bool WallRunTrack::SetSprintVelocityDropRate(float newValue)
			{
				sprintVelocityDropRate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE2C0
			bool WallRunTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE2E0
			bool WallRunTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE300
			bool WallRunTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE610
			fight::Property* WallRunTrack::GetProperty(int index)
			{
				return gWallRunTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101CE630
			void WallRunTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWallRunTrackProperties);
			}

			// FUNCTION: ENGINE 0x101CE940
			WallRunTrack::WallRunTrack() : acceleration(1.0f), blendInTime(0.0f), blendOutTime(0.0f), gravity(2e+01f), sprintVelocityDropRate(0.0f), surfaceAngleThreshold(1.5707964f), syncFrameDownLeft(-1.0f), syncFrameDownRight(-1.0f), syncFrameLeft(-1.0f), syncFrameRight(-1.0f), syncFrameUp(-1.0f), syncFrameUpLeft(-1.0f), syncFrameUpRight(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), turningRate(1.5707964f), unlockableVelocityMin(-1.0f), velocityMax(1e+02f), velocityMin(1.0f), priority(0), unlockableFirst(0), unlockableLast(0), forceAnimationVelocities(false)
			{
			}

			// FUNCTION: ENGINE 0x101CEA80
			float WallRunTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101CEA90
			float WallRunTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101CEAA0
			WallRunTrack::~WallRunTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CF930
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WallRunTrack::RegisterProperties()
			{
				if (gWallRunTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("timeBegin", &WallRunTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("timeEnd", &WallRunTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("velocityMin", &WallRunTrack::SetVelocityMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("velocityMax", &WallRunTrack::SetVelocityMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("acceleration", &WallRunTrack::SetAcceleration);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("gravity", &WallRunTrack::SetGravity);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("turningRate", &WallRunTrack::SetTurningRate);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("surfaceAngleThreshold", &WallRunTrack::SetSurfaceAngleThreshold);
					properties[7] = property;
					property = new fight::PropertyName<WallRunTrack>("animUp", &WallRunTrack::SetAnimUp);
					properties[8] = property;
					property = new fight::PropertyName<WallRunTrack>("animLeft", &WallRunTrack::SetAnimLeft);
					properties[9] = property;
					property = new fight::PropertyName<WallRunTrack>("animRight", &WallRunTrack::SetAnimRight);
					properties[10] = property;
					property = new fight::PropertyName<WallRunTrack>("animUpLeft", &WallRunTrack::SetAnimUpLeft);
					properties[11] = property;
					property = new fight::PropertyName<WallRunTrack>("animUpRight", &WallRunTrack::SetAnimUpRight);
					properties[12] = property;
					property = new fight::PropertyName<WallRunTrack>("animDownLeft", &WallRunTrack::SetAnimDownLeft);
					properties[13] = property;
					property = new fight::PropertyName<WallRunTrack>("animDownRight", &WallRunTrack::SetAnimDownRight);
					properties[14] = property;
					property = new fight::PropertyBool<WallRunTrack>("forceAnimationVelocities", &WallRunTrack::SetForceAnimationVelocities);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("syncFrameUp", &WallRunTrack::SetSyncFrameUp);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("syncFrameLeft", &WallRunTrack::SetSyncFrameLeft);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("syncFrameRight", &WallRunTrack::SetSyncFrameRight);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("syncFrameUpLeft", &WallRunTrack::SetSyncFrameUpLeft);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("syncFrameUpRight", &WallRunTrack::SetSyncFrameUpRight);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("syncFrameDownLeft", &WallRunTrack::SetSyncFrameDownLeft);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("syncFrameDownRight", &WallRunTrack::SetSyncFrameDownRight);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("unlockableVelocityMin", &WallRunTrack::SetUnlockableVelocityMin);
					properties[23] = property;
					property = new fight::PropertyEnumConstList<WallRunTrack>("unlockableFirst", gJumpTrackUnlockableFirstTable, gJumpTrackUnlockableFirstCount, &WallRunTrack::SetUnlockableFirst);
					properties[24] = property;
					property = new fight::PropertyEnumConstList<WallRunTrack>("unlockableLast", gJumpTrackUnlockableFirstTable, gJumpTrackUnlockableFirstCount, &WallRunTrack::SetUnlockableLast);
					properties[25] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("sprintVelocityDropRate", &WallRunTrack::SetSprintVelocityDropRate);
					properties[26] = property;
					property = new fight::PropertyIntConstRange<WallRunTrack>("priority", &WallRunTrack::SetPriority);
					properties[27] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("blendInTime", &WallRunTrack::SetBlendInTime);
					properties[28] = property;
					property = new fight::PropertyFloatConstRange<WallRunTrack>("blendOutTime", &WallRunTrack::SetBlendOutTime);
					properties[29] = property;
					fight::RegisterPropertyList(properties, &gWallRunTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101CF020
			fight::TrackFactory* CreateWallRunTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallRunTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CF7B0
			void RegisterWallRunTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallRunTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gWallOrientTrackProperties;  // 0x11254CB0

			// FUNCTION: ENGINE 0x101CE320
			bool WallOrientTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE340
			bool WallOrientTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE360
			bool WallOrientTrack::SetOrientOffset(float newValue)
			{
				orientOffset = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE380
			bool WallOrientTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE3A0
			bool WallOrientTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE3B0
			bool WallOrientTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE3D0
			bool WallOrientTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE640
			fight::Property* WallOrientTrack::GetProperty(int index)
			{
				return gWallOrientTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101CE660
			void WallOrientTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWallOrientTrackProperties);
			}

			// FUNCTION: ENGINE 0x101CE670
			WallOrientTrack::WallOrientTrack() : blendInTime(0.0f), blendOutTime(0.0f), orientOffset(0.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(0.0f), priority(-7)
			{
			}

			// FUNCTION: ENGINE 0x101CE6D0
			float WallOrientTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101CE6E0
			float WallOrientTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101CE6F0
			WallOrientTrack::~WallOrientTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CF0B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WallOrientTrack::RegisterProperties()
			{
				if (gWallOrientTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WallOrientTrack>("timeBegin", &WallOrientTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WallOrientTrack>("timeEnd", &WallOrientTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<WallOrientTrack>("orientOffset", &WallOrientTrack::SetOrientOffset);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<WallOrientTrack>("turningVelocity", &WallOrientTrack::SetTurningVelocity);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<WallOrientTrack>("priority", &WallOrientTrack::SetPriority);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<WallOrientTrack>("blendInTime", &WallOrientTrack::SetBlendInTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<WallOrientTrack>("blendOutTime", &WallOrientTrack::SetBlendOutTime);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gWallOrientTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101CF050
			fight::TrackFactory* CreateWallOrientTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallOrientTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CF7E0
			void RegisterWallOrientTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallOrientTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gWallRunEnterTrackProperties;  // 0x11254CB4

			// FUNCTION: ENGINE 0x101CE3F0
			bool WallRunEnterTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE410
			bool WallRunEnterTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE430
			bool WallRunEnterTrack::SetTimeCancel(float newValue)
			{
				timeCancel = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE450
			bool WallRunEnterTrack::SetVelocityXZMin(float newValue)
			{
				velocityXZMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE470
			bool WallRunEnterTrack::SetVelocityXZMax(float newValue)
			{
				velocityXZMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE490
			bool WallRunEnterTrack::SetVelocityUpMin(float newValue)
			{
				velocityUpMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE4B0
			bool WallRunEnterTrack::SetVelocityUpMax(float newValue)
			{
				velocityUpMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE4D0
			bool WallRunEnterTrack::SetTurningVelocityMin(float newValue)
			{
				turningVelocityMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE4F0
			bool WallRunEnterTrack::SetTurningVelocityMax(float newValue)
			{
				turningVelocityMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE510
			bool WallRunEnterTrack::SetTurningAccelerationMin(float newValue)
			{
				turningAccelerationMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE530
			bool WallRunEnterTrack::SetTurningAccelerationMax(float newValue)
			{
				turningAccelerationMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE550
			bool WallRunEnterTrack::SetSurfaceDistance(float newValue)
			{
				surfaceDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE570
			bool WallRunEnterTrack::SetSurfacePushoutVelocityMax(float newValue)
			{
				surfacePushoutVelocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE590
			bool WallRunEnterTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE5A0
			bool WallRunEnterTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE5C0
			bool WallRunEnterTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE5E0
			fight::BranchHolder* WallRunEnterTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x101CE5F0
			bool WallRunEnterTrack::SetInterruptPriority(int newValue)
			{
				interruptPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CE600
			fight::ConditionList* WallRunEnterTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x101CE700
			fight::Property* WallRunEnterTrack::GetProperty(int index)
			{
				return gWallRunEnterTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101CE720
			void WallRunEnterTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWallRunEnterTrackProperties);
			}

			// FUNCTION: ENGINE 0x101CE730
			WallRunEnterTrack::WallRunEnterTrack() : branch(0), blendInTime(0.0f), blendOutTime(0.0f), surfaceDistance(1.0f), surfacePushoutVelocityMax(5.0f), timeBegin(0.0f), timeCancel(0.0f), timeEnd(-1.0f), turningAccelerationMax(0.0f), turningAccelerationMin(0.0f), turningVelocityMax(0.0f), turningVelocityMin(0.0f), velocityUpMax(1e+01f), velocityUpMin(5.0f), velocityXZMax(2e+01f), velocityXZMin(1e+01f), interruptPriority(0), priority(-5)
			{
			}

			// FUNCTION: ENGINE 0x101CE810
			float WallRunEnterTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101CE820
			float WallRunEnterTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101CE830
			WallRunEnterTrack::~WallRunEnterTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CF2C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WallRunEnterTrack::RegisterProperties()
			{
				if (gWallRunEnterTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("timeBegin", &WallRunEnterTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("timeEnd", &WallRunEnterTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("timeCancel", &WallRunEnterTrack::SetTimeCancel);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("velocityXZMin", &WallRunEnterTrack::SetVelocityXZMin);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("velocityXZMax", &WallRunEnterTrack::SetVelocityXZMax);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("velocityUpMin", &WallRunEnterTrack::SetVelocityUpMin);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("velocityUpMax", &WallRunEnterTrack::SetVelocityUpMax);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("turningVelocityMin", &WallRunEnterTrack::SetTurningVelocityMin);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("turningVelocityMax", &WallRunEnterTrack::SetTurningVelocityMax);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("turningAccelerationMin", &WallRunEnterTrack::SetTurningAccelerationMin);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("turningAccelerationMax", &WallRunEnterTrack::SetTurningAccelerationMax);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("surfaceDistance", &WallRunEnterTrack::SetSurfaceDistance);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("surfacePushoutVelocityMax", &WallRunEnterTrack::SetSurfacePushoutVelocityMax);
					properties[12] = property;
					property = new fight::PropertyIntConstRange<WallRunEnterTrack>("priority", &WallRunEnterTrack::SetPriority);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("blendInTime", &WallRunEnterTrack::SetBlendInTime);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<WallRunEnterTrack>("blendOutTime", &WallRunEnterTrack::SetBlendOutTime);
					properties[15] = property;
					property = new fight::PropertyBranch<WallRunEnterTrack>("branch", &WallRunEnterTrack::SetBranch);
					properties[16] = property;
					property = new fight::PropertyIntConstRange<WallRunEnterTrack>("interruptPriority", &WallRunEnterTrack::SetInterruptPriority);
					properties[17] = property;
					property = new fight::PropertyConditionGroup<WallRunEnterTrack>("conditions", &WallRunEnterTrack::SetConditions);
					properties[18] = property;
					fight::RegisterPropertyList(properties, &gWallRunEnterTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101CF080
			fight::TrackFactory* CreateWallRunEnterTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallRunEnterTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CF810
			void RegisterWallRunEnterTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallRunEnterTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<WallRunTrack>;
			template class fight::PropertyName<WallRunTrack>;
			template class fight::PropertyBool<WallRunTrack>;
			template class fight::PropertyEnumConstList<WallRunTrack>;
			template class fight::PropertyIntConstRange<WallRunTrack>;
			template class fight::TrackFactoryTemplate<WallRunTrack>;
			template class fight::TrackFactoryCasterTemplate<WallRunTrack>;
			template class fight::PropertyFloatConstRange<WallOrientTrack>;
			template class fight::PropertyIntConstRange<WallOrientTrack>;
			template class fight::TrackFactoryTemplate<WallOrientTrack>;
			template class fight::TrackFactoryCasterTemplate<WallOrientTrack>;
			template class fight::PropertyFloatConstRange<WallRunEnterTrack>;
			template class fight::PropertyIntConstRange<WallRunEnterTrack>;
			template class fight::PropertyBranch<WallRunEnterTrack>;
			template class fight::PropertyConditionGroup<WallRunEnterTrack>;
			template class fight::TrackFactoryTemplate<WallRunEnterTrack>;
			template class fight::TrackFactoryCasterTemplate<WallRunEnterTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101CEAB0
// FUNCTION: ENGINE 0x101CEAE0
// FUNCTION: ENGINE 0x101CEB10
// FUNCTION: ENGINE 0x101CEB20
// FUNCTION: ENGINE 0x101CEB50
// FUNCTION: ENGINE 0x101CEB60
// FUNCTION: ENGINE 0x101CEB90
// FUNCTION: ENGINE 0x101CEBA0
// FUNCTION: ENGINE 0x101CEBD0
// FUNCTION: ENGINE 0x101CEC00
// FUNCTION: ENGINE 0x101CEC30
// FUNCTION: ENGINE 0x101CEC60
// FUNCTION: ENGINE 0x101CEC70
// FUNCTION: ENGINE 0x101CECA0
// FUNCTION: ENGINE 0x101CECC0
// FUNCTION: ENGINE 0x101CECD0
// FUNCTION: ENGINE 0x101CED10
// FUNCTION: ENGINE 0x101CED20
// FUNCTION: ENGINE 0x101CED50
// FUNCTION: ENGINE 0x101CED70
// FUNCTION: ENGINE 0x101CED80
// FUNCTION: ENGINE 0x101CEDB0
// FUNCTION: ENGINE 0x101CEDD0
// FUNCTION: ENGINE 0x101CEDE0
// FUNCTION: ENGINE 0x101CEE10
// FUNCTION: ENGINE 0x101CEE40
// FUNCTION: ENGINE 0x101CEE50
// FUNCTION: ENGINE 0x101CEE80
// FUNCTION: ENGINE 0x101CEEA0
// FUNCTION: ENGINE 0x101CEEB0
// FUNCTION: ENGINE 0x101CEEE0
// FUNCTION: ENGINE 0x101CEF10
// FUNCTION: ENGINE 0x101CEF20
// FUNCTION: ENGINE 0x101CEF50
// FUNCTION: ENGINE 0x101CEF70
// FUNCTION: ENGINE 0x101CEF80
// FUNCTION: ENGINE 0x101CEFB0
// FUNCTION: ENGINE 0x101CEFD0
// FUNCTION: ENGINE 0x101CF000
// FUNCTION: ENGINE 0x101CF840
// FUNCTION: ENGINE 0x101CF870
// FUNCTION: ENGINE 0x101CF890
// FUNCTION: ENGINE 0x101CF8C0
// FUNCTION: ENGINE 0x101CF8E0
// FUNCTION: ENGINE 0x101CF910
// FUNCTION: ENGINE 0x101D00F0
// FUNCTION: ENGINE 0x101D0140
// FUNCTION: ENGINE 0x101D0190
// FUNCTION: ENGINE 0x101D01C0
// FUNCTION: ENGINE 0x101D01F0
