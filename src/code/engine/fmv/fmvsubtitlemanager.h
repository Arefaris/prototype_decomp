// engine::FmvSubtitleManager (code/engine/fmv/fmvsubtitlemanager.cpp, the file named by the class's own reflection
// strings): the manager plays subtitles over a full-motion video. It is a content library object like the reflected
// game objects; its elements, FmvSubtitleManager::SubTitleEnty, carry the subtitle's id (a reflected string of
// SubTitleEnty::STRING_CAPACITY characters), the interval it is shown in and its text.
#ifndef ENGINE_FMV_FMVSUBTITLEMANAGER_H
#define ENGINE_FMV_FMVSUBTITLEMANAGER_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/stringmetatype.h"

namespace engine
{
	class StreamPackage;
	class FmvSubtitleManager : public content::MetaLoadObject
	{
	public:
		// One subtitle (0x10C bytes)
		struct SubTitleEnty
		{
			enum { STRING_CAPACITY = 0x100 };

			// 0x108C07F0: the interval the subtitle is not shown in yet (-1) and the text object it is up in
			SubTitleEnty() : startTime(-1.0f), endTime(-1.0f), unknown108(0)
			{
				subtitleId[0] = 0;
			}

			// 0x108C0500 / 0x108C0AD0: the class's name and version, and its reflected members
			static const content::ClassInfo* GetClassInfo();
			static const content::MemberList* GetMembers();

			char subtitleId[STRING_CAPACITY];   // +0x000
			float startTime;                    // +0x100
			float endTime;                      // +0x104
			int unknown108;                     // +0x108
		};

		// The class's reflected members
		static const content::ClassInfo* GetClassInfo();
		static const content::MemberList* GetMembers();

		// 0x108C1340 / 0x108C1390 (the deleting destructor is 0x108C1480): the array starts with room for ten subtitles
		FmvSubtitleManager();
		virtual ~FmvSubtitleManager();

		// 0x108C0CD0: shows the subtitles that belong to the time (the seconds into the movie) in the text objects
		// and takes down the ones whose time has passed
		void Update(float time);
		// 0x108C10B0: takes down every subtitle's text object and empties the array (name guess)
		void Reset();

		// The element array the reflected "subtitles" member is
		typedef container::ArrayDynamic<SubTitleEnty, container::AllocatorNew> SubTitleArray;

		SubTitleArray subtitles;
		// Not touched by the constructor (the object is 0x18 bytes)
		int unknown14;
	};
}

namespace engine
{
	// 0x108C1210: the stream package a movie's subtitles are kept in, the one named like the movie's file (null when
	// the path names no movie); name unknown
	StreamPackage* Unknown108C1210(const char* path);
	// 0x108C1130: the subtitle manager of that movie in the package's inventory, referenced for the caller (null
	// when the path names no movie or the package has none); name unknown
	FmvSubtitleManager* Unknown108C1130(const char* path, StreamPackage* package);
}

namespace content
{
	// The meta type of a string member of capacity characters: one instance per member
	StringMetaType* GetStringMetaType(int capacity, const char* code);

	// The element access of the manager's subtitle array for its meta type; its own copy here because the default
	// element the reflection inserts is kept in a static of the helper (Default)
	template<> class ArrayDynamicHelper<engine::FmvSubtitleManager::SubTitleArray> : public ArrayDynamicHelperBase
	{
	public:
		typedef engine::FmvSubtitleManager::SubTitleArray A;
		typedef A::Element T;

		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
		virtual void* GetConst(void* array, int index)
		{
			return &(*(A*)array)[index];
		}
		// the engine's copy (0x108C13C0)
		virtual void Insert(void* array, int index, int unused);
		virtual void Erase(void* array, int index, int unused)
		{
			A* a = (A*)array;
			a->Erase(a->begin + index);
		}
		virtual int Capacity(void* array)
		{
			return ((A*)array)->Capacity();
		}
		// the engine's copy (0x108C12A0)
		virtual void Expand(void* array, unsigned int count);
	};
}

#endif
