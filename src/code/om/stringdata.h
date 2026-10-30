// The data behind an owned om::String (names guessed): the characters sit behind a header of the number of strings that
// share them and the room they have; `this` of a StringData is the data pointer of the string.
#ifndef OM_STRINGDATA_H
#define OM_STRINGDATA_H

namespace om
{
	// What the data pointer of an owned string is eight bytes behind
	struct StringHeader
	{
		int refCount;
		unsigned int capacity;
	};

	// 0x105B3950
	int AtomicIncrement(int* value);
	// 0x105B3970
	int AtomicDecrement(int* value);

	class StringData
	{
	public:
		// 0x105B3890
		StringHeader* GetHeader();
		// 0x105B3880
		char* GetCharacters();
		// 0x105B39D0
		char* GetReadCharacters();
		// 0x105B39E0
		char* GetWriteCharacters();
		// 0x105B3990
		void AddRef();
		// 0x105B39A0
		unsigned int GetRefCount();
		// 0x105B39B0
		static void Free(StringData* data);
		// 0x105B3AC0
		void Unshare();
		// 0x105B3AF0: a buffer of the room, holding the characters
		static void Create(StringData** result, const char* text, unsigned int count, unsigned int capacity);
	};
}

#endif
