// The om library's text and binary forms of the plain values (0x105B7A80 - 0x105B8680; names guessed): the children of a
// text value, the stream buffer the binary forms read and write through, and the numbers, booleans and 64-bit values.
#include "code/om/textvalue.h"

#include "code/om/metaproperty.h"
#include "code/om/stream.h"
#include <stdio.h>
#include <stdlib.h>

namespace om
{
	// FUNCTION: ENGINE 0x105B7A80
	TextValue* TextNodeTree::First() const
	{
		TreeNode* node = root;
		if (node == &nil)
		{
			return 0;
		}
		while (node->left != &nil)
		{
			node = node->left;
		}
		return (TextValue*)node;
	}

	// FUNCTION: ENGINE 0x105B7AA0
	TextValue* TextNodeTree::Next(TextValue* node) const
	{
		TreeNode* end = (TreeNode*)&nil;
		TreeNode* next = ((TreeNode*)node)->right;
		if (next != end)
		{
			while (next->left != end)
			{
				next = next->left;
			}
		}
		else
		{
			next = ((TreeNode*)node)->parent;
			while (next != end && (TreeNode*)node == next->right)
			{
				node = (TextValue*)next;
				next = next->parent;
			}
		}
		return next != end ? (TextValue*)next : 0;
	}

	// FUNCTION: ENGINE 0x105B7B50
	StreamBuffer::StreamBuffer(Stream* newStream, int nativeOrder) :
		stream(newStream),
		swap(nativeOrder == 0)
	{
	}

#ifdef NONMATCHING
	// 0x105B7B90: reverses the bytes of a value (the start in ecx, the size in eax)
	static void ReverseBytes(int size, char* data)
	{
		char* last = data + size - 1;
		while (data < last)
		{
			char first = *last;
			char second = *data;
			*data = first;
			*last = second;
			data++;
			last--;
		}
	}

	// FUNCTION: ENGINE 0x105B7BC0
	// NONMATCHING: the engine's static ReverseBytes takes the data in ecx and the size in eax, ours the other way (96.6 %)
	bool StreamBuffer::Read(void* data, int size)
	{
		if (stream->Read(data, size))
		{
			if (swap)
			{
				ReverseBytes(size, (char*)data);
			}
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B7C00
	// NONMATCHING: same register assignment of ReverseBytes (93.9 %)
	bool StreamBuffer::Write(const void* data, int size)
	{
		if (swap)
		{
			ReverseBytes(size, (char*)data);
			bool result = stream->Write(data, size);
			ReverseBytes(size, (char*)data);
			return result;
		}
		return stream->Write(data, size);
	}
#endif
}
