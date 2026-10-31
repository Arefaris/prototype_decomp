#include "code/core/strings.h"
#include "code/engine/gamelink.h"

namespace engine
{
	// The pump (0x11315388; made by the game link's start-up)
	extern ServicePump* gServicePump;

	// FUNCTION: ENGINE 0x10853890
	ServicePump* GetServicePump()
	{
		return gServicePump;
	}

	// FUNCTION: ENGINE 0x10853BB0
	GameLinkDebugOutput::GameLinkDebugOutput()
	{
	}

	// FUNCTION: ENGINE 0x10853BE0
	void GameLinkDebugOutput::OnOutput(core::DebugMessage* message)
	{
		if (next != 0)
		{
			next->OnOutput(message);
		}
		ServicePump* pump = GetServicePump();
		if (pump != 0)
		{
			const char* text = message->text;
			if ((message->flags & 8) == 0)
			{
				const char* bracket = core::StrChr(text, '[');
				if (bracket != 0)
				{
					text = bracket;
				}
			}
			pump->SendText(text);
		}
	}
}
