// The loaders that read a resource out of a P3D stream: content::ObjectLoader (RTTI name, 6 vftable slots) and
// content::SimpleChunkHandler (8 slots), the bases of every "chunk handler" the content library registers under a
// chunk id. The stream reader they hand on is content::ChunkReader (0x288 bytes: the chunk the reader currently sits
// in, the stream it reads from at +0x284); its name is a guess, as are the member and slot names below. The classes
// live in another unit; only what their users (the pure3d loaders) need is declared, so no vftable of theirs is
// emitted here.
#ifndef CONTENT_CHUNKHANDLER_H
#define CONTENT_CHUNKHANDLER_H

#include "code/content/loadinventory.h"

namespace content
{
	// The stream a chunk handler reads through (0x288 bytes; 0x1060BB60 is the constructor, 0x1060B8E0 opens the
	// chunks, 0x1060B8A0 answers whether there is another one). The layout is partial.
	// The stream a chunk reader reads through (reference counted; only its read is known)
	class ChunkStream : public core::IRefCount
	{
	public:
		// 0x1060B260: reads count items of size bytes into destination (the last word is unknown)
		void Read(void* destination, unsigned int count, unsigned int size, unsigned int unknown);
		// 0x1060B2C0: steps over `bytes` bytes of the stream without reading them (name guess)
		void Skip(unsigned int bytes);
	};

	class ChunkReader
	{
	public:
		// 0x1060B8A0: whether there is another chunk in the one the reader sits in
		bool HasChunk();
		// 0x1060B8E0: opens the next chunk and answers its id
		unsigned int BeginChunk();
		// 0x1060BB10: how many bytes of the chunk's data have been read
		unsigned int GetPosition();
		// 0x1060BAF0: how many bytes of data the chunk has
		unsigned int GetSize();
		// 0x1060BAE0: the id of the chunk the reader sits in
		unsigned int GetChunkId();
		// 0x1060BA90: closes the chunk
		void EndChunk();
		// 0x105FF620: reads a length byte and that many characters into the buffer and terminates it; answers the
		// buffer
		char* ReadString(char* buffer);
		// Reads from the stream the chunks come from
		__forceinline void Read(void* destination, unsigned int count, unsigned int size, unsigned int unknown)
		{
			((ChunkStream*)stream)->Read(destination, count, size, unknown);
		}

		unsigned char unknown0[0x280];
		// The index of the chunk the reader sits in
		unsigned int chunk;
		// The stream the chunks come from
		core::IRefCount* stream;
	};

	class ObjectLoader : public LoadObject
	{
	public:
		virtual ~ObjectLoader();
		// Slot 3, 4: overridden from LoadObject
		virtual void Slot3(int unused);
		virtual bool IsReady();
		// Slot 5: makes the reader the chunk handler loads out of (the pure slot SimpleChunkHandler fills)
		virtual void CreateObject(void** object, void** name, void* source, void* unknown, LoadInventory* inventory) = 0;
	};

	class SimpleChunkHandler : public ObjectLoader
	{
	public:
		virtual ~SimpleChunkHandler();
		// Slot 5: makes the reader (0x288 bytes) and loads the object out of it through slot 7
		virtual void CreateObject(void** object, void** name, void* source, void* unknown, LoadInventory* inventory);
		// Slot 6: the id of the chunk the handler is registered for (+8)
		virtual int GetChunkFlags();
		// Slot 7: reads the object the chunk describes into the two outputs (which the derived loader fills; the
		// object is any reference-counted one, not only a LoadObject); the inventory is where it looks up the objects
		// the chunk refers to
		virtual void LoadObject(core::IRefCount** object, ObjectName* name, ChunkReader* reader,
			LoadInventory* inventory) = 0;

		// The chunk id the constructor is given, and a word the derived loaders do not use
		unsigned int chunkId;
		int unknownC;
	};
}

#endif
