// The reflection of the mgraph library (0x10AC0000 - 0x10AE0000): the template instances of the om library for the
// node types, their pins and their properties, in the order the compiler emitted them (a guess: one translation unit).
#include "code/audio/drivers.h"
#include "code/mgraph/nodes.h"
#include "code/mgraph/listnodes.h"
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

	// Left to the engine: the text and binary slots of the colour property (the engine merges the paths of the cached type found
	// and not found)
	template<> bool MetaProperty<mgraph::NodeColour const&>::SetText(TextValue const*, void*);
	template<> bool MetaProperty<mgraph::NodeColour const&>::SetBinary(BinaryStream*, void*);

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
	// FUNCTION: ENGINE 0x10AC8C10
	template MetaProperty<mgraph::NodeColour const&>::MetaProperty(MetaTypeBase*, MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,mgraph::NodeColour const&>*, MetaMethod0Base<mgraph::NodeColour const&>*, unsigned int);
	// FUNCTION: ENGINE 0x10AC8C70
	template MetaProperty<int>::MetaProperty(MetaTypeBase*, MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,int>*, MetaMethod0Base<int>*, unsigned int);
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
	// FUNCTION: ENGINE 0x10AC9360
	template MetaMethod1<mgraph::Node,mgraph::Node,void,int>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Node,mgraph::Node,void,int>::Function);
	// FUNCTION: ENGINE 0x10AC9880
	template MetaMethod0Const<mgraph::Node,mgraph::Node,int>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Node,mgraph::Node,int>::Function);
	// FUNCTION: ENGINE 0x10AC9B80
	template bool MetaProperty<int>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10AC9C10
	template void MetaProperty<int>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10AC9C80
	template bool MetaProperty<int>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10AC9CC0
	template bool MetaProperty<int>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10ACA0F0
	template void MetaClass<mgraph::NodeColour>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ACA1B0
	template void MetaClass<mgraph::Node>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10ACA3E0
	template void MetaProperty<mgraph::NodeColour const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,mgraph::NodeColour const&>*, MetaMethod0Base<mgraph::NodeColour const&>*, unsigned int);
	// FUNCTION: ENGINE 0x10ACA520
	template MetaMethod1<mgraph::Node,mgraph::Node,void,int>* MetaMethod1<mgraph::Node,mgraph::Node,void,int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Node,mgraph::Node,void,int>::Function);
	// FUNCTION: ENGINE 0x10ACA560
	template MetaMethod0Const<mgraph::Node,mgraph::Node,int>* MetaMethod0Const<mgraph::Node,mgraph::Node,int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Node,mgraph::Node,int>::Function);
	// FUNCTION: ENGINE 0x10ACA5A0
	template void MetaProperty<int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,int>*, MetaMethod0Base<int>*, unsigned int);
	// FUNCTION: ENGINE 0x10ACA5F0
	template void MetaMethod0Const<mgraph::Node,mgraph::Node,int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10ACA870
	// NONMATCHING: the engine merges the paths of the cached type found and not found (32.6 %)
#ifdef NONMATCHING
	template bool MetaProperty<mgraph::NodeColour const&>::SetText(TextValue const*, void*);
#endif
	// FUNCTION: ENGINE 0x10ACA980
	// NONMATCHING: the engine merges the paths of the cached type found and not found (30.6 %)
#ifdef NONMATCHING
	template bool MetaProperty<mgraph::NodeColour const&>::SetBinary(BinaryStream*, void*);
#endif
	// FUNCTION: ENGINE 0x10ACB2F0
	template void MetaMethod1<mgraph::Node,mgraph::Node,void,int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
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
	// FUNCTION: ENGINE 0x10AC3260
	template MetaMethod1Base<void,audio::Focus>* MetaProperty<audio::Focus>::GetSetter();
	// FUNCTION: ENGINE 0x10AC93B0
	template MetaMethod1<mgraph::Node,mgraph::Node,void,int>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AC9640
	template MetaMethod1<mgraph::Node,mgraph::Node,void,mgraph::NodeColour const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AC96E0
	template MetaMethod0Const<mgraph::Node,mgraph::Node,mgraph::NodeColour const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AC97A0
	template MetaMethod1<mgraph::Node,mgraph::Node,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AC9830
	template MetaMethod0Const<mgraph::Node,mgraph::Node,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AC98C0
	template MetaMethod0Const<mgraph::Node,mgraph::Node,int>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AD5120
	template char const* MetaClass<mgraph::PropertyNodeBase>::AllocationTag();
	// FUNCTION: ENGINE 0x10AD5130
	template char const* MetaClass<mgraph::CommutativeMath<mgraph::VectorAdd> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD5140
	template char const* MetaClass<mgraph::CommutativeMath<mgraph::FloatAdd> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD5150
	template char const* MetaClass<mgraph::CommutativeMath<mgraph::FloatMultiply> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD5160
	template char const* MetaClass<mgraph::CommutativeMath<mgraph::BoolOr> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD5170
	template char const* MetaClass<mgraph::CommutativeMath<mgraph::BoolAnd> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD5180
	template char const* MetaClass<mgraph::CommutativeMath<mgraph::TriggerAnd> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD5190
	template char const* MetaClass<mgraph::CommutativeMath<mgraph::TriggerOr> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD51A0
	template char const* MetaClass<mgraph::NonCommutativeMath<mgraph::FloatSub> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD51B0
	template char const* MetaClass<mgraph::Operator2<mgraph::GreaterThan<float> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD51C0
	template char const* MetaClass<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD51D0
	template char const* MetaClass<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD51E0
	template char const* MetaClass<mgraph::Operator2<mgraph::LessThan<float> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD51F0
	template char const* MetaClass<mgraph::Operator2<mgraph::Equal<float> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD5200
	template char const* MetaClass<mgraph::Operator2<mgraph::NotEqual<float> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD5210
	template char const* MetaClass<mgraph::UnaryMath<mgraph::BoolNot> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD5220
	template char const* MetaSimpleType<DynamicArray<bool,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD7AA0
	template void DynamicArray<bool,unsigned short>::DestroyElements(bool*, unsigned short);
	// FUNCTION: ENGINE 0x10AD9080
	template char const* DynamicArray<bool,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9090
	template char const* DynamicArray<unsigned __int64,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10AD90A0
	template char const* DynamicArray<Vector,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10AD90B0
	template char const* DynamicArray<mgraph::TriggerData,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10AD90C0
	template char const* DynamicArray<Complex,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10AD90D0
	template char const* DynamicArray<mgraph::EnvelopeData,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9DE0
	template char const* MetaClass<mgraph::Rand<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9DF0
	template char const* MetaClass<mgraph::Rand<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9E00
	template char const* MetaClass<mgraph::Rand<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9E10
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<bool> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9E20
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9E30
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<float> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9E40
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9E50
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<unsigned int> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9E60
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9E70
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9E80
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9E90
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<String> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9EA0
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9EB0
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<Vector> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9EC0
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9ED0
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9EE0
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9EF0
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<Complex> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9F00
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9F10
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9F20
	template char const* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9F30
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<bool> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9F40
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9F50
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<float> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9F60
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9F70
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<unsigned int> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9F80
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9F90
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9FA0
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9FB0
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<String> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9FC0
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9FD0
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<Vector> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9FE0
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD9FF0
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADA000
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADA010
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<Complex> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADA020
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADA030
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADA040
	template char const* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADA1F0
	template MetaProperty<Vector>::~MetaProperty();
	// FUNCTION: ENGINE 0x10ADD550
	template void DynamicArray<Complex,unsigned short>::DestroyElements(Complex*, unsigned short);
	// FUNCTION: ENGINE 0x10ADD5B0
	template Complex* DynamicArray<Complex,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10ADD5D0
	template void DynamicArray<VectorT<float,2>,unsigned short>::ReleaseElements(VectorT<float,2>*, unsigned short);
	// FUNCTION: ENGINE 0x10ADD660
	template mgraph::EnvelopeData const& DynamicArray<mgraph::EnvelopeData,unsigned short>::operator[](unsigned short) const;
	// FUNCTION: ENGINE 0x10ADD670
	template mgraph::EnvelopeData* DynamicArray<mgraph::EnvelopeData,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10ADD6D0
	template char const* MetaMethod1<mgraph::Rand<Vector>,mgraph::Rand<Vector>,void,Vector>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD6E0
	template char const* MetaMethod1<mgraph::Rand<float>,mgraph::Rand<float>,void,float>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD6F0
	template char const* MetaMethod1<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,void,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD700
	template char const* MetaMethod0Const<mgraph::Rand<Vector>,mgraph::Rand<Vector>,Vector>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD710
	template char const* MetaProperty<Vector>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD7B0
	template char const* MetaMethod0Const<mgraph::Rand<float>,mgraph::Rand<float>,float>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD7C0
	template char const* MetaMethod0Const<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD7D0
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD7E0
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD7F0
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD800
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD810
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD820
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD830
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD840
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD850
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD860
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD870
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD880
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD890
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD8A0
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD8B0
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD8C0
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD8D0
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD8E0
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD8F0
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD900
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD910
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD920
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD930
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD940
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD950
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD960
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD970
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD980
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD990
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD9A0
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD9B0
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD9C0
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD9D0
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD9E0
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADD9F0
	template char const* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADDA00
	template char const* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE560
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<bool> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE570
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE580
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<float> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE590
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE5A0
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE5B0
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE5C0
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE5D0
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE5E0
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<String> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE5F0
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE600
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<Vector> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE610
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE620
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE630
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<Complex> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE640
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE650
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE660
	template char const* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE670
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<bool> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE680
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<bool> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE690
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE6A0
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE6B0
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<float> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE6C0
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<float> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE6D0
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE6E0
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE6F0
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<unsigned int> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE700
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<unsigned int> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE710
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE720
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE730
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE740
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE750
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE760
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE770
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<String> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE780
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<String> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE790
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE7A0
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE7B0
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<Vector> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE7C0
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<Vector> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE7D0
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE7E0
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE7F0
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE800
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE810
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE820
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE830
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<Complex> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE840
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<Complex> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE850
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE860
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE870
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE880
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE890
	template char const* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE8A0
	template char const* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE8B0
	template char const* MetaClass<mgraph::Switch<mgraph::Packet<bool> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE8C0
	template char const* MetaClass<mgraph::Switch<mgraph::Packet<float> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE8D0
	template char const* MetaClass<mgraph::Switch<mgraph::Packet<unsigned int> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE8E0
	template char const* MetaClass<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE8F0
	template char const* MetaClass<mgraph::Switch<mgraph::Packet<String> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE900
	template char const* MetaClass<mgraph::Switch<mgraph::Packet<Vector> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE910
	template char const* MetaClass<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE920
	template char const* MetaClass<mgraph::Switch<mgraph::Packet<Complex> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE930
	template char const* MetaClass<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE940
	template char const* MetaClass<mgraph::ListCount<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE950
	template char const* MetaClass<mgraph::ListEntry<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE960
	template char const* MetaClass<mgraph::ListCount<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE970
	template char const* MetaClass<mgraph::ListEntry<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE980
	template char const* MetaClass<mgraph::ListCount<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE990
	template char const* MetaClass<mgraph::ListEntry<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE9A0
	template char const* MetaClass<mgraph::ListCount<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE9B0
	template char const* MetaClass<mgraph::ListEntry<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE9C0
	template char const* MetaClass<mgraph::ListCount<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE9D0
	template char const* MetaClass<mgraph::ListEntry<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE9E0
	template char const* MetaClass<mgraph::ListCount<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADE9F0
	template char const* MetaClass<mgraph::ListEntry<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADEA00
	template char const* MetaClass<mgraph::ListCount<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADEA10
	template char const* MetaClass<mgraph::ListEntry<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADEA20
	template char const* MetaClass<mgraph::ListCount<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADEA30
	template char const* MetaClass<mgraph::ListEntry<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADEA40
	template char const* MetaClass<mgraph::ListCount<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10ADEA50
	template char const* MetaClass<mgraph::ListEntry<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0310
	template MetaMethod1<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,void,unsigned int>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AE0320
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,void,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0340
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,void,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0360
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,void,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0380
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,void,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE03A0
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,void,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE03C0
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,void,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE03E0
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,void,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0400
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,void,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0420
	template void MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,void,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0440
	template MetaMethod1Base<void,bool const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE04A0
	template MetaMethod1Base<void,DynamicArray<bool,unsigned short> const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE0500
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0520
	template MetaMethod1Base<void,DynamicArray<float,unsigned short> const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE0580
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE05A0
	template MetaMethod1Base<void,DynamicArray<unsigned int,unsigned short> const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE0600
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0620
	template MetaMethod1Base<void,unsigned __int64 const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE0680
	template MetaMethod1Base<void,DynamicArray<unsigned __int64,unsigned short> const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE06E0
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0700
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0720
	template MetaMethod1Base<void,Vector const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE0780
	template MetaMethod1Base<void,DynamicArray<Vector,unsigned short> const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE07E0
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0800
	template MetaMethod1Base<void,DynamicArray<mgraph::TriggerData,unsigned short> const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE0860
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0880
	template MetaMethod1Base<void,Complex const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE08E0
	template MetaMethod1Base<void,DynamicArray<Complex,unsigned short> const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE0940
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0960
	template MetaMethod1Base<void,mgraph::EnvelopeData const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE09C0
	template MetaMethod1Base<void,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE0A20
	template void MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE0D80
	template char const* DelegateMetaProperty<Vector>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0D90
	template char const* MetaMethod1<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,void,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0DA0
	template char const* MetaMethod1<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,void,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0DB0
	template char const* MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,void,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0DC0
	template char const* MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,void,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0DD0
	template char const* MetaMethod1<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,void,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0DE0
	template char const* MetaMethod1<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,void,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0DF0
	template char const* MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,void,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0E00
	template char const* MetaMethod1<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,void,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0E10
	template char const* MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,void,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0E20
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,void,bool const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0E30
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,bool const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0E40
	template char const* MetaProperty<bool const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0E50
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,DynamicArray<bool,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0E60
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,DynamicArray<bool,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0E70
	template char const* MetaProperty<DynamicArray<bool,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0E80
	template char const* MetaMethod0Const<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0E90
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,void,float const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0EA0
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,float const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0EB0
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,DynamicArray<float,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0EC0
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,DynamicArray<float,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0ED0
	template char const* MetaProperty<DynamicArray<float,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0EE0
	template char const* MetaMethod0Const<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0EF0
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,void,unsigned int const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0F00
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,unsigned int const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0F10
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,DynamicArray<unsigned int,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0F20
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,DynamicArray<unsigned int,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0F30
	template char const* MetaProperty<DynamicArray<unsigned int,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0F40
	template char const* MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0F50
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,void,unsigned __int64 const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0F60
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,unsigned __int64 const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0F70
	template char const* MetaProperty<unsigned __int64 const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0F80
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,DynamicArray<unsigned __int64,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0F90
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,DynamicArray<unsigned __int64,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0FA0
	template char const* MetaProperty<DynamicArray<unsigned __int64,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0FB0
	template char const* MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0FC0
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,void,String const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0FD0
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,String const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0FE0
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,DynamicArray<String,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE0FF0
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,DynamicArray<String,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1000
	template char const* MetaMethod0Const<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1010
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,void,Vector const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1020
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,Vector const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1030
	template char const* MetaProperty<Vector const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1040
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,DynamicArray<Vector,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1050
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,DynamicArray<Vector,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1060
	template char const* MetaProperty<DynamicArray<Vector,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1070
	template char const* MetaMethod0Const<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1080
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,DynamicArray<mgraph::TriggerData,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1090
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,DynamicArray<mgraph::TriggerData,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE10A0
	template char const* MetaProperty<DynamicArray<mgraph::TriggerData,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE10B0
	template char const* MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE10C0
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,void,Complex const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE10D0
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,Complex const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE10E0
	template char const* MetaProperty<Complex const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE10F0
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,DynamicArray<Complex,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1100
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,DynamicArray<Complex,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1110
	template char const* MetaProperty<DynamicArray<Complex,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1120
	template char const* MetaMethod0Const<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1130
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,void,mgraph::EnvelopeData const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1140
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::EnvelopeData const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1150
	template char const* MetaProperty<mgraph::EnvelopeData const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1160
	template char const* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1170
	template char const* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1180
	template char const* MetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1190
	template char const* MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE14F0
	template char const* DelegateMetaProperty<bool const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1500
	template char const* DelegateMetaProperty<DynamicArray<bool,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1510
	template char const* DelegateMetaProperty<DynamicArray<float,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1520
	template char const* DelegateMetaProperty<DynamicArray<unsigned int,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1530
	template char const* DelegateMetaProperty<unsigned __int64 const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1540
	template char const* DelegateMetaProperty<DynamicArray<unsigned __int64,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1550
	template char const* DelegateMetaProperty<Vector const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1560
	template char const* DelegateMetaProperty<DynamicArray<Vector,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1570
	template char const* DelegateMetaProperty<DynamicArray<mgraph::TriggerData,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1580
	template char const* DelegateMetaProperty<Complex const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1590
	template char const* DelegateMetaProperty<DynamicArray<Complex,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE15A0
	template char const* DelegateMetaProperty<mgraph::EnvelopeData const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE15B0
	template char const* DelegateMetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AE1880
	template int MetaClass<mgraph::PropertyNodeBase>::Slot5();
	// FUNCTION: ENGINE 0x10AE1890
	template void MetaClass<mgraph::PropertyNodeBase>::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE18C0
	template int MetaClass<mgraph::Rand<Vector> >::Slot5();
	// FUNCTION: ENGINE 0x10AE18D0
	template void MetaClass<mgraph::Rand<Vector> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1AE0
	template int MetaClass<mgraph::CommutativeMath<mgraph::VectorAdd> >::Slot5();
	// FUNCTION: ENGINE 0x10AE1AF0
	template void MetaClass<mgraph::CommutativeMath<mgraph::VectorAdd> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1B00
	template int MetaClass<mgraph::CommutativeMath<mgraph::FloatAdd> >::Slot5();
	// FUNCTION: ENGINE 0x10AE1B10
	template void MetaClass<mgraph::CommutativeMath<mgraph::FloatAdd> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1B20
	template int MetaClass<mgraph::CommutativeMath<mgraph::FloatMultiply> >::Slot5();
	// FUNCTION: ENGINE 0x10AE1B30
	template void MetaClass<mgraph::CommutativeMath<mgraph::FloatMultiply> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1B40
	template int MetaClass<mgraph::CommutativeMath<mgraph::BoolOr> >::Slot5();
	// FUNCTION: ENGINE 0x10AE1B50
	template void MetaClass<mgraph::CommutativeMath<mgraph::BoolOr> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1B60
	template int MetaClass<mgraph::CommutativeMath<mgraph::BoolAnd> >::Slot5();
	// FUNCTION: ENGINE 0x10AE1B70
	template void MetaClass<mgraph::CommutativeMath<mgraph::BoolAnd> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1B80
	template int MetaClass<mgraph::CommutativeMath<mgraph::TriggerAnd> >::Slot5();
	// FUNCTION: ENGINE 0x10AE1B90
	template void MetaClass<mgraph::CommutativeMath<mgraph::TriggerAnd> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1BA0
	template int MetaClass<mgraph::CommutativeMath<mgraph::TriggerOr> >::Slot5();
	// FUNCTION: ENGINE 0x10AE1BB0
	template void MetaClass<mgraph::CommutativeMath<mgraph::TriggerOr> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1BC0
	template int MetaClass<mgraph::NonCommutativeMath<mgraph::FloatSub> >::Slot5();
	// FUNCTION: ENGINE 0x10AE1BD0
	template void MetaClass<mgraph::NonCommutativeMath<mgraph::FloatSub> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1BE0
	template int MetaClass<mgraph::Operator2<mgraph::GreaterThan<float> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE1BF0
	template void MetaClass<mgraph::Operator2<mgraph::GreaterThan<float> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1C00
	template int MetaClass<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE1C10
	template void MetaClass<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1C20
	template int MetaClass<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE1C30
	template void MetaClass<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1C40
	template int MetaClass<mgraph::Operator2<mgraph::LessThan<float> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE1C50
	template void MetaClass<mgraph::Operator2<mgraph::LessThan<float> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1C60
	template int MetaClass<mgraph::Operator2<mgraph::Equal<float> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE1C70
	template void MetaClass<mgraph::Operator2<mgraph::Equal<float> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1C80
	template int MetaClass<mgraph::Operator2<mgraph::NotEqual<float> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE1C90
	template void MetaClass<mgraph::Operator2<mgraph::NotEqual<float> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1CA0
	template int MetaClass<mgraph::UnaryMath<mgraph::BoolNot> >::Slot5();
	// FUNCTION: ENGINE 0x10AE1CB0
	template void MetaClass<mgraph::UnaryMath<mgraph::BoolNot> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE1F00
	template void* MetaClass<mgraph::PropertyNodeBase>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1F50
	template void* MetaClass<mgraph::CommutativeMath<mgraph::VectorAdd> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1F70
	template void* MetaClass<mgraph::CommutativeMath<mgraph::FloatAdd> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1F90
	template void* MetaClass<mgraph::CommutativeMath<mgraph::FloatMultiply> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1FB0
	template void* MetaClass<mgraph::CommutativeMath<mgraph::BoolOr> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1FD0
	template void* MetaClass<mgraph::CommutativeMath<mgraph::BoolAnd> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1FF0
	template void* MetaClass<mgraph::CommutativeMath<mgraph::TriggerAnd> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE2010
	template void* MetaClass<mgraph::CommutativeMath<mgraph::TriggerOr> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE2030
	template void* MetaClass<mgraph::NonCommutativeMath<mgraph::FloatSub> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE2050
	template void* MetaClass<mgraph::Operator2<mgraph::GreaterThan<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE2070
	template void* MetaClass<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE2090
	template void* MetaClass<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE20B0
	template void* MetaClass<mgraph::Operator2<mgraph::LessThan<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE20D0
	template void* MetaClass<mgraph::Operator2<mgraph::Equal<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE20F0
	template void* MetaClass<mgraph::Operator2<mgraph::NotEqual<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE2110
	template void* MetaClass<mgraph::UnaryMath<mgraph::BoolNot> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE24C0
	template int MetaSimpleType<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE24D0
	template void MetaSimpleType<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE24E0
	template int MetaSimpleType<mgraph::Packet<bool> >::Slot5();
	// FUNCTION: ENGINE 0x10AE24F0
	template void MetaSimpleType<mgraph::Packet<bool> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE2560
	template int MetaSimpleType<mgraph::Packet<DynamicArray<float,unsigned short> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE2570
	template void MetaSimpleType<mgraph::Packet<DynamicArray<float,unsigned short> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE2580
	template int MetaSimpleType<mgraph::Packet<float> >::Slot5();
	// FUNCTION: ENGINE 0x10AE2590
	template void MetaSimpleType<mgraph::Packet<float> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE2600
	template int MetaSimpleType<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE2610
	template void MetaSimpleType<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE2620
	template int MetaSimpleType<mgraph::Packet<unsigned int> >::Slot5();
	// FUNCTION: ENGINE 0x10AE2630
	template void MetaSimpleType<mgraph::Packet<unsigned int> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE26A0
	template int MetaSimpleType<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE26B0
	template void MetaSimpleType<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE26C0
	template int MetaSimpleType<mgraph::Packet<unsigned __int64> >::Slot5();
	// FUNCTION: ENGINE 0x10AE26D0
	template void MetaSimpleType<mgraph::Packet<unsigned __int64> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE2740
	template int MetaSimpleType<mgraph::Packet<DynamicArray<String,unsigned short> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE2750
	template void MetaSimpleType<mgraph::Packet<DynamicArray<String,unsigned short> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE2760
	template int MetaSimpleType<mgraph::Packet<String> >::Slot5();
	// FUNCTION: ENGINE 0x10AE2770
	template void MetaSimpleType<mgraph::Packet<String> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE27E0
	template int MetaSimpleType<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE27F0
	template void MetaSimpleType<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE2800
	template int MetaSimpleType<mgraph::Packet<Vector> >::Slot5();
	// FUNCTION: ENGINE 0x10AE2810
	template void MetaSimpleType<mgraph::Packet<Vector> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE2880
	template int MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE2890
	template void MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE28A0
	template int MetaSimpleType<mgraph::Packet<mgraph::TriggerData> >::Slot5();
	// FUNCTION: ENGINE 0x10AE28B0
	template void MetaSimpleType<mgraph::Packet<mgraph::TriggerData> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE2920
	template int MetaSimpleType<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE2930
	template void MetaSimpleType<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE2940
	template int MetaSimpleType<mgraph::Packet<Complex> >::Slot5();
	// FUNCTION: ENGINE 0x10AE2950
	template void MetaSimpleType<mgraph::Packet<Complex> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE29C0
	template int MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE29D0
	template void MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE29E0
	template int MetaSimpleType<mgraph::Packet<mgraph::EnvelopeData> >::Slot5();
	// FUNCTION: ENGINE 0x10AE29F0
	template void MetaSimpleType<mgraph::Packet<mgraph::EnvelopeData> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE2A80
	template int MetaClass<mgraph::Rand<float> >::Slot5();
	// FUNCTION: ENGINE 0x10AE2A90
	template void MetaClass<mgraph::Rand<float> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE2AC0
	template int MetaClass<mgraph::Rand<unsigned int> >::Slot5();
	// FUNCTION: ENGINE 0x10AE2AD0
	template void MetaClass<mgraph::Rand<unsigned int> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4300
	template bool om::ReadBinary<class mgraph::Packet<bool> >(BinaryStream*, mgraph::Packet<bool>*);
	// FUNCTION: ENGINE 0x10AE4330
	template bool om::WriteBinary<class mgraph::Packet<bool> >(BinaryStream*, mgraph::Packet<bool> const&);
	// FUNCTION: ENGINE 0x10AE4360
	template bool om::ReadText<class mgraph::Packet<bool> >(TextValue const*, mgraph::Packet<bool>*);
	// FUNCTION: ENGINE 0x10AE4390
	template void om::WriteText<class mgraph::Packet<bool> >(TextValue*, mgraph::Packet<bool> const&);
	// FUNCTION: ENGINE 0x10AE43E0
	template int MetaClass<mgraph::Throw<mgraph::Packet<bool> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE43F0
	template void MetaClass<mgraph::Throw<mgraph::Packet<bool> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4440
	template int MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4450
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4480
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<bool> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4490
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<bool> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE44C0
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE44D0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4560
	template bool om::ReadBinary<class mgraph::Packet<float> >(BinaryStream*, mgraph::Packet<float>*);
	// FUNCTION: ENGINE 0x10AE4590
	template bool om::WriteBinary<class mgraph::Packet<float> >(BinaryStream*, mgraph::Packet<float> const&);
	// FUNCTION: ENGINE 0x10AE45C0
	template bool om::ReadText<class mgraph::Packet<float> >(TextValue const*, mgraph::Packet<float>*);
	// FUNCTION: ENGINE 0x10AE45F0
	template void om::WriteText<class mgraph::Packet<float> >(TextValue*, mgraph::Packet<float> const&);
	// FUNCTION: ENGINE 0x10AE4640
	template int MetaClass<mgraph::Throw<mgraph::Packet<float> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4650
	template void MetaClass<mgraph::Throw<mgraph::Packet<float> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4680
	template int MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4690
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE46C0
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<float> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE46D0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<float> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4700
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4710
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE47C0
	template int MetaClass<mgraph::Throw<mgraph::Packet<unsigned int> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE47D0
	template void MetaClass<mgraph::Throw<mgraph::Packet<unsigned int> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4800
	template int MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4810
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4840
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4850
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4880
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4890
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4940
	template int MetaClass<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4950
	template void MetaClass<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE49F0
	template int MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4A00
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4A30
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4A40
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4A70
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4A80
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4B30
	template int MetaClass<mgraph::Throw<mgraph::Packet<String> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4B40
	template void MetaClass<mgraph::Throw<mgraph::Packet<String> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4BE0
	template int MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4BF0
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4C20
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<String> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4C30
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<String> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4C60
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4C70
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4D00
	template bool om::ReadBinary<class mgraph::Packet<class om::Vector> >(BinaryStream*, mgraph::Packet<Vector>*);
	// FUNCTION: ENGINE 0x10AE4D30
	template bool om::WriteBinary<class mgraph::Packet<class om::Vector> >(BinaryStream*, mgraph::Packet<Vector> const&);
	// FUNCTION: ENGINE 0x10AE4D60
	template bool om::ReadText<class mgraph::Packet<class om::Vector> >(TextValue const*, mgraph::Packet<Vector>*);
	// FUNCTION: ENGINE 0x10AE4D90
	template void om::WriteText<class mgraph::Packet<class om::Vector> >(TextValue*, mgraph::Packet<Vector> const&);
	// FUNCTION: ENGINE 0x10AE4DE0
	template int MetaClass<mgraph::Throw<mgraph::Packet<Vector> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4DF0
	template void MetaClass<mgraph::Throw<mgraph::Packet<Vector> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4E40
	template int MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4E50
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4E80
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<Vector> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4E90
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<Vector> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4EC0
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE4ED0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE4F60
	template bool om::ReadBinary<class mgraph::Packet<class mgraph::TriggerData> >(BinaryStream*, mgraph::Packet<mgraph::TriggerData>*);
	// FUNCTION: ENGINE 0x10AE4F90
	template bool om::WriteBinary<class mgraph::Packet<class mgraph::TriggerData> >(BinaryStream*, mgraph::Packet<mgraph::TriggerData> const&);
	// FUNCTION: ENGINE 0x10AE4FC0
	template bool om::ReadText<class mgraph::Packet<class mgraph::TriggerData> >(TextValue const*, mgraph::Packet<mgraph::TriggerData>*);
	// FUNCTION: ENGINE 0x10AE4FF0
	template void om::WriteText<class mgraph::Packet<class mgraph::TriggerData> >(TextValue*, mgraph::Packet<mgraph::TriggerData> const&);
	// FUNCTION: ENGINE 0x10AE5040
	template int MetaClass<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE5050
	template void MetaClass<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE50A0
	template int MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE50B0
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE50E0
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE50F0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE51A0
	template int MetaClass<mgraph::Throw<mgraph::Packet<Complex> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE51B0
	template void MetaClass<mgraph::Throw<mgraph::Packet<Complex> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE52B0
	template int MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE52C0
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE52F0
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<Complex> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE5300
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<Complex> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE5330
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE5340
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE53F0
	template int MetaClass<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE5400
	template void MetaClass<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE5450
	template int MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE5460
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE5490
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE54A0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE54D0
	template int MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE54E0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE5B60
	template void* DynamicArray<float,unsigned short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE5BA0
	template void* DynamicArray<bool,unsigned short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE5BC0
	template void* DynamicArray<unsigned int,unsigned short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE5BE0
	template void* DynamicArray<unsigned __int64,unsigned short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE5C00
	template void* DynamicArray<Vector,unsigned short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE5C20
	template void* DynamicArray<mgraph::TriggerData,unsigned short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE5C40
	template void* DynamicArray<Complex,unsigned short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE5C60
	template void* DynamicArray<mgraph::EnvelopeData,unsigned short>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6200
	template int MetaClass<mgraph::Catch<mgraph::Packet<bool> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6210
	template void MetaClass<mgraph::Catch<mgraph::Packet<bool> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6240
	template int MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6250
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6260
	template int MetaClass<mgraph::Inlet<mgraph::Packet<bool> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6270
	template void MetaClass<mgraph::Inlet<mgraph::Packet<bool> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6280
	template int MetaClass<mgraph::Outlet<mgraph::Packet<bool> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6290
	template void MetaClass<mgraph::Outlet<mgraph::Packet<bool> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE62A0
	template int MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE62B0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE62C0
	template int MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE62D0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6320
	template int MetaClass<mgraph::Catch<mgraph::Packet<float> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6330
	template void MetaClass<mgraph::Catch<mgraph::Packet<float> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6360
	template int MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6370
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6380
	template int MetaClass<mgraph::Inlet<mgraph::Packet<float> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6390
	template void MetaClass<mgraph::Inlet<mgraph::Packet<float> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE63A0
	template int MetaClass<mgraph::Outlet<mgraph::Packet<float> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE63B0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<float> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE63C0
	template int MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE63D0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE63E0
	template int MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE63F0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6460
	template int MetaClass<mgraph::Catch<mgraph::Packet<unsigned int> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6470
	template void MetaClass<mgraph::Catch<mgraph::Packet<unsigned int> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE64A0
	template int MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE64B0
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE64C0
	template int MetaClass<mgraph::Inlet<mgraph::Packet<unsigned int> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE64D0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<unsigned int> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE64E0
	template int MetaClass<mgraph::Outlet<mgraph::Packet<unsigned int> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE64F0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<unsigned int> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6500
	template int MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6510
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6520
	template int MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6530
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE65C0
	template int MetaClass<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE65D0
	template void MetaClass<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6600
	template int MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6610
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6620
	template int MetaClass<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6630
	template void MetaClass<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6640
	template int MetaClass<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6650
	template void MetaClass<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6660
	template int MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6670
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6680
	template int MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6690
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6720
	template int MetaClass<mgraph::Catch<mgraph::Packet<String> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6730
	template void MetaClass<mgraph::Catch<mgraph::Packet<String> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6760
	template int MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6770
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6780
	template int MetaClass<mgraph::Inlet<mgraph::Packet<String> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6790
	template void MetaClass<mgraph::Inlet<mgraph::Packet<String> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE67A0
	template int MetaClass<mgraph::Outlet<mgraph::Packet<String> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE67B0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<String> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE67C0
	template int MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE67D0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE67E0
	template int MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE67F0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6840
	template int MetaClass<mgraph::Catch<mgraph::Packet<Vector> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6850
	template void MetaClass<mgraph::Catch<mgraph::Packet<Vector> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6880
	template int MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6890
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE68A0
	template int MetaClass<mgraph::Inlet<mgraph::Packet<Vector> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE68B0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<Vector> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE68C0
	template int MetaClass<mgraph::Outlet<mgraph::Packet<Vector> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE68D0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<Vector> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE68E0
	template int MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE68F0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6900
	template int MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6910
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6960
	template int MetaClass<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6970
	template void MetaClass<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE69A0
	template int MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE69B0
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE69C0
	template int MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE69D0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE69E0
	template int MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE69F0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6A00
	template int MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6A10
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6A20
	template int MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6A30
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6AC0
	template int MetaClass<mgraph::Catch<mgraph::Packet<Complex> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6AD0
	template void MetaClass<mgraph::Catch<mgraph::Packet<Complex> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6B00
	template int MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6B10
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6B20
	template int MetaClass<mgraph::Inlet<mgraph::Packet<Complex> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6B30
	template void MetaClass<mgraph::Inlet<mgraph::Packet<Complex> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6B40
	template int MetaClass<mgraph::Outlet<mgraph::Packet<Complex> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6B50
	template void MetaClass<mgraph::Outlet<mgraph::Packet<Complex> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6B60
	template int MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6B70
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6B80
	template int MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6B90
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6C00
	template int MetaClass<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6C10
	template void MetaClass<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6C40
	template int MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6C50
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6C60
	template int MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6C70
	template void MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6C80
	template int MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6C90
	template void MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6CA0
	template int MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6CB0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE6CC0
	template int MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Slot5();
	// FUNCTION: ENGINE 0x10AE6CD0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE71E0
	template void* MetaClass<mgraph::Rand<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7200
	template void* MetaClass<mgraph::Rand<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7220
	template void* MetaClass<mgraph::Rand<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE72D0
	template void* MetaClass<mgraph::Throw<mgraph::Packet<bool> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE72F0
	template void* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7310
	template void* MetaClass<mgraph::Throw<mgraph::Packet<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7330
	template void* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7350
	template void* MetaClass<mgraph::Throw<mgraph::Packet<unsigned int> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7370
	template void* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7390
	template void* MetaClass<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE73B0
	template void* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE73D0
	template void* MetaClass<mgraph::Throw<mgraph::Packet<String> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE73F0
	template void* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7410
	template void* MetaClass<mgraph::Throw<mgraph::Packet<Vector> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7430
	template void* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7450
	template void* MetaClass<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7470
	template void* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7490
	template void* MetaClass<mgraph::Throw<mgraph::Packet<Complex> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE74B0
	template void* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE74D0
	template void* MetaClass<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE74F0
	template void* MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7510
	template void* MetaClass<mgraph::Catch<mgraph::Packet<bool> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7530
	template void* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7550
	template void* MetaClass<mgraph::Catch<mgraph::Packet<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7570
	template void* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7590
	template void* MetaClass<mgraph::Catch<mgraph::Packet<unsigned int> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE75B0
	template void* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE75D0
	template void* MetaClass<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE75F0
	template void* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7610
	template void* MetaClass<mgraph::Catch<mgraph::Packet<String> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7630
	template void* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7650
	template void* MetaClass<mgraph::Catch<mgraph::Packet<Vector> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7670
	template void* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7690
	template void* MetaClass<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE76B0
	template void* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE76D0
	template void* MetaClass<mgraph::Catch<mgraph::Packet<Complex> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE76F0
	template void* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7710
	template void* MetaClass<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7730
	template void* MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE8330
	template unsigned __int64 const& DynamicArray<unsigned __int64,unsigned short>::operator[](unsigned short) const;
	// FUNCTION: ENGINE 0x10AE83C0
	template void DynamicArray<unsigned __int64,unsigned short>::Empty();
	// FUNCTION: ENGINE 0x10AE8990
	template DynamicArray<VectorT<float,2>,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10AE89E0
	template void DynamicArray<Complex,unsigned short>::Reserve(unsigned short);
	// FUNCTION: ENGINE 0x10AE8A20
	template Complex& DynamicArray<Complex,unsigned short>::Append();
	// FUNCTION: ENGINE 0x10AE8AA0
	template void DynamicArray<Complex,unsigned short>::Empty();
	// FUNCTION: ENGINE 0x10AE8B90
	template void DynamicArray<mgraph::EnvelopeData,unsigned short>::Reserve(unsigned short);
	// FUNCTION: ENGINE 0x10AE8C50
	template void* MetaMethod1<mgraph::Rand<Vector>,mgraph::Rand<Vector>,void,Vector>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE8CD0
	template MetaMethod1<mgraph::Rand<Vector>,mgraph::Rand<Vector>,void,Vector>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AE8CE0
	template void MetaMethod1<mgraph::Rand<Vector>,mgraph::Rand<Vector>,void,Vector>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE9030
	template void* MetaMethod1<mgraph::Rand<float>,mgraph::Rand<float>,void,float>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE9050
	template MetaMethod1<mgraph::Rand<float>,mgraph::Rand<float>,void,float>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Rand<float>,mgraph::Rand<float>,void,float>::Function);
	// FUNCTION: ENGINE 0x10AE9080
	template void MetaMethod1<mgraph::Rand<float>,mgraph::Rand<float>,void,float>::Call(void*, float);
	// FUNCTION: ENGINE 0x10AE90A0
	template MetaMethod1<mgraph::Rand<float>,mgraph::Rand<float>,void,float>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AE90B0
	template void MetaMethod1<mgraph::Rand<float>,mgraph::Rand<float>,void,float>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE90D0
	template void* MetaMethod1<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,void,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE90F0
	template MetaMethod1<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,void,unsigned int>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AE9120
	template void MetaMethod1<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,void,unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x10AE9140
	template MetaMethod1<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,void,unsigned int>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AE9150
	template void MetaMethod1<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,void,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE9830
	template void* MetaMethod0Const<mgraph::Rand<Vector>,mgraph::Rand<Vector>,Vector>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE98B0
	template MetaMethod0Const<mgraph::Rand<Vector>,mgraph::Rand<Vector>,Vector>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AE98C0
	template void MetaMethod0Const<mgraph::Rand<Vector>,mgraph::Rand<Vector>,Vector>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE98E0
	template void* MetaProperty<Vector>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE9920
	template int MetaClass<mgraph::Switch<mgraph::Packet<bool> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE9930
	template void MetaClass<mgraph::Switch<mgraph::Packet<bool> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE9960
	template int MetaClass<mgraph::Switch<mgraph::Packet<float> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE9970
	template void MetaClass<mgraph::Switch<mgraph::Packet<float> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE99A0
	template int MetaClass<mgraph::Switch<mgraph::Packet<unsigned int> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE99B0
	template void MetaClass<mgraph::Switch<mgraph::Packet<unsigned int> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE99E0
	template int MetaClass<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE99F0
	template void MetaClass<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE9A20
	template int MetaClass<mgraph::Switch<mgraph::Packet<String> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE9A30
	template void MetaClass<mgraph::Switch<mgraph::Packet<String> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE9A60
	template int MetaClass<mgraph::Switch<mgraph::Packet<Vector> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE9A70
	template void MetaClass<mgraph::Switch<mgraph::Packet<Vector> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE9AA0
	template int MetaClass<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE9AB0
	template void MetaClass<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE9AE0
	template int MetaClass<mgraph::Switch<mgraph::Packet<Complex> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE9AF0
	template void MetaClass<mgraph::Switch<mgraph::Packet<Complex> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE9B20
	template int MetaClass<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::Slot5();
	// FUNCTION: ENGINE 0x10AE9B30
	template void MetaClass<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AE9B40
	template void* MetaMethod0Const<mgraph::Rand<float>,mgraph::Rand<float>,float>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE9B60
	template MetaMethod0Const<mgraph::Rand<float>,mgraph::Rand<float>,float>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Rand<float>,mgraph::Rand<float>,float>::Function);
	// FUNCTION: ENGINE 0x10AE9B90
	template float MetaMethod0Const<mgraph::Rand<float>,mgraph::Rand<float>,float>::Call(void*);
	// FUNCTION: ENGINE 0x10AE9BA0
	template MetaMethod0Const<mgraph::Rand<float>,mgraph::Rand<float>,float>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AE9BB0
	template void MetaMethod0Const<mgraph::Rand<float>,mgraph::Rand<float>,float>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE9BD0
	template void MetaMethod0Const<mgraph::Rand<float>,mgraph::Rand<float>,float>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10AE9C70
	template void* MetaMethod0Const<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE9C90
	template MetaMethod0Const<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,unsigned int>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AE9CC0
	template unsigned int MetaMethod0Const<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x10AE9CD0
	template MetaMethod0Const<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,unsigned int>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AE9CE0
	template void MetaMethod0Const<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE9D00
	template void MetaMethod0Const<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10AE9DA0
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE9DC0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AE9DF0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE9E10
	template MetaMethod1<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AE9E20
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE9E40
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE9E60
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AE9E90
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AE9EA0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AE9EB0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE9ED0
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE9EF0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AE9F20
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE9F40
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AE9F50
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AE9F70
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE9F90
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AE9FC0
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AE9FD0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AE9FE0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA000
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA020
	template MetaMethod1<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA050
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEA070
	template MetaMethod1<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEA080
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA0A0
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA0C0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA0F0
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEA100
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEA110
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA130
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA150
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA180
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEA1A0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEA1B0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA1D0
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA1F0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA220
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEA230
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEA240
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA260
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA280
	template MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA2B0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEA2D0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEA2E0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA300
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA320
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA350
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEA360
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEA370
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA390
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA3B0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA3E0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEA400
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEA410
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA430
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA450
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA480
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEA490
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEA4A0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA4C0
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA4E0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA510
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEA530
	template MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEA540
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA560
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA580
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA5B0
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEA5C0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEA5D0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA5F0
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA610
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA640
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEA660
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEA670
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA690
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA6B0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA6E0
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEA6F0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEA700
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA720
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA740
	template MetaMethod1<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA770
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEA790
	template MetaMethod1<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEA7A0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA7C0
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA7E0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA810
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEA820
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEA830
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA850
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA870
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA8A0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEA8C0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEA8D0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA8F0
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA910
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA940
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEA950
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEA960
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEA980
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEA9A0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEA9D0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEA9F0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEAA00
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEAA20
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEAA40
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEAA70
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEAA80
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEAA90
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEAAB0
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEAAD0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEAB00
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEAB20
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEAB30
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEAB50
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEAB70
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEABA0
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEABB0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEABC0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEABE0
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEAC00
	template MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEAC30
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEAC50
	template MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEAC60
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEAC80
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEACA0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEACD0
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEACE0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEACF0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEAD10
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEAD30
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEAD60
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEAD80
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEAD90
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEADB0
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEADD0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEAE00
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEAE10
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEAE20
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEAE40
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEAE60
	template MetaMethod1<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEAE90
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEAEB0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEAEC0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEAEE0
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEAF00
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEAF30
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEAF40
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEAF50
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEAF70
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEAF90
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEAFC0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEAFE0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEAFF0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEB010
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEB030
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEB060
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEB070
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEB080
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEB0A0
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEB0C0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEB0F0
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEB110
	template MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEB120
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEB140
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEB160
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEB190
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEB1A0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEB1B0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEB1D0
	template void* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEB1F0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEB220
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Call(void*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AEB240
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEB250
	template void MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEB270
	template void* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEB290
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AEB2C0
	template Name<CaseSensitive64BitKey> const& MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEB2D0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEB2E0
	template void MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEB570
	template DelegateProperty<DynamicArray<bool,unsigned short> >::DelegateProperty();
	// FUNCTION: ENGINE 0x10AEB580
	template MetaTypeBase* DelegateProperty<DynamicArray<bool,unsigned short> >::GetMetaType();
	// FUNCTION: ENGINE 0x10AEB590
	template DelegateProperty<DynamicArray<bool,unsigned short> >::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AEB5A0
	template DelegateProperty<DynamicArray<unsigned __int64,unsigned short> >::DelegateProperty();
	// FUNCTION: ENGINE 0x10AEB5B0
	template MetaTypeBase* DelegateProperty<DynamicArray<unsigned __int64,unsigned short> >::GetMetaType();
	// FUNCTION: ENGINE 0x10AEB5C0
	template DelegateProperty<DynamicArray<unsigned __int64,unsigned short> >::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AEB5D0
	template DelegateProperty<DynamicArray<Vector,unsigned short> >::DelegateProperty();
	// FUNCTION: ENGINE 0x10AEB5E0
	template MetaTypeBase* DelegateProperty<DynamicArray<Vector,unsigned short> >::GetMetaType();
	// FUNCTION: ENGINE 0x10AEB5F0
	template DelegateProperty<DynamicArray<Vector,unsigned short> >::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AEB600
	template DelegateProperty<DynamicArray<mgraph::TriggerData,unsigned short> >::DelegateProperty();
	// FUNCTION: ENGINE 0x10AEB610
	template MetaTypeBase* DelegateProperty<DynamicArray<mgraph::TriggerData,unsigned short> >::GetMetaType();
	// FUNCTION: ENGINE 0x10AEB620
	template DelegateProperty<DynamicArray<mgraph::TriggerData,unsigned short> >::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AEB630
	template DelegateProperty<Complex>::DelegateProperty();
	// FUNCTION: ENGINE 0x10AEB640
	template MetaTypeBase* DelegateProperty<Complex>::GetMetaType();
	// FUNCTION: ENGINE 0x10AEB650
	template DelegateProperty<Complex>::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AEB660
	template DelegateProperty<DynamicArray<Complex,unsigned short> >::DelegateProperty();
	// FUNCTION: ENGINE 0x10AEB670
	template MetaTypeBase* DelegateProperty<DynamicArray<Complex,unsigned short> >::GetMetaType();
	// FUNCTION: ENGINE 0x10AEB680
	template DelegateProperty<DynamicArray<Complex,unsigned short> >::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AEB690
	template DelegateProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> >::DelegateProperty();
	// FUNCTION: ENGINE 0x10AEB6A0
	template MetaTypeBase* DelegateProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> >::GetMetaType();
	// FUNCTION: ENGINE 0x10AEB6B0
	template DelegateProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> >::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AEBEE0
	template MetaMethod1Base<void,Vector>* MetaProperty<Vector>::GetSetter();
	// FUNCTION: ENGINE 0x10AEBEF0
	template MetaMethod0Base<Vector>* MetaProperty<Vector>::GetGetter();
	// FUNCTION: ENGINE 0x10AEC260
	template int MetaClass<mgraph::ListCount<bool> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC270
	template void MetaClass<mgraph::ListCount<bool> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC280
	template int MetaClass<mgraph::ListEntry<bool> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC290
	template void MetaClass<mgraph::ListEntry<bool> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC2A0
	template int MetaClass<mgraph::ListCount<float> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC2B0
	template void MetaClass<mgraph::ListCount<float> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC2C0
	template int MetaClass<mgraph::ListEntry<float> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC2D0
	template void MetaClass<mgraph::ListEntry<float> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC2E0
	template int MetaClass<mgraph::ListCount<unsigned int> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC2F0
	template void MetaClass<mgraph::ListCount<unsigned int> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC300
	template int MetaClass<mgraph::ListEntry<unsigned int> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC310
	template void MetaClass<mgraph::ListEntry<unsigned int> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC320
	template int MetaClass<mgraph::ListCount<unsigned __int64> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC330
	template void MetaClass<mgraph::ListCount<unsigned __int64> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC340
	template int MetaClass<mgraph::ListEntry<unsigned __int64> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC350
	template void MetaClass<mgraph::ListEntry<unsigned __int64> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC360
	template int MetaClass<mgraph::ListCount<String> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC370
	template void MetaClass<mgraph::ListCount<String> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC380
	template int MetaClass<mgraph::ListEntry<String> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC390
	template void MetaClass<mgraph::ListEntry<String> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC3A0
	template int MetaClass<mgraph::ListCount<Vector> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC3B0
	template void MetaClass<mgraph::ListCount<Vector> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC3C0
	template int MetaClass<mgraph::ListEntry<Vector> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC3D0
	template void MetaClass<mgraph::ListEntry<Vector> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC3E0
	template int MetaClass<mgraph::ListCount<mgraph::TriggerData> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC3F0
	template void MetaClass<mgraph::ListCount<mgraph::TriggerData> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC400
	template int MetaClass<mgraph::ListEntry<mgraph::TriggerData> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC410
	template void MetaClass<mgraph::ListEntry<mgraph::TriggerData> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC420
	template int MetaClass<mgraph::ListCount<Complex> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC430
	template void MetaClass<mgraph::ListCount<Complex> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC440
	template int MetaClass<mgraph::ListEntry<Complex> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC450
	template void MetaClass<mgraph::ListEntry<Complex> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC460
	template int MetaClass<mgraph::ListCount<mgraph::EnvelopeData> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC470
	template void MetaClass<mgraph::ListCount<mgraph::EnvelopeData> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AEC480
	template int MetaClass<mgraph::ListEntry<mgraph::EnvelopeData> >::Slot5();
	// FUNCTION: ENGINE 0x10AEC490
	template void MetaClass<mgraph::ListEntry<mgraph::EnvelopeData> >::Slot6(void*);
	// FUNCTION: ENGINE 0x10AECEA0
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<bool> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECEC0
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECEE0
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECF00
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECF20
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECF40
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECF60
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECF80
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECFA0
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<String> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECFC0
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECFE0
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<Vector> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED000
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED020
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED040
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<Complex> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED060
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED080
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED0A0
	template void* MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED0C0
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<bool> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED0E0
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<bool> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED100
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED120
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED140
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED160
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED180
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED1A0
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED1C0
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<unsigned int> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED1E0
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<unsigned int> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED200
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED220
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED240
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED260
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED280
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED2A0
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED2C0
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<String> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED2E0
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<String> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED300
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED320
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED340
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<Vector> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED360
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<Vector> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED380
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED3A0
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED3C0
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED3E0
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED400
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED420
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED440
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<Complex> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED460
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<Complex> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED480
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED4A0
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED4C0
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED4E0
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED500
	template void* MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED520
	template void* MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED540
	template void* MetaClass<mgraph::Switch<mgraph::Packet<bool> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED560
	template void* MetaClass<mgraph::Switch<mgraph::Packet<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED580
	template void* MetaClass<mgraph::Switch<mgraph::Packet<unsigned int> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED5A0
	template void* MetaClass<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED5C0
	template void* MetaClass<mgraph::Switch<mgraph::Packet<String> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED5E0
	template void* MetaClass<mgraph::Switch<mgraph::Packet<Vector> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED600
	template void* MetaClass<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED620
	template void* MetaClass<mgraph::Switch<mgraph::Packet<Complex> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED640
	template void* MetaClass<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED660
	template void* MetaClass<mgraph::ListCount<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED680
	template void* MetaClass<mgraph::ListEntry<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED6A0
	template void* MetaClass<mgraph::ListCount<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED6C0
	template void* MetaClass<mgraph::ListEntry<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED6E0
	template void* MetaClass<mgraph::ListCount<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED700
	template void* MetaClass<mgraph::ListEntry<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED720
	template void* MetaClass<mgraph::ListCount<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED740
	template void* MetaClass<mgraph::ListEntry<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED760
	template void* MetaClass<mgraph::ListCount<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED780
	template void* MetaClass<mgraph::ListEntry<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED7A0
	template void* MetaClass<mgraph::ListCount<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED7C0
	template void* MetaClass<mgraph::ListEntry<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED7E0
	template void* MetaClass<mgraph::ListCount<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED800
	template void* MetaClass<mgraph::ListEntry<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED820
	template void* MetaClass<mgraph::ListCount<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED840
	template void* MetaClass<mgraph::ListEntry<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED860
	template void* MetaClass<mgraph::ListCount<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AED880
	template void* MetaClass<mgraph::ListEntry<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEEEB0
	template void* DelegateMetaProperty<Vector>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEEF00
	template void DelegateMetaProperty<Vector>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AEEF10
	template void DelegateMetaProperty<Vector>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEEF30
	template void* MetaMethod1<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,void,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEEF50
	template void* MetaMethod1<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,void,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEEF70
	template void* MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,void,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEEF90
	template void* MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,void,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEEFB0
	template void* MetaMethod1<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,void,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEEFD0
	template void* MetaMethod1<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,void,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEEFF0
	template void* MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,void,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF010
	template void* MetaMethod1<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,void,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF030
	template void* MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,void,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF050
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,void,bool const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF070
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,void,bool const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,void,bool const&>::Function);
	// FUNCTION: ENGINE 0x10AEF0A0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,void,bool const&>::Call(void*, bool const&);
	// FUNCTION: ENGINE 0x10AEF0C0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,void,bool const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEF0D0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,void,bool const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEF0F0
	template Garbage<bool>::Garbage(bool*);
	// FUNCTION: ENGINE 0x10AEF110
	template Garbage<bool>::~Garbage();
	// FUNCTION: ENGINE 0x10AEF130
	template void Garbage<bool>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEF150
	template char const* Garbage<bool>::AllocationTag();
	// FUNCTION: ENGINE 0x10AEF160
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,bool const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF1B0
	template bool const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,bool const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEF1C0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,bool const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEF1D0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,bool const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEF290
	template void* MetaProperty<bool const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF2B0
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,DynamicArray<bool,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF2D0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,DynamicArray<bool,unsigned short> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,DynamicArray<bool,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AEF300
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,DynamicArray<bool,unsigned short> const&>::Call(void*, DynamicArray<bool,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AEF320
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,DynamicArray<bool,unsigned short> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEF330
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,DynamicArray<bool,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEF350
	template Garbage<DynamicArray<bool,unsigned short> >::Garbage(DynamicArray<bool,unsigned short>*);
	// FUNCTION: ENGINE 0x10AEF370
	template void Garbage<DynamicArray<bool,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEF390
	template char const* Garbage<DynamicArray<bool,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AEF3A0
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,DynamicArray<bool,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF3C0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,DynamicArray<bool,unsigned short> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,DynamicArray<bool,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AEF3F0
	template DynamicArray<bool,unsigned short> const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,DynamicArray<bool,unsigned short> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEF400
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,DynamicArray<bool,unsigned short> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEF410
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,DynamicArray<bool,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEF430
	template void* MetaProperty<DynamicArray<bool,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF450
	template void* MetaMethod0Const<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF470
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,void,float const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF490
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,void,float const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,void,float const&>::Function);
	// FUNCTION: ENGINE 0x10AEF4C0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,void,float const&>::Call(void*, float const&);
	// FUNCTION: ENGINE 0x10AEF4E0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,void,float const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEF4F0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,void,float const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEF510
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,float const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF530
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,float const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,float const&>::Function);
	// FUNCTION: ENGINE 0x10AEF560
	template float const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,float const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEF570
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,float const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEF580
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,float const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEF5A0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,float const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10AEF640
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,DynamicArray<float,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF660
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,DynamicArray<float,unsigned short> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,DynamicArray<float,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AEF690
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,DynamicArray<float,unsigned short> const&>::Call(void*, DynamicArray<float,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AEF6B0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,DynamicArray<float,unsigned short> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEF6C0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,DynamicArray<float,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEF6E0
	template Garbage<DynamicArray<float,unsigned short> >::Garbage(DynamicArray<float,unsigned short>*);
	// FUNCTION: ENGINE 0x10AEF700
	template void Garbage<DynamicArray<float,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEF720
	template char const* Garbage<DynamicArray<float,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AEF730
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,DynamicArray<float,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF750
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,DynamicArray<float,unsigned short> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,DynamicArray<float,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AEF780
	template DynamicArray<float,unsigned short> const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,DynamicArray<float,unsigned short> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEF790
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,DynamicArray<float,unsigned short> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEF7A0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,DynamicArray<float,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEF7C0
	template void* MetaProperty<DynamicArray<float,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF7E0
	template void* MetaMethod0Const<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF800
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,void,unsigned int const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF820
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,void,unsigned int const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,void,unsigned int const&>::Function);
	// FUNCTION: ENGINE 0x10AEF850
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,void,unsigned int const&>::Call(void*, unsigned int const&);
	// FUNCTION: ENGINE 0x10AEF870
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,void,unsigned int const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEF880
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,void,unsigned int const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEF8A0
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,unsigned int const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF8C0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,unsigned int const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,unsigned int const&>::Function);
	// FUNCTION: ENGINE 0x10AEF8F0
	template unsigned int const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,unsigned int const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEF900
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,unsigned int const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEF910
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,unsigned int const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEF930
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,unsigned int const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10AEF9D0
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,DynamicArray<unsigned int,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEF9F0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,DynamicArray<unsigned int,unsigned short> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,DynamicArray<unsigned int,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AEFA20
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,DynamicArray<unsigned int,unsigned short> const&>::Call(void*, DynamicArray<unsigned int,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AEFA40
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,DynamicArray<unsigned int,unsigned short> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEFA50
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,DynamicArray<unsigned int,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEFA70
	template Garbage<DynamicArray<unsigned int,unsigned short> >::Garbage(DynamicArray<unsigned int,unsigned short>*);
	// FUNCTION: ENGINE 0x10AEFA90
	template void Garbage<DynamicArray<unsigned int,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEFAB0
	template char const* Garbage<DynamicArray<unsigned int,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AEFAC0
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,DynamicArray<unsigned int,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEFAE0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,DynamicArray<unsigned int,unsigned short> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,DynamicArray<unsigned int,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AEFB10
	template DynamicArray<unsigned int,unsigned short> const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,DynamicArray<unsigned int,unsigned short> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEFB20
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,DynamicArray<unsigned int,unsigned short> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEFB30
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,DynamicArray<unsigned int,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEFB50
	template void* MetaProperty<DynamicArray<unsigned int,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEFB70
	template void* MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEFB90
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,void,unsigned __int64 const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEFBB0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,void,unsigned __int64 const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,void,unsigned __int64 const&>::Function);
	// FUNCTION: ENGINE 0x10AEFBE0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,void,unsigned __int64 const&>::Call(void*, unsigned __int64 const&);
	// FUNCTION: ENGINE 0x10AEFC00
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,void,unsigned __int64 const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEFC10
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,void,unsigned __int64 const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEFC30
	template Garbage<unsigned __int64>::Garbage(unsigned __int64*);
	// FUNCTION: ENGINE 0x10AEFC50
	template Garbage<unsigned __int64>::~Garbage();
	// FUNCTION: ENGINE 0x10AEFC70
	template void Garbage<unsigned __int64>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEFC90
	template char const* Garbage<unsigned __int64>::AllocationTag();
	// FUNCTION: ENGINE 0x10AEFCA0
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,unsigned __int64 const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEFCC0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,unsigned __int64 const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,unsigned __int64 const&>::Function);
	// FUNCTION: ENGINE 0x10AEFCF0
	template unsigned __int64 const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,unsigned __int64 const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEFD00
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,unsigned __int64 const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEFD10
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,unsigned __int64 const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEFD30
	template void om::WriteResult<unsigned __int64>(BinaryStream*, unsigned __int64 const&);
	// FUNCTION: ENGINE 0x10AEFD60
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,unsigned __int64 const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10AEFDD0
	template void* MetaProperty<unsigned __int64 const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEFDF0
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,DynamicArray<unsigned __int64,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEFE10
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,DynamicArray<unsigned __int64,unsigned short> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,DynamicArray<unsigned __int64,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AEFE40
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,DynamicArray<unsigned __int64,unsigned short> const&>::Call(void*, DynamicArray<unsigned __int64,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AEFE60
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,DynamicArray<unsigned __int64,unsigned short> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AEFE70
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,DynamicArray<unsigned __int64,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEFE90
	template Garbage<DynamicArray<unsigned __int64,unsigned short> >::Garbage(DynamicArray<unsigned __int64,unsigned short>*);
	// FUNCTION: ENGINE 0x10AEFEB0
	template void Garbage<DynamicArray<unsigned __int64,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEFED0
	template char const* Garbage<DynamicArray<unsigned __int64,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AEFEE0
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,DynamicArray<unsigned __int64,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEFF00
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,DynamicArray<unsigned __int64,unsigned short> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,DynamicArray<unsigned __int64,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AEFF30
	template DynamicArray<unsigned __int64,unsigned short> const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,DynamicArray<unsigned __int64,unsigned short> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AEFF40
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,DynamicArray<unsigned __int64,unsigned short> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AEFF50
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,DynamicArray<unsigned __int64,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AEFF70
	template void* MetaProperty<DynamicArray<unsigned __int64,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEFF90
	template void* MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEFFB0
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,void,String const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEFFD0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,void,String const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,void,String const&>::Function);
	// FUNCTION: ENGINE 0x10AF0000
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,void,String const&>::Call(void*, String const&);
	// FUNCTION: ENGINE 0x10AF0020
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,void,String const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AF0030
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,void,String const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0050
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,String const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF00A0
	template String const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,String const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AF00B0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,String const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AF00C0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,String const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF00E0
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,DynamicArray<String,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0100
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,DynamicArray<String,unsigned short> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,DynamicArray<String,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AF0130
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,DynamicArray<String,unsigned short> const&>::Call(void*, DynamicArray<String,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AF0150
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,DynamicArray<String,unsigned short> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AF0160
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,DynamicArray<String,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0180
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,DynamicArray<String,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF01A0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,DynamicArray<String,unsigned short> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,DynamicArray<String,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AF01D0
	template DynamicArray<String,unsigned short> const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,DynamicArray<String,unsigned short> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AF01E0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,DynamicArray<String,unsigned short> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AF01F0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,DynamicArray<String,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0210
	template void* MetaMethod0Const<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0230
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,void,Vector const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0250
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,void,Vector const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,void,Vector const&>::Function);
	// FUNCTION: ENGINE 0x10AF0280
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,void,Vector const&>::Call(void*, Vector const&);
	// FUNCTION: ENGINE 0x10AF02A0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,void,Vector const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AF02B0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,void,Vector const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF02D0
	template Garbage<Vector>::Garbage(Vector*);
	// FUNCTION: ENGINE 0x10AF02F0
	template Garbage<Vector>::~Garbage();
	// FUNCTION: ENGINE 0x10AF0310
	template void Garbage<Vector>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0330
	template char const* Garbage<Vector>::AllocationTag();
	// FUNCTION: ENGINE 0x10AF0340
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,Vector const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0390
	template Vector const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,Vector const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AF03A0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,Vector const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AF03B0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,Vector const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF03D0
	template void* MetaProperty<Vector const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF03F0
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,DynamicArray<Vector,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0410
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,DynamicArray<Vector,unsigned short> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,DynamicArray<Vector,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AF0440
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,DynamicArray<Vector,unsigned short> const&>::Call(void*, DynamicArray<Vector,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AF0460
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,DynamicArray<Vector,unsigned short> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AF0470
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,DynamicArray<Vector,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0490
	template Garbage<DynamicArray<Vector,unsigned short> >::Garbage(DynamicArray<Vector,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF04B0
	template void Garbage<DynamicArray<Vector,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF04D0
	template char const* Garbage<DynamicArray<Vector,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AF04E0
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,DynamicArray<Vector,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0500
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,DynamicArray<Vector,unsigned short> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,DynamicArray<Vector,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AF0530
	template DynamicArray<Vector,unsigned short> const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,DynamicArray<Vector,unsigned short> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AF0540
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,DynamicArray<Vector,unsigned short> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AF0550
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,DynamicArray<Vector,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0570
	template void* MetaProperty<DynamicArray<Vector,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0590
	template void* MetaMethod0Const<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF05B0
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,DynamicArray<mgraph::TriggerData,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF05D0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,DynamicArray<mgraph::TriggerData,unsigned short> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,DynamicArray<mgraph::TriggerData,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AF0600
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,DynamicArray<mgraph::TriggerData,unsigned short> const&>::Call(void*, DynamicArray<mgraph::TriggerData,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AF0620
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,DynamicArray<mgraph::TriggerData,unsigned short> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AF0630
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,DynamicArray<mgraph::TriggerData,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0650
	template Garbage<DynamicArray<mgraph::TriggerData,unsigned short> >::Garbage(DynamicArray<mgraph::TriggerData,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF0670
	template void Garbage<DynamicArray<mgraph::TriggerData,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0690
	template char const* Garbage<DynamicArray<mgraph::TriggerData,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AF06A0
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,DynamicArray<mgraph::TriggerData,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF06C0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,DynamicArray<mgraph::TriggerData,unsigned short> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,DynamicArray<mgraph::TriggerData,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AF06F0
	template DynamicArray<mgraph::TriggerData,unsigned short> const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,DynamicArray<mgraph::TriggerData,unsigned short> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AF0700
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,DynamicArray<mgraph::TriggerData,unsigned short> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AF0710
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,DynamicArray<mgraph::TriggerData,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0730
	template void* MetaProperty<DynamicArray<mgraph::TriggerData,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0750
	template void* MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0770
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,void,Complex const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0790
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,void,Complex const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,void,Complex const&>::Function);
	// FUNCTION: ENGINE 0x10AF07D0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,void,Complex const&>::Call(void*, Complex const&);
	// FUNCTION: ENGINE 0x10AF07F0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,void,Complex const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AF0800
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,void,Complex const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0820
	template Garbage<Complex>::Garbage(Complex*);
	// FUNCTION: ENGINE 0x10AF0840
	template void DynamicArray<unsigned int,unsigned short>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0890
	template void Garbage<Complex>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF08B0
	template char const* Garbage<Complex>::AllocationTag();
	// FUNCTION: ENGINE 0x10AF08E0
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,Complex const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0900
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,Complex const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,Complex const&>::Function);
	// FUNCTION: ENGINE 0x10AF0930
	template Complex const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,Complex const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AF0940
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,Complex const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AF0950
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,Complex const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0970
	template void* MetaProperty<Complex const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0990
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,DynamicArray<Complex,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF09B0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,DynamicArray<Complex,unsigned short> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,DynamicArray<Complex,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AF09E0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,DynamicArray<Complex,unsigned short> const&>::Call(void*, DynamicArray<Complex,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AF0A00
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,DynamicArray<Complex,unsigned short> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AF0A10
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,DynamicArray<Complex,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0A30
	template Garbage<DynamicArray<Complex,unsigned short> >::Garbage(DynamicArray<Complex,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF0A50
	template void Garbage<DynamicArray<Complex,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0A70
	template char const* Garbage<DynamicArray<Complex,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AF0A80
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,DynamicArray<Complex,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0AA0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,DynamicArray<Complex,unsigned short> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,DynamicArray<Complex,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AF0AD0
	template DynamicArray<Complex,unsigned short> const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,DynamicArray<Complex,unsigned short> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AF0AE0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,DynamicArray<Complex,unsigned short> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AF0AF0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,DynamicArray<Complex,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0B10
	template void* MetaProperty<DynamicArray<Complex,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0B30
	template void* MetaMethod0Const<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0B50
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,void,mgraph::EnvelopeData const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0B70
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,void,mgraph::EnvelopeData const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,void,mgraph::EnvelopeData const&>::Function);
	// FUNCTION: ENGINE 0x10AF0BB0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,void,mgraph::EnvelopeData const&>::Call(void*, mgraph::EnvelopeData const&);
	// FUNCTION: ENGINE 0x10AF0BD0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,void,mgraph::EnvelopeData const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AF0BE0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,void,mgraph::EnvelopeData const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0C00
	template Garbage<mgraph::EnvelopeData>::Garbage(mgraph::EnvelopeData*);
	// FUNCTION: ENGINE 0x10AF0C20
	template void Garbage<mgraph::EnvelopeData>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0C40
	template char const* Garbage<mgraph::EnvelopeData>::AllocationTag();
	// FUNCTION: ENGINE 0x10AF0C70
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::EnvelopeData const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0C90
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::EnvelopeData const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::EnvelopeData const&>::Function);
	// FUNCTION: ENGINE 0x10AF0CC0
	template mgraph::EnvelopeData const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::EnvelopeData const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AF0CD0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::EnvelopeData const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AF0CE0
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::EnvelopeData const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0D00
	template void* MetaProperty<mgraph::EnvelopeData const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0D20
	template void* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0D40
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AF0D70
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::Call(void*, DynamicArray<mgraph::EnvelopeData,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AF0D90
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AF0DA0
	template void MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0DC0
	template Garbage<DynamicArray<mgraph::EnvelopeData,unsigned short> >::Garbage(DynamicArray<mgraph::EnvelopeData,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF0DE0
	template void Garbage<DynamicArray<mgraph::EnvelopeData,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0E00
	template char const* Garbage<DynamicArray<mgraph::EnvelopeData,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AF0E10
	template void* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0E30
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AF0E60
	template DynamicArray<mgraph::EnvelopeData,unsigned short> const& MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AF0E70
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AF0E80
	template void MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF0EA0
	template void* MetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF0EC0
	template void* MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF1CA0
	template MetaMethod1Base<void,bool const&>* MetaProperty<bool const&>::GetSetter();
	// FUNCTION: ENGINE 0x10AF1CB0
	template MetaMethod0Base<bool const&>* MetaProperty<bool const&>::GetGetter();
	// FUNCTION: ENGINE 0x10AF1CD0
	template bool MetaProperty<bool const&>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10AF1D60
	template void MetaProperty<bool const&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10AF1E50
	template bool MetaProperty<unsigned __int64 const&>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10AF1EF0
	template void MetaProperty<unsigned __int64 const&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10AF2220
	template DelegateMetaProperty<bool const&>::DelegateMetaProperty(void*, MetaProperty<bool const&>*);
	// FUNCTION: ENGINE 0x10AF2250
	template void DelegateMetaProperty<bool const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AF2260
	template void DelegateMetaProperty<bool const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF2280
	template void* DelegateMetaProperty<DynamicArray<bool,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF22D0
	template void DelegateMetaProperty<DynamicArray<bool,unsigned short> const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AF22E0
	template void DelegateMetaProperty<DynamicArray<bool,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF2300
	template void* DelegateMetaProperty<DynamicArray<float,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF2320
	template DelegateMetaProperty<DynamicArray<float,unsigned short> const&>::DelegateMetaProperty(void*, MetaProperty<DynamicArray<float,unsigned short> const&>*);
	// FUNCTION: ENGINE 0x10AF2350
	template void DelegateMetaProperty<DynamicArray<float,unsigned short> const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AF2360
	template void DelegateMetaProperty<DynamicArray<float,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF2380
	template void* DelegateMetaProperty<DynamicArray<unsigned int,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF23A0
	template DelegateMetaProperty<DynamicArray<unsigned int,unsigned short> const&>::DelegateMetaProperty(void*, MetaProperty<DynamicArray<unsigned int,unsigned short> const&>*);
	// FUNCTION: ENGINE 0x10AF23D0
	template void DelegateMetaProperty<DynamicArray<unsigned int,unsigned short> const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AF23E0
	template void DelegateMetaProperty<DynamicArray<unsigned int,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF2400
	template void* DelegateMetaProperty<unsigned __int64 const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF2420
	template DelegateMetaProperty<unsigned __int64 const&>::DelegateMetaProperty(void*, MetaProperty<unsigned __int64 const&>*);
	// FUNCTION: ENGINE 0x10AF2450
	template void DelegateMetaProperty<unsigned __int64 const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AF2460
	template void DelegateMetaProperty<unsigned __int64 const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF2480
	template void* DelegateMetaProperty<DynamicArray<unsigned __int64,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF24D0
	template void DelegateMetaProperty<DynamicArray<unsigned __int64,unsigned short> const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AF24E0
	template void DelegateMetaProperty<DynamicArray<unsigned __int64,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF2500
	template void* DelegateMetaProperty<Vector const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF2550
	template void DelegateMetaProperty<Vector const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AF2560
	template void DelegateMetaProperty<Vector const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF2580
	template void* DelegateMetaProperty<DynamicArray<Vector,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF25D0
	template void DelegateMetaProperty<DynamicArray<Vector,unsigned short> const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AF25E0
	template void DelegateMetaProperty<DynamicArray<Vector,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF2600
	template void* DelegateMetaProperty<DynamicArray<mgraph::TriggerData,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF2650
	template void DelegateMetaProperty<DynamicArray<mgraph::TriggerData,unsigned short> const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AF2660
	template void DelegateMetaProperty<DynamicArray<mgraph::TriggerData,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF2680
	template void* DelegateMetaProperty<Complex const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF26A0
	template DelegateMetaProperty<Complex const&>::DelegateMetaProperty(void*, MetaProperty<Complex const&>*);
	// FUNCTION: ENGINE 0x10AF26D0
	template void DelegateMetaProperty<Complex const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AF26E0
	template void DelegateMetaProperty<Complex const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF2700
	template void* DelegateMetaProperty<DynamicArray<Complex,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF2720
	template DelegateMetaProperty<DynamicArray<Complex,unsigned short> const&>::DelegateMetaProperty(void*, MetaProperty<DynamicArray<Complex,unsigned short> const&>*);
	// FUNCTION: ENGINE 0x10AF2750
	template void DelegateMetaProperty<DynamicArray<Complex,unsigned short> const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AF2760
	template void DelegateMetaProperty<DynamicArray<Complex,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF2780
	template void* DelegateMetaProperty<mgraph::EnvelopeData const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF27A0
	template DelegateMetaProperty<mgraph::EnvelopeData const&>::DelegateMetaProperty(void*, MetaProperty<mgraph::EnvelopeData const&>*);
	// FUNCTION: ENGINE 0x10AF27D0
	template void DelegateMetaProperty<mgraph::EnvelopeData const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AF2800
	template void* DelegateMetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF2820
	template DelegateMetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::DelegateMetaProperty(void*, MetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>*);
	// FUNCTION: ENGINE 0x10AF2850
	template void DelegateMetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AF2860
	template void DelegateMetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AF2880
	template void* Garbage<bool>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF28A0
	template void* Garbage<DynamicArray<bool,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF28C0
	template void* Garbage<DynamicArray<float,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF28E0
	template Garbage<DynamicArray<float,unsigned short> >::~Garbage();
	// FUNCTION: ENGINE 0x10AF2920
	template void* Garbage<DynamicArray<unsigned int,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF2940
	template void* Garbage<unsigned __int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF2960
	template void* Garbage<DynamicArray<unsigned __int64,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF2980
	template void* Garbage<Vector>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF29A0
	template void* Garbage<DynamicArray<Vector,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF29C0
	template void* Garbage<DynamicArray<mgraph::TriggerData,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF29E0
	template void* Garbage<Complex>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF2A00
	template void* Garbage<DynamicArray<Complex,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF2A20
	template void* Garbage<mgraph::EnvelopeData>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF31A0
	template void MetaClass<mgraph::PropertyNodeBase>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF3210
	template void MetaClass<mgraph::CommutativeMath<mgraph::VectorAdd> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF3280
	template void MetaClass<mgraph::CommutativeMath<mgraph::FloatAdd> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF32F0
	template void MetaClass<mgraph::CommutativeMath<mgraph::FloatMultiply> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF3360
	template void MetaClass<mgraph::CommutativeMath<mgraph::BoolOr> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF33D0
	template void MetaClass<mgraph::CommutativeMath<mgraph::BoolAnd> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF3440
	template void MetaClass<mgraph::CommutativeMath<mgraph::TriggerAnd> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF34B0
	template void MetaClass<mgraph::CommutativeMath<mgraph::TriggerOr> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF3520
	template void MetaClass<mgraph::NonCommutativeMath<mgraph::FloatSub> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF3590
	template void MetaClass<mgraph::Operator2<mgraph::GreaterThan<float> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF3600
	template void MetaClass<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF3670
	template void MetaClass<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF36E0
	template void MetaClass<mgraph::Operator2<mgraph::LessThan<float> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF3750
	template void MetaClass<mgraph::Operator2<mgraph::Equal<float> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF37C0
	template void MetaClass<mgraph::Operator2<mgraph::NotEqual<float> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF3830
	template void MetaClass<mgraph::UnaryMath<mgraph::BoolNot> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF3B40
	template bool MetaSimpleType<mgraph::Packet<bool> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10AF3B70
	template void MetaSimpleType<mgraph::Packet<bool> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10AF3BA0
	template bool MetaSimpleType<mgraph::Packet<bool> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10AF3BD0
	template bool MetaSimpleType<mgraph::Packet<bool> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10AF3F30
	template bool MetaSimpleType<mgraph::Packet<float> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10AF3F60
	template void MetaSimpleType<mgraph::Packet<float> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10AF3F90
	template bool MetaSimpleType<mgraph::Packet<float> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10AF3FC0
	template bool MetaSimpleType<mgraph::Packet<float> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10AF4CB0
	template bool MetaSimpleType<mgraph::Packet<Vector> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10AF4CE0
	template void MetaSimpleType<mgraph::Packet<Vector> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10AF4D10
	template bool MetaSimpleType<mgraph::Packet<Vector> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10AF4D40
	template bool MetaSimpleType<mgraph::Packet<Vector> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10AF50A0
	template bool MetaSimpleType<mgraph::Packet<mgraph::TriggerData> >::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10AF50D0
	template void MetaSimpleType<mgraph::Packet<mgraph::TriggerData> >::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10AF5100
	template bool MetaSimpleType<mgraph::Packet<mgraph::TriggerData> >::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10AF5130
	template bool MetaSimpleType<mgraph::Packet<mgraph::TriggerData> >::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10AF5DE0
	template bool om::ReadBinary<class mgraph::Packet<class om::DynamicArray<bool,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<bool,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF5E10
	template bool om::WriteBinary<class mgraph::Packet<class om::DynamicArray<bool,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<bool,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF5E40
	template bool om::ReadText<class mgraph::Packet<class om::DynamicArray<bool,unsigned short> > >(TextValue const*, mgraph::Packet<DynamicArray<bool,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF5E70
	template void om::WriteText<class mgraph::Packet<class om::DynamicArray<bool,unsigned short> > >(TextValue*, mgraph::Packet<DynamicArray<bool,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF5FC0
	template bool om::ReadBinary<class mgraph::Packet<class om::DynamicArray<float,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<float,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF5FF0
	template bool om::WriteBinary<class mgraph::Packet<class om::DynamicArray<float,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<float,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF6020
	template bool om::ReadText<class mgraph::Packet<class om::DynamicArray<float,unsigned short> > >(TextValue const*, mgraph::Packet<DynamicArray<float,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF6050
	template void om::WriteText<class mgraph::Packet<class om::DynamicArray<float,unsigned short> > >(TextValue*, mgraph::Packet<DynamicArray<float,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF6170
	template bool om::ReadBinary<class mgraph::Packet<class om::DynamicArray<unsigned int,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<unsigned int,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF61A0
	template bool om::WriteBinary<class mgraph::Packet<class om::DynamicArray<unsigned int,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<unsigned int,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF61D0
	template bool om::ReadText<class mgraph::Packet<class om::DynamicArray<unsigned int,unsigned short> > >(TextValue const*, mgraph::Packet<DynamicArray<unsigned int,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF6200
	template void om::WriteText<class mgraph::Packet<class om::DynamicArray<unsigned int,unsigned short> > >(TextValue*, mgraph::Packet<DynamicArray<unsigned int,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF6230
	template bool om::ReadBinary<class mgraph::Packet<unsigned int> >(BinaryStream*, mgraph::Packet<unsigned int>*);
	// FUNCTION: ENGINE 0x10AF6260
	template bool om::WriteBinary<class mgraph::Packet<unsigned int> >(BinaryStream*, mgraph::Packet<unsigned int> const&);
	// FUNCTION: ENGINE 0x10AF6290
	template bool om::ReadText<class mgraph::Packet<unsigned int> >(TextValue const*, mgraph::Packet<unsigned int>*);
	// FUNCTION: ENGINE 0x10AF62C0
	template void om::WriteText<class mgraph::Packet<unsigned int> >(TextValue*, mgraph::Packet<unsigned int> const&);
	// FUNCTION: ENGINE 0x10AF66E0
	template bool om::ReadBinary<class mgraph::Packet<class om::DynamicArray<unsigned __int64,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF6710
	template bool om::WriteBinary<class mgraph::Packet<class om::DynamicArray<unsigned __int64,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF6740
	template bool om::ReadText<class mgraph::Packet<class om::DynamicArray<unsigned __int64,unsigned short> > >(TextValue const*, mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF6770
	template void om::WriteText<class mgraph::Packet<class om::DynamicArray<unsigned __int64,unsigned short> > >(TextValue*, mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF67A0
	template bool om::ReadBinary<class mgraph::Packet<unsigned __int64> >(BinaryStream*, mgraph::Packet<unsigned __int64>*);
	// FUNCTION: ENGINE 0x10AF67D0
	template bool om::WriteBinary<class mgraph::Packet<unsigned __int64> >(BinaryStream*, mgraph::Packet<unsigned __int64> const&);
	// FUNCTION: ENGINE 0x10AF6800
	template bool om::ReadText<class mgraph::Packet<unsigned __int64> >(TextValue const*, mgraph::Packet<unsigned __int64>*);
	// FUNCTION: ENGINE 0x10AF6830
	template void om::WriteText<class mgraph::Packet<unsigned __int64> >(TextValue*, mgraph::Packet<unsigned __int64> const&);
	// FUNCTION: ENGINE 0x10AF6A10
	template bool om::ReadBinary<class mgraph::Packet<class om::DynamicArray<class om::String,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<String,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF6A40
	template bool om::WriteBinary<class mgraph::Packet<class om::DynamicArray<class om::String,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<String,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF6A70
	template bool om::ReadText<class mgraph::Packet<class om::DynamicArray<class om::String,unsigned short> > >(TextValue const*, mgraph::Packet<DynamicArray<String,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF6AA0
	template void om::WriteText<class mgraph::Packet<class om::DynamicArray<class om::String,unsigned short> > >(TextValue*, mgraph::Packet<DynamicArray<String,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF6AD0
	template bool om::ReadBinary<class mgraph::Packet<class om::String> >(BinaryStream*, mgraph::Packet<String>*);
	// FUNCTION: ENGINE 0x10AF6B00
	template bool om::WriteBinary<class mgraph::Packet<class om::String> >(BinaryStream*, mgraph::Packet<String> const&);
	// FUNCTION: ENGINE 0x10AF6B30
	template bool om::ReadText<class mgraph::Packet<class om::String> >(TextValue const*, mgraph::Packet<String>*);
	// FUNCTION: ENGINE 0x10AF6B60
	template void om::WriteText<class mgraph::Packet<class om::String> >(TextValue*, mgraph::Packet<String> const&);
	// FUNCTION: ENGINE 0x10AF70C0
	template bool om::ReadBinary<class mgraph::Packet<class om::DynamicArray<class om::Vector,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<Vector,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF70F0
	template bool om::WriteBinary<class mgraph::Packet<class om::DynamicArray<class om::Vector,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<Vector,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF7120
	template bool om::ReadText<class mgraph::Packet<class om::DynamicArray<class om::Vector,unsigned short> > >(TextValue const*, mgraph::Packet<DynamicArray<Vector,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF7150
	template void om::WriteText<class mgraph::Packet<class om::DynamicArray<class om::Vector,unsigned short> > >(TextValue*, mgraph::Packet<DynamicArray<Vector,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF7270
	template bool om::ReadBinary<class mgraph::Packet<class om::DynamicArray<class mgraph::TriggerData,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF72A0
	template bool om::WriteBinary<class mgraph::Packet<class om::DynamicArray<class mgraph::TriggerData,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF72D0
	template bool om::ReadText<class mgraph::Packet<class om::DynamicArray<class mgraph::TriggerData,unsigned short> > >(TextValue const*, mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF7300
	template void om::WriteText<class mgraph::Packet<class om::DynamicArray<class mgraph::TriggerData,unsigned short> > >(TextValue*, mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF7420
	template bool om::ReadBinary<class mgraph::Packet<class om::DynamicArray<class om::Complex,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<Complex,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF7450
	template bool om::WriteBinary<class mgraph::Packet<class om::DynamicArray<class om::Complex,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<Complex,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF7480
	template bool om::ReadText<class mgraph::Packet<class om::DynamicArray<class om::Complex,unsigned short> > >(TextValue const*, mgraph::Packet<DynamicArray<Complex,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF74B0
	template void om::WriteText<class mgraph::Packet<class om::DynamicArray<class om::Complex,unsigned short> > >(TextValue*, mgraph::Packet<DynamicArray<Complex,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF74E0
	template bool om::ReadBinary<class mgraph::Packet<class om::Complex> >(BinaryStream*, mgraph::Packet<Complex>*);
	// FUNCTION: ENGINE 0x10AF7510
	template bool om::WriteBinary<class mgraph::Packet<class om::Complex> >(BinaryStream*, mgraph::Packet<Complex> const&);
	// FUNCTION: ENGINE 0x10AF7540
	template bool om::ReadText<class mgraph::Packet<class om::Complex> >(TextValue const*, mgraph::Packet<Complex>*);
	// FUNCTION: ENGINE 0x10AF7570
	template void om::WriteText<class mgraph::Packet<class om::Complex> >(TextValue*, mgraph::Packet<Complex> const&);
	// FUNCTION: ENGINE 0x10AF7750
	template bool om::ReadBinary<class mgraph::Packet<class om::DynamicArray<class mgraph::EnvelopeData,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF7780
	template bool om::WriteBinary<class mgraph::Packet<class om::DynamicArray<class mgraph::EnvelopeData,unsigned short> > >(BinaryStream*, mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF77B0
	template bool om::ReadText<class mgraph::Packet<class om::DynamicArray<class mgraph::EnvelopeData,unsigned short> > >(TextValue const*, mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> >*);
	// FUNCTION: ENGINE 0x10AF77E0
	template void om::WriteText<class mgraph::Packet<class om::DynamicArray<class mgraph::EnvelopeData,unsigned short> > >(TextValue*, mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > const&);
	// FUNCTION: ENGINE 0x10AF7810
	template bool om::ReadBinary<class mgraph::Packet<class mgraph::EnvelopeData> >(BinaryStream*, mgraph::Packet<mgraph::EnvelopeData>*);
	// FUNCTION: ENGINE 0x10AF7840
	template bool om::WriteBinary<class mgraph::Packet<class mgraph::EnvelopeData> >(BinaryStream*, mgraph::Packet<mgraph::EnvelopeData> const&);
	// FUNCTION: ENGINE 0x10AF7870
	template bool om::ReadText<class mgraph::Packet<class mgraph::EnvelopeData> >(TextValue const*, mgraph::Packet<mgraph::EnvelopeData>*);
	// FUNCTION: ENGINE 0x10AF78A0
	template void om::WriteText<class mgraph::Packet<class mgraph::EnvelopeData> >(TextValue*, mgraph::Packet<mgraph::EnvelopeData> const&);
	// FUNCTION: ENGINE 0x10AF7AF0
	template void MetaClass<mgraph::Rand<Vector> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF7B60
	template void MetaClass<mgraph::Rand<float> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF7BD0
	template void MetaClass<mgraph::Rand<unsigned int> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF7C70
	template void MetaClass<mgraph::Throw<mgraph::Packet<bool> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF7CE0
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF7D50
	template void MetaClass<mgraph::Throw<mgraph::Packet<float> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF7DC0
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF7E30
	template void MetaClass<mgraph::Throw<mgraph::Packet<unsigned int> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF7EA0
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF7F10
	template void MetaClass<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF7FB0
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8020
	template void MetaClass<mgraph::Throw<mgraph::Packet<String> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF80D0
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8140
	template void MetaClass<mgraph::Throw<mgraph::Packet<Vector> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF81B0
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8220
	template void MetaClass<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8290
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8300
	template void MetaClass<mgraph::Throw<mgraph::Packet<Complex> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF83A0
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8410
	template void MetaClass<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8480
	template void MetaClass<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF84F0
	template void MetaClass<mgraph::Catch<mgraph::Packet<bool> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8560
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF85D0
	template void MetaClass<mgraph::Catch<mgraph::Packet<float> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8640
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF86B0
	template void MetaClass<mgraph::Catch<mgraph::Packet<unsigned int> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8720
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8790
	template void MetaClass<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8800
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8870
	template void MetaClass<mgraph::Catch<mgraph::Packet<String> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF88E0
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8950
	template void MetaClass<mgraph::Catch<mgraph::Packet<Vector> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF89C0
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8A30
	template void MetaClass<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8AA0
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8B10
	template void MetaClass<mgraph::Catch<mgraph::Packet<Complex> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8B80
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8BF0
	template void MetaClass<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF8C60
	template void MetaClass<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AF9790
	template MetaMethod1<mgraph::Rand<float>,mgraph::Rand<float>,void,float>* MetaMethod1<mgraph::Rand<float>,mgraph::Rand<float>,void,float>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Rand<float>,mgraph::Rand<float>,void,float>::Function);
	// FUNCTION: ENGINE 0x10AF97D0
	template MetaMethod0Const<mgraph::Rand<float>,mgraph::Rand<float>,float>* MetaMethod0Const<mgraph::Rand<float>,mgraph::Rand<float>,float>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Rand<float>,mgraph::Rand<float>,float>::Function);
	// FUNCTION: ENGINE 0x10AF9860
	template MetaMethod1<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,void,unsigned int>* MetaMethod1<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,void,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AF98A0
	template MetaMethod0Const<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,unsigned int>* MetaMethod0Const<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Rand<unsigned int>,mgraph::Rand<unsigned int>,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AF9930
	template MetaMethod1<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9970
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<bool> >,mgraph::Throw<mgraph::Packet<bool> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9A10
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9A50
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9AF0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9B30
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<float> >,mgraph::Throw<mgraph::Packet<float> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9BD0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9C10
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9CB0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9CF0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned int> >,mgraph::Throw<mgraph::Packet<unsigned int> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9D90
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9DD0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9E70
	template MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9EB0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<unsigned __int64> >,mgraph::Throw<mgraph::Packet<unsigned __int64> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9F50
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AF9F90
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA030
	template MetaMethod1<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA070
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<String> >,mgraph::Throw<mgraph::Packet<String> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA110
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA150
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA1F0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA230
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<Vector> >,mgraph::Throw<mgraph::Packet<Vector> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA2D0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA310
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA3B0
	template MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA3F0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA490
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA4D0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA570
	template MetaMethod1<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA5B0
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<Complex> >,mgraph::Throw<mgraph::Packet<Complex> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA650
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA690
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA730
	template MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA770
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA810
	template MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>* MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA850
	template MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>* MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,Name<CaseSensitive64BitKey> const&>::Function);
	// FUNCTION: ENGINE 0x10AFA8F0
	template bool om::ReadText<class mgraph::TriggerData>(TextValue const*, mgraph::TriggerData*);
	// FUNCTION: ENGINE 0x10AFA920
	template void om::WriteText<class mgraph::TriggerData>(TextValue*, mgraph::TriggerData const&);
	// FUNCTION: ENGINE 0x10AFA950
	template bool om::ReadBinary<class mgraph::TriggerData>(BinaryStream*, mgraph::TriggerData*);
	// FUNCTION: ENGINE 0x10AFA980
	template bool om::WriteBinary<class mgraph::TriggerData>(BinaryStream*, mgraph::TriggerData const&);
	// FUNCTION: ENGINE 0x10AFA9B0
	template bool om::ReadText<class om::Complex>(TextValue const*, Complex*);
	// FUNCTION: ENGINE 0x10AFA9E0
	template void om::WriteText<class om::Complex>(TextValue*, Complex const&);
	// FUNCTION: ENGINE 0x10AFAA10
	template bool om::ReadBinary<class om::Complex>(BinaryStream*, Complex*);
	// FUNCTION: ENGINE 0x10AFAA40
	template bool om::WriteBinary<class om::Complex>(BinaryStream*, Complex const&);
	// FUNCTION: ENGINE 0x10AFAB00
	template void om::WriteResult<class mgraph::EnvelopeData>(BinaryStream*, mgraph::EnvelopeData const&);
	// FUNCTION: ENGINE 0x10AFAC20
	template Vector DelegateMetaProperty<Vector>::Get();
	// FUNCTION: ENGINE 0x10AFB190
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<bool> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB200
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB270
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<float> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB2E0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB350
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB3C0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB430
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB4A0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB510
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<String> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB580
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB5F0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<Vector> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB660
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB6D0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB740
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<Complex> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB7B0
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB820
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB890
	template void MetaClass<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB900
	template void MetaClass<mgraph::Inlet<mgraph::Packet<bool> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB970
	template void MetaClass<mgraph::Outlet<mgraph::Packet<bool> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFB9E0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFBA50
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFBAC0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<float> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFBB30
	template void MetaClass<mgraph::Outlet<mgraph::Packet<float> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFBBA0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFBC10
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFBC80
	template void MetaClass<mgraph::Inlet<mgraph::Packet<unsigned int> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFBCF0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<unsigned int> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFBD60
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFBDD0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFBE40
	template void MetaClass<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFBEB0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFBF20
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFBF90
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC000
	template void MetaClass<mgraph::Inlet<mgraph::Packet<String> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC070
	template void MetaClass<mgraph::Outlet<mgraph::Packet<String> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC0E0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC150
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC1C0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<Vector> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC230
	template void MetaClass<mgraph::Outlet<mgraph::Packet<Vector> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC2A0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC310
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC380
	template void MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC3F0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC460
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC4D0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC540
	template void MetaClass<mgraph::Inlet<mgraph::Packet<Complex> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC5B0
	template void MetaClass<mgraph::Outlet<mgraph::Packet<Complex> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC620
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC690
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC700
	template void MetaClass<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC770
	template void MetaClass<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC7E0
	template void MetaClass<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC850
	template void MetaClass<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC8C0
	template void MetaClass<mgraph::Switch<mgraph::Packet<bool> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC930
	template void MetaClass<mgraph::Switch<mgraph::Packet<float> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFC9A0
	template void MetaClass<mgraph::Switch<mgraph::Packet<unsigned int> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCA10
	template void MetaClass<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCA80
	template void MetaClass<mgraph::Switch<mgraph::Packet<String> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCAF0
	template void MetaClass<mgraph::Switch<mgraph::Packet<Vector> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCB60
	template void MetaClass<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCBD0
	template void MetaClass<mgraph::Switch<mgraph::Packet<Complex> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCC40
	template void MetaClass<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCCB0
	template void MetaClass<mgraph::ListCount<bool> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCD20
	template void MetaClass<mgraph::ListEntry<bool> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCD90
	template void MetaClass<mgraph::ListCount<float> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCE00
	template void MetaClass<mgraph::ListEntry<float> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCE70
	template void MetaClass<mgraph::ListCount<unsigned int> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCEE0
	template void MetaClass<mgraph::ListEntry<unsigned int> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCF50
	template void MetaClass<mgraph::ListCount<unsigned __int64> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFCFC0
	template void MetaClass<mgraph::ListEntry<unsigned __int64> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFD030
	template void MetaClass<mgraph::ListCount<String> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFD0A0
	template void MetaClass<mgraph::ListEntry<String> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFD110
	template void MetaClass<mgraph::ListCount<Vector> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFD180
	template void MetaClass<mgraph::ListEntry<Vector> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFD1F0
	template void MetaClass<mgraph::ListCount<mgraph::TriggerData> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFD260
	template void MetaClass<mgraph::ListEntry<mgraph::TriggerData> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFD2D0
	template void MetaClass<mgraph::ListCount<Complex> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFD340
	template void MetaClass<mgraph::ListEntry<Complex> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFD3B0
	template void MetaClass<mgraph::ListCount<mgraph::EnvelopeData> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFD420
	template void MetaClass<mgraph::ListEntry<mgraph::EnvelopeData> >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AFD4E0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,void,bool const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,void,bool const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<bool> >,mgraph::PropertyNode<mgraph::Packet<bool> >,void,bool const&>::Function);
	// FUNCTION: ENGINE 0x10AFD5C0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,DynamicArray<bool,unsigned short> const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,DynamicArray<bool,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,void,DynamicArray<bool,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFD600
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,DynamicArray<bool,unsigned short> const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,DynamicArray<bool,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >,DynamicArray<bool,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFD6A0
	template MetaMethod1<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,void,unsigned int>* MetaMethod1<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,void,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFD6E0
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,unsigned int>* MetaMethod0Const<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<bool> >,mgraph::Switch<mgraph::Packet<bool> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFD720
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,void,float const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,void,float const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,void,float const&>::Function);
	// FUNCTION: ENGINE 0x10AFD760
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,float const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,float const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<float> >,mgraph::PropertyNode<mgraph::Packet<float> >,float const&>::Function);
	// FUNCTION: ENGINE 0x10AFD800
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,DynamicArray<float,unsigned short> const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,DynamicArray<float,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,void,DynamicArray<float,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFD840
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,DynamicArray<float,unsigned short> const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,DynamicArray<float,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >,DynamicArray<float,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFD880
	template void MetaProperty<DynamicArray<float,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,DynamicArray<float,unsigned short> const&>*, MetaMethod0Base<DynamicArray<float,unsigned short> const&>*, unsigned int);
	// FUNCTION: ENGINE 0x10AFD8E0
	template MetaMethod1<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,void,unsigned int>* MetaMethod1<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,void,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFD920
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,unsigned int>* MetaMethod0Const<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<float> >,mgraph::Switch<mgraph::Packet<float> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFD960
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,void,unsigned int const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,void,unsigned int const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,void,unsigned int const&>::Function);
	// FUNCTION: ENGINE 0x10AFD9A0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,unsigned int const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,unsigned int const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned int> >,mgraph::PropertyNode<mgraph::Packet<unsigned int> >,unsigned int const&>::Function);
	// FUNCTION: ENGINE 0x10AFDA40
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,DynamicArray<unsigned int,unsigned short> const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,DynamicArray<unsigned int,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,void,DynamicArray<unsigned int,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFDA80
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,DynamicArray<unsigned int,unsigned short> const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,DynamicArray<unsigned int,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >,DynamicArray<unsigned int,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFDAC0
	template void MetaProperty<DynamicArray<unsigned int,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,DynamicArray<unsigned int,unsigned short> const&>*, MetaMethod0Base<DynamicArray<unsigned int,unsigned short> const&>*, unsigned int);
	// FUNCTION: ENGINE 0x10AFDB20
	template MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,void,unsigned int>* MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,void,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFDB60
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,unsigned int>* MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned int> >,mgraph::Switch<mgraph::Packet<unsigned int> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFDBA0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,void,unsigned __int64 const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,void,unsigned __int64 const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,void,unsigned __int64 const&>::Function);
	// FUNCTION: ENGINE 0x10AFDBE0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,unsigned __int64 const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,unsigned __int64 const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >,unsigned __int64 const&>::Function);
	// FUNCTION: ENGINE 0x10AFDC80
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,DynamicArray<unsigned __int64,unsigned short> const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,DynamicArray<unsigned __int64,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,void,DynamicArray<unsigned __int64,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFDCC0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,DynamicArray<unsigned __int64,unsigned short> const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,DynamicArray<unsigned __int64,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >,DynamicArray<unsigned __int64,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFDD60
	template MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,void,unsigned int>* MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,void,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFDDA0
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,unsigned int>* MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<unsigned __int64> >,mgraph::Switch<mgraph::Packet<unsigned __int64> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFDDE0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,void,String const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,void,String const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<String> >,mgraph::PropertyNode<mgraph::Packet<String> >,void,String const&>::Function);
	// FUNCTION: ENGINE 0x10AFDEC0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,DynamicArray<String,unsigned short> const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,DynamicArray<String,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,void,DynamicArray<String,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFDF00
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,DynamicArray<String,unsigned short> const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,DynamicArray<String,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >,DynamicArray<String,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFDFA0
	template MetaMethod1<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,void,unsigned int>* MetaMethod1<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,void,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFDFE0
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,unsigned int>* MetaMethod0Const<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<String> >,mgraph::Switch<mgraph::Packet<String> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFE020
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,void,Vector const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,void,Vector const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Vector> >,mgraph::PropertyNode<mgraph::Packet<Vector> >,void,Vector const&>::Function);
	// FUNCTION: ENGINE 0x10AFE100
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,DynamicArray<Vector,unsigned short> const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,DynamicArray<Vector,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,void,DynamicArray<Vector,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFE140
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,DynamicArray<Vector,unsigned short> const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,DynamicArray<Vector,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >,DynamicArray<Vector,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFE1E0
	template MetaMethod1<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,void,unsigned int>* MetaMethod1<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,void,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFE220
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,unsigned int>* MetaMethod0Const<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<Vector> >,mgraph::Switch<mgraph::Packet<Vector> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFE260
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,DynamicArray<mgraph::TriggerData,unsigned short> const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,DynamicArray<mgraph::TriggerData,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,void,DynamicArray<mgraph::TriggerData,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFE2A0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,DynamicArray<mgraph::TriggerData,unsigned short> const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,DynamicArray<mgraph::TriggerData,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >,DynamicArray<mgraph::TriggerData,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFE340
	template MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,void,unsigned int>* MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,void,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFE380
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,unsigned int>* MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFE3C0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,void,Complex const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,void,Complex const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,void,Complex const&>::Function);
	// FUNCTION: ENGINE 0x10AFE400
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,Complex const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,Complex const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<Complex> >,mgraph::PropertyNode<mgraph::Packet<Complex> >,Complex const&>::Function);
	// FUNCTION: ENGINE 0x10AFE4A0
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,DynamicArray<Complex,unsigned short> const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,DynamicArray<Complex,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,void,DynamicArray<Complex,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFE4E0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,DynamicArray<Complex,unsigned short> const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,DynamicArray<Complex,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >,DynamicArray<Complex,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFE520
	template void MetaProperty<DynamicArray<Complex,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,DynamicArray<Complex,unsigned short> const&>*, MetaMethod0Base<DynamicArray<Complex,unsigned short> const&>*, unsigned int);
	// FUNCTION: ENGINE 0x10AFE580
	template MetaMethod1<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,void,unsigned int>* MetaMethod1<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,void,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFE5C0
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,unsigned int>* MetaMethod0Const<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<Complex> >,mgraph::Switch<mgraph::Packet<Complex> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFE600
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,void,mgraph::EnvelopeData const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,void,mgraph::EnvelopeData const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,void,mgraph::EnvelopeData const&>::Function);
	// FUNCTION: ENGINE 0x10AFE640
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::EnvelopeData const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::EnvelopeData const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::EnvelopeData const&>::Function);
	// FUNCTION: ENGINE 0x10AFE780
	template MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>* MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,void,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFE7C0
	template MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>* MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AFE800
	template void MetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,DynamicArray<mgraph::EnvelopeData,unsigned short> const&>*, MetaMethod0Base<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>*, unsigned int);
	// FUNCTION: ENGINE 0x10AFE860
	template MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,void,unsigned int>* MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,void,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFE8A0
	template MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,unsigned int>* MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10AFE8E0
	template bool DelegateMetaProperty<bool const&>::Get();
	// FUNCTION: ENGINE 0x10AFE900
	template void DelegateMetaProperty<bool const&>::Set(bool);
	// FUNCTION: ENGINE 0x10AFE920
	template DynamicArray<bool,unsigned short> DelegateMetaProperty<DynamicArray<bool,unsigned short> const&>::Get();
	// FUNCTION: ENGINE 0x10AFE990
	template DynamicArray<float,unsigned short> DelegateMetaProperty<DynamicArray<float,unsigned short> const&>::Get();
	// FUNCTION: ENGINE 0x10AFE9C0
	template void DelegateMetaProperty<DynamicArray<float,unsigned short> const&>::Set(DynamicArray<float,unsigned short>);
	// FUNCTION: ENGINE 0x10AFEA00
	template DynamicArray<unsigned int,unsigned short> DelegateMetaProperty<DynamicArray<unsigned int,unsigned short> const&>::Get();
	// FUNCTION: ENGINE 0x10AFEA30
	template void DelegateMetaProperty<DynamicArray<unsigned int,unsigned short> const&>::Set(DynamicArray<unsigned int,unsigned short>);
	// FUNCTION: ENGINE 0x10AFEA70
	template unsigned __int64 DelegateMetaProperty<unsigned __int64 const&>::Get();
	// FUNCTION: ENGINE 0x10AFEA90
	template void DelegateMetaProperty<unsigned __int64 const&>::Set(unsigned __int64);
	// FUNCTION: ENGINE 0x10AFEAB0
	template DynamicArray<unsigned __int64,unsigned short> DelegateMetaProperty<DynamicArray<unsigned __int64,unsigned short> const&>::Get();
	// FUNCTION: ENGINE 0x10AFED40
	template DynamicArray<mgraph::TriggerData,unsigned short> DelegateMetaProperty<DynamicArray<mgraph::TriggerData,unsigned short> const&>::Get();
	// FUNCTION: ENGINE 0x10AFEDB0
	template Complex DelegateMetaProperty<Complex const&>::Get();
	// FUNCTION: ENGINE 0x10AFEDE0
	template void DelegateMetaProperty<Complex const&>::Set(Complex);
	// FUNCTION: ENGINE 0x10AFEE00
	template DynamicArray<Complex,unsigned short> DelegateMetaProperty<DynamicArray<Complex,unsigned short> const&>::Get();
	// FUNCTION: ENGINE 0x10AFEE30
	template void DelegateMetaProperty<DynamicArray<Complex,unsigned short> const&>::Set(DynamicArray<Complex,unsigned short>);
	// FUNCTION: ENGINE 0x10AFEE70
	template mgraph::EnvelopeData DelegateMetaProperty<mgraph::EnvelopeData const&>::Get();
	// FUNCTION: ENGINE 0x10AFEEB0
	template void DelegateMetaProperty<mgraph::EnvelopeData const&>::Set(mgraph::EnvelopeData);
	// FUNCTION: ENGINE 0x10AFEF90
	template DelegatePropertyBase* MetaProperty<bool const&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x10AFF030
	template DelegatePropertyBase* MetaProperty<DynamicArray<float,unsigned short> const&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x10AFF080
	template DelegatePropertyBase* MetaProperty<DynamicArray<unsigned int,unsigned short> const&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x10AFF0D0
	template DelegatePropertyBase* MetaProperty<unsigned __int64 const&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x10AFF2F0
	template void MetaProperty<Complex const&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10AFF400
	template bool MetaProperty<Complex const&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10AFF440
	template DelegatePropertyBase* MetaProperty<Complex const&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x10AFF490
	template DelegatePropertyBase* MetaProperty<DynamicArray<Complex,unsigned short> const&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x10AFF5B0
	template bool MetaProperty<mgraph::EnvelopeData const&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10AFF5F0
	template DelegatePropertyBase* MetaProperty<mgraph::EnvelopeData const&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x10AFF640
	template DelegatePropertyBase* MetaProperty<DynamicArray<mgraph::EnvelopeData,unsigned short> const&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x10AFFB70
	template Garbage<DynamicArray<unsigned int,unsigned short> >::~Garbage();
	// FUNCTION: ENGINE 0x10AFFC70
	template Garbage<DynamicArray<Complex,unsigned short> >::~Garbage();
	// FUNCTION: ENGINE 0x10AD80C0
	template char const* MetaSimpleType<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD80D0
	template char const* MetaSimpleType<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8160
	template char const* MetaSimpleType<DynamicArray<float,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8170
	template char const* MetaSimpleType<mgraph::Packet<DynamicArray<float,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8180
	template char const* MetaSimpleType<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8210
	template char const* MetaSimpleType<DynamicArray<unsigned int,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8220
	template char const* MetaSimpleType<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8230
	template char const* MetaSimpleType<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD82C0
	template char const* MetaSimpleType<DynamicArray<unsigned __int64,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD82D0
	template char const* MetaSimpleType<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD82E0
	template char const* MetaSimpleType<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8370
	template char const* MetaSimpleType<DynamicArray<String,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8380
	template char const* MetaSimpleType<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8390
	template char const* MetaSimpleType<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8420
	template char const* MetaSimpleType<DynamicArray<Vector,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8430
	template char const* MetaSimpleType<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8440
	template char const* MetaSimpleType<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD84D0
	template char const* MetaSimpleType<DynamicArray<mgraph::TriggerData,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD84E0
	template char const* MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD84F0
	template char const* MetaSimpleType<mgraph::Packet<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8550
	template char const* MetaSimpleType<DynamicArray<Complex,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8560
	template char const* MetaSimpleType<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8570
	template char const* MetaSimpleType<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8600
	template char const* MetaSimpleType<DynamicArray<mgraph::EnvelopeData,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8610
	template char const* MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10AD8620
	template char const* MetaSimpleType<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AE2B90
	template void* MetaSimpleType<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE2BC0
	template void* MetaSimpleType<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE2DF0
	template void* MetaSimpleType<DynamicArray<float,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE2E20
	template void* MetaSimpleType<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE2E50
	template void* MetaSimpleType<mgraph::Packet<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3080
	template void* MetaSimpleType<DynamicArray<unsigned int,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE30B0
	template void* MetaSimpleType<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE30E0
	template void* MetaSimpleType<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3310
	template void* MetaSimpleType<DynamicArray<unsigned __int64,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3340
	template void* MetaSimpleType<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3370
	template void* MetaSimpleType<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE35A0
	template void* MetaSimpleType<DynamicArray<String,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE35D0
	template void* MetaSimpleType<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3600
	template void* MetaSimpleType<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3830
	template void* MetaSimpleType<DynamicArray<Vector,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3860
	template void* MetaSimpleType<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3890
	template void* MetaSimpleType<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3AC0
	template void* MetaSimpleType<DynamicArray<mgraph::TriggerData,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3AF0
	template void* MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3B20
	template void* MetaSimpleType<mgraph::Packet<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3DA0
	template void* MetaSimpleType<DynamicArray<Complex,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3DD0
	template void* MetaSimpleType<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE3E00
	template void* MetaSimpleType<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE4030
	template void* MetaSimpleType<DynamicArray<mgraph::EnvelopeData,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE4060
	template void* MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE4090
	template void* MetaSimpleType<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AF39F0
	template void MetaSimpleType<DynamicArray<bool,unsigned short> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF3A20
	template void MetaSimpleType<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF3A80
	template void MetaSimpleType<mgraph::Packet<DynamicArray<bool,unsigned short> > >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF3AB0
	template void MetaSimpleType<mgraph::Packet<bool> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF3B10
	template void MetaSimpleType<mgraph::Packet<bool> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF3D80
	template void MetaSimpleType<DynamicArray<float,unsigned short> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF3DE0
	template void MetaSimpleType<DynamicArray<float,unsigned short> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF3E10
	template void MetaSimpleType<mgraph::Packet<DynamicArray<float,unsigned short> > >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF3E70
	template void MetaSimpleType<mgraph::Packet<DynamicArray<float,unsigned short> > >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF3EA0
	template void MetaSimpleType<mgraph::Packet<float> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF3F00
	template void MetaSimpleType<mgraph::Packet<float> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF4170
	template void MetaSimpleType<DynamicArray<unsigned int,unsigned short> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF41D0
	template void MetaSimpleType<DynamicArray<unsigned int,unsigned short> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF4200
	template void MetaSimpleType<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF4260
	template void MetaSimpleType<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF4290
	template void MetaSimpleType<mgraph::Packet<unsigned int> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF42F0
	template void MetaSimpleType<mgraph::Packet<unsigned int> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF44A0
	template void MetaSimpleType<DynamicArray<unsigned __int64,unsigned short> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF4500
	template void MetaSimpleType<DynamicArray<unsigned __int64,unsigned short> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF4530
	template void MetaSimpleType<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF4590
	template void MetaSimpleType<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF45C0
	template void MetaSimpleType<mgraph::Packet<unsigned __int64> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF4620
	template void MetaSimpleType<mgraph::Packet<unsigned __int64> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF47D0
	template void MetaSimpleType<DynamicArray<String,unsigned short> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF4830
	template void MetaSimpleType<DynamicArray<String,unsigned short> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF4860
	template void MetaSimpleType<mgraph::Packet<DynamicArray<String,unsigned short> > >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF48C0
	template void MetaSimpleType<mgraph::Packet<DynamicArray<String,unsigned short> > >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF48F0
	template void MetaSimpleType<mgraph::Packet<String> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF4950
	template void MetaSimpleType<mgraph::Packet<String> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF4B00
	template void MetaSimpleType<DynamicArray<Vector,unsigned short> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF4B60
	template void MetaSimpleType<DynamicArray<Vector,unsigned short> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF4B90
	template void MetaSimpleType<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF4BF0
	template void MetaSimpleType<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF4C20
	template void MetaSimpleType<mgraph::Packet<Vector> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF4C80
	template void MetaSimpleType<mgraph::Packet<Vector> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF4EF0
	template void MetaSimpleType<DynamicArray<mgraph::TriggerData,unsigned short> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF4F50
	template void MetaSimpleType<DynamicArray<mgraph::TriggerData,unsigned short> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF4F80
	template void MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF4FE0
	template void MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF5010
	template void MetaSimpleType<mgraph::Packet<mgraph::TriggerData> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF5070
	template void MetaSimpleType<mgraph::Packet<mgraph::TriggerData> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF52C0
	template void MetaSimpleType<DynamicArray<Complex,unsigned short> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF5320
	template void MetaSimpleType<DynamicArray<Complex,unsigned short> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF5350
	template void MetaSimpleType<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF53B0
	template void MetaSimpleType<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF53E0
	template void MetaSimpleType<mgraph::Packet<Complex> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF5440
	template void MetaSimpleType<mgraph::Packet<Complex> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF55F0
	template void MetaSimpleType<DynamicArray<mgraph::EnvelopeData,unsigned short> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF5650
	template void MetaSimpleType<DynamicArray<mgraph::EnvelopeData,unsigned short> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF5680
	template void MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF56E0
	template void MetaSimpleType<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::ReleaseType();
	// FUNCTION: ENGINE 0x10AF5710
	template void MetaSimpleType<mgraph::Packet<mgraph::EnvelopeData> >::Create(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AF5770
	template void MetaSimpleType<mgraph::Packet<mgraph::EnvelopeData> >::ReleaseType();
	// FUNCTION: ENGINE 0x10AC34A0
	template DynamicArray<float,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10AC36E0
	template void DynamicArray<float,unsigned short>::DestroyElements(float*, unsigned short);
	// FUNCTION: ENGINE 0x10AC3700
	template void DynamicArray<float,unsigned short>::ReleaseElements(float*, unsigned short);
	// FUNCTION: ENGINE 0x10AC3F20
	template DynamicArray<float,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10AC3F50
	template void DynamicArray<float,unsigned short>::Empty();
	// FUNCTION: ENGINE 0x10AC5CC0
	template void DynamicArray<float,unsigned short>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ADCFF0
	template void DynamicArray<unsigned int,unsigned short>::DestroyElements(unsigned int*, unsigned short);
	// FUNCTION: ENGINE 0x10ADD040
	template bool* DynamicArray<bool,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10ADD060
	template void DynamicArray<bool,unsigned short>::ReleaseElements(bool*, unsigned short);
	// FUNCTION: ENGINE 0x10ADD1D0
	template void DynamicArray<unsigned __int64,unsigned short>::DestroyElements(unsigned __int64*, unsigned short);
	// FUNCTION: ENGINE 0x10ADD230
	template unsigned __int64* DynamicArray<unsigned __int64,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10ADD250
	template void DynamicArray<unsigned __int64,unsigned short>::ReleaseElements(unsigned __int64*, unsigned short);
	// FUNCTION: ENGINE 0x10ADD350
	template void DynamicArray<Vector,unsigned short>::DestroyElements(Vector*, unsigned short);
	// FUNCTION: ENGINE 0x10ADD3B0
	template Vector* DynamicArray<Vector,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10ADD450
	template void DynamicArray<mgraph::TriggerData,unsigned short>::DestroyElements(mgraph::TriggerData*, unsigned short);
	// FUNCTION: ENGINE 0x10ADD4A0
	template mgraph::TriggerData* DynamicArray<mgraph::TriggerData,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10ADD4C0
	template void DynamicArray<mgraph::TriggerData,unsigned short>::ReleaseElements(mgraph::TriggerData*, unsigned short);
	// FUNCTION: ENGINE 0x10ADD690
	template void DynamicArray<mgraph::EnvelopeData,unsigned short>::ReleaseElements(mgraph::EnvelopeData*, unsigned short);
	// FUNCTION: ENGINE 0x10AE7EF0
	template DynamicArray<bool,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10AE7F10
	template void DynamicArray<bool,unsigned short>::Clear();
	// FUNCTION: ENGINE 0x10AE7F40
	template void DynamicArray<bool,unsigned short>::Reserve(unsigned short);
	// FUNCTION: ENGINE 0x10AE8000
	template void DynamicArray<bool,unsigned short>::Empty();
	// FUNCTION: ENGINE 0x10AE82B0
	template DynamicArray<unsigned __int64,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10AE82D0
	template void DynamicArray<unsigned __int64,unsigned short>::Clear();
	// FUNCTION: ENGINE 0x10AE8300
	template void DynamicArray<unsigned __int64,unsigned short>::Reserve(unsigned short);
	// FUNCTION: ENGINE 0x10AE8340
	template unsigned __int64& DynamicArray<unsigned __int64,unsigned short>::Append();
	// FUNCTION: ENGINE 0x10AE8590
	template DynamicArray<Vector,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10AE85B0
	template void DynamicArray<Vector,unsigned short>::Clear();
	// FUNCTION: ENGINE 0x10AE85E0
	template void DynamicArray<Vector,unsigned short>::Reserve(unsigned short);
	// FUNCTION: ENGINE 0x10AE8620
	template Vector& DynamicArray<Vector,unsigned short>::Append();
	// FUNCTION: ENGINE 0x10AE86A0
	template void DynamicArray<Vector,unsigned short>::Empty();
	// FUNCTION: ENGINE 0x10AE8790
	template DynamicArray<mgraph::TriggerData,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10AE87B0
	template void DynamicArray<mgraph::TriggerData,unsigned short>::Clear();
	// FUNCTION: ENGINE 0x10AE87E0
	template void DynamicArray<mgraph::TriggerData,unsigned short>::Reserve(unsigned short);
	// FUNCTION: ENGINE 0x10AE88A0
	template void DynamicArray<mgraph::TriggerData,unsigned short>::Empty();
	// FUNCTION: ENGINE 0x10AE89B0
	template void DynamicArray<Complex,unsigned short>::Clear();
	// FUNCTION: ENGINE 0x10AE8CA0
	template void MetaMethod1<mgraph::Rand<Vector>,mgraph::Rand<Vector>,void,Vector>::Call(void*, Vector);
	// FUNCTION: ENGINE 0x10AE9880
	template Vector MetaMethod0Const<mgraph::Rand<Vector>,mgraph::Rand<Vector>,Vector>::Call(void*);
	// FUNCTION: ENGINE 0x10AEEC00
	template DynamicArray<Vector,unsigned short>::DynamicArray(DynamicArray<Vector,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AF5DB0
	template int om::NewValue<bool,unsigned short>(DynamicArray<bool,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF5F60
	template int om::NewValue<float,unsigned short>(DynamicArray<float,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF6140
	template int om::NewValue<unsigned int,unsigned short>(DynamicArray<unsigned int,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF63B0
	template bool om::ReadText(TextValue const*, DynamicArray<unsigned __int64,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF64B0
	template void om::WriteText(TextValue*, DynamicArray<unsigned __int64,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AF65B0
	template bool om::ReadBinary(BinaryStream*, DynamicArray<unsigned __int64,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF66B0
	template int om::NewValue<unsigned __int64,unsigned short>(DynamicArray<unsigned __int64,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF69E0
	template int om::NewValue<class om::String,unsigned short>(DynamicArray<String,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF7090
	template int om::NewValue<class om::Vector,unsigned short>(DynamicArray<Vector,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF7240
	template int om::NewValue<class mgraph::TriggerData,unsigned short>(DynamicArray<mgraph::TriggerData,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF73F0
	template int om::NewValue<class om::Complex,unsigned short>(DynamicArray<Complex,unsigned short>*);
	// FUNCTION: ENGINE 0x10AF7720
	template int om::NewValue<class mgraph::EnvelopeData,unsigned short>(DynamicArray<mgraph::EnvelopeData,unsigned short>*);
	// FUNCTION: ENGINE 0x10AFAC40
	template void DelegateMetaProperty<Vector>::Set(Vector);
	// FUNCTION: ENGINE 0x10AFE950
	template void DelegateMetaProperty<DynamicArray<bool,unsigned short> const&>::Set(DynamicArray<bool,unsigned short>);
	// FUNCTION: ENGINE 0x10AFEAE0
	template void DelegateMetaProperty<DynamicArray<unsigned __int64,unsigned short> const&>::Set(DynamicArray<unsigned __int64,unsigned short>);
	// FUNCTION: ENGINE 0x10AFEC80
	template Vector DelegateMetaProperty<Vector const&>::Get();
	// FUNCTION: ENGINE 0x10AFECB0
	template void DelegateMetaProperty<Vector const&>::Set(Vector);
	// FUNCTION: ENGINE 0x10AFECD0
	template DynamicArray<Vector,unsigned short> DelegateMetaProperty<DynamicArray<Vector,unsigned short> const&>::Get();
	// FUNCTION: ENGINE 0x10AFED00
	template void DelegateMetaProperty<DynamicArray<Vector,unsigned short> const&>::Set(DynamicArray<Vector,unsigned short>);
	// FUNCTION: ENGINE 0x10AFED70
	template void DelegateMetaProperty<DynamicArray<mgraph::TriggerData,unsigned short> const&>::Set(DynamicArray<mgraph::TriggerData,unsigned short>);
	// FUNCTION: ENGINE 0x10AFFB30
	template Garbage<DynamicArray<bool,unsigned short> >::~Garbage();
	// FUNCTION: ENGINE 0x10AFFBB0
	template Garbage<DynamicArray<unsigned __int64,unsigned short> >::~Garbage();
	// FUNCTION: ENGINE 0x10AFFBF0
	template Garbage<DynamicArray<Vector,unsigned short> >::~Garbage();
	// FUNCTION: ENGINE 0x10AFFC30
	template Garbage<DynamicArray<mgraph::TriggerData,unsigned short> >::~Garbage();
}

namespace mgraph
{
	using namespace om;
	// FUNCTION: ENGINE 0x10AE2C80
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<bool> >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE2DA0
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<DynamicArray<bool,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE2F10
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<float> >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE3030
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<DynamicArray<float,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE31E0
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<unsigned int> >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE32C0
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE3470
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<unsigned __int64> >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE3550
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE3700
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<String> >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE37E0
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<DynamicArray<String,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE3950
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<Vector> >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE3A70
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE3BF0
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<mgraph::TriggerData> >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE3D50
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE3F00
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<Complex> >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE3FE0
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE4190
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<mgraph::EnvelopeData> >::GetPacketType();
	// FUNCTION: ENGINE 0x10AE4270
	template MetaTypeBase* mgraph::PinDataType<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::GetPacketType();
	// FUNCTION: ENGINE 0x10ACA0C0
	template void mgraph::NodeType<mgraph::Node>::Destroy();
	// FUNCTION: ENGINE 0x10ACAD70
	template void mgraph::NodeType<mgraph::Node>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ACAD90
	template char const* mgraph::NodeType<mgraph::Node>::AllocationTag();
	// FUNCTION: ENGINE 0x10AF2D10
	template void mgraph::NodeType<mgraph::PropertyNodeBase>::Destroy();
	// FUNCTION: ENGINE 0x10AF2D40
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::VectorAdd> >::Destroy();
	// FUNCTION: ENGINE 0x10AF2D70
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatAdd> >::Destroy();
	// FUNCTION: ENGINE 0x10AF2DA0
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatMultiply> >::Destroy();
	// FUNCTION: ENGINE 0x10AF2DD0
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolOr> >::Destroy();
	// FUNCTION: ENGINE 0x10AF2E00
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolAnd> >::Destroy();
	// FUNCTION: ENGINE 0x10AF2E30
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerAnd> >::Destroy();
	// FUNCTION: ENGINE 0x10AF2E60
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerOr> >::Destroy();
	// FUNCTION: ENGINE 0x10AF2E90
	template void mgraph::NodeType<mgraph::NonCommutativeMath<mgraph::FloatSub> >::Destroy();
	// FUNCTION: ENGINE 0x10AF2EC0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThan<float> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF2EF0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF2F20
	template void mgraph::NodeType<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF2F50
	template void mgraph::NodeType<mgraph::Operator2<mgraph::LessThan<float> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF2F80
	template void mgraph::NodeType<mgraph::Operator2<mgraph::Equal<float> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF2FB0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::NotEqual<float> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF2FE0
	template void mgraph::NodeType<mgraph::UnaryMath<mgraph::BoolNot> >::Destroy();
	// FUNCTION: ENGINE 0x10AF5920
	template void mgraph::NodeType<mgraph::Rand<float> >::Destroy();
	// FUNCTION: ENGINE 0x10AF5950
	template void mgraph::NodeType<mgraph::Rand<unsigned int> >::Destroy();
	// FUNCTION: ENGINE 0x10AF5EA0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<bool> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF5ED0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<bool> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF5F00
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF5F30
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF6080
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<float> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF60B0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<float> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF60E0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF6110
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF62F0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned int> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF6320
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned int> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF6350
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF6380
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF6860
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF6980
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF69B0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF6B90
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<String> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF6C80
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<String> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF6CB0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF6CE0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF7180
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<Vector> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF71B0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<Vector> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF71E0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF7210
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF7330
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF7360
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF7390
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF73C0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF75A0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<Complex> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF76C0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF76F0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF78D0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF7900
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::Destroy();
	// FUNCTION: ENGINE 0x10AF7930
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AF7960
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AFAC80
	template void mgraph::NodeType<mgraph::ListCount<bool> >::Destroy();
	// FUNCTION: ENGINE 0x10AFACB0
	template void mgraph::NodeType<mgraph::ListEntry<bool> >::Destroy();
	// FUNCTION: ENGINE 0x10AFACE0
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<bool> > >::Destroy();
	// FUNCTION: ENGINE 0x10AFAD10
	template void mgraph::NodeType<mgraph::ListCount<float> >::Destroy();
	// FUNCTION: ENGINE 0x10AFAD40
	template void mgraph::NodeType<mgraph::ListEntry<float> >::Destroy();
	// FUNCTION: ENGINE 0x10AFAD70
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<float> > >::Destroy();
	// FUNCTION: ENGINE 0x10AFADA0
	template void mgraph::NodeType<mgraph::ListCount<unsigned int> >::Destroy();
	// FUNCTION: ENGINE 0x10AFADD0
	template void mgraph::NodeType<mgraph::ListEntry<unsigned int> >::Destroy();
	// FUNCTION: ENGINE 0x10AFAE00
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned int> > >::Destroy();
	// FUNCTION: ENGINE 0x10AFAE30
	template void mgraph::NodeType<mgraph::ListCount<unsigned __int64> >::Destroy();
	// FUNCTION: ENGINE 0x10AFAE60
	template void mgraph::NodeType<mgraph::ListEntry<unsigned __int64> >::Destroy();
	// FUNCTION: ENGINE 0x10AFAE90
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::Destroy();
	// FUNCTION: ENGINE 0x10AFAEC0
	template void mgraph::NodeType<mgraph::ListCount<String> >::Destroy();
	// FUNCTION: ENGINE 0x10AFAEF0
	template void mgraph::NodeType<mgraph::ListEntry<String> >::Destroy();
	// FUNCTION: ENGINE 0x10AFAF20
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<String> > >::Destroy();
	// FUNCTION: ENGINE 0x10AFAF50
	template void mgraph::NodeType<mgraph::ListCount<Vector> >::Destroy();
	// FUNCTION: ENGINE 0x10AFAF80
	template void mgraph::NodeType<mgraph::ListEntry<Vector> >::Destroy();
	// FUNCTION: ENGINE 0x10AFAFB0
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<Vector> > >::Destroy();
	// FUNCTION: ENGINE 0x10AFAFE0
	template void mgraph::NodeType<mgraph::ListCount<mgraph::TriggerData> >::Destroy();
	// FUNCTION: ENGINE 0x10AFB010
	template void mgraph::NodeType<mgraph::ListEntry<mgraph::TriggerData> >::Destroy();
	// FUNCTION: ENGINE 0x10AFB040
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::Destroy();
	// FUNCTION: ENGINE 0x10AFB070
	template void mgraph::NodeType<mgraph::ListCount<Complex> >::Destroy();
	// FUNCTION: ENGINE 0x10AFB0A0
	template void mgraph::NodeType<mgraph::ListEntry<Complex> >::Destroy();
	// FUNCTION: ENGINE 0x10AFB0D0
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<Complex> > >::Destroy();
	// FUNCTION: ENGINE 0x10AFB100
	template void mgraph::NodeType<mgraph::ListCount<mgraph::EnvelopeData> >::Destroy();
	// FUNCTION: ENGINE 0x10AFB130
	template void mgraph::NodeType<mgraph::ListEntry<mgraph::EnvelopeData> >::Destroy();
	// FUNCTION: ENGINE 0x10AFB160
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE1750
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Rand<Vector> >::Get();
	// FUNCTION: ENGINE 0x10AE1860
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNodeBase>::Get();
	// FUNCTION: ENGINE 0x10AE1D00
	template void* mgraph::NodeType<mgraph::CommutativeMath<mgraph::VectorAdd> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1900
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::VectorAdd> >::Get();
	// FUNCTION: ENGINE 0x10AE1920
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatAdd> >::Get();
	// FUNCTION: ENGINE 0x10AE1940
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatMultiply> >::Get();
	// FUNCTION: ENGINE 0x10AE1960
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolOr> >::Get();
	// FUNCTION: ENGINE 0x10AE1980
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolAnd> >::Get();
	// FUNCTION: ENGINE 0x10AE19A0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerAnd> >::Get();
	// FUNCTION: ENGINE 0x10AE19C0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerOr> >::Get();
	// FUNCTION: ENGINE 0x10AE19E0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::NonCommutativeMath<mgraph::FloatSub> >::Get();
	// FUNCTION: ENGINE 0x10AE1A00
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThan<float> > >::Get();
	// FUNCTION: ENGINE 0x10AE1A20
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::Get();
	// FUNCTION: ENGINE 0x10AE1A40
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::Get();
	// FUNCTION: ENGINE 0x10AE1A60
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::LessThan<float> > >::Get();
	// FUNCTION: ENGINE 0x10AE1A80
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::Equal<float> > >::Get();
	// FUNCTION: ENGINE 0x10AE1AA0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::NotEqual<float> > >::Get();
	// FUNCTION: ENGINE 0x10AE1AC0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::UnaryMath<mgraph::BoolNot> >::Get();
	// FUNCTION: ENGINE 0x10AE5B80
	template void* mgraph::NodeType<mgraph::Rand<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE18E0
	template void* mgraph::NodeType<mgraph::PropertyNodeBase>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1D20
	template void* mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatAdd> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1D40
	template void* mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatMultiply> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1D60
	template void* mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolOr> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1D80
	template void* mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolAnd> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1DA0
	template void* mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerAnd> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1DC0
	template void* mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerOr> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1DE0
	template void* mgraph::NodeType<mgraph::NonCommutativeMath<mgraph::FloatSub> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1E00
	template void* mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThan<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1E20
	template void* mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1E40
	template void* mgraph::NodeType<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1E60
	template void* mgraph::NodeType<mgraph::Operator2<mgraph::LessThan<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1E80
	template void* mgraph::NodeType<mgraph::Operator2<mgraph::Equal<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE1EA0
	template void* mgraph::NodeType<mgraph::Operator2<mgraph::NotEqual<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE2490
	template void mgraph::NodeType<mgraph::Rand<Vector> >::Destroy();
	// FUNCTION: ENGINE 0x10AE2BF0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<bool> > >::Get();
	// FUNCTION: ENGINE 0x10AE2C10
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE2E80
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<float> > >::Get();
	// FUNCTION: ENGINE 0x10AE2EA0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE3110
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::Get();
	// FUNCTION: ENGINE 0x10AE3130
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE33A0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::Get();
	// FUNCTION: ENGINE 0x10AE33C0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE3630
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<String> > >::Get();
	// FUNCTION: ENGINE 0x10AE3650
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE38C0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Vector> > >::Get();
	// FUNCTION: ENGINE 0x10AE38E0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE3B50
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE3E30
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Complex> > >::Get();
	// FUNCTION: ENGINE 0x10AE3E50
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE40C0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::Get();
	// FUNCTION: ENGINE 0x10AE40E0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE42C0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Rand<float> >::Get();
	// FUNCTION: ENGINE 0x10AE42E0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Rand<unsigned int> >::Get();
	// FUNCTION: ENGINE 0x10AE44E0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<bool> > >::Get();
	// FUNCTION: ENGINE 0x10AE4500
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<bool> > >::Get();
	// FUNCTION: ENGINE 0x10AE4520
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE4540
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE4720
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<float> > >::Get();
	// FUNCTION: ENGINE 0x10AE4740
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<float> > >::Get();
	// FUNCTION: ENGINE 0x10AE4760
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE4780
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE48A0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned int> > >::Get();
	// FUNCTION: ENGINE 0x10AE48C0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned int> > >::Get();
	// FUNCTION: ENGINE 0x10AE48E0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE4900
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE4A90
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::Get();
	// FUNCTION: ENGINE 0x10AE4AB0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::Get();
	// FUNCTION: ENGINE 0x10AE4AD0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE4AF0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE4C80
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<String> > >::Get();
	// FUNCTION: ENGINE 0x10AE4CA0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<String> > >::Get();
	// FUNCTION: ENGINE 0x10AE4CC0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE4CE0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE4EE0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Vector> > >::Get();
	// FUNCTION: ENGINE 0x10AE4F00
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Vector> > >::Get();
	// FUNCTION: ENGINE 0x10AE4F20
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE4F40
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5100
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::Get();
	// FUNCTION: ENGINE 0x10AE5120
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::Get();
	// FUNCTION: ENGINE 0x10AE5140
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5160
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5350
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Complex> > >::Get();
	// FUNCTION: ENGINE 0x10AE5370
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Complex> > >::Get();
	// FUNCTION: ENGINE 0x10AE5390
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE53B0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE54F0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::Get();
	// FUNCTION: ENGINE 0x10AE5510
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::Get();
	// FUNCTION: ENGINE 0x10AE5530
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5550
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE6D20
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6D00
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<bool> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6CE0
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<bool> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE5CC0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<bool> > >::Get();
	// FUNCTION: ENGINE 0x10AE5CE0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<bool> > >::Get();
	// FUNCTION: ENGINE 0x10AE5D00
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5D20
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5D40
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<float> > >::Get();
	// FUNCTION: ENGINE 0x10AE5D60
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<float> > >::Get();
	// FUNCTION: ENGINE 0x10AE5D80
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5DA0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5DC0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned int> > >::Get();
	// FUNCTION: ENGINE 0x10AE5DE0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned int> > >::Get();
	// FUNCTION: ENGINE 0x10AE5E00
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5E20
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5E40
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::Get();
	// FUNCTION: ENGINE 0x10AE5E80
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::Get();
	// FUNCTION: ENGINE 0x10AE5EA0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5EC0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5EE0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<String> > >::Get();
	// FUNCTION: ENGINE 0x10AE5F20
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<String> > >::Get();
	// FUNCTION: ENGINE 0x10AE5F40
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5F60
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5F80
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<Vector> > >::Get();
	// FUNCTION: ENGINE 0x10AE5FA0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<Vector> > >::Get();
	// FUNCTION: ENGINE 0x10AE5FC0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE5FE0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE6000
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::Get();
	// FUNCTION: ENGINE 0x10AE6020
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::Get();
	// FUNCTION: ENGINE 0x10AE6040
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE6060
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE6080
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<Complex> > >::Get();
	// FUNCTION: ENGINE 0x10AE60C0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<Complex> > >::Get();
	// FUNCTION: ENGINE 0x10AE60E0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE6100
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE6120
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::Get();
	// FUNCTION: ENGINE 0x10AE6140
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::Get();
	// FUNCTION: ENGINE 0x10AE6160
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE6180
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Get();
	// FUNCTION: ENGINE 0x10AE1EC0
	template void* mgraph::NodeType<mgraph::UnaryMath<mgraph::BoolNot> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC4A0
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<bool> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC4C0
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC4E0
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC500
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC520
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC540
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC560
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC580
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC5A0
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<String> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC5C0
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC5E0
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Vector> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC600
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC620
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC640
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Complex> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC660
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC680
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC6A0
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE5C80
	template void* mgraph::NodeType<mgraph::Rand<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE5CA0
	template void* mgraph::NodeType<mgraph::Rand<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC6C0
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<bool> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC6E0
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<bool> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC700
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC720
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC740
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC760
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC780
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC7A0
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC7C0
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned int> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC7E0
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned int> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC800
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC820
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC840
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC860
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC880
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC8A0
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE8D00
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<bool> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8D30
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8D60
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<float> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8D90
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8DC0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8DF0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8E20
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8E50
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8E80
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<String> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8EB0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8EE0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Vector> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8F10
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8F40
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8F70
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Complex> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8FA0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE8FD0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9000
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9170
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<bool> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE91A0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<bool> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE91D0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9200
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9230
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<float> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9260
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<float> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9290
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE92C0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE92F0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned int> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9320
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned int> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9350
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9380
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE93B0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE93E0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9410
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9440
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9470
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<String> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE94A0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<String> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE94D0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9500
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9530
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Vector> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9560
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Vector> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9590
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE95C0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE95F0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9620
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9650
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9680
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE96B0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Complex> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE96E0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Complex> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9710
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9740
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9770
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE97A0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::Destroy();
	// FUNCTION: ENGINE 0x10AE97D0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AE9800
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Destroy();
	// FUNCTION: ENGINE 0x10AEBF00
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListCount<bool> >::Get();
	// FUNCTION: ENGINE 0x10AEBF20
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListEntry<bool> >::Get();
	// FUNCTION: ENGINE 0x10AEBF40
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<bool> > >::Get();
	// FUNCTION: ENGINE 0x10AEBF60
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListCount<float> >::Get();
	// FUNCTION: ENGINE 0x10AEBF80
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListEntry<float> >::Get();
	// FUNCTION: ENGINE 0x10AEBFA0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<float> > >::Get();
	// FUNCTION: ENGINE 0x10AEBFC0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListCount<unsigned int> >::Get();
	// FUNCTION: ENGINE 0x10AEBFE0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListEntry<unsigned int> >::Get();
	// FUNCTION: ENGINE 0x10AEC000
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned int> > >::Get();
	// FUNCTION: ENGINE 0x10AEC020
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListCount<unsigned __int64> >::Get();
	// FUNCTION: ENGINE 0x10AEC040
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListEntry<unsigned __int64> >::Get();
	// FUNCTION: ENGINE 0x10AEC060
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::Get();
	// FUNCTION: ENGINE 0x10AEC080
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListCount<String> >::Get();
	// FUNCTION: ENGINE 0x10AEC0A0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListEntry<String> >::Get();
	// FUNCTION: ENGINE 0x10AEC0C0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<String> > >::Get();
	// FUNCTION: ENGINE 0x10AEC0E0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListCount<Vector> >::Get();
	// FUNCTION: ENGINE 0x10AEC100
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListEntry<Vector> >::Get();
	// FUNCTION: ENGINE 0x10AEC120
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<Vector> > >::Get();
	// FUNCTION: ENGINE 0x10AEC140
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListCount<mgraph::TriggerData> >::Get();
	// FUNCTION: ENGINE 0x10AEC160
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListEntry<mgraph::TriggerData> >::Get();
	// FUNCTION: ENGINE 0x10AEC180
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::Get();
	// FUNCTION: ENGINE 0x10AEC1A0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListCount<Complex> >::Get();
	// FUNCTION: ENGINE 0x10AEC1C0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListEntry<Complex> >::Get();
	// FUNCTION: ENGINE 0x10AEC1E0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<Complex> > >::Get();
	// FUNCTION: ENGINE 0x10AEC200
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListCount<mgraph::EnvelopeData> >::Get();
	// FUNCTION: ENGINE 0x10AEC220
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::ListEntry<mgraph::EnvelopeData> >::Get();
	// FUNCTION: ENGINE 0x10AEC240
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::Get();
	// FUNCTION: ENGINE 0x10AEC8C0
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<String> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC8E0
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<String> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC900
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC920
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC940
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Vector> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC960
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Vector> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC980
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC9A0
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC9C0
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AEC9E0
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECA00
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECA20
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECA40
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Complex> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECA60
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Complex> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECA80
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECAA0
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECAC0
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECAE0
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECB00
	template void* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECB20
	template void* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6D40
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6D60
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6D80
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6DA0
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6DC0
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6DE0
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned int> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6E00
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned int> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6E20
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6E40
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6E60
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6E80
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6EA0
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6EC0
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6EE0
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<String> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6F00
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<String> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6F20
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6F40
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6F60
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<Vector> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6F80
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<Vector> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6FA0
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6FC0
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE6FE0
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7000
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7020
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7040
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7060
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<Complex> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7080
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<Complex> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE70A0
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE70C0
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE70E0
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7100
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7120
	template void* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AE7140
	template void* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECB40
	template void* mgraph::NodeType<mgraph::ListCount<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECB60
	template void* mgraph::NodeType<mgraph::ListEntry<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECB80
	template void* mgraph::NodeType<mgraph::Switch<mgraph::Packet<bool> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECBA0
	template void* mgraph::NodeType<mgraph::ListCount<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECBC0
	template void* mgraph::NodeType<mgraph::ListEntry<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECBE0
	template void* mgraph::NodeType<mgraph::Switch<mgraph::Packet<float> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECC00
	template void* mgraph::NodeType<mgraph::ListCount<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECC20
	template void* mgraph::NodeType<mgraph::ListEntry<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECC40
	template void* mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned int> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECC60
	template void* mgraph::NodeType<mgraph::ListCount<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECC80
	template void* mgraph::NodeType<mgraph::ListEntry<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECCA0
	template void* mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECCC0
	template void* mgraph::NodeType<mgraph::ListCount<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECCE0
	template void* mgraph::NodeType<mgraph::ListEntry<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECD00
	template void* mgraph::NodeType<mgraph::Switch<mgraph::Packet<String> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECD20
	template void* mgraph::NodeType<mgraph::ListCount<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECD40
	template void* mgraph::NodeType<mgraph::ListEntry<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECD60
	template void* mgraph::NodeType<mgraph::Switch<mgraph::Packet<Vector> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECD80
	template void* mgraph::NodeType<mgraph::ListCount<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECDA0
	template void* mgraph::NodeType<mgraph::ListEntry<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECDC0
	template void* mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECDE0
	template void* mgraph::NodeType<mgraph::ListCount<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECE00
	template void* mgraph::NodeType<mgraph::ListEntry<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECE20
	template void* mgraph::NodeType<mgraph::Switch<mgraph::Packet<Complex> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECE40
	template void* mgraph::NodeType<mgraph::ListCount<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECE60
	template void* mgraph::NodeType<mgraph::ListEntry<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AECE80
	template void* mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::operator new(size_t);
}
