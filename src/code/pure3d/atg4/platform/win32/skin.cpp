// pure3d::SkinState and the skinning code (code/pure3d/atg4/platform/win32/skin.cpp, path from the asserts). Names
// are guesses.
#include <mmintrin.h>
#include <xmmintrin.h>

#include "code/core/debug.h"
#include "code/core/interlocked.h"
#include "code/core/refptr.h"
#include "code/core/thread.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/pddi/vertexdeclaration.h"
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

	// Whether the skinning jobs run on a worker thread, and how many have been queued
	// GLOBAL: ENGINE 0x11137804
	bool gSkinAsync = true;
	// GLOBAL: ENGINE 0x1128180C
	int gSkinQueuedCount = 0;

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

	// The four bones' matrices blended by the vertex's weights into four rows, bone after bone (the engine's inline form)
	template <class Vertex>
	__forceinline void BlendBoneRowsInline(const Vertex* vertex, const math::Matrix* matrices, const math::Vector4* weights,
		math::Vector4* row0, math::Vector4* row1, math::Vector4* row2, math::Vector4* row3)
	{
		const __m128* p0 = (const __m128*)&matrices[vertex->bones[0]];
		const __m128* p1 = (const __m128*)&matrices[vertex->bones[1]];
		const __m128* p2 = (const __m128*)&matrices[vertex->bones[2]];
		const __m128* p3 = (const __m128*)&matrices[vertex->bones[3]];
		__m128 xs = _mm_load_ps(&weights->x);
		xs = _mm_shuffle_ps(xs, xs, _MM_SHUFFLE(0, 0, 0, 0));
		_mm_store_ps(&row0->x, _mm_mul_ps(xs, *p0++));
		_mm_store_ps(&row1->x, _mm_mul_ps(xs, *p0++));
		_mm_store_ps(&row2->x, _mm_mul_ps(xs, *p0++));
		_mm_store_ps(&row3->x, _mm_mul_ps(xs, *p0++));
		__m128 ys = _mm_load_ps(&weights->x);
		ys = _mm_shuffle_ps(ys, ys, _MM_SHUFFLE(1, 1, 1, 1));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(*p1++, ys), _mm_load_ps(&row0->x)));
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(*p1++, ys), _mm_load_ps(&row1->x)));
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(*p1++, ys), _mm_load_ps(&row2->x)));
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(*p1++, ys), _mm_load_ps(&row3->x)));
		__m128 zs = _mm_load_ps(&weights->x);
		zs = _mm_shuffle_ps(zs, zs, _MM_SHUFFLE(2, 2, 2, 2));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(*p2++, zs), _mm_load_ps(&row0->x)));
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(*p2++, zs), _mm_load_ps(&row1->x)));
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(*p2++, zs), _mm_load_ps(&row2->x)));
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(*p2++, zs), _mm_load_ps(&row3->x)));
		__m128 qs = _mm_load_ps(&weights->x);
		qs = _mm_shuffle_ps(qs, qs, _MM_SHUFFLE(3, 3, 3, 3));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(*p3++, qs), _mm_load_ps(&row0->x)));
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(*p3++, qs), _mm_load_ps(&row1->x)));
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(*p3++, qs), _mm_load_ps(&row2->x)));
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(*p3++, qs), _mm_load_ps(&row3->x)));
	}

	// The zeros the offset paths read when the expression has no offsets of a kind
	// GLOBAL: ENGINE 0x11281818
	float gNoVertexOffsets[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// The skinning paths share one shape. What the engine's bytes ask for: the box accumulators are two __m128
	// locals filled lane by lane through float casts (they get the same stack slot discipline as the blended rows),
	// the matrix rows the blends use are references to the bone's memory (`const __m128& m0 = *p++`, so the loads
	// stay where they are used and the pointer walks the four rows), the output pointer is a local copy of `out`, and
	// the loop is `for (unsigned int i = count; i > 0; i--)` when its counter lives in a register (the one-bone
	// paths) and `for (unsigned int i = 0; i < (unsigned int)count; i++)` when it lives in memory (the four-bone
	// paths and the paths that read the expression's offsets: the compiler counts down from the guard and creates the
	// counter after the loop-invariant stride scalings). The paths that read the offsets also use a __restrict
	// output pointer: the offsets they read each pass do not change and the engine's loop hoists them. A vector that
	// is added to and blended again (the tangent of 0x1071CA40) is one variable and its fourth lane is read right
	// after the load, which puts the vector and its result into one stack slot.
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
	// NONMATCHING: the four-bone blend: the engine loads the first bone's rows and the vertex's vectors earlier and keeps the blended rows in memory (frame 0xA4, ours 0x74), the translation row's first product comes late; the loop's counter, guard and pre-header are the engine's, 16.6 %
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
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 v2 = _mm_load_ps(&vertices->tangent.x);
			__m128 m0, m1, m2, m3;
			BlendBoneRowsInline(vertices, matrices, &vertices->weights, (math::Vector4*)&m0, (math::Vector4*)&m1, (math::Vector4*)&m2, (math::Vector4*)&m3);
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
#endif

	// FUNCTION: ENGINE 0x1071BBD0
	// NONMATCHING: the four-bone blend (see 0x1071B610): frame 0x64 against ours 0x54, 35.1 %
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
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 m0, m1, m2, m3;
			BlendBoneRowsInline(vertices, matrices, &vertices->weights, (math::Vector4*)&m0, (math::Vector4*)&m1, (math::Vector4*)&m2, (math::Vector4*)&m3);
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
	// NONMATCHING: the four-bone blend (see 0x1071B610): the loop, its pre-header and the frame are the engine's; the first bone's rows come out in other registers and the translation row's product is not delayed, 43.2 %
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
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 m0, m1, m2, m3;
			BlendBoneRowsInline(vertices, matrices, &vertices->weights, (math::Vector4*)&m0, (math::Vector4*)&m1, (math::Vector4*)&m2, (math::Vector4*)&m3);
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
	// NONMATCHING: the four-bone blend (see 0x1071B610) with the offsets: the tangent is added to in place and its fourth lane is read right after the load, as in 0x1071CA40; 30.7 %
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
		math::Vector4 positionOffset;
		positionOffset.w = 0.0f;
		math::Vector4 normalOffset;
		normalOffset.w = 0.0f;
		math::Vector4 tangentOffset;
		tangentOffset.w = 0.0f;
		math::Vector4* __restrict dst = out;
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
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 v2 = _mm_load_ps(&vertices->tangent.x);
			float tangentW = ((float*)&v2)[3];
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
			v2 = _mm_add_ps(v2, _mm_load_ps(&tangentOffset.x));
			__m128 m0, m1, m2, m3;
			BlendBoneRowsInline(vertices, matrices, &vertices->weights, (math::Vector4*)&m0, (math::Vector4*)&m1, (math::Vector4*)&m2, (math::Vector4*)&m3);
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, p0);
			__m128 r1 = BlendRows3Inline(m0, m1, m2, p1);
			__m128 r2 = BlendRows3Inline(m0, m1, m2, v2);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r2)[3] = tangentW;
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
#endif

	// FUNCTION: ENGINE 0x1071CA40
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
		__m128 positionOffset;
		((float*)&positionOffset)[3] = 0.0f;
		__m128 normalOffset;
		((float*)&normalOffset)[3] = 0.0f;
		__m128 tangentOffset;
		((float*)&tangentOffset)[3] = 0.0f;
		math::Vector4* __restrict dst = out;
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
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 v2 = _mm_load_ps(&vertices->tangent.x);
			float tangentW = ((float*)&v2)[3];
			((float*)&positionOffset)[0] = positions[0];
			((float*)&positionOffset)[1] = positions[1];
			((float*)&positionOffset)[2] = positions[2];
			positions += positionStride;
			((float*)&normalOffset)[0] = normals[0];
			((float*)&normalOffset)[1] = normals[1];
			((float*)&normalOffset)[2] = normals[2];
			normals += normalStride;
			((float*)&tangentOffset)[0] = tangents[0];
			((float*)&tangentOffset)[1] = tangents[1];
			((float*)&tangentOffset)[2] = tangents[2];
			tangents += tangentStride;
			__m128 p0 = _mm_add_ps(v0, positionOffset);
			__m128 p1 = _mm_add_ps(v1, normalOffset);
			v2 = _mm_add_ps(v2, tangentOffset);
			const __m128* p = (const __m128*)&matrices[vertices->bones[0]];
			const __m128& m0 = *p++;
			const __m128& m1 = *p++;
			const __m128& m2 = *p++;
			const __m128& m3 = *p++;
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, p0);
			__m128 r1 = BlendRows3Inline(m0, m1, m2, p1);
			__m128 r2 = BlendRows3Inline(m0, m1, m2, v2);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r2)[3] = tangentW;
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

	// FUNCTION: ENGINE 0x1071CDC0
	// NONMATCHING: the four-bone blend (see 0x1071B610) with the offsets, 34.5 %
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
		math::Vector4 positionOffset;
		positionOffset.w = 0.0f;
		math::Vector4 normalOffset;
		normalOffset.w = 0.0f;
		math::Vector4* __restrict dst = out;
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
		for (unsigned int i = 0; i < (unsigned int)count; i++)
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
			__m128 m0, m1, m2, m3;
			BlendBoneRowsInline(vertices, matrices, &vertices->weights, (math::Vector4*)&m0, (math::Vector4*)&m1, (math::Vector4*)&m2, (math::Vector4*)&m3);
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, p0);
			__m128 r1 = BlendRows3Inline(m0, m1, m2, p1);
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
#endif

	// FUNCTION: ENGINE 0x1071D1B0
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
		math::Vector4 positionOffset;
		positionOffset.w = 0.0f;
		math::Vector4 normalOffset;
		normalOffset.w = 0.0f;
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
		math::Vector4* __restrict dst = out;
		for (unsigned int i = 0; i < (unsigned int)count; i++)
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
			const __m128* p = (const __m128*)&matrices[vertices->bones[0]];
			const __m128& m0 = *p++;
			const __m128& m1 = *p++;
			const __m128& m2 = *p++;
			const __m128& m3 = *p++;
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, p0);
			__m128 r1 = BlendRows3Inline(m0, m1, m2, p1);
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

	// FUNCTION: ENGINE 0x1071D440
	// NONMATCHING: the four-bone blend (see 0x1071B610) with the position offset (one for all the vertices, read ahead of the loop), 40.7 %
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
		math::Vector4 positionOffset;
		positionOffset.w = 0.0f;
		math::Vector4* __restrict dst = out;
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
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			positionOffset.x = positions[0];
			positionOffset.y = positions[1];
			positionOffset.z = positions[2];
			__m128 p0 = _mm_add_ps(v0, _mm_load_ps(&positionOffset.x));
			__m128 m0, m1, m2, m3;
			BlendBoneRowsInline(vertices, matrices, &vertices->weights, (math::Vector4*)&m0, (math::Vector4*)&m1, (math::Vector4*)&m2, (math::Vector4*)&m3);
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, p0);
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
#endif

	// FUNCTION: ENGINE 0x1071D770
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
		math::Vector4* __restrict dst = out;
		math::Vector4 positionOffset;
		positionOffset.w = 0.0f;
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
		if ((unsigned int)count > 0)
		{
			unsigned int i = count;
			do
			{
				__m128 v0 = _mm_load_ps(&vertices->position.x);
				positionOffset.x = positions[0];
				positionOffset.y = positions[1];
				positionOffset.z = positions[2];
				__m128 p0 = _mm_add_ps(v0, _mm_load_ps(&positionOffset.x));
				const __m128* p = (const __m128*)&matrices[vertices->bones[0]];
				const __m128& m0 = *p++;
				const __m128& m1 = *p++;
				const __m128& m2 = *p++;
				const __m128& m3 = *p++;
				__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, p0);
				((float*)&r0)[3] = 1.0f;
				_mm_storeu_ps(&dst->x, r0);
				dst++;
				maxBounds = _mm_max_ps(maxBounds, r0);
				minBounds = _mm_min_ps(minBounds, r0);
				vertices++;
			} while (--i);
		}
		_mm_empty();
		bounds.min.x = ((float*)&minBounds)[0];
		bounds.min.y = ((float*)&minBounds)[1];
		bounds.min.z = ((float*)&minBounds)[2];
		bounds.max.x = ((float*)&maxBounds)[0];
		bounds.max.y = ((float*)&maxBounds)[1];
		bounds.max.z = ((float*)&maxBounds)[2];
	}

	// FUNCTION: ENGINE 0x1071D960
	// NONMATCHING: the four-bone blend (see 0x1071B610) with the second position, 30.0 %
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
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 v2 = _mm_load_ps(&vertices->tangent.x);
			__m128 p3 = _mm_add_ps(_mm_load_ps(&vertices->offset.x), v0);
			__m128 m0, m1, m2, m3;
			BlendBoneRowsInline(vertices, matrices, &vertices->weights, (math::Vector4*)&m0, (math::Vector4*)&m1, (math::Vector4*)&m2, (math::Vector4*)&m3);
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, v0);
			__m128 r1 = BlendRows3Inline(m0, m1, m2, v1);
			__m128 r2 = BlendRows3Inline(m0, m1, m2, v2);
			__m128 r3 = BlendRows4Inline(m0, m1, m2, m3, p3);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r2)[3] = ((float*)&v2)[3];
			((float*)&r3)[3] = 0.0f;
			_mm_storeu_ps(&dst->x, r0);
			dst++;
			_mm_storeu_ps(&dst->x, r1);
			dst++;
			_mm_storeu_ps(&dst->x, r2);
			dst++;
			_mm_storeu_ps(&dst->x, _mm_sub_ps(r3, r0));
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
#endif

	// FUNCTION: ENGINE 0x1071DD60
	void SkinState::Unknown1071DD60(math::Vector4* out, const SkinVertex2* vertices, int count)
	{
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x6D2, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
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
			__m128 p3 = _mm_add_ps(_mm_load_ps(&vertices->offset.x), v0);
			const __m128* p = (const __m128*)&matrices[vertices->bones[0]];
			const __m128& m0 = *p++;
			const __m128& m1 = *p++;
			const __m128& m2 = *p++;
			const __m128& m3 = *p++;
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, v0);
			__m128 r1 = BlendRows3Inline(m0, m1, m2, v1);
			__m128 r2 = BlendRows3Inline(m0, m1, m2, v2);
			__m128 r3 = BlendRows4Inline(m0, m1, m2, m3, p3);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r2)[3] = ((float*)&v2)[3];
			((float*)&r3)[3] = 0.0f;
			_mm_storeu_ps(&dst->x, r0);
			dst++;
			_mm_storeu_ps(&dst->x, r1);
			dst++;
			_mm_storeu_ps(&dst->x, r2);
			dst++;
			_mm_storeu_ps(&dst->x, _mm_sub_ps(r3, r0));
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

	// FUNCTION: ENGINE 0x1071DFF0
	// NONMATCHING: the four-bone blend (see 0x1071B610) with the second position, frame 0x74 against ours 0x64, 33.2 %
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
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 p3 = _mm_add_ps(_mm_load_ps(&vertices->offset.x), v0);
			__m128 m0, m1, m2, m3;
			BlendBoneRowsInline(vertices, matrices, &vertices->weights, (math::Vector4*)&m0, (math::Vector4*)&m1, (math::Vector4*)&m2, (math::Vector4*)&m3);
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, v0);
			__m128 r1 = BlendRows3Inline(m0, m1, m2, v1);
			__m128 r3 = BlendRows4Inline(m0, m1, m2, m3, p3);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r3)[3] = 0.0f;
			_mm_storeu_ps(&dst->x, r0);
			dst++;
			_mm_storeu_ps(&dst->x, r1);
			dst++;
			_mm_storeu_ps(&dst->x, _mm_sub_ps(r3, r0));
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
#endif

	// FUNCTION: ENGINE 0x1071E390
	void SkinState::Unknown1071E390(math::Vector4* out, const SkinVertex2* vertices, int count)
	{
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x772, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
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
			__m128 p3 = _mm_add_ps(_mm_load_ps(&vertices->offset.x), v0);
			const __m128* p = (const __m128*)&matrices[vertices->bones[0]];
			const __m128& m0 = *p++;
			const __m128& m1 = *p++;
			const __m128& m2 = *p++;
			const __m128& m3 = *p++;
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, v0);
			__m128 r1 = BlendRows3Inline(m0, m1, m2, v1);
			__m128 r3 = BlendRows4Inline(m0, m1, m2, m3, p3);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r3)[3] = 0.0f;
			_mm_storeu_ps(&dst->x, r0);
			dst++;
			_mm_storeu_ps(&dst->x, r1);
			dst++;
			_mm_storeu_ps(&dst->x, _mm_sub_ps(r3, r0));
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

	// FUNCTION: ENGINE 0x1071E5D0
	// NONMATCHING: the four-bone blend (see 0x1071B610) with the second position, frame 0x64 against ours 0x54, 34.9 %
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
		for (unsigned int i = 0; i < (unsigned int)count; i++)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 p3 = _mm_add_ps(_mm_load_ps(&vertices->offset.x), v0);
			__m128 m0, m1, m2, m3;
			BlendBoneRowsInline(vertices, matrices, &vertices->weights, (math::Vector4*)&m0, (math::Vector4*)&m1, (math::Vector4*)&m2, (math::Vector4*)&m3);
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, v0);
			__m128 r3 = BlendRows4Inline(m0, m1, m2, m3, p3);
			((float*)&r0)[3] = 1.0f;
			((float*)&r3)[3] = 0.0f;
			_mm_storeu_ps(&dst->x, r0);
			dst++;
			_mm_storeu_ps(&dst->x, _mm_sub_ps(r3, r0));
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
#endif

	// FUNCTION: ENGINE 0x1071E8F0
	void SkinState::Unknown1071E8F0(math::Vector4* out, const SkinVertex2* vertices, int count)
	{
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x801, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
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
			__m128 p3 = _mm_add_ps(_mm_load_ps(&vertices->offset.x), v0);
			const __m128* p = (const __m128*)&matrices[vertices->bones[0]];
			const __m128& m0 = *p++;
			const __m128& m1 = *p++;
			const __m128& m2 = *p++;
			const __m128& m3 = *p++;
			__m128 r0 = BlendRows4Inline(m0, m1, m2, m3, v0);
			__m128 r3 = BlendRows4Inline(m0, m1, m2, m3, p3);
			((float*)&r0)[3] = 1.0f;
			((float*)&r3)[3] = 0.0f;
			_mm_storeu_ps(&dst->x, r0);
			dst++;
			_mm_storeu_ps(&dst->x, _mm_sub_ps(r3, r0));
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

	// Blends the four rows of four bone matrices, weighted by the four lanes of the weights (out = m0 * w.x +
	// m1 * w.y + m2 * w.z + m3 * w.w), for the vertex record whose bone indices sit at +0x40. Nothing calls it (the
	// four-bone paths carry the same code inline), so the name is a guess and the row pointers are the four rows of
	// the destination matrix. Each phase widens one lane of the weights and multiplies the four rows of one bone by it,
	// the first phase storing and the other three accumulating; the weights are read again in every phase (a store
	// through a row pointer may change them), and that part of the source is right. What does not come out is the
	// first phase and the bone pointers' increments.
	// FUNCTION: ENGINE 0x1071B310
	// NONMATCHING: the pointer increments of the bone rows and the loads of the first bone's rows (the engine loads the first row before the weights and does not fold the loads into the multiplies), 45 %
#ifdef NONMATCHING
	void BlendBoneRows(const SkinVertex* vertex, const math::Matrix* matrices, const math::Vector4* weights,
		math::Vector4* row0, math::Vector4* row1, math::Vector4* row2, math::Vector4* row3)
	{
		const __m128* p0 = (const __m128*)&matrices[vertex->bones[0]];
		const __m128* p1 = (const __m128*)&matrices[vertex->bones[1]];
		const __m128* p2 = (const __m128*)&matrices[vertex->bones[2]];
		const __m128* p3 = (const __m128*)&matrices[vertex->bones[3]];
		__m128 a00 = *p0++;
		__m128 ws = _mm_load_ps(&weights->x);
		ws = _mm_shuffle_ps(ws, ws, _MM_SHUFFLE(0, 0, 0, 0));
		_mm_store_ps(&row0->x, _mm_mul_ps(ws, a00));
		__m128 a01 = *p0++;
		_mm_store_ps(&row1->x, _mm_mul_ps(ws, a01));
		__m128 a02 = *p0++;
		_mm_store_ps(&row2->x, _mm_mul_ps(ws, a02));
		__m128 a03 = *p0++;
		_mm_store_ps(&row3->x, _mm_mul_ps(ws, a03));
		__m128 a10 = *p1++;
		__m128 xs = _mm_load_ps(&weights->x);
		xs = _mm_shuffle_ps(xs, xs, _MM_SHUFFLE(1, 1, 1, 1));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(a10, xs), _mm_load_ps(&row0->x)));
		__m128 a11 = *p1++;
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(a11, xs), _mm_load_ps(&row1->x)));
		__m128 a12 = *p1++;
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(a12, xs), _mm_load_ps(&row2->x)));
		__m128 a13 = *p1++;
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(a13, xs), _mm_load_ps(&row3->x)));
		__m128 a20 = *p2++;
		__m128 ys = _mm_load_ps(&weights->x);
		ys = _mm_shuffle_ps(ys, ys, _MM_SHUFFLE(2, 2, 2, 2));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(a20, ys), _mm_load_ps(&row0->x)));
		__m128 a21 = *p2++;
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(a21, ys), _mm_load_ps(&row1->x)));
		__m128 a22 = *p2++;
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(a22, ys), _mm_load_ps(&row2->x)));
		__m128 a23 = *p2++;
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(a23, ys), _mm_load_ps(&row3->x)));
		__m128 a30 = *p3++;
		__m128 zs = _mm_load_ps(&weights->x);
		zs = _mm_shuffle_ps(zs, zs, _MM_SHUFFLE(3, 3, 3, 3));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(a30, zs), _mm_load_ps(&row0->x)));
		__m128 a31 = *p3++;
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(a31, zs), _mm_load_ps(&row1->x)));
		__m128 a32 = *p3++;
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(a32, zs), _mm_load_ps(&row2->x)));
		__m128 a33 = *p3++;
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(a33, zs), _mm_load_ps(&row3->x)));
	}
#endif

	// The same for the wider vertex record (its bone indices sit at +0x50)
	// FUNCTION: ENGINE 0x1071B490
	// NONMATCHING: the same as 0x1071B310, 45 %
#ifdef NONMATCHING
	void BlendBoneRowsWide(const SkinVertex2* vertex, const math::Matrix* matrices, const math::Vector4* weights,
		math::Vector4* row0, math::Vector4* row1, math::Vector4* row2, math::Vector4* row3)
	{
		const __m128* p0 = (const __m128*)&matrices[vertex->bones[0]];
		const __m128* p1 = (const __m128*)&matrices[vertex->bones[1]];
		const __m128* p2 = (const __m128*)&matrices[vertex->bones[2]];
		const __m128* p3 = (const __m128*)&matrices[vertex->bones[3]];
		__m128 a00 = *p0++;
		__m128 ws = _mm_load_ps(&weights->x);
		ws = _mm_shuffle_ps(ws, ws, _MM_SHUFFLE(0, 0, 0, 0));
		_mm_store_ps(&row0->x, _mm_mul_ps(ws, a00));
		__m128 a01 = *p0++;
		_mm_store_ps(&row1->x, _mm_mul_ps(ws, a01));
		__m128 a02 = *p0++;
		_mm_store_ps(&row2->x, _mm_mul_ps(ws, a02));
		__m128 a03 = *p0++;
		_mm_store_ps(&row3->x, _mm_mul_ps(ws, a03));
		__m128 a10 = *p1++;
		__m128 xs = _mm_load_ps(&weights->x);
		xs = _mm_shuffle_ps(xs, xs, _MM_SHUFFLE(1, 1, 1, 1));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(a10, xs), _mm_load_ps(&row0->x)));
		__m128 a11 = *p1++;
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(a11, xs), _mm_load_ps(&row1->x)));
		__m128 a12 = *p1++;
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(a12, xs), _mm_load_ps(&row2->x)));
		__m128 a13 = *p1++;
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(a13, xs), _mm_load_ps(&row3->x)));
		__m128 a20 = *p2++;
		__m128 ys = _mm_load_ps(&weights->x);
		ys = _mm_shuffle_ps(ys, ys, _MM_SHUFFLE(2, 2, 2, 2));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(a20, ys), _mm_load_ps(&row0->x)));
		__m128 a21 = *p2++;
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(a21, ys), _mm_load_ps(&row1->x)));
		__m128 a22 = *p2++;
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(a22, ys), _mm_load_ps(&row2->x)));
		__m128 a23 = *p2++;
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(a23, ys), _mm_load_ps(&row3->x)));
		__m128 a30 = *p3++;
		__m128 zs = _mm_load_ps(&weights->x);
		zs = _mm_shuffle_ps(zs, zs, _MM_SHUFFLE(3, 3, 3, 3));
		_mm_store_ps(&row0->x, _mm_add_ps(_mm_mul_ps(a30, zs), _mm_load_ps(&row0->x)));
		__m128 a31 = *p3++;
		_mm_store_ps(&row1->x, _mm_add_ps(_mm_mul_ps(a31, zs), _mm_load_ps(&row1->x)));
		__m128 a32 = *p3++;
		_mm_store_ps(&row2->x, _mm_add_ps(_mm_mul_ps(a32, zs), _mm_load_ps(&row2->x)));
		__m128 a33 = *p3++;
		_mm_store_ps(&row3->x, _mm_add_ps(_mm_mul_ps(a33, zs), _mm_load_ps(&row3->x)));
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
	void Skin::FillBufferDesc(ShaderParameters* parameters)
	{
		if (buffer != 0)
		{
			buffer->Unknown10625FA0(parameters);
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

	// FUNCTION: ENGINE 0x10720CF0
	// EQUIVALENT: the engine's instructions in its registers and frame, 91.3 %; the order of the loads and the multiply in the three stream set-ups, of the flag test in front of the third one and of one store and the load of the format word in the queueing branch differs
	void SkinState::Unknown10720CF0()
	{
		if (unknown2AE)
		{
			return;
		}
		Unknown9();
		mPoseIndex++;
		if (mPoseIndex > 0)
		{
			mPoseIndex = 0;
		}
		Skin* skin = (Skin*)GetPrimitive();
		ShaderParameters bufferParameters;
		((PrimBuffer*)mPoses[mPoseIndex])->Unknown10625FA0(&bufferParameters);
		dxVertexDeclaration destLock;
		destLock.unknown110 = 0;
		((PrimBuffer*)mPoses[mPoseIndex])->Lock(&destLock, 0);
		if (destLock.unknown108 == 0)
		{
			((PrimBuffer*)mPoses[mPoseIndex])->Unlock();
			return;
		}
		_InterlockedIncrement((long volatile*)&gSkinJobCount);
		int count = destLock.unknown0;
		OLD_ASSERT_AT(SKIN_FILE, 0x87B, ((destLock.elements[0].unknown9 & 0x0F) == 0),
			"(((unsigned)destLock.componentDesc[0].stride) & 0x0F) == 0", "Bad Skin dest stride");
		void* sourceData;
		int sourceCount;
		skin->GetDrawData(&sourceData, &sourceCount);
		OLD_ASSERT_AT(SKIN_FILE, 0x880, (((unsigned)sourceData & 0x0F) == 0), "(((unsigned)sourceData) & 0x0F) == 0",
			"Bad Skin src ptr");
		ShaderParameters skinParameters;
		skin->GetParameters(&skinParameters);
		int start0 = streams[0].offset + destLock.unknown108;
		streams[0].end = streams[0].stride * destLock.unknown0 + start0;
		streams[0].start = start0;
		streams[0].current = start0;
		int start1 = streams[1].offset + destLock.unknown108;
		streams[1].end = streams[1].stride * destLock.unknown0 + start1;
		streams[1].start = start1;
		streams[1].current = start1;
		int start2 = streams[2].offset + destLock.unknown108;
		streams[2].start = start2;
		streams[2].current = start2;
		streams[2].end = streams[2].stride * destLock.unknown0 + start2;
		bool hasNormals = streams[1].enabled;
		bool hasTangents = streams[2].enabled;
		if (gSkinAsync)
		{
			jobPending = true;
			unknown10 = 2;
			pose->Lock();
			core::EventReset(&unknown14, 1);
			jobData->source = sourceData;
			jobData->destination = destLock.unknown108;
			jobData->count = count;
			if (expression != 0)
			{
				jobData->positionOffsets = expression->positionOffsets;
				jobData->normalOffsets = expression->normalOffsets;
				jobData->tangentOffsets = expression->tangentOffsets;
			}
			jobData->hasNormals = streams[1].enabled;
			jobData->hasTangents = streams[2].enabled;
			jobData->wide = ((unsigned int)skinParameters.unknownC >> 29) & 1;
			PushListHead(&gPendingSkins, (void**)&entry);
			gSkinQueuedCount++;
			return;
		}
		math::Vector4* out = (math::Vector4*)destLock.unknown108;
		const SkinVertex* vertices = (const SkinVertex*)sourceData;
		const SkinVertex2* wideVertices = (const SkinVertex2*)sourceData;
		if (hasNormals)
		{
			if (hasTangents)
			{
				if (expression != 0)
				{
					if (skin->unknown298)
					{
						Unknown1071CA40(out, vertices, destLock.unknown0);
					}
					else
					{
						Unknown1071C530(out, vertices, destLock.unknown0);
					}
				}
				else if (skinParameters.unknownC & 0x20000000)
				{
					if (skin->unknown298)
					{
						Unknown1071DD60(out, wideVertices, destLock.unknown0);
					}
					else
					{
						Unknown1071D960(out, wideVertices, destLock.unknown0);
					}
				}
				else if (skin->unknown298)
				{
					Unknown1071B9A0(out, vertices, destLock.unknown0);
				}
				else
				{
					Unknown1071B610(out, vertices, destLock.unknown0);
				}
			}
			else
			{
				if (expression != 0)
				{
					if (skin->unknown298)
					{
						Unknown1071D1B0(out, vertices, destLock.unknown0);
					}
					else
					{
						Unknown1071CDC0(out, vertices, destLock.unknown0);
					}
				}
				else if (skinParameters.unknownC & 0x20000000)
				{
					if (skin->unknown298)
					{
						Unknown1071E390(out, wideVertices, destLock.unknown0);
					}
					else
					{
						Unknown1071DFF0(out, wideVertices, destLock.unknown0);
					}
				}
				else if (skin->unknown298)
				{
					Unknown1071BEE0(out, vertices, destLock.unknown0);
				}
				else
				{
					Unknown1071BBD0(out, vertices, destLock.unknown0);
				}
			}
		}
		else
		{
			if (expression != 0)
			{
				if (skin->unknown298)
				{
					Unknown1071D770(out, vertices, destLock.unknown0);
				}
				else
				{
					Unknown1071D440(out, vertices, destLock.unknown0);
				}
			}
			else if (skinParameters.unknownC & 0x20000000)
			{
				if (skin->unknown298)
				{
					Unknown1071E8F0(out, wideVertices, destLock.unknown0);
				}
				else
				{
					Unknown1071E5D0(out, wideVertices, destLock.unknown0);
				}
			}
			else if (skin->unknown298)
			{
				Unknown1071C390(out, vertices, destLock.unknown0);
			}
			else
			{
				Unknown1071C0C0(out, vertices, destLock.unknown0);
			}
		}
		((PrimBuffer*)mPoses[mPoseIndex])->Unlock();
		_InterlockedDecrement((long volatile*)&gSkinJobCount);
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
