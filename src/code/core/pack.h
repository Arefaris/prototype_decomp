// The core module's LZ77 packer (file and all names guessed; the unit is 0x10652A90 - 0x1065314E). The file cache
// unpacks chunks with it (FileCache::ReadPacked).
//
// Stream format: a token byte, high nibble h, low nibble l.
// - h == 0: a run of l literal bytes follows (l == 0: 15 + a length extension).
// - h != 0: a match of l bytes (l == 0: 15 + a length extension) at distance (next byte << 4) | h back in the output.
// A length extension is a number of zero bytes worth 255 each and one closing byte added to them. Distances that are
// a multiple of 16 cannot be written (their token would read as literals), and matches are at least five bytes long.
#ifndef CORE_PACK_H
#define CORE_PACK_H

namespace core
{
	// Size of the work buffer Pack needs for `count` positions (the match tree)
	unsigned int GetPackWorkSize(unsigned int count);
	// Unpacks one chunk; size is how much of it to produce, full its unpacked size (packedSize is not used)
	void Unpack(const unsigned char* source, unsigned int packedSize, unsigned char* target, unsigned int size,
		unsigned int full);
	// Packs `size` bytes of source into target; `work` holds GetPackWorkSize(count) bytes, count >= size; fast skips
	// the tree insertions inside matches and the exhaustive search for writable distances
	void Pack(const void* source, unsigned int size, void* target, unsigned int* packedSize, unsigned int count,
		void* work, bool fast);
}

#endif
