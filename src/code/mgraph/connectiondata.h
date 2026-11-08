// The description of a connection between two pins by the names of their nodes and pins (RTTI: mgraph::ConnectionData):
// what a graph reads from its text or binary form before it makes the connection.
#ifndef MGRAPH_CONNECTIONDATA_H
#define MGRAPH_CONNECTIONDATA_H

#include "code/om/name.h"
#include <string.h>
#include "code/om/allocation.h"

namespace om
{
	class BinaryStream;
	class TextValue;
	void ReleaseTracked(void* memory);
}

namespace mgraph
{
	class Graph;
	class GraphConnectionBase;

	// A block of memory the data owns and copies with the data (the engine tags it "MemBufCopy"; name guessed)
	struct MemoryBufferCopy
	{
		MemoryBufferCopy() :
			data(0),
			size(0),
			alignment(0)
		{
		}
		MemoryBufferCopy& operator=(const MemoryBufferCopy& other)
		{
			if (&other != this)
			{
				const void* source = other.data;
				unsigned int length = other.size;
				om::ReleaseTracked(data);
				size = length;
				alignment = 4;
				data = om::Allocate("MemBufCopy", length, 4);
				memcpy(data, source, length);
			}
			return *this;
		}

		void* data;
		unsigned int size;
		unsigned int alignment;
	};

	class ConnectionData
	{
	public:
		// 0x10AD3B30
		ConnectionData(const ConnectionData& other);
		// Slot 0 (0x10AD3E20): reads the names from the text nodes "Output" and "Input" (each with a "NodeName" and a "PinName")
		virtual bool ReadText(const om::TextValue* text);
		// Slot 1 (0x10AD3DC0): reads the four names from a binary stream
		virtual bool ReadBinary(om::BinaryStream* stream);

		// 0x10AD3A70: makes the connection from the output pin to the input pin in a graph, null when a node or pin is missing
		GraphConnectionBase* MakeConnection(Graph* graph);
		// 0x10AD3DA0: the connection of the graph that the names describe
		GraphConnectionBase* FindConnection(Graph* graph);

		om::ClassName outputNode;  // 8
		om::ClassName outputPin;  // 0x10
		om::ClassName inputNode;  // 0x18
		om::ClassName inputPin;  // 0x20
		MemoryBufferCopy buffer;  // 0x28
	};
}

#endif
