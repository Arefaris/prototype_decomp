// engine::Replay (RTTI name; the desync replay: records the inputs of a session or plays a recording back through
// ReplaySimDriver) and engine::ReplaySimDriver (RTTI name; another unit, only the members the replay reaches are
// described). The replay is a simulation task, a real time task and a game state at once, and has the script functions
// Replay_Resume, Replay_Reset, Replay_Record, Replay_RecordDesync, Replay_Replay, Replay_ReplayDesync and Replay_Quit.
// The unit is 0x108C27A0 - 0x108C2F60; no assert path names it, so the file name is a guess. Names other than the RTTI
// and script names are guesses.
#ifndef ENGINE_ONLINE_REPLAY_H
#define ENGINE_ONLINE_REPLAY_H

#include "code/engine/gamestate.h"
#include "code/engine/online/onlinemanager.h"
#include "code/engine/system/simulationdriver.h"

namespace engine
{
	// The driver that records and plays back (0xB4 bytes; the RTTI says ISimulationDriver, SimulationDriverTimeData)
	class ReplaySimDriver : public ISimulationDriver
	{
	public:
		// 0x10900260
		ReplaySimDriver();

		// 0x108C27E0 / 0x108C27F0 / 0x108C2800 / 0x108C2810 / 0x108C2820
		bool HasRecording() const
		{
			return recording != 0;
		}
		bool GetPlaybackFlagA4() const
		{
			return playbackFlagA4;
		}
		bool GetPlaybackFlagA5() const
		{
			return playbackFlagA5;
		}
		void SetFlagA6(bool value)
		{
			flagA6 = value;
		}
		bool GetFlagA9() const
		{
			return flagA9;
		}

		// 0x10900450 / 0x10900480: forwarded by the replay
		void Unknown10900450();
		void Unknown10900480();
		// 0x109004B0: whether the recording of the file has the entries (names guessed)
		bool Query(const char* file, int first, int second);
		// 0x10900D40: stops what is going on
		void Stop();
		// 0x10900960: starts the recording or the playback of the file
		void Start(int mode, bool desync, const char* file);

		// The driver's slots (another unit)
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual bool Slot4();
		virtual void Slot5();

		int unknown70[8];
		int recording;  // +0x90
		int unknown94;
		int unknown98;
		int unknown9C;
		int unknownA0;
		bool playbackFlagA4;
		bool playbackFlagA5;
		bool flagA6;
		bool unknownA7;
		bool unknownA8;
		bool flagA9;
		int unknownAC;
		int unknownB0;
	};

	// The tasks the replay registers itself as (the base of the simulation tasks; one virtual function)
	struct ISimulationTask
	{
		virtual void UpdateSimulation(UpdateContext context) = 0;
	};

	// The modes the replay is in
	enum ReplayMode
	{
		REPLAY_OFF,
		REPLAY_RECORD,
		REPLAY_UNKNOWN2,
		REPLAY_PLAYBACK
	};

	class Replay : public ISimulationTask, public IRealTimeTask, public GameState
	{
	public:
		// 0x108C2D30: registers the script functions and the real time task
		Replay();
		// 0x108C2E70
		~Replay();
		// 0x108C27A0 / 0x108C27C0
		static void* operator new(unsigned int size)
		{
			return AllocateManagerObject(size, 0, "Engine::Desync::Replay");
		}
		static void operator delete(void* block)
		{
			FreeManagerObject(block);
		}

		// vftable slot of the simulation task (0x108C2900) and of the real time task (0x108C2C40: pauses the game
		// when a playback has ended)
		virtual void UpdateSimulation(UpdateContext context);
		virtual void Update(UpdateContext context);
		// the game state's slots (0x108C2910 / 0x108C2930)
		virtual void Enter();
		virtual void Leave();

		// 0x108C2830: the state the replay runs in
		void SetState(int id, int priority, int leaveState);
		// 0x108C2860 / 0x108C2870
		void Unknown108C2860();
		void Unknown108C2870();
		// 0x108C2880 / 0x108C28A0: the file of the recording
		void SetFileName(const char* newName);
		const char* GetFileName();
		// 0x108C28B0: whether the file has the entries (not while the replay is off or recording)
		bool Query(int first, int second);
		// 0x108C28E0: sets the mode and what the driver does in it
		void SetMode(int newMode, bool newDesync);
		// 0x108C2940: asks for the replay's state
		void RequestState();
		// 0x108C2960: starts the driver in the mode
		void StartDriver();
		// 0x108C29A0
		void SetDriverFlagA6();
		// 0x108C29B0: back to off
		void Stop();
		// 0x108C29C0 / 0x108C29E0 / 0x108C2A00 / 0x108C2A30
		bool GetPlaybackFlagA5();
		bool GetPlaybackFlagA4();
		bool HasRecording();
		bool GetFlagA9();
		// The script functions (0x108C2A40, 0x108C2A70, 0x108C2AA0, 0x108C2AD0, 0x108C2B00, 0x108C2B30, 0x108C2B60)
		void Resume();
		void Reset();
		void Record();
		void RecordDesync();
		void Play();
		void PlayDesync();
		void Quit();

		ReplaySimDriver* driver;  // +0x5C
		int unknown60;
		int mode;  // +0x64
		bool desync;  // +0x68
		int stateId;  // +0x6C
		int leaveState;  // +0x70
		char fileName[0x100];  // +0x74
		int unknown174;
	};

	// 0x113187D0: the one replay
	extern Replay* gReplay;
	// 0x108C27D0 / 0x108C2ED0 / 0x108C2F30
	void SetReplay(Replay* replay);
	void CreateReplay();
	void DestroyReplay();
}

#endif
