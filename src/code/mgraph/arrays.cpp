// The arrays of the mgraph library (0x10B00DC0 - 0x10B5xxxx): the member functions of om::DynamicArray<E> that the nodes, pins and
// property nodes use, for the packets and channels of the engine's packet types, in the order the compiler emitted them (a guess:
// one translation unit).
#include "code/mgraph/nodes.h"
#include "code/mgraph/throw.h"
#include "code/mgraph/propertynode.h"

#pragma warning(disable: 4661 4345)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B33E60
	template mgraph::Packet<unsigned int>::Packet(mgraph::Packet<unsigned int> const&);
}

namespace om
{
	using namespace mgraph;

	// FUNCTION: ENGINE 0x10B00DC0
	template DynamicArray<mgraph::Packet<bool>,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B00DD0
	template char const* DynamicArray<mgraph::Packet<bool>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B011F0
	template DynamicArray<mgraph::Packet<mgraph::TriggerData>,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B01220
	template char const* DynamicArray<mgraph::Packet<mgraph::TriggerData>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B04A00
	template DynamicArray<mgraph::Packet<unsigned int>,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B04A10
	template char const* DynamicArray<mgraph::Packet<unsigned int>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B07200
	template DynamicArray<unsigned __int64,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B07360
	template DynamicArray<unsigned __int64,unsigned short>& DynamicArray<unsigned __int64,unsigned short>::operator=(DynamicArray<unsigned __int64,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B08BB0
	template DynamicArray<Vector,unsigned short>& DynamicArray<Vector,unsigned short>::operator=(DynamicArray<Vector,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B0A4D0
	template DynamicArray<Complex,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B0A630
	template DynamicArray<Complex,unsigned short>& DynamicArray<Complex,unsigned short>::operator=(DynamicArray<Complex,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B11120
	template DynamicArray<mgraph::EnvelopeData,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B11150
	template void DynamicArray<mgraph::EnvelopeData,unsigned short>::Clear();
	// FUNCTION: ENGINE 0x10B11190
	template mgraph::EnvelopeData& DynamicArray<mgraph::EnvelopeData,unsigned short>::Append();
	// FUNCTION: ENGINE 0x10B11210
	template DynamicArray<mgraph::EnvelopeData,unsigned short>& DynamicArray<mgraph::EnvelopeData,unsigned short>::operator=(DynamicArray<mgraph::EnvelopeData,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B11290
	template void DynamicArray<mgraph::EnvelopeData,unsigned short>::Empty();
	// FUNCTION: ENGINE 0x10B13080
	template DynamicArray<mgraph::PropertyChannel<float>,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B13090
	template void DynamicArray<mgraph::PropertyChannel<float>,unsigned short>::DestroyElements(mgraph::PropertyChannel<float>*, unsigned short);
	// FUNCTION: ENGINE 0x10B130A0
	template void DynamicArray<Vector,unsigned short>::ReleaseElements(Vector*, unsigned short);
	// FUNCTION: ENGINE 0x10B130E0
	template DynamicArray<mgraph::PropertyChannel<float>,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B13510
	template DynamicArray<mgraph::PropertyChannel<unsigned int>,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B13520
	template void DynamicArray<mgraph::PropertyChannel<unsigned int>,unsigned short>::DestroyElements(mgraph::PropertyChannel<unsigned int>*, unsigned short);
	// FUNCTION: ENGINE 0x10B13570
	template DynamicArray<mgraph::PropertyChannel<unsigned int>,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B13A80
	template String& DynamicArray<String,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B14430
	template DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B14440
	template void DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::DestroyElements(mgraph::PropertyChannel<unsigned __int64>*, unsigned short);
	// FUNCTION: ENGINE 0x10B14490
	template DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B149E0
	template mgraph::PropertyChannel<unsigned __int64> const& DynamicArray<mgraph::PropertyChannel<unsigned __int64>,unsigned short>::operator[](unsigned short) const;
	// FUNCTION: ENGINE 0x10B158A0
	template DynamicArray<mgraph::PropertyChannel<Vector>,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B158B0
	template void DynamicArray<mgraph::PropertyChannel<Vector>,unsigned short>::DestroyElements(mgraph::PropertyChannel<Vector>*, unsigned short);
	// FUNCTION: ENGINE 0x10B158C0
	template void DynamicArray<mgraph::PropertyChannel<Vector>,unsigned short>::ReleaseElements(mgraph::PropertyChannel<Vector>*, unsigned short);
	// FUNCTION: ENGINE 0x10B15900
	template DynamicArray<mgraph::PropertyChannel<Vector>,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B15FC0
	template void DynamicArray<mgraph::PropertyChannel<Complex>,unsigned short>::DestroyElements(mgraph::PropertyChannel<Complex>*, unsigned short);
	// FUNCTION: ENGINE 0x10B16010
	template DynamicArray<mgraph::PropertyChannel<Complex>,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B165C0
	template mgraph::PropertyChannel<Complex> const& DynamicArray<mgraph::PropertyChannel<Complex>,unsigned short>::operator[](unsigned short) const;
	// FUNCTION: ENGINE 0x10B16D00
	template DynamicArray<mgraph::PropertyChannel<Complex>,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B16F90
	template DynamicArray<mgraph::PropertyChannel<mgraph::EnvelopeData>,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B16FA0
	template void DynamicArray<mgraph::PropertyChannel<mgraph::EnvelopeData>,unsigned short>::ReleaseElements(mgraph::PropertyChannel<mgraph::EnvelopeData>*, unsigned short);
	// FUNCTION: ENGINE 0x10B2BD00
	template DynamicArray<mgraph::PropertyChannel<String>,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B2D260
	template DynamicArray<mgraph::PropertyChannel<mgraph::EnvelopeData>,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B2D290
	template DynamicArray<mgraph::EnvelopeData,unsigned short>::DynamicArray(DynamicArray<mgraph::EnvelopeData,unsigned short> const&);
	// FUNCTION: ENGINE 0x10B37D80
	template mgraph::PropertyChannel<bool> const& DynamicArray<mgraph::PropertyChannel<bool>,unsigned short>::operator[](unsigned short) const;
	// FUNCTION: ENGINE 0x10B38600
	template char const* DynamicArray<mgraph::PropertyChannel<DynamicArray<bool,unsigned short> >,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B38740
	template mgraph::PropertyChannel<DynamicArray<bool,unsigned short> > const& DynamicArray<mgraph::PropertyChannel<DynamicArray<bool,unsigned short> >,unsigned short>::operator[](unsigned short) const;
	// FUNCTION: ENGINE 0x10B393A0
	template mgraph::PropertyChannel<float> const& DynamicArray<mgraph::PropertyChannel<float>,unsigned short>::operator[](unsigned short) const;
	// FUNCTION: ENGINE 0x10B3A9F0
	template mgraph::PropertyChannel<DynamicArray<float,unsigned short> > const& DynamicArray<mgraph::PropertyChannel<DynamicArray<float,unsigned short> >,unsigned short>::operator[](unsigned short) const;
	// FUNCTION: ENGINE 0x10B3B580
	template char const* DynamicArray<mgraph::PropertyChannel<DynamicArray<unsigned __int64,unsigned short> >,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B3C2B0
	template char const* DynamicArray<mgraph::PropertyChannel<String>,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B3C420
	template mgraph::PropertyChannel<String> const& DynamicArray<mgraph::PropertyChannel<String>,unsigned short>::operator[](unsigned short) const;
	// FUNCTION: ENGINE 0x10B3DC50
	template mgraph::PropertyChannel<Vector> const& DynamicArray<mgraph::PropertyChannel<Vector>,unsigned short>::operator[](unsigned short) const;
}
