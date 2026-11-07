// The inlets and outlets of the mgraph library (0x10B20000 - 0x10B40000): the template instances for the packet types, in the order the
// compiler emitted them.
#include "code/mgraph/inlets.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// Left to the engine: the constructors of the inlets (92.5 %: the engine keeps the node in esi and the first pin in edi, the compiler swaps them; its symbols are mapped)
	template<> mgraph::Inlet<mgraph::Packet<Vector > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	template<> mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	template<> mgraph::Inlet<mgraph::Packet<mgraph::TriggerData > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	template<> mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	template<> mgraph::Inlet<mgraph::Packet<Complex > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	template<> mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	template<> mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	template<> mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Inlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B200B0
	template mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B201F0
	template mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::~Outlet();
	// FUNCTION: ENGINE 0x10B20260
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B20280
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B20290
	template bool mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B20310
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B203B0
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B20930
	template mgraph::Inlet<mgraph::Packet<Vector > >::~Inlet();
	// FUNCTION: ENGINE 0x10B209A0
	template void mgraph::Inlet<mgraph::Packet<Vector > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B209C0
	template bool mgraph::Inlet<mgraph::Packet<Vector > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B20A50
	template void mgraph::Inlet<mgraph::Packet<Vector > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B20C60
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<Vector > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B20C80
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<Vector > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B20F60
	template mgraph::Outlet<mgraph::Packet<Vector > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B210A0
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<Vector > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B210B0
	template mgraph::Outlet<mgraph::Packet<Vector > >::~Outlet();
	// FUNCTION: ENGINE 0x10B21120
	template void mgraph::Outlet<mgraph::Packet<Vector > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B21140
	template bool mgraph::Outlet<mgraph::Packet<Vector > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B211C0
	template void mgraph::Outlet<mgraph::Packet<Vector > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B21260
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<Vector > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B217A0
	template mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::~Inlet();
	// FUNCTION: ENGINE 0x10B21810
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B21830
	template bool mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B218C0
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B21AD0
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B21AF0
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B21DD0
	template mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B21F10
	template mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::~Outlet();
	// FUNCTION: ENGINE 0x10B21F80
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B21FA0
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B21FB0
	template bool mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B22030
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B220D0
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B22630
	template mgraph::Inlet<mgraph::Packet<mgraph::TriggerData > >::~Inlet();
	// FUNCTION: ENGINE 0x10B226A0
	template void mgraph::Inlet<mgraph::Packet<mgraph::TriggerData > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B226C0
	template bool mgraph::Inlet<mgraph::Packet<mgraph::TriggerData > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B22750
	template void mgraph::Inlet<mgraph::Packet<mgraph::TriggerData > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B22960
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<mgraph::TriggerData > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B22980
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<mgraph::TriggerData > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B22C60
	template mgraph::Outlet<mgraph::Packet<mgraph::TriggerData > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B22DA0
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<mgraph::TriggerData > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B22DB0
	template mgraph::Outlet<mgraph::Packet<mgraph::TriggerData > >::~Outlet();
	// FUNCTION: ENGINE 0x10B22E20
	template void mgraph::Outlet<mgraph::Packet<mgraph::TriggerData > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B22E40
	template bool mgraph::Outlet<mgraph::Packet<mgraph::TriggerData > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B22EC0
	template void mgraph::Outlet<mgraph::Packet<mgraph::TriggerData > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B22F60
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<mgraph::TriggerData > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B234A0
	template mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::~Inlet();
	// FUNCTION: ENGINE 0x10B23510
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B23530
	template bool mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B235C0
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B237D0
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B237F0
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B23AD0
	template mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B23C10
	template mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::~Outlet();
	// FUNCTION: ENGINE 0x10B23C80
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B23CA0
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B23CB0
	template bool mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B23D30
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B23DD0
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B24310
	template mgraph::Inlet<mgraph::Packet<Complex > >::~Inlet();
	// FUNCTION: ENGINE 0x10B24380
	template void mgraph::Inlet<mgraph::Packet<Complex > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B243A0
	template bool mgraph::Inlet<mgraph::Packet<Complex > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B24430
	template void mgraph::Inlet<mgraph::Packet<Complex > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B24640
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<Complex > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B24660
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<Complex > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B24940
	template mgraph::Outlet<mgraph::Packet<Complex > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B24A80
	template mgraph::Outlet<mgraph::Packet<Complex > >::~Outlet();
	// FUNCTION: ENGINE 0x10B24AF0
	template void mgraph::Outlet<mgraph::Packet<Complex > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B24B10
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<Complex > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B24B20
	template bool mgraph::Outlet<mgraph::Packet<Complex > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B24BA0
	template void mgraph::Outlet<mgraph::Packet<Complex > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B24C40
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<Complex > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B25180
	template mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::~Inlet();
	// FUNCTION: ENGINE 0x10B251F0
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B25210
	template bool mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B252A0
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B254B0
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B254D0
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B257B0
	template mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B258F0
	template mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::~Outlet();
	// FUNCTION: ENGINE 0x10B25960
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B25980
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetPacketMetaType();
	// FUNCTION: ENGINE 0x10B25990
	template bool mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B25A10
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B25AB0
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B25FF0
	template mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData > >::~Inlet();
	// FUNCTION: ENGINE 0x10B26060
	template void mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B26080
	template bool mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B26110
	template void mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B26320
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B26340
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B26620
	template mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B26760
	template mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData > >::~Outlet();
	// FUNCTION: ENGINE 0x10B267D0
	template void mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B26800
	template bool mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B26880
	template void mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B26920
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B26EA0
	template mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::~Inlet();
	// FUNCTION: ENGINE 0x10B26F10
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B26F30
	template bool mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B26FC0
	template void mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B271D0
	template om::MetaTypeBase* mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::GetValueMetaType();
	// FUNCTION: ENGINE 0x10B271F0
	template mgraph::AbstractInputPinBase* mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B274D0
	template mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Outlet(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B27610
	template mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::~Outlet();
	// FUNCTION: ENGINE 0x10B27680
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B276B0
	template bool mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B27730
	template void mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Rename(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B277D0
	template mgraph::AbstractOutputPinBase* mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::CreateAbstractPin(mgraph::Abstraction*);
	// FUNCTION: ENGINE 0x10B276A0
	template om::MetaTypeBase* mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::GetPacketMetaType();
}
