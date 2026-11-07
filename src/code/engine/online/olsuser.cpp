// engine::OLSUserList (the RTTI name is engine::OLSUser; see olsfriend.h). Unit 0x10886A70 - 0x108879EA.
#include "code/engine/online/olsfriend.h"
#include "code/core/strings.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/gamelink.h"
#include "code/engine/online/ols.h"
#include "code/engine/online/olsgame.h"
#include "code/core/heap.h"
#include <new>
#include <string.h>

namespace engine
{
	// FUNCTION: ENGINE 0x10844110
	OLSValue::OLSValue()
	{
		type = 0;
		wide.data = 0;
		wide.capacity = 0;
	}

	// FUNCTION: ENGINE 0x10844120
	OLSValue::~OLSValue()
	{
		if (type == 4)
		{
			reinterpret_cast<WideStringBuffer*>(&wide)->Release();
		}
	}

	// FUNCTION: ENGINE 0x10887500
	void OLSUserRecord::FreeValues()
	{
		if (items != 0)
		{
			delete[] items;
			items = 0;
			itemCount = 0;
		}
		if (values != 0)
		{
			delete[] values;
			values = 0;
			valueCount = 0;
		}
	}

	// FUNCTION: ENGINE 0x108873F0
	void OLSUserRecord::AllocateValues(int newItemCount, int newValueCount)
	{
		core::HeapScope scope(0x81);
		itemCount = newItemCount;
		items = new OLSValue[newItemCount];
		valueCount = newValueCount;
		values = new OLSIdValue[newValueCount];
		Reset();
	}

	// FUNCTION: ENGINE 0x108443F0
	OLSKeyTable::OLSKeyTable(int newCount)
	{
		count = newCount;
		entries = new Entry[newCount];
		for (int i = 0; i < count; i++)
		{
			entries[i].id = 0;
		}
	}

	// FUNCTION: ENGINE 0x10844440
	OLSKeyTable::~OLSKeyTable()
	{
		delete[] entries;
	}

	// FUNCTION: ENGINE 0x10887560
	OLSUserList::OLSUserList(int newSettingCount, int newIdCount, int newRecordCount)
		: settingCount(newSettingCount), idCount(newIdCount), recordCount(newRecordCount), activeCount(0),
		settingKeyTable(newSettingCount), idKeyTable(newIdCount)
	{
		selected = -1;
		records = new OLSUserRecord[recordCount];
		Reset();
		for (int i = 0; i < recordCount; i++)
		{
			records[i].index = i;
			records[i].AllocateValues(settingCount, idCount);
		}
		settings = new OLSSettingInfo[settingCount];
		for (int i = 0; i < settingCount; i++)
		{
			settings[i].scope = 2;
		}
		settingKeys = new OLSKeyTable::Entry[idCount];
		for (int i = 0; i < idCount; i++)
		{
			settingKeys[i].id = -1;
			settingKeys[i].kind = 0;
		}
	}

	// FUNCTION: ENGINE 0x10887C00
	OLSUserList::~OLSUserList()
	{
		GameDatabase* database = gGameDatabase;
		for (int i = 0; i < settingCount; i++)
		{
			if (settings[i].used == 1 && settings[i].scope != 2)
			{
				database->ReleaseSubject(core::Name<core::CaseSensitiveKey>(settings[i].name, 0));
			}
		}
		controller::InputSystem::Get()->RemoveCallback(this);
		delete[] records;
		delete[] settingKeys;
		delete[] settings;
	}

	// FUNCTION: ENGINE 0x10886BF0
	void OLSUserRecord::SetName(const WideStringBuffer& text)
	{
		name.CopyFrom(text);
	}

	// The engine's out-of-line copies of the inline setters of the record (0x10887340, 0x10887360, 0x10887380) come
	// from calls that are not expanded
#pragma inline_depth(0)
	void KeepUserRecordCopies(OLSUserRecord* record)
	{
		record->SetGame(0);
		record->SetSession(0);
		record->SetInvite(0);
	}
#pragma inline_depth()

	// FUNCTION: ENGINE 0x108873A0
	// NONMATCHING: the engine stores the controller before the argument of the name's allocation is pushed (83.8 %)
#ifdef NONMATCHING
	OLSUserRecord::OLSUserRecord()
	{
		controller = 0xffffffff;
		items = 0;
		values = 0;
		unknown14 = 0;
		unknown18 = 0;
		invite = 0;
		flags = 0;
		itemCount = 0;
		valueCount = 0;
		name.Allocate(0x20);
		Reset();
	}
#endif

	// FUNCTION: ENGINE 0x10887B70
	OLSUserRecord::~OLSUserRecord()
	{
		FreeValues();
	}

	// FUNCTION: ENGINE 0x10886BB0
	// EQUIVALENT: scheduling and register allocation (the engine keeps minus one in ecx and loads the memset arguments after
	// the stores of minus one; 67 %)
	void OLSUserRecord::Reset()
	{
		controller = 0xffffffff;
		id = -1;
		unknown2C = -1;
		unknown14 = 0;
		unknown18 = 0;
		invite = 0;
		flags = 0;
		memset(values, 0, valueCount << 4);
		name.Set("");
	}

	// FUNCTION: ENGINE 0x10886C40
	void OLSUserList::ResetRecord(int index)
	{
		records[index].Reset();
	}

	// FUNCTION: ENGINE 0x10886C60
	void OLSUserList::Reset()
	{
		activeCount = 0;
		currentUser = -1;
		for (int i = 0; i < recordCount; i++)
		{
			ResetRecord(i);
		}
	}

	// FUNCTION: ENGINE 0x108871C0
	int OLSUserList::GetSelected()
	{
		return selected;
	}

	// FUNCTION: ENGINE 0x10886C90
	int OLSUserList::FindIndexById(int userId)
	{
		for (int i = 0; i < recordCount; i++)
		{
			if (userId == records[i].id)
			{
				return records[i].index;
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x10886CD0
	// EQUIVALENT: register allocation (the engine keeps the records in edi and the controller in esi; 92 %)
	int OLSUserList::FindIndexByController(unsigned int controllerId)
	{
		for (int i = 0; i < recordCount; i++)
		{
			if (controllerId == records[i].controller)
			{
				return records[i].index;
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x10886F50
	void OLSUserList::SetCurrentUser(int id)
	{
		currentUser = id;
	}

	// FUNCTION: ENGINE 0x10886D10
	int OLSUserList::FindIndexByHost(const OLSHostKey* key)
	{
		unsigned char host = key->slot;
		if (key->address == *GetNetSystem()->localAddress)
		{
			host = 0xfe;
		}
		for (int i = 0; i < recordCount; i++)
		{
			if (host == (unsigned char)(records[i].controller >> 8))
			{
				return records[i].index;
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x10886D80
	// NONMATCHING: the engine addresses the id of the record with the offset as the base register (99.5 %)
#ifdef NONMATCHING
	OLSUserRecord* OLSUserList::AddUser(int userId)
	{
		int freeIndex = -1;
		for (int i = 0; i < recordCount; i++)
		{
			if (userId == records[i].id)
			{
				return &records[i];
			}
			if (freeIndex == -1 && records[i].id == -1)
			{
				freeIndex = i;
			}
		}
		if (freeIndex >= 0)
		{
			activeCount++;
			records[freeIndex].Reset();
			records[freeIndex].id = userId;
			OLSUserMessage message(0);
			message.user = records[freeIndex].index;
			message.unknownC = 0;
			OLS::Get()->SendMessage(&message);
			return &records[freeIndex];
		}
		return 0;
	}
#endif

	// FUNCTION: ENGINE 0x10886E60
	void OLSUserList::Release(int index)
	{
		if (records[index].flags == 0)
		{
			records[index].Reset();
			activeCount--;
			OLSUserMessage message(1);
			message.user = records[index].index;
			message.unknownC = 0;
			OLS::Get()->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x10886EF0
	void OLSUserList::SetRecordId(int index, int newId)
	{
		records[index].id = newId;
	}

	// FUNCTION: ENGINE 0x10886F10
	void OLSUserList::SetFlag(int index, unsigned int mask, bool set)
	{
		OLSUserRecord* record = &records[index];
		if (set)
		{
			record->flags |= mask;
			return;
		}
		record->flags &= ~mask;
		Release(index);
	}

	// FUNCTION: ENGINE 0x10886F60
	// NONMATCHING: the engine loads the observer into ecx and indexes the record with the offset as the second register (57.3 %)
#ifdef NONMATCHING
	void OLSUserList::OnFlags(unsigned int id, int local, unsigned int flags, bool set)
	{
		if (local == 0 && !set)
		{
			int index = FindIndexByController(id);
			if (index != -1)
			{
				if (OLS::Get()->userObserver != 0)
				{
					OLSUserObserver* observer = OLS::Get()->userObserver;
					observer->OnUserUnlinked(index);
				}
				records[index].controller = 0xffffffff;
				records[index].unknown2C = -1;
				SetFlag(index, 0x10, false);
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x10886FE0
	// NONMATCHING: the engine loads the observer into ecx and indexes the record with the offset as the second register (47.4 %)
#ifdef NONMATCHING
	void OLSUserList::OnValue(unsigned int id, int local, controller::PlayerInfo* input)
	{
		if (local == 0)
		{
			if (input->firstId != -1)
			{
				int index = AddUser(input->firstId)->index;
				if (index != -1)
				{
					records[index].controller = id;
					SetFlag(index, 0x10, true);
					if (OLS::Get()->userObserver != 0)
					{
						OLS::Get()->userObserver->OnUserLinked(index);
					}
				}
			}
			else
			{
				int index = FindIndexByController(id);
				if (index != -1)
				{
					if (OLS::Get()->userObserver != 0)
					{
						OLS::Get()->userObserver->OnUserUnlinked(index);
					}
					records[index].controller = 0xffffffff;
					records[index].unknown2C = -1;
					SetFlag(index, 0x10, false);
				}
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x108870C0
	void OLSUserList::OnNotify(int a, int b, int c)
	{
		int index = FindIndexByController(a);
		if (index != -1)
		{
			records[index].unknown2C = c;
			OLSUserMessage message(5);
			message.unknownC = 0;
			message.user = index;
			OLS::Get()->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x10887130
	void OLSUserList::SetSettingKey(int index, const OLSKeyTable::Entry* key)
	{
		settingKeys[index] = *key;
		idKeyTable.Set(index, key->kind, 1);
	}

	// FUNCTION: ENGINE 0x10887160
	void OLSUserList::SetSettingInfo(int index, const OLSSettingInfo* info)
	{
		settings[index] = *info;
		settingKeyTable.Set(index, (int)info->name, info->type);
		settingsChanged = true;
	}

	// FUNCTION: ENGINE 0x108871B0
	void OLSUserList::SetSelected(int index)
	{
		selected = index;
	}

	// FUNCTION: ENGINE 0x108871D0
	int OLSUserList::CanAnswerInvite()
	{
		OLSUserRecord::Invite* invite = records[selected].invite;
		if (invite != 0 && (invite->flags & 0x400) == 0)
		{
			return 1;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10887200
	const char* OLSUserList::GetSelectedName()
	{
		records[selected].name.CopyTo(text, 0x100);
		return text;
	}

	// FUNCTION: ENGINE 0x10886C00
	void OLSUserRecord::Describe(OLSKeyTable* keys, char* buffer, int size)
	{
		keys->Format(items, itemCount, buffer, size);
	}

	// FUNCTION: ENGINE 0x10887230
	const char* OLSUserList::GetSelectedValuesText()
	{
		records[selected].Describe(&settingKeyTable, text, 0x100);
		return text;
	}

	// FUNCTION: ENGINE 0x10887260
	const char* OLSUserList::GetSelectedIdsText()
	{
		text[0] = 0;
		for (int i = 0; i < idCount; i++)
		{
			const OLSIdValue* value = &records[selected].values[i];
			core::SNPrintf(text, 0x100, "%s %s=%s,%s,%d,{%d,%d,%d,%d,%d,%d}", text, (const char*)settingKeys[i].kind,
				value->flagA ? "true" : "false", value->flagB ? "true" : "false", value->number, value->word,
				value->bytes[0], value->bytes[1], value->bytes[2], value->bytes[3], value->bytes[4]);
		}
		return text;
	}

	// FUNCTION: ENGINE 0x108876C0
	int OLSUserList::SetGame(int userId, int value, const WideStringBuffer* nameText)
	{
		OLSUserRecord* record = AddUser(userId);
		if (record == 0)
		{
			return -1;
		}
		record->SetGame(value);
		record->SetName(*nameText);
		return record->index;
	}

	// FUNCTION: ENGINE 0x10887710
	void OLSUserList::ClearGame(int value)
	{
		for (int i = 0; i < recordCount; i++)
		{
			if (records[i].unknown14 == value)
			{
				int index = records[i].index;
				OLS::Get()->GetLocalUser()->SetSetting(index, 2);
				records[i].SetGame(0);
				Release(i);
			}
		}
	}

	// FUNCTION: ENGINE 0x10887780
	int OLSUserList::SetSession(int userId, int value, const WideStringBuffer* nameText, unsigned int newController)
	{
		OLSUserRecord* record = AddUser(userId);
		if (record == 0)
		{
			return -1;
		}
		record->SetSession(value);
		record->SetName(*nameText);
		int index = record->index;
		record->controller = newController;
		return index;
	}

	// FUNCTION: ENGINE 0x108877D0
	void OLSUserList::ClearSession(int value)
	{
		for (int i = 0; i < recordCount; i++)
		{
			if (records[i].unknown18 == value)
			{
				records[i].SetSession(0);
				Release(i);
			}
		}
	}

	// FUNCTION: ENGINE 0x10887820
	int OLSUserList::SetInvite(int userId, OLSUserRecord::Invite* invite, const WideStringBuffer* nameText)
	{
		OLSUserRecord* record = AddUser(userId);
		if (record == 0)
		{
			return -1;
		}
		record->SetInvite(invite);
		record->SetName(*nameText);
		return record->index;
	}

	// FUNCTION: ENGINE 0x10887870
	void OLSUserList::ClearInvite(int userId)
	{
		int index = FindIndexById(userId);
		if (index != -1)
		{
			records[index].SetInvite(0);
			Release(index);
		}
	}

}
