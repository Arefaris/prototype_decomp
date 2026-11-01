// The entity type of om::DynamicObjectEntity (a template instance of the om library).
#include "code/om/dynamicobjectentity.h"
#include "code/om/reflection.h"

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

	// FUNCTION: ENGINE 0x105C1C40
	template MetaClass<om::DynamicObjectEntity>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105C1C70
	template const type_info* MetaClass<om::DynamicObjectEntity>::GetType();
	// FUNCTION: ENGINE 0x105C1CA0
	template MetaClass<om::DynamicObjectEntity>::~MetaClass();
	// FUNCTION: ENGINE 0x105C1CB0
	template void MetaClass<om::DynamicObjectEntity>::operator delete(void*);
	// FUNCTION: ENGINE 0x105C1D00
	template const char* MetaClass<om::DynamicObjectEntity>::AllocationTag();
	// FUNCTION: ENGINE 0x105C1DE0
	template void* EntityType<om::DynamicObjectEntity>::operator new(size_t);
	// FUNCTION: ENGINE 0x105C1E00
	template int MetaClass<om::DynamicObjectEntity>::Slot5();
	// FUNCTION: ENGINE 0x105C1E10
	template void MetaClass<om::DynamicObjectEntity>::Slot6(void*);
	// FUNCTION: ENGINE 0x105C1E20
	template void* MetaClass<om::DynamicObjectEntity>::operator new(size_t);
	// FUNCTION: ENGINE 0x105C1EA0
	template void MetaClass<om::DynamicObjectEntity>::Create(const ClassName&, MetaClassBase*);
}

namespace om
{
	// FUNCTION: ENGINE 0x105C2000
	template MetaClassBase* GetCachedClass<om::DynamicObjectEntity>();
}
