// The scenario's fight conditions (RTTI: engine::scenario::*Condition): they ask a script event (a ScriptOwner, the
// node a scenario message was sent to) about the message that caused it. The unit is 0x108C14A0 - 0x108C2570 (no
// assert path; the file name is a guess, the property names come from the reflection strings). The conditions of
// 0x108FF340 - 0x10900260 (their constructors, destructors and properties are another unit) are declared here with
// the members their evaluations in this unit read.
#ifndef ENGINE_SCENARIO_SCENARIOCONDITIONS_H
#define ENGINE_SCENARIO_SCENARIOCONDITIONS_H

#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/genericscriptvalue.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	namespace scenario
	{
		// The value of a scripted game object attribute (the engine calls the class GenericScriptValue)
		typedef GenericScriptValue AttributeValue;

		// RTTI: engine::scenario::ScenarioGameObjectCondition (10 vftable slots, 0x20 bytes): the game object the
		// message names in its handle slot is the object the condition was given
		class ScenarioGameObjectCondition : public fight::Condition
		{
		public:
			// 0x108C18C0
			ScenarioGameObjectCondition();
			virtual ~ScenarioGameObjectCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			int GetSlot() const;
			bool SetSlot(int newValue);
			const fight::Name& GetName() const;
			bool SetName(const fight::Name& newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			int slot;  // +0xC: the handle slot of the message, as the number the affiliate lister holds
			fight::Name name;  // +0x10
			GameObjectHandle handle;  // +0x18: the object of that name, found on the first test
			int unknown1c;
		};

		// RTTI: engine::scenario::ScenarioScriptAttributeCondition (10 vftable slots, 0x1C bytes): an attribute of the
		// object in a handle slot has the value
		class ScenarioScriptAttributeCondition : public fight::Condition
		{
		public:
			// 0x108C16C0
			ScenarioScriptAttributeCondition();
			virtual ~ScenarioScriptAttributeCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			int GetSlot() const;
			bool SetSlot(int newValue);
			bool SetType(int newValue);
			const char* GetAttributeKey() const;
			bool SetAttributeKey(const char* text);
			bool SetValue(const char* text);

			static void RegisterProperties();
			static void ClearProperties();

			int slot;  // +0xC
			char* attributeKey;  // +0x10
			AttributeValue value;  // +0x14
		};

		// RTTI: engine::scenario::HasTagCondition (10 vftable slots, 0x14 bytes): the object in a handle slot has a tag
		class HasTagCondition : public fight::Condition
		{
		public:
			// 0x108C17B0
			HasTagCondition();
			virtual ~HasTagCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			int GetSlot() const;
			bool SetSlot(int newValue);
			const char* GetTag() const;
			bool SetTag(const char* text);

			static void RegisterProperties();
			static void ClearProperties();

			int slot;  // +0xC
			char* tag;  // +0x10
		};

		// RTTI: engine::scenario::ScenarioMessageCondition (10 vftable slots, 0x10 bytes): the event of the message
		// is the one the condition names. Its constructor, destructor and properties are in another unit
		// (0x108FF3A0 ...); only the evaluation is here
		class ScenarioMessageCondition : public fight::Condition
		{
		public:
			ScenarioMessageCondition();
			virtual ~ScenarioMessageCondition();

			// vftable slot 0 (0x108FF3A0)
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual bool Evaluate(int a, int b, int c, int d);

			// The member the property writes (0x108FF330)
			bool SetEvent(int newValue);

			// The property list, built once and freed again (0x108FFD20 / 0x108FF3B0)
			static void RegisterProperties();
			static void ClearProperties();

			int event;  // +0xC: the index in the lister of the message kinds
		};

		// RTTI: engine::scenario::ScenarioGameObjectAttributeCondition (10 vftable slots, 0x20 bytes): the attribute
		// of the object in a handle slot is the name
		class ScenarioGameObjectAttributeCondition : public fight::Condition
		{
		public:
			ScenarioGameObjectAttributeCondition();
			virtual ~ScenarioGameObjectAttributeCondition();

			virtual fight::Property* GetProperty(int index);
			virtual bool Evaluate(int a, int b, int c, int d);

			// The getters the evaluation unit holds (0x108C15B0 ...) and the setters the properties write
			int GetSlot() const;
			const char* GetKey() const;
			const fight::Name& GetValue() const;
			bool SetSlot(int newValue);
			bool SetKey(const char* text);
			bool SetValue(const fight::Name& newValue);

			// The property list, built once and freed again (0x108FFB40 / 0x108FF350)
			static void RegisterProperties();
			static void ClearProperties();

			int unknownc;
			fight::Name value;  // +0x10
			const char* key;  // +0x18: the attribute's name
			int slot;  // +0x1C
		};

		// RTTI: engine::scenario::ScenarioGameObjectTouchesTriggerCondition (10 vftable slots, 0x24 bytes): an
		// enter (type 0) or exit (type 1) trigger message between the two named objects
		class ScenarioGameObjectTouchesTriggerCondition : public fight::Condition
		{
		public:
			ScenarioGameObjectTouchesTriggerCondition();
			virtual ~ScenarioGameObjectTouchesTriggerCondition();

			virtual fight::Property* GetProperty(int index);
			virtual bool Evaluate(int a, int b, int c, int d);

			const fight::Name& GetObject() const;
			const fight::Name& GetTrigger() const;
			int GetType() const;
			bool SetType(int newValue);
			bool SetTrigger(const fight::Name& newValue);
			bool SetObject(const fight::Name& newValue);

			// The property list, built once and freed again (0x108FFC30 / 0x108FF390)
			static void RegisterProperties();
			static void ClearProperties();

			int unknownc;
			fight::Name object;  // +0x10: the object of the message's second handle ("gameObjectName")
			fight::Name trigger;  // +0x18: the object of its first handle ("triggerName")
			int type;  // +0x20
			int unknown24;  // never written: the object is 0x28 bytes
		};

		// RTTI: engine::scenario::ScenarioPropStateCondition (10 vftable slots, 0x18 bytes): the new state of an
		// object-state message
		class ScenarioPropStateCondition : public fight::Condition
		{
		public:
			ScenarioPropStateCondition();
			virtual ~ScenarioPropStateCondition();

			virtual fight::Property* GetProperty(int index);
			virtual bool Evaluate(int a, int b, int c, int d);

			bool SetState(const fight::Name& newValue);

			// The property list, built once and freed again (0x108FFDA0 / 0x108FF400)
			static void RegisterProperties();
			static void ClearProperties();

			int unknownc;
			fight::Name state;  // +0x10
		};

		// RTTI: engine::scenario::ScenarioStringCondition (10 vftable slots, 0x18 bytes): the string of a string
		// message
		class ScenarioStringCondition : public fight::Condition
		{
		public:
			ScenarioStringCondition();
			virtual ~ScenarioStringCondition();

			virtual fight::Property* GetProperty(int index);
			virtual bool Evaluate(int a, int b, int c, int d);

			bool SetString(const fight::Name& newValue);

			// The property list, built once and freed again (0x108FFE20 / 0x108FF420)
			static void RegisterProperties();
			static void ClearProperties();

			int unknownc;
			fight::Name string;  // +0x10
		};

		// The property lists of the other five classes (0x1131B328 - 0x1131B338)
		extern fight::Property** gScenarioGameObjectAttributeConditionProperties;
		extern fight::Property** gScenarioGameObjectTouchesTriggerConditionProperties;
		extern fight::Property** gScenarioMessageConditionProperties;
		extern fight::Property** gScenarioPropStateConditionProperties;
		extern fight::Property** gScenarioStringConditionProperties;

		// The property lists of the three classes (0x113187A8 / 0x113187AC / 0x113187B0)
		extern fight::Property** gScenarioGameObjectConditionProperties;
		extern fight::Property** gScenarioScriptAttributeConditionProperties;
		extern fight::Property** gHasTagConditionProperties;

		// 0x108C1F70 / 0x108C21E0 / 0x108C2200: the factory of each class
		fight::ConditionFactory* CreateScenarioGameObjectConditionFactory(const char* name);
		fight::ConditionFactory* CreateScenarioScriptAttributeConditionFactory(const char* name);
		fight::ConditionFactory* CreateHasTagConditionFactory(const char* name);
		// 0x108C2220 / 0x108C2430 / 0x108C2460: adds the factory of each class to the registry
		void RegisterScenarioGameObjectConditionFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterScenarioScriptAttributeConditionFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterHasTagConditionFactory(fight::TrackRegistry* registry, const char* name);

		// 0x108FFAA0 - 0x108FFB20: the factory of each of the other five classes
		fight::ConditionFactory* CreateScenarioGameObjectAttributeConditionFactory(const char* name);
		fight::ConditionFactory* CreateScenarioGameObjectTouchesTriggerConditionFactory(const char* name);
		fight::ConditionFactory* CreateScenarioMessageConditionFactory(const char* name);
		fight::ConditionFactory* CreateScenarioPropStateConditionFactory(const char* name);
		fight::ConditionFactory* CreateScenarioStringConditionFactory(const char* name);

		// The registrations of the other five classes (0x108FFEA0 - 0x108FFF60)
		void RegisterScenarioMessageConditionFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterScenarioGameObjectAttributeConditionFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterScenarioStringConditionFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterScenarioPropStateConditionFactory(fight::TrackRegistry* registry, const char* name);
		void RegisterScenarioGameObjectTouchesTriggerConditionFactory(fight::TrackRegistry* registry,
			const char* name);

		// 0x108C2570: adds the factories of all eight classes
		void RegisterScenarioConditionFactories(fight::TrackRegistry* registry);
	}
}

#endif
