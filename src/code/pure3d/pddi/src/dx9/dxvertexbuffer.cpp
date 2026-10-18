// pure3d::dxVertexBuffer, the Direct3D 9 vertex buffer of the pddi layer (unit around 0x106262D0 - 0x106266D0; the
// file name is guessed, no assert path survives).
#include <new>
#include <string.h>

#include "code/core/thread.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/dx9/dxdefaultpoolmanager.h"
#include "code/pure3d/pddi/dx9/dxvertexbuffer.h"

namespace pure3d
{
	// The names of the vertex semantics a shader parameter can have (their strings sit in the static initialisers at
	// 0x10D67xxx; every address is a name guess)
	extern core::Name<core::CaseInsensitiveKey32> gName1127F180;  // "position"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F16C;  // "weights"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F1B8;  // "normal"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F0C8;  // "colour"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F130;  // "colour0"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F2D0;  // "colour1"
	extern core::Name<core::CaseInsensitiveKey32> gName1127F0B0;  // "fog"
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
		if (unknownC == 0 && unknown130 == 1 && gRenderDevice->IsCurrentThread())
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
}
