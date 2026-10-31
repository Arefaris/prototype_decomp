// Fight items of the alert group: DisguiseBlownCondition, BlowDisguiseTrack (unit 0x102689E0 - 0x1026E0E0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_ALERT_ALERT_DISGUISEBLOWN_H
#define PROTO_FIGHTITEMS_ALERT_ALERT_DISGUISEBLOWN_H

#include "code/proto/messages/disguisemessages.h"
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
			// RTTI: proto::fightitems::alert::DisguiseBlownCondition (10 vftable slots, 0x14 bytes)
			class DisguiseBlownCondition : public fight::Condition
			{
			public:
				// 0x1026D990
				DisguiseBlownCondition();
				virtual ~DisguiseBlownCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10268C00, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetValue(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float value;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gDisguiseBlownConditionProperties;
			fight::ConditionFactory* CreateDisguiseBlownConditionFactory(const char* name);
			void RegisterDisguiseBlownConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::alert::BlowDisguiseTrack (16 vftable slots, 0x1C bytes)
			class BlowDisguiseTrack : public fight::Track
			{
			public:
				// 0x1026DA00
				BlowDisguiseTrack();
				virtual ~BlowDisguiseTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10268E90, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetBlownTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blownTime;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
			};

			extern fight::Property** gBlowDisguiseTrackProperties;
			fight::TrackFactory* CreateBlowDisguiseTrackFactory(const char* name);
			void RegisterBlowDisguiseTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::alert::BlowDisguiseAction (9 vftable slots, 0x2C bytes)
			class BlowDisguiseAction : public fight::Action
			{
			public:
				// 0x10268D40
				BlowDisguiseAction(BlowDisguiseTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10268BD0
				virtual ~BlowDisguiseAction();

				// vftable slot 5 (0x10268AA0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10268AB0)
				virtual void Slot6();
				// vftable slot 7 (0x10268DF0)
				virtual bool Slot7(int arg, float value);

				core::Link<BlowDisguiseTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
