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

namespace proto
{
	class SaveGameManager
	{
	public:
		// The members the script natives bind (sgm_*): their addresses are 0x1047FB60 - 0x10482320
		void Save();
		void Method2(const char* newSlot, int newMode);
		bool IsStoryComplete(int newStory);
		void SaveCheckpoint(bool first, bool second);
		bool IsCheckpointAvailable();
		int ConvertGOHToIndex(engine::LuaGOH object);
		engine::LuaGOH ConvertIndexToGOH(int index);
	};
}

#endif
