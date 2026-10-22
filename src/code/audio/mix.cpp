// The audio library's mixer reflection (0x105CC2D0 - 0x105D0F40): the reflection of audio::Mix and audio::MixStrip
// made of the om library's template instances.
#include "code/audio/mix.h"
#include "code/om/metamethod.h"
#include "code/om/metaproperty.h"
#include "code/om/delegate.h"

#pragma warning(disable: 4661)

namespace om
{

	// FUNCTION: ENGINE 0x1032BB10
	template MetaMethod1Base<void, const Name<CaseSensitive64BitKey>&>* MetaProperty<const Name<CaseSensitive64BitKey>&>::GetSetter();
	// FUNCTION: ENGINE 0x103B2000
	template MetaMethod1Base<void, float>* MetaProperty<float>::GetSetter();
	// FUNCTION: ENGINE 0x104030C0
	template MetaMethod1Base<void, bool>* MetaProperty<bool>::GetSetter();
	// FUNCTION: ENGINE 0x10428CA0
	template MetaMethod0Base<const Name<CaseSensitive64BitKey>&>* MetaProperty<const Name<CaseSensitive64BitKey>&>::GetGetter();
	// FUNCTION: ENGINE 0x104589A0
	template MetaMethod0Base<float>* MetaProperty<float>::GetGetter();
	// FUNCTION: ENGINE 0x10470240
	template MetaMethod0Base<bool>* MetaProperty<bool>::GetGetter();
	// FUNCTION: ENGINE 0x105CBFF0
	template MetaMethod0Base<const Name<CaseSensitive64BitKey>&>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105CC490
	template MetaProperty<unsigned int>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, unsigned int>*, MetaMethod0Base<unsigned int>*, unsigned int);
	// FUNCTION: ENGINE 0x105CC4D0
	template MetaMethod1Base<void, unsigned int>* MetaProperty<unsigned int>::GetSetter();
	// FUNCTION: ENGINE 0x105CC4E0
	template MetaMethod0Base<unsigned int>* MetaProperty<unsigned int>::GetGetter();
	// FUNCTION: ENGINE 0x105CC4F0
	template const type_info* MetaProperty<unsigned int>::GetValueType();
	// FUNCTION: ENGINE 0x105CC500
	template MetaProperty<const Name<CaseSensitive64BitKey>&>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, const Name<CaseSensitive64BitKey>&>*, MetaMethod0Base<const Name<CaseSensitive64BitKey>&>*, unsigned int);
	// FUNCTION: ENGINE 0x105CC540
	template const type_info* MetaProperty<const Name<CaseSensitive64BitKey>&>::GetValueType();
	// FUNCTION: ENGINE 0x105CC550
	template MetaProperty<float>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, float>*, MetaMethod0Base<float>*, unsigned int);
	// FUNCTION: ENGINE 0x105CC590
	template const type_info* MetaProperty<float>::GetValueType();
	// FUNCTION: ENGINE 0x105CC5A0
	template MetaProperty<bool>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, bool>*, MetaMethod0Base<bool>*, unsigned int);
	// FUNCTION: ENGINE 0x105CC5E0
	template const type_info* MetaProperty<bool>::GetValueType();
	// FUNCTION: ENGINE 0x105CC5F0
	template MetaMethod0Base<unsigned int>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105CC600
	template MetaMethod0Base<float>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105CC610
	template MetaMethod0Base<bool>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105CC620
	template MetaMethod0Const<audio::MixStrip, audio::MixStrip, bool>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105CC630
	template MetaMethod1Base<void, const Name<CaseSensitive64BitKey>&>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105CC640
	template MetaMethod1Base<void, unsigned int>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105CC650
	template MetaMethod1Base<void, float>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105CC660
	template MetaMethod1Base<void, bool>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105CC670
	template MetaProperty<const Name<CaseSensitive64BitKey>&>::~MetaProperty();
	// FUNCTION: ENGINE 0x105CC680
	template MetaProperty<float>::~MetaProperty();
	// FUNCTION: ENGINE 0x105CC690
	template MetaProperty<bool>::~MetaProperty();
	// FUNCTION: ENGINE 0x105CC6A0
	template MetaProperty<unsigned int>::~MetaProperty();
	// FUNCTION: ENGINE 0x105CC6B0
	template MetaMethod1Base<void, unsigned int>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105CC6D0
	template MetaMethod1Base<void, float>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105CC6F0
	template MetaMethod1Base<void, bool>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105CC710
	template MetaMethod0Base<unsigned int>::MetaMethod0Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105CC730
	template void MetaProperty<unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CC750
	template MetaMethod1Base<void, const Name<CaseSensitive64BitKey>&>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105CC770
	template MetaMethod0Base<const Name<CaseSensitive64BitKey>&>::MetaMethod0Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105CC790
	template void MetaProperty<const Name<CaseSensitive64BitKey>&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CC7B0
	template MetaMethod0Base<float>::MetaMethod0Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105CC7D0
	template void MetaProperty<float>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CC7F0
	template MetaMethod0Base<bool>::MetaMethod0Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105CC810
	template void MetaProperty<bool>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CC950
	template const char* MetaMethod1<audio::Mix, audio::Mix, void, unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x105CC960
	template const char* MetaMethod1<audio::MixStrip, audio::MixStrip, void, float>::AllocationTag();
	// FUNCTION: ENGINE 0x105CC970
	template const char* MetaMethod1<audio::MixStrip, audio::MixStrip, void, bool>::AllocationTag();
	// FUNCTION: ENGINE 0x105CC980
	template const char* MetaMethod0Const<audio::Mix, audio::Mix, unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x105CC990
	template const char* MetaProperty<unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x105CC9A0
	template const char* MetaMethod1<audio::MixStrip, audio::MixStrip, void, const Name<CaseSensitive64BitKey>&>::AllocationTag();
	// FUNCTION: ENGINE 0x105CC9B0
	template const char* MetaMethod0Const<audio::MixStrip, audio::MixStrip, const Name<CaseSensitive64BitKey>&>::AllocationTag();
	// FUNCTION: ENGINE 0x105CC9C0
	template const char* MetaProperty<const Name<CaseSensitive64BitKey>&>::AllocationTag();
	// FUNCTION: ENGINE 0x105CC9D0
	template const char* MetaMethod0Const<audio::MixStrip, audio::MixStrip, float>::AllocationTag();
	// FUNCTION: ENGINE 0x105CC9E0
	template const char* MetaProperty<float>::AllocationTag();
	// FUNCTION: ENGINE 0x105CC9F0
	template const char* MetaMethod0Const<audio::MixStrip, audio::MixStrip, bool>::AllocationTag();
	// FUNCTION: ENGINE 0x105CCA00
	template const char* MetaProperty<bool>::AllocationTag();
	// FUNCTION: ENGINE 0x105CCB10
	template const char* DelegateMetaProperty<unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x105CCB20
	template const char* DelegateMetaProperty<const Name<CaseSensitive64BitKey>&>::AllocationTag();
	// FUNCTION: ENGINE 0x105CCB30
	template const char* DelegateMetaProperty<float>::AllocationTag();
	// FUNCTION: ENGINE 0x105CCB40
	template const char* DelegateMetaProperty<bool>::AllocationTag();
	// FUNCTION: ENGINE 0x105CCE60
	template void* MetaMethod1<audio::Mix, audio::Mix, void, unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CCE80
	template MetaMethod1<audio::Mix, audio::Mix, void, unsigned int>::MetaMethod1(MetaClassBase*, const ClassName&, void (audio::Mix::*)(unsigned int));
	// FUNCTION: ENGINE 0x105CCED0
	template void MetaMethod1<audio::Mix, audio::Mix, void, unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x105CCF10
	template void MetaMethod1<audio::Mix, audio::Mix, void, unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CCFA0
	template void* MetaMethod1<audio::MixStrip, audio::MixStrip, void, float>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CCFC0
	template MetaMethod1<audio::MixStrip, audio::MixStrip, void, float>::MetaMethod1(MetaClassBase*, const ClassName&, void (audio::MixStrip::*)(float));
	// FUNCTION: ENGINE 0x105CCFF0
	template void MetaMethod1<audio::MixStrip, audio::MixStrip, void, float>::Call(void*, float);
	// FUNCTION: ENGINE 0x105CD010
	template MetaMethod1<audio::Mix, audio::Mix, void, unsigned int>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105CD020
	template void MetaMethod1<audio::MixStrip, audio::MixStrip, void, float>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CD060
	template void* MetaMethod1<audio::MixStrip, audio::MixStrip, void, bool>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CD080
	template MetaMethod1<audio::MixStrip, audio::MixStrip, void, bool>::MetaMethod1(MetaClassBase*, const ClassName&, void (audio::MixStrip::*)(bool));
	// FUNCTION: ENGINE 0x105CD0B0
	template void MetaMethod1<audio::MixStrip, audio::MixStrip, void, bool>::Call(void*, bool);
	// FUNCTION: ENGINE 0x105CD0D0
	template MetaMethod1<audio::MixStrip, audio::MixStrip, void, float>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105CD0E0
	template void MetaMethod1<audio::MixStrip, audio::MixStrip, void, bool>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CD120
	template void* MetaMethod0Const<audio::Mix, audio::Mix, unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CD140
	template MetaMethod0Const<audio::Mix, audio::Mix, unsigned int>::MetaMethod0Const(MetaClassBase*, const ClassName&, unsigned int (audio::Mix::*)() const);
	// FUNCTION: ENGINE 0x105CD170
	template unsigned int MetaMethod0Const<audio::Mix, audio::Mix, unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x105CD180
	template MetaMethod1<audio::MixStrip, audio::MixStrip, void, bool>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105CD1A0
	template void MetaMethod0Const<audio::Mix, audio::Mix, unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CD260
	template void* MetaProperty<unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CD280
	template void* MetaMethod1<audio::MixStrip, audio::MixStrip, void, const Name<CaseSensitive64BitKey>&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CD2A0
	template MetaMethod1<audio::MixStrip, audio::MixStrip, void, const Name<CaseSensitive64BitKey>&>::MetaMethod1(MetaClassBase*, const ClassName&, void (audio::MixStrip::*)(const Name<CaseSensitive64BitKey>&));
	// FUNCTION: ENGINE 0x105CD300
	template void MetaMethod1<audio::MixStrip, audio::MixStrip, void, const Name<CaseSensitive64BitKey>&>::Call(void*, const Name<CaseSensitive64BitKey>&);
	// FUNCTION: ENGINE 0x105CD320
	template MetaMethod0Const<audio::Mix, audio::Mix, unsigned int>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105CD330
	template void MetaMethod1<audio::MixStrip, audio::MixStrip, void, const Name<CaseSensitive64BitKey>&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CD360
	template const char* Garbage<Name<CaseSensitive64BitKey>>::AllocationTag();
	// FUNCTION: ENGINE 0x105CD370
	template void* MetaMethod0Const<audio::MixStrip, audio::MixStrip, const Name<CaseSensitive64BitKey>&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CD390
	template MetaMethod0Const<audio::MixStrip, audio::MixStrip, const Name<CaseSensitive64BitKey>&>::MetaMethod0Const(MetaClassBase*, const ClassName&, const Name<CaseSensitive64BitKey>& (audio::MixStrip::*)() const);
	// FUNCTION: ENGINE 0x105CD3C0
	template const Name<CaseSensitive64BitKey>& MetaMethod0Const<audio::MixStrip, audio::MixStrip, const Name<CaseSensitive64BitKey>&>::Call(void*);
	// FUNCTION: ENGINE 0x105CD3D0
	template MetaMethod1<audio::MixStrip, audio::MixStrip, void, const Name<CaseSensitive64BitKey>&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105CD3E0
	template void MetaMethod0Const<audio::MixStrip, audio::MixStrip, const Name<CaseSensitive64BitKey>&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CD400
	template void* MetaProperty<const Name<CaseSensitive64BitKey>&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CD420
	template void* MetaMethod0Const<audio::MixStrip, audio::MixStrip, float>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CD440
	template MetaMethod0Const<audio::MixStrip, audio::MixStrip, float>::MetaMethod0Const(MetaClassBase*, const ClassName&, float (audio::MixStrip::*)() const);
	// FUNCTION: ENGINE 0x105CD470
	template float MetaMethod0Const<audio::MixStrip, audio::MixStrip, float>::Call(void*);
	// FUNCTION: ENGINE 0x105CD480
	template MetaMethod0Const<audio::MixStrip, audio::MixStrip, const Name<CaseSensitive64BitKey>&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105CD4B0
	template void MetaMethod0Const<audio::MixStrip, audio::MixStrip, float>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CD570
	template void* MetaProperty<float>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CD590
	template void* MetaMethod0Const<audio::MixStrip, audio::MixStrip, bool>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CD5B0
	template MetaMethod0Const<audio::MixStrip, audio::MixStrip, bool>::MetaMethod0Const(MetaClassBase*, const ClassName&, bool (audio::MixStrip::*)() const);
	// FUNCTION: ENGINE 0x105CD5E0
	template bool MetaMethod0Const<audio::MixStrip, audio::MixStrip, bool>::Call(void*);
	// FUNCTION: ENGINE 0x105CD5F0
	template MetaMethod0Const<audio::MixStrip, audio::MixStrip, float>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105CD600
	template void MetaMethod0Const<audio::MixStrip, audio::MixStrip, bool>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CD620
	template void* MetaProperty<bool>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CD930
	template bool MetaProperty<unsigned int>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105CD9C0
	template void MetaProperty<unsigned int>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105CDA30
	template bool MetaProperty<unsigned int>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105CDA70
	template void MetaProperty<unsigned int>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105CDA90
	template bool MetaProperty<float>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105CDB20
	template void MetaProperty<float>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105CDBA0
	template bool MetaProperty<float>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105CDBE0
	template void MetaProperty<float>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105CDC10
	template bool MetaProperty<bool>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105CDCA0
	// EQUIVALENT: the engine calls the getter before it tests the cached type, ours inside the two branches; the same calls in the same order otherwise (38.7 %)
	template void MetaProperty<bool>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105CDD10
	// EQUIVALENT: the same stream read and setter call; the engine loads the stream pointer and the argument pushes in another order (59.3 %)
	template bool MetaProperty<bool>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105CDD50
	// EQUIVALENT: the same getter call and byte write; the engine loads the stream pointer before the compare (80 %)
	template void MetaProperty<bool>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105CDD80
	template void* DelegateMetaProperty<unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CDDA0
	template void* DelegateMetaProperty<const Name<CaseSensitive64BitKey>&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CDDC0
	template void* DelegateMetaProperty<float>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CDDE0
	template void* DelegateMetaProperty<bool>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CDE00
	template void* Garbage<Name<CaseSensitive64BitKey>>::operator new(size_t);
	// FUNCTION: ENGINE 0x105CDE20
	template Garbage<Name<CaseSensitive64BitKey>>::Garbage(Name<CaseSensitive64BitKey>*);
	// FUNCTION: ENGINE 0x105CDE40
	template Garbage<Name<CaseSensitive64BitKey>>::~Garbage();
	// FUNCTION: ENGINE 0x105CDE60
	template void Garbage<Name<CaseSensitive64BitKey>>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CDE80
	template DelegateProperty<unsigned int>::DelegateProperty();
	// FUNCTION: ENGINE 0x105CDE90
	template MetaTypeBase* DelegateProperty<unsigned int>::GetMetaType();
	// FUNCTION: ENGINE 0x105CDEA0
	template DelegateProperty<unsigned int>::~DelegateProperty();
	// FUNCTION: ENGINE 0x105CDEB0
	template DelegateProperty<Name<CaseSensitive64BitKey>>::DelegateProperty();
	// FUNCTION: ENGINE 0x105CDEC0
	template MetaTypeBase* DelegateProperty<Name<CaseSensitive64BitKey>>::GetMetaType();
	// FUNCTION: ENGINE 0x105CDED0
	template DelegateProperty<Name<CaseSensitive64BitKey>>::~DelegateProperty();
	// FUNCTION: ENGINE 0x105CDEE0
	template DelegateProperty<bool>::DelegateProperty();
	// FUNCTION: ENGINE 0x105CDEF0
	template MetaTypeBase* DelegateProperty<bool>::GetMetaType();
	// FUNCTION: ENGINE 0x105CDF00
	template DelegateProperty<bool>::~DelegateProperty();
	// FUNCTION: ENGINE 0x105CE430
	template MetaMethod1<audio::Mix, audio::Mix, void, unsigned int>* MetaMethod1<audio::Mix, audio::Mix, void, unsigned int>::Create(MetaClassBase*, const ClassName&, void (audio::Mix::*)(unsigned int));
	// FUNCTION: ENGINE 0x105CE470
	template MetaMethod0Const<audio::Mix, audio::Mix, unsigned int>* MetaMethod0Const<audio::Mix, audio::Mix, unsigned int>::Create(MetaClassBase*, const ClassName&, unsigned int (audio::Mix::*)() const);
	// FUNCTION: ENGINE 0x105CE4B0
	template void MetaProperty<unsigned int>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, unsigned int>*, MetaMethod0Base<unsigned int>*, unsigned int);
	// FUNCTION: ENGINE 0x105CE500
	template MetaMethod1<audio::MixStrip, audio::MixStrip, void, const Name<CaseSensitive64BitKey>&>* MetaMethod1<audio::MixStrip, audio::MixStrip, void, const Name<CaseSensitive64BitKey>&>::Create(MetaClassBase*, const ClassName&, void (audio::MixStrip::*)(const Name<CaseSensitive64BitKey>&));
	// FUNCTION: ENGINE 0x105CE540
	template MetaMethod0Const<audio::MixStrip, audio::MixStrip, const Name<CaseSensitive64BitKey>&>* MetaMethod0Const<audio::MixStrip, audio::MixStrip, const Name<CaseSensitive64BitKey>&>::Create(MetaClassBase*, const ClassName&, const Name<CaseSensitive64BitKey>& (audio::MixStrip::*)() const);
	// FUNCTION: ENGINE 0x105CE580
	template void MetaProperty<const Name<CaseSensitive64BitKey>&>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, const Name<CaseSensitive64BitKey>&>*, MetaMethod0Base<const Name<CaseSensitive64BitKey>&>*, unsigned int);
	// FUNCTION: ENGINE 0x105CE5E0
	template MetaMethod1<audio::MixStrip, audio::MixStrip, void, float>* MetaMethod1<audio::MixStrip, audio::MixStrip, void, float>::Create(MetaClassBase*, const ClassName&, void (audio::MixStrip::*)(float));
	// FUNCTION: ENGINE 0x105CE620
	template MetaMethod0Const<audio::MixStrip, audio::MixStrip, float>* MetaMethod0Const<audio::MixStrip, audio::MixStrip, float>::Create(MetaClassBase*, const ClassName&, float (audio::MixStrip::*)() const);
	// FUNCTION: ENGINE 0x105CE660
	template void MetaProperty<float>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, float>*, MetaMethod0Base<float>*, unsigned int);
	// FUNCTION: ENGINE 0x105CE6B0
	template MetaMethod1<audio::MixStrip, audio::MixStrip, void, bool>* MetaMethod1<audio::MixStrip, audio::MixStrip, void, bool>::Create(MetaClassBase*, const ClassName&, void (audio::MixStrip::*)(bool));
	// FUNCTION: ENGINE 0x105CE6F0
	template MetaMethod0Const<audio::MixStrip, audio::MixStrip, bool>* MetaMethod0Const<audio::MixStrip, audio::MixStrip, bool>::Create(MetaClassBase*, const ClassName&, bool (audio::MixStrip::*)() const);
	// FUNCTION: ENGINE 0x105CE730
	template void MetaProperty<bool>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, bool>*, MetaMethod0Base<bool>*, unsigned int);
	// FUNCTION: ENGINE 0x105CE9E0
	template void MetaProperty<const Name<CaseSensitive64BitKey>&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105CEA60
	template void MetaProperty<const Name<CaseSensitive64BitKey>&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105CEAD0
	template DelegateMetaProperty<unsigned int>::DelegateMetaProperty(void*, MetaProperty<unsigned int>*);
	// FUNCTION: ENGINE 0x105CEB00
	template void DelegateMetaProperty<unsigned int>::SetObject(void*);
	// FUNCTION: ENGINE 0x105CEB10
	template void DelegateMetaProperty<unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CEB30
	template DelegateMetaProperty<unsigned int>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x105CEB40
	template unsigned int DelegateMetaProperty<unsigned int>::Get();
	// FUNCTION: ENGINE 0x105CEB60
	template void DelegateMetaProperty<unsigned int>::Set(unsigned int);
	// FUNCTION: ENGINE 0x105CEB80
	template DelegateMetaProperty<const Name<CaseSensitive64BitKey>&>::DelegateMetaProperty(void*, MetaProperty<const Name<CaseSensitive64BitKey>&>*);
	// FUNCTION: ENGINE 0x105CEBB0
	template void DelegateMetaProperty<const Name<CaseSensitive64BitKey>&>::SetObject(void*);
	// FUNCTION: ENGINE 0x105CEBC0
	template void DelegateMetaProperty<const Name<CaseSensitive64BitKey>&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CEBE0
	template DelegateMetaProperty<const Name<CaseSensitive64BitKey>&>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x105CEBF0
	template Name<CaseSensitive64BitKey> DelegateMetaProperty<const Name<CaseSensitive64BitKey>&>::Get();
	// FUNCTION: ENGINE 0x105CEC20
	template void DelegateMetaProperty<const Name<CaseSensitive64BitKey>&>::Set(Name<CaseSensitive64BitKey>);
	// FUNCTION: ENGINE 0x105CEC40
	template DelegateMetaProperty<float>::DelegateMetaProperty(void*, MetaProperty<float>*);
	// FUNCTION: ENGINE 0x105CEC70
	template void DelegateMetaProperty<float>::SetObject(void*);
	// FUNCTION: ENGINE 0x105CEC80
	template void DelegateMetaProperty<float>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CECA0
	template DelegateMetaProperty<float>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x105CECB0
	template float DelegateMetaProperty<float>::Get();
	// FUNCTION: ENGINE 0x105CECD0
	template void DelegateMetaProperty<float>::Set(float);
	// FUNCTION: ENGINE 0x105CECF0
	template DelegateMetaProperty<bool>::DelegateMetaProperty(void*, MetaProperty<bool>*);
	// FUNCTION: ENGINE 0x105CED20
	template void DelegateMetaProperty<bool>::SetObject(void*);
	// FUNCTION: ENGINE 0x105CED30
	template void DelegateMetaProperty<bool>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CED50
	template DelegateMetaProperty<bool>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x105CED60
	template bool DelegateMetaProperty<bool>::Get();
	// FUNCTION: ENGINE 0x105CED80
	template void DelegateMetaProperty<bool>::Set(bool);
	// FUNCTION: ENGINE 0x105CF560
	template DelegatePropertyBase* MetaProperty<unsigned int>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x105CF5B0
	// EQUIVALENT: register allocation: the engine keeps zero in esi and this in edi, ours the other way round (79.8 %)
	template bool MetaProperty<const Name<CaseSensitive64BitKey>&>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105CF660
	template bool MetaProperty<const Name<CaseSensitive64BitKey>&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105CF6B0
	template DelegatePropertyBase* MetaProperty<const Name<CaseSensitive64BitKey>&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x105CF700
	template DelegatePropertyBase* MetaProperty<float>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x105CF750
	template DelegatePropertyBase* MetaProperty<bool>::CreateDelegate(void*);
}
