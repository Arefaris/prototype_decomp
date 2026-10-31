// Fight items of the motion group: FXLight_PointTrack (unit 0x10162970 - 0x10163BA0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_fxlight.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gFXLight_PointTrackProperties;  // 0x11254568

			// FUNCTION: ENGINE 0x10162970
			bool FXLight_PointTrack::SetAbortWhenInterrupted(bool newValue)
			{
				abortWhenInterrupted = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162990
			bool FXLight_PointTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101629B0
			bool FXLight_PointTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162D60
			bool FXLight_PointTrack::SetParentObjectName(const fight::Name& newValue)
			{
				parentObjectName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101629D0
			bool FXLight_PointTrack::SetWait(float newValue)
			{
				wait = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101629F0
			bool FXLight_PointTrack::SetFadeIn(float newValue)
			{
				fadeIn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162A10
			bool FXLight_PointTrack::SetDuration(float newValue)
			{
				duration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162A30
			bool FXLight_PointTrack::SetFadeOut(float newValue)
			{
				fadeOut = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162A50
			bool FXLight_PointTrack::SetWaitRand(float newValue)
			{
				waitRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162A70
			bool FXLight_PointTrack::SetFadeInRand(float newValue)
			{
				fadeInRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162A90
			bool FXLight_PointTrack::SetDurationRand(float newValue)
			{
				durationRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162AB0
			bool FXLight_PointTrack::SetFadeOutRand(float newValue)
			{
				fadeOutRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162AD0
			bool FXLight_PointTrack::SetIntensity(float newValue)
			{
				intensity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162AF0
			bool FXLight_PointTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162B10
			bool FXLight_PointTrack::SetIntensityRand(float newValue)
			{
				intensityRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162B30
			bool FXLight_PointTrack::SetRadiusRand(float newValue)
			{
				radiusRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162B50
			bool FXLight_PointTrack::SetFlickerIntensityFreq(float newValue)
			{
				flickerIntensityFreq = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162B70
			bool FXLight_PointTrack::SetFlickerIntensityFreqRand(float newValue)
			{
				flickerIntensityFreqRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162B90
			bool FXLight_PointTrack::SetFlickerIntensityMag(float newValue)
			{
				flickerIntensityMag = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162BB0
			bool FXLight_PointTrack::SetFlickerIntensityMagRand(float newValue)
			{
				flickerIntensityMagRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162BD0
			bool FXLight_PointTrack::SetFlickerRadiusFreq(float newValue)
			{
				flickerRadiusFreq = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162BF0
			bool FXLight_PointTrack::SetFlickerRadiusFreqRand(float newValue)
			{
				flickerRadiusFreqRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162C10
			bool FXLight_PointTrack::SetFlickerRadiusMag(float newValue)
			{
				flickerRadiusMag = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162C30
			bool FXLight_PointTrack::SetFlickerRadiusMagRand(float newValue)
			{
				flickerRadiusMagRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162C50
			bool FXLight_PointTrack::SetStartColour(const math::Colour128& newValue)
			{
				startColour = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162C80
			bool FXLight_PointTrack::SetEndColour(const math::Colour128& newValue)
			{
				endColour = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162CB0
			bool FXLight_PointTrack::SetEmitSpace(int newValue)
			{
				emitSpace = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162CD0
			bool FXLight_PointTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10162CF0
			bool FXLight_PointTrack::SetAttachSpace(int newValue)
			{
				attachSpace = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162D80
			bool FXLight_PointTrack::SetAttachJoint(const fight::Name& newValue)
			{
				attachJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162D10
			bool FXLight_PointTrack::SetFalloff(bool newValue)
			{
				falloff = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10162D30
			fight::Property* FXLight_PointTrack::GetProperty(int index)
			{
				return gFXLight_PointTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10162D50
			void FXLight_PointTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFXLight_PointTrackProperties);
			}

			// FUNCTION: ENGINE 0x10162DA0
			FXLight_PointTrack::FXLight_PointTrack() : endColour(1.0f, 1.0f, 1.0f, 1.0f), startColour(1.0f, 1.0f, 1.0f, 1.0f), offset(0.0f, 0.0f, 0.0f), duration(1.0f), durationRand(0.0f), fadeIn(0.0f), fadeInRand(0.0f), fadeOut(1.0f), fadeOutRand(0.0f), flickerIntensityFreq(0.0f), flickerIntensityFreqRand(0.0f), flickerIntensityMag(0.0f), flickerIntensityMagRand(0.0f), flickerRadiusFreq(0.0f), flickerRadiusFreqRand(0.0f), flickerRadiusMag(0.0f), flickerRadiusMagRand(0.0f), intensity(1.0f), intensityRand(0.0f), radius(1e+01f), radiusRand(0.0f), timeBegin(0.0f), timeEnd(-1.0f), wait(0.0f), waitRand(0.0f), attachSpace(0), emitSpace(0), abortWhenInterrupted(false), falloff(true)
			{
			}

			// FUNCTION: ENGINE 0x10162F00
			float FXLight_PointTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10162F10
			float FXLight_PointTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10162F20
			FXLight_PointTrack::~FXLight_PointTrack()
			{
			}

			// FUNCTION: ENGINE 0x101632F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FXLight_PointTrack::RegisterProperties()
			{
				if (gFXLight_PointTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<FXLight_PointTrack>("abortWhenInterrupted", &FXLight_PointTrack::SetAbortWhenInterrupted);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("timeBegin", &FXLight_PointTrack::SetTimeBegin);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("timeEnd", &FXLight_PointTrack::SetTimeEnd);
					properties[2] = property;
					property = new fight::PropertyName<FXLight_PointTrack>("parentObjectName", &FXLight_PointTrack::SetParentObjectName);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("wait", &FXLight_PointTrack::SetWait);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("fadeIn", &FXLight_PointTrack::SetFadeIn);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("duration", &FXLight_PointTrack::SetDuration);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("fadeOut", &FXLight_PointTrack::SetFadeOut);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("waitRand", &FXLight_PointTrack::SetWaitRand);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("fadeInRand", &FXLight_PointTrack::SetFadeInRand);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("durationRand", &FXLight_PointTrack::SetDurationRand);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("fadeOutRand", &FXLight_PointTrack::SetFadeOutRand);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("intensity", &FXLight_PointTrack::SetIntensity);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("radius", &FXLight_PointTrack::SetRadius);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("intensityRand", &FXLight_PointTrack::SetIntensityRand);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("radiusRand", &FXLight_PointTrack::SetRadiusRand);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerIntensityFreq", &FXLight_PointTrack::SetFlickerIntensityFreq);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerIntensityFreqRand", &FXLight_PointTrack::SetFlickerIntensityFreqRand);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerIntensityMag", &FXLight_PointTrack::SetFlickerIntensityMag);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerIntensityMagRand", &FXLight_PointTrack::SetFlickerIntensityMagRand);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerRadiusFreq", &FXLight_PointTrack::SetFlickerRadiusFreq);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerRadiusFreqRand", &FXLight_PointTrack::SetFlickerRadiusFreqRand);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerRadiusMag", &FXLight_PointTrack::SetFlickerRadiusMag);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<FXLight_PointTrack>("flickerRadiusMagRand", &FXLight_PointTrack::SetFlickerRadiusMagRand);
					properties[23] = property;
					property = new fight::PropertyColour<FXLight_PointTrack>("startColour", &FXLight_PointTrack::SetStartColour);
					properties[24] = property;
					property = new fight::PropertyColour<FXLight_PointTrack>("endColour", &FXLight_PointTrack::SetEndColour);
					properties[25] = property;
					property = new fight::PropertyEnumConstList<FXLight_PointTrack>("emitSpace", gFXLight_PointTrackEmitSpaceTable, gFXLight_PointTrackEmitSpaceCount, &FXLight_PointTrack::SetEmitSpace);
					properties[26] = property;
					property = new fight::PropertyVector<FXLight_PointTrack>("offset", &FXLight_PointTrack::SetOffset);
					properties[27] = property;
					property = new fight::PropertyEnumConstList<FXLight_PointTrack>("attachSpace", gFXLight_PointTrackAttachSpaceTable, gFXLight_PointTrackAttachSpaceCount, &FXLight_PointTrack::SetAttachSpace);
					properties[28] = property;
					property = new fight::PropertyNameList<FXLight_PointTrack>("attachJoint", &FXLight_PointTrack::SetAttachJoint);
					properties[29] = property;
					property = new fight::PropertyBool<FXLight_PointTrack>("falloff", &FXLight_PointTrack::SetFalloff);
					properties[30] = property;
					fight::RegisterPropertyList(properties, &gFXLight_PointTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101631E0
			fight::TrackFactory* CreateFXLight_PointTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FXLight_PointTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10163210
			void RegisterFXLight_PointTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FXLight_PointTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyBool<FXLight_PointTrack>;
			template class fight::PropertyFloatConstRange<FXLight_PointTrack>;
			template class fight::PropertyName<FXLight_PointTrack>;
			template class fight::PropertyColour<FXLight_PointTrack>;
			template class fight::PropertyEnumConstList<FXLight_PointTrack>;
			template class fight::PropertyVector<FXLight_PointTrack>;
			template class fight::PropertyNameList<FXLight_PointTrack>;
			template class fight::TrackFactoryTemplate<FXLight_PointTrack>;
			template class fight::TrackFactoryCasterTemplate<FXLight_PointTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10162F30
// FUNCTION: ENGINE 0x10162F40
// FUNCTION: ENGINE 0x10162F70
// FUNCTION: ENGINE 0x10162FA0
// FUNCTION: ENGINE 0x10162FD0
// FUNCTION: ENGINE 0x10162FF0
// FUNCTION: ENGINE 0x10163000
// FUNCTION: ENGINE 0x10163030
// FUNCTION: ENGINE 0x10163060
// FUNCTION: ENGINE 0x10163070
// FUNCTION: ENGINE 0x101630A0
// FUNCTION: ENGINE 0x101630C0
// FUNCTION: ENGINE 0x101630D0
// FUNCTION: ENGINE 0x10163110
// FUNCTION: ENGINE 0x10163120
// FUNCTION: ENGINE 0x10163150
// FUNCTION: ENGINE 0x10163170
// FUNCTION: ENGINE 0x10163180
// FUNCTION: ENGINE 0x101631B0
// FUNCTION: ENGINE 0x101631D0
// FUNCTION: ENGINE 0x10163240
// FUNCTION: ENGINE 0x10163270
// FUNCTION: ENGINE 0x10163290
// FUNCTION: ENGINE 0x101632C0
// FUNCTION: ENGINE 0x101632E0
// FUNCTION: ENGINE 0x10163AF0
// FUNCTION: ENGINE 0x10163B20
// FUNCTION: ENGINE 0x10163B50
