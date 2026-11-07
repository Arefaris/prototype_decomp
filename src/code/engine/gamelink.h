// The game link (RTTI: engine::GameLinkManager, engine::GameLinkDebugOutput; the debugging link of the game with its
// tools, unit 0x10853890 - 0x10854060, no assert path; file names and all names that RTTI does not give are guesses).
#ifndef ENGINE_GAMELINK_H
#define ENGINE_GAMELINK_H

#include "code/core/crashrecord.h"
#include "code/core/time.h"
#include "code/engine/netmessage.h"
#include "code/engine/online/replay.h"
#include "code/engine/updatecontext.h"

namespace engine
{
	class GameLinkManager;

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
		// 0x108D5D80: the data the packet holds and its length
		const char* GetData(unsigned int* length);

		int type;  // +0
	};

	// One connection of the net library's session (another unit; names guessed)
	class NetConnection
	{
	public:
		// 0x108C4030: takes the next received message into the buffer: answers its data (null when there is none), its
		// length, a flag and where it came from
		const char* Receive(char* buffer, int capacity, unsigned int* length, unsigned char* flag, int** source);
		// 0x108C40C0
		bool IsReady();
		// 0x108C3F90: sends a message
		void Send(int target, int channel, const char* data, unsigned int length, int unknown);
	};

	// The net library's session (the connections are made and closed through it)
	class NetSession
	{
	public:
		// 0x108C31D0 / 0x108C3670
		NetConnection* Open(int kind, int unknown, int capacity);
		void Close(NetConnection* connection);

		unsigned char unknown0[0x28];
		int unknown28;
	};

	// The net library's global state (0x113187D4; 0x108C4260 answers it)
	struct NetSystem
	{
		unsigned char unknown0[0x20];
		int unknown20;
	};
	// 0x108C4260
	NetSystem* GetNetSystem();

	// The link to the other end of the game link (the net library's, another unit; names guessed)
	class NetLink
	{
	public:
		// 0x108D5B90: sets the link up (the size of its buffers and a tag)
		NetLink(int unknown1, int capacity, int unknown2);
		// 0x108D5BF0
		~NetLink();
		// 0x108D5C30: takes what has come in
		void Poll();
		// 0x108D5900 / 0x108D5910: the lock of the link's packet
		void Lock();
		void Unlock();
		// 0x108D5940
		NetPacket* GetPacket();
		// 0x108D5B40: sends the first bytes of a packet; false when the link is not up or failed
		bool Transmit(NetPacket* packet, unsigned int length);
		// 0x108D58C0: the function that is told about the packets that come in, and its context
		void SetReceiver(void (*receiver)(void*, NetPacket*, GameLinkManager*), GameLinkManager* context);

		unsigned char unknown0[0x190];
	};

	// The game link: its ends exchange Lua commands and text (RTTI: engine::GameLinkManager, base ISimulationTask;
	// the singleton at 0x11315388, names guessed)
	class GameLinkManager : public ISimulationTask
	{
	public:
		// 0x10853F90
		GameLinkManager(int newHeap);
		// 0x10853C30 (the deleting destructor is 0x10853DC0)
		~GameLinkManager();
		// vftable slot 0 (0x10853DE0): takes in what the other end sent
		virtual void UpdateSimulation(UpdateContext context);
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
		// 0x10853C90: runs a Lua command that came in; the answer of the serializer goes back as text
		void ReceiveLua(const char* data, unsigned int length);
		// 0x10853E70: hands a packet that was put together here to the other end, or to the local Lua when there is none
		void Forward(NetPacket* packet);
		// 0x10853F10: what the net library does with a packet that came in (kind 2 goes on to the other end)
		void OnPacket(void* unused, NetPacket* packet);
		// 0x108538C0 / 0x10853910: the Lua function that serializes the answers (a reference to it)
		void BindSerializer();
		void ReleaseSerializer();
		// 0x10853B40 / 0x10853B70: the connection of the other end
		void Connect();
		void Disconnect();

		NetLink* link;  // +4
		int serializer;  // +8
		int heap;  // +0xC
		int pending;  // +0x10
		NetConnection* connection;  // +0x14
		NetSession* session;  // +0x18
		NetMessageAllocatorDynamic allocator;  // +0x1C
	};

	// 0x10853F40: what the net library calls with a packet that came in (the manager is its context)
	void ReceiveCallback(void* unused, NetPacket* packet, GameLinkManager* manager);

	// 0x10853890
	GameLinkManager* GetGameLinkManager();

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
