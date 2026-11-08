// content::NameMetaType: the meta type of the four kinds of name a reflected class can hold (unit 0x105FCC70 - 0x105FD3A2;
// only the small slots so far; the file name is guessed).
#include "code/content/metatype.h"
#include "code/core/heap.h"

namespace content
{
	// FUNCTION: ENGINE 0x105FCC70
	NameMetaType::NameMetaType(bool unknown8, bool unknown9, const char* code)
		: MetaType(code)
	{
		flag8 = unknown8;
		flag9 = unknown9;
	}

	// FUNCTION: ENGINE 0x105FCDE0
	int NameMetaType::Unknown9(int a, int b)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x105FCDF0
	void NameMetaType::WriteBinaryShort(WriteContext* context, unsigned int key)
	{
		unsigned int value = key;
		context->writer->Write(&value, 1, 4);
	}

	// FUNCTION: ENGINE 0x105FD350
	void NameMetaType::Destroy(void* object)
	{
		if (flag8)
		{
			if (flag9)
			{
				core::FreeAligned(object);
				return;
			}
			if (object != 0)
			{
				::operator delete(object);
				return;
			}
		}
		else
		{
			if (flag9)
			{
				core::FreeAligned(object);
				return;
			}
			if (object != 0)
			{
				::operator delete(object);
			}
		}
	}
}
