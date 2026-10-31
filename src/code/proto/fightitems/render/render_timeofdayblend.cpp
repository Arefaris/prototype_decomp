// Fight items of the render group: TimeOfDayBlendTrack (unit 0x102643C0 - 0x10264E40; no assert path, the file name is a guess).
#include "code/proto/fightitems/render/render_timeofdayblend.h"

namespace proto
{
	namespace fightitems
	{
		namespace render
		{
			fight::Property** gTimeOfDayBlendTrackProperties;  // 0x11255DD8

			// FUNCTION: ENGINE 0x10264540
			bool TimeOfDayBlendTrack::SetGroupName(const fight::Name& newValue)
			{
				groupName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10264560
			bool TimeOfDayBlendTrack::SetVariationName(const fight::Name& newValue)
			{
				variationName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102643C0
			bool TimeOfDayBlendTrack::SetFadeIn(float newValue)
			{
				fadeIn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102643E0
			bool TimeOfDayBlendTrack::SetDuration(float newValue)
			{
				duration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10264400
			bool TimeOfDayBlendTrack::SetFadeOut(float newValue)
			{
				fadeOut = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10264420
			bool TimeOfDayBlendTrack::SetLevel(int newValue)
			{
				level = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10264430
			bool TimeOfDayBlendTrack::SetSky(bool newValue)
			{
				sky = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10264440
			bool TimeOfDayBlendTrack::SetGlobalLighting(bool newValue)
			{
				globalLighting = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10264450
			bool TimeOfDayBlendTrack::SetLighting(bool newValue)
			{
				lighting = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10264460
			bool TimeOfDayBlendTrack::SetBloom(bool newValue)
			{
				bloom = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10264470
			bool TimeOfDayBlendTrack::SetColourMatrix(bool newValue)
			{
				colourMatrix = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10264480
			bool TimeOfDayBlendTrack::SetShaders(bool newValue)
			{
				shaders = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10264490
			bool TimeOfDayBlendTrack::SetClouds(bool newValue)
			{
				clouds = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102644A0
			bool TimeOfDayBlendTrack::SetFog(bool newValue)
			{
				fog = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102644B0
			bool TimeOfDayBlendTrack::SetAbortable(bool newValue)
			{
				abortable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102644C0
			bool TimeOfDayBlendTrack::SetDynamicDuration(bool newValue)
			{
				dynamicDuration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102644D0
			bool TimeOfDayBlendTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102644F0
			bool TimeOfDayBlendTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10264510
			fight::Property* TimeOfDayBlendTrack::GetProperty(int index)
			{
				return gTimeOfDayBlendTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10264530
			void TimeOfDayBlendTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTimeOfDayBlendTrackProperties);
			}

			// FUNCTION: ENGINE 0x10264580
			TimeOfDayBlendTrack::TimeOfDayBlendTrack() : duration(5.0f), fadeIn(1.0f), fadeOut(1.0f), timeBegin(0.0f), timeEnd(0.0f), level(0), abortable(false), bloom(true), clouds(true), colourMatrix(true), dynamicDuration(false), fog(true), globalLighting(true), lighting(true), shaders(true), sky(true)
			{
			}

			// FUNCTION: ENGINE 0x10264610
			float TimeOfDayBlendTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10264620
			float TimeOfDayBlendTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10264630
			TimeOfDayBlendTrack::~TimeOfDayBlendTrack()
			{
			}

			// FUNCTION: ENGINE 0x102648E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TimeOfDayBlendTrack::RegisterProperties()
			{
				if (gTimeOfDayBlendTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<TimeOfDayBlendTrack>("groupName", &TimeOfDayBlendTrack::SetGroupName);
					properties[0] = property;
					property = new fight::PropertyName<TimeOfDayBlendTrack>("variationName", &TimeOfDayBlendTrack::SetVariationName);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TimeOfDayBlendTrack>("fadeIn", &TimeOfDayBlendTrack::SetFadeIn);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<TimeOfDayBlendTrack>("duration", &TimeOfDayBlendTrack::SetDuration);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<TimeOfDayBlendTrack>("fadeOut", &TimeOfDayBlendTrack::SetFadeOut);
					properties[4] = property;
					property = new fight::PropertyEnumConstList<TimeOfDayBlendTrack>("level", gTimeOfDayBlendTrackLevelTable, gTimeOfDayBlendTrackLevelCount, &TimeOfDayBlendTrack::SetLevel);
					properties[5] = property;
					property = new fight::PropertyBool<TimeOfDayBlendTrack>("sky", &TimeOfDayBlendTrack::SetSky);
					properties[6] = property;
					property = new fight::PropertyBool<TimeOfDayBlendTrack>("globalLighting", &TimeOfDayBlendTrack::SetGlobalLighting);
					properties[7] = property;
					property = new fight::PropertyBool<TimeOfDayBlendTrack>("lighting", &TimeOfDayBlendTrack::SetLighting);
					properties[8] = property;
					property = new fight::PropertyBool<TimeOfDayBlendTrack>("bloom", &TimeOfDayBlendTrack::SetBloom);
					properties[9] = property;
					property = new fight::PropertyBool<TimeOfDayBlendTrack>("colourMatrix", &TimeOfDayBlendTrack::SetColourMatrix);
					properties[10] = property;
					property = new fight::PropertyBool<TimeOfDayBlendTrack>("shaders", &TimeOfDayBlendTrack::SetShaders);
					properties[11] = property;
					property = new fight::PropertyBool<TimeOfDayBlendTrack>("clouds", &TimeOfDayBlendTrack::SetClouds);
					properties[12] = property;
					property = new fight::PropertyBool<TimeOfDayBlendTrack>("fog", &TimeOfDayBlendTrack::SetFog);
					properties[13] = property;
					property = new fight::PropertyBool<TimeOfDayBlendTrack>("abortable", &TimeOfDayBlendTrack::SetAbortable);
					properties[14] = property;
					property = new fight::PropertyBool<TimeOfDayBlendTrack>("dynamicDuration", &TimeOfDayBlendTrack::SetDynamicDuration);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<TimeOfDayBlendTrack>("timeBegin", &TimeOfDayBlendTrack::SetTimeBegin);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<TimeOfDayBlendTrack>("timeEnd", &TimeOfDayBlendTrack::SetTimeEnd);
					properties[17] = property;
					fight::RegisterPropertyList(properties, &gTimeOfDayBlendTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10264830
			fight::TrackFactory* CreateTimeOfDayBlendTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TimeOfDayBlendTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10264860
			void RegisterTimeOfDayBlendTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TimeOfDayBlendTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyName<TimeOfDayBlendTrack>;
			template class fight::PropertyFloatConstRange<TimeOfDayBlendTrack>;
			template class fight::PropertyEnumConstList<TimeOfDayBlendTrack>;
			template class fight::PropertyBool<TimeOfDayBlendTrack>;
			template class fight::TrackFactoryTemplate<TimeOfDayBlendTrack>;
			template class fight::TrackFactoryCasterTemplate<TimeOfDayBlendTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10264640
// FUNCTION: ENGINE 0x10264650
// FUNCTION: ENGINE 0x10264680
// FUNCTION: ENGINE 0x102646B0
// FUNCTION: ENGINE 0x102646E0
// FUNCTION: ENGINE 0x10264710
// FUNCTION: ENGINE 0x10264720
// FUNCTION: ENGINE 0x10264760
// FUNCTION: ENGINE 0x10264770
// FUNCTION: ENGINE 0x102647A0
// FUNCTION: ENGINE 0x102647C0
// FUNCTION: ENGINE 0x102647D0
// FUNCTION: ENGINE 0x10264800
// FUNCTION: ENGINE 0x10264820
// FUNCTION: ENGINE 0x10264890
// FUNCTION: ENGINE 0x102648C0
// FUNCTION: ENGINE 0x10264DA0
// FUNCTION: ENGINE 0x10264DD0
// FUNCTION: ENGINE 0x10264DF0
