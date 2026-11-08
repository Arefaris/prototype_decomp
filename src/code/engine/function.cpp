// engine::Function: see the header (unit 0x108351B0 - 0x10835280, no assert path; the file name is a guess).
#include "code/engine/function.h"
#include "code/math/vector.h"

namespace engine
{
	// FUNCTION: ENGINE 0x108351B0
	Function::Function(const char* newName, int newArgumentCount)
	{
		argumentCount = newArgumentCount;
		name = 0;
		owner = 0;
		generation = 0;
	}

	// FUNCTION: ENGINE 0x108351D0
	void Function::SetName(const char* newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x108351E0
	// NONMATCHING: 92 %, the engine puts the exit for the text types right behind the first of its two tests and the
	// one for the integers behind the others; this compiler lays the exits out the other way round
#ifdef NONMATCHING
	char Function::GetTypeCode(const type_info& type, int size)
	{
		if (type == typeid(void))
		{
			return 'v';
		}
		if (type == typeid(bool))
		{
			return 'b';
		}
		if (type == typeid(char*))
		{
		text:
			return 's';
		}
		if (type == typeid(const char*))
		{
			goto text;
		}
		if (type == typeid(int) || type == typeid(unsigned int))
		{
			goto integer;
		}
		if (type == typeid(float))
		{
			return 'f';
		}
		if (type == typeid(math::Vector))
		{
			return 'V';
		}
		if (type == typeid(core::Name<core::CaseSensitiveKey>))
		{
			return 'n';
		}
		if (type == typeid(LuaGOH))
		{
			return 'h';
		}
		return size == 4 ? 'e' : 'v';
	integer:
		return 'i';
	}
#endif
}
