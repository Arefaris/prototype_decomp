// Fight items of the motion group: EdgeNormalCondition, EdgePositionCondition, EdgeDetectTrack, EdgeSynchronizeTrack (unit 0x1015AC70 - 0x1015C310; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_EDGE_H
#define PROTO_FIGHTITEMS_MOTION_EDGE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::EdgeNormalCondition (10 vftable slots, 0x1C bytes)
			class EdgeNormalCondition : public fight::Condition
			{
			public:
				// 0x1015AEE0
				EdgeNormalCondition();
				virtual ~EdgeNormalCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B9210, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetNormal(const math::Vector& newValue);
				bool SetArc(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector normal;  // +0xC
					float arc;  // +0x18
			};

			extern fight::Property** gEdgeNormalConditionProperties;
			fight::ConditionFactory* CreateEdgeNormalConditionFactory(const char* name);
			void RegisterEdgeNormalConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::EdgePositionCondition (10 vftable slots, 0x18 bytes)
			class EdgePositionCondition : public fight::Condition
			{
			public:
				// 0x1015AF70
				EdgePositionCondition();
				virtual ~EdgePositionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100B93A0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetComponent(int newValue);
				bool SetCompare(int newValue);
				bool SetOffset(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float offset;  // +0xC
					int compare;  // +0x10
					int component;  // +0x14
			};

			extern fight::Property** gEdgePositionConditionProperties;
			fight::ConditionFactory* CreateEdgePositionConditionFactory(const char* name);
			void RegisterEdgePositionConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::EdgeDetectTrack (16 vftable slots, 0x60 bytes)
			class EdgeDetectTrack : public fight::Track
			{
			public:
				// 0x1015AFF0
				EdgeDetectTrack();
				virtual ~EdgeDetectTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100BA1C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSurfaceOffset(float newValue);
				bool SetLookaheadDistance(float newValue);
				bool SetEdgeDepth(float newValue);
				bool SetCardinalVector(const math::Vector& newValue);
				bool SetLookaheadDistanceNonCardinal(float newValue);
				fight::BranchHolder* SetBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					math::Vector cardinalVector;  // +0x34
					fight::ConditionList conditions;  // +0x40
					float edgeDepth;  // +0x44
					float lookaheadDistance;  // +0x48
					float lookaheadDistanceNonCardinal;  // +0x4C
					float surfaceOffset;  // +0x50
					float timeBegin;  // +0x54
					float timeEnd;  // +0x58
					int priority;  // +0x5C
			};

			extern fight::Property** gEdgeDetectTrackProperties;
			fight::TrackFactory* CreateEdgeDetectTrackFactory(const char* name);
			void RegisterEdgeDetectTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::EdgeSynchronizeTrack (16 vftable slots, 0x30 bytes)
			class EdgeSynchronizeTrack : public fight::Track
			{
			public:
				// 0x1015B110
				EdgeSynchronizeTrack();
				virtual ~EdgeSynchronizeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100BA760, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector offset;  // +0x10
					float blendInTime;  // +0x1C
					float blendOutTime;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					int priority;  // +0x2C
			};

			extern fight::Property** gEdgeSynchronizeTrackProperties;
			fight::TrackFactory* CreateEdgeSynchronizeTrackFactory(const char* name);
			void RegisterEdgeSynchronizeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
