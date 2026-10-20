// GRenderer of the Scaleform GFx library inside the engine DLL (RTTI: GRenderer : GRefCountBase<GRenderer>, vftable
// 0x10E8D674, 34 slots): the interface the player draws through. The names of the slots are guesses from what the
// engine's implementation of each does; the arguments of the pure ones are as many as the implementation takes.
#ifndef GFX_GRENDERER_H
#define GFX_GRENDERER_H

#include "code/gfx/gcolor.h"
#include "code/gfx/gmatrix.h"
#include "code/gfx/grefcount.h"

// The colour transform of a draw: for each channel, what it is multiplied by and what is added (32 bytes)
struct GCxform
{
	float M[4][2];
};

// What the player names a part of what it draws by (a name and nothing else is known)
struct GRendererMarker
{
	const char* mName;
};

class GTexture;

class GRenderer : public GRefCountBase<GRenderer>
{
public:
	// What a renderer can do, as it tells the player
	struct RenderCaps
	{
		unsigned int mCapBits;
		unsigned int mBlendModes;
		unsigned int mVertexFormats;
		unsigned int mMaxTextureSize;
	};

	// 0x1095DFA0
	GRenderer();
	// 0x1095DEE0 (the deleting destructor is 0x1095DF70)
	virtual ~GRenderer();
	virtual bool GetRenderCaps(RenderCaps* caps) = 0;
	virtual GTexture* CreateTexture() = 0;
	// slots 3 and 4 (0x1095DEF0 / 0x1095DF00): nothing in the base
	virtual void Unknown0C();
	virtual void Unknown10();
	virtual void BeginDisplay(GColor background, const void* viewport, float x0, float y0, float x1, float y1) = 0;
	virtual void EndDisplay() = 0;
	virtual void SetMatrix(const GMatrix2D& matrix) = 0;
	virtual void SetUserMatrix(const GMatrix2D& matrix) = 0;
	virtual void SetCxform(const GCxform& cxform) = 0;
	virtual void PushBlendMode(int mode) = 0;
	virtual void PopBlendMode() = 0;
	// slots 12 - 14 (0x1095DF10 - 0x1095DF30): nothing in the base
	virtual void SetMarker(const GRendererMarker* marker);
	virtual void ClearMarker();
	virtual bool HasMarker();
	virtual void SetVertexData(const void* vertices, int count, int format, void* cache) = 0;
	virtual void SetIndexData(const void* indices, int count, int format, void* cache) = 0;
	virtual void ReleaseCachedData(void* data, int type) = 0;
	virtual void DrawIndexedTriList(int baseVertex, int minVertex, int vertexCount, int startIndex, int triangleCount) = 0;
	virtual void DrawLineStrip(int baseVertex, int lineCount) = 0;
	virtual void LineStyleDisable() = 0;
	virtual void LineStyleColor(GColor color) = 0;
	virtual void FillStyleDisable() = 0;
	virtual void FillStyleColor(GColor color) = 0;
	virtual void FillStyleBitmap(const void* fill) = 0;
	virtual void FillStyleGouraud(int type, const void* texture0, const void* texture1, const void* texture2) = 0;
	virtual void DrawBitmaps(void* bitmaps, int listSize, int startIndex, int count, const GTexture* texture,
		const GMatrix2D& matrix, void* cache) = 0;
	virtual void BeginSubmitMask(int mode) = 0;
	virtual void EndSubmitMask() = 0;
	virtual void DisableMask() = 0;
	virtual unsigned int GetRenderStats(void* stats, bool reset) = 0;
	virtual void Unknown7C() = 0;
	// slots 32 and 33 (0x1095DF40 / 0x1095DF50)
	virtual bool Unknown80(int argument);
	virtual void Unknown84(int argument);
};

#endif
