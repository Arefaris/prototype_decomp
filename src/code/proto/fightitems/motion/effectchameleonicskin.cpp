// Fight items of the motion group: EffectChameleonicSkinTrack (unit 0x1015C310 - 0x1015CB40; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/effectchameleonicskin.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gEffectChameleonicSkinTrackProperties;  // 0x112544A8

			// FUNCTION: ENGINE 0x1015C310
			bool EffectChameleonicSkinTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015C330
			bool EffectChameleonicSkinTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015C350
			bool EffectChameleonicSkinTrack::SetActionOnBegin(int newValue)
			{
				actionOnBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015C360
			bool EffectChameleonicSkinTrack::SetActionOnEnd(int newValue)
			{
				actionOnEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015C370
			bool EffectChameleonicSkinTrack::SetWarpingFactor(float newValue)
			{
				warpingFactor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015C390
			bool EffectChameleonicSkinTrack::SetWarpOffsetScale(float newValue)
			{
				warpOffsetScale = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015C3B0
			bool EffectChameleonicSkinTrack::SetColourType(int newValue)
			{
				colourType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015C3C0
			bool EffectChameleonicSkinTrack::SetColour(const math::Colour128& newValue)
			{
				colour = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015C3F0
			bool EffectChameleonicSkinTrack::SetColourMix(float newValue)
			{
				colourMix = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015C410
			bool EffectChameleonicSkinTrack::SetBlurRadius(float newValue)
			{
				blurRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015C430
			fight::Property* EffectChameleonicSkinTrack::GetProperty(int index)
			{
				return gEffectChameleonicSkinTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1015C450
			void EffectChameleonicSkinTrack::ClearProperties()
			{
				fight::FreePropertyList(&gEffectChameleonicSkinTrackProperties);
			}

			// FUNCTION: ENGINE 0x1015C460
			EffectChameleonicSkinTrack::EffectChameleonicSkinTrack() : colour(0.0f, 0.0f, 0.5019608f, 1.0f), blurRadius(3.0f), colourMix(0.06f), timeBegin(0.0f), timeEnd(-1.0f), warpOffsetScale(0.02f), warpingFactor(0.8f), actionOnBegin(0), actionOnEnd(3), colourType(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1015C520
			float EffectChameleonicSkinTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1015C530
			float EffectChameleonicSkinTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1015C540
			EffectChameleonicSkinTrack::~EffectChameleonicSkinTrack()
			{
			}

			// FUNCTION: ENGINE 0x1015C770
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EffectChameleonicSkinTrack::RegisterProperties()
			{
				if (gEffectChameleonicSkinTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<EffectChameleonicSkinTrack>("timeBegin", &EffectChameleonicSkinTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<EffectChameleonicSkinTrack>("timeEnd", &EffectChameleonicSkinTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<EffectChameleonicSkinTrack>("actionOnBegin", gEffectChameleonicSkinTrackActionOnBeginTable, 3, &EffectChameleonicSkinTrack::SetActionOnBegin);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<EffectChameleonicSkinTrack>("actionOnEnd", gEffectChameleonicSkinTrackActionOnEndTable, 3, &EffectChameleonicSkinTrack::SetActionOnEnd);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<EffectChameleonicSkinTrack>("warpingFactor", &EffectChameleonicSkinTrack::SetWarpingFactor);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<EffectChameleonicSkinTrack>("warpOffsetScale", &EffectChameleonicSkinTrack::SetWarpOffsetScale);
					properties[5] = property;
					property = new fight::PropertyEnumConstList<EffectChameleonicSkinTrack>("colourType", gEffectChameleonicSkinTrackColourTypeTable, 2, &EffectChameleonicSkinTrack::SetColourType);
					properties[6] = property;
					property = new fight::PropertyColour<EffectChameleonicSkinTrack>("colour", &EffectChameleonicSkinTrack::SetColour);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<EffectChameleonicSkinTrack>("colourMix", &EffectChameleonicSkinTrack::SetColourMix);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<EffectChameleonicSkinTrack>("blurRadius", &EffectChameleonicSkinTrack::SetBlurRadius);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gEffectChameleonicSkinTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015C740
			fight::TrackFactory* CreateEffectChameleonicSkinTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<EffectChameleonicSkinTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015CA70
			void RegisterEffectChameleonicSkinTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<EffectChameleonicSkinTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<EffectChameleonicSkinTrack>;
			template class fight::PropertyEnumConstList<EffectChameleonicSkinTrack>;
			template class fight::PropertyColour<EffectChameleonicSkinTrack>;
			template class fight::TrackFactoryTemplate<EffectChameleonicSkinTrack>;
			template class fight::TrackFactoryCasterTemplate<EffectChameleonicSkinTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1015C550
// FUNCTION: ENGINE 0x1015C580
// FUNCTION: ENGINE 0x1015C590
// FUNCTION: ENGINE 0x1015C5C0
// FUNCTION: ENGINE 0x1015C5F0
// FUNCTION: ENGINE 0x1015C620
// FUNCTION: ENGINE 0x1015C630
// FUNCTION: ENGINE 0x1015C670
// FUNCTION: ENGINE 0x1015C680
// FUNCTION: ENGINE 0x1015C6B0
// FUNCTION: ENGINE 0x1015C6D0
// FUNCTION: ENGINE 0x1015C6E0
// FUNCTION: ENGINE 0x1015C710
// FUNCTION: ENGINE 0x1015C730
// FUNCTION: ENGINE 0x1015CAA0
// FUNCTION: ENGINE 0x1015CAD0
// FUNCTION: ENGINE 0x1015CAF0
