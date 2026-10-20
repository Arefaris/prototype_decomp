// The small structures the pddi layer passes around: the description of an index buffer (and the state it keeps),
// and pure3d::PrimDrawDesc, what the device draws a primitive from (unit around 0x10611BB0 - 0x10611E10; the file name
// is guessed, no assert path survives). The constructors live apart from the users: the engine's callers do not see
// them, which shows in the registers they keep across the calls.
#include "code/pure3d/pddi/dx9/dxindexbuffer.h"
#include "code/pure3d/primstream.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10611BB0
	IndexBufferDescription::IndexBufferDescription(int newCount, int newIndexSize, unsigned int newUsage)
	{
		count = newCount;
		indexSize = newIndexSize;
		usage = newUsage;
	}

	// FUNCTION: ENGINE 0x10611BD0
	dxIndexBufferState::dxIndexBufferState() : unknown0(0), unknown4(0), unknown8(0), unknown10(0), unknown14(0)
	{
	}

	// FUNCTION: ENGINE 0x10611C30
	PrimDrawDesc::PrimDrawDesc(void* newFormat, const math::Matrix* newWorld, int count, void** parts,
		PrimGroupList* list, int d, int e, int f, int g)
	{
		streamCount = count;
		format = newFormat;
		world = newWorld;
		indices = (dxIndexBuffer*)list;
		primitiveType = d;
		this->count = 0;
		*(int*)&unknown38[0] = e;
		*(int*)&unknown38[4] = f;
		*(int*)&unknown38[8] = g;
		baseVertex = 0;
		startIndex = 0;
		int i;
		for (i = 0; i < count; i++)
		{
			streams[i] = (dxVertexBuffer*)parts[i];
		}
		for (unsigned int j = count; j < 8; j++)
		{
			streams[j] = 0;
		}
	}

	// FUNCTION: ENGINE 0x10611CB0
	PrimDrawDesc::PrimDrawDesc(void* newFormat, int newWorld, int count, PrimBuffer** buffers, int c, int d, int e, int f)
	{
		format = newFormat;
		streamCount = count;
		world = (const math::Matrix*)newWorld;
		indices = (dxIndexBuffer*)c;
		this->count = d;
		primitiveType = e;
		*(int*)&unknown38[0] = 0;
		*(int*)&unknown38[4] = 0;
		*(int*)&unknown38[8] = 0;
		baseVertex = 0;
		startIndex = 0;
		int i;
		for (i = 0; i < count; i++)
		{
			streams[i] = buffers[i];
		}
		for (unsigned int j = count; j < 8; j++)
		{
			streams[j] = 0;
		}
	}

	// FUNCTION: ENGINE 0x10611DC0
	PrimDrawDescGpuSkin::PrimDrawDescGpuSkin(void* newFormat, const math::Matrix* newWorld, int count, void** parts, int a,
		int b, int c, int kind, int d, int e)
		: PrimDrawDesc(newFormat, (int)newWorld, count, (PrimBuffer**)parts, a, b, c, e)
	{
		unknown4C = kind;
		unknown50 = d;
	}
}
