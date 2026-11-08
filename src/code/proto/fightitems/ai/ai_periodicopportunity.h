// Fight items of the ai group: PeriodicOpportunityTrack, DelayedSequenceTrack (unit 0x10244160 - 0x10244F30; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_PERIODICOPPORTUNITY_H
#define PROTO_FIGHTITEMS_AI_AI_PERIODICOPPORTUNITY_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/engine/fight/branch.h"
#include "code/engine/fight/effecttrack.h"
#include "code/proto/fightitems/ai/aiaction.h"
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

			// 0x10206270 (name guess): a float between two limits, from the random generator of the fight code
			float FightRandomRange(float low, float high);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::PeriodicOpportunityAction (9 vftable slots, 0x6C bytes): the engine's opportunity action without its callback
			class PeriodicOpportunityAction : public fight::Action
			{
			public:
				// 0x102066F0
				PeriodicOpportunityAction(fight::Track* newListener, PeriodicOpportunityTrack* newTrack, float newDuration, float newHook, fight::Branch* newBranch, int newPriority, fight::Sequencer* newParent, core::IRefCount* newOwner);
				// 0x102064E0
				virtual ~PeriodicOpportunityAction();

				// vftable slot 5 (0x10206360)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10206560)
				virtual void Slot6();
				// vftable slot 7 (0x10206820)
				virtual bool Slot7(int arg, float value);
				// vftable slot 8 (0x10206980)
				virtual fight::Action* Slot8(fight::Action* other, core::IRefCount* effect, core::IRefCount* owner);

				engine::TrackWatch watch;  // +0x1C
				core::Link<PeriodicOpportunityTrack> link;  // +0x28
				float duration;  // +0x34
				float hook;  // +0x38
				fight::BranchWatch branchWatch;  // +0x3C
				int priority;  // +0x48
				fight::Sequencer* parent;  // +0x4C
				core::IRefCount* owner;  // +0x50
				int first;  // +0x54
				int second;  // +0x58
				float elapsed;  // +0x5C
				fight::BranchWatch started;  // +0x60
			};
			// RTTI: proto::fightitems::ai::DelayedSequenceAction (9 vftable slots, 0x44 bytes)
			class DelayedSequenceAction : public fight::Action
			{
			public:
				// 0x10206A30
				DelayedSequenceAction(DelayedSequenceTrack* newTrack, engine::GameObjectHandle newTarget, int newEffect, fight::Track* newListener, core::IRefCount* newOwner);
				// 0x102065C0
				virtual ~DelayedSequenceAction();

				// vftable slot 5 (0x10206B10)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x102062F0)
				virtual void Slot6();
				// vftable slot 7 (0x10206B50)
				virtual bool Slot7(int arg, float value);

				int effect;  // +0x1C
				core::IRefCount* owner;  // +0x20
				engine::TrackWatch listener;  // +0x24
				core::Link<DelayedSequenceTrack> link;  // +0x30
				engine::GameObjectHandle target;  // +0x3C
				float delay;  // +0x40
			};
			// ---- actions end
		}
	}
}

#endif
