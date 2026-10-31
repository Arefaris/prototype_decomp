// Fight items of the motion group: HeliLocoTrack (unit 0x10179BB0 - 0x1017A690; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_heliloco.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gHeliLocoTrackProperties;  // 0x112546E8

			// FUNCTION: ENGINE 0x10179BB0
			bool HeliLocoTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10179BD0
			bool HeliLocoTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10179BF0
			bool HeliLocoTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10179C10
			bool HeliLocoTrack::SetVelocity(float newValue)
			{
				velocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10179C30
			bool HeliLocoTrack::SetExtraFallingVelocity(float newValue)
			{
				extraFallingVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10179C50
			bool HeliLocoTrack::SetTurnAcceleration(float newValue)
			{
				turnAcceleration = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10179C70
			bool HeliLocoTrack::SetTurnVelocity(float newValue)
			{
				turnVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10179C90
			bool HeliLocoTrack::SetMinimum(const math::Vector& newValue)
			{
				minimum.x = newValue.x;
				minimum.y = newValue.y;
				minimum.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10179CB0
			bool HeliLocoTrack::SetMaximum(const math::Vector& newValue)
			{
				maximum.x = newValue.x;
				maximum.y = newValue.y;
				maximum.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10179CD0
			bool HeliLocoTrack::SetTiltMax(float newValue)
			{
				tiltMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10179CF0
			bool HeliLocoTrack::SetTiltDampingConstant(float newValue)
			{
				tiltDampingConstant = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10179D10
			bool HeliLocoTrack::SetTiltSpringConstant(float newValue)
			{
				tiltSpringConstant = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10179D30
			bool HeliLocoTrack::SetVelocityToAngleFactor(float newValue)
			{
				velocityToAngleFactor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10179D50
			bool HeliLocoTrack::SetMaxWashEffectHeight(float newValue)
			{
				maxWashEffectHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10179D70
			bool HeliLocoTrack::SetWashEffectFrequency(float newValue)
			{
				washEffectFrequency = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10179D90
			bool HeliLocoTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10179DA0
			bool HeliLocoTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10179DC0
			bool HeliLocoTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10179DE0
			fight::Property* HeliLocoTrack::GetProperty(int index)
			{
				return gHeliLocoTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10179E00
			void HeliLocoTrack::ClearProperties()
			{
				fight::FreePropertyList(&gHeliLocoTrackProperties);
			}

			// FUNCTION: ENGINE 0x10179E10
			HeliLocoTrack::HeliLocoTrack() : maximum(0.0f, 0.0f, 0.0f), minimum(0.0f, 0.0f, 0.0f), acceleration(1e+02f), blendInTime(0.1f), blendOutTime(0.1f), extraFallingVelocity(5.0f), maxWashEffectHeight(0.0f), tiltDampingConstant(1.5f), tiltMax(0.5235988f), tiltSpringConstant(3.0f), timeBegin(0.0f), timeEnd(-1.0f), turnAcceleration(0.0f), turnVelocity(0.0f), velocity(25.0f), velocityToAngleFactor(0.03f), washEffectFrequency(0.1f), priority(0)
			{
			}

			// FUNCTION: ENGINE 0x10179F10
			float HeliLocoTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10179F20
			float HeliLocoTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10179F30
			HeliLocoTrack::~HeliLocoTrack()
			{
			}

			// FUNCTION: ENGINE 0x1017A110
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HeliLocoTrack::RegisterProperties()
			{
				if (gHeliLocoTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("timeBegin", &HeliLocoTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("timeEnd", &HeliLocoTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("acceleration", &HeliLocoTrack::SetAcceleration);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("velocity", &HeliLocoTrack::SetVelocity);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("extraFallingVelocity", &HeliLocoTrack::SetExtraFallingVelocity);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("turnAcceleration", &HeliLocoTrack::SetTurnAcceleration);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("turnVelocity", &HeliLocoTrack::SetTurnVelocity);
					properties[6] = property;
					property = new fight::PropertyVector<HeliLocoTrack>("minimum", &HeliLocoTrack::SetMinimum);
					properties[7] = property;
					property = new fight::PropertyVector<HeliLocoTrack>("maximum", &HeliLocoTrack::SetMaximum);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("tiltMax", &HeliLocoTrack::SetTiltMax);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("tiltDampingConstant", &HeliLocoTrack::SetTiltDampingConstant);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("tiltSpringConstant", &HeliLocoTrack::SetTiltSpringConstant);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("velocityToAngleFactor", &HeliLocoTrack::SetVelocityToAngleFactor);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("maxWashEffectHeight", &HeliLocoTrack::SetMaxWashEffectHeight);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("washEffectFrequency", &HeliLocoTrack::SetWashEffectFrequency);
					properties[14] = property;
					property = new fight::PropertyIntConstRange<HeliLocoTrack>("priority", &HeliLocoTrack::SetPriority);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("blendInTime", &HeliLocoTrack::SetBlendInTime);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<HeliLocoTrack>("blendOutTime", &HeliLocoTrack::SetBlendOutTime);
					properties[17] = property;
					fight::RegisterPropertyList(properties, &gHeliLocoTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1017A0E0
			fight::TrackFactory* CreateHeliLocoTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HeliLocoTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1017A5C0
			void RegisterHeliLocoTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HeliLocoTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<HeliLocoTrack>;
			template class fight::PropertyVector<HeliLocoTrack>;
			template class fight::PropertyIntConstRange<HeliLocoTrack>;
			template class fight::TrackFactoryTemplate<HeliLocoTrack>;
			template class fight::TrackFactoryCasterTemplate<HeliLocoTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10179F40
// FUNCTION: ENGINE 0x10179F70
// FUNCTION: ENGINE 0x10179F80
// FUNCTION: ENGINE 0x10179FB0
// FUNCTION: ENGINE 0x10179FE0
// FUNCTION: ENGINE 0x1017A010
// FUNCTION: ENGINE 0x1017A020
// FUNCTION: ENGINE 0x1017A050
// FUNCTION: ENGINE 0x1017A070
// FUNCTION: ENGINE 0x1017A080
// FUNCTION: ENGINE 0x1017A0B0
// FUNCTION: ENGINE 0x1017A0D0
// FUNCTION: ENGINE 0x1017A5F0
// FUNCTION: ENGINE 0x1017A620
// FUNCTION: ENGINE 0x1017A640
