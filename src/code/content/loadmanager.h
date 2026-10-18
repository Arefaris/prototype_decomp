// The content system's load manager: the loaders the chunk ids are registered under. Only what other units use is
// declared; the class name is a guess.
#ifndef CONTENT_LOADMANAGER_H
#define CONTENT_LOADMANAGER_H

namespace content
{
	class ObjectLoader;

	class LoadManager
	{
	public:
		// 0x10607BD0: the loader registered for the chunk id
		ObjectLoader* GetLoader(unsigned int chunkId);
		// 0x10606D30: whether the calling thread is the loading thread (it reads nothing of the object)
		bool IsCurrentThread();
	};

	// 0x11276A64
	extern LoadManager* gLoadManager;
}

#endif
