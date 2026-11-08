// The entity type of mgraph::Graph (a template instance of the om library).
#include "code/mgraph/graph.h"

namespace om
{

	// FUNCTION: ENGINE 0x10AC5F50
	template char const* EntityType<mgraph::Graph>::AllocationTag();
	// FUNCTION: ENGINE 0x10AC8150
	template EntityType<mgraph::Graph>::EntityType(char const*, unsigned int, unsigned int, int);
	// FUNCTION: ENGINE 0x10AC81D0
	template void EntityType<mgraph::Graph>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AC8210
	template MetaTypeBase* EntityType<mgraph::Graph>::GetMetaType();
	// FUNCTION: ENGINE 0x10AC8280
	template EntityType<mgraph::Graph>::~EntityType();
	// FUNCTION: ENGINE 0x10AC82E0
	template void EntityType<mgraph::Graph>::CreateEntity(Entity**, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AC8340
	template void EntityType<mgraph::Graph>::CreateUnregisteredEntity(Entity**, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AC83A0
	template void EntityType<mgraph::Graph>::CreateUnregisteredEntity2(Entity**, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AC8810
	template void EntityType<mgraph::Graph>::Register(char const*, int);
	// FUNCTION: ENGINE 0x10AC8230
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void EntityType<mgraph::Graph>::ReleaseMetaType();
}
