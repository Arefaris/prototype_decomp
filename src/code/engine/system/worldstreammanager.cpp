// The world stream manager (RTTI: engine::WorldStreamManager, a StreamClient that streams the world cells; unit
// 0x108540E0 - 0x108551xx, no assert path, file name guessed). Of the unit only the instances of templates it uses.
#include "code/content/loadinventory.h"
#include "code/engine/reflectedclasses.h"

// The lookup of a location by name (the filter the inventory is handed)
// FUNCTION: ENGINE 0x108547D0
template class content::LoadInventory::DynamicCaster<engine::world::Location>;
