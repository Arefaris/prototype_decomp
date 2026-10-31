// Fight items of the alert group: DisguiseReactionCondition, ReactionTrack (unit 0x10275910 - 0x10276170; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_ALERT_ALERT_REACTION_H
#define PROTO_FIGHTITEMS_ALERT_ALERT_REACTION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/alert/alertdata.h"

namespace proto
{
	namespace fightitems
	{
		namespace alert
		{
			// RTTI: proto::fightitems::alert::DisguiseReactionCondition (10 vftable slots, 0x14 bytes)
			class DisguiseReactionCondition : public fight::Condition
			{
			public:
				// 0x102759B0
				DisguiseReactionCondition();
				virtual ~DisguiseReactionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1026D600, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetReaction(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int compare;  // +0xC
					int reaction;  // +0x10
			};

			extern fight::Property** gDisguiseReactionConditionProperties;
			fight::ConditionFactory* CreateDisguiseReactionConditionFactory(const char* name);
			void RegisterDisguiseReactionConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::ReactionTrack (16 vftable slots, 0x1C bytes)
			class ReactionTrack : public fight::Track
			{
			public:
				// 0x10275A20
				ReactionTrack();
				virtual ~ReactionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1026D880, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetReaction(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int reaction;  // +0x18
			};

			extern fight::Property** gReactionTrackProperties;
			fight::TrackFactory* CreateReactionTrackFactory(const char* name);
			void RegisterReactionTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::alert::ReactionAction (9 vftable slots, 0x2C bytes)
			class ReactionAction : public fight::Action
			{
			public:
				// 0x1026D740
				ReactionAction(ReactionTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1026D5D0
				virtual ~ReactionAction();

				// vftable slot 5 (0x1026D7F0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x1026D460)
				virtual void Slot6();
				// vftable slot 7 (0x1026D450)
				virtual bool Slot7(int arg, float value);

				core::Link<ReactionTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
