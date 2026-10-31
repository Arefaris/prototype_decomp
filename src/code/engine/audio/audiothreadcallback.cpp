#include "code/core/heap.h"
#include "code/engine/audio/audiothreadcallback.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10844F50
	void ThreadEntryCallback::OnThreadEntry(om::Thread* thread)
	{
		core::SetCurrentHeap(0xb);
	}
}
