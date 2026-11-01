// The node types of mgraph::LinkedGraph and mgraph::EmbeddedGraph (0x10ACC0F0 - 0x10ACD6C0), like those of the other node classes in nodetypes.cpp.
#include "code/mgraph/nodes.h"
#include "code/om/metaclass.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10ACC0F0
	template char const* mgraph::NodeType<mgraph::LinkedGraph>::AllocationTag();
	// FUNCTION: ENGINE 0x10ACC1E0
	template MetaTypeBase* mgraph::NodeType<mgraph::LinkedGraph>::FindMetaType();
	// FUNCTION: ENGINE 0x10ACC220
	template void* mgraph::NodeType<mgraph::LinkedGraph>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ACC740
	template mgraph::NodeType<mgraph::LinkedGraph>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ACC780
	template void mgraph::NodeType<mgraph::LinkedGraph>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ACC7A0
	template void mgraph::NodeType<mgraph::LinkedGraph>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10ACC7E0
	template MetaTypeBase* mgraph::NodeType<mgraph::LinkedGraph>::GetMetaType();
	// FUNCTION: ENGINE 0x10ACC800
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::LinkedGraph>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10ACC850
	template mgraph::NodeType<mgraph::LinkedGraph>::~NodeType();
	// FUNCTION: ENGINE 0x10ACC8F0
	template void mgraph::NodeType<mgraph::LinkedGraph>::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ACCAA0
	template void mgraph::NodeType<mgraph::LinkedGraph>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ACD1B0
	template char const* mgraph::NodeType<mgraph::EmbeddedGraph>::AllocationTag();
	// FUNCTION: ENGINE 0x10ACD220
	template MetaTypeBase* mgraph::NodeType<mgraph::EmbeddedGraph>::FindMetaType();
	// FUNCTION: ENGINE 0x10ACD260
	template void* mgraph::NodeType<mgraph::EmbeddedGraph>::operator new(size_t);
	// FUNCTION: ENGINE 0x10ACD6C0
	template mgraph::NodeType<mgraph::EmbeddedGraph>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ACD6F0
	template void mgraph::NodeType<mgraph::EmbeddedGraph>::operator delete(void*);
	// FUNCTION: ENGINE 0x10ACD710
	template void mgraph::NodeType<mgraph::EmbeddedGraph>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10ACD750
	template MetaTypeBase* mgraph::NodeType<mgraph::EmbeddedGraph>::GetMetaType();
	// FUNCTION: ENGINE 0x10ACD770
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::EmbeddedGraph>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10ACD7C0
	template mgraph::NodeType<mgraph::EmbeddedGraph>::~NodeType();
	// FUNCTION: ENGINE 0x10ACD970
	template void mgraph::NodeType<mgraph::EmbeddedGraph>::Register(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ACDB20
	template void mgraph::NodeType<mgraph::EmbeddedGraph>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
}
