// The description of the whole numbers and the other plain values the om library reflects (0x10AA2770 - 0x10AA2E90): the
// functions that make one description when there is none yet and let go of a user of it, per type, in the order the
// compiler emitted them (a guess: the translation unit of the dynamic properties).
#include "code/om/dictionary.h"
#include "code/om/dynamicproperty.h"
#include "code/om/metaproperty.h"
#include "code/om/metasimpletype.h"
#include "code/om/vector.h"

#pragma warning(disable: 4661)

namespace om
{
	// Left to the engine: the slots whose instances differ from the engine's (the engine writes the 64-bit and boolean forms
	// and the values of the types that cannot be made through their own code)
	template<> bool MetaSimpleType<unsigned __int64>::ReadBinary(BinaryStream*, void*);
	template<> bool MetaSimpleType<unsigned __int64>::WriteBinary(BinaryStream*, void const*);
	template<> int MetaSimpleType<float>::Slot5();
	template<> void MetaSimpleType<float>::Slot6(void*);
	template<> bool MetaSimpleType<bool>::ReadBinary(BinaryStream*, void*);
	template<> bool MetaSimpleType<bool>::WriteBinary(BinaryStream*, void const*);
	template<> int MetaSimpleType<bool>::Slot5();
	template<> void MetaSimpleType<bool>::Slot6(void*);
	template<> int MetaSimpleType<String>::Slot5();
	template<> bool MetaSimpleType<String>::WriteBinary(BinaryStream*, void const*);
	template<> void MetaSimpleType<String>::Slot6(void*);
	template<> bool MetaSimpleType<Vector>::ReadBinary(BinaryStream*, void*);
	template<> bool MetaSimpleType<__int64>::ReadText(TextValue const*, void*);

	// FUNCTION: ENGINE 0x10AA2770
	template void MetaSimpleType<unsigned char>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA27D0
	template void MetaSimpleType<unsigned char>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA2800
	template void MetaSimpleType<unsigned short>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA2860
	template void MetaSimpleType<unsigned short>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA2890
	template void MetaSimpleType<unsigned int>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA28F0
	template void MetaSimpleType<unsigned int>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA2920
	template void MetaSimpleType<unsigned __int64>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA2980
	template void MetaSimpleType<unsigned __int64>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA29B0
	template void MetaSimpleType<char>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA2A10
	template void MetaSimpleType<char>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA2A40
	template void MetaSimpleType<short>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA2AA0
	template void MetaSimpleType<short>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA2AD0
	template void MetaSimpleType<int>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA2B30
	template void MetaSimpleType<int>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA2B60
	template void MetaSimpleType<__int64>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA2BC0
	template void MetaSimpleType<__int64>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA2BF0
	template void MetaSimpleType<float>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA2C50
	template void MetaSimpleType<float>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA2C80
	template void MetaSimpleType<bool>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA2CE0
	template void MetaSimpleType<bool>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA2D10
	template void MetaSimpleType<String>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA2D70
	template void MetaSimpleType<String>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA2DA0
	template void MetaSimpleType<Vector>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA2E00
	template void MetaSimpleType<Vector>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA2F00
	template void MetaSimpleType<ClassName>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA2F60
	template void MetaSimpleType<ClassName>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA2F90
	template bool MetaSimpleType<ClassName>::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10AA2FB0
	template bool MetaSimpleType<ClassName>::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10AA6EF0
	template bool MetaSimpleType<ClassName>::ReadText(TextValue const*, void*);
	typedef Dictionary<ClassName, ClassName, Comparer<ClassName> > NameDictionary;
	// FUNCTION: ENGINE 0x10AA30C0
	template void MetaSimpleType<NameDictionary>::Create(ClassName const&);
	// FUNCTION: ENGINE 0x10AA3120
	template void MetaSimpleType<NameDictionary>::ReleaseType();
	// FUNCTION: ENGINE 0x10AA8240
	template void MetaSimpleType<NameDictionary>::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10AA8260
	template bool MetaSimpleType<NameDictionary>::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10AA9890
	template bool MetaSimpleType<NameDictionary>::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10AA98B0
	template bool MetaSimpleType<NameDictionary>::ReadBinary(BinaryStream*, void*);
}
