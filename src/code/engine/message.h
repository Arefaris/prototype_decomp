// engine::Message and engine::IntrusiveMessage (names from the RTTI). Layout from the message constructors: vftable,
// a message type (12 for the camera messages, 14 for PlayerControlChangedMessage, whose object is 0x14 bytes, so
// this is not the size), a 16-bit id and 16 bits of flags. The constructor parameters and the member names are
// guesses; the base constructor is inline (the derived constructors store the fields themselves and write only the
// final vftable).
#ifndef ENGINE_MESSAGE_H
#define ENGINE_MESSAGE_H

namespace content
{
	struct ClassInfo;
	struct MemberList;
}

namespace engine
{
	class Behaviour;

	struct Message
	{
	public:
		Message(int newType, short newId)
		{
			type = newType;
			id = newId;
			flags = 0;
		}
		virtual ~Message()
		{
		}

		// 0x108A08F0 (another unit): hands the message to one behaviour (name guess)
		void SendTo(Behaviour* behaviour);

		int type;
		short id;
		short flags;
	};

	struct IntrusiveMessage : public Message
	{
	public:
		IntrusiveMessage(int newType, short newId) : Message(newType, newId)
		{
		}

		// 0x108476E0 / 0x10847720 (another unit): the reflection data
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
		virtual ~IntrusiveMessage()
		{
		}
	};

	// A message that is not written into the script's event table (RTTI name; layout and members as Message)
	struct NonintrusiveMessage : public Message
	{
	public:
		NonintrusiveMessage(int newType, short newId) : Message(newType, newId)
		{
		}
		virtual ~NonintrusiveMessage()
		{
		}
	};
}

#endif
