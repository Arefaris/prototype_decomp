// engine::OLSFriend: see olsfriend.h.
#include "code/engine/online/olsfriend.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/online/ols.h"
#include "code/core/strings.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108E9C30
	OLSFriendEntry::~OLSFriendEntry()
	{
	}

	// FUNCTION: ENGINE 0x108EA320
	// EQUIVALENT: register allocation (the engine keeps this in ebx, the element count in esi and the end of the array in edi, ours this in esi); every other instruction is the engine's
	OLSFriend::~OLSFriend()
	{
		GetScriptManager()->Unregister(this);
		if (entries != 0)
		{
			// The element count sits in the word before the array
			int* block = (int*)entries - 1;
			int index = *block;
			OLSFriendEntry* element = entries + index;
			while (--index >= 0)
			{
				element--;
				element->~OLSFriendEntry();
			}
			operator delete[](block);
		}
	}

	// FUNCTION: ENGINE 0x108E9C50
	// EQUIVALENT: scheduling (the engine keeps the id in edi across the second Get and pushes it afterwards; ours pushes it first; 63 %)
	void OLSFriendEntry::Reset()
	{
		flags = 0;
		unknown10 = -1;
		if (userId != -1)
		{
			int id = OLS::Get()->userList->records[userId].id;
			OLS::Get()->userList->Unknown10887870(id);
			userId = -1;
		}
		name.Set("");
		status.Set("");
	}

	// FUNCTION: ENGINE 0x108E9D00
	void OLSFriend::ResetEntries()
	{
		userCount = 0;
		for (int i = 0; i < unknown4; i++)
		{
			entries[i].Reset();
		}
	}

	// FUNCTION: ENGINE 0x108E9D30
	int OLSFriend::GetUserId(int index)
	{
		return entries[index].userId;
	}

	// FUNCTION: ENGINE 0x108E9FD0
	int OLSFriend::GetNumUsers()
	{
		return userCount;
	}

	// FUNCTION: ENGINE 0x108E9D50
	// EQUIVALENT: register allocation (the engine counts with ecx and keeps the entry pointer in esi, ours uses edx; 94 %)
	const char* OLSFriend::GetPresence()
	{
		if (state == 2)
		{
			return "";
		}
		int selected = OLS::Get()->userList->GetSelected();
		for (int i = 0; i < userCount; i++)
		{
			if (entries[i].userId == selected)
			{
				entries[i].name.CopyTo(text, 0x100);
				return text;
			}
		}
		return "";
	}

	// FUNCTION: ENGINE 0x108E9DC0
	// EQUIVALENT: register allocation and scheduling (the engine uses ecx where ours uses edx for the flag tests and schedules the name copy's address computation after the pushes; 56 %)
	const char* OLSFriend::GetAttributes()
	{
		int selected = OLS::Get()->userList->GetSelected();
		if (state == 2)
		{
			char name[0x20];
			OLSUserList* list = OLS::Get()->userList;
			list->records[selected].name.CopyTo(name, 0x20);
			core::SNPrintf(text, 0x100, "name=%s", name);
			return text;
		}
		for (int i = 0; i < userCount; i++)
		{
			if (entries[i].userId == selected)
			{
				unsigned int flags = entries[i].flags;
				core::SNPrintf(text, 0x100,
					"online=%d away=%d busy=%d playing=%d voice=%d joinable=%d gameinvite=%d sentinvite=%d sentrequest=%d recrequest=%d mute=%d isfriend=%d isblacklist=%d recent=%d",
					(flags & 0x1) == 0x1, (flags & 0x2) == 0x2, (flags & 0x4) == 0x4, (flags & 0x8) == 0x8, (flags & 0x10) == 0x10,
					(flags & 0x20) == 0x20, (flags & 0x40) == 0x40, (flags & 0x80) == 0x80, (flags & 0x100) == 0x100,
					(flags & 0x200) == 0x200, (flags & 0x800) == 0x800, (flags & 0x1000) == 0x1000, (flags & 0x2000) == 0x2000,
					(flags & 0x400) == 0x400);
				return text;
			}
		}
		return "";
	}

	// FUNCTION: ENGINE 0x108E9FE0
	// EQUIVALENT: register allocation (the engine pushes the id from ecx; 97 %)
	void OLSFriend::BlackListUser()
	{
		int selected = OLS::Get()->userList->GetSelected();
		OLSUserRecord* records = OLS::Get()->userList->records;
		Slot13(records[selected].id);
	}

	// FUNCTION: ENGINE 0x108EA020
	// EQUIVALENT: register allocation (the engine pushes the id from ecx; 97 %)
	void OLSFriend::MuteUser()
	{
		int selected = OLS::Get()->userList->GetSelected();
		OLSUserRecord* records = OLS::Get()->userList->records;
		Slot14(records[selected].id);
	}

	// FUNCTION: ENGINE 0x108EA060
	void OLSFriend::SendFriendRequest()
	{
		int selected = OLS::Get()->userList->GetSelected();
		Slot9(selected);
	}

	// FUNCTION: ENGINE 0x108EA080
	void OLSFriend::AcceptFriendRequest()
	{
		int selected = OLS::Get()->userList->GetSelected();
		Slot10(selected);
	}

	// FUNCTION: ENGINE 0x108EA0A0
	void OLSFriend::DeclineFriendRequest()
	{
		int selected = OLS::Get()->userList->GetSelected();
		Slot11(selected);
	}

	// FUNCTION: ENGINE 0x108EA0C0
	void OLSFriend::RemoveFriendRequest()
	{
		int selected = OLS::Get()->userList->GetSelected();
		Slot12(selected);
	}

	// FUNCTION: ENGINE 0x108EA0E0
	void OLSFriend::RequestFriendStatus()
	{
		int selected = OLS::Get()->userList->GetSelected();
		Slot22(selected);
	}

	// FUNCTION: ENGINE 0x108EA170
	void OLSFriend::AcceptGameInvite()
	{
		OLSUserList* list = OLS::Get()->userList;
		int selected = list->GetSelected();
		Slot19(list->records[selected].invite->id);
	}

	// FUNCTION: ENGINE 0x108EA1B0
	void OLSFriend::DeclineGameInvite()
	{
		OLSUserList* list = OLS::Get()->userList;
		int selected = list->GetSelected();
		Slot18(list->records[selected].invite->id);
	}

	// FUNCTION: ENGINE 0x108E9F70
	void OLSFriend::LoadUserSearch(int kind, const char* name)
	{
		state = kind;
		switch (kind)
		{
		case 0:
			Slot6();
			break;
		case 1:
			Slot3();
			break;
		case 2:
			Slot8();
			break;
		case 3:
			Slot21(name);
			break;
		}
	}

	// FUNCTION: ENGINE 0x108EA4F0
	void OLSFriend::LoadUsers(int kind)
	{
		LoadUserSearch(kind, "");
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108EA390
// FUNCTION: ENGINE 0x108EA3A0
// FUNCTION: ENGINE 0x108EA3B0
// FUNCTION: ENGINE 0x108EA3C0
// FUNCTION: ENGINE 0x108EA3D0
// FUNCTION: ENGINE 0x108EA3E0
// FUNCTION: ENGINE 0x108EA3F0
// FUNCTION: ENGINE 0x108EA400
// FUNCTION: ENGINE 0x108EA410
// FUNCTION: ENGINE 0x108EA420
// FUNCTION: ENGINE 0x108EA430
// FUNCTION: ENGINE 0x108EA440
// FUNCTION: ENGINE 0x108EA450
// FUNCTION: ENGINE 0x108EA460
// FUNCTION: ENGINE 0x108EA470
// FUNCTION: ENGINE 0x108EA480
// FUNCTION: ENGINE 0x108EA490
// FUNCTION: ENGINE 0x108EA4A0
// FUNCTION: ENGINE 0x108EA4B0
// FUNCTION: ENGINE 0x108EA4C0
// FUNCTION: ENGINE 0x108EA4D0
// FUNCTION: ENGINE 0x108EA4E0
// FUNCTION: ENGINE 0x108EA8A0
