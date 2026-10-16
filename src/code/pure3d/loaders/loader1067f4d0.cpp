// pure3d::Loader1067F4D0: see the header. The file name is a guess.
#include <new>

#include "code/pure3d/loaders/loader1067f4d0.h"

#include "code/core/criticalsection.h"

namespace pure3d
{
	// 0x1127E430: the lock the loaders of this unit hold while they read
	extern unsigned char gLoaderLock[24];

	// 0x1067CF80: reads the sub-chunk of the tables into them (name unknown)
	void Unknown1067CF80(content::ChunkReader* reader, int flags, Loaded1066F430Tables* tables);
	// 0x1067EB90: reads the entries chunk into the object (name unknown)
	void Unknown1067EB90(Loaded1066F430* loaded, content::ChunkReader* reader, int flags);

	// FUNCTION: ENGINE 0x1067F4D0
	// EQUIVALENT: register allocation and scheduling (27.9 %): the engine keeps the object in a stack slot and the
	// entry count in ebx, this compiler the other way round; every read, call and store is the same
	void Loader1067F4D0::LoadObject(core::IRefCount** object, content::ObjectName* name,
		content::ChunkReader* reader, int flags)
	{
		core::CriticalSectionEnter(gLoaderLock);
		unsigned char length;
		reader->Read(&length, 1, 1, 1);
		char text[0x100];
		reader->Read(text, length, 1, 1);
		text[length] = 0;
		unsigned int skipped;
		reader->Read(&skipped, 1, 4, 1);
		unsigned int count;
		reader->Read(&count, 1, 4, 1);
		reader->Read(&skipped, 1, 4, 1);
		Loaded1066F430* loaded = new Loaded1066F430();
		loaded->AddRef();
		content::ObjectName loadedName(text, 1);
		loaded->SetName(loadedName);
		Loaded1066F430Tables* tables = loaded->tables;
		if (count != 0)
		{
			loaded->begin = (Loaded1066F430Entry*)operator new[](count * sizeof(Loaded1066F430Entry));
			if (loaded->begin != 0)
			{
				loaded->capacity = loaded->begin + count;
			}
			else
			{
				loaded->capacity = 0;
			}
		}
		else
		{
			loaded->begin = 0;
			loaded->capacity = 0;
		}
		loaded->end = loaded->begin;
		while (reader->HasChunk())
		{
			reader->BeginChunk();
			unsigned int id = reader->GetChunkId();
			if (id == 0x7020001)
			{
				reader->Read(&skipped, 1, 4, 1);
				tables->unknown4 = new unsigned short[count];
				reader->Read(tables->unknown4, count, 2, 1);
				unsigned int number;
				reader->Read(&number, 1, 4, 1);
				tables->count = (unsigned short)number;
				tables->unknown8 = new unsigned short[tables->count];
				reader->Read(tables->unknown8, tables->count, 2, 1);
				reader->Read(&skipped, 1, 4, 1);
				unsigned int size;
				reader->Read(&size, 1, 4, 1);
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
						Unknown1067CF80(reader, flags, tables);
					}
					reader->EndChunk();
				}
			}
			else if (id == 0x7021100 || id == 0x7021101)
			{
				Unknown1067EB90(loaded, reader, flags);
			}
			reader->EndChunk();
		}
		*object = loaded;
		*name = content::ObjectName(text, 1);
		core::CriticalSectionLeave(gLoaderLock);
	}
}
