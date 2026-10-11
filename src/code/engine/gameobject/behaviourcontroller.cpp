#include "code/core/heap.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/message.h"
#include <string.h>
#include <typeinfo>

namespace core
{
	bool GetThreadValue(int slot, int* value);
	bool SetThreadValue(int slot, int value);
}

namespace engine
{
	// The thread-local slot of the behaviour being constructed and the time slice round-robin counter
	// (gameobjectsystem.cpp)
	extern int gThreadSlotC;
	extern unsigned char gTimeSliceCounter;

	// Per message type, the indices of the behaviours listening (0xFF ends the list, 0xFE: none worked out, scan the
	// masks); shared between controllers with the same masks and reference counted (names guessed)
	class DispatchTable
	{
	public:
		void AddRef()
		{
			refCount++;
		}
		void Release();

		signed char entries[63][8];
		int refCount;
	};

	// The pool of dispatch tables (0x11317848; InitVTablePool creates it)
	class VTablePool
	{
	public:
		// 0x10898120 / 0x10898240
		DispatchTable* Find(const BehaviourController::MessageMask* masks, int count);
		void Free(DispatchTable* table);
	};
	extern VTablePool* gVTablePool;

	inline void DispatchTable::Release()
	{
		refCount--;
		if (refCount <= 0)
		{
			gVTablePool->Free(this);
		}
	}

	// FUNCTION: ENGINE 0x10839420
	void SetDispatchTable(DispatchTable*& slot, DispatchTable* table)
	{
		if (table != 0)
		{
			table->AddRef();
		}
		if (slot != 0)
		{
			slot->Release();
		}
		slot = table;
	}

	// The behaviour being constructed (it creates its schedule before its controller knows it)
	// FUNCTION: ENGINE 0x10839380
	Behaviour* GetConstructingBehaviour()
	{
		int behaviour;
		core::GetThreadValue(gThreadSlotC, &behaviour);
		return (Behaviour*)behaviour;
	}

	// FUNCTION: ENGINE 0x108393A0
	void SetConstructingBehaviour(Behaviour* behaviour)
	{
		core::SetThreadValue(gThreadSlotC, (int)behaviour);
	}

	// FUNCTION: ENGINE 0x10839340
	content::ClassInfo* BehaviourController::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "BehaviourController";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108394D0
	void BehaviourController::Slot1()
	{
		GetHandle(owner).SetFlags(updateMask);
		dirty = true;
		for (Behaviour** item = behaviours.begin; item < behaviours.end; item++)
		{
			(*item)->Slot1();
		}
		SetDispatchTable(dispatch, gVTablePool->Find(messageMasks, behaviours.Size()));
	}

	// FUNCTION: ENGINE 0x10839540
	bool BehaviourController::Slot2()
	{
		bool done = true;
		for (Behaviour** item = behaviours.begin; item < behaviours.end; item++)
		{
			done = (*item)->Slot2() && done;
		}
		if (dispatch != 0)
		{
			dispatch->Release();
			dispatch = 0;
		}
		return done;
	}

	// FUNCTION: ENGINE 0x108395A0
	int BehaviourController::IndexOf(Behaviour* behaviour)
	{
		Behaviour** item = behaviours.begin;
		for (; item != behaviours.end; item++)
		{
			if (*item == behaviour)
			{
				return item - behaviours.begin;
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x108395D0
	// EQUIVALENT: the engine works out the cleared passes with 16-bit operations on zero-extended registers; ours
	// extends both operands first
	void BehaviourController::UpdatePasses(unsigned short mask, bool add)
	{
		if (add)
		{
			updateMask |= mask;
			if (owner->IsRegistered())
			{
				GameObjectHandle handle = GetHandle(owner);
				handle.SetFlags(mask);
			}
		}
		else
		{
			unsigned short previous = updateMask;
			updateMask = 0;
			int count = behaviours.Size();
			for (int i = 0; i < count; i++)
			{
				updateMask |= schedule[i].GetPasses();
			}
			if (updateMask != previous && owner->IsRegistered())
			{
				GameObjectHandle handle = GetHandle(owner);
				handle.ClearFlags((unsigned short)(~updateMask & previous));
			}
		}
		dirty = true;
	}

	// FUNCTION: ENGINE 0x10839690
	bool BehaviourController::Query2(int mask, Behaviour* behaviour)
	{
		int index = IndexOf(behaviour);
		if (index < 0)
		{
			if (GetConstructingBehaviour() != 0)
			{
				return schedule[scheduleCount - 1].TestPasses(mask);
			}
			return false;
		}
		return schedule[index].TestPasses(mask);
	}

	// FUNCTION: ENGINE 0x108396F0
	bool BehaviourController::Query3(Behaviour* behaviour)
	{
		int index = IndexOf(behaviour);
		if (index < 0)
		{
			if (GetConstructingBehaviour() != 0)
			{
				return schedule[scheduleCount - 1].GetPasses() != 0;
			}
			return false;
		}
		return schedule[index].GetPasses() != 0;
	}

	// FUNCTION: ENGINE 0x10839750
	void BehaviourController::UpdateListening(int messageType, bool listen)
	{
		if (listen)
		{
			listenMask |= GetMessageBit(messageType);
		}
		else
		{
			listenMask = 0;
			int count = behaviours.Size();
			for (int i = 0; i < count; i++)
			{
				listenMask |= messageMasks[i].bits;
			}
		}
		if (dispatch != 0)
		{
			SetDispatchTable(dispatch, gVTablePool->Find(messageMasks, behaviours.Size()));
		}
	}

	// FUNCTION: ENGINE 0x108397E0
	bool BehaviourController::Query4(int messageType, Behaviour* behaviour)
	{
		unsigned __int64 bit = GetMessageBit(messageType);
		int index = IndexOf(behaviour);
		if (index < 0)
		{
			if (GetConstructingBehaviour() != 0)
			{
				return (messageMasks[scheduleCount - 1].bits & bit) != 0;
			}
			return false;
		}
		return (messageMasks[index].bits & bit) != 0;
	}

	// FUNCTION: ENGINE 0x10839860
	unsigned char BehaviourController::GetFrameSkip(Behaviour* behaviour)
	{
		int index = IndexOf(behaviour);
		if (index < 0)
		{
			if (GetConstructingBehaviour() != 0)
			{
				return schedule[scheduleCount - 1].frameSkip;
			}
			return 1;
		}
		return schedule[index].frameSkip;
	}

	// FUNCTION: ENGINE 0x108398A0
	// EQUIVALENT: register allocation (the engine keeps the schedule offset in edi and the entry in ebx, ours the other
	// way round) and the order of two local stores
	void BehaviourController::UpdateBehaviours(float dt, unsigned short mask)
	{
		dt = updateTimeScalar * dt;
		unsigned int frame = GetGameObjectFrame();
		bool fullPass = mask == 4;
		if (dirty && fullPass)
		{
			dirty = false;
			int count = behaviours.Size();
			unsigned short passes = 0;
			for (int i = 0; i < count; i++)
			{
				if (schedule[i].IsUpdated())
				{
					schedule[i].time = 0.0f;
					schedule[i].SetUpdated(false);
				}
				schedule[i].SetScheduled(false);
				ScheduleEntry& entry = schedule[i];
				if (entry.IsActive())
				{
					if (entry.frameSkip == 1 || frame % entry.frameSkip == entry.phase)
					{
						if (entry.TestPasses(mask))
						{
							behaviours.begin[i]->Update(entry.time + dt, mask);
						}
						schedule[i].SetUpdated(true);
					}
					else
					{
						entry.time += dt;
					}
					if (schedule[i].GetPasses() != 0)
					{
						schedule[i].SetScheduled(true);
						passes |= schedule[i].GetPasses();
					}
				}
			}
			GameObjectHandle handle = GetHandle(owner);
			handle.SetFlags(passes);
			handle.ClearFlags((unsigned short)(updateMask & ~passes));
			return;
		}
		int count = behaviours.Size();
		for (int i = 0; i < count; i++)
		{
			if (fullPass && schedule[i].IsUpdated())
			{
				schedule[i].time = 0.0f;
				schedule[i].SetUpdated(false);
			}
			ScheduleEntry& entry = schedule[i];
			if (dirty ? entry.IsActive() : entry.IsScheduled())
			{
				if (entry.frameSkip == 1 || frame % entry.frameSkip == entry.phase)
				{
					if (entry.TestPasses(mask))
					{
						behaviours.begin[i]->Update(entry.time + dt, mask);
					}
					schedule[i].SetUpdated(true);
				}
				else if (fullPass)
				{
					entry.time += dt;
				}
			}
		}
		if (dirty && fullPass)
		{
			int total = behaviours.Size();
			unsigned short passes = 0;
			for (int i = 0; i < total; i++)
			{
				schedule[i].SetScheduled(false);
				if (schedule[i].IsActive() && schedule[i].GetPasses() != 0)
				{
					schedule[i].SetScheduled(true);
					passes |= schedule[i].GetPasses();
				}
			}
			GameObjectHandle handle = GetHandle(owner);
			handle.SetFlags(passes);
			handle.ClearFlags((unsigned short)(updateMask & ~passes));
		}
	}

	// FUNCTION: ENGINE 0x10839C00
	void BehaviourController::OnMessage(Message* message)
	{
		if (dispatch != 0)
		{
			signed char list[8];
			*(unsigned __int64*)list = *(unsigned __int64*)dispatch->entries[message->type];
			if (list[0] != (signed char)0xfe)
			{
				if (list[0] != (signed char)0xff)
				{
					signed char* index = list;
					do
					{
						behaviours.begin[*index]->OnMessage(message);
						index++;
					}
					while (*index != (signed char)0xff);
				}
				return;
			}
		}
		unsigned __int64 bit = GetMessageBit(message->type);
		int count = behaviours.Size();
		for (int i = 0; i < count; i++)
		{
			if (messageMasks[i].bits & bit)
			{
				behaviours.begin[i]->OnMessage(message);
			}
		}
	}

	// FUNCTION: ENGINE 0x10839CC0
	void BehaviourController::OnPostedMessage(Message* message)
	{
		if (dispatch != 0)
		{
			signed char list[8];
			*(unsigned __int64*)list = *(unsigned __int64*)dispatch->entries[message->type];
			if (list[0] != (signed char)0xfe)
			{
				if (list[0] != (signed char)0xff)
				{
					signed char* index = list;
					do
					{
						behaviours.begin[*index]->OnPostedMessage(message);
						index++;
					}
					while (*index != (signed char)0xff);
				}
				return;
			}
		}
		unsigned __int64 bit = GetMessageBit(message->type);
		int count = behaviours.Size();
		for (int i = 0; i < count; i++)
		{
			if (messageMasks[i].bits & bit)
			{
				behaviours.begin[i]->OnPostedMessage(message);
			}
		}
	}

	// FUNCTION: ENGINE 0x10839D80
	void BehaviourController::RegisterBehaviour(Behaviour* behaviour)
	{
		ScheduleEntry* entry;
		bool active;
		if (GetConstructingBehaviour() != 0)
		{
			SetConstructingBehaviour(0);
			entry = &schedule[scheduleCount - 1];
			active = behaviour->IsActive();
		}
		else
		{
			if (schedule == 0)
			{
				schedule = (ScheduleEntry*)core::HeapAlloc(1, 0x200);
				messageMasks = (MessageMask*)core::HeapAlloc(1, 0x200);
			}
			schedule[scheduleCount] = ScheduleEntry();
			messageMasks[scheduleCount] = MessageMask();
			scheduleCount++;
			entry = &schedule[scheduleCount - 1];
			active = behaviour->IsActive();
		}
		entry->SetActive(active);
	}

	// FUNCTION: ENGINE 0x10839E60
	void BehaviourController::OnActiveChanged(bool active)
	{
		bool wasActive = IsActive();
		if (active)
		{
			Behaviour::OnActiveChanged(true);
		}
		bool all = true;
		for (Behaviour** item = behaviours.begin; item != behaviours.end; item++)
		{
			Behaviour* behaviour = *item;
			behaviour->SetEnabled(active);
			if (behaviour->IsActive() != active)
			{
				all = false;
			}
		}
		if (all)
		{
			Behaviour::OnActiveChanged(active);
		}
		else if (active)
		{
			Behaviour::OnActiveChanged(wasActive);
		}
	}

	// FUNCTION: ENGINE 0x10839EF0
	void BehaviourController::SetRequestBitAll(unsigned char bit, bool on)
	{
		bool any = false;
		for (Behaviour** item = behaviours.begin; item != behaviours.end; item++)
		{
			Behaviour* behaviour = *item;
			behaviour->SetRequestBit(bit, on);
			if (behaviour->IsActive())
			{
				any = true;
			}
		}
		if (!IsActive() && any)
		{
			Behaviour::OnActiveChanged(true);
		}
		else if (IsActive() && !any)
		{
			Behaviour::OnActiveChanged(false);
		}
	}

	// FUNCTION: ENGINE 0x10839F90
	void BehaviourController::SetEnabledAll(bool enabled)
	{
		if (enabled)
		{
			Behaviour::OnActiveChanged(true);
		}
		bool any = false;
		for (Behaviour** item = behaviours.begin; item != behaviours.end; item++)
		{
			Behaviour* behaviour = *item;
			behaviour->SetEnabled(enabled);
			if (behaviour->IsActive())
			{
				any = true;
			}
		}
		Behaviour::OnActiveChanged(any);
	}

	// FUNCTION: ENGINE 0x10839FF0
	bool BehaviourController::SetEnabledOfType(const type_info& type, bool enabled)
	{
		bool all = true;
		for (Behaviour** item = behaviours.begin; item != behaviours.end; item++)
		{
			Behaviour* behaviour = *item;
			if (typeid(*behaviour) == type)
			{
				behaviour->SetEnabled(enabled);
				if (behaviour->IsActive() != enabled)
				{
					all = false;
				}
			}
		}
		return all;
	}

	// FUNCTION: ENGINE 0x1083A060
	void BehaviourController::HandleMessage(Message* message)
	{
		for (Behaviour** item = behaviours.begin; item != behaviours.end; item++)
		{
			message->SendTo(*item);
		}
	}

	// FUNCTION: ENGINE 0x1083A090
	bool BehaviourController::IsActiveOfType(const type_info& type)
	{
		bool found = false;
		for (Behaviour** item = behaviours.begin; item != behaviours.end; item++)
		{
			Behaviour* behaviour = *item;
			if (typeid(*behaviour) == type)
			{
				if (!behaviour->IsActive())
				{
					return false;
				}
				found = true;
			}
		}
		return found;
	}

	// FUNCTION: ENGINE 0x1083A380
	BehaviourController::ScheduleEntry* BehaviourController::GetSchedule(Behaviour* behaviour)
	{
		int index = IndexOf(behaviour);
		if (index < 0)
		{
			if (GetConstructingBehaviour() == 0)
			{
				RegisterBehaviour(behaviour);
				SetConstructingBehaviour(behaviour);
			}
			return &schedule[scheduleCount - 1];
		}
		return &schedule[index];
	}

	// FUNCTION: ENGINE 0x1083A3D0
	BehaviourController::MessageMask* BehaviourController::GetMessageMask(Behaviour* behaviour)
	{
		int index = IndexOf(behaviour);
		if (index < 0)
		{
			if (GetConstructingBehaviour() == 0)
			{
				RegisterBehaviour(behaviour);
				SetConstructingBehaviour(behaviour);
			}
			return &messageMasks[scheduleCount - 1];
		}
		return &messageMasks[index];
	}

	// FUNCTION: ENGINE 0x1083A420
	void BehaviourController::NotifyActiveChanged(Behaviour* behaviour)
	{
		ScheduleEntry* entry = GetSchedule(behaviour);
		if (behaviour->IsActive())
		{
			entry->SetActive(true);
			if (!IsActive())
			{
				Behaviour::OnActiveChanged(true);
			}
			unsigned short passes = entry->GetPasses();
			if (passes != 0 && owner->IsRegistered())
			{
				GetHandle(owner).SetFlags(passes);
			}
		}
		else
		{
			entry->SetActive(false);
		}
		dirty = true;
	}

	// FUNCTION: ENGINE 0x1083A4B0
	void BehaviourController::SetListening2(int mask, Behaviour* behaviour, bool add)
	{
		ScheduleEntry* entry;
		if (add)
		{
			entry = GetSchedule(behaviour);
			if (entry->TestPasses(mask))
			{
				return;
			}
			entry->flags |= mask;
		}
		else
		{
			entry = GetSchedule(behaviour);
			if (!entry->TestPasses(mask))
			{
				return;
			}
			entry->flags &= ~mask;
		}
		UpdatePasses(mask, add);
	}

	// FUNCTION: ENGINE 0x1083A530
	void BehaviourController::SetListening(int messageType, Behaviour* behaviour, bool listen)
	{
		unsigned __int64 bit = GetMessageBit(messageType);
		if (listen)
		{
			GetMessageMask(behaviour)->bits |= bit;
		}
		else
		{
			GetMessageMask(behaviour)->bits &= ~bit;
		}
		UpdateListening(messageType, listen);
	}

	// FUNCTION: ENGINE 0x1083A5B0
	void BehaviourController::Remove(unsigned char frameSkip, Behaviour* behaviour)
	{
		unsigned char phase = frameSkip;
		int count = behaviours.Size();
		for (int i = 0; i < count; i++)
		{
			if (schedule[i].frameSkip == frameSkip)
			{
				phase = schedule[i].phase;
				break;
			}
		}
		if (phase == frameSkip)
		{
			phase = gTimeSliceCounter++ % frameSkip;
		}
		ScheduleEntry* entry = GetSchedule(behaviour);
		entry->phase = phase;
		entry->frameSkip = frameSkip;
	}

	// FUNCTION: ENGINE 0x1083A630
	void BehaviourController::SetTimeSliceFrameSkip(unsigned char frameSkip)
	{
		if (frameSkip != timeSliceFrameSkip)
		{
			timeSliceFrameSkip = frameSkip;
			for (Behaviour** item = behaviours.begin; item != behaviours.end; item++)
			{
				Behaviour* behaviour = *item;
				if (behaviour->timeSliceFrameSkip > 0)
				{
					Remove((unsigned char)(behaviour->timeSliceFrameSkip * frameSkip + 1), behaviour);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1083A680
	void BehaviourController::RemoveAll()
	{
		while (behaviours.begin != behaviours.end)
		{
			delete behaviours.end[-1];
			if (behaviours.begin != behaviours.end)
			{
				behaviours.end--;
			}
		}
		if (schedule != 0)
		{
			core::Free(schedule);
		}
		if (messageMasks != 0)
		{
			core::Free(messageMasks);
		}
		schedule = 0;
		messageMasks = 0;
	}

	// FUNCTION: ENGINE 0x1083A9C0
	content::MemberList* BehaviourController::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<Behaviour>();
		static content::BaseClassCasterImpl<Behaviour, BehaviourController> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<BehaviourController, container::ArrayDynamicHeap<Behaviour*> >(
				content::GetObjectMetaType<Behaviour>("pnr"), "pnr"),
				content::MemberOffset(&((BehaviourController*)0)->behaviours,
				(int)&((BehaviourController*)0)->behaviours), "behaviours" },
			{ content::GetPrimitiveMetaType<float>("n"),
				content::MemberOffset(&((BehaviourController*)0)->updateTimeScalar,
				(int)&((BehaviourController*)0)->updateTimeScalar), "updateTimeScalar" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1083AAA0
	BehaviourController::BehaviourController(GameObject* newOwner)
		: Behaviour(newOwner), updateTimeScalar(1.0f), listenMask(0), updateMask(0), scheduleCount(0), schedule(0),
		messageMasks(0), dispatch(0)
	{
		dirty = true;
	}

	// FUNCTION: ENGINE 0x1083AB00
	BehaviourController::~BehaviourController()
	{
		RemoveAll();
	}

	// FUNCTION: ENGINE 0x1083AB30
	void BehaviourController::AddBehaviour(Behaviour* behaviour)
	{
		if (behaviours.Size() == behaviours.Capacity())
		{
			behaviours.Reserve(behaviours.Capacity() + 8);
		}
		behaviours.PushBack(behaviour);
		RegisterBehaviour(behaviour);
	}

	// FUNCTION: ENGINE 0x1083AC70
	void BehaviourController::Slot0()
	{
		container::CompactSwap(behaviours, GetConstructionHeap());
		int count = behaviours.Size();
		ScheduleEntry* newSchedule;
		MessageMask* newMasks;
		if (count > 0)
		{
			unsigned int size = count * sizeof(ScheduleEntry);
			newSchedule = (ScheduleEntry*)core::HeapAlloc(GetConstructionHeap(), size);
			newMasks = (MessageMask*)core::HeapAlloc(GetConstructionHeap(), size);
			memcpy(newSchedule, schedule, size);
			memcpy(newMasks, messageMasks, size);
		}
		else
		{
			newSchedule = 0;
			newMasks = 0;
		}
		container::Swap(schedule, newSchedule);
		container::Swap(messageMasks, newMasks);
		if (newSchedule != 0)
		{
			core::Free(newSchedule);
		}
		if (newMasks != 0)
		{
			core::Free(newMasks);
		}
		for (Behaviour** behaviour = behaviours.begin; behaviour < behaviours.end; behaviour++)
		{
			(*behaviour)->Slot0();
		}
	}

	// FUNCTION: ENGINE 0x1083AB90
	// container::CompactSwap<Behaviour*>
	// FUNCTION: ENGINE 0x1083A960
	// container::ArrayDynamicHeap<Behaviour*>'s range constructor

	// Kept copies: the schedule entry's and dispatch table's inline helpers, the reflection helpers and casters, the
	// behaviour array's members and the scalar deleting destructor
	// FUNCTION: ENGINE 0x10839200
	// FUNCTION: ENGINE 0x10839230
	// FUNCTION: ENGINE 0x10839260
	// FUNCTION: ENGINE 0x10839290
	// FUNCTION: ENGINE 0x108392B0
	// FUNCTION: ENGINE 0x108392D0
	// FUNCTION: ENGINE 0x10839310
	// FUNCTION: ENGINE 0x10839320
	// FUNCTION: ENGINE 0x108393D0
	// FUNCTION: ENGINE 0x10839490
	// FUNCTION: ENGINE 0x108394A0
	// FUNCTION: ENGINE 0x1083A130
	// FUNCTION: ENGINE 0x1083A190
	// FUNCTION: ENGINE 0x1083A1D0
	// FUNCTION: ENGINE 0x1083A1E0
	// FUNCTION: ENGINE 0x1083A200
	// FUNCTION: ENGINE 0x1083A210
	// FUNCTION: ENGINE 0x1083A220
	// FUNCTION: ENGINE 0x1083A230
	// FUNCTION: ENGINE 0x1083A240
	// FUNCTION: ENGINE 0x1083A260
	// FUNCTION: ENGINE 0x1083A2D0
	// FUNCTION: ENGINE 0x1083A710
	// FUNCTION: ENGINE 0x1083A730
	// FUNCTION: ENGINE 0x1083A7C0
	// FUNCTION: ENGINE 0x1083A810
	// FUNCTION: ENGINE 0x1083A8A0
	// FUNCTION: ENGINE 0x1083A8E0
	// FUNCTION: ENGINE 0x1083A920
	// FUNCTION: ENGINE 0x1083AC50
}
