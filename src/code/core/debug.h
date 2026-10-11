// The core module's error report entry point (0x1063C750, another unit; name guessed): forwards to the reporting
// back end (0x1063C340) with the variadic arguments. The engine's assert-style checks keep a per-site static flag
// and clear it when the handler answers 3 (the user chose to ignore that site from now on). The meaning of the
// three integer arguments around the file and line is unknown.
#ifndef CORE_DEBUG_H
#define CORE_DEBUG_H

namespace core
{
	int ReportError(int a, int b, const char* file, int line, int c, const char* format, ...);
}

#endif
