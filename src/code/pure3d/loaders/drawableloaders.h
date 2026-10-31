// What the drawable loaders (PolySkinLoader, GeometryLoader, CompositeDrawableLoader) read besides their own chunks:
// the frame controller and vertex animation loaders they call through the content system, and the lists the vertex
// animation chunks make. The classes live in other units; only what the loaders use is declared, so no vftable of
// theirs is emitted here. Names are guesses except those the RTTI gives (marked).
#ifndef PURE3D_LOADERS_DRAWABLELOADERS_H
#define PURE3D_LOADERS_DRAWABLELOADERS_H

#include <new>

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/chunkhandler.h"
#include "code/content/loadmanager.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/entity.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	class FrameController;

	// RTTI: pure3d::FrameControllerHandler (vftable 0x10E60044): reads the frame controllers of some chunk ids
	class FrameControllerHandler : public RefCounted
	{
	public:
		// 0x10777B70; the destructor is declared first and not defined here, so that the vftable stays with the engine's own
		// copy (the deleting destructor is 0x10777BA0)
		FrameControllerHandler();
		virtual ~FrameControllerHandler();
		// Slot 3: whether the handler reads the controller of that chunk id; slot 4: reads it (the name of the controller
		// and the id and version of the chunk)
		virtual bool IsSupported(unsigned int chunkId) = 0;
		virtual FrameController* Load(const char* name, unsigned int chunkId, unsigned int version,
			content::ChunkReader* reader, content::LoadInventory* inventory) = 0;
	};

	// RTTI: pure3d::DefaultFrameControllerHandler (vftable 0x10E600D4): the handler of the engine's own controllers
	class DefaultFrameControllerHandler : public FrameControllerHandler
	{
	public:
		// 0x107783B0 (the deleting destructor is 0x107783E0)
		DefaultFrameControllerHandler();
		virtual ~DefaultFrameControllerHandler();
		// Slots 3 (0x10777AF0) and 4 (0x10778920)
		virtual bool IsSupported(unsigned int chunkId);
		virtual FrameController* Load(const char* name, unsigned int chunkId, unsigned int version,
			content::ChunkReader* reader, content::LoadInventory* inventory);
	};

	// RTTI: pure3d::FrameControllerLoader (chunk 0x121201): asks its handlers (four at most)
	class FrameControllerLoader : public content::SimpleChunkHandler
	{
	public:
		virtual ~FrameControllerLoader();
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);

		// 0x10777BC0: the first handler that reads that chunk id
		FrameControllerHandler* FindHandler(unsigned int chunkId);
		// 0x10778430: takes a handler (nothing when there are four already)
		void AddHandler(FrameControllerHandler* handler);

		unsigned int handlerCount; // +0x10
		FrameControllerHandler* handlers[4]; // +0x14
	};

	// RTTI: pure3d::OldFrameControllerLoader (vftable 0x10E60128, ten slots)
	class OldFrameControllerLoader : public content::SimpleChunkHandler
	{
	public:
		virtual ~OldFrameControllerLoader();
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);
		// Slot 8 (0x10777C20): whether the loader reads that chunk id; slot 9 (0x10779010)
		virtual bool IsSupported(unsigned int chunkId);
		virtual FrameController* Load(char* name, unsigned int chunkId, content::ChunkReader* reader,
			content::LoadInventory* inventory);
	};

	// RTTI: pure3d::OldVertexAnimKeyFrameList (0x20 bytes): the key frames of the vertex animation chunk
	class OldVertexAnimKeyFrameList : public RefCounted
	{
	public:
		unsigned char unknown8[0x18];
	};

	// RTTI: pure3d::VertexAnimKeyFrameList (0x20 bytes): the key frames of one part, made from the old list
	class VertexAnimKeyFrameList : public RefCounted
	{
	public:
		// 0x107760D0: the key frames of the old list that belong to the part with that index
		VertexAnimKeyFrameList(OldVertexAnimKeyFrameList* oldList, int part);
		// 0x107758C0
		unsigned int GetCount();

		unsigned char unknown8[0xC];
		int* keysBegin;
		int* keysEnd;
		unsigned char unknown1C[4];
	};

	// The array of parts as the engine's template lays it out: the empty allocator takes a word of its own
	struct PartArray : public container::ArrayDynamic<DrawablePart, container::AllocatorNew>
	{
		int allocator;
	};

	// The arrays of segments and joints the composite loader fills (the same layout)
	struct SegmentArray : public container::ArrayDynamic<DrawableSegment, container::AllocatorNew>
	{
		int allocator;
	};

	struct JointArray : public container::ArrayDynamic<unsigned short, container::AllocatorNew>
	{
		int allocator;
	};

	// Puts a copy of the part behind the last one when there is room for it
	inline bool PushBack(PartArray& array, const DrawablePart& part)
	{
		if (array.end < array.capacity)
		{
			DrawablePart* item = array.end++;
			if (item != 0)
			{
				new (item) DrawablePart(part);
			}
			return true;
		}
		return false;
	}

	// Reads a four-byte value
	inline unsigned int ReadWord(content::ChunkReader* reader)
	{
		unsigned int value;
		reader->Read(&value, 1, 4, 1);
		return value;
	}

	// Reads the vertex animation chunk (0x121305) into an old key frame list (an empty object; name guess)
	class VertexAnimKeyFrameListReader
	{
	public:
		// 0x107752F0 / 0x10775300
		VertexAnimKeyFrameListReader();
		~VertexAnimKeyFrameListReader();
		// 0x10776D50
		OldVertexAnimKeyFrameList* Read(content::ChunkReader* reader, content::LoadInventory* inventory);
	};
}

#endif
