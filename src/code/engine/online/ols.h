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
		int unknown10;
		unsigned int user;
	};

	// The messages of the online services' parts (RTTI names; the part's message type is the constructor's first
	// argument to the base)
	struct OLSUserMessage : public OLSMessage
	{
		// 0x10886A30 (the engine kept this copy)
		explicit OLSUserMessage(short newId);
		virtual ~OLSUserMessage()
		{
		}
	};

	struct OLSGameMessage : public OLSMessage
	{
		// 0x10887D20
		explicit OLSGameMessage(short newId);
		virtual ~OLSGameMessage()
		{
		}
	};

	struct OLSProfileStorageMessage : public OLSMessage
	{
		// 0x1088ACA0
		explicit OLSProfileStorageMessage(short newId);
		virtual ~OLSProfileStorageMessage()
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
	};

	// A user that plays on this machine (another unit)
	class OLSLocalUser
	{
	public:
		// 0x108882C0: leaves the online session; false when there was none
		bool Unknown108882C0();
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
		OLSLocalUser* GetLocalUser()
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

		unsigned char unknown0[0x78];
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
		OLSLocalUser** localUsers;  // +0x8C
		unsigned char unknown90[0xac - 0x90];
		container::SListLite<Callback> callbacks;
	};
}

#endif
