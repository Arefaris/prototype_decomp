// The asynchronous render event queue (renderglobals.cpp): the game thread allocates an event from the queue's
// allocator, constructs it in place and pushes it; the render thread runs Execute, which calls the event's free
// function with the stored arguments and returns the event's memory (RenderEvent and the RenderEventN templates are
// RTTI names: engine::render::RenderEvent3<class engine::render::Drawable,int,bool> and so on; QueueRenderEvent and
// the member names are guesses). The units that use an instantiation instantiate it explicitly, which is why the
// original has out-of-line copies of the constructors that nothing calls.
#ifndef ENGINE_RENDER_ASYNC_RENDEREVENT_H
#define ENGINE_RENDER_ASYNC_RENDEREVENT_H

#include <new>

namespace engine
{
	namespace render
	{
		class RenderEvent
		{
		public:
			virtual void Execute() = 0;
		};

		// 0x10817A50: memory for an event (flushes the queue once when it is full)
		void* AllocRenderEvent(unsigned int size);
		// 0x10817AD0
		void FreeRenderEvent(void* event);
		// 0x10818CC0: hands the event to the render thread (frees it when the queue stays full)
		void PushRenderEvent(RenderEvent* event);

		template<class A1> class RenderEvent1 : public RenderEvent
		{
		public:
			typedef void (*Function)(A1);

			RenderEvent1(Function function, A1 a1) : mFunction(function), mA1(a1)
			{
			}
			virtual void Execute()
			{
				mFunction(mA1);
				FreeRenderEvent(this);
			}

			Function mFunction;
			A1 mA1;
		};

		template<class A1, class A2> class RenderEvent2 : public RenderEvent
		{
		public:
			typedef void (*Function)(A1, A2);

			RenderEvent2(Function function, A1 a1, A2 a2) : mFunction(function), mA1(a1), mA2(a2)
			{
			}
			virtual void Execute()
			{
				mFunction(mA1, mA2);
				FreeRenderEvent(this);
			}

			Function mFunction;
			A1 mA1;
			A2 mA2;
		};

		template<class A1, class A2, class A3> class RenderEvent3 : public RenderEvent
		{
		public:
			typedef void (*Function)(A1, A2, A3);

			RenderEvent3(Function function, A1 a1, A2 a2, A3 a3) : mFunction(function), mA1(a1), mA2(a2), mA3(a3)
			{
			}
			virtual void Execute()
			{
				mFunction(mA1, mA2, mA3);
				FreeRenderEvent(this);
			}

			Function mFunction;
			A1 mA1;
			A2 mA2;
			A3 mA3;
		};

		template<class A1, class A2, class A3, class A4> class RenderEvent4 : public RenderEvent
		{
		public:
			typedef void (*Function)(A1, A2, A3, A4);

			RenderEvent4(Function function, A1 a1, A2 a2, A3 a3, A4 a4) :
				mFunction(function), mA1(a1), mA2(a2), mA3(a3), mA4(a4)
			{
			}
			virtual void Execute()
			{
				mFunction(mA1, mA2, mA3, mA4);
				FreeRenderEvent(this);
			}

			Function mFunction;
			A1 mA1;
			A2 mA2;
			A3 mA3;
			A4 mA4;
		};

		template<class A1, class A2, class A3, class A4, class A5> class RenderEvent5 : public RenderEvent
		{
		public:
			typedef void (*Function)(A1, A2, A3, A4, A5);

			RenderEvent5(Function function, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) :
				mFunction(function), mA1(a1), mA2(a2), mA3(a3), mA4(a4), mA5(a5)
			{
			}
			virtual void Execute()
			{
				mFunction(mA1, mA2, mA3, mA4, mA5);
				FreeRenderEvent(this);
			}

			Function mFunction;
			A1 mA1;
			A2 mA2;
			A3 mA3;
			A4 mA4;
			A5 mA5;
		};

		template<class A1, class A2, class A3, class A4, class A5, class A6> class RenderEvent6 : public RenderEvent
		{
		public:
			typedef void (*Function)(A1, A2, A3, A4, A5, A6);

			RenderEvent6(Function function, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) :
				mFunction(function), mA1(a1), mA2(a2), mA3(a3), mA4(a4), mA5(a5), mA6(a6)
			{
			}
			virtual void Execute()
			{
				mFunction(mA1, mA2, mA3, mA4, mA5, mA6);
				FreeRenderEvent(this);
			}

			Function mFunction;
			A1 mA1;
			A2 mA2;
			A3 mA3;
			A4 mA4;
			A5 mA5;
			A6 mA6;
		};

		template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> class RenderEvent7 :
			public RenderEvent
		{
		public:
			typedef void (*Function)(A1, A2, A3, A4, A5, A6, A7);

			RenderEvent7(Function function, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) :
				mFunction(function), mA1(a1), mA2(a2), mA3(a3), mA4(a4), mA5(a5), mA6(a6), mA7(a7)
			{
			}
			virtual void Execute()
			{
				mFunction(mA1, mA2, mA3, mA4, mA5, mA6, mA7);
				FreeRenderEvent(this);
			}

			Function mFunction;
			A1 mA1;
			A2 mA2;
			A3 mA3;
			A4 mA4;
			A5 mA5;
			A6 mA6;
			A7 mA7;
		};

		template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> class RenderEvent8 :
			public RenderEvent
		{
		public:
			typedef void (*Function)(A1, A2, A3, A4, A5, A6, A7, A8);

			RenderEvent8(Function function, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) :
				mFunction(function), mA1(a1), mA2(a2), mA3(a3), mA4(a4), mA5(a5), mA6(a6), mA7(a7), mA8(a8)
			{
			}
			virtual void Execute()
			{
				mFunction(mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8);
				FreeRenderEvent(this);
			}

			Function mFunction;
			A1 mA1;
			A2 mA2;
			A3 mA3;
			A4 mA4;
			A5 mA5;
			A6 mA6;
			A7 mA7;
			A8 mA8;
		};

		// Queues a call of function with the arguments on the render thread
		template<class A1> void QueueRenderEvent(void (*function)(A1), A1 a1)
		{
			PushRenderEvent(new (AllocRenderEvent(sizeof(RenderEvent1<A1>))) RenderEvent1<A1>(function, a1));
		}

		template<class A1, class A2> void QueueRenderEvent(void (*function)(A1, A2), A1 a1, A2 a2)
		{
			PushRenderEvent(new (AllocRenderEvent(sizeof(RenderEvent2<A1, A2>))) RenderEvent2<A1, A2>(function, a1,
				a2));
		}

		template<class A1, class A2, class A3> void QueueRenderEvent(void (*function)(A1, A2, A3), A1 a1, A2 a2, A3 a3)
		{
			PushRenderEvent(new (AllocRenderEvent(sizeof(RenderEvent3<A1, A2, A3>))) RenderEvent3<A1, A2, A3>(
				function, a1, a2, a3));
		}

		template<class A1, class A2, class A3, class A4> void QueueRenderEvent(void (*function)(A1, A2, A3, A4), A1 a1,
			A2 a2, A3 a3, A4 a4)
		{
			PushRenderEvent(new (AllocRenderEvent(sizeof(RenderEvent4<A1, A2, A3, A4>))) RenderEvent4<A1, A2, A3, A4>(
				function, a1, a2, a3, a4));
		}

		template<class A1, class A2, class A3, class A4, class A5> void QueueRenderEvent(
			void (*function)(A1, A2, A3, A4, A5), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
		{
			PushRenderEvent(new (AllocRenderEvent(sizeof(RenderEvent5<A1, A2, A3, A4, A5>)))
				RenderEvent5<A1, A2, A3, A4, A5>(function, a1, a2, a3, a4, a5));
		}

		template<class A1, class A2, class A3, class A4, class A5, class A6> void QueueRenderEvent(
			void (*function)(A1, A2, A3, A4, A5, A6), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
		{
			PushRenderEvent(new (AllocRenderEvent(sizeof(RenderEvent6<A1, A2, A3, A4, A5, A6>)))
				RenderEvent6<A1, A2, A3, A4, A5, A6>(function, a1, a2, a3, a4, a5, a6));
		}

		template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> void QueueRenderEvent(
			void (*function)(A1, A2, A3, A4, A5, A6, A7), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
		{
			PushRenderEvent(new (AllocRenderEvent(sizeof(RenderEvent7<A1, A2, A3, A4, A5, A6, A7>)))
				RenderEvent7<A1, A2, A3, A4, A5, A6, A7>(function, a1, a2, a3, a4, a5, a6, a7));
		}

		template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> void QueueRenderEvent(
			void (*function)(A1, A2, A3, A4, A5, A6, A7, A8), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
		{
			PushRenderEvent(new (AllocRenderEvent(sizeof(RenderEvent8<A1, A2, A3, A4, A5, A6, A7, A8>)))
				RenderEvent8<A1, A2, A3, A4, A5, A6, A7, A8>(function, a1, a2, a3, a4, a5, a6, a7, a8));
		}
	}
}

#endif
