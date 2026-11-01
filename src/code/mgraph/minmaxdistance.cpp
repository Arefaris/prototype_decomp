// The min-max distance node of the mgraph library (0x10B73A00 - 0x10B748C0): the reflection of the class and the description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/minmaxdistance.h"
#include "code/om/metaclass.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B74130
	const char* MinMaxDistance::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B747D0
	void RegisterMinMaxDistance()
	{
		String nodeName("MinMaxDistance", 0);
		ClassName name(core::Hash64(nodeName.GetText(), 0));
		String category("Audio", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<MinMaxDistance>::RegisterDerived(CachedNodeType<Node>(), flags, name);
	}

	// FUNCTION: ENGINE 0x10B74750
	template<> Node* NodeType<MinMaxDistance>::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new MinMaxDistance(static_cast<Graph*>(graph), *nodeName);
	}
}

using namespace om;
using namespace mgraph;



	// FUNCTION: ENGINE 0x10B73A50
	template om::MetaClass<mgraph::MinMaxDistance>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B73A80
	template type_info const* om::MetaClass<mgraph::MinMaxDistance>::GetType();
	// FUNCTION: ENGINE 0x10B73AC0
	template void om::MetaClass<mgraph::MinMaxDistance>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B73AF0
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::MinMaxDistance>::Get();
	// FUNCTION: ENGINE 0x10B73B30
	template char const* mgraph::NodeType<mgraph::MinMaxDistance>::AllocationTag();
	// FUNCTION: ENGINE 0x10B73B40
	template char const* om::MetaClass<mgraph::MinMaxDistance>::AllocationTag();
	// FUNCTION: ENGINE 0x10B73C50
	template int om::MetaClass<mgraph::MinMaxDistance>::Slot5();
	// FUNCTION: ENGINE 0x10B73C60
	template void om::MetaClass<mgraph::MinMaxDistance>::Slot6(void*);
	// FUNCTION: ENGINE 0x10B73C70
	template void* mgraph::NodeType<mgraph::MinMaxDistance>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B73C90
	template void* om::MetaClass<mgraph::MinMaxDistance>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B73F40
	template void om::MetaClass<mgraph::MinMaxDistance>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B74070
	template void mgraph::NodeType<mgraph::MinMaxDistance>::Destroy();
	// FUNCTION: ENGINE 0x10B740D0
	template mgraph::NodeType<mgraph::MinMaxDistance>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B74110
	template void mgraph::NodeType<mgraph::MinMaxDistance>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B74140
	template void mgraph::NodeType<mgraph::MinMaxDistance>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B74170
	template MetaTypeBase* mgraph::NodeType<mgraph::MinMaxDistance>::FindMetaType();
	// FUNCTION: ENGINE 0x10B74190
	template MetaTypeBase* mgraph::NodeType<mgraph::MinMaxDistance>::GetMetaType();
	// FUNCTION: ENGINE 0x10B741B0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::MinMaxDistance>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B74200
	template mgraph::NodeType<mgraph::MinMaxDistance>::~NodeType();
	// FUNCTION: ENGINE 0x10B74780
	template void mgraph::NodeType<mgraph::MinMaxDistance>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);