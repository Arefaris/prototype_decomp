// engine::Message and engine::IntrusiveMessage (names from the RTTI). Layout from the camera message constructors:
// vftable, a length (the size of the whole message object), a 16-bit id and 16 bits of flags. The constructor
// parameters and the member names are guesses; the base constructor is inline (the derived constructors store the
// fields themselves and write only the final vftable).
#ifndef ENGINE_MESSAGE_H
#define ENGINE_MESSAGE_H

namespace engine
{
	class Message
	{
	public:
		Message(int newLength, short newId)
		{
			length = newLength;
			id = newId;
			flags = 0;
		}
		virtual ~Message()
		{
		}

		int length;
		short id;
		short flags;
	};

	class IntrusiveMessage : public Message
	{
	public:
		IntrusiveMessage(int newLength, short newId) : Message(newLength, newId)
		{
		}
		virtual ~IntrusiveMessage()
		{
		}
	};
}

#endif
