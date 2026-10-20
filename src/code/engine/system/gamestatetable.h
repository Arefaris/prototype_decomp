// The table of the game states, the requests that switch between them and the per-frame update of that machine
// (gamestate.cpp, unit 0x108366C0 - 0x108391C0). The classes are the RTTI ones (engine::GameStateRequest, derived from
// engine::SyncCommands::SyncCallback); the layouts follow the code and every other name is a guess.
#ifndef ENGINE_SYSTEM_GAMESTATETABLE_H
#define ENGINE_SYSTEM_GAMESTATETABLE_H

#include "code/container/string.h"
#include "code/core/time.h"
#include "code/engine/gamestate.h"
#include "code/engine/system/simulationdriver.h"

namespace engine
{
	// The callback of the requests (engine::SyncCommands::SyncCallback, one pure slot)
	class SyncCommands
	{
	public:
		class SyncCallback
		{
		public:
			// A state request was carried out (or, with aborted, dropped)
			virtual void OnFinished(int state, bool aborted) = 0;
		};
	};

	// A request to enter a state (the requests wait in a list while another one is carried out)
	class GameStateRequest : public SyncCommands::SyncCallback
	{
	public:
		// 0x108371E0: leaves the mode and the last flag alone
		GameStateRequest() : state(0), callback(0), started(false), unknownD(false), aborted(false)
		{
		}
		// 0x10837950 / 0x10837520 (the vector's functions inline them)
		GameStateRequest(const GameStateRequest& other)
		{
			state = other.state;
			callback = other.callback;
			started = other.started;
			unknownD = other.unknownD;
			aborted = other.aborted;
			mode = other.mode;
			overlay = other.overlay;
		}
		GameStateRequest& operator=(const GameStateRequest& other)
		{
			state = other.state;
			callback = other.callback;
			started = other.started;
			unknownD = other.unknownD;
			aborted = other.aborted;
			mode = other.mode;
			overlay = other.overlay;
			return *this;
		}
		// 0x108390F0: the request the machine works on is over
		virtual void OnFinished(int newState, bool wasAborted);

		int state;                           // +4
		SyncCommands::SyncCallback* callback;   // +8
		bool started;                        // +0xC
		bool unknownD;                       // +0xD
		bool aborted;                        // +0xE
		int mode;                            // +0x10: 0 enter, 1 replace, 2 return to
		bool overlay;                        // +0x14
	};

	// The ids of the messages the machine sends to the online layer
	extern unsigned int gMessageEnter;       // 0x111C6428
	extern unsigned int gMessageReplace;     // 0x111C642C
	extern unsigned int gMessageLeave;       // 0x111C6430
	extern unsigned int gMessageReturn;      // 0x111C6434

	// What the table keeps about a state (0x20 bytes)
	struct GameStateEntry
	{
		GameStateEntry(GameState* newState, int newId, int newPriority, int newFlag, int newMode, int newParent) :
			state(newState), id(newId), priority(newPriority), flag(newFlag), mode(newMode), parent(newParent)
		{
		}

		GameState* state;                    // +0
		int id;                              // +4
		int priority;                        // +8
		int flag;                            // +0xC
		int mode;                            // +0x10
		int parent;                          // +0x14
		unsigned int savedFlags;             // +0x18
		unsigned int flagMask;               // +0x1C
	};

	// A name for a request's state (0x28 bytes)
	struct GameStateName
	{
		int state;
		container::StringC<32> name;
	};

	// The tasks the machine calls every frame (engine::IRealTimeTask, engine::ISimulationTask), by priority
	struct TaskEntry
	{
		IRealTimeTask* task;
		unsigned int mask;
		int priority;
		unsigned int data;
	};
	struct SimulationTaskEntry
	{
		IRealTimeTask* task;
		unsigned int mask;
		int priority;
		unsigned int data;
	};
}

#endif
