#include "code/engine/audio/streamserver.h"

namespace om
{
	// 0x105CB420 (path.cpp's unit; name guessed): the second path appended to the first
	String CombinePaths(const String& directory, const String& file);
}

namespace engine
{
	// FUNCTION: ENGINE 0x10844EB0
	StreamServer::StreamServer()
	{
	}

	// FUNCTION: ENGINE 0x10844EC0
	// EQUIVALENT: the engine destroys the directory string before the temporary of the sum, ours after it (the same
	// destructors on the same objects), 98.2 %
	om::String StreamServer::GetPath(const om::String& name)
	{
		om::String extension(".p3d", false);
		om::String directory("audio\\english\\audiofile\\", false);
		return om::CombinePaths(directory, name + extension);
	}

	// FUNCTION: ENGINE 0x10844F30
	void StreamServer::Slot1(void* argument)
	{
	}
}
