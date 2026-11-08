// content::NameMetaType: the meta type of the four kinds of name a reflected class can hold (unit 0x105FCC70 - 0x105FD3A2;
// only the small slots so far; the file name is guessed).
#include "code/content/metatype.h"
#include "code/core/hash.h"
#include "code/core/heap.h"
#include "code/core/name.h"
#include "code/scaleformp3d/flashfilecache.h"

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

namespace scaleformp3d
{
	// FUNCTION: ENGINE 0x105FCE40
	FlashFileKey::FlashFileKey(const char* text, int unknown)
	{
		low = 0;
		high = 0;
		unsigned __int64 hash = core::Hash64NoCase(text, 0);
		low = static_cast<unsigned int>(hash);
		high = static_cast<unsigned int>(hash >> 32);
	}
}

namespace core
{
	// FUNCTION: ENGINE 0x105FCED0
	void Name<CaseInsensitiveKey32>::SetText(const char* text)
	{
		hash = Hash32NoCase(text, 0);
	}
}
