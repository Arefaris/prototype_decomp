// pure3d::dxIndexBuffer, the Direct3D 9 index buffer of the pddi layer (unit around 0x106266D0 - 0x10626920; the
// file name is guessed, no assert path survives).
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
	// EQUIVALENT: register allocation: the engine clears the state block with a zero it materialises in eax after the
	// state's constructor call, this compiler reuses the zero the initialiser list left in ebx (64.9 %)
	dxIndexBuffer::dxIndexBuffer() : unknown8(0), buffer(0), unknown10(0), unknown14(0), unknown18(1)
	{
		unknown34 = -1;
		state.Clear();
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
		if (buffer == 0 && unknown18 == 1 && gRenderDevice->IsCurrentThread())
		{
			while (buffer == 0)
			{
				gD3DDevice->lpVtbl->CreateIndexBuffer(gD3DDevice, state.unknown4, usage, format, D3DPOOL_MANAGED,
					&buffer, 0);
				core::ThreadSleep(100);
			}
		}
	}

	// FUNCTION: ENGINE 0x10626920
	int dxIndexBuffer::GetUnknown1C()
	{
		return state.unknown0;
	}
}
