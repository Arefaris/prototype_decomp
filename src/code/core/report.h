// The core module's assertion / error report (names guessed). 0x1063C750 forwards its arguments and a va_list of
// the rest to 0x1063C340; the callers seen so far pass (0, 0, __FILE__, __LINE__, 0, message, 0) and switch the
// report off for good when it answers 3 (presumably "ignore always").
#ifndef CORE_REPORT_H
#define CORE_REPORT_H

namespace core
{
	int Report(int kind, int flags, const char* file, int line, int category, const char* format, ...);
}

#endif
