// The core module's reports and debug channels (unit 0x1063BC30 - 0x1063C77B, file name report.cpp and all names
// guessed). Report formats its message (the format with its arguments, or "Failed condition at file (line)" with the
// expression) and hands it to a dispatcher that is a stub in this build (it answers 2). Callers seen so far: the
// out-of-memory reports pass (0, 0, __FILE__, __LINE__, 0, message, 0); the asserts pass (1, " oldassert ", __FILE__,
// __LINE__, "condition", 0). Both switch the report off for good (a static bool next to the call) when it answers 3
// (presumably "ignore always").
// Debug channels: a table of named channels (0x48 bytes each: name, level, flags) under a lock, set up with the
// default levels of " oldwarning ", " Warning ", " Severe " and the flags of " Pre "; channel lists are strings of
// names separated by blanks, tabs and ";,[]\"'". The output handler (core::DefaultOutputHandler, RTTI name) writes
// debug text to OutputDebugString and stderr in 256-byte pieces. core::IsolatedTask (RTTI name) runs a task on a
// thread of its own (waiting up to a second for it to start, else running it in place).
#ifndef CORE_REPORT_H
#define CORE_REPORT_H

#include <stdarg.h>

#include "code/core/crashrecord.h"

namespace core
{
	struct DebugChannel
	{
		DebugChannel();

		char name[0x40];
		int level;
		int flags;
	};

	// Four values (0x110BC5E0: 1, 2, 4, 1; meaning unknown)
	struct ReportSettings
	{
		ReportSettings(int a, int b, int c, int d);

		int a;
		int b;
		int c;
		int d;
	};

	class DefaultOutputHandler : public IDebugOutputHandler
	{
	public:
		DefaultOutputHandler();
		virtual void OnOutput(DebugMessage* message);
		virtual ~DefaultOutputHandler()
		{
			sAlive = false;
		}

		static bool sAlive;
	};

	class IsolatedTask
	{
	public:
		explicit IsolatedTask(int result);
		virtual int Run();

		// Runs the task on a thread of its own; the result lands in result
		void Start();
		int Execute();

		unsigned int generation;
		volatile bool started;
		int result;
	};

	void InitThreadHook();
	void ShutdownThreadHook();
	// The output handler (the default one unless replaced); previous may be null
	void SetOutputHandler(IDebugOutputHandler* handler, IDebugOutputHandler** previous);
	void SetReportUserData(int value);
	IDebugOutputHandler* GetOutputHandler();
	void ReportNop1();
	void SetReportFlag(bool value);
	int GetReportLevel();
	void SetReportLevel(int level);
	void GetReportSettings(ReportSettings* settings);
	void SetReportSettings(const ReportSettings* settings);
	void ShutdownChannels();
	bool AreChannelsReady();
	void ReportNop2();
	void ReportNop3();
	bool ReportTrue();
	bool ReportFalse();
	// "INFO", "ERROR", "FATAL", "UNKNOWN"
	const char* GetReportLevelName(unsigned int level);
	void ReportNop4();
	// The stub dispatcher: always 2
	int DispatchReport(int kind, const char* tag, const char* file, int line, const char* text);
	int ReportV(int kind, const char* tag, const char* file, int line, const char* expression, const char* format,
		va_list arguments);
	void RemoveChannels(const char* list);
	void SetChannelLevels(const char* list, int level);
	void SetChannelFlags(const char* list, int flags);
	int GetChannelLevel(const char* name);
	unsigned int GetChannelCount();
	const char* GetChannelName(unsigned int index);
	int GetChannelLevelAt(unsigned int index);
	bool ReportTrue2();
	void InitChannels(unsigned int capacity, int heap);
	int Report(int kind, const char* tag, const char* file, int line, const char* expression, const char* format, ...);
}

#endif
