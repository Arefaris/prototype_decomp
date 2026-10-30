// pure3d::PoseData (code/pure3d/anim/src/posedata.cpp, path from the asserts; the unit runs from about 0x10707240 to
// 0x10709AA0). Names are guesses.
#include "code/core/debug.h"
#include "code/core/heap.h"
#include "code/core/memutils.h"
#include "code/pure3d/posedata.h"
#include "code/pure3d/posedatasimd.h"

namespace engine
{
	namespace driving
	{
		// 0x10D946E0
		extern const float gOne;
	}
}

namespace pure3d
{
	// The file the unit's asserts carry (posedata.cpp)
	#define POSEDATA_FILE "..\\..\\..\\code\\pure3d\\anim\\src\\posedata.cpp"

	// The bytes the arrays of a pose of that many joints take: 0xA0 per joint for the local space (the arrays and the
	// local matrices), 0x80 for the joint and skinning matrices
	// FUNCTION: ENGINE 0x10708240
	int GetRawMemorySize(unsigned int jointCount, int spaces)
	{
		int size = 0;
		if (spaces & 1)
		{
			size = jointCount * 0xA0;
		}
		if (spaces & 2)
		{
			size += jointCount * 0x80;
		}
		return size;
	}

	// FUNCTION: ENGINE 0x10708DB0
	void* AllocateBoneData(unsigned int jointCount, int* size, int spaces)
	{
		int bytes = GetRawMemorySize(jointCount, spaces) + 0x10;
		void* memory = core::HeapAlloc(core::GetCurrentHeap(), bytes);
		if (size != 0)
		{
			*size = bytes;
		}
		return memory;
	}

	// The block address rounded up to 16 bytes
	// FUNCTION: ENGINE 0x10708DF0
	unsigned int AlignBoneMemory(unsigned int address)
	{
		return (address + 0xF) & 0xFFFFFFF0;
	}

	// The sixteen components of a matrix, one by one
	static __forceinline void CopyMatrix(math::Matrix* destination, const math::Matrix* source)
	{
		for (int row = 0; row < 4; row++)
		{
			destination->m[row][0] = source->m[row][0];
			destination->m[row][1] = source->m[row][1];
			destination->m[row][2] = source->m[row][2];
			destination->m[row][3] = source->m[row][3];
		}
	}

	// The first three components of the vector moved the fraction t of the way to the other one
	static __forceinline void LerpVector3(math::Vector4* value, const math::Vector4* target, float t)
	{
		value->x = (target->x - value->x) * t + value->x;
		value->y = (target->y - value->y) * t + value->y;
		value->z = (target->z - value->z) * t + value->z;
	}

	// All four components of a vector
	static __forceinline void CopyVector4(math::Vector4* destination, const math::Vector4* source)
	{
		destination->x = source->x;
		destination->y = source->y;
		destination->z = source->z;
		destination->w = source->w;
	}

	// The first three components of a vector
	static __forceinline void CopyVector3(math::Vector4* destination, const math::Vector4* source)
	{
		destination->x = source->x;
		destination->y = source->y;
		destination->z = source->z;
	}

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
					__m128 shear1 = _mm_shuffle_ps(_mm_movelh_ps(gPoseUnitY, shear), gPoseUnitY,
						_MM_SHUFFLE(3, 2, 1, 2));
					__m128 shearZ = _mm_shuffle_ps(gPoseUnitZ, shear, _MM_SHUFFLE(2, 1, 3, 2));
					__m128 shear2 = _mm_shuffle_ps(shearZ, shearZ, _MM_SHUFFLE(1, 0, 3, 2));
					__m128 scaled2 = _mm_mul_ps(SPLAT(scale, 2), shear2);
					__m128 scaled1 = _mm_mul_ps(SPLAT(scale, 1), shear1);
					__m128 scaled0 = _mm_shuffle_ps(_mm_movelh_ps(zero, scale), zero, _MM_SHUFFLE(3, 2, 1, 2));
					__m128 negativePivot = _mm_mul_ps(_mm_xor_ps(gPoseSignMask, pivot), scale);
					__m128 offset = _mm_add_ps(_mm_add_ps(_mm_mul_ps(SPLAT(negativePivot, 0), gPoseUnitX),
						_mm_mul_ps(SPLAT(negativePivot, 1), shear1)), _mm_mul_ps(SPLAT(negativePivot, 2), shear2));
					__m128 move = _mm_loadu_ps(&mArrays.mUnknown1C[i].x);
					offset = _mm_add_ps(offset, _mm_shuffle_ps(pivot, _mm_movehl_ps(pivot, zero),
						_MM_SHUFFLE(1, 2, 1, 0)));
					offset = _mm_add_ps(offset, _mm_shuffle_ps(move, _mm_movehl_ps(move, zero),
						_MM_SHUFFLE(1, 2, 1, 0)));
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

	// FUNCTION: ENGINE 0x10708CA0
	void JointArrays::Set(const PoseLayout* layout)
	{
		mJointCount = layout->jointCount;
		int block = (int)layout->memory;
		if (layout->spaces & 2)
		{
			block += mJointCount * 0x80;
		}
		block += mJointCount * 0x40;
		mRotations = (math::Quaternion*)block;
		block += mJointCount * 0x10;
		mTranslations = (math::Vector4*)block;
		block += mJointCount * 0x10;
		mUnknown10 = (math::Vector4*)block;
		block += mJointCount * 0x10;
		mScales = (math::Vector4*)block;
		block += mJointCount * 0x10;
		mUnknown14 = (math::Vector4*)block;
		mUnknown1C = (math::Vector4*)(block + mJointCount * 0x10);
	}

	// FUNCTION: ENGINE 0x10708260
	void PoseData::GetLayout(PoseLayout* layout)
	{
		layout->jointCount = mArrays.mJointCount;
		layout->spaces = mSpaces;
		layout->updateLocal = mLocalOutOfDate;
		layout->updateWorld = mWorldOutOfDate;
		layout->further = mFurther;
		layout->memory = mUnknown38;
	}

	// FUNCTION: ENGINE 0x10708310
	void PoseData::FreeMemory()
	{
		core::Free(mUnknown34);
	}

	// FUNCTION: ENGINE 0x107082B0
	void PoseData::SetMemory(void* memory)
	{
		int spaces = mSpaces;
		mUnknown38 = memory;
		char* block = (char*)memory;
		if (spaces & 2)
		{
			int size = mArrays.mJointCount * 0x40;
			char* skin = block + size;
			mSkinMatrices = (math::Matrix*)skin;
			mWorldMatrices = (math::Matrix*)block;
			block = skin + size;
		}
		if (spaces & 1)
		{
			mLocalMatrices = (math::Matrix*)block;
			block += mArrays.mJointCount * 0x40;
			int stride = mArrays.mJointCount * 0x10;
			mArrays.mRotations = (math::Quaternion*)block;
			block += stride;
			mArrays.mTranslations = (math::Vector4*)block;
			block += stride;
			mArrays.mUnknown10 = (math::Vector4*)block;
			block += stride;
			mArrays.mScales = (math::Vector4*)block;
			block += stride;
			mArrays.mUnknown14 = (math::Vector4*)block;
			mArrays.mUnknown1C = (math::Vector4*)(block + stride);
		}
	}

	// FUNCTION: ENGINE 0x10709960
	PoseData::PoseData(SkeletonData* skeleton, int spaces)
	{
		mFlags |= 7;
		mSkeleton = skeleton;
		mUnknown34 = 0;
		mUnknown38 = 0;
		mArrays.mJointCount = skeleton->mJointCount;
		mSpaces = spaces;
		mUnknown34 = AllocateBoneData(mArrays.mJointCount, 0, spaces);
		SetMemory((void*)AlignBoneMemory((unsigned int)mUnknown34));
		Initialise();
	}

	// FUNCTION: ENGINE 0x107099B0
	PoseData::PoseData(SkeletonData* skeleton, void* memory, unsigned int* size, int spaces)
	{
		mFlags |= 7;
		mSkeleton = skeleton;
		mUnknown34 = 0;
		mUnknown38 = 0;
		mArrays.mJointCount = skeleton->mJointCount;
		mSpaces = spaces;
		unsigned int aligned = AlignBoneMemory((unsigned int)memory);
		OLD_ASSERT_TEXT_AT(POSEDATA_FILE, 0xDE,
			(*size >= (unsigned int)(GetRawMemorySize(mArrays.mJointCount, mSpaces) + (aligned - (unsigned int)memory))),
			"size >= GetRawMemorySize( mJointCount, mSpaces ) + (alignedMemory - unalignedRawMemory)");
		SetMemory((void*)aligned);
		Initialise();
	}

	// FUNCTION: ENGINE 0x107087D0
	// EQUIVALENT: scheduling (the engine loads the destination array before the source array of every copy; 68 %)
	void PoseData::SetRestPose()
	{
		for (unsigned int i = 0; i < mArrays.mJointCount; i++)
		{
			if (mSpaces & 1)
			{
				mArrays.mRotations[i] = mSkeleton->mRotations[i];
				CopyMatrix(&mLocalMatrices[i], &mSkeleton->mFileMatrices[i]);
				CopyVector3(&mArrays.mTranslations[i], &mSkeleton->mTranslations[i]);
				CopyVector3(&mArrays.mUnknown10[i], &mSkeleton->mUnknown10[i]);
				CopyVector3(&mArrays.mScales[i], &mSkeleton->mScales[i]);
				CopyVector3(&mArrays.mUnknown14[i], &mSkeleton->mUnknown18[i]);
				CopyVector3(&mArrays.mUnknown1C[i], &mSkeleton->mUnknown1C[i]);
			}
			if (mSpaces & 2)
			{
				mWorldMatrices[i].Identity();
			}
		}
		mFlags = (mFlags & 0xFE) | 2;
		if (mSpaces != 3)
		{
			mFlags &= ~2;
		}
	}

	// FUNCTION: ENGINE 0x10709910
	void PoseData::Initialise()
	{
		if (mSpaces != 3)
		{
			mFlags &= ~3;
			math::Matrix* matrix = mSkinMatrices;
			for (unsigned int i = 0; i < mArrays.mJointCount; i++)
			{
				matrix->Identity();
				matrix++;
			}
		}
		SetRestPose();
		Update();
	}

	// FUNCTION: ENGINE 0x107098B0
	void PoseData::GetJointMatrix(int joint, math::Matrix* matrix)
	{
		Update();
		*matrix = mWorldMatrices[joint];
	}

	// FUNCTION: ENGINE 0x107098D0
	// EQUIVALENT: instruction selection (the engine loads the three floats into SSE registers and stores them from there, ours copies the first through the x87 unit; 51 %)
	void PoseData::GetJointPosition(int joint, math::Vector* position)
	{
		Update();
		math::Matrix* m = &mWorldMatrices[joint];
		position->Set(m->m[3][0], m->m[3][1], m->m[3][2]);
	}

	// FUNCTION: ENGINE 0x10709350
	void PoseData::CopyFrom(PoseData* other)
	{
		unsigned int count = mArrays.mJointCount < other->mArrays.mJointCount ? mArrays.mJointCount : other->mArrays.mJointCount;
		for (unsigned int i = 0; i < count; i++)
		{
			if (mSpaces & other->mSpaces & 1)
			{
				CopyVector4(&mArrays.mUnknown10[i], &other->mArrays.mUnknown10[i]);
				CopyVector4(&mArrays.mScales[i], &other->mArrays.mScales[i]);
				CopyVector4(&mArrays.mUnknown14[i], &other->mArrays.mUnknown14[i]);
				CopyVector4(&mArrays.mUnknown1C[i], &other->mArrays.mUnknown1C[i]);
				CopyMatrix(&mLocalMatrices[i], &other->mLocalMatrices[i]);
				mArrays.mRotations[i] = other->mArrays.mRotations[i];
				CopyVector4(&mArrays.mTranslations[i], &other->mArrays.mTranslations[i]);
			}
			if (mSpaces & other->mSpaces & 2)
			{
				CopyMatrix(&mWorldMatrices[i], &other->mWorldMatrices[i]);
				CopyMatrix(&mSkinMatrices[i], &other->mSkinMatrices[i]);
			}
		}
	}

	// FUNCTION: ENGINE 0x107095C0
	void PoseData::CopyMatchingFrom(PoseData* other)
	{
		for (unsigned int i = 0; i < other->mArrays.mJointCount; i++)
		{
			for (unsigned int j = 0; j < mArrays.mJointCount; j++)
			{
				if (mSkeleton->mNames[j] == other->mSkeleton->mNames[i])
				{
					if (other->mSpaces & mSpaces & 1)
					{
						CopyVector4(&mArrays.mUnknown10[j], &other->mArrays.mUnknown10[i]);
						CopyVector4(&mArrays.mScales[j], &other->mArrays.mScales[i]);
						CopyVector4(&mArrays.mUnknown14[j], &other->mArrays.mUnknown14[i]);
						CopyVector4(&mArrays.mUnknown1C[j], &other->mArrays.mUnknown1C[i]);
						CopyMatrix(&mLocalMatrices[j], &other->mLocalMatrices[i]);
						mArrays.mRotations[j] = other->mArrays.mRotations[i];
						CopyVector4(&mArrays.mTranslations[j], &other->mArrays.mTranslations[i]);
					}
					if (other->mSpaces & mSpaces & 2)
					{
						CopyMatrix(&mWorldMatrices[j], &other->mWorldMatrices[i]);
						CopyMatrix(&mSkinMatrices[j], &other->mSkinMatrices[i]);
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x107089B0
	// EQUIVALENT: register allocation and scheduling (the engine counts the joints in ebp and keeps the byte offset in esi,
	// loads the target before the value in two of the lerps; 17.6 %)
	void PoseData::Blend(PoseData* other, float t, bool root)
	{
		unsigned int joint = 0;
		if (root)
		{
			math::Quaternion rotation;
			rotation.x = 0.0f;
			rotation.y = 0.0f;
			rotation.z = 0.0f;
			rotation.w = engine::driving::gOne;
			rotation.Slerp(rotation, other->mArrays.mRotations[0], t);
			math::Multiply(rotation, rotation, mArrays.mRotations[0]);
			mArrays.mRotations[0] = rotation;
			mArrays.mTranslations[0].x = other->mArrays.mTranslations[0].x * t + mArrays.mTranslations[0].x;
			mArrays.mTranslations[0].y = other->mArrays.mTranslations[0].y * t + mArrays.mTranslations[0].y;
			mArrays.mTranslations[0].z = other->mArrays.mTranslations[0].z * t + mArrays.mTranslations[0].z;
			joint = 1;
		}
		for (; joint < mSkeleton->mJointCount; joint++)
		{
			mArrays.mRotations[joint].Slerp(mArrays.mRotations[joint], other->mArrays.mRotations[joint], t);
			LerpVector3(&mArrays.mTranslations[joint], &other->mArrays.mTranslations[joint], t);
			LerpVector3(&mArrays.mUnknown10[joint], &other->mArrays.mUnknown10[joint], t);
			LerpVector3(&mArrays.mScales[joint], &other->mArrays.mScales[joint], t);
			LerpVector3(&mArrays.mUnknown14[joint], &other->mArrays.mUnknown14[joint], t);
			LerpVector3(&mArrays.mUnknown1C[joint], &other->mArrays.mUnknown1C[joint], t);
		}
		mFlags |= 3;
	}

	// FUNCTION: ENGINE 0x10708980
	void PoseData::CopyMatricesFrom(PoseData* other)
	{
		core::MemCopy4(mWorldMatrices, other->mWorldMatrices, mArrays.mJointCount << 7);
		mFlags &= 0xFC;
	}
}
