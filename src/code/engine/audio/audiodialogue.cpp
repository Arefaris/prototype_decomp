// The audio dialogue unit (RTTI: engine::AudioDialoguePersonality, AudioDialogueSubtitle, AudioDialogueSound and their
// loaders; 0x10855xxx - 0x1085Bxxx): the instance of the dynamic property of a string that the unit's vftables use. No
// assert path names the unit; the file name is a guess.
#include "code/core/criticalsection.h"
#include "code/engine/audio/audiodialogue.h"
#include "code/om/dynamicarray.h"
#include "code/om/dynamicproperty.h"
#include "code/om/string.h"

#pragma warning(disable: 4661)

namespace om
{
	// The text forms, the binary writer of the string and the delegate's setter are the engine's (0x10857C00, 0x10857CE0,
	// 0x10857B40, 0x108591D0)
	template<> bool DynamicProperty<String>::ReadText(const TextValue* parent);
	template<> void DynamicProperty<String>::WriteText(TextValue* parent);
	template<> bool WriteValueBinary<String>(BinaryStream* stream, const String& value);
	template<> void CommandDelegate<String>::Set(String value);

	// FUNCTION: ENGINE 0x10856240
	// FUNCTION: ENGINE 0x10856260
	// FUNCTION: ENGINE 0x108562F0
	// FUNCTION: ENGINE 0x10857900
	// FUNCTION: ENGINE 0x10857F60
	// FUNCTION: ENGINE 0x10856220
	template char const* DynamicArray<unsigned int,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10857970
	// FUNCTION: ENGINE 0x10857990
	// FUNCTION: ENGINE 0x108579A0
	// FUNCTION: ENGINE 0x108579C0
	// FUNCTION: ENGINE 0x108579E0
	// FUNCTION: ENGINE 0x108579F0
	// FUNCTION: ENGINE 0x10857A00
	// FUNCTION: ENGINE 0x10857A10
	// FUNCTION: ENGINE 0x10857A20
	// FUNCTION: ENGINE 0x10857A40
	// FUNCTION: ENGINE 0x10857A50
	// FUNCTION: ENGINE 0x10857A60
	// FUNCTION: ENGINE 0x10857A80
	// FUNCTION: ENGINE 0x10857AA0
	// FUNCTION: ENGINE 0x10857AB0
	// FUNCTION: ENGINE 0x10857AC0
	// FUNCTION: ENGINE 0x10857AD0
	// FUNCTION: ENGINE 0x10857AE0
	// FUNCTION: ENGINE 0x10857B00
	// FUNCTION: ENGINE 0x10857B10
	// FUNCTION: ENGINE 0x10857B20
	// FUNCTION: ENGINE 0x10857B30
	// FUNCTION: ENGINE 0x10857B90
	// FUNCTION: ENGINE 0x10857BB0
	// FUNCTION: ENGINE 0x10857BE0
	// FUNCTION: ENGINE 0x10857E60
	// FUNCTION: ENGINE 0x10857EA0
	// FUNCTION: ENGINE 0x10857F00
	// FUNCTION: ENGINE 0x10857F30
	// FUNCTION: ENGINE 0x10857FA0
	// FUNCTION: ENGINE 0x10857FC0
	// FUNCTION: ENGINE 0x10857FE0
	// FUNCTION: ENGINE 0x10858020
	// FUNCTION: ENGINE 0x10858030
	// FUNCTION: ENGINE 0x10858050
	// FUNCTION: ENGINE 0x10858080
	// FUNCTION: ENGINE 0x108580B0
	// FUNCTION: ENGINE 0x108580D0
	// FUNCTION: ENGINE 0x108580F0
	// FUNCTION: ENGINE 0x10858120
	// FUNCTION: ENGINE 0x10858130
	// FUNCTION: ENGINE 0x10858150
	// FUNCTION: ENGINE 0x10859150
	// FUNCTION: ENGINE 0x108591B0
	// FUNCTION: ENGINE 0x10859200
	// FUNCTION: ENGINE 0x10859220
	// FUNCTION: ENGINE 0x10859250
	// FUNCTION: ENGINE 0x10859290
	// FUNCTION: ENGINE 0x108592E0
	// FUNCTION: ENGINE 0x10859E00
	template void* DynamicProperty<String>::operator new(size_t);
	template DynamicProperty<String>::~DynamicProperty();
	template void DynamicProperty<String>::SetName(Name<CaseSensitive64BitKey>);
	template void DynamicProperty<String>::SetFromPointer2(void const*, unsigned int);
	template Name<CaseSensitive64BitKey> DynamicProperty<String>::GetName() const;
	template void DynamicProperty<String>::GetValue(void*) const;
	template void const* DynamicProperty<String>::GetValuePointer() const;
	template void* DynamicProperty<String>::GetValuePointer();
	template MetaTypeBase* DynamicProperty<String>::GetMetaType() const;
	template void DynamicProperty<String>::operator delete(void*);
	template CommandMember0Const<DynamicProperty<String>,DynamicProperty<String>,String>::~CommandMember0Const();
	template Owned<Command1<void,String> >::Owned(Command1<void,String>*);
	template Owned<Command1<void,String> >::~Owned();
	template Owned<Command0<String> >::Owned(Command0<String>*);
	template Owned<Command0<String> >::~Owned();
	template Command0<String>::Command0();
	template void DynamicProperty<String>::Set(String);
	template char const* CommandDelegate<String>::AllocationTag();
	template char const* CommandMember0Const<DynamicProperty<String>,DynamicProperty<String>,String>::AllocationTag();
	template Command1<void,String>::Command1();
	template char const* CommandMember1<DynamicProperty<String>,DynamicProperty<String>,void,String>::AllocationTag();
	template void DynamicProperty<String>::SetFrom(DynamicPropertyBase*);
	template void DynamicProperty<String>::WriteToDelegate(DelegatePropertyBase*);
	template void DynamicProperty<String>::ReadFromDelegate(DelegatePropertyBase*);
	template void DynamicProperty<String>::SetFromPointer(void const*);
	template bool DynamicProperty<String>::ReadBinary(BinaryStream*);
	template bool DynamicProperty<String>::WriteBinary(BinaryStream*);
	template void* CommandDelegate<String>::operator new(size_t);
	template void* CommandMember0Const<DynamicProperty<String>,DynamicProperty<String>,String>::operator new(size_t);
	template CommandMember0Const<DynamicProperty<String>,DynamicProperty<String>,String>::CommandMember0Const(DynamicProperty<String>*, CommandMember0Const<DynamicProperty<String>,DynamicProperty<String>,String>::Function);
	template String CommandMember0Const<DynamicProperty<String>,DynamicProperty<String>,String>::Call();
	template Command0<String>::~Command0();
	template void CommandMember0Const<DynamicProperty<String>,DynamicProperty<String>,String>::operator delete(void*);
	template Command0<String>* CommandMember0Const<DynamicProperty<String>,DynamicProperty<String>,String>::Create(DynamicProperty<String>*, CommandMember0Const<DynamicProperty<String>,DynamicProperty<String>,String>::Function);
	template void* CommandMember1<DynamicProperty<String>,DynamicProperty<String>,void,String>::operator new(size_t);
	template CommandMember1<DynamicProperty<String>,DynamicProperty<String>,void,String>::CommandMember1(DynamicProperty<String>*, CommandMember1<DynamicProperty<String>,DynamicProperty<String>,void,String>::Function);
	template void CommandMember1<DynamicProperty<String>,DynamicProperty<String>,void,String>::Call(String);
	template void CommandMember1<DynamicProperty<String>,DynamicProperty<String>,void,String>::operator delete(void*);
	template CommandDelegate<String>::CommandDelegate(Command0<String>*, Command1<void,String>*);
	template String CommandDelegate<String>::Get();
	template MetaTypeBase* CommandDelegate<String>::GetMetaType();
	template Command1<void,String>* CommandMember1<DynamicProperty<String>,DynamicProperty<String>,void,String>::Create(DynamicProperty<String>*, CommandMember1<DynamicProperty<String>,DynamicProperty<String>,void,String>::Function);
	template DelegatePropertyBase* DynamicProperty<String>::CreateDelegate();
	template DynamicProperty<String>::DynamicProperty(const ClassName&, String);
}

namespace engine
{
	// FUNCTION: ENGINE 0x10856410
	// FUNCTION: ENGINE 0x10856470
	// FUNCTION: ENGINE 0x108564B0
	// FUNCTION: ENGINE 0x10856450
	// FUNCTION: ENGINE 0x10856490
	// FUNCTION: ENGINE 0x10858280
	// FUNCTION: ENGINE 0x10857880
	// FUNCTION: ENGINE 0x10858260
	// FUNCTION: ENGINE 0x10855820
	const char* AudioDialoguePersonalityLoader::AllocationTag()
	{
		return "";
	}

	// The engine's constructors (0x10858230, 0x10856620) store the reference count before it pushes the address of the lock, this one
	// behind it (78.3 %): it is neither annotated nor mapped and only makes the compiler emit the vftable and the
	// destructors the matching functions below belong to
	AudioDialogueSubtitleLoader::AudioDialogueSubtitleLoader()
	{
	}

	// FUNCTION: ENGINE 0x10856280
	const char* AudioDialogueSubtitleLoader::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10856510
	// FUNCTION: ENGINE 0x10856650
	// FUNCTION: ENGINE 0x10855880
	const char* AudioDialogueSubtitle::AllocationTag()
	{
		return "";
	}

	// The loaders as the registry makes them (a helper to keep the constructors and the destructors out of line)
	content::ObjectLoader2* MakeDialogueLoader(int kind)
	{
		if (kind == 2)
		{
			return (content::ObjectLoader2*)new AudioDialogueSubtitle;
		}
		if (kind == 1)
		{
			return new AudioDialogueSubtitleLoader;
		}
		return new AudioDialoguePersonalityLoader;
	}
}
