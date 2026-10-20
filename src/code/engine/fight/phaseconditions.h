// The fight conditions on a keyboard key and on a puppet's animation phase (unit 0x108B8E50 - 0x108B94F0; no assert path, file name guessed).
#ifndef ENGINE_FIGHT_PHASECONDITIONS_H
#define ENGINE_FIGHT_PHASECONDITIONS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::PCKeyboardCondition (10 vftable slots, 0xC bytes)
	class PCKeyboardCondition : public fight::Condition
	{
	public:
		// 0x108B8EC0
		PCKeyboardCondition();
		virtual ~PCKeyboardCondition();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9 (0x108FCE80)
		virtual bool Evaluate(int a, int b, int c, int d);

		// The members the properties write

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

	};

	extern fight::Property** gPCKeyboardConditionProperties;
	// 0x108B8FE0
	// 0x108B9000
	fight::ConditionFactory* CreatePCKeyboardConditionFactory(const char* name);

	namespace animation
	{
		// RTTI: engine::animation::PuppetPhaseCondition (10 vftable slots, 0x24 bytes)
		class PuppetPhaseCondition : public fight::Condition
		{
		public:
			// 0x108B90B0
			PuppetPhaseCondition();
			virtual ~PuppetPhaseCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9 (0x108FCFF0)
			virtual bool Evaluate(int a, int b, int c, int d);

			// The members the properties write
			bool SetPositionConditionType(int value);
			bool SetMinPositionPhase(float value);
			bool SetMaxPositionPhase(float value);
			bool SetVelocityConditionType(int value);
			bool SetMinVelocityPhase(float value);
			bool SetMaxVelocityPhase(float value);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			float maxPositionPhase;  // +0xC
			float maxVelocityPhase;  // +0x10
			float minPositionPhase;  // +0x14
			float minVelocityPhase;  // +0x18
			int positionConditionType;  // +0x1C
			int velocityConditionType;  // +0x20
		};

		extern fight::Property** gPuppetPhaseConditionProperties;
		// 0x108B9250
		// 0x108B9400
		fight::ConditionFactory* CreatePuppetPhaseConditionFactory(const char* name);
	}

}

#endif
