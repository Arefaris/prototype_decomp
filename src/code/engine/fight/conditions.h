// The fight conditions that test health, object templates, attributes and velocities (unit 0x1080A6B0 - 0x1080BA40).
#ifndef ENGINE_FIGHT_CONDITIONS_H
#define ENGINE_FIGHT_CONDITIONS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::HealthCondition (10 vftable slots, 0x18 bytes)
	class HealthCondition : public fight::Condition
	{
	public:
		// 0x1080A700
		HealthCondition();
		virtual ~HealthCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x108AACC0)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetCompare(int value);
		bool SetHealthThreshold(float value);
		bool SetUsePercentage(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		float healthThreshold;  // +0xC
		int compare;  // +0x10
		bool usePercentage;  // +0x14
	};

	extern fight::Property** gHealthConditionProperties;
	// 0x1080A8D0
	// 0x1080A9E0
	fight::ConditionFactory* CreateHealthConditionFactory(const char* name);

	// RTTI: engine::ObjectTemplateCondition (10 vftable slots, 0x20 bytes)
	class ObjectTemplateCondition : public fight::Condition
	{
	public:
		// 0x1080AAF0
		ObjectTemplateCondition();
		virtual ~ObjectTemplateCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x1082B9A0)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetCompare(int value);
		bool SetObjectTemplate(const fight::Name& value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		int unknownc;
		fight::Name objectTemplate;  // +0x10
		int compare;  // +0x18
		int unknown1c;
	};

	extern fight::Property** gObjectTemplateConditionProperties;
	// 0x1080AC20
	// 0x1080AC40
	fight::ConditionFactory* CreateObjectTemplateConditionFactory(const char* name);

	// RTTI: engine::AttributeNameCondition (10 vftable slots, 0x28 bytes)
	class AttributeNameCondition : public fight::Condition
	{
	public:
		// 0x1080AE70
		AttributeNameCondition();
		virtual ~AttributeNameCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x108AADE0)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write
		bool SetKey(const fight::Name& value);
		bool SetCompare(int value);
		bool SetValue(const fight::Name& value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		int unknownc;
		fight::Name key;  // +0x10
		fight::Name value;  // +0x18
		int compare;  // +0x20
		int unknown24;
	};

	extern fight::Property** gAttributeNameConditionProperties;
	// 0x1080AFA0
	// 0x1080AFC0
	fight::ConditionFactory* CreateAttributeNameConditionFactory(const char* name);

	namespace animation
	{
		// RTTI: engine::animation::VelocityCondition (10 vftable slots, 0x1C bytes)
		class VelocityCondition : public fight::Condition
		{
		public:
			// 0x1080B260
			VelocityCondition();
			virtual ~VelocityCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x107F1C50)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetType(int value);
			bool SetDirection(int value);
			bool SetCompare(int value);
			bool SetVelocity(float value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			float velocity;  // +0xC
			int compare;  // +0x10
			int direction;  // +0x14
			int type;  // +0x18
		};

		extern fight::Property** gVelocityConditionProperties;
		// 0x1080B5A0
		// 0x1080B860
		fight::ConditionFactory* CreateVelocityConditionFactory(const char* name);
	}

	namespace animation
	{
		// RTTI: engine::animation::VelocityAngularCondition (10 vftable slots, 0x1C bytes)
		class VelocityAngularCondition : public fight::Condition
		{
		public:
			// 0x1080B2D0
			VelocityAngularCondition();
			virtual ~VelocityAngularCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x107F1D00)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetType(int value);
			bool SetDirection(int value);
			bool SetCompare(int value);
			bool SetAngularVelocity(float value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			float angularVelocity;  // +0xC
			int compare;  // +0x10
			int direction;  // +0x14
			int type;  // +0x18
		};

		extern fight::Property** gVelocityAngularConditionProperties;
		// 0x1080B5C0
		// 0x1080B890
		fight::ConditionFactory* CreateVelocityAngularConditionFactory(const char* name);
	}

}

#endif
