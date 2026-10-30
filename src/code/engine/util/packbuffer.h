// engine::util::PackBuffer, Packer and UnPacker (RTTI names): the byte and bit stream the online messages are written to
// and read from. A buffer keeps the memory, its size, the byte it is at and the bit inside that byte; the packer writes
// values at that place and the unpacker reads them. Unit 0x108EC240 - 0x108EC7B0 (no assert path; the directory and file
// name are guesses); the method names are guesses.
#ifndef ENGINE_UTIL_PACKBUFFER_H
#define ENGINE_UTIL_PACKBUFFER_H

namespace engine
{
	namespace util
	{
		// RTTI: engine::util::PackBuffer (1 vftable slot, 0x14 bytes)
		class PackBuffer
		{
		public:
			// 0x108EC280
			PackBuffer(unsigned char* newBuffer, int newSize);
			// 0x108EC2B0 (deleting destructor 0x108EC6D0)
			virtual ~PackBuffer();

			unsigned char* buffer;  // +4
			int size;  // +8
			int position;  // +0xC: the byte the stream is at
			int bit;  // +0x10: the bit inside it
		};

		// RTTI: engine::util::Packer (1 vftable slot)
		class Packer : public PackBuffer
		{
		public:
			// 0x108EC2C0
			Packer(unsigned char* newBuffer, int newSize);
			// 0x108EC2E0 (deleting destructor 0x108EC6F0)
			virtual ~Packer();

			// 0x108EC240
			void PackByte(unsigned char value);
			// 0x108EC350: one bit
			void PackBit(bool value);
			// 0x108EC390: the low bits of a value, lowest first
			void PackBits(unsigned int value, int count);
			// 0x108EC3F0: a string with its end
			void PackString(const char* text);
			// 0x108EC430
			void PackBytes(const void* data, unsigned int length);
			// 0x108EC710: a number between -1 and 1 as a sign and seven bits
			void PackSignedUnit7(float value);
			// 0x108EC750: the same with fifteen bits
			void PackSignedUnit15(float value);
		};

		// RTTI: engine::util::UnPacker (1 vftable slot)
		class UnPacker : public PackBuffer
		{
		public:
			// 0x108EC460
			UnPacker(unsigned char* newBuffer, int newSize);
			// 0x108EC480 (deleting destructor 0x108EC7A0)
			virtual ~UnPacker();

			// 0x108EC260
			void UnpackByte(unsigned int* value);
			// 0x108EC4F0: one bit
			void UnpackBit(bool* value);
			// 0x108EC530: that many bits, lowest first
			void UnpackBits(int* value, int count);
			// 0x108EC590 / 0x108EC5E0: a number between -1 and 1 packed with seven or fifteen bits
			void UnpackSignedUnit7(float* value);
			void UnpackSignedUnit15(float* value);
			// 0x108EC630: a string, cut to the size of the buffer it goes to (the rest of it is skipped)
			void UnpackString(char* text, int size);
			// 0x108EC6A0
			void UnpackBytes(void* data, unsigned int length);
		};
	}
}

#endif
