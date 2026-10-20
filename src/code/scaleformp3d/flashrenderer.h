// scaleformp3d::FlashRenderer (RTTI name; derives from GRenderer, vftable 0x10E8D704, 34 slots): the renderer the
// Flash player draws through, which turns its draw calls into pddi calls. Only the members the reconstructed
// functions touch are named; the rest is padding. All names are guesses.
#ifndef SCALEFORMP3D_FLASHRENDERER_H
#define SCALEFORMP3D_FLASHRENDERER_H

#include "code/container/arrayfixed.h"
#include "code/gfx/grenderer.h"

namespace scaleformp3d
{
	// The fill or the line style of a draw: what it is drawn with (0x94 bytes; its members are in the next unit)
	class FlashStyleState
	{
	public:
		// 0x10968040: no style
		void Disable();

		unsigned char unknown0[0x94];
	};

	class FlashRenderer : public GRenderer
	{
	public:
		virtual ~FlashRenderer();
		virtual bool GetRenderCaps(RenderCaps* caps);
		virtual GTexture* CreateTexture();
		virtual void BeginDisplay(GColor background, const void* viewport, float x0, float y0, float x1, float y1);
		virtual void EndDisplay();
		virtual void SetMatrix(const GMatrix2D& matrix);
		virtual void SetUserMatrix(const GMatrix2D& matrix);
		virtual void SetCxform(const GCxform& cxform);
		virtual void PushBlendMode(int mode);
		virtual void PopBlendMode();
		virtual void SetMarker(const GRendererMarker* marker);
		virtual void ClearMarker();
		virtual bool HasMarker();
		virtual void SetVertexData(const void* vertices, int count, int format, void* cache);
		virtual void SetIndexData(const void* indices, int count, int format, void* cache);
		virtual void ReleaseCachedData(void* data, int type);
		virtual void DrawIndexedTriList(int baseVertex, int minVertex, int vertexCount, int startIndex, int triangleCount);
		virtual void DrawLineStrip(int baseVertex, int lineCount);
		virtual void LineStyleDisable();
		virtual void LineStyleColor(GColor color);
		virtual void FillStyleDisable();
		virtual void FillStyleColor(GColor color);
		virtual void FillStyleBitmap(const void* fill);
		virtual void FillStyleGouraud(int type, const void* texture0, const void* texture1, const void* texture2);
		virtual void DrawBitmaps(void* bitmaps, int listSize, int startIndex, int count, const GTexture* texture,
			const GMatrix2D& matrix, void* cache);
		virtual void BeginSubmitMask(int mode);
		virtual void EndSubmitMask();
		virtual void DisableMask();
		virtual unsigned int GetRenderStats(void* stats, bool reset);
		virtual void Unknown7C();

		// 0x1095D1C0: the order of the colours the vertex format asks for
		void SelectColourOrder();
		// 0x1095D8D0: which shader the draws use
		void SetShaderIndex(int index);
		// 0x1095D380: whether the indices are not 16 bit
		bool HasWideIndices() const;

		unsigned char unknown10[0x20 - 0x10];
		float mConstant20[4];                  // 0x20
		float mConstant30[4];                  // 0x30
		unsigned char unknown40[0x50 - 0x40];
		float mColourMultiply[4];              // 0x50
		float mColourAdd[4];                   // 0x60
		unsigned char unknown70[0x80 - 0x70];
		bool mConstantsChanged;                // 0x80
		unsigned char unknown81[0x3158 - 0x81];
		int mShaderIndex;                      // 0x3158
		unsigned char unknown315C[0x321C - 0x315C];
		int mColourOrder;                      // 0x321C
		bool mUnknown3220;                     // 0x3220
		unsigned char unknown3221[3];
		GMatrix2D mUserMatrix;                 // 0x3224
		GMatrix2D mMatrix;                     // 0x323C
		GCxform mCxform;                       // 0x3254
		unsigned char unknown3274[0x327C - 0x3274];
		const void* mVertices;                 // 0x327C
		int mVertexCount;                      // 0x3280
		const void* mIndices;                  // 0x3284
		int mIndexCount;                       // 0x3288
		int mVertexFormat;                     // 0x328C
		int mIndexFormat;                      // 0x3290
		int mBlendMode;                        // 0x3294
		container::ArrayFixed<int, 64> mBlendModes; // 0x3298
		FlashStyleState mFillStyle;            // 0x339C
		FlashStyleState mLineStyle;            // 0x3430
		unsigned char unknown34C4[0x34DD - 0x34C4];
		bool mVerticesCurrent;                 // 0x34DD
		bool mIndicesCurrent;                  // 0x34DE
		unsigned char unknown34DF[0x3554 - 0x34DF];
		int mMarkerLayer;                      // 0x3554
	};
}

#endif
