// The base classes of the net messages' allocators (RTTI names engine::NetMessageSent and engine::NetMessageAllocator;
// both abstract). The unit is the net library's (0x108D5xxx) and the game link's constructors (0x10853810 / 0x10853BA0).
// The slot names are guesses.
#ifndef ENGINE_NETMESSAGE_H
#define ENGINE_NETMESSAGE_H

namespace engine
{
	// What is told about a message that was sent (one pure slot)
	class NetMessageSent
	{
	public:
		// (0x10853810 is the engine's out-of-line copy)
		NetMessageSent()
		{
		}
		virtual void Slot0() = 0;
	};

	// Where the net messages come from (two pure slots)
	class NetMessageAllocator : public NetMessageSent
	{
	public:
		// 0x10853BA0
		NetMessageAllocator();
		virtual void Slot1() = 0;
	};
}

#endif
