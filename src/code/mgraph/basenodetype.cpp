// The node type of the base class mgraph::Node (0x10ACAD10 - 0x10ACAEB0), like those of the other node classes in nodetypes.cpp.
#include "code/mgraph/nodes.h"
#include "code/om/metaclass.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10ACAD40
	template mgraph::NodeType<mgraph::Node>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10ACADA0
	template void mgraph::NodeType<mgraph::Node>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10ACADD0
	template MetaTypeBase* mgraph::NodeType<mgraph::Node>::GetMetaType();
	// FUNCTION: ENGINE 0x10ACADF0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Node>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10ACAE40
	template mgraph::NodeType<mgraph::Node>::~NodeType();
}
