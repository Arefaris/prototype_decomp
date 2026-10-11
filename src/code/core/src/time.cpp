#include "code/core/memory/memorypool.h"
#include "code/core/time.h"

// The kernel32 imports (see controllerdirectinput.cpp)
extern "C"
{
	struct SYSTEMTIME
	{
		unsigned short wYear;
		unsigned short wMonth;
		unsigned short wDayOfWeek;
		unsigned short wDay;
		unsigned short wHour;
		unsigned short wMinute;
		unsigned short wSecond;
		unsigned short wMilliseconds;
	};

	__declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64* count);
	__declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64* frequency);
	__declspec(dllimport) void __stdcall GetLocalTime(SYSTEMTIME* time);
}
#pragma comment(linker, "/alternatename:__imp__QueryPerformanceCounter@4=__imp__QueryPerformanceCounter")
#pragma comment(linker, "/alternatename:__imp__QueryPerformanceFrequency@4=__imp__QueryPerformanceFrequency")
#pragma comment(linker, "/alternatename:__imp__GetLocalTime@4=__imp__GetLocalTime")

namespace core
{
	const char* CoreName();

	// 0x110BC664: the day of the year each month starts on (no leap day)
	extern const int gMonthStartDays[12];

	// GLOBAL: ENGINE 0x11279000
	static int sTimeUsers;
	// GLOBAL: ENGINE 0x11279008
	static unsigned __int64 sTickFrequency;

	// FUNCTION: ENGINE 0x1063C7A0
	unsigned __int64 Time::GetMicroseconds() const
	{
		return (unsigned __int64)milliseconds * 1000 + microseconds;
	}

	// FUNCTION: ENGINE 0x1063C7C0
	void TimeNop1()
	{
	}

	// FUNCTION: ENGINE 0x1063C7D0
	void InitMemoryStage1()
	{
		if (++sTimeUsers == 1)
		{
			__int64 frequency;
			QueryPerformanceFrequency(&frequency);
			sTickFrequency = frequency;
		}
	}

	// FUNCTION: ENGINE 0x1063C810
	void ShutdownTime()
	{
		sTimeUsers--;
	}

	// FUNCTION: ENGINE 0x1063C820
	bool IsTimeReady()
	{
		return sTimeUsers != 0;
	}

	// FUNCTION: ENGINE 0x1063C830
	unsigned __int64 GetTicks()
	{
		__int64 count;
		QueryPerformanceCounter(&count);
		return count;
	}

	// FUNCTION: ENGINE 0x1063C850
	unsigned __int64 GetTickFrequency()
	{
		return sTickFrequency;
	}

	// FUNCTION: ENGINE 0x1063C860
	unsigned __int64 GetSeconds()
	{
		__int64 count;
		QueryPerformanceCounter(&count);
		return (unsigned __int64)count / sTickFrequency;
	}

	// FUNCTION: ENGINE 0x1063C890
	void GetDate(Date* date)
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		date->year = time.wYear;
		date->month = (unsigned char)time.wMonth;
		date->day = (unsigned char)time.wDay;
		date->hour = (unsigned char)time.wHour;
		date->minute = (unsigned char)time.wMinute;
		date->second = (unsigned char)time.wSecond;
	}

	// FUNCTION: ENGINE 0x1063C8E0
	unsigned int GetDayOfWeek(unsigned short year, unsigned char month, unsigned char day)
	{
		bool leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
		unsigned int days = gMonthStartDays[month - 1] + day - 1;
		if (leap && month > 2)
		{
			days++;
		}
		unsigned int years = (year - 1) % 400;
		return ((years / 4 - years / 100 + years) % 7 + days) % 7;
	}

	// FUNCTION: ENGINE 0x1063C980
	void TimerList::AddRef()
	{
		refCount++;
	}

	// FUNCTION: ENGINE 0x1063C990
	void TimerList::Release()
	{
		if (--refCount == 0)
		{
			delete this;
		}
	}

	// FUNCTION: ENGINE 0x1063C9A0
	void TimerList::Update(unsigned int now)
	{
		if (!started)
		{
			last = now;
			started = true;
			return;
		}
		unsigned int delta = now - last;
		last = now;
		for (unsigned int i = 0; i < count; i++)
		{
			if (timers[i] != 0)
			{
				Timer* timer = timers[i];
				timer->elapsed += delta;
				if (timer->elapsed >= timer->period)
				{
					if (timer->mode == 1)
					{
						timer->Stop();
					}
					ITimerCallback* callback = timer->callback;
					unsigned int elapsed = timer->elapsed;
					timer->elapsed = 0;
					if (callback != 0)
					{
						callback->OnTimer(elapsed, timer->userData);
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1063CA30
	void* TimerList::AllocTimer()
	{
		return pool->AllocBlock();
	}

	// FUNCTION: ENGINE 0x1063CA40
	void TimerList::FreeTimer(void* timer)
	{
		pool->Free(timer);
	}

	// FUNCTION: ENGINE 0x1063CA60
	void* Timer::operator new(unsigned int size, TimerList* list)
	{
		return list->AllocTimer();
	}

	// FUNCTION: ENGINE 0x1063CA70
	void Timer::AddRef()
	{
		refCount++;
	}

	// FUNCTION: ENGINE 0x1063CA80
	void Timer::Start()
	{
		if (!running)
		{
			elapsed = 0;
			running = true;
			for (unsigned int i = 0; i < list->count; i++)
			{
				if (list->timers[i] == 0)
				{
					list->timers[i] = this;
					return;
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1063CAC0
	void Timer::Stop()
	{
		if (running)
		{
			running = false;
			for (unsigned int i = 0; i < list->count; i++)
			{
				if (list->timers[i] == this)
				{
					list->timers[i] = 0;
					return;
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1063CB00
	void Timer::SetCallback(ITimerCallback* callback, void* userData)
	{
		this->callback = callback;
		this->userData = userData;
	}

	// FUNCTION: ENGINE 0x1063CB20
	void Timer::ClearCallback(ITimerCallback* callback)
	{
		this->callback = 0;
	}

	// FUNCTION: ENGINE 0x1063CB30
	unsigned int Timer::GetPeriod()
	{
		return period;
	}

	// FUNCTION: ENGINE 0x1063CB40
	void Timer::SetPeriod(unsigned int period)
	{
		if (running)
		{
			Stop();
			this->period = period;
			Start();
		}
		else
		{
			this->period = period;
		}
	}

	// FUNCTION: ENGINE 0x1063CB70
	int Timer::GetMode()
	{
		return mode;
	}

	// FUNCTION: ENGINE 0x1063CB80
	void Timer::SetMode(int mode)
	{
		this->mode = mode;
	}

	// FUNCTION: ENGINE 0x1063CB90
	bool Timer::IsStopped()
	{
		return !running;
	}

	// FUNCTION: ENGINE 0x1063CBA0
	unsigned int Timer::GetElapsed()
	{
		return elapsed;
	}

	// FUNCTION: ENGINE 0x1063CBB0
	float Timer::GetProgress()
	{
		return (float)elapsed / (float)period;
	}

	// FUNCTION: ENGINE 0x1063CBE0
	void Time::Set(unsigned int millis, unsigned int micros)
	{
		milliseconds = millis;
		microseconds = micros;
		seconds = millis * 0.001f + micros * 0.000001f;
	}

	// FUNCTION: ENGINE 0x1063CC30
	void Time::SetMicroseconds(unsigned __int64 value)
	{
		Set((unsigned int)(value / 1000), (unsigned int)(value % 1000));
	}

	// FUNCTION: ENGINE 0x1063CC60
	void Time::SetSeconds(float value)
	{
		seconds = value;
		milliseconds = (unsigned int)(value * 1000.0f);
		microseconds = (unsigned int)(value * 1000000.0f) % 1000;
	}

	// FUNCTION: ENGINE 0x1063CCE0
	void Time::Clear()
	{
		milliseconds = 0;
		microseconds = 0;
		seconds = 0.0f;
	}

	// FUNCTION: ENGINE 0x1063CD00
	void Time::Add(unsigned int millis, unsigned int micros)
	{
		microseconds += micros;
		milliseconds += millis + microseconds / 1000;
		microseconds %= 1000;
		seconds = milliseconds * 0.001f + microseconds * 0.000001f;
	}

	// FUNCTION: ENGINE 0x1063CD60
	void Time::AddMicroseconds(unsigned __int64 value)
	{
		Add((unsigned int)(value / 1000), (unsigned int)(value % 1000));
	}

	// FUNCTION: ENGINE 0x1063CD90
	void Time::SubtractMicroseconds(unsigned __int64 value)
	{
		unsigned __int64 current = (unsigned __int64)milliseconds * 1000 + microseconds;
		if (current > value)
		{
			SetMicroseconds(current - value);
		}
		else
		{
			Clear();
		}
	}

	// FUNCTION: ENGINE 0x1063CDD0
	unsigned __int64 ScaleTime(unsigned __int64 value, unsigned __int64 multiplier, unsigned __int64 divisor)
	{
		return (value / divisor) * multiplier + ((value % divisor) * multiplier) / divisor;
	}

	// FUNCTION: ENGINE 0x1063CE40
	void TimeNop2()
	{
	}

	// FUNCTION: ENGINE 0x1063CE50
	unsigned __int64 GetMicroseconds()
	{
		__int64 count;
		QueryPerformanceCounter(&count);
		return ScaleTime(count, 1000000, sTickFrequency);
	}

	// FUNCTION: ENGINE 0x1063CE90
	unsigned __int64 GetElapsedMicroseconds()
	{
		__int64 count;
		QueryPerformanceCounter(&count);
		return ScaleTime(count, 1000000, sTickFrequency);
	}

	// FUNCTION: ENGINE 0x1063CED0
	unsigned int GetMilliseconds()
	{
		__int64 count;
		QueryPerformanceCounter(&count);
		return (unsigned int)ScaleTime(count, 1000, sTickFrequency);
	}

	// FUNCTION: ENGINE 0x1063CF20
	TimerList::~TimerList()
	{
		Free(timers);
		pool->Release();
	}

	// FUNCTION: ENGINE 0x1063CF70
	void TimerList::Update()
	{
		Update(GetMilliseconds());
	}

	// FUNCTION: ENGINE 0x1063CF90
	Timer::Timer(TimerList* list, unsigned int period, ITimerCallback* callback, void* userData, bool start, int mode)
		: refCount(1), mode(mode), period(period), running(false), callback(callback), userData(userData), list(list)
	{
		CoreName();
		list->AddRef();
		if (start)
		{
			Start();
		}
	}

	// FUNCTION: ENGINE 0x1063CFF0
	Timer::~Timer()
	{
		if (running)
		{
			Stop();
		}
	}

	// FUNCTION: ENGINE 0x1063D010
	void Timer::Release()
	{
		if (--refCount == 0)
		{
			TimerList* owner = list;
			this->~Timer();
			owner->FreeTimer(this);
			owner->Release();
		}
	}

	// FUNCTION: ENGINE 0x1063D040
	Time::Time(unsigned int millis, unsigned int micros)
	{
		Set(millis, micros);
	}

	// FUNCTION: ENGINE 0x1063D060
	TimerList::TimerList(unsigned int count, int heap)
		: refCount(1), started(false), count(count)
	{
		CoreName();
		CreateMemoryPool((MemoryPool**)&pool, sizeof(Timer), count, heap, "TimerList", 0x10);
		timers = (Timer**)HeapAlloc(heap, count * sizeof(Timer*));
		CoreName();
		for (unsigned int i = 0; i < count; i++)
		{
			timers[i] = 0;
		}
	}

	// FUNCTION: ENGINE 0x1063D140
	void TimerList::CreateTimer(ITimer** out, unsigned int period, ITimerCallback* callback, void* userData,
		bool start, int mode)
	{
		*out = new (this) Timer(this, period, callback, userData, start, mode);
	}

	// FUNCTION: ENGINE 0x1063D1B0
	void CreateTimerList(ITimerList** out, unsigned int count, int heap)
	{
		*out = new (heap) TimerList(count, heap);
	}
}
