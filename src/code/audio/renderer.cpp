// The audio renderer (0x105D0F40 - 0x105D2600): the reflection of audio::Renderer made of template instances of the
// om library.
#include "code/audio/renderer.h"
#include "code/om/metaclass.h"

namespace om
{

	// FUNCTION: ENGINE 0x105D11D0
	template MetaClass<audio::Renderer>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105D1200
	template const type_info* MetaClass<audio::Renderer>::GetType();
	// FUNCTION: ENGINE 0x105D1230
	template MetaClass<audio::Renderer>::~MetaClass();
	// FUNCTION: ENGINE 0x105D1240
	template void MetaClass<audio::Renderer>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D1320
	template const char* MetaClass<audio::Renderer>::AllocationTag();
	// FUNCTION: ENGINE 0x105D1960
	template int MetaClass<audio::Renderer>::Slot5();
	// FUNCTION: ENGINE 0x105D1970
	template void MetaClass<audio::Renderer>::Slot6(void*);
	// FUNCTION: ENGINE 0x105D1980
	template void* MetaClass<audio::Renderer>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D2190
	template void MetaClass<audio::Renderer>::Create(const ClassName&, MetaClassBase*);
}
