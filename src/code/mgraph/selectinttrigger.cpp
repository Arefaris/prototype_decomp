// The select-int-from-trigger node of the mgraph library (0x10B748C0 - 0x10B75A30): the reflection of the class and its methods and the
// description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/selectinttrigger.h"
#include "code/om/invoke.h"
#include "code/om/metaclass.h"
#include "code/om/metamethod.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B75260
	const char* SelectIntFromTrigger::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B75740
	template<> Node* NodeType<SelectIntFromTrigger>::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new SelectIntFromTrigger(static_cast<Graph*>(graph), *nodeName);
	}
}

using namespace om;
using namespace mgraph;


	// FUNCTION: ENGINE 0x10B74930
	template type_info const* om::MetaClass<mgraph::SelectIntFromTrigger>::GetType();
	// FUNCTION: ENGINE 0x10B74970
	template void om::MetaClass<mgraph::SelectIntFromTrigger>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B749E0
	template char const* mgraph::NodeType<mgraph::SelectIntFromTrigger>::AllocationTag();
	// FUNCTION: ENGINE 0x10B749F0
	template char const* om::MetaClass<mgraph::SelectIntFromTrigger>::AllocationTag();
	// FUNCTION: ENGINE 0x10B74A40
	template char const* om::MetaMethod1<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,void,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10B74A50
	template char const* om::MetaMethod0Const<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x10B74AC0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::SelectIntFromTrigger>::Get();
	// FUNCTION: ENGINE 0x10B74AE0
	template MetaTypeBase* mgraph::NodeType<mgraph::SelectIntFromTrigger>::FindMetaType();
	// FUNCTION: ENGINE 0x10B74B00
	template int om::MetaClass<mgraph::SelectIntFromTrigger>::Slot5();
	// FUNCTION: ENGINE 0x10B74B10
	template void om::MetaClass<mgraph::SelectIntFromTrigger>::Slot6(void*);
	// FUNCTION: ENGINE 0x10B74B20
	template void* mgraph::NodeType<mgraph::SelectIntFromTrigger>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B74B40
	template void* om::MetaClass<mgraph::SelectIntFromTrigger>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B74BC0
	template void* om::MetaMethod1<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,void,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B74BE0
	template om::MetaMethod1<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,void,unsigned int>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10B74C10
	template void om::MetaMethod1<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,void,unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x10B74C30
	template om::MetaMethod1<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,void,unsigned int>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10B74C40
	template void om::MetaMethod1<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,void,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B74C60
	template void* om::MetaMethod0Const<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B74C80
	template om::MetaMethod0Const<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,unsigned int>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10B74CB0
	template unsigned int om::MetaMethod0Const<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x10B74CC0
	template om::MetaMethod0Const<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,unsigned int>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10B74CD0
	template void om::MetaMethod0Const<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B74CF0
	template void om::MetaMethod0Const<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B74F80
	template void om::MetaClass<mgraph::SelectIntFromTrigger>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B750A0
	template MetaMethod1<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,void,unsigned int>* om::MetaMethod1<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,void,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,void,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10B750E0
	template MetaMethod0Const<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,unsigned int>* om::MetaMethod0Const<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,unsigned int>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,unsigned int>::Function);
	// FUNCTION: ENGINE 0x10B75170
	template void mgraph::NodeType<mgraph::SelectIntFromTrigger>::Destroy();
	// FUNCTION: ENGINE 0x10B75200
	template mgraph::NodeType<mgraph::SelectIntFromTrigger>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B75240
	template void mgraph::NodeType<mgraph::SelectIntFromTrigger>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B75270
	template void mgraph::NodeType<mgraph::SelectIntFromTrigger>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B752A0
	template MetaTypeBase* mgraph::NodeType<mgraph::SelectIntFromTrigger>::GetMetaType();
	// FUNCTION: ENGINE 0x10B752C0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::SelectIntFromTrigger>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B75310
	template mgraph::NodeType<mgraph::SelectIntFromTrigger>::~NodeType();
	// FUNCTION: ENGINE 0x10B753B0
	template void om::MetaMethod1<mgraph::SelectIntFromTrigger,mgraph::SelectIntFromTrigger,void,unsigned int>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B75770
	template void mgraph::NodeType<mgraph::SelectIntFromTrigger>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);