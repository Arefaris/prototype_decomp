// scaleformp3d::FlashRenderer (the unit 0x1095CBB0 - 0x10966BE0; file name guessed from the class). Names are guesses.
#include "code/scaleformp3d/flashrenderer.h"
#include "code/container/arraydynamicnew.h"
#include "code/core/strings.h"

namespace pure3d
{
	class dxVertexBuffer;
	class dxIndexBuffer;
}

namespace scaleformp3d
{
	// FUNCTION: ENGINE 0x1095CEB0
	// EQUIVALENT: the same stores of the same values; the engine keeps the caps in edx, computes the blend modes first and
	// stores them last (53.4 %)
	bool FlashRenderer::GetRenderCaps(RenderCaps* caps)
	{
		bool flag = mUnknown3220;
		caps->mVertexFormats = 0x236B;
		caps->mMaxTextureSize = 0x500;
		caps->mBlendModes = (flag ? 0x18 : 0) | 3;
		caps->mCapBits = (flag ? 0x300 : 0) | 0xC;
		return true;
	}

	// FUNCTION: ENGINE 0x1095F5A0
	void FlashRenderer::SetMatrix(const GMatrix2D& matrix)
	{
		mMatrix.M[0][0] = matrix.M[0][0];
		mMatrix.M[0][1] = matrix.M[0][1];
		mMatrix.M[0][2] = matrix.M[0][2];
		mMatrix.M[1][0] = matrix.M[1][0];
		mMatrix.M[1][1] = matrix.M[1][1];
		mMatrix.M[1][2] = matrix.M[1][2];
	}

	// FUNCTION: ENGINE 0x1095F5E0
	void FlashRenderer::SetUserMatrix(const GMatrix2D& matrix)
	{
		mUserMatrix.M[0][0] = matrix.M[0][0];
		mUserMatrix.M[0][1] = matrix.M[0][1];
		mUserMatrix.M[0][2] = matrix.M[0][2];
		mUserMatrix.M[1][0] = matrix.M[1][0];
		mUserMatrix.M[1][1] = matrix.M[1][1];
		mUserMatrix.M[1][2] = matrix.M[1][2];
	}

	// FUNCTION: ENGINE 0x1095F620
	void FlashRenderer::SetCxform(const GCxform& cxform)
	{
		mCxform = cxform;
	}

	// FUNCTION: ENGINE 0x1095DB10
	void FlashRenderer::SetMarker(const GRendererMarker* marker)
	{
		if (marker != 0)
		{
			if (core::StrCmp(marker->mName, "markerLayer0") == 0)
			{
				mMarkerLayer = 1;
			}
			else if (core::StrCmp(marker->mName, "markerLayer1") == 0)
			{
				mMarkerLayer = 2;
			}
			else if (core::StrCmp(marker->mName, "markerLayer2") == 0)
			{
				mMarkerLayer = 3;
			}
			else if (core::StrCmp(marker->mName, "markerLayer3") == 0)
			{
				mMarkerLayer = 4;
			}
		}
	}

	// FUNCTION: ENGINE 0x1095DBB0
	void FlashRenderer::ClearMarker()
	{
		mMarkerLayer = 0;
	}

	// FUNCTION: ENGINE 0x1095DBC0
	bool FlashRenderer::HasMarker()
	{
		return mMarkerLayer != 0;
	}

	// FUNCTION: ENGINE 0x1095D130
	void FlashRenderer::SetIndexData(const void* indices, int count, int format, void* cache)
	{
		mIndices = indices;
		mIndexCount = count;
		mIndicesCurrent = false;
		mIndexFormat = format;
	}

	// FUNCTION: ENGINE 0x1095D1C0
	void FlashRenderer::SelectColourOrder()
	{
		switch (mVertexFormat)
		{
		case 2:
			break;
		case 3:
			mColourOrder = 1;
			break;
		case 4:
			mColourOrder = 0;
			break;
		default:
			mColourOrder = 2;
			break;
		}
	}

	// FUNCTION: ENGINE 0x1095E3C0
	void FlashRenderer::SetVertexData(const void* vertices, int count, int format, void* cache)
	{
		mVertices = vertices;
		mVertexFormat = format;
		mVertexCount = count;
		SelectColourOrder();
		mVerticesCurrent = false;
	}

	// FUNCTION: ENGINE 0x1095F590
	void FlashRenderer::ReleaseCachedData(void* data, int type)
	{
	}

	// FUNCTION: ENGINE 0x1095D8D0
	void FlashRenderer::SetShaderIndex(int index)
	{
		mShaderIndex = index;
	}

	// FUNCTION: ENGINE 0x1095D380
	bool FlashRenderer::HasWideIndices() const
	{
		return mIndexFormat != 1;
	}

	// FUNCTION: ENGINE 0x1095D870
	void FlashRenderer::Unknown7C()
	{
	}

	// FUNCTION: ENGINE 0x1095F640
	void FlashRenderer::FillStyleDisable()
	{
		mFillStyle.Disable();
	}

	// FUNCTION: ENGINE 0x1095F650
	void FlashRenderer::LineStyleDisable()
	{
		mLineStyle.Disable();
	}

	// FUNCTION: ENGINE 0x1095CF80
	void FlashRenderer::SetTextureMode(int wrap, bool smooth)
	{
		if (mWrapS != wrap || mSmooth != smooth)
		{
			mWrapS = wrap;
			mSmooth = smooth;
			mConstantsChanged = true;
		}
	}

	// FUNCTION: ENGINE 0x1095DA10
	// EQUIVALENT: the same loads, multiplies and stores; the engine keeps the scale in the register that held the first value
	// and loads the other adds into four registers in another order (85 %)
	void FlashRenderer::SetColourTransform(const GCxform* cxform)
	{
		float r = cxform->M[0][0];
		float g = cxform->M[1][0];
		float b = cxform->M[2][0];
		float a = cxform->M[3][0];
		mColourMultiply[0] = r;
		mColourMultiply[1] = g;
		mColourMultiply[2] = b;
		mColourMultiply[3] = a;
		float scale = 1.0f / 255.0f;
		float ar = cxform->M[0][1];
		float ag = cxform->M[1][1];
		float ab = cxform->M[2][1];
		float aa = cxform->M[3][1];
		mColourAdd[0] = ar * scale;
		mColourAdd[1] = ag * scale;
		mColourAdd[2] = ab * scale;
		mColourAdd[3] = aa * scale;
		mConstantsChanged = true;
	}

	// FUNCTION: ENGINE 0x1095DA90
	void FlashRenderer::SetConstant20(const float* values)
	{
		float x = values[0];
		float y = values[1];
		float w = values[2];
		mConstant20[0] = x;
		mConstant20[1] = y;
		mConstant20[2] = 0.0f;
		mConstant20[3] = w;
		mConstantsChanged = true;
	}

	// FUNCTION: ENGINE 0x1095DAC0
	void FlashRenderer::SetConstant30(const float* values)
	{
		float x = values[0];
		float y = values[1];
		float w = values[2];
		mConstant30[0] = x;
		mConstant30[1] = y;
		mConstant30[2] = 0.0f;
		mConstant30[3] = w;
		mConstantsChanged = true;
	}

	// FUNCTION: ENGINE 0x1095DAF0
	void FlashRenderer::SetTextureFlag(bool flag)
	{
		mTextureFlag = flag;
		mConstantsChanged = true;
		SelectColourOrder();
	}

	// FUNCTION: ENGINE 0x1095D880
	void FlashRenderer::GetRenderStats(GRenderStats* stats, bool reset)
	{
		if (stats != 0)
		{
			*stats = mStats;
		}
		if (reset)
		{
			mStats.mValues[0] = 0;
			mStats.mValues[1] = 0;
			mStats.mValues[2] = 0;
			mStats.mValues[3] = 0;
		}
	}

	FlashRenderer* gFlashRenderer;

	// FUNCTION: ENGINE 0x1095CFD0
	// EQUIVALENT: the same loads, conversions and stores in the same order; the engine loads the green, alpha and blue bytes
	// first into other registers (65.2 %)
	void SetDrawColour(const GColor* colour)
	{
		unsigned char green = colour->mGreen;
		unsigned char alpha = colour->mAlpha;
		unsigned char blue = colour->mBlue;
		unsigned char red = colour->mRed;
		float* values = gFlashRenderer->mColour;
		values[0] = (float)red;
		values[1] = (float)green;
		values[2] = (float)blue;
		values[3] = (float)alpha;
		gFlashRenderer->mConstantsChanged = true;
	}

	// FUNCTION: ENGINE 0x1095D5C0
	int GetVertexSize(int format)
	{
		switch (format)
		{
		case 1:
			return 4;
		case 2:
		case 3:
			return 8;
		case 4:
			return 12;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1095D600
	const short* ReadPosition(float* out, const short* in)
	{
		out[0] = (float)in[0];
		out[1] = (float)in[1];
		out[2] = 0.0f;
		return in + 2;
	}

	// FUNCTION: ENGINE 0x1095D030
	unsigned int FlashRenderer::SelectVertexLayout()
	{
		switch (mVertexFormat)
		{
		case 1:
		case 2:
			mUnknown3220 = false;
			break;
		case 3:
			mUnknown3220 = true;
			break;
		case 4:
			mUnknown3220 = true;
			return 0x6020;
		}
		return 0x2020;
	}

	// The members of the stack of blend modes that the engine keeps as functions of their own
	// FUNCTION: ENGINE 0x1095DC00 ; container::ArrayFixed<int,64>::Size
	int (container::ArrayFixed<int, 64>::*gKeepBlendModesSize)() const = &container::ArrayFixed<int, 64>::Size;

	// FUNCTION: ENGINE 0x1095DC10 ; container::ArrayFixed<int,64>::operator[]
	int& (container::ArrayFixed<int, 64>::*gKeepBlendModesAt)(int) = &container::ArrayFixed<int, 64>::operator[];

	// FUNCTION: ENGINE 0x1095DC80 ; container::ArrayFixed<int,64>::IsEmpty
	bool (container::ArrayFixed<int, 64>::*gKeepBlendModesIsEmpty)() const = &container::ArrayFixed<int, 64>::IsEmpty;

	// The members of the rings of vertex and index buffers that the engine keeps as functions of their own
	// FUNCTION: ENGINE 0x1095DC20 ; container::ArrayDynamicNew<classpure3d::dxVertexBuffer*>::Size
	unsigned int (container::ArrayDynamicNew<pure3d::dxVertexBuffer*>::*gKeepVertexRingSize)() const =
		&container::ArrayDynamicNew<pure3d::dxVertexBuffer*>::Size;

	// FUNCTION: ENGINE 0x1095DC30 ; container::ArrayDynamicNew<classpure3d::dxIndexBuffer*>::Size
	unsigned int (container::ArrayDynamicNew<pure3d::dxIndexBuffer*>::*gKeepIndexRingSize)() const =
		&container::ArrayDynamicNew<pure3d::dxIndexBuffer*>::Size;

	// FUNCTION: ENGINE 0x1095DC40 ; container::ArrayDynamicNew<classpure3d::dxVertexBuffer*>::IsFull
	bool (container::ArrayDynamicNew<pure3d::dxVertexBuffer*>::*gKeepVertexRingIsFull)() const =
		&container::ArrayDynamicNew<pure3d::dxVertexBuffer*>::IsFull;

	// FUNCTION: ENGINE 0x1095DC50 ; container::ArrayDynamicNew<classpure3d::dxVertexBuffer*>::operator[]
	pure3d::dxVertexBuffer*& (container::ArrayDynamicNew<pure3d::dxVertexBuffer*>::*gKeepVertexRingAt)(int) =
		&container::ArrayDynamicNew<pure3d::dxVertexBuffer*>::operator[];

	// FUNCTION: ENGINE 0x1095E7D0 ; container::ArrayFixed<int,64>::PushBack
	bool (container::ArrayFixed<int, 64>::*gKeepBlendModesPushBack)(const int&) = &container::ArrayFixed<int, 64>::PushBack;

	// FUNCTION: ENGINE 0x1095E8B0 ; container::ArrayFixed<int,64>::Reset
	void (container::ArrayFixed<int, 64>::*gKeepBlendModesReset)() = &container::ArrayFixed<int, 64>::Reset;

	// FUNCTION: ENGINE 0x1095E880 ; container::ArrayDynamicNew<classpure3d::dxVertexBuffer*>::PushBack
	bool (container::ArrayDynamicNew<pure3d::dxVertexBuffer*>::*gKeepVertexRingPushBack)(pure3d::dxVertexBuffer* const&) =
		&container::ArrayDynamicNew<pure3d::dxVertexBuffer*>::PushBack;

	// FUNCTION: ENGINE 0x1095EDB0 ; container::ArrayDynamicNew<classpure3d::dxVertexBuffer*>::Clear
	void (container::ArrayDynamicNew<pure3d::dxVertexBuffer*>::*gKeepVertexRingClear)() =
		&container::ArrayDynamicNew<pure3d::dxVertexBuffer*>::Clear;
}
