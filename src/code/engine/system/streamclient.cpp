// engine::StreamClient (RTTI name): a client of the stream manager that wants the packages whose tags match its own.
// The file name is a guess; the unit 0x1089B620 - 0x1089B6E0 holds the copies of its members the engine kept.
#include "code/engine/system/streampackage.h"

namespace engine
{
	// FUNCTION: ENGINE 0x1089B620
	void StreamClient::SetTags(const char* text)
	{
		tags.FromString(text);
	}

	// FUNCTION: ENGINE 0x1089B630
	void StreamClient::ClearTags()
	{
		tags.Clear();
	}

	// FUNCTION: ENGINE 0x1089B640
	StreamClient::StreamClient(const char* tagText)
	{
		unknown18 = false;
		unknown19 = false;
		tags.FromString(tagText);
	}

	// FUNCTION: ENGINE 0x1089B670
	StreamClient::~StreamClient()
	{
	}

	// FUNCTION: ENGINE 0x1089B690
	StreamClient::StreamClient()
	{
		unknown18 = false;
		unknown19 = false;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1089B6B0
