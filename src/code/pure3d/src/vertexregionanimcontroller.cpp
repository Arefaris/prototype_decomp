// pure3d::VertexRegionAnimController (unit around 0x1072EBD0 - 0x10730570; file name guessed from the class). Names are
// guesses.
#include "code/engine/driving/carattributes.h"
#include "code/engine/nis/nis.h"
#include <new>

#include "code/core/refptr.h"
#include "code/pure3d/channel.h"
#include "code/pure3d/loaders/drawableloaders.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x107303F0
	// NONMATCHING: the engine releases the regions through a counted loop over a copy of the first pointer and clears
	// the list behind the loop (about 40 %)
#ifdef NONMATCHING
	VertexRegionAnimController::~VertexRegionAnimController()
	{
		core::SafeRelease(mKeyFrames);
		VertexDeformRegion** first = mRegions.items;
		int regionCount = mRegions.end - first;
		for (VertexDeformRegion** region = first; regionCount != 0; regionCount--, region++)
		{
			core::SafeRelease(*region);
		}
		mRegions.end = first;
		delete mOffsets;
		mOffsets = 0;
		mRegions.end = first;
	}
#endif

	// FUNCTION: ENGINE 0x107302C0
	// NONMATCHING: the engine reloads the expression into ecx right after the allocation (96.0 %)
#ifdef NONMATCHING
	VertexRegionAnimController::VertexRegionAnimController(const VertexRegionAnimController& other) : SimpleFrameController(other), mRegions()
	{
		mKeyFrames = 0;
		mPrimitive = 0;
		mMeshState = 0;
		mExpression = 0;
		mOffsets = 0;
		mChanged = true;
		core::RefAssign(mKeyFrames, other.mKeyFrames);
		mPrimitive = other.mPrimitive;
		mMeshState = other.mMeshState;
		mExpression = other.mExpression;
		if (mExpression != 0)
		{
			delete mOffsets;
			float* offsets = new float[mExpression->count];
			VertexOffsetList* expression = mExpression;
			mOffsets = offsets;
			unsigned int count = expression->count;
			for (unsigned int i = 0; i < count; i++)
			{
				mOffsets[i] = 0.0f;
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x10730270
	VertexRegionAnimController::VertexRegionAnimController() : mRegions()
	{
		mKeyFrames = 0;
		mPrimitive = 0;
		mMeshState = 0;
		mExpression = 0;
		mOffsets = 0;
		((math::Matrix*)unknown98)->Identity();
	}

	// FUNCTION: ENGINE 0x1072EBD0
	bool VertexRegionAnimController::Unknown25()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x1072EBE0
	bool VertexRegionAnimController::IsSupported(Animation* animation)
	{
		if (animation != 0 && animation->mGroupCount > 0)
		{
			if (animation->numFrames == engine::driving::gTwo)
			{
				return animation->mType == 0x58545256;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1072EC20
	void VertexRegionAnimController::SetTarget(Entity* target)
	{
	}

	// FUNCTION: ENGINE 0x10730460
	VertexRegionAnimController* VertexRegionAnimController::Clone()
	{
		return new VertexRegionAnimController(*this);
	}

	// FUNCTION: ENGINE 0x1072EB40
	VertexDeformRegion::VertexDeformRegion() : RefCounted(NO_BARRIER), mMesh(0), mChanged(true)
	{
	}

	// FUNCTION: ENGINE 0x1072F0D0
	VertexDeformRegion::~VertexDeformRegion()
	{
		core::SafeRelease(mMesh);
	}

	// FUNCTION: ENGINE 0x1072F0F0
	void VertexDeformRegion::SetMesh(Mesh* mesh)
	{
		core::RefAssign(mMesh, mesh);
	}

	// FUNCTION: ENGINE 0x1072F110
	VertexEllipseRegionDeformation::VertexEllipseRegionDeformation()
	{
	}

	// FUNCTION: ENGINE 0x1072F120
	VertexEllipseRegionDeformation::~VertexEllipseRegionDeformation()
	{
	}

	// FUNCTION: ENGINE 0x1072EB70
	void VertexDeformRegion::SetUnknown1C(const math::Vector* value)
	{
		unknown1C.x = value->x;
		unknown1C.y = value->y;
		unknown1C.z = value->z;
		_ReadWriteBarrier();
		mChanged = true;
	}

	// FUNCTION: ENGINE 0x1072EB90
	// NONMATCHING: the engine loads the three components into SSE registers before it stores them, ours copies the first
	// through the x87 unit (26.5 %)
#ifdef NONMATCHING
	void VertexDeformRegion::SetTransform(const math::Matrix& transform)
	{
		float x = transform.m[3][0];
		float y = transform.m[3][1];
		float z = transform.m[3][2];
		mPosition.x = x;
		mPosition.y = y;
		mPosition.z = z;
		mChanged = true;
		*(engine::NISTransform*)mInverse = *(const engine::NISTransform*)&transform;
		((math::Matrix*)mInverse)->Invert4x4();
	}
#endif

	// FUNCTION: ENGINE 0x1072ED10
	void VertexRegionAnimController::SetTransform(const math::Matrix& transform)
	{
		*(engine::NISTransform*)unknown98 = *(const engine::NISTransform*)&transform;
		((math::Matrix*)unknown98)->Invert4x4();
	}

	// FUNCTION: ENGINE 0x1072ED30
	bool VertexRegionAnimController::GetUnknownD8()
	{
		return mChanged;
	}

	// FUNCTION: ENGINE 0x1072F130
	void VertexRegionAnimController::SetKeyFrames(VertexAnimKeyFrameList* keyFrames)
	{
		core::RefAssign(mKeyFrames, keyFrames);
	}

	// FUNCTION: ENGINE 0x1072F8C0
	void VertexRegionAnimController::SetRegion(VertexDeformRegion* region)
	{
		if (region != 0 && !mRegions.IsFull())
		{
			region->AddRef();
			mRegions.PushBack(region);
			mChanged = true;
		}
	}

	// FUNCTION: ENGINE 0x1072EC30
	// EQUIVALENT: the same calls and stores in the same order; the engine keeps the overflow test of the array size in ecx
	// and the expression pointer in ecx, ours uses ebx and eax (72.6 %)
	void VertexRegionAnimController::SetMeshState(MeshState* state)
	{
		mPrimitive = state->GetPrimitive();
		mMeshState = state;
		mExpression = state->GetExpression();
		if (mExpression != 0)
		{
			delete mOffsets;
			mOffsets = new float[mExpression->count];
			unsigned int count = mExpression->count;
			for (unsigned int i = 0; i < count; i++)
			{
				mOffsets[i] = 0.0f;
			}
		}
	}

	// FUNCTION: ENGINE 0x1072FEF0
	void VertexRegionAnimController::Unknown27()
	{
		VertexDeformRegionList* regions = &mRegions;
		mFrame = 0.0f;
		mChanged = true;
		int count = regions->end - regions->items;
		for (int i = 0; i != count; i++)
		{
			core::SafeRelease(regions->items[i]);
		}
		regions->end = regions->items;
		SetFromKey(0, true);
	}

	// FUNCTION: ENGINE 0x1072F700
	// NONMATCHING: the engine truncates the difference with an inline x87 conversion straight from the register that holds
	// it (the control word is switched around the fistp), ours stores it and converts with cvttss2si (20.9 %)
#ifdef NONMATCHING
	void VertexRegionAnimController::Unknown28()
	{
		int key = (int)(mFrame = Unknown9() - engine::driving::gOne);
		mChanged = true;
		SetFromKey(key, true);
	}
#endif

	// FUNCTION: ENGINE 0x10730490
	void VertexRegionAnimController::Unknown5()
	{
		if (UpdateWeights() == true)
		{
			IntChannel* channel = (IntChannel*)mAnimation->GetGroup(0)->FindChannel(0x58545256, 0x544E49);
			if (channel != 0)
			{
				unsigned int index0;
				unsigned int index1;
				int key0;
				int key1;
				float frame0;
				float frame1;
				channel->FindKeys(mFrame, &index0, &index1);
				channel->GetKey(index0, &frame0, &key0);
				SetFromKey(key0, true);
				channel->GetKey(index1, &frame1, &key1);
				SetToKey(key1, channel->mode);
				ApplyKeys();
				mChanged = false;
			}
		}
	}
}
