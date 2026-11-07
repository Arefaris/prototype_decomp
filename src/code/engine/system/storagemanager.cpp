// engine::StorageManager::StorageGameState (RTTI name): the game state the storage services (the profile and the saved
// games) run in while they wait for the console's storage; the unit is the part of the storage manager around
// 0x108741E0 - 0x10874880 (no assert path, the file name is a guess).
#include "code/engine/gamestate.h"

// 0x107DEF90: the allocation from the heap the second argument names
void* operator new(unsigned int size, int heap);

namespace engine
{
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

		// FUNCTION: ENGINE 0x108747B0
		void CreateState(int heap)
		{
			gState = new (heap) StorageGameState;
			AddGameState(gState, 4, 0x14, 0, 0, 0);
		}

		// FUNCTION: ENGINE 0x10874800
		void FreeState()
		{
			FreeGameState(4);
			delete gState;
		}
	}
}
