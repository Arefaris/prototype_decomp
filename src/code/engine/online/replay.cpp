// The desync replay (engine::Replay; 0x108C27A0 - 0x108C2F60).
#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/engine/function.h"
#include "code/engine/online/onlinemanager.h"
#include "code/engine/online/replay.h"
#include "code/engine/system/gamestatetable.h"

namespace engine
{
	// The game state table's functions (gamestate.cpp)
	void AddGameState(void* stateObject, int id, int priority, int flag, int mode, int parent);
	void FreeGameState(int id);
	void RequestGameState(int state, int mode, SyncCommands::SyncCallback* callback);
	int GetGameStateStatus(int id);
	void AddRealTimeTask(IRealTimeTask* task, unsigned int mask, int priority, unsigned int data);
	void RemoveRealTimeTask(IRealTimeTask* task);
	LuaScriptManager* GetScriptManager();

	// The size of the stack of the replay's state
	// GLOBAL: ENGINE 0x111DBDA0
	static int sReplayStackSize = 0x1400;

	Replay* gReplay;  // 0x113187D0

	void SetReplay(Replay* replay)
	{
		gReplay = replay;
	}

	void Replay::SetState(int id, int priority, int newLeaveState)
	{
		stateId = id;
		leaveState = newLeaveState;
		this->id = id;
		AddGameState(static_cast<GameState*>(this), id, priority, 0, 1, 0);
	}

	Replay::Replay() :
		GameState(0, sReplayStackSize),
		unknown60(0),
		mode(REPLAY_OFF),
		desync(false),
		stateId(0),
		leaveState(0),
		unknown174(0)
	{
		core::StrNCpy(fileName, "replay.log", 0x100u);
		driver = new ReplaySimDriver();
		LuaScriptManager* scripts = GetScriptManager();
		scripts->RegisterMethod("Replay_Resume", this, &Replay::Resume);
		scripts->RegisterMethod("Replay_Reset", this, &Replay::Reset);
		scripts->RegisterMethod("Replay_Record", this, &Replay::Record);
		scripts->RegisterMethod("Replay_RecordDesync", this, &Replay::RecordDesync);
		scripts->RegisterMethod("Replay_Replay", this, &Replay::Play);
		scripts->RegisterMethod("Replay_ReplayDesync", this, &Replay::PlayDesync);
		scripts->RegisterMethod("Replay_Quit", this, &Replay::Quit);
		AddRealTimeTask(this, 1, 1, (unsigned int)" Replay RT Task");
	}

	Replay::~Replay()
	{
		RemoveRealTimeTask(this);
		GetScriptManager()->Unregister(this);
		if (stateId != 0)
		{
			FreeGameState(stateId);
		}
		delete driver;
		driver = 0;
	}

	void CreateReplay()
	{
		if (gReplay == 0)
		{
			gReplay = new Replay();
		}
	}

	void DestroyReplay()
	{
		if (gReplay != 0)
		{
			delete gReplay;
			gReplay = 0;
		}
	}

	void Replay::Unknown108C2860()
	{
		driver->Unknown10900450();
	}

	void Replay::Unknown108C2870()
	{
		driver->Unknown10900480();
	}

	void Replay::SetFileName(const char* newName)
	{
		core::StrNCpy(fileName, newName, 0x100u);
	}

	const char* Replay::GetFileName()
	{
		return fileName;
	}

	bool Replay::Query(int first, int second)
	{
		if (mode != REPLAY_OFF && mode != REPLAY_RECORD)
		{
			return driver->Query(fileName, first, second);
		}
		return false;
	}

	void Replay::SetMode(int newMode, bool newDesync)
	{
		driver->Stop();
		mode = newMode;
		desync = newDesync;
	}

	void Replay::UpdateSimulation(int a, int b, float time)
	{
	}

	// FUNCTION: ENGINE 0x108C2C40
	// EQUIVALENT: the engine pushes the -1 of the pause state's call from a register (or ecx, -1) instead of an immediate (62.0 %)
	void Replay::Update(int a, int b, float time)
	{
		// A local the engine keeps on the stack and never reads
		volatile int unused = 0;
		if (GetPlaybackFlagA5())
		{
			if (GetGameStateStatus(1) == 1)
			{
				PauseState::GetCurrent()->Slot2(-1);
			}
		}
		if (unknown174 == 0)
		{
			unknown174 = 0;
		}
	}

	void Replay::Enter()
	{
		RequestGameState(leaveState, 0, 0);
	}

	void Replay::Leave()
	{
		unknown60 = 0;
	}

	void Replay::RequestState()
	{
		RequestGameState(stateId, 1, 0);
		unknown60 = 1;
	}

	void Replay::StartDriver()
	{
		core::HeapScope scope(1);
		if (mode != REPLAY_OFF)
		{
			driver->Start(mode, desync, fileName);
		}
	}

	void Replay::SetDriverFlagA6()
	{
		driver->SetFlagA6(true);
	}

	void Replay::Stop()
	{
		SetMode(REPLAY_OFF, false);
	}

	bool Replay::GetPlaybackFlagA5()
	{
		if (mode == REPLAY_PLAYBACK || mode == REPLAY_UNKNOWN2)
		{
			return driver->GetPlaybackFlagA5();
		}
		return false;
	}

	bool Replay::GetPlaybackFlagA4()
	{
		if (mode == REPLAY_PLAYBACK)
		{
			return driver->GetPlaybackFlagA4();
		}
		return false;
	}

	bool Replay::HasRecording()
	{
		if (mode == REPLAY_RECORD || mode == REPLAY_UNKNOWN2)
		{
			return driver->HasRecording();
		}
		return false;
	}

	bool Replay::GetFlagA9()
	{
		return driver->GetFlagA9();
	}

	void Replay::Resume()
	{
		if (GetPlaybackFlagA5())
		{
			SetMode(REPLAY_OFF, false);
		}
		else
		{
			StartDriver();
		}
		PauseState::GetCurrent()->Slot3();
	}

	void Replay::Reset()
	{
		SetMode(REPLAY_OFF, false);
		RequestState();
		PauseState::GetCurrent()->Slot3();
	}

	void Replay::Record()
	{
		SetMode(REPLAY_RECORD, false);
		RequestState();
		PauseState::GetCurrent()->Slot3();
	}

	void Replay::RecordDesync()
	{
		SetMode(REPLAY_RECORD, true);
		RequestState();
		PauseState::GetCurrent()->Slot3();
	}

	void Replay::Play()
	{
		SetMode(REPLAY_PLAYBACK, false);
		RequestState();
		PauseState::GetCurrent()->Slot3();
	}

	void Replay::PlayDesync()
	{
		SetMode(REPLAY_PLAYBACK, true);
		RequestState();
		PauseState::GetCurrent()->Slot3();
	}

	void Replay::Quit()
	{
		Stop();
		PauseState::GetCurrent()->Slot4();
	}
}

template class Method0<engine::Replay, void>;
template class Closure0<engine::Replay, void>;
template void engine::LuaScriptManager::RegisterMethod<engine::Replay, void>(const char*, engine::Replay*,
	void (engine::Replay::*)());

// ---- annotations of the functions mapped in symbols.txt (generated) ----

// FUNCTION: ENGINE 0x108C27A0 @ void * engine::Replay::operator new(unsigned int)
// FUNCTION: ENGINE 0x108C27C0 @ void engine::Replay::operator delete(void *)
// FUNCTION: ENGINE 0x108C27D0 @ void engine::SetReplay(engine::Replay *)
// FUNCTION: ENGINE 0x108C27E0 @ bool engine::ReplaySimDriver::HasRecording(void)const 
// FUNCTION: ENGINE 0x108C27F0 @ bool engine::ReplaySimDriver::GetPlaybackFlagA4(void)const 
// FUNCTION: ENGINE 0x108C2800 @ bool engine::ReplaySimDriver::GetPlaybackFlagA5(void)const 
// FUNCTION: ENGINE 0x108C2810 @ void engine::ReplaySimDriver::SetFlagA6(bool)
// FUNCTION: ENGINE 0x108C2820 @ bool engine::ReplaySimDriver::GetFlagA9(void)const 
// FUNCTION: ENGINE 0x108C2830 @ void engine::Replay::SetState(int,int,int)
// FUNCTION: ENGINE 0x108C2860 @ void engine::Replay::Unknown108C2860(void)
// FUNCTION: ENGINE 0x108C2870 @ void engine::Replay::Unknown108C2870(void)
// FUNCTION: ENGINE 0x108C2880 @ void engine::Replay::SetFileName(char const *)
// FUNCTION: ENGINE 0x108C28A0 @ char const * engine::Replay::GetFileName(void)
// FUNCTION: ENGINE 0x108C28B0 @ bool engine::Replay::Query(int,int)
// FUNCTION: ENGINE 0x108C28E0 @ void engine::Replay::SetMode(int,bool)
// FUNCTION: ENGINE 0x108C2900 @ void engine::Replay::UpdateSimulation(int,int,float)
// FUNCTION: ENGINE 0x108C2910 @ void engine::Replay::Enter(void)
// FUNCTION: ENGINE 0x108C2930 @ void engine::Replay::Leave(void)
// FUNCTION: ENGINE 0x108C2940 @ void engine::Replay::RequestState(void)
// FUNCTION: ENGINE 0x108C2960 @ void engine::Replay::StartDriver(void)
// FUNCTION: ENGINE 0x108C29A0 @ void engine::Replay::SetDriverFlagA6(void)
// FUNCTION: ENGINE 0x108C29B0 @ void engine::Replay::Stop(void)
// FUNCTION: ENGINE 0x108C29C0 @ bool engine::Replay::GetPlaybackFlagA5(void)
// FUNCTION: ENGINE 0x108C29E0 @ bool engine::Replay::GetPlaybackFlagA4(void)
// FUNCTION: ENGINE 0x108C2A00 @ bool engine::Replay::HasRecording(void)
// FUNCTION: ENGINE 0x108C2A30 @ bool engine::Replay::GetFlagA9(void)
// FUNCTION: ENGINE 0x108C2A40 @ void engine::Replay::Resume(void)
// FUNCTION: ENGINE 0x108C2A70 @ void engine::Replay::Reset(void)
// FUNCTION: ENGINE 0x108C2AA0 @ void engine::Replay::Record(void)
// FUNCTION: ENGINE 0x108C2AD0 @ void engine::Replay::RecordDesync(void)
// FUNCTION: ENGINE 0x108C2B00 @ void engine::Replay::Play(void)
// FUNCTION: ENGINE 0x108C2B30 @ void engine::Replay::PlayDesync(void)
// FUNCTION: ENGINE 0x108C2B60 @ void engine::Replay::Quit(void)
// FUNCTION: ENGINE 0x108C2B80 @ Method0<engine::Replay,void>::Method0<engine::Replay,void>(char const *,void (engine::Replay::*)())
// FUNCTION: ENGINE 0x108C2BC0 @ Method0<Replay, void>::Call
// FUNCTION: ENGINE 0x108C2BD0 @ Closure0<engine::Replay,void>::Closure0<engine::Replay,void>(char const *,engine::Replay *,void (engine::Replay::*)())
// FUNCTION: ENGINE 0x108C2C20 @ void Method0<engine::Replay,void>::Invoke(void *,union engine::FunctionArgument const *,void *)
// FUNCTION: ENGINE 0x108C2CA0 @ void engine::LuaScriptManager::RegisterMethod<engine::Replay,void>(char const *,engine::Replay *,void (engine::Replay::*)())
// FUNCTION: ENGINE 0x108C2D20 @ void Closure0<engine::Replay,void>::Invoke(void *,union engine::FunctionArgument const *,void *)
// FUNCTION: ENGINE 0x108C2D30 @ engine::Replay::Replay(void)
// FUNCTION: ENGINE 0x108C2E70 @ engine::Replay::~Replay(void)
// FUNCTION: ENGINE 0x108C2ED0 @ void engine::CreateReplay(void)
// FUNCTION: ENGINE 0x108C2F10 @ void * engine::Replay::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108C2F30 @ void engine::DestroyReplay(void)
