// The scenario's fight conditions (see scenarioconditions.h): 0x108C14A0 - 0x108C2770.
#include "code/engine/scenario/scenarioconditions.h"

#include "code/core/strings.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/engine/scenario/scenariolisters.h"
#include "code/engine/scenario/scriptowner.h"
#include "code/engine/scenariomessage.h"
#include <new>
#include <string.h>

namespace engine
{
	namespace scenario
	{
		extern fight::EnumEntry gScriptAttributeTypeTable[];
		extern const int gScriptAttributeTypeCount;

		fight::Property** gScenarioGameObjectConditionProperties;  // 0x113187A8
		fight::Property** gScenarioScriptAttributeConditionProperties;  // 0x113187AC
		fight::Property** gHasTagConditionProperties;  // 0x113187B0

		// ---- the accessors the properties use ---------------------------------------------------------------------

		// FUNCTION: ENGINE 0x108C14A0
		int ScenarioGameObjectCondition::GetSlot() const
		{
			return slot;
		}

		// FUNCTION: ENGINE 0x108C14B0
		bool ScenarioGameObjectCondition::SetSlot(int newValue)
		{
			slot = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108C14C0
		const fight::Name& ScenarioGameObjectCondition::GetName() const
		{
			return name;
		}

		// FUNCTION: ENGINE 0x108C14D0
		int ScenarioScriptAttributeCondition::GetSlot() const
		{
			return slot;
		}

		// FUNCTION: ENGINE 0x108C14E0
		bool ScenarioScriptAttributeCondition::SetSlot(int newValue)
		{
			slot = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108C14F0
		bool ScenarioScriptAttributeCondition::SetType(int newValue)
		{
			value.SetType(newValue);
			return true;
		}

		// FUNCTION: ENGINE 0x108C1510
		const char* ScenarioScriptAttributeCondition::GetAttributeKey() const
		{
			return attributeKey;
		}

		// FUNCTION: ENGINE 0x108C1520
		bool ScenarioScriptAttributeCondition::SetValue(const char* text)
		{
			value.SetFromString(text);
			return true;
		}

		// FUNCTION: ENGINE 0x108C1540
		int HasTagCondition::GetSlot() const
		{
			return slot;
		}

		// FUNCTION: ENGINE 0x108C1550
		bool HasTagCondition::SetSlot(int newValue)
		{
			slot = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108C1560
		const char* HasTagCondition::GetTag() const
		{
			return tag;
		}

		// FUNCTION: ENGINE 0x108C15B0
		int ScenarioGameObjectAttributeCondition::GetSlot() const
		{
			return slot;
		}

		// FUNCTION: ENGINE 0x108C15C0
		const char* ScenarioGameObjectAttributeCondition::GetKey() const
		{
			return key;
		}

		// FUNCTION: ENGINE 0x108C15D0
		const fight::Name& ScenarioGameObjectAttributeCondition::GetValue() const
		{
			return value;
		}

		// FUNCTION: ENGINE 0x108C15E0
		const fight::Name& ScenarioGameObjectTouchesTriggerCondition::GetTrigger() const
		{
			return trigger;
		}

		// FUNCTION: ENGINE 0x108C15F0
		const fight::Name& ScenarioGameObjectTouchesTriggerCondition::GetObject() const
		{
			return object;
		}

		// FUNCTION: ENGINE 0x108C1600
		int ScenarioGameObjectTouchesTriggerCondition::GetType() const
		{
			return type;
		}

		// ---- the property lists --------------------------------------------------------------------------------------

		// FUNCTION: ENGINE 0x108C1610
		fight::Property* ScenarioGameObjectCondition::GetProperty(int index)
		{
			return gScenarioGameObjectConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x108C1620
		void ScenarioGameObjectCondition::ClearProperties()
		{
			fight::FreePropertyList(&gScenarioGameObjectConditionProperties);
		}

		// FUNCTION: ENGINE 0x108C1680
		fight::Property* ScenarioScriptAttributeCondition::GetProperty(int index)
		{
			return gScenarioScriptAttributeConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x108C1690
		void ScenarioScriptAttributeCondition::ClearProperties()
		{
			fight::FreePropertyList(&gScenarioScriptAttributeConditionProperties);
		}

		// FUNCTION: ENGINE 0x108C16A0
		fight::Property* HasTagCondition::GetProperty(int index)
		{
			return gHasTagConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x108C16B0
		void HasTagCondition::ClearProperties()
		{
			fight::FreePropertyList(&gHasTagConditionProperties);
		}

		// ---- constructors, destructors and the text setters ------------------------------------------------------

		// FUNCTION: ENGINE 0x108C16C0
		ScenarioScriptAttributeCondition::ScenarioScriptAttributeCondition()
			: fight::Condition(0), slot(0), attributeKey(0)
		{
		}

		// FUNCTION: ENGINE 0x108C16F0
		ScenarioScriptAttributeCondition::~ScenarioScriptAttributeCondition()
		{
			delete[] attributeKey;
		}

		// FUNCTION: ENGINE 0x108C1720
		// EQUIVALENT: register allocation (the zero lives in ecx, the engine's edx, and its loop tests against it) and the order of the esi restore, 74.6 %
		bool ScenarioScriptAttributeCondition::SetAttributeKey(const char* text)
		{
			char* old = attributeKey;
			if (text == 0)
			{
				attributeKey = 0;
				delete[] old;
				return true;
			}
			const char* end = text;
			const char* start = text + 1;
			do
			{
			}
			while (*end++ != 0);
			int length = end - start;
			if (length > 0)
			{
				int size = length + 1;
				attributeKey = new char[size];
				int count;
				core::StrNCpyCount(attributeKey, text, size, &count);
			}
			else
			{
				attributeKey = 0;
			}
			delete[] old;
			return true;
		}

		// FUNCTION: ENGINE 0x108C17B0
		HasTagCondition::HasTagCondition() : fight::Condition(0), slot(0), tag(0)
		{
		}

		// FUNCTION: ENGINE 0x108C17E0
		HasTagCondition::~HasTagCondition()
		{
			delete[] tag;
		}

		// FUNCTION: ENGINE 0x108C1800
		// EQUIVALENT: register allocation (the zero lives in ecx, the engine's edx, and its loop tests against it) and the order of the esi restore, 74.6 %
		bool HasTagCondition::SetTag(const char* text)
		{
			char* old = tag;
			if (text == 0)
			{
				tag = 0;
				delete[] old;
				return true;
			}
			const char* end = text;
			const char* start = text + 1;
			do
			{
			}
			while (*end++ != 0);
			int length = end - start;
			if (length > 0)
			{
				int size = length + 1;
				tag = new char[size];
				int count;
				core::StrNCpyCount(tag, text, size, &count);
			}
			else
			{
				tag = 0;
			}
			delete[] old;
			return true;
		}

		// FUNCTION: ENGINE 0x108C1890
		bool ScenarioGameObjectCondition::SetName(const fight::Name& newValue)
		{
			name = newValue;
			handle.index = 0xFFFF;
			handle.serial = 0;
			return true;
		}

		// FUNCTION: ENGINE 0x108C18C0
		ScenarioGameObjectCondition::ScenarioGameObjectCondition() : fight::Condition(0), slot(0)
		{
		}

		// FUNCTION: ENGINE 0x108C18F0
		ScenarioGameObjectCondition::~ScenarioGameObjectCondition()
		{
		}

		// ---- the evaluations ---------------------------------------------------------------------------------------

		// Whether the script event is a node of its own
		static inline bool IsNodeOwner(const ScriptOwner* owner)
		{
			return owner != 0 && (unsigned int)owner->value - 1 <= 0xFFFE;
		}

		// The test of the game object table that the engine expands where it asks the handle of a message
		static __forceinline bool IsHandleValid(const GameObjectHandle& handle)
		{
			return handle.index != 0xFFFF && GetGameObjectEntries()[handle.index].serial == handle.serial
				&& GetGameObjectEntries()[handle.index].object != 0;
		}

		// The handles are compared as the one word they are
		static inline bool SameHandle(const GameObjectHandle& first, const GameObjectHandle& second)
		{
			return *(const unsigned int*)&first == *(const unsigned int*)&second;
		}

		// FUNCTION: ENGINE 0x108C1630
		// EQUIVALENT: the engine adds -1 where ours subtracts 1 (the same range test) and issues the lister's argument load after the move of the part, 84.8 %
		bool ScenarioMessageCondition::Evaluate(int a, int b, int c, int d)
		{
			ScriptOwner* owner = (ScriptOwner*)c;
			if (!IsNodeOwner(owner))
			{
				return false;
			}
			ScenarioMessage* part = owner->GetPart();
			bool result = (unsigned short)part->id == gScenarioMessageLister.GetValue(event);
			return result;
		}

		// FUNCTION: ENGINE 0x108C1900
		// EQUIVALENT: the engine adds -1 where ours subtracts 1 (the same range test), 96.6 %
		bool ScenarioStringCondition::Evaluate(int a, int b, int c, int d)
		{
			ScriptOwner* owner = (ScriptOwner*)c;
			if (IsNodeOwner(owner))
			{
				ScenarioMessage* part = owner->GetPart();
				if (part->id == 2)
				{
					return string == static_cast<StringMessage*>(part)->string;
				}
			}
			return false;
		}

		// FUNCTION: ENGINE 0x108C1940
		// EQUIVALENT: the engine adds -1 where ours subtracts 1 (the same range test), 96.6 %
		bool ScenarioPropStateCondition::Evaluate(int a, int b, int c, int d)
		{
			ScriptOwner* owner = (ScriptOwner*)c;
			if (IsNodeOwner(owner))
			{
				ScenarioMessage* part = owner->GetPart();
				if (part->id == 6)
				{
					return static_cast<ObjectStateChangedMessage*>(part)->newState == state;
				}
			}
			return false;
		}

		// FUNCTION: ENGINE 0x108C1AA0
		// EQUIVALENT: the false returns are laid out at the end, the engine's right after each test; the engine adds -1 where ours subtracts 1; the same table test and the same calls, 23.5 %
		bool ScenarioGameObjectCondition::Evaluate(int a, int b, int c, int d)
		{
			ScriptOwner* owner = (ScriptOwner*)c;
			if (owner == 0 || (unsigned int)owner->value - 1 > 0xFFFE)
			{
				return false;
			}
			ScenarioMessage* part = owner->GetPart();
			int index = gAffiliateLister.GetValue(slot);
			GameObjectHandle messageHandle = part->GetHandle(index);
			if (!IsHandleValid(messageHandle))
			{
				return false;
			}
			if (!handle.IsValid())
			{
				handle = FindGameObject(name, *(const content::ObjectName*)"");
			}
			return SameHandle(handle, messageHandle);
		}

		// FUNCTION: ENGINE 0x108C1B50
		// EQUIVALENT: the engine adds -1 where ours subtracts 1, the lister argument is loaded after the move of the part in the engine, and the table base lives in other registers, 66.5 %
		bool ScenarioGameObjectAttributeCondition::Evaluate(int a, int b, int c, int d)
		{
			ScriptOwner* owner = (ScriptOwner*)c;
			if (!IsNodeOwner(owner))
			{
				return false;
			}
			ScenarioMessage* part = owner->GetPart();
			int index = gAffiliateLister.GetValue(slot);
			GameObjectHandle messageHandle = part->GetHandle(index);
			if (!IsHandleValid(messageHandle))
			{
				return false;
			}
			content::ObjectName attributeName(key, 1);
			BaseAttribute* attribute = messageHandle.Get()->FindAttribute(attributeName);
			if (attribute == 0)
			{
				return false;
			}
			core::Name<core::CaseSensitiveKey>* attributeValue = &static_cast<Attribute<core::Name<core::CaseSensitiveKey> >*>(attribute)->value;
			if (attributeValue == 0)
			{
				return false;
			}
			return *attributeValue == value;
		}

		// FUNCTION: ENGINE 0x108C1C30
		// EQUIVALENT: the engine adds -1 where ours subtracts 1, the lister argument is loaded after the move of the part in the engine, and the table base lives in other registers, 63.0 %
		bool ScenarioScriptAttributeCondition::Evaluate(int a, int b, int c, int d)
		{
			ScriptOwner* owner = (ScriptOwner*)c;
			if (!IsNodeOwner(owner))
			{
				return false;
			}
			ScenarioMessage* part = owner->GetPart();
			int index = gAffiliateLister.GetValue(slot);
			GameObjectHandle messageHandle = part->GetHandle(index);
			if (!IsHandleValid(messageHandle))
			{
				return false;
			}
			content::ObjectName attributeName(attributeKey, 1);
			BaseAttribute* attribute = messageHandle.Get()->FindAttribute(attributeName);
			if (attribute == 0)
			{
				return false;
			}
			AttributeValue* attributeValue = &static_cast<Attribute<AttributeValue>*>(attribute)->value;
			if (attributeValue == 0)
			{
				return false;
			}
			return value.ToString() == attributeValue->ToString();
		}

		// FUNCTION: ENGINE 0x108C1D20
		// EQUIVALENT: the engine adds -1 where ours subtracts 1, the lister argument is loaded after the move of the part in the engine, and the table base lives in other registers, 59.2 %
		bool HasTagCondition::Evaluate(int a, int b, int c, int d)
		{
			ScriptOwner* owner = (ScriptOwner*)c;
			if (!IsNodeOwner(owner))
			{
				return false;
			}
			ScenarioMessage* part = owner->GetPart();
			int index = gAffiliateLister.GetValue(slot);
			GameObjectHandle messageHandle = part->GetHandle(index);
			if (!IsHandleValid(messageHandle))
			{
				return false;
			}
			fight::Name tagName(tag, 1);
			return messageHandle.RouterAdd(*static_cast<const MessageListeners*>(&tagName));
		}

		// FUNCTION: ENGINE 0x108C1DC0
		// EQUIVALENT: the engine adds -1 where ours subtracts 1, the table base and the pointers to the handles use other registers, 55.8 %
		bool ScenarioGameObjectTouchesTriggerCondition::Evaluate(int a, int b, int c, int d)
		{
			ScriptOwner* owner = (ScriptOwner*)c;
			if (!IsNodeOwner(owner))
			{
				return false;
			}
			ScenarioMessage* part = owner->GetPart();
			unsigned short id = part->id;
			if (id == 3 || id == 4)
			{
				bool matches;
				switch (type)
				{
					case 0:
						matches = id == 3;
						break;
					case 1:
						matches = id == 4;
						break;
					default:
						return false;
				}
				if (matches)
				{
					GameObjectHandle second = part->GetHandle(1);
					GameObjectHandle first = part->GetHandle(0);
					if (IsHandleValid(second) && IsHandleValid(first))
					{
						if (SameHandle(FindGameObject(object, *(const content::ObjectName*)""), second))
						{
							if (SameHandle(FindGameObject(trigger, *(const content::ObjectName*)""), first))
							{
								return true;
							}
						}
					}
				}
			}
			return false;
		}

		// ---- the factories and the property lists -------------------------------------------------------------------

		// FUNCTION: ENGINE 0x108C1F70
		fight::ConditionFactory* CreateScenarioGameObjectConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioGameObjectCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108C21E0
		fight::ConditionFactory* CreateScenarioScriptAttributeConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioScriptAttributeCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108C2200
		fight::ConditionFactory* CreateHasTagConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<HasTagCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108C2220
		void RegisterScenarioGameObjectConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioGameObjectCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		// FUNCTION: ENGINE 0x108C2430
		void RegisterScenarioScriptAttributeConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioScriptAttributeCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		// FUNCTION: ENGINE 0x108C2460
		void RegisterHasTagConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<HasTagCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		// FUNCTION: ENGINE 0x108C2250
		// EQUIVALENT: shrink-wrap
		void ScenarioScriptAttributeCondition::RegisterProperties()
		{
			if (gScenarioScriptAttributeConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumListObject<ScenarioScriptAttributeCondition>("gameobjectslot",
					&gAffiliateLister, &ScenarioScriptAttributeCondition::SetSlot);
				properties[0] = property;
				property = new fight::PropertyEnumConstList<ScenarioScriptAttributeCondition>("type",
					gScriptAttributeTypeTable, gScriptAttributeTypeCount, &ScenarioScriptAttributeCondition::SetType);
				properties[1] = property;
				property = new fight::PropertyString<ScenarioScriptAttributeCondition>("attributekey",
					&ScenarioScriptAttributeCondition::SetAttributeKey);
				properties[2] = property;
				property = new fight::PropertyString<ScenarioScriptAttributeCondition>("value",
					&ScenarioScriptAttributeCondition::SetValue);
				properties[3] = property;
				fight::RegisterPropertyList(properties, &gScenarioScriptAttributeConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x108C2380
		// EQUIVALENT: shrink-wrap, 97.2 %
		void HasTagCondition::RegisterProperties()
		{
			if (gHasTagConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumListObject<HasTagCondition>("affiliate", &gAffiliateLister,
					&HasTagCondition::SetSlot);
				properties[0] = property;
				property = new fight::PropertyString<HasTagCondition>("tag", &HasTagCondition::SetTag);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gHasTagConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x108C25E0
		// EQUIVALENT: shrink-wrap, 97.2 %
		void ScenarioGameObjectCondition::RegisterProperties()
		{
			if (gScenarioGameObjectConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumListObject<ScenarioGameObjectCondition>("gameobjectslot",
					&gAffiliateLister, &ScenarioGameObjectCondition::SetSlot);
				properties[0] = property;
				property = new fight::PropertyName<ScenarioGameObjectCondition>("gameobjectname",
					&ScenarioGameObjectCondition::SetName);
				properties[1] = property;
				fight::RegisterPropertyList(properties, &gScenarioGameObjectConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x108C2570
		void RegisterScenarioConditionFactories(fight::TrackRegistry* registry)
		{
			RegisterScenarioMessageConditionFactory(registry, "event");
			RegisterScenarioGameObjectConditionFactory(registry, "gameObject");
			RegisterScenarioGameObjectAttributeConditionFactory(registry, "gameObjectAttribute");
			RegisterScenarioScriptAttributeConditionFactory(registry, "gameObjectScriptAttribute");
			RegisterScenarioStringConditionFactory(registry, "event_String");
			RegisterScenarioPropStateConditionFactory(registry, "prop_State");
			RegisterHasTagConditionFactory(registry, "hasTag");
			RegisterScenarioGameObjectTouchesTriggerConditionFactory(registry, "gameObjectTriggerTouch");
		}

		// ---- the property classes, factories and registrations ---------------------------------------------------

		template class fight::PropertyEnumListObject<ScenarioGameObjectCondition>;
		template class fight::PropertyEnumListObject<ScenarioScriptAttributeCondition>;
		template class fight::PropertyEnumConstList<ScenarioScriptAttributeCondition>;
		template class fight::PropertyString<ScenarioScriptAttributeCondition>;
		template class fight::PropertyEnumListObject<HasTagCondition>;
		template class fight::PropertyString<HasTagCondition>;
		template class fight::PropertyName<ScenarioGameObjectCondition>;
		template class fight::ConditionFactoryTemplate<ScenarioGameObjectCondition>;
		template class fight::ConditionFactoryTemplate<ScenarioScriptAttributeCondition>;
		template class fight::ConditionFactoryTemplate<HasTagCondition>;
		template class fight::ConditionFactoryCasterTemplate<ScenarioGameObjectCondition>;
		template class fight::ConditionFactoryCasterTemplate<ScenarioScriptAttributeCondition>;
		template class fight::ConditionFactoryCasterTemplate<HasTagCondition>;

		// The template members this unit instantiates (the property classes, factories and casters of the three
		// classes), in address order:
		// FUNCTION: ENGINE 0x108C19C0 @ ConditionFactoryCasterTemplate<ScenarioGameObjectCondition>::ConditionFactoryCasterTemplate
		// FUNCTION: ENGINE 0x108C19D0 @ ConditionFactoryCasterTemplate<ScenarioGameObjectCondition>::IsType
		// FUNCTION: ENGINE 0x108C1A00 @ ConditionFactoryCasterTemplate<ScenarioScriptAttributeCondition>::ConditionFactoryCasterTemplate
		// FUNCTION: ENGINE 0x108C1A10 @ ConditionFactoryCasterTemplate<ScenarioScriptAttributeCondition>::IsType
		// FUNCTION: ENGINE 0x108C1A40 @ ConditionFactoryCasterTemplate<HasTagCondition>::ConditionFactoryCasterTemplate
		// FUNCTION: ENGINE 0x108C1A50 @ ConditionFactoryCasterTemplate<HasTagCondition>::IsType
		// FUNCTION: ENGINE 0x108C1EE0 @ PropertyEnumListObject<ScenarioGameObjectCondition>::PropertyEnumListObject
		// FUNCTION: ENGINE 0x108C1F10 @ PropertyEnumListObject<ScenarioGameObjectCondition>::GetCount
		// FUNCTION: ENGINE 0x108C1F20 @ PropertyEnumListObject<ScenarioGameObjectCondition>::GetEntry
		// FUNCTION: ENGINE 0x108C1F40 @ PropertyEnumListObject<ScenarioGameObjectCondition>::Set
		// FUNCTION: ENGINE 0x108C1F60 @ PropertyEnumListObject<ScenarioGameObjectCondition>::IsNull
		// FUNCTION: ENGINE 0x108C1F90 @ PropertyEnumListObject<ScenarioScriptAttributeCondition>::PropertyEnumListObject
		// FUNCTION: ENGINE 0x108C1FC0 @ PropertyEnumListObject<ScenarioScriptAttributeCondition>::GetCount
		// FUNCTION: ENGINE 0x108C1FD0 @ PropertyEnumListObject<ScenarioScriptAttributeCondition>::GetEntry
		// FUNCTION: ENGINE 0x108C1FF0 @ PropertyEnumListObject<ScenarioScriptAttributeCondition>::Set
		// FUNCTION: ENGINE 0x108C2010 @ PropertyEnumListObject<ScenarioScriptAttributeCondition>::IsNull
		// FUNCTION: ENGINE 0x108C2020 @ PropertyEnumConstList<ScenarioScriptAttributeCondition>::PropertyEnumConstList
		// FUNCTION: ENGINE 0x108C2050 @ PropertyEnumConstList<ScenarioScriptAttributeCondition>::GetCount
		// FUNCTION: ENGINE 0x108C2060 @ PropertyEnumConstList<ScenarioScriptAttributeCondition>::GetEntry
		// FUNCTION: ENGINE 0x108C2080 @ PropertyEnumConstList<ScenarioScriptAttributeCondition>::Set
		// FUNCTION: ENGINE 0x108C20A0 @ PropertyEnumConstList<ScenarioScriptAttributeCondition>::IsNull
		// FUNCTION: ENGINE 0x108C20B0 @ PropertyString<ScenarioScriptAttributeCondition>::PropertyString
		// FUNCTION: ENGINE 0x108C20D0 @ PropertyString<ScenarioScriptAttributeCondition>::Set
		// FUNCTION: ENGINE 0x108C20F0 @ PropertyString<ScenarioScriptAttributeCondition>::IsNull
		// FUNCTION: ENGINE 0x108C2100 @ PropertyEnumListObject<HasTagCondition>::PropertyEnumListObject
		// FUNCTION: ENGINE 0x108C2130 @ PropertyEnumListObject<HasTagCondition>::GetCount
		// FUNCTION: ENGINE 0x108C2140 @ PropertyEnumListObject<HasTagCondition>::GetEntry
		// FUNCTION: ENGINE 0x108C2160 @ PropertyEnumListObject<HasTagCondition>::Set
		// FUNCTION: ENGINE 0x108C2180 @ PropertyEnumListObject<HasTagCondition>::IsNull
		// FUNCTION: ENGINE 0x108C2190 @ PropertyString<HasTagCondition>::PropertyString
		// FUNCTION: ENGINE 0x108C21B0 @ PropertyString<HasTagCondition>::Set
		// FUNCTION: ENGINE 0x108C21D0 @ PropertyString<HasTagCondition>::IsNull
		// FUNCTION: ENGINE 0x108C2490 @ PropertyName<ScenarioGameObjectCondition>::PropertyName
		// FUNCTION: ENGINE 0x108C24B0 @ PropertyName<ScenarioGameObjectCondition>::Set
		// FUNCTION: ENGINE 0x108C24D0 @ ConditionFactoryTemplate<ScenarioScriptAttributeCondition>::ConditionFactoryTemplate
		// FUNCTION: ENGINE 0x108C2500 @ ConditionFactoryTemplate<ScenarioScriptAttributeCondition>::CreateCondition
		// FUNCTION: ENGINE 0x108C2520 @ ConditionFactoryTemplate<HasTagCondition>::ConditionFactoryTemplate
		// FUNCTION: ENGINE 0x108C2550 @ ConditionFactoryTemplate<HasTagCondition>::CreateCondition
		// FUNCTION: ENGINE 0x108C2690 @ ConditionFactoryCasterTemplate<ScenarioScriptAttributeCondition>::CreateFactory
		// FUNCTION: ENGINE 0x108C26D0 @ ConditionFactoryCasterTemplate<HasTagCondition>::CreateFactory
		// FUNCTION: ENGINE 0x108C2710 @ ConditionFactoryTemplate<ScenarioGameObjectCondition>::ConditionFactoryTemplate
		// FUNCTION: ENGINE 0x108C2740 @ ConditionFactoryTemplate<ScenarioGameObjectCondition>::CreateCondition
		// FUNCTION: ENGINE 0x108C2760 @ ConditionFactoryCasterTemplate<ScenarioGameObjectCondition>::CreateFactory

	}
}
