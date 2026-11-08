// proto::SaveGameManager (RTTI; base engine::GameDataBaseClient): the object that saves and loads the game and its
// checkpoints and registers the sgm_* natives with the script context. The class is created by CreateSaveGameManager
// (0x10487D10) into the global 0x1126B474. Unit 0x1047FEE0 - 0x10488BD0 (no assert path; the file names are guesses).
// Only what the reconstructed functions touch is laid out.
#ifndef PROTO_SAVEGAMEMANAGER_H
#define PROTO_SAVEGAMEMANAGER_H

namespace engine
{
	class LuaGOH;
}

namespace engine
{
	// RTTI engine::GameDataBaseClient (vftable 0x10E095F4, 5 slots at 0x1047F940 - 0x1047F980; the game database is told
	// about it with SetStorageListener): what the game database tells about the storage. The slot names are guesses.
	class GameDataBaseClient
	{
	public:
		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3(bool result);
		virtual void Slot4(bool result);
	};
}

namespace proto
{
	class SaveGameManager : public engine::GameDataBaseClient
	{
	public:
		// The overrides of the base class's slots: 0x1047FEE0, 0x1047FEF0 and 0x1047FF00 (other ranges), 0x10480000 and
		// 0x10480020; the destructor is the last slot (deleting destructor 0x10487D70)
		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3(bool result);
		virtual void Slot4(bool result);
		virtual ~SaveGameManager();

		// The members the script natives bind (sgm_*): their addresses are 0x1047FB60 - 0x10482320
		// 0x10480040 (sgm_IsActive) / 0x10480050 (sgm_GetLastResult)
		bool IsActive();
		bool GetLastResult();
		// 0x10480060: takes the natives out of the script context again
		void UnregisterScript();
		void Save();
		void Method2(const char* newSlot, int newMode);
		bool IsStoryComplete(int newStory);
		void SaveCheckpoint(bool first, bool second);
		bool IsCheckpointAvailable();
		int ConvertGOHToIndex(engine::LuaGOH object);
		engine::LuaGOH ConvertIndexToGOH(int index);

		// Only the first words of the layout are known
		int state;  // +0x4: the state machine's state (0: idle)
		bool lastResult;  // +0x8
		bool unknown9;
		bool succeeded;  // +0xA
	};
}

#endif
