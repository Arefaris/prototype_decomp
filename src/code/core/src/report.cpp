#include <stdio.h>
#include <string.h>

#include "code/core/criticalsection.h"
#include "code/core/heap.h"
#include "code/core/report.h"
#include "code/core/strings.h"

// The kernel32 imports (see controllerdirectinput.cpp)
extern "C"
{
	__declspec(dllimport) void __stdcall OutputDebugStringA(const char* text);
	__declspec(dllimport) void* __stdcall CreateThread(void* security, unsigned long stackSize,
		unsigned long (__stdcall* start)(void* parameter), void* parameter, unsigned long flags, unsigned long* id);
	__declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);
	__declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void* handle, unsigned long milliseconds);
	__declspec(dllimport) int __stdcall GetExitCodeThread(void* thread, unsigned long* code);
	__declspec(dllimport) int __stdcall TerminateThread(void* thread, unsigned long code);
	__declspec(dllimport) int __stdcall CloseHandle(void* handle);
}
#pragma comment(linker, "/alternatename:__imp__OutputDebugStringA@4=__imp__OutputDebugStringA")
#pragma comment(linker, "/alternatename:__imp__CreateThread@24=__imp__CreateThread")
#pragma comment(linker, "/alternatename:__imp__Sleep@4=__imp__Sleep")
#pragma comment(linker, "/alternatename:__imp__WaitForSingleObject@8=__imp__WaitForSingleObject")
#pragma comment(linker, "/alternatename:__imp__GetExitCodeThread@8=__imp__GetExitCodeThread")
#pragma comment(linker, "/alternatename:__imp__TerminateThread@8=__imp__TerminateThread")
#pragma comment(linker, "/alternatename:__imp__CloseHandle@4=__imp__CloseHandle")

namespace core
{
	// Initialised data of the unit (only declared: their initial values live in the original's .data)
	// 0x110BC5B4: "INFO", "ERROR", "FATAL"
	extern const char* gReportLevelNames[3];
	// 0x110BC5C0: the output handler, initially the default one (0x110BC5CC)
	extern IDebugOutputHandler* gOutputHandler;
	// 0x110BC5C4: -1 until InitChannels
	extern int gReportLevel;
	// 0x110BC5C8: bumped after every isolated task (a thread that starts late does not run it any more)
	extern unsigned int gTaskGeneration;
	// 0x110BC5E0
	extern ReportSettings gReportSettings;

	// GLOBAL: ENGINE 0x11278FD0
	static unsigned char sChannelLock[0x18];
	// GLOBAL: ENGINE 0x11278FE8
	bool DefaultOutputHandler::sAlive;
	// GLOBAL: ENGINE 0x11278FE9
	static bool sReportFlag;
	// GLOBAL: ENGINE 0x11278FEC
	static unsigned int sChannelLockState;
	// GLOBAL: ENGINE 0x11278FF0
	static int sReportUserData;
	// GLOBAL: ENGINE 0x11278FF4
	static unsigned int sChannelCapacity;
	// GLOBAL: ENGINE 0x11278FF8
	static unsigned int sChannelCount;
	// GLOBAL: ENGINE 0x11278FFC
	static DebugChannel* sChannels;

	// FUNCTION: ENGINE 0x1063BC30
	ReportSettings::ReportSettings(int a, int b, int c, int d)
	{
		this->d = d;
		this->a = a;
		this->b = b;
		this->c = c;
	}

	// FUNCTION: ENGINE 0x1063BC90
	DefaultOutputHandler::DefaultOutputHandler()
	{
		sAlive = true;
	}

	// Writes text to the debugger and (unless the message says not to) to stderr, in 256-byte pieces
	static __forceinline void WriteText(DebugMessage* message, const char* text, unsigned int length)
	{
		if (length == 0)
		{
			return;
		}
		unsigned int pieces = length / 0x100;
		unsigned int rest = length % 0x100;
		unsigned int i = 0;
		while (i < pieces)
		{
			char piece[0x101];
			memcpy(piece, &text[i * 0x100], 0x100);
			piece[0x100] = 0;
			OutputDebugStringA(piece);
			if ((message->flags & 0x40) == 0)
			{
				fputs(piece, stderr);
			}
			i++;
		}
		if (rest != 0)
		{
			OutputDebugStringA(&text[i * 0x100]);
			if ((message->flags & 0x40) == 0)
			{
				fputs(&text[i * 0x100], stderr);
			}
		}
	}

	// FUNCTION: ENGINE 0x1063BCE0
	void DefaultOutputHandler::OnOutput(DebugMessage* message)
	{
		const char* text = message->text;
		if (text == 0)
		{
			text = "NULL";
		}
		int length = StrLen(text);
		if (length > 0)
		{
			bool lineEnd = text[length - 1] == '\n';
			WriteText(message, text, length);
			if (!lineEnd)
			{
				OutputDebugStringA("\n");
				if ((message->flags & 0x40) == 0)
				{
					fputc('\n', stderr);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1063BE10
	static void LockChannels()
	{
		if (sChannelLockState == 0x55555555)
		{
			CriticalSectionEnter(sChannelLock);
		}
	}

	// FUNCTION: ENGINE 0x1063BE30
	static void UnlockChannels()
	{
		if (sChannelLockState == 0x55555555)
		{
			CriticalSectionLeave(sChannelLock);
		}
	}

	// FUNCTION: ENGINE 0x1063BE50
	DebugChannel::DebugChannel()
		: level(0), flags(1)
	{
	}

	// FUNCTION: ENGINE 0x1063BE70
	static inline bool IsSeparator(char c)
	{
		return c != 0 && strchr(" \t;,[]\"'", c) != 0;
	}

	// FUNCTION: ENGINE 0x1063BEA0
	static const char* SkipSeparators(const char* list)
	{
		if (list == 0)
		{
			return "";
		}
		while (IsSeparator(*list))
		{
			list++;
		}
		return list;
	}

	// FUNCTION: ENGINE 0x1063BEE0
	static const char* NextToken(const char* list)
	{
		list = SkipSeparators(list);
		while (*list != 0 && strchr(" \t;,[]\"'", *list) == 0)
		{
			list++;
		}
		while (IsSeparator(*list))
		{
			list++;
		}
		return list;
	}

	// FUNCTION: ENGINE 0x1063BF40
	// EQUIVALENT: one SIB byte: the original addresses the first loop's character as [length + token], ours as
	// [token + length] (index forms, a char local, pointer forms tried)
	static unsigned int TokenLength(const char* list)
	{
		unsigned int length = 0;
		const char* token = SkipSeparators(list);
		while (length < 0x3F && token[length] != 0 && !IsSeparator(token[length]))
		{
			length++;
		}
		while (length > 0 && IsSeparator(token[length - 1]))
		{
			length--;
		}
		return length;
	}

	// FUNCTION: ENGINE 0x1063BFA0
	static int FindChannel(const char* list)
	{
		const char* token = SkipSeparators(list);
		unsigned int length = TokenLength(token);
		if (length > 0)
		{
			for (unsigned int i = 0; i < sChannelCount; i++)
			{
				if (StrNICmp(token, sChannels[i].name, length) == 0)
				{
					return i;
				}
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x1063C000
	static int AddChannel(const char* list)
	{
		const char* token = SkipSeparators(list);
		unsigned int length = TokenLength(token);
		if (length > 0)
		{
			unsigned int i;
			for (i = 0; i < sChannelCount; i++)
			{
				if (StrNICmp(token, sChannels[i].name, length) == 0)
				{
					return i;
				}
			}
			if (sChannelCount < sChannelCapacity)
			{
				StrNCpy(sChannels[sChannelCount].name, token, length + 1);
				sChannels[sChannelCount++].name[0x3F] = 0;
				return sChannelCount - 1;
			}
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x1063C0A0
	static bool RemoveChannel(const char* list)
	{
		const char* token = SkipSeparators(list);
		unsigned int length = TokenLength(token);
		if (length > 0)
		{
			LockChannels();
			for (unsigned int i = 0; i < sChannelCount; i++)
			{
				if (StrNICmp(token, sChannels[i].name, length) == 0)
				{
					if (i < sChannelCount - 1)
					{
						sChannels[i] = sChannels[sChannelCount - 1];
					}
					sChannelCount--;
					UnlockChannels();
					return true;
				}
			}
			UnlockChannels();
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1063C130
	void InitThreadHook()
	{
		CriticalSectionInit(sChannelLock);
		sChannelLockState = 0x55555555;
	}

	// FUNCTION: ENGINE 0x1063C150
	void ShutdownThreadHook()
	{
		CriticalSectionDelete(sChannelLock);
		sChannelLockState = 0x33333333;
	}

	// FUNCTION: ENGINE 0x1063C170
	void SetOutputHandler(IDebugOutputHandler* handler, IDebugOutputHandler** previous)
	{
		LockChannels();
		IDebugOutputHandler* old = gOutputHandler;
		gOutputHandler = handler;
		if (previous != 0)
		{
			*previous = old;
		}
		UnlockChannels();
	}

	// FUNCTION: ENGINE 0x1063C1A0
	void SetReportUserData(int value)
	{
		LockChannels();
		sReportUserData = value;
		UnlockChannels();
	}

	// FUNCTION: ENGINE 0x1063C1C0
	IDebugOutputHandler* GetOutputHandler()
	{
		return gOutputHandler;
	}

	// FUNCTION: ENGINE 0x1063C1D0
	void ReportNop1()
	{
	}

	// FUNCTION: ENGINE 0x1063C1E0
	void SetReportFlag(bool value)
	{
		sReportFlag = value;
	}

	// FUNCTION: ENGINE 0x1063C1F0
	int GetReportLevel()
	{
		return gReportLevel;
	}

	// FUNCTION: ENGINE 0x1063C200
	void SetReportLevel(int level)
	{
		gReportLevel = level;
	}

	// FUNCTION: ENGINE 0x1063C210
	void GetReportSettings(ReportSettings* settings)
	{
		if (settings != 0)
		{
			*settings = gReportSettings;
		}
	}

	// FUNCTION: ENGINE 0x1063C240
	void SetReportSettings(const ReportSettings* settings)
	{
		if (settings != 0)
		{
			gReportSettings = *settings;
		}
	}

	// FUNCTION: ENGINE 0x1063C270
	void ShutdownChannels()
	{
		if (sChannels != 0)
		{
			delete[] sChannels;
			sChannels = 0;
			sChannelCount = 0;
			sChannelCapacity = 0;
		}
	}

	// FUNCTION: ENGINE 0x1063C2B0
	bool AreChannelsReady()
	{
		return sChannels != 0;
	}

	// FUNCTION: ENGINE 0x1063C2C0
	void ReportNop2()
	{
	}

	// FUNCTION: ENGINE 0x1063C2D0
	void ReportNop3()
	{
	}

	// FUNCTION: ENGINE 0x1063C2E0
	bool ReportTrue()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x1063C2F0
	bool ReportFalse()
	{
		return false;
	}

	// FUNCTION: ENGINE 0x1063C300
	const char* GetReportLevelName(unsigned int level)
	{
		if (level < 3)
		{
			return gReportLevelNames[level];
		}
		return "UNKNOWN";
	}

	// FUNCTION: ENGINE 0x1063C320
	void ReportNop4()
	{
	}

	// FUNCTION: ENGINE 0x1063C330
	int DispatchReport(int kind, const char* tag, const char* file, int line, const char* text)
	{
		return 2;
	}

	// FUNCTION: ENGINE 0x1063C340
	int ReportV(int kind, const char* tag, const char* file, int line, const char* expression, const char* format,
		va_list arguments)
	{
		char text[0x400];
		if ((expression == 0 || *expression == 0) && (format == 0 || *format == 0))
		{
			format = "<NULL>";
		}
		if (format != 0 && *format != 0)
		{
			VSNPrintf(text, 0x400, format, arguments);
		}
		else
		{
			SNPrintf(text, 0x400, "Failed condition at %s (%d):\n  %s\n", file, line, expression);
		}
		return DispatchReport(kind, tag, file, line, text);
	}

	// FUNCTION: ENGINE 0x1063C3E0
	void RemoveChannels(const char* list)
	{
		const char* token = SkipSeparators(list);
		while (*token != 0)
		{
			RemoveChannel(token);
			token = NextToken(token);
		}
	}

	// FUNCTION: ENGINE 0x1063C410
	void SetChannelLevels(const char* list, int level)
	{
		const char* token = SkipSeparators(list);
		LockChannels();
		while (*token != 0)
		{
			unsigned int index = AddChannel(token);
			if (index < sChannelCount)
			{
				sChannels[index].level = level;
			}
			token = NextToken(token);
		}
		UnlockChannels();
	}

	// FUNCTION: ENGINE 0x1063C470
	void SetChannelFlags(const char* list, int flags)
	{
		const char* token = SkipSeparators(list);
		LockChannels();
		while (*token != 0)
		{
			unsigned int index = AddChannel(token);
			if (index < sChannelCount)
			{
				sChannels[index].flags = flags;
			}
			token = NextToken(token);
		}
		UnlockChannels();
	}

	// FUNCTION: ENGINE 0x1063C4D0
	int GetChannelLevel(const char* name)
	{
		int level = 0;
		LockChannels();
		unsigned int index = FindChannel(name);
		if (index < sChannelCount)
		{
			level = sChannels[index].level;
		}
		UnlockChannels();
		return level;
	}

	// FUNCTION: ENGINE 0x1063C500
	unsigned int GetChannelCount()
	{
		return sChannelCount;
	}

	// FUNCTION: ENGINE 0x1063C510
	const char* GetChannelName(unsigned int index)
	{
		if (index < sChannelCount)
		{
			return sChannels[index].name;
		}
		return "";
	}

	// FUNCTION: ENGINE 0x1063C530
	int GetChannelLevelAt(unsigned int index)
	{
		if (index < sChannelCount)
		{
			return sChannels[index].level;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1063C550
	int IsolatedTask::Execute()
	{
		started = true;
		if (gTaskGeneration == generation)
		{
			return Run();
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1063C570
	static unsigned long __stdcall IsolatedTaskThread(void* task)
	{
		return ((IsolatedTask*)task)->Execute();
	}

	// FUNCTION: ENGINE 0x1063C580
	IsolatedTask::IsolatedTask(int result)
		: generation(0), started(false), result(result)
	{
	}

	// FUNCTION: ENGINE 0x1063C5A0
	int IsolatedTask::Run()
	{
		return result;
	}

	// FUNCTION: ENGINE 0x1063C5B0
	void IsolatedTask::Start()
	{
		generation = gTaskGeneration;
		unsigned long id;
		void* thread = CreateThread(0, 0x400, IsolatedTaskThread, this, 0, &id);
		for (unsigned int i = 0; i < 10; i++)
		{
			if (started)
			{
				break;
			}
			Sleep(100);
		}
		if (started)
		{
			unsigned long code;
			WaitForSingleObject(thread, 0xFFFFFFFF);
			GetExitCodeThread(thread, &code);
			CloseHandle(thread);
			result = code;
		}
		else
		{
			TerminateThread(thread, 0);
			CloseHandle(thread);
			result = Execute();
		}
		gTaskGeneration++;
	}

	// FUNCTION: ENGINE 0x1063C660
	bool ReportTrue2()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x1063C680
	void InitChannels(unsigned int capacity, int heap)
	{
		if (sChannels == 0)
		{
			HeapScope scope(heap);
			sChannelCapacity = capacity;
			sChannels = new DebugChannel[capacity];
			sChannelCount = 0;
			SetChannelLevels(" oldwarning ", 1);
			SetChannelLevels(" Warning ", 1);
			SetChannelLevels(" Severe ", 3);
			SetChannelFlags(" Pre ", 0x1C);
			if (gReportLevel == -1)
			{
				gReportLevel = 0;
			}
		}
	}

	// FUNCTION: ENGINE 0x1063C750
	int Report(int kind, const char* tag, const char* file, int line, const char* expression, const char* format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		return ReportV(kind, tag, file, line, expression, format, arguments);
	}
}
