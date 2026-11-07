// The world stream manager (RTTI: engine::WorldStreamManager, a StreamClient that streams the world cells; unit
// 0x108540E0 - 0x108551xx, no assert path, file name guessed). Of the unit the class's lifetime and its two slots.
#include "code/core/heap.h"
#include "code/engine/world/location.h"
#include "code/container/arrayfixed.h"
#include "code/container/arraydynamicstatic.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/system/streamtrigger.h"
#include "code/engine/system/streamtriggermessages.h"
#include "code/engine/system/tagset.h"
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
		loadCallback = config->loadCallback;
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

namespace engine
{
	// The stream manager's list of the game objects that carry stream triggers (the unit 0x1082xxxx's; names guessed)
	int GetStreamDriverCount();
	GameObject* GetStreamDriver(int index);
	int GetGameStateStatus(int which);
	// 0x1082C7B0 / 0x1082C860: the stream manager's pending loads (names guessed)
	bool Unknown1082C7B0();
	bool Unknown1082C860(int* unused, core::Name<core::CaseSensitiveKey>* name);

	// FUNCTION: ENGINE 0x108541F0
	// Copies the first run of digits of the text and, unless omitLetter, the first lowercase letter behind it
	void ExtractNumberAndLetter(char* out, const char* text, bool omitLetter)
	{
		while (*text != 0 && !(*text >= '0' && *text <= '9'))
		{
			text++;
		}
		if (*text != 0)
		{
			while (*text != 0 && *text >= '0' && *text <= '9')
			{
				*out++ = *text++;
			}
			if (*text != 0)
			{
				while (*text != 0 && !(*text >= 'a' && *text <= 'z'))
				{
					text++;
				}
			}
		}
		if (!omitLetter)
		{
			*out++ = *text;
		}
		*out = 0;
	}

	// FUNCTION: ENGINE 0x10854270
	// The number of the zone the (last) stream driver is in, "-" when there is none
	void WorldStreamManager::GetCurrentZoneNumber(char* out)
	{
		out[0] = '-';
		out[1] = 0;
		if (GetStreamDriverCount() > 0)
		{
			int index = GetGameStateStatus(10) == 5 ? GetStreamDriverCount() - 1 : 0;
			GameObject* driver = GetStreamDriver(index);
			if (driver != 0)
			{
				StreamTriggerInfoMessage message;
				driver->SendMessage(&message);
				if (message.count > 0)
				{
					ExtractNumberAndLetter(out, message.entries[0].trigger->GetPackages(), true);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10854420
	void WorldStreamManager::UpdateDrivers()
	{
		for (int i = 0; i < GetStreamDriverCount(); i++)
		{
			GameObject* driver = GetStreamDriver(i);
			if (driver->behaviours.requested.Test(7) && driver->behaviours.requested.Test(7))
			{
				driver->behaviours.UpdateBehaviours(0.0f, 4);
			}
		}
		if (loadCallback != 0)
		{
			int count = 0;
			while (Unknown1082C7B0())
			{
				loadCallback(1);
				int unused;
				core::Name<core::CaseSensitiveKey> name;
				if (Unknown1082C860(&unused, &name))
				{
					count++;
					if (count == 1000)
					{
						return;
					}
				}
			}
		}
	}

	typedef container::ArrayDynamic<core::Name<core::CaseSensitiveKey>, container::AllocatorCoreStatic<12, 16> > NameArray;
	typedef container::ArrayFixed<StreamTrigger*, 16> TriggerArray;

	// FUNCTION: ENGINE 0x108544E0
	// NONMATCHING: the engine keeps the result in bl on the early exits, ours folds them to xor al, al (43.6 %)
#ifdef NONMATCHING
	// As below, but the tags of names that the filter holds go into out first, and the trigger counts only when out then
	// includes the tags of the package
	bool IsTriggerLoadedFor(const math::Vector* point, StreamTrigger* trigger, const TagSet* filter, const TagSet* tags,
		NameArray* names, TagSet* out, float margin)
	{
		bool result = false;
		if (trigger->Contains(*point, 0.0f))
		{
			if (trigger->FindPackage(*tags)->GetState() == 5)
			{
				for (unsigned int i = 0; i < names->Size(); i++)
				{
					core::Name<core::CaseSensitiveKey>* name = &(*names)[i];
					if (filter->Contains(*name))
					{
						out->Add(*name);
					}
				}
				if (!out->Includes(*tags))
				{
					return false;
				}
				result = true;
				container::ArrayDynamic<StreamTrigger*, StreamTrigger::Allocator>* neighbours = trigger->neighbourTriggers;
				if (neighbours != 0)
				{
					for (unsigned int i = 0; i < neighbours->Size(); i++)
					{
						if ((*neighbours)[i]->FindPackage(*tags)->GetState() != 5 && (*neighbours)[i]->Contains(*point, margin))
						{
							result = false;
						}
					}
				}
				return result;
			}
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x10854600
	// Whether the point is in the trigger, the trigger's package of the tags is loaded and every neighbour that
	// contains the point (grown by margin) has its package loaded too
	bool IsTriggerLoaded(const math::Vector* point, StreamTrigger* trigger, const TagSet* tags, float margin)
	{
		bool result = false;
		if (trigger->Contains(*point, 0.0f))
		{
			if (trigger->FindPackage(*tags)->GetState() == 5)
			{
				result = true;
				container::ArrayDynamic<StreamTrigger*, StreamTrigger::Allocator>* neighbours = trigger->neighbourTriggers;
				if (neighbours != 0)
				{
					for (unsigned int i = 0; i < neighbours->Size(); i++)
					{
						if ((*neighbours)[i]->FindPackage(*tags)->GetState() != 5 && (*neighbours)[i]->Contains(*point, margin))
						{
							result = false;
						}
					}
				}
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x108546C0
	// Whether one of the triggers, or one of their neighbours, has its package of the tags loaded around the point
	bool WorldStreamManager::IsAnyTriggerLoaded(const math::Vector* point, const TagSet* tags, TriggerArray* triggers, float margin)
	{
		int count = triggers->Size();
		for (int i = 0; i < count; i++)
		{
			if (IsTriggerLoaded(point, (*triggers)[i], tags, margin))
			{
				return true;
			}
			container::ArrayDynamic<StreamTrigger*, StreamTrigger::Allocator>* neighbours = (*triggers)[i]->neighbourTriggers;
			if (neighbours != 0)
			{
				for (int j = 0; j < (int)neighbours->Size(); j++)
				{
					if (IsTriggerLoaded(point, (*neighbours)[j], tags, margin))
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10854810
	// Collects the stream triggers of the stream drivers whose tags intersect the given ones
	void WorldStreamManager::CollectStreamTriggers(const TagSet* tags, TriggerArray* triggers)
	{
		for (int i = 0; i < GetStreamDriverCount(); i++)
		{
			GameObject* driver = GetStreamDriver(i);
			if (driver != 0)
			{
				StreamTriggerInfoMessage message;
				driver->SendMessage(&message);
				if (message.count > 0)
				{
					for (unsigned int j = 0; j < message.count; j++)
					{
						if (message.entries[j].tags->Intersects(*tags))
						{
							triggers->PushBack(message.entries[j].trigger);
						}
					}
				}
			}
		}
	}
}

// The lookup of a location by name (the filter the inventory is handed)
// FUNCTION: ENGINE 0x108547D0
template class content::LoadInventory::DynamicCaster<engine::world::Location>;
