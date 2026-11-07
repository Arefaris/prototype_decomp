// The ring buffer the audio thread's events are built in (0x105BA550 - 0x105BA840; names guessed).
#include "code/audio/remoteplayerevent.h"
#include "code/om/allocation.h"
#include <intrin.h>

namespace om
{
	// 0x105C2540
	void SleepMilliseconds(int milliseconds);
	unsigned int AlignUp(unsigned int value, unsigned int alignment);

	// FUNCTION: ENGINE 0x105BA610
	unsigned int AlignUp(unsigned int value, unsigned int alignment)
	{
		if (alignment != 0)
		{
			unsigned int rest = value % alignment;
			if (rest != 0)
			{
				return value - rest + alignment;
			}
		}
		return value;
	}
}

namespace audio
{
	// FUNCTION: ENGINE 0x105BA640
	long AtomicRead(volatile long* value)
	{
		return _InterlockedAnd(value, -1);
	}

	// FUNCTION: ENGINE 0x105BA660
	long AtomicExchange(volatile long* value, const long* newValue)
	{
		__asm
		{
			mov eax, newValue
			mov ecx, [eax]
			mov edx, value
			xchg [edx], ecx
			mov newValue, ecx
		}
		return (long)newValue;
	}

	// FUNCTION: ENGINE 0x105BA770
	void ProcessEvents()
	{
		Event* event = reinterpret_cast<Event*>(gEventQueue->Peek());
		while (event != 0)
		{
			event->Execute();
			delete event;
			event = reinterpret_cast<Event*>(gEventQueue->Peek());
		}
	}

	// FUNCTION: ENGINE 0x105BA5B0
	EventQueue::EventQueue(unsigned int newCapacity)
	{
		capacity = newCapacity;
		unknown14 = 0;
		gEventQueue = this;
		unsigned char* memory = (unsigned char*)om::Allocate("EventQueue", capacity, 8);
		free = 0;
		visible = 0;
		write = 0;
		buffer = memory;
	}

	// FUNCTION: ENGINE 0x105BA5F0
	EventQueue::~EventQueue()
	{
		om::Release(buffer, capacity, 8);
		gEventQueue = 0;
	}

	// FUNCTION: ENGINE 0x105BA680
	void EventQueue::GetSpace(unsigned int* space, unsigned int* limit)
	{
		unsigned int read = AtomicRead((volatile long*)&free);
		if (write >= read)
		{
			*space = capacity - write;
			*limit = read;
		}
		else
		{
			*space = read - write;
			*limit = 0;
		}
	}

	// FUNCTION: ENGINE 0x105BA6D0
	unsigned char* EventQueue::Peek()
	{
		unsigned int read = AtomicRead((volatile long*)&free);
		unsigned int available = AtomicRead((volatile long*)&visible);
		if (available != read)
		{
			unsigned char* base = buffer;
			if (*(unsigned int*)(base + read) == 0xFFFFFFFF)
			{
				return base;
			}
			return base + read;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105BA710
	void EventQueue::Publish()
	{
		AtomicExchange((volatile long*)&visible, (const long*)&write);
	}

	// FUNCTION: ENGINE 0x105BA730
	void EventQueue::Free(void* block, unsigned int size)
	{
		unsigned int rounded = om::AlignUp(size, 8);
		long position = (long)(rounded + ((unsigned char*)block - buffer)) & (capacity - 1);
		AtomicExchange((volatile long*)&free, &position);
	}

	// FUNCTION: ENGINE 0x105BA7B0
	void* EventQueue::Allocate(unsigned int size)
	{
		unsigned int rounded = om::AlignUp(size, 8);
		unsigned int limit;
		unsigned int space;
		GetSpace(&space, &limit);
		while (space <= rounded && limit <= rounded)
		{
			Publish();
			om::SleepMilliseconds(0x3C);
			GetSpace(&space, &limit);
		}
		if (space <= rounded)
		{
			*(unsigned int*)(buffer + write) = 0xFFFFFFFF;
			write = rounded;
			return buffer;
		}
		unsigned char* result = buffer + write;
		write += rounded;
		return result;
	}
}
