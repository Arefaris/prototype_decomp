// The core module's assertion / error report (names guessed). 0x1063C750 forwards its arguments and a va_list of
// the rest to 0x1063C340. Callers seen so far: the out-of-memory reports pass (0, 0, __FILE__, __LINE__, 0, message,
// 0); the asserts pass (1, " oldassert ", __FILE__, __LINE__, "condition", 0). Both switch the report off for good
// (a static bool next to the call) when it answers 3 (presumably "ignore always").
#ifndef CORE_REPORT_H
#define CORE_REPORT_H

namespace core
{
	int Report(int kind, const char* tag, const char* file, int line, const char* expression, const char* format, ...);
}

#endif
