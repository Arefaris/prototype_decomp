// The property nodes of the mgraph library (0x10B13850 - 0x10B3F300): the template instances of the property node, its events and
// the delegates of its channels for the scalar packet types, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/propertynode.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B13850
	template void mgraph::PropertyNode<mgraph::Packet<unsigned int> >::SetDefaultValue(unsigned int const*);
	// FUNCTION: ENGINE 0x10B13880
	template mgraph::PropertyChannel<unsigned int>::PropertyChannel(unsigned int const&);
	// FUNCTION: ENGINE 0x10B138B0
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B138C0
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B13930
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<unsigned int> >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B13950
	template void mgraph::PropertyNode<mgraph::Packet<unsigned int> >::SetPropertyValue(unsigned int, DynamicPropertyBase const*, int);
	// FUNCTION: ENGINE 0x10B139A0
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B139C0
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B139E0
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<unsigned int> >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<unsigned int> >*, unsigned int, unsigned int*);
	// FUNCTION: ENGINE 0x10B13A20
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<unsigned int> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B13A40
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B13A60
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<unsigned int> >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B13A90
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<unsigned int> >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<unsigned int> >*, unsigned int, unsigned int const&, int);
	// FUNCTION: ENGINE 0x10B13AD0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<unsigned int> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B13AF0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B13B80
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<unsigned int> >::~PropertyNodeInputEvent();
	// FUNCTION: ENGINE 0x10B13C40
	template void mgraph::PropertyNode<mgraph::Packet<unsigned int> >::PostInputEvent(mgraph::EventQueue*, unsigned int, unsigned int const*);
	// FUNCTION: ENGINE 0x10B13CC0
	template void mgraph::PropertyNode<mgraph::Packet<unsigned int> >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B13D50
	template void mgraph::PropertyNode<mgraph::Packet<unsigned int> >::PostOutputEvent(mgraph::EventQueue*, unsigned int, unsigned int*);
	// FUNCTION: ENGINE 0x10B13DD0
	template unsigned int const* mgraph::PropertyNode<mgraph::Packet<unsigned int> >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B13DF0
	template void mgraph::PropertyNode<mgraph::Packet<unsigned int> >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B13E10
	template void mgraph::PropertyNode<mgraph::Packet<unsigned int> >::SetChannelValue(unsigned int const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B13E90
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<unsigned int> >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<unsigned int> >*, unsigned int);
	// FUNCTION: ENGINE 0x10B13ED0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<unsigned int> >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B13EE0
	template unsigned int mgraph::PropertyPropertyDelegate<mgraph::Packet<unsigned int> >::Get();
	// FUNCTION: ENGINE 0x10B13F00
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<unsigned int> >::Set(unsigned int);
	// FUNCTION: ENGINE 0x10B140B0
	template void mgraph::PropertyNode<mgraph::Packet<unsigned int> >::SetNumChannels(unsigned short);
	// FUNCTION: ENGINE 0x10B14190
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B141D0
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B14750
	template void mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::SetDefaultValue(unsigned __int64 const*);
	// FUNCTION: ENGINE 0x10B147C0
	template mgraph::PropertyChannel<unsigned __int64>::PropertyChannel(unsigned __int64 const&);
	// FUNCTION: ENGINE 0x10B147F0
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B14800
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B14870
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B14890
	template void mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::SetPropertyValue(unsigned int, DynamicPropertyBase const*, int);
	// FUNCTION: ENGINE 0x10B148F0
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B14910
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B14930
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<unsigned __int64> >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >*, unsigned int, unsigned __int64*);
	// FUNCTION: ENGINE 0x10B14970
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<unsigned __int64> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B149A0
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B149C0
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<unsigned __int64> >::~PropertyNodeInputEvent();
	// FUNCTION: ENGINE 0x10B149F0
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<unsigned __int64> >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >*, unsigned int, unsigned __int64 const&, int);
	// FUNCTION: ENGINE 0x10B14A40
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<unsigned __int64> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B14A60
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B14AF0
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<unsigned __int64> >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B14BC0
	template void mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::PostInputEvent(mgraph::EventQueue*, unsigned int, unsigned __int64 const*);
	// FUNCTION: ENGINE 0x10B14C50
	template void mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B14CE0
	template void mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::PostOutputEvent(mgraph::EventQueue*, unsigned int, unsigned __int64*);
	// FUNCTION: ENGINE 0x10B14D60
	template unsigned __int64 const* mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B14D70
	template void mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B14D90
	template void mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::SetChannelValue(unsigned __int64 const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B14E20
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<unsigned __int64> >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >*, unsigned int);
	// FUNCTION: ENGINE 0x10B14E60
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<unsigned __int64> >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B14E70
	template unsigned __int64 mgraph::PropertyPropertyDelegate<mgraph::Packet<unsigned __int64> >::Get();
	// FUNCTION: ENGINE 0x10B14E90
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<unsigned __int64> >::Set(unsigned __int64);
	// FUNCTION: ENGINE 0x10B15030
	template void mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::SetNumChannels(unsigned short);
	// FUNCTION: ENGINE 0x10B15150
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B37B50
	template void mgraph::PropertyNode<mgraph::Packet<bool> >::SetDefaultValue(bool const*);
	// FUNCTION: ENGINE 0x10B37B80
	template mgraph::PropertyChannel<bool>::PropertyChannel(bool const&);
	// FUNCTION: ENGINE 0x10B37BB0
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B37BC0
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B37C30
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<bool> >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B37C50
	template void mgraph::PropertyNode<mgraph::Packet<bool> >::SetPropertyValue(unsigned int, DynamicPropertyBase const*, int);
	// FUNCTION: ENGINE 0x10B37CA0
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B37CC0
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B37CE0
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<bool> >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<bool> >*, unsigned int, bool*);
	// FUNCTION: ENGINE 0x10B37D20
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<bool> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B37D40
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B37D60
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<bool> >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B37D90
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<bool> >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<bool> >*, unsigned int, bool const&, int);
	// FUNCTION: ENGINE 0x10B37DD0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<bool> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B37DF0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B37E80
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<bool> >::~PropertyNodeInputEvent();
	// FUNCTION: ENGINE 0x10B37F30
	template void mgraph::PropertyNode<mgraph::Packet<bool> >::PostInputEvent(mgraph::EventQueue*, unsigned int, bool const*);
	// FUNCTION: ENGINE 0x10B37FB0
	template void mgraph::PropertyNode<mgraph::Packet<bool> >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B38040
	template void mgraph::PropertyNode<mgraph::Packet<bool> >::PostOutputEvent(mgraph::EventQueue*, unsigned int, bool*);
	// FUNCTION: ENGINE 0x10B380C0
	template bool const* mgraph::PropertyNode<mgraph::Packet<bool> >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B380D0
	template void mgraph::PropertyNode<mgraph::Packet<bool> >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B380E0
	template void mgraph::PropertyNode<mgraph::Packet<bool> >::SetChannelValue(bool const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B38160
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<bool> >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<bool> >*, unsigned int);
	// FUNCTION: ENGINE 0x10B381A0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<bool> >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B381B0
	template bool mgraph::PropertyPropertyDelegate<mgraph::Packet<bool> >::Get();
	// FUNCTION: ENGINE 0x10B381C0
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<bool> >::Set(bool);
	// FUNCTION: ENGINE 0x10B38360
	template void mgraph::PropertyNode<mgraph::Packet<bool> >::SetNumChannels(unsigned short);
	// FUNCTION: ENGINE 0x10B39170
	template void mgraph::PropertyNode<mgraph::Packet<float> >::SetDefaultValue(float const*);
	// FUNCTION: ENGINE 0x10B391A0
	template mgraph::PropertyChannel<float>::PropertyChannel(float const&);
	// FUNCTION: ENGINE 0x10B391D0
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B391E0
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B39250
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<float> >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B39270
	template void mgraph::PropertyNode<mgraph::Packet<float> >::SetPropertyValue(unsigned int, DynamicPropertyBase const*, int);
	// FUNCTION: ENGINE 0x10B392C0
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B392E0
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B39300
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<float> >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<float> >*, unsigned int, float*);
	// FUNCTION: ENGINE 0x10B39340
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<float> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B39360
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B39380
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<float> >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B393B0
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<float> >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<float> >*, unsigned int, float const&, int);
	// FUNCTION: ENGINE 0x10B393F0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<float> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B39410
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B394A0
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<float> >::~PropertyNodeInputEvent();
	// FUNCTION: ENGINE 0x10B39560
	template void mgraph::PropertyNode<mgraph::Packet<float> >::PostInputEvent(mgraph::EventQueue*, unsigned int, float const*);
	// FUNCTION: ENGINE 0x10B395E0
	template void mgraph::PropertyNode<mgraph::Packet<float> >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B39670
	template void mgraph::PropertyNode<mgraph::Packet<float> >::PostOutputEvent(mgraph::EventQueue*, unsigned int, float*);
	// FUNCTION: ENGINE 0x10B396F0
	template float const* mgraph::PropertyNode<mgraph::Packet<float> >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B39710
	template void mgraph::PropertyNode<mgraph::Packet<float> >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B39730
	template void mgraph::PropertyNode<mgraph::Packet<float> >::SetChannelValue(float const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B397C0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<float> >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<float> >*, unsigned int);
	// FUNCTION: ENGINE 0x10B39800
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<float> >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B39810
	template float mgraph::PropertyPropertyDelegate<mgraph::Packet<float> >::Get();
	// FUNCTION: ENGINE 0x10B39830
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<float> >::Set(float);
	// FUNCTION: ENGINE 0x10B399E0
	template void mgraph::PropertyNode<mgraph::Packet<float> >::SetNumChannels(unsigned short);
}

namespace om
{
	// FUNCTION: ENGINE 0x10B130A0
	template void DynamicArray<mgraph::PropertyChannel<float>,unsigned short>::ReleaseElements(mgraph::PropertyChannel<float>*, unsigned short);
	// FUNCTION: ENGINE 0x10B13530
	template void DynamicArray<mgraph::PropertyChannel<unsigned int>,unsigned short>::ReleaseElements(mgraph::PropertyChannel<unsigned int>*, unsigned short);
	// FUNCTION: ENGINE 0x10B13900
	template mgraph::PropertyChannel<unsigned int>& DynamicArray<mgraph::PropertyChannel<unsigned int>,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B13920
	template char const* DynamicArray<mgraph::PropertyChannel<unsigned int>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B13C20
	template mgraph::PropertyChannel<unsigned int>* DynamicArray<mgraph::PropertyChannel<unsigned int>,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B13F80
	template void DynamicArray<mgraph::PropertyChannel<unsigned int>,unsigned short>::Resize(unsigned short, mgraph::PropertyChannel<unsigned int> const&);
	// FUNCTION: ENGINE 0x10B14450
	template void DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::ReleaseElements(mgraph::PropertyChannel<unsigned __int64>*, unsigned short);
	// FUNCTION: ENGINE 0x10B14840
	template mgraph::PropertyChannel<unsigned __int64>& DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B14860
	template char const* DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B14BA0
	template mgraph::PropertyChannel<unsigned __int64>* DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B14F10
	template void DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::Resize(unsigned short, mgraph::PropertyChannel<unsigned __int64> const&);
	// FUNCTION: ENGINE 0x10B37C00
	template mgraph::PropertyChannel<bool>& DynamicArray<mgraph::PropertyChannel<bool>,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B37C20
	template char const* DynamicArray<mgraph::PropertyChannel<bool>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B37F10
	template mgraph::PropertyChannel<bool>* DynamicArray<mgraph::PropertyChannel<bool>,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B38240
	template void DynamicArray<mgraph::PropertyChannel<bool>,unsigned short>::Resize(unsigned short, mgraph::PropertyChannel<bool> const&);
	// FUNCTION: ENGINE 0x10B39220
	template mgraph::PropertyChannel<float>& DynamicArray<mgraph::PropertyChannel<float>,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B39240
	template char const* DynamicArray<mgraph::PropertyChannel<float>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B39540
	template mgraph::PropertyChannel<float>* DynamicArray<mgraph::PropertyChannel<float>,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B398B0
	template void DynamicArray<mgraph::PropertyChannel<float>,unsigned short>::Resize(unsigned short, mgraph::PropertyChannel<float> const&);
}
