// The entity type of om::DynamicObjectEntity (a template instance of the om library).
#include "code/om/dynamicobjectentity.h"

namespace om
{

	// FUNCTION: ENGINE 0x105C1CE0
	template const char* EntityType<om::DynamicObjectEntity>::AllocationTag();
	// FUNCTION: ENGINE 0x105C1F30
	template EntityType<om::DynamicObjectEntity>::EntityType(const char*, unsigned int, unsigned int, int);
	// FUNCTION: ENGINE 0x105C1FE0
	template void EntityType<om::DynamicObjectEntity>::operator delete(void*);
	// FUNCTION: ENGINE 0x105C2020
	template MetaTypeBase* EntityType<om::DynamicObjectEntity>::GetMetaType();
	// FUNCTION: ENGINE 0x105C2040
	template void EntityType<om::DynamicObjectEntity>::CreateEntity(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105C2090
	template void EntityType<om::DynamicObjectEntity>::CreateUnregisteredEntity(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105C20F0
	template void EntityType<om::DynamicObjectEntity>::CreateUnregisteredEntity2(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105C2150
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void EntityType<om::DynamicObjectEntity>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x105C21A0
	template EntityType<om::DynamicObjectEntity>::~EntityType();
	// FUNCTION: ENGINE 0x105C2230
	template void EntityType<om::DynamicObjectEntity>::Register(const char*, int);
}
