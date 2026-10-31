// Fight items of the motion group: RadialBlurTrack (unit 0x1019F890 - 0x101A0B00; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_radialblur.h"
#include <new>

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gRadialBlurTrackProperties;  // 0x11254958

			// FUNCTION: ENGINE 0x1019F890
			bool RadialBlurTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019F8B0
			bool RadialBlurTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019F8D0
			bool RadialBlurTrack::SetWait(float newValue)
			{
				wait = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019F8F0
			bool RadialBlurTrack::SetFadeIn(float newValue)
			{
				fadeIn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019F910
			bool RadialBlurTrack::SetDuration(float newValue)
			{
				duration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019F930
			bool RadialBlurTrack::SetFadeOut(float newValue)
			{
				fadeOut = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019F950
			bool RadialBlurTrack::SetWaitRand(float newValue)
			{
				waitRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019F970
			bool RadialBlurTrack::SetFadeInRand(float newValue)
			{
				fadeInRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019F990
			bool RadialBlurTrack::SetDurationRand(float newValue)
			{
				durationRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019F9B0
			bool RadialBlurTrack::SetFadeOutRand(float newValue)
			{
				fadeOutRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019F9D0
			bool RadialBlurTrack::SetIntensityStart(float newValue)
			{
				intensityStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019F9F0
			bool RadialBlurTrack::SetIntensityEnd(float newValue)
			{
				intensityEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FA10
			bool RadialBlurTrack::SetSizeStart(float newValue)
			{
				sizeStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FA30
			bool RadialBlurTrack::SetSizeEnd(float newValue)
			{
				sizeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FA50
			bool RadialBlurTrack::SetFalloffStart(float newValue)
			{
				falloffStart = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FA70
			bool RadialBlurTrack::SetFalloffEnd(float newValue)
			{
				falloffEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FA90
			bool RadialBlurTrack::SetFlickerIntensityFreq(float newValue)
			{
				flickerIntensityFreq = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FAB0
			bool RadialBlurTrack::SetFlickerIntensityFreqRand(float newValue)
			{
				flickerIntensityFreqRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FAD0
			bool RadialBlurTrack::SetFlickerIntensityMag(float newValue)
			{
				flickerIntensityMag = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FAF0
			bool RadialBlurTrack::SetFlickerIntensityMagRand(float newValue)
			{
				flickerIntensityMagRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FB10
			bool RadialBlurTrack::SetFlickerSizeFreq(float newValue)
			{
				flickerSizeFreq = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FB30
			bool RadialBlurTrack::SetFlickerSizeFreqRand(float newValue)
			{
				flickerSizeFreqRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FB50
			bool RadialBlurTrack::SetFlickerSizeMag(float newValue)
			{
				flickerSizeMag = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FB70
			bool RadialBlurTrack::SetFlickerSizeMagRand(float newValue)
			{
				flickerSizeMagRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FB90
			bool RadialBlurTrack::SetFlickerFalloffFreq(float newValue)
			{
				flickerFalloffFreq = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FBB0
			bool RadialBlurTrack::SetFlickerFalloffFreqRand(float newValue)
			{
				flickerFalloffFreqRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FBD0
			bool RadialBlurTrack::SetFlickerFalloffMag(float newValue)
			{
				flickerFalloffMag = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FBF0
			bool RadialBlurTrack::SetFlickerFalloffMagRand(float newValue)
			{
				flickerFalloffMagRand = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FC10
			bool RadialBlurTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FC30
			bool RadialBlurTrack::SetAttachSpace(int newValue)
			{
				attachSpace = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FCD0
			bool RadialBlurTrack::SetAttachJoint(const fight::Name& newValue)
			{
				attachJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FCA0
			bool RadialBlurTrack::SetPatch(const char* newValue)
			{
				patch = fight::ReplaceString(patch, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x1019FC50
			bool RadialBlurTrack::SetInGameCameraOnly(bool newValue)
			{
				inGameCameraOnly = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1019FC70
			fight::Property* RadialBlurTrack::GetProperty(int index)
			{
				return gRadialBlurTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1019FC90
			void RadialBlurTrack::ClearProperties()
			{
				fight::FreePropertyList(&gRadialBlurTrackProperties);
			}

			// FUNCTION: ENGINE 0x1019FCF0
			RadialBlurTrack::RadialBlurTrack() : offset(0.0f, 0.0f, 0.0f), patch(0), duration(1.0f), durationRand(0.0f), fadeIn(1.0f), fadeInRand(0.0f), fadeOut(1.0f), fadeOutRand(0.0f), falloffEnd(1.0f), falloffStart(1.0f), flickerFalloffFreq(0.0f), flickerFalloffFreqRand(0.0f), flickerFalloffMag(0.0f), flickerFalloffMagRand(0.0f), flickerIntensityFreq(0.0f), flickerIntensityFreqRand(0.0f), flickerIntensityMag(0.0f), flickerIntensityMagRand(0.0f), flickerSizeFreq(0.0f), flickerSizeFreqRand(0.0f), flickerSizeMag(0.0f), flickerSizeMagRand(0.0f), intensityEnd(3.0f), intensityStart(3.0f), sizeEnd(1.0f), sizeStart(1.0f), timeBegin(0.0f), timeEnd(-1.0f), wait(0.0f), waitRand(0.0f), attachSpace(0), inGameCameraOnly(false)
			{
			}

			// FUNCTION: ENGINE 0x1019FE20
			float RadialBlurTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1019FE30
			float RadialBlurTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1019FE40
			RadialBlurTrack::~RadialBlurTrack()
			{
				delete[] patch;
			}

			// FUNCTION: ENGINE 0x101A01E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RadialBlurTrack::RegisterProperties()
			{
				if (gRadialBlurTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("timeBegin", &RadialBlurTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("timeEnd", &RadialBlurTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("wait", &RadialBlurTrack::SetWait);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("fadeIn", &RadialBlurTrack::SetFadeIn);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("duration", &RadialBlurTrack::SetDuration);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("fadeOut", &RadialBlurTrack::SetFadeOut);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("waitRand", &RadialBlurTrack::SetWaitRand);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("fadeInRand", &RadialBlurTrack::SetFadeInRand);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("durationRand", &RadialBlurTrack::SetDurationRand);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("fadeOutRand", &RadialBlurTrack::SetFadeOutRand);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("intensityStart", &RadialBlurTrack::SetIntensityStart);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("intensityEnd", &RadialBlurTrack::SetIntensityEnd);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("sizeStart", &RadialBlurTrack::SetSizeStart);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("sizeEnd", &RadialBlurTrack::SetSizeEnd);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("falloffStart", &RadialBlurTrack::SetFalloffStart);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("falloffEnd", &RadialBlurTrack::SetFalloffEnd);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("flickerIntensityFreq", &RadialBlurTrack::SetFlickerIntensityFreq);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("flickerIntensityFreqRand", &RadialBlurTrack::SetFlickerIntensityFreqRand);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("flickerIntensityMag", &RadialBlurTrack::SetFlickerIntensityMag);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("flickerIntensityMagRand", &RadialBlurTrack::SetFlickerIntensityMagRand);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("flickerSizeFreq", &RadialBlurTrack::SetFlickerSizeFreq);
					properties[20] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("flickerSizeFreqRand", &RadialBlurTrack::SetFlickerSizeFreqRand);
					properties[21] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("flickerSizeMag", &RadialBlurTrack::SetFlickerSizeMag);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("flickerSizeMagRand", &RadialBlurTrack::SetFlickerSizeMagRand);
					properties[23] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("flickerFalloffFreq", &RadialBlurTrack::SetFlickerFalloffFreq);
					properties[24] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("flickerFalloffFreqRand", &RadialBlurTrack::SetFlickerFalloffFreqRand);
					properties[25] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("flickerFalloffMag", &RadialBlurTrack::SetFlickerFalloffMag);
					properties[26] = property;
					property = new fight::PropertyFloatConstRange<RadialBlurTrack>("flickerFalloffMagRand", &RadialBlurTrack::SetFlickerFalloffMagRand);
					properties[27] = property;
					property = new fight::PropertyVector<RadialBlurTrack>("offset", &RadialBlurTrack::SetOffset);
					properties[28] = property;
					property = new fight::PropertyEnumConstList<RadialBlurTrack>("attachSpace", gRadialBlurTrackAttachSpaceTable, gRadialBlurTrackAttachSpaceCount, &RadialBlurTrack::SetAttachSpace);
					properties[29] = property;
					property = new fight::PropertyNameList<RadialBlurTrack>("attachJoint", &RadialBlurTrack::SetAttachJoint);
					properties[30] = property;
					property = new fight::PropertyString<RadialBlurTrack>("patch", &RadialBlurTrack::SetPatch);
					properties[31] = property;
					property = new fight::PropertyBool<RadialBlurTrack>("inGameCameraOnly", &RadialBlurTrack::SetInGameCameraOnly);
					properties[32] = property;
					fight::RegisterPropertyList(properties, &gRadialBlurTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A0120
			fight::TrackFactory* CreateRadialBlurTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<RadialBlurTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A0150
			void RegisterRadialBlurTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<RadialBlurTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<RadialBlurTrack>;
			template class fight::PropertyVector<RadialBlurTrack>;
			template class fight::PropertyEnumConstList<RadialBlurTrack>;
			template class fight::PropertyNameList<RadialBlurTrack>;
			template class fight::PropertyString<RadialBlurTrack>;
			template class fight::PropertyBool<RadialBlurTrack>;
			template class fight::TrackFactoryTemplate<RadialBlurTrack>;
			template class fight::TrackFactoryCasterTemplate<RadialBlurTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1019FE70
// FUNCTION: ENGINE 0x1019FE80
// FUNCTION: ENGINE 0x1019FEB0
// FUNCTION: ENGINE 0x1019FEE0
// FUNCTION: ENGINE 0x1019FF10
// FUNCTION: ENGINE 0x1019FF40
// FUNCTION: ENGINE 0x1019FF50
// FUNCTION: ENGINE 0x1019FF80
// FUNCTION: ENGINE 0x1019FFA0
// FUNCTION: ENGINE 0x1019FFB0
// FUNCTION: ENGINE 0x1019FFF0
// FUNCTION: ENGINE 0x101A0000
// FUNCTION: ENGINE 0x101A0030
// FUNCTION: ENGINE 0x101A0050
// FUNCTION: ENGINE 0x101A0060
// FUNCTION: ENGINE 0x101A0090
// FUNCTION: ENGINE 0x101A00B0
// FUNCTION: ENGINE 0x101A00C0
// FUNCTION: ENGINE 0x101A00F0
// FUNCTION: ENGINE 0x101A0110
// FUNCTION: ENGINE 0x101A0180
// FUNCTION: ENGINE 0x101A01B0
// FUNCTION: ENGINE 0x101A01D0
// FUNCTION: ENGINE 0x101A0A50
// FUNCTION: ENGINE 0x101A0A80
// FUNCTION: ENGINE 0x101A0AB0
