// The lookups of the proto load objects the AI helpers read by name (DynamicCaster filters and the inventory's Find by the
// text or the name of an object). The engine keeps one out-of-line copy of each; the classes whose layout is not
// recovered yet are declared in reflectedstubs.h or below.
#include "code/engine/gameobject/gameobjectspawner.h"
#include "code/proto/behaviours/tokenbehaviour.h"
#include "code/proto/reflectedstubs.h"

namespace proto
{
	// Reflected load objects whose layout is not recovered (RTTI structs, base content::MetaLoadObject)
	struct TargetSelectionWeights : public content::MetaLoadObject
	{
	};
}

template class content::LoadInventory::DynamicCaster<proto::Heightmap>;
template class content::LoadInventory::DynamicCaster<proto::WorldBoundary>;
template class content::LoadInventory::DynamicCaster<proto::TargetSelectionWeights>;
template class content::LoadInventory::DynamicCaster<proto::TokenWeights>;
template class content::LoadInventory::DynamicCaster<proto::HeliPathfindingLoader>;
template class content::LoadInventory::DynamicCaster<proto::CharacterBudgetPolicyList>;

template proto::Heightmap* content::LoadInventory::Find<proto::Heightmap>(const char*);
template proto::WorldBoundary* content::LoadInventory::Find<proto::WorldBoundary>(const char*);
template proto::WorldBoundary* content::LoadInventory::Find<proto::WorldBoundary>(const content::ObjectName&);
template proto::TargetSelectionWeights* content::LoadInventory::Find<proto::TargetSelectionWeights>(const char*);
template proto::TokenWeights* content::LoadInventory::Find<proto::TokenWeights>(const char*);
template proto::HeliPathfindingLoader* content::LoadInventory::Find<proto::HeliPathfindingLoader>(const char*);
template proto::CharacterBudgetPolicyList* content::LoadInventory::Find<proto::CharacterBudgetPolicyList>(const char*);
template content::MetaObjectTemplate* content::LoadInventory::Find<content::MetaObjectTemplate>(const char*);

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103621E0
// FUNCTION: ENGINE 0x103621F0
// FUNCTION: ENGINE 0x10362220
// FUNCTION: ENGINE 0x10362230
// FUNCTION: ENGINE 0x10362F60
// FUNCTION: ENGINE 0x10362FB0
// FUNCTION: ENGINE 0x10363000
// FUNCTION: ENGINE 0x10369580
// FUNCTION: ENGINE 0x10369590
// FUNCTION: ENGINE 0x103695C0
// FUNCTION: ENGINE 0x103695D0
// FUNCTION: ENGINE 0x10374650
// FUNCTION: ENGINE 0x103746A0
// FUNCTION: ENGINE 0x103746F0
// FUNCTION: ENGINE 0x10382EA0
// FUNCTION: ENGINE 0x10382EB0
// FUNCTION: ENGINE 0x10384400
// FUNCTION: ENGINE 0x10386EB0
// FUNCTION: ENGINE 0x10386EC0
// FUNCTION: ENGINE 0x10387CD0
