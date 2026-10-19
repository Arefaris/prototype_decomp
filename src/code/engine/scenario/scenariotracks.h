// The scenario's fight tracks: the track that sends a scenario string event (RTTI: engine::ScenarioStringTrack) and
// the Lua script track, action and condition (engine::scenario::LuaTrack / LuaAction / LuaCondition). The unit is
// 0x10808480 - 0x10809B90 (no assert path; file and member names are guesses, the property names come from the
// reflection strings).
#ifndef ENGINE_SCENARIO_SCENARIOTRACKS_H
#define ENGINE_SCENARIO_SCENARIOTRACKS_H

#include "code/engine/fight/trackfactory.h"

namespace engine
{
	// RTTI: engine::ScenarioStringTrack (16 vftable slots, 0x20 bytes): fires a scenario string event
	class ScenarioStringTrack : public fight::Track
	{
	public:
		ScenarioStringTrack();
		virtual ~ScenarioStringTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (another unit)
		virtual void Slot15();

		// The members the properties write: "timeBegin", "string" and "tutorialonly"
		bool SetTimeBegin(float value);
		bool SetString(const fight::Name& value);
		bool SetTutorialOnly(bool value);

		// The property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		fight::Name string;
		float timeBegin;
		bool tutorialOnly;
	};

	extern fight::Property** gScenarioStringTrackProperties;

	fight::TrackFactory* CreateScenarioStringTrackFactory(const char* name);
	void RegisterScenarioStringTrackFactory(fight::TrackRegistry* registry, const char* name);
}

#endif
