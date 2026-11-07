// engine::OLSFriend (RTTI name): the interface the online service's friend list is driven through. Its script
// methods are registered by the unit that owns it (Method / Closure wrappers in olsfriendwrappers.cpp); the
// interface itself has 23 virtual slots whose defaults do nothing. Slot names and signatures are guesses from the
// default bodies; the unit is 0x108EA320 - 0x108EA510 (no assert path, file name guessed).
#ifndef ENGINE_ONLINE_OLSFRIEND_H
#define ENGINE_ONLINE_OLSFRIEND_H

#include "code/engine/controller/inputsystem.h"

namespace engine
{
	// A string of wide characters the front end shows (0x108A5560 / 0x108A5570: constructor and destructor, another unit)
	class WideStringBuffer
	{
	public:
		// 0x108A5560 / 0x108A5570
		WideStringBuffer();
		~WideStringBuffer();
		// 0x108A5670: the text as characters, cut to the size
		void CopyTo(char* destination, int size);
		// 0x108A55B0: makes room for that many characters (the characters it held are gone)
		void Allocate(int newCapacity);
		// 0x108A5640: takes the characters as the text
		void Set(const char* text);
		// 0x108A5590: gives the characters back
		void Release();
		// 0x108A55F0: uses the characters of somebody else as its text when it holds none of its own
		void Borrow(const wchar_t* text);
		// 0x108A5600 / 0x108A5620: copies the text of another buffer / the wide characters in
		void CopyFrom(const WideStringBuffer& other);
		void Copy(const wchar_t* text);

		wchar_t* data;
		// The characters data has room for; 0 when it is borrowed or empty
		unsigned int capacity;  // +4
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
		// 0x108873A0 / 0x10887B70: the destructor lets the values go (FreeValues, 0x10887500)
		OLSUserRecord();
		~OLSUserRecord();
		void FreeValues();
		// 0x10886BB0: makes the record free again
		void Reset();
		// 0x10886BF0: gives the user a name
		void SetName(const WideStringBuffer& text);
		// 0x10887340 / 0x10887360 / 0x10887380: the game / the session / the invitation the user is in (names guessed); each
		// is kept in its member and in a flag of the record
		struct Invite;
		void SetGame(int value)
		{
			unknown14 = value;
			if (value != 0)
			{
				flags |= 2;
			}
			else
			{
				flags &= ~2;
			}
		}
		void SetSession(int value)
		{
			unknown18 = value;
			if (value != 0)
			{
				flags |= 1;
			}
			else
			{
				flags &= ~1;
			}
		}
		void SetInvite(Invite* value)
		{
			invite = value;
			if (value != 0)
			{
				flags |= 4;
			}
			else
			{
				flags &= ~4;
			}
		}

		int index;  // +0
		WideStringBuffer name;  // +4
		unsigned int controller;  // +0xC (-1 for none)
		int id;  // +0x10 (-1 for a free record)
		int unknown14;
		int unknown18;
		// The invitation the user sent (its id is at +0x10)
		struct Invite
		{
			unsigned char unknown0[0xC];
			unsigned int flags;  // +0xC
			int id;  // +0x10
		}* invite;  // +0x1C
		unsigned int flags;  // +0x20
		int unknown24;
		int valueCount;  // +0x28
		int unknown2C;
		void* unknown30;
		unsigned char* values;  // +0x34 (valueCount entries of 0x10 bytes)
	};

	// A tagged value of the online services (16 bytes; the tag at +0, a wide string for tag 4 at +8; 0x10844110 /
	// 0x10844120 are the engine's copies of its constructor and destructor)
	struct OLSValue
	{
		OLSValue();
		~OLSValue();

		unsigned char type;
		unsigned char unknown1[7];
		WideStringBuffer text;  // +8
	};

	// A table of eight-byte entries (an id and a kind; 0x10844450 sets one), made by 0x108443F0 (names guessed)
	struct OLSKeyTable
	{
		struct Entry
		{
			int id;
			int kind;
		};

		// 0x10844450
		void Set(int index, int id, int kind);

		Entry* entries;
		int count;
	};

	// What the user list knows about one setting (0x14 bytes, copied from the platform layer; names guessed)
	struct OLSSettingInfo
	{
		int used;
		int unknown4;
		int type;  // +8: 1 to 5
		const char* name;  // +0xC
		int scope;  // +0x10: 2 for none
	};

	// How the list recognises a user on the net (a machine and the slot on it; names guessed)
	struct OLSHostKey
	{
		unsigned int address;
		int unknown4;
		unsigned char slot;  // +8
	};

	// The list of users at OLS +0x94 (RTTI engine::OLSUser; a listener of the input system, the platform layers derive
	// from it and implement the slots behind the input ones). Names guessed
	class OLSUserList : public controller::InputSystem::InputCallback
	{
	public:
		// 0x10887560: the number of settings, of ids and of records
		OLSUserList(int newSettingCount, int newIdCount, int newRecordCount);
		// vftable slots 0 - 2 of the input listener: a controller was connected / given a player / its state changed
		virtual void OnFlags(unsigned int id, int local, unsigned int flags, bool set);
		virtual void OnValue(unsigned int id, int local, controller::PlayerInfo* input);
		virtual void OnNotify(int a, int b, int c);
		// vftable slot 3 (0x10887CD0), slot 4 (0x104DCCF0) and slot 5 (0x108878B0, the list starts listening and makes
		// the database subjects of its settings)
		virtual void Slot3();
		virtual void Slot4();
		virtual void Start();

		// 0x108871C0: the index of the selected user
		int GetSelected();
		// 0x108871B0
		void SetSelected(int index);
		// 0x10886F50
		void SetCurrentUser(int id);
		// 0x10887870: the user is no longer needed as the invited one (by its id)
		void ClearInvite(int id);

		// 0x10886C40 / 0x10886C60: makes one record / all of them free again
		void ResetRecord(int index);
		void Reset();
		// 0x10886C90 / 0x10886CD0: the index of the record of a user id / of a controller, -1 for none
		int FindIndexById(int id);
		int FindIndexByController(unsigned int controller);
		// 0x10886D10: the index of the record whose controller sits on the machine of the key
		int FindIndexByHost(const OLSHostKey* key);
		// 0x10886D80: the record of the user id (a free one is made when there is none), null when the list is full
		OLSUserRecord* AddUser(int id);
		// 0x10886E60: lets the record go when no flag is left (the users hear of it)
		void Release(int index);
		// 0x10886EF0 / 0x10886F10: set the id of a record / set or clear flags of it (clearing may release it)
		void SetRecordId(int index, int id);
		void SetFlag(int index, unsigned int mask, bool set);
		// 0x10887130 / 0x10887160: describe a setting (its id and kind / the platform's information)
		void SetSettingKey(int index, const OLSKeyTable::Entry* key);
		void SetSettingInfo(int index, const OLSSettingInfo* info);
		// 0x108871D0: whether the selected user has an invitation that can still be answered
		int CanAnswerInvite();
		// 0x10887200: the name of the selected user as text (in the member buffer)
		const char* GetSelectedName();
		// 0x10887230: the selected user's values as text
		const char* GetSelectedValuesText();
		// 0x108876C0 / 0x10887780 / 0x10887820: the user takes part in a game / in a session / was invited (answer the index)
		int SetGame(int id, int value, const WideStringBuffer* text);
		int SetSession(int id, int value, const WideStringBuffer* text, unsigned int controller);
		int SetInvite(int id, OLSUserRecord::Invite* invite, const WideStringBuffer* text);
		// 0x10887710 / 0x108877D0: forget every user of a game / of a session
		void ClearGame(int value);
		void ClearSession(int value);

		int settingCount;  // +8
		int idCount;  // +0xC
		int recordCount;  // +0x10
		int activeCount;  // +0x14
		OLSUserRecord* records;  // +0x18
		int currentUser;  // +0x1C (the id of the user the current profile belongs to)
		OLSSettingInfo* settings;  // +0x20
		bool settingsChanged;  // +0x24
		OLSKeyTable::Entry* settingKeys;  // +0x28
		char text[0x100];  // +0x2C
		OLSKeyTable settingKeyTable;  // +0x12C
		OLSKeyTable idKeyTable;  // +0x134
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
