// The content system's load manager: the loaders the chunk ids are registered under. Only what other units use is
// declared; the class name is a guess.
#ifndef CONTENT_LOADMANAGER_H
#define CONTENT_LOADMANAGER_H

#include "code/content/loadinventory.h"

namespace container
{
	class String;
}

namespace content
{
	class LoadStream;
	class ObjectLoader;

	// A loader that reads a whole file by its extension (RTTI: content::FileLoader, a load object)
	class FileLoader : public LoadObject
	{
	};

	// A load under way (a reference counted interface; only what the users need is declared)
	class LoadJob : public core::IRefCount
	{
	public:
		// Slot 3 (the argument is 0 where the engine calls it; meaning unknown)
		virtual void Slot3(int unused);
		// 0x106089E0: 3 once the load is done
		int GetStatus();
		// 0x106089D0: the inventory the load put its objects in
		LoadInventory* GetInventory();
		// 0x10608B40: takes the stream the job reads from
		void SetStream(LoadStream* stream);
	};

	class LoadManager
	{
	public:
		// 0x10607BD0: the loader registered for the chunk id
		ObjectLoader* GetLoader(unsigned int chunkId);
		// 0x10608370 / 0x10608910: registers a loader for the chunk id / takes the loaders of that id out again
		void AddLoader(ObjectLoader* loader, unsigned int chunkId);
		void RemoveLoader(unsigned int chunkId);
		// 0x106083B0 / 0x10608800: registers a file loader for the files with an extension / takes it out again
		void AddFileLoader(FileLoader* loader, const char* extension);
		void RemoveFileLoader(FileLoader* loader);
		// 0x106087D0: takes a chunk loader out again
		void RemoveLoader(ObjectLoader* loader);
		// 0x10607660: starts loading what the request (a name, a stream and a few words) names; waits for it when
		// the last argument is set
		void Load(const container::String* request, LoadJob** job, bool wait);
		// 0x106070B0: gives the loading thread a turn (waits a moment when called from another thread)
		void Yield();
		// 0x10606D60: does nothing
		void Idle();
		// 0x10606D30: whether the calling thread is the loading thread (it reads nothing of the object)
		bool IsCurrentThread();
	};

	// 0x11276A64
	extern LoadManager* gLoadManager;
}

#endif
