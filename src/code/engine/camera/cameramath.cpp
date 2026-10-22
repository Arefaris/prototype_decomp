#include "code/engine/camera/cameramath.h"
#include "code/math/sincos.h"
#include "code/math/worldbounds.h"
#include <float.h>
#include <math.h>

// FUNCTION: ENGINE 0x1084D000
bool math::Vector::IsNear(const Vector& other, float tolerance) const
{
	return fabsf(x - other.x) <= tolerance && fabsf(y - other.y) <= tolerance && fabsf(z - other.z) <= tolerance;
}

namespace engine
{
	namespace camera
	{
		// FUNCTION: ENGINE 0x1084CBB0
		float EaseOut(float t, float duration)
		{
			if (duration != 0.0f)
			{
				float x = t / duration;
				return 1.0f - 1.0f / (((0.235f * x + 0.48f) * x + 1.0f) * x + 1.0f);
			}
			return 1.0f;
		}

		// FUNCTION: ENGINE 0x1084CBF0
		float EaseFloat(float from, float to, float t, float duration)
		{
			return EaseOut(t, duration) * (to - from) + from;
		}

		// FUNCTION: ENGINE 0x1084CC20
		// EQUIVALENT: the engine loads the three pointers in another order, so the registers and the position of the stores differ; 74.2 %
		void EaseVector(math::Vector* out, const math::Vector* from, const math::Vector* to, float t, float duration)
		{
			float e = EaseOut(t, duration);
			out->x = (to->x - from->x) * e + from->x;
			out->y = (to->y - from->y) * e + from->y;
			out->z = (to->z - from->z) * e + from->z;
		}

		// FUNCTION: ENGINE 0x1084CD20
		// EQUIVALENT: same operations in the same order; the engine spills the easing factor and loads the vectors in another order; 23.4 %
		void EaseVectorSpline(math::Vector* out, const math::Vector* from, const math::Vector* to, const math::Vector* next,
			float t, float duration)
		{
			float e = EaseOut(t, duration);
			float w = 0.0f;
			if (t != 0.0f)
			{
				w = 1.0f - (e / t) * duration;
			}
			float ty = to->y;
			float tz = to->z;
			float ny = next->y;
			float nz = next->z;
			out->x = (to->x - from->x) * e + (next->x - to->x) * w + from->x;
			float fz = from->z;
			out->y = (ty - from->y) * e + (ny - ty) * w + from->y;
			out->z = (tz - fz) * e + (nz - tz) * w + fz;
		}

		// FUNCTION: ENGINE 0x1084CE10
		// EQUIVALENT: same operations; the engine schedules the loads and the multiplications differently and so takes other xmm registers; 54.0 %
		float SmoothDamp(float current, float target, float* velocity, float delta, float smoothTime)
		{
			if (smoothTime == 0.0f)
			{
				*velocity = 0.0f;
				return target;
			}
			smoothTime = 2.0f / smoothTime;
			float x = smoothTime * delta;
			float decay = 1.0f / (((x * 0.235f + 0.48f) * x + 1.0f) * x + 1.0f);
			delta = ((current - target) * smoothTime + *velocity) * delta;
			float result = (delta + (current - target)) * decay + target;
			*velocity = (*velocity - delta * smoothTime) * decay;
			smoothTime = result;
			if (target == 0.0f && fabsf(smoothTime) <= 0.00001f && fabsf(*velocity) <= 0.00001f)
			{
				*velocity = 0.0f;
				return 0.0f;
			}
			return smoothTime;
		}

		// FUNCTION: ENGINE 0x1084CF10
		float WrapAngle(float angle, float min)
		{
			if (_isnan(angle))
			{
				return 0.0f;
			}
			float upper = min + 6.2831855f;
			float shifted;
			if (min > angle)
			{
				shifted = angle + 6.2831855f;
				if (shifted >= min)
				{
					return shifted;
				}
			}
			else
			{
				if (angle < upper)
				{
					return angle;
				}
				shifted = angle - 6.2831855f;
				if (upper > shifted)
				{
					return shifted;
				}
			}
			float turns = (angle - min) * 0.15915494f;
			return (turns - floor(turns)) * 6.2831855f + min;
		}

		// FUNCTION: ENGINE 0x1084CFB0
		float LerpFieldOfView(float t, float a, float b)
		{
			if (a == b)
			{
				return a;
			}
			float focalA = 1.0f / tan(a * 0.5f);
			float focalB = 1.0f / tan(b * 0.5f);
			float fov = atan(1.0f / ((focalB - focalA) * t + focalA));
			return fov + fov;
		}

		// FUNCTION: ENGINE 0x1084D050
		float GetYaw(const math::Vector* v)
		{
			if (fabsf(v->x) <= 0.00001f && fabsf(v->z) <= 0.00001f)
			{
				return 0.0f;
			}
			return atan2(v->x, v->z);
		}

		// FUNCTION: ENGINE 0x1084D080
		void FromSpherical(math::Vector* out, const Spherical* s)
		{
			float sinYaw, cosYaw, sinPitch, cosPitch;
			math::SinCos(s->yaw, &sinYaw, &cosYaw);
			math::SinCos(s->pitch, &sinPitch, &cosPitch);
			float r = s->distance;
			float horizontal = r * cosPitch;
			out->x = horizontal * sinYaw;
			out->y = r * sinPitch;
			out->z = horizontal * cosYaw;
		}

		// FUNCTION: ENGINE 0x1084D120
		void RotateAroundX(float angle, math::Vector* v)
		{
			float s, c;
			math::SinCos(angle, &s, &c);
			float y = v->y;
			v->y = v->z * s + y * c;
			v->z = v->z * c - y * s;
		}

		// FUNCTION: ENGINE 0x1084D190
		void RotateAroundY(float angle, math::Vector* v)
		{
			float s, c;
			math::SinCos(angle, &s, &c);
			float x = v->x;
			v->x = v->z * s + x * c;
			v->z = v->z * c - x * s;
		}

		// FUNCTION: ENGINE 0x1084D200
		// NONMATCHING: the engine keeps the vector temporaries in memory (483 bytes against our 384); 22.4 %
#ifdef NONMATCHING
		void SmoothDampVector(math::Vector* out, const math::Vector* current, const math::Vector* target,
			math::Vector* velocity, float delta, float smoothTime)
		{
			if (smoothTime == 0.0f)
			{
				velocity->z = 0.0f;
				velocity->y = 0.0f;
				velocity->x = 0.0f;
				out->x = target->x;
				out->y = target->y;
				out->z = target->z;
				return;
			}
			float omega = 2.0f / smoothTime;
			float x = omega * delta;
			float decay = 1.0f / (((x * 0.235f + 0.48f) * x + 1.0f) * x + 1.0f);
			float cx = current->x - target->x;
			float cy = current->y - target->y;
			float cz = current->z - target->z;
			float tx = (velocity->x + cx * omega) * delta;
			float ty = (velocity->y + cy * omega) * delta;
			float tz = (velocity->z + cz * omega) * delta;
			velocity->x = (velocity->x - tx * omega) * decay;
			velocity->z = (velocity->z - tz * omega) * decay;
			velocity->y = (velocity->y - ty * omega) * decay;
			out->x = target->x + (tx + cx) * decay;
			out->y = target->y + (ty + cy) * decay;
			out->z = target->z + (tz + cz) * decay;
		}
#endif

		// FUNCTION: ENGINE 0x1084D3F0
		float ClampAngle(float angle, float lo, float hi)
		{
			float span = WrapAngle(hi - lo, 0.0f);
			float offset = WrapAngle(angle - lo, 0.0f);
			if (span < offset)
			{
				if (WrapAngle(angle - (span * 0.5f + lo), -3.1415927f) > 0.0f)
				{
					angle = hi;
				}
				else
				{
					angle = lo;
				}
			}
			return WrapAngle(angle, -3.1415927f);
		}

		// FUNCTION: ENGINE 0x1084D4C0
		float LerpAngle(float t, float from, float to, float direction)
		{
			float diff = to - from;
			float delta;
			if (direction > 0.0f)
			{
				delta = WrapAngle(diff, 0.0f);
			}
			else if (direction < 0.0f)
			{
				delta = -WrapAngle(math::WORLD_MIN - diff, 0.0f);
			}
			else
			{
				delta = WrapAngle(diff, -3.1415927f);
			}
			return WrapAngle(delta * t + from, -3.1415927f);
		}

		// FUNCTION: ENGINE 0x1084D560
		float ApplyDeadZone(float value, float deadZone)
		{
			float magnitude = fabsf(value);
			if (magnitude <= deadZone)
			{
				return 0.0f;
			}
			float scaled = (magnitude - deadZone) / (1.0f - deadZone);
			value = value >= 0.0f ? scaled : math::WORLD_MIN - scaled;
			return value;
		}

		// FUNCTION: ENGINE 0x1084D5D0
		// EQUIVALENT: register allocation and the position of the argument loads before the WrapAngle calls; 63.1 %
		void Spherical::Normalize()
		{
			float d = distance;
			if (d == 0.0f)
			{
				yaw = 0.0f;
				pitch = 0.0f;
				return;
			}
			bool flip = false;
			if (d < 0.0f)
			{
				float p0 = math::WORLD_MIN - pitch;
				distance = math::WORLD_MIN - d;
				flip = true;
				pitch = p0;
			}
			float p = WrapAngle(pitch, -3.1415927f);
			pitch = p;
			if (fabsf(p) > 1.5707964f)
			{
				flip = !flip;
				if (p > 0.0f)
				{
					pitch = 3.1415927f - p;
				}
				else
				{
					pitch = p - 3.1415927f;
				}
			}
			if (flip)
			{
				yaw = yaw + 3.1415927f;
			}
			yaw = WrapAngle(yaw, -3.1415927f);
		}

		// FUNCTION: ENGINE 0x1084D6B0
		// EQUIVALENT: the engine keeps the x component on the x87 stack for the later comparison, ours reloads it; the same operations; 24.5 %
		Spherical* ToSpherical(Spherical* out, const math::Vector* v)
		{
			float length = (float)sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
			out->distance = length;
			if (length < 0.00001f)
			{
				out->yaw = 0.0f;
				out->pitch = 0.0f;
				return out;
			}
			if (fabsf(v->x) <= 0.00001f && fabsf(v->z) <= 0.00001f)
			{
				out->yaw = 0.0f;
				out->pitch = (float)asin(v->y / length);
				return out;
			}
			out->yaw = atan2(v->x, v->z);
			out->pitch = (float)asin(v->y / length);
			return out;
		}

		// FUNCTION: ENGINE 0x1084D750
		float GetPitch(const math::Vector* v)
		{
			float length = (float)sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
			if (length < 0.00001f)
			{
				return 0.0f;
			}
			return (float)asin(v->y / length);
		}
	}
}
