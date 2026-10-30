// The loaders that read a resource out of a P3D stream: content::ObjectLoader (RTTI name, 6 vftable slots) and
// content::SimpleChunkHandler (8 slots), the bases of every "chunk handler" the content library registers under a
// chunk id. The stream reader they hand on is content::ChunkReader (0x288 bytes: the chunk the reader currently sits
// in, the stream it reads from at +0x284); its name is a guess, as are the member and slot names below. The classes
// live in another unit; only what their users (the pure3d loaders) need is declared, so no vftable of theirs is
// emitted here.
#ifndef CONTENT_CHUNKHANDLER_H
#define CONTENT_CHUNKHANDLER_H

#include "code/container/string.h"
#include "code/content/loadinventory.h"
#include "code/core/file/file.h"

namespace math
{
	class Vector;
}

namespace content
{
	class LoadStream;

	// The reads of a compressed file's data (class name guessed; not reconstructed)
	class CompressedReader
	{
	public:
		// 0x1060DC40: queues the read of size bytes into destination
		void Read(void* destination, unsigned int size);
		// 0x1060DC90: whether everything queued has been read
		bool IsDone();
		// 0x1060DCC0: waits until it has
		void Wait();

		unsigned char unknown0[0xC];
		// The size of the unpacked data
		unsigned int size;
	};

	// What the load manager reads a stream from: the path as a 256 character string, then the places the loaded
	// objects go to (the engine builds it on the stack; names guessed)
	struct LoadArguments
	{
		container::StringC<256> path;
		LoadStream* stream;
		LoadInventory* inventory;
		int heap;
		int objectHeap;
		unsigned int capacity;
		bool blocking;
		bool unknown119;
		unsigned short unknown11A;
		int unknown11C;
	};

	// The stream a chunk reader reads through (RTTI content::LoadStream, a reference counted load object of 0x4C
	// bytes; the member names are guesses). It reads a file through two buffers of the stream buffer pool, or a
	// block of memory, or a compressed file. The chunk handlers know it as the chunk stream.
	class LoadStream : public LoadObject
	{
	public:
		// 0x1060AA00: opens the file of a path (reads it through the buffers when mode is 1)
		LoadStream(const char* path, int unused, int mode);
		// 0x1060AA40: opens the file a load request names
		LoadStream(LoadArguments* request, int unused, int mode);
		// 0x1060AA90: reads through an open file
		LoadStream(core::IFile* newFile, int unused, int mode, int blocking);
		// 0x1060AF70: reads a compressed file's data (offset and size are those of the part of it to read)
		LoadStream(CompressedReader* newCompressed, int offset, int size, int blocking);
		// 0x1060AAE0: reads a block of memory
		LoadStream(const void* data, unsigned int newSize);
		// 0x1060AB10 (the scalar deleting destructor is 0x1060AF50)
		virtual ~LoadStream();

		// 0x1060B260: reads count items of size bytes into destination (the last word is unknown)
		void Read(void* destination, unsigned int count, unsigned int size, unsigned int unknown);
		// 0x1060B2C0: steps over `bytes` bytes of the stream without reading them (name guess)
		void Skip(unsigned int bytes);
		// 0x1060A530 / 0x1060A520: the position in the stream and its size (names guessed)
		unsigned int GetPosition();
		unsigned int GetSize();
		// 0x105FF580 / 0x105FF5A0 / 0x105FF5C0: a four-byte, a two-byte and a one-byte value (names guessed)
		unsigned int ReadUInt();
		unsigned short ReadUShort();
		unsigned char ReadUChar();
		// 0x1067C400: a four-byte float (name guessed)
		float ReadFloat();

		// 0x1060A540: 0 when a file is open, else 1 for a block of memory and 2 for a compressed file
		int GetSource();
		// 0x1060A560: the name of the file
		const char* GetName();
		// 0x1060A570: forgets everything (the members are cleared, nothing is released)
		void Reset();
		// 0x1060A5B0: opens the file (the one with ".rz" behind the name when compressed is set)
		void Open(const char* path, bool compressed);
		// 0x1060A670: reads from a block of memory
		void Attach(const void* data, unsigned int newSize);
		// 0x1060A6A0: copies a block (mode 1 with the processor)
		void Copy(void* destination, const void* source, unsigned int length, int mode);
		// 0x1060A770: starts reading the next block into the buffer
		void ReadBlock(void* buffer);
		// 0x1060A830: waits until the file or the compressed file is ready
		void Wait();
		// 0x1060A8C0: turns the bytes of count items of size bytes around when the data is of the other byte order
		void SwapBytes(void* data, int count, int size);
		// 0x1060AB50: gives the stream its buffers (the region of the pool and the size of the stream)
		void SetBuffers(unsigned int region, unsigned int regionSize);
		// 0x1060ABF0 / 0x1060AC20: the reads of a stream with no buffers
		void SkipDirect(int bytes);
		bool ReadDirect(void* destination, int count, int size, int option);
		// 0x1060AC80: swaps to the other buffer and starts filling the one just emptied
		void NextBuffer();
		// 0x1060B010: opens the stream (when it is not open yet or force is set); path is the name of the
		// uncompressed file for a stream of a compressed one
		void Prepare(bool force, const char* path);
		// 0x1060B130: the reads through the buffers
		bool ReadBuffered(void* destination, int count, int size, int option);
		// 0x1060B240: opens the stream when needed and answers whether it is open
		bool IsOpen();
		// 0x1060B330: the buffer the stream sits in and its size
		bool GetBuffer(void** buffer, unsigned int* bufferSize);

		core::IFile* file;
		CompressedReader* compressed;
		bool opened;
		bool blocking;
		bool buffered;
		// Whether the data is stored in the other byte order (flipped by a chunk file's byte-swapped marker; name
		// guessed)
		bool swapped;
		bool unknown14;
		unsigned int size;
		unsigned int position;
		unsigned int filePosition;
		unsigned int currentBuffer;
		unsigned int buffers[2];
		unsigned int current;
		unsigned int offset;
		unsigned int fill;
		unsigned int lastRead;
		unsigned int bufferSize;
		unsigned int unknown44;
		unsigned int sinceYield;
	};

	typedef LoadStream ChunkStream;

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
		// 0x105FF5E0, 0x105FF670, 0x1067C440, 0x1067C420: a four-byte value, count items of size bytes, three floats and
		// a float (names guessed)
		unsigned int ReadUnsigned();
		// 0x105FF600: a two-byte value (name guessed)
		unsigned short ReadUShort();
		void ReadData(void* destination, unsigned int count, unsigned int size);
		void ReadVector(math::Vector* vector);
		float ReadFloat();
		// Reads from the stream the chunks come from
		__forceinline void Read(void* destination, unsigned int count, unsigned int size, unsigned int unknown)
		{
			((ChunkStream*)stream)->Read(destination, count, size, unknown);
		}

		// 0x1060BB60: reads the first chunk's header out of the stream (takes a reference to it)
		explicit ChunkReader(ChunkStream* newStream);
		// 0x1060B9E0: enters a chunk whose id has been read already (the id is the argument)
		unsigned int BeginChunk(unsigned int id);

		// The header of a chunk the reader has entered (names guessed; the lengths include the 12 header bytes)
		struct Entry
		{
			unsigned int id;
			// Header and data
			unsigned int dataLength;
			// Header, data and the chunks inside
			unsigned int length;
			// The stream position of the chunk's first byte
			unsigned int start;
		};

		unsigned char unknown0[0x80];
		// One entry for each chunk the reader sits in
		Entry entries[32];
		// The index of the chunk the reader sits in
		int chunk;
		// The stream the chunks come from
		ChunkStream* stream;
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
