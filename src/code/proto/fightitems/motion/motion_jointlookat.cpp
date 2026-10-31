// Fight items of the motion group: JointLookAtCondition, JointLookAtTrack (unit 0x101827B0 - 0x10183A80; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_jointlookat.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gJointLookAtConditionProperties;  // 0x11254788

			// FUNCTION: ENGINE 0x10182A90
			bool JointLookAtCondition::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101827B0
			bool JointLookAtCondition::SetHeading(const math::Vector& newValue)
			{
				heading.x = newValue.x;
				heading.y = newValue.y;
				heading.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101827D0
			bool JointLookAtCondition::SetPrimaryRotationAxis(const math::Vector& newValue)
			{
				primaryRotationAxis.x = newValue.x;
				primaryRotationAxis.y = newValue.y;
				primaryRotationAxis.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101827F0
			bool JointLookAtCondition::SetPrimaryAngleMin(float newValue)
			{
				primaryAngleMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10182810
			bool JointLookAtCondition::SetPrimaryAngleMax(float newValue)
			{
				primaryAngleMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10182A30
			fight::Property* JointLookAtCondition::GetProperty(int index)
			{
				return gJointLookAtConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10182A50
			void JointLookAtCondition::ClearProperties()
			{
				fight::FreePropertyList(&gJointLookAtConditionProperties);
			}

			// FUNCTION: ENGINE 0x10182AF0
			JointLookAtCondition::JointLookAtCondition() : fight::Condition(0), joint("Character_Root", 1), heading(0.0f, 0.0f, -1.0f), primaryRotationAxis(0.0f, 1.0f, 0.0f), primaryAngleMax(3.1415927f), primaryAngleMin(-3.1415927f)
			{
			}

			// FUNCTION: ENGINE 0x10182B80
			JointLookAtCondition::~JointLookAtCondition()
			{
			}

			// FUNCTION: ENGINE 0x10183230
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void JointLookAtCondition::RegisterProperties()
			{
				if (gJointLookAtConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<JointLookAtCondition>("joint", &JointLookAtCondition::SetJoint);
					properties[0] = property;
					property = new fight::PropertyVector<JointLookAtCondition>("heading", &JointLookAtCondition::SetHeading);
					properties[1] = property;
					property = new fight::PropertyVector<JointLookAtCondition>("primaryRotationAxis", &JointLookAtCondition::SetPrimaryRotationAxis);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<JointLookAtCondition>("primaryAngleMin", &JointLookAtCondition::SetPrimaryAngleMin);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<JointLookAtCondition>("primaryAngleMax", &JointLookAtCondition::SetPrimaryAngleMax);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gJointLookAtConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101830B0
			fight::ConditionFactory* CreateJointLookAtConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<JointLookAtCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10183110
			void RegisterJointLookAtConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<JointLookAtCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gJointLookAtTrackProperties;  // 0x1125478C

			// FUNCTION: ENGINE 0x10182830
			bool JointLookAtTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10182850
			bool JointLookAtTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10182AB0
			bool JointLookAtTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10182870
			bool JointLookAtTrack::SetHeading(const math::Vector& newValue)
			{
				heading.x = newValue.x;
				heading.y = newValue.y;
				heading.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10182890
			bool JointLookAtTrack::SetPrimaryRotationAxis(const math::Vector& newValue)
			{
				primaryRotationAxis.x = newValue.x;
				primaryRotationAxis.y = newValue.y;
				primaryRotationAxis.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101828B0
			bool JointLookAtTrack::SetPrimaryTurnRate(float newValue)
			{
				primaryTurnRate = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101828D0
			bool JointLookAtTrack::SetPrimaryAngleMin(float newValue)
			{
				primaryAngleMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101828F0
			bool JointLookAtTrack::SetPrimaryAngleMax(float newValue)
			{
				primaryAngleMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10182910
			bool JointLookAtTrack::SetSecondaryTurnRate(float newValue)
			{
				secondaryTurnRate = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10182930
			bool JointLookAtTrack::SetSecondaryAngleMin(float newValue)
			{
				secondaryAngleMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10182950
			bool JointLookAtTrack::SetSecondaryAngleMax(float newValue)
			{
				secondaryAngleMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10182970
			bool JointLookAtTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10182980
			bool JointLookAtTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101829A0
			bool JointLookAtTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10182AD0
			bool JointLookAtTrack::SetUseGrabSlot(const fight::Name& newValue)
			{
				useGrabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101829C0
			bool JointLookAtTrack::SetWhere(int newValue)
			{
				where = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101829D0
			bool JointLookAtTrack::SetUseAutoTarget(bool newValue)
			{
				useAutoTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101829E0
			bool JointLookAtTrack::SetUseIntentionWhenNoTarget(bool newValue)
			{
				useIntentionWhenNoTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101829F0
			bool JointLookAtTrack::SetUseFreeAimWhenNoTarget(bool newValue)
			{
				useFreeAimWhenNoTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10182A00
			bool JointLookAtTrack::SetUseLocalAngelsInIntention(bool newValue)
			{
				useLocalAngelsInIntention = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10182A10
			bool JointLookAtTrack::SetTargetOffset(const math::Vector& newValue)
			{
				targetOffset.x = newValue.x;
				targetOffset.y = newValue.y;
				targetOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10182A60
			fight::Property* JointLookAtTrack::GetProperty(int index)
			{
				return gJointLookAtTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10182A80
			void JointLookAtTrack::ClearProperties()
			{
				fight::FreePropertyList(&gJointLookAtTrackProperties);
			}

			// FUNCTION: ENGINE 0x10182B90
			JointLookAtTrack::JointLookAtTrack() : heading(0.0f, 0.0f, -1.0f), primaryRotationAxis(0.0f, 1.0f, 0.0f), targetOffset(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), primaryAngleMax(3.1415927f), primaryAngleMin(-3.1415927f), primaryTurnRate(-0.017453292f), secondaryAngleMax(3.1415927f), secondaryAngleMin(-3.1415927f), secondaryTurnRate(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(-10), where(0), useAutoTarget(true), useFreeAimWhenNoTarget(false), useIntentionWhenNoTarget(true), useLocalAngelsInIntention(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10182C90
			float JointLookAtTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10182CA0
			float JointLookAtTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10182CB0
			JointLookAtTrack::~JointLookAtTrack()
			{
			}

			// FUNCTION: ENGINE 0x101833C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void JointLookAtTrack::RegisterProperties()
			{
				if (gJointLookAtTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<JointLookAtTrack>("timeBegin", &JointLookAtTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<JointLookAtTrack>("timeEnd", &JointLookAtTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<JointLookAtTrack>("joint", &JointLookAtTrack::SetJoint);
					properties[2] = property;
					property = new fight::PropertyVector<JointLookAtTrack>("heading", &JointLookAtTrack::SetHeading);
					properties[3] = property;
					property = new fight::PropertyVector<JointLookAtTrack>("primaryRotationAxis", &JointLookAtTrack::SetPrimaryRotationAxis);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<JointLookAtTrack>("primaryTurnRate", &JointLookAtTrack::SetPrimaryTurnRate);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<JointLookAtTrack>("primaryAngleMin", &JointLookAtTrack::SetPrimaryAngleMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<JointLookAtTrack>("primaryAngleMax", &JointLookAtTrack::SetPrimaryAngleMax);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<JointLookAtTrack>("secondaryTurnRate", &JointLookAtTrack::SetSecondaryTurnRate);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<JointLookAtTrack>("secondaryAngleMin", &JointLookAtTrack::SetSecondaryAngleMin);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<JointLookAtTrack>("secondaryAngleMax", &JointLookAtTrack::SetSecondaryAngleMax);
					properties[10] = property;
					property = new fight::PropertyIntConstRange<JointLookAtTrack>("priority", &JointLookAtTrack::SetPriority);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<JointLookAtTrack>("blendInTime", &JointLookAtTrack::SetBlendInTime);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<JointLookAtTrack>("blendOutTime", &JointLookAtTrack::SetBlendOutTime);
					properties[13] = property;
					property = new fight::PropertyNameList<JointLookAtTrack>("useGrabSlot", &JointLookAtTrack::SetUseGrabSlot);
					properties[14] = property;
					property = new fight::PropertyEnumConstList<JointLookAtTrack>("where", gJointLookAtTrackWhereTable, gJointLookAtTrackWhereCount, &JointLookAtTrack::SetWhere);
					properties[15] = property;
					property = new fight::PropertyBool<JointLookAtTrack>("useAutoTarget", &JointLookAtTrack::SetUseAutoTarget);
					properties[16] = property;
					property = new fight::PropertyBool<JointLookAtTrack>("useIntentionWhenNoTarget", &JointLookAtTrack::SetUseIntentionWhenNoTarget);
					properties[17] = property;
					property = new fight::PropertyBool<JointLookAtTrack>("useFreeAimWhenNoTarget", &JointLookAtTrack::SetUseFreeAimWhenNoTarget);
					properties[18] = property;
					property = new fight::PropertyBool<JointLookAtTrack>("useLocalAngelsInIntention", &JointLookAtTrack::SetUseLocalAngelsInIntention);
					properties[19] = property;
					property = new fight::PropertyVector<JointLookAtTrack>("targetOffset", &JointLookAtTrack::SetTargetOffset);
					properties[20] = property;
					fight::RegisterPropertyList(properties, &gJointLookAtTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101830E0
			fight::TrackFactory* CreateJointLookAtTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<JointLookAtTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10183140
			void RegisterJointLookAtTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<JointLookAtTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyNameList<JointLookAtCondition>;
			template class fight::PropertyVector<JointLookAtCondition>;
			template class fight::PropertyFloatConstRange<JointLookAtCondition>;
			template class fight::ConditionFactoryTemplate<JointLookAtCondition>;
			template class fight::ConditionFactoryCasterTemplate<JointLookAtCondition>;
			template class fight::PropertyFloatConstRange<JointLookAtTrack>;
			template class fight::PropertyNameList<JointLookAtTrack>;
			template class fight::PropertyVector<JointLookAtTrack>;
			template class fight::PropertyIntConstRange<JointLookAtTrack>;
			template class fight::PropertyEnumConstList<JointLookAtTrack>;
			template class fight::PropertyBool<JointLookAtTrack>;
			template class fight::TrackFactoryTemplate<JointLookAtTrack>;
			template class fight::TrackFactoryCasterTemplate<JointLookAtTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10182CC0
// FUNCTION: ENGINE 0x10182CD0
// FUNCTION: ENGINE 0x10182D00
// FUNCTION: ENGINE 0x10182D10
// FUNCTION: ENGINE 0x10182D40
// FUNCTION: ENGINE 0x10182D70
// FUNCTION: ENGINE 0x10182DA0
// FUNCTION: ENGINE 0x10182DD0
// FUNCTION: ENGINE 0x10182DF0
// FUNCTION: ENGINE 0x10182E00
// FUNCTION: ENGINE 0x10182E30
// FUNCTION: ENGINE 0x10182E60
// FUNCTION: ENGINE 0x10182E70
// FUNCTION: ENGINE 0x10182EA0
// FUNCTION: ENGINE 0x10182ED0
// FUNCTION: ENGINE 0x10182EE0
// FUNCTION: ENGINE 0x10182F10
// FUNCTION: ENGINE 0x10182F30
// FUNCTION: ENGINE 0x10182F40
// FUNCTION: ENGINE 0x10182F70
// FUNCTION: ENGINE 0x10182F90
// FUNCTION: ENGINE 0x10182FA0
// FUNCTION: ENGINE 0x10182FE0
// FUNCTION: ENGINE 0x10182FF0
// FUNCTION: ENGINE 0x10183020
// FUNCTION: ENGINE 0x10183040
// FUNCTION: ENGINE 0x10183050
// FUNCTION: ENGINE 0x10183080
// FUNCTION: ENGINE 0x101830A0
// FUNCTION: ENGINE 0x10183170
// FUNCTION: ENGINE 0x101831A0
// FUNCTION: ENGINE 0x101831C0
// FUNCTION: ENGINE 0x101831D0
// FUNCTION: ENGINE 0x10183200
// FUNCTION: ENGINE 0x10183220
// FUNCTION: ENGINE 0x10183940
// FUNCTION: ENGINE 0x10183970
// FUNCTION: ENGINE 0x10183990
// FUNCTION: ENGINE 0x101839C0
// FUNCTION: ENGINE 0x101839E0
// FUNCTION: ENGINE 0x10183A30
