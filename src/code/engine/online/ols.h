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
		unsigned char unknown7C[0xac - 0x7c];
		container::SListLite<Callback> callbacks;
	};
}

#endif
