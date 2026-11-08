// engine::GameDBStorage (RTTI name): the profile storage of the game database. The unit is 0x108A56C0 - 0x108A5F30 (no
// assert path names it; the file name is a guess). Names are guesses.
#include "code/engine/database/gamedatabase.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108A5BB0
	GameDBStorage::GameDBStorage() : callback(0), timestampSubject(0), timestampObserved(false), state(0), unknown14(0), data(0), player(-1), profileSize(0)
	{
	}

	// FUNCTION: ENGINE 0x108A56C0
	GameDBStorage::~GameDBStorage()
	{
	}

	// FUNCTION: ENGINE 0x108A5E10
	// NONMATCHING: the engine loads both halves of the first hash before it forms the second name's, and keeps this in
	// ebx (29 %)
#ifdef NONMATCHING
	void GameDBStorage::OnDBSlot1(int a, int b)
	{
		if (timestampSubject != 0)
		{
			core::Name<core::CaseSensitiveKey> name(timestampSubject->name);
			const unsigned int* first = (const unsigned int*)&((core::Name<core::CaseSensitiveKey>*)a)->GetHash();
			unsigned int low = first[0];
			unsigned int high = first[1];
			const unsigned int* second = (const unsigned int*)&name.GetHash();
			if (second[0] == low && second[1] == high)
			{
				timestampSubject = 0;
				timestampObserved = true;
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x108A5EF0
	void GameDBStorage::ObserveTimestamp()
	{
		if (timestampSubject == 0 && !timestampObserved)
		{
			core::Name<core::CaseSensitiveKey> name("OLS_Profile_TimeStamp", true);
			timestampSubject = gGameDatabase->AddObserver(name, this, 0, 0);
		}
	}

	// FUNCTION: ENGINE 0x108A5880
	void GameDBStorage::SetCallback(GameDBStorageCallback* newCallback)
	{
		callback = newCallback;
	}

	// FUNCTION: ENGINE 0x108A5870
	bool GameDBStorage::IsOperationInProgress()
	{
		return state != 0;
	}
}
