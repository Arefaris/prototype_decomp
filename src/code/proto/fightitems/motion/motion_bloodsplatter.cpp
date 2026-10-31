// Fight items of the motion group: BloodSplatterTrack (unit 0x10143E60 - 0x10144950; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_bloodsplatter.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gBloodSplatterTrackProperties;  // 0x112542E8

			// FUNCTION: ENGINE 0x10143E60
			bool BloodSplatterTrack::SetTimeBegin(float value)
			{
				timeBegin = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10143E80
			bool BloodSplatterTrack::SetTimeEnd(float value)
			{
				timeEnd = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101440F0
			bool BloodSplatterTrack::SetShader(const fight::Name& value)
			{
				shader = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10143EA0
			bool BloodSplatterTrack::SetWait(float value)
			{
				wait = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10143EC0
			bool BloodSplatterTrack::SetDuration(float value)
			{
				duration = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10143EE0
			bool BloodSplatterTrack::SetFadeDuration(float value)
			{
				fadeDuration = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10143F00
			bool BloodSplatterTrack::SetWaitRand(float value)
			{
				waitRand = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10143F20
			bool BloodSplatterTrack::SetDurationRand(float value)
			{
				durationRand = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10143F40
			bool BloodSplatterTrack::SetFadeDurationRand(float value)
			{
				fadeDurationRand = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10143F60
			bool BloodSplatterTrack::SetPositionX(float value)
			{
				positionX = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10143F80
			bool BloodSplatterTrack::SetPositionY(float value)
			{
				positionY = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10143FA0
			bool BloodSplatterTrack::SetPositionXRand(float value)
			{
				positionXRand = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10143FC0
			bool BloodSplatterTrack::SetPositionYRand(float value)
			{
				positionYRand = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10143FE0
			bool BloodSplatterTrack::SetScaleX(float value)
			{
				scaleX = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10144000
			bool BloodSplatterTrack::SetScaleY(float value)
			{
				scaleY = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10144020
			bool BloodSplatterTrack::SetScaleXYRand(float value)
			{
				scaleXYRand = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10144040
			bool BloodSplatterTrack::SetScaleXRand(float value)
			{
				scaleXRand = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10144060
			bool BloodSplatterTrack::SetScaleYRand(float value)
			{
				scaleYRand = value;
				return true;
			}

			// FUNCTION: ENGINE 0x10144080
			bool BloodSplatterTrack::SetAngle(float value)
			{
				angle = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101440A0
			bool BloodSplatterTrack::SetAngleRand(float value)
			{
				angleRand = value;
				return true;
			}

			// FUNCTION: ENGINE 0x101440C0
			fight::Property* BloodSplatterTrack::GetProperty(int index)
			{
				return gBloodSplatterTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101440E0
			void BloodSplatterTrack::ClearProperties()
			{
				fight::FreePropertyList(&gBloodSplatterTrackProperties);
			}

			// FUNCTION: ENGINE 0x10144110
			BloodSplatterTrack::BloodSplatterTrack() : angle(0.0f), angleRand(0.0f), duration(1.0f), durationRand(0.0f), fadeDuration(1.0f), fadeDurationRand(0.0f), positionX(0.0f), positionXRand(0.0f), positionY(0.0f), positionYRand(0.0f), scaleX(1.0f), scaleXRand(0.0f), scaleXYRand(0.0f), scaleY(1.0f), scaleYRand(0.0f), timeBegin(0.0f), timeEnd(-1.0f), wait(0.0f), waitRand(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x101441C0
			float BloodSplatterTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101441D0
			float BloodSplatterTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101441E0
			BloodSplatterTrack::~BloodSplatterTrack()
			{
			}

			// FUNCTION: ENGINE 0x10144380
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void BloodSplatterTrack::RegisterProperties()
			{
				if (gBloodSplatterTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("timeBegin", &BloodSplatterTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("timeEnd", &BloodSplatterTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<BloodSplatterTrack>("shader", &BloodSplatterTrack::SetShader);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("wait", &BloodSplatterTrack::SetWait);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("duration", &BloodSplatterTrack::SetDuration);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("fadeDuration", &BloodSplatterTrack::SetFadeDuration);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("waitRand", &BloodSplatterTrack::SetWaitRand);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("durationRand", &BloodSplatterTrack::SetDurationRand);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("fadeDurationRand", &BloodSplatterTrack::SetFadeDurationRand);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("positionX", &BloodSplatterTrack::SetPositionX);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("positionY", &BloodSplatterTrack::SetPositionY);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("positionXRand", &BloodSplatterTrack::SetPositionXRand);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("positionYRand", &BloodSplatterTrack::SetPositionYRand);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("scaleX", &BloodSplatterTrack::SetScaleX);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("scaleY", &BloodSplatterTrack::SetScaleY);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("scaleXYRand", &BloodSplatterTrack::SetScaleXYRand);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("scaleXRand", &BloodSplatterTrack::SetScaleXRand);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("scaleYRand", &BloodSplatterTrack::SetScaleYRand);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("angle", &BloodSplatterTrack::SetAngle);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<BloodSplatterTrack>("angleRand", &BloodSplatterTrack::SetAngleRand);
					properties[19] = property;
					fight::RegisterPropertyList(properties, &gBloodSplatterTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101442D0
			fight::TrackFactory* CreateBloodSplatterTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<BloodSplatterTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10144300
			void RegisterBloodSplatterTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<BloodSplatterTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<BloodSplatterTrack>;
			template class fight::PropertyName<BloodSplatterTrack>;
			template class fight::TrackFactoryTemplate<BloodSplatterTrack>;
			template class fight::TrackFactoryCasterTemplate<BloodSplatterTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101441F0
// FUNCTION: ENGINE 0x10144200
// FUNCTION: ENGINE 0x10144230
// FUNCTION: ENGINE 0x10144260
// FUNCTION: ENGINE 0x10144290
// FUNCTION: ENGINE 0x101442C0
// FUNCTION: ENGINE 0x10144330
// FUNCTION: ENGINE 0x10144360
// FUNCTION: ENGINE 0x101448B0
// FUNCTION: ENGINE 0x101448E0
// FUNCTION: ENGINE 0x10144900
