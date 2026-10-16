// The proto game's start-up: the heap table the game runs on and the stream slot groups the loader fills. No assert
// path names the unit, so the file name and every function name here are guesses (the frontend object it builds is
// called "protomain").
#include "code/core/strings.h"
#include "code/engine/frontend/frontend.h"
#include "code/engine/system/enginememory.h"

namespace engine
{
	namespace render
	{
		// 0x1128186A (drawableimpl.h): passed to the texture uploader
		extern bool gTextureLoadFlag;
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x104E1ED0
	void CreateGameHeaps()
	{
		if (!engine::HasCommandLineOption("DesyncHunt"))
		{
			engine::HasCommandLineOption("DesyncHunt2");
		}
		engine::CreateHeap(0x0B, 0x5000000, 0, "Sound", 0x100, 2, false, -1, false);
		engine::CreateHeap(0xB5, 0x28000, 0, "FreeRoamEvents Heap", 0x100, 2, false, -1, false);
		engine::CreateHeap(0x0A, 0x600000, 0, "Effects", 0, 2, false, -1, false);
		engine::CreateHeap(0x7A, 0x500000, 0, "Script", 0x100, 1, false, -1, false);
		if (!engine::HasCommandLineOption("BatchMode"))
		{
			if (!engine::HasCommandLineOption("ExportSchema"))
			{
				if (!engine::HasCommandLineOption("ExportHelpFile"))
				{
					engine::CreateHeap(1, 0x200000, 0, "Temporary", 0x100, 2, false, -1, false);
					engine::CreateHeap(0x78, 0x80000, 0, "Cement Files", 0x100, 2, false, -1, false);
					engine::CreateHeap(0x80, 0x40000, 0, "GameDB Heap", 0x100, 1, false, -1, false);
					engine::CreateHeap(0x6F, 0xA00000, 0, "Debug", 0, 2, false, -1, false);
					engine::CreateHeap(0x0C, 0x100000, 0, "Stream Information", 0, 2, false, -1, false);
					engine::HeapConfig2 config;
					config.index = 0xAF;
					config.size = 0x600000;
					config.heap = 0x6F;
					config.name = "Name Strings";
					config.alignment = 8;
					engine::CreateHeap(config);
					core::SetStringHeap(0xAF);
					engine::CreateHeap(0x76, 0x1900000, 0x1000, "Render", 0, 2, false, -1, false);
					engine::CreateHeap(0x72, 0x740000, 0x20, "Front End", 0, 2, false, -1, false);
					engine::CreateHeap(0x86, 0x300000, 0x1000, "Advertisements", 0, 2, false, -1, false);
					engine::CreateHeap(0x74, 0x50000, 0, "Static Fight", 0, 2, false, -1, false);
					engine::CreateHeap(0x75, 0x32C000, 0, "Dynamic Fight", 0, 2, false, -1, false);
					engine::CreateHeap(0xB9, 0x120000, 0, "Devastator", 0, 2, false, -1, false);
					engine::CreateHeap(0x77, 0xBB800, 0, "Decals", 0, 2, false, -1, false);
					engine::CreateHeap(0x85, 0x700000, 0, "Physics", 0, 2, false, -1, false);
					engine::CreateHeap(0x9C, 0x28800, 0, "Triggers", 0, 2, false, -1, false);
					engine::CreateHeap(0xA6, 0x90000, 0, "MissionDynamic", 0, 2, false, -1, false);
					engine::CreateHeap(0xA1, 0x100000, 0, "PedInstance", 0, 2, false, -1, false);
					engine::CreateHeap(0xA2, 0xD0000, 0, "PedDrawables", 0, 2, false, -1, false);
					engine::CreateHeap(0xA4, 0x500000, 0, "PropInstance", 0, 2, false, -1, false);
					engine::CreateHeap(0xA9, 0x550000, 0, "VehicleInstance", 0, 2, false, -1, false);
					engine::CreateHeap(0xA8, 0x110000, 0, "AmbientManager", 0, 2, false, -1, false);
					engine::CreateHeap(0x70, 0x60000, 0, "MainCharacter", 0, 2, false, -1, false);
					engine::CreateHeap(0x9E, 0x580800, 0, "Characters", 0, 2, false, -1, false);
					engine::CreateHeap(0xA0, 0x200000, 0, "DeadBody", 0, 2, false, -1, false);
					engine::CreateHeap(0x9F, 0xC0000, 0, "Consume", 0, 2, false, -1, false);
					engine::CreateHeap(0xB2, 0x40000, 0, "BlobShadows", 0x76, 2, false, -1, false);
					engine::CreateHeap(0xB4, 0x144000, 0, "Checkpoints", 0, 2, false, -1, false);
					engine::CreateHeap(0xB7, 0x30000, 0, "CollectibleInstance", 0, 2, false, -1, false);
					engine::CreateHeap(0xB6, 0x90000, 0, "AI", 0, 1, false, -1, false);
					engine::CreateHeap(0xB8, 0xE0000, 0, "Gameobject System", 0, 2, false, -1, false);
				}
			}
		}
		if (engine::HasCommandLineOption("SkipTopLevelMipMap"))
		{
			engine::render::gTextureLoadFlag = true;
		}
	}
}
