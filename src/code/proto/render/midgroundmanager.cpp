// proto::MidgroundManager: see the header. The file name, the member names and the layout are guesses.
#include <new>

#include "code/container/string.h"
#include "code/core/heap.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/system/streampackage.h"
#include "code/proto/render/midgroundmanager.h"

namespace proto
{
	// 0x1126E538: the key of the game database string that names the level (name guess)
	core::Name<core::CaseSensitiveKey> gLevelNameKey("Proto_Volatile_ActiveMission", 0);
	// 0x104DF9E0: the name of the level a game database string stands for (name guess)
	const char* FindLevelName(const char* text);
}

namespace engine
{
	// 0x1130EFE0 and 0x1125E2C0: a list the midground drawables are added to and the value that is added (name guesses)
	class DrawableRegistry
	{
	public:
		// 0x10849540
		void Add(void* entry);
	};
	DrawableRegistry* GetDrawableRegistry();
	extern void* gMidgroundRegistryEntry;
}

namespace proto
{
	// FUNCTION: ENGINE 0x102DDD30
	// The record goes into the array through a restrict pointer in this body (the engine's loads of the record's
	// members come before the stores into the array, which is what a restrict destination allows), and it lives in a
	// block of its own so that its frame slot is the iterator's
	void MidgroundManager::CellLoaded(MidgroundCell* cell)
	{
		engine::render::Drawable* drawable;
		{
			MidgroundMap::Iterator iterator(&map);
			drawable = iterator.Find(cell->unknown54->name.GetHash());
		}
		if (drawable != 0)
		{
			drawable->SetUnknownBC(1.0f);
			drawable->SetPartsUnknown(true);
			{
				MidgroundCellRecord record(drawable, cell, unknown8);
				if (records.end < records.capacity)
				{
					MidgroundCellRecord* __restrict item = records.end++;
					if (item != 0)
					{
						new (item) MidgroundCellRecord(record);
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x102DDE30
	void MidgroundManager::CellUnloaded(MidgroundCell* cell)
	{
		engine::render::Drawable* drawable = MidgroundMap::Iterator(&map).Find(cell->unknown54->name.GetHash());
		if (drawable == 0)
		{
			return;
		}
		drawable->SetUnknownBC(1.0f);
		drawable->SetPartsUnknown(true);
		core::Name<core::CaseSensitiveKey> name(cell->unknown54->name);
		for (MidgroundCellRecord *item = records.begin, *end = records.end; item != end; item++)
		{
			if (name == item->name)
			{
				records.EraseFast(item);
				return;
			}
		}
	}

	// FUNCTION: ENGINE 0x102DE130
	void MidgroundManager::Load()
	{
		const char* levelName = FindLevelName(engine::gGameDatabase->GetString(gLevelNameKey, 0, 0));
		container::StringC<1024> text;
		text.Format("%s_midground", levelName);
		engine::StreamPackage* package;
		{
			// the engine keeps the package's name on an eight-byte boundary of the frame
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> packageName(text.buffer, 1);
			package = engine::FindStreamPackage(packageName);
		}
		if (package != 0)
		{
			core::HeapScope scope(package->instance->slot->heap);
			content::LoadInventory::Iterator it(package->GetInventory());
			engine::render::DrawableArchetype* archetype = it.First<engine::render::DrawableArchetype>();
			while (archetype != 0)
			{
				if (!archetype->IsFlagged())
				{
					core::Name<core::CaseSensitiveKey> name(*archetype->GetName());
					engine::render::Drawable drawable = engine::render::Drawable::CreateInstance(
						(engine::render::SourceDrawable*)archetype, true, false);
					drawable.SetUnknownCC(2);
					drawables.PushBack(drawable);
					map.Insert(name.GetHash(), drawables.end - 1);
				}
				archetype = it.Next<engine::render::DrawableArchetype>();
			}
		}
		engine::GetDrawableRegistry()->Add(engine::gMidgroundRegistryEntry);
	}
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D60850
// FUNCTION: ENGINE 0x10D857B0
