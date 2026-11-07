#include "code/proto/render/hud.h"

namespace proto
{
	// FUNCTION: ENGINE 0x102D7BB0
	// NONMATCHING: the stores are the engine's; the engine returns this in eax before the last coordinate is stored (about
	// 71 %)
#ifdef NONMATCHING
	HUDState::HUDState(pure3d::Primitive* newPrimitive, const math::Vector2* newPosition, const math::Vector2* newSize,
		float newParameter, int newMode) : pure3d::PrimitiveState(newPrimitive)
	{
		opacity = 1.0f;
		position.x = newPosition->x;
		position.y = newPosition->y;
		size.x = newSize->x;
		size.y = newSize->y;
		parameter = newParameter;
		unknown34 = 0.0f;
		colour = 0xFFFFFFFF;
		mode = newMode;
		time = 0.0f;
	}
#endif

	// FUNCTION: ENGINE 0x102D7C50
	HUDState::HUDState(const HUDState& other) : pure3d::PrimitiveState(other.primitive)
	{
		opacity = 1.0f;
		position.x = other.position.x;
		position.y = other.position.y;
		size.x = other.size.x;
		size.y = other.size.y;
		parameter = other.parameter;
		unknown34 = 0.0f;
		colour = other.colour;
		mode = other.mode;
		time = 0.0f;
	}

	// FUNCTION: ENGINE 0x102D7CD0
	pure3d::PrimitiveState* HUDState::Unknown3()
	{
		return new HUDState(*this);
	}

	// FUNCTION: ENGINE 0x102D7FF0
	void HUDState::Unknown5()
	{
	}

	// FUNCTION: ENGINE 0x102D8000
	bool HUDState::Unknown6()
	{
		return 0.0f == opacity;
	}

	// FUNCTION: ENGINE 0x102D8020
	void HUDState::GetBoundingBox(math::AABB* box)
	{
		box->min.x = 0.0f;
		box->min.y = 0.0f;
		box->min.z = 0.0f;
		box->max.x = 0.0f;
		box->max.y = 0.0f;
		box->max.z = 0.0f;
		box->Inflate();
	}

	// FUNCTION: ENGINE 0x102D8060
	void HUDState::SetMode(int newMode)
	{
		mode = newMode;
		if (newMode == 0)
		{
			unknown34 = (float)((unsigned char*)&colour)[3] * (1.0f / 255.0f);
		}
	}

	int HUD::sCount = 0;

	// FUNCTION: ENGINE 0x102D8520
	HUD::HUD(pure3d::Shader* shader) : pure3d::Primitive(0x8000)
	{
		id = sCount++;
		pure3d::Primitive::Unknown4(shader);
		flagWord.SetBit(3, true);
	}

	// FUNCTION: ENGINE 0x102D8090
	HUD::~HUD()
	{
	}

	// FUNCTION: ENGINE 0x102D80B0
	void HUD::GetBoundingBox(math::AABB* box)
	{
		box->max.x = 10000.0f;
		box->max.y = 10000.0f;
		box->max.z = 10000.0f;
		box->min.x = -10000.0f;
		box->min.y = -10000.0f;
		box->min.z = -10000.0f;
	}

	// FUNCTION: ENGINE 0x102D80A0
	bool HUD::FillBatch(void* batch, pure3d::PrimitiveState* state, bool* unknown)
	{
		*unknown = false;
		return false;
	}

	// FUNCTION: ENGINE 0x102D8100
	int HUD::Unknown8()
	{
		return id;
	}

	// FUNCTION: ENGINE 0x102D85B0
	// NONMATCHING: the stores are the engine's; the engine returns this in eax before the last coordinate is stored (about
	// 91 %)
#ifdef NONMATCHING
	LaserSightState::LaserSightState(pure3d::Primitive* newPrimitive, const math::Vector* newStart,
		const math::Vector* newEnd, float newParameter, const math::Vector4* newColour)
		: pure3d::PrimitiveState(newPrimitive)
	{
		start.x = newStart->x;
		start.y = newStart->y;
		start.z = newStart->z;
		end.x = newEnd->x;
		end.y = newEnd->y;
		end.z = newEnd->z;
		colour.x = newColour->x;
		colour.y = newColour->y;
		colour.z = newColour->z;
		colour.w = newColour->w;
		parameter = newParameter;
	}
#endif

	// FUNCTION: ENGINE 0x102D8650
	LaserSightState::LaserSightState(const LaserSightState& other) : pure3d::PrimitiveState(other.primitive)
	{
		start.x = other.start.x;
		start.y = other.start.y;
		start.z = other.start.z;
		end.x = other.end.x;
		end.y = other.end.y;
		end.z = other.end.z;
		colour.x = other.colour.x;
		colour.y = other.colour.y;
		colour.z = other.colour.z;
		colour.w = other.colour.w;
		parameter = other.parameter;
	}

	// FUNCTION: ENGINE 0x102D86D0
	pure3d::PrimitiveState* LaserSightState::Unknown3()
	{
		return new LaserSightState(*this);
	}

	// FUNCTION: ENGINE 0x102D8700
	void LaserSightState::Update(float dt)
	{
	}

	// FUNCTION: ENGINE 0x102D8710
	void LaserSightState::Unknown5()
	{
	}

	// FUNCTION: ENGINE 0x102D8720
	bool LaserSightState::Unknown6()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x102D8730
	void LaserSightState::GetBoundingBox(math::AABB* box)
	{
		box->max.x = 10000.0f;
		box->max.y = 10000.0f;
		box->max.z = 10000.0f;
		box->min.x = -10000.0f;
		box->min.y = -10000.0f;
		box->min.z = -10000.0f;
	}

	// FUNCTION: ENGINE 0x102D9020
	LaserSight::LaserSight(pure3d::Shader* shader) : pure3d::Primitive(0x2000)
	{
		pure3d::Primitive::Unknown4(shader);
		flagWord.SetBit(3, true);
	}

	// FUNCTION: ENGINE 0x102D8780
	LaserSight::~LaserSight()
	{
	}

	// FUNCTION: ENGINE 0x102D87A0
	void LaserSight::GetBoundingBox(math::AABB* box)
	{
		box->max.x = 10000.0f;
		box->max.y = 10000.0f;
		box->max.z = 10000.0f;
		box->min.x = -10000.0f;
		box->min.y = -10000.0f;
		box->min.z = -10000.0f;
	}

	// FUNCTION: ENGINE 0x102D8790
	bool LaserSight::FillBatch(void* batch, pure3d::PrimitiveState* state, bool* unknown)
	{
		*unknown = false;
		return false;
	}
}
