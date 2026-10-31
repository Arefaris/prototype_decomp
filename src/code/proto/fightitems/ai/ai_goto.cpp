// Fight items of the ai group: HasFixedDestinationCondition, HasFixedAreaDestinationCondition, DumbGotoTrack, DumbGotoLODTrack, GoToTrack (unit 0x102338F0 - 0x10234D10; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_goto.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gHasFixedDestinationConditionProperties;  // 0x112559FC

			// FUNCTION: ENGINE 0x102338F0
			bool HasFixedDestinationCondition::SetHasDestination(bool newValue)
			{
				hasDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10233A80
			fight::Property* HasFixedDestinationCondition::GetProperty(int index)
			{
				return gHasFixedDestinationConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10233AA0
			void HasFixedDestinationCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHasFixedDestinationConditionProperties);
			}

			// FUNCTION: ENGINE 0x10233AB0
			HasFixedDestinationCondition::HasFixedDestinationCondition() : fight::Condition(0), hasDestination(true)
			{
			}

			// FUNCTION: ENGINE 0x10233AD0
			HasFixedDestinationCondition::~HasFixedDestinationCondition()
			{
			}

			// FUNCTION: ENGINE 0x10234390
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HasFixedDestinationCondition::RegisterProperties()
			{
				if (gHasFixedDestinationConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<HasFixedDestinationCondition>("hasDestination", &HasFixedDestinationCondition::SetHasDestination);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gHasFixedDestinationConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102342A0
			fight::ConditionFactory* CreateHasFixedDestinationConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasFixedDestinationCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10234900
			void RegisterHasFixedDestinationConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasFixedDestinationCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHasFixedAreaDestinationConditionProperties;  // 0x11255A00

			// FUNCTION: ENGINE 0x10233900
			bool HasFixedAreaDestinationCondition::SetHasDestination(bool newValue)
			{
				hasDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10233AE0
			fight::Property* HasFixedAreaDestinationCondition::GetProperty(int index)
			{
				return gHasFixedAreaDestinationConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10233B00
			void HasFixedAreaDestinationCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHasFixedAreaDestinationConditionProperties);
			}

			// FUNCTION: ENGINE 0x10233B10
			HasFixedAreaDestinationCondition::HasFixedAreaDestinationCondition() : fight::Condition(0), hasDestination(true)
			{
			}

			// FUNCTION: ENGINE 0x10233B30
			HasFixedAreaDestinationCondition::~HasFixedAreaDestinationCondition()
			{
			}

			// FUNCTION: ENGINE 0x10234430
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HasFixedAreaDestinationCondition::RegisterProperties()
			{
				if (gHasFixedAreaDestinationConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<HasFixedAreaDestinationCondition>("hasDestination", &HasFixedAreaDestinationCondition::SetHasDestination);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gHasFixedAreaDestinationConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102342D0
			fight::ConditionFactory* CreateHasFixedAreaDestinationConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasFixedAreaDestinationCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10234930
			void RegisterHasFixedAreaDestinationConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasFixedAreaDestinationCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDumbGotoTrackProperties;  // 0x11255A04

			// FUNCTION: ENGINE 0x10233910
			bool DumbGotoTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10233930
			bool DumbGotoTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10233950
			bool DumbGotoTrack::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10233970
			bool DumbGotoTrack::SetBrakingDistance(float newValue)
			{
				brakingDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10233990
			bool DumbGotoTrack::SetClearDestination(bool newValue)
			{
				clearDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10233B40
			fight::Property* DumbGotoTrack::GetProperty(int index)
			{
				return gDumbGotoTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10233B60
			void DumbGotoTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDumbGotoTrackProperties);
			}

			// FUNCTION: ENGINE 0x10233B70
			DumbGotoTrack::DumbGotoTrack() : brakingDistance(0.0f), timeBegin(0.0f), timeEnd(-1.0f), tolerance(0.5f), clearDestination(true)
			{
			}

			// FUNCTION: ENGINE 0x10233BC0
			float DumbGotoTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10233BD0
			float DumbGotoTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10233BE0
			DumbGotoTrack::~DumbGotoTrack()
			{
			}

			// FUNCTION: ENGINE 0x102344D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DumbGotoTrack::RegisterProperties()
			{
				if (gDumbGotoTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DumbGotoTrack>("timeBegin", &DumbGotoTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DumbGotoTrack>("timeEnd", &DumbGotoTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DumbGotoTrack>("tolerance", &DumbGotoTrack::SetTolerance);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<DumbGotoTrack>("brakingDistance", &DumbGotoTrack::SetBrakingDistance);
					properties[3] = property;
					property = new fight::PropertyBool<DumbGotoTrack>("clearDestination", &DumbGotoTrack::SetClearDestination);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gDumbGotoTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10234300
			fight::TrackFactory* CreateDumbGotoTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DumbGotoTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10234960
			void RegisterDumbGotoTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DumbGotoTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDumbGotoLODTrackProperties;  // 0x11255A08

			// FUNCTION: ENGINE 0x102339A0
			bool DumbGotoLODTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102339C0
			bool DumbGotoLODTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102339E0
			bool DumbGotoLODTrack::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10233A00
			bool DumbGotoLODTrack::SetBrakingDistance(float newValue)
			{
				brakingDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10233A20
			bool DumbGotoLODTrack::SetClearDestination(bool newValue)
			{
				clearDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10233BF0
			fight::Property* DumbGotoLODTrack::GetProperty(int index)
			{
				return gDumbGotoLODTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10233C10
			void DumbGotoLODTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDumbGotoLODTrackProperties);
			}

			// FUNCTION: ENGINE 0x10233C20
			DumbGotoLODTrack::DumbGotoLODTrack() : brakingDistance(0.0f), timeBegin(0.0f), timeEnd(-1.0f), tolerance(0.5f), clearDestination(true)
			{
			}

			// FUNCTION: ENGINE 0x10233C70
			float DumbGotoLODTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10233C80
			float DumbGotoLODTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10233C90
			DumbGotoLODTrack::~DumbGotoLODTrack()
			{
			}

			// FUNCTION: ENGINE 0x10234660
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DumbGotoLODTrack::RegisterProperties()
			{
				if (gDumbGotoLODTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DumbGotoLODTrack>("timeBegin", &DumbGotoLODTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DumbGotoLODTrack>("timeEnd", &DumbGotoLODTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DumbGotoLODTrack>("tolerance", &DumbGotoLODTrack::SetTolerance);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<DumbGotoLODTrack>("brakingDistance", &DumbGotoLODTrack::SetBrakingDistance);
					properties[3] = property;
					property = new fight::PropertyBool<DumbGotoLODTrack>("clearDestination", &DumbGotoLODTrack::SetClearDestination);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gDumbGotoLODTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10234330
			fight::TrackFactory* CreateDumbGotoLODTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DumbGotoLODTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10234990
			void RegisterDumbGotoLODTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DumbGotoLODTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGoToTrackProperties;  // 0x11255A0C

			// FUNCTION: ENGINE 0x10233A30
			bool GoToTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10233A50
			bool GoToTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10233A70
			bool GoToTrack::SetClearDestination(bool newValue)
			{
				clearDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10233CA0
			fight::Property* GoToTrack::GetProperty(int index)
			{
				return gGoToTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10233CC0
			void GoToTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGoToTrackProperties);
			}

			// FUNCTION: ENGINE 0x10233CD0
			GoToTrack::GoToTrack() : timeBegin(0.0f), timeEnd(-1.0f), clearDestination(true)
			{
			}

			// FUNCTION: ENGINE 0x10233D10
			float GoToTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10233D20
			float GoToTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10233D30
			GoToTrack::~GoToTrack()
			{
			}

			// FUNCTION: ENGINE 0x102347F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GoToTrack::RegisterProperties()
			{
				if (gGoToTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GoToTrack>("timeBegin", &GoToTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GoToTrack>("timeEnd", &GoToTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<GoToTrack>("clearDestination", &GoToTrack::SetClearDestination);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gGoToTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10234360
			fight::TrackFactory* CreateGoToTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GoToTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102349C0
			void RegisterGoToTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GoToTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyBool<HasFixedDestinationCondition>;
			template class fight::ConditionFactoryTemplate<HasFixedDestinationCondition>;
			template class fight::ConditionFactoryCasterTemplate<HasFixedDestinationCondition>;
			template class fight::PropertyBool<HasFixedAreaDestinationCondition>;
			template class fight::ConditionFactoryTemplate<HasFixedAreaDestinationCondition>;
			template class fight::ConditionFactoryCasterTemplate<HasFixedAreaDestinationCondition>;
			template class fight::PropertyFloatConstRange<DumbGotoTrack>;
			template class fight::PropertyBool<DumbGotoTrack>;
			template class fight::TrackFactoryTemplate<DumbGotoTrack>;
			template class fight::TrackFactoryCasterTemplate<DumbGotoTrack>;
			template class fight::PropertyFloatConstRange<DumbGotoLODTrack>;
			template class fight::PropertyBool<DumbGotoLODTrack>;
			template class fight::TrackFactoryTemplate<DumbGotoLODTrack>;
			template class fight::TrackFactoryCasterTemplate<DumbGotoLODTrack>;
			template class fight::PropertyFloatConstRange<GoToTrack>;
			template class fight::PropertyBool<GoToTrack>;
			template class fight::TrackFactoryTemplate<GoToTrack>;
			template class fight::TrackFactoryCasterTemplate<GoToTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10233D40
// FUNCTION: ENGINE 0x10233D70
// FUNCTION: ENGINE 0x10233DA0
// FUNCTION: ENGINE 0x10233DD0
// FUNCTION: ENGINE 0x10233E00
// FUNCTION: ENGINE 0x10233E30
// FUNCTION: ENGINE 0x10233E40
// FUNCTION: ENGINE 0x10233E70
// FUNCTION: ENGINE 0x10233E80
// FUNCTION: ENGINE 0x10233EB0
// FUNCTION: ENGINE 0x10233EC0
// FUNCTION: ENGINE 0x10233EF0
// FUNCTION: ENGINE 0x10233F00
// FUNCTION: ENGINE 0x10233F30
// FUNCTION: ENGINE 0x10233F40
// FUNCTION: ENGINE 0x10233F70
// FUNCTION: ENGINE 0x10233FA0
// FUNCTION: ENGINE 0x10233FC0
// FUNCTION: ENGINE 0x10233FD0
// FUNCTION: ENGINE 0x10234000
// FUNCTION: ENGINE 0x10234020
// FUNCTION: ENGINE 0x10234030
// FUNCTION: ENGINE 0x10234060
// FUNCTION: ENGINE 0x10234090
// FUNCTION: ENGINE 0x102340A0
// FUNCTION: ENGINE 0x102340D0
// FUNCTION: ENGINE 0x102340F0
// FUNCTION: ENGINE 0x10234100
// FUNCTION: ENGINE 0x10234130
// FUNCTION: ENGINE 0x10234160
// FUNCTION: ENGINE 0x10234170
// FUNCTION: ENGINE 0x102341A0
// FUNCTION: ENGINE 0x102341C0
// FUNCTION: ENGINE 0x102341D0
// FUNCTION: ENGINE 0x10234200
// FUNCTION: ENGINE 0x10234230
// FUNCTION: ENGINE 0x10234240
// FUNCTION: ENGINE 0x10234270
// FUNCTION: ENGINE 0x10234290
// FUNCTION: ENGINE 0x102349F0
// FUNCTION: ENGINE 0x10234A20
// FUNCTION: ENGINE 0x10234A40
// FUNCTION: ENGINE 0x10234A70
// FUNCTION: ENGINE 0x10234A90
// FUNCTION: ENGINE 0x10234AC0
// FUNCTION: ENGINE 0x10234AE0
// FUNCTION: ENGINE 0x10234B10
// FUNCTION: ENGINE 0x10234B30
// FUNCTION: ENGINE 0x10234B60
// FUNCTION: ENGINE 0x10234B80
// FUNCTION: ENGINE 0x10234BD0
// FUNCTION: ENGINE 0x10234C20
// FUNCTION: ENGINE 0x10234C70
// FUNCTION: ENGINE 0x10234CC0
