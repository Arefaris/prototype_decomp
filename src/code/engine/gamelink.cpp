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

namespace engine
{
	// FUNCTION: ENGINE 0x10853930
	void ServicePump::Send(NetPacket* packet, unsigned int length)
	{
		if (length > 0)
		{
			link->Transmit(packet, length);
		}
	}

	// FUNCTION: ENGINE 0x10853950
	void ServicePump::SendPacketText(NetPacket* packet, const char* text)
	{
		packet->type = 3;
		unsigned int length = packet->Write(0x2000, text, -1);
		packet->Finish();
		Send(packet, length);
	}

	// FUNCTION: ENGINE 0x10853990
	void ServicePump::SendMessage(const char* text)
	{
		link->Lock();
		NetPacket* packet = link->GetPacket();
		SendPacketText(packet, text);
		link->Unlock();
	}

	// FUNCTION: ENGINE 0x108539C0
	void ServicePump::SendText(const char* text)
	{
		link->Lock();
		NetPacket* packet = link->GetPacket();
		packet->type = 5;
		unsigned int length = core::StrLen(text);
		if (length > 0)
		{
			unsigned int sent = packet->Write(0x2000, text, length);
			if (text[length - 1] != '\n')
			{
				sent = packet->Append(0x2000, "\n", 1);
			}
			packet->Finish();
			Send(packet, sent);
		}
		link->Unlock();
	}

	// FUNCTION: ENGINE 0x10853A50
	void ServicePump::SendLongText(const char* text)
	{
		link->Lock();
		NetPacket* packet = link->GetPacket();
		const char* cursor = text;
		unsigned int length = core::StrLen(cursor);
		while (length > 0x1FF7)
		{
			packet->type = 1;
			unsigned int sent = packet->Write(0x2000, cursor, 0x1FF7);
			cursor += 0x1FF7;
			length -= 0x1FF7;
			packet->Finish();
			Send(packet, sent);
		}
		packet->type = 0;
		unsigned int sent = packet->Write(0x2000, cursor, length);
		packet->Finish();
		Send(packet, sent);
		link->Unlock();
	}
}
