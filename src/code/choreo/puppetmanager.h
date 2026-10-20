// The registry of the puppets: handles that lead to puppets, the list of the puppets that are updated every frame, and
// the tasks that update them in batches (the unit 0x10955580 - 0x10955C00 with its container members, and the task
// part of 0x10958D80 - 0x10958F60; file name and all names guessed).
#ifndef CHOREO_PUPPETMANAGER_H
#define CHOREO_PUPPETMANAGER_H

#include "code/choreo/poseblendjob.h"
#include "code/choreo/puppet.h"
#include "code/core/asynctask.h"
#include "code/core/criticalsection.h"
#include "code/core/heap.h"

#include <new>

namespace core
{
	// 0x10B7FD90: waits for the tasks of the group and destroys its event (name guess)
	void DestroyAsyncTaskGroup(AsyncTaskGroup* group);
}

namespace choreo
{
	// What a handle leads to: a puppet and the generation the slot had when the handle was made (8 bytes)
	struct PuppetSlot
	{
		Puppet* mPuppet;
		int mGeneration;
	};

	// A handle to a puppet of the registry: the slot and the generation the slot had then
	class PuppetHandle
	{
	public:
		// 0x109555A0: no slot
		PuppetHandle();
		// 0x10955790: whether the slot still holds the puppet the handle was made for
		bool IsValid() const;
		// 0x109557D0 / 0x109557E0: the puppet of the slot
		Puppet* Get();
		Puppet* Get() const;

		int mIndex;         // 0x00
		int mGeneration;    // 0x04
	};

	// How the registry is set up (default 1024 puppets, batches of 4)
	struct PuppetManagerSettings
	{
		// 0x10955590
		PuppetManagerSettings();

		unsigned int mCapacity;
		unsigned int mBatchSize;
	};

	// Copies [first, last) to dest, front to back; answers the end of the copies
	template<class T>
	inline T* CopyRange(T* first, T* last, T* dest)
	{
		for (; first != last; first++, dest++)
		{
			*dest = *first;
		}
		return dest;
	}

	// Copy-constructs value at p (null: nothing)
	template<class T>
	inline void ConstructAt(T* p, const T& value)
	{
		if (p != 0)
		{
			new (p) T(value);
		}
	}

	// Copy-constructs count copies of value into raw storage at dest; answers the end of the copies
	template<class T>
	T* FillCopies(T* dest, unsigned int count, const T& value);

	// The slots of the handles: begin and end over operator new[] (the engine keeps no spare capacity)
	template<class T>
	struct SlotArray
	{
		unsigned int Size() const
		{
			return end - begin;
		}
		T* At(int index)
		{
			return begin + index;
		}
		T* Begin()
		{
			return begin;
		}
		T* End()
		{
			return end;
		}
		bool IsEmpty() const
		{
			return begin == end;
		}
		// Room for count slots, uninitialised (an empty array when there is none)
		bool Allocate(unsigned int count)
		{
			if (count > 0)
			{
				begin = (T*)operator new[](count * sizeof(T));
				if (begin != 0)
				{
					end = begin + count;
					return true;
				}
			}
			begin = 0;
			end = 0;
			return false;
		}
		// Room for count slots, each a copy of value; false when there is storage already
		bool Create(unsigned int count, const T& value);
		void Free()
		{
			if (begin != 0)
			{
				operator delete[](begin);
			}
			begin = 0;
			end = 0;
		}

		T* begin;
		T* end;
	};

	// The free slots: begin, end and capacity over operator new[]; the slots are taken from the end
	struct SlotStack
	{
		bool PushBack(const unsigned int& value)
		{
			if (end < capacity)
			{
				unsigned int* item = end++;
				if (item != 0)
				{
					*item = value;
				}
				return true;
			}
			return false;
		}
		void Erase(unsigned int* position)
		{
			CopyRange(position + 1, end, position);
			end--;
		}
		void Clear()
		{
			end = begin;
		}
		void Allocate(unsigned int count)
		{
			if (count != 0)
			{
				begin = (unsigned int*)operator new[](count * sizeof(unsigned int));
				if (begin != 0)
				{
					end = begin;
					capacity = begin + count;
					return;
				}
			}
			else
			{
				begin = 0;
			}
			end = 0;
			capacity = 0;
		}
		void Free()
		{
			if (begin != 0)
			{
				operator delete[](begin);
			}
			capacity = 0;
			end = 0;
			begin = 0;
		}

		unsigned int* begin;
		unsigned int* end;
		unsigned int* capacity;
	};

	// The puppets that are updated: begin, end and capacity, 16 byte aligned from the current heap
	struct PuppetList
	{
		// 0x10955890: room for count puppets (an empty list when there is none)
		bool Allocate(unsigned int count);
		// 0x10955AA0: the same
		bool Reserve(unsigned int count);
		void Free()
		{
			if (begin != 0)
			{
				core::FreeAligned(begin);
			}
			capacity = 0;
			end = 0;
			begin = 0;
		}
		Puppet** Find(Puppet* const& puppet)
		{
			Puppet** item = begin;
			while (item != end && *item != puppet)
			{
				item++;
			}
			return item;
		}
		bool PushBack(Puppet* const& puppet)
		{
			if (end < capacity)
			{
				Puppet** item = end++;
				if (item != 0)
				{
					*item = puppet;
				}
				return true;
			}
			return false;
		}
		void Erase(Puppet** position)
		{
			CopyRange(position + 1, end, position);
			end--;
		}

		Puppet** begin;
		Puppet** end;
		Puppet** capacity;
	};

	// The batches the update is cut into
	static const unsigned int MAX_PUPPET_JOBS = 64;

	// 0x1131E6FC: the object that is asked to wait for the tasks when there is one (a callback with one virtual)
	extern void* gPuppetWaiter;
	// 0x1131E700 / 0x1131E704: the next generation of a slot, and whether the puppets are being updated
	extern int gPuppetGeneration;
	extern bool gPuppetsUpdating;
	// 0x1131E708: the slot of each handle
	extern SlotArray<PuppetSlot> gPuppetSlots;
	// 0x1131E714: the slots that are free
	extern SlotStack gPuppetFreeSlots;
	// 0x1131E724: the puppets of the registry
	extern PuppetList gPuppetList;
	// 0x1131E740 / 0x1131E758: the locks of the pose blend job (the results and the buffers)
	extern unsigned char gPuppetResultLock[0x18];
	extern unsigned char gPuppetBufferLock[0x18];
	// 0x1131E770 / 0x1131E778 / 0x1131E780: the event the tasks signal, the task function and the task group
	extern unsigned char gPuppetEvent[8];
	extern int gPuppetTaskFunction;
	extern core::AsyncTaskGroup gPuppetTaskGroup;
	// 0x1131E7A0 / 0x1131F1A0: a task and what it works on for each batch
	extern core::AsyncTaskNode gPuppetTaskNodes[MAX_PUPPET_JOBS];
	extern PoseBlendJob gPuppetJobs[MAX_PUPPET_JOBS];
	// 0x111ECA94: how many puppets a batch holds at most
	extern unsigned int gPuppetBatchSize;
	// 0x111EC5C4: whether the update runs on the worker threads (it does unless the owner says otherwise)
	extern bool gPuppetsThreaded;

	// 0x109555B0 / 0x109555C0 / 0x109555D0: whether the update is threaded, and the switches
	bool GetPuppetsThreaded();
	void SetPuppetsThreaded(bool threaded);
	void TogglePuppetsThreaded();
	// 0x109555E0
	void SetPuppetWaiter(void* waiter);

	// 0x10955C00 / 0x10955B50: sets the registry up for as many puppets as the settings say / takes it down
	void InitializePuppetManager(const PuppetManagerSettings* settings);
	void ShutdownPuppetManager();
	// 0x10955940 / 0x109559C0: a handle for a puppet (one more owner of it) / takes the puppet out again
	PuppetHandle CreatePuppetHandle(Puppet* puppet);
	void DestroyPuppetHandle(PuppetHandle handle);
	// 0x109557F0: updates all the puppets of the registry over dt
	void UpdatePuppetManager(float dt);

	// 0x10958ED0 - 0x10958F60: the tasks of the update
	unsigned int GetPuppetJobCount();
	void StartPuppetJobs(const PuppetManagerSettings* settings);
	void StopPuppetJobs();
	// 0x10958F60: updates the puppets first to last over dt, on the tasks when the update is threaded; the waiter is
	// asked to wait for them when there is one
	void RunPuppetJobs(float dt, Puppet** first, Puppet** last, void* waiter);
}

#endif
