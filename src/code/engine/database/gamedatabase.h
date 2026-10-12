// engine::GameDatabase (RTTI): the game's settings and progress database. Each value is a subject (DBSubject, keyed
// by the 64-bit hash of its name) of one of four types (int, float, string, wide string) with values per index and
// player; observers (DBObserver) are told about changes. Profile values go through GameDBStorage, online ones through
// OnlineGameDBHelper; scripts reach the database through the db_* functions. Unit 0x107F6B30 - 0x107F9F50 (no assert
// path; directory and file name are guesses). The script function names are original, the others are guesses.
#ifndef ENGINE_DATABASE_GAMEDATABASE_H
#define ENGINE_DATABASE_GAMEDATABASE_H

#include "code/container/map.h"
#include "code/container/slist.h"
#include "code/core/name.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/dbobserver.h"

namespace engine
{
	class DBSubject;
	class GameDatabase;

	// How a subject is shown and edited (0x10842F10 constructs it, 0x10843310 copies it; another unit; field meanings
	// unknown)
	class DBSubjectInfo
	{
	public:
		DBSubjectInfo(bool flag, int a, int b);
		DBSubjectInfo(const DBSubjectInfo& other);

		bool flag;
		int a;
		int b;
	};

	// The value records the online helper and the storage exchange: player, index, type, then the value (an int, a
	// float or the characters of a string)
	struct DBRecord
	{
		unsigned char player;
		unsigned char index;
		char type;
		unsigned char unused3;
		union
		{
			int intValue;
			float floatValue;
			char text[4];
		};
	};

	// One database value (another unit, 0x10843330 - 0x10843F50, with base class functions at 0x10893240 -
	// 0x10893BE0)
	class DBSubject
	{
	public:
		enum Type
		{
			TYPE_INT,
			TYPE_FLOAT,
			TYPE_STRING,
			TYPE_WIDE_STRING
		};

		DBSubject();
		~DBSubject();
		// Set the subject up under name (its category, two per-category settings, the initial value and the editing
		// information); key receives the name's hash
		unsigned __int64* InitInt(unsigned __int64* key, const core::Name<core::CaseSensitiveKey>& name, int category,
			int a, int b, int value, const DBSubjectInfo& info);
		unsigned __int64* InitFloat(unsigned __int64* key, const core::Name<core::CaseSensitiveKey>& name, int category,
			int a, int b, float value, const DBSubjectInfo& info);
		unsigned __int64* InitString(unsigned __int64* key, const core::Name<core::CaseSensitiveKey>& name,
			int category, int a, int b, const char* value, int length, const DBSubjectInfo& info);

		int GetInt(unsigned int player, unsigned int index);
		float GetFloat(unsigned int player, unsigned int index);
		const char* GetString(unsigned int player, unsigned int index);
		const wchar_t* GetWideString(unsigned int player, unsigned int index);
		void SetInt(unsigned int player, int value, unsigned int index);
		void SetFloat(unsigned int player, float value, unsigned int index);
		void SetString(unsigned int player, const char* value, unsigned int index);
		void SetWideString(unsigned int player, const wchar_t* value, unsigned int index);
		void ResetInt(int value);
		void ResetFloat(float value);
		void Reset(unsigned int player);
		void ClearObservers();
		void ClearValues();
		bool IsLocked();
		void AddObserver(DBObserver* observer, int a, int b);
		void RemoveObserver(void* owner);
		bool IsValidPlayer(unsigned int player);
		bool IsShared();

		core::Name<core::CaseSensitiveKey> GetName() const
		{
			return name;
		}
		DBSubject* GetLinked() const
		{
			return linked;
		}

		int unknown0;
		int id;
		core::Name<core::CaseSensitiveKey> name;
		int scope;
		DBSubject* linked;
		void* observers;
		void* unknown1C;
		bool unknown20;
		unsigned char count;
		int type;
		int stride;
		int unknown2C;
		int unknown30;
		bool unknown34;
		int category;
		bool persistent;
	};

	// The profile storage (another unit, RTTI engine::GameDBStorage; 0x20 bytes)
	class GameDBStorage : public DBObserver
	{
	public:
		class GameDBStorageCallback
		{
		public:
			// Builds the profile data of player (the caller frees it)
			virtual void* BuildProfile(unsigned int player) = 0;
			virtual void OnLoadValues(unsigned __int64 key, unsigned int player, int count, const void* values)
			{
			}
			virtual void OnSlot2(int a)
			{
			}
			virtual void OnSlot3(bool a, int b)
			{
			}
			virtual void OnSlot4(int a)
			{
			}
			virtual void OnSlot5(int a)
			{
			}
			virtual void OnSlot6(int a)
			{
			}
		};

		GameDBStorage();
		~GameDBStorage();
		void SetCallback(GameDBStorageCallback* callback);
		bool IsOperationInProgress();
		void SlotA(int a);
		// 0x108A5BE0: writes the values of player of subject at buffer, returns the bytes written
		int WriteSubject(unsigned int player, DBSubject* subject, void* buffer);

		virtual void OnDBSlot0(int a, int b);
		virtual void OnDBSlot1(int a, int b);
		virtual void Slot2();
		virtual void Slot3(int a, int b);
		virtual void Slot4(int a);
		virtual bool Save(unsigned int player, void* buffer, int a, int b, int c, int d, int e);
		virtual bool Slot6(int a, int b, int c);
		virtual bool Slot7(int a, int b);

		int unknown4[7];
	};

	// The online database helper (another unit, RTTI engine::OnlineGameDBHelper; 0x64 bytes)
	class OnlineGameDBHelper
	{
	public:
		class DataCallback
		{
		public:
			virtual void OnData(DBSubject* subject, const DBRecord* record, int unused)
			{
			}
		};

		OnlineGameDBHelper(int a, int b, int c, int d);
		~OnlineGameDBHelper();
		void AddSubject(DBSubject* subject);
		void RemoveSubject(DBSubject* subject);
		void Send(DBSubject* subject, unsigned int player, const DBRecord* record, int size);
		void OnInput(unsigned int id, int value);
		void Clear();

		void* vftable0;
		int unknown4[7];
		DataCallback* callback;
		int unknown24[16];
	};

	// The front end's Flash movies (another unit); a callback answers a call from ActionScript
	class FEMovie
	{
	public:
		struct Value
		{
			int type;
			int unknown4;
			union
			{
				const char* string;
				double number;
			};
		};

		struct Callback
		{
			virtual void OnCall(void* movie, const Value* arguments, unsigned int count, Value* result) = 0;
		};

		// 0x10872860 / 0x108728D0 (another unit): binds / unbinds the ActionScript function name
		static void AddCallback(const char* name, Callback* callback, int unknown);
		static void RemoveCallback(const char* name);
	};

	// Told about storage operations (GameDatabase forwards the storage callbacks to it; interface name unknown)
	class GameDBStorageListener
	{
	public:
		virtual void Slot0() = 0;
		virtual bool Slot1(int a) = 0;
		virtual void Slot2(bool a) = 0;
		virtual void Slot3(int a) = 0;
		virtual void Slot4(int a) = 0;
	};

	// What GameDatabase::Create is given
	struct GameDatabaseParams
	{
		bool unknown0;
		int profileSize;
		int bufferSize;
		int helperA;
		int helperB;
		int unknown14;
	};

	class GameDatabase : public controller::InputSystem::InputCallback, public OnlineGameDBHelper::DataCallback,
		public GameDBStorage::GameDBStorageCallback, public FEMovie::Callback
	{
	public:
		typedef container::AllocatorCoreStatic<0x80, 16> Allocator;
		typedef container::Map<unsigned __int64, DBSubject*, Allocator> SubjectMap;
		typedef container::SList<DBSubject*, Allocator> SubjectList;

		static void Create(const GameDatabaseParams& params);
		static void Destroy();

		explicit GameDatabase(const GameDatabaseParams& params);
		~GameDatabase();

		virtual void OnNotify(int a, int b, int c);
		virtual void OnData(DBSubject* subject, const DBRecord* record, int unused);
		virtual void* BuildProfile(unsigned int player);
		virtual void OnLoadValues(unsigned __int64 key, unsigned int player, int count, const void* values);
		virtual void OnSlot2(int a);
		virtual void OnSlot3(bool a, int b);
		virtual void OnSlot4(int a);
		virtual void OnCall(void* movie, const FEMovie::Value* arguments, unsigned int count, FEMovie::Value* result);

		DBSubject* AddIntSubject(const core::Name<core::CaseSensitiveKey>& name, int category, int value,
			DBSubjectInfo info);
		DBSubject* AddFloatSubject(const core::Name<core::CaseSensitiveKey>& name, int category, float value,
			DBSubjectInfo info);
		DBSubject* AddStringSubject(const core::Name<core::CaseSensitiveKey>& name, int category,
			const char* value, int length, DBSubjectInfo info);
		bool RemoveSubject(unsigned __int64 key, DBSubject* subject);
		bool ReleaseSubject(const core::Name<core::CaseSensitiveKey>& name);
		DBSubject* AddObserver(const core::Name<core::CaseSensitiveKey>& name, DBObserver* observer, int a, int b);
		void RemoveObserver(const core::Name<core::CaseSensitiveKey>& name, void* owner);
		void Reset();

		int GetInt(const core::Name<core::CaseSensitiveKey>& name, unsigned int player, unsigned int index);
		float GetFloat(const core::Name<core::CaseSensitiveKey>& name, unsigned int player, unsigned int index);
		const char* GetString(const core::Name<core::CaseSensitiveKey>& name, unsigned int player, unsigned int index);
		const wchar_t* GetWideString(const core::Name<core::CaseSensitiveKey>& name, unsigned int player,
			unsigned int index);
		bool Exists(const core::Name<core::CaseSensitiveKey>& name, unsigned int player, unsigned int index);
		void SetInt(const core::Name<core::CaseSensitiveKey>& name, unsigned int player, int value, unsigned int index);
		void SetFloat(const core::Name<core::CaseSensitiveKey>& name, unsigned int player, float value,
			unsigned int index);
		void SetString(const core::Name<core::CaseSensitiveKey>& name, unsigned int player, const char* value,
			unsigned int index);
		void SetId(const core::Name<core::CaseSensitiveKey>& name, int id);
		void ResetInt(const core::Name<core::CaseSensitiveKey>& name, int value);
		void ResetFloat(const core::Name<core::CaseSensitiveKey>& name, float value);
		void ResetSubjects(int category, unsigned int player);
		void ResetSubject(const core::Name<core::CaseSensitiveKey>& name, unsigned int player);
		void ResetProfileSubjects(unsigned int player);
		void ResetGameSubjects(unsigned int player);
		bool IsSettable(const char* name, unsigned int player);
		bool IsStorageOperationInProgress();

		// The script functions (db_GetInt, ...): this is not used, they go through gGameDatabase
		int ScriptGetInt(const char* name, unsigned int player, unsigned int index);
		float ScriptGetFloat(const char* name, unsigned int player, unsigned int index);
		const char* ScriptGetString(const char* name, unsigned int player, unsigned int index);
		void ScriptSetInt(const char* name, unsigned int player, int value, unsigned int index);
		void ScriptSetFloat(const char* name, unsigned int player, float value, unsigned int index);
		void ScriptSetString(const char* name, unsigned int player, const char* value, unsigned int index);
		void ScriptResetSubject(const char* name, unsigned int player);

		void LinkSubjects(DBSubject* a, DBSubject* b);
		int FindPlayer(unsigned int id, bool local);
		void StoreValue(DBSubject* subject, unsigned int player, const void* value, int size, unsigned int index);
		void RegisterOnline(DBSubject* subject, int category);
		void SetSubjectId(DBSubject* subject, int id);
		void StorageSlot3(int a, int b);
		void StorageSlot4(int a);
		void StorageSlotA(int a);
		void SetStorageListener(GameDBStorageListener* listener);
		void SetBufferSize(int size);
		void PushMode(unsigned char newMode);
		void PopMode();
		void SetIntValue(DBSubject* subject, unsigned int player, int value, unsigned int index);
		void SetFloatValue(DBSubject* subject, unsigned int player, float value, unsigned int index);
		void SetStringValue(DBSubject* subject, unsigned int player, const char* value, unsigned int index);
		bool StorageSlot6(int a, int b, int c);
		bool StorageSlot7(int a, int b);
		DBSubject* CreateIntSubject(const core::Name<core::CaseSensitiveKey>& name, int category, int value,
			const DBSubjectInfo& info);
		DBSubject* CreateFloatSubject(const core::Name<core::CaseSensitiveKey>& name, int category, float value,
			const DBSubjectInfo& info);
		DBSubject* CreateStringSubject(const core::Name<core::CaseSensitiveKey>& name, int category,
			const char* value, int length, const DBSubjectInfo& info);
		int WriteSubjects(unsigned int player, void* buffer, unsigned int size, bool profile);
		int FillBuffer(unsigned int player, int* buffer, int size);
		bool Save(unsigned int player, int a, int b, int c, int d, int e);

		bool inputMode;
		SubjectMap* subjects;
		SubjectList* released;
		unsigned char modeStack[10];
		unsigned int modeCount;
		unsigned char mode;
		OnlineGameDBHelper onlineHelper;
		GameDBStorage storage;
		unsigned int profileSize;
		int bufferSize;
		GameDBStorageListener* storageListener;
		int categoryA[4];
		int categoryB[4];
	};

	// The database (0x11283CB4)
	extern GameDatabase* gGameDatabase;
}

#endif
