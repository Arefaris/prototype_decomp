// The node types of the mgraph library (0x10B00000 - 0x10B2B000): the template instances of NodeType<N> for the node
// classes (constructor, destructor, the reflection of the class and the statics that look up and release it) and the
// allocation of the node classes themselves, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/nodes.h"
#include "code/om/metaclass.h"

#pragma warning(disable: 4661)

const char* mgraph::PropertyNodeBase::AllocationTag()
{
	return "";
}

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B005A0
	template mgraph::NodeType<mgraph::PropertyNodeBase>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B00650
	template void mgraph::NodeType<mgraph::PropertyNodeBase>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B00670
	template void mgraph::NodeType<mgraph::PropertyNodeBase>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B00700
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNodeBase>::GetMetaType();
	// FUNCTION: ENGINE 0x10B00720
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNodeBase>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B00770
	template mgraph::NodeType<mgraph::PropertyNodeBase>::~NodeType();
	// FUNCTION: ENGINE 0x10B00810
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::VectorAdd> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B00840
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::VectorAdd> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B00860
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::VectorAdd> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B00870
	template char const* mgraph::CommutativeMath<mgraph::VectorAdd>::AllocationTag();
	// FUNCTION: ENGINE 0x10B00880
	template void* mgraph::CommutativeMath<mgraph::VectorAdd>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B008A0
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::VectorAdd> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B008C0
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::VectorAdd> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B008E0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::VectorAdd> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B00930
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::VectorAdd> >::~NodeType();
	// FUNCTION: ENGINE 0x10B009D0
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatAdd> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B00A00
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatAdd> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B00A20
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatAdd> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B00A30
	template char const* mgraph::CommutativeMath<mgraph::FloatAdd>::AllocationTag();
	// FUNCTION: ENGINE 0x10B00A40
	template void* mgraph::CommutativeMath<mgraph::FloatAdd>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B00A60
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatAdd> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B00A80
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatAdd> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B00AA0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatAdd> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B00AF0
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatAdd> >::~NodeType();
	// FUNCTION: ENGINE 0x10B00B90
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatMultiply> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B00BC0
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatMultiply> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B00BE0
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatMultiply> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B00BF0
	template char const* mgraph::CommutativeMath<mgraph::FloatMultiply>::AllocationTag();
	// FUNCTION: ENGINE 0x10B00C00
	template void* mgraph::CommutativeMath<mgraph::FloatMultiply>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B00C20
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatMultiply> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B00C40
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatMultiply> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B00C60
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatMultiply> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B00CB0
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatMultiply> >::~NodeType();
	// FUNCTION: ENGINE 0x10B00D50
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolOr> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B00D80
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolOr> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B00DA0
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolOr> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B00DB0
	template char const* mgraph::CommutativeMath<mgraph::BoolOr>::AllocationTag();
	// FUNCTION: ENGINE 0x10B00E30
	template void* mgraph::CommutativeMath<mgraph::BoolOr>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B00E50
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolOr> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B00ED0
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolOr> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B00EF0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolOr> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B00F40
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolOr> >::~NodeType();
	// FUNCTION: ENGINE 0x10B00FE0
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolAnd> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B01010
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolAnd> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B01030
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolAnd> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B01040
	template char const* mgraph::CommutativeMath<mgraph::BoolAnd>::AllocationTag();
	// FUNCTION: ENGINE 0x10B01050
	template void* mgraph::CommutativeMath<mgraph::BoolAnd>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B01070
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolAnd> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B01090
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolAnd> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B010B0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolAnd> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B01100
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolAnd> >::~NodeType();
	// FUNCTION: ENGINE 0x10B011A0
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerAnd> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B011D0
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerAnd> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B01200
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerAnd> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B01210
	template char const* mgraph::CommutativeMath<mgraph::TriggerAnd>::AllocationTag();
	// FUNCTION: ENGINE 0x10B01280
	template void* mgraph::CommutativeMath<mgraph::TriggerAnd>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B012A0
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerAnd> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B01320
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerAnd> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B01340
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerAnd> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B01390
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerAnd> >::~NodeType();
	// FUNCTION: ENGINE 0x10B01430
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerOr> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B01460
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerOr> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B01480
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerOr> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B01490
	template char const* mgraph::CommutativeMath<mgraph::TriggerOr>::AllocationTag();
	// FUNCTION: ENGINE 0x10B014A0
	template void* mgraph::CommutativeMath<mgraph::TriggerOr>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B014C0
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerOr> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B014E0
	template MetaTypeBase* mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerOr> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B01500
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerOr> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B01550
	template mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerOr> >::~NodeType();
	// FUNCTION: ENGINE 0x10B015F0
	template mgraph::NodeType<mgraph::NonCommutativeMath<mgraph::FloatSub> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B01620
	template void mgraph::NodeType<mgraph::NonCommutativeMath<mgraph::FloatSub> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B01640
	template void mgraph::NodeType<mgraph::NonCommutativeMath<mgraph::FloatSub> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B01650
	template char const* mgraph::NonCommutativeMath<mgraph::FloatSub>::AllocationTag();
	// FUNCTION: ENGINE 0x10B01660
	template void* mgraph::NonCommutativeMath<mgraph::FloatSub>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B01680
	template MetaTypeBase* mgraph::NodeType<mgraph::NonCommutativeMath<mgraph::FloatSub> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B016A0
	template MetaTypeBase* mgraph::NodeType<mgraph::NonCommutativeMath<mgraph::FloatSub> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B016C0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::NonCommutativeMath<mgraph::FloatSub> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B01710
	template mgraph::NodeType<mgraph::NonCommutativeMath<mgraph::FloatSub> >::~NodeType();
	// FUNCTION: ENGINE 0x10B017B0
	template mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThan<float> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B017E0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThan<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B01800
	template void mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThan<float> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B01810
	template char const* mgraph::Operator2<mgraph::GreaterThan<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B01820
	template void* mgraph::Operator2<mgraph::GreaterThan<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B01840
	template MetaTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThan<float> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B01860
	template MetaTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThan<float> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B01880
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThan<float> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B018D0
	template mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThan<float> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B01970
	template mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B019A0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B019C0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B019D0
	template char const* mgraph::Operator2<mgraph::GreaterThanOrEqual<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B019E0
	template void* mgraph::Operator2<mgraph::GreaterThanOrEqual<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B01A00
	template MetaTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B01A20
	template MetaTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B01A40
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B01A90
	template mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B01B30
	template mgraph::NodeType<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B01B60
	template void mgraph::NodeType<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B01B80
	template void mgraph::NodeType<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B01B90
	template char const* mgraph::Operator2<mgraph::LessThanOrEqual<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B01BA0
	template void* mgraph::Operator2<mgraph::LessThanOrEqual<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B01BC0
	template MetaTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B01BE0
	template MetaTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B01C00
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B01C50
	template mgraph::NodeType<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B01CF0
	template mgraph::NodeType<mgraph::Operator2<mgraph::LessThan<float> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B01D20
	template void mgraph::NodeType<mgraph::Operator2<mgraph::LessThan<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B01D40
	template void mgraph::NodeType<mgraph::Operator2<mgraph::LessThan<float> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B01D50
	template char const* mgraph::Operator2<mgraph::LessThan<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B01D60
	template void* mgraph::Operator2<mgraph::LessThan<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B01D80
	template MetaTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::LessThan<float> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B01DA0
	template MetaTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::LessThan<float> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B01DC0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Operator2<mgraph::LessThan<float> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B01E10
	template mgraph::NodeType<mgraph::Operator2<mgraph::LessThan<float> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B01EB0
	template mgraph::NodeType<mgraph::Operator2<mgraph::Equal<float> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B01EE0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::Equal<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B01F00
	template void mgraph::NodeType<mgraph::Operator2<mgraph::Equal<float> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B01F10
	template char const* mgraph::Operator2<mgraph::Equal<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B01F20
	template void* mgraph::Operator2<mgraph::Equal<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B01F40
	template MetaTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::Equal<float> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B01F60
	template MetaTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::Equal<float> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B01F80
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Operator2<mgraph::Equal<float> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B01FD0
	template mgraph::NodeType<mgraph::Operator2<mgraph::Equal<float> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B02070
	template mgraph::NodeType<mgraph::Operator2<mgraph::NotEqual<float> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B020A0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::NotEqual<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B020C0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::NotEqual<float> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B020D0
	template char const* mgraph::Operator2<mgraph::NotEqual<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B020E0
	template void* mgraph::Operator2<mgraph::NotEqual<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B02100
	template MetaTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::NotEqual<float> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B02120
	template MetaTypeBase* mgraph::NodeType<mgraph::Operator2<mgraph::NotEqual<float> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B02140
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Operator2<mgraph::NotEqual<float> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B02190
	template mgraph::NodeType<mgraph::Operator2<mgraph::NotEqual<float> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B02230
	template mgraph::NodeType<mgraph::UnaryMath<mgraph::BoolNot> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B02260
	template void mgraph::NodeType<mgraph::UnaryMath<mgraph::BoolNot> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B02280
	template void mgraph::NodeType<mgraph::UnaryMath<mgraph::BoolNot> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B02290
	template char const* mgraph::UnaryMath<mgraph::BoolNot>::AllocationTag();
	// FUNCTION: ENGINE 0x10B022A0
	template void* mgraph::UnaryMath<mgraph::BoolNot>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B022C0
	template MetaTypeBase* mgraph::NodeType<mgraph::UnaryMath<mgraph::BoolNot> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B022E0
	template MetaTypeBase* mgraph::NodeType<mgraph::UnaryMath<mgraph::BoolNot> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B02300
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::UnaryMath<mgraph::BoolNot> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B02350
	template mgraph::NodeType<mgraph::UnaryMath<mgraph::BoolNot> >::~NodeType();
	// FUNCTION: ENGINE 0x10B02FE0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::Destroy();
	// FUNCTION: ENGINE 0x10B03920
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<Complex> > >::Destroy();
	// FUNCTION: ENGINE 0x10B045F0
	template mgraph::NodeType<mgraph::Rand<Vector> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B04620
	template void mgraph::NodeType<mgraph::Rand<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B04640
	template void mgraph::NodeType<mgraph::Rand<Vector> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B04650
	template char const* mgraph::Rand<Vector>::AllocationTag();
	// FUNCTION: ENGINE 0x10B04660
	template void* mgraph::Rand<Vector>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B04680
	template MetaTypeBase* mgraph::NodeType<mgraph::Rand<Vector> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B046A0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Rand<Vector> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B046F0
	template mgraph::NodeType<mgraph::Rand<Vector> >::~NodeType();
	// FUNCTION: ENGINE 0x10B04790
	template mgraph::NodeType<mgraph::Rand<float> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B047C0
	template void mgraph::NodeType<mgraph::Rand<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B047E0
	template void mgraph::NodeType<mgraph::Rand<float> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B047F0
	template char const* mgraph::Rand<float>::AllocationTag();
	// FUNCTION: ENGINE 0x10B04840
	template void* mgraph::Rand<float>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B04860
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Rand<float> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B048D0
	template mgraph::NodeType<mgraph::Rand<float> >::~NodeType();
	// FUNCTION: ENGINE 0x10B04940
	template MetaTypeBase* mgraph::NodeType<mgraph::Rand<float> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B04990
	template mgraph::NodeType<mgraph::Rand<unsigned int> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B049C0
	template void mgraph::NodeType<mgraph::Rand<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B049E0
	template void mgraph::NodeType<mgraph::Rand<unsigned int> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B049F0
	template char const* mgraph::Rand<unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10B04AD0
	template void* mgraph::Rand<unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B04AF0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Rand<unsigned int> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B04BC0
	template mgraph::NodeType<mgraph::Rand<unsigned int> >::~NodeType();
	// FUNCTION: ENGINE 0x10B04C30
	template MetaTypeBase* mgraph::NodeType<mgraph::Rand<unsigned int> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B04C80
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<bool> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B04CC0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<bool> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B04CF0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<bool> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B04D00
	template char const* mgraph::Throw<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B04D50
	template void* mgraph::Throw<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B04D70
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<bool> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B04DF0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<bool> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B04E60
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<bool> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B04EE0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<bool> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B04F10
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<bool> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B04F30
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<bool> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B04F40
	template char const* mgraph::Catch<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B04F50
	template void* mgraph::Catch<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B04F70
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<bool> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B04F90
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<bool> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B04FE0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<bool> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B05080
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B050B0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B05120
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B05130
	template char const* mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B051A0
	template void* mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B051C0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B052E0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B05350
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B055C0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B055F0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B05610
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B05620
	template char const* mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B056A0
	template void* mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B05730
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B05750
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B057A0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B05840
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<float> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B05880
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B058B0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<float> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B058C0
	template char const* mgraph::Throw<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B05910
	template void* mgraph::Throw<mgraph::Packet<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B05930
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<float> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B059B0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<float> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B05A20
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<float> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B05AA0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<float> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B05AD0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B05AF0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<float> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B05B00
	template char const* mgraph::Catch<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B05B10
	template void* mgraph::Catch<mgraph::Packet<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B05B30
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<float> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B05B50
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<float> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B05BA0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<float> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B05C40
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B05C70
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B05CA0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B05CB0
	template char const* mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B05D00
	template void* mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B05D20
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B05DA0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B05E10
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B05ED0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B05EF0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B05F00
	template char const* mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B05F80
	template void* mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B06010
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B06030
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B06080
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B06120
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned int> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B06160
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned int> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B06190
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned int> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B061A0
	template char const* mgraph::Throw<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B061F0
	template void* mgraph::Throw<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B06210
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned int> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B06290
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned int> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B06300
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned int> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B06380
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned int> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B063B0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned int> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B063D0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned int> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B063E0
	template char const* mgraph::Catch<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B063F0
	template void* mgraph::Catch<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B06410
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned int> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B06430
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned int> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B06480
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned int> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B06520
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B06550
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B065C0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B065D0
	template char const* mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B06640
	template void* mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B06660
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B06710
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B06780
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B069F0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B06A20
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B06A40
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B06A50
	template char const* mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B06AD0
	template void* mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B06B60
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B06B80
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B06BD0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B06C70
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B06CA0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B06CD0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B06CE0
	template char const* mgraph::Throw<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B06D50
	template void* mgraph::Throw<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B06D70
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B06DF0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B06E60
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B06EE0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B06F10
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B06F30
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B07060
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B07080
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B070D0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B07170
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B071A0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B07210
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B07220
	template char const* mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B07290
	template void* mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B072B0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B073D0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B07440
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B076C0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B076F0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B07710
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B07720
	template char const* mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B077A0
	template void* mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B07830
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B07850
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B078A0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B07940
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<String> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B07970
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<String> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B079A0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<String> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B079B0
	template char const* mgraph::Throw<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B07A30
	template void* mgraph::Throw<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B07A50
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<String> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B07AE0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<String> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B07B50
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<String> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B07BF0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<String> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B07C20
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<String> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B07C40
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<String> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B07C50
	template char const* mgraph::Catch<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B07CE0
	template void* mgraph::Catch<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B07D70
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<String> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B07D90
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<String> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B07DE0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<String> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B07E80
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B07EB0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B07F20
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B07F30
	template char const* mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B07FA0
	template void* mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B07FC0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B08070
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B080E0
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B08330
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B08360
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B08380
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B08390
	template char const* mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B08410
	template void* mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B084A0
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B084C0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B08510
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B085B0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<Vector> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B085F0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<Vector> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B08620
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<Vector> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B08630
	template char const* mgraph::Throw<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B08690
	template void* mgraph::Throw<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B086B0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<Vector> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B08730
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<Vector> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B087A0
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<Vector> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B08820
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<Vector> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B08850
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<Vector> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B08870
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<Vector> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B08880
	template char const* mgraph::Catch<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B08890
	template void* mgraph::Catch<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B088B0
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<Vector> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B088D0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<Vector> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B08920
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<Vector> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B089C0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B089F0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B08A60
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B08A70
	template char const* mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B08AE0
	template void* mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B08B00
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B08C20
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B08C90
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B08F10
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B08F40
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B08F60
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B08F70
	template char const* mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B08FF0
	template void* mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B09080
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B090A0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B090F0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B09190
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B091D0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B09200
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B09210
	template char const* mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B09260
	template void* mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B09280
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B09300
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B09370
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B093F0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B09420
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B09440
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B09450
	template char const* mgraph::Catch<mgraph::Packet<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B09460
	template void* mgraph::Catch<mgraph::Packet<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B09480
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B094A0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B094F0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B097A0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B097D0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B09840
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B09850
	template char const* mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B098C0
	template void* mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B098E0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B09A00
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B09A70
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B09CE0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B09D10
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B09D30
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B09D40
	template char const* mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B09DC0
	template void* mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B09E50
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B09E70
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B09EC0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B09F60
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<Complex> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B09F90
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<Complex> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B09FC0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<Complex> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B09FD0
	template char const* mgraph::Throw<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0A030
	template void* mgraph::Throw<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0A050
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<Complex> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B0A0D0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<Complex> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B0A140
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<Complex> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B0A1C0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<Complex> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B0A1F0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<Complex> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0A210
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<Complex> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B0A330
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<Complex> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B0A350
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<Complex> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B0A3A0
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<Complex> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B0A440
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B0A470
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0A4E0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B0A4F0
	template char const* mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0A560
	template void* mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0A580
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B0A6A0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B0A710
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B0A990
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B0A9C0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0A9E0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B0A9F0
	template char const* mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0AA70
	template void* mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0AB00
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B0AB20
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B0AB70
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B0AC10
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B0AC40
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0AC70
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B0AC80
	template char const* mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0ACE0
	template void* mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0AD00
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B0AD50
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B0ADC0
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B0AE50
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B0AE80
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0AEA0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B0AEB0
	template char const* mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0AF40
	template void* mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0AFD0
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B0AFF0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B0B040
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B0B0E0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B0B110
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0B180
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B0B190
	template char const* mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0B200
	template void* mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0B220
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B0B2D0
	template mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B0B340
	template MetaTypeBase* mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B0B390
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B0B3C0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B0B3E0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B0B3F0
	template char const* mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0B470
	template void* mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B0B500
	template MetaTypeBase* mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B0B520
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B0B570
	template mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B12B90
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<bool> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B12BC0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<bool> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B12BE0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<bool> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B12BF0
	template char const* mgraph::PropertyNode<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B12C40
	template void* mgraph::PropertyNode<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B12C80
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<bool> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B12CA0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<bool> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B12CF0
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<bool> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B12D90
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B12DC0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B12DE0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B12DF0
	template char const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B12E50
	template void* mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B12EC0
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B12EE0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B12F70
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B13010
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<float> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B13040
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B13060
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<float> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B13070
	template char const* mgraph::PropertyNode<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B130C0
	template void* mgraph::PropertyNode<mgraph::Packet<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B13100
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<float> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B13120
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<float> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B13170
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<float> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B13210
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B13240
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B13260
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B13270
	template char const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B132D0
	template void* mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B13350
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B13370
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B13400
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B134A0
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B134D0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B134F0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B13500
	template char const* mgraph::PropertyNode<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B13550
	template void* mgraph::PropertyNode<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B13590
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B135B0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B13600
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B14130
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B14160
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B14180
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B14190
	template char const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B141F0
	template void* mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B14270
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B14290
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B14320
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B143C0
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B143F0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B14410
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B14420
	template char const* mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B14470
	template void* mgraph::PropertyNode<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B144B0
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B144D0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B14520
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B150B0
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B150E0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B15100
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B15110
	template char const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B15170
	template void* mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B151F0
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B15210
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B152A0
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B15340
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<String> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B15370
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<String> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B15390
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<String> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B153A0
	template char const* mgraph::PropertyNode<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B15410
	template void* mgraph::PropertyNode<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B15460
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<String> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B15480
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<String> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B15500
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<String> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B155A0
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B155D0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B155F0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B15600
	template char const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B15660
	template void* mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B156C0
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B156E0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B15790
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B15830
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Vector> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B15860
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Vector> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B15880
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Vector> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B15890
	template char const* mgraph::PropertyNode<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B158E0
	template void* mgraph::PropertyNode<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B15920
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Vector> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B15940
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Vector> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B15990
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Vector> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B15A30
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B15A60
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B15A80
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B15A90
	template char const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B15AF0
	template void* mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B15B70
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B15B90
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B15C20
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B15CC0
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B15CF0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B15D10
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B15D20
	template char const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B15D80
	template void* mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B15DF0
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B15E10
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B15EA0
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B15F40
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Complex> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B15F70
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Complex> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B15F90
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Complex> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B15FA0
	template char const* mgraph::PropertyNode<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B15FF0
	template void* mgraph::PropertyNode<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B16030
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Complex> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B16050
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Complex> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B160A0
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Complex> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B16C90
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B16CC0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B16CE0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B16CF0
	template char const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B16D50
	template void* mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B16DD0
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B16DF0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B16E80
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B16F20
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B16F50
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B16F70
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B16F80
	template char const* mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B16FF0
	template void* mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B170A0
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B170C0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B17160
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B17200
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B17230
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B17250
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B17260
	template char const* mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B172C0
	template void* mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B172E0
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B17300
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B17350
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B17420
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<bool> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B175A0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<bool> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B175B0
	template char const* mgraph::Inlet<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B175D0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<bool> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B176B0
	template void* mgraph::Inlet<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B176D0
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<bool> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B17C40
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<bool> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B17C60
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<bool> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B17D50
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<bool> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B17DF0
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<bool> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B17E20
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<bool> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B17E40
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<bool> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B17E50
	template char const* mgraph::Outlet<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B17E60
	template void* mgraph::Outlet<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B17E80
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<bool> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B18230
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<bool> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B18250
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<bool> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B182A0
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<bool> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B18340
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B18440
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B18450
	template char const* mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B18470
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B18580
	template void* mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B185A0
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B18AD0
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B18AF0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B18BE0
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B18C80
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B18CB0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B18CD0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B18CE0
	template char const* mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B18CF0
	template void* mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B18D10
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B190A0
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B190C0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B19110
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B191B0
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<float> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B192E0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<float> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B192F0
	template char const* mgraph::Inlet<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B19310
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B193F0
	template void* mgraph::Inlet<mgraph::Packet<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B19410
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<float> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B19940
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<float> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B19960
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<float> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B19A50
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<float> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B19AF0
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<float> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B19B20
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B19B40
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<float> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B19B50
	template char const* mgraph::Outlet<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B19B60
	template void* mgraph::Outlet<mgraph::Packet<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B19B80
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<float> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B19F10
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<float> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B19F30
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<float> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B19F80
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<float> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B1A020
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1A120
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B1A130
	template char const* mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1A150
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1A260
	template void* mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1A280
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B1A7B0
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B1A7D0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B1A8C0
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B1A960
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1A990
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1A9B0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B1A9C0
	template char const* mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1A9D0
	template void* mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1A9F0
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B1AD80
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B1ADA0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B1ADF0
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B1AE90
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned int> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1AF90
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned int> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B1AFA0
	template char const* mgraph::Inlet<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1AFC0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned int> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1B0D0
	template void* mgraph::Inlet<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1B0F0
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned int> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B1B620
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned int> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B1B640
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned int> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B1B730
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned int> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B1B7D0
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned int> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1B800
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned int> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1B820
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned int> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B1B830
	template char const* mgraph::Outlet<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1B840
	template void* mgraph::Outlet<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1B860
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned int> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B1BBF0
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned int> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B1BC10
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned int> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B1BC60
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned int> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B1BD00
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1BE00
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B1BE10
	template char const* mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1BE30
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1BF40
	template void* mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1BF60
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B1C490
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B1C4B0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B1C5A0
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B1C640
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1C670
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1C690
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B1C6A0
	template char const* mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1C6B0
	template void* mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1C6D0
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B1CA60
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B1CA80
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B1CAD0
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B1CB70
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1CC70
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B1CC80
	template char const* mgraph::Inlet<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1CCA0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1CDB0
	template void* mgraph::Inlet<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1CDD0
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B1D300
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B1D320
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B1D410
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B1D4B0
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1D4E0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1D500
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B1D510
	template char const* mgraph::Outlet<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1D520
	template void* mgraph::Outlet<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1D540
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B1D8D0
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B1D8F0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B1D940
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B1D9E0
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1DAE0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B1DAF0
	template char const* mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1DB10
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1DC20
	template void* mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1DC40
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B1E170
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B1E190
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B1E280
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B1E320
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1E350
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1E370
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B1E380
	template char const* mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1E390
	template void* mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1E3B0
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B1E740
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B1E760
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B1E7B0
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B1E850
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<String> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1E950
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<String> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B1E960
	template char const* mgraph::Inlet<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1E980
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<String> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1EA90
	template void* mgraph::Inlet<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1EAB0
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<String> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B1EFE0
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<String> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B1F000
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<String> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B1F0F0
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<String> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B1F190
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<String> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1F1C0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<String> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1F1E0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<String> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B1F1F0
	template char const* mgraph::Outlet<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1F200
	template void* mgraph::Outlet<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1F220
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<String> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B1F5B0
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<String> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B1F5D0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<String> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B1F620
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<String> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B1F6C0
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B1F7C0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B1F7D0
	template char const* mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B1F7F0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B1F900
	template void* mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B1F920
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B1FE50
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B1FE70
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B1FF60
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B20000
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B20030
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B20050
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B20060
	template char const* mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B20070
	template void* mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B20090
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B20420
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B20440
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B20490
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B20530
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Vector> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B206A0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Vector> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B206B0
	template char const* mgraph::Inlet<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B206D0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Vector> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B207B0
	template void* mgraph::Inlet<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B207D0
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Vector> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B20D00
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Vector> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B20D20
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Vector> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B20E10
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Vector> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B20EB0
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Vector> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B20EE0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Vector> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B20F00
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Vector> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B20F10
	template char const* mgraph::Outlet<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B20F20
	template void* mgraph::Outlet<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B20F40
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Vector> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B212D0
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Vector> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B212F0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Vector> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B21340
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Vector> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B213E0
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B214E0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B214F0
	template char const* mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B21510
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B21620
	template void* mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B21640
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B21B70
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B21B90
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B21C80
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B21D20
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B21D50
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B21D70
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B21D80
	template char const* mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B21D90
	template void* mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B21DB0
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B22140
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B22160
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B221B0
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B22250
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B223A0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B223B0
	template char const* mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B223D0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B224B0
	template void* mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B224D0
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B22A00
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B22A20
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B22B10
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B22BB0
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B22BE0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B22C00
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B22C10
	template char const* mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B22C20
	template void* mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B22C40
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B22FD0
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B22FF0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B23040
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B230E0
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B231E0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B231F0
	template char const* mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B23210
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B23320
	template void* mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B23340
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B23870
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B23890
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B23980
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B23A20
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B23A50
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B23A70
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B23A80
	template char const* mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B23A90
	template void* mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B23AB0
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B23E40
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B23E60
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B23EB0
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B23F50
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Complex> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B24050
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Complex> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B24060
	template char const* mgraph::Inlet<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B24080
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Complex> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B24190
	template void* mgraph::Inlet<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B241B0
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Complex> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B246E0
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Complex> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B24700
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Complex> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B247F0
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Complex> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B24890
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Complex> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B248C0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Complex> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B248E0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Complex> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B248F0
	template char const* mgraph::Outlet<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B24900
	template void* mgraph::Outlet<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B24920
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Complex> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B24CB0
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Complex> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B24CD0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Complex> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B24D20
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Complex> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B24DC0
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B24EC0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B24ED0
	template char const* mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B24EF0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B25000
	template void* mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B25020
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B25550
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B25570
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B25660
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B25700
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B25730
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B25750
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B25760
	template char const* mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B25770
	template void* mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B25790
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B25B20
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B25B40
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B25B90
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B25C30
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B25D30
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B25D40
	template char const* mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B25D60
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B25E70
	template void* mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B25E90
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B263C0
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B263E0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B264D0
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B26570
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B265A0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B265C0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B265D0
	template char const* mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B265E0
	template void* mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B26600
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B26990
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B269B0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B26A00
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B26AA0
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B26BC0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B26BD0
	template char const* mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B26D20
	template void* mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B26D40
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B27270
	template MetaTypeBase* mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B27290
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B27380
	template mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B27420
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B27450
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B27470
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B27480
	template char const* mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B27490
	template void* mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B274B0
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B27840
	template MetaTypeBase* mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B27860
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B278B0
	template mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::~NodeType();
	// FUNCTION: ENGINE 0x10B27950
	template mgraph::NodeType<mgraph::ListCount<bool> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B27980
	template void mgraph::NodeType<mgraph::ListCount<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B279A0
	template void mgraph::NodeType<mgraph::ListCount<bool> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B279B0
	template char const* mgraph::ListCount<bool>::AllocationTag();
	// FUNCTION: ENGINE 0x10B279C0
	template void* mgraph::ListCount<bool>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B279E0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<bool> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B27A00
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<bool> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B27A20
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListCount<bool> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B27A70
	template mgraph::NodeType<mgraph::ListCount<bool> >::~NodeType();
	// FUNCTION: ENGINE 0x10B27B10
	template mgraph::NodeType<mgraph::ListEntry<bool> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B27B40
	template void mgraph::NodeType<mgraph::ListEntry<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B27B60
	template void mgraph::NodeType<mgraph::ListEntry<bool> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B27B70
	template char const* mgraph::ListEntry<bool>::AllocationTag();
	// FUNCTION: ENGINE 0x10B27B80
	template void* mgraph::ListEntry<bool>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B27BA0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<bool> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B27BC0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<bool> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B27BE0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListEntry<bool> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B27C30
	template mgraph::NodeType<mgraph::ListEntry<bool> >::~NodeType();
	// FUNCTION: ENGINE 0x10B27CD0
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<bool> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B27D00
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<bool> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B27D20
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<bool> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B27D30
	template char const* mgraph::Switch<mgraph::Packet<bool> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B27D80
	template void* mgraph::Switch<mgraph::Packet<bool> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B27DA0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<bool> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B27E10
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<bool> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B27E80
	template MetaTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<bool> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B27ED0
	template mgraph::NodeType<mgraph::ListCount<float> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B27F00
	template void mgraph::NodeType<mgraph::ListCount<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B27F20
	template void mgraph::NodeType<mgraph::ListCount<float> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B27F30
	template char const* mgraph::ListCount<float>::AllocationTag();
	// FUNCTION: ENGINE 0x10B27F40
	template void* mgraph::ListCount<float>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B27F60
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<float> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B27F80
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<float> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B27FA0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListCount<float> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B27FF0
	template mgraph::NodeType<mgraph::ListCount<float> >::~NodeType();
	// FUNCTION: ENGINE 0x10B28090
	template mgraph::NodeType<mgraph::ListEntry<float> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B280C0
	template void mgraph::NodeType<mgraph::ListEntry<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B280E0
	template void mgraph::NodeType<mgraph::ListEntry<float> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B280F0
	template char const* mgraph::ListEntry<float>::AllocationTag();
	// FUNCTION: ENGINE 0x10B28100
	template void* mgraph::ListEntry<float>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B28120
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<float> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B28140
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<float> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B28160
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListEntry<float> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B281B0
	template mgraph::NodeType<mgraph::ListEntry<float> >::~NodeType();
	// FUNCTION: ENGINE 0x10B28250
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<float> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B28280
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<float> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B282A0
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<float> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B282B0
	template char const* mgraph::Switch<mgraph::Packet<float> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B28300
	template void* mgraph::Switch<mgraph::Packet<float> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B28320
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<float> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B28390
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<float> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B28400
	template MetaTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<float> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B28450
	template mgraph::NodeType<mgraph::ListCount<unsigned int> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B28480
	template void mgraph::NodeType<mgraph::ListCount<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B284A0
	template void mgraph::NodeType<mgraph::ListCount<unsigned int> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B284B0
	template char const* mgraph::ListCount<unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10B284C0
	template void* mgraph::ListCount<unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B284E0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<unsigned int> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B28500
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<unsigned int> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B28520
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListCount<unsigned int> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B28570
	template mgraph::NodeType<mgraph::ListCount<unsigned int> >::~NodeType();
	// FUNCTION: ENGINE 0x10B28610
	template mgraph::NodeType<mgraph::ListEntry<unsigned int> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B28640
	template void mgraph::NodeType<mgraph::ListEntry<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B28660
	template void mgraph::NodeType<mgraph::ListEntry<unsigned int> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B28670
	template char const* mgraph::ListEntry<unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10B28680
	template void* mgraph::ListEntry<unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B286A0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<unsigned int> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B286C0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<unsigned int> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B286E0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListEntry<unsigned int> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B28730
	template mgraph::NodeType<mgraph::ListEntry<unsigned int> >::~NodeType();
	// FUNCTION: ENGINE 0x10B287D0
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned int> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B28800
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned int> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B28820
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned int> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B28830
	template char const* mgraph::Switch<mgraph::Packet<unsigned int> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B28880
	template void* mgraph::Switch<mgraph::Packet<unsigned int> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B288A0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned int> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B28910
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned int> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B28980
	template MetaTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned int> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B289D0
	template mgraph::NodeType<mgraph::ListCount<unsigned __int64> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B28A00
	template void mgraph::NodeType<mgraph::ListCount<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B28A20
	template void mgraph::NodeType<mgraph::ListCount<unsigned __int64> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B28A30
	template char const* mgraph::ListCount<unsigned __int64>::AllocationTag();
	// FUNCTION: ENGINE 0x10B28A40
	template void* mgraph::ListCount<unsigned __int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B28A60
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<unsigned __int64> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B28A80
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<unsigned __int64> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B28AA0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListCount<unsigned __int64> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B28AF0
	template mgraph::NodeType<mgraph::ListCount<unsigned __int64> >::~NodeType();
	// FUNCTION: ENGINE 0x10B28B90
	template mgraph::NodeType<mgraph::ListEntry<unsigned __int64> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B28BC0
	template void mgraph::NodeType<mgraph::ListEntry<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B28BE0
	template void mgraph::NodeType<mgraph::ListEntry<unsigned __int64> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B28BF0
	template char const* mgraph::ListEntry<unsigned __int64>::AllocationTag();
	// FUNCTION: ENGINE 0x10B28C00
	template void* mgraph::ListEntry<unsigned __int64>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B28C20
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<unsigned __int64> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B28C40
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<unsigned __int64> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B28C60
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListEntry<unsigned __int64> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B28CB0
	template mgraph::NodeType<mgraph::ListEntry<unsigned __int64> >::~NodeType();
	// FUNCTION: ENGINE 0x10B28D50
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B28D80
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B28DA0
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B28DB0
	template char const* mgraph::Switch<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B28E00
	template void* mgraph::Switch<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B28E20
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B28E90
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B28F00
	template MetaTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B28F50
	template mgraph::NodeType<mgraph::ListCount<String> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B28F80
	template void mgraph::NodeType<mgraph::ListCount<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B28FA0
	template void mgraph::NodeType<mgraph::ListCount<String> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B28FB0
	template char const* mgraph::ListCount<String>::AllocationTag();
	// FUNCTION: ENGINE 0x10B28FC0
	template void* mgraph::ListCount<String>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B28FE0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<String> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B29000
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<String> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B29020
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListCount<String> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B29070
	template mgraph::NodeType<mgraph::ListCount<String> >::~NodeType();
	// FUNCTION: ENGINE 0x10B29110
	template mgraph::NodeType<mgraph::ListEntry<String> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B29140
	template void mgraph::NodeType<mgraph::ListEntry<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B29160
	template void mgraph::NodeType<mgraph::ListEntry<String> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B29170
	template char const* mgraph::ListEntry<String>::AllocationTag();
	// FUNCTION: ENGINE 0x10B29180
	template void* mgraph::ListEntry<String>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B291A0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<String> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B291C0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<String> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B291E0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListEntry<String> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B29230
	template mgraph::NodeType<mgraph::ListEntry<String> >::~NodeType();
	// FUNCTION: ENGINE 0x10B292D0
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<String> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B29300
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<String> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B29320
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<String> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B29330
	template char const* mgraph::Switch<mgraph::Packet<String> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B29380
	template void* mgraph::Switch<mgraph::Packet<String> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B293A0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<String> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B29410
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<String> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B29480
	template MetaTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<String> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B294D0
	template mgraph::NodeType<mgraph::ListCount<Vector> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B29500
	template void mgraph::NodeType<mgraph::ListCount<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B29520
	template void mgraph::NodeType<mgraph::ListCount<Vector> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B29530
	template char const* mgraph::ListCount<Vector>::AllocationTag();
	// FUNCTION: ENGINE 0x10B29540
	template void* mgraph::ListCount<Vector>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B29560
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<Vector> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B29580
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<Vector> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B295A0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListCount<Vector> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B295F0
	template mgraph::NodeType<mgraph::ListCount<Vector> >::~NodeType();
	// FUNCTION: ENGINE 0x10B29690
	template mgraph::NodeType<mgraph::ListEntry<Vector> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B296C0
	template void mgraph::NodeType<mgraph::ListEntry<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B296E0
	template void mgraph::NodeType<mgraph::ListEntry<Vector> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B296F0
	template char const* mgraph::ListEntry<Vector>::AllocationTag();
	// FUNCTION: ENGINE 0x10B29700
	template void* mgraph::ListEntry<Vector>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B29720
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<Vector> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B29740
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<Vector> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B29760
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListEntry<Vector> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B297B0
	template mgraph::NodeType<mgraph::ListEntry<Vector> >::~NodeType();
	// FUNCTION: ENGINE 0x10B29850
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<Vector> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B29880
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<Vector> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B298A0
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<Vector> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B298B0
	template char const* mgraph::Switch<mgraph::Packet<Vector> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B29900
	template void* mgraph::Switch<mgraph::Packet<Vector> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B29920
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<Vector> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B29990
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<Vector> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B29A00
	template MetaTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<Vector> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B29A50
	template mgraph::NodeType<mgraph::ListCount<mgraph::TriggerData> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B29A80
	template void mgraph::NodeType<mgraph::ListCount<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B29AA0
	template void mgraph::NodeType<mgraph::ListCount<mgraph::TriggerData> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B29AB0
	template char const* mgraph::ListCount<mgraph::TriggerData>::AllocationTag();
	// FUNCTION: ENGINE 0x10B29AC0
	template void* mgraph::ListCount<mgraph::TriggerData>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B29AE0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<mgraph::TriggerData> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B29B00
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<mgraph::TriggerData> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B29B20
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListCount<mgraph::TriggerData> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B29B70
	template mgraph::NodeType<mgraph::ListCount<mgraph::TriggerData> >::~NodeType();
	// FUNCTION: ENGINE 0x10B29C10
	template mgraph::NodeType<mgraph::ListEntry<mgraph::TriggerData> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B29C40
	template void mgraph::NodeType<mgraph::ListEntry<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B29C60
	template void mgraph::NodeType<mgraph::ListEntry<mgraph::TriggerData> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B29C70
	template char const* mgraph::ListEntry<mgraph::TriggerData>::AllocationTag();
	// FUNCTION: ENGINE 0x10B29C80
	template void* mgraph::ListEntry<mgraph::TriggerData>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B29CA0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<mgraph::TriggerData> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B29CC0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<mgraph::TriggerData> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B29CE0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListEntry<mgraph::TriggerData> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B29D30
	template mgraph::NodeType<mgraph::ListEntry<mgraph::TriggerData> >::~NodeType();
	// FUNCTION: ENGINE 0x10B29DD0
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B29E00
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B29E20
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B29E30
	template char const* mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B29E80
	template void* mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B29EA0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B29F10
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B29F80
	template MetaTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B29FD0
	template mgraph::NodeType<mgraph::ListCount<Complex> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2A000
	template void mgraph::NodeType<mgraph::ListCount<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2A020
	template void mgraph::NodeType<mgraph::ListCount<Complex> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B2A030
	template char const* mgraph::ListCount<Complex>::AllocationTag();
	// FUNCTION: ENGINE 0x10B2A040
	template void* mgraph::ListCount<Complex>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B2A060
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<Complex> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B2A080
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<Complex> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B2A0A0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListCount<Complex> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B2A0F0
	template mgraph::NodeType<mgraph::ListCount<Complex> >::~NodeType();
	// FUNCTION: ENGINE 0x10B2A190
	template mgraph::NodeType<mgraph::ListEntry<Complex> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2A1C0
	template void mgraph::NodeType<mgraph::ListEntry<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2A1E0
	template void mgraph::NodeType<mgraph::ListEntry<Complex> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B2A1F0
	template char const* mgraph::ListEntry<Complex>::AllocationTag();
	// FUNCTION: ENGINE 0x10B2A200
	template void* mgraph::ListEntry<Complex>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B2A220
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<Complex> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B2A240
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<Complex> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B2A260
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListEntry<Complex> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B2A2B0
	template mgraph::NodeType<mgraph::ListEntry<Complex> >::~NodeType();
	// FUNCTION: ENGINE 0x10B2A350
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<Complex> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2A380
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<Complex> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2A3A0
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<Complex> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B2A3B0
	template char const* mgraph::Switch<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B2A400
	template void* mgraph::Switch<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B2A420
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<Complex> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B2A490
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<Complex> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B2A500
	template MetaTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<Complex> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B2A550
	template mgraph::NodeType<mgraph::ListCount<mgraph::EnvelopeData> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2A580
	template void mgraph::NodeType<mgraph::ListCount<mgraph::EnvelopeData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2A5A0
	template void mgraph::NodeType<mgraph::ListCount<mgraph::EnvelopeData> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B2A5B0
	template char const* mgraph::ListCount<mgraph::EnvelopeData>::AllocationTag();
	// FUNCTION: ENGINE 0x10B2A5C0
	template void* mgraph::ListCount<mgraph::EnvelopeData>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B2A5E0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<mgraph::EnvelopeData> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B2A600
	template MetaTypeBase* mgraph::NodeType<mgraph::ListCount<mgraph::EnvelopeData> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B2A620
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListCount<mgraph::EnvelopeData> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B2A670
	template mgraph::NodeType<mgraph::ListCount<mgraph::EnvelopeData> >::~NodeType();
	// FUNCTION: ENGINE 0x10B2A710
	template mgraph::NodeType<mgraph::ListEntry<mgraph::EnvelopeData> >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2A740
	template void mgraph::NodeType<mgraph::ListEntry<mgraph::EnvelopeData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2A760
	template void mgraph::NodeType<mgraph::ListEntry<mgraph::EnvelopeData> >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B2A770
	template char const* mgraph::ListEntry<mgraph::EnvelopeData>::AllocationTag();
	// FUNCTION: ENGINE 0x10B2A780
	template void* mgraph::ListEntry<mgraph::EnvelopeData>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B2A7A0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<mgraph::EnvelopeData> >::FindMetaType();
	// FUNCTION: ENGINE 0x10B2A7C0
	template MetaTypeBase* mgraph::NodeType<mgraph::ListEntry<mgraph::EnvelopeData> >::GetMetaType();
	// FUNCTION: ENGINE 0x10B2A7E0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::ListEntry<mgraph::EnvelopeData> >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B2A830
	template mgraph::NodeType<mgraph::ListEntry<mgraph::EnvelopeData> >::~NodeType();
	// FUNCTION: ENGINE 0x10B2A8D0
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2A900
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2A920
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B2A930
	template char const* mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B2A980
	template void* mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B2A9A0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B2AA10
	template mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B2AA80
	template MetaTypeBase* mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B2F180
	template void mgraph::NodeType<mgraph::PropertyNodeBase>::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2FE10
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::VectorAdd> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2FE60
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatAdd> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2FEB0
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatMultiply> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2FF00
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolOr> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2FF50
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolAnd> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2FFA0
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerAnd> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2FFF0
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerOr> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B30040
	template void mgraph::NodeType<mgraph::NonCommutativeMath<mgraph::FloatSub> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B30090
	template void mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThan<float> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B300E0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B30130
	template void mgraph::NodeType<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B30180
	template void mgraph::NodeType<mgraph::Operator2<mgraph::LessThan<float> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B301D0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::Equal<float> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B30220
	template void mgraph::NodeType<mgraph::Operator2<mgraph::NotEqual<float> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B30270
	template void mgraph::NodeType<mgraph::UnaryMath<mgraph::BoolNot> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B327F0
	template void mgraph::NodeType<mgraph::Rand<Vector> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B32840
	template void mgraph::NodeType<mgraph::Rand<float> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B32890
	template void mgraph::NodeType<mgraph::Rand<unsigned int> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B369A0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<bool> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B369F0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<bool> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36A40
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36A90
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36AE0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<float> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36B30
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<float> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36B80
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36BD0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36C20
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned int> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36C70
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned int> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36CC0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36D10
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36D60
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36DB0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36E00
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36E50
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36EA0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<String> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36EF0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<String> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36F40
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36F90
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36FE0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<Vector> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B37030
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<Vector> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B37080
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B370D0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B37120
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B37170
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B371C0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B37210
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B37260
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<Complex> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B372B0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<Complex> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B37300
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B37350
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B373A0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B373F0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B37440
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B37490
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43120
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<bool> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43170
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B431C0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<float> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43210
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43260
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B432B0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43300
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43350
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B433A0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<String> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B433F0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43440
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Vector> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43490
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B434E0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43530
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Complex> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43580
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B435D0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43620
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43670
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<bool> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B436C0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<bool> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43710
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43760
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B437B0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<float> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43800
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<float> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43850
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B438A0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B438F0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned int> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43940
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned int> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43990
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B439E0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43A30
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43A80
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43AD0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43B20
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43B70
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<String> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43BC0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<String> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43C10
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43C60
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43CB0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Vector> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43D00
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Vector> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43D50
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43DA0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43DF0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43E40
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43E90
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43EE0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43F30
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Complex> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43F80
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Complex> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B43FD0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44020
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44070
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B440C0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44110
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44160
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B441B0
	template void mgraph::NodeType<mgraph::ListCount<bool> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44200
	template void mgraph::NodeType<mgraph::ListEntry<bool> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44250
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<bool> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B442A0
	template void mgraph::NodeType<mgraph::ListCount<float> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B442F0
	template void mgraph::NodeType<mgraph::ListEntry<float> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44340
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<float> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44390
	template void mgraph::NodeType<mgraph::ListCount<unsigned int> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B443E0
	template void mgraph::NodeType<mgraph::ListEntry<unsigned int> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44430
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned int> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44480
	template void mgraph::NodeType<mgraph::ListCount<unsigned __int64> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B444D0
	template void mgraph::NodeType<mgraph::ListEntry<unsigned __int64> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44520
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44570
	template void mgraph::NodeType<mgraph::ListCount<String> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B445C0
	template void mgraph::NodeType<mgraph::ListEntry<String> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44610
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<String> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44660
	template void mgraph::NodeType<mgraph::ListCount<Vector> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B446B0
	template void mgraph::NodeType<mgraph::ListEntry<Vector> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44700
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<Vector> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44750
	template void mgraph::NodeType<mgraph::ListCount<mgraph::TriggerData> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B447A0
	template void mgraph::NodeType<mgraph::ListEntry<mgraph::TriggerData> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B447F0
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44840
	template void mgraph::NodeType<mgraph::ListCount<Complex> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44890
	template void mgraph::NodeType<mgraph::ListEntry<Complex> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B448E0
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<Complex> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44930
	template void mgraph::NodeType<mgraph::ListCount<mgraph::EnvelopeData> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44980
	template void mgraph::NodeType<mgraph::ListEntry<mgraph::EnvelopeData> >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B449D0
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B49560
	template void mgraph::NodeType<mgraph::PropertyNodeBase>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B49670
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::VectorAdd> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B496C0
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatAdd> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B49710
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::FloatMultiply> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B49760
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolOr> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B497B0
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::BoolAnd> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B49830
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerAnd> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B498B0
	template void mgraph::NodeType<mgraph::CommutativeMath<mgraph::TriggerOr> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B49900
	template void mgraph::NodeType<mgraph::NonCommutativeMath<mgraph::FloatSub> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B49950
	template void mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThan<float> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B499A0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B499F0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B49A40
	template void mgraph::NodeType<mgraph::Operator2<mgraph::LessThan<float> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B49A90
	template void mgraph::NodeType<mgraph::Operator2<mgraph::Equal<float> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B49AE0
	template void mgraph::NodeType<mgraph::Operator2<mgraph::NotEqual<float> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B49B30
	template void mgraph::NodeType<mgraph::UnaryMath<mgraph::BoolNot> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4CD60
	template void mgraph::NodeType<mgraph::Rand<Vector> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D320
	template void mgraph::NodeType<mgraph::Rand<float> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D3A0
	template void mgraph::NodeType<mgraph::Rand<unsigned int> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D460
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<bool> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D4E0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<bool> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D530
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D5B0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D630
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<float> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D6B0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<float> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D700
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D780
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D800
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned int> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D880
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned int> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D8D0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D950
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4D9D0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DA50
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DAA0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DB20
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DBA0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<String> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DC20
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<String> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DC70
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DCF0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DD70
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<Vector> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DDF0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<Vector> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DE40
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DEC0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DF40
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DF90
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4DFE0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4E060
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4E0E0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<Complex> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4E160
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<Complex> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4E1B0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4E230
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4E2C0
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4E310
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4E360
	template void mgraph::NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B4E3B0
	template void mgraph::NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B50C80
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<bool> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B50CD0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B50D20
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<float> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B50D70
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<float,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B50DC0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned int> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B50E10
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B50E60
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<unsigned __int64> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B50EB0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B50F00
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<String> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B50F50
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<String,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B50FA0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Vector> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B50FF0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51040
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51090
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<Complex> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B510E0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51130
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::EnvelopeData> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51180
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B511D0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<bool> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51220
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<bool> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51270
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B512C0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51310
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<float> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51360
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<float> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B513B0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51400
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<float,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51450
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned int> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B514A0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned int> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B514F0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51540
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51590
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B515E0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51630
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51680
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B516D0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<String> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51720
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<String> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51770
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B517C0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<String,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51810
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Vector> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51860
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Vector> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B518B0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51900
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51950
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B519A0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B519F0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51A40
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51A90
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<Complex> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51AE0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<Complex> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51B30
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51B80
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51BD0
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51C20
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51C70
	template void mgraph::NodeType<mgraph::Inlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51CC0
	template void mgraph::NodeType<mgraph::Outlet<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51D10
	template void mgraph::NodeType<mgraph::ListCount<bool> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51D90
	template void mgraph::NodeType<mgraph::ListEntry<bool> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51DE0
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<bool> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51E30
	template void mgraph::NodeType<mgraph::ListCount<float> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51EB0
	template void mgraph::NodeType<mgraph::ListEntry<float> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51F00
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<float> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51F50
	template void mgraph::NodeType<mgraph::ListCount<unsigned int> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B51FA0
	template void mgraph::NodeType<mgraph::ListEntry<unsigned int> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B52020
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned int> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B52070
	template void mgraph::NodeType<mgraph::ListCount<unsigned __int64> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B520C0
	template void mgraph::NodeType<mgraph::ListEntry<unsigned __int64> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B52140
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B52190
	template void mgraph::NodeType<mgraph::ListCount<String> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B521E0
	template void mgraph::NodeType<mgraph::ListEntry<String> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B52260
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<String> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B522B0
	template void mgraph::NodeType<mgraph::ListCount<Vector> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B52330
	template void mgraph::NodeType<mgraph::ListEntry<Vector> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B52380
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<Vector> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B523D0
	template void mgraph::NodeType<mgraph::ListCount<mgraph::TriggerData> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B52420
	template void mgraph::NodeType<mgraph::ListEntry<mgraph::TriggerData> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B52470
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B524C0
	template void mgraph::NodeType<mgraph::ListCount<Complex> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B52510
	template void mgraph::NodeType<mgraph::ListEntry<Complex> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B52590
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<Complex> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B525E0
	template void mgraph::NodeType<mgraph::ListCount<mgraph::EnvelopeData> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B52630
	template void mgraph::NodeType<mgraph::ListEntry<mgraph::EnvelopeData> >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B52680
	template void mgraph::NodeType<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
}
