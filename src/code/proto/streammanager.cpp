// proto::StreamManager: see the header. The file name, the layout and the names are guesses.
#include "code/proto/streammanager.h"

namespace proto
{
	// FUNCTION: ENGINE 0x1056F780
	StreamManager::StreamManager() : unknown4(0), unknown8(0), unknownC(-1)
	{
		gProtoStreamManager = this;
	}

	// FUNCTION: ENGINE 0x1056F7B0
	StreamManager::~StreamManager()
	{
		gProtoStreamManager = 0;
	}
}

// Kept copies (template instances and wrappers of this unit):
// FUNCTION: ENGINE 0x1056FA70
