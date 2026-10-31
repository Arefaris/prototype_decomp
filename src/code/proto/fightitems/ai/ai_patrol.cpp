// Fight items of the ai group: HasPatrolPathCondition, PatrolTrack, PathPatrolTrack (unit 0x10243760 - 0x10244160; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_patrol.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gHasPatrolPathConditionProperties;  // 0x11255B20

			// FUNCTION: ENGINE 0x10243760
			bool HasPatrolPathCondition::SetHasPath(bool newValue)
			{
				hasPath = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102437F0
			fight::Property* HasPatrolPathCondition::GetProperty(int index)
			{
				return gHasPatrolPathConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10243810
			void HasPatrolPathCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHasPatrolPathConditionProperties);
			}

			// FUNCTION: ENGINE 0x10243820
			HasPatrolPathCondition::HasPatrolPathCondition() : fight::Condition(0), hasPath(true)
			{
			}

			// FUNCTION: ENGINE 0x10243840
			HasPatrolPathCondition::~HasPatrolPathCondition()
			{
			}

			// FUNCTION: ENGINE 0x10243C90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HasPatrolPathCondition::RegisterProperties()
			{
				if (gHasPatrolPathConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<HasPatrolPathCondition>("hasPath", &HasPatrolPathCondition::SetHasPath);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gHasPatrolPathConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10243C00
			fight::ConditionFactory* CreateHasPatrolPathConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasPatrolPathCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10243EF0
			void RegisterHasPatrolPathConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasPatrolPathCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gPatrolTrackProperties;  // 0x11255B24

			// FUNCTION: ENGINE 0x10243770
			bool PatrolTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10243790
			bool PatrolTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10243850
			fight::Property* PatrolTrack::GetProperty(int index)
			{
				return gPatrolTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10243870
			void PatrolTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPatrolTrackProperties);
			}

			// FUNCTION: ENGINE 0x10243880
			PatrolTrack::PatrolTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x102438B0
			float PatrolTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x102438C0
			float PatrolTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x102438D0
			PatrolTrack::~PatrolTrack()
			{
			}

			// FUNCTION: ENGINE 0x10243D30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PatrolTrack::RegisterProperties()
			{
				if (gPatrolTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PatrolTrack>("timeBegin", &PatrolTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PatrolTrack>("timeEnd", &PatrolTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gPatrolTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10243C30
			fight::TrackFactory* CreatePatrolTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PatrolTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10243F20
			void RegisterPatrolTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PatrolTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gPathPatrolTrackProperties;  // 0x11255B28

			// FUNCTION: ENGINE 0x102437B0
			bool PathPatrolTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102437D0
			bool PathPatrolTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102438E0
			fight::Property* PathPatrolTrack::GetProperty(int index)
			{
				return gPathPatrolTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10243900
			void PathPatrolTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPathPatrolTrackProperties);
			}

			// FUNCTION: ENGINE 0x10243910
			PathPatrolTrack::PathPatrolTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10243940
			float PathPatrolTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10243950
			float PathPatrolTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10243960
			PathPatrolTrack::~PathPatrolTrack()
			{
			}

			// FUNCTION: ENGINE 0x10243E10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PathPatrolTrack::RegisterProperties()
			{
				if (gPathPatrolTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PathPatrolTrack>("timeBegin", &PathPatrolTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PathPatrolTrack>("timeEnd", &PathPatrolTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gPathPatrolTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10243C60
			fight::TrackFactory* CreatePathPatrolTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PathPatrolTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10243F50
			void RegisterPathPatrolTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PathPatrolTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyBool<HasPatrolPathCondition>;
			template class fight::ConditionFactoryTemplate<HasPatrolPathCondition>;
			template class fight::ConditionFactoryCasterTemplate<HasPatrolPathCondition>;
			template class fight::PropertyFloatConstRange<PatrolTrack>;
			template class fight::TrackFactoryTemplate<PatrolTrack>;
			template class fight::TrackFactoryCasterTemplate<PatrolTrack>;
			template class fight::PropertyFloatConstRange<PathPatrolTrack>;
			template class fight::TrackFactoryTemplate<PathPatrolTrack>;
			template class fight::TrackFactoryCasterTemplate<PathPatrolTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10243970
// FUNCTION: ENGINE 0x102439A0
// FUNCTION: ENGINE 0x102439D0
// FUNCTION: ENGINE 0x10243A00
// FUNCTION: ENGINE 0x10243A10
// FUNCTION: ENGINE 0x10243A40
// FUNCTION: ENGINE 0x10243A50
// FUNCTION: ENGINE 0x10243A80
// FUNCTION: ENGINE 0x10243A90
// FUNCTION: ENGINE 0x10243AC0
// FUNCTION: ENGINE 0x10243AF0
// FUNCTION: ENGINE 0x10243B10
// FUNCTION: ENGINE 0x10243B20
// FUNCTION: ENGINE 0x10243B50
// FUNCTION: ENGINE 0x10243B80
// FUNCTION: ENGINE 0x10243B90
// FUNCTION: ENGINE 0x10243BC0
// FUNCTION: ENGINE 0x10243BF0
// FUNCTION: ENGINE 0x10243F80
// FUNCTION: ENGINE 0x10243FB0
// FUNCTION: ENGINE 0x10243FD0
// FUNCTION: ENGINE 0x10244000
// FUNCTION: ENGINE 0x10244020
// FUNCTION: ENGINE 0x10244050
// FUNCTION: ENGINE 0x10244070
// FUNCTION: ENGINE 0x102440C0
// FUNCTION: ENGINE 0x10244110
