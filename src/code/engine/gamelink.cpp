#include "code/core/strings.h"
#include "code/core/report.h"
#include "code/engine/gamelink.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/system/enginememory.h"
#include "code/lua/lua.h"

namespace engine
{
	// The pump (0x11315388; made by the game link's start-up)
	extern GameLinkManager* gGameLinkManager;

	// FUNCTION: ENGINE 0x10853890
	GameLinkManager* GetGameLinkManager()
	{
		return gGameLinkManager;
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
		GameLinkManager* pump = GetGameLinkManager();
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
	void GameLinkManager::Send(NetPacket* packet, unsigned int length)
	{
		if (length > 0)
		{
			link->Transmit(packet, length);
		}
	}

	// FUNCTION: ENGINE 0x10853950
	void GameLinkManager::SendPacketText(NetPacket* packet, const char* text)
	{
		packet->type = 3;
		unsigned int length = packet->Write(0x2000, text, -1);
		packet->Finish();
		Send(packet, length);
	}

	// FUNCTION: ENGINE 0x10853990
	void GameLinkManager::SendMessage(const char* text)
	{
		link->Lock();
		NetPacket* packet = link->GetPacket();
		SendPacketText(packet, text);
		link->Unlock();
	}

	// FUNCTION: ENGINE 0x108539C0
	void GameLinkManager::SendText(const char* text)
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
	void GameLinkManager::SendLongText(const char* text)
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

namespace engine
{
	// The debug output handler of the link (0x111C7EE0; its chain pointer is the word behind the vftable) and the
	// Lua script that defines the serializer (0x111C7E94; names guessed)
	extern GameLinkDebugOutput gGameLinkDebugOutput;
	extern const char* gGameLinkScript;
	extern GameLinkManager* gGameLinkManager;
	// The online manager (the global at 0x11318530; the session is the pointer at +0x70)
	struct OnlineManagerView
	{
		unsigned char unknown0[0x70];
		NetSession* session;
	};
	extern OnlineManagerView* gOnlineManager;
	// 0x10899F60, 0x10838900, 0x10837AB0: other units'
	void Unknown10899F60();
	void AddSimulationTask(IRealTimeTask* task, unsigned int mask, int priority, unsigned int data);
	void RemoveSimulationTask(IRealTimeTask* task);
	int ProtectedCall(lua_State* L, int argumentCount, int resultCount);

	// FUNCTION: ENGINE 0x108538C0
	void GameLinkManager::BindSerializer()
	{
		GetScriptManager()->DoBuffer(gGameLinkScript, 0, -1);
		LuaScriptManager* manager = GetScriptManager();
		lua_getfield(manager->state, LUA_GLOBALSINDEX, "GameLinkSerialize");
		serializer = manager->MakeReference();
	}

	// FUNCTION: ENGINE 0x10853910
	void GameLinkManager::ReleaseSerializer()
	{
		LuaScriptManager* manager = GetScriptManager();
		int reference = serializer;
		manager->ReleaseReference(reference);
		serializer = 0;
	}

	// FUNCTION: ENGINE 0x10853B40
	void GameLinkManager::Connect()
	{
		if (connection == 0)
		{
			session = gOnlineManager->session;
			connection = session->Open(6, -1, 0x2000);
		}
	}

	// FUNCTION: ENGINE 0x10853B70
	void GameLinkManager::Disconnect()
	{
		if (connection != 0)
		{
			session->Close(connection);
			connection = 0;
			session = 0;
		}
	}

	// FUNCTION: ENGINE 0x10853C30
	GameLinkManager::~GameLinkManager()
	{
		core::SetOutputHandler(gGameLinkDebugOutput.next, 0);
		gGameLinkDebugOutput.next = 0;
		RemoveSimulationTask((IRealTimeTask*)this);
		if (link != 0)
		{
			delete link;
		}
		ReleaseSerializer();
		Disconnect();
	}

	// FUNCTION: ENGINE 0x10853F10
	void GameLinkManager::OnPacket(void* unused, NetPacket* packet)
	{
		switch (packet->type)
		{
		case 2:
			packet->Finish();
			Forward(packet);
			break;
		}
	}

	// FUNCTION: ENGINE 0x10853F40
	void ReceiveCallback(void* unused, NetPacket* packet, GameLinkManager* manager)
	{
		manager->OnPacket(unused, packet);
	}

	// FUNCTION: ENGINE 0x10853E70
	void GameLinkManager::Forward(NetPacket* packet)
	{
		NetPacket* original = packet;
		unsigned int length;
		const char* data = packet->GetData(&length);
		if (connection != 0)
		{
			if (!connection->IsReady())
			{
				original->type = 0;
				unsigned int sent = original->Write(0x2000, "Can't send data to peer", -1);
				original->Finish();
				Send(original, sent);
				return;
			}
			int target = GetNetSystem()->unknown20;
			connection->Send(target, 0xFF, data, length, 1);
			pending++;
			return;
		}
		Unknown10899F60();
		ReceiveLua(data, length);
	}

	// FUNCTION: ENGINE 0x10853C90
	void GameLinkManager::ReceiveLua(const char* data, unsigned int length)
	{
		LuaScriptManager* manager = GetScriptManager();
		lua_State* L = manager->currentState;
		int top = lua_gettop(L);
		if (luaL_loadbuffer(L, data, length, "=ReceiveLuaCommandPacket") != 0)
		{
			SendMessage(lua_tolstring(L, -1, 0));
			lua_settop(L, top);
			return;
		}
		bool saved = manager->GetUnknownB4();
		manager->SetUnknownB4(false);
		int error = ProtectedCall(L, 0, -1);
		manager->SetUnknownB4(saved);
		if (error != 0)
		{
			SendMessage(lua_tolstring(L, -1, 0));
			lua_settop(L, top);
			return;
		}
		int results = lua_gettop(L) - top;
		lua_rawgeti(L, LUA_REGISTRYINDEX, serializer);
		const char* text = "";
		if (lua_type(L, -1) == LUA_TFUNCTION)
		{
			lua_insert(L, top + 1);
			if (ProtectedCall(L, results, 1) == 0)
			{
				text = lua_tolstring(L, -1, 0);
			}
		}
		SendLongText(text);
		lua_settop(L, top);
		lua_gc(L, LUA_GCCOLLECT, 0);
	}

	// FUNCTION: ENGINE 0x10853DE0
	void GameLinkManager::UpdateSimulation(UpdateContext context)
	{
		char buffer[0x2000];
		unsigned int length;
		unsigned char flag;
		int* source;
		link->Poll();
		if (connection != 0)
		{
			const char* data;
			while ((data = connection->Receive(buffer, 0x2000, &length, &flag, &source)) != 0)
			{
				if (source == &session->unknown28)
				{
					pending--;
				}
				ReceiveLua(data, length);
			}
		}
	}

	// FUNCTION: ENGINE 0x10853F90
	// NONMATCHING: the engine keeps the constant 0x70000 in ebx (37.8 %)
#ifdef NONMATCHING
	GameLinkManager::GameLinkManager(int newHeap) :
		link(0),
		serializer(0),
		heap(newHeap),
		pending(0),
		connection(0),
		session(0)
	{
		link = new (newHeap) NetLink(0x70000, 0x2000, 0x6F);
		link->SetReceiver(ReceiveCallback, this);
		AddSimulationTask((IRealTimeTask*)this, 2, 1, (unsigned int)"GameLink Simtime Task");
		BindSerializer();
		core::SetOutputHandler(&gGameLinkDebugOutput, &gGameLinkDebugOutput.next);
	}
#endif

	// FUNCTION: ENGINE 0x10854030
	void CreateGameLinkManager(int heap)
	{
		gGameLinkManager = new (heap) GameLinkManager(heap);
	}

	// FUNCTION: ENGINE 0x10853F60
	void DestroyGameLinkManager()
	{
		delete gGameLinkManager;
		gGameLinkManager = 0;
	}
}
