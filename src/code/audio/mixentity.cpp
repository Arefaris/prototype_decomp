// The entity type of audio::Mix (a template instance of the om library).
#include "code/audio/mix.h"

namespace om
{

	// FUNCTION: ENGINE 0x105CC440
	template const char* EntityType<audio::Mix>::AllocationTag();
	// FUNCTION: ENGINE 0x105CF140
	template EntityType<audio::Mix>::EntityType(const char*, unsigned int, unsigned int, bool);
	// FUNCTION: ENGINE 0x105CF1E0
	template void EntityType<audio::Mix>::operator delete(void*);
	// FUNCTION: ENGINE 0x105CF200
	template MetaTypeBase* EntityType<audio::Mix>::GetMetaType();
	// FUNCTION: ENGINE 0x105CF220
	template void EntityType<audio::Mix>::CreateEntity(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105CF270
	template void EntityType<audio::Mix>::CreateUnregisteredEntity(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105CF2D0
	template void EntityType<audio::Mix>::CreateUnregisteredEntity2(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105CF330
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void EntityType<audio::Mix>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x105CF380
	template EntityType<audio::Mix>::~EntityType();
	// FUNCTION: ENGINE 0x105CF810
	template void EntityType<audio::Mix>::Register(const char*, bool);
}
