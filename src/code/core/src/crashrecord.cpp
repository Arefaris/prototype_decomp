#include <string.h>

#include "code/core/crashrecord.h"
#include "code/core/strings.h"

namespace core
{
	// FUNCTION: ENGINE 0x106444F0
	void DebugOutputHandlerBase::OnOutput(DebugMessage* message)
	{
		if (next != 0)
		{
			next->OnOutput(message);
		}
	}

	// FUNCTION: ENGINE 0x10644520
	void CrashRecordDebugOutputHandler::GetRecord(char* out)
	{
		unsigned int older = sizeof(buffer) - position;
		if (total >= sizeof(buffer) && older > 0)
		{
			memcpy(out, buffer + position, older);
			out += older;
		}
		if (position > 0)
		{
			memcpy(out, buffer, position);
		}
	}

	// FUNCTION: ENGINE 0x10644580
	bool CrashRecordDebugOutputHandler::Append(const char* text)
	{
		unsigned int at = position;
		bool newline = true;
		while (*text != 0)
		{
			unsigned int length = StrLen(text);
			if (length > sizeof(buffer) - at)
			{
				length = sizeof(buffer) - at;
			}
			memcpy(buffer + at, text, length);
			at += length;
			newline = buffer[at - 1] == '\n';
			total += length;
			if (at >= sizeof(buffer))
			{
				total = sizeof(buffer);
				at = 0;
			}
			text += length;
		}
		position = at;
		return newline;
	}

	// FUNCTION: ENGINE 0x10644600
	bool CrashRecordCrashHandler::OnCrash(void* context)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10644640
	bool CrashHandlerBase::OnCrash(void* context)
	{
		if (next != 0)
		{
			return next->OnCrash(context);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10644690
	CrashRecordCrashHandler::CrashRecordCrashHandler()
	{
	}

	// FUNCTION: ENGINE 0x106446A0
	CrashRecordDebugOutputHandler::CrashRecordDebugOutputHandler()
		: position(0), total(0)
	{
		memset(buffer, 0, sizeof(buffer));
	}

	// FUNCTION: ENGINE 0x106446F0
	// Records every message but the automatic test's, ending each with a line break; errors stop the game while
	// gCrashRecordStop is set
	void CrashRecordDebugOutputHandler::OnOutput(DebugMessage* message)
	{
		if (StrNCmp(message->tag, "/autotest", 9) != 0)
		{
			if (!Append(message->text))
			{
				Append("\n");
			}
		}
		if (message->level >= 2 && gCrashRecordStop)
		{
			DebugSignal(3);
			DebugWait(10);
		}
		if (next != 0)
		{
			next->OnOutput(message);
		}
	}
}
