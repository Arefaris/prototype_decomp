// The audio library's global settings and sound groups (engine::AudioGlobalSettings, engine::SoundGroup; 0x108C8E00 -
// 0x108CE800): the accessors the reflection binds as properties and the om library's template instances for them.
#include "code/engine/audio/audioglobalsettings.h"
#include "code/om/delegate.h"
#include "code/om/metaclass.h"
#include "code/om/metamethod.h"
#include "code/om/metaproperty.h"
#include "code/om/textvalue.h"

#pragma warning(disable: 4661)

namespace engine
{
	SoundGroup::SoundGroup() :
		maxSounds(1),
		maxSoundsPerInstance(1),
		interruptList(),
		name()
	{
	}

	SoundGroup::SoundGroup(const SoundGroup& other) :
		maxSounds(other.maxSounds),
		maxSoundsPerInstance(other.maxSoundsPerInstance),
		interruptList(other.interruptList),
		name(other.name)
	{
	}

	SoundGroup::~SoundGroup()
	{
	}

	const om::String& SoundGroup::GetName() const
	{
		return name;
	}

	void SoundGroup::SetName(const om::String& newName)
	{
		name = newName;
	}

	const unsigned int& SoundGroup::GetMaxSounds() const
	{
		return maxSounds;
	}

	void SoundGroup::SetMaxSounds(const unsigned int& newMaxSounds)
	{
		maxSounds = newMaxSounds;
	}

	const unsigned int& SoundGroup::GetMaxSoundsPerInstance() const
	{
		return maxSoundsPerInstance;
	}

	void SoundGroup::SetMaxSoundsPerInstance(const unsigned int& newMaxSoundsPerInstance)
	{
		maxSoundsPerInstance = newMaxSoundsPerInstance;
	}

	const om::DynamicArray<om::String, unsigned short>& SoundGroup::GetInterruptList() const
	{
		return interruptList;
	}

	void SoundGroup::SetInterruptList(const om::DynamicArray<om::String, unsigned short>& newInterruptList)
	{
		interruptList = newInterruptList;
	}

	const float& AudioGlobalSettings::GetListenerOffset() const
	{
		return listenerOffset;
	}

	void AudioGlobalSettings::SetListenerOffset(const float& newListenerOffset)
	{
		listenerOffset = newListenerOffset;
	}

	const float& AudioGlobalSettings::GetReverbDistanceFactor() const
	{
		return reverbDistanceFactor;
	}

	void AudioGlobalSettings::SetReverbDistanceFactor(const float& newReverbDistanceFactor)
	{
		reverbDistanceFactor = newReverbDistanceFactor;
	}

	const om::DynamicArray<SoundGroup, unsigned short>& AudioGlobalSettings::GetSoundGroups() const
	{
		return soundGroups;
	}

	void AudioGlobalSettings::SetSoundGroups(const om::DynamicArray<SoundGroup, unsigned short>& newSoundGroups)
	{
		soundGroups = newSoundGroups;
	}
}

namespace om
{
	// The text and binary forms of the arrays, in this unit (0x108CAB10 and on; not reconstructed, the engine's are used)
	bool ReadText(const TextValue* text, DynamicArray<String, unsigned short>* value);
	void WriteText(TextValue* text, const DynamicArray<String, unsigned short>& value);
	bool ReadBinary(BinaryStream* stream, DynamicArray<String, unsigned short>* value);
	bool WriteBinary(BinaryStream* stream, const DynamicArray<String, unsigned short>& value);
	bool ReadText(const TextValue* text, DynamicArray<engine::SoundGroup, unsigned short>* value);
	void WriteText(TextValue* text, const DynamicArray<engine::SoundGroup, unsigned short>& value);
	bool ReadBinary(BinaryStream* stream, DynamicArray<engine::SoundGroup, unsigned short>* value);
	bool WriteBinary(BinaryStream* stream, const DynamicArray<engine::SoundGroup, unsigned short>& value);

	// Not reconstructed yet (declared only: the engine's copies are used)
	template<> bool MetaProperty<const String&>::SetText(const TextValue* text, void* object);
	template<> void MetaProperty<const String&>::GetBinary(BinaryStream* stream, void* object);
	template<> bool MetaProperty<const DynamicArray<String, unsigned short>&>::SetText(const TextValue* text, void* object);
	template<> bool MetaProperty<const DynamicArray<String, unsigned short>&>::SetBinary(BinaryStream* stream, void* object);
	template<> bool MetaProperty<const DynamicArray<engine::SoundGroup, unsigned short>&>::SetText(const TextValue* text, void* object);
	template<> void MetaProperty<const DynamicArray<engine::SoundGroup, unsigned short>&>::GetText(TextValue* text, void* object);
	template<> bool MetaProperty<const DynamicArray<engine::SoundGroup, unsigned short>&>::SetBinary(BinaryStream* stream, void* object);

	template<> void DelegateMetaProperty<const DynamicArray<String, unsigned short>&>::Set(DynamicArray<String, unsigned short> value);
	template<> void DelegateMetaProperty<const DynamicArray<engine::SoundGroup, unsigned short>&>::Set(DynamicArray<engine::SoundGroup, unsigned short> value);

	template class DynamicArray<String, unsigned short>;
	template class DynamicArray<engine::SoundGroup, unsigned short>;
	template class MetaClass<engine::SoundGroup>;
	template class MetaClass<engine::AudioGlobalSettings>;
	template class MetaMethod1<engine::SoundGroup, engine::SoundGroup, void, const String&>;
	template class MetaMethod0Const<engine::SoundGroup, engine::SoundGroup, const String&>;
	template class MetaMethod1<engine::SoundGroup, engine::SoundGroup, void, const unsigned int&>;
	template class MetaMethod0Const<engine::SoundGroup, engine::SoundGroup, const unsigned int&>;
	template class MetaMethod1<engine::SoundGroup, engine::SoundGroup, void, const DynamicArray<String, unsigned short>&>;
	template class MetaMethod0Const<engine::SoundGroup, engine::SoundGroup, const DynamicArray<String, unsigned short>&>;
	template class MetaMethod1<engine::AudioGlobalSettings, engine::AudioGlobalSettings, void, const float&>;
	template class MetaMethod0Const<engine::AudioGlobalSettings, engine::AudioGlobalSettings, const float&>;
	template class MetaMethod1<engine::AudioGlobalSettings, engine::AudioGlobalSettings, void, const DynamicArray<engine::SoundGroup, unsigned short>&>;
	template class MetaMethod0Const<engine::AudioGlobalSettings, engine::AudioGlobalSettings, const DynamicArray<engine::SoundGroup, unsigned short>&>;
	template class MetaProperty<const String&>;
	template class MetaProperty<const unsigned int&>;
	template class MetaProperty<const float&>;
	template class MetaProperty<const DynamicArray<String, unsigned short>&>;
	template class MetaProperty<const DynamicArray<engine::SoundGroup, unsigned short>&>;
	template class DelegateMetaProperty<const String&>;
	template class DelegateMetaProperty<const unsigned int&>;
	template class DelegateMetaProperty<const float&>;
	template class DelegateMetaProperty<const DynamicArray<String, unsigned short>&>;
	template class DelegateMetaProperty<const DynamicArray<engine::SoundGroup, unsigned short>&>;
	template class Garbage<String>;
	template class Garbage<DynamicArray<String, unsigned short> >;
	template class Garbage<DynamicArray<engine::SoundGroup, unsigned short> >;
}

// ---- annotations of the functions mapped in symbols.txt (generated) ----

// FUNCTION: ENGINE 0x108C8E40 @ void om::DelegateMetaProperty<om::DynamicArray<om::String,unsigned short> const &>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C8E70 @ unsigned int const & engine::SoundGroup::GetMaxSounds(void)const 
// FUNCTION: ENGINE 0x108C8E80 @ void engine::SoundGroup::SetMaxSounds(unsigned int const &)
// FUNCTION: ENGINE 0x108C8E90 @ unsigned int const & engine::SoundGroup::GetMaxSoundsPerInstance(void)const 
// FUNCTION: ENGINE 0x108C8EA0 @ void engine::SoundGroup::SetMaxSoundsPerInstance(unsigned int const &)
// FUNCTION: ENGINE 0x108C8EB0 @ om::DynamicArray<om::String,unsigned short> const & engine::SoundGroup::GetInterruptList(void)const 
// FUNCTION: ENGINE 0x108C8EC0 @ om::String const & engine::SoundGroup::GetName(void)const 
// FUNCTION: ENGINE 0x108C8ED0 @ void engine::SoundGroup::SetName(om::String const &)
// FUNCTION: ENGINE 0x108C8EE0 @ float const & engine::AudioGlobalSettings::GetListenerOffset(void)const 
// FUNCTION: ENGINE 0x108C8EF0 @ void engine::AudioGlobalSettings::SetListenerOffset(float const &)
// FUNCTION: ENGINE 0x108C8F00 @ float const & engine::AudioGlobalSettings::GetReverbDistanceFactor(void)const 
// FUNCTION: ENGINE 0x108C8F10 @ void engine::AudioGlobalSettings::SetReverbDistanceFactor(float const &)
// FUNCTION: ENGINE 0x108C8F20 @ om::DynamicArray<engine::SoundGroup,unsigned short> const & engine::AudioGlobalSettings::GetSoundGroups(void)const 
// FUNCTION: ENGINE 0x108C8F40 @ om::MetaClass<engine::SoundGroup>::MetaClass<engine::SoundGroup>(om::Name<om::CaseSensitive64BitKey> const &,om::MetaClassBase *)
// FUNCTION: ENGINE 0x108C8F70 @ type_info const * om::MetaClass<engine::SoundGroup>::GetType(void)
// FUNCTION: ENGINE 0x108C8FA0 @ om::MetaClass<engine::SoundGroup>::~MetaClass<engine::SoundGroup>(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C8FB0 @ void om::MetaClass<engine::SoundGroup>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C8FD0 @ om::MetaClass<engine::AudioGlobalSettings>::MetaClass<engine::AudioGlobalSettings>(om::Name<om::CaseSensitive64BitKey> const &,om::MetaClassBase *)
// FUNCTION: ENGINE 0x108C9000 @ type_info const * om::MetaClass<engine::AudioGlobalSettings>::GetType(void)
// FUNCTION: ENGINE 0x108C9030 @ om::MetaClass<engine::AudioGlobalSettings>::~MetaClass<engine::AudioGlobalSettings>(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C9040 @ void om::MetaClass<engine::AudioGlobalSettings>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C90A0 @ char const * om::Garbage<om::String>::AllocationTag(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C90B0 @ char const * om::Garbage<om::DynamicArray<om::String,unsigned short> >::AllocationTag(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C90C0 @ char const * om::MetaClass<engine::SoundGroup>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C90D0 @ char const * om::MetaClass<engine::AudioGlobalSettings>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C90E0 @ om::MetaProperty<om::String const &>::MetaProperty<om::String const &>(om::MetaTypeBase *,om::MetaClassBase *,om::Name<om::CaseSensitive64BitKey> const &,om::MetaMethod1B
// FUNCTION: ENGINE 0x108C9120 @ type_info const * om::MetaProperty<om::String const &>::GetValueType(void)
// FUNCTION: ENGINE 0x108C9130 @ om::MetaProperty<om::DynamicArray<om::String,unsigned short> const &>::MetaProperty<om::DynamicArray<om::String,unsigned short> const &>(om::MetaTypeBase *,om::MetaClassB
// FUNCTION: ENGINE 0x108C9170 @ type_info const * om::MetaProperty<om::DynamicArray<om::String,unsigned short> const &>::GetValueType(void)
// FUNCTION: ENGINE 0x108C9180 @ om::MetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::MetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>(om::MetaTypeBase 
// FUNCTION: ENGINE 0x108C91C0 @ om::DynamicArray<om::String,unsigned short>::DynamicArray<om::String,unsigned short>(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C91D0 @ type_info const * om::MetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::GetValueType(void)
// FUNCTION: ENGINE 0x108C91E0 @ om::MetaMethod1Base<void,om::String const &>::~MetaMethod1Base<void,om::String const &>(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C91F0 @ om::MetaMethod0Base<om::String const &>::~MetaMethod0Base<om::String const &>(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C9200 @ om::MetaMethod1Base<void,om::DynamicArray<om::String,unsigned short> const &>::~MetaMethod1Base<void,om::DynamicArray<om::String,unsigned short> const &>(void) (name gues
// FUNCTION: ENGINE 0x108C9210 @ om::MetaMethod0Base<om::DynamicArray<om::String,unsigned short> const &>::~MetaMethod0Base<om::DynamicArray<om::String,unsigned short> const &>(void) (name guess; identic
// FUNCTION: ENGINE 0x108C9220 @ om::MetaMethod1Base<void,float const &>::~MetaMethod1Base<void,float const &>(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C9230 @ om::MetaMethod0Base<float const &>::~MetaMethod0Base<float const &>(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C9240 @ om::MetaProperty<om::String const &>::~MetaProperty<om::String const &>(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C9250 @ om::MetaProperty<om::DynamicArray<om::String,unsigned short> const &>::~MetaProperty<om::DynamicArray<om::String,unsigned short> const &>(void) (name guess; identical cop
// FUNCTION: ENGINE 0x108C9260 @ om::MetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::~MetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>(void) (name gues
// FUNCTION: ENGINE 0x108C9270 @ om::MetaMethod1Base<void,om::String const &>::MetaMethod1Base<void,om::String const &>(om::MetaClassBase *,om::Name<om::CaseSensitive64BitKey> const &)
// FUNCTION: ENGINE 0x108C92D0 @ om::MetaMethod1Base<void,om::DynamicArray<om::String,unsigned short> const &>::MetaMethod1Base<void,om::DynamicArray<om::String,unsigned short> const &>(om::MetaClassBase
// FUNCTION: ENGINE 0x108C9330 @ om::MetaMethod1Base<void,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::MetaMethod1Base<void,om::DynamicArray<engine::SoundGroup,unsigned short> const &>(o
// FUNCTION: ENGINE 0x108C9390 @ void * om::MetaMethod1Base<void,om::String const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108C93B0 @ void * om::MetaMethod0Base<om::String const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108C93D0 @ void * om::MetaMethod1Base<void,om::DynamicArray<om::String,unsigned short> const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108C93F0 @ void * om::MetaMethod0Base<om::DynamicArray<om::String,unsigned short> const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108C9410 @ void * om::MetaMethod1Base<void,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108C9430 @ void * om::MetaMethod0Base<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108C9450 @ engine::SoundGroup & om::DynamicArray<engine::SoundGroup,unsigned short>::operator[](unsigned short) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C9470 @ void om::DynamicArray<engine::SoundGroup,unsigned short>::ReleaseElements(engine::SoundGroup *,unsigned short)
// FUNCTION: ENGINE 0x108C94F0 @ void om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::String const &>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C9560 @ void om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::String const &>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C9580 @ char const * om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::String const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C9590 @ char const * om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::String const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C95A0 @ char const * om::MetaProperty<om::String const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C95B0 @ char const * om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,unsigned int const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C95C0 @ char const * om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,unsigned int const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C95D0 @ char const * om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::DynamicArray<om::String,unsigned short> const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C95E0 @ char const * om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::DynamicArray<om::String,unsigned short> const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C95F0 @ char const * om::MetaProperty<om::DynamicArray<om::String,unsigned short> const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C9600 @ char const * om::Garbage<om::DynamicArray<engine::SoundGroup,unsigned short> >::AllocationTag(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C9610 @ char const * om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,float const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C9620 @ char const * om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,float const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C9630 @ char const * om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::AllocationTag(void
// FUNCTION: ENGINE 0x108C9640 @ char const * om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::AllocationTag(void
// FUNCTION: ENGINE 0x108C9650 @ char const * om::MetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C96D0 @ char const * om::DynamicArray<engine::SoundGroup,unsigned short>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C9700 @ void om::DynamicArray<om::String,unsigned short>::Clear(void)
// FUNCTION: ENGINE 0x108C9760 @ char const * om::DelegateMetaProperty<om::String const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C9770 @ char const * om::DelegateMetaProperty<om::DynamicArray<om::String,unsigned short> const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C9780 @ char const * om::DelegateMetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::AllocationTag(void)
// FUNCTION: ENGINE 0x108C9820 @ int om::MetaClass<engine::SoundGroup>::Slot5(void)
// FUNCTION: ENGINE 0x108C9830 @ void om::MetaClass<engine::SoundGroup>::Slot6(void *)
// FUNCTION: ENGINE 0x108C9860 @ int om::MetaClass<engine::AudioGlobalSettings>::Slot5(void)
// FUNCTION: ENGINE 0x108C9870 @ void om::MetaClass<engine::AudioGlobalSettings>::Slot6(void *)
// FUNCTION: ENGINE 0x108C9880 @ void * om::Garbage<om::String>::operator new(unsigned int) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C98D0 @ void * om::MetaClass<engine::SoundGroup>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108C98F0 @ void * om::MetaClass<engine::SoundGroup>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108C9920 @ void * om::MetaClass<engine::AudioGlobalSettings>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108C9940 @ void * om::MetaClass<engine::AudioGlobalSettings>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108C9990 @ void * om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::String const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108C99B0 @ om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::String const &>::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::String const &>(om::MetaClassBa
// FUNCTION: ENGINE 0x108C99E0 @ void om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::String const &>::Call(void *,om::String const &)
// FUNCTION: ENGINE 0x108C9A00 @ om::MetaMethod1Base<void,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::~MetaMethod1Base<void,om::DynamicArray<engine::SoundGroup,unsigned short> const &>(
// FUNCTION: ENGINE 0x108C9A10 @ void om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,unsigned int const &>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C9A40 @ void * om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::String const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108C9A60 @ om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::String const &>::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::String const &>(om::MetaClassBa
// FUNCTION: ENGINE 0x108C9A90 @ om::String const & om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::String const &>::Call(void *)
// FUNCTION: ENGINE 0x108C9AA0 @ om::MetaMethod0Base<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::~MetaMethod0Base<om::DynamicArray<engine::SoundGroup,unsigned short> const &>(void) (nam
// FUNCTION: ENGINE 0x108C9AB0 @ void om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,unsigned int const &>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C9AD0 @ void * om::MetaProperty<om::String const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108C9AF0 @ void * om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,unsigned int const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108C9B10 @ om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,unsigned int const &>::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,unsigned int const &>(om::MetaCla
// FUNCTION: ENGINE 0x108C9B40 @ void om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,unsigned int const &>::Call(void *,unsigned int const &)
// FUNCTION: ENGINE 0x108C9B60 @ om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::String const &>::~MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::String const &>(void) (name gu
// FUNCTION: ENGINE 0x108C9B70 @ void om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::DynamicArray<om::String,unsigned short> const &>::operator delete(void *) (name guess; identical copie
// FUNCTION: ENGINE 0x108C9B90 @ void * om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,unsigned int const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108C9BB0 @ om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,unsigned int const &>::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,unsigned int const &>(om::MetaCla
// FUNCTION: ENGINE 0x108C9BE0 @ unsigned int const & om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,unsigned int const &>::Call(void *)
// FUNCTION: ENGINE 0x108C9BF0 @ om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::String const &>::~MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::String const &>(void) (name gu
// FUNCTION: ENGINE 0x108C9C00 @ void om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::DynamicArray<om::String,unsigned short> const &>::operator delete(void *) (name guess; identical copie
// FUNCTION: ENGINE 0x108C9CC0 @ void * om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::DynamicArray<om::String,unsigned short> const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108C9CE0 @ om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::DynamicArray<om::String,unsigned short> const &>::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om
// FUNCTION: ENGINE 0x108C9D10 @ void om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::DynamicArray<om::String,unsigned short> const &>::Call(void *,om::DynamicArray<om::String,unsigned sho
// FUNCTION: ENGINE 0x108C9D30 @ om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,unsigned int const &>::~MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,unsigned int const &>(void) (nam
// FUNCTION: ENGINE 0x108C9D40 @ void om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,float const &>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C9D70 @ void * om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::DynamicArray<om::String,unsigned short> const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108C9D90 @ om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::DynamicArray<om::String,unsigned short> const &>::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om
// FUNCTION: ENGINE 0x108C9DC0 @ om::DynamicArray<om::String,unsigned short> const & om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::DynamicArray<om::String,unsigned short> const &>::Call(
// FUNCTION: ENGINE 0x108C9DD0 @ om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,unsigned int const &>::~MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,unsigned int const &>(void) (nam
// FUNCTION: ENGINE 0x108C9DE0 @ void om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,float const &>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108C9E00 @ void * om::MetaProperty<om::DynamicArray<om::String,unsigned short> const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108C9E40 @ void * om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,float const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108C9E60 @ om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,float const &>::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,floa
// FUNCTION: ENGINE 0x108C9E90 @ void om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,float const &>::Call(void *,float const &)
// FUNCTION: ENGINE 0x108C9EB0 @ om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::DynamicArray<om::String,unsigned short> const &>::~MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,o
// FUNCTION: ENGINE 0x108C9EC0 @ void om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::operator delete(void *) (n
// FUNCTION: ENGINE 0x108C9EE0 @ void * om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,float const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108C9F00 @ om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,float const &>::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,floa
// FUNCTION: ENGINE 0x108C9F30 @ float const & om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,float const &>::Call(void *)
// FUNCTION: ENGINE 0x108C9F40 @ om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::DynamicArray<om::String,unsigned short> const &>::~MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,o
// FUNCTION: ENGINE 0x108C9F50 @ void om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::operator delete(void *) (n
// FUNCTION: ENGINE 0x108CA010 @ void * om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::operator new(unsigned in
// FUNCTION: ENGINE 0x108CA030 @ om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::MetaMethod1<engine::AudioGlobal
// FUNCTION: ENGINE 0x108CA060 @ void om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::Call(void *,om::DynamicArr
// FUNCTION: ENGINE 0x108CA080 @ om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,float const &>::~MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,flo
// FUNCTION: ENGINE 0x108CA0C0 @ void * om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::operator new(unsigned in
// FUNCTION: ENGINE 0x108CA0E0 @ om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::MetaMethod0Const<engine::AudioG
// FUNCTION: ENGINE 0x108CA110 @ om::DynamicArray<engine::SoundGroup,unsigned short> const & om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,om::DynamicArray<engine::SoundGro
// FUNCTION: ENGINE 0x108CA120 @ om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,float const &>::~MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,flo
// FUNCTION: ENGINE 0x108CA150 @ void * om::MetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108CA190 @ void * om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::String const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA1C0 @ void * om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::String const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA1F0 @ void * om::MetaProperty<om::String const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA220 @ void * om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,unsigned int const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA250 @ void * om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,unsigned int const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA280 @ void * om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::DynamicArray<om::String,unsigned short> const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA2B0 @ void * om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::DynamicArray<om::String,unsigned short> const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA2E0 @ void * om::MetaProperty<om::DynamicArray<om::String,unsigned short> const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA340 @ void * om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,float const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA370 @ void * om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,float const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA3A0 @ void * om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::`scalar deleting destruc
// FUNCTION: ENGINE 0x108CA3D0 @ void * om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::`scalar deleting destruc
// FUNCTION: ENGINE 0x108CA400 @ void * om::MetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA460 @ om::MetaMethod1Base<void,om::String const &> * om::MetaProperty<om::String const &>::GetSetter(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CA470 @ om::MetaMethod0Base<om::String const &> * om::MetaProperty<om::String const &>::GetGetter(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CA480 @ om::MetaMethod1Base<void,om::DynamicArray<om::String,unsigned short> const &> * om::MetaProperty<om::DynamicArray<om::String,unsigned short> const &>::GetSetter(void) (na
// FUNCTION: ENGINE 0x108CA490 @ om::MetaMethod0Base<om::DynamicArray<om::String,unsigned short> const &> * om::MetaProperty<om::DynamicArray<om::String,unsigned short> const &>::GetGetter(void) (name gu
// FUNCTION: ENGINE 0x108CA4A0 @ om::MetaMethod1Base<void,om::DynamicArray<engine::SoundGroup,unsigned short> const &> * om::MetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::Get
// FUNCTION: ENGINE 0x108CA4B0 @ om::MetaMethod0Base<om::DynamicArray<engine::SoundGroup,unsigned short> const &> * om::MetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::GetGette
// FUNCTION: ENGINE 0x108CA4C0 @ void * om::DynamicArray<om::String,unsigned short>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108CA4E0 @ void * om::DynamicArray<engine::SoundGroup,unsigned short>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108CA500 @ engine::SoundGroup * om::DynamicArray<engine::SoundGroup,unsigned short>::Allocate(unsigned short)
// FUNCTION: ENGINE 0x108CA630 @ engine::SoundGroup::~SoundGroup(void)
// FUNCTION: ENGINE 0x108CA650 @ void * om::DelegateMetaProperty<om::String const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108CA670 @ void * om::DelegateMetaProperty<om::DynamicArray<om::String,unsigned short> const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108CA690 @ void * om::DelegateMetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108CA6D0 @ om::Garbage<om::String>::Garbage<om::String>(om::String *)
// FUNCTION: ENGINE 0x108CA6F0 @ om::Garbage<om::String>::~Garbage<om::String>(void)
// FUNCTION: ENGINE 0x108CA720 @ void om::Garbage<om::String>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CA7E0 @ om::Garbage<om::DynamicArray<om::String,unsigned short> >::Garbage<om::DynamicArray<om::String,unsigned short> >(om::DynamicArray<om::String,unsigned short> *)
// FUNCTION: ENGINE 0x108CA800 @ void om::DynamicArray<om::String,unsigned short>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CA820 @ void om::Garbage<om::DynamicArray<om::String,unsigned short> >::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CA860 @ om::Garbage<om::DynamicArray<engine::SoundGroup,unsigned short> >::Garbage<om::DynamicArray<engine::SoundGroup,unsigned short> >(om::DynamicArray<engine::SoundGroup,unsig
// FUNCTION: ENGINE 0x108CA880 @ void om::DynamicArray<engine::SoundGroup,unsigned short>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CA8A0 @ void om::Garbage<om::DynamicArray<engine::SoundGroup,unsigned short> >::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CA8C0 @ om::DelegateProperty<om::DynamicArray<om::String,unsigned short> >::DelegateProperty<om::DynamicArray<om::String,unsigned short> >(void)
// FUNCTION: ENGINE 0x108CA8D0 @ om::MetaTypeBase * om::DelegateProperty<om::DynamicArray<om::String,unsigned short> >::GetMetaType(void)
// FUNCTION: ENGINE 0x108CA8E0 @ om::DelegateProperty<om::DynamicArray<om::String,unsigned short> >::~DelegateProperty<om::DynamicArray<om::String,unsigned short> >(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CA8F0 @ om::DelegateProperty<om::DynamicArray<engine::SoundGroup,unsigned short> >::DelegateProperty<om::DynamicArray<engine::SoundGroup,unsigned short> >(void)
// FUNCTION: ENGINE 0x108CA900 @ om::MetaTypeBase * om::DelegateProperty<om::DynamicArray<engine::SoundGroup,unsigned short> >::GetMetaType(void)
// FUNCTION: ENGINE 0x108CA910 @ om::DelegateProperty<om::DynamicArray<engine::SoundGroup,unsigned short> >::~DelegateProperty<om::DynamicArray<engine::SoundGroup,unsigned short> >(void) (name guess; ide
// FUNCTION: ENGINE 0x108CA920 @ void * om::Garbage<om::String>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA970 @ void * om::DynamicArray<om::String,unsigned short>::`scalar deleting destructor'(unsigned int) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CA9A0 @ void * om::DelegateProperty<om::DynamicArray<om::String,unsigned short> >::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA9C0 @ void * om::DelegateProperty<om::DynamicArray<engine::SoundGroup,unsigned short> >::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CA9E0 @ void om::DynamicArray<om::String,unsigned short>::Reserve(unsigned short)
// FUNCTION: ENGINE 0x108CAA10 @ om::String & om::DynamicArray<om::String,unsigned short>::Append(void)
// FUNCTION: ENGINE 0x108CAAB0 @ void om::DynamicArray<engine::SoundGroup,unsigned short>::Reserve(unsigned short)
// FUNCTION: ENGINE 0x108CADE0 @ engine::SoundGroup::SoundGroup(void)
// FUNCTION: ENGINE 0x108CAF00 @ void om::MetaClass<engine::SoundGroup>::Create(om::Name<om::CaseSensitive64BitKey> const &,om::MetaClassBase *)
// FUNCTION: ENGINE 0x108CB080 @ void om::MetaClass<engine::AudioGlobalSettings>::Create(om::Name<om::CaseSensitive64BitKey> const &,om::MetaClassBase *)
// FUNCTION: ENGINE 0x108CB0F0 @ om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::String const &> * om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::String const &>::Create(om
// FUNCTION: ENGINE 0x108CB130 @ om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::String const &> * om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::String const &>::Create(om
// FUNCTION: ENGINE 0x108CB170 @ void om::MetaProperty<om::String const &>::Create(om::MetaClassBase *,om::Name<om::CaseSensitive64BitKey> const &,om::MetaMethod1Base<void,om::String const &> *,om::MetaM
// FUNCTION: ENGINE 0x108CB1D0 @ om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,unsigned int const &> * om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,unsigned int const &>::Creat
// FUNCTION: ENGINE 0x108CB210 @ om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,unsigned int const &> * om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,unsigned int const &>::Creat
// FUNCTION: ENGINE 0x108CB2B0 @ om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,void,om::DynamicArray<om::String,unsigned short> const &> * om::MetaMethod1<engine::SoundGroup,engine::SoundGroup,vo
// FUNCTION: ENGINE 0x108CB2F0 @ om::MetaMethod0Const<engine::SoundGroup,engine::SoundGroup,om::DynamicArray<om::String,unsigned short> const &> * om::MetaMethod0Const<engine::SoundGroup,engine::SoundGro
// FUNCTION: ENGINE 0x108CB330 @ void om::MetaProperty<om::DynamicArray<om::String,unsigned short> const &>::Create(om::MetaClassBase *,om::Name<om::CaseSensitive64BitKey> const &,om::MetaMethod1Base<voi
// FUNCTION: ENGINE 0x108CB420 @ om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,float const &> * om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void
// FUNCTION: ENGINE 0x108CB460 @ om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,float const &> * om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings
// FUNCTION: ENGINE 0x108CB4A0 @ void om::MetaProperty<float const &>::Create(om::MetaClassBase *,om::Name<om::CaseSensitive64BitKey> const &,om::MetaMethod1Base<void,float const &> *,om::MetaMethod0Base
// FUNCTION: ENGINE 0x108CB500 @ om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,om::DynamicArray<engine::SoundGroup,unsigned short> const &> * om::MetaMethod1<engine::AudioG
// FUNCTION: ENGINE 0x108CB540 @ om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,om::DynamicArray<engine::SoundGroup,unsigned short> const &> * om::MetaMethod0Const<engine::A
// FUNCTION: ENGINE 0x108CB580 @ void om::MetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::Create(om::MetaClassBase *,om::Name<om::CaseSensitive64BitKey> const &,om::MetaMethod1
// FUNCTION: ENGINE 0x108CB6B0 @ void om::MetaProperty<om::String const &>::GetText(om::TextValue *,void *)
// FUNCTION: ENGINE 0x108CB750 @ bool om::MetaProperty<om::String const &>::SetBinary(om::BinaryStream *,void *)
// FUNCTION: ENGINE 0x108CB930 @ engine::SoundGroup::SoundGroup(engine::SoundGroup const &)
// FUNCTION: ENGINE 0x108CB970 @ om::DelegateMetaProperty<om::String const &>::DelegateMetaProperty<om::String const &>(void *,om::MetaProperty<om::String const &> *)
// FUNCTION: ENGINE 0x108CB9A0 @ void om::DelegateMetaProperty<om::String const &>::SetObject(void *)
// FUNCTION: ENGINE 0x108CB9B0 @ void om::DelegateMetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CB9D0 @ om::DelegateProperty<om::String>::~DelegateProperty<om::String>(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CB9E0 @ om::String om::DelegateMetaProperty<om::String const &>::Get(void)
// FUNCTION: ENGINE 0x108CBA10 @ void om::DelegateMetaProperty<om::String const &>::Set(om::String)
// FUNCTION: ENGINE 0x108CBA40 @ om::DelegateMetaProperty<om::DynamicArray<om::String,unsigned short> const &>::DelegateMetaProperty<om::DynamicArray<om::String,unsigned short> const &>(void *,om::MetaPr
// FUNCTION: ENGINE 0x108CBA70 @ void om::DelegateMetaProperty<om::DynamicArray<om::String,unsigned short> const &>::SetObject(void *)
// FUNCTION: ENGINE 0x108CBA80 @ void om::DelegateMetaProperty<om::String const &>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CBAA0 @ om::DelegateMetaProperty<om::DynamicArray<om::String,unsigned short> const &>::~DelegateMetaProperty<om::DynamicArray<om::String,unsigned short> const &>(void) (name gues
// FUNCTION: ENGINE 0x108CBB40 @ void om::DelegateMetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::SetObject(void *)
// FUNCTION: ENGINE 0x108CBB50 @ void om::DelegateMetaProperty<float const &>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CBB70 @ om::DelegateMetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::~DelegateMetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>(
// FUNCTION: ENGINE 0x108CBC20 @ om::Garbage<om::DynamicArray<om::String,unsigned short> >::~Garbage<om::DynamicArray<om::String,unsigned short> >(void)
// FUNCTION: ENGINE 0x108CBC50 @ void * om::DelegateMetaProperty<om::DynamicArray<om::String,unsigned short> const &>::`scalar deleting destructor'(unsigned int) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CBC80 @ void * om::DelegateMetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::`scalar deleting destructor'(unsigned int) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CBCB0 @ void * om::DelegateMetaProperty<om::String const &>::`scalar deleting destructor'(unsigned int) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CBCE0 @ void * om::Garbage<om::DynamicArray<om::String,unsigned short> >::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CBE10 @ void engine::SoundGroup::SetInterruptList(om::DynamicArray<om::String,unsigned short> const &)
// FUNCTION: ENGINE 0x108CC7C0 @ om::DynamicArray<om::String,unsigned short> om::DelegateMetaProperty<om::DynamicArray<om::String,unsigned short> const &>::Get(void)
// FUNCTION: ENGINE 0x108CC9A0 @ om::DelegatePropertyBase * om::MetaProperty<om::String const &>::CreateDelegate(void *)
// FUNCTION: ENGINE 0x108CCAC0 @ void om::MetaProperty<om::DynamicArray<om::String,unsigned short> const &>::GetText(om::TextValue *,void *)
// FUNCTION: ENGINE 0x108CCB50 @ void om::MetaProperty<om::DynamicArray<om::String,unsigned short> const &>::GetBinary(om::BinaryStream *,void *)
// FUNCTION: ENGINE 0x108CCB70 @ om::DelegatePropertyBase * om::MetaProperty<om::DynamicArray<om::String,unsigned short> const &>::CreateDelegate(void *)
// FUNCTION: ENGINE 0x108CCC20 @ om::DelegatePropertyBase * om::MetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::CreateDelegate(void *)
// FUNCTION: ENGINE 0x108CD430 @ om::DynamicArray<engine::SoundGroup,unsigned short>::DynamicArray<engine::SoundGroup,unsigned short>(om::DynamicArray<engine::SoundGroup,unsigned short> const &)
// FUNCTION: ENGINE 0x108CD830 @ void engine::AudioGlobalSettings::SetSoundGroups(om::DynamicArray<engine::SoundGroup,unsigned short> const &)
// FUNCTION: ENGINE 0x108CE130 @ om::DynamicArray<engine::SoundGroup,unsigned short> om::DelegateMetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::Get(void)
// FUNCTION: ENGINE 0x108CE5F0 @ void om::MetaProperty<om::DynamicArray<engine::SoundGroup,unsigned short> const &>::GetBinary(om::BinaryStream *,void *)
// FUNCTION: ENGINE 0x108CEEF0 @ om::MetaMethod1<engine::AudioGlobalSettings,engine::AudioGlobalSettings,void,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::~MetaMethod1<engine::AudioGloba
// FUNCTION: ENGINE 0x108CEF00 @ om::MetaMethod0Const<engine::AudioGlobalSettings,engine::AudioGlobalSettings,om::DynamicArray<engine::SoundGroup,unsigned short> const &>::~MetaMethod0Const<engine::Audio
// FUNCTION: ENGINE 0x108CEF10 @ om::MetaProperty<float const &>::~MetaProperty<float const &>(void) (name guess; identical copies)
