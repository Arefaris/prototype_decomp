// Fight items of the motion group: AnimationBlendVerticalAimTrack, AnimationBlendSimpleTrack, AnimationBlendVerticalAimStrafeTrack, AnimationBlendDirectionalTrack (unit 0x1013C5B0 - 0x10140FC0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_animationblend.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gAnimationBlendVerticalAimTrackProperties;  // 0x11254208

			// FUNCTION: ENGINE 0x1013C5B0
			bool AnimationBlendVerticalAimTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C5D0
			bool AnimationBlendVerticalAimTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C5F0
			bool AnimationBlendVerticalAimTrack::SetAngleRate(float newValue)
			{
				angleRate = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C610
			bool AnimationBlendVerticalAimTrack::SetAngleDefault(float newValue)
			{
				angleDefault = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C630
			bool AnimationBlendVerticalAimTrack::SetAngleOffset(float newValue)
			{
				angleOffset = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C650
			bool AnimationBlendVerticalAimTrack::SetAngleOffsetMin(float newValue)
			{
				angleOffsetMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C670
			bool AnimationBlendVerticalAimTrack::SetAngleMin(float newValue)
			{
				angleMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C690
			bool AnimationBlendVerticalAimTrack::SetAngleMax(float newValue)
			{
				angleMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C6B0
			bool AnimationBlendVerticalAimTrack::SetOffsetInterpolationDist(float newValue)
			{
				offsetInterpolationDist = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C6D0
			bool AnimationBlendVerticalAimTrack::SetInterpolationDirection(int newValue)
			{
				interpolationDirection = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C6F0
			bool AnimationBlendVerticalAimTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C710
			bool AnimationBlendVerticalAimTrack::SetCyclic(int newValue)
			{
				cyclic = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D300
			bool AnimationBlendVerticalAimTrack::SetAnimUp(const fight::Name& newValue)
			{
				animUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C730
			bool AnimationBlendVerticalAimTrack::SetAnimUpAngle(float newValue)
			{
				animUpAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C750
			bool AnimationBlendVerticalAimTrack::SetAnimUpSyncFrame(float newValue)
			{
				animUpSyncFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C770
			bool AnimationBlendVerticalAimTrack::SetAnimUpStartFrame(float newValue)
			{
				animUpStartFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C790
			bool AnimationBlendVerticalAimTrack::SetAnimUpEndFrame(float newValue)
			{
				animUpEndFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C7B0
			bool AnimationBlendVerticalAimTrack::SetAnimUpSpeed(float newValue)
			{
				animUpSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D320
			bool AnimationBlendVerticalAimTrack::SetAnimNeutral(const fight::Name& newValue)
			{
				animNeutral = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C7D0
			bool AnimationBlendVerticalAimTrack::SetAnimNeutralAngle(float newValue)
			{
				animNeutralAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C7F0
			bool AnimationBlendVerticalAimTrack::SetAnimNeutralSyncFrame(float newValue)
			{
				animNeutralSyncFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C810
			bool AnimationBlendVerticalAimTrack::SetAnimNeutralStartFrame(float newValue)
			{
				animNeutralStartFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C830
			bool AnimationBlendVerticalAimTrack::SetAnimNeutralEndFrame(float newValue)
			{
				animNeutralEndFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C850
			bool AnimationBlendVerticalAimTrack::SetAnimNeutralSpeed(float newValue)
			{
				animNeutralSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D340
			bool AnimationBlendVerticalAimTrack::SetAnimDown(const fight::Name& newValue)
			{
				animDown = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C870
			bool AnimationBlendVerticalAimTrack::SetAnimDownAngle(float newValue)
			{
				animDownAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C890
			bool AnimationBlendVerticalAimTrack::SetAnimDownSyncFrame(float newValue)
			{
				animDownSyncFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C8B0
			bool AnimationBlendVerticalAimTrack::SetAnimDownStartFrame(float newValue)
			{
				animDownStartFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C8D0
			bool AnimationBlendVerticalAimTrack::SetAnimDownEndFrame(float newValue)
			{
				animDownEndFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C8F0
			bool AnimationBlendVerticalAimTrack::SetAnimDownSpeed(float newValue)
			{
				animDownSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D360
			bool AnimationBlendVerticalAimTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C910
			bool AnimationBlendVerticalAimTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C930
			bool AnimationBlendVerticalAimTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C950
			bool AnimationBlendVerticalAimTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C970
			bool AnimationBlendVerticalAimTrack::SetTargetingMode(int newValue)
			{
				targetingMode = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D230
			fight::Property* AnimationBlendVerticalAimTrack::GetProperty(int index)
			{
				return gAnimationBlendVerticalAimTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1013D250
			void AnimationBlendVerticalAimTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAnimationBlendVerticalAimTrackProperties);
			}

			// FUNCTION: ENGINE 0x1013D700
			AnimationBlendVerticalAimTrack::AnimationBlendVerticalAimTrack() : angleDefault(0.0f), angleMax(1.5707964f), angleMin(-1.5707964f), angleOffset(0.0f), angleOffsetMin(0.0f), angleRate(20.94395f), animDownAngle(-1.5707964f), animDownEndFrame(-1.0f), animDownSpeed(1.0f), animDownStartFrame(0.0f), animDownSyncFrame(0.0f), animNeutralAngle(0.0f), animNeutralEndFrame(-1.0f), animNeutralSpeed(1.0f), animNeutralStartFrame(0.0f), animNeutralSyncFrame(0.0f), animUpAngle(1.5707964f), animUpEndFrame(-1.0f), animUpSpeed(1.0f), animUpStartFrame(0.0f), animUpSyncFrame(0.0f), blendInTime(0.0f), blendOutTime(0.0f), offsetInterpolationDist(0.0f), speed(1.0f), timeBegin(0.0f), timeEnd(-1.0f), cyclic(0), interpolationDirection(0), priority(0), targetingMode(0)
			{
			}

			// FUNCTION: ENGINE 0x1013D890
			float AnimationBlendVerticalAimTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1013D8A0
			float AnimationBlendVerticalAimTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1013D8B0
			AnimationBlendVerticalAimTrack::~AnimationBlendVerticalAimTrack()
			{
			}

			// FUNCTION: ENGINE 0x1013EB60
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AnimationBlendVerticalAimTrack::RegisterProperties()
			{
				if (gAnimationBlendVerticalAimTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("timeBegin", &AnimationBlendVerticalAimTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("timeEnd", &AnimationBlendVerticalAimTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("angleRate", &AnimationBlendVerticalAimTrack::SetAngleRate);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("angleDefault", &AnimationBlendVerticalAimTrack::SetAngleDefault);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("angleOffset", &AnimationBlendVerticalAimTrack::SetAngleOffset);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("angleOffsetMin", &AnimationBlendVerticalAimTrack::SetAngleOffsetMin);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("angleMin", &AnimationBlendVerticalAimTrack::SetAngleMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("angleMax", &AnimationBlendVerticalAimTrack::SetAngleMax);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("offsetInterpolationDist", &AnimationBlendVerticalAimTrack::SetOffsetInterpolationDist);
					properties[8] = property;
					property = new fight::PropertyEnumConstList<AnimationBlendVerticalAimTrack>("interpolationDirection", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &AnimationBlendVerticalAimTrack::SetInterpolationDirection);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("speed", &AnimationBlendVerticalAimTrack::SetSpeed);
					properties[10] = property;
					property = new fight::PropertyEnumConstList<AnimationBlendVerticalAimTrack>("cyclic", gAnimationBlendVerticalAimTrackCyclicTable, 3, &AnimationBlendVerticalAimTrack::SetCyclic);
					properties[11] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimTrack>("animUp", &AnimationBlendVerticalAimTrack::SetAnimUp);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animUpAngle", &AnimationBlendVerticalAimTrack::SetAnimUpAngle);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animUpSyncFrame", &AnimationBlendVerticalAimTrack::SetAnimUpSyncFrame);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animUpStartFrame", &AnimationBlendVerticalAimTrack::SetAnimUpStartFrame);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animUpEndFrame", &AnimationBlendVerticalAimTrack::SetAnimUpEndFrame);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animUpSpeed", &AnimationBlendVerticalAimTrack::SetAnimUpSpeed);
					properties[17] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimTrack>("animNeutral", &AnimationBlendVerticalAimTrack::SetAnimNeutral);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animNeutralAngle", &AnimationBlendVerticalAimTrack::SetAnimNeutralAngle);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animNeutralSyncFrame", &AnimationBlendVerticalAimTrack::SetAnimNeutralSyncFrame);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animNeutralStartFrame", &AnimationBlendVerticalAimTrack::SetAnimNeutralStartFrame);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animNeutralEndFrame", &AnimationBlendVerticalAimTrack::SetAnimNeutralEndFrame);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animNeutralSpeed", &AnimationBlendVerticalAimTrack::SetAnimNeutralSpeed);
					properties[23] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimTrack>("animDown", &AnimationBlendVerticalAimTrack::SetAnimDown);
					properties[24] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animDownAngle", &AnimationBlendVerticalAimTrack::SetAnimDownAngle);
					properties[25] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animDownSyncFrame", &AnimationBlendVerticalAimTrack::SetAnimDownSyncFrame);
					properties[26] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animDownStartFrame", &AnimationBlendVerticalAimTrack::SetAnimDownStartFrame);
					properties[27] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animDownEndFrame", &AnimationBlendVerticalAimTrack::SetAnimDownEndFrame);
					properties[28] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("animDownSpeed", &AnimationBlendVerticalAimTrack::SetAnimDownSpeed);
					properties[29] = property;
					property = new fight::PropertyNameList<AnimationBlendVerticalAimTrack>("partition", &AnimationBlendVerticalAimTrack::SetPartition);
					properties[30] = property;
					property = new fight::PropertyIntConstRange<AnimationBlendVerticalAimTrack>("priority", &AnimationBlendVerticalAimTrack::SetPriority);
					properties[31] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("blendInTime", &AnimationBlendVerticalAimTrack::SetBlendInTime);
					properties[32] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>("blendOutTime", &AnimationBlendVerticalAimTrack::SetBlendOutTime);
					properties[33] = property;
					property = new fight::PropertyEnumConstList<AnimationBlendVerticalAimTrack>("targetingMode", gAnimationBlendVerticalAimTrackTargetingModeTable, gAnimationBlendVerticalAimTrackTargetingModeCount, &AnimationBlendVerticalAimTrack::SetTargetingMode);
					properties[34] = property;
					fight::RegisterPropertyList(properties, &gAnimationBlendVerticalAimTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1013E6D0
			fight::TrackFactory* CreateAnimationBlendVerticalAimTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AnimationBlendVerticalAimTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1013E7B0
			void RegisterAnimationBlendVerticalAimTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AnimationBlendVerticalAimTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAnimationBlendSimpleTrackProperties;  // 0x1125420C

			// FUNCTION: ENGINE 0x1013C990
			bool AnimationBlendSimpleTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C9B0
			bool AnimationBlendSimpleTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D380
			bool AnimationBlendSimpleTrack::SetWeightVariable(const fight::Name& newValue)
			{
				weightVariable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C9D0
			bool AnimationBlendSimpleTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013C9F0
			bool AnimationBlendSimpleTrack::SetCyclic(int newValue)
			{
				cyclic = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D3A0
			bool AnimationBlendSimpleTrack::SetAnimA(const fight::Name& newValue)
			{
				animA = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CA00
			bool AnimationBlendSimpleTrack::SetAnimASyncFrame(float newValue)
			{
				animASyncFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CA20
			bool AnimationBlendSimpleTrack::SetAnimAStartFrame(float newValue)
			{
				animAStartFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CA40
			bool AnimationBlendSimpleTrack::SetAnimAEndFrame(float newValue)
			{
				animAEndFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CA60
			bool AnimationBlendSimpleTrack::SetAnimASpeed(float newValue)
			{
				animASpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D3C0
			bool AnimationBlendSimpleTrack::SetAnimB(const fight::Name& newValue)
			{
				animB = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CA80
			bool AnimationBlendSimpleTrack::SetAnimBSyncFrame(float newValue)
			{
				animBSyncFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CAA0
			bool AnimationBlendSimpleTrack::SetAnimBStartFrame(float newValue)
			{
				animBStartFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CAC0
			bool AnimationBlendSimpleTrack::SetAnimBEndFrame(float newValue)
			{
				animBEndFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CAE0
			bool AnimationBlendSimpleTrack::SetAnimBSpeed(float newValue)
			{
				animBSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D3E0
			bool AnimationBlendSimpleTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CB00
			bool AnimationBlendSimpleTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CB10
			bool AnimationBlendSimpleTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CB30
			bool AnimationBlendSimpleTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D260
			fight::Property* AnimationBlendSimpleTrack::GetProperty(int index)
			{
				return gAnimationBlendSimpleTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1013D280
			void AnimationBlendSimpleTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAnimationBlendSimpleTrackProperties);
			}

			// FUNCTION: ENGINE 0x1013D8C0
			AnimationBlendSimpleTrack::AnimationBlendSimpleTrack() : animAEndFrame(-1.0f), animASpeed(1.0f), animAStartFrame(0.0f), animASyncFrame(0.0f), animBEndFrame(-1.0f), animBSpeed(1.0f), animBStartFrame(0.0f), animBSyncFrame(0.0f), blendInTime(0.0f), blendOutTime(0.0f), speed(1.0f), timeBegin(0.0f), timeEnd(-1.0f), cyclic(0), priority(0)
			{
			}

			// FUNCTION: ENGINE 0x1013D980
			float AnimationBlendSimpleTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1013D990
			float AnimationBlendSimpleTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1013D9A0
			AnimationBlendSimpleTrack::~AnimationBlendSimpleTrack()
			{
			}

			// FUNCTION: ENGINE 0x1013F470
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AnimationBlendSimpleTrack::RegisterProperties()
			{
				if (gAnimationBlendSimpleTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>("timeBegin", &AnimationBlendSimpleTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>("timeEnd", &AnimationBlendSimpleTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<AnimationBlendSimpleTrack>("weightVariable", &AnimationBlendSimpleTrack::SetWeightVariable);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>("speed", &AnimationBlendSimpleTrack::SetSpeed);
					properties[3] = property;
					property = new fight::PropertyEnumConstList<AnimationBlendSimpleTrack>("cyclic", gAnimationBlendSimpleTrackCyclicTable, 3, &AnimationBlendSimpleTrack::SetCyclic);
					properties[4] = property;
					property = new fight::PropertyName<AnimationBlendSimpleTrack>("animA", &AnimationBlendSimpleTrack::SetAnimA);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>("animASyncFrame", &AnimationBlendSimpleTrack::SetAnimASyncFrame);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>("animAStartFrame", &AnimationBlendSimpleTrack::SetAnimAStartFrame);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>("animAEndFrame", &AnimationBlendSimpleTrack::SetAnimAEndFrame);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>("animASpeed", &AnimationBlendSimpleTrack::SetAnimASpeed);
					properties[9] = property;
					property = new fight::PropertyName<AnimationBlendSimpleTrack>("animB", &AnimationBlendSimpleTrack::SetAnimB);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>("animBSyncFrame", &AnimationBlendSimpleTrack::SetAnimBSyncFrame);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>("animBStartFrame", &AnimationBlendSimpleTrack::SetAnimBStartFrame);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>("animBEndFrame", &AnimationBlendSimpleTrack::SetAnimBEndFrame);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>("animBSpeed", &AnimationBlendSimpleTrack::SetAnimBSpeed);
					properties[14] = property;
					property = new fight::PropertyNameList<AnimationBlendSimpleTrack>("partition", &AnimationBlendSimpleTrack::SetPartition);
					properties[15] = property;
					property = new fight::PropertyIntConstRange<AnimationBlendSimpleTrack>("priority", &AnimationBlendSimpleTrack::SetPriority);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>("blendInTime", &AnimationBlendSimpleTrack::SetBlendInTime);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>("blendOutTime", &AnimationBlendSimpleTrack::SetBlendOutTime);
					properties[18] = property;
					fight::RegisterPropertyList(properties, &gAnimationBlendSimpleTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1013E700
			fight::TrackFactory* CreateAnimationBlendSimpleTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AnimationBlendSimpleTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1013E7E0
			void RegisterAnimationBlendSimpleTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AnimationBlendSimpleTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAnimationBlendVerticalAimStrafeTrackProperties;  // 0x11254210

			// FUNCTION: ENGINE 0x1013CB50
			bool AnimationBlendVerticalAimStrafeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CB70
			bool AnimationBlendVerticalAimStrafeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D400
			bool AnimationBlendVerticalAimStrafeTrack::SetRefLocomotionName(const fight::Name& newValue)
			{
				refLocomotionName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CB90
			bool AnimationBlendVerticalAimStrafeTrack::SetAngleRate(float newValue)
			{
				angleRate = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CBC0
			bool AnimationBlendVerticalAimStrafeTrack::SetAngleDefault(float newValue)
			{
				angleDefault = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CBF0
			bool AnimationBlendVerticalAimStrafeTrack::SetAngleOffset(float newValue)
			{
				angleOffset = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CC20
			bool AnimationBlendVerticalAimStrafeTrack::SetAngleOffsetMin(float newValue)
			{
				angleOffsetMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CC50
			bool AnimationBlendVerticalAimStrafeTrack::SetOffsetInterpolationDist(float newValue)
			{
				offsetInterpolationDist = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CC70
			bool AnimationBlendVerticalAimStrafeTrack::SetInterpolationDirection(int newValue)
			{
				interpolationDirection = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CC90
			bool AnimationBlendVerticalAimStrafeTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CCB0
			bool AnimationBlendVerticalAimStrafeTrack::SetCyclic(int newValue)
			{
				cyclic = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D420
			bool AnimationBlendVerticalAimStrafeTrack::SetPivotJoint(const fight::Name& newValue)
			{
				pivotJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CCD0
			bool AnimationBlendVerticalAimStrafeTrack::SetPivotOffset(const math::Vector& newValue)
			{
				pivotOffset.x = newValue.x;
				pivotOffset.y = newValue.y;
				pivotOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CD00
			bool AnimationBlendVerticalAimStrafeTrack::SetTargetingMode(int newValue)
			{
				targetingMode = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CD20
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimUpAngle(float newValue)
			{
				animUpAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CD50
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimNeutralAngle(float newValue)
			{
				animNeutralAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CD80
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimDownAngle(float newValue)
			{
				animDownAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D440
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimIdleUp(const fight::Name& newValue)
			{
				animIdleUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D460
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimIdleNeutral(const fight::Name& newValue)
			{
				animIdleNeutral = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D480
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimIdleDown(const fight::Name& newValue)
			{
				animIdleDown = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D4A0
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimNorthUp(const fight::Name& newValue)
			{
				animNorthUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D4C0
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimNorthNeutral(const fight::Name& newValue)
			{
				animNorthNeutral = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D4E0
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimNorthDown(const fight::Name& newValue)
			{
				animNorthDown = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D500
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimEastUp(const fight::Name& newValue)
			{
				animEastUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D520
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimEastNeutral(const fight::Name& newValue)
			{
				animEastNeutral = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D540
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimEastDown(const fight::Name& newValue)
			{
				animEastDown = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D560
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimSouthUp(const fight::Name& newValue)
			{
				animSouthUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D580
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimSouthNeutral(const fight::Name& newValue)
			{
				animSouthNeutral = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D5A0
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimSouthDown(const fight::Name& newValue)
			{
				animSouthDown = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D5C0
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimWestUp(const fight::Name& newValue)
			{
				animWestUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D5E0
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimWestNeutral(const fight::Name& newValue)
			{
				animWestNeutral = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D600
			bool AnimationBlendVerticalAimStrafeTrack::SetAnimWestDown(const fight::Name& newValue)
			{
				animWestDown = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D620
			bool AnimationBlendVerticalAimStrafeTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CDB0
			bool AnimationBlendVerticalAimStrafeTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CDD0
			bool AnimationBlendVerticalAimStrafeTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CDF0
			bool AnimationBlendVerticalAimStrafeTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D290
			fight::Property* AnimationBlendVerticalAimStrafeTrack::GetProperty(int index)
			{
				return gAnimationBlendVerticalAimStrafeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1013D2B0
			void AnimationBlendVerticalAimStrafeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAnimationBlendVerticalAimStrafeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1013D9B0
			AnimationBlendVerticalAimStrafeTrack::AnimationBlendVerticalAimStrafeTrack() : pivotOffset(0.0f, 0.0f, 0.0f), angleDefault(0.0f), angleOffset(0.0f), angleOffsetMin(0.0f), angleRate(20.94395f), animDownAngle(-1.5707964f), animNeutralAngle(0.0f), animUpAngle(1.5707964f), blendInTime(0.0f), blendOutTime(0.0f), offsetInterpolationDist(0.0f), speed(1.0f), timeBegin(0.0f), timeEnd(-1.0f), cyclic(0), interpolationDirection(0), priority(0), targetingMode(0)
			{
			}

			// FUNCTION: ENGINE 0x1013DB80
			float AnimationBlendVerticalAimStrafeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1013DB90
			float AnimationBlendVerticalAimStrafeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1013DBA0
			AnimationBlendVerticalAimStrafeTrack::~AnimationBlendVerticalAimStrafeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1013F970
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AnimationBlendVerticalAimStrafeTrack::RegisterProperties()
			{
				if (gAnimationBlendVerticalAimStrafeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>("timeBegin", &AnimationBlendVerticalAimStrafeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>("timeEnd", &AnimationBlendVerticalAimStrafeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("refLocomotionName", &AnimationBlendVerticalAimStrafeTrack::SetRefLocomotionName);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>("angleRate", &AnimationBlendVerticalAimStrafeTrack::SetAngleRate);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>("angleDefault", &AnimationBlendVerticalAimStrafeTrack::SetAngleDefault);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>("angleOffset", &AnimationBlendVerticalAimStrafeTrack::SetAngleOffset);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>("angleOffsetMin", &AnimationBlendVerticalAimStrafeTrack::SetAngleOffsetMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>("offsetInterpolationDist", &AnimationBlendVerticalAimStrafeTrack::SetOffsetInterpolationDist);
					properties[7] = property;
					property = new fight::PropertyEnumConstList<AnimationBlendVerticalAimStrafeTrack>("interpolationDirection", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &AnimationBlendVerticalAimStrafeTrack::SetInterpolationDirection);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>("speed", &AnimationBlendVerticalAimStrafeTrack::SetSpeed);
					properties[9] = property;
					property = new fight::PropertyEnumConstList<AnimationBlendVerticalAimStrafeTrack>("cyclic", gAnimationBlendVerticalAimStrafeTrackCyclicTable, 3, &AnimationBlendVerticalAimStrafeTrack::SetCyclic);
					properties[10] = property;
					property = new fight::PropertyNameList<AnimationBlendVerticalAimStrafeTrack>("pivotJoint", &AnimationBlendVerticalAimStrafeTrack::SetPivotJoint);
					properties[11] = property;
					property = new fight::PropertyVector<AnimationBlendVerticalAimStrafeTrack>("pivotOffset", &AnimationBlendVerticalAimStrafeTrack::SetPivotOffset);
					properties[12] = property;
					property = new fight::PropertyEnumConstList<AnimationBlendVerticalAimStrafeTrack>("targetingMode", gAnimationBlendVerticalAimTrackTargetingModeTable, gAnimationBlendVerticalAimTrackTargetingModeCount, &AnimationBlendVerticalAimStrafeTrack::SetTargetingMode);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>("animUpAngle", &AnimationBlendVerticalAimStrafeTrack::SetAnimUpAngle);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>("animNeutralAngle", &AnimationBlendVerticalAimStrafeTrack::SetAnimNeutralAngle);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>("animDownAngle", &AnimationBlendVerticalAimStrafeTrack::SetAnimDownAngle);
					properties[16] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animIdleUp", &AnimationBlendVerticalAimStrafeTrack::SetAnimIdleUp);
					properties[17] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animIdleNeutral", &AnimationBlendVerticalAimStrafeTrack::SetAnimIdleNeutral);
					properties[18] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animIdleDown", &AnimationBlendVerticalAimStrafeTrack::SetAnimIdleDown);
					properties[19] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animNorthUp", &AnimationBlendVerticalAimStrafeTrack::SetAnimNorthUp);
					properties[20] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animNorthNeutral", &AnimationBlendVerticalAimStrafeTrack::SetAnimNorthNeutral);
					properties[21] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animNorthDown", &AnimationBlendVerticalAimStrafeTrack::SetAnimNorthDown);
					properties[22] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animEastUp", &AnimationBlendVerticalAimStrafeTrack::SetAnimEastUp);
					properties[23] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animEastNeutral", &AnimationBlendVerticalAimStrafeTrack::SetAnimEastNeutral);
					properties[24] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animEastDown", &AnimationBlendVerticalAimStrafeTrack::SetAnimEastDown);
					properties[25] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animSouthUp", &AnimationBlendVerticalAimStrafeTrack::SetAnimSouthUp);
					properties[26] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animSouthNeutral", &AnimationBlendVerticalAimStrafeTrack::SetAnimSouthNeutral);
					properties[27] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animSouthDown", &AnimationBlendVerticalAimStrafeTrack::SetAnimSouthDown);
					properties[28] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animWestUp", &AnimationBlendVerticalAimStrafeTrack::SetAnimWestUp);
					properties[29] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animWestNeutral", &AnimationBlendVerticalAimStrafeTrack::SetAnimWestNeutral);
					properties[30] = property;
					property = new fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>("animWestDown", &AnimationBlendVerticalAimStrafeTrack::SetAnimWestDown);
					properties[31] = property;
					property = new fight::PropertyNameList<AnimationBlendVerticalAimStrafeTrack>("partition", &AnimationBlendVerticalAimStrafeTrack::SetPartition);
					properties[32] = property;
					property = new fight::PropertyIntConstRange<AnimationBlendVerticalAimStrafeTrack>("priority", &AnimationBlendVerticalAimStrafeTrack::SetPriority);
					properties[33] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>("blendInTime", &AnimationBlendVerticalAimStrafeTrack::SetBlendInTime);
					properties[34] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>("blendOutTime", &AnimationBlendVerticalAimStrafeTrack::SetBlendOutTime);
					properties[35] = property;
					fight::RegisterPropertyList(properties, &gAnimationBlendVerticalAimStrafeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1013E730
			fight::TrackFactory* CreateAnimationBlendVerticalAimStrafeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AnimationBlendVerticalAimStrafeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1013E810
			void RegisterAnimationBlendVerticalAimStrafeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AnimationBlendVerticalAimStrafeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAnimationBlendDirectionalTrackProperties;  // 0x11254214

			// FUNCTION: ENGINE 0x1013CE10
			bool AnimationBlendDirectionalTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CE30
			bool AnimationBlendDirectionalTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CE50
			bool AnimationBlendDirectionalTrack::SetInput(int newValue)
			{
				input = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CE70
			bool AnimationBlendDirectionalTrack::SetBlendRate(float newValue)
			{
				blendRate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CE90
			bool AnimationBlendDirectionalTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CEB0
			bool AnimationBlendDirectionalTrack::SetCyclic(int newValue)
			{
				cyclic = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D640
			bool AnimationBlendDirectionalTrack::SetAnimNeutral(const fight::Name& newValue)
			{
				animNeutral = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CED0
			bool AnimationBlendDirectionalTrack::SetAnimNeutralSyncFrame(float newValue)
			{
				animNeutralSyncFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CEF0
			bool AnimationBlendDirectionalTrack::SetAnimNeutralStartFrame(float newValue)
			{
				animNeutralStartFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CF10
			bool AnimationBlendDirectionalTrack::SetAnimNeutralEndFrame(float newValue)
			{
				animNeutralEndFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CF30
			bool AnimationBlendDirectionalTrack::SetAnimNeutralSpeed(float newValue)
			{
				animNeutralSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D660
			bool AnimationBlendDirectionalTrack::SetAnimNorth(const fight::Name& newValue)
			{
				animNorth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CF50
			bool AnimationBlendDirectionalTrack::SetAnimNorthSyncFrame(float newValue)
			{
				animNorthSyncFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CF70
			bool AnimationBlendDirectionalTrack::SetAnimNorthStartFrame(float newValue)
			{
				animNorthStartFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CF90
			bool AnimationBlendDirectionalTrack::SetAnimNorthEndFrame(float newValue)
			{
				animNorthEndFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CFB0
			bool AnimationBlendDirectionalTrack::SetAnimNorthSpeed(float newValue)
			{
				animNorthSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CFD0
			bool AnimationBlendDirectionalTrack::SetAnimNorthAllowedTransitions(int newValue)
			{
				animNorthAllowedTransitions = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D680
			bool AnimationBlendDirectionalTrack::SetAnimEast(const fight::Name& newValue)
			{
				animEast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013CFF0
			bool AnimationBlendDirectionalTrack::SetAnimEastSyncFrame(float newValue)
			{
				animEastSyncFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D010
			bool AnimationBlendDirectionalTrack::SetAnimEastStartFrame(float newValue)
			{
				animEastStartFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D030
			bool AnimationBlendDirectionalTrack::SetAnimEastEndFrame(float newValue)
			{
				animEastEndFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D050
			bool AnimationBlendDirectionalTrack::SetAnimEastSpeed(float newValue)
			{
				animEastSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D070
			bool AnimationBlendDirectionalTrack::SetAnimEastAllowedTransitions(int newValue)
			{
				animEastAllowedTransitions = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D6A0
			bool AnimationBlendDirectionalTrack::SetAnimSouth(const fight::Name& newValue)
			{
				animSouth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D090
			bool AnimationBlendDirectionalTrack::SetAnimSouthSyncFrame(float newValue)
			{
				animSouthSyncFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D0B0
			bool AnimationBlendDirectionalTrack::SetAnimSouthStartFrame(float newValue)
			{
				animSouthStartFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D0D0
			bool AnimationBlendDirectionalTrack::SetAnimSouthEndFrame(float newValue)
			{
				animSouthEndFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D0F0
			bool AnimationBlendDirectionalTrack::SetAnimSouthSpeed(float newValue)
			{
				animSouthSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D110
			bool AnimationBlendDirectionalTrack::SetAnimSouthAllowedTransitions(int newValue)
			{
				animSouthAllowedTransitions = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D6C0
			bool AnimationBlendDirectionalTrack::SetAnimWest(const fight::Name& newValue)
			{
				animWest = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D130
			bool AnimationBlendDirectionalTrack::SetAnimWestSyncFrame(float newValue)
			{
				animWestSyncFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D150
			bool AnimationBlendDirectionalTrack::SetAnimWestStartFrame(float newValue)
			{
				animWestStartFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D170
			bool AnimationBlendDirectionalTrack::SetAnimWestEndFrame(float newValue)
			{
				animWestEndFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D190
			bool AnimationBlendDirectionalTrack::SetAnimWestSpeed(float newValue)
			{
				animWestSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D1B0
			bool AnimationBlendDirectionalTrack::SetAnimWestAllowedTransitions(int newValue)
			{
				animWestAllowedTransitions = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D6E0
			bool AnimationBlendDirectionalTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D1D0
			bool AnimationBlendDirectionalTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D1F0
			bool AnimationBlendDirectionalTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D210
			bool AnimationBlendDirectionalTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1013D2C0
			fight::Property* AnimationBlendDirectionalTrack::GetProperty(int index)
			{
				return gAnimationBlendDirectionalTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1013D2E0
			void AnimationBlendDirectionalTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAnimationBlendDirectionalTrackProperties);
			}

			// FUNCTION: ENGINE 0x1013DBB0
			AnimationBlendDirectionalTrack::AnimationBlendDirectionalTrack() : animEastEndFrame(-1.0f), animEastSpeed(1.0f), animEastStartFrame(0.0f), animEastSyncFrame(0.0f), animNeutralEndFrame(-1.0f), animNeutralSpeed(1.0f), animNeutralStartFrame(0.0f), animNeutralSyncFrame(0.0f), animNorthEndFrame(-1.0f), animNorthSpeed(1.0f), animNorthStartFrame(0.0f), animNorthSyncFrame(0.0f), animSouthEndFrame(-1.0f), animSouthSpeed(1.0f), animSouthStartFrame(0.0f), animSouthSyncFrame(0.0f), animWestEndFrame(-1.0f), animWestSpeed(1.0f), animWestStartFrame(0.0f), animWestSyncFrame(0.0f), blendInTime(0.0f), blendOutTime(0.0f), blendRate(1.0f), speed(1.0f), timeBegin(0.0f), timeEnd(-1.0f), cyclic(0), input(0), priority(0), animEastAllowedTransitions(-1), animNorthAllowedTransitions(-1), animSouthAllowedTransitions(-1), animWestAllowedTransitions(-1)
			{
			}

			// FUNCTION: ENGINE 0x1013DD20
			float AnimationBlendDirectionalTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1013DD30
			float AnimationBlendDirectionalTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1013DD40
			AnimationBlendDirectionalTrack::~AnimationBlendDirectionalTrack()
			{
			}

			// FUNCTION: ENGINE 0x101402C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AnimationBlendDirectionalTrack::RegisterProperties()
			{
				if (gAnimationBlendDirectionalTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("timeBegin", &AnimationBlendDirectionalTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("timeEnd", &AnimationBlendDirectionalTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<AnimationBlendDirectionalTrack>("input", gAnimationBlendDirectionalTrackInputTable, 1, &AnimationBlendDirectionalTrack::SetInput);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("blendRate", &AnimationBlendDirectionalTrack::SetBlendRate);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("speed", &AnimationBlendDirectionalTrack::SetSpeed);
					properties[4] = property;
					property = new fight::PropertyEnumConstList<AnimationBlendDirectionalTrack>("cyclic", gAnimationBlendDirectionalTrackCyclicTable, 3, &AnimationBlendDirectionalTrack::SetCyclic);
					properties[5] = property;
					property = new fight::PropertyName<AnimationBlendDirectionalTrack>("animNeutral", &AnimationBlendDirectionalTrack::SetAnimNeutral);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animNeutralSyncFrame", &AnimationBlendDirectionalTrack::SetAnimNeutralSyncFrame);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animNeutralStartFrame", &AnimationBlendDirectionalTrack::SetAnimNeutralStartFrame);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animNeutralEndFrame", &AnimationBlendDirectionalTrack::SetAnimNeutralEndFrame);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animNeutralSpeed", &AnimationBlendDirectionalTrack::SetAnimNeutralSpeed);
					properties[10] = property;
					property = new fight::PropertyName<AnimationBlendDirectionalTrack>("animNorth", &AnimationBlendDirectionalTrack::SetAnimNorth);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animNorthSyncFrame", &AnimationBlendDirectionalTrack::SetAnimNorthSyncFrame);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animNorthStartFrame", &AnimationBlendDirectionalTrack::SetAnimNorthStartFrame);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animNorthEndFrame", &AnimationBlendDirectionalTrack::SetAnimNorthEndFrame);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animNorthSpeed", &AnimationBlendDirectionalTrack::SetAnimNorthSpeed);
					properties[15] = property;
					property = new fight::PropertyBitfieldConstList<AnimationBlendDirectionalTrack>("animNorthAllowedTransitions", gAnimationBlendDirectionalTrackAnimNorthAllowedTransitionsTable, gAnimationBlendDirectionalTrackAnimNorthAllowedTransitionsCount, &AnimationBlendDirectionalTrack::SetAnimNorthAllowedTransitions);
					properties[16] = property;
					property = new fight::PropertyName<AnimationBlendDirectionalTrack>("animEast", &AnimationBlendDirectionalTrack::SetAnimEast);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animEastSyncFrame", &AnimationBlendDirectionalTrack::SetAnimEastSyncFrame);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animEastStartFrame", &AnimationBlendDirectionalTrack::SetAnimEastStartFrame);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animEastEndFrame", &AnimationBlendDirectionalTrack::SetAnimEastEndFrame);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animEastSpeed", &AnimationBlendDirectionalTrack::SetAnimEastSpeed);
					properties[21] = property;
					property = new fight::PropertyBitfieldConstList<AnimationBlendDirectionalTrack>("animEastAllowedTransitions", gAnimationBlendDirectionalTrackAnimNorthAllowedTransitionsTable, gAnimationBlendDirectionalTrackAnimNorthAllowedTransitionsCount, &AnimationBlendDirectionalTrack::SetAnimEastAllowedTransitions);
					properties[22] = property;
					property = new fight::PropertyName<AnimationBlendDirectionalTrack>("animSouth", &AnimationBlendDirectionalTrack::SetAnimSouth);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animSouthSyncFrame", &AnimationBlendDirectionalTrack::SetAnimSouthSyncFrame);
					properties[24] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animSouthStartFrame", &AnimationBlendDirectionalTrack::SetAnimSouthStartFrame);
					properties[25] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animSouthEndFrame", &AnimationBlendDirectionalTrack::SetAnimSouthEndFrame);
					properties[26] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animSouthSpeed", &AnimationBlendDirectionalTrack::SetAnimSouthSpeed);
					properties[27] = property;
					property = new fight::PropertyBitfieldConstList<AnimationBlendDirectionalTrack>("animSouthAllowedTransitions", gAnimationBlendDirectionalTrackAnimNorthAllowedTransitionsTable, gAnimationBlendDirectionalTrackAnimNorthAllowedTransitionsCount, &AnimationBlendDirectionalTrack::SetAnimSouthAllowedTransitions);
					properties[28] = property;
					property = new fight::PropertyName<AnimationBlendDirectionalTrack>("animWest", &AnimationBlendDirectionalTrack::SetAnimWest);
					properties[29] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animWestSyncFrame", &AnimationBlendDirectionalTrack::SetAnimWestSyncFrame);
					properties[30] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animWestStartFrame", &AnimationBlendDirectionalTrack::SetAnimWestStartFrame);
					properties[31] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animWestEndFrame", &AnimationBlendDirectionalTrack::SetAnimWestEndFrame);
					properties[32] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("animWestSpeed", &AnimationBlendDirectionalTrack::SetAnimWestSpeed);
					properties[33] = property;
					property = new fight::PropertyBitfieldConstList<AnimationBlendDirectionalTrack>("animWestAllowedTransitions", gAnimationBlendDirectionalTrackAnimNorthAllowedTransitionsTable, gAnimationBlendDirectionalTrackAnimNorthAllowedTransitionsCount, &AnimationBlendDirectionalTrack::SetAnimWestAllowedTransitions);
					properties[34] = property;
					property = new fight::PropertyNameList<AnimationBlendDirectionalTrack>("partition", &AnimationBlendDirectionalTrack::SetPartition);
					properties[35] = property;
					property = new fight::PropertyIntConstRange<AnimationBlendDirectionalTrack>("priority", &AnimationBlendDirectionalTrack::SetPriority);
					properties[36] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("blendInTime", &AnimationBlendDirectionalTrack::SetBlendInTime);
					properties[37] = property;
					property = new fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>("blendOutTime", &AnimationBlendDirectionalTrack::SetBlendOutTime);
					properties[38] = property;
					fight::RegisterPropertyList(properties, &gAnimationBlendDirectionalTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1013E760
			fight::TrackFactory* CreateAnimationBlendDirectionalTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AnimationBlendDirectionalTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1013E840
			void RegisterAnimationBlendDirectionalTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AnimationBlendDirectionalTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<AnimationBlendVerticalAimTrack>;
			template class fight::PropertyEnumConstList<AnimationBlendVerticalAimTrack>;
			template class fight::PropertyName<AnimationBlendVerticalAimTrack>;
			template class fight::PropertyNameList<AnimationBlendVerticalAimTrack>;
			template class fight::PropertyIntConstRange<AnimationBlendVerticalAimTrack>;
			template class fight::TrackFactoryTemplate<AnimationBlendVerticalAimTrack>;
			template class fight::TrackFactoryCasterTemplate<AnimationBlendVerticalAimTrack>;
			template class fight::PropertyFloatConstRange<AnimationBlendSimpleTrack>;
			template class fight::PropertyName<AnimationBlendSimpleTrack>;
			template class fight::PropertyEnumConstList<AnimationBlendSimpleTrack>;
			template class fight::PropertyNameList<AnimationBlendSimpleTrack>;
			template class fight::PropertyIntConstRange<AnimationBlendSimpleTrack>;
			template class fight::TrackFactoryTemplate<AnimationBlendSimpleTrack>;
			template class fight::TrackFactoryCasterTemplate<AnimationBlendSimpleTrack>;
			template class fight::PropertyFloatConstRange<AnimationBlendVerticalAimStrafeTrack>;
			template class fight::PropertyName<AnimationBlendVerticalAimStrafeTrack>;
			template class fight::PropertyEnumConstList<AnimationBlendVerticalAimStrafeTrack>;
			template class fight::PropertyNameList<AnimationBlendVerticalAimStrafeTrack>;
			template class fight::PropertyVector<AnimationBlendVerticalAimStrafeTrack>;
			template class fight::PropertyIntConstRange<AnimationBlendVerticalAimStrafeTrack>;
			template class fight::TrackFactoryTemplate<AnimationBlendVerticalAimStrafeTrack>;
			template class fight::TrackFactoryCasterTemplate<AnimationBlendVerticalAimStrafeTrack>;
			template class fight::PropertyFloatConstRange<AnimationBlendDirectionalTrack>;
			template class fight::PropertyEnumConstList<AnimationBlendDirectionalTrack>;
			template class fight::PropertyName<AnimationBlendDirectionalTrack>;
			template class fight::PropertyBitfieldConstList<AnimationBlendDirectionalTrack>;
			template class fight::PropertyNameList<AnimationBlendDirectionalTrack>;
			template class fight::PropertyIntConstRange<AnimationBlendDirectionalTrack>;
			template class fight::TrackFactoryTemplate<AnimationBlendDirectionalTrack>;
			template class fight::TrackFactoryCasterTemplate<AnimationBlendDirectionalTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1013DDA0
// FUNCTION: ENGINE 0x1013DDB0
// FUNCTION: ENGINE 0x1013DDE0
// FUNCTION: ENGINE 0x1013DDF0
// FUNCTION: ENGINE 0x1013DE20
// FUNCTION: ENGINE 0x1013DE30
// FUNCTION: ENGINE 0x1013DE60
// FUNCTION: ENGINE 0x1013DE70
// FUNCTION: ENGINE 0x1013DEA0
// FUNCTION: ENGINE 0x1013DED0
// FUNCTION: ENGINE 0x1013DF00
// FUNCTION: ENGINE 0x1013DF30
// FUNCTION: ENGINE 0x1013DF60
// FUNCTION: ENGINE 0x1013DF90
// FUNCTION: ENGINE 0x1013DFC0
// FUNCTION: ENGINE 0x1013DFD0
// FUNCTION: ENGINE 0x1013E010
// FUNCTION: ENGINE 0x1013E020
// FUNCTION: ENGINE 0x1013E050
// FUNCTION: ENGINE 0x1013E070
// FUNCTION: ENGINE 0x1013E080
// FUNCTION: ENGINE 0x1013E0C0
// FUNCTION: ENGINE 0x1013E0E0
// FUNCTION: ENGINE 0x1013E0F0
// FUNCTION: ENGINE 0x1013E120
// FUNCTION: ENGINE 0x1013E150
// FUNCTION: ENGINE 0x1013E160
// FUNCTION: ENGINE 0x1013E1A0
// FUNCTION: ENGINE 0x1013E1B0
// FUNCTION: ENGINE 0x1013E1E0
// FUNCTION: ENGINE 0x1013E200
// FUNCTION: ENGINE 0x1013E210
// FUNCTION: ENGINE 0x1013E240
// FUNCTION: ENGINE 0x1013E260
// FUNCTION: ENGINE 0x1013E270
// FUNCTION: ENGINE 0x1013E2A0
// FUNCTION: ENGINE 0x1013E2D0
// FUNCTION: ENGINE 0x1013E2E0
// FUNCTION: ENGINE 0x1013E320
// FUNCTION: ENGINE 0x1013E330
// FUNCTION: ENGINE 0x1013E360
// FUNCTION: ENGINE 0x1013E380
// FUNCTION: ENGINE 0x1013E390
// FUNCTION: ENGINE 0x1013E3D0
// FUNCTION: ENGINE 0x1013E3F0
// FUNCTION: ENGINE 0x1013E400
// FUNCTION: ENGINE 0x1013E430
// FUNCTION: ENGINE 0x1013E450
// FUNCTION: ENGINE 0x1013E460
// FUNCTION: ENGINE 0x1013E490
// FUNCTION: ENGINE 0x1013E4C0
// FUNCTION: ENGINE 0x1013E4D0
// FUNCTION: ENGINE 0x1013E510
// FUNCTION: ENGINE 0x1013E520
// FUNCTION: ENGINE 0x1013E550
// FUNCTION: ENGINE 0x1013E570
// FUNCTION: ENGINE 0x1013E580
// FUNCTION: ENGINE 0x1013E5D0
// FUNCTION: ENGINE 0x1013E5E0
// FUNCTION: ENGINE 0x1013E600
// FUNCTION: ENGINE 0x1013E610
// FUNCTION: ENGINE 0x1013E670
// FUNCTION: ENGINE 0x1013E6A0
// FUNCTION: ENGINE 0x1013E6C0
// FUNCTION: ENGINE 0x1013E870
// FUNCTION: ENGINE 0x1013E8C0
// FUNCTION: ENGINE 0x1013E8E0
// FUNCTION: ENGINE 0x1013E920
// FUNCTION: ENGINE 0x1013E940
// FUNCTION: ENGINE 0x1013E950
// FUNCTION: ENGINE 0x1013E980
// FUNCTION: ENGINE 0x1013E9A0
// FUNCTION: ENGINE 0x1013E9D0
// FUNCTION: ENGINE 0x1013E9F0
// FUNCTION: ENGINE 0x1013EA00
// FUNCTION: ENGINE 0x1013EA30
// FUNCTION: ENGINE 0x1013EA50
// FUNCTION: ENGINE 0x1013EA80
// FUNCTION: ENGINE 0x1013EAA0
// FUNCTION: ENGINE 0x1013EAB0
// FUNCTION: ENGINE 0x1013EAE0
// FUNCTION: ENGINE 0x1013EB00
// FUNCTION: ENGINE 0x1013EB30
// FUNCTION: ENGINE 0x1013EB50
// FUNCTION: ENGINE 0x10140D10
// FUNCTION: ENGINE 0x10140D40
// FUNCTION: ENGINE 0x10140D70
// FUNCTION: ENGINE 0x10140DA0
// FUNCTION: ENGINE 0x10140DC0
// FUNCTION: ENGINE 0x10140DF0
// FUNCTION: ENGINE 0x10140E20
// FUNCTION: ENGINE 0x10140E50
// FUNCTION: ENGINE 0x10140E80
// FUNCTION: ENGINE 0x10140ED0
// FUNCTION: ENGINE 0x10140F20
// FUNCTION: ENGINE 0x10140F70
