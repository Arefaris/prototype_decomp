// The game link (RTTI: engine::GameLinkManager, engine::GameLinkDebugOutput; the debugging link of the game with its
// tools, unit 0x10853890 - 0x10854060, no assert path; file names and all names that RTTI does not give are guesses).
#ifndef ENGINE_GAMELINK_H
#define ENGINE_GAMELINK_H

#include "code/core/crashrecord.h"
#include "code/core/time.h"

namespace engine
{
	// A message being put together for the other end (the net library's, another unit; names guessed)
	class NetPacket
	{
	public:
		// 0x108D5CB0 / 0x108D5D20: puts text of the given length into the packet (a negative length means the whole
		// string); answers how much it holds
		unsigned int Write(int capacity, const char* text, int length);
		unsigned int Append(int capacity, const char* text, int length);
		// 0x108D5C60 (called through its thunk 0x108D5C70): finishes the packet
		void Finish();

		int type;  // +0
	};

	// The connection of the game link (the net library's, another unit; names guessed)
	class NetLink
	{
	public:
		// 0x108D5900 / 0x108D5910: the lock of the link's packet
		void Lock();
		void Unlock();
		// 0x108D5940
		NetPacket* GetPacket();
		// 0x108D5B40: sends the first bytes of a packet; false when the link is not up or failed
		bool Transmit(NetPacket* packet, unsigned int length);
	};

	// The object the game link is reached through (the pump of its services; the singleton at 0x11315388, names guessed)
	class ServicePump
	{
	public:
		virtual void Update(core::Time elapsed) = 0;
		// 0x108539C0: sends a line of text to the other end (a line break is added when it has none)
		void SendText(const char* text);
		// 0x10853990: sends a text as one message of kind 3
		void SendMessage(const char* text);
		// 0x10853A50: sends a long text in pieces
		void SendLongText(const char* text);
		// 0x10853930 (the engine's unit-local helper): hands a finished packet to the link
		void Send(NetPacket* packet, unsigned int length);
		// 0x10853950: puts the text into the packet as a message of kind 3 and sends it
		void SendPacketText(NetPacket* packet, const char* text);

		NetLink* link;  // +4
	};

	// 0x10853890
	ServicePump* GetServicePump();

	// The debug output handler that also sends the text over the link (RTTI: bases core::DebugOutputHandlerBase and
	// core::IDebugOutputHandler)
	class GameLinkDebugOutput : public core::DebugOutputHandlerBase
	{
	public:
		// 0x10853BB0 (the deleting destructor in slot 1 is 0x10853BC0)
		GameLinkDebugOutput();
		// vftable slot 0 (0x10853BE0): hands the message to the next handler and sends its text
		virtual void OnOutput(core::DebugMessage* message);
	};
}

#endif
