// The delay node of the mgraph library (0x10B6E360 - 0x10B6F1A0): the reflection of the class and the description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/delay.h"
#include "code/om/metaclass.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B6E980
	const char* Delay::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B6F040
	void RegisterDelay()
	{
		String nodeName("Delay", 0);
		ClassName name(core::Hash64(nodeName.GetText(), 0));
		String category("Logic", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Delay>::RegisterDerived(CachedNodeType<Node>(), flags, name);
	}

	// FUNCTION: ENGINE 0x10B6EFC0
	template<> Node* NodeType<Delay>::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new Delay(static_cast<Graph*>(graph), *nodeName);
	}
}

using namespace om;
using namespace mgraph;



	// FUNCTION: ENGINE 0x10B6E3B0
	template om::MetaClass<mgraph::Delay>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6E3E0
	template type_info const* om::MetaClass<mgraph::Delay>::GetType();
	// FUNCTION: ENGINE 0x10B6E420
	template void om::MetaClass<mgraph::Delay>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6E450
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Delay>::Get();
	// FUNCTION: ENGINE 0x10B6E490
	template char const* mgraph::NodeType<mgraph::Delay>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6E4A0
	template char const* om::MetaClass<mgraph::Delay>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6E5C0
	template int om::MetaClass<mgraph::Delay>::Slot5();
	// FUNCTION: ENGINE 0x10B6E5D0
	template void om::MetaClass<mgraph::Delay>::Slot6(void*);
	// FUNCTION: ENGINE 0x10B6E5E0
	template void* mgraph::NodeType<mgraph::Delay>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6E600
	template void* om::MetaClass<mgraph::Delay>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6E770
	template void om::MetaClass<mgraph::Delay>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6E890
	template void mgraph::NodeType<mgraph::Delay>::Destroy();
	// FUNCTION: ENGINE 0x10B6E920
	template mgraph::NodeType<mgraph::Delay>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B6E960
	template void mgraph::NodeType<mgraph::Delay>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6E990
	template void mgraph::NodeType<mgraph::Delay>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B6E9C0
	template MetaTypeBase* mgraph::NodeType<mgraph::Delay>::FindMetaType();
	// FUNCTION: ENGINE 0x10B6E9E0
	template MetaTypeBase* mgraph::NodeType<mgraph::Delay>::GetMetaType();
	// FUNCTION: ENGINE 0x10B6EA00
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Delay>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B6EA50
	template mgraph::NodeType<mgraph::Delay>::~NodeType();
	// FUNCTION: ENGINE 0x10B6EFF0
	template void mgraph::NodeType<mgraph::Delay>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);