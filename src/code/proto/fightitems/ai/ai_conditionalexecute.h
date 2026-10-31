// Fight items of the ai group: ConditionalExecuteTrack (unit 0x10226DB0 - 0x102272B0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_CONDITIONALEXECUTE_H
#define PROTO_FIGHTITEMS_AI_AI_CONDITIONALEXECUTE_H

#include "code/engine/fight/bitfieldproperty.h"
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

			// ---- actions end
		}
	}
}

#endif
