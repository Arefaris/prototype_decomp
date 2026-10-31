// Fight items of the motion group: WallJumpTrack, WallJumpUpTrack (unit 0x101CC5E0 - 0x101CE030; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_walljump.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gWallJumpTrackProperties;  // 0x11254CA0

			// FUNCTION: ENGINE 0x101CC5E0
			bool WallJumpTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC600
			bool WallJumpTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC620
			bool WallJumpTrack::SetVelocityMin(float newValue)
			{
				velocityMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC640
			bool WallJumpTrack::SetVelocityMax(float newValue)
			{
				velocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC660
			bool WallJumpTrack::SetVelocityXZMax(float newValue)
			{
				velocityXZMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC680
			bool WallJumpTrack::SetGravity(float newValue)
			{
				gravity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC6A0
			bool WallJumpTrack::SetWallAngleMin(float newValue)
			{
				wallAngleMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC6C0
			bool WallJumpTrack::SetWallAngleMax(float newValue)
			{
				wallAngleMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC6E0
			bool WallJumpTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC700
			bool WallJumpTrack::SetUpThresholdArc(float newValue)
			{
				upThresholdArc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC720
			bool WallJumpTrack::SetUseMomentum(bool newValue)
			{
				useMomentum = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC730
			bool WallJumpTrack::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC750
			bool WallJumpTrack::SetMinYAngle(float newValue)
			{
				minYAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC770
			bool WallJumpTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC780
			bool WallJumpTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC7A0
			bool WallJumpTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCBA0
			fight::Property* WallJumpTrack::GetProperty(int index)
			{
				return gWallJumpTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101CCBC0
			void WallJumpTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWallJumpTrackProperties);
			}

			// FUNCTION: ENGINE 0x101CCBD0
			WallJumpTrack::WallJumpTrack() : arc(1.5707964f), blendInTime(0.0f), blendOutTime(0.0f), gravity(0.0f), minYAngle(0.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(0.5235988f), upThresholdArc(0.2617994f), velocityMax(0.0f), velocityMin(0.0f), velocityXZMax(0.0f), wallAngleMax(0.7853982f), wallAngleMin(0.0f), priority(-5), useMomentum(true)
			{
			}

			// FUNCTION: ENGINE 0x101CCC90
			float WallJumpTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101CCCA0
			float WallJumpTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101CCCB0
			WallJumpTrack::~WallJumpTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CD250
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WallJumpTrack::RegisterProperties()
			{
				if (gWallJumpTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("timeBegin", &WallJumpTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("timeEnd", &WallJumpTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("velocityMin", &WallJumpTrack::SetVelocityMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("velocityMax", &WallJumpTrack::SetVelocityMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("velocityXZMax", &WallJumpTrack::SetVelocityXZMax);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("gravity", &WallJumpTrack::SetGravity);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("wallAngleMin", &WallJumpTrack::SetWallAngleMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("wallAngleMax", &WallJumpTrack::SetWallAngleMax);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("turningVelocity", &WallJumpTrack::SetTurningVelocity);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("upThresholdArc", &WallJumpTrack::SetUpThresholdArc);
					properties[9] = property;
					property = new fight::PropertyBool<WallJumpTrack>("useMomentum", &WallJumpTrack::SetUseMomentum);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("arc", &WallJumpTrack::SetArc);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("minYAngle", &WallJumpTrack::SetMinYAngle);
					properties[12] = property;
					property = new fight::PropertyIntConstRange<WallJumpTrack>("priority", &WallJumpTrack::SetPriority);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("blendInTime", &WallJumpTrack::SetBlendInTime);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<WallJumpTrack>("blendOutTime", &WallJumpTrack::SetBlendOutTime);
					properties[15] = property;
					fight::RegisterPropertyList(properties, &gWallJumpTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101CD1F0
			fight::TrackFactory* CreateWallJumpTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallJumpTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CDE80
			void RegisterWallJumpTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallJumpTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gWallJumpUpTrackProperties;  // 0x11254CA4

			// FUNCTION: ENGINE 0x101CC7C0
			bool WallJumpUpTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC7E0
			bool WallJumpUpTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC800
			bool WallJumpUpTrack::SetFlightTimeMin(float newValue)
			{
				flightTimeMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC820
			bool WallJumpUpTrack::SetFlightTimeMax(float newValue)
			{
				flightTimeMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC840
			bool WallJumpUpTrack::SetHeightMin(float newValue)
			{
				heightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC860
			bool WallJumpUpTrack::SetHeightMax(float newValue)
			{
				heightMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC880
			bool WallJumpUpTrack::SetTurnVelocityMin(float newValue)
			{
				turnVelocityMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC8A0
			bool WallJumpUpTrack::SetTurnVelocityMax(float newValue)
			{
				turnVelocityMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC8C0
			bool WallJumpUpTrack::SetTurnAccelerationMin(float newValue)
			{
				turnAccelerationMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC8E0
			bool WallJumpUpTrack::SetTurnAccelerationMax(float newValue)
			{
				turnAccelerationMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC900
			bool WallJumpUpTrack::SetUnlockableFirst(int newValue)
			{
				unlockableFirst = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC920
			bool WallJumpUpTrack::SetUnlockableLast(int newValue)
			{
				unlockableLast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC940
			bool WallJumpUpTrack::SetUnlockableFlightTimeMin(float newValue)
			{
				unlockableFlightTimeMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC960
			bool WallJumpUpTrack::SetUnlockableHeightMin(float newValue)
			{
				unlockableHeightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC980
			bool WallJumpUpTrack::SetObstacleLookaheadDistance(float newValue)
			{
				obstacleLookaheadDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC9A0
			bool WallJumpUpTrack::SetCharacterHeight(float newValue)
			{
				characterHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC9C0
			bool WallJumpUpTrack::SetCharacterWidth(float newValue)
			{
				characterWidth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CC9E0
			bool WallJumpUpTrack::SetCharacterDepth(float newValue)
			{
				characterDepth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCA00
			bool WallJumpUpTrack::SetCharacterSurfaceClearance(float newValue)
			{
				characterSurfaceClearance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCA20
			bool WallJumpUpTrack::SetObstacleHeightMin(float newValue)
			{
				obstacleHeightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCA40
			bool WallJumpUpTrack::SetObstacleHeightMax(float newValue)
			{
				obstacleHeightMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCA60
			bool WallJumpUpTrack::SetObstacleLengthMax(float newValue)
			{
				obstacleLengthMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCA80
			bool WallJumpUpTrack::SetPushOutHeightMin(float newValue)
			{
				pushOutHeightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCAA0
			bool WallJumpUpTrack::SetPushOutVelocityMax(float newValue)
			{
				pushOutVelocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCAC0
			bool WallJumpUpTrack::SetObstacleFaceHeightMin(float newValue)
			{
				obstacleFaceHeightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCAE0
			bool WallJumpUpTrack::SetPushOutHeightMax(float newValue)
			{
				pushOutHeightMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCB00
			bool WallJumpUpTrack::SetObstacleSlopeMax(float newValue)
			{
				obstacleSlopeMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCB20
			bool WallJumpUpTrack::SetAbortRayLength(float newValue)
			{
				abortRayLength = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCB40
			bool WallJumpUpTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCB60
			bool WallJumpUpTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCB80
			bool WallJumpUpTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101CCCC0
			fight::Property* WallJumpUpTrack::GetProperty(int index)
			{
				return gWallJumpUpTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101CCCE0
			void WallJumpUpTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWallJumpUpTrackProperties);
			}

			// FUNCTION: ENGINE 0x101CCCF0
			WallJumpUpTrack::WallJumpUpTrack() : abortRayLength(5.0f), blendInTime(0.0f), blendOutTime(0.0f), characterDepth(2.0f), characterHeight(1.0f), characterSurfaceClearance(0.5f), characterWidth(1.0f), flightTimeMax(4.0f), flightTimeMin(2.0f), heightMax(4.0f), heightMin(2.0f), obstacleFaceHeightMin(0.5f), obstacleHeightMax(2.0f), obstacleHeightMin(0.25f), obstacleLengthMax(2.0f), obstacleLookaheadDistance(5.0f), obstacleSlopeMax(1.0471976f), pushOutHeightMax(2.0f), pushOutHeightMin(1.0f), pushOutVelocityMax(5.0f), timeBegin(0.0f), timeEnd(-1.0f), turnAccelerationMax(0.0f), turnAccelerationMin(0.0f), turnVelocityMax(0.0f), turnVelocityMin(0.0f), unlockableFlightTimeMin(0.0f), unlockableHeightMin(0.0f), priority(-5), unlockableFirst(0), unlockableLast(0)
			{
			}

			// FUNCTION: ENGINE 0x101CCE30
			float WallJumpUpTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101CCE40
			float WallJumpUpTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101CCE50
			WallJumpUpTrack::~WallJumpUpTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CD680
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WallJumpUpTrack::RegisterProperties()
			{
				if (gWallJumpUpTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("timeBegin", &WallJumpUpTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("timeEnd", &WallJumpUpTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("flightTimeMin", &WallJumpUpTrack::SetFlightTimeMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("flightTimeMax", &WallJumpUpTrack::SetFlightTimeMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("heightMin", &WallJumpUpTrack::SetHeightMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("heightMax", &WallJumpUpTrack::SetHeightMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("turnVelocityMin", &WallJumpUpTrack::SetTurnVelocityMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("turnVelocityMax", &WallJumpUpTrack::SetTurnVelocityMax);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("turnAccelerationMin", &WallJumpUpTrack::SetTurnAccelerationMin);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("turnAccelerationMax", &WallJumpUpTrack::SetTurnAccelerationMax);
					properties[9] = property;
					property = new fight::PropertyEnumConstList<WallJumpUpTrack>("unlockableFirst", gJumpTrackUnlockableFirstTable, gJumpTrackUnlockableFirstCount, &WallJumpUpTrack::SetUnlockableFirst);
					properties[10] = property;
					property = new fight::PropertyEnumConstList<WallJumpUpTrack>("unlockableLast", gJumpTrackUnlockableFirstTable, gJumpTrackUnlockableFirstCount, &WallJumpUpTrack::SetUnlockableLast);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("unlockableFlightTimeMin", &WallJumpUpTrack::SetUnlockableFlightTimeMin);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("unlockableHeightMin", &WallJumpUpTrack::SetUnlockableHeightMin);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("obstacleLookaheadDistance", &WallJumpUpTrack::SetObstacleLookaheadDistance);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("characterHeight", &WallJumpUpTrack::SetCharacterHeight);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("characterWidth", &WallJumpUpTrack::SetCharacterWidth);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("characterDepth", &WallJumpUpTrack::SetCharacterDepth);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("characterSurfaceClearance", &WallJumpUpTrack::SetCharacterSurfaceClearance);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("obstacleHeightMin", &WallJumpUpTrack::SetObstacleHeightMin);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("obstacleHeightMax", &WallJumpUpTrack::SetObstacleHeightMax);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("obstacleLengthMax", &WallJumpUpTrack::SetObstacleLengthMax);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("pushOutHeightMin", &WallJumpUpTrack::SetPushOutHeightMin);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("pushOutVelocityMax", &WallJumpUpTrack::SetPushOutVelocityMax);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("obstacleFaceHeightMin", &WallJumpUpTrack::SetObstacleFaceHeightMin);
					properties[24] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("pushOutHeightMax", &WallJumpUpTrack::SetPushOutHeightMax);
					properties[25] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("obstacleSlopeMax", &WallJumpUpTrack::SetObstacleSlopeMax);
					properties[26] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("abortRayLength", &WallJumpUpTrack::SetAbortRayLength);
					properties[27] = property;
					property = new fight::PropertyIntConstRange<WallJumpUpTrack>("priority", &WallJumpUpTrack::SetPriority);
					properties[28] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("blendInTime", &WallJumpUpTrack::SetBlendInTime);
					properties[29] = property;
					property = new fight::PropertyFloatConstRange<WallJumpUpTrack>("blendOutTime", &WallJumpUpTrack::SetBlendOutTime);
					properties[30] = property;
					fight::RegisterPropertyList(properties, &gWallJumpUpTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101CD220
			fight::TrackFactory* CreateWallJumpUpTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallJumpUpTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CDEB0
			void RegisterWallJumpUpTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WallJumpUpTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<WallJumpTrack>;
			template class fight::PropertyBool<WallJumpTrack>;
			template class fight::PropertyIntConstRange<WallJumpTrack>;
			template class fight::TrackFactoryTemplate<WallJumpTrack>;
			template class fight::TrackFactoryCasterTemplate<WallJumpTrack>;
			template class fight::PropertyFloatConstRange<WallJumpUpTrack>;
			template class fight::PropertyEnumConstList<WallJumpUpTrack>;
			template class fight::PropertyIntConstRange<WallJumpUpTrack>;
			template class fight::TrackFactoryTemplate<WallJumpUpTrack>;
			template class fight::TrackFactoryCasterTemplate<WallJumpUpTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101CCE60
// FUNCTION: ENGINE 0x101CCE90
// FUNCTION: ENGINE 0x101CCEC0
// FUNCTION: ENGINE 0x101CCED0
// FUNCTION: ENGINE 0x101CCF00
// FUNCTION: ENGINE 0x101CCF10
// FUNCTION: ENGINE 0x101CCF40
// FUNCTION: ENGINE 0x101CCF70
// FUNCTION: ENGINE 0x101CCFA0
// FUNCTION: ENGINE 0x101CCFB0
// FUNCTION: ENGINE 0x101CCFE0
// FUNCTION: ENGINE 0x101CD000
// FUNCTION: ENGINE 0x101CD010
// FUNCTION: ENGINE 0x101CD040
// FUNCTION: ENGINE 0x101CD060
// FUNCTION: ENGINE 0x101CD070
// FUNCTION: ENGINE 0x101CD0A0
// FUNCTION: ENGINE 0x101CD0D0
// FUNCTION: ENGINE 0x101CD0E0
// FUNCTION: ENGINE 0x101CD120
// FUNCTION: ENGINE 0x101CD130
// FUNCTION: ENGINE 0x101CD160
// FUNCTION: ENGINE 0x101CD180
// FUNCTION: ENGINE 0x101CD190
// FUNCTION: ENGINE 0x101CD1C0
// FUNCTION: ENGINE 0x101CD1E0
// FUNCTION: ENGINE 0x101CDEE0
// FUNCTION: ENGINE 0x101CDF10
// FUNCTION: ENGINE 0x101CDF30
// FUNCTION: ENGINE 0x101CDF60
// FUNCTION: ENGINE 0x101CDF90
// FUNCTION: ENGINE 0x101CDFE0
