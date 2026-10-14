// pure3d::PoseData (code/pure3d/anim/src/posedata.cpp, path from the asserts; the unit runs from about 0x10707240 to
// 0x10709AA0). Names are guesses.
#include "code/pure3d/posedata.h"
#include "code/pure3d/posedatasimd.h"

namespace pure3d
{
	// The lane n of a vector in all four lanes
	#define SPLAT(v, n) _mm_shuffle_ps(v, v, _MM_SHUFFLE(n, n, n, n))

	// The row vector row times the matrix with the rows m0 to m3
	static __forceinline __m128 RowTimesMatrix(const __m128& row, const __m128& m0, const __m128& m1, const __m128& m2,
		const __m128& m3)
	{
		return _mm_add_ps(_mm_add_ps(_mm_mul_ps(SPLAT(row, 0), m0), _mm_mul_ps(SPLAT(row, 2), m2)),
			_mm_add_ps(_mm_mul_ps(SPLAT(row, 3), m3), _mm_mul_ps(SPLAT(row, 1), m1)));
	}

	// The first three rows of the matrix of the rotation of a quaternion (x, y, z, w); the last column is zero
	#define ROTATION_ROWS(q, row0, row1, row2) \
		{ \
			__m128 doubled = _mm_add_ps(q, q); \
			__m128 yzxw2 = _mm_shuffle_ps(doubled, doubled, _MM_SHUFFLE(3, 0, 2, 1)); \
			__m128 zxyw = _mm_shuffle_ps(q, q, _MM_SHUFFLE(3, 1, 0, 2)); \
			__m128 splatW = _mm_shuffle_ps(q, q, _MM_SHUFFLE(3, 3, 3, 3)); \
			__m128 zxyw2 = _mm_shuffle_ps(doubled, doubled, _MM_SHUFFLE(3, 1, 0, 2)); \
			__m128 product = _mm_mul_ps(zxyw, doubled); \
			__m128 withW = _mm_mul_ps(yzxw2, splatW); \
			__m128 sums = _mm_add_ps(withW, product); \
			__m128 differences = _mm_sub_ps(product, withW); \
			__m128 yzxw = _mm_shuffle_ps(q, q, _MM_SHUFFLE(3, 0, 2, 1)); \
			__m128 diagonal = _mm_sub_ps(_mm_sub_ps(gPoseOne, _mm_mul_ps(yzxw, yzxw2)), _mm_mul_ps(zxyw2, zxyw)); \
			sums = _mm_shuffle_ps(sums, sums, _MM_SHUFFLE(3, 0, 2, 1)); \
			__m128 zero = _mm_setzero_ps(); \
			row0 = _mm_unpacklo_ps(_mm_unpacklo_ps(diagonal, differences), _mm_unpacklo_ps(sums, zero)); \
			row1 = _mm_unpackhi_ps(_mm_unpacklo_ps(differences, sums), _mm_unpacklo_ps(diagonal, zero)); \
			row2 = _mm_unpacklo_ps(_mm_unpackhi_ps(sums, diagonal), _mm_unpackhi_ps(differences, zero)); \
		}

	// FUNCTION: ENGINE 0x107098A0
	void PoseData::Update()
	{
		UpdateLocal();
		UpdateWorld();
	}

	// FUNCTION: ENGINE 0x10708E00
	// EQUIVALENT: the same vector operations in the same order (the same size as the engine's); scheduling and
	// register allocation differ
	void PoseData::UpdateLocal()
	{
		if (!(mFlags & 1))
		{
			return;
		}
		if (mSpaces != 3)
		{
			mFlags &= ~2;
			return;
		}
		if (mFlags & 4)
		{
			__m128 zero = _mm_setzero_ps();
			for (unsigned int i = 0; i < mArrays.mJointCount; i++)
			{
				if (mSkeleton->mUnknown3C[i] == 0)
				{
					// Rotation, scale with shear, and the pivots: the scale and the shear act about the pivot of
					// mUnknown10, mUnknown1C moves the result
					__m128 q = _mm_loadu_ps(&mArrays.mRotations[i].x);
					__m128 row0, row1, row2;
					ROTATION_ROWS(q, row0, row1, row2);
					__m128 pivot = _mm_loadu_ps(&mArrays.mUnknown10[i].x);
					__m128 shear = _mm_loadu_ps(&mArrays.mUnknown14[i].x);
					__m128 scale = _mm_loadu_ps(&mArrays.mScales[i].x);
					__m128 shear1 = _mm_shuffle_ps(_mm_movelh_ps(gPoseUnitY, shear), gPoseUnitY, _MM_SHUFFLE(3, 2, 1, 2));
					__m128 shearZ = _mm_shuffle_ps(gPoseUnitZ, shear, _MM_SHUFFLE(2, 1, 3, 2));
					__m128 shear2 = _mm_shuffle_ps(shearZ, shearZ, _MM_SHUFFLE(1, 0, 3, 2));
					__m128 scaled2 = _mm_mul_ps(SPLAT(scale, 2), shear2);
					__m128 scaled1 = _mm_mul_ps(SPLAT(scale, 1), shear1);
					__m128 scaled0 = _mm_shuffle_ps(_mm_movelh_ps(zero, scale), zero, _MM_SHUFFLE(3, 2, 1, 2));
					__m128 negativePivot = _mm_mul_ps(_mm_xor_ps(gPoseSignMask, pivot), scale);
					__m128 offset = _mm_add_ps(_mm_add_ps(_mm_mul_ps(SPLAT(negativePivot, 0), gPoseUnitX),
						_mm_mul_ps(SPLAT(negativePivot, 1), shear1)), _mm_mul_ps(SPLAT(negativePivot, 2), shear2));
					__m128 move = _mm_loadu_ps(&mArrays.mUnknown1C[i].x);
					offset = _mm_add_ps(offset, _mm_shuffle_ps(pivot, _mm_movehl_ps(pivot, zero), _MM_SHUFFLE(1, 2, 1, 0)));
					offset = _mm_add_ps(offset, _mm_shuffle_ps(move, _mm_movehl_ps(move, zero), _MM_SHUFFLE(1, 2, 1, 0)));
					__m128 translation = _mm_loadu_ps(&mArrays.mTranslations[i].x);
					offset = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(SPLAT(translation, 0), scaled0), offset),
						_mm_mul_ps(SPLAT(translation, 2), scaled2)), _mm_mul_ps(SPLAT(translation, 1), scaled1));
					_mm_store_ps(mLocalMatrices[i].m[0], RowTimesMatrix(scaled0, row0, row1, row2, gPoseUnitW));
					_mm_store_ps(mLocalMatrices[i].m[1], RowTimesMatrix(scaled1, row0, row1, row2, gPoseUnitW));
					_mm_store_ps(mLocalMatrices[i].m[2], RowTimesMatrix(scaled2, row0, row1, row2, gPoseUnitW));
					_mm_store_ps(mLocalMatrices[i].m[3], _mm_shuffle_ps(offset, _mm_movehl_ps(offset, gPoseOne),
						_MM_SHUFFLE(1, 2, 1, 0)));
				}
				else
				{
					// Rotation, scale and translation; the scale of the parent is divided out for some joints
					__m128 q = _mm_loadu_ps(&mArrays.mRotations[i].x);
					__m128 scale = _mm_loadu_ps(&mArrays.mScales[i].x);
					__m128 translation = _mm_loadu_ps(&mArrays.mTranslations[i].x);
					__m128 row0, row1, row2;
					ROTATION_ROWS(q, row0, row1, row2);
					row0 = _mm_mul_ps(SPLAT(scale, 0), row0);
					row1 = _mm_mul_ps(SPLAT(scale, 1), row1);
					row2 = _mm_mul_ps(SPLAT(scale, 2), row2);
					__m128 row3 = _mm_shuffle_ps(translation, _mm_movehl_ps(translation, gPoseUnitW),
						_MM_SHUFFLE(1, 2, 1, 0));
					if (i > 0 && mSkeleton->mUnknown40[i] != 0)
					{
						unsigned int parent = mSkeleton->mParents[i];
						__m128 inverse = _mm_div_ps(gPoseOne, _mm_loadu_ps(&mArrays.mScales[parent].x));
						inverse = _mm_shuffle_ps(inverse, _mm_movehl_ps(inverse, gPoseZero), _MM_SHUFFLE(1, 2, 1, 0));
						row0 = _mm_mul_ps(inverse, row0);
						row1 = _mm_mul_ps(inverse, row1);
						row2 = _mm_mul_ps(inverse, row2);
					}
					_mm_store_ps(mLocalMatrices[i].m[0], row0);
					_mm_store_ps(mLocalMatrices[i].m[1], row1);
					_mm_store_ps(mLocalMatrices[i].m[2], row2);
					_mm_store_ps(mLocalMatrices[i].m[3], row3);
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < mArrays.mJointCount; i++)
			{
				// The rotation and the translation only
				__m128 q = _mm_loadu_ps(&mArrays.mRotations[i].x);
				__m128 translation = _mm_loadu_ps(&mArrays.mTranslations[i].x);
				__m128 row0, row1, row2;
				ROTATION_ROWS(q, row0, row1, row2);
				_mm_store_ps(mLocalMatrices[i].m[0], row0);
				_mm_store_ps(mLocalMatrices[i].m[1], row1);
				_mm_store_ps(mLocalMatrices[i].m[2], row2);
				_mm_store_ps(mLocalMatrices[i].m[3], _mm_shuffle_ps(translation, _mm_movehl_ps(translation, gPoseUnitW),
					_MM_SHUFFLE(1, 2, 1, 0)));
			}
		}
		mFlags = (mFlags & ~1) | 2;
	}

	// FUNCTION: ENGINE 0x10708330
	// EQUIVALENT: the same vector operations in the same order; scheduling and register allocation differ
	void PoseData::UpdateWorld()
	{
		if (!(mFlags & 2))
		{
			return;
		}
		if (mSpaces != 3)
		{
			mFlags &= ~2;
			return;
		}
		math::Matrix* local = mLocalMatrices;
		math::Matrix* world = mWorldMatrices;
		math::Matrix* skin = mSkinMatrices;
		world[0] = local[0];
		math::Matrix* inverse = mSkeleton->mInverseJoints;
		{
			// The skinning matrix of the root: its inverse bind pose times its joint matrix
			__m128 w0 = _mm_load_ps(world[0].m[0]);
			__m128 w1 = _mm_load_ps(world[0].m[1]);
			__m128 w2 = _mm_load_ps(world[0].m[2]);
			__m128 w3 = _mm_load_ps(world[0].m[3]);
			_mm_store_ps(skin[0].m[0], RowTimesMatrix(_mm_load_ps(inverse[0].m[0]), w0, w1, w2, w3));
			_mm_store_ps(skin[0].m[1], RowTimesMatrix(_mm_load_ps(inverse[0].m[1]), w0, w1, w2, w3));
			_mm_store_ps(skin[0].m[2], RowTimesMatrix(_mm_load_ps(inverse[0].m[2]), w0, w1, w2, w3));
			_mm_store_ps(skin[0].m[3], RowTimesMatrix(_mm_load_ps(inverse[0].m[3]), w0, w1, w2, w3));
		}
		for (unsigned int i = 1; i < mArrays.mJointCount; i++)
		{
			// The joint matrix is the local matrix times the parent's joint matrix, the skinning matrix the inverse
			// bind pose times the joint matrix
			__m128 l0 = _mm_load_ps(local[i].m[0]);
			__m128 l1 = _mm_load_ps(local[i].m[1]);
			__m128 l2 = _mm_load_ps(local[i].m[2]);
			__m128 l3 = _mm_load_ps(local[i].m[3]);
			const math::Matrix& parent = world[mSkeleton->mParents[i]];
			__m128 p0 = _mm_load_ps(parent.m[0]);
			__m128 p1 = _mm_load_ps(parent.m[1]);
			__m128 p2 = _mm_load_ps(parent.m[2]);
			__m128 p3 = _mm_load_ps(parent.m[3]);
			__m128 w0 = RowTimesMatrix(l0, p0, p1, p2, p3);
			__m128 w1 = RowTimesMatrix(l1, p0, p1, p2, p3);
			__m128 w2 = RowTimesMatrix(l2, p0, p1, p2, p3);
			__m128 w3 = RowTimesMatrix(l3, p0, p1, p2, p3);
			_mm_store_ps(world[i].m[0], w0);
			_mm_store_ps(world[i].m[1], w1);
			_mm_store_ps(world[i].m[2], w2);
			_mm_store_ps(world[i].m[3], w3);
			const math::Matrix& bind = mSkeleton->mInverseJoints[i];
			_mm_store_ps(skin[i].m[0], RowTimesMatrix(_mm_load_ps(bind.m[0]), w0, w1, w2, w3));
			_mm_store_ps(skin[i].m[1], RowTimesMatrix(_mm_load_ps(bind.m[1]), w0, w1, w2, w3));
			_mm_store_ps(skin[i].m[2], RowTimesMatrix(_mm_load_ps(bind.m[2]), w0, w1, w2, w3));
			_mm_store_ps(skin[i].m[3], RowTimesMatrix(_mm_load_ps(bind.m[3]), w0, w1, w2, w3));
		}
		mFlags &= ~2;
	}
}
