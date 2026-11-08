// The factory makers of the exit track and the message conditions (see exitfactories.h).
#include "code/engine/fight/exitfactories.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108127A0
	fight::TrackFactory* CreateExitTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<ExitTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108127C0
	fight::ConditionFactory* CreateMessageConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<MessageCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x108127E0
	fight::ConditionFactory* CreatePrintMessageConditionFactory(const char* name)
	{
		fight::ConditionFactoryCasterTemplate<PrintMessageCondition> caster;
		return fight::FindConditionFactory(name, &caster);
	}

	template class fight::TrackFactoryTemplate<ExitTrack>;
	template class fight::TrackFactoryCasterTemplate<ExitTrack>;
	template class fight::ConditionFactoryTemplate<MessageCondition>;
	template class fight::ConditionFactoryCasterTemplate<MessageCondition>;
	template class fight::ConditionFactoryTemplate<PrintMessageCondition>;
	template class fight::ConditionFactoryCasterTemplate<PrintMessageCondition>;
}

// The unit's template instances (the property and factory classes of its tracks and conditions), mapped in symbols.txt:
// FUNCTION: ENGINE 0x108123A0
// FUNCTION: ENGINE 0x108123B0
// FUNCTION: ENGINE 0x108123E0
// FUNCTION: ENGINE 0x10812410
// FUNCTION: ENGINE 0x10812430
// FUNCTION: ENGINE 0x10812470
// FUNCTION: ENGINE 0x10812480
// FUNCTION: ENGINE 0x108124B0
// FUNCTION: ENGINE 0x108124E0
// FUNCTION: ENGINE 0x10812500
// FUNCTION: ENGINE 0x10812540
// FUNCTION: ENGINE 0x10812550
// FUNCTION: ENGINE 0x10812580
// FUNCTION: ENGINE 0x108125B0
// FUNCTION: ENGINE 0x108125D0
