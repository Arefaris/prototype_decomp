// proto::MidgroundManager: see the header. The file name, the member names and the layout are guesses.
#include "code/proto/render/midgroundmanager.h"

namespace proto
{
	// FUNCTION: ENGINE 0x102DDD30
	// NONMATCHING: everything but the array stride is the engine's (86.8 %); the engine's MidgroundCellRecord is
	// 0x18 bytes because its core::Name is eight-byte aligned, ours is 0x14 (see the header)
#ifdef NONMATCHING
	void MidgroundManager::CellLoaded(MidgroundCell* cell)
	{
		MidgroundMap::Iterator iterator(&map);
		engine::render::Drawable* drawable = iterator.Find(cell->unknown54->name.GetHash());
		if (drawable == 0)
		{
			return;
		}
		drawable->SetUnknownBC(1.0f);
		drawable->SetPartsUnknown(true);
		MidgroundCellRecord record;
		record.drawable = drawable;
		record.unknownC = 1;
		record.name = cell->unknown54->name;
		record.unknown10 = unknown8;
		records.PushBack(record);
	}
#endif

	// FUNCTION: ENGINE 0x102DDE30
	// NONMATCHING: as CellLoaded, the records array's 0x18 stride (the engine's core::Name is eight-byte aligned)
#ifdef NONMATCHING
	void MidgroundManager::CellUnloaded(MidgroundCell* cell)
	{
		MidgroundMap::Iterator iterator(&map);
		engine::render::Drawable* drawable = iterator.Find(cell->unknown54->name.GetHash());
		if (drawable == 0)
		{
			return;
		}
		drawable->SetUnknownBC(1.0f);
		drawable->SetPartsUnknown(true);
		core::Name<core::CaseSensitiveKey> name(cell->unknown54->name);
		MidgroundCellRecord* item = records.begin;
		while (item != records.end)
		{
			if (item->name == name)
			{
				records.EraseFast(item);
				return;
			}
			item++;
		}
	}
#endif
}
