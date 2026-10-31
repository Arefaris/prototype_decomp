// The constructors, property setters and property lists of five scenario conditions (the evaluations are in
// scenarioconditions.cpp). The unit runs 0x108FF310 - 0x10900260; it has no assert path, the file name is a guess.
#include "code/engine/scenario/scenarioconditions.h"
#include "code/engine/scenario/scenariolisters.h"

namespace engine
{
	namespace scenario
	{
		fight::EnumEntry gTriggerDirectionTable[2] =
			{
				{ fight::Name("Enter", 0) },
				{ fight::Name("Exit", 0) }
			};
		extern const int gTriggerDirectionCount;

		fight::Property** gScenarioGameObjectAttributeConditionProperties;  // 0x1131B328
		fight::Property** gScenarioGameObjectTouchesTriggerConditionProperties;  // 0x1131B32C
		fight::Property** gScenarioMessageConditionProperties;  // 0x1131B330
		fight::Property** gScenarioPropStateConditionProperties;  // 0x1131B334
		fight::Property** gScenarioStringConditionProperties;  // 0x1131B338

		// FUNCTION: ENGINE 0x108FF310
		bool ScenarioGameObjectAttributeCondition::SetSlot(int newValue)
		{
			slot = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108FF320
		bool ScenarioGameObjectTouchesTriggerCondition::SetType(int newValue)
		{
			type = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108FF330
		bool ScenarioMessageCondition::SetEvent(int newValue)
		{
			event = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108FF340
		fight::Property* ScenarioGameObjectAttributeCondition::GetProperty(int index)
		{
			return gScenarioGameObjectAttributeConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x108FF350
		void ScenarioGameObjectAttributeCondition::ClearProperties()
		{
			fight::FreePropertyList(&gScenarioGameObjectAttributeConditionProperties);
		}

		// FUNCTION: ENGINE 0x108FF360
		bool ScenarioGameObjectAttributeCondition::SetKey(const char* text)
		{
			key = fight::ReplaceString(const_cast<char*>(key), text);
			return true;
		}

		// FUNCTION: ENGINE 0x108FF380
		fight::Property* ScenarioGameObjectTouchesTriggerCondition::GetProperty(int index)
		{
			return gScenarioGameObjectTouchesTriggerConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x108FF390
		void ScenarioGameObjectTouchesTriggerCondition::ClearProperties()
		{
			fight::FreePropertyList(&gScenarioGameObjectTouchesTriggerConditionProperties);
		}

		// FUNCTION: ENGINE 0x108FF3A0
		fight::Property* ScenarioMessageCondition::GetProperty(int index)
		{
			return gScenarioMessageConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x108FF3B0
		void ScenarioMessageCondition::ClearProperties()
		{
			fight::FreePropertyList(&gScenarioMessageConditionProperties);
		}

		// FUNCTION: ENGINE 0x108FF3C0
		ScenarioMessageCondition::ScenarioMessageCondition() : fight::Condition(0), event(0)
		{
		}

		// FUNCTION: ENGINE 0x108FF3E0
		ScenarioMessageCondition::~ScenarioMessageCondition()
		{
		}

		// FUNCTION: ENGINE 0x108FF3F0
		fight::Property* ScenarioPropStateCondition::GetProperty(int index)
		{
			return gScenarioPropStateConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x108FF400
		void ScenarioPropStateCondition::ClearProperties()
		{
			fight::FreePropertyList(&gScenarioPropStateConditionProperties);
		}

		// FUNCTION: ENGINE 0x108FF410
		fight::Property* ScenarioStringCondition::GetProperty(int index)
		{
			return gScenarioStringConditionProperties[index];
		}

		// FUNCTION: ENGINE 0x108FF420
		void ScenarioStringCondition::ClearProperties()
		{
			fight::FreePropertyList(&gScenarioStringConditionProperties);
		}

		// FUNCTION: ENGINE 0x108FF430
		bool ScenarioGameObjectAttributeCondition::SetValue(const fight::Name& newValue)
		{
			value = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108FF450
		bool ScenarioGameObjectTouchesTriggerCondition::SetTrigger(const fight::Name& newValue)
		{
			trigger = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108FF470
		bool ScenarioGameObjectTouchesTriggerCondition::SetObject(const fight::Name& newValue)
		{
			object = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108FF490
		bool ScenarioPropStateCondition::SetState(const fight::Name& newValue)
		{
			state = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108FF4B0
		bool ScenarioStringCondition::SetString(const fight::Name& newValue)
		{
			string = newValue;
			return true;
		}

		// FUNCTION: ENGINE 0x108FF4D0
		ScenarioGameObjectAttributeCondition::ScenarioGameObjectAttributeCondition()
			: fight::Condition(0), key(0), slot(0)
		{
		}

		// FUNCTION: ENGINE 0x108FF500
		ScenarioGameObjectAttributeCondition::~ScenarioGameObjectAttributeCondition()
		{
			delete[] key;
		}

		// FUNCTION: ENGINE 0x108FF520
		ScenarioGameObjectTouchesTriggerCondition::ScenarioGameObjectTouchesTriggerCondition()
			: fight::Condition(0), type(1)
		{
		}

		// FUNCTION: ENGINE 0x108FF550
		ScenarioGameObjectTouchesTriggerCondition::~ScenarioGameObjectTouchesTriggerCondition()
		{
		}

		// FUNCTION: ENGINE 0x108FF580
		ScenarioPropStateCondition::ScenarioPropStateCondition() : fight::Condition(0)
		{
		}

		// FUNCTION: ENGINE 0x108FF5A0
		ScenarioPropStateCondition::~ScenarioPropStateCondition()
		{
		}

		// FUNCTION: ENGINE 0x108FF5B0
		ScenarioStringCondition::ScenarioStringCondition() : fight::Condition(0)
		{
		}

		// FUNCTION: ENGINE 0x108FF5D0
		ScenarioStringCondition::~ScenarioStringCondition()
		{
		}

		// FUNCTION: ENGINE 0x108FFAA0
		fight::ConditionFactory* CreateScenarioGameObjectAttributeConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioGameObjectAttributeCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108FFAC0
		fight::ConditionFactory* CreateScenarioGameObjectTouchesTriggerConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioGameObjectTouchesTriggerCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108FFAE0
		fight::ConditionFactory* CreateScenarioMessageConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioMessageCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108FFB00
		fight::ConditionFactory* CreateScenarioPropStateConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioPropStateCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108FFB20
		fight::ConditionFactory* CreateScenarioStringConditionFactory(const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioStringCondition> caster;
			return fight::FindConditionFactory(name, &caster);
		}

		// FUNCTION: ENGINE 0x108FFB40
		// EQUIVALENT: shrink-wrap
		void ScenarioGameObjectAttributeCondition::RegisterProperties()
		{
			if (gScenarioGameObjectAttributeConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumListObject<ScenarioGameObjectAttributeCondition>("gameobjectslot",
					&gAffiliateLister, &ScenarioGameObjectAttributeCondition::SetSlot);
				properties[0] = property;
				property = new fight::PropertyString<ScenarioGameObjectAttributeCondition>("attributeKey",
					&ScenarioGameObjectAttributeCondition::SetKey);
				properties[1] = property;
				property = new fight::PropertyName<ScenarioGameObjectAttributeCondition>("value",
					&ScenarioGameObjectAttributeCondition::SetValue);
				properties[2] = property;
				fight::RegisterPropertyList(properties, &gScenarioGameObjectAttributeConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x108FFC30
		// EQUIVALENT: shrink-wrap
		void ScenarioGameObjectTouchesTriggerCondition::RegisterProperties()
		{
			if (gScenarioGameObjectTouchesTriggerConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyName<ScenarioGameObjectTouchesTriggerCondition>("triggerName",
					&ScenarioGameObjectTouchesTriggerCondition::SetTrigger);
				properties[0] = property;
				property = new fight::PropertyName<ScenarioGameObjectTouchesTriggerCondition>("gameObjectName",
					&ScenarioGameObjectTouchesTriggerCondition::SetObject);
				properties[1] = property;
				property = new fight::PropertyEnumConstList<ScenarioGameObjectTouchesTriggerCondition>("direction",
					gTriggerDirectionTable, gTriggerDirectionCount, &ScenarioGameObjectTouchesTriggerCondition::SetType);
				properties[2] = property;
				fight::RegisterPropertyList(properties, &gScenarioGameObjectTouchesTriggerConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x108FFD20
		// EQUIVALENT: shrink-wrap
		void ScenarioMessageCondition::RegisterProperties()
		{
			if (gScenarioMessageConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyEnumListObject<ScenarioMessageCondition>("type",
					&gScenarioMessageLister, &ScenarioMessageCondition::SetEvent);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gScenarioMessageConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x108FFDA0
		// EQUIVALENT: shrink-wrap
		void ScenarioPropStateCondition::RegisterProperties()
		{
			if (gScenarioPropStateConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyName<ScenarioPropStateCondition>("state",
					&ScenarioPropStateCondition::SetState);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gScenarioPropStateConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x108FFE20
		// EQUIVALENT: shrink-wrap
		void ScenarioStringCondition::RegisterProperties()
		{
			if (gScenarioStringConditionProperties == 0)
			{
				fight::Property* properties[256] = { 0 };
				fight::Property* property = 0;
				property = new fight::PropertyName<ScenarioStringCondition>("string",
					&ScenarioStringCondition::SetString);
				properties[0] = property;
				fight::RegisterPropertyList(properties, &gScenarioStringConditionProperties);
			}
		}

		// FUNCTION: ENGINE 0x108FFEA0
		void RegisterScenarioGameObjectAttributeConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioGameObjectAttributeCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		// FUNCTION: ENGINE 0x108FFED0
		void RegisterScenarioGameObjectTouchesTriggerConditionFactory(fight::TrackRegistry* registry,
			const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioGameObjectTouchesTriggerCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		// FUNCTION: ENGINE 0x108FFF00
		void RegisterScenarioMessageConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioMessageCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		// FUNCTION: ENGINE 0x108FFF30
		void RegisterScenarioPropStateConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioPropStateCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		// FUNCTION: ENGINE 0x108FFF60
		void RegisterScenarioStringConditionFactory(fight::TrackRegistry* registry, const char* name)
		{
			fight::ConditionFactoryCasterTemplate<ScenarioStringCondition> caster;
			registry->AddFactory(fight::FindConditionFactory(name, &caster));
		}

		template class fight::ConditionFactoryCasterTemplate<ScenarioGameObjectAttributeCondition>;
		template class fight::ConditionFactoryCasterTemplate<ScenarioGameObjectTouchesTriggerCondition>;
		template class fight::ConditionFactoryCasterTemplate<ScenarioMessageCondition>;
		template class fight::ConditionFactoryCasterTemplate<ScenarioPropStateCondition>;
		template class fight::ConditionFactoryCasterTemplate<ScenarioStringCondition>;
		template class fight::PropertyEnumListObject<ScenarioGameObjectAttributeCondition>;
		template class fight::PropertyString<ScenarioGameObjectAttributeCondition>;
		template class fight::PropertyName<ScenarioGameObjectAttributeCondition>;
		template class fight::PropertyName<ScenarioGameObjectTouchesTriggerCondition>;
		template class fight::PropertyEnumConstList<ScenarioGameObjectTouchesTriggerCondition>;
		template class fight::PropertyEnumListObject<ScenarioMessageCondition>;
		template class fight::PropertyName<ScenarioPropStateCondition>;
		template class fight::PropertyName<ScenarioStringCondition>;
		template class fight::ConditionFactoryTemplate<ScenarioGameObjectAttributeCondition>;
		template class fight::ConditionFactoryTemplate<ScenarioGameObjectTouchesTriggerCondition>;
		template class fight::ConditionFactoryTemplate<ScenarioMessageCondition>;
		template class fight::ConditionFactoryTemplate<ScenarioPropStateCondition>;
		template class fight::ConditionFactoryTemplate<ScenarioStringCondition>;
	}
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D78380
// FUNCTION: ENGINE 0x10D8AF50


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108FF560
// FUNCTION: ENGINE 0x108FF5E0
// FUNCTION: ENGINE 0x108FF5F0
// FUNCTION: ENGINE 0x108FF620
// FUNCTION: ENGINE 0x108FF630
// FUNCTION: ENGINE 0x108FF660
// FUNCTION: ENGINE 0x108FF670
// FUNCTION: ENGINE 0x108FF6A0
// FUNCTION: ENGINE 0x108FF6B0
// FUNCTION: ENGINE 0x108FF6E0
// FUNCTION: ENGINE 0x108FF6F0
// FUNCTION: ENGINE 0x108FF720
// FUNCTION: ENGINE 0x108FF740
// FUNCTION: ENGINE 0x108FF760
// FUNCTION: ENGINE 0x108FF780
// FUNCTION: ENGINE 0x108FF7A0
// FUNCTION: ENGINE 0x108FF7D0
// FUNCTION: ENGINE 0x108FF7E0
// FUNCTION: ENGINE 0x108FF800
// FUNCTION: ENGINE 0x108FF820
// FUNCTION: ENGINE 0x108FF830
// FUNCTION: ENGINE 0x108FF850
// FUNCTION: ENGINE 0x108FF870
// FUNCTION: ENGINE 0x108FF880
// FUNCTION: ENGINE 0x108FF8A0
// FUNCTION: ENGINE 0x108FF8C0
// FUNCTION: ENGINE 0x108FF8E0
// FUNCTION: ENGINE 0x108FF900
// FUNCTION: ENGINE 0x108FF930
// FUNCTION: ENGINE 0x108FF940
// FUNCTION: ENGINE 0x108FF960
// FUNCTION: ENGINE 0x108FF980
// FUNCTION: ENGINE 0x108FF990
// FUNCTION: ENGINE 0x108FF9C0
// FUNCTION: ENGINE 0x108FF9D0
// FUNCTION: ENGINE 0x108FF9F0
// FUNCTION: ENGINE 0x108FFA10
// FUNCTION: ENGINE 0x108FFA20
// FUNCTION: ENGINE 0x108FFA40
// FUNCTION: ENGINE 0x108FFA60
// FUNCTION: ENGINE 0x108FFA80
// FUNCTION: ENGINE 0x108FFF90
// FUNCTION: ENGINE 0x108FFFC0
// FUNCTION: ENGINE 0x108FFFE0
// FUNCTION: ENGINE 0x10900010
// FUNCTION: ENGINE 0x10900030
// FUNCTION: ENGINE 0x10900060
// FUNCTION: ENGINE 0x10900080
// FUNCTION: ENGINE 0x109000B0
// FUNCTION: ENGINE 0x109000D0
// FUNCTION: ENGINE 0x10900100
// FUNCTION: ENGINE 0x10900120
// FUNCTION: ENGINE 0x10900160
// FUNCTION: ENGINE 0x109001A0
// FUNCTION: ENGINE 0x109001E0
// FUNCTION: ENGINE 0x10900220
