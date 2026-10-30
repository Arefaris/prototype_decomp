// The byte and bit stream of the online messages (unit 0x108EC240 - 0x108EC7B0; no assert path, file name guessed).
#include "code/engine/util/packbuffer.h"
#include "code/engine/driving/carattributes.h"
#include <string.h>

namespace engine
{
	namespace util
	{
		// FUNCTION: ENGINE 0x108EC280
		PackBuffer::PackBuffer(unsigned char* newBuffer, int newSize)
		{
			buffer = newBuffer;
			size = newSize;
			position = 0;
			bit = 0;
		}

		// FUNCTION: ENGINE 0x108EC2B0
		PackBuffer::~PackBuffer()
		{
		}

		// FUNCTION: ENGINE 0x108EC2C0
		Packer::Packer(unsigned char* newBuffer, int newSize) : PackBuffer(newBuffer, newSize)
		{
		}

		// FUNCTION: ENGINE 0x108EC2E0
		Packer::~Packer()
		{
		}

		// FUNCTION: ENGINE 0x108EC480
		UnPacker::~UnPacker()
		{
		}

		// FUNCTION: ENGINE 0x108EC460
		UnPacker::UnPacker(unsigned char* newBuffer, int newSize) : PackBuffer(newBuffer, newSize)
		{
		}

		// FUNCTION: ENGINE 0x108EC240
		void Packer::PackByte(unsigned char value)
		{
			buffer[position] = value;
			position++;
		}

		// FUNCTION: ENGINE 0x108EC260
		void UnPacker::UnpackByte(unsigned int* value)
		{
			*value = buffer[position];
			position++;
		}

		// FUNCTION: ENGINE 0x108EC350
		void Packer::PackBit(bool value)
		{
			if (value)
			{
				buffer[position] |= (unsigned char)(1 << bit);
			}
			else
			{
				buffer[position] &= ~(unsigned char)(1 << bit);
			}
			bit++;
			if (bit == 8)
			{
				position++;
				bit = 0;
			}
		}

		// FUNCTION: ENGINE 0x108EC390
		// EQUIVALENT: register allocation (the engine keeps the value and the count in stack words and the pointer to the byte in esi; ours keeps them in registers; 7 %)
		void Packer::PackBits(unsigned int value, int count)
		{
			if (count > 0)
			{
				do
				{
					if ((value & 1) != 0)
					{
						buffer[position] |= (unsigned char)(1 << bit);
					}
					else
					{
						buffer[position] &= ~(unsigned char)(1 << bit);
					}
					value = (int)value >> 1;
					bit++;
					if (bit == 8)
					{
						position++;
						bit = 0;
					}
					count--;
				}
				while (count != 0);
			}
		}

		// FUNCTION: ENGINE 0x108EC3F0
		void Packer::PackString(const char* text)
		{
			int length = 0;
			while (text[length] != 0)
			{
				buffer[position + length] = text[length];
				length++;
			}
			buffer[position + length] = 0;
			position += length + 1;
		}

		// FUNCTION: ENGINE 0x108EC430
		void Packer::PackBytes(const void* data, unsigned int length)
		{
			memcpy(buffer + position, data, length);
			position += length;
		}

		// FUNCTION: ENGINE 0x108EC4F0
		void UnPacker::UnpackBit(bool* value)
		{
			*value = false;
			if ((1 << bit & (int)(char)buffer[position]) != 0)
			{
				*value = true;
			}
			bit++;
			if (bit == 8)
			{
				position++;
				bit = 0;
			}
		}

		// FUNCTION: ENGINE 0x108EC530
		// EQUIVALENT: register allocation (the engine counts down in a stack word and keeps the result pointer in edi; 14 %)
		void UnPacker::UnpackBits(int* value, int count)
		{
			int weight = 1;
			*value = 0;
			if (count > 0)
			{
				do
				{
					if ((1 << bit & (int)(char)buffer[position]) != 0)
					{
						*value = *value + weight;
					}
					bit++;
					weight = weight * 2;
					if (bit == 8)
					{
						position++;
						bit = 0;
					}
					count--;
				}
				while (count != 0);
			}
		}

		// FUNCTION: ENGINE 0x108EC590
		void UnPacker::UnpackSignedUnit7(float* value)
		{
			unsigned char byte = buffer[position];
			position++;
			if ((byte & 0x80) == 0)
			{
				*value = (float)(int)(char)(byte & 0x7f) * (1.0f / 127.0f);
			}
			else
			{
				*value = (float)(int)(char)(byte & 0x7f) * (-1.0f / 127.0f);
			}
		}

		// FUNCTION: ENGINE 0x108EC5E0
		void UnPacker::UnpackSignedUnit15(float* value)
		{
			unsigned short word = *(unsigned short*)(buffer + position);
			position += 2;
			if ((word & 0x8000) == 0)
			{
				*value = (float)(word & 0x7fff) * (1.0f / 32767.0f);
			}
			else
			{
				*value = (float)(word & 0x7fff) * (-1.0f / 32767.0f);
			}
		}

		// FUNCTION: ENGINE 0x108EC630
		void UnPacker::UnpackString(char* text, int size)
		{
			int length = 0;
			while (buffer[position] != 0 && length < size - 1)
			{
				text[length] = buffer[position];
				position++;
				length++;
			}
			text[length] = 0;
			while (buffer[position] != 0)
			{
				position++;
			}
			position++;
		}

		// FUNCTION: ENGINE 0x108EC6A0
		void UnPacker::UnpackBytes(void* data, unsigned int length)
		{
			memcpy(data, buffer + position, length);
			position += length;
		}

		// FUNCTION: ENGINE 0x108EC710
		void Packer::PackSignedUnit7(float value)
		{
			int scaled = (int)(value * 127.0f + driving::gHalf);
			unsigned char byte = (unsigned char)scaled;
			if (scaled < 0)
			{
				byte = -byte;
			}
			if (value < 0.0f)
			{
				byte = byte | 0x80;
			}
			buffer[position] = byte;
			position++;
		}

		// FUNCTION: ENGINE 0x108EC750
		void Packer::PackSignedUnit15(float value)
		{
			int scaled = (int)(value * 32767.0f + driving::gHalf);
			if (scaled < 0)
			{
				scaled = -scaled;
			}
			int word = (unsigned short)scaled;
			if (value < 0.0f)
			{
				word -= 0x8000;
			}
			*(short*)(buffer + position) = (short)word;
			position += 2;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108EC6D0
// FUNCTION: ENGINE 0x108EC6F0
// FUNCTION: ENGINE 0x108EC7A0
