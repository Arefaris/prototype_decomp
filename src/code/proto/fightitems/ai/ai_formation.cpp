// Fight items of the ai group: InFormationCondition, FormationReformingCondition, FollowFormationTrack, FollowTargetTrack, ReformTrack (unit 0x10232390 - 0x102338F0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_formation.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gInFormationConditionProperties;  // 0x112559E4

			// FUNCTION: ENGINE 0x10232390
			bool InFormationCondition::SetIn(bool newValue)
			{
				in = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102325C0
			fight::Property* InFormationCondition::GetProperty(int index)
			{
				return gInFormationConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x102325E0
			void InFormationCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInFormationConditionProperties);
			}

			// FUNCTION: ENGINE 0x102325F0
			InFormationCondition::InFormationCondition() : fight::Condition(0), in(true)
			{
			}

			// FUNCTION: ENGINE 0x10232610
			InFormationCondition::~InFormationCondition()
			{
			}

			// FUNCTION: ENGINE 0x10232E70
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InFormationCondition::RegisterProperties()
			{
				if (gInFormationConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<InFormationCondition>("in", &InFormationCondition::SetIn);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gInFormationConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10232D80
			fight::ConditionFactory* CreateInFormationConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InFormationCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102334E0
			void RegisterInFormationConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InFormationCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gFormationReformingConditionProperties;  // 0x112559E8

			// FUNCTION: ENGINE 0x102323A0
			bool FormationReformingCondition::SetReforming(bool newValue)
			{
				reforming = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10232620
			fight::Property* FormationReformingCondition::GetProperty(int index)
			{
				return gFormationReformingConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10232640
			void FormationReformingCondition::ClearProperties()
			{
				fight::FreePropertyList(&gFormationReformingConditionProperties);
			}

			// FUNCTION: ENGINE 0x10232650
			FormationReformingCondition::FormationReformingCondition() : fight::Condition(0), reforming(true)
			{
			}

			// FUNCTION: ENGINE 0x10232670
			FormationReformingCondition::~FormationReformingCondition()
			{
			}

			// FUNCTION: ENGINE 0x10232F10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FormationReformingCondition::RegisterProperties()
			{
				if (gFormationReformingConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<FormationReformingCondition>("reforming", &FormationReformingCondition::SetReforming);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gFormationReformingConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10232DB0
			fight::ConditionFactory* CreateFormationReformingConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FormationReformingCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10233510
			void RegisterFormationReformingConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<FormationReformingCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gFollowFormationTrackProperties;  // 0x112559EC

			// FUNCTION: ENGINE 0x102323B0
			bool FollowFormationTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102323D0
			bool FollowFormationTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102323F0
			bool FollowFormationTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10232410
			bool FollowFormationTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10232430
			bool FollowFormationTrack::SetBrakingDeceleration(float newValue)
			{
				brakingDeceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10232450
			bool FollowFormationTrack::SetExtraBrakingDistance(float newValue)
			{
				extraBrakingDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10232470
			bool FollowFormationTrack::SetLookAhead(float newValue)
			{
				lookAhead = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10232490
			bool FollowFormationTrack::SetMaxVelocity(float newValue)
			{
				maxVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10232680
			fight::Property* FollowFormationTrack::GetProperty(int index)
			{
				return gFollowFormationTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102326A0
			void FollowFormationTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFollowFormationTrackProperties);
			}

			// FUNCTION: ENGINE 0x102326B0
			FollowFormationTrack::FollowFormationTrack() : acceleration(5.0f), brakingDeceleration(1.0f), extraBrakingDistance(5.0f), lookAhead(2.0f), maxVelocity(1.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(6.2831855f)
			{
			}

			// FUNCTION: ENGINE 0x10232730
			float FollowFormationTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10232740
			float FollowFormationTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10232750
			FollowFormationTrack::~FollowFormationTrack()
			{
			}

			// FUNCTION: ENGINE 0x10232FB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FollowFormationTrack::RegisterProperties()
			{
				if (gFollowFormationTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FollowFormationTrack>("timeBegin", &FollowFormationTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FollowFormationTrack>("timeEnd", &FollowFormationTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FollowFormationTrack>("turningVelocity", &FollowFormationTrack::SetTurningVelocity);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<FollowFormationTrack>("acceleration", &FollowFormationTrack::SetAcceleration);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<FollowFormationTrack>("brakingDeceleration", &FollowFormationTrack::SetBrakingDeceleration);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<FollowFormationTrack>("extraBrakingDistance", &FollowFormationTrack::SetExtraBrakingDistance);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<FollowFormationTrack>("lookAhead", &FollowFormationTrack::SetLookAhead);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<FollowFormationTrack>("maxVelocity", &FollowFormationTrack::SetMaxVelocity);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gFollowFormationTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10232DE0
			fight::TrackFactory* CreateFollowFormationTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FollowFormationTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10233540
			void RegisterFollowFormationTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FollowFormationTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gFollowTargetTrackProperties;  // 0x112559F0

			// FUNCTION: ENGINE 0x102324B0
			bool FollowTargetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102324D0
			bool FollowTargetTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102324F0
			bool FollowTargetTrack::SetMaxAngleFromTargetFacing(float newValue)
			{
				maxAngleFromTargetFacing = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10232510
			bool FollowTargetTrack::SetMaxMotionLengthDelta(float newValue)
			{
				maxMotionLengthDelta = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10232530
			bool FollowTargetTrack::SetMaxRotationDelta(float newValue)
			{
				maxRotationDelta = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10232550
			bool FollowTargetTrack::SetSmoothWithLast(bool newValue)
			{
				smoothWithLast = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10232760
			fight::Property* FollowTargetTrack::GetProperty(int index)
			{
				return gFollowTargetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10232780
			void FollowTargetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFollowTargetTrackProperties);
			}

			// FUNCTION: ENGINE 0x10232790
			FollowTargetTrack::FollowTargetTrack() : maxAngleFromTargetFacing(0.5235988f), maxMotionLengthDelta(1.0f), maxRotationDelta(0.17453294f), timeBegin(0.0f), timeEnd(-1.0f), smoothWithLast(true)
			{
			}

			// FUNCTION: ENGINE 0x10232800
			float FollowTargetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10232810
			float FollowTargetTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10232820
			FollowTargetTrack::~FollowTargetTrack()
			{
			}

			// FUNCTION: ENGINE 0x10233200
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FollowTargetTrack::RegisterProperties()
			{
				if (gFollowTargetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FollowTargetTrack>("timeBegin", &FollowTargetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FollowTargetTrack>("timeEnd", &FollowTargetTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FollowTargetTrack>("maxAngleFromTargetFacing", &FollowTargetTrack::SetMaxAngleFromTargetFacing);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<FollowTargetTrack>("maxMotionLengthDelta", &FollowTargetTrack::SetMaxMotionLengthDelta);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<FollowTargetTrack>("maxRotationDelta", &FollowTargetTrack::SetMaxRotationDelta);
					properties[4] = property;
					property = new fight::PropertyBool<FollowTargetTrack>("smoothWithLast", &FollowTargetTrack::SetSmoothWithLast);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gFollowTargetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10232E10
			fight::TrackFactory* CreateFollowTargetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FollowTargetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10233570
			void RegisterFollowTargetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FollowTargetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gReformTrackProperties;  // 0x112559F4

			// FUNCTION: ENGINE 0x10232560
			bool ReformTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10232580
			bool ReformTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102325A0
			bool ReformTrack::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10232830
			fight::Property* ReformTrack::GetProperty(int index)
			{
				return gReformTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10232850
			void ReformTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReformTrackProperties);
			}

			// FUNCTION: ENGINE 0x10232860
			ReformTrack::ReformTrack() : timeBegin(0.0f), timeEnd(-1.0f), tolerance(5.0f)
			{
			}

			// FUNCTION: ENGINE 0x102328B0
			float ReformTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x102328C0
			float ReformTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x102328D0
			ReformTrack::~ReformTrack()
			{
			}

			// FUNCTION: ENGINE 0x102333D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReformTrack::RegisterProperties()
			{
				if (gReformTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReformTrack>("timeBegin", &ReformTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReformTrack>("timeEnd", &ReformTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReformTrack>("tolerance", &ReformTrack::SetTolerance);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gReformTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10232E40
			fight::TrackFactory* CreateReformTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReformTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102335A0
			void RegisterReformTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReformTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyBool<InFormationCondition>;
			template class fight::ConditionFactoryTemplate<InFormationCondition>;
			template class fight::ConditionFactoryCasterTemplate<InFormationCondition>;
			template class fight::PropertyBool<FormationReformingCondition>;
			template class fight::ConditionFactoryTemplate<FormationReformingCondition>;
			template class fight::ConditionFactoryCasterTemplate<FormationReformingCondition>;
			template class fight::PropertyFloatConstRange<FollowFormationTrack>;
			template class fight::TrackFactoryTemplate<FollowFormationTrack>;
			template class fight::TrackFactoryCasterTemplate<FollowFormationTrack>;
			template class fight::PropertyFloatConstRange<FollowTargetTrack>;
			template class fight::PropertyBool<FollowTargetTrack>;
			template class fight::TrackFactoryTemplate<FollowTargetTrack>;
			template class fight::TrackFactoryCasterTemplate<FollowTargetTrack>;
			template class fight::PropertyFloatConstRange<ReformTrack>;
			template class fight::TrackFactoryTemplate<ReformTrack>;
			template class fight::TrackFactoryCasterTemplate<ReformTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102328E0
// FUNCTION: ENGINE 0x10232910
// FUNCTION: ENGINE 0x10232940
// FUNCTION: ENGINE 0x10232970
// FUNCTION: ENGINE 0x102329A0
// FUNCTION: ENGINE 0x102329D0
// FUNCTION: ENGINE 0x102329E0
// FUNCTION: ENGINE 0x10232A10
// FUNCTION: ENGINE 0x10232A20
// FUNCTION: ENGINE 0x10232A50
// FUNCTION: ENGINE 0x10232A60
// FUNCTION: ENGINE 0x10232A90
// FUNCTION: ENGINE 0x10232AA0
// FUNCTION: ENGINE 0x10232AD0
// FUNCTION: ENGINE 0x10232AE0
// FUNCTION: ENGINE 0x10232B10
// FUNCTION: ENGINE 0x10232B40
// FUNCTION: ENGINE 0x10232B60
// FUNCTION: ENGINE 0x10232B70
// FUNCTION: ENGINE 0x10232BA0
// FUNCTION: ENGINE 0x10232BC0
// FUNCTION: ENGINE 0x10232BD0
// FUNCTION: ENGINE 0x10232C00
// FUNCTION: ENGINE 0x10232C30
// FUNCTION: ENGINE 0x10232C40
// FUNCTION: ENGINE 0x10232C70
// FUNCTION: ENGINE 0x10232CA0
// FUNCTION: ENGINE 0x10232CB0
// FUNCTION: ENGINE 0x10232CE0
// FUNCTION: ENGINE 0x10232D00
// FUNCTION: ENGINE 0x10232D10
// FUNCTION: ENGINE 0x10232D40
// FUNCTION: ENGINE 0x10232D70
// FUNCTION: ENGINE 0x102335D0
// FUNCTION: ENGINE 0x10233600
// FUNCTION: ENGINE 0x10233620
// FUNCTION: ENGINE 0x10233650
// FUNCTION: ENGINE 0x10233670
// FUNCTION: ENGINE 0x102336A0
// FUNCTION: ENGINE 0x102336C0
// FUNCTION: ENGINE 0x102336F0
// FUNCTION: ENGINE 0x10233710
// FUNCTION: ENGINE 0x10233740
// FUNCTION: ENGINE 0x10233760
// FUNCTION: ENGINE 0x102337B0
// FUNCTION: ENGINE 0x10233800
// FUNCTION: ENGINE 0x10233850
// FUNCTION: ENGINE 0x102338A0
