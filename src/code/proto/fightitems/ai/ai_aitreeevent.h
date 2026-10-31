// Fight items of the ai group: EventValueCondition, EventCondition, AiTreeEventSendTrack (unit 0x1022F8E0 - 0x102305F0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_AITREEEVENT_H
#define PROTO_FIGHTITEMS_AI_AI_AITREEEVENT_H

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
			// RTTI: proto::fightitems::ai::EventValueCondition (10 vftable slots, 0x20 bytes)
			class EventValueCondition : public fight::Condition
			{
			public:
				// 0x1022FA40
				EventValueCondition();
				virtual ~EventValueCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101F0A00, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetEvent(const fight::Name& newValue);
				bool SetCompare(int newValue);
				bool SetValue(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name event;  // +0x10
					int compare;  // +0x18
					int value;  // +0x1C
			};

			extern fight::Property** gEventValueConditionProperties;
			fight::ConditionFactory* CreateEventValueConditionFactory(const char* name);
			void RegisterEventValueConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::EventCondition (10 vftable slots, 0x20 bytes)
			class EventCondition : public fight::Condition
			{
			public:
				// 0x1022FA90
				EventCondition();
				virtual ~EventCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101F08E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetEvent(const fight::Name& newValue);
				bool SetWhen(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name event;  // +0x10
					int when;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gEventConditionProperties;
			fight::ConditionFactory* CreateEventConditionFactory(const char* name);
			void RegisterEventConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::AiTreeEventSendTrack (16 vftable slots, 0x20 bytes)
			class AiTreeEventSendTrack : public fight::Track
			{
			public:
				// 0x1022FAD0
				AiTreeEventSendTrack();
				virtual ~AiTreeEventSendTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F0DB0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetEvent(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name event;  // +0x10
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
			};

			extern fight::Property** gAiTreeEventSendTrackProperties;
			fight::TrackFactory* CreateAiTreeEventSendTrackFactory(const char* name);
			void RegisterAiTreeEventSendTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::AiTreeEventSendAction (9 vftable slots, 0x2C bytes)
			class AiTreeEventSendAction : public fight::Action
			{
			public:
				// 0x101F0B90
				AiTreeEventSendAction(AiTreeEventSendTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101F08B0
				virtual ~AiTreeEventSendAction();

				// vftable slot 5 (0x101F0C40)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101F0D00)
				virtual void Slot6();
				// vftable slot 7 (0x101F07A0)
				virtual bool Slot7(int arg, float value);

				core::Link<AiTreeEventSendTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
