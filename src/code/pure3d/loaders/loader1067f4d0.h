// A chunk handler of the P3D loaders (unit around 0x1067F4D0; the class name and the file name are guesses from the
// address): reads a named set of entries - an array of 0x50-byte records the sub-chunks fill and a block of index
// tables - into a MetaLoadObject of 0x30 bytes. Only its LoadObject is reconstructed.
#ifndef PURE3D_LOADERS_LOADER1067F4D0_H
#define PURE3D_LOADERS_LOADER1067F4D0_H

#include "code/content/chunkhandler.h"

namespace pure3d
{
	// One record of the entries (the loader does not touch its members)
	struct Loaded1066F430Entry
	{
		unsigned char unknown0[0x50];
	};

	// The tables a loaded object holds (0x10 bytes)
	struct Loaded1066F430Tables
	{
		unsigned short unknown0;
		unsigned short count;
		unsigned short* unknown4;
		unsigned short* unknown8;
		unsigned char* unknownC;
	};

	// The growable array of entries (begin, end, end of the storage, then the allocator's word; a container::ArrayDynamic
	// of operator new[] storage)
	struct Loaded1066F430Entries
	{
		// Replaces the storage with room for count entries (empty); false, with an empty array, when count is 0 or
		// the allocation fails
		bool Allocate(unsigned int count);

		Loaded1066F430Entry* begin;
		Loaded1066F430Entry* end;
		Loaded1066F430Entry* capacity;
		unsigned char allocator[4];
	};

	// The object the loader makes (0x30 bytes, constructor 0x1066F430)
	class Loaded1066F430 : public content::MetaLoadObject
	{
	public:
		// 0x1066F430
		Loaded1066F430();

		unsigned char unknown8[0xC];
		// +0x14: the entries
		Loaded1066F430Entries entries;
		// +0x24: the tables, made by the constructor
		Loaded1066F430Tables* tables;
		unsigned char unknown28[8];
	};

	class Loader1067F4D0 : public content::SimpleChunkHandler
	{
	public:
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);
	};
}

#endif
