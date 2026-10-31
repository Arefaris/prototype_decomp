// The render schemes of the pass tree and their descriptions (unit around 0x107A05F0 - 0x107A1F70; file name guessed). Names are
// guesses.
#include "code/pure3d/renderscheme.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x107A05F0
	SelectionRenderScheme::~SelectionRenderScheme()
	{
	}

	// FUNCTION: ENGINE 0x107A06F0
	ShadowDebugRenderScheme::~ShadowDebugRenderScheme()
	{
	}

	// FUNCTION: ENGINE 0x107A0700
	void ShadowDebugRenderScheme::Begin()
	{
		RenderScheme::Begin();
		pddi->Unknown8(1);
	}

	// FUNCTION: ENGINE 0x107A0720
	void ShadowDebugRenderScheme::End()
	{
		pddi->Unknown8(0);
		RenderScheme::End();
	}

	// FUNCTION: ENGINE 0x107A0740
	Debug2DPassDesc::Debug2DPassDesc(const void* name) : PassDesc(name, 1)
	{
		unknown18 = false;
		unknown19 = false;
	}

	// FUNCTION: ENGINE 0x107A0DE0
	PrimColourRenderScheme::~PrimColourRenderScheme()
	{
	}

	// FUNCTION: ENGINE 0x107A1170
	OrthoNormalRenderScheme::~OrthoNormalRenderScheme()
	{
	}

	// FUNCTION: ENGINE 0x107A1350
	StandardRenderScheme::~StandardRenderScheme()
	{
	}

	// FUNCTION: ENGINE 0x107A1360
	void StandardRenderScheme::Begin()
	{
		RenderScheme::Begin();
		pddi->Unknown8(1);
	}

	// FUNCTION: ENGINE 0x107A1380
	void StandardRenderScheme::End()
	{
		pddi->Unknown8(0);
		RenderScheme::End();
	}

	// FUNCTION: ENGINE 0x107A1900
	BasicRenderScheme::~BasicRenderScheme()
	{
	}
}
