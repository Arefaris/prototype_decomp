// proto::MissionObjectivesManager::LogText and ::MissionObjectives: see the header.
#include "code/proto/frontend/missionobjectives.h"

#include "code/core/textconvert.h"
#include "code/engine/frontend/femovie.h"

namespace engine
{
	class FrontEnd;
	// 0x10864330
	FrontEnd* Unknown10864330();
	// 0x10872840: calls a function of the front end's movie with a format and the arguments it names (name unknown)
	void Unknown10872840(FrontEnd* frontEnd, const char* function, const char* format, ...);
	// 0x10873F60 (the text bible's unit): the text a name stands for
	const char* GetSpeakerText(const core::Name<core::CaseSensitiveKey>& name);
	// 0x108833E0
	void FormatMessage(const FEMovie::Value* values, int unused, FEMovie::Value* result, char* target, int size, const char* text);
}

namespace proto
{
	// 0x11096774: the movie clip the objectives are shown in
	static const char* sObjectivesClip = "mcAnchor";
	// 0x1126CCE8: where the text of an entry is made
	static char sObjectiveText[0x400];

	// 0x104BB490 (name guess): the text of an entry, made from the text bible's message
	const char* GetObjectiveText(const core::Name<core::CaseSensitiveKey>* name);

	// FUNCTION: ENGINE 0x104BB490
	const char* GetObjectiveText(const core::Name<core::CaseSensitiveKey>* name)
	{
		const char* answer = 0;
		engine::FEMovie::Value values;
		values.type = 4;
		values.string = "MISSIONOBJECTIVE";
		engine::FEMovie::Value result;
		const char* message = engine::GetSpeakerText(*name);
		if (message != 0)
		{
			char buffer[2048];
			engine::FormatMessage(&values, 1, &result, buffer, 0x400, message);
			core::ConvertText(sObjectiveText, 1, buffer, 2, 0, 0x400, 0, 0, 0);
			answer = sObjectiveText;
		}
		return answer;
	}

	// FUNCTION: ENGINE 0x104BBB10
	MissionObjectivesManager::LogText::LogText() :
		state(3)
	{
	}

	// FUNCTION: ENGINE 0x104BBB40
	MissionObjectivesManager::LogText::LogText(const core::Name<core::CaseSensitiveKey>& newTitle, const core::Name<core::CaseSensitiveKey>& newText, int newState) :
		title(newTitle),
		text(newText),
		state(newState)
	{
	}

	// FUNCTION: ENGINE 0x104BB590
	void MissionObjectivesManager::LogText::Show()
	{
		const char* message = GetObjectiveText(&text);
		if (message != 0)
		{
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%s%d%d%d%d", sObjectivesClip, "SetObjectives", message, state, -1, 0, 0);
		}
	}

	// FUNCTION: ENGINE 0x104BC450
	MissionObjectivesManager::MissionObjectives::MissionObjectives()
	{
	}

	// FUNCTION: ENGINE 0x104BBB80
	MissionObjectivesManager::MissionObjectives::MissionObjectives(const core::Name<core::CaseSensitiveKey>& newTitle, const core::Name<core::CaseSensitiveKey>& newText,
		int newUnknown24, bool newUnknown28, bool newUnknown29) :
		LogText(newTitle, newText, 0),
		unknown20(0x26),
		unknown24(newUnknown24),
		unknown28(newUnknown28),
		unknown29(newUnknown29)
	{
	}

	// FUNCTION: ENGINE 0x104BB5F0
	void MissionObjectivesManager::MissionObjectives::Show()
	{
		const char* message = GetObjectiveText(&text);
		if (message != 0)
		{
			engine::Unknown10872840(engine::Unknown10864330(), "AS_CallASFunction", "%s%s%s%d%d%d%d", sObjectivesClip, "SetObjectives", message, state, unknown24, unknown29, unknown28);
		}
	}
}
