// Fight items of the ai group: EventValueCondition, EventCondition, AiTreeEventSendTrack (unit 0x1022F8E0 - 0x102305F0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_aitreeevent.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gEventValueConditionProperties;  // 0x112559B8

			// FUNCTION: ENGINE 0x1022F9E0
			bool EventValueCondition::SetEvent(const fight::Name& newValue)
			{
				event = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022F8E0
			bool EventValueCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022F8F0
			bool EventValueCondition::SetValue(int newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022F950
			fight::Property* EventValueCondition::GetProperty(int index)
			{
				return gEventValueConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022F970
			void EventValueCondition::ClearProperties()
			{
				fight::FreePropertyList(&gEventValueConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022FA40
			EventValueCondition::EventValueCondition() : fight::Condition(0), compare(0), value(10)
			{
			}

			// FUNCTION: ENGINE 0x1022FA80
			EventValueCondition::~EventValueCondition()
			{
			}

			// FUNCTION: ENGINE 0x102300E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EventValueCondition::RegisterProperties()
			{
				if (gEventValueConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<EventValueCondition>("event", &EventValueCondition::SetEvent);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<EventValueCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &EventValueCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyIntConstRange<EventValueCondition>("value", &EventValueCondition::SetValue);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gEventValueConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022FED0
			fight::ConditionFactory* CreateEventValueConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<EventValueCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022FF60
			void RegisterEventValueConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<EventValueCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gEventConditionProperties;  // 0x112559BC

			// FUNCTION: ENGINE 0x1022FA00
			bool EventCondition::SetEvent(const fight::Name& newValue)
			{
				event = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022F900
			bool EventCondition::SetWhen(int newValue)
			{
				when = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022F980
			fight::Property* EventCondition::GetProperty(int index)
			{
				return gEventConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1022F9A0
			void EventCondition::ClearProperties()
			{
				fight::FreePropertyList(&gEventConditionProperties);
			}

			// FUNCTION: ENGINE 0x1022FA90
			EventCondition::EventCondition() : fight::Condition(0), when(0)
			{
			}

			// FUNCTION: ENGINE 0x1022FAC0
			EventCondition::~EventCondition()
			{
			}

			// FUNCTION: ENGINE 0x10230210
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EventCondition::RegisterProperties()
			{
				if (gEventConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<EventCondition>("event", &EventCondition::SetEvent);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<EventCondition>("when", gEventConditionWhenTable, gEventConditionWhenCount, &EventCondition::SetWhen);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gEventConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022FF00
			fight::ConditionFactory* CreateEventConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<EventCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022FF90
			void RegisterEventConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<EventCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAiTreeEventSendTrackProperties;  // 0x112559C0

			// FUNCTION: ENGINE 0x1022F910
			bool AiTreeEventSendTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022F930
			bool AiTreeEventSendTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022FA20
			bool AiTreeEventSendTrack::SetEvent(const fight::Name& newValue)
			{
				event = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1022F9B0
			fight::Property* AiTreeEventSendTrack::GetProperty(int index)
			{
				return gAiTreeEventSendTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1022F9D0
			void AiTreeEventSendTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAiTreeEventSendTrackProperties);
			}

			// FUNCTION: ENGINE 0x1022FAD0
			AiTreeEventSendTrack::AiTreeEventSendTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1022FB20
			float AiTreeEventSendTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1022FB30
			float AiTreeEventSendTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1022FB40
			AiTreeEventSendTrack::~AiTreeEventSendTrack()
			{
			}

			// FUNCTION: ENGINE 0x10230300
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AiTreeEventSendTrack::RegisterProperties()
			{
				if (gAiTreeEventSendTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AiTreeEventSendTrack>("timeBegin", &AiTreeEventSendTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AiTreeEventSendTrack>("timeEnd", &AiTreeEventSendTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<AiTreeEventSendTrack>("event", &AiTreeEventSendTrack::SetEvent);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gAiTreeEventSendTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1022FF30
			fight::TrackFactory* CreateAiTreeEventSendTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AiTreeEventSendTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1022FFC0
			void RegisterAiTreeEventSendTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AiTreeEventSendTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101F0B90
			AiTreeEventSendAction::AiTreeEventSendAction(AiTreeEventSendTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101F08B0
			AiTreeEventSendAction::~AiTreeEventSendAction()
			{
			}

			// FUNCTION: ENGINE 0x101F07A0
			bool AiTreeEventSendAction::Slot7(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x101F0DB0
			fight::Action* AiTreeEventSendTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new AiTreeEventSendAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyName<EventValueCondition>;
			template class fight::PropertyEnumConstList<EventValueCondition>;
			template class fight::PropertyIntConstRange<EventValueCondition>;
			template class fight::ConditionFactoryTemplate<EventValueCondition>;
			template class fight::ConditionFactoryCasterTemplate<EventValueCondition>;
			template class fight::PropertyName<EventCondition>;
			template class fight::PropertyEnumConstList<EventCondition>;
			template class fight::ConditionFactoryTemplate<EventCondition>;
			template class fight::ConditionFactoryCasterTemplate<EventCondition>;
			template class fight::PropertyFloatConstRange<AiTreeEventSendTrack>;
			template class fight::PropertyName<AiTreeEventSendTrack>;
			template class fight::TrackFactoryTemplate<AiTreeEventSendTrack>;
			template class fight::TrackFactoryCasterTemplate<AiTreeEventSendTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101F0C10
// FUNCTION: ENGINE 0x1022FB50
// FUNCTION: ENGINE 0x1022FB60
// FUNCTION: ENGINE 0x1022FB90
// FUNCTION: ENGINE 0x1022FBA0
// FUNCTION: ENGINE 0x1022FBD0
// FUNCTION: ENGINE 0x1022FBE0
// FUNCTION: ENGINE 0x1022FC10
// FUNCTION: ENGINE 0x1022FC40
// FUNCTION: ENGINE 0x1022FC70
// FUNCTION: ENGINE 0x1022FCA0
// FUNCTION: ENGINE 0x1022FCE0
// FUNCTION: ENGINE 0x1022FCF0
// FUNCTION: ENGINE 0x1022FD20
// FUNCTION: ENGINE 0x1022FD40
// FUNCTION: ENGINE 0x1022FD50
// FUNCTION: ENGINE 0x1022FD80
// FUNCTION: ENGINE 0x1022FDA0
// FUNCTION: ENGINE 0x1022FDB0
// FUNCTION: ENGINE 0x1022FDF0
// FUNCTION: ENGINE 0x1022FE00
// FUNCTION: ENGINE 0x1022FE30
// FUNCTION: ENGINE 0x1022FE50
// FUNCTION: ENGINE 0x1022FE60
// FUNCTION: ENGINE 0x1022FE90
// FUNCTION: ENGINE 0x1022FEC0
// FUNCTION: ENGINE 0x1022FFF0
// FUNCTION: ENGINE 0x10230020
// FUNCTION: ENGINE 0x10230040
// FUNCTION: ENGINE 0x10230070
// FUNCTION: ENGINE 0x10230090
// FUNCTION: ENGINE 0x102300C0
// FUNCTION: ENGINE 0x10230410
// FUNCTION: ENGINE 0x10230440
// FUNCTION: ENGINE 0x10230460
// FUNCTION: ENGINE 0x10230490
// FUNCTION: ENGINE 0x102304B0
// FUNCTION: ENGINE 0x102304E0
// FUNCTION: ENGINE 0x10230500
// FUNCTION: ENGINE 0x10230550
// FUNCTION: ENGINE 0x102305A0
