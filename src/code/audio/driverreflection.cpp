// The reflection of the audio renderer drivers (0x10AA9B40 - 0x10AC0000): the template instances of the om library for
// the drivers' properties and enumerations.
#include "code/audio/drivers.h"
#include "code/om/delegate.h"
#include "code/om/invoke.h"
#include "code/om/metaclass.h"
#include "code/om/metaenum.h"
#include "code/om/metamethod.h"
#include "code/om/metaproperty.h"

#pragma warning(disable: 4661)

namespace om
{
	using namespace audio;

	// FUNCTION: ENGINE 0x10AB6500
	template MetaEnum<audio::AudioFileType>::MetaEnum(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AB6520
	template type_info const* MetaEnum<audio::AudioFileType>::GetType();
	// FUNCTION: ENGINE 0x10AB6530
	template MetaEnum<audio::AudioFileType>::~MetaEnum();
	// FUNCTION: ENGINE 0x10AB6540
	template bool MetaEnum<audio::AudioFileType>::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10AB6560
	template void MetaEnum<audio::AudioFileType>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB65A0
	template MetaClass<audio::AudioFile>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AB65D0
	template type_info const* MetaClass<audio::AudioFile>::GetType();
	// FUNCTION: ENGINE 0x10AB6610
	template void MetaClass<audio::AudioFile>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB6640
	template char const* EntityType<audio::AudioFile>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB6650
	template char const* MetaEnum<audio::AudioFileType>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB6670
	template char const* MetaClass<audio::AudioFile>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB66D0
	template bool MetaEnum<audio::AudioFileType>::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10AB66F0
	template int MetaEnum<audio::AudioFileType>::Slot5();
	// FUNCTION: ENGINE 0x10AB6700
	template void MetaEnum<audio::AudioFileType>::Slot6(void*);
	// FUNCTION: ENGINE 0x10AB6740
	template void* EntityType<audio::AudioFile>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB6760
	template void* MetaEnum<audio::AudioFileType>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB6780
	template int MetaClass<audio::AudioFile>::Slot5();
	// FUNCTION: ENGINE 0x10AB6790
	template void MetaClass<audio::AudioFile>::Slot6(void*);
	// FUNCTION: ENGINE 0x10AB67A0
	template void* MetaClass<audio::AudioFile>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB6BA0
	template void MetaEnum<audio::AudioFileType>::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10AB6BB0
	template void MetaClass<audio::AudioFile>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AB6CA0
	template bool MetaEnum<audio::AudioFileType>::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10AB6D10
	template EntityType<audio::AudioFile>::EntityType(char const*, unsigned int, unsigned int, int);
	// FUNCTION: ENGINE 0x10AB6DB0
	template void EntityType<audio::AudioFile>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB6DF0
	template MetaTypeBase* EntityType<audio::AudioFile>::GetMetaType();
	// FUNCTION: ENGINE 0x10AB6E10
	template void EntityType<audio::AudioFile>::CreateEntity(Entity**, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AB6E60
	template void EntityType<audio::AudioFile>::CreateUnregisteredEntity(Entity**, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AB6EC0
	template void EntityType<audio::AudioFile>::CreateUnregisteredEntity2(Entity**, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AB6F70
	template EntityType<audio::AudioFile>::~EntityType();
	// FUNCTION: ENGINE 0x10AB70E0
	template void EntityType<audio::AudioFile>::Register(char const*, int);
	// FUNCTION: ENGINE 0x10AB79C0
	template MetaClass<audio::MmeRendererDriver>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AB79F0
	template type_info const* MetaClass<audio::MmeRendererDriver>::GetType();
	// FUNCTION: ENGINE 0x10AB7A30
	template void MetaClass<audio::MmeRendererDriver>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB7A50
	template char const* MetaProperty<audio::WAVEFORMAT>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB7AB0
	template char const* MetaClass<audio::MmeRendererDriver>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB7AC0
	template MetaProperty<audio::WAVEFORMAT>::MetaProperty(MetaTypeBase*, MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,audio::WAVEFORMAT>*, MetaMethod0Base<audio::WAVEFORMAT>*, unsigned int);
	// FUNCTION: ENGINE 0x10AB7B00
	template type_info const* MetaProperty<audio::WAVEFORMAT>::GetValueType();
	// FUNCTION: ENGINE 0x10AB7B30
	template MetaProperty<audio::WAVEFORMAT>::~MetaProperty();
	// FUNCTION: ENGINE 0x10AB7B40
	template MetaMethod1Base<void,audio::WAVEFORMAT>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AB7C00
	template char const* MetaMethod1<audio::MmeRendererDriver,audio::MmeRendererDriver,void,audio::WAVEFORMAT>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB7C10
	template char const* MetaMethod0Const<audio::MmeRendererDriver,audio::MmeRendererDriver,audio::WAVEFORMAT>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB7C50
	template char const* DelegateMetaProperty<audio::WAVEFORMAT>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB8210
	template int MetaClass<audio::MmeRendererDriver>::Slot5();
	// FUNCTION: ENGINE 0x10AB8220
	template void MetaClass<audio::MmeRendererDriver>::Slot6(void*);
	// FUNCTION: ENGINE 0x10AB8230
	template void* MetaClass<audio::MmeRendererDriver>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB82A0
	template void* MetaMethod1<audio::MmeRendererDriver,audio::MmeRendererDriver,void,audio::WAVEFORMAT>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB82C0
	template MetaMethod1<audio::MmeRendererDriver,audio::MmeRendererDriver,void,audio::WAVEFORMAT>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<audio::MmeRendererDriver,audio::MmeRendererDriver,void,audio::WAVEFORMAT>::Function);
	// FUNCTION: ENGINE 0x10AB82F0
	template void MetaMethod1<audio::MmeRendererDriver,audio::MmeRendererDriver,void,audio::WAVEFORMAT>::Call(void*, audio::WAVEFORMAT);
	// FUNCTION: ENGINE 0x10AB8310
	template MetaMethod1<audio::MmeRendererDriver,audio::MmeRendererDriver,void,audio::WAVEFORMAT>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AB8320
	template void MetaMethod1<audio::MmeRendererDriver,audio::MmeRendererDriver,void,audio::WAVEFORMAT>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB8340
	template void* MetaMethod0Const<audio::MmeRendererDriver,audio::MmeRendererDriver,audio::WAVEFORMAT>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB8360
	template MetaMethod0Const<audio::MmeRendererDriver,audio::MmeRendererDriver,audio::WAVEFORMAT>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<audio::MmeRendererDriver,audio::MmeRendererDriver,audio::WAVEFORMAT>::Function);
	// FUNCTION: ENGINE 0x10AB8390
	template audio::WAVEFORMAT MetaMethod0Const<audio::MmeRendererDriver,audio::MmeRendererDriver,audio::WAVEFORMAT>::Call(void*);
	// FUNCTION: ENGINE 0x10AB83A0
	template MetaMethod0Const<audio::MmeRendererDriver,audio::MmeRendererDriver,audio::WAVEFORMAT>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AB83B0
	template void MetaMethod0Const<audio::MmeRendererDriver,audio::MmeRendererDriver,audio::WAVEFORMAT>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB8480
	template MetaMethod1Base<void,audio::WAVEFORMAT>* MetaProperty<audio::WAVEFORMAT>::GetSetter();
	// FUNCTION: ENGINE 0x10AB8490
	template MetaMethod0Base<audio::WAVEFORMAT>* MetaProperty<audio::WAVEFORMAT>::GetGetter();
	// FUNCTION: ENGINE 0x10AB84C0
	template void* DelegateMetaProperty<audio::WAVEFORMAT>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB8510
	template DelegateProperty<audio::WAVEFORMAT>::DelegateProperty();
	// FUNCTION: ENGINE 0x10AB8520
	template MetaTypeBase* DelegateProperty<audio::WAVEFORMAT>::GetMetaType();
	// FUNCTION: ENGINE 0x10AB8530
	template DelegateProperty<audio::WAVEFORMAT>::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AB8710
	template void MetaClass<audio::MmeRendererDriver>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AB87D0
	template MetaMethod1<audio::MmeRendererDriver,audio::MmeRendererDriver,void,audio::WAVEFORMAT>* MetaMethod1<audio::MmeRendererDriver,audio::MmeRendererDriver,void,audio::WAVEFORMAT>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<audio::MmeRendererDriver,audio::MmeRendererDriver,void,audio::WAVEFORMAT>::Function);
	// FUNCTION: ENGINE 0x10AB8810
	template MetaMethod0Const<audio::MmeRendererDriver,audio::MmeRendererDriver,audio::WAVEFORMAT>* MetaMethod0Const<audio::MmeRendererDriver,audio::MmeRendererDriver,audio::WAVEFORMAT>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<audio::MmeRendererDriver,audio::MmeRendererDriver,audio::WAVEFORMAT>::Function);
	// FUNCTION: ENGINE 0x10AB8900
	template DelegateMetaProperty<audio::WAVEFORMAT>::DelegateMetaProperty(void*, MetaProperty<audio::WAVEFORMAT>*);
	// FUNCTION: ENGINE 0x10AB8930
	template void DelegateMetaProperty<audio::WAVEFORMAT>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AB8940
	template void DelegateMetaProperty<audio::WAVEFORMAT>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB8960
	template DelegateMetaProperty<audio::WAVEFORMAT>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x10AB8970
	template audio::WAVEFORMAT DelegateMetaProperty<audio::WAVEFORMAT>::Get();
	// FUNCTION: ENGINE 0x10AB8990
	template void DelegateMetaProperty<audio::WAVEFORMAT>::Set(audio::WAVEFORMAT);
	// FUNCTION: ENGINE 0x10AB8D60
	template bool MetaProperty<audio::WAVEFORMAT>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10AB8DF0
	template void MetaProperty<audio::WAVEFORMAT>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10AB8E80
	template bool MetaProperty<audio::WAVEFORMAT>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10AB8EE0
	template bool MetaProperty<audio::WAVEFORMAT>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10AB8F30
	template DelegatePropertyBase* MetaProperty<audio::WAVEFORMAT>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x10AB8FC0
	template void MetaMethod0Const<audio::MmeRendererDriver,audio::MmeRendererDriver,audio::WAVEFORMAT>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10AB9080
	template void MetaMethod1<audio::MmeRendererDriver,audio::MmeRendererDriver,void,audio::WAVEFORMAT>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ABAA00
	template MetaClass<audio::WdmKsRendererDriver>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ABAA30
	template type_info const* MetaClass<audio::WdmKsRendererDriver>::GetType();
	// FUNCTION: ENGINE 0x10ABAA70
	template void MetaClass<audio::WdmKsRendererDriver>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABABA0
	template char const* MetaClass<audio::WdmKsRendererDriver>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABAC20
	template char const* MetaMethod1<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,void,audio::WAVEFORMAT>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABAC30
	template char const* MetaMethod0Const<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,audio::WAVEFORMAT>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABB480
	template int MetaClass<audio::WdmKsRendererDriver>::Slot5();
	// FUNCTION: ENGINE 0x10ABB490
	template void MetaClass<audio::WdmKsRendererDriver>::Slot6(void*);
	// FUNCTION: ENGINE 0x10ABB4A0
	template void* MetaClass<audio::WdmKsRendererDriver>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABB610
	template void* MetaMethod1<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,void,audio::WAVEFORMAT>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABB630
	template MetaMethod1<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,void,audio::WAVEFORMAT>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,void,audio::WAVEFORMAT>::Function);
	// FUNCTION: ENGINE 0x10ABB660
	template void MetaMethod1<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,void,audio::WAVEFORMAT>::Call(void*, audio::WAVEFORMAT);
	// FUNCTION: ENGINE 0x10ABB680
	template MetaMethod1<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,void,audio::WAVEFORMAT>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10ABB690
	template void MetaMethod1<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,void,audio::WAVEFORMAT>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABB6B0
	template void* MetaMethod0Const<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,audio::WAVEFORMAT>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABB6D0
	template MetaMethod0Const<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,audio::WAVEFORMAT>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,audio::WAVEFORMAT>::Function);
	// FUNCTION: ENGINE 0x10ABB700
	template audio::WAVEFORMAT MetaMethod0Const<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,audio::WAVEFORMAT>::Call(void*);
	// FUNCTION: ENGINE 0x10ABB710
	template MetaMethod0Const<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,audio::WAVEFORMAT>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10ABB720
	template void MetaMethod0Const<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,audio::WAVEFORMAT>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABBCB0
	template void MetaClass<audio::WdmKsRendererDriver>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ABBDF0
	template MetaMethod1<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,void,audio::WAVEFORMAT>* MetaMethod1<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,void,audio::WAVEFORMAT>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,void,audio::WAVEFORMAT>::Function);
	// FUNCTION: ENGINE 0x10ABBE30
	template MetaMethod0Const<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,audio::WAVEFORMAT>* MetaMethod0Const<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,audio::WAVEFORMAT>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,audio::WAVEFORMAT>::Function);
	// FUNCTION: ENGINE 0x10ABC440
	template void MetaMethod0Const<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,audio::WAVEFORMAT>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ABC790
	template void MetaMethod1<audio::WdmKsRendererDriver,audio::WdmKsRendererDriver,void,audio::WAVEFORMAT>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ABD190
	template MetaClass<audio::DirectSoundRendererDriverImpl>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ABD1C0
	template type_info const* MetaClass<audio::DirectSoundRendererDriverImpl>::GetType();
	// FUNCTION: ENGINE 0x10ABD1D0
	template MetaEnum<audio::BufferLocation>::MetaEnum(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ABD1F0
	template type_info const* MetaEnum<audio::BufferLocation>::GetType();
	// FUNCTION: ENGINE 0x10ABD200
	template MetaEnum<audio::BufferLocation>::~MetaEnum();
	// FUNCTION: ENGINE 0x10ABD210
	template bool MetaEnum<audio::BufferLocation>::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10ABD230
	template void MetaEnum<audio::BufferLocation>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABD250
	template MetaEnum<audio::MixType>::MetaEnum(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ABD270
	template type_info const* MetaEnum<audio::MixType>::GetType();
	// FUNCTION: ENGINE 0x10ABD280
	template MetaEnum<audio::MixType>::~MetaEnum();
	// FUNCTION: ENGINE 0x10ABD290
	template bool MetaEnum<audio::MixType>::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10ABD2B0
	template void MetaEnum<audio::MixType>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABD2D0
	template MetaEnum<audio::Focus>::MetaEnum(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ABD2F0
	template type_info const* MetaEnum<audio::Focus>::GetType();
	// FUNCTION: ENGINE 0x10ABD300
	template MetaEnum<audio::Focus>::~MetaEnum();
	// FUNCTION: ENGINE 0x10ABD310
	template bool MetaEnum<audio::Focus>::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10ABD330
	template void MetaEnum<audio::Focus>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABD440
	template void MetaClass<audio::DirectSoundRendererDriverImpl>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABD4F0
	template char const* MetaClass<audio::DirectSoundRendererDriverImpl>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD500
	template char const* MetaEnum<audio::BufferLocation>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD510
	template char const* MetaEnum<audio::MixType>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD520
	template char const* MetaEnum<audio::Focus>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD530
	template MetaProperty<audio::BufferLocation>::MetaProperty(MetaTypeBase*, MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,audio::BufferLocation>*, MetaMethod0Base<audio::BufferLocation>*, unsigned int);
	// FUNCTION: ENGINE 0x10ABD570
	template type_info const* MetaProperty<audio::BufferLocation>::GetValueType();
	// FUNCTION: ENGINE 0x10ABD580
	template MetaProperty<audio::MixType>::MetaProperty(MetaTypeBase*, MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,audio::MixType>*, MetaMethod0Base<audio::MixType>*, unsigned int);
	// FUNCTION: ENGINE 0x10ABD5C0
	template type_info const* MetaProperty<audio::MixType>::GetValueType();
	// FUNCTION: ENGINE 0x10ABD5D0
	template MetaProperty<audio::Focus>::MetaProperty(MetaTypeBase*, MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,audio::Focus>*, MetaMethod0Base<audio::Focus>*, unsigned int);
	// FUNCTION: ENGINE 0x10ABD610
	template type_info const* MetaProperty<audio::Focus>::GetValueType();
	// FUNCTION: ENGINE 0x10ABD6B0
	template MetaMethod1Base<void,audio::BufferLocation>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ABD750
	template MetaMethod0Base<audio::MixType>::MetaMethod0Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ABD790
	template MetaMethod0Base<audio::Focus>::MetaMethod0Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ABD8D0
	template char const* MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::BufferLocation>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD8E0
	template char const* MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::MixType>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD8F0
	template char const* MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::Focus>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD900
	template char const* MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::WAVEFORMAT>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD910
	template char const* MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::BufferLocation>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD920
	template char const* MetaProperty<audio::BufferLocation>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD930
	template char const* MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::MixType>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD940
	template char const* MetaProperty<audio::MixType>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD950
	template char const* MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::Focus>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD960
	template char const* MetaProperty<audio::Focus>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD970
	template char const* MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::WAVEFORMAT>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD9E0
	template char const* DelegateMetaProperty<audio::BufferLocation>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABD9F0
	template char const* DelegateMetaProperty<audio::MixType>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABDA00
	template char const* DelegateMetaProperty<audio::Focus>::AllocationTag();
	// FUNCTION: ENGINE 0x10ABDEE0
	template int MetaClass<audio::DirectSoundRendererDriverImpl>::Slot5();
	// FUNCTION: ENGINE 0x10ABDEF0
	template void MetaClass<audio::DirectSoundRendererDriverImpl>::Slot6(void*);
	// FUNCTION: ENGINE 0x10ABDF10
	template bool MetaEnum<audio::BufferLocation>::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10ABDF30
	template int MetaEnum<audio::BufferLocation>::Slot5();
	// FUNCTION: ENGINE 0x10ABDF40
	template void MetaEnum<audio::BufferLocation>::Slot6(void*);
	// FUNCTION: ENGINE 0x10ABDF60
	template bool MetaEnum<audio::MixType>::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10ABDF80
	template int MetaEnum<audio::MixType>::Slot5();
	// FUNCTION: ENGINE 0x10ABDF90
	template void MetaEnum<audio::MixType>::Slot6(void*);
	// FUNCTION: ENGINE 0x10ABDFB0
	template bool MetaEnum<audio::Focus>::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10ABDFD0
	template int MetaEnum<audio::Focus>::Slot5();
	// FUNCTION: ENGINE 0x10ABDFE0
	template void MetaEnum<audio::Focus>::Slot6(void*);
	// FUNCTION: ENGINE 0x10ABE080
	template void* MetaClass<audio::DirectSoundRendererDriverImpl>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE0A0
	template void* MetaEnum<audio::BufferLocation>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE0C0
	template void* MetaEnum<audio::MixType>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE0E0
	template void* MetaEnum<audio::Focus>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE150
	template void* MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::BufferLocation>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE170
	template MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::BufferLocation>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::BufferLocation>::Function);
	// FUNCTION: ENGINE 0x10ABE1A0
	template void MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::BufferLocation>::Call(void*, audio::BufferLocation);
	// FUNCTION: ENGINE 0x10ABE1C0
	template MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::BufferLocation>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10ABE1D0
	template void MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::BufferLocation>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABE1F0
	template void* MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::MixType>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE210
	template MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::MixType>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::MixType>::Function);
	// FUNCTION: ENGINE 0x10ABE240
	template void MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::MixType>::Call(void*, audio::MixType);
	// FUNCTION: ENGINE 0x10ABE260
	template MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::MixType>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10ABE270
	template void MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::MixType>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABE290
	template void* MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::Focus>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE2B0
	template MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::Focus>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::Focus>::Function);
	// FUNCTION: ENGINE 0x10ABE2E0
	template void MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::Focus>::Call(void*, audio::Focus);
	// FUNCTION: ENGINE 0x10ABE300
	template MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::Focus>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10ABE310
	template void MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::Focus>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABE330
	template void* MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::WAVEFORMAT>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE350
	template MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::WAVEFORMAT>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::WAVEFORMAT>::Function);
	// FUNCTION: ENGINE 0x10ABE380
	template void MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::WAVEFORMAT>::Call(void*, audio::WAVEFORMAT);
	// FUNCTION: ENGINE 0x10ABE3A0
	template MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::WAVEFORMAT>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10ABE3B0
	template void MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::WAVEFORMAT>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABE3D0
	template void* MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::BufferLocation>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE3F0
	template MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::BufferLocation>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::BufferLocation>::Function);
	// FUNCTION: ENGINE 0x10ABE420
	template audio::BufferLocation MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::BufferLocation>::Call(void*);
	// FUNCTION: ENGINE 0x10ABE440
	template MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::BufferLocation>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10ABE450
	template void MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::BufferLocation>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABE470
	template void* MetaProperty<audio::BufferLocation>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE490
	template void* MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::MixType>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE4B0
	template MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::MixType>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::MixType>::Function);
	// FUNCTION: ENGINE 0x10ABE4E0
	template audio::MixType MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::MixType>::Call(void*);
	// FUNCTION: ENGINE 0x10ABE500
	template MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::MixType>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10ABE510
	template void MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::MixType>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABE530
	template void* MetaProperty<audio::MixType>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE550
	template void* MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::Focus>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE570
	template MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::Focus>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::Focus>::Function);
	// FUNCTION: ENGINE 0x10ABE5A0
	template audio::Focus MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::Focus>::Call(void*);
	// FUNCTION: ENGINE 0x10ABE5C0
	template MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::Focus>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10ABE5D0
	template void MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::Focus>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABE5F0
	template void* MetaProperty<audio::Focus>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE610
	template void* MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::WAVEFORMAT>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE630
	template MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::WAVEFORMAT>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::WAVEFORMAT>::Function);
	// FUNCTION: ENGINE 0x10ABE660
	template audio::WAVEFORMAT MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::WAVEFORMAT>::Call(void*);
	// FUNCTION: ENGINE 0x10ABE680
	template MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::WAVEFORMAT>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10ABE690
	template void MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::WAVEFORMAT>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABE980
	template void* DelegateMetaProperty<audio::BufferLocation>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE9A0
	template void* DelegateMetaProperty<audio::MixType>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABE9C0
	template void* DelegateMetaProperty<audio::Focus>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ABEA70
	template DelegateProperty<audio::BufferLocation>::DelegateProperty();
	// FUNCTION: ENGINE 0x10ABEA80
	template MetaTypeBase* DelegateProperty<audio::BufferLocation>::GetMetaType();
	// FUNCTION: ENGINE 0x10ABEAA0
	template DelegateProperty<audio::MixType>::DelegateProperty();
	// FUNCTION: ENGINE 0x10ABEAB0
	template MetaTypeBase* DelegateProperty<audio::MixType>::GetMetaType();
	// FUNCTION: ENGINE 0x10ABEAD0
	template DelegateProperty<audio::Focus>::DelegateProperty();
	// FUNCTION: ENGINE 0x10ABEAE0
	template MetaTypeBase* DelegateProperty<audio::Focus>::GetMetaType();
	// FUNCTION: ENGINE 0x10ABF730
	template void MetaClass<audio::DirectSoundRendererDriverImpl>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ABF880
	template void MetaEnum<audio::BufferLocation>::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10ABF920
	template void MetaEnum<audio::MixType>::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10ABF9C0
	template void MetaEnum<audio::Focus>::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10ABF9D0
	template MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::BufferLocation>* MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::BufferLocation>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::BufferLocation>::Function);
	// FUNCTION: ENGINE 0x10ABFA20
	template MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::BufferLocation>* MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::BufferLocation>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::BufferLocation>::Function);
	// FUNCTION: ENGINE 0x10ABFA70
	template void MetaProperty<audio::BufferLocation>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,audio::BufferLocation>*, MetaMethod0Base<audio::BufferLocation>*, unsigned int);
	// FUNCTION: ENGINE 0x10ABFAC0
	template MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::MixType>* MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::MixType>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::MixType>::Function);
	// FUNCTION: ENGINE 0x10ABFB10
	template MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::MixType>* MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::MixType>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::MixType>::Function);
	// FUNCTION: ENGINE 0x10ABFB60
	template void MetaProperty<audio::MixType>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,audio::MixType>*, MetaMethod0Base<audio::MixType>*, unsigned int);
	// FUNCTION: ENGINE 0x10ABFBB0
	template MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::Focus>* MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::Focus>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::Focus>::Function);
	// FUNCTION: ENGINE 0x10ABFC00
	template MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::Focus>* MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::Focus>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::Focus>::Function);
	// FUNCTION: ENGINE 0x10ABFC50
	template void MetaProperty<audio::Focus>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,audio::Focus>*, MetaMethod0Base<audio::Focus>*, unsigned int);
	// FUNCTION: ENGINE 0x10ABFCA0
	template MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::WAVEFORMAT>* MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::WAVEFORMAT>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,void,audio::WAVEFORMAT>::Function);
	// FUNCTION: ENGINE 0x10ABFCF0
	template MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::WAVEFORMAT>* MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::WAVEFORMAT>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<audio::DirectSoundRendererDriverImpl,audio::DirectSoundRendererDriverImpl,audio::WAVEFORMAT>::Function);
	// FUNCTION: ENGINE 0x10ABFEB0
	template DelegateMetaProperty<audio::BufferLocation>::DelegateMetaProperty(void*, MetaProperty<audio::BufferLocation>*);
	// FUNCTION: ENGINE 0x10ABFEE0
	template void DelegateMetaProperty<audio::BufferLocation>::SetObject(void*);
	// FUNCTION: ENGINE 0x10ABFEF0
	template void DelegateMetaProperty<audio::BufferLocation>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABFF10
	template DelegateMetaProperty<audio::BufferLocation>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x10ABFF20
	template audio::BufferLocation DelegateMetaProperty<audio::BufferLocation>::Get();
	// FUNCTION: ENGINE 0x10ABFF40
	template void DelegateMetaProperty<audio::BufferLocation>::Set(audio::BufferLocation);
	// FUNCTION: ENGINE 0x10ABFF60
	template DelegateMetaProperty<audio::MixType>::DelegateMetaProperty(void*, MetaProperty<audio::MixType>*);
	// FUNCTION: ENGINE 0x10ABFF90
	template void DelegateMetaProperty<audio::MixType>::SetObject(void*);
	// FUNCTION: ENGINE 0x10ABFFA0
	template void DelegateMetaProperty<audio::MixType>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ABFFC0
	template DelegateMetaProperty<audio::MixType>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x10ABFFD0
	template audio::MixType DelegateMetaProperty<audio::MixType>::Get();
	// FUNCTION: ENGINE 0x10ABFFF0
	template void DelegateMetaProperty<audio::MixType>::Set(audio::MixType);
}
