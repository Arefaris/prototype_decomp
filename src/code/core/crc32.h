// CRC-32 of the core module (file and function names guessed; the unit is 0x10646050 - 0x1064613A).
// MSB-first CRC-32, polynomial 0x04C11DB7, no reflection and no final inversion; the table is built on first use.
// Used by content::CRCWriteStream and the save-game checks (callers start from 0xFFFFFFFF).
#ifndef CORE_CRC32_H
#define CORE_CRC32_H

namespace core
{
	// Fills the 256-entry table once (a flag remembers it); every CRC user calls it before hashing
	void BuildCrc32Table();
	// Continues `crc` over `size` bytes of `data`
	unsigned int Crc32(const void* data, unsigned int size, unsigned int crc);
}

#endif
