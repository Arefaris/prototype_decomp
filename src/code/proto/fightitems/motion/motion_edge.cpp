// Fight items of the motion group: EdgeNormalCondition, EdgePositionCondition, EdgeDetectTrack, EdgeSynchronizeTrack (unit 0x1015AC70 - 0x1015C310; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_edge.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gEdgeNormalConditionProperties;  // 0x11254478

			// FUNCTION: ENGINE 0x1015AC70
			bool EdgeNormalCondition::SetNormal(const math::Vector& newValue)
			{
				normal.x = newValue.x;
				normal.y = newValue.y;
				normal.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1015AC90
			bool EdgeNormalCondition::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1015AEB0
			fight::Property* EdgeNormalCondition::GetProperty(int index)
			{
				return gEdgeNormalConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1015AED0
			void EdgeNormalCondition::ClearProperties()
			{
				fight::FreePropertyList(&gEdgeNormalConditionProperties);
			}

			// FUNCTION: ENGINE 0x1015AEE0
			EdgeNormalCondition::EdgeNormalCondition() : fight::Condition(0), normal(0.0f, 1.0f, 0.0f), arc(1.5707964f)
			{
			}

			// FUNCTION: ENGINE 0x1015AF30
			EdgeNormalCondition::~EdgeNormalCondition()
			{
			}

			// FUNCTION: ENGINE 0x1015B920
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EdgeNormalCondition::RegisterProperties()
			{
				if (gEdgeNormalConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyVector<EdgeNormalCondition>("normal", &EdgeNormalCondition::SetNormal);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<EdgeNormalCondition>("arc", &EdgeNormalCondition::SetArc);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gEdgeNormalConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015B860
			fight::ConditionFactory* CreateEdgeNormalConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<EdgeNormalCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015BFD0
			void RegisterEdgeNormalConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<EdgeNormalCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gEdgePositionConditionProperties;  // 0x1125447C

			// FUNCTION: ENGINE 0x1015ACB0
			bool EdgePositionCondition::SetComponent(int newValue)
			{
				component = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015ACC0
			bool EdgePositionCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015ACD0
			bool EdgePositionCondition::SetOffset(float newValue)
			{
				offset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015AF40
			fight::Property* EdgePositionCondition::GetProperty(int index)
			{
				return gEdgePositionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1015AF60
			void EdgePositionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gEdgePositionConditionProperties);
			}

			// FUNCTION: ENGINE 0x1015AF70
			EdgePositionCondition::EdgePositionCondition() : fight::Condition(0), offset(0.0f), compare(0), component(2)
			{
			}

			// FUNCTION: ENGINE 0x1015AFB0
			EdgePositionCondition::~EdgePositionCondition()
			{
			}

			// FUNCTION: ENGINE 0x1015BA00
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EdgePositionCondition::RegisterProperties()
			{
				if (gEdgePositionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<EdgePositionCondition>("component", gEdgePositionConditionComponentTable, 3, &EdgePositionCondition::SetComponent);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<EdgePositionCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &EdgePositionCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<EdgePositionCondition>("offset", &EdgePositionCondition::SetOffset);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gEdgePositionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015B890
			fight::ConditionFactory* CreateEdgePositionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<EdgePositionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015C000
			void RegisterEdgePositionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<EdgePositionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gEdgeDetectTrackProperties;  // 0x11254480

			// FUNCTION: ENGINE 0x1015ACF0
			bool EdgeDetectTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015AD10
			bool EdgeDetectTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015AD30
			bool EdgeDetectTrack::SetSurfaceOffset(float newValue)
			{
				surfaceOffset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015AD50
			bool EdgeDetectTrack::SetLookaheadDistance(float newValue)
			{
				lookaheadDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015AD70
			bool EdgeDetectTrack::SetEdgeDepth(float newValue)
			{
				edgeDepth = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015AD90
			bool EdgeDetectTrack::SetCardinalVector(const math::Vector& newValue)
			{
				cardinalVector.x = newValue.x;
				cardinalVector.y = newValue.y;
				cardinalVector.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1015ADB0
			bool EdgeDetectTrack::SetLookaheadDistanceNonCardinal(float newValue)
			{
				lookaheadDistanceNonCardinal = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015ADD0
			fight::BranchHolder* EdgeDetectTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x1015ADE0
			bool EdgeDetectTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015ADF0
			fight::ConditionList* EdgeDetectTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1015AFC0
			fight::Property* EdgeDetectTrack::GetProperty(int index)
			{
				return gEdgeDetectTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1015AFE0
			void EdgeDetectTrack::ClearProperties()
			{
				fight::FreePropertyList(&gEdgeDetectTrackProperties);
			}

			// FUNCTION: ENGINE 0x1015AFF0
			EdgeDetectTrack::EdgeDetectTrack() : branch(0), cardinalVector(0.0f, 0.0f, 0.0f), edgeDepth(1.0f), lookaheadDistance(1.0f), lookaheadDistanceNonCardinal(1.0f), surfaceOffset(0.5f), timeBegin(0.0f), timeEnd(-1.0f), priority(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1015B090
			float EdgeDetectTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1015B0A0
			float EdgeDetectTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1015B0B0
			EdgeDetectTrack::~EdgeDetectTrack()
			{
			}

			// FUNCTION: ENGINE 0x1015BB40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EdgeDetectTrack::RegisterProperties()
			{
				if (gEdgeDetectTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<EdgeDetectTrack>("timeBegin", &EdgeDetectTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<EdgeDetectTrack>("timeEnd", &EdgeDetectTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<EdgeDetectTrack>("surfaceOffset", &EdgeDetectTrack::SetSurfaceOffset);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<EdgeDetectTrack>("lookaheadDistance", &EdgeDetectTrack::SetLookaheadDistance);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<EdgeDetectTrack>("edgeDepth", &EdgeDetectTrack::SetEdgeDepth);
					properties[4] = property;
					property = new fight::PropertyVector<EdgeDetectTrack>("cardinalVector", &EdgeDetectTrack::SetCardinalVector);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<EdgeDetectTrack>("lookaheadDistanceNonCardinal", &EdgeDetectTrack::SetLookaheadDistanceNonCardinal);
					properties[6] = property;
					property = new fight::PropertyBranch<EdgeDetectTrack>("branch", &EdgeDetectTrack::SetBranch);
					properties[7] = property;
					property = new fight::PropertyIntConstRange<EdgeDetectTrack>("priority", &EdgeDetectTrack::SetPriority);
					properties[8] = property;
					property = new fight::PropertyConditionGroup<EdgeDetectTrack>("conditions", &EdgeDetectTrack::SetConditions);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gEdgeDetectTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015B8C0
			fight::TrackFactory* CreateEdgeDetectTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<EdgeDetectTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015C030
			void RegisterEdgeDetectTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<EdgeDetectTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gEdgeSynchronizeTrackProperties;  // 0x11254484

			// FUNCTION: ENGINE 0x1015AE00
			bool EdgeSynchronizeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015AE20
			bool EdgeSynchronizeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015AE40
			bool EdgeSynchronizeTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1015AE60
			bool EdgeSynchronizeTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015AE70
			bool EdgeSynchronizeTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015AE90
			bool EdgeSynchronizeTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015B0E0
			fight::Property* EdgeSynchronizeTrack::GetProperty(int index)
			{
				return gEdgeSynchronizeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1015B100
			void EdgeSynchronizeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gEdgeSynchronizeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1015B110
			EdgeSynchronizeTrack::EdgeSynchronizeTrack() : offset(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(1.0f), priority(-5)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1015B180
			float EdgeSynchronizeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1015B190
			float EdgeSynchronizeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1015B1A0
			EdgeSynchronizeTrack::~EdgeSynchronizeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1015BE00
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EdgeSynchronizeTrack::RegisterProperties()
			{
				if (gEdgeSynchronizeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<EdgeSynchronizeTrack>("timeBegin", &EdgeSynchronizeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<EdgeSynchronizeTrack>("timeEnd", &EdgeSynchronizeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<EdgeSynchronizeTrack>("offset", &EdgeSynchronizeTrack::SetOffset);
					properties[2] = property;
					property = new fight::PropertyIntConstRange<EdgeSynchronizeTrack>("priority", &EdgeSynchronizeTrack::SetPriority);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<EdgeSynchronizeTrack>("blendInTime", &EdgeSynchronizeTrack::SetBlendInTime);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<EdgeSynchronizeTrack>("blendOutTime", &EdgeSynchronizeTrack::SetBlendOutTime);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gEdgeSynchronizeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015B8F0
			fight::TrackFactory* CreateEdgeSynchronizeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<EdgeSynchronizeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015C060
			void RegisterEdgeSynchronizeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<EdgeSynchronizeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyVector<EdgeNormalCondition>;
			template class fight::PropertyFloatConstRange<EdgeNormalCondition>;
			template class fight::ConditionFactoryTemplate<EdgeNormalCondition>;
			template class fight::ConditionFactoryCasterTemplate<EdgeNormalCondition>;
			template class fight::PropertyEnumConstList<EdgePositionCondition>;
			template class fight::PropertyFloatConstRange<EdgePositionCondition>;
			template class fight::ConditionFactoryTemplate<EdgePositionCondition>;
			template class fight::ConditionFactoryCasterTemplate<EdgePositionCondition>;
			template class fight::PropertyFloatConstRange<EdgeDetectTrack>;
			template class fight::PropertyVector<EdgeDetectTrack>;
			template class fight::PropertyBranch<EdgeDetectTrack>;
			template class fight::PropertyIntConstRange<EdgeDetectTrack>;
			template class fight::PropertyConditionGroup<EdgeDetectTrack>;
			template class fight::TrackFactoryTemplate<EdgeDetectTrack>;
			template class fight::TrackFactoryCasterTemplate<EdgeDetectTrack>;
			template class fight::PropertyFloatConstRange<EdgeSynchronizeTrack>;
			template class fight::PropertyVector<EdgeSynchronizeTrack>;
			template class fight::PropertyIntConstRange<EdgeSynchronizeTrack>;
			template class fight::TrackFactoryTemplate<EdgeSynchronizeTrack>;
			template class fight::TrackFactoryCasterTemplate<EdgeSynchronizeTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1015B1B0
// FUNCTION: ENGINE 0x1015B1E0
// FUNCTION: ENGINE 0x1015B210
// FUNCTION: ENGINE 0x1015B240
// FUNCTION: ENGINE 0x1015B270
// FUNCTION: ENGINE 0x1015B280
// FUNCTION: ENGINE 0x1015B2B0
// FUNCTION: ENGINE 0x1015B2C0
// FUNCTION: ENGINE 0x1015B2F0
// FUNCTION: ENGINE 0x1015B300
// FUNCTION: ENGINE 0x1015B330
// FUNCTION: ENGINE 0x1015B340
// FUNCTION: ENGINE 0x1015B370
// FUNCTION: ENGINE 0x1015B3A0
// FUNCTION: ENGINE 0x1015B3C0
// FUNCTION: ENGINE 0x1015B3D0
// FUNCTION: ENGINE 0x1015B400
// FUNCTION: ENGINE 0x1015B430
// FUNCTION: ENGINE 0x1015B440
// FUNCTION: ENGINE 0x1015B480
// FUNCTION: ENGINE 0x1015B490
// FUNCTION: ENGINE 0x1015B4C0
// FUNCTION: ENGINE 0x1015B4E0
// FUNCTION: ENGINE 0x1015B4F0
// FUNCTION: ENGINE 0x1015B520
// FUNCTION: ENGINE 0x1015B550
// FUNCTION: ENGINE 0x1015B560
// FUNCTION: ENGINE 0x1015B590
// FUNCTION: ENGINE 0x1015B5C0
// FUNCTION: ENGINE 0x1015B5D0
// FUNCTION: ENGINE 0x1015B600
// FUNCTION: ENGINE 0x1015B620
// FUNCTION: ENGINE 0x1015B630
// FUNCTION: ENGINE 0x1015B660
// FUNCTION: ENGINE 0x1015B680
// FUNCTION: ENGINE 0x1015B6B0
// FUNCTION: ENGINE 0x1015B6D0
// FUNCTION: ENGINE 0x1015B6E0
// FUNCTION: ENGINE 0x1015B710
// FUNCTION: ENGINE 0x1015B730
// FUNCTION: ENGINE 0x1015B760
// FUNCTION: ENGINE 0x1015B790
// FUNCTION: ENGINE 0x1015B7A0
// FUNCTION: ENGINE 0x1015B7D0
// FUNCTION: ENGINE 0x1015B7F0
// FUNCTION: ENGINE 0x1015B800
// FUNCTION: ENGINE 0x1015B830
// FUNCTION: ENGINE 0x1015B850
// FUNCTION: ENGINE 0x1015C090
// FUNCTION: ENGINE 0x1015C0C0
// FUNCTION: ENGINE 0x1015C0E0
// FUNCTION: ENGINE 0x1015C110
// FUNCTION: ENGINE 0x1015C130
// FUNCTION: ENGINE 0x1015C160
// FUNCTION: ENGINE 0x1015C180
// FUNCTION: ENGINE 0x1015C1B0
// FUNCTION: ENGINE 0x1015C1D0
// FUNCTION: ENGINE 0x1015C220
// FUNCTION: ENGINE 0x1015C270
// FUNCTION: ENGINE 0x1015C2C0
