// engine::FEEventHandler (RTTI name): hands the events of the online services and of the game database on to the front
// end's movie. It listens to the online services (OLS::Callback) and to the game database (DBObserver). The movie
// registers the events it wants to hear through the script functions fe_RegisterEvent and fe_UnregisterEvent: an event
// of the online services is a category (Profile, Match, Peer ...) the movie turns on by name, one of the database is a
// subject by name. Unit 0x108E1260 - 0x108E1BC0 (no assert path; file name and member names guessed).
#ifndef ENGINE_FRONTEND_FEEVENTHANDLER_H
#define ENGINE_FRONTEND_FEEVENTHANDLER_H

#include "code/engine/dbobserver.h"
#include "code/engine/online/ols.h"

namespace engine
{
	// The subjects the movie registered, by the hash of their names: the same code as proto::MidgroundMap, which the linker
	// shares (the values are the names the handler keeps)
	class FEEventMap
	{
	public:
		struct Iterator
		{
			Iterator(FEEventMap* newMap)
			{
				map = newMap;
				key = 0;
				index = 0;
				current = 0;
				step = 0;
			}

			// 0x102DD6F0: the name the key is stored under, null when there is none
			char* Find(const unsigned __int64& newKey);

			FEEventMap* map;
			int unknown4;
			unsigned __int64 key;
			int index;
			int current;
			int step;
		};

		// 0x102DE010: a map of at least that many slots (the other numbers are the load limits)
		FEEventMap(unsigned int newCapacity, int a, int b);
		~FEEventMap()
		{
			delete[] buckets;
			delete[] keys;
		}
		// 0x102DDAD0
		void Insert(const unsigned __int64& key, char* name);
		// 0x1060C340: forgets the key
		void Remove(const unsigned __int64& key, char* name);

		unsigned int capacity;
		int count;
		int unknown8;
		int unknownC;
		int unknown10;
		int unknown14;
		int unknown18;
		char** buckets;  // +0x1C
		unsigned __int64* keys;  // +0x20
		char* sentinel;  // +0x24
	};

	// One category of the online services' events (0x111E10E8, 13 of them; 0x10 bytes): the movie turns it on by name
	struct FEEventCategory
	{
		const char* name;  // +0
		bool enabled;  // +4
		const char** events;  // +8: the names of the events of the category
		int count;  // +0xC
	};
	extern FEEventCategory gFEEventCategories[13];
	// The first characters of the kinds a registration names (0x111E0F84 and 0x111E0F88: the strings "OLS" and "GDB")
	extern const char* gFEOnlineKind;
	extern const char* gFEDatabaseKind;

	class FEOverlay;
	class FrontEnd;

	// 0x10872840: calls a function of the front end's movie with a format and its arguments (the format "%s%s%s%d%s")
	void Unknown10872840(FrontEnd* frontEnd, const char* function, const char* format, ...);

	class FEEventHandler : public OLS::Callback, public DBObserver
	{
	public:
		// One name the movie registered (0x20 bytes)
		struct NameSlot
		{
			char text[0x20];
		};

		// 0x108E1890
		explicit FEEventHandler(int newCount);
		// 0x108E1400 (not virtual: the handler is released by ReleaseSubsystemAA68)
		~FEEventHandler();

		// vftable slot 0 of the online callback (0x108E1330)
		virtual void OnMessage(OLSMessage* message);
		// The movie asks for a kind of event by name (the script functions; 0x108E1780 and 0x108E1A30)
		virtual void RegisterEvent(const char* kind, const char* name);
		virtual void UnregisterEvent(const char* kind, const char* name);
		// The database observer's slots (0x108E1660 and 0x108E1B00)
		virtual void OnDBSlot0(int a, int b);
		virtual void OnDBSlot1(int a, int b);

		int count;  // +0xC
		NameSlot* names;  // +0x10
		FEEventMap map;  // +0x14
	};

	// The handler (0x1131AA68)
	extern FEEventHandler* gFEEventHandler;
	// 0x108E1B80: makes the handler once (the number is how many database subjects the movie can register)
	void CreateFEEventHandler(int count);
	// 0x108E1320
	FEEventHandler* GetFEEventHandler();
}

#endif
