// engine::DBSubject and the classes around it (this unit 0x10842F10 - 0x10844090; no assert path, file name is a guess):
// one database value of a given type with a value per player and index, the observers told about its changes and the
// changes still to be told.
#include "code/engine/database/gamedatabase.h"
#include "code/core/strings.h"
#include "code/engine/system/enginememory.h"
#include <string.h>

namespace engine
{
	// FUNCTION: ENGINE 0x10842F10
	DBSubjectInfo::DBSubjectInfo(bool newFlag, int newA, int newB)
	{
		flag = newFlag;
		a = newA;
		b = newB;
	}

	// FUNCTION: ENGINE 0x10842F30
	DBSubjectInfo& DBSubjectInfo::operator=(const DBSubjectInfo& other)
	{
		flag = other.flag;
		a = other.a;
		b = other.b;
		return *this;
	}

	// FUNCTION: ENGINE 0x10842F50
	DBChange::DBChange(unsigned char newPlayer, int value, unsigned char newIndex)
	{
		player = newPlayer;
		type = 0;
		index = newIndex;
		intValue = value;
	}

	// FUNCTION: ENGINE 0x10842F70
	DBChange::DBChange(unsigned char newPlayer, float value, unsigned char newIndex)
	{
		type = 1;
		player = newPlayer;
		index = newIndex;
		floatValue = value;
	}

	// FUNCTION: ENGINE 0x10842FA0
	DBChange::DBChange(unsigned char newPlayer, const char* newText, unsigned char newIndex, int length)
	{
		type = 2;
		player = newPlayer;
		index = newIndex;
		text = new (1) char[length];
		core::StrNCpy(text, newText, (unsigned int)length);
	}

	// FUNCTION: ENGINE 0x10842FE0
	DBChange::DBChange(unsigned char newPlayer, const wchar_t* newText, unsigned char newIndex, int length)
	{
		type = 3;
		player = newPlayer;
		index = newIndex;
		wideText = (wchar_t*)new (1) char[length];
		memcpy(wideText, newText, length);
	}

	// FUNCTION: ENGINE 0x10843020
	// EQUIVALENT: schedule only (the engine stores the nulled pointer before the delete[] call's stack cleanup, ours cleans up first), 77.5 %
	DBChange::~DBChange()
	{
		if ((type == 3 || type == 2) && text != 0)
		{
			delete[] text;
			text = 0;
		}
	}

	// FUNCTION: ENGINE 0x10843070
	int DBSubject::GetInt(unsigned int player, unsigned int index)
	{
		return ((int*)values)[count * player + index];
	}

	// FUNCTION: ENGINE 0x10843090
	float DBSubject::GetFloat(unsigned int player, unsigned int index)
	{
		return ((float*)values)[count * player + index];
	}

	// FUNCTION: ENGINE 0x108430B0
	const char* DBSubject::GetString(unsigned int player, unsigned int index)
	{
		return (const char*)values + (count * player + index) * stride;
	}

	// FUNCTION: ENGINE 0x108430D0
	const wchar_t* DBSubject::GetWideString(unsigned int player, unsigned int index)
	{
		return (const wchar_t*)((const char*)values + (count * player + index) * stride);
	}

	// FUNCTION: ENGINE 0x108430F0
	int DBSubject::GetDefaultInt()
	{
		return defaultInt;
	}

	// FUNCTION: ENGINE 0x10843100
	float DBSubject::GetDefaultFloat()
	{
		return defaultFloat;
	}

	// FUNCTION: ENGINE 0x10843110
	const char* DBSubject::GetDefaultString()
	{
		return defaultString;
	}

	// FUNCTION: ENGINE 0x10843120
	const wchar_t* DBSubject::GetDefaultWideString()
	{
		return defaultWideString;
	}

	// FUNCTION: ENGINE 0x10843130
	void DBSubject::ResetInt(int value)
	{
		defaultInt = value;
	}

	// FUNCTION: ENGINE 0x10843140
	void DBSubject::ResetFloat(float value)
	{
		defaultFloat = value;
	}

	// FUNCTION: ENGINE 0x10843180
	void DBSubject::ClearObservers()
	{
		locked = true;
	}

	// FUNCTION: ENGINE 0x10843190
	bool DBSubject::IsLocked()
	{
		return locked;
	}

	// FUNCTION: ENGINE 0x10843310
	DBSubjectInfo::DBSubjectInfo(const DBSubjectInfo& other)
	{
		*this = other;
	}

	// FUNCTION: ENGINE 0x10843330
	DBSubject::DBSubject() : name("", 1)
	{
		scope = -1;
		linked = 0;
		players = 0;
		count = 0;
		type = -1;
		stride = 0;
		locked = false;
		category = 4;
		persistent = false;
		observers = new (0x80) ObserverList;
		changes = new (0x80) ChangeList;
	}

	// FUNCTION: ENGINE 0x108433C0
	// EQUIVALENT: register allocation only (the same loads of the hash words and stores, high word first), 80.5 %
	unsigned __int64* DBSubject::SetName(unsigned __int64* key, const core::Name<core::CaseSensitiveKey>& newName)
	{
		name = newName;
		const unsigned int* hash = (const unsigned int*)&newName.GetHash();
		unsigned int low = hash[0];
		unsigned int high = hash[1];
		((unsigned int*)key)[1] = high;
		((unsigned int*)key)[0] = low;
		return key;
	}

	// FUNCTION: ENGINE 0x108433F0
	unsigned __int64* DBSubject::InitInt(unsigned __int64* key, const core::Name<core::CaseSensitiveKey>& newName,
		int newCategory, int newPlayers, int newScope, int value, const DBSubjectInfo& info)
	{
		scope = newScope;
		players = newPlayers;
		type = TYPE_INT;
		count = info.a;
		stride = 4;
		id = info.b;
		category = newCategory;
		persistent = info.flag;
		int total = count * newPlayers;
		defaultInt = value;
		values = new (0x80) int[total];
		for (int i = 0; i < total; i++)
		{
			((int*)values)[i] = value;
		}
		SetName(key, newName);
		return key;
	}

	// FUNCTION: ENGINE 0x10843490
	unsigned __int64* DBSubject::InitFloat(unsigned __int64* key, const core::Name<core::CaseSensitiveKey>& newName,
		int newCategory, int newPlayers, int newScope, float value, const DBSubjectInfo& info)
	{
		scope = newScope;
		players = newPlayers;
		type = TYPE_FLOAT;
		count = info.a;
		stride = 4;
		id = info.b;
		category = newCategory;
		persistent = info.flag;
		int total = count * newPlayers;
		defaultFloat = value;
		values = new (0x80) float[total];
		for (int i = 0; i < total; i++)
		{
			((float*)values)[i] = value;
		}
		SetName(key, newName);
		return key;
	}

	// FUNCTION: ENGINE 0x10843570
	unsigned __int64* DBSubject::InitString(unsigned __int64* key, const core::Name<core::CaseSensitiveKey>& newName,
		int newCategory, int newPlayers, int newScope, const char* value, int length, const DBSubjectInfo& info)
	{
		scope = newScope;
		type = TYPE_STRING;
		players = newPlayers;
		count = info.a;
		stride = length;
		id = info.b;
		category = newCategory;
		persistent = info.flag;
		if (value != 0 && *value != 0)
		{
			defaultString = new (0x80) char[length];
			core::StrNCpy((char*)defaultString, value, (unsigned int)stride);
		}
		else
		{
			defaultString = 0;
		}
		int total = count * newPlayers;
		values = new (0x80) char[stride * total];
		char* destination = (char*)values;
		if (total > 0)
		{
			do
			{
				core::StrNCpy(destination, value, (unsigned int)stride);
				destination += stride;
				total--;
			}
			while (total != 0);
		}
		SetName(key, newName);
		return key;
	}

	// FUNCTION: ENGINE 0x10843640
	unsigned __int64* DBSubject::InitWideString(unsigned __int64* key,
		const core::Name<core::CaseSensitiveKey>& newName, int newCategory, int newPlayers, int newScope,
		const wchar_t* value, int length, const DBSubjectInfo& info)
	{
		scope = newScope;
		type = TYPE_WIDE_STRING;
		players = newPlayers;
		count = info.a;
		stride = length;
		id = info.b;
		category = newCategory;
		persistent = info.flag;
		defaultWideString = (const wchar_t*)new (0x80) char[length];
		memcpy((void*)defaultWideString, value, stride);
		int total = count * newPlayers;
		values = new (0x80) char[stride * total];
		char* destination = (char*)values;
		if (total > 0)
		{
			do
			{
				memcpy(destination, value, stride);
				destination += stride;
				total--;
			}
			while (total != 0);
		}
		SetName(key, newName);
		return key;
	}

	// FUNCTION: ENGINE 0x10843700
	unsigned int DBSubject::GetObserverCount()
	{
		return observers->Size();
	}

	// FUNCTION: ENGINE 0x108437E0
	void DBSubject::AddChange(DBChange* change)
	{
		changes->PushBack(change);
	}

	// FUNCTION: ENGINE 0x10843810
	void DBSubject::AddObserver(DBObserver* observer, int a, int b)
	{
		DBObserverEntry entry = { observer, a, b };
		observers->PushBack(entry);
	}

	// FUNCTION: ENGINE 0x10843930
	void DBSubject::SetInt(unsigned int player, int value, unsigned int index)
	{
		((int*)values)[count * player + index] = value;
		AddChange(new (1) DBChange(player, value, index));
	}

	// FUNCTION: ENGINE 0x10843990
	void DBSubject::SetFloat(unsigned int player, float value, unsigned int index)
	{
		((float*)values)[count * player + index] = value;
		AddChange(new (1) DBChange(player, value, index));
	}

	// FUNCTION: ENGINE 0x10843A00
	void DBSubject::SetString(unsigned int player, const char* value, unsigned int index)
	{
		core::StrNCpy((char*)values + (count * player + index) * stride, value, (unsigned int)stride);
		AddChange(new (1) DBChange(player, value, index, stride));
	}

	// FUNCTION: ENGINE 0x10843A70
	void DBSubject::SetWideString(unsigned int player, const wchar_t* value, unsigned int index)
	{
		memcpy((char*)values + (count * player + index) * stride, value, stride);
		AddChange(new (1) DBChange(player, value, index, stride));
	}

	// FUNCTION: ENGINE 0x10843AE0
	void DBSubject::CopyValues(DBSubject* source, unsigned int player)
	{
		int total = source->count;
		switch (source->type)
		{
		case TYPE_INT:
			for (int i = 0; i < total; i++)
			{
				SetInt(player, source->GetInt(player, i), i);
			}
			break;
		case TYPE_FLOAT:
			for (int i = 0; i < total; i++)
			{
				SetFloat(player, source->GetFloat(player, i), i);
			}
			break;
		case TYPE_STRING:
			for (int i = 0; i < total; i++)
			{
				SetString(player, source->GetString(player, i), i);
			}
			break;
		case TYPE_WIDE_STRING:
			for (int i = 0; i < total; i++)
			{
				SetWideString(player, source->GetWideString(player, i), i);
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x10843BE0
	void DBSubject::Reset(unsigned int player)
	{
		switch (type)
		{
		case TYPE_INT:
			for (int i = 0; i < count; i++)
			{
				SetInt(player, defaultInt, i);
			}
			break;
		case TYPE_FLOAT:
			for (int i = 0; i < count; i++)
			{
				SetFloat(player, defaultFloat, i);
			}
			break;
		case TYPE_STRING:
			for (int i = 0; i < count; i++)
			{
				SetString(player, defaultString, i);
			}
			break;
		case TYPE_WIDE_STRING:
			for (int i = 0; i < count; i++)
			{
				SetWideString(player, defaultWideString, i);
			}
			break;
		}
	}

	// FUNCTION: ENGINE 0x10843CC0
	void DBSubject::SendChanges(int mode)
	{
		for (ChangeList::Iterator change = changes->Begin(); change != changes->End(); ++change)
		{
			ObserverList::Iterator entry = observers->Begin();
			DBChange* value = *change;
			core::Name<core::CaseSensitiveKey> notified;
			for (; entry != observers->End(); ++entry)
			{
				DBObserverEntry observerEntry = *entry;
				if (observerEntry.a == 0 && mode == observerEntry.b)
				{
					notified = name;
					observerEntry.observer->OnDBSlot0((int)&notified, (int)value);
				}
			}
			if (mode == 0 && value != 0)
			{
				delete value;
			}
		}
		if (mode == 0)
		{
			changes->Clear();
		}
	}

	// FUNCTION: ENGINE 0x10843DA0
	void DBSubject::NotifyObservers()
	{
		for (ObserverList::Iterator entry = observers->Begin(); entry != observers->End(); ++entry)
		{
			(*entry).observer->OnDBSlot1((int)&name, (int)this);
		}
	}

	// FUNCTION: ENGINE 0x10843DD0
	// EQUIVALENT: register allocation only (the engine keeps this in ecx and reloads the list, ours keeps the list in ecx), 57.1 %
	void DBSubject::RemoveObserver(void* owner)
	{
		ObserverList::ValueNode* previous = 0;
		for (ObserverList::ValueNode* node = (ObserverList::ValueNode*)observers->head; node != 0;
			node = (ObserverList::ValueNode*)node->next)
		{
			if (node->value.observer == owner)
			{
				if (previous == 0)
				{
					Allocator::Free(observers->PopFront());
				}
				else
				{
					Allocator::Free(observers->RemoveAfter(previous));
				}
				return;
			}
			previous = node;
		}
	}

	// FUNCTION: ENGINE 0x10843F30
	void DBSubject::ClearValues()
	{
		SendChanges(0);
		if (locked)
		{
			NotifyObservers();
		}
	}

	// FUNCTION: ENGINE 0x10843F50
	DBSubject::~DBSubject()
	{
		if (observers != 0)
		{
			observers->Clear();
			delete observers;
			observers = 0;
		}
		if (changes != 0)
		{
			for (ChangeList::Iterator change = changes->Begin(); change != changes->End(); ++change)
			{
				if (*change != 0)
				{
					delete *change;
				}
			}
			changes->Clear();
			delete changes;
			changes = 0;
		}
		switch (type)
		{
		case TYPE_INT:
			delete[] (int*)values;
			break;
		case TYPE_FLOAT:
			delete[] (float*)values;
			break;
		case TYPE_STRING:
			delete[] defaultString;
			delete[] (char*)values;
			break;
		case TYPE_WIDE_STRING:
			delete[] defaultWideString;
			delete[] (char*)values;
			break;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10843050
// FUNCTION: ENGINE 0x108431A0
// FUNCTION: ENGINE 0x108431B0
// FUNCTION: ENGINE 0x108431C0
// FUNCTION: ENGINE 0x108431D0
// FUNCTION: ENGINE 0x108431E0
// FUNCTION: ENGINE 0x10843200
// FUNCTION: ENGINE 0x10843220
// FUNCTION: ENGINE 0x10843240
// FUNCTION: ENGINE 0x10843270
// FUNCTION: ENGINE 0x108432D0
// FUNCTION: ENGINE 0x108432E0
// FUNCTION: ENGINE 0x10843710
// FUNCTION: ENGINE 0x10843750
// FUNCTION: ENGINE 0x10843860
// FUNCTION: ENGINE 0x108438B0
// FUNCTION: ENGINE 0x108438E0
// FUNCTION: ENGINE 0x108438F0
// FUNCTION: ENGINE 0x10843900
// FUNCTION: ENGINE 0x10843E30
// FUNCTION: ENGINE 0x10843E60
// FUNCTION: ENGINE 0x10843E90
// FUNCTION: ENGINE 0x10843EE0
