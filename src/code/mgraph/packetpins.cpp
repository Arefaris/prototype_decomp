// Pin and packet array members of the mgraph library that the engine keeps once in the translation units of the nodes (0x10B00000 - 0x10B14000):
// the allocation operators of the pins, the element release and allocation of the packet arrays.
#include "code/mgraph/nodes.h"
#include "code/mgraph/throw.h"
#include "code/mgraph/propertynode.h"

#pragma warning(disable: 4661 4345)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B04CB0
	template mgraph::Packet<bool >::~Packet();
	// FUNCTION: ENGINE 0x10B04CE0
	template mgraph::Throw<mgraph::Packet<bool > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B05870
	template mgraph::Packet<float >::~Packet();
	// FUNCTION: ENGINE 0x10B058A0
	template mgraph::Throw<mgraph::Packet<float > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B06150
	template mgraph::Packet<unsigned int >::~Packet();
	// FUNCTION: ENGINE 0x10B06180
	template mgraph::Throw<mgraph::Packet<unsigned int > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B06D40
	template mgraph::Packet<unsigned __int64 >::~Packet();
	// FUNCTION: ENGINE 0x10B06CC0
	template mgraph::Throw<mgraph::Packet<unsigned __int64 > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B085E0
	template mgraph::Packet<Vector >::~Packet();
	// FUNCTION: ENGINE 0x10B08610
	template mgraph::Throw<mgraph::Packet<Vector > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B091C0
	template mgraph::Packet<mgraph::TriggerData >::~Packet();
	// FUNCTION: ENGINE 0x10B091F0
	template mgraph::Throw<mgraph::Packet<mgraph::TriggerData > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B0A020
	template mgraph::Packet<Complex >::~Packet();
	// FUNCTION: ENGINE 0x10B09FB0
	template mgraph::Throw<mgraph::Packet<Complex > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B0AC60
	template mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B07990
	template mgraph::Throw<mgraph::Packet<String > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B05110
	template mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B05C90
	template mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B065B0
	template mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B07F10
	template mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B08A50
	template mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B09830
	template mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B0B170
	template mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::ChannelStorage::ChannelStorage();
	// FUNCTION: ENGINE 0x10B00E70
	template void* mgraph::OutputPin<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B012C0
	template void* mgraph::OutputPin<mgraph::Packet<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B04B40
	template void* mgraph::OutputPin<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B06FF0
	template void* mgraph::OutputPin<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B07D00
	template void* mgraph::OutputPin<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B08430
	template void* mgraph::OutputPin<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0A2C0
	template void* mgraph::OutputPin<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0B2B0
	template void* mgraph::InputPin<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
}

namespace om
{
	using namespace mgraph;


	// FUNCTION: ENGINE 0x10B05630
	template DynamicArray<mgraph::Packet<DynamicArray<bool,unsigned short> >,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B05160
	template void DynamicArray<mgraph::Packet<DynamicArray<bool,unsigned short> >,unsigned short>::ReleaseElements(mgraph::Packet<DynamicArray<bool,unsigned short> >*, unsigned short);
	// FUNCTION: ENGINE 0x10B05CC0
	template void DynamicArray<mgraph::Packet<DynamicArray<float,unsigned short> >,unsigned short>::ReleaseElements(mgraph::Packet<DynamicArray<float,unsigned short> >*, unsigned short);
	// FUNCTION: ENGINE 0x10B06A60
	template DynamicArray<mgraph::Packet<DynamicArray<unsigned int,unsigned short> >,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B06600
	template void DynamicArray<mgraph::Packet<DynamicArray<unsigned int,unsigned short> >,unsigned short>::ReleaseElements(mgraph::Packet<DynamicArray<unsigned int,unsigned short> >*, unsigned short);
	// FUNCTION: ENGINE 0x10B07730
	template DynamicArray<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> >,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B07250
	template void DynamicArray<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> >,unsigned short>::ReleaseElements(mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> >*, unsigned short);
	// FUNCTION: ENGINE 0x10B083A0
	template DynamicArray<mgraph::Packet<DynamicArray<String,unsigned short> >,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B07F60
	template void DynamicArray<mgraph::Packet<DynamicArray<String,unsigned short> >,unsigned short>::ReleaseElements(mgraph::Packet<DynamicArray<String,unsigned short> >*, unsigned short);
	// FUNCTION: ENGINE 0x10B08F80
	template DynamicArray<mgraph::Packet<DynamicArray<Vector,unsigned short> >,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B08AA0
	template void DynamicArray<mgraph::Packet<DynamicArray<Vector,unsigned short> >,unsigned short>::ReleaseElements(mgraph::Packet<DynamicArray<Vector,unsigned short> >*, unsigned short);
	// FUNCTION: ENGINE 0x10B09D50
	template DynamicArray<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> >,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B09880
	template void DynamicArray<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> >,unsigned short>::ReleaseElements(mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> >*, unsigned short);
	// FUNCTION: ENGINE 0x10B0B400
	template DynamicArray<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> >,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B0B1C0
	template void DynamicArray<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> >,unsigned short>::ReleaseElements(mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> >*, unsigned short);
	// FUNCTION: ENGINE 0x10B04800
	template DynamicArray<mgraph::Packet<float >,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B06F50
	template DynamicArray<mgraph::Packet<unsigned __int64 >,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B0A230
	template DynamicArray<mgraph::Packet<Complex >,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B0AEC0
	template DynamicArray<mgraph::Packet<mgraph::EnvelopeData >,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B09FE0
	template void DynamicArray<mgraph::Packet<Complex >,unsigned short>::ReleaseElements(mgraph::Packet<Complex >*, unsigned short);
	// FUNCTION: ENGINE 0x10B02530
	template mgraph::Packet<mgraph::TriggerData>* DynamicArray<mgraph::Packet<mgraph::TriggerData>,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B0C5C0
	template mgraph::Packet<unsigned int>* DynamicArray<mgraph::Packet<unsigned int>,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B06CF0
	template void DynamicArray<mgraph::Packet<unsigned __int64>,unsigned short>::ReleaseElements(mgraph::Packet<unsigned __int64>*, unsigned short);
	// FUNCTION: ENGINE 0x10B08640
	template void DynamicArray<mgraph::Packet<Vector>,unsigned short>::ReleaseElements(mgraph::Packet<Vector>*, unsigned short);
	// FUNCTION: ENGINE 0x10B0AC90
	template void DynamicArray<mgraph::Packet<mgraph::EnvelopeData>,unsigned short>::ReleaseElements(mgraph::Packet<mgraph::EnvelopeData>*, unsigned short);
}
