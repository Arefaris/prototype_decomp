// The entity type of music::Cue (a template instance of the om library).
#include "code/music/cue.h"

namespace om
{

	// FUNCTION: ENGINE 0x105DC1B0
	template const char* EntityType<music::Cue>::AllocationTag();
	// FUNCTION: ENGINE 0x105DD8F0
	template EntityType<music::Cue>::EntityType(const char*, unsigned int, unsigned int, bool);
	// FUNCTION: ENGINE 0x105DD9A0
	template void EntityType<music::Cue>::operator delete(void*);
	// FUNCTION: ENGINE 0x105DD9E0
	template MetaTypeBase* EntityType<music::Cue>::GetMetaType();
	// FUNCTION: ENGINE 0x105DDA00
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void EntityType<music::Cue>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x105DDA50
	template EntityType<music::Cue>::~EntityType();
	// FUNCTION: ENGINE 0x105DDAB0
	template void EntityType<music::Cue>::CreateEntity(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105DDB00
	template void EntityType<music::Cue>::CreateUnregisteredEntity(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105DDB60
	template void EntityType<music::Cue>::CreateUnregisteredEntity2(Entity**, const ClassName&);
	// FUNCTION: ENGINE 0x105DF7D0
	template void EntityType<music::Cue>::Register(const char*, bool);
}
