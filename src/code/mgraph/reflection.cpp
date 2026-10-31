// The reflection of the mgraph library (0x10AC0000 - 0x10AE0000): the template instances of the om library for the
// node types, their pins and their properties, in the order the compiler emitted them (a guess: one translation unit).
#include "code/audio/drivers.h"
#include "code/mgraph/nodes.h"
#include "code/om/delegate.h"
#include "code/om/invoke.h"
#include "code/om/metaclass.h"
#include "code/om/metaenum.h"
#include "code/om/metamethod.h"
#include "code/om/metaproperty.h"
#include "code/om/metasimpletype.h"

#pragma warning(disable: 4661)

namespace om
{
	using namespace mgraph;

	// FUNCTION: ENGINE 0x10AC2850
	template MetaClass<audio::XAudio2RendererDriver>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AC2880
	template type_info const* MetaClass<audio::XAudio2RendererDriver>::GetType();
	// FUNCTION: ENGINE 0x10AC28C0
	template void MetaClass<audio::XAudio2RendererDriver>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC2900
	template char const* MetaClass<audio::XAudio2RendererDriver>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC2E20
	template int MetaClass<audio::XAudio2RendererDriver>::Slot5();
	// FUNCTION: ENGINE 0x10AC2E30
	template void MetaClass<audio::XAudio2RendererDriver>::Slot6(void*);
	// FUNCTION: ENGINE 0x10AC2E40
	template void* MetaClass<audio::XAudio2RendererDriver>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC2EB0
	template void MetaClass<audio::XAudio2RendererDriver>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AC5D40
	template MetaClass<mgraph::Graph>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AC5D70
	template type_info const* MetaClass<mgraph::Graph>::GetType();
	// FUNCTION: ENGINE 0x10AC5DB0
	template void MetaClass<mgraph::Graph>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC5F70
	template char const* MetaClass<mgraph::Graph>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC65C0
	template int MetaClass<mgraph::Graph>::Slot5();
	// FUNCTION: ENGINE 0x10AC65D0
	template void MetaClass<mgraph::Graph>::Slot6(void*);
	// FUNCTION: ENGINE 0x10AC65E0
	template void* MetaClass<mgraph::Graph>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC73D0
	template void MetaClass<mgraph::Graph>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AC8A70
	template MetaClass<mgraph::NodeColour>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AC8AA0
	template type_info const* MetaClass<mgraph::NodeColour>::GetType();
	// FUNCTION: ENGINE 0x10AC8AE0
	template void MetaClass<mgraph::Node>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC8B00
	template MetaClass<mgraph::Node>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AC8B30
	template type_info const* MetaClass<mgraph::Node>::GetType();
	// FUNCTION: ENGINE 0x10AC8B70
	template void MetaClass<mgraph::NodeColour>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC8BF0
	template char const* MetaClass<mgraph::NodeColour>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC8C00
	template char const* MetaClass<mgraph::Node>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC9160
	template int MetaClass<mgraph::NodeColour>::Slot5();
	// FUNCTION: ENGINE 0x10AC9170
	template void MetaClass<mgraph::NodeColour>::Slot6(void*);
	// FUNCTION: ENGINE 0x10AC91A0
	template int MetaClass<mgraph::Node>::Slot5();
	// FUNCTION: ENGINE 0x10AC91B0
	template void MetaClass<mgraph::Node>::Slot6(void*);
	// FUNCTION: ENGINE 0x10AC91E0
	template void* MetaClass<mgraph::NodeColour>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC9230
	template void* MetaClass<mgraph::Node>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ACA0F0
	template void MetaClass<mgraph::NodeColour>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ACA1B0
	template void MetaClass<mgraph::Node>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ACC020
	template MetaClass<mgraph::LinkedGraph>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ACC050
	template type_info const* MetaClass<mgraph::LinkedGraph>::GetType();
	// FUNCTION: ENGINE 0x10ACC090
	template void MetaClass<mgraph::LinkedGraph>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ACC100
	template char const* MetaClass<mgraph::LinkedGraph>::AllocationTag();
	// FUNCTION: ENGINE 0x10ACC200
	template int MetaClass<mgraph::LinkedGraph>::Slot5();
	// FUNCTION: ENGINE 0x10ACC210
	template void MetaClass<mgraph::LinkedGraph>::Slot6(void*);
	// FUNCTION: ENGINE 0x10ACC240
	template void* MetaClass<mgraph::LinkedGraph>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ACC5C0
	template void MetaClass<mgraph::LinkedGraph>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ACD0E0
	template MetaClass<mgraph::EmbeddedGraph>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ACD110
	template type_info const* MetaClass<mgraph::EmbeddedGraph>::GetType();
	// FUNCTION: ENGINE 0x10ACD150
	template void MetaClass<mgraph::EmbeddedGraph>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ACD1C0
	template char const* MetaClass<mgraph::EmbeddedGraph>::AllocationTag();
	// FUNCTION: ENGINE 0x10ACD240
	template int MetaClass<mgraph::EmbeddedGraph>::Slot5();
	// FUNCTION: ENGINE 0x10ACD250
	template void MetaClass<mgraph::EmbeddedGraph>::Slot6(void*);
	// FUNCTION: ENGINE 0x10ACD280
	template void* MetaClass<mgraph::EmbeddedGraph>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ACD540
	template void MetaClass<mgraph::EmbeddedGraph>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD2B10
	template MetaClass<mgraph::GraphItem>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD2B40
	template type_info const* MetaClass<mgraph::GraphItem>::GetType();
	// FUNCTION: ENGINE 0x10AD2B80
	template void MetaClass<mgraph::GraphItem>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD2BA0
	template char const* MetaClass<mgraph::GraphItem>::AllocationTag();
	// FUNCTION: ENGINE 0x10AD2BD0
	template int MetaClass<mgraph::GraphItem>::Slot5();
	// FUNCTION: ENGINE 0x10AD2BE0
	template void MetaClass<mgraph::GraphItem>::Slot6(void*);
	// FUNCTION: ENGINE 0x10AD2BF0
	template void* MetaClass<mgraph::GraphItem>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AD2C40
	template void MetaClass<mgraph::GraphItem>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD4250
	template MetaClass<mgraph::PropertyNodeBase>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD4280
	template type_info const* MetaClass<mgraph::PropertyNodeBase>::GetType();
	// FUNCTION: ENGINE 0x10AD42C0
	template void MetaClass<mgraph::CommutativeMath<mgraph::VectorAdd> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD42E0
	template MetaClass<mgraph::CommutativeMath<mgraph::VectorAdd> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD4310
	template type_info const* MetaClass<mgraph::CommutativeMath<mgraph::VectorAdd> >::GetType();
	// FUNCTION: ENGINE 0x10AD4340
	template MetaClass<mgraph::CommutativeMath<mgraph::FloatAdd> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD4370
	template type_info const* MetaClass<mgraph::CommutativeMath<mgraph::FloatAdd> >::GetType();
	// FUNCTION: ENGINE 0x10AD43A0
	template MetaClass<mgraph::CommutativeMath<mgraph::FloatMultiply> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD43D0
	template type_info const* MetaClass<mgraph::CommutativeMath<mgraph::FloatMultiply> >::GetType();
	// FUNCTION: ENGINE 0x10AD4400
	template MetaClass<mgraph::CommutativeMath<mgraph::BoolOr> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD4430
	template type_info const* MetaClass<mgraph::CommutativeMath<mgraph::BoolOr> >::GetType();
	// FUNCTION: ENGINE 0x10AD4460
	template MetaClass<mgraph::CommutativeMath<mgraph::BoolAnd> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD4490
	template type_info const* MetaClass<mgraph::CommutativeMath<mgraph::BoolAnd> >::GetType();
	// FUNCTION: ENGINE 0x10AD44C0
	template MetaClass<mgraph::CommutativeMath<mgraph::TriggerAnd> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD44F0
	template type_info const* MetaClass<mgraph::CommutativeMath<mgraph::TriggerAnd> >::GetType();
	// FUNCTION: ENGINE 0x10AD4520
	template MetaClass<mgraph::CommutativeMath<mgraph::TriggerOr> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD4550
	template type_info const* MetaClass<mgraph::CommutativeMath<mgraph::TriggerOr> >::GetType();
	// FUNCTION: ENGINE 0x10AD4580
	template MetaClass<mgraph::NonCommutativeMath<mgraph::FloatSub> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD45B0
	template type_info const* MetaClass<mgraph::NonCommutativeMath<mgraph::FloatSub> >::GetType();
	// FUNCTION: ENGINE 0x10AD45E0
	template MetaClass<mgraph::Operator2<mgraph::GreaterThan<float> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD4610
	template type_info const* MetaClass<mgraph::Operator2<mgraph::GreaterThan<float> > >::GetType();
	// FUNCTION: ENGINE 0x10AD4640
	template MetaClass<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD4670
	template type_info const* MetaClass<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::GetType();
	// FUNCTION: ENGINE 0x10AD46A0
	template MetaClass<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD46D0
	template type_info const* MetaClass<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::GetType();
	// FUNCTION: ENGINE 0x10AD4700
	template MetaClass<mgraph::Operator2<mgraph::LessThan<float> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD4730
	template type_info const* MetaClass<mgraph::Operator2<mgraph::LessThan<float> > >::GetType();
	// FUNCTION: ENGINE 0x10AD4760
	template MetaClass<mgraph::Operator2<mgraph::Equal<float> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD4790
	template type_info const* MetaClass<mgraph::Operator2<mgraph::Equal<float> > >::GetType();
	// FUNCTION: ENGINE 0x10AD47C0
	template MetaClass<mgraph::Operator2<mgraph::NotEqual<float> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD47F0
	template type_info const* MetaClass<mgraph::Operator2<mgraph::NotEqual<float> > >::GetType();
	// FUNCTION: ENGINE 0x10AD4820
	template MetaClass<mgraph::UnaryMath<mgraph::BoolNot> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD4850
	template type_info const* MetaClass<mgraph::UnaryMath<mgraph::BoolNot> >::GetType();
	// FUNCTION: ENGINE 0x10AD4990
	template void MetaClass<mgraph::PropertyNodeBase>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD49B0
	template void MetaClass<mgraph::CommutativeMath<mgraph::FloatAdd> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD49D0
	template void MetaClass<mgraph::CommutativeMath<mgraph::FloatMultiply> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD49F0
	template void MetaClass<mgraph::CommutativeMath<mgraph::BoolOr> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD4A10
	template void MetaClass<mgraph::CommutativeMath<mgraph::BoolAnd> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD4A30
	template void MetaClass<mgraph::CommutativeMath<mgraph::TriggerAnd> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD4A50
	template void MetaClass<mgraph::CommutativeMath<mgraph::TriggerOr> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD4A70
	template void MetaClass<mgraph::NonCommutativeMath<mgraph::FloatSub> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD4A90
	template void MetaClass<mgraph::Operator2<mgraph::GreaterThan<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD4AB0
	template void MetaClass<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD4AD0
	template void MetaClass<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD4AF0
	template void MetaClass<mgraph::Operator2<mgraph::LessThan<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD4B10
	template void MetaClass<mgraph::Operator2<mgraph::Equal<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD4B30
	template void MetaClass<mgraph::Operator2<mgraph::NotEqual<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD4B50
	template void MetaClass<mgraph::UnaryMath<mgraph::BoolNot> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD64B0
	template MetaClass<mgraph::Rand<Vector> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD64E0
	template type_info const* MetaClass<mgraph::Rand<Vector> >::GetType();
	// FUNCTION: ENGINE 0x10AD6510
	template MetaClass<mgraph::Rand<float> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6540
	template type_info const* MetaClass<mgraph::Rand<float> >::GetType();
	// FUNCTION: ENGINE 0x10AD6570
	template MetaClass<mgraph::Rand<unsigned int> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD65A0
	template type_info const* MetaClass<mgraph::Rand<unsigned int> >::GetType();
	// FUNCTION: ENGINE 0x10AD6600
	template void MetaClass<mgraph::Rand<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD6620
	template void MetaClass<mgraph::Rand<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD6640
	template void MetaClass<mgraph::Throw<mgraph::Packet<bool> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD6660
	template MetaClass<mgraph::Throw<mgraph::Packet<bool> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6690
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<bool> > >::GetType();
	// FUNCTION: ENGINE 0x10AD66C0
	template MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD66F0
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD6720
	template MetaClass<mgraph::Throw<mgraph::Packet<float> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6750
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<float> > >::GetType();
	// FUNCTION: ENGINE 0x10AD6780
	template MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD67B0
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD67E0
	template MetaClass<mgraph::Throw<mgraph::Packet<unsigned int> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6810
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<unsigned int> > >::GetType();
	// FUNCTION: ENGINE 0x10AD6840
	template MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6870
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD68A0
	template MetaClass<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD68D0
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::GetType();
	// FUNCTION: ENGINE 0x10AD6900
	template MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6930
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD6960
	template MetaClass<mgraph::Throw<mgraph::Packet<String> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6990
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<String> > >::GetType();
	// FUNCTION: ENGINE 0x10AD69C0
	template MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD69F0
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD6A20
	template MetaClass<mgraph::Throw<mgraph::Packet<Vector> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6A50
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<Vector> > >::GetType();
	// FUNCTION: ENGINE 0x10AD6A80
	template MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6AB0
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD6AE0
	template MetaClass<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6B10
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::GetType();
	// FUNCTION: ENGINE 0x10AD6B40
	template MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6B70
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD6BA0
	template MetaClass<mgraph::Throw<mgraph::Packet<Complex> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6BD0
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<Complex> > >::GetType();
	// FUNCTION: ENGINE 0x10AD6C00
	template MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6C30
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD6C60
	template MetaClass<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6C90
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::GetType();
	// FUNCTION: ENGINE 0x10AD6CC0
	template MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6CF0
	template type_info const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD6D20
	template MetaClass<mgraph::Catch<mgraph::Packet<bool> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6D50
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<bool> > >::GetType();
	// FUNCTION: ENGINE 0x10AD6D80
	template MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6DB0
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD6DE0
	template MetaClass<mgraph::Catch<mgraph::Packet<float> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6E10
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<float> > >::GetType();
	// FUNCTION: ENGINE 0x10AD6E40
	template MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6E70
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD6EA0
	template MetaClass<mgraph::Catch<mgraph::Packet<unsigned int> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6ED0
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<unsigned int> > >::GetType();
	// FUNCTION: ENGINE 0x10AD6F00
	template MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6F30
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD6F60
	template MetaClass<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6F90
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::GetType();
	// FUNCTION: ENGINE 0x10AD6FC0
	template MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD6FF0
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD7020
	template MetaClass<mgraph::Catch<mgraph::Packet<String> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD7050
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<String> > >::GetType();
	// FUNCTION: ENGINE 0x10AD7080
	template MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD70B0
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD70E0
	template MetaClass<mgraph::Catch<mgraph::Packet<Vector> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD7110
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<Vector> > >::GetType();
	// FUNCTION: ENGINE 0x10AD7140
	template MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD7170
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD71A0
	template MetaClass<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD71D0
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::GetType();
	// FUNCTION: ENGINE 0x10AD7200
	template MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD7230
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD7260
	template MetaClass<mgraph::Catch<mgraph::Packet<Complex> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD7290
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<Complex> > >::GetType();
	// FUNCTION: ENGINE 0x10AD72C0
	template MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD72F0
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD7320
	template MetaClass<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD7350
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::GetType();
	// FUNCTION: ENGINE 0x10AD7380
	template MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AD73B0
	template type_info const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10AD7620
	template void MetaClass<mgraph::Rand<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7640
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7660
	template void MetaClass<mgraph::Throw<mgraph::Packet<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7680
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD76A0
	template void MetaClass<mgraph::Throw<mgraph::Packet<unsigned int> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD76C0
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD76E0
	template void MetaClass<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7700
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7720
	template void MetaClass<mgraph::Throw<mgraph::Packet<String> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7740
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7760
	template void MetaClass<mgraph::Throw<mgraph::Packet<Vector> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7780
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD77A0
	template void MetaClass<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD77C0
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD77E0
	template void MetaClass<mgraph::Throw<mgraph::Packet<Complex> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7800
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7820
	template void MetaClass<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7840
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7860
	template void MetaClass<mgraph::Catch<mgraph::Packet<bool> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7880
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD78A0
	template void MetaClass<mgraph::Catch<mgraph::Packet<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD78C0
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD78E0
	template void MetaClass<mgraph::Catch<mgraph::Packet<unsigned int> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7900
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7920
	template void MetaClass<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7940
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7960
	template void MetaClass<mgraph::Catch<mgraph::Packet<String> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7980
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD79A0
	template void MetaClass<mgraph::Catch<mgraph::Packet<Vector> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD79C0
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD79E0
	template void MetaClass<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7A00
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7A20
	template void MetaClass<mgraph::Catch<mgraph::Packet<Complex> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7A40
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7A60
	template void MetaClass<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AD7A80
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADA2A0
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<bool> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA2D0
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<bool> > >::GetType();
	// FUNCTION: ENGINE 0x10ADA300
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA330
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADA360
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<float> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA390
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<float> > >::GetType();
	// FUNCTION: ENGINE 0x10ADA3C0
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA3F0
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADA420
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA450
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::GetType();
	// FUNCTION: ENGINE 0x10ADA480
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA4B0
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADA4E0
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA510
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::GetType();
	// FUNCTION: ENGINE 0x10ADA540
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA570
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADA5A0
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<String> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA5D0
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<String> > >::GetType();
	// FUNCTION: ENGINE 0x10ADA600
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA630
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADA660
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<Vector> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA690
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<Vector> > >::GetType();
	// FUNCTION: ENGINE 0x10ADA6C0
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA6F0
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADA720
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA750
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADA780
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<Complex> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA7B0
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<Complex> > >::GetType();
	// FUNCTION: ENGINE 0x10ADA7E0
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA810
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADA840
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA870
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::GetType();
	// FUNCTION: ENGINE 0x10ADA8A0
	template MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA8D0
	template type_info const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADA900
	template MetaClass<mgraph::Inlet<mgraph::Packet<bool> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA930
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<bool> > >::GetType();
	// FUNCTION: ENGINE 0x10ADA960
	template MetaClass<mgraph::Outlet<mgraph::Packet<bool> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA990
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<bool> > >::GetType();
	// FUNCTION: ENGINE 0x10ADA9C0
	template MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADA9F0
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADAA20
	template MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADAA50
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADAA80
	template MetaClass<mgraph::Inlet<mgraph::Packet<float> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADAAB0
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<float> > >::GetType();
	// FUNCTION: ENGINE 0x10ADAAE0
	template MetaClass<mgraph::Outlet<mgraph::Packet<float> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADAB10
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<float> > >::GetType();
	// FUNCTION: ENGINE 0x10ADAB40
	template MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADAB70
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADABA0
	template MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADABD0
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADAC00
	template MetaClass<mgraph::Inlet<mgraph::Packet<unsigned int> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADAC30
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<unsigned int> > >::GetType();
	// FUNCTION: ENGINE 0x10ADAC60
	template MetaClass<mgraph::Outlet<mgraph::Packet<unsigned int> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADAC90
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<unsigned int> > >::GetType();
	// FUNCTION: ENGINE 0x10ADACC0
	template MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADACF0
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADAD20
	template MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADAD50
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADAD80
	template MetaClass<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADADB0
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::GetType();
	// FUNCTION: ENGINE 0x10ADADE0
	template MetaClass<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADAE10
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::GetType();
	// FUNCTION: ENGINE 0x10ADAE40
	template MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADAE70
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADAEA0
	template MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADAED0
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADAF00
	template MetaClass<mgraph::Inlet<mgraph::Packet<String> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADAF30
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<String> > >::GetType();
	// FUNCTION: ENGINE 0x10ADAF60
	template MetaClass<mgraph::Outlet<mgraph::Packet<String> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADAF90
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<String> > >::GetType();
	// FUNCTION: ENGINE 0x10ADAFC0
	template MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADAFF0
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADB020
	template MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB050
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADB080
	template MetaClass<mgraph::Inlet<mgraph::Packet<Vector> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB0B0
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<Vector> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB0E0
	template MetaClass<mgraph::Outlet<mgraph::Packet<Vector> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB110
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<Vector> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB140
	template MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB170
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADB1A0
	template MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB1D0
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADB200
	template MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB230
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB260
	template MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB290
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB2C0
	template MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB2F0
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADB320
	template MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB350
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADB380
	template MetaClass<mgraph::Inlet<mgraph::Packet<Complex> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB3B0
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<Complex> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB3E0
	template MetaClass<mgraph::Outlet<mgraph::Packet<Complex> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB410
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<Complex> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB440
	template MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB470
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADB4A0
	template MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB4D0
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADB500
	template MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB530
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB560
	template MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB590
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB5C0
	template MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB5F0
	template type_info const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADB620
	template MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB650
	template type_info const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::GetType();
	// FUNCTION: ENGINE 0x10ADB680
	template MetaClass<mgraph::Switch<mgraph::Packet<bool> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB6B0
	template type_info const* MetaClass<mgraph::Switch<mgraph::Packet<bool> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB6E0
	template MetaClass<mgraph::Switch<mgraph::Packet<float> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB710
	template type_info const* MetaClass<mgraph::Switch<mgraph::Packet<float> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB740
	template MetaClass<mgraph::Switch<mgraph::Packet<unsigned int> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB770
	template type_info const* MetaClass<mgraph::Switch<mgraph::Packet<unsigned int> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB7A0
	template MetaClass<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB7D0
	template type_info const* MetaClass<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB800
	template MetaClass<mgraph::Switch<mgraph::Packet<String> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB830
	template type_info const* MetaClass<mgraph::Switch<mgraph::Packet<String> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB860
	template MetaClass<mgraph::Switch<mgraph::Packet<Vector> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB890
	template type_info const* MetaClass<mgraph::Switch<mgraph::Packet<Vector> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB8C0
	template MetaClass<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB8F0
	template type_info const* MetaClass<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB920
	template MetaClass<mgraph::Switch<mgraph::Packet<Complex> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB950
	template type_info const* MetaClass<mgraph::Switch<mgraph::Packet<Complex> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB980
	template MetaClass<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADB9B0
	template type_info const* MetaClass<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::GetType();
	// FUNCTION: ENGINE 0x10ADB9E0
	template MetaClass<mgraph::ListCount<bool> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBA10
	template type_info const* MetaClass<mgraph::ListCount<bool> >::GetType();
	// FUNCTION: ENGINE 0x10ADBA40
	template MetaClass<mgraph::ListEntry<bool> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBA70
	template type_info const* MetaClass<mgraph::ListEntry<bool> >::GetType();
	// FUNCTION: ENGINE 0x10ADBAA0
	template MetaClass<mgraph::ListCount<float> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBAD0
	template type_info const* MetaClass<mgraph::ListCount<float> >::GetType();
	// FUNCTION: ENGINE 0x10ADBB00
	template MetaClass<mgraph::ListEntry<float> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBB30
	template type_info const* MetaClass<mgraph::ListEntry<float> >::GetType();
	// FUNCTION: ENGINE 0x10ADBB60
	template MetaClass<mgraph::ListCount<unsigned int> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBB90
	template type_info const* MetaClass<mgraph::ListCount<unsigned int> >::GetType();
	// FUNCTION: ENGINE 0x10ADBBC0
	template MetaClass<mgraph::ListEntry<unsigned int> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBBF0
	template type_info const* MetaClass<mgraph::ListEntry<unsigned int> >::GetType();
	// FUNCTION: ENGINE 0x10ADBC20
	template MetaClass<mgraph::ListCount<unsigned __int64> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBC50
	template type_info const* MetaClass<mgraph::ListCount<unsigned __int64> >::GetType();
	// FUNCTION: ENGINE 0x10ADBC80
	template MetaClass<mgraph::ListEntry<unsigned __int64> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBCB0
	template type_info const* MetaClass<mgraph::ListEntry<unsigned __int64> >::GetType();
	// FUNCTION: ENGINE 0x10ADBCE0
	template MetaClass<mgraph::ListCount<String> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBD10
	template type_info const* MetaClass<mgraph::ListCount<String> >::GetType();
	// FUNCTION: ENGINE 0x10ADBD40
	template MetaClass<mgraph::ListEntry<String> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBD70
	template type_info const* MetaClass<mgraph::ListEntry<String> >::GetType();
	// FUNCTION: ENGINE 0x10ADBDA0
	template MetaClass<mgraph::ListCount<Vector> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBDD0
	template type_info const* MetaClass<mgraph::ListCount<Vector> >::GetType();
	// FUNCTION: ENGINE 0x10ADBE00
	template MetaClass<mgraph::ListEntry<Vector> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBE30
	template type_info const* MetaClass<mgraph::ListEntry<Vector> >::GetType();
	// FUNCTION: ENGINE 0x10ADBE60
	template MetaClass<mgraph::ListCount<mgraph::TriggerData> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBE90
	template type_info const* MetaClass<mgraph::ListCount<mgraph::TriggerData> >::GetType();
	// FUNCTION: ENGINE 0x10ADBEC0
	template MetaClass<mgraph::ListEntry<mgraph::TriggerData> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBEF0
	template type_info const* MetaClass<mgraph::ListEntry<mgraph::TriggerData> >::GetType();
	// FUNCTION: ENGINE 0x10ADBF20
	template MetaClass<mgraph::ListCount<Complex> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBF50
	template type_info const* MetaClass<mgraph::ListCount<Complex> >::GetType();
	// FUNCTION: ENGINE 0x10ADBF80
	template MetaClass<mgraph::ListEntry<Complex> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADBFB0
	template type_info const* MetaClass<mgraph::ListEntry<Complex> >::GetType();
	// FUNCTION: ENGINE 0x10ADBFE0
	template MetaClass<mgraph::ListCount<mgraph::EnvelopeData> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADC010
	template type_info const* MetaClass<mgraph::ListCount<mgraph::EnvelopeData> >::GetType();
	// FUNCTION: ENGINE 0x10ADC040
	template MetaClass<mgraph::ListEntry<mgraph::EnvelopeData> >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ADC070
	template type_info const* MetaClass<mgraph::ListEntry<mgraph::EnvelopeData> >::GetType();
	// FUNCTION: ENGINE 0x10ADC5A0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<bool> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC5C0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC5E0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC600
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC620
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC640
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC660
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC680
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC6A0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<String> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC6C0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC6E0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<Vector> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC700
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC720
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC740
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<Complex> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC760
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC780
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC7A0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC7C0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<bool> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC7E0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<bool> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC800
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC820
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC840
	template void MetaClass<mgraph::Inlet<mgraph::Packet<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC860
	template void MetaClass<mgraph::Outlet<mgraph::Packet<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC880
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC8A0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC8C0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<unsigned int> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC8E0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<unsigned int> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC900
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC920
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC940
	template void MetaClass<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC960
	template void MetaClass<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC980
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC9A0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC9C0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<String> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADC9E0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<String> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCA00
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCA20
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCA40
	template void MetaClass<mgraph::Inlet<mgraph::Packet<Vector> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCA60
	template void MetaClass<mgraph::Outlet<mgraph::Packet<Vector> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCA80
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCAA0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCAC0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCAE0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCB00
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCB20
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCB40
	template void MetaClass<mgraph::Inlet<mgraph::Packet<Complex> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCB60
	template void MetaClass<mgraph::Outlet<mgraph::Packet<Complex> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCB80
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCBA0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCBC0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCBE0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCC00
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCC20
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCC40
	template void MetaClass<mgraph::Switch<mgraph::Packet<bool> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCC60
	template void MetaClass<mgraph::Switch<mgraph::Packet<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCC80
	template void MetaClass<mgraph::Switch<mgraph::Packet<unsigned int> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCCA0
	template void MetaClass<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCCC0
	template void MetaClass<mgraph::Switch<mgraph::Packet<String> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCCE0
	template void MetaClass<mgraph::Switch<mgraph::Packet<Vector> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCD00
	template void MetaClass<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCD20
	template void MetaClass<mgraph::Switch<mgraph::Packet<Complex> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCD40
	template void MetaClass<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCD60
	template void MetaClass<mgraph::ListCount<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCD80
	template void MetaClass<mgraph::ListEntry<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCDA0
	template void MetaClass<mgraph::ListCount<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCDC0
	template void MetaClass<mgraph::ListEntry<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCDE0
	template void MetaClass<mgraph::ListCount<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCE00
	template void MetaClass<mgraph::ListEntry<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCE20
	template void MetaClass<mgraph::ListCount<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCE40
	template void MetaClass<mgraph::ListEntry<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCE60
	template void MetaClass<mgraph::ListCount<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCE80
	template void MetaClass<mgraph::ListEntry<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCEA0
	template void MetaClass<mgraph::ListCount<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCEC0
	template void MetaClass<mgraph::ListEntry<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCEE0
	template void MetaClass<mgraph::ListCount<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCF00
	template void MetaClass<mgraph::ListEntry<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCF20
	template void MetaClass<mgraph::ListCount<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCF40
	template void MetaClass<mgraph::ListEntry<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCF60
	template void MetaClass<mgraph::ListCount<mgraph::EnvelopeData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCF80
	template void MetaClass<mgraph::ListEntry<mgraph::EnvelopeData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC5C20
	template MetaMethod1Base<void,mgraph::NodeColour const&>* MetaProperty<mgraph::NodeColour const&>::GetSetter();
	// FUNCTION: ENGINE 0x10AC5C30
	template MetaMethod0Base<mgraph::NodeColour const&>* MetaProperty<mgraph::NodeColour const&>::GetGetter();
	// FUNCTION: ENGINE 0x10AC5C70
	template void MetaProperty<mgraph::NodeColour const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC8C60
	template type_info const* MetaProperty<mgraph::NodeColour const&>::GetValueType();
	// FUNCTION: ENGINE 0x10AC8CB0
	template type_info const* MetaProperty<int>::GetValueType();
	// FUNCTION: ENGINE 0x10AC8D20
	template MetaMethod1Base<void,int>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AC8DA0
	template MetaMethod0Base<int>::MetaMethod0Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AC8ED0
	template char const* MetaMethod1<mgraph::Node,mgraph::Node,void,int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC8EE0
	template char const* MetaMethod1<mgraph::NodeColour,mgraph::NodeColour,void,unsigned int const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC8EF0
	template char const* MetaMethod0Const<mgraph::NodeColour,mgraph::NodeColour,unsigned int const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC8F00
	template char const* MetaMethod1<mgraph::Node,mgraph::Node,void,mgraph::NodeColour const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC8F10
	template char const* MetaMethod0Const<mgraph::Node,mgraph::Node,mgraph::NodeColour const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC8F20
	template char const* MetaProperty<mgraph::NodeColour const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC8F30
	template char const* MetaMethod1<mgraph::Node,mgraph::Node,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC8F40
	template char const* MetaMethod0Const<mgraph::Node,mgraph::Node,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC8F50
	template char const* MetaMethod0Const<mgraph::Node,mgraph::Node,int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC8F60
	template char const* MetaProperty<int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC8FD0
	template bool om::ReadBinary<class mgraph::NodeColour>(BinaryStream*, mgraph::NodeColour*);
	// FUNCTION: ENGINE 0x10AC9000
	template void om::WriteResult<class mgraph::NodeColour>(BinaryStream*, mgraph::NodeColour const&);
	// FUNCTION: ENGINE 0x10AC9070
	template char const* DelegateMetaProperty<mgraph::NodeColour const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC9080
	template char const* DelegateMetaProperty<int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC9090
	template bool om::ReadText<class mgraph::NodeColour>(TextValue const*, mgraph::NodeColour*);
	// FUNCTION: ENGINE 0x10AC90C0
	template void om::WriteText<class mgraph::NodeColour>(TextValue*, mgraph::NodeColour const&);
	// FUNCTION: ENGINE 0x10AC9340
	template void* MetaMethod1<mgraph::Node,mgraph::Node,void,int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC9390
	template void MetaMethod1<mgraph::Node,mgraph::Node,void,int>::Call(void*, int);
	// FUNCTION: ENGINE 0x10AC93C0
	template void MetaMethod1<mgraph::Node,mgraph::Node,void,int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC9400
	template void* MetaMethod1<mgraph::NodeColour,mgraph::NodeColour,void,unsigned int const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC9420
	template MetaMethod1<mgraph::NodeColour,mgraph::NodeColour,void,unsigned int const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::NodeColour,mgraph::NodeColour,void,unsigned int const&>::Function);
	// FUNCTION: ENGINE 0x10AC9450
	template void MetaMethod1<mgraph::NodeColour,mgraph::NodeColour,void,unsigned int const&>::Call(void*, unsigned int const&);
	// FUNCTION: ENGINE 0x10AC9470
	template MetaMethod1<mgraph::NodeColour,mgraph::NodeColour,void,unsigned int const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AC9480
	template void MetaMethod1<mgraph::NodeColour,mgraph::NodeColour,void,unsigned int const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC94A0
	template void* MetaMethod0Const<mgraph::NodeColour,mgraph::NodeColour,unsigned int const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC94C0
	template MetaMethod0Const<mgraph::NodeColour,mgraph::NodeColour,unsigned int const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::NodeColour,mgraph::NodeColour,unsigned int const&>::Function);
	// FUNCTION: ENGINE 0x10AC94F0
	template unsigned int const& MetaMethod0Const<mgraph::NodeColour,mgraph::NodeColour,unsigned int const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AC9500
	template MetaMethod0Const<mgraph::NodeColour,mgraph::NodeColour,unsigned int const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AC9510
	template void MetaMethod0Const<mgraph::NodeColour,mgraph::NodeColour,unsigned int const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC9530
	template void MetaMethod0Const<mgraph::NodeColour,mgraph::NodeColour,unsigned int const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10AC95D0
	template void* MetaMethod1<mgraph::Node,mgraph::Node,void,mgraph::NodeColour const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC95F0
	template MetaMethod1<mgraph::Node,mgraph::Node,void,mgraph::NodeColour const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Node,mgraph::Node,void,mgraph::NodeColour const&>::Function);
	// FUNCTION: ENGINE 0x10AC9620
	template void MetaMethod1<mgraph::Node,mgraph::Node,void,mgraph::NodeColour const&>::Call(void*, mgraph::NodeColour const&);
	// FUNCTION: ENGINE 0x10AC9650
	template void MetaMethod1<mgraph::Node,mgraph::Node,void,mgraph::NodeColour const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC9670
	template char const* Garbage<mgraph::NodeColour>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC9680
	template void* MetaMethod0Const<mgraph::Node,mgraph::Node,mgraph::NodeColour const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC96A0
	template MetaMethod0Const<mgraph::Node,mgraph::Node,mgraph::NodeColour const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Node,mgraph::Node,mgraph::NodeColour const&>::Function);
	// FUNCTION: ENGINE 0x10AC96D0
	template mgraph::NodeColour const& MetaMethod0Const<mgraph::Node,mgraph::Node,mgraph::NodeColour const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AC96F0
	template void MetaMethod0Const<mgraph::Node,mgraph::Node,mgraph::NodeColour const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC9710
	template void* MetaProperty<mgraph::NodeColour const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC9730
	template void* MetaMethod1<mgraph::Node,mgraph::Node,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC9750
	template MetaMethod1<mgraph::Node,mgraph::Node,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Node,mgraph::Node,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AC9780
	template void MetaMethod1<mgraph::Node,mgraph::Node,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AC97B0
	template void MetaMethod1<mgraph::Node,mgraph::Node,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC97D0
	template void* MetaMethod0Const<mgraph::Node,mgraph::Node,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC97F0
	template MetaMethod0Const<mgraph::Node,mgraph::Node,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Node,mgraph::Node,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AC9820
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Node,mgraph::Node,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AC9840
	template void MetaMethod0Const<mgraph::Node,mgraph::Node,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC9860
	template void* MetaMethod0Const<mgraph::Node,mgraph::Node,int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC98B0
	template int MetaMethod0Const<mgraph::Node,mgraph::Node,int>::Call(void*);
	// FUNCTION: ENGINE 0x10AC98D0
	template void MetaMethod0Const<mgraph::Node,mgraph::Node,int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC98F0
	template void* MetaProperty<int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC9D10
	template bool om::ReadBinary<class mgraph::TriggerData>(BinaryStream*, mgraph::TriggerData*);
	// FUNCTION: ENGINE 0x10AC9D40
	template void* DelegateMetaProperty<mgraph::NodeColour const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC9D60
	template void* DelegateMetaProperty<int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC9D80
	template void* Garbage<mgraph::NodeColour>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AC9DA0
	template Garbage<mgraph::NodeColour>::Garbage(mgraph::NodeColour*);
	// FUNCTION: ENGINE 0x10AC9DC0
	template Garbage<mgraph::NodeColour>::~Garbage();
	// FUNCTION: ENGINE 0x10AC9DE0
	template void Garbage<mgraph::NodeColour>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC9E00
	template DelegateProperty<mgraph::NodeColour>::DelegateProperty();
	// FUNCTION: ENGINE 0x10AC9E10
	template MetaTypeBase* DelegateProperty<mgraph::NodeColour>::GetMetaType();
	// FUNCTION: ENGINE 0x10AC9E20
	template DelegateProperty<mgraph::NodeColour>::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AC9E90
	template bool om::ReadText<class mgraph::TriggerData>(TextValue const*, mgraph::TriggerData*);
	// FUNCTION: ENGINE 0x10AC9EC0
	template void om::WriteText<class mgraph::TriggerData>(TextValue*, mgraph::TriggerData const&);
	// FUNCTION: ENGINE 0x10ACA280
	template MetaMethod1<mgraph::NodeColour,mgraph::NodeColour,void,unsigned int const&>* MetaMethod1<mgraph::NodeColour,mgraph::NodeColour,void,unsigned int const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::NodeColour,mgraph::NodeColour,void,unsigned int const&>::Function);
	// FUNCTION: ENGINE 0x10ACA2C0
	template MetaMethod0Const<mgraph::NodeColour,mgraph::NodeColour,unsigned int const&>* MetaMethod0Const<mgraph::NodeColour,mgraph::NodeColour,unsigned int const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::NodeColour,mgraph::NodeColour,unsigned int const&>::Function);
	// FUNCTION: ENGINE 0x10ACA360
	template MetaMethod1<mgraph::Node,mgraph::Node,void,mgraph::NodeColour const&>* MetaMethod1<mgraph::Node,mgraph::Node,void,mgraph::NodeColour const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Node,mgraph::Node,void,mgraph::NodeColour const&>::Function);
	// FUNCTION: ENGINE 0x10ACA3A0
	template MetaMethod0Const<mgraph::Node,mgraph::Node,mgraph::NodeColour const&>* MetaMethod0Const<mgraph::Node,mgraph::Node,mgraph::NodeColour const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Node,mgraph::Node,mgraph::NodeColour const&>::Function);
	// FUNCTION: ENGINE 0x10ACA440
	template MetaMethod1<mgraph::Node,mgraph::Node,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Node,mgraph::Node,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Node,mgraph::Node,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10ACA480
	template MetaMethod0Const<mgraph::Node,mgraph::Node,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Node,mgraph::Node,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Node,mgraph::Node,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10ACA690
	template bool om::WriteBinary<class mgraph::NodeColour>(BinaryStream*, mgraph::NodeColour const&);
	// FUNCTION: ENGINE 0x10ACA8F0
	template void MetaProperty<mgraph::NodeColour const&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10ACA9E0
	template bool MetaProperty<mgraph::NodeColour const&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10ACAA70
	template DelegateMetaProperty<mgraph::NodeColour const&>::DelegateMetaProperty(void*, MetaProperty<mgraph::NodeColour const&>*);
	// FUNCTION: ENGINE 0x10ACAAA0
	template void DelegateMetaProperty<mgraph::NodeColour const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10ACAAB0
	template void DelegateMetaProperty<mgraph::NodeColour const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ACAAD0
	template DelegateMetaProperty<mgraph::NodeColour const&>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x10ACAAE0
	template mgraph::NodeColour DelegateMetaProperty<mgraph::NodeColour const&>::Get();
	// FUNCTION: ENGINE 0x10ACAB00
	template void DelegateMetaProperty<mgraph::NodeColour const&>::Set(mgraph::NodeColour);
	// FUNCTION: ENGINE 0x10ACAB20
	template DelegateMetaProperty<int>::DelegateMetaProperty(void*, MetaProperty<int>*);
	// FUNCTION: ENGINE 0x10ACAB50
	template void DelegateMetaProperty<int>::SetObject(void*);
	// FUNCTION: ENGINE 0x10ACAB60
	template void DelegateMetaProperty<int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ACAB80
	template DelegateMetaProperty<int>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x10ACAB90
	template int DelegateMetaProperty<int>::Get();
	// FUNCTION: ENGINE 0x10ACABB0
	template void DelegateMetaProperty<int>::Set(int);
	// FUNCTION: ENGINE 0x10ACAF00
	template void MetaMethod0Const<mgraph::Node,mgraph::Node,mgraph::NodeColour const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ACAFB0
	template mgraph::NodeColour* om::ReadArgument<class mgraph::NodeColour>(BinaryStream*, GarbageList*);
	// FUNCTION: ENGINE 0x10ACB030
	template DelegatePropertyBase* MetaProperty<mgraph::NodeColour const&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x10ACB080
	template DelegatePropertyBase* MetaProperty<int>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x10ACB3D0
	template void MetaMethod1<mgraph::NodeColour,mgraph::NodeColour,void,unsigned int const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ACB4A0
	template void MetaMethod1<mgraph::Node,mgraph::Node,void,mgraph::NodeColour const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ACB570
	template void MetaMethod1<mgraph::Node,mgraph::Node,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ACB640
	template void MetaMethod0Const<mgraph::Node,mgraph::Node,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ACC110
	template char const* MetaMethod1<mgraph::LinkedGraph,mgraph::LinkedGraph,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ACC120
	template char const* MetaMethod0Const<mgraph::LinkedGraph,mgraph::LinkedGraph,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ACC290
	template void* MetaMethod1<mgraph::LinkedGraph,mgraph::LinkedGraph,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ACC2B0
	template MetaMethod1<mgraph::LinkedGraph,mgraph::LinkedGraph,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::LinkedGraph,mgraph::LinkedGraph,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10ACC2E0
	template void MetaMethod1<mgraph::LinkedGraph,mgraph::LinkedGraph,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ACC300
	template MetaMethod1<mgraph::LinkedGraph,mgraph::LinkedGraph,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10ACC310
	template void MetaMethod1<mgraph::LinkedGraph,mgraph::LinkedGraph,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ACC330
	template void* MetaMethod0Const<mgraph::LinkedGraph,mgraph::LinkedGraph,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ACC350
	template MetaMethod0Const<mgraph::LinkedGraph,mgraph::LinkedGraph,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::LinkedGraph,mgraph::LinkedGraph,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10ACC380
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::LinkedGraph,mgraph::LinkedGraph,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10ACC390
	template MetaMethod0Const<mgraph::LinkedGraph,mgraph::LinkedGraph,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10ACC3A0
	template void MetaMethod0Const<mgraph::LinkedGraph,mgraph::LinkedGraph,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ACC630
	template MetaMethod1<mgraph::LinkedGraph,mgraph::LinkedGraph,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::LinkedGraph,mgraph::LinkedGraph,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::LinkedGraph,mgraph::LinkedGraph,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10ACC670
	template MetaMethod0Const<mgraph::LinkedGraph,mgraph::LinkedGraph,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::LinkedGraph,mgraph::LinkedGraph,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::LinkedGraph,mgraph::LinkedGraph,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10ACC940
	template void MetaMethod1<mgraph::LinkedGraph,mgraph::LinkedGraph,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ACCA10
	template void MetaMethod0Const<mgraph::LinkedGraph,mgraph::LinkedGraph,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ACD1D0
	template char const* MetaMethod1<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ACD1E0
	template char const* MetaMethod0Const<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ACD2D0
	template void* MetaMethod1<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ACD2F0
	template MetaMethod1<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10ACD320
	template void MetaMethod1<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ACD340
	template MetaMethod1<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10ACD350
	template void MetaMethod1<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ACD370
	template void* MetaMethod0Const<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ACD390
	template MetaMethod0Const<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10ACD3C0
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10ACD3D0
	template MetaMethod0Const<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10ACD3E0
	template void MetaMethod0Const<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ACD5B0
	template MetaMethod1<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10ACD5F0
	template MetaMethod0Const<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10ACD9C0
	template void MetaMethod1<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,void,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ACDA90
	template void MetaMethod0Const<mgraph::EmbeddedGraph,mgraph::EmbeddedGraph,Name<CaseSensitive64BitKey> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ADA1C0
	template type_info const* MetaProperty<Vector>::GetValueType();
	// FUNCTION: ENGINE 0x10ADA200
	template MetaMethod1Base<void,Vector>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ADEA50
	template char const* MetaMethod1<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,void,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADEA60
	template MetaMethod1<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,void,unsigned int>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADEA90
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,void,unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x10ADEAB0
	template MetaMethod1<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,void,unsigned int>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADEAE0
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,void,unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x10ADEB00
	template MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,void,unsigned int>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADEB30
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,void,unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x10ADEB50
	template MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,void,unsigned int>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADEB80
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,void,unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x10ADEBA0
	template MetaMethod1<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,void,unsigned int>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADEBD0
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,void,unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x10ADEBF0
	template MetaMethod1<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,void,unsigned int>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADEC20
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,void,unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x10ADEC40
	template MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,void,unsigned int>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADEC70
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,void,unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x10ADEC90
	template MetaMethod1<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,void,unsigned int>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADECC0
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,void,unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x10ADECE0
	template MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,void,unsigned int>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADED10
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,void,unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x10ADF3E0
	template type_info const* MetaProperty<bool const&>::GetValueType();
	// FUNCTION: ENGINE 0x10ADF430
	template type_info const* MetaProperty<DynamicArray<bool,unsigned short> const&>::GetValueType();
	// FUNCTION: ENGINE 0x10ADF440
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,unsigned int>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADF470
	template unsigned int MetaMethod0Const<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x10ADF480
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ADF520
	template MetaProperty<DynamicArray<float,unsigned short> const&>::MetaProperty(MetaTypeBase*, MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,DynamicArray<float,unsigned short> const&>*, MetaMethod0Base<DynamicArray<float,unsigned short> const&>*, unsigned int);
	// FUNCTION: ENGINE 0x10ADF560
	template type_info const* MetaProperty<DynamicArray<float,unsigned short> const&>::GetValueType();
	// FUNCTION: ENGINE 0x10ADF570
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,unsigned int>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADF5A0
	template unsigned int MetaMethod0Const<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x10ADF5B0
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ADF650
	template MetaProperty<DynamicArray<unsigned int,unsigned short> const&>::MetaProperty(MetaTypeBase*, MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,DynamicArray<unsigned int,unsigned short> const&>*, MetaMethod0Base<DynamicArray<unsigned int,unsigned short> const&>*, unsigned int);
	// FUNCTION: ENGINE 0x10ADF690
	template type_info const* MetaProperty<DynamicArray<unsigned int,unsigned short> const&>::GetValueType();
	// FUNCTION: ENGINE 0x10ADF6A0
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,unsigned int>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADF6D0
	template unsigned int MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x10ADF6E0
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ADF7C0
	template type_info const* MetaProperty<unsigned __int64 const&>::GetValueType();
	// FUNCTION: ENGINE 0x10ADF810
	template type_info const* MetaProperty<DynamicArray<unsigned __int64,unsigned short> const&>::GetValueType();
	// FUNCTION: ENGINE 0x10ADF820
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,unsigned int>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADF850
	template unsigned int MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x10ADF860
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ADF900
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,unsigned int>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADF930
	template unsigned int MetaMethod0Const<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x10ADF940
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ADFA20
	template type_info const* MetaProperty<Vector const&>::GetValueType();
	// FUNCTION: ENGINE 0x10ADFA70
	template type_info const* MetaProperty<DynamicArray<Vector,unsigned short> const&>::GetValueType();
	// FUNCTION: ENGINE 0x10ADFA80
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,unsigned int>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADFAB0
	template unsigned int MetaMethod0Const<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x10ADFAC0
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ADFBA0
	template type_info const* MetaProperty<DynamicArray<mgraph::TriggerData,unsigned short> const&>::GetValueType();
	// FUNCTION: ENGINE 0x10ADFBB0
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,unsigned int>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADFBE0
	template unsigned int MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x10ADFBF0
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ADFCD0
	template type_info const* MetaProperty<Complex const&>::GetValueType();
	// FUNCTION: ENGINE 0x10ADFCE0
	template MetaProperty<DynamicArray<Complex,unsigned short> const&>::MetaProperty(MetaTypeBase*, MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,DynamicArray<Complex,unsigned short> const&>*, MetaMethod0Base<DynamicArray<Complex,unsigned short> const&>*, unsigned int);
	// FUNCTION: ENGINE 0x10ADFD20
	template type_info const* MetaProperty<DynamicArray<Complex,unsigned short> const&>::GetValueType();
	// FUNCTION: ENGINE 0x10ADFD30
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,unsigned int>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADFD60
	template unsigned int MetaMethod0Const<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x10ADFD70
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ADFE50
	template type_info const* MetaProperty<mgraph::EnvelopeData const&>::GetValueType();
	// FUNCTION: ENGINE 0x10ADFE60
	template MetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::MetaProperty(MetaTypeBase*, MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>*, MetaMethod0Base<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>*, unsigned int);
	// FUNCTION: ENGINE 0x10ADFEA0
	template type_info const* MetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::GetValueType();
	// FUNCTION: ENGINE 0x10ADFEB0
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,unsigned int>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10ADFEE0
	template unsigned int MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x10ADFEF0
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10AD5260
	template type_info const* MetaSimpleType<DynamicArray<bool,unsigned short> >::GetType();
	// FUNCTION: ENGINE 0x10AD5270
	template MetaSimpleType<mgraph::Packet<DynamicArray<bool,unsigned short> > >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD5290
	template type_info const* MetaSimpleType<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetType();
	// FUNCTION: ENGINE 0x10AD52A0
	template MetaSimpleType<mgraph::Packet<bool> >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD52D0
	template type_info const* MetaSimpleType<mgraph::Packet<bool> >::GetType();
	// FUNCTION: ENGINE 0x10AD5340
	template type_info const* MetaSimpleType<DynamicArray<float,unsigned short> >::GetType();
	// FUNCTION: ENGINE 0x10AD5350
	template MetaSimpleType<mgraph::Packet<DynamicArray<float,unsigned short> > >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD5370
	template type_info const* MetaSimpleType<mgraph::Packet<DynamicArray<float,unsigned short> > >::GetType();
	// FUNCTION: ENGINE 0x10AD5380
	template MetaSimpleType<mgraph::Packet<float> >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD53A0
	template type_info const* MetaSimpleType<mgraph::Packet<float> >::GetType();
	// FUNCTION: ENGINE 0x10AD5410
	template type_info const* MetaSimpleType<DynamicArray<unsigned int,unsigned short> >::GetType();
	// FUNCTION: ENGINE 0x10AD5420
	template MetaSimpleType<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD5440
	template type_info const* MetaSimpleType<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetType();
	// FUNCTION: ENGINE 0x10AD5450
	template MetaSimpleType<mgraph::Packet<unsigned int> >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD5470
	template type_info const* MetaSimpleType<mgraph::Packet<unsigned int> >::GetType();
	// FUNCTION: ENGINE 0x10AD54E0
	template type_info const* MetaSimpleType<DynamicArray<unsigned __int64,unsigned short> >::GetType();
	// FUNCTION: ENGINE 0x10AD54F0
	template MetaSimpleType<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD5510
	template type_info const* MetaSimpleType<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetType();
	// FUNCTION: ENGINE 0x10AD5520
	template MetaSimpleType<mgraph::Packet<unsigned __int64> >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD5540
	template type_info const* MetaSimpleType<mgraph::Packet<unsigned __int64> >::GetType();
	// FUNCTION: ENGINE 0x10AD55B0
	template type_info const* MetaSimpleType<DynamicArray<String,unsigned short> >::GetType();
	// FUNCTION: ENGINE 0x10AD55C0
	template MetaSimpleType<mgraph::Packet<DynamicArray<String,unsigned short> > >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD55E0
	template type_info const* MetaSimpleType<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetType();
	// FUNCTION: ENGINE 0x10AD55F0
	template MetaSimpleType<mgraph::Packet<String> >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD5610
	template type_info const* MetaSimpleType<mgraph::Packet<String> >::GetType();
	// FUNCTION: ENGINE 0x10AD5680
	template type_info const* MetaSimpleType<DynamicArray<Vector,unsigned short> >::GetType();
	// FUNCTION: ENGINE 0x10AD5690
	template MetaSimpleType<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD56B0
	template type_info const* MetaSimpleType<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetType();
	// FUNCTION: ENGINE 0x10AD56C0
	template MetaSimpleType<mgraph::Packet<Vector> >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD56F0
	template type_info const* MetaSimpleType<mgraph::Packet<Vector> >::GetType();
	// FUNCTION: ENGINE 0x10AD5760
	template type_info const* MetaSimpleType<DynamicArray<mgraph::TriggerData,unsigned short> >::GetType();
	// FUNCTION: ENGINE 0x10AD5770
	template MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD5790
	template type_info const* MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetType();
	// FUNCTION: ENGINE 0x10AD57A0
	template MetaSimpleType<mgraph::Packet<mgraph::TriggerData> >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD57D0
	template type_info const* MetaSimpleType<mgraph::Packet<mgraph::TriggerData> >::GetType();
	// FUNCTION: ENGINE 0x10AD5850
	template type_info const* MetaSimpleType<DynamicArray<Complex,unsigned short> >::GetType();
	// FUNCTION: ENGINE 0x10AD5860
	template MetaSimpleType<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD5880
	template type_info const* MetaSimpleType<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetType();
	// FUNCTION: ENGINE 0x10AD5890
	template MetaSimpleType<mgraph::Packet<Complex> >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD58B0
	template type_info const* MetaSimpleType<mgraph::Packet<Complex> >::GetType();
	// FUNCTION: ENGINE 0x10AD5950
	template type_info const* MetaSimpleType<DynamicArray<mgraph::EnvelopeData,unsigned short> >::GetType();
	// FUNCTION: ENGINE 0x10AD5960
	template MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD5980
	template type_info const* MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::GetType();
	// FUNCTION: ENGINE 0x10AD5990
	template MetaSimpleType<mgraph::Packet<mgraph::EnvelopeData> >::MetaSimpleType(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AD59B0
	template type_info const* MetaSimpleType<mgraph::Packet<mgraph::EnvelopeData> >::GetType();
}
