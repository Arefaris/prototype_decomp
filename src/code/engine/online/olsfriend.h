// engine::OLSFriend (RTTI name): the interface the online service's friend list is driven through. Its script
// methods are registered by the unit that owns it (Method / Closure wrappers in olsfriendwrappers.cpp); the
// interface itself has 23 virtual slots whose defaults do nothing. Slot names and signatures are guesses from the
// default bodies; the unit is 0x108EA320 - 0x108EA510 (no assert path, file name guessed).
#ifndef ENGINE_ONLINE_OLSFRIEND_H
#define ENGINE_ONLINE_OLSFRIEND_H

namespace engine
{
	// A string of wide characters the front end shows (0x108A5560 / 0x108A5570: constructor and destructor, another unit)
	class WideStringBuffer
	{
	public:
		WideStringBuffer();
		~WideStringBuffer();
		// 0x108A5670: the text as characters, cut to the size
		void CopyTo(char* destination, int size);
		// 0x108A55B0: makes room for that many characters
		void Allocate(int capacity);
		// 0x108A5640: takes the characters as the text
		void Set(const char* text);

		unsigned char unknown0[8];
	};

	// What the friend list keeps for one friend (0x1C bytes; the destructor is 0x108E9C30)
	struct OLSFriendEntry
	{
		// 0x108EA260
		OLSFriendEntry();
		~OLSFriendEntry();
		// 0x108E9C50: empties the entry and lets the user list know it no longer needs the user
		void Reset();

		WideStringBuffer name;  // +0
		int userId;  // +8
		unsigned int flags;  // +0xC
		int unknown10;
		WideStringBuffer status;  // +0x14
	};

	// What the friend list keeps for a user the online service knows (0x38 bytes)
	struct OLSUserRecord
	{
		// 0x10886BB0: makes the record free again
		void Reset();

		int index;  // +0
		WideStringBuffer name;  // +4
		unsigned int controller;  // +0xC (-1 for none)
		int id;  // +0x10 (-1 for a free record)
		int unknown14;
		int unknown18;
		// The invitation the user sent (its id is at +0x10)
		struct Invite
		{
			unsigned char unknown0[0x10];
			int id;  // +0x10
		}* invite;  // +0x1C
		unsigned int flags;  // +0x20
		int unknown24;
		int valueCount;  // +0x28
		int unknown2C;
		void* unknown30;
		unsigned char* values;  // +0x34 (valueCount entries of 0x10 bytes)
	};

	// The list of users at OLS +0x94 (another unit; names guessed)
	class OLSUserList
	{
	public:
		// 0x108871C0: the index of the selected user
		int GetSelected();
		// 0x10886F50
		void SetCurrentUser(int id);
		// 0x10887870: the user is no longer needed (by its id)
		void Unknown10887870(int id);

		// 0x10886C40 / 0x10886C60: makes one record / all of them free again
		void ResetRecord(int index);
		void Reset();
		// 0x10886C90 / 0x10886CD0: the index of the record of a user id / of a controller, -1 for none
		int FindIndexById(int id);
		int FindIndexByController(unsigned int controller);

		unsigned char unknown0[0x10];
		int recordCount;  // +0x10
		int activeCount;  // +0x14
		OLSUserRecord* records;  // +0x18
		int currentUser;  // +0x1C (the id of the user the current profile belongs to)
		unsigned char unknown20[0x13C - 0x20];
		int selected;  // +0x13C
	};

	class OLSFriend
	{
	public:
		// 0x108EADF0: makes room for that many users and registers the script methods
		explicit OLSFriend(unsigned int newCount);
		// 0x108EA8A0 is the deleting destructor, 0x108EA320 the body
		virtual ~OLSFriend();
		// vftable slots 1 - 22: the defaults (0x108EA390 - 0x108EA4E0)
		virtual void Slot1()
		{
		}
		virtual void Slot2()
		{
		}
		virtual void Slot3()
		{
		}
		virtual bool Slot4(int a)
		{
			return false;
		}
		virtual bool Slot5()
		{
			return false;
		}
		virtual void Slot6()
		{
		}
		virtual void Slot7()
		{
		}
		virtual void Slot8()
		{
		}
		virtual void Slot9(int a)
		{
		}
		virtual void Slot10(int a)
		{
		}
		virtual void Slot11(int a)
		{
		}
		virtual void Slot12(int a)
		{
		}
		virtual void Slot13(int a)
		{
		}
		virtual void Slot14(int a)
		{
		}
		virtual void Slot15(int a, int b, int c)
		{
		}
		virtual void Slot16(int a, int b, int c)
		{
		}
		virtual void Slot17(int a, WideStringBuffer b)
		{
		}
		virtual void Slot18(int a)
		{
		}
		virtual void Slot19(int a)
		{
		}
		virtual void Slot20()
		{
		}
		virtual void Slot21(const char* a)
		{
		}
		virtual void Slot22(int a)
		{
		}

		// The script methods (names from the registration in the constructor, 0x108EADF0)
		// 0x108E9D30: the id of the user at an index
		int GetUserId(int index);
		// 0x108E9D00: empties every entry
		void ResetEntries();
		// 0x108E9CE0: the profile of that index (-1 for none) was picked (name guessed)
		void OnProfileSelected(int index);
		// 0x108E9D50 / 0x108E9DC0: what the selected user is doing, as the scripts want it (answered in the text member)
		const char* GetPresence();
		const char* GetAttributes();
		// 0x108E9FD0
		int GetNumUsers();
		// 0x108E9FE0 / 0x108EA020: put the selected user on the black list / mute it (slots 13 and 14, by the id)
		void BlackListUser();
		void MuteUser();
		// 0x108EA060 / 0x108EA080 / 0x108EA0A0 / 0x108EA0C0 / 0x108EA0E0: slots 9, 10, 11, 12 and 22 with the selected user
		void SendFriendRequest();
		void AcceptFriendRequest();
		void DeclineFriendRequest();
		void RemoveFriendRequest();
		void RequestFriendStatus();
		// 0x108EA170 / 0x108EA1B0: slots 19 and 18 with the id of the invitation the selected user sent
		void AcceptGameInvite();
		void DeclineGameInvite();
		// 0x108EA100: sends an invitation with that text (not reconstructed)
		void SendGameInvite(const char* text);
		// 0x108E9F70: loads the users of a kind (the state follows it) and 0x108EA4F0: the same without a name
		void LoadUserSearch(int kind, const char* name);
		void LoadUsers(int kind);

		int unknown4;
		int userCount;  // +8
		OLSFriendEntry* entries;  // +0xC (allocated with new[])
		int unknown10;
		char text[0x100];  // +0x14: the text the presence and attribute queries answer with
		int state;  // +0x114: the kind of search the list was last loaded with
	};
}

#endif
