#include "code/math/mathutils.h"
#include "code/proto/render/bloodsplatter.h"

namespace proto
{
	// FUNCTION: ENGINE 0x102CBF50
	// NONMATCHING: the stores and the sum are the engine's; the engine leaves the last coordinate on the x87 stack until
	// after `return this` is loaded (about 64 %)
#ifdef NONMATCHING
	BloodSplatterState::BloodSplatterState(pure3d::Primitive* newPrimitive, const math::Vector2* newPosition,
		const math::Vector2* newSize, float newAngle, float newFadeIn, float newHold, float newFadeOut)
		: pure3d::PrimitiveState(newPrimitive)
	{
		position.x = newPosition->x;
		position.y = newPosition->y;
		size.x = newSize->x;
		size.y = newSize->y;
		angle = newAngle;
		hold = newHold;
		fadeOut = newFadeOut;
		remaining = newFadeIn + newHold + newFadeOut;
		fadeIn = newFadeIn;
	}
#endif

	// FUNCTION: ENGINE 0x102CC000
	BloodSplatterState::BloodSplatterState(const BloodSplatterState& other) : pure3d::PrimitiveState(other.primitive)
	{
		position.x = other.position.x;
		position.y = other.position.y;
		size.x = other.size.x;
		size.y = other.size.y;
		angle = other.angle;
		hold = other.hold;
		fadeOut = other.fadeOut;
		remaining = other.remaining;
		fadeIn = other.fadeIn;
	}

	// FUNCTION: ENGINE 0x102CC070
	pure3d::PrimitiveState* BloodSplatterState::Unknown3()
	{
		return new BloodSplatterState(*this);
	}

	// FUNCTION: ENGINE 0x102CC350
	void BloodSplatterState::Update(float dt)
	{
		float left = remaining - dt * 0.001f;
		if (left < 0.0f)
		{
			left = 0.0f;
		}
		remaining = left;
	}

	// FUNCTION: ENGINE 0x102CC0D0
	void BloodSplatterState::GetBoundingBox(math::AABB* box)
	{
		box->min.x = 0.0f;
		box->min.y = 0.0f;
		box->min.z = 0.0f;
		box->max.x = 0.0f;
		box->max.y = 0.0f;
		box->max.z = 0.0f;
		box->Inflate();
	}

	// FUNCTION: ENGINE 0x102CC160
	float BloodSplatterState::GetRemainingShare()
	{
		return math::Clamp(remaining / fadeOut, 0.0f, 1.0f);
	}

	int BloodSplatter::sCount = 0;

	// FUNCTION: ENGINE 0x102CC940
	// NONMATCHING: the arithmetic and calls are the engine's; the engine stores the vftable after the counter and the
	// shader argument are loaded, ours right after the primitive's constructor (about 52 %)
#ifdef NONMATCHING
	BloodSplatter::BloodSplatter(pure3d::Shader* shader) : pure3d::Primitive(0x1000), id(sCount++)
	{
		Unknown4(shader);
		flagWord.SetBit(3, true);
	}
#endif

	// FUNCTION: ENGINE 0x102CC1D0
	BloodSplatter::~BloodSplatter()
	{
	}

	// FUNCTION: ENGINE 0x102CC210
	void BloodSplatter::GetBoundingBox(math::AABB* box)
	{
		box->max.x = 10000.0f;
		box->max.y = 10000.0f;
		box->max.z = 10000.0f;
		box->min.x = -10000.0f;
		box->min.y = -10000.0f;
		box->min.z = -10000.0f;
	}

	// FUNCTION: ENGINE 0x102CC200
	bool BloodSplatter::FillBatch(void* batch, pure3d::PrimitiveState* state, bool* unknown)
	{
		*unknown = false;
		return false;
	}

	// The centre is a Vector4 but the caller's pointer (the vftable takes a Vector) is followed by a fourth float in
	// the engine too
	// FUNCTION: ENGINE 0x102CC8D0
	void BloodSplatter::GetCentre(math::Vector* centre)
	{
		centre[0].x = 0.0f;
		centre[0].y = 0.0f;
		centre[0].z = 0.0f;
		centre[1].x = 10000.0f;
	}

	// FUNCTION: ENGINE 0x102CC290
	int BloodSplatter::Unknown8()
	{
		return id;
	}

	// FUNCTION: ENGINE 0x102CC1E0
	int BloodSplatter::GetUnknown9()
	{
		return -1;
	}

	// FUNCTION: ENGINE 0x102CC1F0
	void BloodSplatter::SetUnknown10(int value)
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102CC320
// FUNCTION: ENGINE 0x102CC390
// FUNCTION: ENGINE 0x102CBFF0
