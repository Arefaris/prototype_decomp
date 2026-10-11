// engine::Message and engine::IntrusiveMessage (names from the RTTI). Layout from the message constructors: vftable,
// a message type (12 for the camera messages, 14 for PlayerControlChangedMessage, whose object is 0x14 bytes, so
// this is not the size), a 16-bit id and 16 bits of flags. The constructor parameters and the member names are
// guesses; the base constructor is inline (the derived constructors store the fields themselves and write only the
// final vftable).
#ifndef ENGINE_MESSAGE_H
#define ENGINE_MESSAGE_H

namespace engine
{
	class Message
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

		int type;
		short id;
		short flags;
	};

	class IntrusiveMessage : public Message
	{
	public:
		IntrusiveMessage(int newType, short newId) : Message(newType, newId)
		{
		}
		virtual ~IntrusiveMessage()
		{
		}
	};
}

#endif
