// The om library's streams (0x105C0E00 - 0x105C1010).
#include "code/om/stream.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

namespace om
{
	// FUNCTION: ENGINE 0x105C0E10
	void StreamPrintf(Stream* stream, const char* format, ...)
	{
		char buffer[0x800];
		va_list arguments;
		va_start(arguments, format);
		_vsnprintf_s(buffer, 0x800, 0xFFFFFFFF, format, arguments);
		buffer[0x7FF] = 0;
		stream->Write(buffer, strlen(buffer));
	}

	// FUNCTION: ENGINE 0x105C0EA0
	TextOutStream::TextOutStream(Stream* newTarget) :
		target(newTarget),
		atLineStart(false),
		indent(0),
		indentWithTabs(true)
	{
	}

	// FUNCTION: ENGINE 0x105C0ED0
	bool TextOutStream::WriteIndent()
	{
		unsigned int groups = indent / 10;
		unsigned int rest = indent % 10;
		for (unsigned int i = 0; i < groups; i++)
		{
			target->Write("										", 10);
		}
		if (rest > 0)
		{
			target->Write("										", rest);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105C0F20
	bool TextOutStream::WriteLinePart(const char* text, unsigned int length)
	{
		if (length > 0)
		{
			if (atLineStart)
			{
				if (indentWithTabs)
				{
					if (!WriteIndent())
					{
						return false;
					}
				}
				else
				{
					char space = ' ';
					if (!target->Write(&space, 1))
					{
						return false;
					}
				}
				atLineStart = false;
			}
			return target->Write(text, length);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105C0F90
	bool TextOutStream::Write(const void* data, unsigned int size)
	{
		const char* start = static_cast<const char*>(data);
		const char* end = start + size;
		const char* position = start;
		while (position < end)
		{
			if (*position == '\n')
			{
				if (indentWithTabs)
				{
					position++;
					if (!WriteLinePart(start, position - start))
					{
						return false;
					}
				}
				else
				{
					if (!WriteLinePart(start, position - start))
					{
						return false;
					}
					position++;
				}
				start = position;
				atLineStart = true;
			}
			else
			{
				position++;
			}
		}
		return WriteLinePart(start, position - start);
	}
}
