// The meter node of the mgraph library (0x10B730D0 - 0x10B73A00): the reflection of the class and the description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/meter.h"
#include "code/om/metaclass.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B734D0
	const char* Meter::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B73910
	void RegisterMeter()
	{
		String nodeName("Meter", 0);
		ClassName name(core::Hash64(nodeName.GetText(), 0));
		String category("Audio", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Meter>::RegisterDerived(CachedNodeType<Node>(), flags, name);
	}

	// FUNCTION: ENGINE 0x10B73890
	template<> Node* NodeType<Meter>::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new Meter(static_cast<Graph*>(graph), *nodeName);
	}
}

using namespace om;
using namespace mgraph;



	// FUNCTION: ENGINE 0x10B730E0
	template om::MetaClass<mgraph::Meter>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B73110
	template type_info const* om::MetaClass<mgraph::Meter>::GetType();
	// FUNCTION: ENGINE 0x10B73150
	template void om::MetaClass<mgraph::Meter>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B73170
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Meter>::Get();
	// FUNCTION: ENGINE 0x10B731B0
	template char const* mgraph::NodeType<mgraph::Meter>::AllocationTag();
	// FUNCTION: ENGINE 0x10B731C0
	template char const* om::MetaClass<mgraph::Meter>::AllocationTag();
	// FUNCTION: ENGINE 0x10B73200
	template int om::MetaClass<mgraph::Meter>::Slot5();
	// FUNCTION: ENGINE 0x10B73210
	template void om::MetaClass<mgraph::Meter>::Slot6(void*);
	// FUNCTION: ENGINE 0x10B73220
	template void* mgraph::NodeType<mgraph::Meter>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B73240
	template void* om::MetaClass<mgraph::Meter>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B733D0
	template void om::MetaClass<mgraph::Meter>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B73440
	template void mgraph::NodeType<mgraph::Meter>::Destroy();
	// FUNCTION: ENGINE 0x10B73470
	template mgraph::NodeType<mgraph::Meter>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B734B0
	template void mgraph::NodeType<mgraph::Meter>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B734E0
	template void mgraph::NodeType<mgraph::Meter>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B73510
	template MetaTypeBase* mgraph::NodeType<mgraph::Meter>::FindMetaType();
	// FUNCTION: ENGINE 0x10B73530
	template MetaTypeBase* mgraph::NodeType<mgraph::Meter>::GetMetaType();
	// FUNCTION: ENGINE 0x10B73550
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Meter>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B735A0
	template mgraph::NodeType<mgraph::Meter>::~NodeType();
	// FUNCTION: ENGINE 0x10B738C0
	template void mgraph::NodeType<mgraph::Meter>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);