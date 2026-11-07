// The pins and connections of the mgraph library for the packets of float, the envelope data and the arrays of float
// (0x10AB2C00 - 0x10AB5600): the template instances of the unit of the envelope node.
#include "code/mgraph/envelope.h"
#include "code/mgraph/pins.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10AB2D10
	template mgraph::InputPin<mgraph::Packet<float> >::InputPin(void*, om::Name<om::CaseSensitive64BitKey> const*, int, int, mgraph::Packet<float>);
	// FUNCTION: ENGINE 0x10AB2DC0
	template mgraph::InputPin<mgraph::Packet<float> >::~InputPin();
	// FUNCTION: ENGINE 0x10AB2DF0
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<float> >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10AB2ED0
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AB2EE0
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AB2F10
	template mgraph::ContextConnection<mgraph::Packet<float> >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10AB2F60
	template void mgraph::ContextConnection<mgraph::Packet<float> >::Destroy();
	// FUNCTION: ENGINE 0x10AB2FD0
	template om::MetaTypeBase* mgraph::InputPin<mgraph::Packet<float> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10AB3040
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<float> >::operator new(unsigned int);
	// FUNCTION: ENGINE 0x10AB3060
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<float> >::operator new(unsigned int);
	// FUNCTION: ENGINE 0x10AB3080
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<float> >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10AB3180
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<float> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10AB3330
	template void mgraph::OutputPin<mgraph::Packet<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB33A0
	template om::MetaTypeBase* mgraph::OutputPin<mgraph::Packet<float> >::GetPacketType();
	// FUNCTION: ENGINE 0x10AB33B0
	template om::MetaTypeBase* mgraph::OutputPin<mgraph::Packet<float> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10AB3400
	template mgraph::OutputPin<mgraph::Packet<float> >::~OutputPin();
	// FUNCTION: ENGINE 0x10AB4890
	template void mgraph::InputPin<mgraph::Packet<mgraph::EnvelopeData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB48B0
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10AB4980
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AB4990
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AB49B0
	template mgraph::ContextConnection<mgraph::Packet<mgraph::EnvelopeData> >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10AB49E0
	template void mgraph::ContextConnection<mgraph::Packet<mgraph::EnvelopeData> >::Destroy();
	// FUNCTION: ENGINE 0x10AB4A50
	template om::MetaTypeBase* mgraph::InputPin<mgraph::Packet<mgraph::EnvelopeData> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10AB4A80
	template bool mgraph::InputPin<mgraph::Packet<mgraph::EnvelopeData> >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10AB4A90
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::operator new(unsigned int);
	// FUNCTION: ENGINE 0x10AB4AB0
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::operator new(unsigned int);
	// FUNCTION: ENGINE 0x10AB4AD0
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10AB4BB0
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<mgraph::EnvelopeData> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10AB4DE0
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<DynamicArray<float, unsigned short> > >::GetChannelData();
	// FUNCTION: ENGINE 0x10AB4E10
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<float, unsigned short> > >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10AB4EE0
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<float, unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AB4EF0
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<float, unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AB4F10
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<float, unsigned short> > >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10AB4F40
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<float, unsigned short> > >::Destroy();
	// FUNCTION: ENGINE 0x10AB4FB0
	template om::MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<float, unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10AB4FD0
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<float, unsigned short> > >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10AB4FE0
	template bool mgraph::InputPin<mgraph::Packet<DynamicArray<float, unsigned short> > >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10AB4FF0
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<float, unsigned short> > >::operator new(unsigned int);
	// FUNCTION: ENGINE 0x10AB5010
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<float, unsigned short> > >::operator new(unsigned int);
	// FUNCTION: ENGINE 0x10AB5030
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<float, unsigned short> > >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10AB5110
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<DynamicArray<float, unsigned short> > >::MakeConnection(mgraph::Pin*);
}

namespace om
{
	using namespace mgraph;

	// FUNCTION: ENGINE 0x10AB3390
	template char const* DynamicArray<mgraph::Packet<float>, unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB33E0
	template mgraph::Packet<float>* DynamicArray<mgraph::Packet<float>, unsigned short>::Allocate(unsigned short);
}
