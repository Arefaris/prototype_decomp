// The debug output and crash handler chains (RTTI names core::IDebugOutputHandler, core::DebugOutputHandlerBase,
// core::CrashRecordDebugOutputHandler, core::ICrashHandler, core::CrashHandlerBase, core::CrashRecordCrashHandler;
// member and method names guessed). Handlers pass a message (or a crash) on to the next handler of their chain. The
// crash record keeps the last 4 KB of debug output in a ring buffer. Unit 0x106444D0 - 0x1064475C (file name
// crashrecord.cpp guessed).
#ifndef CORE_CRASHRECORD_H
#define CORE_CRASHRECORD_H

namespace core
{
	// What Report hands the output handlers (fields as the handlers read them)
	struct DebugMessage
	{
		int kind;
		const char* tag;
		const char* file;
		int line;
		const char* expression;
		const char* text;
		int level;
		unsigned int flags;
	};

	class IDebugOutputHandler
	{
	public:
		virtual void OnOutput(DebugMessage* message) = 0;
		virtual ~IDebugOutputHandler()
		{
		}
	};

	class DebugOutputHandlerBase : public IDebugOutputHandler
	{
	public:
		DebugOutputHandlerBase()
			: next(0)
		{
		}
		virtual void OnOutput(DebugMessage* message);
		virtual ~DebugOutputHandlerBase()
		{
		}

		IDebugOutputHandler* next;
	};

	class CrashRecordDebugOutputHandler : public DebugOutputHandlerBase
	{
	public:
		CrashRecordDebugOutputHandler();
		virtual void OnOutput(DebugMessage* message);
		virtual ~CrashRecordDebugOutputHandler()
		{
		}

		// Copies the record, oldest output first
		void GetRecord(char* out);
		// Appends to the ring; true when the record now ends in a line break
		bool Append(const char* text);

		char buffer[0x1000];
		unsigned int position;
		unsigned int total;
	};

	class ICrashHandler
	{
	public:
		virtual bool OnCrash(void* context) = 0;
	};

	class CrashHandlerBase : public ICrashHandler
	{
	public:
		CrashHandlerBase()
			: next(0)
		{
		}
		virtual bool OnCrash(void* context);

		ICrashHandler* next;
	};

	class CrashRecordCrashHandler : public CrashHandlerBase
	{
	public:
		CrashRecordCrashHandler();
		virtual bool OnCrash(void* context);
	};

	// 0x11279430: the crash record (constructed by a dynamic initializer of its own, 0x10D66900)
	extern CrashRecordDebugOutputHandler gCrashRecord;
	// 0x11279429: read only (set from a debugger?): errors stop the game when set
	extern bool gCrashRecordStop;
	// 0x10644760 / 0x106447E0: empty (names guessed)
	void DebugSignal(int value);
	void DebugWait(int value);
}

#endif
