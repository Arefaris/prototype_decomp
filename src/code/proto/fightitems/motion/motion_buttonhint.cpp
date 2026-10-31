// Fight items of the motion group: ButtonHintShowingCondition, EnableButtonHintsTrack, ButtonHintShowTrack (unit 0x10146A60 - 0x101479B0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_buttonhint.h"
#include <new>

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gButtonHintShowingConditionProperties;  // 0x11254310

			// FUNCTION: ENGINE 0x10146C40
			bool ButtonHintShowingCondition::SetButtonHint(const fight::Name& newValue)
			{
				buttonHint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10146B20
			fight::Property* ButtonHintShowingCondition::GetProperty(int index)
			{
				return gButtonHintShowingConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10146B40
			void ButtonHintShowingCondition::ClearProperties()
			{
				fight::FreePropertyList(&gButtonHintShowingConditionProperties);
			}

			// FUNCTION: ENGINE 0x10146C80
			ButtonHintShowingCondition::ButtonHintShowingCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x10146CB0
			ButtonHintShowingCondition::~ButtonHintShowingCondition()
			{
			}

			// FUNCTION: ENGINE 0x10147510
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ButtonHintShowingCondition::RegisterProperties()
			{
				if (gButtonHintShowingConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<ButtonHintShowingCondition>("buttonHint", &ButtonHintShowingCondition::SetButtonHint);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gButtonHintShowingConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10147220
			fight::ConditionFactory* CreateButtonHintShowingConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ButtonHintShowingCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10147390
			void RegisterButtonHintShowingConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ButtonHintShowingCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gEnableButtonHintsTrackProperties;  // 0x11254314

			// FUNCTION: ENGINE 0x10146A60
			bool EnableButtonHintsTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10146A80
			bool EnableButtonHintsTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10146B50
			fight::Property* EnableButtonHintsTrack::GetProperty(int index)
			{
				return gEnableButtonHintsTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10146B70
			void EnableButtonHintsTrack::ClearProperties()
			{
				fight::FreePropertyList(&gEnableButtonHintsTrackProperties);
			}

			// FUNCTION: ENGINE 0x10146B80
			EnableButtonHintsTrack::EnableButtonHintsTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10146BB0
			float EnableButtonHintsTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10146BC0
			float EnableButtonHintsTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10146BD0
			EnableButtonHintsTrack::~EnableButtonHintsTrack()
			{
			}

			// FUNCTION: ENGINE 0x101472B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EnableButtonHintsTrack::RegisterProperties()
			{
				if (gEnableButtonHintsTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<EnableButtonHintsTrack>("timeBegin", &EnableButtonHintsTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<EnableButtonHintsTrack>("timeEnd", &EnableButtonHintsTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gEnableButtonHintsTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10147250
			fight::TrackFactory* CreateEnableButtonHintsTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<EnableButtonHintsTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101473C0
			void RegisterEnableButtonHintsTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<EnableButtonHintsTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gButtonHintShowTrackProperties;  // 0x11254318

			// FUNCTION: ENGINE 0x10146AA0
			bool ButtonHintShowTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10146AC0
			bool ButtonHintShowTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10146AE0
			bool ButtonHintShowTrack::SetButton(int newValue)
			{
				button = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10146AF0
			bool ButtonHintShowTrack::SetPressType(int newValue)
			{
				pressType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10146C10
			bool ButtonHintShowTrack::SetDisplayMessage(const char* newValue)
			{
				displayMessage = fight::ReplaceString(displayMessage, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x10146C60
			bool ButtonHintShowTrack::SetScenarioMessage(const fight::Name& newValue)
			{
				scenarioMessage = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10146B00
			bool ButtonHintShowTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10146B10
			bool ButtonHintShowTrack::SetPersistent(bool newValue)
			{
				persistent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10146BE0
			fight::Property* ButtonHintShowTrack::GetProperty(int index)
			{
				return gButtonHintShowTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10146C00
			void ButtonHintShowTrack::ClearProperties()
			{
				fight::FreePropertyList(&gButtonHintShowTrackProperties);
			}

			// FUNCTION: ENGINE 0x10146CF0
			ButtonHintShowTrack::ButtonHintShowTrack() : displayMessage(0), timeBegin(0.0f), timeEnd(-1.0f), button(0), pressType(0), priority(0), persistent(true)
			{
			}

			// FUNCTION: ENGINE 0x10146D50
			float ButtonHintShowTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10146D60
			float ButtonHintShowTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10146D70
			ButtonHintShowTrack::~ButtonHintShowTrack()
			{
				delete[] displayMessage;
			}

			// FUNCTION: ENGINE 0x101475B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ButtonHintShowTrack::RegisterProperties()
			{
				if (gButtonHintShowTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ButtonHintShowTrack>("timeBegin", &ButtonHintShowTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ButtonHintShowTrack>("timeEnd", &ButtonHintShowTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnum<ButtonHintShowTrack>("button", &ButtonHintShowTrack::GetButtonEntry, &ButtonHintShowTrack::GetButtonCount, &ButtonHintShowTrack::SetButton);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<ButtonHintShowTrack>("pressType", gButtonHintShowTrackPressTypeTable, gButtonHintShowTrackPressTypeCount, &ButtonHintShowTrack::SetPressType);
					properties[3] = property;
					property = new fight::PropertyString<ButtonHintShowTrack>("displayMessage", &ButtonHintShowTrack::SetDisplayMessage);
					properties[4] = property;
					property = new fight::PropertyName<ButtonHintShowTrack>("scenarioMessage", &ButtonHintShowTrack::SetScenarioMessage);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<ButtonHintShowTrack>("priority", &ButtonHintShowTrack::SetPriority);
					properties[6] = property;
					property = new fight::PropertyBool<ButtonHintShowTrack>("persistent", &ButtonHintShowTrack::SetPersistent);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gButtonHintShowTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10147280
			fight::TrackFactory* CreateButtonHintShowTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ButtonHintShowTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101473F0
			void RegisterButtonHintShowTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ButtonHintShowTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100A0840
			EnableButtonHintsAction::EnableButtonHintsAction(EnableButtonHintsTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x600), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x100A04E0
			EnableButtonHintsAction::~EnableButtonHintsAction()
			{
			}

			// FUNCTION: ENGINE 0x100A0A50
			fight::Action* EnableButtonHintsTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new EnableButtonHintsAction(this, handle);
			}

			// FUNCTION: ENGINE 0x100A05E0
			ButtonHintShowAction::ButtonHintShowAction(ButtonHintShowTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x600), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x100A0490
			ButtonHintShowAction::~ButtonHintShowAction()
			{
			}

			// FUNCTION: ENGINE 0x100A0A00
			fight::Action* ButtonHintShowTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ButtonHintShowAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyName<ButtonHintShowingCondition>;
			template class fight::ConditionFactoryTemplate<ButtonHintShowingCondition>;
			template class fight::ConditionFactoryCasterTemplate<ButtonHintShowingCondition>;
			template class fight::PropertyFloatConstRange<EnableButtonHintsTrack>;
			template class fight::TrackFactoryTemplate<EnableButtonHintsTrack>;
			template class fight::TrackFactoryCasterTemplate<EnableButtonHintsTrack>;
			template class fight::PropertyFloatConstRange<ButtonHintShowTrack>;
			template class fight::PropertyEnum<ButtonHintShowTrack>;
			template class fight::PropertyEnumConstList<ButtonHintShowTrack>;
			template class fight::PropertyString<ButtonHintShowTrack>;
			template class fight::PropertyName<ButtonHintShowTrack>;
			template class fight::PropertyIntConstRange<ButtonHintShowTrack>;
			template class fight::PropertyBool<ButtonHintShowTrack>;
			template class fight::TrackFactoryTemplate<ButtonHintShowTrack>;
			template class fight::TrackFactoryCasterTemplate<ButtonHintShowTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100A0080
// FUNCTION: ENGINE 0x100A00A0
// FUNCTION: ENGINE 0x100A0130
// FUNCTION: ENGINE 0x100A0190
// FUNCTION: ENGINE 0x100A0660
// FUNCTION: ENGINE 0x100A08C0
