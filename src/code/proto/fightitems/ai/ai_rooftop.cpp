// Fight items of the ai group: IsInRooftopCondition, StayOnRoofTrack, RooftopDestinationFindTrack (unit 0x10247690 - 0x10249200; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_rooftop.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gIsInRooftopConditionProperties;  // 0x11255B64

			// FUNCTION: ENGINE 0x10247690
			bool IsInRooftopCondition::SetRooftop(bool newValue)
			{
				rooftop = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247B20
			fight::Property* IsInRooftopCondition::GetProperty(int index)
			{
				return gIsInRooftopConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10247B40
			void IsInRooftopCondition::ClearProperties()
			{
				fight::FreePropertyList(&gIsInRooftopConditionProperties);
			}

			// FUNCTION: ENGINE 0x10247B50
			IsInRooftopCondition::IsInRooftopCondition() : fight::Condition(0), rooftop(false)
			{
			}

			// FUNCTION: ENGINE 0x10247B70
			IsInRooftopCondition::~IsInRooftopCondition()
			{
			}

			// FUNCTION: ENGINE 0x102484A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IsInRooftopCondition::RegisterProperties()
			{
				if (gIsInRooftopConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<IsInRooftopCondition>("rooftop", &IsInRooftopCondition::SetRooftop);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gIsInRooftopConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10248410
			fight::ConditionFactory* CreateIsInRooftopConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsInRooftopCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10248F80
			void RegisterIsInRooftopConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsInRooftopCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gStayOnRoofTrackProperties;  // 0x11255B68

			// FUNCTION: ENGINE 0x102476A0
			bool StayOnRoofTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102476C0
			bool StayOnRoofTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247B80
			fight::Property* StayOnRoofTrack::GetProperty(int index)
			{
				return gStayOnRoofTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10247BA0
			void StayOnRoofTrack::ClearProperties()
			{
				fight::FreePropertyList(&gStayOnRoofTrackProperties);
			}

			// FUNCTION: ENGINE 0x10247BB0
			StayOnRoofTrack::StayOnRoofTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10247BE0
			float StayOnRoofTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10247BF0
			float StayOnRoofTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10247C00
			StayOnRoofTrack::~StayOnRoofTrack()
			{
			}

			// FUNCTION: ENGINE 0x10248540
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void StayOnRoofTrack::RegisterProperties()
			{
				if (gStayOnRoofTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<StayOnRoofTrack>("timeBegin", &StayOnRoofTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<StayOnRoofTrack>("timeEnd", &StayOnRoofTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gStayOnRoofTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10248440
			fight::TrackFactory* CreateStayOnRoofTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<StayOnRoofTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10248FB0
			void RegisterStayOnRoofTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<StayOnRoofTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gRooftopDestinationFindTrackProperties;  // 0x11255B6C

			// FUNCTION: ENGINE 0x102476E0
			bool RooftopDestinationFindTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247700
			bool RooftopDestinationFindTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247720
			bool RooftopDestinationFindTrack::SetEdgeReserveRadius(float newValue)
			{
				edgeReserveRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247740
			bool RooftopDestinationFindTrack::SetMinDistanceForEdge(float newValue)
			{
				minDistanceForEdge = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247760
			bool RooftopDestinationFindTrack::SetHeightForEdge(float newValue)
			{
				heightForEdge = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247780
			bool RooftopDestinationFindTrack::SetEdgeCloserThan(float newValue)
			{
				edgeCloserThan = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102477A0
			bool RooftopDestinationFindTrack::SetMinDistance(float newValue)
			{
				minDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102477C0
			bool RooftopDestinationFindTrack::SetMaxDistance(float newValue)
			{
				maxDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102477E0
			bool RooftopDestinationFindTrack::SetMinAngle(float newValue)
			{
				minAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10247800
			bool RooftopDestinationFindTrack::SetMaxAngle(float newValue)
			{
				maxAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10247820
			bool RooftopDestinationFindTrack::SetNumTries(int newValue)
			{
				numTries = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247840
			bool RooftopDestinationFindTrack::SetIgnoreRestrictions(bool newValue)
			{
				ignoreRestrictions = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247860
			bool RooftopDestinationFindTrack::SetCheckNotReserved(bool newValue)
			{
				checkNotReserved = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247880
			bool RooftopDestinationFindTrack::SetCheckCanGo(bool newValue)
			{
				checkCanGo = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102478A0
			bool RooftopDestinationFindTrack::SetUseNavMeshHeight(bool newValue)
			{
				useNavMeshHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102478C0
			bool RooftopDestinationFindTrack::SetHeightDifferenceCheck(int newValue)
			{
				heightDifferenceCheck = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102478E0
			bool RooftopDestinationFindTrack::SetMaxHeightDifference(float newValue)
			{
				maxHeightDifference = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247900
			bool RooftopDestinationFindTrack::SetMinHeightDifference(float newValue)
			{
				minHeightDifference = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247920
			bool RooftopDestinationFindTrack::SetLookJustCloser(float newValue)
			{
				lookJustCloser = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247940
			bool RooftopDestinationFindTrack::SetMinDistanceFromCurrent(float newValue)
			{
				minDistanceFromCurrent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247960
			bool RooftopDestinationFindTrack::SetFreeRadiusAround(float newValue)
			{
				freeRadiusAround = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247980
			bool RooftopDestinationFindTrack::SetAllowedAreas(int newValue)
			{
				allowedAreas = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102479A0
			bool RooftopDestinationFindTrack::SetIgnoreAreasWhenAgentOutside(bool newValue)
			{
				ignoreAreasWhenAgentOutside = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102479C0
			bool RooftopDestinationFindTrack::SetMaxDistanceToGround(float newValue)
			{
				maxDistanceToGround = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102479E0
			bool RooftopDestinationFindTrack::SetAirDestination(bool newValue)
			{
				airDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247A00
			bool RooftopDestinationFindTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10247A20
			bool RooftopDestinationFindTrack::SetCameraVisibility(int newValue)
			{
				cameraVisibility = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247A40
			bool RooftopDestinationFindTrack::SetCollisionFlagsLOF(int newValue)
			{
				collisionFlagsLOF = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247A60
			bool RooftopDestinationFindTrack::SetCollideWithTypeLOF(int newValue)
			{
				collideWithTypeLOF = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247A80
			bool RooftopDestinationFindTrack::SetOffsetLOF(const math::Vector& newValue)
			{
				offsetLOF.x = newValue.x;
				offsetLOF.y = newValue.y;
				offsetLOF.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10247AA0
			bool RooftopDestinationFindTrack::SetHeuristic(int newValue)
			{
				heuristic = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247AC0
			bool RooftopDestinationFindTrack::SetReferencePosition(int newValue)
			{
				referencePosition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247AE0
			fight::BranchHolder* RooftopDestinationFindTrack::SetWhenFound()
			{
				return &whenFound;
			}

			// FUNCTION: ENGINE 0x10247AF0
			bool RooftopDestinationFindTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10247B10
			fight::ConditionList* RooftopDestinationFindTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x10247C10
			fight::Property* RooftopDestinationFindTrack::GetProperty(int index)
			{
				return gRooftopDestinationFindTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10247C30
			void RooftopDestinationFindTrack::ClearProperties()
			{
				fight::FreePropertyList(&gRooftopDestinationFindTrackProperties);
			}

			// FUNCTION: ENGINE 0x10247C40
			RooftopDestinationFindTrack::RooftopDestinationFindTrack() : whenFound(0), offset(0.0f, 0.0f, 0.0f), offsetLOF(0.0f, 0.0f, 0.0f), edgeCloserThan(1e+01f), edgeReserveRadius(1e+01f), freeRadiusAround(0.0f), heightForEdge(1e+01f), lookJustCloser(0.0f), maxAngle(1.5707964f), maxDistance(2e+01f), maxDistanceToGround(0.0f), maxHeightDifference(3.0f), minAngle(-1.5707964f), minDistance(1e+01f), minDistanceForEdge(1e+01f), minDistanceFromCurrent(0.0f), minHeightDifference(8.0f), timeBegin(0.0f), timeEnd(-1.0f), cameraVisibility(0), collisionFlagsLOF(0), heightDifferenceCheck(0), heuristic(0), numTries(1), priority(0), referencePosition(0), allowedAreas(gCombatDestinationFindTrackAllowedAreasDefault), collideWithTypeLOF(gCombatDestinationFindTrackCollideWithTypeLOFDefault), airDestination(false), checkCanGo(true), checkNotReserved(true), ignoreAreasWhenAgentOutside(false), ignoreRestrictions(false), useNavMeshHeight(true)
			{
			}

			// FUNCTION: ENGINE 0x10247DE0
			float RooftopDestinationFindTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10247DF0
			float RooftopDestinationFindTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10247E00
			RooftopDestinationFindTrack::~RooftopDestinationFindTrack()
			{
			}

			// FUNCTION: ENGINE 0x10248620
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RooftopDestinationFindTrack::RegisterProperties()
			{
				if (gRooftopDestinationFindTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("timeBegin", &RooftopDestinationFindTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("timeEnd", &RooftopDestinationFindTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("edgeReserveRadius", &RooftopDestinationFindTrack::SetEdgeReserveRadius);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("minDistanceForEdge", &RooftopDestinationFindTrack::SetMinDistanceForEdge);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("heightForEdge", &RooftopDestinationFindTrack::SetHeightForEdge);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("edgeCloserThan", &RooftopDestinationFindTrack::SetEdgeCloserThan);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("minDistance", &RooftopDestinationFindTrack::SetMinDistance);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("maxDistance", &RooftopDestinationFindTrack::SetMaxDistance);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("minAngle", &RooftopDestinationFindTrack::SetMinAngle);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("maxAngle", &RooftopDestinationFindTrack::SetMaxAngle);
					properties[9] = property;
					property = new fight::PropertyIntConstRange<RooftopDestinationFindTrack>("numTries", &RooftopDestinationFindTrack::SetNumTries);
					properties[10] = property;
					property = new fight::PropertyBool<RooftopDestinationFindTrack>("ignoreRestrictions", &RooftopDestinationFindTrack::SetIgnoreRestrictions);
					properties[11] = property;
					property = new fight::PropertyBool<RooftopDestinationFindTrack>("checkNotReserved", &RooftopDestinationFindTrack::SetCheckNotReserved);
					properties[12] = property;
					property = new fight::PropertyBool<RooftopDestinationFindTrack>("checkCanGo", &RooftopDestinationFindTrack::SetCheckCanGo);
					properties[13] = property;
					property = new fight::PropertyBool<RooftopDestinationFindTrack>("useNavMeshHeight", &RooftopDestinationFindTrack::SetUseNavMeshHeight);
					properties[14] = property;
					property = new fight::PropertyEnumConstList<RooftopDestinationFindTrack>("heightDifferenceCheck", gCombatDestinationFindTrackHeightDifferenceCheckTable, gCombatDestinationFindTrackHeightDifferenceCheckCount, &RooftopDestinationFindTrack::SetHeightDifferenceCheck);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("maxHeightDifference", &RooftopDestinationFindTrack::SetMaxHeightDifference);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("minHeightDifference", &RooftopDestinationFindTrack::SetMinHeightDifference);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("lookJustCloser", &RooftopDestinationFindTrack::SetLookJustCloser);
					properties[18] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("minDistanceFromCurrent", &RooftopDestinationFindTrack::SetMinDistanceFromCurrent);
					properties[19] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("freeRadiusAround", &RooftopDestinationFindTrack::SetFreeRadiusAround);
					properties[20] = property;
					property = new fight::PropertyBitfieldConstList<RooftopDestinationFindTrack>("allowedAreas", gCombatDestinationFindTrackAllowedAreasTable, gCombatDestinationFindTrackAllowedAreasCount, &RooftopDestinationFindTrack::SetAllowedAreas);
					properties[21] = property;
					property = new fight::PropertyBool<RooftopDestinationFindTrack>("ignoreAreasWhenAgentOutside", &RooftopDestinationFindTrack::SetIgnoreAreasWhenAgentOutside);
					properties[22] = property;
					property = new fight::PropertyFloatConstRange<RooftopDestinationFindTrack>("maxDistanceToGround", &RooftopDestinationFindTrack::SetMaxDistanceToGround);
					properties[23] = property;
					property = new fight::PropertyBool<RooftopDestinationFindTrack>("airDestination", &RooftopDestinationFindTrack::SetAirDestination);
					properties[24] = property;
					property = new fight::PropertyVector<RooftopDestinationFindTrack>("offset", &RooftopDestinationFindTrack::SetOffset);
					properties[25] = property;
					property = new fight::PropertyEnumConstList<RooftopDestinationFindTrack>("cameraVisibility", gCombatDestinationFindTrackCameraVisibilityTable, gCombatDestinationFindTrackCameraVisibilityCount, &RooftopDestinationFindTrack::SetCameraVisibility);
					properties[26] = property;
					property = new fight::PropertyEnumConstList<RooftopDestinationFindTrack>("collisionFlagsLOF", gTargetHasLoFConditionCollisionFlagsTable, gTargetHasLoFConditionCollisionFlagsCount, &RooftopDestinationFindTrack::SetCollisionFlagsLOF);
					properties[27] = property;
					property = new fight::PropertyBitfieldConstList<RooftopDestinationFindTrack>("collideWithTypeLOF", motion::gDetectObbCollisionConditionCollideWithTable, motion::gDetectObbCollisionConditionCollideWithCount, &RooftopDestinationFindTrack::SetCollideWithTypeLOF);
					properties[28] = property;
					property = new fight::PropertyVector<RooftopDestinationFindTrack>("offsetLOF", &RooftopDestinationFindTrack::SetOffsetLOF);
					properties[29] = property;
					property = new fight::PropertyEnumConstList<RooftopDestinationFindTrack>("heuristic", gCombatDestinationFindTrackHeuristicTable, gCombatDestinationFindTrackHeuristicCount, &RooftopDestinationFindTrack::SetHeuristic);
					properties[30] = property;
					property = new fight::PropertyEnumConstList<RooftopDestinationFindTrack>("referencePosition", gCombatDestinationFindTrackReferencePositionTable, gCombatDestinationFindTrackReferencePositionCount, &RooftopDestinationFindTrack::SetReferencePosition);
					properties[31] = property;
					property = new fight::PropertyBranch<RooftopDestinationFindTrack>("whenFound", &RooftopDestinationFindTrack::SetWhenFound);
					properties[32] = property;
					property = new fight::PropertyIntConstRange<RooftopDestinationFindTrack>("priority", &RooftopDestinationFindTrack::SetPriority);
					properties[33] = property;
					property = new fight::PropertyConditionGroup<RooftopDestinationFindTrack>("conditions", &RooftopDestinationFindTrack::SetConditions);
					properties[34] = property;
					fight::RegisterPropertyList(properties, &gRooftopDestinationFindTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10248470
			fight::TrackFactory* CreateRooftopDestinationFindTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<RooftopDestinationFindTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10248FE0
			void RegisterRooftopDestinationFindTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<RooftopDestinationFindTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyBool<IsInRooftopCondition>;
			template class fight::ConditionFactoryTemplate<IsInRooftopCondition>;
			template class fight::ConditionFactoryCasterTemplate<IsInRooftopCondition>;
			template class fight::PropertyFloatConstRange<StayOnRoofTrack>;
			template class fight::TrackFactoryTemplate<StayOnRoofTrack>;
			template class fight::TrackFactoryCasterTemplate<StayOnRoofTrack>;
			template class fight::PropertyFloatConstRange<RooftopDestinationFindTrack>;
			template class fight::PropertyIntConstRange<RooftopDestinationFindTrack>;
			template class fight::PropertyBool<RooftopDestinationFindTrack>;
			template class fight::PropertyEnumConstList<RooftopDestinationFindTrack>;
			template class fight::PropertyBitfieldConstList<RooftopDestinationFindTrack>;
			template class fight::PropertyVector<RooftopDestinationFindTrack>;
			template class fight::PropertyBranch<RooftopDestinationFindTrack>;
			template class fight::PropertyConditionGroup<RooftopDestinationFindTrack>;
			template class fight::TrackFactoryTemplate<RooftopDestinationFindTrack>;
			template class fight::TrackFactoryCasterTemplate<RooftopDestinationFindTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10247E30
// FUNCTION: ENGINE 0x10247E60
// FUNCTION: ENGINE 0x10247E90
// FUNCTION: ENGINE 0x10247EC0
// FUNCTION: ENGINE 0x10247ED0
// FUNCTION: ENGINE 0x10247F00
// FUNCTION: ENGINE 0x10247F10
// FUNCTION: ENGINE 0x10247F40
// FUNCTION: ENGINE 0x10247F50
// FUNCTION: ENGINE 0x10247F80
// FUNCTION: ENGINE 0x10247FB0
// FUNCTION: ENGINE 0x10247FD0
// FUNCTION: ENGINE 0x10247FE0
// FUNCTION: ENGINE 0x10248010
// FUNCTION: ENGINE 0x10248040
// FUNCTION: ENGINE 0x10248050
// FUNCTION: ENGINE 0x10248080
// FUNCTION: ENGINE 0x102480B0
// FUNCTION: ENGINE 0x102480C0
// FUNCTION: ENGINE 0x102480F0
// FUNCTION: ENGINE 0x10248110
// FUNCTION: ENGINE 0x10248120
// FUNCTION: ENGINE 0x10248150
// FUNCTION: ENGINE 0x10248170
// FUNCTION: ENGINE 0x10248180
// FUNCTION: ENGINE 0x102481C0
// FUNCTION: ENGINE 0x102481D0
// FUNCTION: ENGINE 0x10248200
// FUNCTION: ENGINE 0x10248220
// FUNCTION: ENGINE 0x10248230
// FUNCTION: ENGINE 0x10248270
// FUNCTION: ENGINE 0x10248280
// FUNCTION: ENGINE 0x102482A0
// FUNCTION: ENGINE 0x102482B0
// FUNCTION: ENGINE 0x10248310
// FUNCTION: ENGINE 0x10248340
// FUNCTION: ENGINE 0x10248360
// FUNCTION: ENGINE 0x10248370
// FUNCTION: ENGINE 0x102483A0
// FUNCTION: ENGINE 0x102483C0
// FUNCTION: ENGINE 0x102483F0
// FUNCTION: ENGINE 0x10249010
// FUNCTION: ENGINE 0x10249040
// FUNCTION: ENGINE 0x10249060
// FUNCTION: ENGINE 0x10249090
// FUNCTION: ENGINE 0x102490B0
// FUNCTION: ENGINE 0x102490E0
// FUNCTION: ENGINE 0x10249110
// FUNCTION: ENGINE 0x10249160
// FUNCTION: ENGINE 0x102491B0
