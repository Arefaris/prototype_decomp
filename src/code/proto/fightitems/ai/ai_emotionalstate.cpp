// Fight items of the ai group: EmotionalStateCondition, RequestStopPursuitCondition, RequestCheckBodyCondition, RequestPlayerDiversionCondition, RequestDenyPatsyCondition, RequestCallStrikeTeamCondition, RequestRecognizePatsyCondition, RequestPointingCondition, RequestLostHimCondition, RequestSuspicionCondition, RequestRadioHQCondition, ForceEmotionalStateTrack (unit 0x1022AC60 - 0x1022CB50; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_emotionalstate.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gEmotionalStateConditionProperties;  // 0x11255948

			// FUNCTION: ENGINE 0x1022B420
			bool EmotionalStateCondition::SetState(const fight::Name& newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022ACE0
			fight::Property* EmotionalStateCondition::GetProperty(int index)
			{
				return gEmotionalStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022AD00
			void EmotionalStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gEmotionalStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022B460
			EmotionalStateCondition::EmotionalStateCondition() : fight::Condition(0), state(static_cast<const char*>(0), 1)
			{
			}

			// FUNCTION: ENGINE 0x1022B490
			EmotionalStateCondition::~EmotionalStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022C7C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EmotionalStateCondition::RegisterProperties()
			{
				if (gEmotionalStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameConstList<EmotionalStateCondition>("state", &EmotionalStateCondition::SetState);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gEmotionalStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022C0A0
			fight::ConditionFactory* CreateEmotionalStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<EmotionalStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022C420
			void RegisterEmotionalStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<EmotionalStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gRequestStopPursuitConditionProperties;  // 0x1125594C

			// FUNCTION: ENGINE 0x1022AC60
			bool RequestStopPursuitCondition::SetMinActorAge(float newValue)
			{
				minActorAge = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022AD10
			fight::Property* RequestStopPursuitCondition::GetProperty(int index)
			{
				return gRequestStopPursuitConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022AD30
			void RequestStopPursuitCondition::ClearProperties()
			{
				fight::FreePropertyList(&gRequestStopPursuitConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022AD40
			RequestStopPursuitCondition::RequestStopPursuitCondition() : fight::Condition(0), minActorAge(5.0f)
			{
			}

			// FUNCTION: ENGINE 0x1022AD70
			RequestStopPursuitCondition::~RequestStopPursuitCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022C2E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RequestStopPursuitCondition::RegisterProperties()
			{
				if (gRequestStopPursuitConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<RequestStopPursuitCondition>("minActorAge", &RequestStopPursuitCondition::SetMinActorAge);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gRequestStopPursuitConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022C0D0
			fight::ConditionFactory* CreateRequestStopPursuitConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestStopPursuitCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022C450
			void RegisterRequestStopPursuitConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestStopPursuitCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gRequestCheckBodyConditionProperties;  // 0x11255950

			// FUNCTION: ENGINE 0x1022ADE0
			fight::Property* RequestCheckBodyCondition::GetProperty(int index)
			{
				return gRequestCheckBodyConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022AE00
			void RequestCheckBodyCondition::ClearProperties()
			{
				fight::FreePropertyList(&gRequestCheckBodyConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022AE10
			RequestCheckBodyCondition::RequestCheckBodyCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1022AE30
			RequestCheckBodyCondition::~RequestCheckBodyCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022AD80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RequestCheckBodyCondition::RegisterProperties()
			{
				if (gRequestCheckBodyConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gRequestCheckBodyConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022C100
			fight::ConditionFactory* CreateRequestCheckBodyConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestCheckBodyCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022C480
			void RegisterRequestCheckBodyConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestCheckBodyCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gRequestPlayerDiversionConditionProperties;  // 0x11255954

			// FUNCTION: ENGINE 0x1022AEA0
			fight::Property* RequestPlayerDiversionCondition::GetProperty(int index)
			{
				return gRequestPlayerDiversionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022AEC0
			void RequestPlayerDiversionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gRequestPlayerDiversionConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022AED0
			RequestPlayerDiversionCondition::RequestPlayerDiversionCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1022AEF0
			RequestPlayerDiversionCondition::~RequestPlayerDiversionCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022AE40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RequestPlayerDiversionCondition::RegisterProperties()
			{
				if (gRequestPlayerDiversionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gRequestPlayerDiversionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022C130
			fight::ConditionFactory* CreateRequestPlayerDiversionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestPlayerDiversionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022C4B0
			void RegisterRequestPlayerDiversionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestPlayerDiversionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gRequestDenyPatsyConditionProperties;  // 0x11255958

			// FUNCTION: ENGINE 0x1022AF60
			fight::Property* RequestDenyPatsyCondition::GetProperty(int index)
			{
				return gRequestDenyPatsyConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022AF80
			void RequestDenyPatsyCondition::ClearProperties()
			{
				fight::FreePropertyList(&gRequestDenyPatsyConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022AF90
			RequestDenyPatsyCondition::RequestDenyPatsyCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1022AFB0
			RequestDenyPatsyCondition::~RequestDenyPatsyCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022AF00
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RequestDenyPatsyCondition::RegisterProperties()
			{
				if (gRequestDenyPatsyConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gRequestDenyPatsyConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022C160
			fight::ConditionFactory* CreateRequestDenyPatsyConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestDenyPatsyCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022C4E0
			void RegisterRequestDenyPatsyConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestDenyPatsyCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gRequestCallStrikeTeamConditionProperties;  // 0x1125595C

			// FUNCTION: ENGINE 0x1022AC80
			bool RequestCallStrikeTeamCondition::SetMinActorAge(float newValue)
			{
				minActorAge = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022AFC0
			fight::Property* RequestCallStrikeTeamCondition::GetProperty(int index)
			{
				return gRequestCallStrikeTeamConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022AFE0
			void RequestCallStrikeTeamCondition::ClearProperties()
			{
				fight::FreePropertyList(&gRequestCallStrikeTeamConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022AFF0
			RequestCallStrikeTeamCondition::RequestCallStrikeTeamCondition() : fight::Condition(0), minActorAge(5.0f)
			{
			}

			// FUNCTION: ENGINE 0x1022B020
			RequestCallStrikeTeamCondition::~RequestCallStrikeTeamCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022C380
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RequestCallStrikeTeamCondition::RegisterProperties()
			{
				if (gRequestCallStrikeTeamConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<RequestCallStrikeTeamCondition>("minActorAge", &RequestCallStrikeTeamCondition::SetMinActorAge);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gRequestCallStrikeTeamConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022C190
			fight::ConditionFactory* CreateRequestCallStrikeTeamConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestCallStrikeTeamCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022C510
			void RegisterRequestCallStrikeTeamConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestCallStrikeTeamCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gRequestRecognizePatsyConditionProperties;  // 0x11255960

			// FUNCTION: ENGINE 0x1022B090
			fight::Property* RequestRecognizePatsyCondition::GetProperty(int index)
			{
				return gRequestRecognizePatsyConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022B0B0
			void RequestRecognizePatsyCondition::ClearProperties()
			{
				fight::FreePropertyList(&gRequestRecognizePatsyConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022B0C0
			RequestRecognizePatsyCondition::RequestRecognizePatsyCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1022B0E0
			RequestRecognizePatsyCondition::~RequestRecognizePatsyCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022B030
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RequestRecognizePatsyCondition::RegisterProperties()
			{
				if (gRequestRecognizePatsyConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gRequestRecognizePatsyConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022C1C0
			fight::ConditionFactory* CreateRequestRecognizePatsyConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestRecognizePatsyCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022C540
			void RegisterRequestRecognizePatsyConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestRecognizePatsyCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gRequestPointingConditionProperties;  // 0x11255964

			// FUNCTION: ENGINE 0x1022B150
			fight::Property* RequestPointingCondition::GetProperty(int index)
			{
				return gRequestPointingConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022B170
			void RequestPointingCondition::ClearProperties()
			{
				fight::FreePropertyList(&gRequestPointingConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022B180
			RequestPointingCondition::RequestPointingCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1022B1A0
			RequestPointingCondition::~RequestPointingCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022B0F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RequestPointingCondition::RegisterProperties()
			{
				if (gRequestPointingConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gRequestPointingConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022C1F0
			fight::ConditionFactory* CreateRequestPointingConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestPointingCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022C570
			void RegisterRequestPointingConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestPointingCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gRequestLostHimConditionProperties;  // 0x11255968

			// FUNCTION: ENGINE 0x1022B210
			fight::Property* RequestLostHimCondition::GetProperty(int index)
			{
				return gRequestLostHimConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022B230
			void RequestLostHimCondition::ClearProperties()
			{
				fight::FreePropertyList(&gRequestLostHimConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022B240
			RequestLostHimCondition::RequestLostHimCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1022B260
			RequestLostHimCondition::~RequestLostHimCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022B1B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RequestLostHimCondition::RegisterProperties()
			{
				if (gRequestLostHimConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gRequestLostHimConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022C220
			fight::ConditionFactory* CreateRequestLostHimConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestLostHimCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022C5A0
			void RegisterRequestLostHimConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestLostHimCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gRequestSuspicionConditionProperties;  // 0x1125596C

			// FUNCTION: ENGINE 0x1022B2D0
			fight::Property* RequestSuspicionCondition::GetProperty(int index)
			{
				return gRequestSuspicionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022B2F0
			void RequestSuspicionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gRequestSuspicionConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022B300
			RequestSuspicionCondition::RequestSuspicionCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1022B320
			RequestSuspicionCondition::~RequestSuspicionCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022B270
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RequestSuspicionCondition::RegisterProperties()
			{
				if (gRequestSuspicionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gRequestSuspicionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022C250
			fight::ConditionFactory* CreateRequestSuspicionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestSuspicionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022C5D0
			void RegisterRequestSuspicionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestSuspicionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gRequestRadioHQConditionProperties;  // 0x11255970

			// FUNCTION: ENGINE 0x1022B390
			fight::Property* RequestRadioHQCondition::GetProperty(int index)
			{
				return gRequestRadioHQConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022B3B0
			void RequestRadioHQCondition::ClearProperties()
			{
				fight::FreePropertyList(&gRequestRadioHQConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022B3C0
			RequestRadioHQCondition::RequestRadioHQCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1022B3E0
			RequestRadioHQCondition::~RequestRadioHQCondition()
			{
			}

			// FUNCTION: ENGINE 0x1022B330
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RequestRadioHQCondition::RegisterProperties()
			{
				if (gRequestRadioHQConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gRequestRadioHQConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022C280
			fight::ConditionFactory* CreateRequestRadioHQConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestRadioHQCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022C600
			void RegisterRequestRadioHQConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<RequestRadioHQCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gForceEmotionalStateTrackProperties;  // 0x11255974

			// FUNCTION: ENGINE 0x1022ACA0
			bool ForceEmotionalStateTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022ACC0
			bool ForceEmotionalStateTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022B440
			bool ForceEmotionalStateTrack::SetState(const fight::Name& newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022B3F0
			fight::Property* ForceEmotionalStateTrack::GetProperty(int index)
			{
				return gForceEmotionalStateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1022B410
			void ForceEmotionalStateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gForceEmotionalStateTrackProperties);
			}

			// FUNCTION: ENGINE 0x1022B680
			ForceEmotionalStateTrack::ForceEmotionalStateTrack() : state(static_cast<const char*>(0), 1), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1022B6C0
			float ForceEmotionalStateTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1022B6D0
			float ForceEmotionalStateTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1022B6E0
			ForceEmotionalStateTrack::~ForceEmotionalStateTrack()
			{
			}

			// FUNCTION: ENGINE 0x1022C860
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ForceEmotionalStateTrack::RegisterProperties()
			{
				if (gForceEmotionalStateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ForceEmotionalStateTrack>("timeBegin", &ForceEmotionalStateTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ForceEmotionalStateTrack>("timeEnd", &ForceEmotionalStateTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameConstList<ForceEmotionalStateTrack>("state", &ForceEmotionalStateTrack::SetState);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gForceEmotionalStateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022C2B0
			fight::TrackFactory* CreateForceEmotionalStateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ForceEmotionalStateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022C630
			void RegisterForceEmotionalStateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ForceEmotionalStateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}


			// FUNCTION: ENGINE 0x101EC010
			// EQUIVALENT: register allocation and scheduling (the engine keeps the false result in bl and pushes the name's address after the call of the name getter, ours before it); the same calls (best 23.6 %)
			bool EmotionalStateCondition::Evaluate(int a, int b, int c, int d)
			{
				bool result = false;
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object != 0)
				{
					return *proto::Unknown103B92B0(object) == state;
				}
				return result;
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101ECF50
			ForceEmotionalStateAction::ForceEmotionalStateAction(ForceEmotionalStateTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101EBFE0
			ForceEmotionalStateAction::~ForceEmotionalStateAction()
			{
			}

			// FUNCTION: ENGINE 0x101EBE70
			bool ForceEmotionalStateAction::Slot5(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x101EBE80
			void ForceEmotionalStateAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101ED070
			fight::Action* ForceEmotionalStateTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ForceEmotionalStateAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyNameConstList<EmotionalStateCondition>;
			template class fight::ConditionFactoryTemplate<EmotionalStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<EmotionalStateCondition>;
			template class fight::PropertyFloatConstRange<RequestStopPursuitCondition>;
			template class fight::ConditionFactoryTemplate<RequestStopPursuitCondition>;
			template class fight::ConditionFactoryCasterTemplate<RequestStopPursuitCondition>;
			template class fight::ConditionFactoryTemplate<RequestCheckBodyCondition>;
			template class fight::ConditionFactoryCasterTemplate<RequestCheckBodyCondition>;
			template class fight::ConditionFactoryTemplate<RequestPlayerDiversionCondition>;
			template class fight::ConditionFactoryCasterTemplate<RequestPlayerDiversionCondition>;
			template class fight::ConditionFactoryTemplate<RequestDenyPatsyCondition>;
			template class fight::ConditionFactoryCasterTemplate<RequestDenyPatsyCondition>;
			template class fight::PropertyFloatConstRange<RequestCallStrikeTeamCondition>;
			template class fight::ConditionFactoryTemplate<RequestCallStrikeTeamCondition>;
			template class fight::ConditionFactoryCasterTemplate<RequestCallStrikeTeamCondition>;
			template class fight::ConditionFactoryTemplate<RequestRecognizePatsyCondition>;
			template class fight::ConditionFactoryCasterTemplate<RequestRecognizePatsyCondition>;
			template class fight::ConditionFactoryTemplate<RequestPointingCondition>;
			template class fight::ConditionFactoryCasterTemplate<RequestPointingCondition>;
			template class fight::ConditionFactoryTemplate<RequestLostHimCondition>;
			template class fight::ConditionFactoryCasterTemplate<RequestLostHimCondition>;
			template class fight::ConditionFactoryTemplate<RequestSuspicionCondition>;
			template class fight::ConditionFactoryCasterTemplate<RequestSuspicionCondition>;
			template class fight::ConditionFactoryTemplate<RequestRadioHQCondition>;
			template class fight::ConditionFactoryCasterTemplate<RequestRadioHQCondition>;
			template class fight::PropertyFloatConstRange<ForceEmotionalStateTrack>;
			template class fight::PropertyNameConstList<ForceEmotionalStateTrack>;
			template class fight::TrackFactoryTemplate<ForceEmotionalStateTrack>;
			template class fight::TrackFactoryCasterTemplate<ForceEmotionalStateTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101ECFD0
// FUNCTION: ENGINE 0x1022B4A0
// FUNCTION: ENGINE 0x1022B4D0
// FUNCTION: ENGINE 0x1022B500
// FUNCTION: ENGINE 0x1022B530
// FUNCTION: ENGINE 0x1022B560
// FUNCTION: ENGINE 0x1022B590
// FUNCTION: ENGINE 0x1022B5C0
// FUNCTION: ENGINE 0x1022B5F0
// FUNCTION: ENGINE 0x1022B620
// FUNCTION: ENGINE 0x1022B650
// FUNCTION: ENGINE 0x1022B6F0
// FUNCTION: ENGINE 0x1022B700
// FUNCTION: ENGINE 0x1022B730
// FUNCTION: ENGINE 0x1022B740
// FUNCTION: ENGINE 0x1022B770
// FUNCTION: ENGINE 0x1022B780
// FUNCTION: ENGINE 0x1022B7B0
// FUNCTION: ENGINE 0x1022B7E0
// FUNCTION: ENGINE 0x1022B800
// FUNCTION: ENGINE 0x1022B850
// FUNCTION: ENGINE 0x1022B860
// FUNCTION: ENGINE 0x1022B890
// FUNCTION: ENGINE 0x1022B8C0
// FUNCTION: ENGINE 0x1022B8E0
// FUNCTION: ENGINE 0x1022B930
// FUNCTION: ENGINE 0x1022B940
// FUNCTION: ENGINE 0x1022B970
// FUNCTION: ENGINE 0x1022B9A0
// FUNCTION: ENGINE 0x1022B9C0
// FUNCTION: ENGINE 0x1022BA10
// FUNCTION: ENGINE 0x1022BA20
// FUNCTION: ENGINE 0x1022BA50
// FUNCTION: ENGINE 0x1022BA60
// FUNCTION: ENGINE 0x1022BA90
// FUNCTION: ENGINE 0x1022BAC0
// FUNCTION: ENGINE 0x1022BAE0
// FUNCTION: ENGINE 0x1022BB30
// FUNCTION: ENGINE 0x1022BB40
// FUNCTION: ENGINE 0x1022BB70
// FUNCTION: ENGINE 0x1022BBA0
// FUNCTION: ENGINE 0x1022BBC0
// FUNCTION: ENGINE 0x1022BC10
// FUNCTION: ENGINE 0x1022BC20
// FUNCTION: ENGINE 0x1022BC50
// FUNCTION: ENGINE 0x1022BC80
// FUNCTION: ENGINE 0x1022BCA0
// FUNCTION: ENGINE 0x1022BCF0
// FUNCTION: ENGINE 0x1022BD00
// FUNCTION: ENGINE 0x1022BD30
// FUNCTION: ENGINE 0x1022BD60
// FUNCTION: ENGINE 0x1022BD80
// FUNCTION: ENGINE 0x1022BDD0
// FUNCTION: ENGINE 0x1022BDE0
// FUNCTION: ENGINE 0x1022BE10
// FUNCTION: ENGINE 0x1022BE40
// FUNCTION: ENGINE 0x1022BE60
// FUNCTION: ENGINE 0x1022BEB0
// FUNCTION: ENGINE 0x1022BEC0
// FUNCTION: ENGINE 0x1022BEF0
// FUNCTION: ENGINE 0x1022BF20
// FUNCTION: ENGINE 0x1022BF50
// FUNCTION: ENGINE 0x1022BF80
// FUNCTION: ENGINE 0x1022BFB0
// FUNCTION: ENGINE 0x1022BFC0
// FUNCTION: ENGINE 0x1022BFF0
// FUNCTION: ENGINE 0x1022C020
// FUNCTION: ENGINE 0x1022C030
// FUNCTION: ENGINE 0x1022C060
// FUNCTION: ENGINE 0x1022C090
// FUNCTION: ENGINE 0x1022C660
// FUNCTION: ENGINE 0x1022C690
// FUNCTION: ENGINE 0x1022C6B0
// FUNCTION: ENGINE 0x1022C6C0
// FUNCTION: ENGINE 0x1022C6F0
// FUNCTION: ENGINE 0x1022C710
// FUNCTION: ENGINE 0x1022C720
// FUNCTION: ENGINE 0x1022C750
// FUNCTION: ENGINE 0x1022C770
// FUNCTION: ENGINE 0x1022C7A0
// FUNCTION: ENGINE 0x1022C970
// FUNCTION: ENGINE 0x1022C9C0
// FUNCTION: ENGINE 0x1022CA10
// FUNCTION: ENGINE 0x1022CA40
// FUNCTION: ENGINE 0x1022CA60
// FUNCTION: ENGINE 0x1022CA90
// FUNCTION: ENGINE 0x1022CAB0
// FUNCTION: ENGINE 0x1022CB00
