// The connections between the pins of the mgraph library (0x10B0B820 - 0x10B2B000): the template instances of the
// connection classes for the packet types, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/pins.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B02460
	template void mgraph::OutputPin<mgraph::Packet<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B024E0
	template char const* mgraph::OutputPin<mgraph::Packet<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B024F0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<mgraph::TriggerData> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B02500
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<mgraph::TriggerData> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B02550
	template mgraph::OutputPin<mgraph::Packet<mgraph::TriggerData> >::~OutputPin();
	// FUNCTION: ENGINE 0x10B0B680
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetChannelData();
	// FUNCTION: ENGINE 0x10B0B6E0
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0B700
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0B740
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0B760
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0B7C0
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0B7D0
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0B7F0
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B0B820
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Destroy();
	// FUNCTION: ENGINE 0x10B0B860
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0B880
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0B890
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0B8B0
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0B8C0
	template bool mgraph::InputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0B8D0
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0B8F0
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0B9A0
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0BB90
	template char const* mgraph::OutputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0BBA0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0BBB0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0BE30
	template char const* mgraph::OutputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0BE40
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0BE50
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0C050
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<float> >::GetChannelData();
	// FUNCTION: ENGINE 0x10B0C0A0
	template void mgraph::InputPin<mgraph::Packet<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0C0C0
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<unsigned int> >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0C0E0
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<unsigned int> >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0C120
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0C140
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0C1A0
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0C1B0
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0C1D0
	template mgraph::ContextConnection<mgraph::Packet<unsigned int> >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B0C200
	template void mgraph::ContextConnection<mgraph::Packet<unsigned int> >::Destroy();
	// FUNCTION: ENGINE 0x10B0C240
	template void mgraph::ContextConnection<mgraph::Packet<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0C260
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<unsigned int> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0C270
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<unsigned int> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0C290
	template void mgraph::InputPin<mgraph::Packet<unsigned int> >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0C2A0
	template bool mgraph::InputPin<mgraph::Packet<unsigned int> >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0C2E0
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0C300
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0C3B0
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<unsigned int> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0C510
	template void mgraph::OutputPin<mgraph::Packet<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0C570
	template char const* mgraph::OutputPin<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0C580
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<unsigned int> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0C590
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<unsigned int> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0C5E0
	template mgraph::OutputPin<mgraph::Packet<unsigned int> >::~OutputPin();
	// FUNCTION: ENGINE 0x10B0C750
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetChannelData();
	// FUNCTION: ENGINE 0x10B0C7B0
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0C7D0
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0C810
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0C830
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0C890
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0C8A0
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0C8C0
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B0C8F0
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Destroy();
	// FUNCTION: ENGINE 0x10B0C930
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0C950
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0C960
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0C980
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0C990
	template bool mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0C9A0
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0C9C0
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0CA70
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0CC60
	template char const* mgraph::OutputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0CC70
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0CC80
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0CE80
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<unsigned __int64> >::GetChannelData();
	// FUNCTION: ENGINE 0x10B0CEF0
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<unsigned __int64> >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0CF10
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<unsigned __int64> >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0CF50
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0CF70
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0CFD0
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0CFE0
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0D000
	template mgraph::ContextConnection<mgraph::Packet<unsigned __int64> >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B0D030
	template void mgraph::ContextConnection<mgraph::Packet<unsigned __int64> >::Destroy();
	// FUNCTION: ENGINE 0x10B0D070
	template void mgraph::ContextConnection<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0D090
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<unsigned __int64> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0D0A0
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<unsigned __int64> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0D0C0
	template void mgraph::InputPin<mgraph::Packet<unsigned __int64> >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0D0D0
	template bool mgraph::InputPin<mgraph::Packet<unsigned __int64> >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0D110
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0D130
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0D1E0
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<unsigned __int64> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0D3A0
	template char const* mgraph::OutputPin<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0D3B0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<unsigned __int64> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0D3C0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<unsigned __int64> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0D5A0
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetChannelData();
	// FUNCTION: ENGINE 0x10B0D600
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0D620
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0D660
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0D680
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0D6E0
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0D6F0
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0D710
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B0D740
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Destroy();
	// FUNCTION: ENGINE 0x10B0D780
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0D7A0
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0D7B0
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0D7D0
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0D7E0
	template bool mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0D7F0
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0D810
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0D8C0
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0DAC0
	template char const* mgraph::OutputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0DAD0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0DAE0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0DD00
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<mgraph::EnvelopeData> >::GetChannelData();
	// FUNCTION: ENGINE 0x10B0DD90
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<String> >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0DDB0
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<String> >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0DDF0
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0DE10
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0DE70
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0DE80
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0DEA0
	template mgraph::ContextConnection<mgraph::Packet<String> >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B0DED0
	template void mgraph::ContextConnection<mgraph::Packet<String> >::Destroy();
	// FUNCTION: ENGINE 0x10B0DF10
	template void mgraph::ContextConnection<mgraph::Packet<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0DF30
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<String> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0DF40
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<String> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0DF60
	template void mgraph::InputPin<mgraph::Packet<String> >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0DF70
	template bool mgraph::InputPin<mgraph::Packet<String> >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0DFC0
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0DFE0
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0E090
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<String> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0E250
	template char const* mgraph::OutputPin<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0E260
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<String> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0E270
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<String> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0E480
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetChannelData();
	// FUNCTION: ENGINE 0x10B0E4E0
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0E500
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0E540
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0E560
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0E5C0
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0E5D0
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0E5F0
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B0E620
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::Destroy();
	// FUNCTION: ENGINE 0x10B0E660
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0E680
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0E690
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0E6B0
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0E6C0
	template bool mgraph::InputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0E6D0
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0E6F0
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0E7A0
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0E990
	template char const* mgraph::OutputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0E9A0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0E9B0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0EBB0
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetChannelData();
	// FUNCTION: ENGINE 0x10B0EC10
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0EC30
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0EC70
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0EC90
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0ECF0
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0ED00
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0ED20
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B0ED50
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Destroy();
	// FUNCTION: ENGINE 0x10B0ED90
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0EDB0
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0EDC0
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0EDE0
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0EDF0
	template bool mgraph::InputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0EE00
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0EE20
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0EED0
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0F0D0
	template char const* mgraph::OutputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0F0E0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0F0F0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0F320
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetChannelData();
	// FUNCTION: ENGINE 0x10B0F380
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0F3A0
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0F3E0
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0F400
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0F460
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0F470
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0F490
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B0F4C0
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Destroy();
	// FUNCTION: ENGINE 0x10B0F500
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0F520
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0F530
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0F550
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0F560
	template bool mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0F570
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0F590
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0F640
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0F830
	template char const* mgraph::OutputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0F840
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0F850
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0FA60
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<Complex> >::GetChannelData();
	// FUNCTION: ENGINE 0x10B0FAD0
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<Complex> >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0FAF0
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<Complex> >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0FB30
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0FB50
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0FBB0
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0FBC0
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0FBE0
	template mgraph::ContextConnection<mgraph::Packet<Complex> >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B0FC10
	template void mgraph::ContextConnection<mgraph::Packet<Complex> >::Destroy();
	// FUNCTION: ENGINE 0x10B0FC50
	template void mgraph::ContextConnection<mgraph::Packet<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0FC70
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<Complex> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0FC80
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<Complex> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B0FCA0
	template void mgraph::InputPin<mgraph::Packet<Complex> >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0FCB0
	template bool mgraph::InputPin<mgraph::Packet<Complex> >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B0FCF0
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0FD10
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0FDC0
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<Complex> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0FF80
	template char const* mgraph::OutputPin<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0FF90
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<Complex> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B0FFA0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<Complex> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B101A0
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetChannelData();
	// FUNCTION: ENGINE 0x10B10200
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B10220
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B10260
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B10280
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B102E0
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B102F0
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B10310
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B10340
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Destroy();
	// FUNCTION: ENGINE 0x10B10380
	template void mgraph::ContextConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B103A0
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B103B0
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B103D0
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B103E0
	template bool mgraph::InputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B103F0
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B10410
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B104C0
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B106C0
	template char const* mgraph::OutputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B106D0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B106E0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B17460
	template mgraph::AbstractInputPin<mgraph::Packet<bool> >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B174D0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<bool> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B174E0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<bool> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B17510
	template void mgraph::AbstractInputPin<mgraph::Packet<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B17530
	template void mgraph::AbstractOutputPin<mgraph::Packet<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B17550
	template mgraph::AbstractOutputPin<mgraph::Packet<bool> >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B17580
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B17590
	template char const* mgraph::AbstractInputPin<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B175F0
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B17600
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B17610
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<bool> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B17620
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<bool> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B17640
	template void* mgraph::AbstractOutputPin<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B17660
	template void* mgraph::AbstractInputPin<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B17A60
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B17A80
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<bool> >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B17AB0
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B17AD0
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B17AF0
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<bool> >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B17B20
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B17CB0
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<bool> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B18370
	template mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B183B0
	template void mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B183D0
	template void mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B183F0
	template mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B18420
	template char const* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B18430
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B18490
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B184A0
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B184B0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B184C0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B184E0
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B184F0
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B18510
	template void* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B18530
	template void* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B188F0
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B18910
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B18940
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B18960
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B18980
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B189B0
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B18B40
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B191E0
	template mgraph::AbstractInputPin<mgraph::Packet<float> >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B19210
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<float> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B19220
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<float> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B19250
	template void mgraph::AbstractInputPin<mgraph::Packet<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B19270
	template void mgraph::AbstractOutputPin<mgraph::Packet<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B19290
	template mgraph::AbstractOutputPin<mgraph::Packet<float> >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B192C0
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B192D0
	template char const* mgraph::AbstractInputPin<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B19330
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B19340
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B19350
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<float> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B19360
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<float> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B19380
	template void* mgraph::AbstractOutputPin<mgraph::Packet<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B193A0
	template void* mgraph::AbstractInputPin<mgraph::Packet<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B19760
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B19780
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<float> >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B197B0
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B197D0
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B197F0
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<float> >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B19820
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B199B0
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<float> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B19B50
	template char const* mgraph::InputPin<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AB2FC0
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<float> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1A050
	template mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1A090
	template void mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1A0B0
	template void mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1A0D0
	template mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1A100
	template char const* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1A110
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1A170
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<float,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1A180
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<float,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1A190
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1A1A0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1A1C0
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1A1D0
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1A1F0
	template void* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1A210
	template void* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1A5D0
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1A5F0
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<float,unsigned short> > >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1A620
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1A640
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1A660
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<float,unsigned short> > >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1A690
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1A820
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1ABE0
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1AEC0
	template mgraph::AbstractInputPin<mgraph::Packet<unsigned int> >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1AF00
	template void mgraph::AbstractInputPin<mgraph::Packet<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1AF20
	template void mgraph::AbstractOutputPin<mgraph::Packet<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1AF40
	template mgraph::AbstractOutputPin<mgraph::Packet<unsigned int> >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1AF70
	template char const* mgraph::AbstractInputPin<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1AF80
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1AFE0
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1AFF0
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1B000
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<unsigned int> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1B010
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<unsigned int> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1B030
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<unsigned int> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1B040
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<unsigned int> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1B060
	template void* mgraph::AbstractInputPin<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1B080
	template void* mgraph::AbstractOutputPin<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1B440
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1B460
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<unsigned int> >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1B490
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1B4B0
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1B4D0
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<unsigned int> >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1B500
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1B690
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<unsigned int> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1BD30
	template mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1BD70
	template void mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1BD90
	template void mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1BDB0
	template mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1BDE0
	template char const* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1BDF0
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1BE50
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1BE60
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1BE70
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1BE80
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1BEA0
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1BEB0
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1BED0
	template void* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1BEF0
	template void* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1C2B0
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1C2D0
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1C300
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1C320
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1C340
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1C370
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1C500
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1CBA0
	template mgraph::AbstractInputPin<mgraph::Packet<unsigned __int64> >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1CBE0
	template void mgraph::AbstractInputPin<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1CC00
	template void mgraph::AbstractOutputPin<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1CC20
	template mgraph::AbstractOutputPin<mgraph::Packet<unsigned __int64> >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1CC50
	template char const* mgraph::AbstractInputPin<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1CC60
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1CCC0
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1CCD0
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1CCE0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<unsigned __int64> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1CCF0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<unsigned __int64> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1CD10
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<unsigned __int64> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1CD20
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<unsigned __int64> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1CD40
	template void* mgraph::AbstractInputPin<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1CD60
	template void* mgraph::AbstractOutputPin<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1D120
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1D140
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<unsigned __int64> >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1D170
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1D190
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1D1B0
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<unsigned __int64> >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1D1E0
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1D370
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<unsigned __int64> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1DA10
	template mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1DA50
	template void mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1DA70
	template void mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1DA90
	template mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1DAC0
	template char const* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1DAD0
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1DB30
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1DB40
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1DB50
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1DB60
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1DB80
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1DB90
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1DBB0
	template void* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1DBD0
	template void* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1DF90
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1DFB0
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1DFE0
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1E000
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1E020
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1E050
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1E1E0
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1E880
	template mgraph::AbstractInputPin<mgraph::Packet<String> >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1E8C0
	template void mgraph::AbstractInputPin<mgraph::Packet<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1E8E0
	template void mgraph::AbstractOutputPin<mgraph::Packet<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1E900
	template mgraph::AbstractOutputPin<mgraph::Packet<String> >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1E930
	template char const* mgraph::AbstractInputPin<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1E940
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1E9A0
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1E9B0
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1E9C0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<String> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1E9D0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<String> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1E9F0
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<String> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1EA00
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<String> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1EA20
	template void* mgraph::AbstractInputPin<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1EA40
	template void* mgraph::AbstractOutputPin<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1EE00
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1EE20
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<String> >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1EE50
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1EE70
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1EE90
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<String> >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1EEC0
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1F050
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<String> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1F6F0
	template mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1F730
	template void mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1F750
	template void mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1F770
	template mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B1F7A0
	template char const* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1F7B0
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1F810
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1F820
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1F830
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1F840
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1F860
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B1F870
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B1F890
	template void* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1F8B0
	template void* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1FC70
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1FC90
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1FCC0
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1FCE0
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1FD00
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B1FD30
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1FEC0
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B20560
	template mgraph::AbstractInputPin<mgraph::Packet<Vector> >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B205D0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<Vector> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B205E0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<Vector> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B20610
	template void mgraph::AbstractInputPin<mgraph::Packet<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B20630
	template void mgraph::AbstractOutputPin<mgraph::Packet<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B20650
	template mgraph::AbstractOutputPin<mgraph::Packet<Vector> >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B20680
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B20690
	template char const* mgraph::AbstractInputPin<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B206F0
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B20700
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B20710
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<Vector> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B20720
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<Vector> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B20740
	template void* mgraph::AbstractOutputPin<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B20760
	template void* mgraph::AbstractInputPin<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B20B20
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B20B40
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<Vector> >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B20B70
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B20B90
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B20BB0
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<Vector> >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B20BE0
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B20D70
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<Vector> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B21410
	template mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B21450
	template void mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B21470
	template void mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B21490
	template mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B214C0
	template char const* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B214D0
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B21530
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B21540
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B21550
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B21560
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B21580
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B21590
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B215B0
	template void* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B215D0
	template void* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B21990
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B219B0
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B219E0
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B21A00
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B21A20
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B21A50
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B21BE0
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B22280
	template mgraph::AbstractInputPin<mgraph::Packet<mgraph::TriggerData> >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B222D0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<mgraph::TriggerData> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B222E0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<mgraph::TriggerData> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B22310
	template void mgraph::AbstractInputPin<mgraph::Packet<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B22330
	template void mgraph::AbstractOutputPin<mgraph::Packet<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B22350
	template mgraph::AbstractOutputPin<mgraph::Packet<mgraph::TriggerData> >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B22380
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B22390
	template char const* mgraph::AbstractInputPin<mgraph::Packet<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B223F0
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B22400
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B22410
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<mgraph::TriggerData> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B22420
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<mgraph::TriggerData> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B22440
	template void* mgraph::AbstractOutputPin<mgraph::Packet<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B22460
	template void* mgraph::AbstractInputPin<mgraph::Packet<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B22820
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B22840
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<mgraph::TriggerData> >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B22870
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B22890
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B228B0
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<mgraph::TriggerData> >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B228E0
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B22A70
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<mgraph::TriggerData> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B23110
	template mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B23150
	template void mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B23170
	template void mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B23190
	template mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B231C0
	template char const* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B231D0
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B23230
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B23240
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B23250
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B23260
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B23280
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B23290
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B232B0
	template void* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B232D0
	template void* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B23690
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B236B0
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B236E0
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B23700
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B23720
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B23750
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B238E0
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B23F80
	template mgraph::AbstractInputPin<mgraph::Packet<Complex> >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B23FC0
	template void mgraph::AbstractInputPin<mgraph::Packet<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B23FE0
	template void mgraph::AbstractOutputPin<mgraph::Packet<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B24000
	template mgraph::AbstractOutputPin<mgraph::Packet<Complex> >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B24030
	template char const* mgraph::AbstractInputPin<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B24040
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B240A0
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B240B0
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B240C0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<Complex> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B240D0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<Complex> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B240F0
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<Complex> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B24100
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<Complex> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B24120
	template void* mgraph::AbstractInputPin<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B24140
	template void* mgraph::AbstractOutputPin<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B24500
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B24520
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<Complex> >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B24550
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B24570
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B24590
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<Complex> >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B245C0
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B24750
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<Complex> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B24DF0
	template mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B24E30
	template void mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B24E50
	template void mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B24E70
	template mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B24EA0
	template char const* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B24EB0
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B24F10
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B24F20
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B24F30
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B24F40
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B24F60
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B24F70
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B24F90
	template void* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B24FB0
	template void* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B25370
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B25390
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B253C0
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B253E0
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B25400
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B25430
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B255C0
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B25C60
	template mgraph::AbstractInputPin<mgraph::Packet<mgraph::EnvelopeData> >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B25CA0
	template void mgraph::AbstractInputPin<mgraph::Packet<mgraph::EnvelopeData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B25CC0
	template void mgraph::AbstractOutputPin<mgraph::Packet<mgraph::EnvelopeData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B25CE0
	template mgraph::AbstractOutputPin<mgraph::Packet<mgraph::EnvelopeData> >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B25D10
	template char const* mgraph::AbstractInputPin<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B25D20
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B25D80
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B25D90
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B25DA0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<mgraph::EnvelopeData> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B25DB0
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<mgraph::EnvelopeData> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B25DD0
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<mgraph::EnvelopeData> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B25DE0
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<mgraph::EnvelopeData> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B25E00
	template void* mgraph::AbstractInputPin<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B25E20
	template void* mgraph::AbstractOutputPin<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B261E0
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B26200
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B26230
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B26250
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B26270
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B262A0
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<mgraph::EnvelopeData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B26430
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<mgraph::EnvelopeData> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B265D0
	template char const* mgraph::InputPin<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B267F0
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<mgraph::EnvelopeData> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B26AD0
	template mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AbstractInputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B26B10
	template void mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B26B30
	template void mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B26B50
	template mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AbstractOutputPin(Name<CaseSensitive64BitKey> const*, void*, int);
	// FUNCTION: ENGINE 0x10B26B80
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B26BA0
	template char const* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B26BB0
	template char const* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B26BD0
	template char const* mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B26C30
	template char const* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B26C40
	template char const* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B26C50
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B26C60
	template MetaTypeBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B26C80
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B26C90
	template MetaTypeBase* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B26CB0
	template void* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B26CD0
	template void* mgraph::AbstractOutputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B27090
	template void* mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B270B0
	template mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AbstractToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B270E0
	template void mgraph::AbstractToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B27100
	template void* mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B27120
	template mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::ConcreteToAbstractGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B27150
	template void mgraph::ConcreteToAbstractGraphConnection<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B272E0
	template mgraph::GraphConnectionBase* mgraph::AbstractInputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B276A0
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10B2E630
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<mgraph::TriggerData> >::GetChannelData();
	// FUNCTION: ENGINE 0x10B2E650
	template void mgraph::InputPin<mgraph::Packet<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2E670
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<mgraph::TriggerData> >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B2E6D0
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2E6F0
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B2E700
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B2E720
	template mgraph::ContextConnection<mgraph::Packet<mgraph::TriggerData> >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B2E750
	template void mgraph::ContextConnection<mgraph::Packet<mgraph::TriggerData> >::Destroy();
	// FUNCTION: ENGINE 0x10B2E790
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2E7B0
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<mgraph::TriggerData> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B2E7C0
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<mgraph::TriggerData> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B2E7E0
	template void mgraph::InputPin<mgraph::Packet<mgraph::EnvelopeData> >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B2E7F0
	template bool mgraph::InputPin<mgraph::Packet<mgraph::TriggerData> >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B2E830
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B2E850
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B2E870
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<mgraph::TriggerData> >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B2E8A0
	template void mgraph::ContextConnection<mgraph::Packet<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2E950
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<mgraph::TriggerData> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B2EAC0
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<Vector> >::GetChannelData();
	// FUNCTION: ENGINE 0x10B2EB00
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<Vector> >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B2EB60
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2EB80
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B2EB90
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B2EBB0
	template mgraph::ContextConnection<mgraph::Packet<Vector> >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B2EBE0
	template void mgraph::ContextConnection<mgraph::Packet<Vector> >::Destroy();
	// FUNCTION: ENGINE 0x10B2EC20
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2EC40
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<Vector> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B2EC50
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<Vector> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B2EC70
	template void mgraph::InputPin<mgraph::Packet<float> >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B2EC80
	template bool mgraph::InputPin<mgraph::Packet<float> >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B2ECC0
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B2ECE0
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B2ED00
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<Vector> >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B2ED30
	template void mgraph::ContextConnection<mgraph::Packet<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2EDE0
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<Vector> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B2EFD0
	template char const* mgraph::OutputPin<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B2EFE0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<Vector> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B2EFF0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<Vector> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B30330
	template void mgraph::OutputPin<mgraph::Packet<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B30390
	template char const* mgraph::OutputPin<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B303A0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<bool> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B303B0
	template MetaTypeBase* mgraph::OutputPin<mgraph::Packet<bool> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B30400
	template mgraph::OutputPin<mgraph::Packet<bool> >::~OutputPin();
	// FUNCTION: ENGINE 0x10B30550
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<bool> >::GetChannelData();
	// FUNCTION: ENGINE 0x10B30570
	template void mgraph::InputPin<mgraph::Packet<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B30590
	template mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<bool> >::ConcreteToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B305B0
	template mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<bool> >::AbstractToConcreteGraphConnection(mgraph::Pin*, mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B30620
	template void mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B30640
	template void mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B30660
	template char const* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B30670
	template char const* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B30690
	template mgraph::ContextConnection<mgraph::Packet<bool> >::ContextConnection(void*, void*, void*);
	// FUNCTION: ENGINE 0x10B306C0
	template void mgraph::ContextConnection<mgraph::Packet<bool> >::Destroy();
	// FUNCTION: ENGINE 0x10B30700
	template void mgraph::ContextConnection<mgraph::Packet<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B30720
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<bool> >::GetPacketType();
	// FUNCTION: ENGINE 0x10B30730
	template MetaTypeBase* mgraph::InputPin<mgraph::Packet<bool> >::GetPacketTypeCached();
	// FUNCTION: ENGINE 0x10B30750
	template void mgraph::InputPin<mgraph::Packet<bool> >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B30760
	template bool mgraph::InputPin<mgraph::Packet<bool> >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B307A0
	template void* mgraph::ConcreteToConcreteGraphConnection<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B307C0
	template void* mgraph::AbstractToConcreteGraphConnection<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B30870
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<bool> >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0C000
	template mgraph::InputPin<mgraph::Packet<unsigned int> >::InputPin(void*, Name<CaseSensitive64BitKey> const*, int, int, mgraph::Packet<unsigned int>);
	// FUNCTION: ENGINE 0x10B0C060
	template mgraph::InputPin<mgraph::Packet<unsigned int> >::~InputPin();
	// FUNCTION: ENGINE 0x10B4EC10
	template mgraph::PinChannelData* mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::GetChannelData();
	// FUNCTION: ENGINE 0x10B4EE00
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::SetChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B4EE10
	template bool mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::IsChannelOwner(void*);
	// FUNCTION: ENGINE 0x10B4EEF0
	template mgraph::GraphConnectionBase* mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::MakeConnection(mgraph::Pin*);
	// FUNCTION: ENGINE 0x10B0B6C0
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0C790
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0CE30
	template mgraph::InputPin<mgraph::Packet<unsigned __int64> >::InputPin(void*, Name<CaseSensitive64BitKey> const*, int, int, mgraph::Packet<unsigned __int64>);
	// FUNCTION: ENGINE 0x10B0CE90
	template mgraph::InputPin<mgraph::Packet<unsigned __int64> >::~InputPin();
	// FUNCTION: ENGINE 0x10B0CED0
	template void mgraph::InputPin<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0D5E0
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0DC90
	template mgraph::InputPin<mgraph::Packet<String> >::InputPin(void*, Name<CaseSensitive64BitKey> const*, int, int, mgraph::Packet<String>);
	// FUNCTION: ENGINE 0x10B0DD70
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0E4C0
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0EBF0
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0F360
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0FAB0
	template void mgraph::InputPin<mgraph::Packet<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B101E0
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2EAE0
	template void mgraph::InputPin<mgraph::Packet<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B30500
	template mgraph::InputPin<mgraph::Packet<bool> >::InputPin(void*, Name<CaseSensitive64BitKey> const*, int, int, mgraph::Packet<bool>);
	// FUNCTION: ENGINE 0x10B30560
	template mgraph::InputPin<mgraph::Packet<bool> >::~InputPin();
	// FUNCTION: ENGINE 0x10B4EC50
	template void mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0E410
	template mgraph::InputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::InputPin(void*, Name<CaseSensitive64BitKey> const*, int, int, mgraph::Packet<DynamicArray<String,unsigned short> >);
	// FUNCTION: ENGINE 0x10B0FA00
	template mgraph::InputPin<mgraph::Packet<Complex> >::InputPin(void*, Name<CaseSensitive64BitKey> const*, int, int, mgraph::Packet<Complex>);
	// FUNCTION: ENGINE 0x10B0FA70
	template mgraph::InputPin<mgraph::Packet<Complex> >::~InputPin();
	// FUNCTION: ENGINE 0x10B2EA60
	template mgraph::InputPin<mgraph::Packet<Vector> >::InputPin(void*, Name<CaseSensitive64BitKey> const*, int, int, mgraph::Packet<Vector>);
	// FUNCTION: ENGINE 0x10B2EAD0
	template mgraph::InputPin<mgraph::Packet<Vector> >::~InputPin();
	// FUNCTION: ENGINE 0x10B05560
	template mgraph::Packet<DynamicArray<bool,unsigned short> >::Packet(mgraph::Packet<DynamicArray<bool,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B05590
	template mgraph::Packet<DynamicArray<bool,unsigned short> >::~Packet();
	// FUNCTION: ENGINE 0x10B05D70
	template mgraph::Packet<DynamicArray<float,unsigned short> >::~Packet();
	// FUNCTION: ENGINE 0x10B069C0
	template mgraph::Packet<DynamicArray<unsigned int,unsigned short> >::~Packet();
	// FUNCTION: ENGINE 0x10B07660
	template mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> >::Packet(mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B07690
	template mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> >::~Packet();
	// FUNCTION: ENGINE 0x10B07A10
	template mgraph::Packet<String>::~Packet();
	// FUNCTION: ENGINE 0x10B082E0
	template mgraph::Packet<DynamicArray<String,unsigned short> >::Packet(mgraph::Packet<DynamicArray<String,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B08310
	template mgraph::Packet<DynamicArray<String,unsigned short> >::~Packet();
	// FUNCTION: ENGINE 0x10B08EB0
	template mgraph::Packet<DynamicArray<Vector,unsigned short> >::Packet(mgraph::Packet<DynamicArray<Vector,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B08EE0
	template mgraph::Packet<DynamicArray<Vector,unsigned short> >::~Packet();
	// FUNCTION: ENGINE 0x10B09C80
	template mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> >::Packet(mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B09CB0
	template mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> >::~Packet();
	// FUNCTION: ENGINE 0x10B0A930
	template mgraph::Packet<DynamicArray<Complex,unsigned short> >::Packet(mgraph::Packet<DynamicArray<Complex,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B0A960
	template mgraph::Packet<DynamicArray<Complex,unsigned short> >::~Packet();
	// FUNCTION: ENGINE 0x10B0AE10
	template mgraph::Packet<mgraph::EnvelopeData>::~Packet();
	// FUNCTION: ENGINE 0x10B32BC0
	template mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> >::~Packet();
	// FUNCTION: ENGINE 0x10B33750
	template mgraph::Packet<float>::Packet(mgraph::Packet<float> const&);
	// FUNCTION: ENGINE 0x10B34630
	template mgraph::Packet<unsigned __int64>::Packet(mgraph::Packet<unsigned __int64> const&);
	// FUNCTION: ENGINE 0x10B34E30
	template mgraph::Packet<String>::Packet(mgraph::Packet<String> const&);
	// FUNCTION: ENGINE 0x10B36360
	template mgraph::Packet<Complex>::Packet(mgraph::Packet<Complex> const&);
	// FUNCTION: ENGINE 0x10B37960
	template mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> >::Packet(mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B4E5C0
	template mgraph::Packet<DynamicArray<float,unsigned short> >::Packet(mgraph::Packet<DynamicArray<float,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B59D60
	template mgraph::Packet<DynamicArray<unsigned int,unsigned short> >::Packet(mgraph::Packet<DynamicArray<unsigned int,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10B374E0
	template void mgraph::OutputPin<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B37540
	template void mgraph::OutputPin<mgraph::Packet<DynamicArray<float,unsigned short> > >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B375A0
	template void mgraph::OutputPin<mgraph::Packet<unsigned int> >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B37600
	template void mgraph::OutputPin<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B37660
	template void mgraph::OutputPin<mgraph::Packet<unsigned __int64> >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B376C0
	template void mgraph::OutputPin<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B37720
	template void mgraph::OutputPin<mgraph::Packet<String> >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B37780
	template void mgraph::OutputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B377E0
	template void mgraph::OutputPin<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B37840
	template void mgraph::OutputPin<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B378A0
	template void mgraph::OutputPin<mgraph::Packet<Complex> >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B37900
	template void mgraph::OutputPin<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B495E0
	template void mgraph::OutputPin<mgraph::Packet<Vector> >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B4CCA0
	template void mgraph::OutputPin<mgraph::Packet<mgraph::TriggerData> >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B4CD00
	template void mgraph::OutputPin<mgraph::Packet<bool> >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B5C130
	template void mgraph::OutputPin<mgraph::Packet<mgraph::EnvelopeData> >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B5C1A0
	template void mgraph::OutputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Slot3(unsigned int, void*);
	// FUNCTION: ENGINE 0x10B05370
	template mgraph::Packet<DynamicArray<bool,unsigned short> >::Packet();
	// FUNCTION: ENGINE 0x10B07460
	template mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> >::Packet();
	// FUNCTION: ENGINE 0x10B08100
	template mgraph::Packet<DynamicArray<String,unsigned short> >::Packet();
	// FUNCTION: ENGINE 0x10B08CB0
	template mgraph::Packet<DynamicArray<Vector,unsigned short> >::Packet();
	// FUNCTION: ENGINE 0x10B09A90
	template mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> >::Packet();
	// FUNCTION: ENGINE 0x10B0A730
	template mgraph::Packet<DynamicArray<Complex,unsigned short> >::Packet();
	// FUNCTION: ENGINE 0x10B32B80
	template mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> >::Packet();
	// FUNCTION: ENGINE 0x10B32F10
	template mgraph::Packet<bool>::Packet();
	// FUNCTION: ENGINE 0x10B33010
	template mgraph::Packet<bool>::Packet(mgraph::Packet<bool> const&);
	// FUNCTION: ENGINE 0x10B33650
	template mgraph::Packet<float>::Packet();
	// FUNCTION: ENGINE 0x10B33DE0
	template mgraph::Packet<unsigned int>::Packet();
	// FUNCTION: ENGINE 0x10B345C0
	template mgraph::Packet<unsigned __int64>::Packet();
	// FUNCTION: ENGINE 0x10B34E10
	template mgraph::Packet<String>::Packet();
	// FUNCTION: ENGINE 0x10B355D0
	template mgraph::Packet<Vector>::Packet();
	// FUNCTION: ENGINE 0x10B356F0
	template mgraph::Packet<Vector>::Packet(mgraph::Packet<Vector> const&);
	// FUNCTION: ENGINE 0x10B35D70
	template mgraph::Packet<mgraph::TriggerData>::Packet();
	// FUNCTION: ENGINE 0x10B36340
	template mgraph::Packet<Complex>::Packet();
	// FUNCTION: ENGINE 0x10B4E5A0
	template mgraph::Packet<DynamicArray<float,unsigned short> >::Packet();
	// FUNCTION: ENGINE 0x10B59D90
	template mgraph::Packet<DynamicArray<unsigned int,unsigned short> >::Packet();
	// FUNCTION: ENGINE 0x10B0BA60
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >* mgraph::ContextConnection<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Create(mgraph::ConnectionOwner*, void*, mgraph::ConcreteInputPinBase*);
	// FUNCTION: ENGINE 0x10B0C440
	template mgraph::ContextConnection<mgraph::Packet<unsigned int> >* mgraph::ContextConnection<mgraph::Packet<unsigned int> >::Create(mgraph::ConnectionOwner*, void*, mgraph::ConcreteInputPinBase*);
	// FUNCTION: ENGINE 0x10B0CB30
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >* mgraph::ContextConnection<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Create(mgraph::ConnectionOwner*, void*, mgraph::ConcreteInputPinBase*);
	// FUNCTION: ENGINE 0x10B0D270
	template mgraph::ContextConnection<mgraph::Packet<unsigned __int64> >* mgraph::ContextConnection<mgraph::Packet<unsigned __int64> >::Create(mgraph::ConnectionOwner*, void*, mgraph::ConcreteInputPinBase*);
	// FUNCTION: ENGINE 0x10B0D990
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >* mgraph::ContextConnection<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Create(mgraph::ConnectionOwner*, void*, mgraph::ConcreteInputPinBase*);
	// FUNCTION: ENGINE 0x10B0E120
	template mgraph::ContextConnection<mgraph::Packet<String> >* mgraph::ContextConnection<mgraph::Packet<String> >::Create(mgraph::ConnectionOwner*, void*, mgraph::ConcreteInputPinBase*);
	// FUNCTION: ENGINE 0x10B0E860
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >* mgraph::ContextConnection<mgraph::Packet<DynamicArray<String,unsigned short> > >::Create(mgraph::ConnectionOwner*, void*, mgraph::ConcreteInputPinBase*);
	// FUNCTION: ENGINE 0x10B0EFA0
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >* mgraph::ContextConnection<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Create(mgraph::ConnectionOwner*, void*, mgraph::ConcreteInputPinBase*);
	// FUNCTION: ENGINE 0x10B0F700
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >* mgraph::ContextConnection<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Create(mgraph::ConnectionOwner*, void*, mgraph::ConcreteInputPinBase*);
	// FUNCTION: ENGINE 0x10B0FE50
	template mgraph::ContextConnection<mgraph::Packet<Complex> >* mgraph::ContextConnection<mgraph::Packet<Complex> >::Create(mgraph::ConnectionOwner*, void*, mgraph::ConcreteInputPinBase*);
	// FUNCTION: ENGINE 0x10B10590
	template mgraph::ContextConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >* mgraph::ContextConnection<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Create(mgraph::ConnectionOwner*, void*, mgraph::ConcreteInputPinBase*);
}

namespace om
{
	// FUNCTION: ENGINE 0x10B00E10
	template void DynamicArray<mgraph::Packet<bool>,unsigned short>::ReleaseElements(mgraph::Packet<bool>*, unsigned short);
	// FUNCTION: ENGINE 0x10B01260
	template void DynamicArray<mgraph::Packet<mgraph::TriggerData>,unsigned short>::ReleaseElements(mgraph::Packet<mgraph::TriggerData>*, unsigned short);
	// FUNCTION: ENGINE 0x10B04AB0
	template void DynamicArray<mgraph::Packet<unsigned int>,unsigned short>::ReleaseElements(mgraph::Packet<unsigned int>*, unsigned short);
	// FUNCTION: ENGINE 0x10B00E90
	template DynamicArray<mgraph::Packet<bool>,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B012E0
	template DynamicArray<mgraph::Packet<mgraph::TriggerData>,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B04B60
	template DynamicArray<mgraph::Packet<unsigned int>,unsigned short>::~DynamicArray();
}
