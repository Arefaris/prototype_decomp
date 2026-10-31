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
	// FUNCTION: ENGINE 0x10ADA1C0
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<bool> > >::AllocationTag();
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
}
