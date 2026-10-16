// proto::MidgroundManager: see the header. The file name, the member names and the layout are guesses.
#include "code/proto/render/midgroundmanager.h"

namespace proto
{
	// FUNCTION: ENGINE 0x102DDD30
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

	// FUNCTION: ENGINE 0x102DDE30
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
}
