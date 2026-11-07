// engine::StorageManager::StorageGameState (RTTI name): the game state the storage services (the profile and the saved
// games) run in while they wait for the console's storage; the unit is the part of the storage manager around
// 0x108741E0 - 0x10874880 (no assert path, the file name is a guess).
#include "code/core/file/file.h"
#include "code/core/textconvert.h"
#include "code/core/thread.h"
#include "code/engine/gamestate.h"

// 0x107DEF90: the allocation from the heap the second argument names
void* operator new(unsigned int size, int heap);

namespace engine
{
	class SyncCommands
	{
	public:
		class SyncCallback;
	};

	// 0x10838B40 / 0x10838B80 (gamestate.cpp): switch to a state, or put one on top of the current one
	void RequestGameState(int state, int mode, SyncCommands::SyncCallback* callback);
	void RequestGameStateOverlay(int state, int mode, SyncCommands::SyncCallback* callback);

	// The game state table's functions (gamestate.cpp)
	void AddGameState(void* stateObject, int id, int priority, int flag, int mode, int parent);
	void FreeGameState(int id);
	unsigned int* RemoveStateFlags(unsigned int flags);

	namespace StorageManager
	{
		class StorageGameState : public GameState
		{
		public:
			// FUNCTION: ENGINE 0x108741E0
			// (the engine expands it where it makes the state and keeps this copy)
			StorageGameState() :
				GameState(0, 0x10000),
				busy(false)
			{
			}
			// FUNCTION: ENGINE 0x10874200
			~StorageGameState()
			{
			}
			// 0x10874210: the storage is busy from now on, and the state no longer holds the game back
			virtual void Enter();
			// 0x10874220
			virtual void Leave();

			bool busy;  // +0x54
		};

		// GLOBAL: ENGINE 0x113169E8
		// the state, made by 0x108747B0 and freed by 0x10874800 (name guess)
		StorageGameState* gState;

		// FUNCTION: ENGINE 0x10874210
		void StorageGameState::Enter()
		{
			busy = true;
			RemoveStateFlags(4);
		}

		// FUNCTION: ENGINE 0x10874220
		void StorageGameState::Leave()
		{
			busy = false;
		}

		// The request the storage fiber works on: the callers below fill it in and raise the pending flag, the fiber answers
		// through gResult (all names guessed)
		// GLOBAL: ENGINE 0x11316968
		int gRequestUnknown68;
		// GLOBAL: ENGINE 0x1131696C
		int gRequestKind;
		// GLOBAL: ENGINE 0x11316970
		int gRequestArg70;
		// GLOBAL: ENGINE 0x11316974
		int gRequestArg74;
		// GLOBAL: ENGINE 0x11316978
		int gResult;
		// GLOBAL: ENGINE 0x1131697C
		bool gRequestFlag7C;
		// GLOBAL: ENGINE 0x1131697D
		bool gRequestFlag7D;
		// GLOBAL: ENGINE 0x11316980
		int gRequestArg80;
		// GLOBAL: ENGINE 0x11316984
		const unsigned short* gRequestArg84;
		// GLOBAL: ENGINE 0x113169D4
		int gRequestUnknownD4;
		// GLOBAL: ENGINE 0x113169D9
		bool gPending;
		// GLOBAL: ENGINE 0x113169DC
		core::Fiber* gCallerFiber;
		// GLOBAL: ENGINE 0x11316710
		int gUnknown710;
		// GLOBAL: ENGINE 0x11316714
		int gUnknown714;
		// GLOBAL: ENGINE 0x1131671C
		int gDefaultResult;
		extern core::Fiber gStorageFiber;
		extern bool gAvailable;

		// FUNCTION: ENGINE 0x10874270
		bool IsIdle()
		{
			return !gPending;
		}

		// FUNCTION: ENGINE 0x10874280
		bool IsAvailable()
		{
			return gAvailable;
		}

		// FUNCTION: ENGINE 0x10874290
		void ResetResult()
		{
			gResult = gDefaultResult;
		}

		// FUNCTION: ENGINE 0x108742B0
		void Request0(int arg)
		{
			gRequestKind = 0;
			gRequestArg80 = arg;
			gPending = true;
		}

		// FUNCTION: ENGINE 0x108742D0
		// NONMATCHING: shrink-wrap (the engine saves esi in the entry block, before the test of the text), 39.1 %
#ifdef NONMATCHING
		void Request2(int arg70, int arg80, const unsigned short* text, int unknown68, int unknown710, const bool* flag7C,
			bool flag7D)
		{
			const unsigned short* saved = text;
			if (text != 0)
			{
				core::Utf16Count(text, (unsigned int*)&text);
			}
			gRequestArg70 = arg70;
			gUnknown710 = unknown710;
			gRequestUnknown68 = unknown68;
			gRequestArg80 = arg80;
			gRequestArg84 = saved;
			gRequestFlag7D = flag7D;
			gRequestFlag7C = *flag7C;
			gRequestKind = 2;
			gPending = true;
		}
#endif

		// FUNCTION: ENGINE 0x10874340
		void Request1(int arg74, int arg80, bool flag7D, int unknownD4)
		{
			gRequestArg74 = arg74;
			gRequestFlag7D = flag7D;
			gRequestUnknownD4 = unknownD4;
			gRequestKind = 1;
			gRequestArg80 = arg80;
			gPending = true;
		}

		// FUNCTION: ENGINE 0x10874380
		void Request3(int arg)
		{
			gRequestKind = 3;
			gRequestArg80 = arg;
			gPending = true;
		}

		// FUNCTION: ENGINE 0x108743A0
		void Request4(int arg80, int unknown714)
		{
			gUnknown714 = unknown714;
			gRequestKind = 4;
			gRequestArg80 = arg80;
			gPending = true;
		}

		// FUNCTION: ENGINE 0x10874400
		void Request5(int arg74, int arg80)
		{
			gRequestArg74 = arg74;
			gRequestArg80 = arg80;
			gRequestKind = 5;
			gPending = true;
		}

		// FUNCTION: ENGINE 0x108743D0
		void Request6(int arg70, int arg80, bool flag7D)
		{
			gRequestArg70 = arg70;
			gRequestArg80 = arg80;
			gRequestFlag7D = flag7D;
			gRequestKind = 6;
			gPending = true;
		}

		// FUNCTION: ENGINE 0x10874430
		void Request7(int arg)
		{
			gRequestKind = 7;
			gRequestArg80 = arg;
			gPending = true;
		}

		// FUNCTION: ENGINE 0x108747B0
		void CreateState(int heap)
		{
			gState = new (heap) StorageGameState;
			AddGameState(gState, 4, 0x14, 0, 0, 0);
		}

		// GLOBAL: ENGINE 0x113169D0
		// the drive the profile and the saved games live on (name guess)
		core::IDrive* gDrive;
		// GLOBAL: ENGINE 0x113169D8
		// whether the storage fiber and the state exist (name guess)
		bool gStarted;

		// 0x108E24D0 (another unit): destroys the object the storage services keep (name guess)
		void Unknown108E24D0();

		// FUNCTION: ENGINE 0x108747A0
		void CloseDrive()
		{
			gDrive->Release();
		}

		// FUNCTION: ENGINE 0x10874830
		void Shutdown()
		{
			FreeGameState(4);
			delete gState;
			Unknown108E24D0();
			CloseDrive();
			core::DestroyFiber(&gStorageFiber);
			gStarted = false;
		}

		// GLOBAL: ENGINE 0x1131697E
		// what the drive is asked about when it is asked whether a file of some size can be made (name guess)
		short gRequestWord7E;

		// 0x108E2D10 (another unit): shows the message of the text to the player and answers the button pressed (names guessed)
		int ShowMessage(const char* title, const char* text, int buttons, core::Fiber* fiber, void* extra);

		// Whether a file of that many bytes can be made on the drive (always, for none); when it cannot, the request fails and
		// the player is told why. The size is passed in eax: the function is the unit's own.
		// FUNCTION: ENGINE 0x10874490
		// NONMATCHING: the engine lays the shared tail out behind the first case, ours behind the last (80.9 %)
#ifdef NONMATCHING
		static bool CheckSpace(int size, const char* title, bool showMessage)
		{
			if (size == 0)
			{
				return true;
			}
			int result;
			gDrive->CanCreateFile((int)&gRequestWord7E, size, &result);
			while (!gDrive->IsIdle())
			{
				core::SwitchFiber(gCallerFiber);
			}
			const char* text;
			switch (result)
			{
			case 0:
				return true;
			default:
				text = "$GeneralFailure";
				break;
			case 7:
				text = "$NoFreeSpace";
				break;
			case 0xE:
				text = "$MemoryQuotaExceeded";
				break;
			case 0x11:
				text = "$NoFreeFiles";
				break;
			case 0x12:
				text = "$FileQuotaExceeded";
			}
			gResult = gDefaultResult;
			if (showMessage)
			{
				ShowMessage(title, text, 1, gCallerFiber, 0);
			}
			return false;
		}

		// FUNCTION: ENGINE 0x10874880
		// NONMATCHING: calls CheckSpace
		bool Unknown10874880()
		{
			return CheckSpace(0, "$ProfileLoad", true);
		}
#endif

		// FUNCTION: ENGINE 0x108741B0
		void RequestState()
		{
			RequestGameState(4, 2, 0);
		}

		// FUNCTION: ENGINE 0x108741C0
		void RequestStateOverlay()
		{
			if (gState->busy)
			{
				RequestGameStateOverlay(4, 2, 0);
			}
		}

		// FUNCTION: ENGINE 0x10874800
		void FreeState()
		{
			FreeGameState(4);
			delete gState;
		}
	}

	// Lets the storage fiber work on the pending request (the engine's name for it is not known)
	// FUNCTION: ENGINE 0x10874250
	void Unknown10874250()
	{
		if (StorageManager::gPending)
		{
			StorageManager::gCallerFiber = core::GetCurrentFiber();
			core::SwitchFiber(&StorageManager::gStorageFiber);
		}
	}
}
