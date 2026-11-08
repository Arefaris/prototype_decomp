// pure3d::dxRenderStateCache: the Direct3D render states the device is in (unit 0x1061ED70 - 0x1061EF70; the file name
// is guessed, no assert path survives).
#include "code/pure3d/pddi/dx9/dxcontext.h"

namespace pure3d
{
	// Sets count words to -1
	static inline void Fill(int* words, int count)
	{
		unsigned int* p = (unsigned int*)words;
		for (int i = 0; i < count; i++)
		{
			p[i] = 0xFFFFFFFF;
		}
	}


	// FUNCTION: ENGINE 0x1061ED70
	void dxRenderStateCache::Reset()
	{
		Fill(samplerStates[0], 4 * 0x50);
		Fill(samplerStates[4], 16 * 0x50);
		Fill(renderStates, 400);
	}

	// FUNCTION: ENGINE 0x1061EE30
	dxRenderStateCache::dxRenderStateCache()
	{
		Fill(samplerStates[0], 4 * 0x50);
		Fill(samplerStates[4], 16 * 0x50);
		Fill(renderStates, 400);
	}

	// FUNCTION: ENGINE 0x1061EDB0
	dxRenderStateCache::~dxRenderStateCache()
	{
		Fill(samplerStates[0], 4 * 0x50);
		Fill(samplerStates[4], 16 * 0x50);
		Fill(renderStates, 400);
	}

	// FUNCTION: ENGINE 0x1061EE70
	void CreateRenderStateCache()
	{
		if (gRenderStateCache == 0)
		{
			gRenderStateCache = new dxRenderStateCache;
		}
		for (int i = 0; i < 256; i++)
		{
			gRenderStateCache->pixelConstantPasses[i] = 0;
			gRenderStateCache->vertexConstantPasses[i] = 0;
		}
		gRenderStateCache->pixelPass = 1;
		gRenderStateCache->vertexPass = 1;
		gRenderStateCache->constantsSkipped = 0;
		gRenderStateCache->constantsWritten = 0;
		gRenderStateCache->vertexDirtyFirst = 0x400;
		gRenderStateCache->pixelDirtyFirst = 0x400;
		gRenderStateCache->vertexDirtyLast = 0;
		gRenderStateCache->pixelDirtyLast = 0;
	}

	// FUNCTION: ENGINE 0x1061EF40
	void DestroyRenderStateCache()
	{
		if (gRenderStateCache != 0)
		{
			delete gRenderStateCache;
			gRenderStateCache = 0;
		}
	}
}
