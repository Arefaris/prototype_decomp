// The world stream manager (RTTI: engine::WorldStreamManager, base StreamClient, 0x54 bytes): the stream client that
// takes the world cells' packages (the tags "WorldCell", "WorldCellSim", "WorldCellRender", "Detail" and "WorldAZone")
// and hands every package instance that loads or unloads to the location it holds. Unit 0x108540E0 - 0x108551xx (no
// assert path; file name guessed). Names other than the RTTI one are guesses.
#ifndef ENGINE_SYSTEM_WORLDSTREAMMANAGER_H
#define ENGINE_SYSTEM_WORLDSTREAMMANAGER_H

#include "code/engine/system/streampackage.h"

namespace engine
{
	namespace world
	{
		class Location;
	}

	class WorldStreamManager : public StreamClient
	{
	public:
		// What the manager is made with: three words and the functions it calls after a package instance loaded / before
		// one unloads (the words are kept at +0x40 - +0x48)
		struct Config
		{
			int unknown0;
			int unknown4;
			int unknown8;
			void (*onLoaded)(StreamPackageInstance* instance);
			void (*onUnloading)(StreamPackageInstance* instance);
		};

		// 0x108540F0
		explicit WorldStreamManager(const Config* config);
		// 0x10854400 (the deleting destructor is 0x108547F0)
		virtual ~WorldStreamManager();
		// vftable slot 1 (0x10854190): the location gets the instance, then the function is called; true
		virtual bool Load(StreamPackageInstance* instance);
		// vftable slot 2 (0x108541C0): the function is called, then the location gets the instance; true
		virtual bool Unload(StreamPackageInstance* instance);

		// 0x10854150: lets go of the location and leaves the stream manager
		void Reset();

		char locationName[0x20];  // +0x1C
		world::Location* location;  // +0x3C
		int unknown40;
		int unknown44;
		int unknown48;
		void (*onLoaded)(StreamPackageInstance* instance);  // +0x4C
		void (*onUnloading)(StreamPackageInstance* instance);  // +0x50
	};

	// 0x108540E0 / 0x108543B0: the manager (0x11315398) and its making in the heap 12
	WorldStreamManager* GetWorldStreamManager();
	void CreateWorldStreamManager(const WorldStreamManager::Config* config);
}

#endif
