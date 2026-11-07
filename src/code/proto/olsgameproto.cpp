#include "code/proto/olsgameproto.h"

#include "code/engine/database/gamedatabase.h"
#include "code/core/name.h"

namespace engine
{
	namespace render
	{
		extern bool gTextureLoadFlag;
	}
}

namespace proto
{
	// 0x1126E538 (midgroundmanager.cpp)
	extern core::Name<core::CaseSensitiveKey> gLevelNameKey;
	// 0x1109D074: the difficulty names and the dev select group (the first is the default)
	extern const char* gDifficultyNames[];
	// 0x104DEEC0 / 0x104DEFC0 / 0x104DEFF0
	void StartDevSelectLevel(const char* name, int flag, const char* group);
	void FinishDevSelectStart();
	void SetGameDatabaseMode(int mode);

	// FUNCTION: ENGINE 0x104DC5D0
	OLSGameProto::OLSGameProto(int newState) : engine::OLSGame(newState)
	{
	}

	// FUNCTION: ENGINE 0x104DC610
	void OLSGameProto::Slot4()
	{
		const char* level = engine::gGameDatabase->GetString(gLevelNameKey, 0, 0);
		StartDevSelectLevel(level, 1, gDifficultyNames[0]);
		FinishDevSelectStart();
		engine::OLSGame::Slot4();
	}

	// FUNCTION: ENGINE 0x104DC660
	void OLSGameProto::Slot6()
	{
		engine::OLSGame::Slot6();
	}

	// FUNCTION: ENGINE 0x104DC670
	void OLSGameProto::Slot7()
	{
		engine::OLSGame::Slot7();
		SetGameDatabaseMode(1);
		savedTextureLoadFlag = engine::render::gTextureLoadFlag;
		engine::render::gTextureLoadFlag = true;
	}

	// FUNCTION: ENGINE 0x104DC6A0
	void OLSGameProto::Slot8()
	{
		engine::render::gTextureLoadFlag = savedTextureLoadFlag;
		SetGameDatabaseMode(0);
		engine::OLSGame::Slot8();
	}

	// FUNCTION: ENGINE 0x104DC700
	OLSGameSystemLinkProto::OLSGameSystemLinkProto(int newState) : engine::OLSGameSystemLink(newState)
	{
	}

	// FUNCTION: ENGINE 0x104DC740
	void OLSGameSystemLinkProto::Slot4()
	{
		const char* level = engine::gGameDatabase->GetString(gLevelNameKey, 0, 0);
		StartDevSelectLevel(level, 1, gDifficultyNames[0]);
		FinishDevSelectStart();
		engine::OLSGameSystemLink::Slot4();
	}

	// FUNCTION: ENGINE 0x104DC790
	void OLSGameSystemLinkProto::Slot6()
	{
		engine::OLSGame::Slot6();
	}

	// FUNCTION: ENGINE 0x104DC7A0
	void OLSGameSystemLinkProto::Slot7()
	{
		engine::OLSGameSystemLink::Slot7();
		SetGameDatabaseMode(1);
		savedTextureLoadFlag = engine::render::gTextureLoadFlag;
		engine::render::gTextureLoadFlag = true;
	}

	// FUNCTION: ENGINE 0x104DC7D0
	void OLSGameSystemLinkProto::Slot8()
	{
		engine::render::gTextureLoadFlag = savedTextureLoadFlag;
		SetGameDatabaseMode(0);
		engine::OLSGameSystemLink::Slot8();
	}
}
