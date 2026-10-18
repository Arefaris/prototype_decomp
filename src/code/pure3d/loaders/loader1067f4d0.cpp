// pure3d::Loader1067F4D0: see the header. The file name is a guess.
#include <new>

#include "code/pure3d/loaders/loader1067f4d0.h"

#include "code/core/criticalsection.h"

namespace pure3d
{
	// 0x1127E430: the lock the loaders of this unit hold while they read
	extern unsigned char gLoaderLock[24];

	// 0x1067CF80: reads the sub-chunk of the tables into them (name unknown)
	void Unknown1067CF80(content::ChunkReader* reader, content::LoadInventory* inventory, Loaded1066F430Tables* tables);
	// 0x1067EB90: reads the entries chunk into the object (name unknown)
	void Unknown1067EB90(Loaded1066F430* loaded, content::ChunkReader* reader, content::LoadInventory* inventory);

	// One word of the stream (the loaders read and drop several of them)
	inline unsigned int ReadUnsigned(content::ChunkReader* reader)
	{
		unsigned int value;
		reader->Read(&value, 1, 4, 1);
		return value;
	}

	// The inlined Allocate of the entries
	inline bool Loaded1066F430Entries::Allocate(unsigned int count)
	{
		if (count != 0)
		{
			begin = (Loaded1066F430Entry*)operator new[](count * sizeof(Loaded1066F430Entry));
			if (begin != 0)
			{
				capacity = begin + count;
				end = begin;
				return true;
			}
		}
		else
		{
			begin = 0;
		}
		end = 0;
		capacity = 0;
		return false;
	}

	// FUNCTION: ENGINE 0x1067F4D0
	void Loader1067F4D0::LoadObject(core::IRefCount** object, content::ObjectName* name,
		content::ChunkReader* reader, content::LoadInventory* inventory)
	{
		core::CriticalSectionEnter(gLoaderLock);
		char text[0x100];
		{
			unsigned char byte;
			reader->Read(&byte, 1, 1, 1);
			unsigned int length = byte;
			reader->Read(text, length, 1, 1);
			text[length] = 0;
		}
		ReadUnsigned(reader);
		unsigned int count = ReadUnsigned(reader);
		ReadUnsigned(reader);
		Loaded1066F430* loaded = new Loaded1066F430();
		loaded->AddRef();
		{
			content::ObjectName loadedName(text, 1);
			loaded->SetName(loadedName);
		}
		Loaded1066F430Tables* tables = loaded->tables;
		loaded->entries.Allocate(count);
		while (reader->HasChunk())
		{
			reader->BeginChunk();
			switch (reader->GetChunkId())
			{
			case 0x7020001:
				{
					ReadUnsigned(reader);
					tables->unknown4 = new unsigned short[count];
					reader->Read(tables->unknown4, count, 2, 1);
					tables->count = (unsigned short)ReadUnsigned(reader);
					tables->unknown8 = new unsigned short[tables->count];
					reader->Read(tables->unknown8, tables->count, 2, 1);
					ReadUnsigned(reader);
					unsigned int size = ReadUnsigned(reader);
					if (size == 0)
					{
						tables->unknownC = 0;
					}
					else
					{
						tables->unknownC = new unsigned char[size];
						reader->Read(tables->unknownC, size, 1, 1);
					}
					while (reader->HasChunk())
					{
						reader->BeginChunk();
						if (reader->GetChunkId() == 0x7020002)
						{
							Unknown1067CF80(reader, inventory, tables);
						}
						reader->EndChunk();
					}
				}
				break;
			case 0x7021100:
			case 0x7021101:
				Unknown1067EB90(loaded, reader, inventory);
				break;
			}
			reader->EndChunk();
		}
		*object = loaded;
		*name = content::ObjectName(text, 1);
		core::CriticalSectionLeave(gLoaderLock);
	}
}
