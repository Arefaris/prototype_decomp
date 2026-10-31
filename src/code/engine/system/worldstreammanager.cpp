// The world stream manager (RTTI: engine::WorldStreamManager, a StreamClient that streams the world cells; unit
// 0x108540E0 - 0x108551xx, no assert path, file name guessed). Of the unit the class's lifetime and its two slots.
#include "code/core/heap.h"
#include "code/engine/world/location.h"
#include "code/engine/system/worldstreammanager.h"

namespace engine
{
	// The manager (made by the world's start-up)
	WorldStreamManager* gWorldStreamManager;
	// Whether the manager is registered with the stream manager as a client
	bool gWorldStreamRegistered;

	// FUNCTION: ENGINE 0x108540E0
	WorldStreamManager* GetWorldStreamManager()
	{
		return gWorldStreamManager;
	}

	// FUNCTION: ENGINE 0x108540F0
	WorldStreamManager::WorldStreamManager(const Config* config)
	{
		location = 0;
		unknown40 = config->unknown0;
		unknown44 = config->unknown4;
		unknown48 = config->unknown8;
		onLoaded = config->onLoaded;
		onUnloading = config->onUnloading;
		core::HeapScope scope(0xc);
		SetTags("WorldCell;WorldCellSim;WorldCellRender;Detail;WorldAZone");
	}

	// FUNCTION: ENGINE 0x10854400
	WorldStreamManager::~WorldStreamManager()
	{
		Reset();
	}

	// FUNCTION: ENGINE 0x10854150
	void WorldStreamManager::Reset()
	{
		if (location != 0)
		{
			location->Release();
			location = 0;
			locationName[0] = 0;
		}
		if (gWorldStreamRegistered)
		{
			StreamManager::UnregisterClient(this);
			gWorldStreamRegistered = false;
		}
	}

	// FUNCTION: ENGINE 0x10854190
	bool WorldStreamManager::Load(StreamPackageInstance* instance)
	{
		location->Unknown108D6170(instance);
		if (onLoaded != 0)
		{
			onLoaded(instance);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108541C0
	bool WorldStreamManager::Unload(StreamPackageInstance* instance)
	{
		if (onUnloading != 0)
		{
			onUnloading(instance);
		}
		location->Unknown108D61E0(instance);
		return true;
	}

	// FUNCTION: ENGINE 0x108543B0
	void CreateWorldStreamManager(const WorldStreamManager::Config* config)
	{
		core::HeapScope scope(0xc);
		gWorldStreamManager = new WorldStreamManager(config);
	}
}

// The lookup of a location by name (the filter the inventory is handed)
// FUNCTION: ENGINE 0x108547D0
template class content::LoadInventory::DynamicCaster<engine::world::Location>;
