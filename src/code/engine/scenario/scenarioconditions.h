// The scenario's fight conditions (RTTI: engine::scenario::*Condition): they ask a script event (a ScriptOwner, the
// node a scenario message was sent to) about the message that caused it. The unit is 0x108C14A0 - 0x108C2570 (no
// assert path; the file name is a guess, the property names come from the reflection strings). The conditions of
// 0x108FF340 - 0x10900260 (their constructors, destructors and properties are another unit) are declared here with
// the members their evaluations in this unit read.
#ifndef ENGINE_SCENARIO_SCENARIOCONDITIONS_H
#define ENGINE_SCENARIO_SCENARIOCONDITIONS_H

#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	namespace scenario
	{
		// The value of a scripted game object attribute (8 bytes, the engine's class is not named): a type and the
		// value, set from text
		class AttributeValue
		{
		public:
			// 0x108718B0
			AttributeValue();
			// 0x10872050
			~AttributeValue();
			// 0x108724B0: converts the value to another type
			void SetType(int newType);
			// 0x10872060: parses text as the value of the current type
			void SetFromString(const char* text);
			// 0x10871AF0: the text of the value, in a buffer of the class
			const char* ToString() const;

			int type;
			int value;
		};

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

			// vftable slot 0 (0x108FF4E0)
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual bool Evaluate(int a, int b, int c, int d);

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

			// The getters the evaluation unit holds (the setters are in the other unit)
			int GetSlot() const;
			const char* GetKey() const;
			const fight::Name& GetValue() const;

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

			int unknownc;
			fight::Name trigger;  // +0x10: the object of the message's second handle
			fight::Name object;  // +0x18: the object of its first handle
			int type;  // +0x20
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

			int unknownc;
			fight::Name string;  // +0x10
		};

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

		// The factories of the other five classes (0x108FFEA0 - 0x108FFF60, another unit)
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
