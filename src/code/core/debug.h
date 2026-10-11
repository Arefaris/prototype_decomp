// The core module's error report entry point (0x1063C750, another unit; name guessed): forwards to the reporting
// back end (0x1063C340) with the variadic arguments. The engine's assert-style checks keep a per-site static flag
// and clear it when the handler answers 3 (the user chose to ignore that site from now on). The asserts pass level
// 1, the kind " oldassert ", the file, the line, the expression text and a message; plain error reports pass 0 for
// level, kind and expression.
#ifndef CORE_DEBUG_H
#define CORE_DEBUG_H

namespace core
{
	int ReportError(int level, const char* kind, const char* file, int line, const char* expression,
		const char* format, ...);
}

// The engine's assert (expression text and message as the original wrote them). The file and line are the
// original's (from its strings), since our tree and line numbers differ.
#define OLD_ASSERT_AT(file, line, expression, text, message) \
	do \
	{ \
		static bool sEnabled = true; \
		if (sEnabled && !(expression)) \
		{ \
			if (core::ReportError(1, " oldassert ", file, line, text, message, 0) == 3) \
			{ \
				sEnabled = false; \
			} \
		} \
	} while (0)

#endif
