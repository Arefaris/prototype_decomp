// Fight items of the ai group: IsInRooftopCondition, StayOnRoofTrack, RooftopDestinationFindTrack (unit 0x10247690 - 0x10249200; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_ROOFTOP_H
#define PROTO_FIGHTITEMS_AI_AI_ROOFTOP_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::IsInRooftopCondition (10 vftable slots, 0x10 bytes)
			class IsInRooftopCondition : public fight::Condition
			{
			public:
				// 0x10247B50
				IsInRooftopCondition();
				virtual ~IsInRooftopCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10209210, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetRooftop(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool rooftop;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gIsInRooftopConditionProperties;
			fight::ConditionFactory* CreateIsInRooftopConditionFactory(const char* name);
			void RegisterIsInRooftopConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::StayOnRoofTrack (16 vftable slots, 0x18 bytes)
			class StayOnRoofTrack : public fight::Track
			{
			public:
				// 0x10247BB0
				StayOnRoofTrack();
				virtual ~StayOnRoofTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1020A030, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gStayOnRoofTrackProperties;
			fight::TrackFactory* CreateStayOnRoofTrackFactory(const char* name);
			void RegisterStayOnRoofTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RooftopDestinationFindTrack (16 vftable slots, 0xBC bytes)
			class RooftopDestinationFindTrack : public fight::Track
			{
			public:
				// 0x10247C40
				RooftopDestinationFindTrack();
				virtual ~RooftopDestinationFindTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10209780, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetEdgeReserveRadius(float newValue);
				bool SetMinDistanceForEdge(float newValue);
				bool SetHeightForEdge(float newValue);
				bool SetEdgeCloserThan(float newValue);
				bool SetMinDistance(float newValue);
				bool SetMaxDistance(float newValue);
				bool SetMinAngle(float newValue);
				bool SetMaxAngle(float newValue);
				bool SetNumTries(int newValue);
				bool SetIgnoreRestrictions(bool newValue);
				bool SetCheckNotReserved(bool newValue);
				bool SetCheckCanGo(bool newValue);
				bool SetUseNavMeshHeight(bool newValue);
				bool SetHeightDifferenceCheck(int newValue);
				bool SetMaxHeightDifference(float newValue);
				bool SetMinHeightDifference(float newValue);
				bool SetLookJustCloser(float newValue);
				bool SetMinDistanceFromCurrent(float newValue);
				bool SetFreeRadiusAround(float newValue);
				bool SetAllowedAreas(int newValue);
				bool SetIgnoreAreasWhenAgentOutside(bool newValue);
				bool SetMaxDistanceToGround(float newValue);
				bool SetAirDestination(bool newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetCameraVisibility(int newValue);
				bool SetCollisionFlagsLOF(int newValue);
				bool SetCollideWithTypeLOF(int newValue);
				bool SetOffsetLOF(const math::Vector& newValue);
				bool SetHeuristic(int newValue);
				bool SetReferencePosition(int newValue);
				fight::BranchHolder* SetWhenFound();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder whenFound;  // +0x10
					math::Vector offset;  // +0x34
					math::Vector offsetLOF;  // +0x40
					fight::ConditionList conditions;  // +0x4C
					float edgeCloserThan;  // +0x50
					float edgeReserveRadius;  // +0x54
					float freeRadiusAround;  // +0x58
					float heightForEdge;  // +0x5C
					float lookJustCloser;  // +0x60
					float maxAngle;  // +0x64
					float maxDistance;  // +0x68
					float maxDistanceToGround;  // +0x6C
					float maxHeightDifference;  // +0x70
					float minAngle;  // +0x74
					float minDistance;  // +0x78
					float minDistanceForEdge;  // +0x7C
					float minDistanceFromCurrent;  // +0x80
					float minHeightDifference;  // +0x84
					float timeBegin;  // +0x88
					float timeEnd;  // +0x8C
					int cameraVisibility;  // +0x90
					int collisionFlagsLOF;  // +0x94
					int heightDifferenceCheck;  // +0x98
					int heuristic;  // +0x9C
					int numTries;  // +0xA0
					int priority;  // +0xA4
					int referencePosition;  // +0xA8
					int allowedAreas;  // +0xAC
					int collideWithTypeLOF;  // +0xB0
					bool airDestination;  // +0xB4
					bool checkCanGo;  // +0xB5
					bool checkNotReserved;  // +0xB6
					bool ignoreAreasWhenAgentOutside;  // +0xB7
					bool ignoreRestrictions;  // +0xB8
					bool useNavMeshHeight;  // +0xB9
					unsigned char unknownBA[0x2];
			};

			extern fight::Property** gRooftopDestinationFindTrackProperties;
			fight::TrackFactory* CreateRooftopDestinationFindTrackFactory(const char* name);
			void RegisterRooftopDestinationFindTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
