// proto::MissionObjectivesManager::LogText and ::MissionObjectives (RTTI structs; the second derives from the first): the
// entries of the mission objectives manager's two lists (the log texts and the objectives, kept in arrays of 0x40 and
// 0x20 of them). An entry names a text of the text bible and the state the front end shows it in; it tells the movie
// about itself in slot 1. The member names are guesses. Unit 0x104BB3D0 - 0x104BCB60 (no assert path; the file name is a
// guess). Of the manager only the two nested types are declared.
#ifndef PROTO_FRONTEND_MISSIONOBJECTIVES_H
#define PROTO_FRONTEND_MISSIONOBJECTIVES_H

#include "code/core/name.h"

namespace proto
{
	class MissionObjectivesManager
	{
	public:
		struct LogText
		{
			// 0x104BBB10
			LogText();
			// 0x104BBB40
			LogText(const core::Name<core::CaseSensitiveKey>& newTitle, const core::Name<core::CaseSensitiveKey>& newText, int newState);
			virtual ~LogText()
			{
			}
			// Slot 1 (0x104BB590): shows the entry in the front end's movie
			virtual void Show();

			int unknown4;
			core::Name<core::CaseSensitiveKey> title;  // +8
			core::Name<core::CaseSensitiveKey> text;  // +0x10
			int state;  // +0x18
			int unknown1C;
		};

		struct MissionObjectives : public LogText
		{
			// 0x104BC450
			MissionObjectives();
			// 0x104BBB80
			MissionObjectives(const core::Name<core::CaseSensitiveKey>& newTitle, const core::Name<core::CaseSensitiveKey>& newText,
				int newUnknown24, bool newUnknown28, bool newUnknown29);
			// Slot 1 (0x104BB5F0)
			virtual void Show();

			int unknown20;
			int unknown24;
			bool unknown28;
			bool unknown29;
		};
	};
}

#endif
