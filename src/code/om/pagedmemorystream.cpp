// The om library's null stream and paged memory stream (0x105BF640 - 0x105BFF20).
#include "code/om/pagedmemorystream.h"
#include <string.h>

namespace om
{
	static inline void CopyBytes(char* destination, const char* source, unsigned int count)
	{
		for (unsigned int i = 0; i < count; i++)
		{
			destination[i] = source[i];
		}
	}

	// FUNCTION: ENGINE 0x105BFEB0
	NullStream::NullStream()
	{
	}

	// FUNCTION: ENGINE 0x105BFF00
	bool NullStream::Write(const void* data, unsigned int size)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x105BFF10
	bool NullStream::Read(void* data, unsigned int size)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x105BFF20
	bool NullStream::GetSize(unsigned int* size)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x105BF9E0
	PagedMemoryStream::PagedMemoryStream() :
		pages()
	{
		position = 0;
		unknown0C = 0;
		length = 0;
		pageSize = 0x1000;
	}

	// FUNCTION: ENGINE 0x105BFA30
	PagedMemoryStream::~PagedMemoryStream()
	{
		for (unsigned int i = 0; i < pages.size; i++)
		{
			Page::operator delete(pages[i]);
		}
	}

	// FUNCTION: ENGINE 0x105BFAC0
	bool PagedMemoryStream::Read(void* data, unsigned int count)
	{
		if (position + count > length)
		{
			return false;
		}
		char* destination = static_cast<char*>(data);
		unsigned int remaining = count;
		while (remaining > 0)
		{
			unsigned int offset = position & 0xFFF;
			Page* page = pages[static_cast<unsigned short>(position >> 12)];
			unsigned int room = 0x1000 - offset;
			unsigned int chunk = remaining;
			if (chunk > room)
			{
				chunk = room;
			}
			const char* source = page->bytes + offset;
			for (unsigned int i = 0; i < chunk; i++)
			{
				destination[i] = source[i];
			}
			position += chunk;
			destination += chunk;
			remaining -= chunk;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105BFCF0
	// NONMATCHING: register assignment (the engine keeps this in ebp and the offset and page index in ebx and edi), 11 %
#ifdef NONMATCHING
	bool PagedMemoryStream::Write(const void* data, unsigned int count)
	{
		const char* source = static_cast<const char*>(data);
		while (count > 0)
		{
			unsigned int offset = position & 0xFFF;
			unsigned int index = position >> 12;
			if (index >= pages.size)
			{
				const char* tag = Page::AllocationTag();
				do
				{
					Page* page = static_cast<Page*>(Allocate(tag, 0x1000, 1));
					if (page != 0)
					{
						memset(page, 0, 0x1000);
					}
					::new (&pages.Append()) Page*(page);
				}
				while (index >= pages.size);
			}
			unsigned int room = 0x1000 - offset;
			unsigned int chunk = count > room ? room : count;
			char* destination = pages[index]->bytes + offset;
			for (unsigned int i = 0; i < chunk; i++)
			{
				destination[i] = source[i];
			}
			position += chunk;
			source += chunk;
			count -= chunk;
		}
		length = length > position ? length : position;
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x105BFA90
	char* PagedMemoryStream::GetPage(unsigned int address, unsigned int* offset)
	{
		*offset = address & 0xFFF;
		return pages[static_cast<unsigned short>(address >> 12)]->bytes;
	}

	// FUNCTION: ENGINE 0x105BFC70
	// NONMATCHING: register assignment (the engine keeps this in ebp, the page index in edi and the tag in ebx), 46 %
#ifdef NONMATCHING
	char* PagedMemoryStream::GetPageOrCreate(unsigned int address, unsigned int* offset)
	{
		*offset = address & 0xFFF;
		unsigned int index = address >> 12;
		if (index >= pages.size)
		{
			const char* tag = Page::AllocationTag();
			do
			{
				Page* page = static_cast<Page*>(Allocate(tag, 0x1000, 1));
				page = page != 0 ? static_cast<Page*>(memset(page, 0, 0x1000)) : 0;
				Page** slot = &pages.Append();
				if (slot != 0)
				{
					*slot = page;
				}
			}
			while (index >= pages.size);
		}
		return pages[index]->bytes;
	}
#endif

	// FUNCTION: ENGINE 0x105BFDF0
	// NONMATCHING: the join after the read of the bytes is shared in the engine, ours duplicates the store of the result, 89 %
#ifdef NONMATCHING
	void PagedMemoryStream::ReadAll(DynamicArray<char, unsigned short>** result)
	{
		unsigned int size;
		unsigned int savedPosition;
		GetSize(&size);
		GetPosition(&savedPosition);
		DynamicArray<char, unsigned short>* bytes = new DynamicArray<char, unsigned short>();
		char fill = 0;
		bytes->Resize(static_cast<unsigned short>(size), fill);
		if (bytes->size > 0)
		{
			char* start = bytes->data;
			Seek(0);
			Read(start, size);
			Seek(savedPosition);
		}
		*result = bytes;
	}
#endif

	// FUNCTION: ENGINE 0x105BF640
	bool PagedMemoryStream::GetSize(unsigned int* result)
	{
		*result = length;
		return true;
	}

	// FUNCTION: ENGINE 0x105BF650
	bool PagedMemoryStream::GetPosition(unsigned int* result)
	{
		*result = position;
		return true;
	}

	// FUNCTION: ENGINE 0x105BF660
	bool PagedMemoryStream::Seek(unsigned int newPosition)
	{
		if (newPosition <= length)
		{
			position = newPosition;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105BF680
	String PagedMemoryStream::GetDescription()
	{
		return String("PagedMemoryStream (unknown name)", 0);
	}
}
