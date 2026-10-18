// pure3d::SkinState and the skinning code (code/pure3d/atg4/platform/win32/skin.cpp, path from the asserts). Names
// are guesses.
#include <mmintrin.h>
#include <xmmintrin.h>

#include "code/core/debug.h"
#include "code/core/interlocked.h"
#include "code/core/refptr.h"
#include "code/core/thread.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/primstream.h"

namespace pure3d
{
	// The file the unit's asserts carry (skin.cpp)
	#define SKIN_FILE "..\\..\\..\\code\\pure3d\\atg4\\platform\\win32\\skin.cpp"

	// Two empty helpers of the unit (their callers are in other units, so their real names and classes are unknown)
	// FUNCTION: ENGINE 0x1071B080
	void Unknown1071B080()
	{
	}

	// FUNCTION: ENGINE 0x1071B1F0
	void Unknown1071B1F0()
	{
	}

	// FUNCTION: ENGINE 0x1071EFC0
	void Unknown1071EFC0()
	{
	}

	// Stores a node in a list head the caller owns (no interlocked exchange); the node's first word is its next
	// FUNCTION: ENGINE 0x1071B000
	void StoreListHead(void** head, void* node)
	{
		*head = node;
	}

	// The queue of skin states whose skinning job is running (a state's entry at +0x33C is the node) and the number
	// of jobs that have not finished
	// GLOBAL: ENGINE 0x11281814
	void* gPendingSkins = 0;
	// GLOBAL: ENGINE 0x11281828
	int gSkinJobCount = 0;

	// Pushes a node on a list head, retrying while another thread changes it; the node's first word is its next
	// FUNCTION: ENGINE 0x1071B010
	void PushListHead(void** head, void** node)
	{
		void* old = *head;
		for (;;)
		{
			*node = old;
			void* expected = old;
			old = (void*)_InterlockedCompareExchange((long volatile*)head, (long)node, (long)old);
			if (old == expected)
			{
				break;
			}
		}
	}

	// Pops a node off a list head, retrying while another thread changes it; null when the list is empty
	// FUNCTION: ENGINE 0x1071B040
	__inline void* PopListHead(void** head)
	{
		void* node = *head;
		void* expected;
		do
		{
			if (node == 0)
			{
				return 0;
			}
			void* next = *(void**)node;
			expected = node;
			node = (void*)_InterlockedCompareExchange((long volatile*)head, (long)next, (long)node);
		} while (node != expected);
		return node;
	}

	// FUNCTION: ENGINE 0x1071B090
	SkinState::AsyncTaskAdaptor::AsyncTaskAdaptor()
	{
	}

	// a * weights.x + b * weights.y + c * weights.z + d, four lanes at a time. The engine inlines these into the
	// skinning paths and also keeps standalone copies (0x1071B270 / 0x1071B2C0): the forced-inline bodies are for the
	// paths, the plain functions are the standalone copies.
	__forceinline __m128 BlendRows4Inline(const __m128& a, const __m128& b, const __m128& c, const __m128& d,
		const __m128& weights)
	{
		__m128 x = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 y = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 z = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 blended = _mm_mul_ps(x, a);
		blended = _mm_add_ps(blended, _mm_mul_ps(y, b));
		blended = _mm_add_ps(blended, _mm_mul_ps(z, c));
		return _mm_add_ps(blended, d);
	}

	// a * weights.x + b * weights.y + c * weights.z, four lanes at a time
	__forceinline __m128 BlendRows3Inline(const __m128& a, const __m128& b, const __m128& c, const __m128& weights)
	{
		__m128 x = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 y = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 z = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 blended = _mm_mul_ps(x, a);
		blended = _mm_add_ps(blended, _mm_mul_ps(y, b));
		return _mm_add_ps(blended, _mm_mul_ps(z, c));
	}

	// One row of the matrix four bones blend to: a * weights.x + b * weights.y + c * weights.z + d * weights.w
	__forceinline __m128 BlendBoneRow(const __m128& a, const __m128& b, const __m128& c, const __m128& d,
		const __m128& weights)
	{
		__m128 x = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 y = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 z = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 q = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(3, 3, 3, 3));
		__m128 blended = _mm_mul_ps(x, a);
		blended = _mm_add_ps(_mm_mul_ps(y, b), blended);
		blended = _mm_add_ps(_mm_mul_ps(z, c), blended);
		return _mm_add_ps(_mm_mul_ps(q, d), blended);
	}

	// FUNCTION: ENGINE 0x1071B270
	__m128 BlendRows4(const __m128& a, const __m128& b, const __m128& c, const __m128& d, const __m128& weights)
	{
		return BlendRows4Inline(a, b, c, d, weights);
	}

	// FUNCTION: ENGINE 0x1071B2C0
	__m128 BlendRows3(const __m128& a, const __m128& b, const __m128& c, const __m128& weights)
	{
		return BlendRows3Inline(a, b, c, weights);
	}

	__forceinline __m128 NextRow(const __m128*& p)
	{
		return *p++;
	}

	// The four rows of a bone matrix
	struct BoneRows
	{
		__m128 r0;
		__m128 r1;
		__m128 r2;
		__m128 r3;
	};

	__forceinline BoneRows LoadBoneRows(const math::Matrix* matrices, unsigned short bone)
	{
		const __m128* rows = (const __m128*)&matrices[bone];
		BoneRows result;
		result.r0 = NextRow(rows);
		result.r1 = NextRow(rows);
		result.r2 = NextRow(rows);
		result.r3 = NextRow(rows);
		return result;
	}

	// The matrix the four bones of a vertex blend to, by the vertex's weights: bone after bone, each adding its
	// four rows scaled by its weight
	template <class Vertex>
	__forceinline BoneRows BlendBones(const math::Matrix* matrices, const Vertex* vertex)
	{
		__m128 w = _mm_load_ps(&vertex->weights.x);
		const math::Matrix& m0 = matrices[vertex->bones[0]];
		const math::Matrix& m1 = matrices[vertex->bones[1]];
		const math::Matrix& m2 = matrices[vertex->bones[2]];
		const math::Matrix& m3 = matrices[vertex->bones[3]];
		__m128 x = _mm_shuffle_ps(w, w, _MM_SHUFFLE(0, 0, 0, 0));
		BoneRows result;
		result.r0 = _mm_mul_ps(x, _mm_load_ps(m0.m[0]));
		result.r1 = _mm_mul_ps(x, _mm_load_ps(m0.m[1]));
		result.r2 = _mm_mul_ps(x, _mm_load_ps(m0.m[2]));
		result.r3 = _mm_mul_ps(x, _mm_load_ps(m0.m[3]));
		__m128 y = _mm_shuffle_ps(w, w, _MM_SHUFFLE(1, 1, 1, 1));
		result.r0 = _mm_add_ps(_mm_mul_ps(_mm_load_ps(m1.m[0]), y), result.r0);
		result.r1 = _mm_add_ps(_mm_mul_ps(_mm_load_ps(m1.m[1]), y), result.r1);
		result.r2 = _mm_add_ps(_mm_mul_ps(_mm_load_ps(m1.m[2]), y), result.r2);
		result.r3 = _mm_add_ps(_mm_mul_ps(_mm_load_ps(m1.m[3]), y), result.r3);
		__m128 z = _mm_shuffle_ps(w, w, _MM_SHUFFLE(2, 2, 2, 2));
		result.r0 = _mm_add_ps(_mm_mul_ps(_mm_load_ps(m2.m[0]), z), result.r0);
		result.r1 = _mm_add_ps(_mm_mul_ps(_mm_load_ps(m2.m[1]), z), result.r1);
		result.r2 = _mm_add_ps(_mm_mul_ps(_mm_load_ps(m2.m[2]), z), result.r2);
		result.r3 = _mm_add_ps(_mm_mul_ps(_mm_load_ps(m2.m[3]), z), result.r3);
		__m128 q = _mm_shuffle_ps(w, w, _MM_SHUFFLE(3, 3, 3, 3));
		result.r0 = _mm_add_ps(_mm_mul_ps(_mm_load_ps(m3.m[0]), q), result.r0);
		result.r1 = _mm_add_ps(_mm_mul_ps(_mm_load_ps(m3.m[1]), q), result.r1);
		result.r2 = _mm_add_ps(_mm_mul_ps(_mm_load_ps(m3.m[2]), q), result.r2);
		result.r3 = _mm_add_ps(_mm_mul_ps(_mm_load_ps(m3.m[3]), q), result.r3);
		return result;
	}

	// The zeros the offset paths read when the expression has no offsets of a kind
	// GLOBAL: ENGINE 0x11281818
	float gNoVertexOffsets[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// The skinning paths share one shape. What the engine's bytes ask for: the box accumulators are two __m128
	// locals filled lane by lane through float casts (they get the same stack slot discipline as the blended rows),
	// the matrix rows the blends use are references to the bone's memory (`const __m128& m0 = *p++`, so the loads
	// stay where they are used and the pointer walks the four rows), the output pointer is a local copy of `out`,
	// and the loop is `for (unsigned int i = count; i > 0; i--)`.
	// FUNCTION: ENGINE 0x1071B9A0
	void SkinState::Unknown1071B9A0(math::Vector4* out, const SkinVertex* vertices, int count)
	{
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x2E6, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		__m128 maxBounds;
		((float*)&maxBounds)[0] = -1e12f;
		((float*)&maxBounds)[1] = -1e12f;
		((float*)&maxBounds)[2] = -1e12f;
		((float*)&maxBounds)[3] = -1e12f;
		__m128 minBounds;
		((float*)&minBounds)[0] = 1e12f;
		((float*)&minBounds)[1] = 1e12f;
		((float*)&minBounds)[2] = 1e12f;
		((float*)&minBounds)[3] = 1e12f;
		math::Vector4* dst = out;
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 v2 = _mm_load_ps(&vertices->tangent.x);
			const __m128* p = (const __m128*)&matrices[vertices->bones[0]];
			const __m128& m0 = *p++;
			const __m128& m1 = *p++;
			const __m128& m2 = *p++;
			const __m128& m3 = *p++;
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, v0);
			__m128 r1 = BlendRows3Inline(m0, m1, m2, v1);
			__m128 r2 = BlendRows3Inline(m0, m1, m2, v2);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r2)[3] = ((float*)&v2)[3];
			_mm_storeu_ps(&dst->x, r0);
			dst++;
			_mm_storeu_ps(&dst->x, r1);
			dst++;
			_mm_storeu_ps(&dst->x, r2);
			dst++;
			maxBounds = _mm_max_ps(maxBounds, r0);
			minBounds = _mm_min_ps(minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = ((float*)&minBounds)[0];
		bounds.min.y = ((float*)&minBounds)[1];
		bounds.min.z = ((float*)&minBounds)[2];
		bounds.max.x = ((float*)&maxBounds)[0];
		bounds.max.y = ((float*)&maxBounds)[1];
		bounds.max.z = ((float*)&maxBounds)[2];
	}

	// FUNCTION: ENGINE 0x1071B610
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling (the engine spills part of the blended rows)
#ifdef NONMATCHING
	void SkinState::Unknown1071B610(math::Vector4* out, const SkinVertex* vertices, int count)
	{
		if (pddi->Unknown24(0x400001)->Unknown7())
		{
			return;
		}
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x298, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 v2 = _mm_load_ps(&vertices->tangent.x);
			BoneRows m = BlendBones(matrices, vertices);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, v0);
			__m128 r1 = BlendRows3Inline(m.r0, m.r1, m.r2, v1);
			__m128 r2 = BlendRows3Inline(m.r0, m.r1, m.r2, v2);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r2)[3] = ((float*)&v2)[3];
			_mm_storeu_ps(&out->x, r0);
			out++;
			_mm_storeu_ps(&out->x, r1);
			out++;
			_mm_storeu_ps(&out->x, r2);
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif

	// FUNCTION: ENGINE 0x1071BBD0
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071BBD0(math::Vector4* out, const SkinVertex* vertices, int count)
	{
		if (pddi->Unknown24(0x400001)->Unknown7())
		{
			return;
		}
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x338, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			BoneRows m = BlendBones(matrices, vertices);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, v0);
			__m128 r1 = BlendRows3Inline(m.r0, m.r1, m.r2, v1);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			_mm_storeu_ps(&out->x, r0);
			out++;
			_mm_storeu_ps(&out->x, r1);
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif

	// FUNCTION: ENGINE 0x1071BEE0
	void SkinState::Unknown1071BEE0(math::Vector4* out, const SkinVertex* vertices, int count)
	{
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x37B, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		__m128 maxBounds;
		((float*)&maxBounds)[0] = -1e12f;
		((float*)&maxBounds)[1] = -1e12f;
		((float*)&maxBounds)[2] = -1e12f;
		((float*)&maxBounds)[3] = -1e12f;
		__m128 minBounds;
		((float*)&minBounds)[0] = 1e12f;
		((float*)&minBounds)[1] = 1e12f;
		((float*)&minBounds)[2] = 1e12f;
		((float*)&minBounds)[3] = 1e12f;
		math::Vector4* dst = out;
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			const __m128* p = (const __m128*)&matrices[vertices->bones[0]];
			const __m128& m0 = *p++;
			const __m128& m1 = *p++;
			const __m128& m2 = *p++;
			const __m128& m3 = *p++;
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, v0);
			__m128 r1 = BlendRows3Inline(m0, m1, m2, v1);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			_mm_storeu_ps(&dst->x, r0);
			dst++;
			_mm_storeu_ps(&dst->x, r1);
			dst++;
			maxBounds = _mm_max_ps(maxBounds, r0);
			minBounds = _mm_min_ps(minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = ((float*)&minBounds)[0];
		bounds.min.y = ((float*)&minBounds)[1];
		bounds.min.z = ((float*)&minBounds)[2];
		bounds.max.x = ((float*)&maxBounds)[0];
		bounds.max.y = ((float*)&maxBounds)[1];
		bounds.max.z = ((float*)&maxBounds)[2];
	}

	// FUNCTION: ENGINE 0x1071C0C0
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071C0C0(math::Vector4* out, const SkinVertex* vertices, int count)
	{
		if (pddi->Unknown24(0x400001)->Unknown7())
		{
			return;
		}
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x3C7, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			BoneRows m = BlendBones(matrices, vertices);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, v0);
			((float*)&r0)[3] = 1.0f;
			_mm_storeu_ps(&out->x, r0);
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif

	// FUNCTION: ENGINE 0x1071C390
	void SkinState::Unknown1071C390(math::Vector4* out, const SkinVertex* vertices, int count)
	{
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x3FD, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		__m128 maxBounds;
		((float*)&maxBounds)[0] = -1e12f;
		((float*)&maxBounds)[1] = -1e12f;
		((float*)&maxBounds)[2] = -1e12f;
		((float*)&maxBounds)[3] = -1e12f;
		__m128 minBounds;
		((float*)&minBounds)[0] = 1e12f;
		((float*)&minBounds)[1] = 1e12f;
		((float*)&minBounds)[2] = 1e12f;
		((float*)&minBounds)[3] = 1e12f;
		math::Vector4* dst = out;
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			const __m128* p = (const __m128*)&matrices[vertices->bones[0]];
			const __m128& m0 = *p++;
			const __m128& m1 = *p++;
			const __m128& m2 = *p++;
			const __m128& m3 = *p++;
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, v0);
			((float*)&r0)[3] = 1.0f;
			_mm_storeu_ps(&dst->x, r0);
			dst++;
			maxBounds = _mm_max_ps(maxBounds, r0);
			minBounds = _mm_min_ps(minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = ((float*)&minBounds)[0];
		bounds.min.y = ((float*)&minBounds)[1];
		bounds.min.z = ((float*)&minBounds)[2];
		bounds.max.x = ((float*)&maxBounds)[0];
		bounds.max.y = ((float*)&maxBounds)[1];
		bounds.max.z = ((float*)&maxBounds)[2];
	}

	// FUNCTION: ENGINE 0x1071C530
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071C530(math::Vector4* out, const SkinVertex* vertices, int count)
	{
		if (pddi->Unknown24(0x400001)->Unknown7())
		{
			return;
		}
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x43D, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		const float* positions = expression->positionOffsets;
		const float* normals = expression->normalOffsets;
		const float* tangents = expression->tangentOffsets;
		int positionStride = 3;
		int normalStride = 3;
		int tangentStride = 3;
		if (positions == 0)
		{
			positions = gNoVertexOffsets;
			positionStride = 0;
		}
		if (normals == 0)
		{
			normals = gNoVertexOffsets;
			normalStride = 0;
		}
		if (tangents == 0)
		{
			tangents = gNoVertexOffsets;
			tangentStride = 0;
		}
		math::Vector4 positionOffset(0.0f, 0.0f, 0.0f, 0.0f);
		math::Vector4 normalOffset(0.0f, 0.0f, 0.0f, 0.0f);
		math::Vector4 tangentOffset(0.0f, 0.0f, 0.0f, 0.0f);
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 v2 = _mm_load_ps(&vertices->tangent.x);
			positionOffset.x = positions[0];
			positionOffset.y = positions[1];
			positionOffset.z = positions[2];
			positions += positionStride;
			normalOffset.x = normals[0];
			normalOffset.y = normals[1];
			normalOffset.z = normals[2];
			normals += normalStride;
			tangentOffset.x = tangents[0];
			tangentOffset.y = tangents[1];
			tangentOffset.z = tangents[2];
			tangents += tangentStride;
			__m128 p0 = _mm_add_ps(v0, _mm_load_ps(&positionOffset.x));
			__m128 p1 = _mm_add_ps(v1, _mm_load_ps(&normalOffset.x));
			__m128 p2 = _mm_add_ps(v2, _mm_load_ps(&tangentOffset.x));
			BoneRows m = BlendBones(matrices, vertices);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, p0);
			__m128 r1 = BlendRows3Inline(m.r0, m.r1, m.r2, p1);
			__m128 r2 = BlendRows3Inline(m.r0, m.r1, m.r2, p2);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r2)[3] = ((float*)&v2)[3];
			_mm_storeu_ps(&out->x, r0);
			out++;
			_mm_storeu_ps(&out->x, r1);
			out++;
			_mm_storeu_ps(&out->x, r2);
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif


	// FUNCTION: ENGINE 0x1071CA40
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071CA40(math::Vector4* out, const SkinVertex* vertices, int count)
	{
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x4AF, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		const float* positions = expression->positionOffsets;
		const float* normals = expression->normalOffsets;
		const float* tangents = expression->tangentOffsets;
		int positionStride = 3;
		int normalStride = 3;
		int tangentStride = 3;
		if (positions == 0)
		{
			positions = gNoVertexOffsets;
			positionStride = 0;
		}
		if (normals == 0)
		{
			normals = gNoVertexOffsets;
			normalStride = 0;
		}
		if (tangents == 0)
		{
			tangents = gNoVertexOffsets;
			tangentStride = 0;
		}
		math::Vector4 positionOffset(0.0f, 0.0f, 0.0f, 0.0f);
		math::Vector4 normalOffset(0.0f, 0.0f, 0.0f, 0.0f);
		math::Vector4 tangentOffset(0.0f, 0.0f, 0.0f, 0.0f);
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 v2 = _mm_load_ps(&vertices->tangent.x);
			positionOffset.x = positions[0];
			positionOffset.y = positions[1];
			positionOffset.z = positions[2];
			positions += positionStride;
			normalOffset.x = normals[0];
			normalOffset.y = normals[1];
			normalOffset.z = normals[2];
			normals += normalStride;
			tangentOffset.x = tangents[0];
			tangentOffset.y = tangents[1];
			tangentOffset.z = tangents[2];
			tangents += tangentStride;
			__m128 p0 = _mm_add_ps(v0, _mm_load_ps(&positionOffset.x));
			__m128 p1 = _mm_add_ps(v1, _mm_load_ps(&normalOffset.x));
			__m128 p2 = _mm_add_ps(v2, _mm_load_ps(&tangentOffset.x));
			BoneRows m = LoadBoneRows(matrices, vertices->bones[0]);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, p0);
			__m128 r1 = BlendRows3Inline(m.r0, m.r1, m.r2, p1);
			__m128 r2 = BlendRows3Inline(m.r0, m.r1, m.r2, p2);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r2)[3] = ((float*)&v2)[3];
			_mm_storeu_ps(&out->x, r0);
			out++;
			_mm_storeu_ps(&out->x, r1);
			out++;
			_mm_storeu_ps(&out->x, r2);
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif


	// FUNCTION: ENGINE 0x1071CDC0
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071CDC0(math::Vector4* out, const SkinVertex* vertices, int count)
	{
		if (pddi->Unknown24(0x400001)->Unknown7())
		{
			return;
		}
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x529, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		const float* positions = expression->positionOffsets;
		const float* normals = expression->normalOffsets;
		int positionStride = 3;
		int normalStride = 3;
		if (positions == 0)
		{
			positions = gNoVertexOffsets;
			positionStride = 0;
		}
		if (normals == 0)
		{
			normals = gNoVertexOffsets;
			normalStride = 0;
		}
		math::Vector4 positionOffset(0.0f, 0.0f, 0.0f, 0.0f);
		math::Vector4 normalOffset(0.0f, 0.0f, 0.0f, 0.0f);
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			positionOffset.x = positions[0];
			positionOffset.y = positions[1];
			positionOffset.z = positions[2];
			positions += positionStride;
			normalOffset.x = normals[0];
			normalOffset.y = normals[1];
			normalOffset.z = normals[2];
			normals += normalStride;
			__m128 p0 = _mm_add_ps(v0, _mm_load_ps(&positionOffset.x));
			__m128 p1 = _mm_add_ps(v1, _mm_load_ps(&normalOffset.x));
			BoneRows m = BlendBones(matrices, vertices);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, p0);
			__m128 r1 = BlendRows3Inline(m.r0, m.r1, m.r2, p1);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			_mm_storeu_ps(&out->x, r0);
			out++;
			_mm_storeu_ps(&out->x, r1);
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif


	// FUNCTION: ENGINE 0x1071D1B0
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071D1B0(math::Vector4* out, const SkinVertex* vertices, int count)
	{
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x585, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		const float* positions = expression->positionOffsets;
		const float* normals = expression->normalOffsets;
		int positionStride = 3;
		int normalStride = 3;
		if (positions == 0)
		{
			positions = gNoVertexOffsets;
			positionStride = 0;
		}
		if (normals == 0)
		{
			normals = gNoVertexOffsets;
			normalStride = 0;
		}
		math::Vector4 positionOffset(0.0f, 0.0f, 0.0f, 0.0f);
		math::Vector4 normalOffset(0.0f, 0.0f, 0.0f, 0.0f);
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			positionOffset.x = positions[0];
			positionOffset.y = positions[1];
			positionOffset.z = positions[2];
			positions += positionStride;
			normalOffset.x = normals[0];
			normalOffset.y = normals[1];
			normalOffset.z = normals[2];
			normals += normalStride;
			__m128 p0 = _mm_add_ps(v0, _mm_load_ps(&positionOffset.x));
			__m128 p1 = _mm_add_ps(v1, _mm_load_ps(&normalOffset.x));
			BoneRows m = LoadBoneRows(matrices, vertices->bones[0]);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, p0);
			__m128 r1 = BlendRows3Inline(m.r0, m.r1, m.r2, p1);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			_mm_storeu_ps(&out->x, r0);
			out++;
			_mm_storeu_ps(&out->x, r1);
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif


	// FUNCTION: ENGINE 0x1071D440
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071D440(math::Vector4* out, const SkinVertex* vertices, int count)
	{
		if (pddi->Unknown24(0x400001)->Unknown7())
		{
			return;
		}
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x5E9, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		const float* positions = expression->positionOffsets;
		if (positions == 0)
		{
			positions = gNoVertexOffsets;
		}
		math::Vector4 positionOffset(0.0f, 0.0f, 0.0f, 0.0f);
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			positionOffset.x = positions[0];
			positionOffset.y = positions[1];
			positionOffset.z = positions[2];
			__m128 p0 = _mm_add_ps(v0, _mm_load_ps(&positionOffset.x));
			BoneRows m = BlendBones(matrices, vertices);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, p0);
			((float*)&r0)[3] = 1.0f;
			_mm_storeu_ps(&out->x, r0);
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif


	// FUNCTION: ENGINE 0x1071D770
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071D770(math::Vector4* out, const SkinVertex* vertices, int count)
	{
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x630, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		const float* positions = expression->positionOffsets;
		if (positions == 0)
		{
			positions = gNoVertexOffsets;
		}
		math::Vector4 positionOffset(0.0f, 0.0f, 0.0f, 0.0f);
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			positionOffset.x = positions[0];
			positionOffset.y = positions[1];
			positionOffset.z = positions[2];
			__m128 p0 = _mm_add_ps(v0, _mm_load_ps(&positionOffset.x));
			BoneRows m = LoadBoneRows(matrices, vertices->bones[0]);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, p0);
			((float*)&r0)[3] = 1.0f;
			_mm_storeu_ps(&out->x, r0);
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif


	// FUNCTION: ENGINE 0x1071D960
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071D960(math::Vector4* out, const SkinVertex2* vertices, int count)
	{
		if (pddi->Unknown24(0x400001)->Unknown7())
		{
			return;
		}
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x680, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 v2 = _mm_load_ps(&vertices->tangent.x);
			BoneRows m = BlendBones(matrices, vertices);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, v0);
			__m128 r1 = BlendRows3Inline(m.r0, m.r1, m.r2, v1);
			__m128 r2 = BlendRows3Inline(m.r0, m.r1, m.r2, v2);
			__m128 r3 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, _mm_add_ps(_mm_load_ps(&vertices->offset.x), v0));
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r2)[3] = ((float*)&v2)[3];
			((float*)&r3)[3] = 0.0f;
			_mm_storeu_ps(&out->x, r0);
			out++;
			_mm_storeu_ps(&out->x, r1);
			out++;
			_mm_storeu_ps(&out->x, r2);
			out++;
			_mm_storeu_ps(&out->x, _mm_sub_ps(r3, r0));
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif


	// FUNCTION: ENGINE 0x1071DD60
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071DD60(math::Vector4* out, const SkinVertex2* vertices, int count)
	{
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x6D2, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 v2 = _mm_load_ps(&vertices->tangent.x);
			BoneRows m = LoadBoneRows(matrices, vertices->bones[0]);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, v0);
			__m128 r1 = BlendRows3Inline(m.r0, m.r1, m.r2, v1);
			__m128 r2 = BlendRows3Inline(m.r0, m.r1, m.r2, v2);
			__m128 r3 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, _mm_add_ps(_mm_load_ps(&vertices->offset.x), v0));
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r2)[3] = ((float*)&v2)[3];
			((float*)&r3)[3] = 0.0f;
			_mm_storeu_ps(&out->x, r0);
			out++;
			_mm_storeu_ps(&out->x, r1);
			out++;
			_mm_storeu_ps(&out->x, r2);
			out++;
			_mm_storeu_ps(&out->x, _mm_sub_ps(r3, r0));
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif


	// FUNCTION: ENGINE 0x1071DFF0
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071DFF0(math::Vector4* out, const SkinVertex2* vertices, int count)
	{
		if (pddi->Unknown24(0x400001)->Unknown7())
		{
			return;
		}
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x72C, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			BoneRows m = BlendBones(matrices, vertices);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, v0);
			__m128 r1 = BlendRows3Inline(m.r0, m.r1, m.r2, v1);
			__m128 r3 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, _mm_add_ps(_mm_load_ps(&vertices->offset.x), v0));
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r3)[3] = 0.0f;
			_mm_storeu_ps(&out->x, r0);
			out++;
			_mm_storeu_ps(&out->x, r1);
			out++;
			_mm_storeu_ps(&out->x, _mm_sub_ps(r3, r0));
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif


	// FUNCTION: ENGINE 0x1071E390
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071E390(math::Vector4* out, const SkinVertex2* vertices, int count)
	{
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x772, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			BoneRows m = LoadBoneRows(matrices, vertices->bones[0]);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, v0);
			__m128 r1 = BlendRows3Inline(m.r0, m.r1, m.r2, v1);
			__m128 r3 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, _mm_add_ps(_mm_load_ps(&vertices->offset.x), v0));
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r3)[3] = 0.0f;
			_mm_storeu_ps(&out->x, r0);
			out++;
			_mm_storeu_ps(&out->x, r1);
			out++;
			_mm_storeu_ps(&out->x, _mm_sub_ps(r3, r0));
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif


	// FUNCTION: ENGINE 0x1071E5D0
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071E5D0(math::Vector4* out, const SkinVertex2* vertices, int count)
	{
		if (pddi->Unknown24(0x400001)->Unknown7())
		{
			return;
		}
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x7C1, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			BoneRows m = BlendBones(matrices, vertices);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, v0);
			__m128 r3 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, _mm_add_ps(_mm_load_ps(&vertices->offset.x), v0));
			((float*)&r0)[3] = 1.0f;
			((float*)&r3)[3] = 0.0f;
			_mm_storeu_ps(&out->x, r0);
			out++;
			_mm_storeu_ps(&out->x, _mm_sub_ps(r3, r0));
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif


	// FUNCTION: ENGINE 0x1071E8F0
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation and scheduling
#ifdef NONMATCHING
	void SkinState::Unknown1071E8F0(math::Vector4* out, const SkinVertex2* vertices, int count)
	{
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x801, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		math::Vector4 maxBounds(-1e12f, -1e12f, -1e12f, -1e12f);
		math::Vector4 minBounds(1e12f, 1e12f, 1e12f, 1e12f);
		for (unsigned int i = count; i > 0; i--)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			BoneRows m = LoadBoneRows(matrices, vertices->bones[0]);
			__m128 r0 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, v0);
			__m128 r3 = BlendRows4Inline(m.r0, m.r1, m.r2, m.r3, _mm_add_ps(_mm_load_ps(&vertices->offset.x), v0));
			((float*)&r0)[3] = 1.0f;
			((float*)&r3)[3] = 0.0f;
			_mm_storeu_ps(&out->x, r0);
			out++;
			_mm_storeu_ps(&out->x, _mm_sub_ps(r3, r0));
			out++;
			*(__m128*)&maxBounds = _mm_max_ps(*(__m128*)&maxBounds, r0);
			*(__m128*)&minBounds = _mm_min_ps(*(__m128*)&minBounds, r0);
			vertices++;
		}
		_mm_empty();
		bounds.min.x = minBounds.x;
		bounds.min.y = minBounds.y;
		bounds.min.z = minBounds.z;
		bounds.max.x = maxBounds.x;
		bounds.max.y = maxBounds.y;
		bounds.max.z = maxBounds.z;
	}
#endif


	// Blends the four rows of four bone matrices, weighted by the four lanes of the weights (out = m0 * w.x +
	// m1 * w.y + m2 * w.z + m3 * w.w), for the vertex record whose bone indices sit at +0x40. The callers are in
	// other units, so the name is a guess and the row pointers are the four rows of the destination matrix.
	// The body is the engine's block for block (each phase widens one lane of the weights and multiplies the four
	// rows of one bone by it, the first phase storing and the other three accumulating), and the whole of it is
	// straight-line code without a single branch, but the engine re-reads every argument pointer from the stack in
	// every phase (45 bytes of reloads we do not need) and materialises the first bone's address in edx, so its
	// allocation of the seven pointers cannot be reproduced from the source.
	// FUNCTION: ENGINE 0x1071B310
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation (the engine re-loads the argument pointers, we keep them), 21 %
#ifdef NONMATCHING
	void BlendBoneRows(const SkinVertex* vertex, const math::Matrix* matrices, const math::Vector4* weights,
		math::Vector4* row0, math::Vector4* row1, math::Vector4* row2, math::Vector4* row3)
	{
		const math::Matrix& m0 = matrices[vertex->bones[0]];
		const math::Matrix& m1 = matrices[vertex->bones[1]];
		const math::Matrix& m2 = matrices[vertex->bones[2]];
		const math::Matrix& m3 = matrices[vertex->bones[3]];
		__m128 w = _mm_load_ps(&weights->x);
		_mm_store_ps(&row0->x, _mm_mul_ps(_mm_shuffle_ps(w, w, _MM_SHUFFLE(0, 0, 0, 0)), _mm_load_ps(m0.m[0])));
		_mm_store_ps(&row1->x, _mm_mul_ps(_mm_shuffle_ps(w, w, _MM_SHUFFLE(0, 0, 0, 0)), _mm_load_ps(m0.m[1])));
		_mm_store_ps(&row2->x, _mm_mul_ps(_mm_shuffle_ps(w, w, _MM_SHUFFLE(0, 0, 0, 0)), _mm_load_ps(m0.m[2])));
		_mm_store_ps(&row3->x, _mm_mul_ps(_mm_shuffle_ps(w, w, _MM_SHUFFLE(0, 0, 0, 0)), _mm_load_ps(m0.m[3])));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m1.m[0]),
			_mm_shuffle_ps(w, w, _MM_SHUFFLE(1, 1, 1, 1))), _mm_load_ps(&row0->x)));
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m1.m[1]),
			_mm_shuffle_ps(w, w, _MM_SHUFFLE(1, 1, 1, 1))), _mm_load_ps(&row1->x)));
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m1.m[2]),
			_mm_shuffle_ps(w, w, _MM_SHUFFLE(1, 1, 1, 1))), _mm_load_ps(&row2->x)));
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m1.m[3]),
			_mm_shuffle_ps(w, w, _MM_SHUFFLE(1, 1, 1, 1))), _mm_load_ps(&row3->x)));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m2.m[0]),
			_mm_shuffle_ps(w, w, _MM_SHUFFLE(2, 2, 2, 2))), _mm_load_ps(&row0->x)));
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m2.m[1]),
			_mm_shuffle_ps(w, w, _MM_SHUFFLE(2, 2, 2, 2))), _mm_load_ps(&row1->x)));
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m2.m[2]),
			_mm_shuffle_ps(w, w, _MM_SHUFFLE(2, 2, 2, 2))), _mm_load_ps(&row2->x)));
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m2.m[3]),
			_mm_shuffle_ps(w, w, _MM_SHUFFLE(2, 2, 2, 2))), _mm_load_ps(&row3->x)));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m3.m[0]),
			_mm_shuffle_ps(w, w, _MM_SHUFFLE(3, 3, 3, 3))), _mm_load_ps(&row0->x)));
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m3.m[1]),
			_mm_shuffle_ps(w, w, _MM_SHUFFLE(3, 3, 3, 3))), _mm_load_ps(&row1->x)));
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m3.m[2]),
			_mm_shuffle_ps(w, w, _MM_SHUFFLE(3, 3, 3, 3))), _mm_load_ps(&row2->x)));
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m3.m[3]),
			_mm_shuffle_ps(w, w, _MM_SHUFFLE(3, 3, 3, 3))), _mm_load_ps(&row3->x)));
	}
#endif

	// The same for the wider vertex record (its bone indices sit at +0x50)
	// FUNCTION: ENGINE 0x1071B490
	// NONMATCHING (crashed in the game as EQUIVALENT): register allocation, the same as 0x1071B310, 21 %
#ifdef NONMATCHING
	void BlendBoneRowsWide(const SkinVertex2* vertex, const math::Matrix* matrices, const math::Vector4* weights,
		math::Vector4* row0, math::Vector4* row1, math::Vector4* row2, math::Vector4* row3)
	{
		const math::Matrix& m0 = matrices[vertex->bones[0]];
		const math::Matrix& m1 = matrices[vertex->bones[1]];
		const math::Matrix& m2 = matrices[vertex->bones[2]];
		const math::Matrix& m3 = matrices[vertex->bones[3]];
		__m128 w = _mm_load_ps(&weights->x);
		__m128 x = _mm_shuffle_ps(w, w, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 y = _mm_shuffle_ps(w, w, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 z = _mm_shuffle_ps(w, w, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 q = _mm_shuffle_ps(w, w, _MM_SHUFFLE(3, 3, 3, 3));
		_mm_store_ps(&row0->x, _mm_mul_ps(x, _mm_load_ps(m0.m[0])));
		_mm_store_ps(&row1->x, _mm_mul_ps(x, _mm_load_ps(m0.m[1])));
		_mm_store_ps(&row2->x, _mm_mul_ps(x, _mm_load_ps(m0.m[2])));
		_mm_store_ps(&row3->x, _mm_mul_ps(x, _mm_load_ps(m0.m[3])));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m1.m[0]), y), _mm_load_ps(&row0->x)));
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m1.m[1]), y), _mm_load_ps(&row1->x)));
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m1.m[2]), y), _mm_load_ps(&row2->x)));
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m1.m[3]), y), _mm_load_ps(&row3->x)));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m2.m[0]), z), _mm_load_ps(&row0->x)));
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m2.m[1]), z), _mm_load_ps(&row1->x)));
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m2.m[2]), z), _mm_load_ps(&row2->x)));
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m2.m[3]), z), _mm_load_ps(&row3->x)));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m3.m[0]), q), _mm_load_ps(&row0->x)));
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m3.m[1]), q), _mm_load_ps(&row1->x)));
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m3.m[2]), q), _mm_load_ps(&row2->x)));
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(_mm_load_ps(m3.m[3]), q), _mm_load_ps(&row3->x)));
	}
#endif

	// FUNCTION: ENGINE 0x1071B070
	bool SkinState::GetUnknown298()
	{
		return unknown298;
	}

	// FUNCTION: ENGINE 0x1071B0B0
	void SkinState::Unknown5()
	{
		if (controller1 != 0)
		{
			controller1->Reset();
		}
		if (controller2 != 0)
		{
			controller2->Reset();
		}
	}

	// FUNCTION: ENGINE 0x1071B0F0
	bool SkinState::Unknown6()
	{
		if (controller1 != 0 && !controller1->Unknown20())
		{
			return false;
		}
		if (controller2 != 0 && !controller2->Unknown20())
		{
			return false;
		}
		return true;
	}

	// The component-wise copies below are what the engine's fld/fstp pairs are: an implicit Vector::operator= would
	// copy the three floats with integer moves instead
	// FUNCTION: ENGINE 0x1071B130
	void SkinState::GetBoundingBox(math::AABB* box)
	{
		math::Vector* outMax = &box->max;
		math::Vector* outMin = &box->min;
		outMax->x = bounds.max.x;
		outMax->y = bounds.max.y;
		outMax->z = bounds.max.z;
		outMin->x = bounds.min.x;
		outMin->y = bounds.min.y;
		outMin->z = bounds.min.z;
	}

	// FUNCTION: ENGINE 0x1071B170
	void SkinState::SetBoundingBox(const math::AABB& box)
	{
		bounds.max.x = box.max.x;
		bounds.max.y = box.max.y;
		bounds.max.z = box.max.z;
		bounds.min.x = box.min.x;
		bounds.min.y = box.min.y;
		bounds.min.z = box.min.z;
	}

	// FUNCTION: ENGINE 0x1071B1B0
	void* SkinState::GetUnknown70()
	{
		return pose;
	}

	// FUNCTION: ENGINE 0x1071B1C0
	Pose* SkinState::GetPose()
	{
		return mPoses[mPoseIndex];
	}

	// FUNCTION: ENGINE 0x1071B1D0
	Pose* SkinState::GetBlendPose()
	{
		return mPoses[mBlendIndex + 1];
	}

	// FUNCTION: ENGINE 0x1071B1E0
	Pose* SkinState::GetPose(int index)
	{
		return mPoses[index + 1];
	}

	// FUNCTION: ENGINE 0x1071B200
	Expression* SkinState::GetExpression()
	{
		return expression;
	}

	// FUNCTION: ENGINE 0x1071B210
	ExpressionState* SkinState::GetExpressionState()
	{
		return expressionState;
	}

	// FUNCTION: ENGINE 0x1071B220
	FrameController* SkinState::GetController1()
	{
		return controller1;
	}

	// FUNCTION: ENGINE 0x1071B230
	FrameController* SkinState::GetController2()
	{
		return controller2;
	}

	// FUNCTION: ENGINE 0x1071B240
	void SkinState::Unknown8(void* source)
	{
		if (source == 0)
		{
			source = unknownC;
		}
		if (controller1 != 0)
		{
			controller1->SetBindingSource(source);
		}
	}

	// FUNCTION: ENGINE 0x1071EAE0
	void Skin::SubmitTask()
	{
		job.Submit(0);
	}

	// FUNCTION: ENGINE 0x1071EF00
	void Skin::GetBoundingBox(math::AABB* box)
	{
		math::Vector* outMax = &box->max;
		math::Vector* outMin = &box->min;
		outMax->x = bounds.max.x;
		outMax->y = bounds.max.y;
		outMax->z = bounds.max.z;
		outMin->x = bounds.min.x;
		outMin->y = bounds.min.y;
		outMin->z = bounds.min.z;
	}

	// FUNCTION: ENGINE 0x1071EF40
	void Skin::SetBoundingBox(const math::AABB& box)
	{
		bounds.max.x = box.max.x;
		bounds.max.y = box.max.y;
		bounds.max.z = box.max.z;
		bounds.min.x = box.min.x;
		bounds.min.y = box.min.y;
		bounds.min.z = box.min.z;
	}

	// FUNCTION: ENGINE 0x1071EF80
	void Skin::SetCentre(const math::Vector4& value)
	{
		centre.x = value.x;
		centre.y = value.y;
		centre.z = value.z;
		centre.w = value.w;
	}

	// FUNCTION: ENGINE 0x1071EFB0
	unsigned int Skin::GetUnknown1C()
	{
		return unknown1C;
	}

	// FUNCTION: ENGINE 0x1071EE50
	bool Skin::FillBatch(void* batch, PrimitiveState* state, bool* unknown)
	{
		PrimBatch* data = (PrimBatch*)batch;
		data->unknown70 = unknown1C;
		data->unknown74 = 0;
		data->unknown78 = 0;
		data->unknown7C = 0;
		data->unknown28 = 0;
		data->unknown80 = 0;
		stream->PrepareBatch(data);
		SkinState* skinState = (SkinState*)state;
		PrimGroupList* group = ((PrimGroupList*)skinState->GetPose())->AddGroup(data, 0);
		if (skinState->GetBlendPose() != 0)
		{
			data->unknown84 = true;
			group = ((PrimGroupList*)skinState->GetBlendPose())->AddGroup(data, group);
		}
		else
		{
			data->unknown84 = false;
		}
		if (buffer != 0)
		{
			((PrimGroupList*)buffer)->AddGroup(data, group);
		}
		*unknown = true;
		return true;
	}

	// The skinning path and the plain one each build their own descriptor (the engine's compiler merges the common
	// tail: the constructor call and the draw)
	// FUNCTION: ENGINE 0x1071ED50
	void Skin::Draw(const core::Name<core::CaseInsensitiveKey32>* shader, PrimitiveState* state,
		const math::Matrix* world, const PrimStreamParameters* parameters, PartBinding* binding)
	{
		SkinState* skinState = (SkinState*)state;
		skinState->Unknown9();
		PrimGroupList* groups[3] = {0, 0, 0};
		int count = 1;
		void* source = binding;
		if (source == 0)
		{
			source = skinState->GetBindingSource();
		}
		Pose* pose = skinState->GetPose();
		groups[0] = (PrimGroupList*)pose;
		if (skinState->GetBlendPose() != 0)
		{
			((PoseSkinView*)pose)->unknown138 = -1;
			groups[1] = (PrimGroupList*)buffer;
			groups[2] = (PrimGroupList*)skinState->GetBlendPose();
			PrimDrawDesc desc(((PrimBufferOwner*)source)->format, world, 3, (void**)groups, stream, unknown1C, 0, 0, 0);
			pddi->DrawPrimitive(shader, &desc, parameters);
		}
		else
		{
			if (buffer != 0)
			{
				groups[1] = (PrimGroupList*)buffer;
				count = 2;
			}
			PrimDrawDesc desc(((PrimBufferOwner*)source)->format, world, count, (void**)groups, stream, unknown1C, 0, 0, 0);
			pddi->DrawPrimitive(shader, &desc, parameters);
		}
	}

	// FUNCTION: ENGINE 0x1071EFE0
	void Skin::UnlockBuffer()
	{
		if (buffer != 0)
		{
			buffer->Unlock();
		}
	}

	// FUNCTION: ENGINE 0x1071F000
	void Skin::FillBufferDesc(int value)
	{
		if (buffer != 0)
		{
			buffer->Unknown10625FA0(value);
		}
	}

	// Packs x and y, taken from [-1, 1], and z, taken from [0, 1], into ten bits each and the fourth lane of the
	// second argument into the top two; the rounding is to the nearest bit (name and parameters are guesses, the
	// callers are in other units)
	// FUNCTION: ENGINE 0x1071F060
	unsigned int PackNormal10(const float* x, const float* y, const float* z)
	{
		unsigned int ix = (unsigned int)((*x + 1.0f) * 512.0f + 0.5f);
		unsigned int iy = (unsigned int)((*y + 1.0f) * 512.0f + 0.5f);
		unsigned int iz = (unsigned int)(*z * 1024.0f + 0.5f);
		unsigned int iw = (unsigned int)y[3];
		if (ix > 0x3FF)
		{
			ix = 0x3FF;
		}
		if (iy > 0x3FF)
		{
			iy = 0x3FF;
		}
		if (iz > 0x3FF)
		{
			iz = 0x3FF;
		}
		return (((((iw << 10) + (iz & 0x3FF)) << 10) + (iy & 0x3FF)) << 10) + (ix & 0x3FF);
	}

	// The same for the second component of each of the three (the fourth is the same lane of the second)
	// FUNCTION: ENGINE 0x1071F180
	unsigned int PackNormal10Y(const float* x, const float* y, const float* z)
	{
		unsigned int ix = (unsigned int)((x[1] + 1.0f) * 512.0f + 0.5f);
		unsigned int iy = (unsigned int)((y[1] + 1.0f) * 512.0f + 0.5f);
		unsigned int iz = (unsigned int)(z[1] * 1024.0f + 0.5f);
		unsigned int iw = (unsigned int)y[3];
		if (ix > 0x3FF)
		{
			ix = 0x3FF;
		}
		if (iy > 0x3FF)
		{
			iy = 0x3FF;
		}
		if (iz > 0x3FF)
		{
			iz = 0x3FF;
		}
		return (((((iw << 10) + (iz & 0x3FF)) << 10) + (iy & 0x3FF)) << 10) + (ix & 0x3FF);
	}

	// And for the third
	// FUNCTION: ENGINE 0x1071F2A0
	unsigned int PackNormal10Z(const float* x, const float* y, const float* z)
	{
		unsigned int ix = (unsigned int)((x[2] + 1.0f) * 512.0f + 0.5f);
		unsigned int iy = (unsigned int)((y[2] + 1.0f) * 512.0f + 0.5f);
		unsigned int iz = (unsigned int)(z[2] * 1024.0f + 0.5f);
		unsigned int iw = (unsigned int)y[3];
		if (ix > 0x3FF)
		{
			ix = 0x3FF;
		}
		if (iy > 0x3FF)
		{
			iy = 0x3FF;
		}
		if (iz > 0x3FF)
		{
			iz = 0x3FF;
		}
		return (((((iw << 10) + (iz & 0x3FF)) << 10) + (iy & 0x3FF)) << 10) + (ix & 0x3FF);
	}

	// FUNCTION: ENGINE 0x1071F020
	void Skin::GetDrawData(void** data, int* size)
	{
		if (unknown138 != 0)
		{
			*data = unknown138;
			*size = unknown13C;
		}
		else
		{
			*data = unknown140;
			*size = 0x50;
		}
	}

	// The centre is a Vector4 but the caller's pointer (the vtable takes a Vector) is followed by a fourth float in
	// the engine too: it copies all four components
	// FUNCTION: ENGINE 0x1071F9D0 (slot 6 of the vtable)
	void Skin::GetCentre(math::Vector* centre)
	{
		centre[0].x = this->centre.x;
		centre[0].y = this->centre.y;
		centre[0].z = this->centre.z;
		centre[1].x = this->centre.w;
	}

	// Submits every queued skinning job (once, the queue is a lock-free stack)
	// FUNCTION: ENGINE 0x1071F780
	void SubmitPendingSkins()
	{
		SkinJobEntry* entry = (SkinJobEntry*)PopListHead(&gPendingSkins);
		while (entry != 0)
		{
			entry->skin->SubmitTask();
			entry = (SkinJobEntry*)PopListHead(&gPendingSkins);
		}
	}

	// Waits for the running skinning jobs to finish
	// FUNCTION: ENGINE 0x1071F7F0
	void WaitForSkinJobs()
	{
		while ((int)_InterlockedAnd((long volatile*)&gSkinJobCount, -1) > 0)
		{
			core::ThreadSleep(0);
		}
	}

	// 0x1071F860 (SkinState::SetController1) is not done: it is the same body as 0x1071F880 but its
	// core::RefAssign copy is the one at 0x10707710 (another unit), so controller1 has to be declared with the type
	// that instantiation belongs to before it can be written.

	// FUNCTION: ENGINE 0x1071F880
	void SkinState::SetController2(FrameController* value)
	{
		core::RefAssign(controller2, value);
	}

	// FUNCTION: ENGINE 0x1071F9B0 (slot 9 of the vtable)
	int Skin::GetUnknown9()
	{
		return unknown294;
	}

	// FUNCTION: ENGINE 0x1071F9C0 (slot 10 of the vtable)
	void Skin::SetUnknown10(int value)
	{
		unknown294 = value;
	}

	// FUNCTION: ENGINE 0x10721160
	void SkinState::Update(float dt)
	{
		int frame = pddi->GetFrameCount(0);
		if (frame != (int)_InterlockedExchange((long volatile*)&mFrame, frame))
		{
			mBlendIndex = 0;
			if (controller1 != 0)
			{
				controller1->Advance(dt, true);
			}
			if (controller2 != 0)
			{
				controller2->Advance(dt, true);
			}
			Unknown10720CF0();
		}
	}

	// FUNCTION: ENGINE 0x107211D0
	bool SkinState::GetUnknown2AC()
	{
		return unknown2AC;
	}

}
