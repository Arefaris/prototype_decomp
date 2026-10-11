#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/system/enginememory.h"

namespace core
{
	// 0x108A1D40 (another unit): called when the InputSystem's pending count underflows; meaning unknown
	void Trace(int a, const void* data, int size);
}

namespace engine
{
	// 0x10890910 / 0x108925B0 (other units): run when the InputSystem is destroyed / created
	void ShutdownInputConfig();
	void InitInputConfig();
	// 0x108A1E30 / 0x108A1E40 (another unit): run while the InputSystem is constructed / destroyed
	void InitControllers();
	void ShutdownControllers();

	namespace controller
	{
		// Kept copies of inline functions and compiler-generated members (symbols in symbols.txt):
		// PlayerInfo::GetNext, HasFlags, SetFlags, ClearFlags, ResetFlags, IsActive, GetFlags, GetInput, SetInput,
		// SetContext, SetSlot, SetId; PlayerInfoFactoryInterface's constructor; the scalar deleting destructors of
		// PhysicalControllerManager, PlayerInfoFactory and InputSystem; PlayerInfo's vector deleting destructor
		// FUNCTION: ENGINE 0x107DF3B0
		// FUNCTION: ENGINE 0x107DF3D0
		// FUNCTION: ENGINE 0x107DF3F0
		// FUNCTION: ENGINE 0x107DF400
		// FUNCTION: ENGINE 0x107DF410
		// FUNCTION: ENGINE 0x107DF420
		// FUNCTION: ENGINE 0x107DF440
		// FUNCTION: ENGINE 0x107DF480
		// FUNCTION: ENGINE 0x107DF490
		// FUNCTION: ENGINE 0x107DF4A0
		// FUNCTION: ENGINE 0x107DF4B0
		// FUNCTION: ENGINE 0x107DF4C0
		// FUNCTION: ENGINE 0x107DF3C0
		// FUNCTION: ENGINE 0x107DF5E0
		// FUNCTION: ENGINE 0x107DFAA0
		// FUNCTION: ENGINE 0x107E0080
		// FUNCTION: ENGINE 0x107DFCB0

		// GLOBAL: ENGINE 0x11283290
		InputSystem* InputSystem::sInstance;

		// FUNCTION: ENGINE 0x107DF4E0
		InputSystem::Config::Config()
		{
			playerCount = 8;
			controllerCount = 8;
			unknown8 = 0;
			heap = 7;
			defaultContext = 3;
			deadZone = 0.3f;
			flag18 = true;
			helperA = 0;
			helperB = 0;
			flag24 = false;
			unknown28 = 0;
			unknown2C = 4;
			name = "hud";
		}

		// FUNCTION: ENGINE 0x107DF540
		void InputSystem::Destroy()
		{
			if (sInstance != 0)
			{
				ShutdownInputConfig();
				delete sInstance;
				sInstance = 0;
			}
		}

		// FUNCTION: ENGINE 0x107DF650
		void InputSystem::SetPlayerFlags(unsigned int id, unsigned int flags)
		{
			PlayerInfo* info = GetPlayer(id);
			if (!info->HasFlags(flags))
			{
				OnFlags(id, flags, true, 1);
				if (info->GetFlags() & 2)
				{
					manager->SetFlags(id, info->GetFlags(), true);
				}
			}
		}

		// FUNCTION: ENGINE 0x107DF6A0
		void InputSystem::ClearPlayerFlags(unsigned int id, unsigned int flags)
		{
			PlayerInfo* info = GetPlayer(id);
			if (info->HasFlags(flags))
			{
				OnFlags(id, flags, false, 1);
				if (flags == 2)
				{
					manager->SetFlags(id, info->GetFlags() | flags, false);
				}
				else if (info->GetFlags() & 2)
				{
					manager->SetFlags(id, flags, false);
				}
			}
		}

		// FUNCTION: ENGINE 0x107DF710
		// EQUIVALENT: the context count is addressed [index + base] instead of [base + index]
		void InputSystem::PushContext(unsigned int id, int context)
		{
			if (IsLocal(id))
			{
				unsigned char index = (unsigned char)id;
				contexts[index].items[contexts[index].count] = context;
				contexts[index].count++;
				players[index].context = context;
			}
		}

		// FUNCTION: ENGINE 0x107DF770
		// EQUIVALENT: the context count is addressed [index + base] instead of [base + index]
		void InputSystem::PopContext(unsigned int id)
		{
			if (IsLocal(id))
			{
				unsigned char index = (unsigned char)id;
				contexts[index].count--;
				players[index].context = contexts[index].items[contexts[index].count - 1];
			}
		}

		// FUNCTION: ENGINE 0x107DF7D0
		int InputSystem::GetContext(unsigned int id)
		{
			if (IsLocal(id))
			{
				unsigned char index = (unsigned char)id;
				return contexts[index].items[contexts[index].count - 1];
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x107DF810
		void InputSystem::ClearRemotePlayers()
		{
			for (int i = 0; i < playerCount; i++)
			{
				players[controllerCount + i].Clear();
			}
		}

		// FUNCTION: ENGINE 0x107DF840
		void InputSystem::ClearControllers()
		{
			for (int i = 0; i < controllerCount; i++)
			{
				players[i].Clear();
			}
		}

		// FUNCTION: ENGINE 0x107DF870
		void InputSystem::SetFactory(PlayerInfoFactoryInterface* newFactory)
		{
			char name[32];
			int i;
			int total = playerCount + controllerCount;
			if (factory != 0)
			{
				for (i = 0; i < total; i++)
				{
					factory->Destroy(players[i].GetInput());
					// Always the first player's pointer (the engine's own slip)
					players->SetInput(0);
				}
				delete factory;
				factory = 0;
			}
			factory = newFactory;
			if (newFactory != 0)
			{
				for (i = 0; i < total; i++)
				{
					players[i].SetInput(factory->Create());
				}
				for (i = 0; i < controllerCount; i++)
				{
					core::SNPrintf(name, 32, "Controller%d", i);
					players[i].GetInput()->SetName(name);
				}
			}
		}

		// FUNCTION: ENGINE 0x107DF960
		// EQUIVALENT: the tail call takes the slot through edx instead of eax
		void InputSystem::Update()
		{
			pending++;
			manager->Refresh();
		}

		// FUNCTION: ENGINE 0x107DF970
		void InputSystem::OnRelease(unsigned int id, int value)
		{
			if (IsLocal(id) && --pending < 0)
			{
				core::Trace(0, &value, 4);
			}
			ReleaseSlot(id, value);
		}

		// FUNCTION: ENGINE 0x107DF9B0
		void InputSystem::Reset()
		{
			ResetSlots();
			for (int i = 0; i < playerCount; i++)
			{
				players[controllerCount + i].Clear();
			}
		}

		// FUNCTION: ENGINE 0x107DFAD0
		// EQUIVALENT: in the last loop the engine keeps i in ecx and stores contexts after the first compare
		InputSystem::InputSystem(const Config& config)
			: SlotManager(config.playerCount), playerCount(config.playerCount),
			controllerCount(config.controllerCount), pending(0), override(0), factory(0)
		{
			core::HeapScope scope(config.heap);
			sInstance = this;
			this->config = config;
			if (this->config.helperA == 0)
			{
				this->config.helperA = new InputHelperA;
			}
			if (this->config.helperB == 0)
			{
				this->config.helperB = new InputHelperB;
			}
			players = new PlayerInfo[playerCount + controllerCount];
			physical = new PhysicalControllerManager(controllerCount);
			InitControllers();
			Reset();
			manager = physical;
			manager->callback = this;
			contexts = new ContextStack[controllerCount];
			for (int i = 0; i < controllerCount; i++)
			{
				players[i].SetId(LocalId(i));
				contexts[i].count = 1;
				contexts[i].items[0] = this->config.defaultContext;
				players[i].SetContext(this->config.defaultContext);
			}
			SetFactory(new PlayerInfoFactory);
		}

		// FUNCTION: ENGINE 0x107DFD20
		InputSystem::~InputSystem()
		{
			delete[] contexts;
			SetFactory(0);
			if (override != 0)
			{
				delete override;
			}
			ShutdownControllers();
			delete physical;
			delete[] players;
			delete config.helperA;
			delete config.helperB;
		}

		// FUNCTION: ENGINE 0x107DFDD0
		PlayerInfo* InputSystem::FindPlayer(unsigned int id, container::SListBase* list)
		{
			PlayerInfo* info = (PlayerInfo*)list->head;
			while (info != 0 && info->id != id)
			{
				info = info->GetNext();
			}
			return info;
		}

		// FUNCTION: ENGINE 0x107DFDF0
		void InputSystem::CollectPlayers()
		{
			manager->Collect(&connected);
			for (PlayerInfo* info = (PlayerInfo*)connected.head; info != 0; info = info->GetNext())
			{
				info->Update();
			}
		}

		// SetVibration is inline in the header; this is its kept copy
		// FUNCTION: ENGINE 0x107DF600
		// FUNCTION: ENGINE 0x107DFE20
		// EQUIVALENT: register choice: the engine keeps the list address in edi
		void InputSystem::UpdatePlayers(int a, int b, float time)
		{
			GetUpdater()->Update(time);
			manager->CollectActive(&active, time);
			for (PlayerInfo* info = (PlayerInfo*)active.head; info != 0; info = info->GetNext())
			{
				info->Update();
			}
		}

		// FUNCTION: ENGINE 0x107DFE70
		// EQUIVALENT: the second SetVibration call loads the id into ecx and the manager later
		void InputSystem::StopVibration()
		{
			for (PlayerInfo* info = (PlayerInfo*)active.head; info != 0; info = info->GetNext())
			{
				SetVibration(info->id, 0, 0.0f, 0.0f, 0.0f, 0.0f);
				SetVibration(info->id, 1, 0.0f, 0.0f, 0.0f, 0.0f);
			}
		}

		// FUNCTION: ENGINE 0x107DFED0
		void InputSystem::SetValue(unsigned int id, int value)
		{
			PlayerInfo* info = GetPlayer(id);
			info->input->SetValue(value);
			for (InputCallback* callback = callbacks.First(); callback != 0; callback = callbacks.Next(callback))
			{
				callback->OnValue(id, 1, info->input);
			}
			manager->SetValue(id, value);
		}

		// FUNCTION: ENGINE 0x107DFF50
		void InputSystem::Notify(int a, int b)
		{
			for (InputCallback* callback = callbacks.First(); callback != 0; callback = callbacks.Next(callback))
			{
				callback->OnNotify(a, 0, b);
			}
		}

		// FUNCTION: ENGINE 0x107DFF90
		void InputSystem::NotifyFlags(unsigned int id, int local, unsigned int flags, bool set)
		{
			for (InputCallback* callback = callbacks.First(); callback != 0; callback = callbacks.Next(callback))
			{
				callback->OnFlags(id, local, flags, set);
			}
		}

		// FUNCTION: ENGINE 0x107E0030
		void InputSystem::Create(const Config& config)
		{
			if (sInstance == 0)
			{
				sInstance = new (config.heap) InputSystem(config);
				InitInputConfig();
			}
		}

		// FUNCTION: ENGINE 0x107E00A0
		void InputSystem::UpdateLocal(unsigned int id, unsigned int flags, bool set)
		{
			PlayerInfo* info = GetPlayer(id);
			if (set)
			{
				info->SetFlags(flags);
			}
			else
			{
				info->ClearFlags(flags);
			}
			if (info->IsActive())
			{
				if (!active.Contains(info))
				{
					info->Clear();
					active.PushBack(info);
				}
			}
			else if (active.Contains(info))
			{
				active.Remove(info);
			}
			NotifyFlags(id, 1, flags, set);
		}

		// FUNCTION: ENGINE 0x107E0140
		// EQUIVALENT: the engine inlines finder / remover helpers our compiler declines to inline; the expanded loops differ in load order
		void InputSystem::UpdateRemote(unsigned int id, unsigned int flags, bool set)
		{
			PlayerInfo* info = 0;
			int i;
			for (i = controllerCount; i < playerCount + controllerCount; i++)
			{
				if (players[i].id == id)
				{
					info = &players[i];
					break;
				}
			}
			if (info == 0)
			{
				if (!(flags & 2) || !set)
				{
					return;
				}
				for (i = controllerCount; i < playerCount + controllerCount; i++)
				{
					if (players[i].id == 0xffffffff)
					{
						players[i].id = id;
						info = &players[i];
						players[i].ResetFlags();
						break;
					}
				}
				if (info == 0 && IsLocal(id))
				{
					GetPlayer(id)->ClearFlags(2);
				}
			}
			if (set)
			{
				info->SetFlags(flags);
			}
			else
			{
				info->ClearFlags(flags);
			}
			PlayerInfo* item;
			if (!(info->GetFlags() & 2))
			{
				for (item = (PlayerInfo*)connected.head; item != 0; item = item->GetNext())
				{
					if (item == info)
					{
						connected.Remove(info);
						info->input->Reset();
						info->id = 0xffffffff;
						int slot = FindSlot(id);
						if (slot >= 0)
						{
							AssignSlot(slot, id);
						}
						break;
					}
				}
				info->id = 0xffffffff;
			}
			else if (!info->IsActive())
			{
				for (item = (PlayerInfo*)connected.head; item != 0; item = item->GetNext())
				{
					if (item == info)
					{
						connected.Remove(info);
						info->input->Reset();
						info->id = 0xffffffff;
						int slot = FindSlot(id);
						if (slot >= 0)
						{
							AssignSlot(slot, id);
						}
						break;
					}
				}
			}
			else
			{
				for (item = (PlayerInfo*)connected.head; item != 0; item = item->GetNext())
				{
					if (item == info)
					{
						break;
					}
				}
				if (item == 0)
				{
					info->Clear();
					connected.PushBack(info);
					info->input->Reset();
					int slot = FindSlot(id);
					if (slot >= 0)
					{
						AssignSlot(slot, id);
					}
					if (IsLocal(id))
					{
						manager->SetValue(id, (int)GetPlayer(id)->input);
					}
				}
			}
			NotifyFlags(id, 0, flags, set);
		}

		// FUNCTION: ENGINE 0x107E0390
		void InputSystem::OnValue(unsigned int id, int value)
		{
			PlayerInfo* info = FindConnected(id);
			if (info != 0)
			{
				info->input->SetValue(value);
				for (InputCallback* callback = callbacks.First(); callback != 0; callback = callbacks.Next(callback))
				{
					callback->OnValue(id, 0, info->input);
				}
			}
		}

		// FUNCTION: ENGINE 0x107E0400
		void InputSystem::AssignSlot(int index, unsigned int id)
		{
			if (slots[index].id != 0xffffffff)
			{
				PlayerInfo* info = slots[index].info;
				if (info != 0)
				{
					info->SetSlot(-1);
				}
				unsigned int oldId = slots[index].id;
				if (IsLocal(oldId))
				{
					GetPlayer(oldId)->SetSlot(-1);
				}
			}
			slots[index].id = id;
			slots[index].info = 0;
			if (id != 0xffffffff)
			{
				slots[index].info = FindPlayer(id, &connected);
				if (slots[index].info != 0)
				{
					slots[index].info->SetSlot(index);
				}
				if (IsLocal(id))
				{
					GetPlayer(id)->SetSlot(index);
				}
			}
		}

		// FUNCTION: ENGINE 0x107E04C0
		void InputSystem::ResetAll()
		{
			if (manager != 0)
			{
				for (int i = 0; i < controllerCount; i++)
				{
					UpdateLocal(LocalId(i), 2, false);
					UpdateRemote(LocalId(i), players[i].GetFlags() | 2, false);
				}
				Reset();
				pending = 0;
			}
		}

		// FUNCTION: ENGINE 0x107E0520
		// EQUIVALENT: the engine reloads manager before storing the callback
		void InputSystem::SetManager(ControllerManagerInterface* newManager, bool reset)
		{
			if (reset)
			{
				ResetAll();
			}
			manager = newManager != 0 ? newManager : physical;
			manager->callback = this;
		}

		// FUNCTION: ENGINE 0x107E0550
		void InputSystem::OnFlags(unsigned int id, unsigned int flags, bool set, int which)
		{
			if (which == 2 || which == 1)
			{
				UpdateLocal(id, flags, set);
			}
			if (which == 2 || which == 0)
			{
				UpdateRemote(id, flags, set);
			}
		}
	}
}
