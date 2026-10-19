// The scenario's fight tracks (see scenariotracks.h). The unit runs 0x10808480 - 0x10809B90.
#include "code/engine/scenario/scenariotracks.h"

namespace engine
{
	// The property list of the scenario string track (0x11284B54)
	fight::Property** gScenarioStringTrackProperties;

	// ---- the scenario string track ---------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x10808480
	bool ScenarioStringTrack::SetTimeBegin(float value)
	{
		timeBegin = value;
		return true;
	}

	// FUNCTION: ENGINE 0x10808490
	bool ScenarioStringTrack::SetTutorialOnly(bool value)
	{
		tutorialOnly = value;
		return true;
	}

	// FUNCTION: ENGINE 0x108084A0
	fight::Property* ScenarioStringTrack::GetProperty(int index)
	{
		return gScenarioStringTrackProperties[index];
	}

	// FUNCTION: ENGINE 0x108084B0
	void ScenarioStringTrack::ClearProperties()
	{
		fight::FreePropertyList(&gScenarioStringTrackProperties);
	}

	// FUNCTION: ENGINE 0x108084C0
	bool ScenarioStringTrack::SetString(const fight::Name& value)
	{
		string = value;
		return true;
	}

	// FUNCTION: ENGINE 0x108084E0
	ScenarioStringTrack::ScenarioStringTrack()
		: timeBegin(0.0f), tutorialOnly(false)
	{
	}

	// FUNCTION: ENGINE 0x10808510
	float ScenarioStringTrack::GetTimeBegin() const
	{
		return timeBegin;
	}

	// FUNCTION: ENGINE 0x10808520
	float ScenarioStringTrack::Slot10() const
	{
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x10808530
	ScenarioStringTrack::~ScenarioStringTrack()
	{
	}

	// FUNCTION: ENGINE 0x108086D0
	// EQUIVALENT: the engine saves esi in the entry block, before the guard's branch (cmp, push esi, jne); ours sinks
	// the push behind the branch and leaves the early exit without the pop; every other instruction is the engine's (97.7 %)
	void ScenarioStringTrack::RegisterProperties()
	{
		if (gScenarioStringTrackProperties == 0)
		{
			fight::Property* properties[256] = { 0 };
			fight::Property* property = new fight::PropertyFloatConstRange<ScenarioStringTrack>("timeBegin", &ScenarioStringTrack::SetTimeBegin);
			properties[0] = property;
			property = new fight::PropertyName<ScenarioStringTrack>("string", &ScenarioStringTrack::SetString);
			properties[1] = property;
			property = new fight::PropertyBool<ScenarioStringTrack>("tutorialonly", &ScenarioStringTrack::SetTutorialOnly);
			properties[2] = property;
			fight::RegisterPropertyList(properties, &gScenarioStringTrackProperties);
		}
	}

	// FUNCTION: ENGINE 0x10808640
	fight::TrackFactory* CreateScenarioStringTrackFactory(const char* name)
	{
		fight::TrackFactoryCasterTemplate<ScenarioStringTrack> caster;
		return fight::FindTrackFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x10808660
	void RegisterScenarioStringTrackFactory(fight::TrackRegistry* registry, const char* name)
	{
		fight::TrackFactoryCasterTemplate<ScenarioStringTrack> caster;
		registry->AddFactory(fight::FindTrackFactory(name, &caster));
	}

	template class fight::PropertyFloatConstRange<ScenarioStringTrack>;
	template class fight::PropertyBool<ScenarioStringTrack>;
	template class fight::PropertyName<ScenarioStringTrack>;
	template class fight::TrackFactoryTemplate<ScenarioStringTrack>;
	template class fight::TrackFactoryCasterTemplate<ScenarioStringTrack>;
}
