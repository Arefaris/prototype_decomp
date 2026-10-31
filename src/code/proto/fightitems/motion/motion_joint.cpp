// Fight items of the motion group: JointTrack (unit 0x10181890 - 0x10182180; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_joint.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gJointTrackProperties;  // 0x11254780

			// FUNCTION: ENGINE 0x10181890
			bool JointTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101818B0
			bool JointTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10181A00
			bool JointTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101818D0
			bool JointTrack::SetUseRestPose(bool newValue)
			{
				useRestPose = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101818E0
			bool JointTrack::SetHasTranslation(bool newValue)
			{
				hasTranslation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101818F0
			bool JointTrack::SetTranslation(const math::Vector& newValue)
			{
				translation.x = newValue.x;
				translation.y = newValue.y;
				translation.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10181910
			bool JointTrack::SetHasRotation(bool newValue)
			{
				hasRotation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10181920
			bool JointTrack::SetRotation(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				rotation.x = scaled.x;
				rotation.y = scaled.y;
				rotation.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10181970
			bool JointTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10181980
			bool JointTrack::SetAutomaticBlendTimes(bool newValue)
			{
				automaticBlendTimes = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10181990
			bool JointTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101819B0
			bool JointTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101819D0
			fight::Property* JointTrack::GetProperty(int index)
			{
				return gJointTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101819F0
			void JointTrack::ClearProperties()
			{
				fight::FreePropertyList(&gJointTrackProperties);
			}

			// FUNCTION: ENGINE 0x10181A20
			JointTrack::JointTrack() : rotation(0.0f, 0.0f, 0.0f), translation(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(-5), automaticBlendTimes(false), hasRotation(false), hasTranslation(false), useRestPose(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10181AB0
			float JointTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10181AC0
			float JointTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10181AD0
			JointTrack::~JointTrack()
			{
			}

			// FUNCTION: ENGINE 0x10181DA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void JointTrack::RegisterProperties()
			{
				if (gJointTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<JointTrack>("timeBegin", &JointTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<JointTrack>("timeEnd", &JointTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<JointTrack>("joint", &JointTrack::SetJoint);
					properties[2] = property;
					property = new fight::PropertyBool<JointTrack>("useRestPose", &JointTrack::SetUseRestPose);
					properties[3] = property;
					property = new fight::PropertyBool<JointTrack>("hasTranslation", &JointTrack::SetHasTranslation);
					properties[4] = property;
					property = new fight::PropertyVector<JointTrack>("translation", &JointTrack::SetTranslation);
					properties[5] = property;
					property = new fight::PropertyBool<JointTrack>("hasRotation", &JointTrack::SetHasRotation);
					properties[6] = property;
					property = new fight::PropertyVector<JointTrack>("rotation", &JointTrack::SetRotation);
					properties[7] = property;
					property = new fight::PropertyIntConstRange<JointTrack>("priority", &JointTrack::SetPriority);
					properties[8] = property;
					property = new fight::PropertyBool<JointTrack>("automaticBlendTimes", &JointTrack::SetAutomaticBlendTimes);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<JointTrack>("blendInTime", &JointTrack::SetBlendInTime);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<JointTrack>("blendOutTime", &JointTrack::SetBlendOutTime);
					properties[11] = property;
					fight::RegisterPropertyList(properties, &gJointTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10181CE0
			fight::TrackFactory* CreateJointTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<JointTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10181D10
			void RegisterJointTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<JointTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<JointTrack>;
			template class fight::PropertyNameList<JointTrack>;
			template class fight::PropertyBool<JointTrack>;
			template class fight::PropertyVector<JointTrack>;
			template class fight::PropertyIntConstRange<JointTrack>;
			template class fight::TrackFactoryTemplate<JointTrack>;
			template class fight::TrackFactoryCasterTemplate<JointTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10181AE0
// FUNCTION: ENGINE 0x10181AF0
// FUNCTION: ENGINE 0x10181B20
// FUNCTION: ENGINE 0x10181B50
// FUNCTION: ENGINE 0x10181B80
// FUNCTION: ENGINE 0x10181BB0
// FUNCTION: ENGINE 0x10181BC0
// FUNCTION: ENGINE 0x10181BF0
// FUNCTION: ENGINE 0x10181C10
// FUNCTION: ENGINE 0x10181C20
// FUNCTION: ENGINE 0x10181C50
// FUNCTION: ENGINE 0x10181C70
// FUNCTION: ENGINE 0x10181C80
// FUNCTION: ENGINE 0x10181CB0
// FUNCTION: ENGINE 0x10181CD0
// FUNCTION: ENGINE 0x10181D40
// FUNCTION: ENGINE 0x10181D70
// FUNCTION: ENGINE 0x10181D90
// FUNCTION: ENGINE 0x101820E0
// FUNCTION: ENGINE 0x10182110
// FUNCTION: ENGINE 0x10182130
