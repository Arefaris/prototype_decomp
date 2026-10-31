// pure3d::dxVertexBuffer, the Direct3D 9 vertex buffer of the pddi layer (unit around 0x106262D0 - 0x106266D0; the
// file name is guessed, no assert path survives).
#include <malloc.h>
#include <new>
#include <string.h>

#include "code/content/loadmanager.h"
#include "code/core/thread.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/dx9/dxdefaultpoolmanager.h"
#include "code/pure3d/pddi/dx9/dxvertexbuffer.h"
#include "code/pure3d/primitive.h"
#include "code/core/namecopy.h"

namespace pure3d
{
	// The names of the vertex semantics a shader parameter can have (their strings sit in the static initialisers at
	// 0x10D67xxx; every address is a name guess)
	extern core::Name<core::CaseInsensitiveKey32> gName1127F180;  // "position"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F16C;  // "weights"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1B8;  // "normal"
	core::Name<core::CaseInsensitiveKey32> gName1127F0C8 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colour", 0)));  // "colour"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F130;  // "colour0"
	core::Name<core::CaseInsensitiveKey32> gName1127F2D0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colour1", 0)));  // "colour1"
	core::Name<core::CaseInsensitiveKey32> gName1127F0B0 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("fog", 0)));  // "fog"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1E4;  // "tex0"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1E8;  // "tex1"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1EC;  // "tex2"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1F0;  // "tex3"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1F4;  // "tex4"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1F8;  // "tex5"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1FC;  // "tex6"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F200;  // "tex7"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1BC;  // "binormal"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1DC;  // "tangent"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F0B4;  // "indices"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F340;  // "blendoffset"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F31C;  // "blendnormal"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F0D0;  // "hdrColour"

	// The Direct3D usage of a vertex semantic and its index (D3DDECLUSAGE)
	struct VertexUsage
	{
		int usage;
		int index;
	};

	// The two bits of the pddi usage that reach Direct3D: 8 for a write-only buffer, 0x200 for a dynamic one
	enum
	{
		D3DUSAGE_WRITEONLY = 8,
		D3DUSAGE_DYNAMIC = 0x200
	};

	// FUNCTION: ENGINE 0x10625BF0
	// The Direct3D usage a semantic name stands for; a name that is none of them leaves the result as it was
	static VertexUsage GetVertexUsage(const core::Name<core::CaseInsensitiveKey32>& name)
	{
		VertexUsage result;
		if (name == gName1127F180)
		{
			result.usage = 0;
			result.index = 0;
		}
		else if (name == gName1127F16C)
		{
			result.usage = 1;
			result.index = 0;
		}
		else if (name == gName1127F1B8)
		{
			result.usage = 3;
			result.index = 0;
		}
		else if (name == gName1127F0C8)
		{
			result.usage = 10;
			result.index = 0;
		}
		else if (name == gName1127F130)
		{
			result.usage = 10;
			result.index = 0;
		}
		else if (name == gName1127F2D0)
		{
			result.usage = 10;
			result.index = 1;
		}
		else if (name == gName1127F0B0)
		{
			result.usage = 11;
			result.index = 0;
		}
		else if (name == gName1127F1E4)
		{
			result.usage = 5;
			result.index = 0;
		}
		else if (name == gName1127F1E8)
		{
			result.usage = 5;
			result.index = 1;
		}
		else if (name == gName1127F1EC)
		{
			result.usage = 5;
			result.index = 2;
		}
		else if (name == gName1127F1F0)
		{
			result.usage = 5;
			result.index = 3;
		}
		else if (name == gName1127F1F4)
		{
			result.usage = 5;
			result.index = 4;
		}
		else if (name == gName1127F1F8)
		{
			result.usage = 5;
			result.index = 5;
		}
		else if (name == gName1127F1FC)
		{
			result.usage = 5;
			result.index = 6;
		}
		else if (name == gName1127F200)
		{
			result.usage = 5;
			result.index = 7;
		}
		else if (name == gName1127F1BC)
		{
			result.usage = 5;
			result.index = 6;
		}
		else if (name == gName1127F1DC)
		{
			result.usage = 5;
			result.index = 7;
		}
		else if (name == gName1127F0B4)
		{
			result.usage = 2;
			result.index = 0;
		}
		else if (name == gName1127F0B4)
		{
			result.usage = 2;
			result.index = 0;
		}
		else if (name == gName1127F340)
		{
			result.usage = 5;
			result.index = 5;
		}
		else if (name == gName1127F31C)
		{
			result.usage = 5;
			result.index = 4;
		}
		else if (name == gName1127F0D0)
		{
			result.usage = 5;
			result.index = 6;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x106262D0
	dxVertexBuffer::dxVertexBuffer() : unknown8(0), unknownC(0), unknown10(0), unknown130(1), unknown134(0),
		unknown138(-1)
	{
		memset(&declaration, 0, sizeof(declaration));
	}

	// FUNCTION: ENGINE 0x10625E30
	dxVertexBuffer::~dxVertexBuffer()
	{
		if (unknown134 != 0)
		{
			delete[] unknown134;
		}
		if (unknownC != 0)
		{
			if (unknown130 == 1)
			{
				unknownC->Release();
			}
			else
			{
				FreePooledVertexBuffer(&unknownC);
			}
		}
		unknownC = 0;
		unknown134 = 0;
		unknown138 = -1;
	}

	// FUNCTION: ENGINE 0x10626330 is the compiler's scalar deleting destructor of this class (slot 2)
	// FUNCTION: ENGINE 0x10625EA0 is the kept copy of the shader parameter's assignment

	// FUNCTION: ENGINE 0x106258D0
	void dxVertexBuffer::Unlock()
	{
		if (unknownC != 0)
		{
			unknownC->lpVtbl->Unlock(unknownC);
		}
		declaration.unknown108 = 0;
		unknown8 = false;
	}

	// FUNCTION: ENGINE 0x10625F00
	// EQUIVALENT: the engine reads the description's flags before the locked block's address for the two stores
	// behind the lock (93.8 %); the stores and the call after them are the same
	void dxVertexBuffer::Lock(dxVertexDeclaration* description, int count)
	{
		unsigned int flags = 0;
		void* data = 0;
		if (description->unknown110 != 0)
		{
			if ((description->unknown110 & 1) != 0)
			{
				flags = 0x10;
			}
			if ((description->unknown110 & 2) != 0)
			{
				flags |= 0x1000;
			}
		}
		if ((unknown10 & 2) != 0 && (unknown10 & 1) != 0)
		{
			flags |= 0x2000;
		}
		if (unknownC != 0)
		{
			unknownC->lpVtbl->Lock(unknownC, 0, declaration.elements[0].unknown9 * count, &data, flags);
		}
		else
		{
			declaration.unknown108 = 0;
		}
		declaration.unknown110 = description->unknown110;
		declaration.unknown108 = (int)data;
		*description = declaration;
		unknown8 = true;
	}

	// FUNCTION: ENGINE 0x10625FA0
	void dxVertexBuffer::Unknown10625FA0(ShaderParameters* parameters)
	{
		parameters->unknown0 = declaration.unknown0;
		parameters->unknown4 = declaration.unknown4;
		parameters->unknown8 = unknown10;
		for (int i = 0; i < declaration.unknown4; i++)
		{
			parameters->parameters[i] = declaration.elements[i];
		}
	}

	// FUNCTION: ENGINE 0x10625930
	// NONMATCHING: the loops are the engine's but its allocation keeps the running element count in a stack slot and the
	// element base in a register (best 33.1 %)
#ifdef NONMATCHING
	int BuildVertexDeclaration(dxVertexBuffer* const* streams, unsigned int count)
	{
		if (count != 1)
		{
			unsigned int total = 0;
			for (unsigned int i = 0; i < count; i++)
			{
				total += streams[i]->declaration.unknown4;
			}
			D3DVERTEXELEMENT9* elements = (D3DVERTEXELEMENT9*)_alloca((total + 1) * sizeof(D3DVERTEXELEMENT9));
			unsigned int written = 0;
			unsigned short stream = 0;
			for (unsigned int i = 0; i < count; i++)
			{
				dxVertexBuffer* buffer = streams[i];
				unsigned int elementCount = buffer->declaration.unknown4;
				D3DVERTEXELEMENT9* out = elements + written;
				written += elementCount;
				for (unsigned int j = 0; j < elementCount; j++)
				{
					out->Stream = buffer->unknown134[j].Stream + stream;
					out->Offset = buffer->unknown134[j].Offset;
					out->Type = buffer->unknown134[j].Type;
					out->Method = buffer->unknown134[j].Method;
					out->Usage = buffer->unknown134[j].Usage;
					out->UsageIndex = buffer->unknown134[j].UsageIndex;
					out++;
				}
				if (buffer->unknown12C >= 0)
				{
					stream += 2;
				}
				else
				{
					stream += 1;
				}
			}
			elements[total].Stream = 0xFF;
			elements[total].Offset = 0;
			elements[total].Type = 0x11;
			elements[total].Method = 0;
			elements[total].Usage = 0;
			elements[total].UsageIndex = 0;
			return FindVertexDeclaration(elements);
		}
		return FindVertexDeclaration(streams[0]->unknown134);
	}
#endif

	// FUNCTION: ENGINE 0x10625900
	int dxVertexBuffer::GetUnknown14()
	{
		return declaration.unknown0;
	}

	// FUNCTION: ENGINE 0x10626350
	void dxVertexBuffer::Create(const VertexBufferDescription* description)
	{
		if (description->unknown0 == 0)
		{
			return;
		}
		unknown134 = new D3DVERTEXELEMENT9[description->unknown4 + 1];
		declaration.unknown0 = description->unknown0;
		declaration.unknown4 = description->unknown4;
		unsigned int offset = 0;
		unsigned int length = description->unknown110 ? description->unknown114 : 0;
		unsigned int stride = 0;
		for (unsigned int i = 0; i < (unsigned int)description->unknown4; i++)
		{
			declaration.elements[i] = description->parameters[i];
			if (!description->unknown110)
			{
				if (declaration.elements[i].unknown8 == 8)
				{
					declaration.elements[i].unknownA = 1;
				}
				unsigned int size = (declaration.GetElementSize(i) + 3) & 0xFFFFFFFC;
				unsigned int total = description->unknown0 * size;
				stride += size;
				declaration.elements[i].value = offset;
				offset += size;
				length += total;
			}
		}
		if (!description->unknown110)
		{
			for (unsigned int i = 0; i < (unsigned int)description->unknown4; i++)
			{
				declaration.elements[i].unknown9 = stride;
			}
		}
		unknown128 = 0;
		unknown12C = -1;
		for (unsigned int i = 0; i < (unsigned int)description->unknown4; i++)
		{
			VertexUsage usage = GetVertexUsage(declaration.elements[i].name);
			int type;
			if (description->parameters[i].unknownC)
			{
				type = gVertexTypesNormalised[gVertexKindGroups[declaration.elements[i].unknown8] * 4 +
					declaration.elements[i].unknownA];
			}
			else
			{
				type = gVertexTypes[gVertexKindGroups[declaration.elements[i].unknown8] * 4 +
					declaration.elements[i].unknownA];
			}
			unknown134[i].Stream = 0;
			unknown134[i].Offset = declaration.elements[i].value;
			unknown134[i].Type = type;
			unknown134[i].Method = 0;
			unknown134[i].Usage = usage.usage;
			unknown134[i].UsageIndex = usage.index;
		}
		unknown134[description->unknown4].Stream = 0xFF;
		unknown134[description->unknown4].Offset = 0;
		unknown134[description->unknown4].Type = 0x11;
		unknown134[description->unknown4].Method = 0;
		unknown134[description->unknown4].Usage = 0;
		unknown134[description->unknown4].UsageIndex = 0;
		unknown130 = 1;
		unsigned int usage = 0;
		if ((description->unknown8 & 1) != 0)
		{
			usage = D3DUSAGE_WRITEONLY;
		}
		if ((description->unknown8 & 2) != 0)
		{
			usage |= D3DUSAGE_DYNAMIC;
			unknown130 = 0;
		}
		if (unknown130 == 0)
		{
			PoolAllocateVertexBuffer(length, usage, 0, &unknownC, 0);
		}
		else
		{
			gD3DDevice->lpVtbl->CreateVertexBuffer(gD3DDevice, length, usage, 0, D3DPOOL_MANAGED, &unknownC, 0);
		}
		if (unknownC == 0 && unknown130 == 1 && content::gLoadManager->IsCurrentThread())
		{
			while (unknownC == 0)
			{
				gD3DDevice->lpVtbl->CreateVertexBuffer(gD3DDevice, length, usage, 0, D3DPOOL_MANAGED, &unknownC, 0);
				core::ThreadSleep(100);
			}
		}
		declaration.unknown108 = 0;
		unknown10 = description->unknown8;
	}

	// FUNCTION: ENGINE 0x10625A80
	void Unknown10625A80()
	{
		for (unsigned int stream = 0; stream < gBoundStreamCount; stream++)
		{
			gD3DDevice->lpVtbl->SetStreamSource(gD3DDevice, stream, 0, 0, 0);
			gBoundStreams[stream] = 0;
		}
		gBoundStreamCount = 0;
	}

	// FUNCTION: ENGINE 0x106268F0
	void Unknown106268F0()
	{
		gD3DDevice->lpVtbl->SetIndices(gD3DDevice, 0);
		gCurrentIndices = 0;
	}

	// Sets the streams of a draw on the device where they are not set already; the element a stream is read from
	// and its second element (when it has one) take a stream each
	static __forceinline unsigned int BindStreams(IDirect3DDevice9* device, dxVertexBuffer* const* streams,
		const unsigned int& count)
	{
		unsigned int slot = 0;
		for (unsigned int i = 0; i < count; i++, streams++)
		{
			dxVertexBuffer* buffer = *streams;
			if (gBoundStreams[slot] != buffer)
			{
				gBoundStreams[slot] = buffer;
				device->lpVtbl->SetStreamSource(device, slot, buffer->unknownC,
					buffer->declaration.elements[buffer->unknown128].value,
					buffer->declaration.elements[buffer->unknown128].unknown9);
				slot++;
				if (buffer->unknown12C >= 0)
				{
					gBoundStreams[slot] = 0;
					device->lpVtbl->SetStreamSource(device, slot, buffer->unknownC,
						buffer->declaration.elements[buffer->unknown12C].value,
						buffer->declaration.elements[buffer->unknown12C].unknown9);
					slot++;
				}
			}
			else
			{
				slot += (buffer->unknown12C >= 0) + 1;
			}
		}
		return slot;
	}

	// FUNCTION: ENGINE 0x10626030
	// NONMATCHING: the engine keeps the stream pointer in a register and the stream counter on the stack, this
	// compiler the other way round (best 23.0 %); the same stores and calls in the same order
#ifdef NONMATCHING
	void Unknown10626030(const PrimDrawDesc* desc)
	{
		IDirect3DDevice9* device = gD3DDevice;
		dxVertexBuffer* first = desc->streams[0];
		if (first->unknown138 == -1)
		{
			first->unknown138 = BuildVertexDeclaration(desc->streams, desc->streamCount);
		}
		SelectVertexDeclaration(first->unknown138);
		unsigned int slot = BindStreams(device, desc->streams, desc->streamCount);
		if (gBoundStreamCount <= slot)
		{
			gBoundStreamCount = slot;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10626180
	// NONMATCHING: the engine keeps the stream pointer in a register and the stream counter on the stack, this
	// compiler the other way round (best 59.4 %); the same stores and calls in the same order
#ifdef NONMATCHING
	void Unknown10626180(const dxDrawBatch* batch)
	{
		IDirect3DDevice9* device = gD3DDevice;
		dxVertexBuffer* first = batch->streams[0];
		if (first->unknown138 == -1 || batch->rebuildDeclaration)
		{
			first->unknown138 = BuildVertexDeclaration(batch->streams, batch->streamCount);
		}
		SelectVertexDeclaration(first->unknown138);
		unsigned int slot = BindStreams(device, batch->streams, batch->streamCount);
		if (gBoundStreamCount <= slot)
		{
			gBoundStreamCount = slot;
		}
	}
#endif

	// The engine's callers hold the vertex buffers and the index buffer of a mesh or a skin as groups of a primitive
	// (PrimGroupList); the batch they fill is the device's draw batch
	// FUNCTION: ENGINE 0x10625910
	PrimGroupList* PrimGroupList::AddGroup(PrimBatch* batch, PrimGroupList* group)
	{
		dxVertexBuffer* buffer = (dxVertexBuffer*)this;
		dxDrawBatch* drawBatch = (dxDrawBatch*)batch;
		int index = (int)group;
		drawBatch->streams[index] = buffer;
		index++;
		drawBatch->streamCount = index;
		if (drawBatch->indexCount == 0)
		{
			drawBatch->indexCount = buffer->declaration.unknown0;
		}
		return (PrimGroupList*)index;
	}
}

namespace pure3d
{
	core::Name<core::CaseInsensitiveKey32> gInstanceIndices = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("instanceIndices", 0)));
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D67520
// FUNCTION: ENGINE 0x10D675A0
// FUNCTION: ENGINE 0x10D676A0
// FUNCTION: ENGINE 0x10D67AE0
// FUNCTION: ENGINE 0x10D86DE0
// FUNCTION: ENGINE 0x10D86E00
// FUNCTION: ENGINE 0x10D86E40
// FUNCTION: ENGINE 0x10D86ED0
