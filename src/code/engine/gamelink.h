// The game link (RTTI: engine::GameLinkManager, engine::GameLinkDebugOutput; the debugging link of the game with its
// tools, unit 0x10853890 - 0x10854060, no assert path; file names and all names that RTTI does not give are guesses).
#ifndef ENGINE_GAMELINK_H
#define ENGINE_GAMELINK_H

#include "code/core/crashrecord.h"
#include "code/core/time.h"

namespace engine
{
	// The object the game link is reached through (the pump of its services; the singleton at 0x11315388, names guessed)
	class ServicePump
	{
	public:
		virtual void Update(core::Time elapsed) = 0;
		// 0x108539C0: sends a line of text to the other end (a line break is added when it has none)
		void SendText(const char* text);
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
