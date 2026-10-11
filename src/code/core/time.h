// The core timing code (unit 0x1063C7A0 - 0x1063D1B0, file name time.cpp guessed): the performance counter clock
// (QueryPerformanceCounter scaled by the frequency read at start-up), the local date, the time value core::Time, and
// core::Timer / core::TimerList (RTTI names; interfaces core::ITimer, core::ITimerList): timers live in a pool of
// their list and sit in its table while running; the list's Update adds the time since the last update to every
// running timer and calls its callback when the period is reached (a one-shot timer, mode 1, stops first). Method,
// member and function names are guessed.
#ifndef CORE_TIME_H
#define CORE_TIME_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/object.h"

namespace core
{
	struct IMemoryPool;
	class TimerList;

	// What a timer calls when its period is reached (no RTTI: name guessed)
	struct ITimerCallback
	{
		virtual void OnTimer(unsigned int elapsed, void* userData) = 0;
	};

	struct ITimer : IRefCount
	{
		virtual void SetCallback(ITimerCallback* callback, void* userData) = 0;
		virtual void ClearCallback(ITimerCallback* callback) = 0;
		virtual unsigned int GetPeriod() = 0;
		// A running timer is stopped and started again (elapsed back to 0)
		virtual void SetPeriod(unsigned int period) = 0;
		// 1: one-shot (stops when the period is reached), otherwise repeating
		virtual int GetMode() = 0;
		virtual void SetMode(int mode) = 0;
		virtual void Start() = 0;
		virtual void Stop() = 0;
		virtual bool IsStopped() = 0;
		virtual unsigned int GetElapsed() = 0;
		virtual float GetProgress() = 0;
	};

	struct ITimerList : IRefCount
	{
		virtual void CreateTimer(ITimer** out, unsigned int period, ITimerCallback* callback, void* userData,
			bool start, int mode) = 0;
		// Overloads in reverse vftable order: Update(now) is slot 4, Update() (now = GetMilliseconds()) slot 5
		virtual void Update() = 0;
		virtual void Update(unsigned int now) = 0;
	};

	class Timer : public ITimer
	{
	public:
		Timer(TimerList* list, unsigned int period, ITimerCallback* callback, void* userData, bool start, int mode);
		virtual ~Timer();
		// From the list's pool
		static void* operator new(unsigned int size, TimerList* list);

		virtual void AddRef();
		virtual void Release();
		virtual void SetCallback(ITimerCallback* callback, void* userData);
		virtual void ClearCallback(ITimerCallback* callback);
		virtual unsigned int GetPeriod();
		virtual void SetPeriod(unsigned int period);
		virtual int GetMode();
		virtual void SetMode(int mode);
		virtual void Start();
		virtual void Stop();
		virtual bool IsStopped();
		virtual unsigned int GetElapsed();
		virtual float GetProgress();

		int refCount;
		int mode;
		unsigned int period;
		bool running;
		unsigned int elapsed;
		ITimerCallback* callback;
		void* userData;
		TimerList* list;
	};

	class TimerList : public ITimerList, public Object
	{
	public:
		TimerList(unsigned int count, int heap);
		virtual ~TimerList();

		virtual void AddRef();
		virtual void Release();
		virtual void CreateTimer(ITimer** out, unsigned int period, ITimerCallback* callback, void* userData,
			bool start, int mode);
		virtual void Update();
		virtual void Update(unsigned int now);

		void* AllocTimer();
		void FreeTimer(void* timer);

		int refCount;
		bool started;
		unsigned int last;
		IMemoryPool* pool;
		unsigned int count;
		Timer** timers;
	};

	void CreateTimerList(ITimerList** out, unsigned int count, int heap);

	class Time
	{
	public:
		Time(unsigned int milliseconds, unsigned int microseconds);
		unsigned __int64 GetMicroseconds() const;
		// Stores both parts as supplied; unlike Add, this does not normalize microseconds.
		void Set(unsigned int milliseconds, unsigned int microseconds);
		void SetMicroseconds(unsigned __int64 value);
		void SetSeconds(float value);
		void Clear();
		void Add(unsigned int milliseconds, unsigned int microseconds);
		void AddMicroseconds(unsigned __int64 value);
		// Saturates at zero when value is at least the current time.
		void SubtractMicroseconds(unsigned __int64 value);

		unsigned int microseconds;
		unsigned int milliseconds;
		float seconds;
	};

	// The local date (GetLocalTime without the day of the week and the milliseconds)
	struct Date
	{
		unsigned short year;
		unsigned char month;
		unsigned char day;
		unsigned char hour;
		unsigned char minute;
		unsigned char second;
	};

	void TimeNop1();
	// Start-up of the clock (reference-counted; reads the counter frequency); named for its caller, the first step
	// of engine::InitMemory
	void InitMemoryStage1();
	void ShutdownTime();
	bool IsTimeReady();
	unsigned __int64 GetTicks();
	unsigned __int64 GetTickFrequency();
	unsigned __int64 GetSeconds();
	void GetDate(Date* date);
	// 0 = Sunday
	unsigned int GetDayOfWeek(unsigned short year, unsigned char month, unsigned char day);

	// Computes (value / divisor) * multiplier + ((value % divisor) * multiplier) / divisor.
	// Name guessed; preserves the original's unsigned 64-bit intermediate arithmetic.
	unsigned __int64 ScaleTime(unsigned __int64 value, unsigned __int64 multiplier, unsigned __int64 divisor);
	void TimeNop2();
	unsigned __int64 GetMicroseconds();
	unsigned __int64 GetElapsedMicroseconds();
	unsigned int GetMilliseconds();
}

#endif
