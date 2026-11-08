// The inlets and outlets of the mgraph library for the primitive packet types (0x10B17000 - 0x10B20000): the template instances of the bool, float, unsigned int,
// unsigned __int64 and string packets and their arrays, in the order the compiler emitted them.
#include "code/mgraph/inlets.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// bool
	// Left to the engine: the constructor of the inlet (see inlets.cpp)
	template<> mgraph::Inlet<mgraph::Packet<bool > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B17850
	template mgraph::Inlet<mgraph::Packet<bool > >::~Inlet();
	// FUNCTION: ENGINE 0x10B178C0
	template void mgraph::Inlet<mgraph::Packet<bool > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B17900
	template bool mgraph::Inlet<mgraph::Packet<bool > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B17990
	template void mgraph::Inlet<mgraph::Packet<bool > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B17BA0
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<bool > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B17BC0
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<bool > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B17EA0
	template mgraph::Outlet<mgraph::Packet<bool > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B18000
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<bool > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B18010
	template mgraph::Outlet<mgraph::Packet<bool > >::~Outlet();
	// FUNCTION: ENGINE 0x10B18080
	template void mgraph::Outlet<mgraph::Packet<bool > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B180A0
	template bool mgraph::Outlet<mgraph::Packet<bool > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B18120
	template void mgraph::Outlet<mgraph::Packet<bool > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B181C0
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<bool > >::CreateAbstractPin(mgraph::Abstraction*);

	// bool[]
	// Left to the engine: the constructor of the inlet (see inlets.cpp)
	template<> mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B18700
	template mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::~Inlet();
	// FUNCTION: ENGINE 0x10B18770
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B18790
	template bool mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B18820
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B18A30
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B18A50
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B18D30
	template mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B18E70
	template mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::~Outlet();
	// FUNCTION: ENGINE 0x10B18EE0
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B18F00
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B18F10
	template bool mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B18F90
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B19030
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);

	// float
	// Left to the engine: the constructor of the inlet (see inlets.cpp)
	template<> mgraph::Inlet<mgraph::Packet<float > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B19570
	template mgraph::Inlet<mgraph::Packet<float > >::~Inlet();
	// FUNCTION: ENGINE 0x10B195E0
	template void mgraph::Inlet<mgraph::Packet<float > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B19600
	template bool mgraph::Inlet<mgraph::Packet<float > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B19690
	template void mgraph::Inlet<mgraph::Packet<float > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B198A0
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<float > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B198C0
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<float > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B19BA0
	template mgraph::Outlet<mgraph::Packet<float > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B19CE0
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<float > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B19CF0
	template mgraph::Outlet<mgraph::Packet<float > >::~Outlet();
	// FUNCTION: ENGINE 0x10B19D60
	template void mgraph::Outlet<mgraph::Packet<float > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B19D80
	template bool mgraph::Outlet<mgraph::Packet<float > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B19E00
	template void mgraph::Outlet<mgraph::Packet<float > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B19EA0
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<float > >::CreateAbstractPin(mgraph::Abstraction*);

	// float[]
	// Left to the engine: the constructor of the inlet (see inlets.cpp)
	template<> mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1A3E0
	template mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::~Inlet();
	// FUNCTION: ENGINE 0x10B1A450
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1A470
	template bool mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B1A500
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1A710
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B1A730
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B1AA10
	template mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1AB50
	template mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::~Outlet();
	// FUNCTION: ENGINE 0x10B1ABC0
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1ABE0
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B1ABF0
	template bool mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B1AC70
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1AD10
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);

	// uint
	// Left to the engine: the constructor of the inlet (see inlets.cpp)
	template<> mgraph::Inlet<mgraph::Packet<unsigned int > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1B250
	template mgraph::Inlet<mgraph::Packet<unsigned int > >::~Inlet();
	// FUNCTION: ENGINE 0x10B1B2C0
	template void mgraph::Inlet<mgraph::Packet<unsigned int > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1B2E0
	template bool mgraph::Inlet<mgraph::Packet<unsigned int > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B1B370
	template void mgraph::Inlet<mgraph::Packet<unsigned int > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1B580
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<unsigned int > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B1B5A0
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<unsigned int > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B1B880
	template mgraph::Outlet<mgraph::Packet<unsigned int > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1B9C0
	template mgraph::Outlet<mgraph::Packet<unsigned int > >::~Outlet();
	// FUNCTION: ENGINE 0x10B1BA30
	template void mgraph::Outlet<mgraph::Packet<unsigned int > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1BA50
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<unsigned int > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B1BA60
	template bool mgraph::Outlet<mgraph::Packet<unsigned int > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B1BAE0
	template void mgraph::Outlet<mgraph::Packet<unsigned int > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1BB80
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<unsigned int > >::CreateAbstractPin(mgraph::Abstraction*);

	// uint[]
	// Left to the engine: the constructor of the inlet (see inlets.cpp)
	template<> mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1C0C0
	template mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::~Inlet();
	// FUNCTION: ENGINE 0x10B1C130
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1C150
	template bool mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B1C1E0
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1C3F0
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B1C410
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B1C6F0
	template mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1C830
	template mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::~Outlet();
	// FUNCTION: ENGINE 0x10B1C8A0
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1C8C0
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B1C8D0
	template bool mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B1C950
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1C9F0
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);

	// uint64
	// Left to the engine: the constructor of the inlet (see inlets.cpp)
	template<> mgraph::Inlet<mgraph::Packet<unsigned __int64 > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1CF30
	template mgraph::Inlet<mgraph::Packet<unsigned __int64 > >::~Inlet();
	// FUNCTION: ENGINE 0x10B1CFA0
	template void mgraph::Inlet<mgraph::Packet<unsigned __int64 > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1CFC0
	template bool mgraph::Inlet<mgraph::Packet<unsigned __int64 > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B1D050
	template void mgraph::Inlet<mgraph::Packet<unsigned __int64 > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1D260
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<unsigned __int64 > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B1D280
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<unsigned __int64 > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B1D560
	template mgraph::Outlet<mgraph::Packet<unsigned __int64 > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1D6A0
	template mgraph::Outlet<mgraph::Packet<unsigned __int64 > >::~Outlet();
	// FUNCTION: ENGINE 0x10B1D710
	template void mgraph::Outlet<mgraph::Packet<unsigned __int64 > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1D730
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<unsigned __int64 > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B1D740
	template bool mgraph::Outlet<mgraph::Packet<unsigned __int64 > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B1D7C0
	template void mgraph::Outlet<mgraph::Packet<unsigned __int64 > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1D860
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<unsigned __int64 > >::CreateAbstractPin(mgraph::Abstraction*);

	// uint64[]
	// Left to the engine: the constructor of the inlet (see inlets.cpp)
	template<> mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1DDA0
	template mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::~Inlet();
	// FUNCTION: ENGINE 0x10B1DE10
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1DE30
	template bool mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B1DEC0
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1E0D0
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B1E0F0
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B1E3D0
	template mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1E510
	template mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::~Outlet();
	// FUNCTION: ENGINE 0x10B1E580
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1E5A0
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B1E5B0
	template bool mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B1E630
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1E6D0
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);

	// string
	// Left to the engine: the constructor of the inlet (see inlets.cpp)
	template<> mgraph::Inlet<mgraph::Packet<String > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1EC10
	template mgraph::Inlet<mgraph::Packet<String > >::~Inlet();
	// FUNCTION: ENGINE 0x10B1EC80
	template void mgraph::Inlet<mgraph::Packet<String > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1ECA0
	template bool mgraph::Inlet<mgraph::Packet<String > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B1ED30
	template void mgraph::Inlet<mgraph::Packet<String > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1EF40
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<String > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B1EF60
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<String > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B1F240
	template mgraph::Outlet<mgraph::Packet<String > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1F380
	template mgraph::Outlet<mgraph::Packet<String > >::~Outlet();
	// FUNCTION: ENGINE 0x10B1F3F0
	template void mgraph::Outlet<mgraph::Packet<String > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1F410
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<String > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B1F420
	template bool mgraph::Outlet<mgraph::Packet<String > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B1F4A0
	template void mgraph::Outlet<mgraph::Packet<String > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1F540
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<String > >::CreateAbstractPin(mgraph::Abstraction*);

	// string[]
	// Left to the engine: the constructor of the inlet (see inlets.cpp)
	template<> mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1FA80
	template mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::~Inlet();
	// FUNCTION: ENGINE 0x10B1FAF0
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1FB10
	template bool mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B1FBA0
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1FDB0
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B1FDD0
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);

}
