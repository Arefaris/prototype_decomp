// pure3d::SkinState and the skinning code (code/pure3d/atg4/platform/win32/skin.cpp, path from the asserts). Names
// are guesses.
#include <xmmintrin.h>

#include "code/core/interlocked.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
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
	void* PopListHead(void** head)
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
		return _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(x, a), _mm_mul_ps(y, b)), _mm_mul_ps(z, c)), d);
	}

	// a * weights.x + b * weights.y + c * weights.z, four lanes at a time
	// FUNCTION: ENGINE 0x1071B2C0
	__m128 BlendRows3(const __m128& a, const __m128& b, const __m128& c, const __m128& weights)
	{
		__m128 x = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 y = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 z = _mm_shuffle_ps(weights, weights, _MM_SHUFFLE(2, 2, 2, 2));
		return _mm_add_ps(_mm_add_ps(_mm_mul_ps(x, a), _mm_mul_ps(y, b)), _mm_mul_ps(z, c));
	}

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

	// FUNCTION: ENGINE 0x1071B130
	// NONMATCHING: the engine copies the box through fld/fstp; needs a user-defined Vector::operator=, which would
	// change every unit
#ifdef NONMATCHING
	void SkinState::GetBoundingBox(math::AABB* box)
	{
		box->max = bounds.max;
		box->min = bounds.min;
	}
#endif

	// FUNCTION: ENGINE 0x1071B170
	// NONMATCHING: the engine copies the box through fld/fstp; needs a user-defined Vector::operator=, which would
	// change every unit
#ifdef NONMATCHING
	void SkinState::SetBoundingBox(const math::AABB& box)
	{
		bounds.max = box.max;
		bounds.min = box.min;
	}
#endif

	// FUNCTION: ENGINE 0x1071B1B0
	void* SkinState::GetUnknown70()
	{
		return unknown70;
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

	// FUNCTION: ENGINE 0x1071EFB0
	void* Skin::GetUnknown1C()
	{
		return unknown1C;
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
