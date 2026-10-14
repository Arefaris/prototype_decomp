#include "code/engine/database/gamedatabase.h"
#include "code/core/hash.h"
#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/system/enginememory.h"
#include <string.h>

namespace engine
{
	// The online services (another unit; names guessed): the signed-in users by controller id
	class OLSUser
	{
	public:
		int unknown0[3];
		unsigned int controller;
	};

	class OLSUserList
	{
	public:
		// 0x10888EC0
		OLSUser* Find(unsigned int id);
	};

	class OLS
	{
	public:
		// 0x108441E0
		static OLS* Get();

		int unknown0[0x78 / 4];
		OLSUserList* users;
	};

	// A wide string either borrowed or copied into an owned buffer (another unit, 0x108A5560 - 0x108A5640; names
	// guessed)
	class WideStringBuffer
	{
	public:
		WideStringBuffer();
		~WideStringBuffer();
		void Borrow(const wchar_t* text);
		void Copy(const wchar_t* text);

		const wchar_t* text;
		unsigned int capacity;
	};

	// The platform side of the database (another unit, RTTI engine::GameDBHelper; names guessed)
	class GameDBHelper
	{
	public:
		struct Config
		{
			// 0x10894450
			Config();

			int unknown0;
		};

		// 0x108944D0: becomes the current helper
		explicit GameDBHelper(const Config& config);
		// 0x10894460
		static GameDBHelper* Get();

		virtual void Slot0();
		virtual ~GameDBHelper();
		virtual void Slot2();
		virtual void Start();
		virtual void Stop();

		int unknown4;
		int unknown8;
	};

	// 0x10848E70 (another unit): whether the command line has the option
	bool HasCommandLineOption(const char* option);

	// The extra data writer behind the storage listener (interface unknown)
	class GameDBExtraWriter
	{
	public:
		virtual void Write(unsigned int player, void* buffer, int size) = 0;
	};

	GameDatabase* gGameDatabase;

	// FUNCTION: ENGINE 0x107F6C30
	void GameDatabase::LinkSubjects(DBSubject* a, DBSubject* b)
	{
		a->linked = b;
		b->linked = a;
	}

	// FUNCTION: ENGINE 0x107F6C50
	// EQUIVALENT: register choice and block layout (the engine saves edi on entry and keeps the player in edi and id in
	// esi; ours keeps the player in esi and saves edi only on the local path)
	int GameDatabase::FindPlayer(unsigned int id, bool local)
	{
		int player = -1;
		if (local)
		{
			if (controller::InputSystem::IsLocal(controller::InputSystem::Get()->slots[id].id))
			{
				player = 0;
				OLSUserList* users = OLS::Get()->users;
				if (users->Find(id) == 0)
				{
					return -1;
				}
			}
		}
		else
		{
			OLSUserList* users = OLS::Get()->users;
			if (users->Find(id) == 0)
			{
				return 0;
			}
			users = OLS::Get()->users;
			OLSUser* user = users->Find(id);
			return controller::InputSystem::Get()->FindSlot(user->controller);
		}
		return player;
	}

	// FUNCTION: ENGINE 0x107F6CF0
	void GameDatabase::OnData(DBSubject* subject, const DBRecord* record, int unused)
	{
		const char* data = record->text;
		switch (record->type)
		{
		case DBSubject::TYPE_INT:
			subject->SetInt(record->player, *(const int*)data, record->index);
			break;
		case DBSubject::TYPE_FLOAT:
			subject->SetFloat(record->player, *(const float*)data, record->index);
			break;
		case DBSubject::TYPE_STRING:
			subject->SetString(record->player, data, record->index);
			break;
		case DBSubject::TYPE_WIDE_STRING:
			subject->SetWideString(record->player, (const wchar_t*)data, record->index);
			break;
		}
	}

	// FUNCTION: ENGINE 0x107F6D80
	void GameDatabase::StoreValue(DBSubject* subject, unsigned int player, const void* value, int size,
		unsigned int index)
	{
		DBRecord* record = (DBRecord*)operator new[](size + 4, 1);
		record->player = (unsigned char)player;
		record->index = (unsigned char)index;
		record->type = (char)subject->type;
		record->unused3 = 0;
		memcpy(record->text, value, size);
		onlineHelper.Send(subject, player, record, size + 4);
		operator delete[](record);
	}

	// FUNCTION: ENGINE 0x107F6DF0
	void GameDatabase::RegisterOnline(DBSubject* subject, int category)
	{
		if (subject->id != -1 && (category == 0 || category == 3))
		{
			onlineHelper.AddSubject(subject);
		}
	}

	// FUNCTION: ENGINE 0x107F6E20
	void GameDatabase::SetSubjectId(DBSubject* subject, int id)
	{
		subject->id = id;
	}

	// FUNCTION: ENGINE 0x107F6E30
	// EQUIVALENT: scheduling (the engine adds the member offset to ecx before loading the vftable, ours loads the
	// vftable through [ecx + 0x98] first)
	void GameDatabase::StorageSlot3(int a, int b)
	{
		GameDBStorage* target = &storage;
		target->Slot3(a, b);
	}

	// FUNCTION: ENGINE 0x107F6E40
	// EQUIVALENT: scheduling (as StorageSlot3)
	void GameDatabase::StorageSlot4(int a)
	{
		GameDBStorage* target = &storage;
		target->Slot4(a);
	}

	// FUNCTION: ENGINE 0x107F6E50
	void GameDatabase::StorageSlotA(int a)
	{
		storage.SlotA(a);
	}

	// FUNCTION: ENGINE 0x107F6E60
	void GameDatabase::OnSlot2(int a)
	{
		if (storageListener != 0)
		{
			storageListener->Slot3(a);
		}
	}

	// FUNCTION: ENGINE 0x107F6E80
	void GameDatabase::OnSlot4(int a)
	{
		if (storageListener != 0)
		{
			storageListener->Slot4(a);
		}
	}

	// FUNCTION: ENGINE 0x107F6EA0
	void GameDatabase::OnSlot3(bool a, int b)
	{
		if (storageListener != 0)
		{
			if (a)
			{
				a = storageListener->Slot1(b) != 0;
			}
			if (storageListener != 0)
			{
				storageListener->Slot2(a);
			}
		}
	}

	// FUNCTION: ENGINE 0x107F6EF0
	void GameDatabase::SetStorageListener(GameDBStorageListener* listener)
	{
		storageListener = listener;
	}

	// FUNCTION: ENGINE 0x107F6F00
	void GameDatabase::SetBufferSize(int size)
	{
		bufferSize = size;
	}

	// FUNCTION: ENGINE 0x107F6F10
	bool GameDatabase::IsStorageOperationInProgress()
	{
		return storage.IsOperationInProgress();
	}

	// FUNCTION: ENGINE 0x107F6F20
	void GameDatabase::PushMode(unsigned char newMode)
	{
		if (modeCount < 10)
		{
			modeStack[modeCount] = mode;
			modeCount++;
			mode = newMode;
		}
	}

	// FUNCTION: ENGINE 0x107F6F40
	void GameDatabase::PopMode()
	{
		if (modeCount > 0)
		{
			modeCount--;
			mode = modeStack[modeCount];
		}
	}

	// FUNCTION: ENGINE 0x107F71F0
	// EQUIVALENT: the engine spills the bool scope == 1 to a stack slot before pushing the call arguments, ours
	// computes it in place
	void GameDatabase::SetIntValue(DBSubject* subject, unsigned int player, int value, unsigned int index)
	{
		if (subject->IsValidPlayer(player))
		{
			DBSubject* linked = subject->linked;
			if (!subject->IsShared())
			{
				subject->SetInt(player, value, index);
			}
			else
			{
				StoreValue(subject, player, &value, 4, index);
			}
			int scope = subject->scope;
			if ((scope == 1 || scope == 0) && linked != 0)
			{
				bool local = scope == 1;
				int linkedPlayer = FindPlayer(player, local);
				if (linkedPlayer != -1)
				{
					if (!linked->IsShared())
					{
						linked->SetInt(linkedPlayer, value, index);
					}
					else
					{
						StoreValue(linked, linkedPlayer, &value, 4, index);
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x107F72B0
	// EQUIVALENT: bool spill as SetIntValue
	void GameDatabase::SetFloatValue(DBSubject* subject, unsigned int player, float value, unsigned int index)
	{
		if (subject->IsValidPlayer(player))
		{
			DBSubject* linked = subject->linked;
			if (!subject->IsShared())
			{
				subject->SetFloat(player, value, index);
			}
			else
			{
				StoreValue(subject, player, &value, 4, index);
			}
			int scope = subject->scope;
			if ((scope == 1 || scope == 0) && linked != 0)
			{
				bool local = scope == 1;
				int linkedPlayer = FindPlayer(player, local);
				if (linkedPlayer != -1)
				{
					if (!linked->IsShared())
					{
						linked->SetFloat(linkedPlayer, value, index);
					}
					else
					{
						StoreValue(linked, linkedPlayer, &value, 4, index);
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x107F7380
	// EQUIVALENT: bool spill as SetIntValue
	void GameDatabase::SetStringValue(DBSubject* subject, unsigned int player, const char* value, unsigned int index)
	{
		if (subject->IsValidPlayer(player))
		{
			DBSubject* linked = subject->linked;
			if (!subject->IsShared())
			{
				subject->SetString(player, value, index);
			}
			else
			{
				StoreValue(subject, player, value, core::StrLen(value) + 1, index);
			}
			int scope = subject->scope;
			if ((scope == 1 || scope == 0) && linked != 0)
			{
				bool local = scope == 1;
				int linkedPlayer = FindPlayer(player, local);
				if (linkedPlayer != -1)
				{
					if (!linked->IsShared())
					{
						linked->SetString(linkedPlayer, value, index);
					}
					else
					{
						StoreValue(linked, linkedPlayer, value, core::StrLen(value) + 1, index);
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x107F7460
	bool GameDatabase::StorageSlot6(int a, int b, int c)
	{
		if (IsStorageOperationInProgress())
		{
			return false;
		}
		return storage.Slot6(a, b, c);
	}

	// FUNCTION: ENGINE 0x107F7490
	bool GameDatabase::StorageSlot7(int a, int b)
	{
		if (IsStorageOperationInProgress())
		{
			return false;
		}
		return storage.Slot7(a, b);
	}

	// FUNCTION: ENGINE 0x107F8350
	DBSubject* GameDatabase::CreateIntSubject(const core::Name<core::CaseSensitiveKey>& name, int category, int value,
		const DBSubjectInfo& info)
	{
		DBSubject* subject = new (0x80) DBSubject;
		unsigned __int64 key;
		subjects->Insert(SubjectMap::Pair(*subject->InitInt(&key, name, category, categoryB[category],
			categoryA[category], value, info), subject));
		return subject;
	}

	// FUNCTION: ENGINE 0x107F83E0
	DBSubject* GameDatabase::CreateFloatSubject(const core::Name<core::CaseSensitiveKey>& name, int category,
		float value, const DBSubjectInfo& info)
	{
		DBSubject* subject = new (0x80) DBSubject;
		unsigned __int64 key;
		subjects->Insert(SubjectMap::Pair(*subject->InitFloat(&key, name, category, categoryB[category],
			categoryA[category], value, info), subject));
		return subject;
	}

	// FUNCTION: ENGINE 0x107F8470
	DBSubject* GameDatabase::CreateStringSubject(const core::Name<core::CaseSensitiveKey>& name, int category,
		const char* value, int length, const DBSubjectInfo& info)
	{
		DBSubject* subject = new (0x80) DBSubject;
		unsigned __int64 key;
		subjects->Insert(SubjectMap::Pair(*subject->InitString(&key, name, category, categoryB[category],
			categoryA[category], value, length, info), subject));
		return subject;
	}

	// FUNCTION: ENGINE 0x107F8500
	bool GameDatabase::ReleaseSubject(const core::Name<core::CaseSensitiveKey>& name)
	{
		unsigned __int64 key = name.GetHash();
		SubjectMap::MapNode* node = (SubjectMap::MapNode*)subjects->TreeBase::Find(SubjectMap::CompareKey, &key);
		if (node == 0 || node->pair.value == 0)
		{
			return false;
		}
		node->pair.value->ClearObservers();
		if (node->pair.value->linked != 0)
		{
			node->pair.value->linked->ClearObservers();
			released->PushBack(node->pair.value->GetLinked());
		}
		released->PushBack(node->pair.value);
		return true;
	}

	// FUNCTION: ENGINE 0x107F85B0
	DBSubject* GameDatabase::AddObserver(const core::Name<core::CaseSensitiveKey>& name, DBObserver* observer, int a,
		int b)
	{
		unsigned __int64 key = name.GetHash();
		SubjectMap::MapNode* node = (SubjectMap::MapNode*)subjects->TreeBase::Find(SubjectMap::CompareKey, &key);
		if (node == 0 || node->pair.value->IsLocked())
		{
			return 0;
		}
		DBSubject* subject = node->pair.value;
		subject->AddObserver(observer, a, b);
		return subject;
	}

	// FUNCTION: ENGINE 0x107F8620
	void GameDatabase::RemoveObserver(const core::Name<core::CaseSensitiveKey>& name, void* owner)
	{
		unsigned __int64 key = name.GetHash();
		SubjectMap::MapNode* node = (SubjectMap::MapNode*)subjects->TreeBase::Find(SubjectMap::CompareKey, &key);
		if (node != 0 && !node->pair.value->IsLocked())
		{
			node->pair.value->RemoveObserver(owner);
		}
	}

	// FUNCTION: ENGINE 0x107F8680
	void GameDatabase::SetInt(const core::Name<core::CaseSensitiveKey>& name, unsigned int player, int value,
		unsigned int index)
	{
		SubjectMap* map = subjects;
		SubjectMap::Iterator it = map->Find(name.GetHash());
		if (it.node != 0 && !it->value->IsLocked())
		{
			SetIntValue(it->value, player, value, index);
		}
	}

	// FUNCTION: ENGINE 0x107F86D0
	void GameDatabase::SetFloat(const core::Name<core::CaseSensitiveKey>& name, unsigned int player, float value,
		unsigned int index)
	{
		SubjectMap* map = subjects;
		SubjectMap::Iterator it = map->Find(name.GetHash());
		if (it.node != 0 && !it->value->IsLocked())
		{
			SetFloatValue(it->value, player, value, index);
		}
	}

	// FUNCTION: ENGINE 0x107F8730
	void GameDatabase::SetString(const core::Name<core::CaseSensitiveKey>& name, unsigned int player,
		const char* value, unsigned int index)
	{
		SubjectMap* map = subjects;
		SubjectMap::Iterator it = map->Find(name.GetHash());
		if (it.node != 0 && !it->value->IsLocked())
		{
			SetStringValue(it->value, player, value, index);
		}
	}

	// FUNCTION: ENGINE 0x107F8780
	bool GameDatabase::IsSettable(const char* name, unsigned int player)
	{
		SubjectMap::Iterator it = subjects->Find(core::Name<core::CaseSensitiveKey>(name, 1).GetHash());
		if (it.node != 0)
		{
			return it->value->IsValidPlayer(player);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107F87D0
	int GameDatabase::GetInt(const core::Name<core::CaseSensitiveKey>& name, unsigned int player, unsigned int index)
	{
		SubjectMap* map = subjects;
		SubjectMap::Iterator it = map->Find(name.GetHash());
		if (it.node != 0)
		{
			DBSubject* subject = it->value;
			return subject->GetInt(player, index);
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x107F8810
	float GameDatabase::GetFloat(const core::Name<core::CaseSensitiveKey>& name, unsigned int player,
		unsigned int index)
	{
		SubjectMap* map = subjects;
		SubjectMap::Iterator it = map->Find(name.GetHash());
		if (it.node != 0)
		{
			DBSubject* subject = it->value;
			return subject->GetFloat(player, index);
		}
		return -1.0f;
	}

	// FUNCTION: ENGINE 0x107F8850
	const char* GameDatabase::GetString(const core::Name<core::CaseSensitiveKey>& name, unsigned int player,
		unsigned int index)
	{
		SubjectMap* map = subjects;
		SubjectMap::Iterator it = map->Find(name.GetHash());
		if (it.node != 0)
		{
			DBSubject* subject = it->value;
			return subject->GetString(player, index);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x107F8890
	const wchar_t* GameDatabase::GetWideString(const core::Name<core::CaseSensitiveKey>& name, unsigned int player,
		unsigned int index)
	{
		SubjectMap* map = subjects;
		SubjectMap::Iterator it = map->Find(name.GetHash());
		if (it.node != 0)
		{
			DBSubject* subject = it->value;
			return subject->GetWideString(player, index);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x107F88D0
	bool GameDatabase::Exists(const core::Name<core::CaseSensitiveKey>& name, unsigned int player, unsigned int index)
	{
		SubjectMap* map = subjects;
		return map->Find(name.GetHash()).node != 0 ? true : false;
	}

	// FUNCTION: ENGINE 0x107F8900
	void GameDatabase::ResetSubjects(int category, unsigned int player)
	{
		SubjectMap* map = subjects;
		if (map != 0)
		{
			for (SubjectMap::MapNode* node = (SubjectMap::MapNode*)map->First(); node != 0;
				node = (SubjectMap::MapNode*)map->Next(node))
			{
				if (node->pair.value->category == category)
				{
					node->pair.value->Reset(player);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x107F8950
	void GameDatabase::ResetSubject(const core::Name<core::CaseSensitiveKey>& name, unsigned int player)
	{
		SubjectMap* map = subjects;
		if (map != 0)
		{
			SubjectMap::MapNode* node = (SubjectMap::MapNode*)map->TreeBase::Find(SubjectMap::CompareKey,
				&name.GetHash());
			if (node != 0)
			{
				DBSubject* subject = node->pair.value;
				DBSubject* linked = subject->linked;
				subject->Reset(player);
				// The engine resets the subject again, not the linked one
				if (linked != 0)
				{
					subject->Reset(player);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x107F89A0
	void GameDatabase::ResetProfileSubjects(unsigned int player)
	{
		ResetSubjects(1, player);
	}

	// FUNCTION: ENGINE 0x107F89B0
	void GameDatabase::ResetGameSubjects(unsigned int player)
	{
		ResetSubjects(3, player);
		ResetSubjects(0, player);
	}

	// FUNCTION: ENGINE 0x107F89D0
	void GameDatabase::ResetInt(const core::Name<core::CaseSensitiveKey>& name, int value)
	{
		SubjectMap* map = subjects;
		if (map != 0)
		{
			SubjectMap::MapNode* node = (SubjectMap::MapNode*)map->TreeBase::Find(SubjectMap::CompareKey,
				&name.GetHash());
			if (node != 0)
			{
				DBSubject* subject = node->pair.value;
				DBSubject* linked = subject->linked;
				subject->ResetInt(value);
				if (linked != 0)
				{
					subject->ResetInt(value);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x107F8A20
	void GameDatabase::ResetFloat(const core::Name<core::CaseSensitiveKey>& name, float value)
	{
		SubjectMap* map = subjects;
		if (map != 0)
		{
			SubjectMap::MapNode* node = (SubjectMap::MapNode*)map->TreeBase::Find(SubjectMap::CompareKey,
				&name.GetHash());
			if (node != 0)
			{
				DBSubject* subject = node->pair.value;
				DBSubject* linked = subject->linked;
				subject->ResetFloat(value);
				if (linked != 0)
				{
					subject->ResetFloat(value);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x107F8A70
	void GameDatabase::OnNotify(int a, int b, int c)
	{
		unsigned int id = a;
		if ((id & 0xFFFFFF00) != 0xFE00)
		{
			return;
		}
		if (inputMode)
		{
			onlineHelper.OnInput(id, c);
			return;
		}
		for (SubjectMap::Iterator it = subjects->Begin(); it != subjects->End(); ++it)
		{
			DBSubject* subject = it->value;
			DBSubject* linked = subject->linked;
			if (subject->scope == 0)
			{
				for (unsigned int i = 0; i < subject->count; i++)
				{
					if (linked != 0)
					{
						switch (subject->type)
						{
						case DBSubject::TYPE_INT:
							linked->SetInt(c, subject->GetInt(0, i), i);
							break;
						case DBSubject::TYPE_FLOAT:
							linked->SetFloat(c, subject->GetFloat(0, i), i);
							break;
						case DBSubject::TYPE_STRING:
							linked->SetString(c, subject->GetString(0, i), i);
							break;
						case DBSubject::TYPE_WIDE_STRING:
							{
								const wchar_t* text = subject->GetWideString(0, i);
								linked->SetWideString(c, text, i);
							}
							break;
						}
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x107F8B90
	void GameDatabase::OnLoadValues(unsigned __int64 key, unsigned int player, int count, const void* values)
	{
		SubjectMap::MapNode* node = (SubjectMap::MapNode*)subjects->TreeBase::Find(SubjectMap::CompareKey, &key);
		if (node == 0)
		{
			return;
		}
		DBSubject* subject = node->pair.value;
		if (subject == 0 || count != subject->count)
		{
			return;
		}
		switch (subject->type)
		{
		case DBSubject::TYPE_INT:
			for (int i = 0; i < count; i++)
			{
				subject->SetInt(player, ((const int*)values)[i], i);
			}
			break;
		case DBSubject::TYPE_FLOAT:
			for (int i = 0; i < count; i++)
			{
				subject->SetFloat(player, ((const float*)values)[i], i);
			}
			break;
		case DBSubject::TYPE_STRING:
			for (int i = 0; i < count; i++)
			{
				subject->SetString(player, (const char*)values + subject->stride * i, i);
			}
			break;
		case DBSubject::TYPE_WIDE_STRING:
			for (int i = 0; i < count; i++)
			{
				subject->SetWideString(player, (const wchar_t*)((const char*)values + subject->stride * i), i);
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x107F8CC0
	void GameDatabase::SetId(const core::Name<core::CaseSensitiveKey>& name, int id)
	{
		SubjectMap* map = subjects;
		SubjectMap::Iterator it = map->Find(name.GetHash());
		if (it.node != 0 && !it->value->IsLocked())
		{
			SetSubjectId(it->value, id);
		}
	}

	// FUNCTION: ENGINE 0x107F8D10
	int GameDatabase::WriteSubjects(unsigned int player, void* buffer, unsigned int size, bool profile)
	{
		SubjectMap* map = subjects;
		SubjectMap::MapNode* node = (SubjectMap::MapNode*)map->First();
		int written = 0;
		if (!profile)
		{
			player = 0;
		}
		for (; node != 0; node = (SubjectMap::MapNode*)map->Next(node))
		{
			DBSubject* subject = node->pair.value;
			bool writeProfile;
			if (profile && subject->category == 1 && subject->persistent)
			{
				writeProfile = true;
			}
			else
			{
				writeProfile = false;
			}
			bool writeGame;
			if (!profile && subject->category != 1 && subject->persistent)
			{
				writeGame = true;
			}
			else
			{
				writeGame = false;
			}
			if (writeProfile || writeGame)
			{
				written += storage.WriteSubject(player, subject, (char*)buffer + written);
			}
		}
		return written;
	}

	// FUNCTION: ENGINE 0x107F8DB0
	// EQUIVALENT: the engine computes profileSize - 4 with add eax, -4, ours with sub eax, 4
	void* GameDatabase::BuildProfile(unsigned int player)
	{
		int size = profileSize;
		int* buffer = (int*)operator new[](size, 0x80);
		memset(buffer, 0, size);
		*buffer = 4;
		unsigned int remaining = profileSize - 4;
		*buffer += WriteSubjects(player, buffer + 1, remaining, true);
		return buffer;
	}

	// FUNCTION: ENGINE 0x107F8E10
	int GameDatabase::FillBuffer(unsigned int player, int* buffer, int size)
	{
		memset(buffer, 0, size);
		*buffer = 4;
		subjects->First();
		*buffer += WriteSubjects(player, (char*)buffer + *buffer, size - 4, false);
		return *buffer;
	}

	// FUNCTION: ENGINE 0x107F8E60
	bool GameDatabase::Save(unsigned int player, int a, int b, int c, int d, int e)
	{
		if (IsStorageOperationInProgress())
		{
			return false;
		}
		int size = bufferSize;
		void* buffer = operator new[](size, 0x80);
		memset(buffer, 0, size);
		int written = FillBuffer(player, (int*)buffer, size);
		if (storageListener != 0)
		{
			((GameDBExtraWriter*)storageListener)->Write(player, (char*)buffer + written, size - written);
		}
		return storage.Save(player, buffer, a, b, c, d, e);
	}

	// FUNCTION: ENGINE 0x107F8F00
	int GameDatabase::ScriptGetInt(const char* name, unsigned int player, unsigned int index)
	{
		core::Name<core::CaseSensitiveKey> key(name, 1);
		static bool sWindowed = HasCommandLineOption("windowed") && HasCommandLineOption("borderless");
		if (sWindowed && key == core::Name<core::CaseSensitiveKey>("SettingVideoResolution", 0))
		{
			return -1;
		}
		return gGameDatabase->GetInt(key, player, index);
	}

	// FUNCTION: ENGINE 0x107F8FB0
	float GameDatabase::ScriptGetFloat(const char* name, unsigned int player, unsigned int index)
	{
		GameDatabase* database = gGameDatabase;
		return database->GetFloat(core::Name<core::CaseSensitiveKey>(name, 1), player, index);
	}

	// FUNCTION: ENGINE 0x107F8FF0
	const char* GameDatabase::ScriptGetString(const char* name, unsigned int player, unsigned int index)
	{
		GameDatabase* database = gGameDatabase;
		return database->GetString(core::Name<core::CaseSensitiveKey>(name, 1), player, index);
	}

	// FUNCTION: ENGINE 0x107F9030
	void GameDatabase::ScriptSetInt(const char* name, unsigned int player, int value, unsigned int index)
	{
		GameDatabase* database = gGameDatabase;
		database->SetInt(core::Name<core::CaseSensitiveKey>(name, 1), player, value, index);
	}

	// FUNCTION: ENGINE 0x107F9070
	void GameDatabase::ScriptSetFloat(const char* name, unsigned int player, float value, unsigned int index)
	{
		GameDatabase* database = gGameDatabase;
		database->SetFloat(core::Name<core::CaseSensitiveKey>(name, 1), player, value, index);
	}

	// FUNCTION: ENGINE 0x107F90B0
	void GameDatabase::ScriptSetString(const char* name, unsigned int player, const char* value, unsigned int index)
	{
		GameDatabase* database = gGameDatabase;
		database->SetString(core::Name<core::CaseSensitiveKey>(name, 1), player, value, index);
	}

	// FUNCTION: ENGINE 0x107F90F0
	void GameDatabase::ScriptResetSubject(const char* name, unsigned int player)
	{
		GameDatabase* database = gGameDatabase;
		database->ResetSubject(core::Name<core::CaseSensitiveKey>(name, 1), player);
	}

	// FUNCTION: ENGINE 0x107F9120
	void GameDatabase::OnCall(void* movie, const FEMovie::Value* arguments, unsigned int count,
		FEMovie::Value* result)
	{
		WideStringBuffer text;
		core::Name<core::CaseSensitiveKey> name(arguments[0].string, 1);
		double index = arguments[2].number;
		double player = arguments[1].number;
		const wchar_t* value = GetWideString(name, (unsigned int)player, (unsigned int)index);
		if (text.capacity > 0)
		{
			text.Copy(value);
		}
		else
		{
			text.Borrow(value);
		}
		result->string = (const char*)text.text;
		result->type = 5;
	}

	// FUNCTION: ENGINE 0x107F9640
	GameDatabase::GameDatabase(const GameDatabaseParams& params) : inputMode(false), modeCount(0),
		mode(params.unknown0), onlineHelper(0x40, 5, params.helperA, params.helperB), storageListener(0)
	{
		subjects = new (0x80) SubjectMap;
		released = new (0x80) SubjectList;
		onlineHelper.callback = this;
		storage.SetCallback(this);
		profileSize = params.profileSize;
		bufferSize = params.bufferSize;
		controller::InputSystem::Get()->AddCallback(this);
		LuaScriptManager* context = GetScriptManager();
		context->SetOwner(this);
		context->RegisterMethod("db_GetInt", this, &GameDatabase::ScriptGetInt);
		context->RegisterMethod("db_GetFloat", this, &GameDatabase::ScriptGetFloat);
		context->RegisterMethod("db_GetString", this, &GameDatabase::ScriptGetString);
		context->RegisterMethod("db_SetInt", this, &GameDatabase::ScriptSetInt);
		context->RegisterMethod("db_SetFloat", this, &GameDatabase::ScriptSetFloat);
		context->RegisterMethod("db_SetString", this, &GameDatabase::ScriptSetString);
		context->RegisterMethod("db_IsSettable", this, &GameDatabase::IsSettable);
		context->RegisterMethod("db_ResetProfileSubjects", this, &GameDatabase::ResetProfileSubjects);
		context->RegisterMethod("db_ResetGameSubjects", this, &GameDatabase::ResetGameSubjects);
		context->RegisterMethod("db_IsStorageOperationInProgress", this, &GameDatabase::IsStorageOperationInProgress);
		context->RegisterMethod("db_ResetSubject", this, &GameDatabase::ScriptResetSubject);
		context->ClearOwner();
		FEMovie::AddCallback("db_GetWideString", this, 0);
		categoryB[0] = 1;
		categoryB[1] = 1;
		categoryB[2] = controller::InputSystem::Get()->controllerCount;
		categoryB[3] = 1;
		categoryA[3] = 1;
		categoryA[0] = 2;
		categoryA[2] = 2;
		categoryA[1] = 0;
	}

	// FUNCTION: ENGINE 0x107F9960
	DBSubject* GameDatabase::AddIntSubject(const core::Name<core::CaseSensitiveKey>& name, int category, int value,
		DBSubjectInfo info)
	{
		DBSubject* subject = CreateIntSubject(name, category, value, info);
		DBSubjectInfo copy(info);
		copy.flag = false;
		if (mode != 0 && category == 1)
		{
			core::Name<core::CaseSensitiveKey> inGameName(core::Hash64("_InGame", subject->GetName().GetHash()));
			copy.b = 0;
			DBSubject* inGame = CreateIntSubject(inGameName, 3, value, copy);
			LinkSubjects(inGame, subject);
			RegisterOnline(inGame, 3);
		}
		else
		{
			subject->scope = 2;
		}
		RegisterOnline(subject, category);
		return subject;
	}

	// FUNCTION: ENGINE 0x107F9A40
	DBSubject* GameDatabase::AddFloatSubject(const core::Name<core::CaseSensitiveKey>& name, int category,
		float value, DBSubjectInfo info)
	{
		DBSubject* subject = CreateFloatSubject(name, category, value, info);
		DBSubjectInfo copy(info);
		copy.flag = false;
		if (mode != 0 && category == 1)
		{
			core::Name<core::CaseSensitiveKey> inGameName(core::Hash64("_InGame", subject->GetName().GetHash()));
			copy.b = 0;
			DBSubject* inGame = CreateFloatSubject(inGameName, 3, value, copy);
			LinkSubjects(inGame, subject);
			RegisterOnline(inGame, 3);
		}
		else
		{
			subject->scope = 2;
		}
		RegisterOnline(subject, category);
		return subject;
	}

	// FUNCTION: ENGINE 0x107F9B40
	DBSubject* GameDatabase::AddStringSubject(const core::Name<core::CaseSensitiveKey>& name, int category,
		const char* value, int length, DBSubjectInfo info)
	{
		DBSubject* subject = CreateStringSubject(name, category, value, length, info);
		DBSubjectInfo copy(info);
		copy.flag = false;
		if (mode != 0 && category == 1)
		{
			core::Name<core::CaseSensitiveKey> inGameName(core::Hash64("_InGame", subject->GetName().GetHash()));
			copy.b = 0;
			DBSubject* inGame = CreateStringSubject(inGameName, 3, value, length, copy);
			LinkSubjects(inGame, subject);
			RegisterOnline(inGame, 3);
		}
		else
		{
			subject->scope = 2;
		}
		RegisterOnline(subject, category);
		return subject;
	}

	// FUNCTION: ENGINE 0x107F9C20
	bool GameDatabase::RemoveSubject(unsigned __int64 key, DBSubject* subject)
	{
		onlineHelper.RemoveSubject(subject);
		delete subject;
		return subjects->Erase(key);
	}

	// FUNCTION: ENGINE 0x107F9C90
	void GameDatabase::Create(const GameDatabaseParams& params)
	{
		core::HeapScope scope(0x80);
		gGameDatabase = new (0x80) GameDatabase(params);
		if (params.unknown14 == 0)
		{
			new GameDBHelper(GameDBHelper::Config());
		}
		GameDBHelper::Get()->Start();
	}

	// FUNCTION: ENGINE 0x107F9D20
	GameDatabase::~GameDatabase()
	{
		SubjectMap* map = subjects;
		if (map != 0)
		{
			for (SubjectMap::MapNode* node = (SubjectMap::MapNode*)map->First(); node != 0;
				node = (SubjectMap::MapNode*)map->Next(node))
			{
				delete node->pair.value;
				node->pair.value = 0;
			}
			delete subjects;
			subjects = 0;
			delete released;
			released = 0;
		}
		FEMovie::RemoveCallback("db_GetWideString");
		LuaScriptManager* context = GetScriptManager();
		context->Unregister(this);
	}

	// FUNCTION: ENGINE 0x107F9E20
	void GameDatabase::Reset()
	{
		SubjectMap* map = subjects;
		for (SubjectMap::MapNode* node = (SubjectMap::MapNode*)map->First(); node != 0;
			node = (SubjectMap::MapNode*)map->Next(node))
		{
			node->pair.value->ClearValues();
		}
		for (SubjectList::Iterator it = released->Begin(); it != released->End(); ++it)
		{
			DBSubject* subject = *it;
			RemoveSubject(subject->GetName().GetHash(), subject);
		}
		if (released->Size() > 0)
		{
			released->Clear();
		}
		onlineHelper.Clear();
		storage.Slot2();
	}

	// FUNCTION: ENGINE 0x107F9F00
	void GameDatabase::Destroy()
	{
		GameDBHelper::Get()->Stop();
		delete GameDBHelper::Get();
		delete gGameDatabase;
		gGameDatabase = 0;
	}
}

template class Method3<engine::GameDatabase, int, const char*, unsigned int, unsigned int>;
template class Method3<engine::GameDatabase, float, const char*, unsigned int, unsigned int>;
template class Method3<engine::GameDatabase, const char*, const char*, unsigned int, unsigned int>;
template class Method4<engine::GameDatabase, void, const char*, unsigned int, int, unsigned int>;
template class Method4<engine::GameDatabase, void, const char*, unsigned int, float, unsigned int>;
template class Method4<engine::GameDatabase, void, const char*, unsigned int, const char*, unsigned int>;
template class Method2<engine::GameDatabase, bool, const char*, unsigned int>;
template class Method1<engine::GameDatabase, void, unsigned int>;
template class Method0<engine::GameDatabase, bool>;
template class Method2<engine::GameDatabase, void, const char*, unsigned int>;
template class Closure3<engine::GameDatabase, int, const char*, unsigned int, unsigned int>;
template class Closure3<engine::GameDatabase, float, const char*, unsigned int, unsigned int>;
template class Closure3<engine::GameDatabase, const char*, const char*, unsigned int, unsigned int>;
template class Closure4<engine::GameDatabase, void, const char*, unsigned int, int, unsigned int>;
template class Closure4<engine::GameDatabase, void, const char*, unsigned int, float, unsigned int>;
template class Closure4<engine::GameDatabase, void, const char*, unsigned int, const char*, unsigned int>;
template class Closure2<engine::GameDatabase, bool, const char*, unsigned int>;
template class Closure1<engine::GameDatabase, void, unsigned int>;
template class Closure0<engine::GameDatabase, bool>;
template class Closure2<engine::GameDatabase, void, const char*, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<engine::GameDatabase, void, unsigned int>(const char*,
	engine::GameDatabase*, void (engine::GameDatabase::*)(unsigned int));

// Kept copies: the script method wrappers and their registration templates, the inline callback base members, the
// subject map / list members and the scalar deleting destructors
// FUNCTION: ENGINE 0x107F6B30
// FUNCTION: ENGINE 0x107F6B40
// FUNCTION: ENGINE 0x107F6B50
// FUNCTION: ENGINE 0x107F6B60
// FUNCTION: ENGINE 0x107F6B70
// FUNCTION: ENGINE 0x107F6B80
// FUNCTION: ENGINE 0x107F6B90
// FUNCTION: ENGINE 0x107F6BA0
// FUNCTION: ENGINE 0x107F6BB0
// FUNCTION: ENGINE 0x107F6BC0
// FUNCTION: ENGINE 0x107F6BD0
// FUNCTION: ENGINE 0x107F6BE0
// FUNCTION: ENGINE 0x107F6BF0
// FUNCTION: ENGINE 0x107F6C00
// FUNCTION: ENGINE 0x107F6C10
// FUNCTION: ENGINE 0x107F6F60
// FUNCTION: ENGINE 0x107F6F80
// FUNCTION: ENGINE 0x107F6FA0
// FUNCTION: ENGINE 0x107F6FC0
// FUNCTION: ENGINE 0x107F7000
// FUNCTION: ENGINE 0x107F7020
// FUNCTION: ENGINE 0x107F7030
// FUNCTION: ENGINE 0x107F7040
// FUNCTION: ENGINE 0x107F7050
// FUNCTION: ENGINE 0x107F7060
// FUNCTION: ENGINE 0x107F70B0
// FUNCTION: ENGINE 0x107F7100
// FUNCTION: ENGINE 0x107F7120
// FUNCTION: ENGINE 0x107F7130
// FUNCTION: ENGINE 0x107F71A0
// FUNCTION: ENGINE 0x107F71D0
// FUNCTION: ENGINE 0x107F74C0
// FUNCTION: ENGINE 0x107F74D0
// FUNCTION: ENGINE 0x107F7500
// FUNCTION: ENGINE 0x107F7540
// FUNCTION: ENGINE 0x107F7580
// FUNCTION: ENGINE 0x107F7610
// FUNCTION: ENGINE 0x107F7630
// FUNCTION: ENGINE 0x107F76A0
// FUNCTION: ENGINE 0x107F76D0
// FUNCTION: ENGINE 0x107F7700
// FUNCTION: ENGINE 0x107F7770
// FUNCTION: ENGINE 0x107F77B0
// FUNCTION: ENGINE 0x107F7800
// FUNCTION: ENGINE 0x107F7870
// FUNCTION: ENGINE 0x107F78A0
// FUNCTION: ENGINE 0x107F78D0
// FUNCTION: ENGINE 0x107F7950
// FUNCTION: ENGINE 0x107F7980
// FUNCTION: ENGINE 0x107F79B0
// FUNCTION: ENGINE 0x107F7A30
// FUNCTION: ENGINE 0x107F7A60
// FUNCTION: ENGINE 0x107F7AA0
// FUNCTION: ENGINE 0x107F7B20
// FUNCTION: ENGINE 0x107F7B50
// FUNCTION: ENGINE 0x107F7B80
// FUNCTION: ENGINE 0x107F7BE0
// FUNCTION: ENGINE 0x107F7C10
// FUNCTION: ENGINE 0x107F7C40
// FUNCTION: ENGINE 0x107F7C90
// FUNCTION: ENGINE 0x107F7CB0
// FUNCTION: ENGINE 0x107F7CD0
// FUNCTION: ENGINE 0x107F7D10
// FUNCTION: ENGINE 0x107F7D30
// FUNCTION: ENGINE 0x107F7D50
// FUNCTION: ENGINE 0x107F7DB0
// FUNCTION: ENGINE 0x107F7DD0
// FUNCTION: ENGINE 0x107F7DF0
// FUNCTION: ENGINE 0x107F7E10
// FUNCTION: ENGINE 0x107F7E30
// FUNCTION: ENGINE 0x107F7EB0
// FUNCTION: ENGINE 0x107F7EE0
// FUNCTION: ENGINE 0x107F7EF0
// FUNCTION: ENGINE 0x107F7F00
// FUNCTION: ENGINE 0x107F7F30
// FUNCTION: ENGINE 0x107F7F40
// FUNCTION: ENGINE 0x107F7F70
// FUNCTION: ENGINE 0x107F7FA0
// FUNCTION: ENGINE 0x107F7FD0
// FUNCTION: ENGINE 0x107F8020
// FUNCTION: ENGINE 0x107F8050
// FUNCTION: ENGINE 0x107F8080
// FUNCTION: ENGINE 0x107F80B0
// FUNCTION: ENGINE 0x107F80E0
// FUNCTION: ENGINE 0x107F8110
// FUNCTION: ENGINE 0x107F8150
// FUNCTION: ENGINE 0x107F8180
// FUNCTION: ENGINE 0x107F81B0
// FUNCTION: ENGINE 0x107F81E0
// FUNCTION: ENGINE 0x107F8210
// FUNCTION: ENGINE 0x107F8270
// FUNCTION: ENGINE 0x107F8290
// FUNCTION: ENGINE 0x107F82E0
// FUNCTION: ENGINE 0x107F8300
// FUNCTION: ENGINE 0x107F8330
// FUNCTION: ENGINE 0x107F91E0
// FUNCTION: ENGINE 0x107F91F0
// FUNCTION: ENGINE 0x107F9240
// FUNCTION: ENGINE 0x107F9270
// FUNCTION: ENGINE 0x107F92D0
// FUNCTION: ENGINE 0x107F9330
// FUNCTION: ENGINE 0x107F9390
// FUNCTION: ENGINE 0x107F93F0
// FUNCTION: ENGINE 0x107F9450
// FUNCTION: ENGINE 0x107F94B0
// FUNCTION: ENGINE 0x107F9510
// FUNCTION: ENGINE 0x107F9560
// FUNCTION: ENGINE 0x107F95E0
// FUNCTION: ENGINE 0x107F98E0
// FUNCTION: ENGINE 0x107F9910
// FUNCTION: ENGINE 0x107F9EE0
