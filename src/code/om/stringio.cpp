// The binary form of a string (0x105C12E0).
#include "code/om/textvalue.h"

#include "code/om/metaproperty.h"
#include "code/om/metatype.h"

namespace om
{
	// FUNCTION: ENGINE 0x105C12E0
	// NONMATCHING: the engine builds the two texts in two constructor calls into a slot below the length and ours shares one call (58.1 %)
#ifdef NONMATCHING
	bool ReadBinary(BinaryStream* stream, String* value)
	{
		char buffer[0x400];
		unsigned int length;
		bool ok = ReadBinary(stream, &length);
		if (ok)
		{
			ok = stream->buffer->ReadRaw(buffer, length + 1);
			if (!ok)
			{
				*value = String("", 0);
			}
			else
			{
				*value = String(buffer, 1);
			}
		}
		return ok;
	}
#endif
}
