// The fight conditions on the character input, the locomotion input and on a turn (unit 0x108F6660 - 0x108F7220; no assert path, file name guessed).
#include "code/engine/controller/characterintentioninputmap.h"
#include "code/engine/fight/inputconditions.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/gameobject/gameobjectmessages.h"

namespace fight
{
	// 0x1009E120 (another unit): compares two floats with one of the compare operators (lhs op rhs)
	bool CompareFloats(int op, const float* lhs, const float* rhs);
}

namespace engine
{
	GameObjectHandle GetObjectHandle(core::IRefCount* object);

	// The two axes of the locomotion input (0x1085B820 / 0x1085B830, another unit): indices into the intention's axis table
	int GetLocoAxisA();
	int GetLocoAxisB();

	// The 2D value a locomotion axis is read into: starts at zero (the engine's kept copy of math::Vector2's default
	// constructor is 0x107E2B50)
	struct AxisValue
	{
		AxisValue();

		float x;
		float y;
	};

	fight::EnumEntry gCharacterInputConditionButtonStateTable[4] =
		{
			{ fight::Name("Up", 0) },
			{ fight::Name("Pressed", 0) },
			{ fight::Name("Down", 0) },
			{ fight::Name("Released", 0) }
		};
	extern const int gCharacterInputConditionButtonStateCount;
	extern const int gCompareOperatorCount;
	extern fight::EnumEntry gCompareOperatorTable[];
	extern fight::EnumEntry gLocoInputConditionInputTypeTable[];
	fight::EnumEntry gTurnInputConditionPreviousDirectionTable[2] =
		{
			{ fight::Name("Facing Direction", 0) },
			{ fight::Name("Physical Velocity Direction", 0) }
		};
	fight::EnumEntry gTurnInputConditionRangeTypeTable[2] =
		{
			{ fight::Name("Inside Range", 0) },
			{ fight::Name("Outside Range", 0) }
		};

	fight::Property** gCharacterInputConditionProperties;  // 0x1131B290

	// FUNCTION: ENGINE 0x108F6660
	bool CharacterInputCondition::SetButton(int newValue)
	{
		button = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F6670
	bool CharacterInputCondition::SetButtonState(int newValue)
	{
		buttonState = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F6680
	bool CharacterInputCondition::SetCompareTime(int newValue)
	{
		compareTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F6690
	bool CharacterInputCondition::SetTime(float newValue)
	{
		time = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F66A0
	bool CharacterInputCondition::SetCompareValue(int newValue)
	{
		compareValue = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F66B0
	bool CharacterInputCondition::SetValue(float newValue)
	{
		value = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F6770
	fight::Property* CharacterInputCondition::GetProperty(int index)
	{
		return gCharacterInputConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108F6780
	void CharacterInputCondition::ClearProperties()
	{
		fight::FreePropertyList(&gCharacterInputConditionProperties);
	}

	// FUNCTION: ENGINE 0x1092D810
	const fight::EnumEntry* CharacterInputCondition::GetButtonEntry(int index)
	{
		return (const fight::EnumEntry*)CharacterIntentionInputMap::GetButtonNames() + index;
	}

	// FUNCTION: ENGINE 0x1092D820
	int CharacterInputCondition::GetButtonCount()
	{
		return CharacterIntentionInputMap::GetButtonCount();
	}

	// FUNCTION: ENGINE 0x1092D830
	// EQUIVALENT: block layout; the engine does not thread the state test (w == 2 and the second pair) and keeps one shared exit for
	// every failure after the first comparison, ours returns false at once where the test cannot hold; every call is the engine's
	bool CharacterInputCondition::Evaluate(int a, int b, int c, int d)
	{
		GameObjectHandle handle = GetObjectHandle((core::IRefCount*)c);
		GameObject* object = handle.Get();
		if (object == 0)
		{
			return false;
		}
		int wantedButton = button;
		CharacterQueryIntentionMessage message;
		object->SendMessage(&message);
		if (message.intention == 0)
		{
			return false;
		}
		CharacterIntentionButton* entry = message.intention->GetButton(wantedButton);
		float held = entry->time;
		int wantedState = buttonState;
		int state = entry->state;
		if (state != wantedState)
		{
			if (!((wantedState == 2 && state == 1) || (wantedState == 0 && state == 3)))
			{
				return false;
			}
			held = 0.0f;
		}
		float limit = time;
		if (!fight::CompareFloats(compareTime, &held, &limit))
		{
			return false;
		}
		float current = entry->value;
		float wantedValue = value;
		return fight::CompareFloats(compareValue, &current, &wantedValue) != 0;
	}

	// FUNCTION: ENGINE 0x108F6790
	CharacterInputCondition::CharacterInputCondition() : fight::Condition(0), time(0.0f), value(0.0f), button(0), buttonState(1), compareTime(4), compareValue(4)
	{
	}

	// FUNCTION: ENGINE 0x108F67D0
	CharacterInputCondition::~CharacterInputCondition()
	{
	}

	// FUNCTION: ENGINE 0x108F6D10
	fight::ConditionFactory* CreateCharacterInputConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<CharacterInputCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F6D70
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void CharacterInputCondition::RegisterProperties()
	{
		if (gCharacterInputConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnum<CharacterInputCondition>("button", &CharacterInputCondition::GetButtonEntry, &CharacterInputCondition::GetButtonCount, &CharacterInputCondition::SetButton);
			properties[0] = property;
			property = new fight::PropertyEnumConstList<CharacterInputCondition>("buttonState", gCharacterInputConditionButtonStateTable, gCharacterInputConditionButtonStateCount, &CharacterInputCondition::SetButtonState);
			properties[1] = property;
			property = new fight::PropertyEnumConstList<CharacterInputCondition>("compareTime", gCompareOperatorTable, gCompareOperatorCount, &CharacterInputCondition::SetCompareTime);
			properties[2] = property;
			property = new fight::PropertyFloatConstRange<CharacterInputCondition>("time", &CharacterInputCondition::SetTime);
			properties[3] = property;
			property = new fight::PropertyEnumConstList<CharacterInputCondition>("compareValue", gCompareOperatorTable, gCompareOperatorCount, &CharacterInputCondition::SetCompareValue);
			properties[4] = property;
			property = new fight::PropertyFloatConstRange<CharacterInputCondition>("value", &CharacterInputCondition::SetValue);
			properties[5] = property;
			fight::RegisterPropertyList(properties, &gCharacterInputConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108F71C0
	void RegisterCharacterInputConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<CharacterInputCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnum<CharacterInputCondition>;
	template class fight::PropertyEnumConstList<CharacterInputCondition>;
	template class fight::PropertyFloatConstRange<CharacterInputCondition>;
	template class fight::ConditionFactoryTemplate<CharacterInputCondition>;
	template class fight::ConditionFactoryCasterTemplate<CharacterInputCondition>;


	fight::Property** gLocoInputConditionProperties;  // 0x1131B294

	// FUNCTION: ENGINE 0x108F66C0
	bool LocoInputCondition::SetInputType(int newValue)
	{
		inputType = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F66D0
	bool LocoInputCondition::SetCompareTime(int newValue)
	{
		compareTime = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F66E0
	bool LocoInputCondition::SetTime(float newValue)
	{
		time = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F66F0
	bool LocoInputCondition::SetCompareValue(int newValue)
	{
		compareValue = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F6700
	bool LocoInputCondition::SetValue(float newValue)
	{
		value = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F67E0
	fight::Property* LocoInputCondition::GetProperty(int index)
	{
		return gLocoInputConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108F67F0
	void LocoInputCondition::ClearProperties()
	{
		fight::FreePropertyList(&gLocoInputConditionProperties);
	}

	// FUNCTION: ENGINE 0x1092D960
	// EQUIVALENT: register allocation; the engine keeps this in ebx and the second axis index on the stack, ours the other way round; every call and memory access is the engine's
	bool LocoInputCondition::Evaluate(int a, int b, int c, int d)
	{
		GameObjectHandle handle = GetObjectHandle((core::IRefCount*)c);
		GameObject* object = handle.Get();
		if (object == 0)
		{
			return false;
		}
		int axisA = GetLocoAxisA();
		int axisB = GetLocoAxisB();
		CharacterQueryIntentionMessage message;
		object->SendMessage(&message);
		CharacterIntention* intention = message.intention;
		if (intention == 0)
		{
			return false;
		}
		AxisValue axis;
		switch (inputType)
		{
		case 0:
			axis = *(AxisValue*)intention->GetAxis(axisA);
			break;
		case 1:
			axis = *(AxisValue*)intention->GetAxis(axisB);
			break;
		}
		float held = axis.y;
		float limit = time;
		if (!fight::CompareFloats(compareTime, &held, &limit))
		{
			return false;
		}
		float current = axis.x;
		float wantedValue = value;
		return fight::CompareFloats(compareValue, &current, &wantedValue) != 0;
	}

	// FUNCTION: ENGINE 0x108F6800
	LocoInputCondition::LocoInputCondition() : fight::Condition(0), time(0.0f), value(0.0f), compareTime(4), compareValue(4), inputType(0)
	{
	}

	// FUNCTION: ENGINE 0x108F6840
	LocoInputCondition::~LocoInputCondition()
	{
	}

	// FUNCTION: ENGINE 0x108F6D30
	fight::ConditionFactory* CreateLocoInputConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<LocoInputCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F6F20
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void LocoInputCondition::RegisterProperties()
	{
		if (gLocoInputConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnumConstList<LocoInputCondition>("inputType", gLocoInputConditionInputTypeTable, 2, &LocoInputCondition::SetInputType);
			properties[0] = property;
			property = new fight::PropertyEnumConstList<LocoInputCondition>("compareTime", gCompareOperatorTable, gCompareOperatorCount, &LocoInputCondition::SetCompareTime);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<LocoInputCondition>("time", &LocoInputCondition::SetTime);
			properties[2] = property;
			property = new fight::PropertyEnumConstList<LocoInputCondition>("compareValue", gCompareOperatorTable, gCompareOperatorCount, &LocoInputCondition::SetCompareValue);
			properties[3] = property;
			property = new fight::PropertyFloatConstRange<LocoInputCondition>("value", &LocoInputCondition::SetValue);
			properties[4] = property;
			fight::RegisterPropertyList(properties, &gLocoInputConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108F71F0
	void RegisterLocoInputConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<LocoInputCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<LocoInputCondition>;
	template class fight::PropertyFloatConstRange<LocoInputCondition>;
	template class fight::ConditionFactoryTemplate<LocoInputCondition>;
	template class fight::ConditionFactoryCasterTemplate<LocoInputCondition>;


	fight::Property** gTurnInputConditionProperties;  // 0x1131B298

	// FUNCTION: ENGINE 0x108F6710
	bool TurnInputCondition::SetPreviousDirection(int newValue)
	{
		previousDirection = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F6720
	bool TurnInputCondition::SetMinAngle(float newValue)
	{
		minAngle = newValue * 0.0174532924f;
		return true;
	}

	// FUNCTION: ENGINE 0x108F6740
	bool TurnInputCondition::SetMaxAngle(float newValue)
	{
		maxAngle = newValue * 0.0174532924f;
		return true;
	}

	// FUNCTION: ENGINE 0x108F6760
	bool TurnInputCondition::SetRangeType(int newValue)
	{
		rangeType = newValue;
		return true;
	}

	// FUNCTION: ENGINE 0x108F6850
	fight::Property* TurnInputCondition::GetProperty(int index)
	{
		return gTurnInputConditionProperties[index];
	}

	// FUNCTION: ENGINE 0x108F6860
	void TurnInputCondition::ClearProperties()
	{
		fight::FreePropertyList(&gTurnInputConditionProperties);
	}

	// FUNCTION: ENGINE 0x108F6870
	TurnInputCondition::TurnInputCondition() : fight::Condition(0), maxAngle(0.785398185f), minAngle(-0.785398185f), previousDirection(0), rangeType(0)
	{
	}

	// FUNCTION: ENGINE 0x108F68B0
	TurnInputCondition::~TurnInputCondition()
	{
	}

	// FUNCTION: ENGINE 0x108F6D50
	fight::ConditionFactory* CreateTurnInputConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<TurnInputCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108F7090
	// EQUIVALENT: the engine saves the registers it uses in the entry block, before the guard's branch; ours sinks the pushes behind the branch and leaves the early exit without the pops; every other instruction is the engine's
	void TurnInputCondition::RegisterProperties()
	{
		if (gTurnInputConditionProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = 0;
			property = new fight::PropertyEnumConstList<TurnInputCondition>("previousDirection", gTurnInputConditionPreviousDirectionTable, 2, &TurnInputCondition::SetPreviousDirection);
			properties[0] = property;
			property = new fight::PropertyFloatConstRange<TurnInputCondition>("minAngle", &TurnInputCondition::SetMinAngle);
			properties[1] = property;
			property = new fight::PropertyFloatConstRange<TurnInputCondition>("maxAngle", &TurnInputCondition::SetMaxAngle);
			properties[2] = property;
			property = new fight::PropertyEnumConstList<TurnInputCondition>("rangeType", gTurnInputConditionRangeTypeTable, 2, &TurnInputCondition::SetRangeType);
			properties[3] = property;
			fight::RegisterPropertyList(properties, &gTurnInputConditionProperties);
		}
	}

	// FUNCTION: ENGINE 0x108F7220
	void RegisterTurnInputConditionFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::ConditionFactoryCasterTemplate<TurnInputCondition> caster;
		registry->AddFactory(fight::FindConditionFactory(name, &caster));
	}

	template class fight::PropertyEnumConstList<TurnInputCondition>;
	template class fight::PropertyFloatConstRange<TurnInputCondition>;
	template class fight::ConditionFactoryTemplate<TurnInputCondition>;
	template class fight::ConditionFactoryCasterTemplate<TurnInputCondition>;


}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D79240
// FUNCTION: ENGINE 0x10D79270
// FUNCTION: ENGINE 0x10D79740
// FUNCTION: ENGINE 0x10D8B2D0
// FUNCTION: ENGINE 0x10D8B2E0
// FUNCTION: ENGINE 0x10D8B490


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108F68C0
// FUNCTION: ENGINE 0x108F68E0
// FUNCTION: ENGINE 0x108F6900
// FUNCTION: ENGINE 0x108F6920
// FUNCTION: ENGINE 0x108F6930
// FUNCTION: ENGINE 0x108F6960
// FUNCTION: ENGINE 0x108F6970
// FUNCTION: ENGINE 0x108F69A0
// FUNCTION: ENGINE 0x108F69B0
// FUNCTION: ENGINE 0x108F69E0
// FUNCTION: ENGINE 0x108F6A10
// FUNCTION: ENGINE 0x108F6A30
// FUNCTION: ENGINE 0x108F6A40
// FUNCTION: ENGINE 0x108F6A60
// FUNCTION: ENGINE 0x108F6A70
// FUNCTION: ENGINE 0x108F6AA0
// FUNCTION: ENGINE 0x108F6AB0
// FUNCTION: ENGINE 0x108F6AD0
// FUNCTION: ENGINE 0x108F6AF0
// FUNCTION: ENGINE 0x108F6B00
// FUNCTION: ENGINE 0x108F6B20
// FUNCTION: ENGINE 0x108F6B40
// FUNCTION: ENGINE 0x108F6B50
// FUNCTION: ENGINE 0x108F6B80
// FUNCTION: ENGINE 0x108F6B90
// FUNCTION: ENGINE 0x108F6BB0
// FUNCTION: ENGINE 0x108F6BD0
// FUNCTION: ENGINE 0x108F6BE0
// FUNCTION: ENGINE 0x108F6C00
// FUNCTION: ENGINE 0x108F6C20
// FUNCTION: ENGINE 0x108F6C30
// FUNCTION: ENGINE 0x108F6C60
// FUNCTION: ENGINE 0x108F6C70
// FUNCTION: ENGINE 0x108F6C90
// FUNCTION: ENGINE 0x108F6CB0
// FUNCTION: ENGINE 0x108F6CC0
// FUNCTION: ENGINE 0x108F6CE0
// FUNCTION: ENGINE 0x108F6D00
// FUNCTION: ENGINE 0x108F7250
// FUNCTION: ENGINE 0x108F7280
// FUNCTION: ENGINE 0x108F72A0
// FUNCTION: ENGINE 0x108F72D0
// FUNCTION: ENGINE 0x108F72F0
// FUNCTION: ENGINE 0x108F7320
// FUNCTION: ENGINE 0x108F7340
// FUNCTION: ENGINE 0x108F7380
// FUNCTION: ENGINE 0x108F73C0
