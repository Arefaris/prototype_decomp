// Fight items of the ai group: PeriodicOpportunityTrack, DelayedSequenceTrack (unit 0x10244160 - 0x10244F30; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_PERIODICOPPORTUNITY_H
#define PROTO_FIGHTITEMS_AI_AI_PERIODICOPPORTUNITY_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::PeriodicOpportunityTrack (16 vftable slots, 0x4C bytes)
			class PeriodicOpportunityTrack : public fight::Track
			{
			public:
				// 0x10244300
				PeriodicOpportunityTrack();
				virtual ~PeriodicOpportunityTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10206C40, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTimeHook(float newValue);
				bool SetPeriod(float newValue);
				fight::BranchHolder* SetBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					fight::ConditionList conditions;  // +0x34
					float period;  // +0x38
					float timeBegin;  // +0x3C
					float timeEnd;  // +0x40
					float timeHook;  // +0x44
					int priority;  // +0x48
			};

			extern fight::Property** gPeriodicOpportunityTrackProperties;
			fight::TrackFactory* CreatePeriodicOpportunityTrackFactory(const char* name);
			void RegisterPeriodicOpportunityTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DelayedSequenceTrack (16 vftable slots, 0x50 bytes)
			class DelayedSequenceTrack : public fight::Track
			{
			public:
				// 0x102443F0
				DelayedSequenceTrack();
				virtual ~DelayedSequenceTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10206D00, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMinDelay(float newValue);
				bool SetMaxDelay(float newValue);
				bool SetForceSequenceWhenNotBusy(bool newValue);
				fight::BranchHolder* SetBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					fight::ConditionList conditions;  // +0x34
					float maxDelay;  // +0x38
					float minDelay;  // +0x3C
					float timeBegin;  // +0x40
					float timeEnd;  // +0x44
					int priority;  // +0x48
					bool forceSequenceWhenNotBusy;  // +0x4C
					unsigned char unknown4D[0x3];
			};

			extern fight::Property** gDelayedSequenceTrackProperties;
			fight::TrackFactory* CreateDelayedSequenceTrackFactory(const char* name);
			void RegisterDelayedSequenceTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
