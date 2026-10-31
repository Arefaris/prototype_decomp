// Fight items of the ai group: ExecuteTaskTrack, SpawnTaskTrack (unit 0x102527C0 - 0x10253340; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_TASK_H
#define PROTO_FIGHTITEMS_AI_AI_TASK_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::ExecuteTaskTrack (16 vftable slots, 0x50 bytes)
			class ExecuteTaskTrack : public fight::Track
			{
			public:
				// 0x10252920
				ExecuteTaskTrack();
				virtual ~ExecuteTaskTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10217540, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTask(const fight::Name& newValue);
				fight::BranchHolder* SetBranch();
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					unsigned char unknown34[0x4];
					fight::Name task;  // +0x38
					fight::ConditionList conditions;  // +0x40
					float timeBegin;  // +0x44
					float timeEnd;  // +0x48
					unsigned char unknown4C[0x4];
			};

			extern fight::Property** gExecuteTaskTrackProperties;
			fight::TrackFactory* CreateExecuteTaskTrackFactory(const char* name);
			void RegisterExecuteTaskTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::SpawnTaskTrack (16 vftable slots, 0x50 bytes)
			class SpawnTaskTrack : public fight::Track
			{
			public:
				// 0x102529D0
				SpawnTaskTrack();
				virtual ~SpawnTaskTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10217590, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTask(const fight::Name& newValue);
				fight::BranchHolder* SetBranch();
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					unsigned char unknown34[0x4];
					fight::Name task;  // +0x38
					fight::ConditionList conditions;  // +0x40
					float timeBegin;  // +0x44
					float timeEnd;  // +0x48
					unsigned char unknown4C[0x4];
			};

			extern fight::Property** gSpawnTaskTrackProperties;
			fight::TrackFactory* CreateSpawnTaskTrackFactory(const char* name);
			void RegisterSpawnTaskTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
