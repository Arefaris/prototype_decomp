// proto::MidgroundManager: see the header. The file name, the member names and the layout are guesses.
#include "code/proto/render/midgroundmanager.h"

namespace proto
{
	// FUNCTION: ENGINE 0x102DDD30
	// EQUIVALENT: register allocation: the record's copy loads the drawable and the 1 through eax / ecx where the
	// engine uses ecx / edx (97.5 %)
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
			records.PushBack(MidgroundCellRecord(drawable, cell, unknown8));
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
}
