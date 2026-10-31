// Fight items of the motion group: DetectedObjectFacingCondition, DetectedObjectAngleCondition, DetectedObjectDistanceCondition, DetectedObjectIsTargetCondition, DetectedObjectConditionGroupCondition, DetectedObjectIsSeenCondition, DetectTrack (unit 0x10154030 - 0x101561B0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/detect.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gDetectedObjectFacingConditionProperties;  // 0x112543E8

			// FUNCTION: ENGINE 0x10154030
			bool DetectedObjectFacingCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10154050
			bool DetectedObjectFacingCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101542B0
			fight::Property* DetectedObjectFacingCondition::GetProperty(int index)
			{
				return gDetectedObjectFacingConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101542D0
			void DetectedObjectFacingCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDetectedObjectFacingConditionProperties);
			}

			// FUNCTION: ENGINE 0x101542E0
			DetectedObjectFacingCondition::DetectedObjectFacingCondition() : fight::Condition(0), angle(0.0f), arc(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x10154310
			DetectedObjectFacingCondition::~DetectedObjectFacingCondition()
			{
			}

			// FUNCTION: ENGINE 0x10155220
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DetectedObjectFacingCondition::RegisterProperties()
			{
				if (gDetectedObjectFacingConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DetectedObjectFacingCondition>("angle", &DetectedObjectFacingCondition::SetAngle);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DetectedObjectFacingCondition>("arc", &DetectedObjectFacingCondition::SetArc);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gDetectedObjectFacingConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101550D0
			fight::ConditionFactory* CreateDetectedObjectFacingConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectedObjectFacingCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10155880
			void RegisterDetectedObjectFacingConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectedObjectFacingCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDetectedObjectAngleConditionProperties;  // 0x112543EC

			// FUNCTION: ENGINE 0x10154070
			bool DetectedObjectAngleCondition::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10154080
			bool DetectedObjectAngleCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101540A0
			bool DetectedObjectAngleCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10154320
			fight::Property* DetectedObjectAngleCondition::GetProperty(int index)
			{
				return gDetectedObjectAngleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10154340
			void DetectedObjectAngleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDetectedObjectAngleConditionProperties);
			}

			// FUNCTION: ENGINE 0x10154350
			DetectedObjectAngleCondition::DetectedObjectAngleCondition() : fight::Condition(0), angle(0.0f), arc(0.0f), type(0)
			{
			}

			// FUNCTION: ENGINE 0x10154390
			DetectedObjectAngleCondition::~DetectedObjectAngleCondition()
			{
			}

			// FUNCTION: ENGINE 0x10155300
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DetectedObjectAngleCondition::RegisterProperties()
			{
				if (gDetectedObjectAngleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<DetectedObjectAngleCondition>("type", gDetectedObjectAngleConditionTypeTable, 2, &DetectedObjectAngleCondition::SetType);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DetectedObjectAngleCondition>("angle", &DetectedObjectAngleCondition::SetAngle);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DetectedObjectAngleCondition>("arc", &DetectedObjectAngleCondition::SetArc);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gDetectedObjectAngleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10155100
			fight::ConditionFactory* CreateDetectedObjectAngleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectedObjectAngleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101558B0
			void RegisterDetectedObjectAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectedObjectAngleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDetectedObjectDistanceConditionProperties;  // 0x112543F0

			// FUNCTION: ENGINE 0x101540C0
			bool DetectedObjectDistanceCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101540D0
			bool DetectedObjectDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101540E0
			bool DetectedObjectDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101543A0
			fight::Property* DetectedObjectDistanceCondition::GetProperty(int index)
			{
				return gDetectedObjectDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101543C0
			void DetectedObjectDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDetectedObjectDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x101543D0
			DetectedObjectDistanceCondition::DetectedObjectDistanceCondition() : fight::Condition(0), distance(2e+01f), compare(4), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x10154410
			DetectedObjectDistanceCondition::~DetectedObjectDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10155430
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DetectedObjectDistanceCondition::RegisterProperties()
			{
				if (gDetectedObjectDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<DetectedObjectDistanceCondition>("direction", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &DetectedObjectDistanceCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<DetectedObjectDistanceCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &DetectedObjectDistanceCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DetectedObjectDistanceCondition>("distance", &DetectedObjectDistanceCondition::SetDistance);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gDetectedObjectDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10155130
			fight::ConditionFactory* CreateDetectedObjectDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectedObjectDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101558E0
			void RegisterDetectedObjectDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectedObjectDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDetectedObjectIsTargetConditionProperties;  // 0x112543F4

			// FUNCTION: ENGINE 0x10154100
			bool DetectedObjectIsTargetCondition::SetIsTarget(bool newValue)
			{
				isTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10154420
			fight::Property* DetectedObjectIsTargetCondition::GetProperty(int index)
			{
				return gDetectedObjectIsTargetConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10154440
			void DetectedObjectIsTargetCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDetectedObjectIsTargetConditionProperties);
			}

			// FUNCTION: ENGINE 0x10154450
			DetectedObjectIsTargetCondition::DetectedObjectIsTargetCondition() : fight::Condition(0), isTarget(true)
			{
			}

			// FUNCTION: ENGINE 0x10154470
			DetectedObjectIsTargetCondition::~DetectedObjectIsTargetCondition()
			{
			}

			// FUNCTION: ENGINE 0x10155570
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DetectedObjectIsTargetCondition::RegisterProperties()
			{
				if (gDetectedObjectIsTargetConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<DetectedObjectIsTargetCondition>("isTarget", &DetectedObjectIsTargetCondition::SetIsTarget);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gDetectedObjectIsTargetConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10155160
			fight::ConditionFactory* CreateDetectedObjectIsTargetConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectedObjectIsTargetCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10155910
			void RegisterDetectedObjectIsTargetConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectedObjectIsTargetCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDetectedObjectConditionGroupConditionProperties;  // 0x112543F8

			// FUNCTION: ENGINE 0x10154110
			fight::ConditionList* DetectedObjectConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x10154480
			fight::Property* DetectedObjectConditionGroupCondition::GetProperty(int index)
			{
				return gDetectedObjectConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101544A0
			void DetectedObjectConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDetectedObjectConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x101544B0
			DetectedObjectConditionGroupCondition::DetectedObjectConditionGroupCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x101544E0
			DetectedObjectConditionGroupCondition::~DetectedObjectConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x10155610
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DetectedObjectConditionGroupCondition::RegisterProperties()
			{
				if (gDetectedObjectConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyConditionGroup<DetectedObjectConditionGroupCondition>("conditions", &DetectedObjectConditionGroupCondition::SetConditions);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gDetectedObjectConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10155190
			fight::ConditionFactory* CreateDetectedObjectConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectedObjectConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10155940
			void RegisterDetectedObjectConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectedObjectConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDetectedObjectIsSeenConditionProperties;  // 0x112543FC

			// FUNCTION: ENGINE 0x10154120
			bool DetectedObjectIsSeenCondition::SetSeen(bool newValue)
			{
				seen = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10154130
			bool DetectedObjectIsSeenCondition::SetMaxDistanceFactor(float newValue)
			{
				maxDistanceFactor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10154150
			bool DetectedObjectIsSeenCondition::SetMaxAngle(float newValue)
			{
				maxAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10154170
			bool DetectedObjectIsSeenCondition::SetOnlyMilitary(bool newValue)
			{
				onlyMilitary = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10154180
			bool DetectedObjectIsSeenCondition::SetExcludeIfCantReport(bool newValue)
			{
				excludeIfCantReport = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10154190
			bool DetectedObjectIsSeenCondition::SetMaxDistance(float newValue)
			{
				maxDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10154500
			fight::Property* DetectedObjectIsSeenCondition::GetProperty(int index)
			{
				return gDetectedObjectIsSeenConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10154520
			void DetectedObjectIsSeenCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDetectedObjectIsSeenConditionProperties);
			}

			// FUNCTION: ENGINE 0x10154530
			DetectedObjectIsSeenCondition::DetectedObjectIsSeenCondition() : fight::Condition(0), maxAngle(3.1415927f), maxDistance(1e+01f), maxDistanceFactor(1.0f), excludeIfCantReport(false), onlyMilitary(false), seen(true)
			{
			}

			// FUNCTION: ENGINE 0x10154590
			DetectedObjectIsSeenCondition::~DetectedObjectIsSeenCondition()
			{
			}

			// FUNCTION: ENGINE 0x101556B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DetectedObjectIsSeenCondition::RegisterProperties()
			{
				if (gDetectedObjectIsSeenConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<DetectedObjectIsSeenCondition>("seen", &DetectedObjectIsSeenCondition::SetSeen);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DetectedObjectIsSeenCondition>("maxDistanceFactor", &DetectedObjectIsSeenCondition::SetMaxDistanceFactor);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DetectedObjectIsSeenCondition>("maxAngle", &DetectedObjectIsSeenCondition::SetMaxAngle);
					properties[2] = property;
					property = new fight::PropertyBool<DetectedObjectIsSeenCondition>("onlyMilitary", &DetectedObjectIsSeenCondition::SetOnlyMilitary);
					properties[3] = property;
					property = new fight::PropertyBool<DetectedObjectIsSeenCondition>("excludeIfCantReport", &DetectedObjectIsSeenCondition::SetExcludeIfCantReport);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<DetectedObjectIsSeenCondition>("maxDistance", &DetectedObjectIsSeenCondition::SetMaxDistance);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gDetectedObjectIsSeenConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101551C0
			fight::ConditionFactory* CreateDetectedObjectIsSeenConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectedObjectIsSeenCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10155970
			void RegisterDetectedObjectIsSeenConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DetectedObjectIsSeenCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDetectTrackProperties;  // 0x11254400

			// FUNCTION: ENGINE 0x101541B0
			bool DetectTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101541D0
			bool DetectTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101545D0
			bool DetectTrack::SetJoint(const fight::Name& newValue)
			{
				joint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101541F0
			bool DetectTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10154210
			bool DetectTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10154230
			bool DetectTrack::SetArcOffset(float newValue)
			{
				arcOffset = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10154250
			bool DetectTrack::SetArcRange(float newValue)
			{
				arcRange = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10154270
			bool DetectTrack::SetCollideWith(int newValue)
			{
				collideWith = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10154280
			fight::BranchHolder* DetectTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x10154290
			bool DetectTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101542A0
			fight::ConditionList* DetectTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x101545A0
			fight::Property* DetectTrack::GetProperty(int index)
			{
				return gDetectTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101545C0
			void DetectTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDetectTrackProperties);
			}

			// FUNCTION: ENGINE 0x10154710
			DetectTrack::DetectTrack() : branch(0), offset(0.0f, 0.0f, 0.0f), arcOffset(0.0f), arcRange(0.0f), radius(1.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0), collideWith(gDetectTrackCollideWithDefault)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101547B0
			float DetectTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101547C0
			float DetectTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101547D0
			DetectTrack::~DetectTrack()
			{
			}

			// FUNCTION: ENGINE 0x10155C10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DetectTrack::RegisterProperties()
			{
				if (gDetectTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DetectTrack>("timeBegin", &DetectTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DetectTrack>("timeEnd", &DetectTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<DetectTrack>("joint", &DetectTrack::SetJoint);
					properties[2] = property;
					property = new fight::PropertyVector<DetectTrack>("offset", &DetectTrack::SetOffset);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<DetectTrack>("radius", &DetectTrack::SetRadius);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<DetectTrack>("arcOffset", &DetectTrack::SetArcOffset);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<DetectTrack>("arcRange", &DetectTrack::SetArcRange);
					properties[6] = property;
					property = new fight::PropertyBitfieldConstList<DetectTrack>("collideWith", gDetectObbCollisionConditionCollideWithTable, gDetectObbCollisionConditionCollideWithCount, &DetectTrack::SetCollideWith);
					properties[7] = property;
					property = new fight::PropertyBranch<DetectTrack>("branch", &DetectTrack::SetBranch);
					properties[8] = property;
					property = new fight::PropertyIntConstRange<DetectTrack>("priority", &DetectTrack::SetPriority);
					properties[9] = property;
					property = new fight::PropertyConditionGroup<DetectTrack>("conditions", &DetectTrack::SetConditions);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gDetectTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101551F0
			fight::TrackFactory* CreateDetectTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DetectTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101559A0
			void RegisterDetectTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DetectTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<DetectedObjectFacingCondition>;
			template class fight::ConditionFactoryTemplate<DetectedObjectFacingCondition>;
			template class fight::ConditionFactoryCasterTemplate<DetectedObjectFacingCondition>;
			template class fight::PropertyEnumConstList<DetectedObjectAngleCondition>;
			template class fight::PropertyFloatConstRange<DetectedObjectAngleCondition>;
			template class fight::ConditionFactoryTemplate<DetectedObjectAngleCondition>;
			template class fight::ConditionFactoryCasterTemplate<DetectedObjectAngleCondition>;
			template class fight::PropertyEnumConstList<DetectedObjectDistanceCondition>;
			template class fight::PropertyFloatConstRange<DetectedObjectDistanceCondition>;
			template class fight::ConditionFactoryTemplate<DetectedObjectDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<DetectedObjectDistanceCondition>;
			template class fight::PropertyBool<DetectedObjectIsTargetCondition>;
			template class fight::ConditionFactoryTemplate<DetectedObjectIsTargetCondition>;
			template class fight::ConditionFactoryCasterTemplate<DetectedObjectIsTargetCondition>;
			template class fight::PropertyConditionGroup<DetectedObjectConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<DetectedObjectConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<DetectedObjectConditionGroupCondition>;
			template class fight::PropertyBool<DetectedObjectIsSeenCondition>;
			template class fight::PropertyFloatConstRange<DetectedObjectIsSeenCondition>;
			template class fight::ConditionFactoryTemplate<DetectedObjectIsSeenCondition>;
			template class fight::ConditionFactoryCasterTemplate<DetectedObjectIsSeenCondition>;
			template class fight::PropertyFloatConstRange<DetectTrack>;
			template class fight::PropertyNameList<DetectTrack>;
			template class fight::PropertyVector<DetectTrack>;
			template class fight::PropertyBitfieldConstList<DetectTrack>;
			template class fight::PropertyBranch<DetectTrack>;
			template class fight::PropertyIntConstRange<DetectTrack>;
			template class fight::PropertyConditionGroup<DetectTrack>;
			template class fight::TrackFactoryTemplate<DetectTrack>;
			template class fight::TrackFactoryCasterTemplate<DetectTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101545F0
// FUNCTION: ENGINE 0x10154620
// FUNCTION: ENGINE 0x10154650
// FUNCTION: ENGINE 0x10154680
// FUNCTION: ENGINE 0x101546B0
// FUNCTION: ENGINE 0x101546E0
// FUNCTION: ENGINE 0x10154800
// FUNCTION: ENGINE 0x10154810
// FUNCTION: ENGINE 0x10154840
// FUNCTION: ENGINE 0x10154850
// FUNCTION: ENGINE 0x10154880
// FUNCTION: ENGINE 0x10154890
// FUNCTION: ENGINE 0x101548C0
// FUNCTION: ENGINE 0x101548D0
// FUNCTION: ENGINE 0x10154900
// FUNCTION: ENGINE 0x10154910
// FUNCTION: ENGINE 0x10154940
// FUNCTION: ENGINE 0x10154950
// FUNCTION: ENGINE 0x10154980
// FUNCTION: ENGINE 0x10154990
// FUNCTION: ENGINE 0x101549C0
// FUNCTION: ENGINE 0x101549F0
// FUNCTION: ENGINE 0x10154A20
// FUNCTION: ENGINE 0x10154A50
// FUNCTION: ENGINE 0x10154A60
// FUNCTION: ENGINE 0x10154AA0
// FUNCTION: ENGINE 0x10154AB0
// FUNCTION: ENGINE 0x10154AE0
// FUNCTION: ENGINE 0x10154B00
// FUNCTION: ENGINE 0x10154B10
// FUNCTION: ENGINE 0x10154B40
// FUNCTION: ENGINE 0x10154B70
// FUNCTION: ENGINE 0x10154B80
// FUNCTION: ENGINE 0x10154BC0
// FUNCTION: ENGINE 0x10154BD0
// FUNCTION: ENGINE 0x10154C00
// FUNCTION: ENGINE 0x10154C20
// FUNCTION: ENGINE 0x10154C30
// FUNCTION: ENGINE 0x10154C60
// FUNCTION: ENGINE 0x10154C90
// FUNCTION: ENGINE 0x10154CA0
// FUNCTION: ENGINE 0x10154CD0
// FUNCTION: ENGINE 0x10154CF0
// FUNCTION: ENGINE 0x10154D00
// FUNCTION: ENGINE 0x10154D30
// FUNCTION: ENGINE 0x10154D50
// FUNCTION: ENGINE 0x10154D80
// FUNCTION: ENGINE 0x10154DA0
// FUNCTION: ENGINE 0x10154DB0
// FUNCTION: ENGINE 0x10154DE0
// FUNCTION: ENGINE 0x10154E10
// FUNCTION: ENGINE 0x10154E20
// FUNCTION: ENGINE 0x10154E50
// FUNCTION: ENGINE 0x10154E80
// FUNCTION: ENGINE 0x10154E90
// FUNCTION: ENGINE 0x10154EC0
// FUNCTION: ENGINE 0x10154EE0
// FUNCTION: ENGINE 0x10154EF0
// FUNCTION: ENGINE 0x10154F30
// FUNCTION: ENGINE 0x10154F40
// FUNCTION: ENGINE 0x10154F60
// FUNCTION: ENGINE 0x10154F70
// FUNCTION: ENGINE 0x10154FD0
// FUNCTION: ENGINE 0x10155000
// FUNCTION: ENGINE 0x10155020
// FUNCTION: ENGINE 0x10155050
// FUNCTION: ENGINE 0x10155070
// FUNCTION: ENGINE 0x10155080
// FUNCTION: ENGINE 0x101550B0
// FUNCTION: ENGINE 0x101559D0
// FUNCTION: ENGINE 0x10155A00
// FUNCTION: ENGINE 0x10155A20
// FUNCTION: ENGINE 0x10155A30
// FUNCTION: ENGINE 0x10155A60
// FUNCTION: ENGINE 0x10155A80
// FUNCTION: ENGINE 0x10155AB0
// FUNCTION: ENGINE 0x10155AD0
// FUNCTION: ENGINE 0x10155B00
// FUNCTION: ENGINE 0x10155B20
// FUNCTION: ENGINE 0x10155B50
// FUNCTION: ENGINE 0x10155B70
// FUNCTION: ENGINE 0x10155BA0
// FUNCTION: ENGINE 0x10155BC0
// FUNCTION: ENGINE 0x10155BF0
// FUNCTION: ENGINE 0x10155F30
// FUNCTION: ENGINE 0x10155F80
// FUNCTION: ENGINE 0x10155FD0
// FUNCTION: ENGINE 0x10156020
// FUNCTION: ENGINE 0x10156070
// FUNCTION: ENGINE 0x101560C0
// FUNCTION: ENGINE 0x10156110
// FUNCTION: ENGINE 0x10156140
// FUNCTION: ENGINE 0x10156160
