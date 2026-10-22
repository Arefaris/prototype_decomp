// The music library's cues and cells (0x105DBFF0 - 0x105E0000): the reflection of music::Cue, Cell and MGraphCell
// made of template instances of the om library.
#include "code/music/cue.h"
#include "code/om/metaclass.h"

namespace om
{

	// FUNCTION: ENGINE 0x105DC060
	template MetaClass<music::Cue>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105DC090
	template const type_info* MetaClass<music::Cue>::GetType();
	// FUNCTION: ENGINE 0x105DC0C0
	template MetaClass<music::Cue>::~MetaClass();
	// FUNCTION: ENGINE 0x105DC0D0
	template void MetaClass<music::Cue>::operator delete(void*);
	// FUNCTION: ENGINE 0x105DC1D0
	template const char* MetaClass<music::Cue>::AllocationTag();
	// FUNCTION: ENGINE 0x105DC710
	template int MetaClass<music::Cue>::Slot5();
	// FUNCTION: ENGINE 0x105DC720
	template void MetaClass<music::Cue>::Slot6(void*);
	// FUNCTION: ENGINE 0x105DC730
	template void* MetaClass<music::Cue>::operator new(size_t);
	// FUNCTION: ENGINE 0x105DCFD0
	template void MetaClass<music::Cue>::Create(const ClassName&, MetaClassBase*);
}
