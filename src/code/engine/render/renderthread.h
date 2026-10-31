// The engine's render thread (unit around 0x10860890 - 0x10861100, with engine::render::RenderThreadCallbackAdapter;
// file name guessed): the queue other threads hand work to and wait on. Layout partial; names are guesses.
#ifndef ENGINE_RENDER_RENDERTHREAD_H
#define ENGINE_RENDER_RENDERTHREAD_H

namespace engine
{
	namespace render
	{
		// A thread waiting for its queued work (12 bytes): its core thread data, its semaphore, whether it waits
		struct RenderQueueWaiter
		{
			int thread;
			void* semaphore;
			bool waiting;
		};

		class RenderQueue
		{
		public:
			// 0x1085FDB0: a queue of that many items on the heap, with that many waiters (the second word is stored at +0)
			RenderQueue(int heap, unsigned int newCapacity, int newUnknown0, unsigned int newWaiterCount);
			// 0x1085FE60
			~RenderQueue();
			// 0x1085FEC0: adds an item at the end and wakes the render thread when it sleeps
			void Send(void* item);
			// 0x1085FF20: the first item without taking it; false when there is none
			bool Peek(void** item);
			// 0x1085FF70: the first item without taking it, waiting for it when there is none
			void WaitPeek(void** item);
			// 0x1085FFD0: takes the first item; false when there is none. On success the lock stays taken (the engine's
			// caller releases it)
			bool Pop(void** item);
			// 0x10860E80: queues item, wakes the render thread when it sleeps and waits until the item is done
			void SendAndWait(void* item);
			// 0x108601C0: the calling thread's waiter (a free one is claimed; null when none is left)
			RenderQueueWaiter* GetWaiter();

			int unknown0;
			// The render thread's semaphore and whether it sleeps on it
			void* semaphore;
			bool sleeping;
			RenderQueueWaiter* waiters;
			unsigned int waiterCount;
			unsigned char lock[0x18];
			unsigned int capacity;
			void** items;
			unsigned int readIndex;
			unsigned int writeIndex;
			bool unknown3C;
		};
	}
}

#endif
