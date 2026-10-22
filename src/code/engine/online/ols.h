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
		unsigned char unknownC[8];
		unsigned int user;
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
