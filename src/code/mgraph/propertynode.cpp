// The property nodes of the mgraph library (0x10B13850 - 0x10B3F300): the template instances of the property node, its events and
// the delegates of its channels for the scalar packet types, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/propertynode.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B00600
	void PropertyNodeBase::PostPropertyValue(unsigned int channel, EventQueue* queue, const om::DynamicPropertyBase* property)
	{
	}

	// FUNCTION: ENGINE 0x10B00610
	void PropertyNodeBase::SetPropertyValue(unsigned int channel, const om::DynamicPropertyBase* property, int unknown)
	{
	}

	// FUNCTION: ENGINE 0x10B00620
	om::MetaTypeBase* PropertyNodeBase::GetValueMetaType()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10B00630
	om::DelegatePropertyBase* PropertyNodeBase::CreateDelegate(unsigned int channel)
	{
		return 0;
	}

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
	template void mgraph::PropertyNode<mgraph::Packet<unsigned int> >::SetNumChannels(unsigned int);
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
	template void mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B15150
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B15190
	template mgraph::PropertyChannel<DynamicArray<unsigned __int64,unsigned short> >::~PropertyChannel();
	// FUNCTION: ENGINE 0x10B16300
	template void mgraph::PropertyNode<mgraph::Packet<Complex> >::SetDefaultValue(Complex const*);
	// FUNCTION: ENGINE 0x10B163A0
	template mgraph::PropertyChannel<Complex>::PropertyChannel(Complex const&);
	// FUNCTION: ENGINE 0x10B163D0
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B163E0
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B16450
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<Complex> >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B164D0
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B164F0
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B16510
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<Complex> >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<Complex> >*, unsigned int, Complex*);
	// FUNCTION: ENGINE 0x10B16550
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<Complex> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B16580
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B165A0
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<Complex> >::~PropertyNodeInputEvent();
	// FUNCTION: ENGINE 0x10B165D0
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<Complex> >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<Complex> >*, unsigned int, Complex const&, int);
	// FUNCTION: ENGINE 0x10B16620
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<Complex> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B16640
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B166D0
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<Complex> >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B167A0
	template void mgraph::PropertyNode<mgraph::Packet<Complex> >::PostInputEvent(mgraph::EventQueue*, unsigned int, Complex const*);
	// FUNCTION: ENGINE 0x10B16830
	template void mgraph::PropertyNode<mgraph::Packet<Complex> >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B168C0
	template void mgraph::PropertyNode<mgraph::Packet<Complex> >::PostOutputEvent(mgraph::EventQueue*, unsigned int, Complex*);
	// FUNCTION: ENGINE 0x10B16940
	template Complex const* mgraph::PropertyNode<mgraph::Packet<Complex> >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B16950
	template void mgraph::PropertyNode<mgraph::Packet<Complex> >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B16970
	template void mgraph::PropertyNode<mgraph::Packet<Complex> >::SetChannelValue(Complex const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B169F0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<Complex> >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<Complex> >*, unsigned int);
	// FUNCTION: ENGINE 0x10B16A30
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<Complex> >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B16A40
	template Complex mgraph::PropertyPropertyDelegate<mgraph::Packet<Complex> >::Get();
	// FUNCTION: ENGINE 0x10B16A70
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<Complex> >::Set(Complex);
	// FUNCTION: ENGINE 0x10B16C10
	template void mgraph::PropertyNode<mgraph::Packet<Complex> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B16D30
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B16F80
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B37B50
	template void mgraph::PropertyNode<mgraph::Packet<bool> >::SetDefaultValue(bool const*);
	// FUNCTION: ENGINE 0x10B37B80
	template mgraph::PropertyChannel<bool>::PropertyChannel(bool const&);
	// FUNCTION: ENGINE 0x10B37BA0
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B37BB0
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B37BC0
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B37C30
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<bool> >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B37C50
	template void mgraph::PropertyNode<mgraph::Packet<bool> >::SetPropertyValue(unsigned int, DynamicPropertyBase const*, int);
	// FUNCTION: ENGINE 0x10B37C80
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<bool> >::operator new(size_t);
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
	template void mgraph::PropertyNode<mgraph::Packet<bool> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B385A0
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<bool,unsigned short>> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B385B0
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B385C0
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B38610
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B38630
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >::SetDefaultValue(DynamicArray<bool,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B38640
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<bool,unsigned short>> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B38660
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B38680
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B386A0
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<bool,unsigned short> > >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >*, unsigned int, DynamicArray<bool,unsigned short>*);
	// FUNCTION: ENGINE 0x10B386E0
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B38700
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B38720
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<bool,unsigned short> > >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B38750
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<bool,unsigned short> > >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >*, unsigned int, DynamicArray<bool,unsigned short> const&, int);
	// FUNCTION: ENGINE 0x10B387A0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B387C0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B38800
	template mgraph::PropertyChannel<DynamicArray<bool,unsigned short> >::PropertyChannel(DynamicArray<bool,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B388E0
	template mgraph::PropertyChannel<DynamicArray<bool,unsigned short> >::PropertyChannel(mgraph::PropertyChannel<DynamicArray<bool,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B38910
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >::PostInputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<bool,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B38A50
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >::PostOutputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<bool,unsigned short>*);
	// FUNCTION: ENGINE 0x10B38AD0
	template DynamicArray<bool,unsigned short> const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B38AE0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B38B50
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<bool,unsigned short> > >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >*, unsigned int);
	// FUNCTION: ENGINE 0x10B38B90
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<bool,unsigned short> > >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B38BA0
	template DynamicArray<bool,unsigned short> mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Get();
	// FUNCTION: ENGINE 0x10B38BC0
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Set(DynamicArray<bool,unsigned short>);
	// FUNCTION: ENGINE 0x10B38DB0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >::SetChannelValue(DynamicArray<bool,unsigned short> const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B38F50
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B39170
	template void mgraph::PropertyNode<mgraph::Packet<float> >::SetDefaultValue(float const*);
	// FUNCTION: ENGINE 0x10B391A0
	template mgraph::PropertyChannel<float>::PropertyChannel(float const&);
	// FUNCTION: ENGINE 0x10B391C0
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B391D0
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B391E0
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B39250
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<float> >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B39270
	template void mgraph::PropertyNode<mgraph::Packet<float> >::SetPropertyValue(unsigned int, DynamicPropertyBase const*, int);
	// FUNCTION: ENGINE 0x10B392A0
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<float> >::operator new(size_t);
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
	template void mgraph::PropertyNode<mgraph::Packet<float> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B39C20
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<float,unsigned short>> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B39C30
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<float,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B39C40
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<float,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B39C90
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B39CB0
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<float,unsigned short>> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B39CD0
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B39CF0
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B39D10
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<float,unsigned short> > >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >*, unsigned int, DynamicArray<float,unsigned short>*);
	// FUNCTION: ENGINE 0x10B39D50
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B39D70
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<float,unsigned short> > >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B39DA0
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<float,unsigned short> > >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >*, unsigned int, DynamicArray<float,unsigned short> const&, int);
	// FUNCTION: ENGINE 0x10B39DF0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<float,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B39E10
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B39E30
	template mgraph::PropertyChannel<DynamicArray<float,unsigned short> >::PropertyChannel(DynamicArray<float,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B39EF0
	template mgraph::PropertyChannel<DynamicArray<float,unsigned short> >::PropertyChannel(mgraph::PropertyChannel<DynamicArray<float,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B39F20
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >::PostInputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<float,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B3A060
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >::PostOutputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<float,unsigned short>*);
	// FUNCTION: ENGINE 0x10B3A0E0
	template DynamicArray<float,unsigned short> const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B3A0F0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >::SetDefaultValue(DynamicArray<float,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B3A100
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B3A170
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<float,unsigned short> > >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >*, unsigned int);
	// FUNCTION: ENGINE 0x10B3A1B0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<float,unsigned short> > >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B3A1C0
	template DynamicArray<float,unsigned short> mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<float,unsigned short> > >::Get();
	// FUNCTION: ENGINE 0x10B3A1E0
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<float,unsigned short> > >::Set(DynamicArray<float,unsigned short>);
	// FUNCTION: ENGINE 0x10B3A220
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<float,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3A400
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >::SetChannelValue(DynamicArray<float,unsigned short> const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B3A530
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B3A850
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<unsigned int,unsigned short>> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3A860
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3A870
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3A8C0
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B3A8E0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::SetDefaultValue(DynamicArray<unsigned int,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B3A8F0
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<unsigned int,unsigned short>> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3A910
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3A930
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3A950
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >*, unsigned int, DynamicArray<unsigned int,unsigned short>*);
	// FUNCTION: ENGINE 0x10B3A990
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3A9B0
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3A9D0
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B3AA00
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >*, unsigned int, DynamicArray<unsigned int,unsigned short> const&, int);
	// FUNCTION: ENGINE 0x10B3AA50
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3AA70
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3AA90
	template mgraph::PropertyChannel<DynamicArray<unsigned int,unsigned short> >::PropertyChannel(DynamicArray<unsigned int,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B3AB70
	template mgraph::PropertyChannel<DynamicArray<unsigned int,unsigned short> >::PropertyChannel(mgraph::PropertyChannel<DynamicArray<unsigned int,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B3ABA0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::PostInputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<unsigned int,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B3ACE0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::PostOutputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<unsigned int,unsigned short>*);
	// FUNCTION: ENGINE 0x10B3AD60
	template DynamicArray<unsigned int,unsigned short> const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B3AD70
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B3ADE0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >*, unsigned int);
	// FUNCTION: ENGINE 0x10B3AE20
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B3AE30
	template DynamicArray<unsigned int,unsigned short> mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Get();
	// FUNCTION: ENGINE 0x10B3AE50
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Set(DynamicArray<unsigned int,unsigned short>);
	// FUNCTION: ENGINE 0x10B3B050
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::SetChannelValue(DynamicArray<unsigned int,unsigned short> const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B3B1F0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B3B520
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short>> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3B530
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3B540
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3B590
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B3B5B0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::SetDefaultValue(DynamicArray<unsigned __int64,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B3B5C0
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short>> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3B5E0
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3B600
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3B620
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >*, unsigned int, DynamicArray<unsigned __int64,unsigned short>*);
	// FUNCTION: ENGINE 0x10B3B660
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3B680
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3B6A0
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B3B6D0
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >*, unsigned int, DynamicArray<unsigned __int64,unsigned short> const&, int);
	// FUNCTION: ENGINE 0x10B3B720
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3B740
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3B780
	template mgraph::PropertyChannel<DynamicArray<unsigned __int64,unsigned short> >::PropertyChannel(DynamicArray<unsigned __int64,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B3B870
	template mgraph::PropertyChannel<DynamicArray<unsigned __int64,unsigned short> >::PropertyChannel(mgraph::PropertyChannel<DynamicArray<unsigned __int64,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B3B8A0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::PostInputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<unsigned __int64,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B3B9E0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::PostOutputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<unsigned __int64,unsigned short>*);
	// FUNCTION: ENGINE 0x10B3BA60
	template DynamicArray<unsigned __int64,unsigned short> const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B3BA70
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B3BAE0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >*, unsigned int);
	// FUNCTION: ENGINE 0x10B3BB20
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B3BB30
	template DynamicArray<unsigned __int64,unsigned short> mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Get();
	// FUNCTION: ENGINE 0x10B3BB50
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Set(DynamicArray<unsigned __int64,unsigned short>);
	// FUNCTION: ENGINE 0x10B3BD50
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::SetChannelValue(DynamicArray<unsigned __int64,unsigned short> const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B3BEF0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B3C200
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3C320
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3CCD0
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<String,unsigned short>> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3CD70
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<String,unsigned short>> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3D9D0
	template void mgraph::PropertyNode<mgraph::Packet<Vector> >::SetDefaultValue(Vector const*);
	// FUNCTION: ENGINE 0x10B3DA10
	template mgraph::PropertyChannel<Vector>::PropertyChannel(Vector const&);
	// FUNCTION: ENGINE 0x10B3DA40
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3DA50
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3DA60
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3DAE0
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<Vector> >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B3DB40
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3DB60
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3DB80
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3DBA0
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<Vector> >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<Vector> >*, unsigned int, Vector*);
	// FUNCTION: ENGINE 0x10B3DBE0
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<Vector> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3DC10
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3DC30
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<Vector> >::~PropertyNodeInputEvent();
	// FUNCTION: ENGINE 0x10B3DC60
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<Vector> >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<Vector> >*, unsigned int, Vector const&, int);
	// FUNCTION: ENGINE 0x10B3DCB0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<Vector> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3DCD0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3DD70
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<Vector> >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B3DE50
	template void mgraph::PropertyNode<mgraph::Packet<Vector> >::PostInputEvent(mgraph::EventQueue*, unsigned int, Vector const*);
	// FUNCTION: ENGINE 0x10B3DEE0
	template void mgraph::PropertyNode<mgraph::Packet<Vector> >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B3DF70
	template void mgraph::PropertyNode<mgraph::Packet<Vector> >::PostOutputEvent(mgraph::EventQueue*, unsigned int, Vector*);
	// FUNCTION: ENGINE 0x10B3DFF0
	template Vector const* mgraph::PropertyNode<mgraph::Packet<Vector> >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B3E010
	template void mgraph::PropertyNode<mgraph::Packet<Vector> >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B3E030
	template void mgraph::PropertyNode<mgraph::Packet<Vector> >::SetChannelValue(Vector const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B3E0F0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<Vector> >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<Vector> >*, unsigned int);
	// FUNCTION: ENGINE 0x10B3E130
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<Vector> >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B3E140
	template Vector mgraph::PropertyPropertyDelegate<mgraph::Packet<Vector> >::Get();
	// FUNCTION: ENGINE 0x10B3E170
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<Vector> >::Set(Vector);
	// FUNCTION: ENGINE 0x10B3E330
	template void mgraph::PropertyNode<mgraph::Packet<Vector> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B3E580
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<Vector,unsigned short>> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3E590
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3E5A0
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3E5F0
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B3E610
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::SetDefaultValue(DynamicArray<Vector,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B3E620
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<Vector,unsigned short>> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3E640
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3E660
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3E680
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >*, unsigned int, DynamicArray<Vector,unsigned short>*);
	// FUNCTION: ENGINE 0x10B3E6C0
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3E6E0
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3E700
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B3E730
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >*, unsigned int, DynamicArray<Vector,unsigned short> const&, int);
	// FUNCTION: ENGINE 0x10B3E780
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3E7A0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3E7E0
	template mgraph::PropertyChannel<DynamicArray<Vector,unsigned short> >::PropertyChannel(DynamicArray<Vector,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B3E8F0
	template mgraph::PropertyChannel<DynamicArray<Vector,unsigned short> >::PropertyChannel(mgraph::PropertyChannel<DynamicArray<Vector,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B3E920
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::PostInputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<Vector,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B3EA60
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::PostOutputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<Vector,unsigned short>*);
	// FUNCTION: ENGINE 0x10B3EAE0
	template DynamicArray<Vector,unsigned short> const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B3EAF0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B3EB60
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >*, unsigned int);
	// FUNCTION: ENGINE 0x10B3EBA0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B3EBB0
	template DynamicArray<Vector,unsigned short> mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Get();
	// FUNCTION: ENGINE 0x10B3EBD0
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Set(DynamicArray<Vector,unsigned short>);
	// FUNCTION: ENGINE 0x10B3EE90
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::SetChannelValue(DynamicArray<Vector,unsigned short> const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B3F030
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B3F240
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short>> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3F2E0
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short>> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3F770
	template DynamicArray<Complex,unsigned short> const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B3F780
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B3FF20
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<Complex,unsigned short>> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3FF90
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B3FFB0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::SetDefaultValue(DynamicArray<Complex,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B3C1B0
	template void mgraph::PropertyNode<mgraph::Packet<String> >::SetDefaultValue(String const*);
	// FUNCTION: ENGINE 0x10B3C1E0
	template mgraph::PropertyChannel<String>::PropertyChannel(String const&);
	// FUNCTION: ENGINE 0x10B3C210
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3C220
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3C2C0
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<String> >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B3C340
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3C360
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3C380
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<String> >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<String> >*, unsigned int, String*);
	// FUNCTION: ENGINE 0x10B3C3C0
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<String> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3C3E0
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3C400
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<String> >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B3C430
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<String> >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<String> >*, unsigned int, String const&, int);
	// FUNCTION: ENGINE 0x10B3C480
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<String> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3C4A0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3C600
	template void mgraph::PropertyNode<mgraph::Packet<String> >::PostInputEvent(mgraph::EventQueue*, unsigned int, String const*);
	// FUNCTION: ENGINE 0x10B3C730
	template void mgraph::PropertyNode<mgraph::Packet<String> >::PostOutputEvent(mgraph::EventQueue*, unsigned int, String*);
	// FUNCTION: ENGINE 0x10B3C7B0
	template String const* mgraph::PropertyNode<mgraph::Packet<String> >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B3C7D0
	template void mgraph::PropertyNode<mgraph::Packet<String> >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B3C7F0
	template void mgraph::PropertyNode<mgraph::Packet<String> >::SetChannelValue(String const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B3C850
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<String> >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<String> >*, unsigned int);
	// FUNCTION: ENGINE 0x10B3C890
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<String> >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B3C8A0
	template String mgraph::PropertyPropertyDelegate<mgraph::Packet<String> >::Get();
	// FUNCTION: ENGINE 0x10B3C8D0
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<String> >::Set(String);
	// FUNCTION: ENGINE 0x10B3CAE0
	template void mgraph::PropertyNode<mgraph::Packet<String> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B3CCE0
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3CCF0
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3CD40
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B3CD60
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::SetDefaultValue(DynamicArray<String,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B3CD90
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3CDB0
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3CDD0
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<String,unsigned short> > >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >*, unsigned int, DynamicArray<String,unsigned short>*);
	// FUNCTION: ENGINE 0x10B3CE10
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3CE30
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<String,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3CE50
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<String,unsigned short> > >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B3CE80
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<String,unsigned short> > >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >*, unsigned int, DynamicArray<String,unsigned short> const&, int);
	// FUNCTION: ENGINE 0x10B3CED0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<String,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3CEF0
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3CF10
	template mgraph::PropertyChannel<DynamicArray<String,unsigned short> >::PropertyChannel(DynamicArray<String,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B3CFF0
	template mgraph::PropertyChannel<DynamicArray<String,unsigned short> >::PropertyChannel(mgraph::PropertyChannel<DynamicArray<String,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B3D020
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::PostInputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<String,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B3D150
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::PostOutputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<String,unsigned short>*);
	// FUNCTION: ENGINE 0x10B3D1D0
	template DynamicArray<String,unsigned short> const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B3D1E0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B3D2C0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<String,unsigned short> > >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B3D2D0
	template DynamicArray<String,unsigned short> mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<String,unsigned short> > >::Get();
	// FUNCTION: ENGINE 0x10B3D5E0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::SetChannelValue(DynamicArray<String,unsigned short> const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B4FB10
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B4FB20
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B4FB30
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B4FB80
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B4FBA0
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B4FBC0
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B4FBE0
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B4FC00
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<mgraph::EnvelopeData> >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >*, unsigned int, mgraph::EnvelopeData*);
	// FUNCTION: ENGINE 0x10B4FC40
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<mgraph::EnvelopeData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B4FC60
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<mgraph::EnvelopeData> >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B4FD30
	template void mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >::PostOutputEvent(mgraph::EventQueue*, unsigned int, mgraph::EnvelopeData*);
	// FUNCTION: ENGINE 0x10B4FDB0
	template mgraph::EnvelopeData const* mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B4FDD0
	template void mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B4FDF0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<mgraph::EnvelopeData> >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >*, unsigned int);
	// FUNCTION: ENGINE 0x10B4FE30
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<mgraph::EnvelopeData> >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B4FEA0
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<mgraph::EnvelopeData> >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >*, unsigned int, mgraph::EnvelopeData const&, int);
	// FUNCTION: ENGINE 0x10B4FF00
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<mgraph::EnvelopeData> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B4FF20
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<mgraph::EnvelopeData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B4FF90
	template mgraph::PropertyChannel<mgraph::EnvelopeData>::PropertyChannel(mgraph::EnvelopeData const&);
	// FUNCTION: ENGINE 0x10B50020
	template mgraph::PropertyChannel<mgraph::EnvelopeData>::PropertyChannel(mgraph::PropertyChannel<mgraph::EnvelopeData> const&);
	// FUNCTION: ENGINE 0x10B500B0
	template void mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >::PostInputEvent(mgraph::EventQueue*, unsigned int, mgraph::EnvelopeData const*);
	// FUNCTION: ENGINE 0x10B501C0
	template void mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >::SetDefaultValue(mgraph::EnvelopeData const*);
	// FUNCTION: ENGINE 0x10B50290
	template mgraph::EnvelopeData mgraph::PropertyPropertyDelegate<mgraph::Packet<mgraph::EnvelopeData> >::Get();
	// FUNCTION: ENGINE 0x10B502D0
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<mgraph::EnvelopeData> >::Set(mgraph::EnvelopeData);
	// FUNCTION: ENGINE 0x10B50330
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<mgraph::EnvelopeData> >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B50470
	template void mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >::SetChannelValue(mgraph::EnvelopeData const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B3DB00
	template void mgraph::PropertyNode<mgraph::Packet<Vector> >::SetPropertyValue(unsigned int, DynamicPropertyBase const*, int);
	// FUNCTION: ENGINE 0x10B3C2E0
	template void mgraph::PropertyNode<mgraph::Packet<String> >::SetPropertyValue(unsigned int, DynamicPropertyBase const*, int);
	// FUNCTION: ENGINE 0x10B3C690
	template void mgraph::PropertyNode<mgraph::Packet<String> >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B3D0B0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B50110
	template void mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B13B10
	template void mgraph::PropertyChannel<unsigned int>::Update(mgraph::PropertyNodeBase*, mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B13E40
	template void mgraph::PropertyNode<mgraph::Packet<unsigned int> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B14A80
	template void mgraph::PropertyChannel<unsigned __int64>::Update(mgraph::PropertyNodeBase*, mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B14DD0
	template void mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B16660
	template void mgraph::PropertyChannel<Complex>::Update(mgraph::PropertyNodeBase*, mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B169A0
	template void mgraph::PropertyNode<mgraph::Packet<Complex> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B37E10
	template void mgraph::PropertyChannel<bool>::Update(mgraph::PropertyNodeBase*, mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B38110
	template void mgraph::PropertyNode<mgraph::Packet<bool> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B39430
	template void mgraph::PropertyChannel<float>::Update(mgraph::PropertyNodeBase*, mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B39770
	template void mgraph::PropertyNode<mgraph::Packet<float> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B3BE60
	template void mgraph::PropertyChannel<DynamicArray<unsigned __int64,unsigned short> >::Update(mgraph::PropertyNodeBase*, mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B3BED0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B3C4C0
	template void mgraph::PropertyChannel<String>::Update(mgraph::PropertyNodeBase*, mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B3C830
	template void mgraph::PropertyNode<mgraph::Packet<String> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B3D6F0
	template void mgraph::PropertyChannel<DynamicArray<String,unsigned short> >::Update(mgraph::PropertyNodeBase*, mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B3D760
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B3DCF0
	template void mgraph::PropertyChannel<Vector>::Update(mgraph::PropertyNodeBase*, mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B3E0A0
	template void mgraph::PropertyNode<mgraph::Packet<Vector> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B3EFA0
	template void mgraph::PropertyChannel<DynamicArray<Vector,unsigned short> >::Update(mgraph::PropertyNodeBase*, mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B3F010
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B40820
	template void mgraph::PropertyChannel<DynamicArray<Complex,unsigned short> >::Update(mgraph::PropertyNodeBase*, mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B40890
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B506B0
	template void mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B389A0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B39FB0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B3AC30
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B3B930
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B3E9B0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B3F250
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3F260
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3F2B0
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B3F2D0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::SetDefaultValue(DynamicArray<mgraph::TriggerData,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B3F300
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3F320
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3F340
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >*, unsigned int, DynamicArray<mgraph::TriggerData,unsigned short>*);
	// FUNCTION: ENGINE 0x10B3F380
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3F3A0
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3F3C0
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B3F3F0
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >*, unsigned int, DynamicArray<mgraph::TriggerData,unsigned short> const&, int);
	// FUNCTION: ENGINE 0x10B3F440
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B3F460
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B3F4A0
	template mgraph::PropertyChannel<DynamicArray<mgraph::TriggerData,unsigned short> >::PropertyChannel(DynamicArray<mgraph::TriggerData,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B3F580
	template mgraph::PropertyChannel<DynamicArray<mgraph::TriggerData,unsigned short> >::PropertyChannel(mgraph::PropertyChannel<DynamicArray<mgraph::TriggerData,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B3F5B0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::PostInputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<mgraph::TriggerData,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B3F640
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B3F6F0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::PostOutputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<mgraph::TriggerData,unsigned short>*);
	// FUNCTION: ENGINE 0x10B3F7F0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >*, unsigned int);
	// FUNCTION: ENGINE 0x10B3F840
	template DynamicArray<mgraph::TriggerData,unsigned short> mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Get();
	// FUNCTION: ENGINE 0x10B3F860
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Set(DynamicArray<mgraph::TriggerData,unsigned short>);
	// FUNCTION: ENGINE 0x10B3FA50
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::SetChannelValue(DynamicArray<mgraph::TriggerData,unsigned short> const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B3FBF0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B3FF30
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3FF40
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B3FFC0
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<Complex,unsigned short>> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B3FFE0
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B40000
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B40020
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >*, unsigned int, DynamicArray<Complex,unsigned short>*);
	// FUNCTION: ENGINE 0x10B40060
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B40080
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B400A0
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B400D0
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >*, unsigned int, DynamicArray<Complex,unsigned short> const&, int);
	// FUNCTION: ENGINE 0x10B40120
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B40140
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B40180
	template mgraph::PropertyChannel<DynamicArray<Complex,unsigned short> >::PropertyChannel(DynamicArray<Complex,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B40230
	template mgraph::PropertyChannel<DynamicArray<Complex,unsigned short> >::PropertyChannel(mgraph::PropertyChannel<DynamicArray<Complex,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B40260
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::PostInputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<Complex,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B402F0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B403A0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::PostOutputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<Complex,unsigned short>*);
	// FUNCTION: ENGINE 0x10B40420
	template DynamicArray<mgraph::TriggerData,unsigned short> const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B40430
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B404A0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >*, unsigned int);
	// FUNCTION: ENGINE 0x10B404E0
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B404F0
	template DynamicArray<Complex,unsigned short> mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Get();
	// FUNCTION: ENGINE 0x10B40510
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Set(DynamicArray<Complex,unsigned short>);
	// FUNCTION: ENGINE 0x10B408B0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::SetNumChannels(unsigned int);
}

namespace om
{
	// FUNCTION: ENGINE 0x10B385E0
	template mgraph::PropertyChannel<DynamicArray<bool,unsigned short> >& DynamicArray<mgraph::PropertyChannel<DynamicArray<bool,unsigned short> >,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B38870
	template bool DynamicArray<bool,unsigned short>::operator==<class om::DynamicArray<bool,unsigned short> >(DynamicArray<bool,unsigned short> const&) const;
	// FUNCTION: ENGINE 0x10B388C0
	template mgraph::PropertyChannel<DynamicArray<bool,unsigned short> >* DynamicArray<mgraph::PropertyChannel<DynamicArray<bool,unsigned short> >,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B38CE0
	template void DynamicArray<mgraph::PropertyChannel<DynamicArray<bool,unsigned short> >,unsigned short>::FillElements(mgraph::PropertyChannel<DynamicArray<bool,unsigned short> >*, unsigned short, mgraph::PropertyChannel<DynamicArray<bool,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B39E80
	template bool DynamicArray<float,unsigned short>::operator==<class om::DynamicArray<float,unsigned short> >(DynamicArray<float,unsigned short> const&) const;
	// FUNCTION: ENGINE 0x10B3A330
	template void DynamicArray<mgraph::PropertyChannel<DynamicArray<float,unsigned short> >,unsigned short>::FillElements(mgraph::PropertyChannel<DynamicArray<float,unsigned short> >*, unsigned short, mgraph::PropertyChannel<DynamicArray<float,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B3A890
	template mgraph::PropertyChannel<DynamicArray<float,unsigned short> >& DynamicArray<mgraph::PropertyChannel<DynamicArray<float,unsigned short> >,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B3AB00
	template bool DynamicArray<unsigned int,unsigned short>::operator==<class om::DynamicArray<unsigned int,unsigned short> >(DynamicArray<unsigned int,unsigned short> const&) const;
	// FUNCTION: ENGINE 0x10B3AF80
	template void DynamicArray<mgraph::PropertyChannel<DynamicArray<unsigned int,unsigned short> >,unsigned short>::FillElements(mgraph::PropertyChannel<DynamicArray<unsigned int,unsigned short> >*, unsigned short, mgraph::PropertyChannel<DynamicArray<unsigned int,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B3B560
	template mgraph::PropertyChannel<DynamicArray<unsigned int,unsigned short> >& DynamicArray<mgraph::PropertyChannel<DynamicArray<unsigned int,unsigned short> >,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B3B6C0
	template mgraph::PropertyChannel<DynamicArray<unsigned __int64,unsigned short> >& DynamicArray<mgraph::PropertyChannel<DynamicArray<unsigned __int64,unsigned short> >,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B3B7F0
	template bool DynamicArray<unsigned __int64,unsigned short>::operator==<class om::DynamicArray<unsigned __int64,unsigned short> >(DynamicArray<unsigned __int64,unsigned short> const&) const;
	// FUNCTION: ENGINE 0x10B3B850
	template mgraph::PropertyChannel<DynamicArray<unsigned __int64,unsigned short> >* DynamicArray<mgraph::PropertyChannel<DynamicArray<unsigned __int64,unsigned short> >,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B3E850
	template bool DynamicArray<Vector,unsigned short>::operator==<class om::DynamicArray<class om::Vector,unsigned short> >(DynamicArray<Vector,unsigned short> const&) const;
	// FUNCTION: ENGINE 0x10B3F280
	template mgraph::PropertyChannel<DynamicArray<Vector,unsigned short> >& DynamicArray<mgraph::PropertyChannel<DynamicArray<Vector,unsigned short> >,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B3F2A0
	template char const* DynamicArray<mgraph::PropertyChannel<DynamicArray<Vector,unsigned short> >,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B3F560
	template mgraph::PropertyChannel<DynamicArray<Vector,unsigned short> >* DynamicArray<mgraph::PropertyChannel<DynamicArray<Vector,unsigned short> >,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B3F980
	template void DynamicArray<mgraph::PropertyChannel<DynamicArray<mgraph::TriggerData,unsigned short> >,unsigned short>::FillElements(mgraph::PropertyChannel<DynamicArray<mgraph::TriggerData,unsigned short> >*, unsigned short, mgraph::PropertyChannel<DynamicArray<mgraph::TriggerData,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B3FF60
	template mgraph::PropertyChannel<DynamicArray<mgraph::TriggerData,unsigned short> >& DynamicArray<mgraph::PropertyChannel<DynamicArray<mgraph::TriggerData,unsigned short> >,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B3FF80
	template char const* DynamicArray<mgraph::PropertyChannel<DynamicArray<mgraph::TriggerData,unsigned short> >,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B400C0
	template mgraph::PropertyChannel<DynamicArray<Complex,unsigned short> >& DynamicArray<mgraph::PropertyChannel<DynamicArray<Complex,unsigned short> >,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B40210
	template mgraph::PropertyChannel<DynamicArray<mgraph::TriggerData,unsigned short> >* DynamicArray<mgraph::PropertyChannel<DynamicArray<mgraph::TriggerData,unsigned short> >,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B40C90
	template char const* DynamicArray<mgraph::PropertyChannel<DynamicArray<Complex,unsigned short> >,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B13900
	template mgraph::PropertyChannel<unsigned int>& DynamicArray<mgraph::PropertyChannel<unsigned int>,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B14840
	template mgraph::PropertyChannel<unsigned __int64>& DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B16420
	template mgraph::PropertyChannel<Complex>& DynamicArray<mgraph::PropertyChannel<Complex>,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B37C00
	template mgraph::PropertyChannel<bool>& DynamicArray<mgraph::PropertyChannel<bool>,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B39220
	template mgraph::PropertyChannel<float>& DynamicArray<mgraph::PropertyChannel<float>,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B3C260
	template mgraph::PropertyChannel<String>& DynamicArray<mgraph::PropertyChannel<String>,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B3DAB0
	template mgraph::PropertyChannel<Vector>& DynamicArray<mgraph::PropertyChannel<Vector>,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B48D70
	template mgraph::PropertyChannel<mgraph::EnvelopeData>& DynamicArray<mgraph::PropertyChannel<mgraph::EnvelopeData>,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B3C550
	template void DynamicArray<mgraph::PropertyChannel<String>,unsigned short>::FillElements(mgraph::PropertyChannel<String>*, unsigned short, mgraph::PropertyChannel<String> const&);
	// FUNCTION: ENGINE 0x10B3C5E0
	template mgraph::PropertyChannel<String>* DynamicArray<mgraph::PropertyChannel<String>,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B48D90
	template char const* DynamicArray<mgraph::PropertyChannel<mgraph::EnvelopeData>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B490D0
	template void DynamicArray<mgraph::PropertyChannel<mgraph::EnvelopeData>,unsigned short>::Resize(unsigned short, mgraph::PropertyChannel<mgraph::EnvelopeData> const&);
	// FUNCTION: ENGINE 0x10B4FCC0
	template bool DynamicArray<VectorT<float,2>,unsigned short>::operator==<class om::DynamicArray<class om::VectorT<float,2>,unsigned short> >(DynamicArray<VectorT<float,2>,unsigned short> const&) const;
	// FUNCTION: ENGINE 0x10B13530
	template void DynamicArray<mgraph::PropertyChannel<unsigned int>,unsigned short>::ReleaseElements(mgraph::PropertyChannel<unsigned int>*, unsigned short);
	// FUNCTION: ENGINE 0x10B13920
	template char const* DynamicArray<mgraph::PropertyChannel<unsigned int>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B13C20
	template mgraph::PropertyChannel<unsigned int>* DynamicArray<mgraph::PropertyChannel<unsigned int>,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B13F80
	template void DynamicArray<mgraph::PropertyChannel<unsigned int>,unsigned short>::Resize(unsigned short, mgraph::PropertyChannel<unsigned int> const&);
	// FUNCTION: ENGINE 0x10B14450
	template void DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::ReleaseElements(mgraph::PropertyChannel<unsigned __int64>*, unsigned short);
	// FUNCTION: ENGINE 0x10B14860
	template char const* DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B14BA0
	template mgraph::PropertyChannel<unsigned __int64>* DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B14F10
	template void DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::Resize(unsigned short, mgraph::PropertyChannel<unsigned __int64> const&);
	// FUNCTION: ENGINE 0x10B16440
	template char const* DynamicArray<mgraph::PropertyChannel<Complex>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B16780
	template mgraph::PropertyChannel<Complex>* DynamicArray<mgraph::PropertyChannel<Complex>,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B16AF0
	template void DynamicArray<mgraph::PropertyChannel<Complex>,unsigned short>::Resize(unsigned short, mgraph::PropertyChannel<Complex> const&);
	// FUNCTION: ENGINE 0x10B16D10
	template void DynamicArray<mgraph::PropertyChannel<Complex>,unsigned short>::ReleaseElements(mgraph::PropertyChannel<Complex>*, unsigned short);
	// FUNCTION: ENGINE 0x10B37C20
	template char const* DynamicArray<mgraph::PropertyChannel<bool>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B37F10
	template mgraph::PropertyChannel<bool>* DynamicArray<mgraph::PropertyChannel<bool>,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B38240
	template void DynamicArray<mgraph::PropertyChannel<bool>,unsigned short>::Resize(unsigned short, mgraph::PropertyChannel<bool> const&);
	// FUNCTION: ENGINE 0x10B39240
	template char const* DynamicArray<mgraph::PropertyChannel<float>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B39540
	template mgraph::PropertyChannel<float>* DynamicArray<mgraph::PropertyChannel<float>,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B398B0
	template void DynamicArray<mgraph::PropertyChannel<float>,unsigned short>::Resize(unsigned short, mgraph::PropertyChannel<float> const&);
	// FUNCTION: ENGINE 0x10B3DAD0
	template char const* DynamicArray<mgraph::PropertyChannel<Vector>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B3DE30
	template mgraph::PropertyChannel<Vector>* DynamicArray<mgraph::PropertyChannel<Vector>,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B3E200
	template void DynamicArray<mgraph::PropertyChannel<Vector>,unsigned short>::Resize(unsigned short, mgraph::PropertyChannel<Vector> const&);
	// FUNCTION: ENGINE 0x10B387E0
	template DynamicArray<bool,unsigned short> DynamicProperty<DynamicArray<bool,unsigned short> >::GetValue() const;
	// FUNCTION: ENGINE 0x10B3B760
	template DynamicArray<unsigned __int64,unsigned short> DynamicProperty<DynamicArray<unsigned __int64,unsigned short> >::GetValue() const;
	// FUNCTION: ENGINE 0x10B3E7C0
	template DynamicArray<Vector,unsigned short> DynamicProperty<DynamicArray<Vector,unsigned short> >::GetValue() const;
	// FUNCTION: ENGINE 0x10B3F480
	template DynamicArray<mgraph::TriggerData,unsigned short> DynamicProperty<DynamicArray<mgraph::TriggerData,unsigned short> >::GetValue() const;
	// FUNCTION: ENGINE 0x10B40160
	template DynamicArray<Complex,unsigned short> DynamicProperty<DynamicArray<Complex,unsigned short> >::GetValue() const;
	// FUNCTION: ENGINE 0x10B3F830
	template DelegateProperty<DynamicArray<float,unsigned short> >::~DelegateProperty();
}


	// FUNCTION: ENGINE 0x10B627D0
	template char const* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B627E0
	template char const* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B627F0
	template char const* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B62830
	template char const* om::DynamicArray<mgraph::PropertyChannel<DynamicArray<mgraph::EnvelopeData,unsigned short> >,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B62840
	template MetaTypeBase* mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B62860
	template void* mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B62880
	template void* mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B628A0
	template void* mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B628C0
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::PropertyNodeOutputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >*, unsigned int, DynamicArray<mgraph::EnvelopeData,unsigned short>*);
	// FUNCTION: ENGINE 0x10B62900
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B62920
	template mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::~PropertyNodeOutputEvent();
	// FUNCTION: ENGINE 0x10B62940
	template mgraph::PropertyChannel<DynamicArray<mgraph::EnvelopeData,unsigned short> >& om::DynamicArray<mgraph::PropertyChannel<DynamicArray<mgraph::EnvelopeData,unsigned short> >,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B62950
	template mgraph::PropertyChannel<DynamicArray<mgraph::EnvelopeData,unsigned short> >* om::DynamicArray<mgraph::PropertyChannel<DynamicArray<mgraph::EnvelopeData,unsigned short> >,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B62970
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::PostOutputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<mgraph::EnvelopeData,unsigned short>*);
	// FUNCTION: ENGINE 0x10B629F0
	template DynamicArray<mgraph::EnvelopeData,unsigned short> const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::GetChannelValue(unsigned int);
	// FUNCTION: ENGINE 0x10B62A00
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Slot15(unsigned int);
	// FUNCTION: ENGINE 0x10B62A20
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::PropertyPropertyDelegate(mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >*, unsigned int);
	// FUNCTION: ENGINE 0x10B62A60
	template mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::~PropertyPropertyDelegate();
	// FUNCTION: ENGINE 0x10B62B10
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::SetDefaultValue(DynamicArray<mgraph::EnvelopeData,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B62B20
	template void mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Set(DynamicArray<mgraph::EnvelopeData,unsigned short>);
	// FUNCTION: ENGINE 0x10B62B70
	template void mgraph::PropertyNodeOutputEvent<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B62B90
	template mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::PropertyNodeInputEvent(mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >*, unsigned int, DynamicArray<mgraph::EnvelopeData,unsigned short> const&, int);
	// FUNCTION: ENGINE 0x10B62C10
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Execute(mgraph::Context*);
	// FUNCTION: ENGINE 0x10B62C30
	template void mgraph::PropertyNodeInputEvent<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B62C50
	template DynamicArray<mgraph::EnvelopeData,unsigned short> om::DynamicProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> >::GetValue() const;
	// FUNCTION: ENGINE 0x10B62CA0
	template mgraph::PropertyChannel<DynamicArray<mgraph::EnvelopeData,unsigned short> >::PropertyChannel(DynamicArray<mgraph::EnvelopeData,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B62D60
	template mgraph::PropertyChannel<DynamicArray<mgraph::EnvelopeData,unsigned short> >::PropertyChannel(mgraph::PropertyChannel<DynamicArray<mgraph::EnvelopeData,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B62DC0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::PostInputEvent(mgraph::EventQueue*, unsigned int, DynamicArray<mgraph::EnvelopeData,unsigned short> const*);
	// FUNCTION: ENGINE 0x10B62E20
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::PostPropertyValue(unsigned int, mgraph::EventQueue*, DynamicPropertyBase const*);
	// FUNCTION: ENGINE 0x10B62F20
	template DynamicArray<mgraph::EnvelopeData,unsigned short> mgraph::PropertyPropertyDelegate<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Get();
	// FUNCTION: ENGINE 0x10B63000
	template bool om::DynamicArray<mgraph::EnvelopeData,unsigned short>::operator==<class om::DynamicArray<class mgraph::EnvelopeData,unsigned short> >(DynamicArray<mgraph::EnvelopeData,unsigned short> const&) const;
	// FUNCTION: ENGINE 0x10B632C0
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::SetChannelValue(DynamicArray<mgraph::EnvelopeData,unsigned short> const*, unsigned int, int);
	// FUNCTION: ENGINE 0x10B63320
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::SetNumChannels(unsigned int);

	// FUNCTION: ENGINE 0x10B63250
	template void mgraph::PropertyChannel<DynamicArray<mgraph::EnvelopeData,unsigned short> >::Update(mgraph::PropertyNodeBase*, mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B63300
	template void mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B6D260
	template void om::DynamicArray<mgraph::EnvelopeData,unsigned short>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6D360
	template om::DynamicArray<mgraph::EnvelopeData,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B6E560
	template void om::DynamicArray<mgraph::PropertyChannel<DynamicArray<mgraph::EnvelopeData,unsigned short> >,unsigned short>::ReleaseElements(mgraph::PropertyChannel<DynamicArray<mgraph::EnvelopeData,unsigned short> >*, unsigned short);