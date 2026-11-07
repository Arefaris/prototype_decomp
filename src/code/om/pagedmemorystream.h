// om::NullStream and om::PagedMemoryStream (RTTI, derived from om::Stream). The null stream takes every write and
// reads nothing; the paged stream keeps what is written in pages of 4096 bytes that it allocates as the writing
// reaches them.
#ifndef OM_PAGEDMEMORYSTREAM_H
#define OM_PAGEDMEMORYSTREAM_H

#include "code/om/dynamicarray.h"
#include "code/om/stream.h"

namespace om
{
	class NullStream : public Stream
	{
	public:
		// 0x105BFEB0
		NullStream();
		// Slots 0 to 2 (0x105BFF00 / 0x105BFF10 / 0x105BFF20): the write works, the read and the size do not
		virtual bool Write(const void* data, unsigned int size);
		virtual bool Read(void* data, unsigned int size);
		virtual bool GetSize(unsigned int* size);
		// Slot 7 (0x105BFED0 is the deleting destructor)
		virtual ~NullStream()
		{
		}
	};

	class PagedMemoryStream : public Stream
	{
	public:
		// 0x105BF9E0
		PagedMemoryStream();
		// Slots 0 to 4 (0x105BFCF0 / 0x105BFAC0 / 0x105BF640 / 0x105BF650 / 0x105BF660)
		virtual bool Write(const void* data, unsigned int size);
		virtual bool Read(void* data, unsigned int size);
		virtual bool GetSize(unsigned int* size);
		virtual bool GetPosition(unsigned int* position);
		virtual bool Seek(unsigned int position);
		// Slot 7 (0x105BFA30 is the destructor's body, 0x105BFBF0 the deleting destructor)
		virtual ~PagedMemoryStream();
		// Slot 8 (0x105BF680)
		virtual String GetDescription();
		OM_ALLOCATION(PagedMemoryStream);
		// 0x105BFA90: the page that holds an address, and the place of the address in it
		char* GetPage(unsigned int address, unsigned int* offset);
		// 0x105BFC70: the same, the page comes into being (zeroed) when the stream has not reached it yet
		char* GetPageOrCreate(unsigned int address, unsigned int* offset);
		// 0x105BFDF0: everything the stream holds, in an array of bytes (the position stays)
		void ReadAll(DynamicArray<char, unsigned short>** result);

		// A page: 4096 bytes from the om allocator (0x105BF880 is its operator new, 0x105BF5C0 its operator delete)
		struct Page
		{
			char bytes[0x1000];
			OM_ALLOCATION(Page);
		};

		unsigned int position;  // 8
		unsigned int unknown0C;
		unsigned int pageSize;  // 0x10: 4096
		unsigned int length;  // 0x14: the end of what was written
		DynamicArray<Page*, unsigned short> pages;  // 0x18
	};
}

#endif
