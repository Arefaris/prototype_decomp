// Fight items of the ai group: FixedDestinationDistanceCondition, FixedDestinationGotoTrack, FixedDestinationJumpToTrack, ClearFixedAreaDestinationTrack, FixedDestinationFlytoTrack (unit 0x102305F0 - 0x10231FB0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_fixeddestination.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gFixedDestinationDistanceConditionProperties;  // 0x112559C8

			// FUNCTION: ENGINE 0x102305F0
			bool FixedDestinationDistanceCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230600
			bool FixedDestinationDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230610
			bool FixedDestinationDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230870
			fight::Property* FixedDestinationDistanceCondition::GetProperty(int index)
			{
				return gFixedDestinationDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10230890
			void FixedDestinationDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gFixedDestinationDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x102308A0
			FixedDestinationDistanceCondition::FixedDestinationDistanceCondition() : fight::Condition(0), distance(2e+01f), compare(4), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x102308E0
			FixedDestinationDistanceCondition::~FixedDestinationDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x102313B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FixedDestinationDistanceCondition::RegisterProperties()
			{
				if (gFixedDestinationDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<FixedDestinationDistanceCondition>("direction", motion::gCrowdPositionConditionDirectionTable, motion::gCrowdPositionConditionDirectionCount, &FixedDestinationDistanceCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<FixedDestinationDistanceCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &FixedDestinationDistanceCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationDistanceCondition>("distance", &FixedDestinationDistanceCondition::SetDistance);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gFixedDestinationDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102312C0
			fight::ConditionFactory* CreateFixedDestinationDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FixedDestinationDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10231BA0
			void RegisterFixedDestinationDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FixedDestinationDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gFixedDestinationGotoTrackProperties;  // 0x112559CC

			// FUNCTION: ENGINE 0x10230630
			bool FixedDestinationGotoTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230650
			bool FixedDestinationGotoTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230670
			bool FixedDestinationGotoTrack::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230690
			bool FixedDestinationGotoTrack::SetBraking(bool newValue)
			{
				braking = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102306A0
			bool FixedDestinationGotoTrack::SetIgnoreRestrictions(bool newValue)
			{
				ignoreRestrictions = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102306B0
			bool FixedDestinationGotoTrack::SetClearDestination(bool newValue)
			{
				clearDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102308F0
			fight::Property* FixedDestinationGotoTrack::GetProperty(int index)
			{
				return gFixedDestinationGotoTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10230910
			void FixedDestinationGotoTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFixedDestinationGotoTrackProperties);
			}

			// FUNCTION: ENGINE 0x10230920
			FixedDestinationGotoTrack::FixedDestinationGotoTrack() : timeBegin(0.0f), timeEnd(-1.0f), tolerance(0.5f), braking(true), clearDestination(true), ignoreRestrictions(true)
			{
			}

			// FUNCTION: ENGINE 0x10230970
			float FixedDestinationGotoTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10230980
			float FixedDestinationGotoTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10230990
			FixedDestinationGotoTrack::~FixedDestinationGotoTrack()
			{
			}

			// FUNCTION: ENGINE 0x102314F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FixedDestinationGotoTrack::RegisterProperties()
			{
				if (gFixedDestinationGotoTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FixedDestinationGotoTrack>("timeBegin", &FixedDestinationGotoTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationGotoTrack>("timeEnd", &FixedDestinationGotoTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationGotoTrack>("tolerance", &FixedDestinationGotoTrack::SetTolerance);
					properties[2] = property;
					property = new fight::PropertyBool<FixedDestinationGotoTrack>("braking", &FixedDestinationGotoTrack::SetBraking);
					properties[3] = property;
					property = new fight::PropertyBool<FixedDestinationGotoTrack>("ignoreRestrictions", &FixedDestinationGotoTrack::SetIgnoreRestrictions);
					properties[4] = property;
					property = new fight::PropertyBool<FixedDestinationGotoTrack>("clearDestination", &FixedDestinationGotoTrack::SetClearDestination);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gFixedDestinationGotoTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102312F0
			fight::TrackFactory* CreateFixedDestinationGotoTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FixedDestinationGotoTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10231BD0
			void RegisterFixedDestinationGotoTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FixedDestinationGotoTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gFixedDestinationJumpToTrackProperties;  // 0x112559D0

			// FUNCTION: ENGINE 0x102306C0
			bool FixedDestinationJumpToTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102306E0
			bool FixedDestinationJumpToTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230700
			bool FixedDestinationJumpToTrack::SetClearDestination(bool newValue)
			{
				clearDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102309A0
			fight::Property* FixedDestinationJumpToTrack::GetProperty(int index)
			{
				return gFixedDestinationJumpToTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102309C0
			void FixedDestinationJumpToTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFixedDestinationJumpToTrackProperties);
			}

			// FUNCTION: ENGINE 0x102309D0
			FixedDestinationJumpToTrack::FixedDestinationJumpToTrack() : timeBegin(0.0f), timeEnd(-1.0f), clearDestination(true)
			{
			}

			// FUNCTION: ENGINE 0x10230A10
			float FixedDestinationJumpToTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10230A20
			float FixedDestinationJumpToTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10230A30
			FixedDestinationJumpToTrack::~FixedDestinationJumpToTrack()
			{
			}

			// FUNCTION: ENGINE 0x102316C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FixedDestinationJumpToTrack::RegisterProperties()
			{
				if (gFixedDestinationJumpToTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FixedDestinationJumpToTrack>("timeBegin", &FixedDestinationJumpToTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationJumpToTrack>("timeEnd", &FixedDestinationJumpToTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<FixedDestinationJumpToTrack>("clearDestination", &FixedDestinationJumpToTrack::SetClearDestination);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gFixedDestinationJumpToTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10231320
			fight::TrackFactory* CreateFixedDestinationJumpToTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FixedDestinationJumpToTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10231C00
			void RegisterFixedDestinationJumpToTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FixedDestinationJumpToTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gClearFixedAreaDestinationTrackProperties;  // 0x112559D4

			// FUNCTION: ENGINE 0x10230710
			bool ClearFixedAreaDestinationTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230730
			bool ClearFixedAreaDestinationTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230750
			bool ClearFixedAreaDestinationTrack::SetClearOnBegin(bool newValue)
			{
				clearOnBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230A40
			fight::Property* ClearFixedAreaDestinationTrack::GetProperty(int index)
			{
				return gClearFixedAreaDestinationTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10230A60
			void ClearFixedAreaDestinationTrack::ClearProperties()
			{
				fight::FreePropertyList(&gClearFixedAreaDestinationTrackProperties);
			}

			// FUNCTION: ENGINE 0x10230A70
			ClearFixedAreaDestinationTrack::ClearFixedAreaDestinationTrack() : timeBegin(0.0f), timeEnd(-1.0f), clearOnBegin(true)
			{
			}

			// FUNCTION: ENGINE 0x10230AB0
			float ClearFixedAreaDestinationTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10230AC0
			float ClearFixedAreaDestinationTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10230AD0
			ClearFixedAreaDestinationTrack::~ClearFixedAreaDestinationTrack()
			{
			}

			// FUNCTION: ENGINE 0x102317D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ClearFixedAreaDestinationTrack::RegisterProperties()
			{
				if (gClearFixedAreaDestinationTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ClearFixedAreaDestinationTrack>("timeBegin", &ClearFixedAreaDestinationTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ClearFixedAreaDestinationTrack>("timeEnd", &ClearFixedAreaDestinationTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<ClearFixedAreaDestinationTrack>("clearOnBegin", &ClearFixedAreaDestinationTrack::SetClearOnBegin);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gClearFixedAreaDestinationTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10231350
			fight::TrackFactory* CreateClearFixedAreaDestinationTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ClearFixedAreaDestinationTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10231C30
			void RegisterClearFixedAreaDestinationTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ClearFixedAreaDestinationTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gFixedDestinationFlytoTrackProperties;  // 0x112559D8

			// FUNCTION: ENGINE 0x10230760
			bool FixedDestinationFlytoTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230780
			bool FixedDestinationFlytoTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102307A0
			bool FixedDestinationFlytoTrack::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102307C0
			bool FixedDestinationFlytoTrack::SetBraking(bool newValue)
			{
				braking = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102307D0
			bool FixedDestinationFlytoTrack::SetIgnoreRestrictions(bool newValue)
			{
				ignoreRestrictions = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102307E0
			bool FixedDestinationFlytoTrack::SetClearDestination(bool newValue)
			{
				clearDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102307F0
			bool FixedDestinationFlytoTrack::SetFreeArea(float newValue)
			{
				freeArea = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230810
			bool FixedDestinationFlytoTrack::SetMinHeight(float newValue)
			{
				minHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230830
			bool FixedDestinationFlytoTrack::SetMaxSpeed(float newValue)
			{
				maxSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10230850
			bool FixedDestinationFlytoTrack::SetSpeedFactor(const math::Vector& newValue)
			{
				speedFactor.x = newValue.x;
				speedFactor.y = newValue.y;
				speedFactor.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10230AE0
			fight::Property* FixedDestinationFlytoTrack::GetProperty(int index)
			{
				return gFixedDestinationFlytoTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10230B00
			void FixedDestinationFlytoTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFixedDestinationFlytoTrackProperties);
			}

			// FUNCTION: ENGINE 0x10230B10
			FixedDestinationFlytoTrack::FixedDestinationFlytoTrack() : speedFactor(-1.0f, -1.0f, -1.0f), freeArea(0.0f), maxSpeed(1.0f), minHeight(6.0f), timeBegin(0.0f), timeEnd(-1.0f), tolerance(0.5f), braking(true), clearDestination(true), ignoreRestrictions(true)
			{
			}

			// FUNCTION: ENGINE 0x10230BA0
			float FixedDestinationFlytoTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10230BB0
			float FixedDestinationFlytoTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10230BC0
			FixedDestinationFlytoTrack::~FixedDestinationFlytoTrack()
			{
			}

			// FUNCTION: ENGINE 0x102318E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FixedDestinationFlytoTrack::RegisterProperties()
			{
				if (gFixedDestinationFlytoTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>("timeBegin", &FixedDestinationFlytoTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>("timeEnd", &FixedDestinationFlytoTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>("tolerance", &FixedDestinationFlytoTrack::SetTolerance);
					properties[2] = property;
					property = new fight::PropertyBool<FixedDestinationFlytoTrack>("braking", &FixedDestinationFlytoTrack::SetBraking);
					properties[3] = property;
					property = new fight::PropertyBool<FixedDestinationFlytoTrack>("ignoreRestrictions", &FixedDestinationFlytoTrack::SetIgnoreRestrictions);
					properties[4] = property;
					property = new fight::PropertyBool<FixedDestinationFlytoTrack>("clearDestination", &FixedDestinationFlytoTrack::SetClearDestination);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>("freeArea", &FixedDestinationFlytoTrack::SetFreeArea);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>("minHeight", &FixedDestinationFlytoTrack::SetMinHeight);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>("maxSpeed", &FixedDestinationFlytoTrack::SetMaxSpeed);
					properties[8] = property;
					property = new fight::PropertyVector<FixedDestinationFlytoTrack>("speedFactor", &FixedDestinationFlytoTrack::SetSpeedFactor);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gFixedDestinationFlytoTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10231380
			fight::TrackFactory* CreateFixedDestinationFlytoTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FixedDestinationFlytoTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10231C60
			void RegisterFixedDestinationFlytoTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FixedDestinationFlytoTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<FixedDestinationDistanceCondition>;
			template class fight::PropertyFloatConstRange<FixedDestinationDistanceCondition>;
			template class fight::ConditionFactoryTemplate<FixedDestinationDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<FixedDestinationDistanceCondition>;
			template class fight::PropertyFloatConstRange<FixedDestinationGotoTrack>;
			template class fight::PropertyBool<FixedDestinationGotoTrack>;
			template class fight::TrackFactoryTemplate<FixedDestinationGotoTrack>;
			template class fight::TrackFactoryCasterTemplate<FixedDestinationGotoTrack>;
			template class fight::PropertyFloatConstRange<FixedDestinationJumpToTrack>;
			template class fight::PropertyBool<FixedDestinationJumpToTrack>;
			template class fight::TrackFactoryTemplate<FixedDestinationJumpToTrack>;
			template class fight::TrackFactoryCasterTemplate<FixedDestinationJumpToTrack>;
			template class fight::PropertyFloatConstRange<ClearFixedAreaDestinationTrack>;
			template class fight::PropertyBool<ClearFixedAreaDestinationTrack>;
			template class fight::TrackFactoryTemplate<ClearFixedAreaDestinationTrack>;
			template class fight::TrackFactoryCasterTemplate<ClearFixedAreaDestinationTrack>;
			template class fight::PropertyFloatConstRange<FixedDestinationFlytoTrack>;
			template class fight::PropertyBool<FixedDestinationFlytoTrack>;
			template class fight::PropertyVector<FixedDestinationFlytoTrack>;
			template class fight::TrackFactoryTemplate<FixedDestinationFlytoTrack>;
			template class fight::TrackFactoryCasterTemplate<FixedDestinationFlytoTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10230BD0
// FUNCTION: ENGINE 0x10230C00
// FUNCTION: ENGINE 0x10230C30
// FUNCTION: ENGINE 0x10230C60
// FUNCTION: ENGINE 0x10230C90
// FUNCTION: ENGINE 0x10230CC0
// FUNCTION: ENGINE 0x10230CD0
// FUNCTION: ENGINE 0x10230D00
// FUNCTION: ENGINE 0x10230D10
// FUNCTION: ENGINE 0x10230D40
// FUNCTION: ENGINE 0x10230D50
// FUNCTION: ENGINE 0x10230D80
// FUNCTION: ENGINE 0x10230D90
// FUNCTION: ENGINE 0x10230DC0
// FUNCTION: ENGINE 0x10230DD0
// FUNCTION: ENGINE 0x10230E00
// FUNCTION: ENGINE 0x10230E40
// FUNCTION: ENGINE 0x10230E50
// FUNCTION: ENGINE 0x10230E80
// FUNCTION: ENGINE 0x10230EA0
// FUNCTION: ENGINE 0x10230EB0
// FUNCTION: ENGINE 0x10230EE0
// FUNCTION: ENGINE 0x10230F10
// FUNCTION: ENGINE 0x10230F20
// FUNCTION: ENGINE 0x10230F50
// FUNCTION: ENGINE 0x10230F80
// FUNCTION: ENGINE 0x10230F90
// FUNCTION: ENGINE 0x10230FC0
// FUNCTION: ENGINE 0x10230FE0
// FUNCTION: ENGINE 0x10230FF0
// FUNCTION: ENGINE 0x10231020
// FUNCTION: ENGINE 0x10231050
// FUNCTION: ENGINE 0x10231060
// FUNCTION: ENGINE 0x10231090
// FUNCTION: ENGINE 0x102310B0
// FUNCTION: ENGINE 0x102310C0
// FUNCTION: ENGINE 0x102310F0
// FUNCTION: ENGINE 0x10231120
// FUNCTION: ENGINE 0x10231130
// FUNCTION: ENGINE 0x10231160
// FUNCTION: ENGINE 0x10231180
// FUNCTION: ENGINE 0x10231190
// FUNCTION: ENGINE 0x102311C0
// FUNCTION: ENGINE 0x102311F0
// FUNCTION: ENGINE 0x10231200
// FUNCTION: ENGINE 0x10231230
// FUNCTION: ENGINE 0x10231250
// FUNCTION: ENGINE 0x10231260
// FUNCTION: ENGINE 0x10231290
// FUNCTION: ENGINE 0x102312B0
// FUNCTION: ENGINE 0x10231C90
// FUNCTION: ENGINE 0x10231CC0
// FUNCTION: ENGINE 0x10231CE0
// FUNCTION: ENGINE 0x10231D10
// FUNCTION: ENGINE 0x10231D30
// FUNCTION: ENGINE 0x10231D60
// FUNCTION: ENGINE 0x10231D80
// FUNCTION: ENGINE 0x10231DB0
// FUNCTION: ENGINE 0x10231DD0
// FUNCTION: ENGINE 0x10231E00
// FUNCTION: ENGINE 0x10231E20
// FUNCTION: ENGINE 0x10231E70
// FUNCTION: ENGINE 0x10231EC0
// FUNCTION: ENGINE 0x10231F10
// FUNCTION: ENGINE 0x10231F60
