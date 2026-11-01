// Fight items of the ai group: ConditionalExecuteTrack (unit 0x10226DB0 - 0x102272B0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_CONDITIONALEXECUTE_H
#define PROTO_FIGHTITEMS_AI_AI_CONDITIONALEXECUTE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/engine/fight/branch.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/lodactions.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::ConditionalExecuteTrack (16 vftable slots, 0x40 bytes)
			class ConditionalExecuteTrack : public fight::Track
			{
			public:
				// 0x10226E40
				ConditionalExecuteTrack();
				virtual ~ConditionalExecuteTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101E88C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				fight::BranchHolder* SetBranch();
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					fight::ConditionList conditions;  // +0x34
					float timeBegin;  // +0x38
					float timeEnd;  // +0x3C
			};

			extern fight::Property** gConditionalExecuteTrackProperties;
			fight::TrackFactory* CreateConditionalExecuteTrackFactory(const char* name);
			void RegisterConditionalExecuteTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// RTTI: proto::fightitems::ai::ConditionalExecuteAction (9 vftable slots, 0x88 bytes)
			class ConditionalExecuteAction : public fight::Action
			{
			public:
				// 0x101E8700
				ConditionalExecuteAction(fight::Track* newListener, ConditionalExecuteTrack* newTrack, int newEffect, core::IRefCount* newOwner);
				// 0x101E8630
				virtual ~ConditionalExecuteAction();

				// vftable slot 3 (0x101E8560)
				virtual fight::Sequencer* GetChild();
				// vftable slot 5 (0x101E87E0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101E8570)
				virtual void Slot6();
				// vftable slot 7 (0x101E8810)
				virtual bool Slot7(int arg, float value);

				engine::TrackWatch watch;  // +0x1C
				core::Link<ConditionalExecuteTrack> link;  // +0x28
				int effect;  // +0x34
				core::IRefCount* owner;  // +0x38
				bool active;  // +0x3C
				unsigned char unknown3D[0x3];
				fight::Sequencer sequencer;  // +0x40
			};

			// ---- actions end
		}
	}
}

#endif
