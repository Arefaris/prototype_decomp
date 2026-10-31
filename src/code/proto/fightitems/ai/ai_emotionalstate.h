// Fight items of the ai group: EmotionalStateCondition, RequestStopPursuitCondition, RequestCheckBodyCondition, RequestPlayerDiversionCondition, RequestDenyPatsyCondition, RequestCallStrikeTeamCondition, RequestRecognizePatsyCondition, RequestPointingCondition, RequestLostHimCondition, RequestSuspicionCondition, RequestRadioHQCondition, ForceEmotionalStateTrack (unit 0x1022AC60 - 0x1022CB50; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_EMOTIONALSTATE_H
#define PROTO_FIGHTITEMS_AI_AI_EMOTIONALSTATE_H

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
			// RTTI: proto::fightitems::ai::EmotionalStateCondition (10 vftable slots, 0x18 bytes)
			class EmotionalStateCondition : public fight::Condition
			{
			public:
				// 0x1022B460
				EmotionalStateCondition();
				virtual ~EmotionalStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101EC010, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetState(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name state;  // +0x10
			};

			extern fight::Property** gEmotionalStateConditionProperties;
			fight::ConditionFactory* CreateEmotionalStateConditionFactory(const char* name);
			void RegisterEmotionalStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RequestStopPursuitCondition (10 vftable slots, 0x10 bytes)
			class RequestStopPursuitCondition : public fight::Condition
			{
			public:
				// 0x1022AD40
				RequestStopPursuitCondition();
				virtual ~RequestStopPursuitCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101EC8C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetMinActorAge(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float minActorAge;  // +0xC
			};

			extern fight::Property** gRequestStopPursuitConditionProperties;
			fight::ConditionFactory* CreateRequestStopPursuitConditionFactory(const char* name);
			void RegisterRequestStopPursuitConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RequestCheckBodyCondition (10 vftable slots, 0xC bytes)
			class RequestCheckBodyCondition : public fight::Condition
			{
			public:
				// 0x1022AE10
				RequestCheckBodyCondition();
				virtual ~RequestCheckBodyCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101EC440, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gRequestCheckBodyConditionProperties;
			fight::ConditionFactory* CreateRequestCheckBodyConditionFactory(const char* name);
			void RegisterRequestCheckBodyConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RequestPlayerDiversionCondition (10 vftable slots, 0xC bytes)
			class RequestPlayerDiversionCondition : public fight::Condition
			{
			public:
				// 0x1022AED0
				RequestPlayerDiversionCondition();
				virtual ~RequestPlayerDiversionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101ECDB0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gRequestPlayerDiversionConditionProperties;
			fight::ConditionFactory* CreateRequestPlayerDiversionConditionFactory(const char* name);
			void RegisterRequestPlayerDiversionConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RequestDenyPatsyCondition (10 vftable slots, 0xC bytes)
			class RequestDenyPatsyCondition : public fight::Condition
			{
			public:
				// 0x1022AF90
				RequestDenyPatsyCondition();
				virtual ~RequestDenyPatsyCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101ECBD0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gRequestDenyPatsyConditionProperties;
			fight::ConditionFactory* CreateRequestDenyPatsyConditionFactory(const char* name);
			void RegisterRequestDenyPatsyConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RequestCallStrikeTeamCondition (10 vftable slots, 0x10 bytes)
			class RequestCallStrikeTeamCondition : public fight::Condition
			{
			public:
				// 0x1022AFF0
				RequestCallStrikeTeamCondition();
				virtual ~RequestCallStrikeTeamCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101EC7D0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetMinActorAge(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float minActorAge;  // +0xC
			};

			extern fight::Property** gRequestCallStrikeTeamConditionProperties;
			fight::ConditionFactory* CreateRequestCallStrikeTeamConditionFactory(const char* name);
			void RegisterRequestCallStrikeTeamConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RequestRecognizePatsyCondition (10 vftable slots, 0xC bytes)
			class RequestRecognizePatsyCondition : public fight::Condition
			{
			public:
				// 0x1022B0C0
				RequestRecognizePatsyCondition();
				virtual ~RequestRecognizePatsyCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101EC9F0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gRequestRecognizePatsyConditionProperties;
			fight::ConditionFactory* CreateRequestRecognizePatsyConditionFactory(const char* name);
			void RegisterRequestRecognizePatsyConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RequestPointingCondition (10 vftable slots, 0xC bytes)
			class RequestPointingCondition : public fight::Condition
			{
			public:
				// 0x1022B180
				RequestPointingCondition();
				virtual ~RequestPointingCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101EC1D0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gRequestPointingConditionProperties;
			fight::ConditionFactory* CreateRequestPointingConditionFactory(const char* name);
			void RegisterRequestPointingConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RequestLostHimCondition (10 vftable slots, 0xC bytes)
			class RequestLostHimCondition : public fight::Condition
			{
			public:
				// 0x1022B240
				RequestLostHimCondition();
				virtual ~RequestLostHimCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101EC310, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gRequestLostHimConditionProperties;
			fight::ConditionFactory* CreateRequestLostHimConditionFactory(const char* name);
			void RegisterRequestLostHimConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RequestSuspicionCondition (10 vftable slots, 0xC bytes)
			class RequestSuspicionCondition : public fight::Condition
			{
			public:
				// 0x1022B300
				RequestSuspicionCondition();
				virtual ~RequestSuspicionCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101EC090, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gRequestSuspicionConditionProperties;
			fight::ConditionFactory* CreateRequestSuspicionConditionFactory(const char* name);
			void RegisterRequestSuspicionConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::RequestRadioHQCondition (10 vftable slots, 0xC bytes)
			class RequestRadioHQCondition : public fight::Condition
			{
			public:
				// 0x1022B3C0
				RequestRadioHQCondition();
				virtual ~RequestRadioHQCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101EC6E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gRequestRadioHQConditionProperties;
			fight::ConditionFactory* CreateRequestRadioHQConditionFactory(const char* name);
			void RegisterRequestRadioHQConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ForceEmotionalStateTrack (16 vftable slots, 0x20 bytes)
			class ForceEmotionalStateTrack : public fight::Track
			{
			public:
				// 0x1022B680
				ForceEmotionalStateTrack();
				virtual ~ForceEmotionalStateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101ED070, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetState(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name state;  // +0x10
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
			};

			extern fight::Property** gForceEmotionalStateTrackProperties;
			fight::TrackFactory* CreateForceEmotionalStateTrackFactory(const char* name);
			void RegisterForceEmotionalStateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::ForceEmotionalStateAction (9 vftable slots, 0x2C bytes)
			class ForceEmotionalStateAction : public fight::Action
			{
			public:
				// 0x101ECF50
				ForceEmotionalStateAction(ForceEmotionalStateTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101EBFE0
				virtual ~ForceEmotionalStateAction();

				// vftable slot 5 (0x101EBE70)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101EBE80)
				virtual void Slot6();
				// vftable slot 7 (0x101ED000)
				virtual bool Slot7(int arg, float value);

				core::Link<ForceEmotionalStateTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
