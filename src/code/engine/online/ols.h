// engine::OLS (RTTI name; the online services singleton, 0x108441E0) as far as its users in the game states need it:
// the user it currently serves and the list of callbacks that are told about online events. A callback derives from
// the list's node type (RTTI: engine::OLS::Callback, container::SListLite<OLS::Callback>::Node) and has one virtual
// function. Names other than the RTTI ones are guesses.
#ifndef ENGINE_ONLINE_OLS_H
#define ENGINE_ONLINE_OLS_H

#include "code/container/slist.h"
#include "code/engine/message.h"
#include "code/engine/online/olsprofile.h"

namespace engine
{
	struct OLSMessageWords;

	// An online event (RTTI: engine::OLSMessage; the user it concerns at +0x14)
	struct OLSMessage : public IntrusiveMessage
	{
		OLSMessage(int newType, short newId) : IntrusiveMessage(newType, newId)
		{
			unknownC = 0;
		}
		virtual ~OLSMessage()
		{
		}

		int unknownC;

		// The words a handler reads behind the common part (see OLSMessageWords)
		OLSMessageWords* Words();
	};

	// The messages that carry two more words (the profile and storage ones; +0x10 and the user they concern at +0x14).
	// The common part is 0x10 bytes: the game message has nothing behind it and the user message one word
	struct OLSMessageWords : public OLSMessage
	{
		OLSMessageWords(int newType, short newId) : OLSMessage(newType, newId)
		{
		}

		int unknown10;
		unsigned int user;
	};

	inline OLSMessageWords* OLSMessage::Words()
	{
		return static_cast<OLSMessageWords*>(this);
	}

	// The messages of the online services' parts (RTTI names; the part's message type is the constructor's first
	// argument to the base)
	struct OLSUserMessage : public OLSMessage
	{
		// 0x10886A30 (the engine kept an out-of-line copy as well, olsmessages.cpp)
		explicit OLSUserMessage(short newId) : OLSMessage(5, newId)
		{
		}
		virtual ~OLSUserMessage()
		{
		}

		int user;  // +0x10
	};

	struct OLSGameMessage : public OLSMessage
	{
		// 0x10887D20
		explicit OLSGameMessage(short newId);
		virtual ~OLSGameMessage()
		{
		}
	};

	struct OLSProfileStorageMessage : public OLSMessageWords
	{
		// 0x1088ACA0
		explicit OLSProfileStorageMessage(short newId);
		virtual ~OLSProfileStorageMessage()
		{
		}
	};

	// Tells that a profile was picked (type 0, id 6 and 7; the inline constructor is the engine's, the deleting destructor is
	// shared with the other messages)
	struct OLSProfileMessage : public OLSMessageWords
	{
		explicit OLSProfileMessage(short newId) : OLSMessageWords(0, newId)
		{
		}
		virtual ~OLSProfileMessage()
		{
		}
	};

	// The user the services currently serve (+0x14: its id)
	class OLSCurrentUser
	{
	public:
		unsigned char unknown0[0x14];
		unsigned int id;
	};

	// The online session at OLS +0x7C (of its 24 slots only the one the exception manager asks is declared)
	class OLSSession
	{
	public:
		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		virtual void Slot10();
		virtual void Slot11();
		virtual void Slot12();
		virtual void Slot13();
		virtual void Slot14();
		virtual void Slot15();
		virtual void Slot16();
		// vftable slot 17: whether the session is up
		virtual bool IsConnected();
	};

	// The user table at OLS +0x80: the entries are 0x40 bytes each
	class OLSUserTable
	{
	public:
		unsigned char unknown0[0x18];
		int count;
		unsigned char* items;  // +0x1C
		unsigned char unknown20[4];
		int current;  // +0x24
		unsigned char unknown28[0x10];
		bool unknown38;
		// 0x108E7F60 (another unit)
		bool Unknown108E7F60();
	};

	// The game the services run on this machine (RTTI engine::OLSGame, olsgame.h)
	class OLSGame;

	// The list of users at OLS +0x94 and the friend list at +0x98 (olsfriend.h)
	class OLSUserList;
	class OLSFriend;

	// What the online services tell about the users they hear of (OLS +0xA0; of its slots only the two the user list
	// calls are declared, names guessed)
	class OLSUserObserver
	{
	public:
		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void OnUserLinked(int index);
		virtual void OnUserUnlinked(int index);
	};

	class OLS
	{
	public:
		class Callback : public container::SListLite<Callback>::Node
		{
		public:
			// Tells the callback about an online event
			virtual void OnMessage(OLSMessage* message) = 0;
		};

		// 0x108441E0
		static OLS* Get();
		// 0x108449A0: tells every callback about an event
		void SendMessage(OLSMessage* message);

		// The local user that is selected: null when there are none
		OLSGame* GetLocalUser()
		{
			return localUsers != 0 ? localUsers[selectedLocalUser] : 0;
		}

		void AddCallback(Callback* callback)
		{
			callbacks.PushBack(callback);
		}
		void RemoveCallback(Callback* callback)
		{
			callbacks.Remove(callback);
		}

		// The vftable (RTTI: engine::OLS, 6 slots; its constructor is 0x10844760, the destructor 0x10844C20 and the deleting
		// destructor in slot 4 is 0x10844C30)
		virtual void Slot0();
		// vftable slot 1 (0x10844300): the per-frame update of the services
		virtual void Update();
		virtual void Slot2();
		virtual void Slot3();
		virtual ~OLS();
		virtual void Slot5();

		unsigned char unknown4[0x74];
		// The profile manager (+0x78); the older name and view of it is currentUser, whose id is its current profile
		union
		{
			OLSCurrentUser* currentUser;
			OLSProfile* profile;
		};
		OLSSession* session;  // +0x7C
		OLSUserTable* userTable;  // +0x80
		unsigned char unknown84[4];
		int selectedLocalUser;  // +0x88
		OLSGame** localUsers;  // +0x8C
		unsigned char unknown90[4];
		OLSUserList* userList;  // +0x94
		OLSFriend* friends;  // +0x98
		unsigned char unknown9C[4];
		OLSUserObserver* userObserver;  // +0xA0
		unsigned char unknownA4[8];
		container::SListLite<Callback> callbacks;
	};
}

#endif
