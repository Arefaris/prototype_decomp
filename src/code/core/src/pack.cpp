#include <string.h>

#include "code/core/pack.h"

namespace core
{
	// A position of the binary search tree of earlier positions, ordered by the bytes that follow them
	struct PackNode
	{
		unsigned int parent;
		int left;
		int right;
	};

	// The work buffer: the node of position `count` is the sentinel whose right child is the root
	struct PackTree
	{
		unsigned int count;
		PackNode* nodes;
		PackNode storage[1];
	};

	// FUNCTION: ENGINE 0x10652A90
	unsigned int GetPackWorkSize(unsigned int count)
	{
		return (count + 1) * sizeof(PackNode) + 8;
	}

	// FUNCTION: ENGINE 0x10652AA0
	void Unpack(const unsigned char* in, unsigned int packedSize, unsigned char* out, unsigned int size, unsigned int full)
	{
		unsigned int done = 0;
		if (size == full)
		{
			while (done < size)
			{
				unsigned int token = *in++;
				if (token > 0xF)
				{
					int length = token & 0xF;
					if (length == 0)
					{
						length = 0xF;
						while (*in == 0)
						{
							in++;
							length += 0xFF;
						}
						length += *in++;
					}
					token = (*in << 4) | (token >> 4);
					in++;
					const unsigned char* from = out - token;
					int quads = length >> 2;
					length -= quads << 2;
					do
					{
						*out++ = *from++;
						*out++ = *from++;
						*out++ = *from++;
						*out++ = *from++;
						done += 4;
					}
					while (--quads);
					if (length != 0)
					{
						done += length;
						do
						{
							*out++ = *from++;
						}
						while (--length);
					}
				}
				else
				{
					if (token == 0)
					{
						while (*in == 0)
						{
							in++;
							token += 0xFF;
						}
						token += *in++;
						*out++ = *in++;
						*out++ = *in++;
						*out++ = *in++;
						*out++ = *in++;
						*out++ = *in++;
						*out++ = *in++;
						*out++ = *in++;
						*out++ = *in++;
						*out++ = *in++;
						*out++ = *in++;
						*out++ = *in++;
						*out++ = *in++;
						*out++ = *in++;
						*out++ = *in++;
						*out++ = *in++;
						done += 15;
					}
					do
					{
						*out++ = *in++;
						done++;
					}
					while (--token);
				}
			}
		}
		else
		{
			while (done < size)
			{
				unsigned int token = *in++;
				int length = token;
				if (token > 0xF)
				{
					length = token & 0xF;
					if (length == 0)
					{
						length = 0xF;
						while (*in == 0)
						{
							in++;
							length += 0xFF;
						}
						length += *in++;
					}
					token = (*in << 4) | (token >> 4);
					in++;
					const unsigned char* from = out - token;
					int remaining = size - done;
					if (length > remaining)
					{
						length = remaining;
					}
					if (length != 0)
					{
						done += length;
						do
						{
							*out++ = *from++;
						}
						while (--length);
					}
				}
				else
				{
					if (length == 0)
					{
						length = 0xF;
						while (*in == 0)
						{
							in++;
							length += 0xFF;
						}
						length += *in++;
					}
					int remaining = size - done;
					if (length > remaining)
					{
						length = remaining;
					}
					do
					{
						*out++ = *in++;
						done++;
					}
					while (--length);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x10652D50
	static PackTree* InitPackTree(void* work, unsigned int count)
	{
		PackTree* tree = (PackTree*)work;
		tree->count = count;
		tree->nodes = tree->storage;
		tree->nodes[count].right = 0;
		tree->nodes[0].parent = count;
		tree->nodes[0].right = -1;
		tree->nodes[0].left = -1;
		return tree;
	}

	// Inserts position pos into the tree and returns the longest match on the way down. Returns whether an equally
	// long or longer match was passed over because its distance cannot be written.
	// FUNCTION: ENGINE 0x10652D80
	static bool InsertPackNode(const unsigned char* data, unsigned int size, unsigned int pos, unsigned int* offset,
		unsigned int* length, PackTree* tree)
	{
		unsigned int node = tree->nodes[tree->count].right;
		bool unwritable = false;
		*length = 0;
		for (;;)
		{
			int diff = 0;
			unsigned int n = 0;
			for (; n < size - pos; n++)
			{
				diff = data[pos + n] - data[node + n];
				if (diff != 0)
				{
					break;
				}
			}
			if (n > *length)
			{
				unsigned int distance = pos - node;
				if ((distance & 0xF) == 0)
				{
					unwritable = true;
				}
				else
				{
					*length = n;
					*offset = distance;
				}
			}
			int* link;
			if (diff >= 0)
			{
				link = &tree->nodes[node].right;
			}
			else
			{
				link = &tree->nodes[node].left;
			}
			if (*link == -1)
			{
				*link = pos;
				tree->nodes[pos].parent = node;
				tree->nodes[pos].right = -1;
				tree->nodes[pos].left = -1;
				return unwritable;
			}
			node = *link;
		}
	}

	// The exhaustive search for the longest match at a writable distance
	// FUNCTION: ENGINE 0x10652E60
	static void FindPackMatch(const unsigned char* data, unsigned int size, unsigned int pos, unsigned int* offset,
		unsigned int* length)
	{
		*offset = 0;
		*length = 0;
		for (unsigned int i = 0; i < pos; i++)
		{
			if (((i - pos) & 0xF) != 0)
			{
				for (unsigned int n = 0; n < size - i; n++)
				{
					if (pos + n >= size || data[i + n] != data[pos + n])
					{
						break;
					}
					if (n + 1 > *length)
					{
						*length = n + 1;
						*offset = i;
					}
				}
			}
		}
		*offset = pos - *offset;
	}

	// Writes a token with its length (and the length extension); returns the bytes written
	// FUNCTION: ENGINE 0x10652F00
	static unsigned int WritePackToken(unsigned char* out, unsigned int length, unsigned char token)
	{
		if (length > 0xF)
		{
			length -= 0xF;
			*out = token;
			unsigned int written = 1;
			while (length > 0xFF)
			{
				out[written++] = 0;
				length -= 0xFF;
			}
			out[written++] = (unsigned char)length;
			return written;
		}
		*out = token | (unsigned char)length;
		return 1;
	}

	// FUNCTION: ENGINE 0x10652F70
	void Pack(const void* source, unsigned int size, void* target, unsigned int* packedSize, unsigned int count,
		void* work, bool fast)
	{
		const unsigned char* data = (const unsigned char*)source;
		unsigned char* out = (unsigned char*)target;
		unsigned int pos = 0;
		unsigned int written = 0;
		unsigned int literals = 0;
		unsigned int literalStart = 0;
		PackTree* tree = InitPackTree(work, count);
		unsigned int offset = 0;
		unsigned int length = 0;
		while (pos < size)
		{
			if (length > 4 && (offset & 0xF) != 0)
			{
				if (literals > 0)
				{
					written += WritePackToken(out + written, literals, 0);
					memcpy(out + written, data + literalStart, literals);
					written += literals;
				}
				written += WritePackToken(out + written, length, (unsigned char)(offset << 4));
				out[written] = (unsigned char)(offset >> 4);
				written++;
				if (fast)
				{
					pos += length;
				}
				else
				{
					unsigned int skip = length;
					for (unsigned int i = 0; i < skip; i++)
					{
						pos++;
						InsertPackNode(data, size, pos, &offset, &length, tree);
					}
				}
				literals = 0;
				literalStart = pos;
			}
			else
			{
				literals++;
				pos++;
				if (!fast)
				{
					if (InsertPackNode(data, size, pos, &offset, &length, tree))
					{
						FindPackMatch(data, size, pos, &offset, &length);
					}
				}
			}
			if (fast)
			{
				InsertPackNode(data, size, pos, &offset, &length, tree);
			}
		}
		if (literals > 0)
		{
			written += WritePackToken(out + written, literals, 0);
			memcpy(out + written, data + literalStart, literals);
			written += literals;
		}
		*packedSize = written;
	}
}
