// pure3d::SkinState and the skinning code (code/pure3d/atg4/platform/win32/skin.cpp, path from the asserts). Names
// are guesses.
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

	// a * weights.x + b * weights.y + c * weights.z + d, four lanes at a time
	// FUNCTION: ENGINE 0x1071B270
	__m128 BlendRows4(const __m128& a, const __m128& b, const __m128& c, const __m128& d,
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
	// FUNCTION: ENGINE 0x1071B2C0
	__m128 BlendRows3(const __m128& a, const __m128& b, const __m128& c, const __m128& weights)
	{
		__m128 x = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 y = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 z = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 blended = _mm_mul_ps(x, a);
		blended = _mm_add_ps(blended, _mm_mul_ps(y, b));
		return _mm_add_ps(blended, _mm_mul_ps(z, c));
	}

	// The body below is the engine's, instruction for instruction: the vertex and matrix loads, the two blends, the
	// fourth lane fixed by hand, the four-lane min/max accumulation and the six component stores of the box. The
	// compiler of the hybrid build allocates the two blend temps and the first two matrix rows the other way round
	// (x to xmm7 and the first row to xmm3 where the engine has xmm6 and xmm4), which mirrors the first eight
	// shuffles and multiplies of every pass; it also keeps the output and the vertex pointer in swapped registers
	// (18 %). The layout of the vertex, the helpers and the box accumulation are settled, so this is a shared source
	// or a front-end difference, not a missing piece.
	// FUNCTION: ENGINE 0x1071B9A0
	// NONMATCHING: register allocation (the blend temps and the first matrix row are mirrored), 18 %
#ifdef NONMATCHING
	void SkinState::Unknown1071B9A0(math::Vector4* out, const SkinVertex* vertices, int count)
	{
		const math::Matrix* matrices = pose->mData.mSkinMatrices;
		OLD_ASSERT_AT(SKIN_FILE, 0x2E6, (((unsigned)matrices & 0x0F) == 0), "(((unsigned)matrices) & 0x0F) == 0",
			"Bad Skin bone matrices ptr");
		__m128 maxBounds = _mm_set_ps(-1e12f, -1e12f, -1e12f, -1e12f);
		__m128 minBounds = _mm_set_ps(1e12f, 1e12f, 1e12f, 1e12f);
		while (count != 0)
		{
			__m128 v0 = _mm_load_ps(&vertices->position.x);
			__m128 v1 = _mm_load_ps(&vertices->normal.x);
			__m128 v2 = _mm_load_ps(&vertices->tangent.x);
			const math::Matrix& bone = matrices[vertices->bones[0]];
			__m128 m0 = _mm_load_ps(bone.m[0]);
			__m128 m1 = _mm_load_ps(bone.m[1]);
			__m128 m2 = _mm_load_ps(bone.m[2]);
			__m128 m3 = _mm_load_ps(bone.m[3]);
			// The position goes through the whole 4x4, the two directions through the 3x3 only. The engine keeps
			// the rows in memory (it writes their fourth lane by hand): the position's and the normal's is 1, the
			// tangent's is the one it came with.
			__m128 r0 = BlendRows4(m0, m1, m2, m3, v0);
			__m128 r1 = BlendRows3(m0, m1, m2, v1);
			__m128 r2 = BlendRows3(m0, m1, m2, v2);
			((float*)&r0)[3] = 1.0f;
			((float*)&r1)[3] = 1.0f;
			((float*)&r2)[3] = ((float*)&v2)[3];
			_mm_storeu_ps(&out[0].x, r0);
			_mm_storeu_ps(&out[1].x, r1);
			_mm_storeu_ps(&out[2].x, r2);
			out += 3;
			maxBounds = _mm_max_ps(maxBounds, r0);
			minBounds = _mm_min_ps(minBounds, r0);
			vertices++;
			count--;
		}
		bounds.min.x = ((float*)&minBounds)[0];
		bounds.min.y = ((float*)&minBounds)[1];
		bounds.min.z = ((float*)&minBounds)[2];
		bounds.max.x = ((float*)&maxBounds)[0];
		bounds.max.y = ((float*)&maxBounds)[1];
		bounds.max.z = ((float*)&maxBounds)[2];
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

	// FUNCTION: ENGINE 0x1071ED50
	// NONMATCHING: the engine keeps the state in edi, the skin in esi, the binding source in ebx and the group count
	// in ebp and pushes the one or three groups as an immediate; ours assigns those registers the other way round
	// (state esi, skin edi, source ebp, count ebx), which no local order tried changes, 14 %
#ifdef NONMATCHING
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
			count = 3;
		}
		else if (buffer != 0)
		{
			groups[1] = (PrimGroupList*)buffer;
			count = 2;
		}
		PrimDrawDesc desc(((PrimBufferOwner*)source)->format, world, count, (void**)groups, stream, unknown1C, 0, 0, 0);
		pddi->DrawPrimitive(shader, &desc, parameters);
	}
#endif

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
	int Skin::GetUnknown294()
	{
		return unknown294;
	}

	// FUNCTION: ENGINE 0x1071F9C0 (slot 10 of the vtable)
	void Skin::SetUnknown294(int value)
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
