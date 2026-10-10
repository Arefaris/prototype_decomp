// String hashes of the core module (file and function names guessed; the unit is 0x1063A440 - 0x1063A69D).
// The 64-bit hash is the engine's name hash (h = h * 65599 ^ c over the signed bytes); the 32-bit one is h * 31 + c.
// Each hash reports its result to a callback (a debugging hook that collects hash -> string, empty by default).
#ifndef CORE_HASH_H
#define CORE_HASH_H

namespace core
{
	typedef void (*Hash64Callback)(unsigned __int64 hash, const char* string);
	typedef void (*Hash32Callback)(unsigned int hash, const char* string);

	// The callbacks installed by default: they do nothing
	void DefaultHash64Callback(unsigned __int64 hash, const char* string);
	void DefaultHash32Callback(unsigned int hash, const char* string);

	// 64-bit name hash of a zero-terminated string, continued from `hash`; a null string returns `hash` unchanged
	unsigned __int64 Hash64(const char* string, unsigned __int64 hash);
	// Hash64 called through one more frame (another entry point of the same thing)
	unsigned __int64 MakeHash64(const char* string, unsigned __int64 hash);
	// As Hash64, but every byte below 'a' is moved up by 0x20 first (a crude lower-casing)
	unsigned __int64 Hash64NoCase(const char* string, unsigned __int64 hash);
	// Installs the hook called with every computed 64-bit hash; null restores the default
	void SetHash64Callback(Hash64Callback callback);

	// 32-bit hash of a zero-terminated string, continued from `hash`
	unsigned int Hash32(const char* string, unsigned int hash);
	unsigned int Hash32NoCase(const char* string, unsigned int hash);
	void SetHash32Callback(Hash32Callback callback);

	// Prints the hash as 16 (8) lower-case hexadecimal digits into `buffer`; returns the number of characters
	int Hash64ToString(unsigned __int64 hash, char* buffer);
	int Hash32ToString(unsigned int hash, char* buffer);
}

#endif
