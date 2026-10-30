// content::ChunkReader (names guessed): the reader of the chunk loaders walks the chunks of a P3D stream. Each chunk
// starts with its id, the length of its header and data and the length of everything it holds (unit 0x1060A410 -
// 0x1060BC20, the stream in front of it is still unreconstructed).
#include "code/content/chunkhandler.h"

namespace content
{
	// FUNCTION: ENGINE 0x1060BB60
	ChunkReader::ChunkReader(ChunkStream* newStream)
	{
		unsigned int magic;
		chunk = -1;
		stream = newStream;
		unknown0[0] = 0;
		stream->AddRef();
		stream->Read(&magic, 4, 1, 1);
		if (magic == 0x503344FF)
		{
			stream->swapped = !stream->swapped;
			magic = 0xFF443350;
		}
		BeginChunk(magic);
	}

	// FUNCTION: ENGINE 0x1060B8A0
	bool ChunkReader::HasChunk()
	{
		Entry* entry = &entries[chunk];
		return entry->length > entry->dataLength && stream->GetPosition() < entry->start + entry->length;
	}

	// FUNCTION: ENGINE 0x1060B8E0
	unsigned int ChunkReader::BeginChunk()
	{
		unsigned int value;
		chunk++;
		if (chunk != 0)
		{
			unsigned int end = entries[chunk - 1].start + entries[chunk - 1].dataLength;
			if (stream->GetPosition() < end)
			{
				stream->Skip(end - stream->GetPosition());
			}
		}
		entries[chunk].start = stream->GetPosition();
		stream->Read(&value, 1, 4, 1);
		entries[chunk].id = value;
		stream->Read(&value, 1, 4, 1);
		entries[chunk].dataLength = value;
		stream->Read(&value, 1, 4, 1);
		entries[chunk].length = value;
		return entries[chunk].id;
	}

	// FUNCTION: ENGINE 0x1060B9E0
	unsigned int ChunkReader::BeginChunk(unsigned int id)
	{
		chunk++;
		entries[chunk].start = stream->GetPosition() - 4;
		entries[chunk].id = id;
		stream->Read(&id, 1, 4, 1);
		entries[chunk].dataLength = id;
		stream->Read(&id, 1, 4, 1);
		entries[chunk].length = id;
		return entries[chunk].id;
	}

	// FUNCTION: ENGINE 0x1060BA90
	void ChunkReader::EndChunk()
	{
		unsigned int start = entries[chunk].start;
		unsigned int length = entries[chunk].length;
		stream->Skip(length + start - stream->GetPosition());
		chunk--;
	}

	// FUNCTION: ENGINE 0x1060BAE0
	unsigned int ChunkReader::GetChunkId()
	{
		return entries[chunk].id;
	}

	// FUNCTION: ENGINE 0x1060BAF0
	unsigned int ChunkReader::GetSize()
	{
		return entries[chunk].dataLength - 12;
	}

	// FUNCTION: ENGINE 0x1060BB10
	unsigned int ChunkReader::GetPosition()
	{
		return stream->GetPosition() - 12 - entries[chunk].start;
	}
}
