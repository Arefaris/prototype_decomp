// The fight conditions on the locomotion input and on a turn (unit 0x108F66C0 - 0x108F7220; no assert path, file name guessed).
#include "code/engine/fight/inputconditions.h"

namespace engine
{
	extern const int gCompareOperatorCount;
	extern fight::EnumEntry gCompareOperatorTable[];
	extern fight::EnumEntry gLocoInputConditionInputTypeTable[];
	extern fight::EnumEntry gTurnInputConditionPreviousDirectionTable[];
	extern fight::EnumEntry gTurnInputConditionRangeTypeTable[];

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
			property = new fight::PropertyEnumConstList<LocoInputCondition>("compareValue", gCompareOperatorTable, 0, &LocoInputCondition::SetCompareValue);
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
