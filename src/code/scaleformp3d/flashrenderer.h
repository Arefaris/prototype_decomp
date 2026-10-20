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

	// 0x1095CFD0: the colour the draws are made in, as four floats in the renderer in use
	void SetDrawColour(const GColor* colour);
	// 0x1131FD68: the renderer in use
	class FlashRenderer;
	extern FlashRenderer* gFlashRenderer;
	// 0x1095D5C0: the bytes a vertex of the format takes in the stream
	int GetVertexSize(int format);
	// 0x1095D600: reads the position of a vertex of two 16 bit coordinates; answers where the next field starts
	const short* ReadPosition(float* out, const short* in);

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
		virtual void GetRenderStats(GRenderStats* stats, bool reset);
		virtual void Unknown7C();

		// 0x1095D030: the flags of the vertex layout the format asks for (and whether the caps flag is on for it)
		unsigned int SelectVertexLayout();
		// 0x1095CF80: the wrap mode of the texture and whether it is smoothed
		void SetTextureMode(int wrap, bool smooth);
		// 0x1095DA10: the colour transform as the multiplies and the adds (the adds scaled to 0 - 1)
		void SetColourTransform(const GCxform* cxform);
		// 0x1095DA90 / 0x1095DAC0: two values and a third (the middle of the vector is zero)
		void SetConstant20(const float* values);
		void SetConstant30(const float* values);
		// 0x1095DAF0: the second flag of the texture state, and the colour order that goes with it
		void SetTextureFlag(bool flag);
		// 0x1095D1C0: the order of the colours the vertex format asks for
		void SelectColourOrder();
		// 0x1095D8D0: which shader the draws use
		void SetShaderIndex(int index);
		// 0x1095D380: whether the indices are not 16 bit
		bool HasWideIndices() const;

		unsigned char unknown10[0x20 - 0x10];
		float mConstant20[4];                  // 0x20
		float mConstant30[4];                  // 0x30
		float mColour[4];                      // 0x40
		float mColourMultiply[4];              // 0x50
		float mColourAdd[4];                   // 0x60
		void* mTexture;                        // 0x70
		int mWrapS : 2;                        // 0x74
		int mWrapT : 2;
		int unknown74Bits : 28;
		bool mSmooth : 1;                      // 0x78
		bool mTextureFlag : 1;
		unsigned char unknown78Bits : 6;
		unsigned char unknown79[7];
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
		unsigned char unknown34C4[0x34C8 - 0x34C4];
		GRenderStats mStats;                   // 0x34C8
		unsigned char unknown34D8[0x34DD - 0x34D8];
		bool mVerticesCurrent;                 // 0x34DD
		bool mIndicesCurrent;                  // 0x34DE
		unsigned char unknown34DF[0x3554 - 0x34DF];
		int mMarkerLayer;                      // 0x3554
	};
}

#endif
