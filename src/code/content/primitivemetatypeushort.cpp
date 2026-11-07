// content::PrimitiveMetaType<unsigned short>: the constructor and the slots of the meta type of 16-bit numbers (the
// first reflected class that uses it keeps the copies, unit 0x10393410 - 0x103937F0 and 0x10393910; the file name is
// guessed). See primitivemetatype.cpp.
#include "code/content/primitivemetatypeimpl.h"

namespace content
{
	template class PrimitiveMetaTypeImpl<unsigned short>;
	template PrimitiveMetaType<unsigned short>::PrimitiveMetaType(const char*);
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10393410
// FUNCTION: ENGINE 0x10393470
// FUNCTION: ENGINE 0x103934B0
// FUNCTION: ENGINE 0x10393560
// FUNCTION: ENGINE 0x10393590
// FUNCTION: ENGINE 0x103936E0
// FUNCTION: ENGINE 0x103936F0
// FUNCTION: ENGINE 0x10393710
// FUNCTION: ENGINE 0x10393730
// FUNCTION: ENGINE 0x10393760
// FUNCTION: ENGINE 0x10393770
// FUNCTION: ENGINE 0x10393790
// FUNCTION: ENGINE 0x10393C90
