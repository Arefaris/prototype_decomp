// Fight items of the ai group: FlyingIdleTrack, IdleTrack (unit 0x10234D10 - 0x102356A0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_idle.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gFlyingIdleTrackProperties;  // 0x11255A14

			// FUNCTION: ENGINE 0x10234D10
			bool FlyingIdleTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10234D30
			bool FlyingIdleTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10234D50
			bool FlyingIdleTrack::SetMinHeight(float newValue)
			{
				minHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10234D70
			bool FlyingIdleTrack::SetFreeRadius(float newValue)
			{
				freeRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10234D90
			bool FlyingIdleTrack::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10234E20
			fight::Property* FlyingIdleTrack::GetProperty(int index)
			{
				return gFlyingIdleTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10234E40
			void FlyingIdleTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFlyingIdleTrackProperties);
			}

			// FUNCTION: ENGINE 0x10234E50
			FlyingIdleTrack::FlyingIdleTrack() : freeRadius(18.0f), minHeight(4.0f), timeBegin(0.0f), timeEnd(-1.0f), tolerance(1.5f)
			{
			}

			// FUNCTION: ENGINE 0x10234EC0
			float FlyingIdleTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10234ED0
			float FlyingIdleTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10234EE0
			FlyingIdleTrack::~FlyingIdleTrack()
			{
			}

			// FUNCTION: ENGINE 0x10235220
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FlyingIdleTrack::RegisterProperties()
			{
				if (gFlyingIdleTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FlyingIdleTrack>("timeBegin", &FlyingIdleTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FlyingIdleTrack>("timeEnd", &FlyingIdleTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FlyingIdleTrack>("minHeight", &FlyingIdleTrack::SetMinHeight);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<FlyingIdleTrack>("freeRadius", &FlyingIdleTrack::SetFreeRadius);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<FlyingIdleTrack>("tolerance", &FlyingIdleTrack::SetTolerance);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gFlyingIdleTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102351C0
			fight::TrackFactory* CreateFlyingIdleTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FlyingIdleTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10235500
			void RegisterFlyingIdleTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FlyingIdleTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gIdleTrackProperties;  // 0x11255A18

			// FUNCTION: ENGINE 0x10234DB0
			bool IdleTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10234DD0
			bool IdleTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10234DF0
			bool IdleTrack::SetIgnoreDefendAreaHeight(bool newValue)
			{
				ignoreDefendAreaHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10234E00
			bool IdleTrack::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10234EF0
			fight::Property* IdleTrack::GetProperty(int index)
			{
				return gIdleTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10234F10
			void IdleTrack::ClearProperties()
			{
				fight::FreePropertyList(&gIdleTrackProperties);
			}

			// FUNCTION: ENGINE 0x10234F20
			IdleTrack::IdleTrack() : timeBegin(0.0f), timeEnd(-1.0f), tolerance(1.5f), ignoreDefendAreaHeight(false)
			{
			}

			// FUNCTION: ENGINE 0x10234F70
			float IdleTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10234F80
			float IdleTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10234F90
			IdleTrack::~IdleTrack()
			{
			}

			// FUNCTION: ENGINE 0x102353B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IdleTrack::RegisterProperties()
			{
				if (gIdleTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<IdleTrack>("timeBegin", &IdleTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<IdleTrack>("timeEnd", &IdleTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<IdleTrack>("ignoreDefendAreaHeight", &IdleTrack::SetIgnoreDefendAreaHeight);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<IdleTrack>("tolerance", &IdleTrack::SetTolerance);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gIdleTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102351F0
			fight::TrackFactory* CreateIdleTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<IdleTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10235530
			void RegisterIdleTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<IdleTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<FlyingIdleTrack>;
			template class fight::TrackFactoryTemplate<FlyingIdleTrack>;
			template class fight::TrackFactoryCasterTemplate<FlyingIdleTrack>;
			template class fight::PropertyFloatConstRange<IdleTrack>;
			template class fight::PropertyBool<IdleTrack>;
			template class fight::TrackFactoryTemplate<IdleTrack>;
			template class fight::TrackFactoryCasterTemplate<IdleTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10234FA0
// FUNCTION: ENGINE 0x10234FD0
// FUNCTION: ENGINE 0x10235000
// FUNCTION: ENGINE 0x10235010
// FUNCTION: ENGINE 0x10235040
// FUNCTION: ENGINE 0x10235050
// FUNCTION: ENGINE 0x10235080
// FUNCTION: ENGINE 0x102350B0
// FUNCTION: ENGINE 0x102350E0
// FUNCTION: ENGINE 0x102350F0
// FUNCTION: ENGINE 0x10235120
// FUNCTION: ENGINE 0x10235150
// FUNCTION: ENGINE 0x10235160
// FUNCTION: ENGINE 0x10235190
// FUNCTION: ENGINE 0x102351B0
// FUNCTION: ENGINE 0x10235560
// FUNCTION: ENGINE 0x10235590
// FUNCTION: ENGINE 0x102355B0
// FUNCTION: ENGINE 0x102355E0
// FUNCTION: ENGINE 0x10235600
// FUNCTION: ENGINE 0x10235650
