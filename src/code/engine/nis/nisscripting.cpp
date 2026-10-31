// The non-interactive sequence player's start-up and shutdown and its Lua natives (nis_Load, nis_Play, nis_Stop,
// nis_Unload), which send a message to the sequence they name. The file name is a guess (the natives follow the
// scene classes of nis.cpp in the binary).
#include "code/engine/function.h"
#include "code/engine/nismessages.h"
#include "code/engine/gameobject/messagerouter.h"

namespace engine
{
	class MessageListeners;
	void SendMessage(Message* message, MessageListeners* listeners);

	// 0x108C76B0 / 0x108C7100 (another unit): makes the game state of the sequences with the id and priority, and
	// takes it down again (names guessed)
	void CreateNISGameState(int id, int priority);
	void DestroyNISGameState();

	// 0x11316F60: the listeners of the sequence messages; 0x11316F10: the owner the natives are registered under
	MessageListeners gNISListeners("NIS Player", 0);
	extern unsigned char gNISScriptOwner;

	// FUNCTION: ENGINE 0x1088C200
	void LoadNIS(const char* name)
	{
		core::Name<core::CaseSensitiveKey> sequence(name, 1);
		NISMessage message(0, sequence);
		SendMessage(&message, &gNISListeners);
	}

	// FUNCTION: ENGINE 0x1088C250
	// EQUIVALENT: ours also stores the vftable of NISMessage before the name is copied, which the play message's own
	// vftable overwrites afterwards (a dead store), 67 %
	void PlayNIS(const char* name)
	{
		core::Name<core::CaseSensitiveKey> sequence(name, 1);
		NISPlayMessage message(sequence);
		SendMessage(&message, &gNISListeners);
	}

	// FUNCTION: ENGINE 0x1088C2B0
	void StopNIS(const char* name)
	{
		core::Name<core::CaseSensitiveKey> sequence(name, 1);
		NISMessage message(5, sequence);
		SendMessage(&message, &gNISListeners);
	}

	// FUNCTION: ENGINE 0x1088C310
	void UnloadNIS(const char* name)
	{
		core::Name<core::CaseSensitiveKey> sequence(name, 1);
		NISMessage message(8, sequence);
		SendMessage(&message, &gNISListeners);
	}

	// FUNCTION: ENGINE 0x1088B920
	void ShutdownNIS()
	{
		LuaScriptManager* script = GetScriptManager();
		script->Unregister(&gNISScriptOwner);
		DestroyNISGameState();
	}

	// FUNCTION: ENGINE 0x1088F050
	void InitNIS()
	{
		CreateNISGameState(10, 0);
		LuaScriptManager* script = GetScriptManager();
		script->SetOwner(&gNISScriptOwner);
		script->Register("nis_Load", LoadNIS);
		script->Register("nis_Play", PlayNIS);
		script->Register("nis_Stop", StopNIS);
		script->Register("nis_Unload", UnloadNIS);
		script->ClearOwner();
	}
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D773A0
// FUNCTION: ENGINE 0x10D8A9C0
