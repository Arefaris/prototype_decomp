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
