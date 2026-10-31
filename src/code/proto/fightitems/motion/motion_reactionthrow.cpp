// Fight items of the motion group: ReactionThrowSpinAngleCondition, ReactionThrowTrack (unit 0x101A8330 - 0x101A9500; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_reactionthrow.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gReactionThrowSpinAngleConditionProperties;  // 0x11254A14

			// FUNCTION: ENGINE 0x101A8330
			bool ReactionThrowSpinAngleCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8350
			bool ReactionThrowSpinAngleCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8600
			fight::Property* ReactionThrowSpinAngleCondition::GetProperty(int index)
			{
				return gReactionThrowSpinAngleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101A8620
			void ReactionThrowSpinAngleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gReactionThrowSpinAngleConditionProperties);
			}

			// FUNCTION: ENGINE 0x101A8630
			ReactionThrowSpinAngleCondition::ReactionThrowSpinAngleCondition() : fight::Condition(0), angle(0.0f), arc(3.1415927f)
			{
			}

			// FUNCTION: ENGINE 0x101A8670
			ReactionThrowSpinAngleCondition::~ReactionThrowSpinAngleCondition()
			{
			}

			// FUNCTION: ENGINE 0x101A8C60
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionThrowSpinAngleCondition::RegisterProperties()
			{
				if (gReactionThrowSpinAngleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionThrowSpinAngleCondition>("angle", &ReactionThrowSpinAngleCondition::SetAngle);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionThrowSpinAngleCondition>("arc", &ReactionThrowSpinAngleCondition::SetArc);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gReactionThrowSpinAngleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A8C00
			fight::ConditionFactory* CreateReactionThrowSpinAngleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionThrowSpinAngleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A8D40
			void RegisterReactionThrowSpinAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ReactionThrowSpinAngleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gReactionThrowTrackProperties;  // 0x11254A18

			// FUNCTION: ENGINE 0x101A8370
			bool ReactionThrowTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8390
			bool ReactionThrowTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A83B0
			bool ReactionThrowTrack::SetDamageMin(float newValue)
			{
				damageMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A83D0
			bool ReactionThrowTrack::SetDamageMax(float newValue)
			{
				damageMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A83F0
			bool ReactionThrowTrack::SetSpinAxisX(const math::Vector& newValue)
			{
				spinAxisX.x = newValue.x;
				spinAxisX.y = newValue.y;
				spinAxisX.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8410
			bool ReactionThrowTrack::SetSpinAxisY(const math::Vector& newValue)
			{
				spinAxisY.x = newValue.x;
				spinAxisY.y = newValue.y;
				spinAxisY.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8430
			bool ReactionThrowTrack::SetSelfDamageScale(float newValue)
			{
				selfDamageScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8450
			bool ReactionThrowTrack::SetUsePuppet(bool newValue)
			{
				usePuppet = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8470
			bool ReactionThrowTrack::SetOrientOffset(float newValue)
			{
				orientOffset = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8490
			bool ReactionThrowTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A84B0
			bool ReactionThrowTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A84D0
			bool ReactionThrowTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A84F0
			bool ReactionThrowTrack::SetPhysicalVelocityCheckDelay(float newValue)
			{
				physicalVelocityCheckDelay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8510
			bool ReactionThrowTrack::SetStopAtVelocityRatio(float newValue)
			{
				stopAtVelocityRatio = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A86B0
			bool ReactionThrowTrack::SetThreatName(const fight::Name& newValue)
			{
				threatName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8530
			bool ReactionThrowTrack::SetThreatRadiusScale(float newValue)
			{
				threatRadiusScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8550
			bool ReactionThrowTrack::SetThreatProjectedDist(float newValue)
			{
				threatProjectedDist = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8570
			fight::BranchHolder* ReactionThrowTrack::SetOnCollision()
			{
				return &onCollision;
			}

			// FUNCTION: ENGINE 0x101A8580
			bool ReactionThrowTrack::SetCollisionInterruptPriority(int newValue)
			{
				collisionInterruptPriority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A85A0
			bool ReactionThrowTrack::SetCollisionReactionDelay(float newValue)
			{
				collisionReactionDelay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A85C0
			bool ReactionThrowTrack::SetMaxHitEffects(int newValue)
			{
				maxHitEffects = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A85E0
			bool ReactionThrowTrack::SetOverrideTargetClass(int newValue)
			{
				overrideTargetClass = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A8680
			fight::Property* ReactionThrowTrack::GetProperty(int index)
			{
				return gReactionThrowTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101A86A0
			void ReactionThrowTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReactionThrowTrackProperties);
			}

			// FUNCTION: ENGINE 0x101A8700
			ReactionThrowTrack::ReactionThrowTrack() : onCollision(0), spinAxisX(0.0f, 0.0f, 0.0f), spinAxisY(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), collisionReactionDelay(0.0f), damageMax(0.0f), damageMin(0.0f), orientOffset(0.0f), physicalVelocityCheckDelay(0.5f), selfDamageScale(1.0f), stopAtVelocityRatio(0.5f), threatProjectedDist(1.0f), threatRadiusScale(1.0f), timeBegin(0.0f), timeEnd(-1.0f), collisionInterruptPriority(0), maxHitEffects(0), overrideTargetClass(12), priority(-5), usePuppet(true)
			{
			}

			// FUNCTION: ENGINE 0x101A8810
			float ReactionThrowTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101A8820
			float ReactionThrowTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101A8830
			ReactionThrowTrack::~ReactionThrowTrack()
			{
			}

			// FUNCTION: ENGINE 0x101A8E40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionThrowTrack::RegisterProperties()
			{
				if (gReactionThrowTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionThrowTrack>("timeBegin", &ReactionThrowTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionThrowTrack>("timeEnd", &ReactionThrowTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReactionThrowTrack>("damageMin", &ReactionThrowTrack::SetDamageMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ReactionThrowTrack>("damageMax", &ReactionThrowTrack::SetDamageMax);
					properties[3] = property;
					property = new fight::PropertyVector<ReactionThrowTrack>("spinAxisX", &ReactionThrowTrack::SetSpinAxisX);
					properties[4] = property;
					property = new fight::PropertyVector<ReactionThrowTrack>("spinAxisY", &ReactionThrowTrack::SetSpinAxisY);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<ReactionThrowTrack>("selfDamageScale", &ReactionThrowTrack::SetSelfDamageScale);
					properties[6] = property;
					property = new fight::PropertyBool<ReactionThrowTrack>("usePuppet", &ReactionThrowTrack::SetUsePuppet);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<ReactionThrowTrack>("orientOffset", &ReactionThrowTrack::SetOrientOffset);
					properties[8] = property;
					property = new fight::PropertyIntConstRange<ReactionThrowTrack>("priority", &ReactionThrowTrack::SetPriority);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<ReactionThrowTrack>("blendInTime", &ReactionThrowTrack::SetBlendInTime);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<ReactionThrowTrack>("blendOutTime", &ReactionThrowTrack::SetBlendOutTime);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<ReactionThrowTrack>("physicalVelocityCheckDelay", &ReactionThrowTrack::SetPhysicalVelocityCheckDelay);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<ReactionThrowTrack>("stopAtVelocityRatio", &ReactionThrowTrack::SetStopAtVelocityRatio);
					properties[13] = property;
					property = new fight::PropertyName<ReactionThrowTrack>("threatName", &ReactionThrowTrack::SetThreatName);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<ReactionThrowTrack>("threatRadiusScale", &ReactionThrowTrack::SetThreatRadiusScale);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<ReactionThrowTrack>("threatProjectedDist", &ReactionThrowTrack::SetThreatProjectedDist);
					properties[16] = property;
					property = new fight::PropertyBranch<ReactionThrowTrack>("onCollision", &ReactionThrowTrack::SetOnCollision);
					properties[17] = property;
					property = new fight::PropertyIntConstRange<ReactionThrowTrack>("collisionInterruptPriority", &ReactionThrowTrack::SetCollisionInterruptPriority);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<ReactionThrowTrack>("collisionReactionDelay", &ReactionThrowTrack::SetCollisionReactionDelay);
					properties[19] = property;
					property = new fight::PropertyIntConstRange<ReactionThrowTrack>("maxHitEffects", &ReactionThrowTrack::SetMaxHitEffects);
					properties[20] = property;
					property = new fight::PropertyEnumConstList<ReactionThrowTrack>("overrideTargetClass", gAutoTargetTrackMinPriorityTargetClassTable, gAutoTargetTrackMinPriorityTargetClassCount, &ReactionThrowTrack::SetOverrideTargetClass);
					properties[21] = property;
					fight::RegisterPropertyList(properties, &gReactionThrowTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A8C30
			fight::TrackFactory* CreateReactionThrowTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionThrowTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A8D70
			void RegisterReactionThrowTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionThrowTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<ReactionThrowSpinAngleCondition>;
			template class fight::ConditionFactoryTemplate<ReactionThrowSpinAngleCondition>;
			template class fight::ConditionFactoryCasterTemplate<ReactionThrowSpinAngleCondition>;
			template class fight::PropertyFloatConstRange<ReactionThrowTrack>;
			template class fight::PropertyVector<ReactionThrowTrack>;
			template class fight::PropertyBool<ReactionThrowTrack>;
			template class fight::PropertyIntConstRange<ReactionThrowTrack>;
			template class fight::PropertyName<ReactionThrowTrack>;
			template class fight::PropertyBranch<ReactionThrowTrack>;
			template class fight::PropertyEnumConstList<ReactionThrowTrack>;
			template class fight::TrackFactoryTemplate<ReactionThrowTrack>;
			template class fight::TrackFactoryCasterTemplate<ReactionThrowTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101A86D0
// FUNCTION: ENGINE 0x101A8850
// FUNCTION: ENGINE 0x101A8860
// FUNCTION: ENGINE 0x101A8890
// FUNCTION: ENGINE 0x101A88A0
// FUNCTION: ENGINE 0x101A88D0
// FUNCTION: ENGINE 0x101A8900
// FUNCTION: ENGINE 0x101A8930
// FUNCTION: ENGINE 0x101A8960
// FUNCTION: ENGINE 0x101A8970
// FUNCTION: ENGINE 0x101A89A0
// FUNCTION: ENGINE 0x101A89D0
// FUNCTION: ENGINE 0x101A89E0
// FUNCTION: ENGINE 0x101A8A10
// FUNCTION: ENGINE 0x101A8A30
// FUNCTION: ENGINE 0x101A8A40
// FUNCTION: ENGINE 0x101A8A70
// FUNCTION: ENGINE 0x101A8A90
// FUNCTION: ENGINE 0x101A8AA0
// FUNCTION: ENGINE 0x101A8AD0
// FUNCTION: ENGINE 0x101A8AF0
// FUNCTION: ENGINE 0x101A8B00
// FUNCTION: ENGINE 0x101A8B30
// FUNCTION: ENGINE 0x101A8B50
// FUNCTION: ENGINE 0x101A8B90
// FUNCTION: ENGINE 0x101A8BA0
// FUNCTION: ENGINE 0x101A8BD0
// FUNCTION: ENGINE 0x101A8BF0
// FUNCTION: ENGINE 0x101A8DA0
// FUNCTION: ENGINE 0x101A8DD0
// FUNCTION: ENGINE 0x101A8DF0
// FUNCTION: ENGINE 0x101A8E20
// FUNCTION: ENGINE 0x101A9400
// FUNCTION: ENGINE 0x101A9450
// FUNCTION: ENGINE 0x101A9480
// FUNCTION: ENGINE 0x101A94B0
