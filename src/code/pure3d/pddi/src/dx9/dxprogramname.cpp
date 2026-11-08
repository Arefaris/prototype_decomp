// pure3d::dxProgramName and the small helpers around it (unit 0x1061AFA0 - 0x1061B1D0; the file name is guessed, no assert
// path survives).
#include <new>
#include <string.h>
#include <stdarg.h>
#include "code/core/strings.h"
#include "code/pure3d/pddi/dx9/dxdefaultpoolmanager.h"
#include "code/pure3d/pddi/dx9/dxprogram.h"

namespace core
{
	int VSNPrintfResult(char* buffer, int size, const char* format, va_list arguments);
}

namespace pure3d
{
	// FUNCTION: ENGINE 0x1061AFA0
	dxProgramName::dxProgramName(unsigned int newCapacity)
	{
		capacity = (newCapacity + 0x3F) & 0xFFFFFFC0;
		text = new char[capacity];
		text[0] = 0;
	}

	// FUNCTION: ENGINE 0x1061AFD0
	dxProgramName::~dxProgramName()
	{
		delete[] text;
	}

	// FUNCTION: ENGINE 0x1061AFE0
	void dxProgramName::Format(const char* format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		core::VSNPrintfResult(text, capacity, format, arguments);
	}

	// FUNCTION: ENGINE 0x1061B000
	void dxProgramName::Assign(const char* newText)
	{
		strncpy_s(text, capacity, newText, capacity - 1);
	}

	// FUNCTION: ENGINE 0x1061B0D0
	int dxProgramName::Length() const
	{
		return strlen(text);
	}

	// The Direct3D multisample modes of the display's settings: none, 2 and 4 samples
	static const int sMultiSampleTypes[3] = { 0, 2, 4 };

	// FUNCTION: ENGINE 0x1061B140
	int GetMultiSampleType(int samples)
	{
		return sMultiSampleTypes[samples];
	}
}
