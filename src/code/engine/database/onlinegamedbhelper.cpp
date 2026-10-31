// The base of the database subjects and the online helper that sends them to the other machines (engine::DBSubjectBase
// and the sharing tests of engine::DBSubject, then engine::OnlineGameDBHelper); unit 0x10893240 - 0x10894440 (no
// assert path; the file name is a guess). Names other than the RTTI ones are guesses.
#include "code/engine/controller/inputsystem.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/online/replay.h"
#include "code/engine/system/engineflags.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10893240
	DBSubjectBase::DBSubjectBase()
	{
		unknown0 = -1;
		id = 0;
	}

	// FUNCTION: ENGINE 0x10893250
	// EQUIVALENT: the engine shares the conditional jump of both paths and returns through a constant load, ours
	// returns the flag (58 %)
	bool DBSubject::IsShared()
	{
		Replay* replay = gReplay;
		if (replay != 0 && (replay->HasRecording() || replay->GetPlaybackFlagA4()))
		{
			if (id == -1)
			{
				return false;
			}
			if (id == 0)
			{
				return false;
			}
			return true;
		}
		if (!HasEngineFlags(0x10))
		{
			return false;
		}
		if (id == -1)
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108932B0
	// EQUIVALENT: the engine loads the slot's id into eax, ours into edx (76 %)
	bool DBSubject::IsPlayerSynced(unsigned int player)
	{
		bool result = false;
		switch (id)
		{
		case 0:
			result = (controller::InputSystem::Get()->slots[player].id & 0xffffff00) == 0xfe00;
			break;
		case 1:
			return true;
		case 2:
			return HasEngineFlags(0x20);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10893390
	// EQUIVALENT: the engine loads the slot's id into eax, ours into edx (73 %)
	bool DBSubject::IsPlayerSent(unsigned int player)
	{
		bool result = false;
		switch (id)
		{
		case 0:
			result = (controller::InputSystem::Get()->slots[player].id & 0xffffff00) == 0xfe00;
			break;
		case 1:
		case 2:
			return HasEngineFlags(0x20);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10893BE0
	bool DBSubject::IsValidPlayer(unsigned int player)
	{
		if (id != -1 && (HasEngineFlags(0x10) || id == 3))
		{
			return IsPlayerSynced(player);
		}
		return true;
	}
}
