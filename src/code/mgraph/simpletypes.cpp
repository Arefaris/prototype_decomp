// The reflection of the values the pins of the mgraph library carry (0x10B02640 - 0x10B0xxxx): the template instances of
// om::MetaSimpleType<T> for the arrays of the property types and for the packets, in the order the compiler emitted them
// (a guess: one translation unit).
#include "code/mgraph/nodes.h"
#include "code/mgraph/throw.h"
#include "code/om/metasimpletype.h"

#pragma warning(disable: 4661)

namespace om
{
	using namespace mgraph;

	// FUNCTION: ENGINE 0x10B02640
	template bool MetaSimpleType<DynamicArray<bool,unsigned short> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B02660
	template void MetaSimpleType<DynamicArray<bool,unsigned short> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B02680
	template bool MetaSimpleType<DynamicArray<bool,unsigned short> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B026A0
	template bool MetaSimpleType<DynamicArray<bool,unsigned short> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B026C0
	template int MetaSimpleType<DynamicArray<bool,unsigned short> >::Slot5();
	// FUNCTION: ENGINE 0x10B026F0
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<bool,unsigned short> > >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B02720
	template void MetaSimpleType<mgraph::Packet<DynamicArray<bool,unsigned short> > >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B02750
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<bool,unsigned short> > >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B02780
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<bool,unsigned short> > >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B02870
	template void MetaSimpleType<DynamicArray<float,unsigned short> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B02890
	template bool MetaSimpleType<DynamicArray<float,unsigned short> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B028B0
	template int MetaSimpleType<DynamicArray<float,unsigned short> >::Slot5();
	// FUNCTION: ENGINE 0x10B028E0
	template void MetaSimpleType<DynamicArray<float,unsigned short> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10B02910
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<float,unsigned short> > >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B02940
	template void MetaSimpleType<mgraph::Packet<DynamicArray<float,unsigned short> > >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B02970
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<float,unsigned short> > >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B029A0
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<float,unsigned short> > >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B02A90
	template bool MetaSimpleType<DynamicArray<unsigned int,unsigned short> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B02AB0
	template void MetaSimpleType<DynamicArray<unsigned int,unsigned short> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B02AD0
	template bool MetaSimpleType<DynamicArray<unsigned int,unsigned short> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B02AF0
	template bool MetaSimpleType<DynamicArray<unsigned int,unsigned short> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B02B10
	template int MetaSimpleType<DynamicArray<unsigned int,unsigned short> >::Slot5();
	// FUNCTION: ENGINE 0x10B02B40
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B02B70
	template void MetaSimpleType<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B02BA0
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B02BD0
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B02C00
	template bool MetaSimpleType<mgraph::Packet<unsigned int> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B02C30
	template void MetaSimpleType<mgraph::Packet<unsigned int> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B02C60
	template bool MetaSimpleType<mgraph::Packet<unsigned int> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B02C90
	template bool MetaSimpleType<mgraph::Packet<unsigned int> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B02D80
	template bool MetaSimpleType<DynamicArray<unsigned __int64,unsigned short> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B02DA0
	template void MetaSimpleType<DynamicArray<unsigned __int64,unsigned short> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B02DC0
	template bool MetaSimpleType<DynamicArray<unsigned __int64,unsigned short> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B02DE0
	template bool MetaSimpleType<DynamicArray<unsigned __int64,unsigned short> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B02E00
	template int MetaSimpleType<DynamicArray<unsigned __int64,unsigned short> >::Slot5();
	// FUNCTION: ENGINE 0x10B02E30
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B02E60
	template void MetaSimpleType<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B02E90
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B02EC0
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B02EF0
	template bool MetaSimpleType<mgraph::Packet<unsigned __int64> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B02F20
	template void MetaSimpleType<mgraph::Packet<unsigned __int64> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B02F50
	template bool MetaSimpleType<mgraph::Packet<unsigned __int64> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B02F80
	template bool MetaSimpleType<mgraph::Packet<unsigned __int64> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B03070
	template bool MetaSimpleType<DynamicArray<String,unsigned short> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B03090
	template void MetaSimpleType<DynamicArray<String,unsigned short> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B030B0
	template bool MetaSimpleType<DynamicArray<String,unsigned short> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B030D0
	template bool MetaSimpleType<DynamicArray<String,unsigned short> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B030F0
	template int MetaSimpleType<DynamicArray<String,unsigned short> >::Slot5();
	// FUNCTION: ENGINE 0x10B03120
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<String,unsigned short> > >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B03150
	template void MetaSimpleType<mgraph::Packet<DynamicArray<String,unsigned short> > >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B03180
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<String,unsigned short> > >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B031B0
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<String,unsigned short> > >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B031E0
	template bool MetaSimpleType<mgraph::Packet<String> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B03210
	template void MetaSimpleType<mgraph::Packet<String> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B03240
	template bool MetaSimpleType<mgraph::Packet<String> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B03270
	template bool MetaSimpleType<mgraph::Packet<String> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B03360
	template bool MetaSimpleType<DynamicArray<Vector,unsigned short> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B03380
	template void MetaSimpleType<DynamicArray<Vector,unsigned short> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B033A0
	template bool MetaSimpleType<DynamicArray<Vector,unsigned short> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B033C0
	template bool MetaSimpleType<DynamicArray<Vector,unsigned short> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B033E0
	template int MetaSimpleType<DynamicArray<Vector,unsigned short> >::Slot5();
	// FUNCTION: ENGINE 0x10B03410
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B03440
	template void MetaSimpleType<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B03470
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B034A0
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B03590
	template int MetaSimpleType<DynamicArray<mgraph::TriggerData,unsigned short> >::Slot5();
	// FUNCTION: ENGINE 0x10B035C0
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B035F0
	template void MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B03620
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B03650
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B03740
	template int MetaSimpleType<DynamicArray<Complex,unsigned short> >::Slot5();
	// FUNCTION: ENGINE 0x10B03770
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B037A0
	template void MetaSimpleType<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B037D0
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B03800
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B03830
	template bool MetaSimpleType<mgraph::Packet<Complex> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B03860
	template void MetaSimpleType<mgraph::Packet<Complex> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B03890
	template bool MetaSimpleType<mgraph::Packet<Complex> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B038C0
	template bool MetaSimpleType<mgraph::Packet<Complex> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B039B0
	template int MetaSimpleType<DynamicArray<mgraph::EnvelopeData,unsigned short> >::Slot5();
	// FUNCTION: ENGINE 0x10B039E0
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B03A10
	template void MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B03A40
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B03A70
	template bool MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B03AA0
	template bool MetaSimpleType<mgraph::Packet<mgraph::EnvelopeData> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B03AD0
	template void MetaSimpleType<mgraph::Packet<mgraph::EnvelopeData> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B03B00
	template bool MetaSimpleType<mgraph::Packet<mgraph::EnvelopeData> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B03B30
	template bool MetaSimpleType<mgraph::Packet<mgraph::EnvelopeData> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B32270
	template void MetaSimpleType<DynamicArray<bool,unsigned short> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10B322A0
	template bool MetaSimpleType<DynamicArray<float,unsigned short> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B322C0
	template bool MetaSimpleType<DynamicArray<float,unsigned short> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B322E0
	template void MetaSimpleType<DynamicArray<unsigned int,unsigned short> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10B32360
	template void MetaSimpleType<DynamicArray<unsigned __int64,unsigned short> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10B323E0
	template void MetaSimpleType<DynamicArray<String,unsigned short> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10B32410
	template void MetaSimpleType<DynamicArray<Vector,unsigned short> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10B32440
	template bool MetaSimpleType<DynamicArray<mgraph::TriggerData,unsigned short> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B32460
	template void MetaSimpleType<DynamicArray<mgraph::TriggerData,unsigned short> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B32480
	template bool MetaSimpleType<DynamicArray<mgraph::TriggerData,unsigned short> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B324A0
	template bool MetaSimpleType<DynamicArray<mgraph::TriggerData,unsigned short> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B324C0
	template void MetaSimpleType<DynamicArray<mgraph::TriggerData,unsigned short> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10B324F0
	template bool MetaSimpleType<DynamicArray<Complex,unsigned short> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B32510
	template void MetaSimpleType<DynamicArray<Complex,unsigned short> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B32530
	template bool MetaSimpleType<DynamicArray<Complex,unsigned short> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B32550
	template bool MetaSimpleType<DynamicArray<Complex,unsigned short> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B32570
	template void MetaSimpleType<DynamicArray<Complex,unsigned short> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10B325F0
	template void MetaSimpleType<DynamicArray<mgraph::EnvelopeData,unsigned short> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B32610
	template bool MetaSimpleType<DynamicArray<mgraph::EnvelopeData,unsigned short> >::WriteBinary(BinaryStream*, void const*);
}
