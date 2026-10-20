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
}
