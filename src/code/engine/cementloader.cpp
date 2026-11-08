// The cement loader of the content manager (unit 0x108E44F0 - 0x108E5B00; no assert path, file name and the function
// and variable names guessed): the content manager opens the cement libraries of one collection of its cement file
// definition on a thread of its own and polls its state.
#include "code/engine/contentmanager.h"
#include "code/core/criticalsection.h"
#include "code/core/thread.h"
#include "code/core/interlocked.h"

namespace core
{
	// The lock and the state the cement thread shares with its caller
	static unsigned char sCementLock[0x18];
	static engine::ContentManager::ContentCementFileDefinition::Collection* sCementCollection;
	static Thread sCementThread;
	static int sCementDefault;
	static int sCementMode;
	static int sCementState;
	static int sCementError;
	static bool sCementThreadStarted;
	static volatile long sCementProgress;

	// 0x108E56E0: the thread's function
	int CementThread(void* argument);

	// FUNCTION: ENGINE 0x108E45A0
	void ShutdownCement()
	{
		CriticalSectionDelete(sCementLock);
		if (engine::gCementDefinition != 0)
		{
			engine::gCementDefinition->Release();
			engine::gCementDefinition = 0;
		}
	}

	// FUNCTION: ENGINE 0x108E4630
	int GetCementResult(int* value)
	{
		*value = sCementDefault;
		return sCementError;
	}

	// FUNCTION: ENGINE 0x108E45D0
	bool HasCement()
	{
		return engine::gCementDefinition != 0;
	}

	// FUNCTION: ENGINE 0x108E45E0
	int PollCement()
	{
		CriticalSectionEnter(sCementLock);
		if (sCementThreadStarted)
		{
			WaitThread(&sCementThread);
			DestroyThread(&sCementThread);
			sCementThreadStarted = false;
		}
		int state = sCementState;
		CriticalSectionLeave(sCementLock);
		return state;
	}

	// FUNCTION: ENGINE 0x108E5B00
	// NONMATCHING: the engine's frame has one unused word below the saved registers (77 %)
#ifdef NONMATCHING
	void StartCement(const Name<CaseSensitiveKey>& name, int mode)
	{
		engine::ContentManager::ContentCementFileDefinition* definition = engine::gCementDefinition;
		engine::ContentManager::ContentCementFileDefinition::Collection* found = 0;
		unsigned int index = 0;
		if (definition->collections.Size() != 0)
		{
			engine::ContentManager::ContentCementFileDefinition::Collection* candidate = definition->collections.Begin();
			do
			{
				if (candidate->name == name)
				{
					found = &definition->collections[index];
					break;
				}
				index++;
				candidate++;
			}
			while (index < definition->collections.Size());
		}
		sCementCollection = found;
		sCementMode = mode;
		sCementState = 1;
		sCementError = 0;
		_InterlockedExchange(&sCementProgress, 0);
		StartThread(&sCementThread, CementThread, 0, 3, 0x4000, 1, 0, "Cement Thread");
	}
#endif
}
