// What the drawable loaders (PolySkinLoader, GeometryLoader, CompositeDrawableLoader) read besides their own chunks:
// the frame controller and vertex animation loaders they call through the content system, and the lists the vertex
// animation chunks make. The classes live in other units; only what the loaders use is declared, so no vftable of
// theirs is emitted here. Names are guesses except those the RTTI gives (marked).
#ifndef PURE3D_LOADERS_DRAWABLELOADERS_H
#define PURE3D_LOADERS_DRAWABLELOADERS_H

#include <new>

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/chunkhandler.h"
#include "code/pure3d/drawable.h"
#include "code/pure3d/entity.h"
#include "code/pure3d/primitive.h"

namespace container
{
	class String;
}

namespace content
{
	class LoadJob;

	// The loaders the chunk ids are registered under (the global at 0x11276A64; the class name is a guess)
	class LoadManager
	{
	public:
		// 0x10607BD0: the loader registered for the chunk id
		ObjectLoader* GetLoader(unsigned int chunkId);
		// 0x10608370 / 0x10608910: registers a loader for the chunk id / takes the loaders of that id out again
		void AddLoader(ObjectLoader* loader, unsigned int chunkId);
		void RemoveLoader(unsigned int chunkId);
		// 0x10607660: starts loading what the request (a name, a stream and a few words) names; waits for it when
		// the last argument is set
		void Load(const container::String* request, LoadJob** job, bool wait);
	};

	extern LoadManager* gLoadManager;
}

namespace pure3d
{
	// RTTI: pure3d::FrameControllerLoader (chunk 0x121201)
	class FrameControllerLoader : public content::SimpleChunkHandler
	{
	public:
		virtual ~FrameControllerLoader();
		virtual void LoadObject(core::IRefCount** object, content::ObjectName* name, content::ChunkReader* reader,
			content::LoadInventory* inventory);
	};

	// RTTI: pure3d::ExpressionAnimationController (a frame controller of the vertex animations; the RTTI puts
	// SimpleFrameController and AnimationFrameController between it and FrameController)
	class ExpressionAnimationController : public FrameController
	{
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

	// RTTI: pure3d::CompDrawVisibilityAnimationController (a frame controller, the bases as the others')
	class CompDrawVisibilityAnimationController : public FrameController
	{
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
