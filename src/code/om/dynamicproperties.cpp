// The dynamic properties of the om library (0x10A9E000 - 0x10AA9B40): the template instances of the property classes
// for the number types and the arrays.
#include "code/om/dynamicarray.h"
#include "code/om/dynamicproperty.h"

#pragma warning(disable: 4661)

namespace om
{
	// FUNCTION: ENGINE 0x10AA32D0
	template<> __declspec(noinline) bool ReadText<__int64>(const TextValue* text, __int64* value)
	{
		MetaTypeBase*& cache = MetaTypeCache<__int64>::type;
		if (cache == 0)
		{
			cache = FindMetaType(typeid(__int64));
		}
		return cache->ReadText(text, value);
	}

	// The engine expands the destructor of the string array in these four functions, ours calls it
	typedef DynamicArray<String, unsigned short> StringArray;
	template<> void DynamicProperty<StringArray>::Set(StringArray newValue);
	template<> StringArray CommandMember0Const<DynamicProperty<StringArray>, DynamicProperty<StringArray>, StringArray>::Call();
	template<> void CommandMember1<DynamicProperty<StringArray>, DynamicProperty<StringArray>, void, StringArray>::Call(StringArray value);
	template<> void CommandDelegate<StringArray>::Set(StringArray value);

	// FUNCTION: ENGINE 0x10AA8150
	// NONMATCHING: the array passed by value is destroyed by a call of its destructor, the engine expands it (8.0 %)
#ifdef NONMATCHING
	template<> void DynamicProperty<StringArray>::Set(StringArray newValue)
	{
		value = newValue;
	}
#endif

	// FUNCTION: ENGINE 0x10AA7B30
	// NONMATCHING: the returned copy of the array is built by a call of the copy constructor and the temporary is destroyed by a call, the engine expands it (33.0 %)
#ifdef NONMATCHING
	template<> StringArray CommandMember0Const<DynamicProperty<StringArray>, DynamicProperty<StringArray>, StringArray>::Call()
	{
		return (object->*function)();
	}
#endif

	// FUNCTION: ENGINE 0x10AA7BA0
	// NONMATCHING: the array passed by value is destroyed by a call of its destructor, the engine expands it (18.0 %)
#ifdef NONMATCHING
	template<> void CommandMember1<DynamicProperty<StringArray>, DynamicProperty<StringArray>, void, StringArray>::Call(StringArray value)
	{
		(object->*function)(value);
	}
#endif

	// FUNCTION: ENGINE 0x10AA7AA0
	// NONMATCHING: the array passed by value is destroyed by a call of its destructor, the engine expands it (18.0 %)
#ifdef NONMATCHING
	template<> void CommandDelegate<StringArray>::Set(StringArray value)
	{
		Command1<void, StringArray>& command = *setter.pointer;
		command.Call(value);
	}
#endif

	// FUNCTION: ENGINE 0x10A9E380
	template type_info const* Factory<DynamicPropertyBase,DynamicProperty<unsigned char> >::GetType();
	// FUNCTION: ENGINE 0x10A9E3B0
	template void Factory<DynamicPropertyBase,DynamicProperty<unsigned char> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10A9E3D0
	template char const* DynamicProperty<unsigned char>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9E450
	template char const* Factory<DynamicPropertyBase,DynamicProperty<unsigned char> >::AllocationTag();
	// FUNCTION: ENGINE 0x10A9E4A0
	template char const* DynamicProperty<unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9E4F0
	template type_info const* Factory<DynamicPropertyBase,DynamicProperty<unsigned int> >::GetType();
	// FUNCTION: ENGINE 0x10A9E510
	template void Factory<DynamicPropertyBase,DynamicProperty<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10A9E530
	template char const* DynamicProperty<unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9E560
	template type_info const* Factory<DynamicPropertyBase,DynamicProperty<unsigned __int64> >::GetType();
	// FUNCTION: ENGINE 0x10A9E580
	template void Factory<DynamicPropertyBase,DynamicProperty<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10A9E5A0
	template char const* DynamicProperty<unsigned __int64>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9E5E0
	template type_info const* Factory<DynamicPropertyBase,DynamicProperty<char> >::GetType();
	// FUNCTION: ENGINE 0x10A9E610
	template void Factory<DynamicPropertyBase,DynamicProperty<char> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10A9E630
	template char const* DynamicProperty<char>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9E670
	template type_info const* Factory<DynamicPropertyBase,DynamicProperty<short> >::GetType();
	// FUNCTION: ENGINE 0x10A9E6A0
	template void Factory<DynamicPropertyBase,DynamicProperty<short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10A9E6C0
	template char const* DynamicProperty<short>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9E700
	template type_info const* Factory<DynamicPropertyBase,DynamicProperty<int> >::GetType();
	// FUNCTION: ENGINE 0x10A9E730
	template void Factory<DynamicPropertyBase,DynamicProperty<int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10A9E750
	template char const* DynamicProperty<int>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9E790
	template type_info const* Factory<DynamicPropertyBase,DynamicProperty<__int64> >::GetType();
	// FUNCTION: ENGINE 0x10A9E7B0
	template void Factory<DynamicPropertyBase,DynamicProperty<__int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10A9E7D0
	template char const* DynamicProperty<__int64>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9E820
	template char const* Factory<DynamicPropertyBase,DynamicProperty<__int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10A9EA10
	template char const* DynamicProperty<DynamicArray<String,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10A9EAA0
	template char const* DynamicProperty<DynamicArray<float,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10A9EB30
	template char const* DynamicProperty<DynamicArray<unsigned int,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10A9EEE0
	template void* DynamicProperty<unsigned char>::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9EF00
	template void* DynamicProperty<unsigned short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9EF20
	template void* DynamicProperty<unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9EF40
	template void* DynamicProperty<unsigned __int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9EF60
	template void* DynamicProperty<char>::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9EF80
	template void* DynamicProperty<short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9EFA0
	template void* DynamicProperty<int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9EFC0
	template void* DynamicProperty<__int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9EFE0
	template void* DynamicProperty<DynamicArray<String,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9F000
	template void* DynamicProperty<DynamicArray<float,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9F020
	template void* DynamicProperty<DynamicArray<unsigned int,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9F070
	template DynamicProperty<unsigned char>::~DynamicProperty();
	// FUNCTION: ENGINE 0x10A9F080
	template void DynamicProperty<unsigned char>::SetName(Name<CaseSensitive64BitKey>);
	// FUNCTION: ENGINE 0x10A9F0A0
	template void DynamicProperty<unsigned char>::SetFromPointer2(void const*, unsigned int);
	// FUNCTION: ENGINE 0x10A9F0B0
	template Name<CaseSensitive64BitKey> DynamicProperty<unsigned char>::GetName() const;
	// FUNCTION: ENGINE 0x10A9F0D0
	template void DynamicProperty<unsigned char>::GetValue(void*) const;
	// FUNCTION: ENGINE 0x10A9F0E0
	template void const* DynamicProperty<unsigned char>::GetValuePointer() const;
	// FUNCTION: ENGINE 0x10A9F0F0
	template void* DynamicProperty<unsigned char>::GetValuePointer();
	// FUNCTION: ENGINE 0x10A9F100
	template MetaTypeBase* DynamicProperty<unsigned char>::GetMetaType() const;
	// FUNCTION: ENGINE 0x10A9F110
	template void DynamicProperty<unsigned char>::operator delete(void*);
	// FUNCTION: ENGINE 0x10A9F130
	template CommandMember0Const<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,unsigned char>::~CommandMember0Const();
	// FUNCTION: ENGINE 0x10A9F190
	template Owned<Command1<void,unsigned char> >::Owned(Command1<void,unsigned char>*);
	// FUNCTION: ENGINE 0x10A9F1A0
	template Owned<Command1<void,unsigned char> >::~Owned();
	// FUNCTION: ENGINE 0x10A9F1B0
	template Owned<Command0<unsigned char> >::Owned(Command0<unsigned char>*);
	// FUNCTION: ENGINE 0x10A9F1C0
	template Owned<Command0<unsigned char> >::~Owned();
	// FUNCTION: ENGINE 0x10A9F1D0
	template Command0<unsigned char>::Command0();
	// FUNCTION: ENGINE 0x10A9F1E0
	template unsigned char DynamicProperty<unsigned char>::GetValue() const;
	// FUNCTION: ENGINE 0x10A9F1F0
	template void DynamicProperty<unsigned char>::Set(unsigned char);
	// FUNCTION: ENGINE 0x10A9F220
	template char const* CommandDelegate<unsigned char>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9F230
	template char const* CommandMember0Const<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,unsigned char>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9F240
	template Command1<void,unsigned char>::Command1();
	// FUNCTION: ENGINE 0x10A9F250
	template char const* CommandMember1<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,void,unsigned char>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9F260
	template void DynamicProperty<unsigned char>::SetFrom(DynamicPropertyBase*);
	// FUNCTION: ENGINE 0x10A9F280
	template void DynamicProperty<unsigned char>::WriteToDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10A9F2A0
	template void DynamicProperty<unsigned char>::ReadFromDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10A9F2C0
	template void DynamicProperty<unsigned char>::SetFromPointer(void const*);
	// FUNCTION: ENGINE 0x10A9F2D0
	template void DynamicProperty<unsigned char>::WriteText(TextValue*);
	// FUNCTION: ENGINE 0x10A9F440
	template bool DynamicProperty<unsigned char>::ReadBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10A9F480
	template bool DynamicProperty<unsigned char>::WriteBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10A9F510
	template void* CommandDelegate<unsigned char>::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9F530
	template DelegateProperty<unsigned char>::DelegateProperty();
	// FUNCTION: ENGINE 0x10A9F540
	template MetaTypeBase* DelegateProperty<unsigned char>::GetMetaType();
	// FUNCTION: ENGINE 0x10A9F550
	template DelegateProperty<unsigned char>::~DelegateProperty();
	// FUNCTION: ENGINE 0x10A9F580
	template void* CommandMember0Const<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,unsigned char>::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9F5A0
	template CommandMember0Const<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,unsigned char>::CommandMember0Const(DynamicProperty<unsigned char>*, CommandMember0Const<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,unsigned char>::Function);
	// FUNCTION: ENGINE 0x10A9F5C0
	template unsigned char CommandMember0Const<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,unsigned char>::Call();
	// FUNCTION: ENGINE 0x10A9F5D0
	template Command0<unsigned char>::~Command0();
	// FUNCTION: ENGINE 0x10A9F5E0
	template void CommandMember0Const<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,unsigned char>::operator delete(void*);
	// FUNCTION: ENGINE 0x10A9F630
	template Command0<unsigned char>* CommandMember0Const<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,unsigned char>::Create(DynamicProperty<unsigned char>*, CommandMember0Const<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,unsigned char>::Function);
	// FUNCTION: ENGINE 0x10A9F870
	template DynamicProperty<unsigned short>::~DynamicProperty();
	// FUNCTION: ENGINE 0x10A9F880
	template void DynamicProperty<unsigned short>::SetName(Name<CaseSensitive64BitKey>);
	// FUNCTION: ENGINE 0x10A9F8A0
	template void DynamicProperty<unsigned short>::SetFromPointer2(void const*, unsigned int);
	// FUNCTION: ENGINE 0x10A9F8B0
	template Name<CaseSensitive64BitKey> DynamicProperty<unsigned short>::GetName() const;
	// FUNCTION: ENGINE 0x10A9F8D0
	template void DynamicProperty<unsigned short>::GetValue(void*) const;
	// FUNCTION: ENGINE 0x10A9F8E0
	template void const* DynamicProperty<unsigned short>::GetValuePointer() const;
	// FUNCTION: ENGINE 0x10A9F8F0
	template void* DynamicProperty<unsigned short>::GetValuePointer();
	// FUNCTION: ENGINE 0x10A9F900
	template MetaTypeBase* DynamicProperty<unsigned short>::GetMetaType() const;
	// FUNCTION: ENGINE 0x10A9F910
	template void DynamicProperty<unsigned short>::operator delete(void*);
	// FUNCTION: ENGINE 0x10A9F930
	template CommandMember0Const<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,unsigned short>::~CommandMember0Const();
	// FUNCTION: ENGINE 0x10A9F9D0
	template Command0<unsigned short>::Command0();
	// FUNCTION: ENGINE 0x10A9F9E0
	template unsigned short DynamicProperty<unsigned short>::GetValue() const;
	// FUNCTION: ENGINE 0x10A9F9F0
	template void DynamicProperty<unsigned short>::Set(unsigned short);
	// FUNCTION: ENGINE 0x10A9FA20
	template char const* CommandDelegate<unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9FA30
	template char const* CommandMember0Const<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9FA40
	template Command1<void,unsigned short>::Command1();
	// FUNCTION: ENGINE 0x10A9FA50
	template char const* CommandMember1<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,void,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10A9FA60
	template void DynamicProperty<unsigned short>::SetFrom(DynamicPropertyBase*);
	// FUNCTION: ENGINE 0x10A9FA80
	template void DynamicProperty<unsigned short>::WriteToDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10A9FAA0
	template void DynamicProperty<unsigned short>::ReadFromDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10A9FAC0
	template void DynamicProperty<unsigned short>::SetFromPointer(void const*);
	// FUNCTION: ENGINE 0x10A9FAD0
	template void DynamicProperty<unsigned short>::WriteText(TextValue*);
	// FUNCTION: ENGINE 0x10A9FC40
	template bool DynamicProperty<unsigned short>::ReadBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10A9FC80
	template bool DynamicProperty<unsigned short>::WriteBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10A9FD10
	template void* CommandDelegate<unsigned short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9FD30
	template DelegateProperty<unsigned short>::DelegateProperty();
	// FUNCTION: ENGINE 0x10A9FD40
	template MetaTypeBase* DelegateProperty<unsigned short>::GetMetaType();
	// FUNCTION: ENGINE 0x10A9FD80
	template void* CommandMember0Const<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,unsigned short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10A9FDA0
	template CommandMember0Const<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,unsigned short>::CommandMember0Const(DynamicProperty<unsigned short>*, CommandMember0Const<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,unsigned short>::Function);
	// FUNCTION: ENGINE 0x10A9FDC0
	template unsigned short CommandMember0Const<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,unsigned short>::Call();
	// FUNCTION: ENGINE 0x10A9FDD0
	template Command0<unsigned short>::~Command0();
	// FUNCTION: ENGINE 0x10A9FDE0
	template void CommandMember0Const<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,unsigned short>::operator delete(void*);
	// FUNCTION: ENGINE 0x10A9FE30
	template Command0<unsigned short>* CommandMember0Const<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,unsigned short>::Create(DynamicProperty<unsigned short>*, CommandMember0Const<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,unsigned short>::Function);
	// FUNCTION: ENGINE 0x10A9FE90
	template DynamicProperty<unsigned int>::~DynamicProperty();
	// FUNCTION: ENGINE 0x10A9FEA0
	template void DynamicProperty<unsigned int>::SetName(Name<CaseSensitive64BitKey>);
	// FUNCTION: ENGINE 0x10A9FEC0
	template void DynamicProperty<unsigned int>::SetFromPointer2(void const*, unsigned int);
	// FUNCTION: ENGINE 0x10A9FED0
	template Name<CaseSensitive64BitKey> DynamicProperty<unsigned int>::GetName() const;
	// FUNCTION: ENGINE 0x10A9FEF0
	template void DynamicProperty<unsigned int>::GetValue(void*) const;
	// FUNCTION: ENGINE 0x10A9FF00
	template void const* DynamicProperty<unsigned int>::GetValuePointer() const;
	// FUNCTION: ENGINE 0x10A9FF10
	template void* DynamicProperty<unsigned int>::GetValuePointer();
	// FUNCTION: ENGINE 0x10A9FF20
	template MetaTypeBase* DynamicProperty<unsigned int>::GetMetaType() const;
	// FUNCTION: ENGINE 0x10A9FF30
	template void DynamicProperty<unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10A9FF50
	template CommandMember0Const<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,unsigned int>::~CommandMember0Const();
	// FUNCTION: ENGINE 0x10A9FFB0
	template Owned<Command1<void,unsigned int> >::Owned(Command1<void,unsigned int>*);
	// FUNCTION: ENGINE 0x10A9FFC0
	template Owned<Command1<void,unsigned int> >::~Owned();
	// FUNCTION: ENGINE 0x10A9FFD0
	template Owned<Command0<unsigned int> >::Owned(Command0<unsigned int>*);
	// FUNCTION: ENGINE 0x10A9FFE0
	template Owned<Command0<unsigned int> >::~Owned();
	// FUNCTION: ENGINE 0x10A9FFF0
	template Command0<unsigned int>::Command0();
	// FUNCTION: ENGINE 0x10AA0000
	template void DynamicProperty<unsigned int>::Set(unsigned int);
	// FUNCTION: ENGINE 0x10AA0020
	template char const* CommandDelegate<unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA0030
	template char const* CommandMember0Const<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA0040
	template Command1<void,unsigned int>::Command1();
	// FUNCTION: ENGINE 0x10AA0050
	template char const* CommandMember1<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,void,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA0060
	template void DynamicProperty<unsigned int>::SetFrom(DynamicPropertyBase*);
	// FUNCTION: ENGINE 0x10AA0080
	template void DynamicProperty<unsigned int>::WriteToDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA00A0
	template void DynamicProperty<unsigned int>::ReadFromDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA00C0
	template void DynamicProperty<unsigned int>::SetFromPointer(void const*);
	// FUNCTION: ENGINE 0x10AA00D0
	template void DynamicProperty<unsigned int>::WriteText(TextValue*);
	// FUNCTION: ENGINE 0x10AA0240
	template bool DynamicProperty<unsigned int>::ReadBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA0280
	template bool DynamicProperty<unsigned int>::WriteBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA0310
	template void* CommandDelegate<unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA0330
	template void* CommandMember0Const<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA0350
	template CommandMember0Const<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,unsigned int>::CommandMember0Const(DynamicProperty<unsigned int>*, CommandMember0Const<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AA0370
	template unsigned int CommandMember0Const<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,unsigned int>::Call();
	// FUNCTION: ENGINE 0x10AA0380
	template Command0<unsigned int>::~Command0();
	// FUNCTION: ENGINE 0x10AA0390
	template void CommandMember0Const<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA03E0
	template Command0<unsigned int>* CommandMember0Const<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,unsigned int>::Create(DynamicProperty<unsigned int>*, CommandMember0Const<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AA0440
	template DynamicProperty<unsigned __int64>::~DynamicProperty();
	// FUNCTION: ENGINE 0x10AA0450
	template void DynamicProperty<unsigned __int64>::SetName(Name<CaseSensitive64BitKey>);
	// FUNCTION: ENGINE 0x10AA0470
	template void DynamicProperty<unsigned __int64>::SetFromPointer2(void const*, unsigned int);
	// FUNCTION: ENGINE 0x10AA0490
	template Name<CaseSensitive64BitKey> DynamicProperty<unsigned __int64>::GetName() const;
	// FUNCTION: ENGINE 0x10AA04B0
	template void DynamicProperty<unsigned __int64>::GetValue(void*) const;
	// FUNCTION: ENGINE 0x10AA04D0
	template void const* DynamicProperty<unsigned __int64>::GetValuePointer() const;
	// FUNCTION: ENGINE 0x10AA04E0
	template void* DynamicProperty<unsigned __int64>::GetValuePointer();
	// FUNCTION: ENGINE 0x10AA04F0
	template MetaTypeBase* DynamicProperty<unsigned __int64>::GetMetaType() const;
	// FUNCTION: ENGINE 0x10AA0500
	template void DynamicProperty<unsigned __int64>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA0520
	template CommandMember0Const<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,unsigned __int64>::~CommandMember0Const();
	// FUNCTION: ENGINE 0x10AA0530
	template Command1<void,unsigned __int64>::~Command1();
	// FUNCTION: ENGINE 0x10AA0580
	template Owned<Command1<void,unsigned __int64> >::Owned(Command1<void,unsigned __int64>*);
	// FUNCTION: ENGINE 0x10AA0590
	template Owned<Command1<void,unsigned __int64> >::~Owned();
	// FUNCTION: ENGINE 0x10AA05A0
	template Owned<Command0<unsigned __int64> >::Owned(Command0<unsigned __int64>*);
	// FUNCTION: ENGINE 0x10AA05B0
	template Owned<Command0<unsigned __int64> >::~Owned();
	// FUNCTION: ENGINE 0x10AA05C0
	template Command0<unsigned __int64>::Command0();
	// FUNCTION: ENGINE 0x10AA05D0
	template unsigned __int64 DynamicProperty<unsigned __int64>::GetValue() const;
	// FUNCTION: ENGINE 0x10AA05E0
	template void DynamicProperty<unsigned __int64>::Set(unsigned __int64);
	// FUNCTION: ENGINE 0x10AA0620
	template char const* CommandDelegate<unsigned __int64>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA0630
	template char const* CommandMember0Const<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,unsigned __int64>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA0640
	template Command1<void,unsigned __int64>::Command1();
	// FUNCTION: ENGINE 0x10AA0650
	template char const* CommandMember1<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,void,unsigned __int64>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA0660
	template void DynamicProperty<unsigned __int64>::SetFrom(DynamicPropertyBase*);
	// FUNCTION: ENGINE 0x10AA0680
	template void DynamicProperty<unsigned __int64>::WriteToDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA06A0
	template void DynamicProperty<unsigned __int64>::ReadFromDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA06C0
	template void DynamicProperty<unsigned __int64>::SetFromPointer(void const*);
	// FUNCTION: ENGINE 0x10AA06E0
	template void DynamicProperty<unsigned __int64>::WriteText(TextValue*);
	// FUNCTION: ENGINE 0x10AA0850
	template bool DynamicProperty<unsigned __int64>::ReadBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA0890
	template bool DynamicProperty<unsigned __int64>::WriteBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA0940
	template void* CommandDelegate<unsigned __int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA0960
	template void* CommandMember0Const<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,unsigned __int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA0980
	template CommandMember0Const<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,unsigned __int64>::CommandMember0Const(DynamicProperty<unsigned __int64>*, CommandMember0Const<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,unsigned __int64>::Function);
	// FUNCTION: ENGINE 0x10AA09A0
	template unsigned __int64 CommandMember0Const<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,unsigned __int64>::Call();
	// FUNCTION: ENGINE 0x10AA09B0
	template Command0<unsigned __int64>::~Command0();
	// FUNCTION: ENGINE 0x10AA09C0
	template void CommandMember0Const<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,unsigned __int64>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA0A10
	template Command0<unsigned __int64>* CommandMember0Const<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,unsigned __int64>::Create(DynamicProperty<unsigned __int64>*, CommandMember0Const<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,unsigned __int64>::Function);
	// FUNCTION: ENGINE 0x10AA0A70
	template DynamicProperty<char>::~DynamicProperty();
	// FUNCTION: ENGINE 0x10AA0A80
	template void DynamicProperty<char>::SetName(Name<CaseSensitive64BitKey>);
	// FUNCTION: ENGINE 0x10AA0AA0
	template void DynamicProperty<char>::SetFromPointer2(void const*, unsigned int);
	// FUNCTION: ENGINE 0x10AA0AB0
	template Name<CaseSensitive64BitKey> DynamicProperty<char>::GetName() const;
	// FUNCTION: ENGINE 0x10AA0AD0
	template void DynamicProperty<char>::GetValue(void*) const;
	// FUNCTION: ENGINE 0x10AA0AE0
	template void const* DynamicProperty<char>::GetValuePointer() const;
	// FUNCTION: ENGINE 0x10AA0AF0
	template void* DynamicProperty<char>::GetValuePointer();
	// FUNCTION: ENGINE 0x10AA0B00
	template MetaTypeBase* DynamicProperty<char>::GetMetaType() const;
	// FUNCTION: ENGINE 0x10AA0B10
	template void DynamicProperty<char>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA0B30
	template CommandMember0Const<DynamicProperty<char>,DynamicProperty<char>,char>::~CommandMember0Const();
	// FUNCTION: ENGINE 0x10AA0B90
	template Owned<Command1<void,char> >::Owned(Command1<void,char>*);
	// FUNCTION: ENGINE 0x10AA0BA0
	template Owned<Command1<void,char> >::~Owned();
	// FUNCTION: ENGINE 0x10AA0BB0
	template Owned<Command0<char> >::Owned(Command0<char>*);
	// FUNCTION: ENGINE 0x10AA0BC0
	template Owned<Command0<char> >::~Owned();
	// FUNCTION: ENGINE 0x10AA0BD0
	template Command0<char>::Command0();
	// FUNCTION: ENGINE 0x10AA0BE0
	template char DynamicProperty<char>::GetValue() const;
	// FUNCTION: ENGINE 0x10AA0BF0
	template void DynamicProperty<char>::Set(char);
	// FUNCTION: ENGINE 0x10AA0C20
	template char const* CommandDelegate<char>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA0C30
	template char const* CommandMember0Const<DynamicProperty<char>,DynamicProperty<char>,char>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA0C40
	template Command1<void,char>::Command1();
	// FUNCTION: ENGINE 0x10AA0C50
	template char const* CommandMember1<DynamicProperty<char>,DynamicProperty<char>,void,char>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA0C60
	template void DynamicProperty<char>::SetFrom(DynamicPropertyBase*);
	// FUNCTION: ENGINE 0x10AA0C80
	template void DynamicProperty<char>::WriteToDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA0CA0
	template void DynamicProperty<char>::ReadFromDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA0CC0
	template void DynamicProperty<char>::SetFromPointer(void const*);
	// FUNCTION: ENGINE 0x10AA0CD0
	template void DynamicProperty<char>::WriteText(TextValue*);
	// FUNCTION: ENGINE 0x10AA0E40
	template bool DynamicProperty<char>::ReadBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA0E80
	template bool DynamicProperty<char>::WriteBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA0F10
	template void* CommandDelegate<char>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA0F30
	template DelegateProperty<char>::DelegateProperty();
	// FUNCTION: ENGINE 0x10AA0F40
	template MetaTypeBase* DelegateProperty<char>::GetMetaType();
	// FUNCTION: ENGINE 0x10AA0F50
	template DelegateProperty<char>::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AA0F80
	template void* CommandMember0Const<DynamicProperty<char>,DynamicProperty<char>,char>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA0FA0
	template CommandMember0Const<DynamicProperty<char>,DynamicProperty<char>,char>::CommandMember0Const(DynamicProperty<char>*, CommandMember0Const<DynamicProperty<char>,DynamicProperty<char>,char>::Function);
	// FUNCTION: ENGINE 0x10AA0FC0
	template char CommandMember0Const<DynamicProperty<char>,DynamicProperty<char>,char>::Call();
	// FUNCTION: ENGINE 0x10AA0FD0
	template Command0<char>::~Command0();
	// FUNCTION: ENGINE 0x10AA0FE0
	template void CommandMember0Const<DynamicProperty<char>,DynamicProperty<char>,char>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA1030
	template Command0<char>* CommandMember0Const<DynamicProperty<char>,DynamicProperty<char>,char>::Create(DynamicProperty<char>*, CommandMember0Const<DynamicProperty<char>,DynamicProperty<char>,char>::Function);
	// FUNCTION: ENGINE 0x10AA1090
	template DynamicProperty<short>::~DynamicProperty();
	// FUNCTION: ENGINE 0x10AA10A0
	template void DynamicProperty<short>::SetName(Name<CaseSensitive64BitKey>);
	// FUNCTION: ENGINE 0x10AA10C0
	template void DynamicProperty<short>::SetFromPointer2(void const*, unsigned int);
	// FUNCTION: ENGINE 0x10AA10D0
	template Name<CaseSensitive64BitKey> DynamicProperty<short>::GetName() const;
	// FUNCTION: ENGINE 0x10AA10F0
	template void DynamicProperty<short>::GetValue(void*) const;
	// FUNCTION: ENGINE 0x10AA1100
	template void const* DynamicProperty<short>::GetValuePointer() const;
	// FUNCTION: ENGINE 0x10AA1110
	template void* DynamicProperty<short>::GetValuePointer();
	// FUNCTION: ENGINE 0x10AA1120
	template MetaTypeBase* DynamicProperty<short>::GetMetaType() const;
	// FUNCTION: ENGINE 0x10AA1130
	template void DynamicProperty<short>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA1150
	template CommandMember0Const<DynamicProperty<short>,DynamicProperty<short>,short>::~CommandMember0Const();
	// FUNCTION: ENGINE 0x10AA11B0
	template Owned<Command1<void,short> >::Owned(Command1<void,short>*);
	// FUNCTION: ENGINE 0x10AA11C0
	template Owned<Command1<void,short> >::~Owned();
	// FUNCTION: ENGINE 0x10AA11D0
	template Owned<Command0<short> >::Owned(Command0<short>*);
	// FUNCTION: ENGINE 0x10AA11E0
	template Owned<Command0<short> >::~Owned();
	// FUNCTION: ENGINE 0x10AA11F0
	template Command0<short>::Command0();
	// FUNCTION: ENGINE 0x10AA1200
	template short DynamicProperty<short>::GetValue() const;
	// FUNCTION: ENGINE 0x10AA1210
	template void DynamicProperty<short>::Set(short);
	// FUNCTION: ENGINE 0x10AA1240
	template char const* CommandDelegate<short>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA1250
	template char const* CommandMember0Const<DynamicProperty<short>,DynamicProperty<short>,short>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA1260
	template Command1<void,short>::Command1();
	// FUNCTION: ENGINE 0x10AA1270
	template char const* CommandMember1<DynamicProperty<short>,DynamicProperty<short>,void,short>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA1280
	template void DynamicProperty<short>::SetFrom(DynamicPropertyBase*);
	// FUNCTION: ENGINE 0x10AA12A0
	template void DynamicProperty<short>::WriteToDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA12C0
	template void DynamicProperty<short>::ReadFromDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA12E0
	template void DynamicProperty<short>::SetFromPointer(void const*);
	// FUNCTION: ENGINE 0x10AA12F0
	template void DynamicProperty<short>::WriteText(TextValue*);
	// FUNCTION: ENGINE 0x10AA1460
	template bool DynamicProperty<short>::ReadBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA14A0
	template bool DynamicProperty<short>::WriteBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA1530
	template void* CommandDelegate<short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA1550
	template DelegateProperty<short>::DelegateProperty();
	// FUNCTION: ENGINE 0x10AA1560
	template MetaTypeBase* DelegateProperty<short>::GetMetaType();
	// FUNCTION: ENGINE 0x10AA1570
	template DelegateProperty<short>::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AA15A0
	template void* CommandMember0Const<DynamicProperty<short>,DynamicProperty<short>,short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA15C0
	template CommandMember0Const<DynamicProperty<short>,DynamicProperty<short>,short>::CommandMember0Const(DynamicProperty<short>*, CommandMember0Const<DynamicProperty<short>,DynamicProperty<short>,short>::Function);
	// FUNCTION: ENGINE 0x10AA15E0
	template short CommandMember0Const<DynamicProperty<short>,DynamicProperty<short>,short>::Call();
	// FUNCTION: ENGINE 0x10AA15F0
	template Command0<short>::~Command0();
	// FUNCTION: ENGINE 0x10AA1600
	template void CommandMember0Const<DynamicProperty<short>,DynamicProperty<short>,short>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA1650
	template Command0<short>* CommandMember0Const<DynamicProperty<short>,DynamicProperty<short>,short>::Create(DynamicProperty<short>*, CommandMember0Const<DynamicProperty<short>,DynamicProperty<short>,short>::Function);
	// FUNCTION: ENGINE 0x10AA16B0
	template DynamicProperty<int>::~DynamicProperty();
	// FUNCTION: ENGINE 0x10AA16C0
	template void DynamicProperty<int>::SetName(Name<CaseSensitive64BitKey>);
	// FUNCTION: ENGINE 0x10AA16E0
	template void DynamicProperty<int>::SetFromPointer2(void const*, unsigned int);
	// FUNCTION: ENGINE 0x10AA16F0
	template Name<CaseSensitive64BitKey> DynamicProperty<int>::GetName() const;
	// FUNCTION: ENGINE 0x10AA1710
	template void DynamicProperty<int>::GetValue(void*) const;
	// FUNCTION: ENGINE 0x10AA1720
	template void const* DynamicProperty<int>::GetValuePointer() const;
	// FUNCTION: ENGINE 0x10AA1730
	template void* DynamicProperty<int>::GetValuePointer();
	// FUNCTION: ENGINE 0x10AA1740
	template MetaTypeBase* DynamicProperty<int>::GetMetaType() const;
	// FUNCTION: ENGINE 0x10AA1750
	template void DynamicProperty<int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA1770
	template CommandMember0Const<DynamicProperty<int>,DynamicProperty<int>,int>::~CommandMember0Const();
	// FUNCTION: ENGINE 0x10AA17D0
	template Owned<Command1<void,int> >::Owned(Command1<void,int>*);
	// FUNCTION: ENGINE 0x10AA17E0
	template Owned<Command1<void,int> >::~Owned();
	// FUNCTION: ENGINE 0x10AA17F0
	template Owned<Command0<int> >::Owned(Command0<int>*);
	// FUNCTION: ENGINE 0x10AA1800
	template Owned<Command0<int> >::~Owned();
	// FUNCTION: ENGINE 0x10AA1810
	template Command0<int>::Command0();
	// FUNCTION: ENGINE 0x10AA1820
	template int DynamicProperty<int>::GetValue() const;
	// FUNCTION: ENGINE 0x10AA1830
	template void DynamicProperty<int>::Set(int);
	// FUNCTION: ENGINE 0x10AA1860
	template char const* CommandDelegate<int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA1870
	template char const* CommandMember0Const<DynamicProperty<int>,DynamicProperty<int>,int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA1880
	template Command1<void,int>::Command1();
	// FUNCTION: ENGINE 0x10AA1890
	template char const* CommandMember1<DynamicProperty<int>,DynamicProperty<int>,void,int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA18A0
	template void DynamicProperty<int>::SetFrom(DynamicPropertyBase*);
	// FUNCTION: ENGINE 0x10AA18C0
	template void DynamicProperty<int>::WriteToDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA18E0
	template void DynamicProperty<int>::ReadFromDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA1900
	template void DynamicProperty<int>::SetFromPointer(void const*);
	// FUNCTION: ENGINE 0x10AA1910
	template void DynamicProperty<int>::WriteText(TextValue*);
	// FUNCTION: ENGINE 0x10AA1A80
	template bool DynamicProperty<int>::ReadBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA1AC0
	template bool DynamicProperty<int>::WriteBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA1B50
	template void* CommandDelegate<int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA1B70
	template DelegateProperty<int>::DelegateProperty();
	// FUNCTION: ENGINE 0x10AA1B80
	template MetaTypeBase* DelegateProperty<int>::GetMetaType();
	// FUNCTION: ENGINE 0x10AA1B90
	template DelegateProperty<int>::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AA1BC0
	template void* CommandMember0Const<DynamicProperty<int>,DynamicProperty<int>,int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA1BE0
	template CommandMember0Const<DynamicProperty<int>,DynamicProperty<int>,int>::CommandMember0Const(DynamicProperty<int>*, CommandMember0Const<DynamicProperty<int>,DynamicProperty<int>,int>::Function);
	// FUNCTION: ENGINE 0x10AA1C00
	template int CommandMember0Const<DynamicProperty<int>,DynamicProperty<int>,int>::Call();
	// FUNCTION: ENGINE 0x10AA1C10
	template Command0<int>::~Command0();
	// FUNCTION: ENGINE 0x10AA1C20
	template void CommandMember0Const<DynamicProperty<int>,DynamicProperty<int>,int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA1C70
	template Command0<int>* CommandMember0Const<DynamicProperty<int>,DynamicProperty<int>,int>::Create(DynamicProperty<int>*, CommandMember0Const<DynamicProperty<int>,DynamicProperty<int>,int>::Function);
	// FUNCTION: ENGINE 0x10AA1CD0
	template DynamicProperty<__int64>::~DynamicProperty();
	// FUNCTION: ENGINE 0x10AA1CE0
	template void DynamicProperty<__int64>::SetName(Name<CaseSensitive64BitKey>);
	// FUNCTION: ENGINE 0x10AA1D00
	template void DynamicProperty<__int64>::SetFromPointer2(void const*, unsigned int);
	// FUNCTION: ENGINE 0x10AA1D20
	template Name<CaseSensitive64BitKey> DynamicProperty<__int64>::GetName() const;
	// FUNCTION: ENGINE 0x10AA1D40
	template void DynamicProperty<__int64>::GetValue(void*) const;
	// FUNCTION: ENGINE 0x10AA1D60
	template void const* DynamicProperty<__int64>::GetValuePointer() const;
	// FUNCTION: ENGINE 0x10AA1D70
	template void* DynamicProperty<__int64>::GetValuePointer();
	// FUNCTION: ENGINE 0x10AA1D80
	template MetaTypeBase* DynamicProperty<__int64>::GetMetaType() const;
	// FUNCTION: ENGINE 0x10AA1D90
	template void DynamicProperty<__int64>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA1DB0
	template CommandMember0Const<DynamicProperty<__int64>,DynamicProperty<__int64>,__int64>::~CommandMember0Const();
	// FUNCTION: ENGINE 0x10AA1DC0
	template Command1<void,__int64>::~Command1();
	// FUNCTION: ENGINE 0x10AA1E10
	template Owned<Command1<void,__int64> >::Owned(Command1<void,__int64>*);
	// FUNCTION: ENGINE 0x10AA1E20
	template Owned<Command1<void,__int64> >::~Owned();
	// FUNCTION: ENGINE 0x10AA1E30
	template Owned<Command0<__int64> >::Owned(Command0<__int64>*);
	// FUNCTION: ENGINE 0x10AA1E40
	template Owned<Command0<__int64> >::~Owned();
	// FUNCTION: ENGINE 0x10AA1E50
	template Command0<__int64>::Command0();
	// FUNCTION: ENGINE 0x10AA1E60
	template __int64 DynamicProperty<__int64>::GetValue() const;
	// FUNCTION: ENGINE 0x10AA1E70
	template void DynamicProperty<__int64>::Set(__int64);
	// FUNCTION: ENGINE 0x10AA1EB0
	template char const* CommandDelegate<__int64>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA1EC0
	template char const* CommandMember0Const<DynamicProperty<__int64>,DynamicProperty<__int64>,__int64>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA1ED0
	template Command1<void,__int64>::Command1();
	// FUNCTION: ENGINE 0x10AA1EE0
	template char const* CommandMember1<DynamicProperty<__int64>,DynamicProperty<__int64>,void,__int64>::AllocationTag();
	// FUNCTION: ENGINE 0x10AA1EF0
	template void DynamicProperty<__int64>::SetFrom(DynamicPropertyBase*);
	// FUNCTION: ENGINE 0x10AA1F10
	template void DynamicProperty<__int64>::WriteToDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA1F30
	template void DynamicProperty<__int64>::ReadFromDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA1F50
	template void DynamicProperty<__int64>::SetFromPointer(void const*);
	// FUNCTION: ENGINE 0x10AA1FA0
	template void* CommandDelegate<__int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA1FC0
	template DelegateProperty<__int64>::DelegateProperty();
	// FUNCTION: ENGINE 0x10AA1FD0
	template MetaTypeBase* DelegateProperty<__int64>::GetMetaType();
	// FUNCTION: ENGINE 0x10AA1FE0
	template DelegateProperty<__int64>::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AA2010
	template void* CommandMember0Const<DynamicProperty<__int64>,DynamicProperty<__int64>,__int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA2030
	template CommandMember0Const<DynamicProperty<__int64>,DynamicProperty<__int64>,__int64>::CommandMember0Const(DynamicProperty<__int64>*, CommandMember0Const<DynamicProperty<__int64>,DynamicProperty<__int64>,__int64>::Function);
	// FUNCTION: ENGINE 0x10AA2050
	template __int64 CommandMember0Const<DynamicProperty<__int64>,DynamicProperty<__int64>,__int64>::Call();
	// FUNCTION: ENGINE 0x10AA2060
	template Command0<__int64>::~Command0();
	// FUNCTION: ENGINE 0x10AA2070
	template void CommandMember0Const<DynamicProperty<__int64>,DynamicProperty<__int64>,__int64>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA20C0
	template Command0<__int64>* CommandMember0Const<DynamicProperty<__int64>,DynamicProperty<__int64>,__int64>::Create(DynamicProperty<__int64>*, CommandMember0Const<DynamicProperty<__int64>,DynamicProperty<__int64>,__int64>::Function);
	// FUNCTION: ENGINE 0x10AA21C0
	template void* CommandMember1<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,void,unsigned char>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA21E0
	template CommandMember1<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,void,unsigned char>::CommandMember1(DynamicProperty<unsigned char>*, CommandMember1<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,void,unsigned char>::Function);
	// FUNCTION: ENGINE 0x10AA2200
	template void CommandMember1<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,void,unsigned char>::Call(unsigned char);
	// FUNCTION: ENGINE 0x10AA2220
	template void CommandMember1<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,void,unsigned char>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA2240
	template void* CommandMember1<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,void,unsigned short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA2260
	template CommandMember1<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,void,unsigned short>::CommandMember1(DynamicProperty<unsigned short>*, CommandMember1<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,void,unsigned short>::Function);
	// FUNCTION: ENGINE 0x10AA2280
	template void CommandMember1<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,void,unsigned short>::Call(unsigned short);
	// FUNCTION: ENGINE 0x10AA22A0
	template void CommandMember1<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,void,DynamicArray<unsigned int,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA22C0
	template void* CommandMember1<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,void,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA22E0
	template CommandMember1<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,void,unsigned int>::CommandMember1(DynamicProperty<unsigned int>*, CommandMember1<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AA2300
	template void CommandMember1<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,void,unsigned int>::Call(unsigned int);
	// FUNCTION: ENGINE 0x10AA2320
	template void CommandMember1<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,void,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA2340
	template void* CommandMember1<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,void,unsigned __int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA2360
	template CommandMember1<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,void,unsigned __int64>::CommandMember1(DynamicProperty<unsigned __int64>*, CommandMember1<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,void,unsigned __int64>::Function);
	// FUNCTION: ENGINE 0x10AA2380
	template void CommandMember1<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,void,unsigned __int64>::Call(unsigned __int64);
	// FUNCTION: ENGINE 0x10AA23A0
	template CommandMember1<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,void,unsigned __int64>::~CommandMember1();
	// FUNCTION: ENGINE 0x10AA23B0
	template void CommandMember1<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,void,unsigned __int64>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA23D0
	template void* CommandMember1<DynamicProperty<char>,DynamicProperty<char>,void,char>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA23F0
	template CommandMember1<DynamicProperty<char>,DynamicProperty<char>,void,char>::CommandMember1(DynamicProperty<char>*, CommandMember1<DynamicProperty<char>,DynamicProperty<char>,void,char>::Function);
	// FUNCTION: ENGINE 0x10AA2410
	template void CommandMember1<DynamicProperty<char>,DynamicProperty<char>,void,char>::Call(char);
	// FUNCTION: ENGINE 0x10AA2430
	template void CommandMember1<DynamicProperty<char>,DynamicProperty<char>,void,char>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA2450
	template void* CommandMember1<DynamicProperty<short>,DynamicProperty<short>,void,short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA2470
	template CommandMember1<DynamicProperty<short>,DynamicProperty<short>,void,short>::CommandMember1(DynamicProperty<short>*, CommandMember1<DynamicProperty<short>,DynamicProperty<short>,void,short>::Function);
	// FUNCTION: ENGINE 0x10AA2490
	template void CommandMember1<DynamicProperty<short>,DynamicProperty<short>,void,short>::Call(short);
	// FUNCTION: ENGINE 0x10AA24B0
	template void CommandMember1<DynamicProperty<short>,DynamicProperty<short>,void,short>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA24D0
	template void* CommandMember1<DynamicProperty<int>,DynamicProperty<int>,void,int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA24F0
	template CommandMember1<DynamicProperty<int>,DynamicProperty<int>,void,int>::CommandMember1(DynamicProperty<int>*, CommandMember1<DynamicProperty<int>,DynamicProperty<int>,void,int>::Function);
	// FUNCTION: ENGINE 0x10AA2510
	template void CommandMember1<DynamicProperty<int>,DynamicProperty<int>,void,int>::Call(int);
	// FUNCTION: ENGINE 0x10AA2530
	template void CommandMember1<DynamicProperty<int>,DynamicProperty<int>,void,int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA2550
	template void* CommandMember1<DynamicProperty<__int64>,DynamicProperty<__int64>,void,__int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA2570
	template CommandMember1<DynamicProperty<__int64>,DynamicProperty<__int64>,void,__int64>::CommandMember1(DynamicProperty<__int64>*, CommandMember1<DynamicProperty<__int64>,DynamicProperty<__int64>,void,__int64>::Function);
	// FUNCTION: ENGINE 0x10AA2590
	template void CommandMember1<DynamicProperty<__int64>,DynamicProperty<__int64>,void,__int64>::Call(__int64);
	// FUNCTION: ENGINE 0x10AA25B0
	template CommandMember1<DynamicProperty<__int64>,DynamicProperty<__int64>,void,__int64>::~CommandMember1();
	// FUNCTION: ENGINE 0x10AA25C0
	template void CommandMember1<DynamicProperty<__int64>,DynamicProperty<__int64>,void,__int64>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA38C0
	// EQUIVALENT: scheduling: the engine loads both halves of the key before the test of the result of the name read (95.5 %)
	template bool DynamicProperty<unsigned char>::ReadText(TextValue const*);
	// FUNCTION: ENGINE 0x10AA3990
	template DynamicPropertyBase* Factory<DynamicPropertyBase,DynamicProperty<unsigned char> >::Create(void*);
	// FUNCTION: ENGINE 0x10AA39F0
	// EQUIVALENT: scheduling: the engine loads both halves of the key before the test of the result of the name read (95.5 %)
	template bool DynamicProperty<unsigned short>::ReadText(TextValue const*);
	// FUNCTION: ENGINE 0x10AA3AC0
	template DynamicPropertyBase* Factory<DynamicPropertyBase,DynamicProperty<unsigned short> >::Create(void*);
	// FUNCTION: ENGINE 0x10AA3B10
	// EQUIVALENT: scheduling: the engine loads both halves of the key before the test of the result of the name read (95.5 %)
	template bool DynamicProperty<unsigned int>::ReadText(TextValue const*);
	// FUNCTION: ENGINE 0x10AA3BE0
	template DynamicPropertyBase* Factory<DynamicPropertyBase,DynamicProperty<unsigned int> >::Create(void*);
	// FUNCTION: ENGINE 0x10AA3C30
	// EQUIVALENT: scheduling: the engine loads both halves of the key before the test of the result of the name read (95.5 %)
	template bool DynamicProperty<unsigned __int64>::ReadText(TextValue const*);
	// FUNCTION: ENGINE 0x10AA3D00
	template DynamicPropertyBase* Factory<DynamicPropertyBase,DynamicProperty<unsigned __int64> >::Create(void*);
	// FUNCTION: ENGINE 0x10AA3D50
	// EQUIVALENT: scheduling: the engine loads both halves of the key before the test of the result of the name read (95.5 %)
	template bool DynamicProperty<char>::ReadText(TextValue const*);
	// FUNCTION: ENGINE 0x10AA3E20
	template DynamicPropertyBase* Factory<DynamicPropertyBase,DynamicProperty<char> >::Create(void*);
	// FUNCTION: ENGINE 0x10AA3E70
	// EQUIVALENT: scheduling: the engine loads both halves of the key before the test of the result of the name read (95.5 %)
	template bool DynamicProperty<short>::ReadText(TextValue const*);
	// FUNCTION: ENGINE 0x10AA3F40
	template DynamicPropertyBase* Factory<DynamicPropertyBase,DynamicProperty<short> >::Create(void*);
	// FUNCTION: ENGINE 0x10AA3F90
	// EQUIVALENT: scheduling: the engine loads both halves of the key before the test of the result of the name read (95.5 %)
	template bool DynamicProperty<int>::ReadText(TextValue const*);
	// FUNCTION: ENGINE 0x10AA4060
	template DynamicPropertyBase* Factory<DynamicPropertyBase,DynamicProperty<int> >::Create(void*);
	// FUNCTION: ENGINE 0x10AA40B0
	// EQUIVALENT: scheduling: the engine loads both halves of the key before the test of the result of the name read (95.5 %)
	template bool DynamicProperty<__int64>::ReadText(TextValue const*);
	// FUNCTION: ENGINE 0x10AA4180
	template void DynamicProperty<__int64>::WriteText(TextValue*);
	// FUNCTION: ENGINE 0x10AA4310
	template bool DynamicProperty<__int64>::ReadBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA4370
	template bool DynamicProperty<__int64>::WriteBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA43F0
	template DynamicPropertyBase* Factory<DynamicPropertyBase,DynamicProperty<__int64> >::Create(void*);
	// FUNCTION: ENGINE 0x10AA45B0
	template CommandDelegate<unsigned char>::CommandDelegate(Command0<unsigned char>*, Command1<void,unsigned char>*);
	// FUNCTION: ENGINE 0x10AA4630
	template unsigned char CommandDelegate<unsigned char>::Get();
	// FUNCTION: ENGINE 0x10AA4640
	template void CommandDelegate<unsigned char>::Set(unsigned char);
	// FUNCTION: ENGINE 0x10AA4650
	template MetaTypeBase* CommandDelegate<unsigned char>::GetMetaType();
	// FUNCTION: ENGINE 0x10AA4670
	template CommandDelegate<unsigned char>::~CommandDelegate();
	// FUNCTION: ENGINE 0x10AA46A0
	template Command0<unsigned char>* CommandMember0Const<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,unsigned char>::Clone();
	// FUNCTION: ENGINE 0x10AA46E0
	template CommandDelegate<unsigned short>::CommandDelegate(Command0<unsigned short>*, Command1<void,unsigned short>*);
	// FUNCTION: ENGINE 0x10AA4760
	template unsigned short CommandDelegate<unsigned short>::Get();
	// FUNCTION: ENGINE 0x10AA4770
	template void CommandDelegate<unsigned short>::Set(unsigned short);
	// FUNCTION: ENGINE 0x10AA4780
	template MetaTypeBase* CommandDelegate<unsigned short>::GetMetaType();
	// FUNCTION: ENGINE 0x10AA47D0
	template Command0<unsigned short>* CommandMember0Const<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,unsigned short>::Clone();
	// FUNCTION: ENGINE 0x10AA4810
	template CommandDelegate<unsigned int>::CommandDelegate(Command0<unsigned int>*, Command1<void,unsigned int>*);
	// FUNCTION: ENGINE 0x10AA4870
	template unsigned int CommandDelegate<unsigned int>::Get();
	// FUNCTION: ENGINE 0x10AA4880
	template void CommandDelegate<unsigned int>::Set(unsigned int);
	// FUNCTION: ENGINE 0x10AA4890
	template MetaTypeBase* CommandDelegate<unsigned int>::GetMetaType();
	// FUNCTION: ENGINE 0x10AA48B0
	template CommandDelegate<unsigned int>::~CommandDelegate();
	// FUNCTION: ENGINE 0x10AA48E0
	template Command0<unsigned int>* CommandMember0Const<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,unsigned int>::Clone();
	// FUNCTION: ENGINE 0x10AA4920
	template CommandDelegate<unsigned __int64>::CommandDelegate(Command0<unsigned __int64>*, Command1<void,unsigned __int64>*);
	// FUNCTION: ENGINE 0x10AA4980
	template unsigned __int64 CommandDelegate<unsigned __int64>::Get();
	// FUNCTION: ENGINE 0x10AA4990
	template void CommandDelegate<unsigned __int64>::Set(unsigned __int64);
	// FUNCTION: ENGINE 0x10AA49B0
	template MetaTypeBase* CommandDelegate<unsigned __int64>::GetMetaType();
	// FUNCTION: ENGINE 0x10AA49D0
	template CommandDelegate<unsigned __int64>::~CommandDelegate();
	// FUNCTION: ENGINE 0x10AA4A00
	template Command0<unsigned __int64>* CommandMember0Const<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,unsigned __int64>::Clone();
	// FUNCTION: ENGINE 0x10AA4A40
	template CommandDelegate<char>::CommandDelegate(Command0<char>*, Command1<void,char>*);
	// FUNCTION: ENGINE 0x10AA4AC0
	template char CommandDelegate<char>::Get();
	// FUNCTION: ENGINE 0x10AA4AD0
	template void CommandDelegate<char>::Set(char);
	// FUNCTION: ENGINE 0x10AA4AE0
	template MetaTypeBase* CommandDelegate<char>::GetMetaType();
	// FUNCTION: ENGINE 0x10AA4B00
	template CommandDelegate<char>::~CommandDelegate();
	// FUNCTION: ENGINE 0x10AA4B30
	template Command0<char>* CommandMember0Const<DynamicProperty<char>,DynamicProperty<char>,char>::Clone();
	// FUNCTION: ENGINE 0x10AA4B70
	template CommandDelegate<short>::CommandDelegate(Command0<short>*, Command1<void,short>*);
	// FUNCTION: ENGINE 0x10AA4BF0
	template short CommandDelegate<short>::Get();
	// FUNCTION: ENGINE 0x10AA4C00
	template void CommandDelegate<short>::Set(short);
	// FUNCTION: ENGINE 0x10AA4C10
	template MetaTypeBase* CommandDelegate<short>::GetMetaType();
	// FUNCTION: ENGINE 0x10AA4C30
	template CommandDelegate<short>::~CommandDelegate();
	// FUNCTION: ENGINE 0x10AA4C60
	template Command0<short>* CommandMember0Const<DynamicProperty<short>,DynamicProperty<short>,short>::Clone();
	// FUNCTION: ENGINE 0x10AA4CA0
	template CommandDelegate<int>::CommandDelegate(Command0<int>*, Command1<void,int>*);
	// FUNCTION: ENGINE 0x10AA4D20
	template int CommandDelegate<int>::Get();
	// FUNCTION: ENGINE 0x10AA4D30
	template void CommandDelegate<int>::Set(int);
	// FUNCTION: ENGINE 0x10AA4D40
	template MetaTypeBase* CommandDelegate<int>::GetMetaType();
	// FUNCTION: ENGINE 0x10AA4D60
	template CommandDelegate<int>::~CommandDelegate();
	// FUNCTION: ENGINE 0x10AA4D90
	template Command0<int>* CommandMember0Const<DynamicProperty<int>,DynamicProperty<int>,int>::Clone();
	// FUNCTION: ENGINE 0x10AA4DD0
	template CommandDelegate<__int64>::CommandDelegate(Command0<__int64>*, Command1<void,__int64>*);
	// FUNCTION: ENGINE 0x10AA4E30
	template __int64 CommandDelegate<__int64>::Get();
	// FUNCTION: ENGINE 0x10AA4E40
	template void CommandDelegate<__int64>::Set(__int64);
	// FUNCTION: ENGINE 0x10AA4E60
	template MetaTypeBase* CommandDelegate<__int64>::GetMetaType();
	// FUNCTION: ENGINE 0x10AA4E80
	template CommandDelegate<__int64>::~CommandDelegate();
	// FUNCTION: ENGINE 0x10AA4EB0
	template Command0<__int64>* CommandMember0Const<DynamicProperty<__int64>,DynamicProperty<__int64>,__int64>::Clone();
	// FUNCTION: ENGINE 0x10AA5170
	template Command1<void,unsigned char>* CommandMember1<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,void,unsigned char>::Create(DynamicProperty<unsigned char>*, CommandMember1<DynamicProperty<unsigned char>,DynamicProperty<unsigned char>,void,unsigned char>::Function);
	// FUNCTION: ENGINE 0x10AA5360
	template Command1<void,unsigned short>* CommandMember1<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,void,unsigned short>::Create(DynamicProperty<unsigned short>*, CommandMember1<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,void,unsigned short>::Function);
	// FUNCTION: ENGINE 0x10AA5390
	template Command1<void,unsigned int>* CommandMember1<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,void,unsigned int>::Create(DynamicProperty<unsigned int>*, CommandMember1<DynamicProperty<unsigned int>,DynamicProperty<unsigned int>,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AA53C0
	template Command1<void,unsigned __int64>* CommandMember1<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,void,unsigned __int64>::Create(DynamicProperty<unsigned __int64>*, CommandMember1<DynamicProperty<unsigned __int64>,DynamicProperty<unsigned __int64>,void,unsigned __int64>::Function);
	// FUNCTION: ENGINE 0x10AA53F0
	template Command1<void,char>* CommandMember1<DynamicProperty<char>,DynamicProperty<char>,void,char>::Create(DynamicProperty<char>*, CommandMember1<DynamicProperty<char>,DynamicProperty<char>,void,char>::Function);
	// FUNCTION: ENGINE 0x10AA5420
	template Command1<void,short>* CommandMember1<DynamicProperty<short>,DynamicProperty<short>,void,short>::Create(DynamicProperty<short>*, CommandMember1<DynamicProperty<short>,DynamicProperty<short>,void,short>::Function);
	// FUNCTION: ENGINE 0x10AA5450
	template Command1<void,int>* CommandMember1<DynamicProperty<int>,DynamicProperty<int>,void,int>::Create(DynamicProperty<int>*, CommandMember1<DynamicProperty<int>,DynamicProperty<int>,void,int>::Function);
	// FUNCTION: ENGINE 0x10AA5480
	template Command1<void,__int64>* CommandMember1<DynamicProperty<__int64>,DynamicProperty<__int64>,void,__int64>::Create(DynamicProperty<__int64>*, CommandMember1<DynamicProperty<__int64>,DynamicProperty<__int64>,void,__int64>::Function);
	// FUNCTION: ENGINE 0x10AA54F0
	template void DynamicProperty<DynamicArray<String,unsigned short> >::SetName(Name<CaseSensitive64BitKey>);
	// FUNCTION: ENGINE 0x10AA5510
	template Name<CaseSensitive64BitKey> DynamicProperty<DynamicArray<String,unsigned short> >::GetName() const;
	// FUNCTION: ENGINE 0x10AA5530
	template void const* DynamicProperty<DynamicArray<String,unsigned short> >::GetValuePointer() const;
	// FUNCTION: ENGINE 0x10AA5540
	template void* DynamicProperty<DynamicArray<String,unsigned short> >::GetValuePointer();
	// FUNCTION: ENGINE 0x10AA5550
	template MetaTypeBase* DynamicProperty<DynamicArray<String,unsigned short> >::GetMetaType() const;
	// FUNCTION: ENGINE 0x10AA5580
	template Command0<DynamicArray<String,unsigned short> >::~Command0();
	// FUNCTION: ENGINE 0x10AA5590
	template Command1<void,DynamicArray<String,unsigned short> >::~Command1();
	// FUNCTION: ENGINE 0x10AA5620
	template Command0<DynamicArray<String,unsigned short> >::Command0();
	// FUNCTION: ENGINE 0x10AA5640
	template char const* CommandDelegate<DynamicArray<String,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AA5650
	template char const* CommandMember0Const<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,DynamicArray<String,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AA5660
	template Command1<void,DynamicArray<String,unsigned short> >::Command1();
	// FUNCTION: ENGINE 0x10AA5670
	template char const* CommandMember1<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,void,DynamicArray<String,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AA5680
	template void* CommandDelegate<DynamicArray<String,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA56A0
	template void* CommandMember0Const<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,DynamicArray<String,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA56C0
	template CommandMember0Const<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,DynamicArray<String,unsigned short> >::CommandMember0Const(DynamicProperty<DynamicArray<String,unsigned short> >*, CommandMember0Const<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,DynamicArray<String,unsigned short> >::Function);
	// FUNCTION: ENGINE 0x10AA56E0
	template CommandMember0Const<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,DynamicArray<String,unsigned short> >::~CommandMember0Const();
	// FUNCTION: ENGINE 0x10AA56F0
	template void CommandMember0Const<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,DynamicArray<String,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA5740
	template Command0<DynamicArray<String,unsigned short> >* CommandMember0Const<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,DynamicArray<String,unsigned short> >::Create(DynamicProperty<DynamicArray<String,unsigned short> >*, CommandMember0Const<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,DynamicArray<String,unsigned short> >::Function);
	// FUNCTION: ENGINE 0x10AA5770
	template void* CommandMember1<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,void,DynamicArray<String,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA5790
	template CommandMember1<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,void,DynamicArray<String,unsigned short> >::CommandMember1(DynamicProperty<DynamicArray<String,unsigned short> >*, CommandMember1<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,void,DynamicArray<String,unsigned short> >::Function);
	// FUNCTION: ENGINE 0x10AA57B0
	template CommandMember1<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,void,DynamicArray<String,unsigned short> >::~CommandMember1();
	// FUNCTION: ENGINE 0x10AA57C0
	template void CommandMember1<DynamicProperty<unsigned short>,DynamicProperty<unsigned short>,void,unsigned short>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA5810
	template DynamicProperty<DynamicArray<String,unsigned short> >::~DynamicProperty();
	// FUNCTION: ENGINE 0x10AA5860
	template CommandDelegate<DynamicArray<String,unsigned short> >::CommandDelegate(Command0<DynamicArray<String,unsigned short> >*, Command1<void,DynamicArray<String,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AA58C0
	template MetaTypeBase* CommandDelegate<DynamicArray<String,unsigned short> >::GetMetaType();
	// FUNCTION: ENGINE 0x10AA5910
	template DynamicArray<String,unsigned short> CommandDelegate<DynamicArray<String,unsigned short> >::Get();
	// FUNCTION: ENGINE 0x10AA5930
	template Command0<DynamicArray<String,unsigned short> >* CommandMember0Const<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,DynamicArray<String,unsigned short> >::Clone();
	// FUNCTION: ENGINE 0x10AA59C0
	template Command1<void,DynamicArray<String,unsigned short> >* CommandMember1<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,void,DynamicArray<String,unsigned short> >::Create(DynamicProperty<DynamicArray<String,unsigned short> >*, CommandMember1<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,void,DynamicArray<String,unsigned short> >::Function);
	// FUNCTION: ENGINE 0x10AA5A30
	template void DynamicProperty<DynamicArray<float,unsigned short> >::SetName(Name<CaseSensitive64BitKey>);
	// FUNCTION: ENGINE 0x10AA5A50
	template Name<CaseSensitive64BitKey> DynamicProperty<DynamicArray<float,unsigned short> >::GetName() const;
	// FUNCTION: ENGINE 0x10AA5A70
	template void const* DynamicProperty<DynamicArray<float,unsigned short> >::GetValuePointer() const;
	// FUNCTION: ENGINE 0x10AA5A80
	template void* DynamicProperty<DynamicArray<float,unsigned short> >::GetValuePointer();
	// FUNCTION: ENGINE 0x10AA5A90
	template MetaTypeBase* DynamicProperty<DynamicArray<float,unsigned short> >::GetMetaType() const;
	// FUNCTION: ENGINE 0x10AA5AC0
	template Command0<DynamicArray<float,unsigned short> >::~Command0();
	// FUNCTION: ENGINE 0x10AA5AD0
	template Command1<void,DynamicArray<float,unsigned short> >::~Command1();
	// FUNCTION: ENGINE 0x10AA5B60
	template Command0<DynamicArray<float,unsigned short> >::Command0();
	// FUNCTION: ENGINE 0x10AA5B90
	template char const* CommandDelegate<DynamicArray<float,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AA5BA0
	template char const* CommandMember0Const<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,DynamicArray<float,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AA5BB0
	template Command1<void,DynamicArray<float,unsigned short> >::Command1();
	// FUNCTION: ENGINE 0x10AA5BC0
	template char const* CommandMember1<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,void,DynamicArray<float,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AA5BD0
	template void* CommandDelegate<DynamicArray<float,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA5BF0
	template DelegateProperty<DynamicArray<float,unsigned short> >::DelegateProperty();
	// FUNCTION: ENGINE 0x10AA5C00
	template MetaTypeBase* DelegateProperty<DynamicArray<float,unsigned short> >::GetMetaType();
	// FUNCTION: ENGINE 0x10AA5C40
	template void* CommandMember0Const<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,DynamicArray<float,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA5C60
	template CommandMember0Const<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,DynamicArray<float,unsigned short> >::CommandMember0Const(DynamicProperty<DynamicArray<float,unsigned short> >*, CommandMember0Const<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,DynamicArray<float,unsigned short> >::Function);
	// FUNCTION: ENGINE 0x10AA5C80
	template CommandMember0Const<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,DynamicArray<float,unsigned short> >::~CommandMember0Const();
	// FUNCTION: ENGINE 0x10AA5C90
	template void CommandMember0Const<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,DynamicArray<float,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA5CE0
	template void DynamicArray<float,unsigned short>::Clear();
	// FUNCTION: ENGINE 0x10AA5D20
	template Command0<DynamicArray<float,unsigned short> >* CommandMember0Const<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,DynamicArray<float,unsigned short> >::Create(DynamicProperty<DynamicArray<float,unsigned short> >*, CommandMember0Const<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,DynamicArray<float,unsigned short> >::Function);
	// FUNCTION: ENGINE 0x10AA5D50
	template void* CommandMember1<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,void,DynamicArray<float,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA5D70
	template CommandMember1<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,void,DynamicArray<float,unsigned short> >::CommandMember1(DynamicProperty<DynamicArray<float,unsigned short> >*, CommandMember1<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,void,DynamicArray<float,unsigned short> >::Function);
	// FUNCTION: ENGINE 0x10AA5D90
	template CommandMember1<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,void,DynamicArray<float,unsigned short> >::~CommandMember1();
	// FUNCTION: ENGINE 0x10AA5DA0
	template void CommandMember1<DynamicProperty<DynamicArray<String,unsigned short> >,DynamicProperty<DynamicArray<String,unsigned short> >,void,DynamicArray<String,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA5DF0
	template DynamicProperty<DynamicArray<float,unsigned short> >::~DynamicProperty();
	// FUNCTION: ENGINE 0x10AA5E50
	template CommandDelegate<DynamicArray<float,unsigned short> >::CommandDelegate(Command0<DynamicArray<float,unsigned short> >*, Command1<void,DynamicArray<float,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AA5ED0
	template MetaTypeBase* CommandDelegate<DynamicArray<float,unsigned short> >::GetMetaType();
	// FUNCTION: ENGINE 0x10AA5F20
	template DynamicArray<float,unsigned short> CommandDelegate<DynamicArray<float,unsigned short> >::Get();
	// FUNCTION: ENGINE 0x10AA5F40
	template Command0<DynamicArray<float,unsigned short> >* CommandMember0Const<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,DynamicArray<float,unsigned short> >::Clone();
	// FUNCTION: ENGINE 0x10AA5F80
	template void om::WriteText(TextValue*, DynamicArray<float,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AA6080
	template bool om::WriteBinary(BinaryStream*, DynamicArray<float,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AA6180
	template void DynamicArray<float,unsigned short>::Reserve(unsigned short);
	// FUNCTION: ENGINE 0x10AA6230
	template Command1<void,DynamicArray<float,unsigned short> >* CommandMember1<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,void,DynamicArray<float,unsigned short> >::Create(DynamicProperty<DynamicArray<float,unsigned short> >*, CommandMember1<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,void,DynamicArray<float,unsigned short> >::Function);
	// FUNCTION: ENGINE 0x10AA62A0
	template void DynamicProperty<DynamicArray<unsigned int,unsigned short> >::SetName(Name<CaseSensitive64BitKey>);
	// FUNCTION: ENGINE 0x10AA62C0
	template Name<CaseSensitive64BitKey> DynamicProperty<DynamicArray<unsigned int,unsigned short> >::GetName() const;
	// FUNCTION: ENGINE 0x10AA62E0
	template void const* DynamicProperty<DynamicArray<unsigned int,unsigned short> >::GetValuePointer() const;
	// FUNCTION: ENGINE 0x10AA62F0
	template void* DynamicProperty<DynamicArray<unsigned int,unsigned short> >::GetValuePointer();
	// FUNCTION: ENGINE 0x10AA6300
	template MetaTypeBase* DynamicProperty<DynamicArray<unsigned int,unsigned short> >::GetMetaType() const;
	// FUNCTION: ENGINE 0x10AA6330
	template Command0<DynamicArray<unsigned int,unsigned short> >::~Command0();
	// FUNCTION: ENGINE 0x10AA6340
	template Command1<void,DynamicArray<unsigned int,unsigned short> >::~Command1();
	// FUNCTION: ENGINE 0x10AA63D0
	template Command0<DynamicArray<unsigned int,unsigned short> >::Command0();
	// FUNCTION: ENGINE 0x10AA6400
	template char const* CommandDelegate<DynamicArray<unsigned int,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AA6410
	template char const* CommandMember0Const<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicArray<unsigned int,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AA6420
	template Command1<void,DynamicArray<unsigned int,unsigned short> >::Command1();
	// FUNCTION: ENGINE 0x10AA6430
	template float const& DynamicArray<float,unsigned short>::operator[](unsigned short) const;
	// FUNCTION: ENGINE 0x10AA6440
	template char const* CommandMember1<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,void,DynamicArray<unsigned int,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AA6450
	template void* CommandDelegate<DynamicArray<unsigned int,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA6470
	template DelegateProperty<DynamicArray<unsigned int,unsigned short> >::DelegateProperty();
	// FUNCTION: ENGINE 0x10AA6480
	template MetaTypeBase* DelegateProperty<DynamicArray<unsigned int,unsigned short> >::GetMetaType();
	// FUNCTION: ENGINE 0x10AA64C0
	template void* CommandMember0Const<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicArray<unsigned int,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA64E0
	template CommandMember0Const<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicArray<unsigned int,unsigned short> >::CommandMember0Const(DynamicProperty<DynamicArray<unsigned int,unsigned short> >*, CommandMember0Const<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicArray<unsigned int,unsigned short> >::Function);
	// FUNCTION: ENGINE 0x10AA6500
	template CommandMember0Const<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicArray<unsigned int,unsigned short> >::~CommandMember0Const();
	// FUNCTION: ENGINE 0x10AA6510
	template void CommandMember0Const<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicArray<unsigned int,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA6560
	template void DynamicArray<unsigned int,unsigned short>::Clear();
	// FUNCTION: ENGINE 0x10AA6590
	template unsigned int const& DynamicArray<unsigned int,unsigned short>::operator[](unsigned short) const;
	// FUNCTION: ENGINE 0x10AA65B0
	template Command0<DynamicArray<unsigned int,unsigned short> >* CommandMember0Const<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicArray<unsigned int,unsigned short> >::Create(DynamicProperty<DynamicArray<unsigned int,unsigned short> >*, CommandMember0Const<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicArray<unsigned int,unsigned short> >::Function);
	// FUNCTION: ENGINE 0x10AA65E0
	template void* CommandMember1<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,void,DynamicArray<unsigned int,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AA6600
	template CommandMember1<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,void,DynamicArray<unsigned int,unsigned short> >::CommandMember1(DynamicProperty<DynamicArray<unsigned int,unsigned short> >*, CommandMember1<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,void,DynamicArray<unsigned int,unsigned short> >::Function);
	// FUNCTION: ENGINE 0x10AA6620
	template CommandMember1<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,void,DynamicArray<unsigned int,unsigned short> >::~CommandMember1();
	// FUNCTION: ENGINE 0x10AA6630
	template void CommandMember1<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,void,DynamicArray<float,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AA6680
	template DynamicProperty<DynamicArray<unsigned int,unsigned short> >::~DynamicProperty();
	// FUNCTION: ENGINE 0x10AA66E0
	template CommandDelegate<DynamicArray<unsigned int,unsigned short> >::CommandDelegate(Command0<DynamicArray<unsigned int,unsigned short> >*, Command1<void,DynamicArray<unsigned int,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AA6760
	template MetaTypeBase* CommandDelegate<DynamicArray<unsigned int,unsigned short> >::GetMetaType();
	// FUNCTION: ENGINE 0x10AA67B0
	template DynamicArray<unsigned int,unsigned short> CommandDelegate<DynamicArray<unsigned int,unsigned short> >::Get();
	// FUNCTION: ENGINE 0x10AA67D0
	template Command0<DynamicArray<unsigned int,unsigned short> >* CommandMember0Const<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicArray<unsigned int,unsigned short> >::Clone();
	// FUNCTION: ENGINE 0x10AA6810
	template void om::WriteText(TextValue*, DynamicArray<unsigned int,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AA6910
	template bool om::WriteBinary(BinaryStream*, DynamicArray<unsigned int,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AA6A30
	template Command1<void,DynamicArray<unsigned int,unsigned short> >* CommandMember1<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,void,DynamicArray<unsigned int,unsigned short> >::Create(DynamicProperty<DynamicArray<unsigned int,unsigned short> >*, CommandMember1<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,void,DynamicArray<unsigned int,unsigned short> >::Function);
	// FUNCTION: ENGINE 0x10AA7010
	template DelegatePropertyBase* DynamicProperty<unsigned char>::CreateDelegate();
	// FUNCTION: ENGINE 0x10AA7080
	template DelegatePropertyBase* DynamicProperty<unsigned short>::CreateDelegate();
	// FUNCTION: ENGINE 0x10AA70E0
	template DelegatePropertyBase* DynamicProperty<unsigned int>::CreateDelegate();
	// FUNCTION: ENGINE 0x10AA7140
	template DelegatePropertyBase* DynamicProperty<unsigned __int64>::CreateDelegate();
	// FUNCTION: ENGINE 0x10AA71A0
	template DelegatePropertyBase* DynamicProperty<char>::CreateDelegate();
	// FUNCTION: ENGINE 0x10AA7200
	template DelegatePropertyBase* DynamicProperty<short>::CreateDelegate();
	// FUNCTION: ENGINE 0x10AA7260
	template DelegatePropertyBase* DynamicProperty<int>::CreateDelegate();
	// FUNCTION: ENGINE 0x10AA72C0
	template DelegatePropertyBase* DynamicProperty<__int64>::CreateDelegate();
	// FUNCTION: ENGINE 0x10AA7320
	template void DynamicProperty<DynamicArray<String,unsigned short> >::WriteToDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA7350
	template void DynamicProperty<DynamicArray<String,unsigned short> >::SetFromPointer2(void const*, unsigned int);
	// FUNCTION: ENGINE 0x10AA7360
	template void DynamicProperty<DynamicArray<String,unsigned short> >::GetValue(void*) const;
	// FUNCTION: ENGINE 0x10AA7370
	template void DynamicProperty<DynamicArray<String,unsigned short> >::WriteText(TextValue*);
	// FUNCTION: ENGINE 0x10AA74E0
	template bool DynamicProperty<DynamicArray<String,unsigned short> >::WriteBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA7540
	template DynamicPropertyBase* Factory<DynamicPropertyBase,DynamicProperty<DynamicArray<String,unsigned short> > >::Create(void*);
	// FUNCTION: ENGINE 0x10AA75A0
	template void DynamicProperty<DynamicArray<float,unsigned short> >::WriteToDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA75D0
	template void DynamicProperty<DynamicArray<float,unsigned short> >::SetFromPointer2(void const*, unsigned int);
	// FUNCTION: ENGINE 0x10AA75E0
	template void DynamicProperty<DynamicArray<float,unsigned short> >::GetValue(void*) const;
	// FUNCTION: ENGINE 0x10AA75F0
	template void DynamicProperty<DynamicArray<float,unsigned short> >::WriteText(TextValue*);
	// FUNCTION: ENGINE 0x10AA7760
	template bool DynamicProperty<DynamicArray<float,unsigned short> >::WriteBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA77C0
	template DynamicPropertyBase* Factory<DynamicPropertyBase,DynamicProperty<DynamicArray<float,unsigned short> > >::Create(void*);
	// FUNCTION: ENGINE 0x10AA7820
	template void DynamicProperty<DynamicArray<unsigned int,unsigned short> >::WriteToDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA7850
	template void DynamicProperty<DynamicArray<unsigned int,unsigned short> >::SetFromPointer2(void const*, unsigned int);
	// FUNCTION: ENGINE 0x10AA7860
	template void DynamicProperty<DynamicArray<unsigned int,unsigned short> >::GetValue(void*) const;
	// FUNCTION: ENGINE 0x10AA7870
	template void DynamicProperty<DynamicArray<unsigned int,unsigned short> >::WriteText(TextValue*);
	// FUNCTION: ENGINE 0x10AA79E0
	template bool DynamicProperty<DynamicArray<unsigned int,unsigned short> >::WriteBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA7A40
	template DynamicPropertyBase* Factory<DynamicPropertyBase,DynamicProperty<DynamicArray<unsigned int,unsigned short> > >::Create(void*);
	// FUNCTION: ENGINE 0x10AA7C30
	template void CommandDelegate<DynamicArray<float,unsigned short> >::Set(DynamicArray<float,unsigned short>);
	// FUNCTION: ENGINE 0x10AA7C70
	template DynamicArray<float,unsigned short> CommandMember0Const<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,DynamicArray<float,unsigned short> >::Call();
	// FUNCTION: ENGINE 0x10AA7CC0
	template void CommandMember1<DynamicProperty<DynamicArray<float,unsigned short> >,DynamicProperty<DynamicArray<float,unsigned short> >,void,DynamicArray<float,unsigned short> >::Call(DynamicArray<float,unsigned short>);
	// FUNCTION: ENGINE 0x10AA7D00
	template bool om::ReadText(TextValue const*, DynamicArray<float,unsigned short>*);
	// FUNCTION: ENGINE 0x10AA7E10
	template bool om::ReadBinary(BinaryStream*, DynamicArray<float,unsigned short>*);
	// FUNCTION: ENGINE 0x10AA7EB0
	template void CommandDelegate<DynamicArray<unsigned int,unsigned short> >::Set(DynamicArray<unsigned int,unsigned short>);
	// FUNCTION: ENGINE 0x10AA7EF0
	template DynamicArray<unsigned int,unsigned short> CommandMember0Const<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicArray<unsigned int,unsigned short> >::Call();
	// FUNCTION: ENGINE 0x10AA7F40
	template void CommandMember1<DynamicProperty<DynamicArray<unsigned int,unsigned short> >,DynamicProperty<DynamicArray<unsigned int,unsigned short> >,void,DynamicArray<unsigned int,unsigned short> >::Call(DynamicArray<unsigned int,unsigned short>);
	// FUNCTION: ENGINE 0x10AA7F80
	template bool om::ReadText(TextValue const*, DynamicArray<unsigned int,unsigned short>*);
	// FUNCTION: ENGINE 0x10AA8090
	template bool om::ReadBinary(BinaryStream*, DynamicArray<unsigned int,unsigned short>*);
	// FUNCTION: ENGINE 0x10AA8130
	template DynamicArray<String,unsigned short> DynamicProperty<DynamicArray<String,unsigned short> >::GetValue() const;
	// FUNCTION: ENGINE 0x10AA81A0
	template DynamicArray<float,unsigned short> DynamicProperty<DynamicArray<float,unsigned short> >::GetValue() const;
	// FUNCTION: ENGINE 0x10AA81C0
	template void DynamicProperty<DynamicArray<float,unsigned short> >::Set(DynamicArray<float,unsigned short>);
	// FUNCTION: ENGINE 0x10AA81F0
	template DynamicArray<unsigned int,unsigned short> DynamicProperty<DynamicArray<unsigned int,unsigned short> >::GetValue() const;
	// FUNCTION: ENGINE 0x10AA8210
	template void DynamicProperty<DynamicArray<unsigned int,unsigned short> >::Set(DynamicArray<unsigned int,unsigned short>);
	// FUNCTION: ENGINE 0x10AA8730
	template void DynamicProperty<DynamicArray<String,unsigned short> >::SetFrom(DynamicPropertyBase*);
	// FUNCTION: ENGINE 0x10AA8750
	template void DynamicProperty<DynamicArray<String,unsigned short> >::ReadFromDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA8770
	template void DynamicProperty<DynamicArray<String,unsigned short> >::SetFromPointer(void const*);
	// FUNCTION: ENGINE 0x10AA8790
	template DelegatePropertyBase* DynamicProperty<DynamicArray<String,unsigned short> >::CreateDelegate();
	// FUNCTION: ENGINE 0x10AA87F0
	// EQUIVALENT: scheduling: the engine loads both halves of the key before the test of the result of the name read (95.5 %)
	template bool DynamicProperty<DynamicArray<String,unsigned short> >::ReadText(TextValue const*);
	// FUNCTION: ENGINE 0x10AA88C0
	template bool DynamicProperty<DynamicArray<String,unsigned short> >::ReadBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA8900
	template void DynamicProperty<DynamicArray<float,unsigned short> >::SetFrom(DynamicPropertyBase*);
	// FUNCTION: ENGINE 0x10AA8920
	template void DynamicProperty<DynamicArray<float,unsigned short> >::ReadFromDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA8940
	template void DynamicProperty<DynamicArray<float,unsigned short> >::SetFromPointer(void const*);
	// FUNCTION: ENGINE 0x10AA8960
	template DelegatePropertyBase* DynamicProperty<DynamicArray<float,unsigned short> >::CreateDelegate();
	// FUNCTION: ENGINE 0x10AA89C0
	// EQUIVALENT: scheduling: the engine loads both halves of the key before the test of the result of the name read (95.5 %)
	template bool DynamicProperty<DynamicArray<float,unsigned short> >::ReadText(TextValue const*);
	// FUNCTION: ENGINE 0x10AA8A90
	template bool DynamicProperty<DynamicArray<float,unsigned short> >::ReadBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AA8AD0
	template void DynamicProperty<DynamicArray<unsigned int,unsigned short> >::SetFrom(DynamicPropertyBase*);
	// FUNCTION: ENGINE 0x10AA8AF0
	template void DynamicProperty<DynamicArray<unsigned int,unsigned short> >::ReadFromDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AA8B10
	template void DynamicProperty<DynamicArray<unsigned int,unsigned short> >::SetFromPointer(void const*);
	// FUNCTION: ENGINE 0x10AA8B30
	template DelegatePropertyBase* DynamicProperty<DynamicArray<unsigned int,unsigned short> >::CreateDelegate();
	// FUNCTION: ENGINE 0x10AA8B90
	// EQUIVALENT: scheduling: the engine loads both halves of the key before the test of the result of the name read (95.5 %)
	template bool DynamicProperty<DynamicArray<unsigned int,unsigned short> >::ReadText(TextValue const*);
	// FUNCTION: ENGINE 0x10AA8C60
	template bool DynamicProperty<DynamicArray<unsigned int,unsigned short> >::ReadBinary(BinaryStream*);
}
