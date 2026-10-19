// pure3d::dxIndexBuffer, the Direct3D 9 index buffer of the pddi layer (unit around 0x106266D0 - 0x106269E0; the
// file name is guessed, no assert path survives).
#include <string.h>

#include "code/content/loadmanager.h"
#include "code/core/thread.h"
#include "code/pure3d/pddi/dx9/dxindexbuffer.h"

#include "code/pure3d/pddi/dx9/dxcontext.h"

namespace pure3d
{
	// The two bits of the pddi usage that reach Direct3D: 8 for a write-only buffer, 0x200 for a dynamic one
	enum
	{
		D3DUSAGE_WRITEONLY = 8,
		D3DUSAGE_DYNAMIC = 0x200
	};

	// FUNCTION: ENGINE 0x106266D0
	dxIndexBuffer::dxIndexBuffer() : unknown8(0), buffer(0), unknown10(0), unknown14(0), unknown18(1)
	{
		unknown34 = -1;
		// The block is cleared as a whole, not member by member
		memset(&state, 0, sizeof(state));
	}

	// FUNCTION: ENGINE 0x10626770
	void dxIndexBuffer::Create(const IndexBufferDescription* description)
	{
		int bytesPerIndex = gIndexSizes[description->indexSize];
		if (bytesPerIndex <= 0)
		{
			return;
		}
		unknown10 = description->usage;
		state.unknown8 = bytesPerIndex;
		state.unknown0 = description->count;
		state.unknown4 = description->count * bytesPerIndex;
		state.unknownC = description->indexSize;
		state.unknown10 = 0;
		unknown34 = gIndexFormatIndices[description->indexSize];
		unsigned int format = gD3DIndexFormats[unknown34];
		unsigned int usage = 0;
		unsigned int flags = description->usage;
		if ((flags & 1) != 0)
		{
			usage = D3DUSAGE_WRITEONLY;
		}
		if ((flags & 2) != 0)
		{
			usage |= D3DUSAGE_DYNAMIC;
			unknown18 = 0;
		}
		if (unknown18 == 0)
		{
			PoolAllocateIndexBuffer(state.unknown4, usage, format, &buffer);
		}
		else
		{
			gD3DDevice->lpVtbl->CreateIndexBuffer(gD3DDevice, state.unknown4, usage, format, D3DPOOL_MANAGED,
				&buffer, 0);
		}
		if (buffer == 0 && unknown18 == 1 && content::gLoadManager->IsCurrentThread())
		{
			while (buffer == 0)
			{
				gD3DDevice->lpVtbl->CreateIndexBuffer(gD3DDevice, state.unknown4, usage, format, D3DPOOL_MANAGED,
					&buffer, 0);
				core::ThreadSleep(100);
			}
		}
	}

	// FUNCTION: ENGINE 0x10626860
	void dxIndexBuffer::Unlock()
	{
		if (buffer != 0)
		{
			buffer->lpVtbl->Unlock(buffer);
		}
		state.unknown10 = 0;
		unknown8 = false;
		if (unknown14)
		{
			// The buffer was taken off the device for the lock: it goes back when no other one has been set since
			if (gCurrentIndices == 0)
			{
				gD3DDevice->lpVtbl->SetIndices(gD3DDevice, buffer);
				gCurrentIndices = this;
			}
			unknown14 = false;
		}
	}

	// FUNCTION: ENGINE 0x10626920
	int dxIndexBuffer::GetUnknown1C()
	{
		return state.unknown0;
	}

	// FUNCTION: ENGINE 0x10626950
	void dxIndexBuffer::Lock(dxIndexBufferState* lockState)
	{
		// The lock's pointer is the first local (declared later it would share the argument's slot)
		void* data = 0;
		int length = state.unknown8 * lockState->unknown0;
		if (gCurrentIndices == this)
		{
			Unknown106268F0();
			unknown14 = true;
		}
		unsigned int flags = 0;
		if ((unknown10 & 2) != 0 && (unknown10 & 1) != 0)
		{
			flags = D3DLOCK_DISCARD;
		}
		if (buffer != 0)
		{
			buffer->lpVtbl->Lock(buffer, 0, length, &data, flags);
			state.unknown10 = (int)data;
		}
		else
		{
			state.unknown10 = 0;
		}
		unknown8 = true;
		*lockState = state;
	}
}
