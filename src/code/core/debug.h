// The engine's assert-style checks on top of core::Report (report.h): a per-site static flag, cleared when the
// handler answers 3 (the user chose to ignore that site from now on).
#ifndef CORE_DEBUG_H
#define CORE_DEBUG_H

#include "code/core/report.h"

// The engine's assert (expression text and message as the original wrote them). The file and line are the
// original's (from its strings), since our tree and line numbers differ.
#define OLD_ASSERT_AT(file, line, expression, text, message) \
	do \
	{ \
		static bool sEnabled = true; \
		if (sEnabled && !(expression)) \
		{ \
			if (core::Report(1, " oldassert ", file, line, text, message, 0) == 3) \
			{ \
				sEnabled = false; \
			} \
		} \
	} while (0)

#endif
