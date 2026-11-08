// pure3d::visibility::BitSet: the sets of bits the visibility server keeps (unit 0x1060F4F0 - 0x1060F830; the file name is
// guessed, no assert path survives).
#include <new>
#include <string.h>
#include "code/pure3d/visibility.h"

namespace pure3d
{
	namespace visibility
	{
#ifdef NONMATCHING
		// The number of bits set in each byte value (0x10E33990)
		static const unsigned char sBitCounts[256] =
		{
			0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
		};
#endif

		// FUNCTION: ENGINE 0x1060F4F0
		void BitSet::ClearAll()
		{
			unsigned int count = bitCount >> 5;
			for (unsigned int i = 0; i < count; i++)
			{
				words[i] = 0;
			}
		}

		// FUNCTION: ENGINE 0x1060F540
		BitSet::BitSet()
		{
			bitCount = 0;
			ownsBlock = false;
			words = 0;
			block = 0;
		}

		// FUNCTION: ENGINE 0x1060F550
		void BitSet::Create(unsigned int bits, void* memory)
		{
			bitCount = bits;
			if (memory == 0)
			{
				block = new char[(bits >> 3) + 0x7F];
				words = (unsigned int*)(((unsigned int)block + 0x7F) / 0x80 * 0x80);
				ownsBlock = true;
				unsigned int count = bitCount >> 5;
				for (unsigned int i = 0; i < count; i++)
				{
					words[i] = 0;
				}
			}
			else
			{
				words = (unsigned int*)memory;
				block = memory;
				ownsBlock = false;
			}
		}

		// FUNCTION: ENGINE 0x1060F5C0
		void BitSet::Free()
		{
			if (ownsBlock)
			{
				delete[] (char*)block;
			}
			block = 0;
			words = 0;
			bitCount = 0;
		}

		// FUNCTION: ENGINE 0x1060F5F0
		// NONMATCHING: the engine counts the groups in edx and the words in esi, 82.4 %
#ifdef NONMATCHING
		int BitSet::CountSet()
		{
			int count = 0;
			unsigned int remaining = bitCount >> 5;
			if (remaining != 0)
			{
				unsigned int* word = words;
				do
				{
					unsigned int value = *word;
					if (value != 0)
					{
						if (value == 0xFFFFFFFF)
						{
							count += 32;
						}
						else
						{
							count += sBitCounts[value & 0xFF] + sBitCounts[(value >> 8) & 0xFF] +
								sBitCounts[(value >> 16) & 0xFF] + sBitCounts[value >> 24];
						}
					}
					word++;
					remaining--;
				}
				while (remaining != 0);
			}
			return count;
		}
#endif

		// FUNCTION: ENGINE 0x1060F670
		// NONMATCHING: the engine loads the three arguments of memcpy before it pushes them, 41.4 %
#ifdef NONMATCHING
		void BitSet::CopyFrom(const BitSet* other)
		{
			unsigned int* destination = words;
			unsigned int bytes = bitCount >> 3;
			const unsigned int* source = other->words;
			memcpy(destination, source, bytes);
		}
#endif

		// FUNCTION: ENGINE 0x1060F690
		// NONMATCHING: the engine's unrolled loop keeps its own index and pointers, ours indexes every word
#ifdef NONMATCHING
		void BitSet::SetNot(const BitSet* other)
		{
			unsigned int count = bitCount >> 5;
			unsigned int* destination = words;
			const unsigned int* source = other->words;
			for (unsigned int i = 0; i < count; i += 4)
			{
				destination[i] = ~source[i];
				destination[i + 1] = ~source[i + 1];
				destination[i + 2] = ~source[i + 2];
				destination[i + 3] = ~source[i + 3];
			}
		}
#endif

		// FUNCTION: ENGINE 0x1060F6F0
		// NONMATCHING: the engine's unrolled loop keeps its own index and pointers, ours indexes every word
#ifdef NONMATCHING
		void BitSet::SetAnd(const BitSet* first, const BitSet* second)
		{
			unsigned int count = bitCount >> 5;
			unsigned int* destination = words;
			const unsigned int* firstWords = first->words;
			const unsigned int* secondWords = second->words;
			for (unsigned int i = 0; i < count; i += 4)
			{
				destination[i] = secondWords[i] & firstWords[i];
				destination[i + 1] = secondWords[i + 1] & firstWords[i + 1];
				destination[i + 2] = secondWords[i + 2] & firstWords[i + 2];
				destination[i + 3] = secondWords[i + 3] & firstWords[i + 3];
			}
		}
#endif

		// FUNCTION: ENGINE 0x1060F780
		// NONMATCHING: the engine's unrolled loop keeps its own index and pointers, ours indexes every word
#ifdef NONMATCHING
		void BitSet::SetOr(const BitSet* first, const BitSet* second)
		{
			unsigned int count = bitCount >> 5;
			unsigned int* destination = words;
			const unsigned int* firstWords = first->words;
			const unsigned int* secondWords = second->words;
			for (unsigned int i = 0; i < count; i += 4)
			{
				destination[i] = secondWords[i] | firstWords[i];
				destination[i + 1] = secondWords[i + 1] | firstWords[i + 1];
				destination[i + 2] = secondWords[i + 2] | firstWords[i + 2];
				destination[i + 3] = secondWords[i + 3] | firstWords[i + 3];
			}
		}
#endif

		// FUNCTION: ENGINE 0x1071A620
		int BitSet::Test(unsigned int bit)
		{
			return (words[bit >> 5] & 1 << (bit & 0x1F)) != 0;
		}

		// FUNCTION: ENGINE 0x1071A650
		void BitSet::Set(unsigned int bit, bool value)
		{
			unsigned int* word = &words[bit >> 5];
			unsigned int mask = 1 << (bit & 0x1F);
			if (value)
			{
				*word |= mask;
			}
			else
			{
				*word &= ~mask;
			}
		}

		// FUNCTION: ENGINE 0x1071A680
		void BitSet::SetBit(unsigned int bit)
		{
			unsigned int* word = &words[bit >> 5];
			*word |= 1 << (bit & 0x1F);
		}
	}
}
