// proto::GameDatabaseHelper (RTTI name; bases engine::GameDBHelper and engine::DBObserver): the game's side of the game
// database. It keeps the list of the missions the dev select screen offers and the scripts' view of it (fe_GetNumMissions,
// fe_GetMissionName, fe_GetLocationName, AddValidMission, fe_PrepareGameDevSelect) and resets a setting to its default
// (fe_RestoreGameDBDefault). Of the class this file has the members that do not read the object (the list is one global);
// the unit is 0x104DEEC0 - 0x104E1310 (no assert path; the file name is a guess). Names other than the RTTI and script
// names are guesses.
#ifndef PROTO_GAMEDATABASEHELPER_H
#define PROTO_GAMEDATABASEHELPER_H

#include "code/engine/database/gamedbhelper.h"
#include "code/engine/dbobserver.h"

namespace proto
{
	// One level of the dev select list: its name, its location and 0x20 more characters
	struct DevSelectEntry
	{
		char name[0x20];
		char location[0x20];
		char unknown40[0x20];
	};

	// The list of levels (0x1109D158, 0x3004 bytes: 128 entries and the end pointer)
	struct DevSelectList
	{
		unsigned int Size() const
		{
			return end - entries;
		}
		// The entry to fill in, null when the list is full
		DevSelectEntry* Push()
		{
			if (Size() != 0x80)
			{
				DevSelectEntry* entry = end;
				end++;
				return entry;
			}
			return 0;
		}

		DevSelectEntry entries[0x80];
		DevSelectEntry* end;
	};
	extern DevSelectList gDevSelectList;

	class GameDatabaseHelper : public engine::GameDBHelper, public engine::DBObserver
	{
	public:
		// 0x104DEDA0
		explicit GameDatabaseHelper(const Config& config);
		// 0x104DF8D0 (deleting destructor 0x104E0C50)
		virtual ~GameDatabaseHelper();

		// The GameDBHelper slots: 0 (0x104DEDE0), 3 (0x104DEDD0, which jumps to the base), 4 (0x104DEE30), 5 (0x104E1150) and
		// 6 (0x104E0C80)
		virtual void OnMessage(engine::OLSMessage* message);
		virtual void Start();
		virtual void Stop();
		virtual bool Enable();
		virtual void Disable();

		// 0x104DF040 / 0x104DF210: makes the subjects of the level and the tutorials and lets them go
		void AddSubjects();
		void ReleaseSubjects();

		// The DBObserver's slot 1 (0x104DF2B0)
		virtual void OnDBSlot1(int a, int b);
		// vftable slot 0 of the DBObserver (0x104E0790): the level name key tells the zone set
		virtual void OnDBSlot0(int a, int b);

		// 0x104E0520: the script function AddValidMission
		void AddValidMission(const char* name, const char* location);
		// 0x104E05A0 / 0x104E05D0 / 0x104E05F0: fe_GetNumMissions, fe_GetMissionName, fe_GetLocationName
		unsigned int GetNumMissions();
		const char* GetMissionName(unsigned int index);
		const char* GetLocationName(unsigned int index);
		// 0x104E02F0: lets go of the subjects of the video and controller settings and tells the front end's hud
		void ReleaseSettingSubjects();
		// 0x104E0610: fe_RestoreGameDBDefault
		void RestoreGameDBDefault(const char* key, unsigned int player);
	};

	// 0x104E04C0: fe_PrepareGameDevSelect
	void PrepareGameDevSelect(unsigned int index);

	// 0x1109D074: the difficulty names and the dev select group (the first is the default)
	extern const char* gDifficultyNames[];
	// 0x104DEEC0: names the level and the difficulty in the game database and has the save manager start it
	void StartDevSelectLevel(const char* name, int flag, const char* group);
	// 0x104DEFC0 / 0x104DEFD0 / 0x104DEFE0: the flag that tells the dev select start is finished
	void FinishDevSelectStart();
	void ClearDevSelectStart();
	bool IsDevSelectStarted();
	// 0x104DEFF0: puts the game database in the mode the online game needs (0 off, 1 and 2 on)
	void SetGameDatabaseMode(int mode);
}

#endif
