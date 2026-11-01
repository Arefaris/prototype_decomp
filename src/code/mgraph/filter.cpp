// The filter node of the mgraph library (0x10B707C0 - 0x10B730D0): the reflection of the class, its properties and methods and the
// description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/filter.h"
#include "code/om/delegate.h"
#include "code/om/invoke.h"
#include "code/om/metaclass.h"
#include "code/om/metaenum.h"
#include "code/om/metamethod.h"
#include "code/om/metaproperty.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B71B80
	const char* Filter::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B726A0
	template<> Node* NodeType<Filter>::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new Filter(static_cast<Graph*>(graph), *nodeName);
	}
}

using namespace om;
using namespace mgraph;


	// FUNCTION: ENGINE 0x10B70800
	template om::MetaEnum<dsp::BiQuadFilterType>::MetaEnum(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B70820
	template type_info const* om::MetaEnum<dsp::BiQuadFilterType>::GetType();
	// FUNCTION: ENGINE 0x10B70830
	template om::MetaEnum<dsp::BiQuadFilterType>::~MetaEnum();
	// FUNCTION: ENGINE 0x10B70840
	template bool om::MetaEnum<dsp::BiQuadFilterType>::WriteBinary(BinaryStream*, void const*);
	// FUNCTION: ENGINE 0x10B70860
	template void om::MetaEnum<dsp::BiQuadFilterType>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B708A0
	template om::MetaClass<mgraph::Filter>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B708D0
	template type_info const* om::MetaClass<mgraph::Filter>::GetType();
	// FUNCTION: ENGINE 0x10B70910
	template void om::MetaClass<mgraph::Filter>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B70990
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Filter>::Get();
	// FUNCTION: ENGINE 0x10B709E0
	template char const* om::MetaEnum<dsp::BiQuadFilterType>::AllocationTag();
	// FUNCTION: ENGINE 0x10B709F0
	template char const* mgraph::NodeType<mgraph::Filter>::AllocationTag();
	// FUNCTION: ENGINE 0x10B70A00
	template char const* om::MetaClass<mgraph::Filter>::AllocationTag();
	// FUNCTION: ENGINE 0x10B70A10
	template om::MetaProperty<dsp::BiQuadFilterType>::MetaProperty(MetaTypeBase*, MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,dsp::BiQuadFilterType>*, MetaMethod0Base<dsp::BiQuadFilterType>*, unsigned int);
	// FUNCTION: ENGINE 0x10B70A50
	template type_info const* om::MetaProperty<dsp::BiQuadFilterType>::GetValueType();
	// FUNCTION: ENGINE 0x10B70A60
	template om::MetaMethod1Base<void,dsp::BiQuadFilterType>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x10B70A70
	template om::MetaMethod0Base<dsp::BiQuadFilterType>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x10B70A80
	template om::MetaProperty<dsp::BiQuadFilterType>::~MetaProperty();
	// FUNCTION: ENGINE 0x10B70A90
	template om::MetaMethod1Base<void,dsp::BiQuadFilterType>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B70B80
	template char const* om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,float>::AllocationTag();
	// FUNCTION: ENGINE 0x10B70B90
	template char const* om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,dsp::BiQuadFilterType>::AllocationTag();
	// FUNCTION: ENGINE 0x10B70BA0
	template char const* om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,float>::AllocationTag();
	// FUNCTION: ENGINE 0x10B70BB0
	template char const* om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,dsp::BiQuadFilterType>::AllocationTag();
	// FUNCTION: ENGINE 0x10B70BC0
	template char const* om::MetaProperty<dsp::BiQuadFilterType>::AllocationTag();
	// FUNCTION: ENGINE 0x10B70C10
	template char const* om::DelegateMetaProperty<dsp::BiQuadFilterType>::AllocationTag();
	// FUNCTION: ENGINE 0x10B70D00
	template bool om::MetaEnum<dsp::BiQuadFilterType>::ReadBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B70D20
	template int om::MetaEnum<dsp::BiQuadFilterType>::Slot5();
	// FUNCTION: ENGINE 0x10B70D30
	template void om::MetaEnum<dsp::BiQuadFilterType>::Slot6(void*);
	// FUNCTION: ENGINE 0x10B70D40
	template MetaTypeBase* mgraph::NodeType<mgraph::Filter>::FindMetaType();
	// FUNCTION: ENGINE 0x10B70D60
	template int om::MetaClass<mgraph::Filter>::Slot5();
	// FUNCTION: ENGINE 0x10B70D70
	template void om::MetaClass<mgraph::Filter>::Slot6(void*);
	// FUNCTION: ENGINE 0x10B70DB0
	template void* om::MetaEnum<dsp::BiQuadFilterType>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B70DD0
	template void* mgraph::NodeType<mgraph::Filter>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B70DF0
	template void* om::MetaClass<mgraph::Filter>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B70E90
	template om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,float>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Filter,mgraph::Filter,void,float>::Function);
	// FUNCTION: ENGINE 0x10B70EC0
	template void om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,float>::Call(void*, float);
	// FUNCTION: ENGINE 0x10B70EE0
	template om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,float>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10B70EF0
	template void om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,float>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B70F10
	template void* om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,dsp::BiQuadFilterType>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B70F30
	template om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,dsp::BiQuadFilterType>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Filter,mgraph::Filter,void,dsp::BiQuadFilterType>::Function);
	// FUNCTION: ENGINE 0x10B70F60
	template void om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,dsp::BiQuadFilterType>::Call(void*, dsp::BiQuadFilterType);
	// FUNCTION: ENGINE 0x10B70F80
	template om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,dsp::BiQuadFilterType>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10B70F90
	template void om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,dsp::BiQuadFilterType>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B70FB0
	template void* om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,float>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B70FD0
	template om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,float>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Filter,mgraph::Filter,float>::Function);
	// FUNCTION: ENGINE 0x10B71000
	template float om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,float>::Call(void*);
	// FUNCTION: ENGINE 0x10B71010
	template om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,float>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10B71020
	template void om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,float>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B71040
	template void om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,float>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B710E0
	template void* om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,dsp::BiQuadFilterType>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B71100
	template om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,dsp::BiQuadFilterType>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Filter,mgraph::Filter,dsp::BiQuadFilterType>::Function);
	// FUNCTION: ENGINE 0x10B71130
	template dsp::BiQuadFilterType om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,dsp::BiQuadFilterType>::Call(void*);
	// FUNCTION: ENGINE 0x10B71140
	template om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,dsp::BiQuadFilterType>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10B71150
	template void om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,dsp::BiQuadFilterType>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B71170
	template void* om::MetaProperty<dsp::BiQuadFilterType>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B71280
	template MetaMethod1Base<void,dsp::BiQuadFilterType>* om::MetaProperty<dsp::BiQuadFilterType>::GetSetter();
	// FUNCTION: ENGINE 0x10B71290
	template MetaMethod0Base<dsp::BiQuadFilterType>* om::MetaProperty<dsp::BiQuadFilterType>::GetGetter();
	// FUNCTION: ENGINE 0x10B71360
	template void* om::DelegateMetaProperty<dsp::BiQuadFilterType>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B713B0
	template om::DelegateProperty<dsp::BiQuadFilterType>::DelegateProperty();
	// FUNCTION: ENGINE 0x10B713C0
	template MetaTypeBase* om::DelegateProperty<dsp::BiQuadFilterType>::GetMetaType();
	// FUNCTION: ENGINE 0x10B713D0
	template om::DelegateProperty<dsp::BiQuadFilterType>::~DelegateProperty();
	// FUNCTION: ENGINE 0x10B71480
	template void mgraph::NodeType<mgraph::Filter>::Destroy();
	// FUNCTION: ENGINE 0x10B71540
	template void om::MetaEnum<dsp::BiQuadFilterType>::WriteText(TextValue*, void const*);
	// FUNCTION: ENGINE 0x10B71550
	template void om::MetaClass<mgraph::Filter>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B71680
	template MetaMethod1<mgraph::Filter,mgraph::Filter,void,float>* om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,float>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Filter,mgraph::Filter,void,float>::Function);
	// FUNCTION: ENGINE 0x10B716C0
	template MetaMethod0Const<mgraph::Filter,mgraph::Filter,float>* om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,float>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Filter,mgraph::Filter,float>::Function);
	// FUNCTION: ENGINE 0x10B71750
	template MetaMethod1<mgraph::Filter,mgraph::Filter,void,dsp::BiQuadFilterType>* om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,dsp::BiQuadFilterType>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Filter,mgraph::Filter,void,dsp::BiQuadFilterType>::Function);
	// FUNCTION: ENGINE 0x10B71790
	template MetaMethod0Const<mgraph::Filter,mgraph::Filter,dsp::BiQuadFilterType>* om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,dsp::BiQuadFilterType>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Filter,mgraph::Filter,dsp::BiQuadFilterType>::Function);
	// FUNCTION: ENGINE 0x10B717D0
	template void om::MetaProperty<dsp::BiQuadFilterType>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,dsp::BiQuadFilterType>*, MetaMethod0Base<dsp::BiQuadFilterType>*, unsigned int);
	// FUNCTION: ENGINE 0x10B71880
	template om::DelegateMetaProperty<dsp::BiQuadFilterType>::DelegateMetaProperty(void*, MetaProperty<dsp::BiQuadFilterType>*);
	// FUNCTION: ENGINE 0x10B718B0
	template void om::DelegateMetaProperty<dsp::BiQuadFilterType>::SetObject(void*);
	// FUNCTION: ENGINE 0x10B718C0
	template void om::DelegateMetaProperty<dsp::BiQuadFilterType>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B718E0
	template om::DelegateMetaProperty<dsp::BiQuadFilterType>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x10B718F0
	template dsp::BiQuadFilterType om::DelegateMetaProperty<dsp::BiQuadFilterType>::Get();
	// FUNCTION: ENGINE 0x10B71910
	template void om::DelegateMetaProperty<dsp::BiQuadFilterType>::Set(dsp::BiQuadFilterType);
	// FUNCTION: ENGINE 0x10B71AC0
	template bool om::MetaEnum<dsp::BiQuadFilterType>::ReadText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B71B30
	template mgraph::NodeType<mgraph::Filter>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B71B60
	template void mgraph::NodeType<mgraph::Filter>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B71B90
	template void mgraph::NodeType<mgraph::Filter>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B71BC0
	template MetaTypeBase* mgraph::NodeType<mgraph::Filter>::GetMetaType();
	// FUNCTION: ENGINE 0x10B71BE0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Filter>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B71C30
	template mgraph::NodeType<mgraph::Filter>::~NodeType();
	// FUNCTION: ENGINE 0x10B71D30
	template bool om::MetaProperty<dsp::BiQuadFilterType>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10B71DC0
	template void om::MetaProperty<dsp::BiQuadFilterType>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x10B71E50
	template bool om::MetaProperty<dsp::BiQuadFilterType>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B71EB0
	template bool om::MetaProperty<dsp::BiQuadFilterType>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10B71F00
	template DelegatePropertyBase* om::MetaProperty<dsp::BiQuadFilterType>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x10B71FD0
	template void om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,float>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B72140
	template void om::MetaMethod0Const<mgraph::Filter,mgraph::Filter,dsp::BiQuadFilterType>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B726D0
	template void mgraph::NodeType<mgraph::Filter>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B72720
	template void om::MetaMethod1<mgraph::Filter,mgraph::Filter,void,dsp::BiQuadFilterType>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);