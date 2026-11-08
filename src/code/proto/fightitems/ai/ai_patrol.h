// Fight items of the ai group: HasPatrolPathCondition, PatrolTrack, PathPatrolTrack (unit 0x10243760 - 0x10244160; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_PATROL_H
#define PROTO_FIGHTITEMS_AI_AI_PATROL_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"
#include "code/proto/patrolpathfollowing.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::HasPatrolPathCondition (10 vftable slots, 0x10 bytes)
			class HasPatrolPathCondition : public fight::Condition
			{
			public:
				// 0x10243820
				HasPatrolPathCondition();
				virtual ~HasPatrolPathCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102052B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetHasPath(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool hasPath;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gHasPatrolPathConditionProperties;
			fight::ConditionFactory* CreateHasPatrolPathConditionFactory(const char* name);
			void RegisterHasPatrolPathConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::PatrolTrack (16 vftable slots, 0x18 bytes)
			class PatrolTrack : public fight::Track
			{
			public:
				// 0x10243880
				PatrolTrack();
				virtual ~PatrolTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10205890, another unit)
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

			extern fight::Property** gPatrolTrackProperties;
			fight::TrackFactory* CreatePatrolTrackFactory(const char* name);
			void RegisterPatrolTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::PathPatrolTrack (16 vftable slots, 0x18 bytes)
			class PathPatrolTrack : public fight::Track
			{
			public:
				// 0x10243910
				PathPatrolTrack();
				virtual ~PathPatrolTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x102058E0, another unit)
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

			extern fight::Property** gPathPatrolTrackProperties;
			fight::TrackFactory* CreatePathPatrolTrackFactory(const char* name);
			void RegisterPathPatrolTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::PatrolAction (9 vftable slots, 0x78 bytes)
			class PatrolAction : public fight::Action
			{
			public:
				// 0x102055B0
				PatrolAction(PatrolTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10205380
				virtual ~PatrolAction();

				// vftable slot 5 (0x10205D10)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10205FF0)
				virtual void Slot6();
				// vftable slot 7 (0x102053C0)
				virtual bool Slot7(int arg, float value);

				core::Link<PatrolTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				CharacterFollower follower;  // +0x2C
				NotifyScenarioDestinationReached notifier;  // +0x34
				PatrolPathFollowing following;  // +0x3C
				float unknown74;  // +0x74
			};
			// RTTI: proto::fightitems::ai::PathPatrolAction (9 vftable slots, 0x7C bytes)
			class PathPatrolAction : public fight::Action
			{
			public:
				// 0x102056E0
				PathPatrolAction(PathPatrolTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x102054C0
				virtual ~PathPatrolAction();

				// vftable slot 5 (0x10205930)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10205010)
				virtual void Slot6();
				// vftable slot 7 (0x10205B10)
				virtual bool Slot7(int arg, float value);

				core::Link<PathPatrolTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				CharacterFollower follower;  // +0x2C
				NotifyScenarioDestinationReached notifier;  // +0x34
				PatrolPathFollowing following;  // +0x3C
				int unknown74;  // +0x74
				int unknown78;  // +0x78
			};

			// ---- actions end
		}
	}
}

#endif
