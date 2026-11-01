// The recorder of the game object state the desync hunter compares (code/engine/system/desyncchecker.cpp; the file name
// is a guess, the unit lies in the online manager's, from 0x108BF8C0). Names are guesses.
#include "code/engine/system/desynchunter.h"
#include "code/content/metatype.h"
#include "code/math/random.h"
#include <new>
#include <string.h>

namespace core
{
	// 0x1063B960: the formatted length of a printf (the arguments come as a pointer to the stack)
	int VSNPrintfResult(char* buffer, int size, const char* format, const char* arguments);
	// 0x1063B990: the same for printf's own arguments
	int SNPrintfCount(char* buffer, int size, const char* format, ...);
}

namespace engine
{
	// FUNCTION: ENGINE 0x108BFA80
	DesyncChecker::DesyncChecker(int newSize, int newCapacity, bool newFlag)
	{
		capacity = newCapacity;
		used = 0;
		flag = newFlag;
		unknown14 = 0;
		size = newSize;
		unknown1C = 0;
		value = 0;
		unknown24 = 0;
		unknown28 = -1;
		unknown2C = 0;
		unknown30 = 0;
		content::NamedMetaType* type = content::NamedMetaType::Find("GameObject", 1);
		gameObjectType = dynamic_cast<content::ClassMetaType*>(type);
		buffer = new char[capacity];
	}

	// FUNCTION: ENGINE 0x108BFAF0
	DesyncChecker::~DesyncChecker()
	{
		delete[] buffer;
	}

	// FUNCTION: ENGINE 0x108BFB00
	void DesyncChecker::Append(const void* data, unsigned int length)
	{
		int end = used + 1 + length;
		if (end <= capacity)
		{
			memcpy(buffer + used, data, length);
			buffer[length + used] = 0;
			used = end;
		}
	}

	// FUNCTION: ENGINE 0x108BFBC0
	void DesyncChecker::Reset()
	{
		value = 0;
	}

	// FUNCTION: ENGINE 0x108BFBD0
	void DesyncChecker::Verify()
	{
	}

	// Appends formatted text, with its terminating zero, when it fits (name guess)
	// FUNCTION: ENGINE 0x108BFB40
	void DesyncPrintf(DesyncChecker* checker, const char* format, ...)
	{
		int offset = checker->used;
		if (offset < checker->capacity)
		{
			int length = core::VSNPrintfResult(checker->buffer + offset, checker->capacity - offset, format, (const char*)(&format + 1));
			int count = length + 1;
			if (count <= 0 || count > checker->capacity - checker->used)
			{
				count = checker->capacity - checker->used;
				memset(checker->buffer + checker->used, 0, count);
			}
			checker->used += count;
		}
	}

	// The sum of the bytes of a block in four lanes (name guess)
	// FUNCTION: ENGINE 0x108BFBE0
	unsigned int DesyncChecksum(const char* data, int length)
	{
		unsigned char lanes[4];
		lanes[0] = 0;
		lanes[1] = 0;
		lanes[2] = 0;
		lanes[3] = 0;
		for (int index = 0; index < length; index++)
		{
			lanes[index & 3] += data[index];
		}
		unsigned int result = lanes[3];
		result = (result << 8) + lanes[2];
		result = (result << 8) + lanes[1];
		result = (result << 8) + lanes[0];
		return result;
	}

	// A variable of the simulation the hunter compares (16 bytes)
	struct DesyncVariable
	{
		void* address;
		int size;
		const char* name;
		int mode;
	};

	// The table of them (0x11318588 / 0x1131858C / 0x11318590; names guessed)
	DesyncVariable* gDesyncVariables;
	unsigned int gDesyncVariableCapacity;
	unsigned int gDesyncVariableCount;

	// FUNCTION: ENGINE 0x108BF9C0
	void RegisterDesyncVariable(void* variable, int size, const char* name, int mode)
	{
		gDesyncVariables[gDesyncVariableCount].address = variable;
		gDesyncVariables[gDesyncVariableCount].size = size;
		gDesyncVariables[gDesyncVariableCount].name = name;
		gDesyncVariables[gDesyncVariableCount].mode = mode;
		gDesyncVariableCount = gDesyncVariableCount + 1;
	}

	// FUNCTION: ENGINE 0x108BFA20
	void UnregisterDesyncVariable(void* variable)
	{
		unsigned int count = gDesyncVariableCount;
		unsigned int index = 0;
		if (0 < count)
		{
			DesyncVariable* entries = gDesyncVariables;
			DesyncVariable* entry = entries;
			for (; index < count; index++, entry++)
			{
				if (entry->address == variable)
				{
					memmove(&entries[index], &entries[index + 1], (count - index) - 1);
					gDesyncVariableCount = gDesyncVariableCount - 1;
					return;
				}
			}
		}
	}

	// Gives the table back (name guess)
	// FUNCTION: ENGINE 0x108BF980
	void FreeDesyncVariables()
	{
		if (gDesyncVariables != 0)
		{
			delete[] gDesyncVariables;
			gDesyncVariables = 0;
			gDesyncVariableCapacity = 0;
			gDesyncVariableCount = 0;
		}
	}

	// Writes the state of the generator as a line of text; answers the bytes it took, the buffer's size at most (name guess)
	// FUNCTION: ENGINE 0x108BF8E0
	int FormatRandomState(char* buffer, int size)
	{
		unsigned int z = math::gRandom->z;
		unsigned int w = math::gRandom->w;
		int length = core::SNPrintfCount(buffer, size, "RNG gAIRand: %08X%08X\n", z, w);
		if (length < size)
		{
			return length + 1;
		}
		return size;
	}
}
