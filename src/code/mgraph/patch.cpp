// The patch of the mgraph library (0x105B9380 - 0x105BA570) and the reflection and entity type that the om library's
// templates make for it.
#include "code/mgraph/patch.h"
#include "code/om/metaclass.h"
#include "code/om/reflection.h"

namespace mgraph
{
	// FUNCTION: ENGINE 0x105B9540
	Patch::Patch(const om::ClassName& newName) :
		DynamicObjectEntity(newName),
		graphName(),
		isSingleton(false)
	{
	}

	// FUNCTION: ENGINE 0x105B9380
	Patch::~Patch()
	{
	}

	// FUNCTION: ENGINE 0x105B93B0
	const om::ClassName& Patch::GetGraphName() const
	{
		return graphName;
	}

	// FUNCTION: ENGINE 0x105B93C0
	bool Patch::GetIsSingleton() const
	{
		return isSingleton;
	}

	// FUNCTION: ENGINE 0x105B93D0
	void Patch::SetIsSingleton(bool newIsSingleton)
	{
		isSingleton = newIsSingleton;
	}

	// FUNCTION: ENGINE 0x105B9820
	om::EntityTypeBase* Patch::GetEntityType()
	{
		return om::FindEntityType(typeid(Patch));
	}
}

namespace om
{
	// FUNCTION: ENGINE 0x105B93E0
	template MetaClass<mgraph::Patch>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105B9410
	template const type_info* MetaClass<mgraph::Patch>::GetType();
	// FUNCTION: ENGINE 0x105B9440
	template MetaClass<mgraph::Patch>::~MetaClass();
	// FUNCTION: ENGINE 0x105B9450
	template void MetaClass<mgraph::Patch>::operator delete(void*);
	// FUNCTION: ENGINE 0x105B94E0
	template const char* MetaClass<mgraph::Patch>::AllocationTag();
	// FUNCTION: ENGINE 0x105B96A0
	template int MetaClass<mgraph::Patch>::Slot5();
	// FUNCTION: ENGINE 0x105B96B0
	template void MetaClass<mgraph::Patch>::Slot6(void*);
	// FUNCTION: ENGINE 0x105B96C0
	template void* MetaClass<mgraph::Patch>::operator new(size_t);

	// FUNCTION: ENGINE 0x105B99C0
	template void MetaClass<mgraph::Patch>::Create(const ClassName&, MetaClassBase*);

	// FUNCTION: ENGINE 0x105B94C0
	template const char* EntityType<mgraph::Patch>::AllocationTag();
	// FUNCTION: ENGINE 0x105B9680
	template void* EntityType<mgraph::Patch>::operator new(size_t);
	// FUNCTION: ENGINE 0x105B9DA0
	template EntityType<mgraph::Patch>::EntityType(const char*, unsigned int, unsigned int, int);
	// FUNCTION: ENGINE 0x105B9E50
	template void EntityType<mgraph::Patch>::operator delete(void*);
	// FUNCTION: ENGINE 0x105B9E90
	template MetaTypeBase* EntityType<mgraph::Patch>::GetMetaType();
	// FUNCTION: ENGINE 0x105B9EB0
	template void EntityType<mgraph::Patch>::CreateEntity(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105B9F00
	template void EntityType<mgraph::Patch>::CreateUnregisteredEntity(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105B9F60
	template void EntityType<mgraph::Patch>::CreateUnregisteredEntity2(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105B9FC0
	// NONMATCHING: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
#ifdef NONMATCHING
	template void EntityType<mgraph::Patch>::ReleaseMetaType();
#endif
	// FUNCTION: ENGINE 0x105BA010
	template EntityType<mgraph::Patch>::~EntityType();
	// FUNCTION: ENGINE 0x105BA4F0
	template void EntityType<mgraph::Patch>::Register(const char*, int);
}
