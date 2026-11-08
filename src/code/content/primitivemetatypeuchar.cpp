// content::PrimitiveMetaType<unsigned char>: the constructor and the slots of the meta type of byte numbers (the first
// reflected class that uses it keeps the copies, in the unit of the navigation mesh reflection, 0x10568A70 -
// 0x10568DC0; the file name is guessed). See primitivemetatype.cpp.
#include "code/content/primitivemetatypeimpl.h"

namespace content
{
	template class PrimitiveMetaTypeImpl<unsigned char>;
	template PrimitiveMetaType<unsigned char>::PrimitiveMetaType(const char*);
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10568A70
// FUNCTION: ENGINE 0x10568AD0
// FUNCTION: ENGINE 0x10568B10
// FUNCTION: ENGINE 0x10568BB0
// FUNCTION: ENGINE 0x10568BE0
// FUNCTION: ENGINE 0x1056A7A0
// FUNCTION: ENGINE 0x10568D40
// FUNCTION: ENGINE 0x10568D60
// FUNCTION: ENGINE 0x10568D90
// FUNCTION: ENGINE 0x10568DA0
// FUNCTION: ENGINE 0x10568DC0
// FUNCTION: ENGINE 0x10568D20
// FUNCTION: ENGINE 0x10568D30
