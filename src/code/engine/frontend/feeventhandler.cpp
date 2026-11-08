// The front end's event handler (unit 0x108E1260 - 0x108E1BC0; no assert path, file name guessed).
// The handler has several bases, so the pointers to its methods have two words
#pragma pointers_to_members(full_generality, multiple_inheritance)
#include "code/engine/frontend/feeventhandler.h"
#include "code/engine/database/gamedatabase.h"
#include "code/engine/frontend/frontend.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/core/strings.h"
#include <string.h>
#include <new>

namespace core
{
	// 0x1063B990 (the count returning form)
	int SNPrintfCount(char* buffer, int size, const char* format, ...);
}

namespace engine
{
	class FrontEnd;
	FrontEnd* Unknown10864330();

	// FUNCTION: ENGINE 0x108E1330
	void FEEventHandler::OnMessage(OLSMessage* message)
	{
		if (gFEEventCategories[message->type].enabled)
		{
			const char* categoryName = gFEEventCategories[message->type].name;
			if (gFEEventCategories[message->type].count > 0)
			{
				unsigned short id = message->id;
				if ((int)id < gFEEventCategories[message->type].count)
				{
					const char* eventName = gFEEventCategories[message->type].events[id];
					int value = message->unknownC;
					if (message->type == 0xB && id == 2 && (char)message->Words()->user == 0)
					{
						value = -1;
					}
					Unknown10872840(Unknown10864330(), "AS_Event", "%s%s%s%d%s", gFEOnlineKind, categoryName, eventName,
						value, "");
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x108E1660
	void FEEventHandler::OnDBSlot0(int a, int b)
	{
		FEEventMap::Iterator iterator(&map);
		char* slot = iterator.Find(((core::Name<core::CaseSensitiveKey>*)a)->GetHash());
		if (slot != 0)
		{
			const int* record = (const int*)b;
			const char* kind = gFEDatabaseKind;
			char valueText[0x80];
			valueText[0] = 0;
			switch (record[0])
			{
			case 0:
				core::SNPrintfCount(valueText, 0x80, "%d", record[2]);
				break;
			case 1:
				core::SNPrintfCount(valueText, 0x80, "%f", ((const float*)record)[2]);
				break;
			case 2:
				core::SNPrintfCount(valueText, 0x80, "%s", (const char*)record[2]);
				break;
			}
			char updateText[0x80];
			core::SNPrintfCount(updateText, 0x80, "Update %d", ((const unsigned char*)record)[5]);
			int sequence = ((const unsigned char*)record)[4];
			Unknown10872840(Unknown10864330(), "AS_Event", "%s%s%s%d%s", kind, slot, updateText, sequence, valueText);
		}
	}

	// FUNCTION: ENGINE 0x108E1B00
	void FEEventHandler::OnDBSlot1(int a, int b)
	{
		FEEventMap::Iterator iterator(&map);
		const unsigned __int64& hash = ((core::Name<core::CaseSensitiveKey>*)a)->GetHash();
		char* slot = iterator.Find(hash);
		if (slot != 0)
		{
			Unknown10872840(Unknown10864330(), "AS_Event", "%s%s%s%d%s", gFEDatabaseKind, slot, "Delete", 0, "");
			*slot = 0;
			map.Remove(hash, slot);
		}
	}

	// FUNCTION: ENGINE 0x108E1780
	void FEEventHandler::RegisterEvent(const char* kind, const char* name)
	{
		if (kind[0] == gFEOnlineKind[0])
		{
			for (int i = 0; i < 13; i++)
			{
				if (core::StrCmp(name, gFEEventCategories[i].name) == 0)
				{
					gFEEventCategories[i].enabled = true;
				}
			}
			return;
		}
		if (kind[0] == gFEDatabaseKind[0])
		{
			int index = 0;
			if (count > 0)
			{
				char* text = names->text;
				do
				{
					if (*text == 0)
					{
						break;
					}
					index++;
					text += sizeof(NameSlot);
				}
				while (index < count);
			}
			core::StrNCpy(names[index].text, name, 0x20u);
			core::Name<core::CaseSensitiveKey> hashName(names[index].text, 1);
			map.Insert(hashName.GetHash(), names[index].text);
			gGameDatabase->AddObserver(hashName, this, 0, 0);
		}
	}

	// FUNCTION: ENGINE 0x108E1A30
	void FEEventHandler::UnregisterEvent(const char* kind, const char* name)
	{
		if (kind[0] == gFEOnlineKind[0])
		{
			for (int i = 0; i < 13; i++)
			{
				if (core::StrCmp(name, gFEEventCategories[i].name) == 0)
				{
					gFEEventCategories[i].enabled = false;
				}
			}
			return;
		}
		if (kind[0] == gFEDatabaseKind[0])
		{
			core::Name<core::CaseSensitiveKey> hashName(name, 1);
			FEEventMap::Iterator iterator(&map);
			const unsigned __int64& hash = hashName.GetHash();
			char* slot = iterator.Find(hash);
			if (slot != 0)
			{
				gGameDatabase->RemoveObserver(hashName, (DBObserver*)this);
				*slot = 0;
				map.Remove(hash, slot);
			}
		}
	}

	// The handler (0x1131AA68; name guessed)
	FEEventHandler* gFEEventHandler;

	// FUNCTION: ENGINE 0x108E1890
	FEEventHandler::FEEventHandler(int newCount) : count(newCount), map(newCount, 0x3C, 100)
	{
		OLS::Get()->AddCallback(this);
		names = new NameSlot[count];
		for (int i = 0; i < count; i++)
		{
			names[i].text[0] = 0;
		}
		LuaScriptManager* scripts = GetScriptManager();
		scripts->SetOwner(this);
		scripts->RegisterMethod("fe_RegisterEvent", this, &FEEventHandler::RegisterEvent);
		scripts->RegisterMethod("fe_UnregisterEvent", this, &FEEventHandler::UnregisterEvent);
		scripts->ClearOwner();
	}

	// FUNCTION: ENGINE 0x108E1400
	FEEventHandler::~FEEventHandler()
	{
		LuaScriptManager* scripts = GetScriptManager();
		scripts->Unregister(this);
		delete[] names;
		OLS::Get()->RemoveCallback(this);
	}

	// FUNCTION: ENGINE 0x108E15A0
	void ReleaseSubsystemAA68()
	{
		if (gFEEventHandler != 0)
		{
			delete gFEEventHandler;
			gFEEventHandler = 0;
		}
	}

	// FUNCTION: ENGINE 0x108E1B80
	void CreateFEEventHandler(int count)
	{
		if (gFEEventHandler == 0)
		{
			gFEEventHandler = new FEEventHandler(count);
		}
	}

	// FUNCTION: ENGINE 0x108E1320
	FEEventHandler* GetFEEventHandler()
	{
		return gFEEventHandler;
	}
}

// Kept copies (inline members of this unit):
// FUNCTION: ENGINE 0x108E13E0
// FUNCTION: ENGINE 0x108E1520
