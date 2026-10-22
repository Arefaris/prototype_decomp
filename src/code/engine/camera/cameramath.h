// The camera code's shared math: angle wrapping, eased interpolation, a critically damped spring and spherical
// coordinates. All names are guesses.
#ifndef ENGINE_CAMERA_CAMERAMATH_H
#define ENGINE_CAMERA_CAMERAMATH_H

#include "code/math/vector.h"

namespace engine
{
	namespace camera
	{
		// A direction as distance, yaw (around Y, from +Z towards +X) and pitch (above the XZ plane)
		class Spherical
		{
		public:
			float distance;
			float yaw;
			float pitch;

			// 0x1084D5D0: brings the angles into range (a negative distance flips, a pitch beyond a quarter turn goes over the pole)
			void Normalize();
		};

		// 0x1084CF10: angle moved by whole turns into [min, min + 2 pi)
		float WrapAngle(float angle, float min);
		// 0x1084CBB0: 1 - exp(-t / duration) approximated with a rational function; 1 for a zero duration
		float EaseOut(float t, float duration);
		// 0x1084CBF0: from + (to - from) * EaseOut(t, duration)
		float EaseFloat(float from, float to, float t, float duration);
		// 0x1084CC20: out = from + (to - from) * EaseOut(t, duration)
		void EaseVector(math::Vector* out, const math::Vector* from, const math::Vector* to, float t, float duration);
		// 0x1084CD20: EaseVector plus the velocity term of the segment from..to
		void EaseVectorSpline(math::Vector* out, const math::Vector* from, const math::Vector* to, const math::Vector* next,
			float t, float duration);
		// 0x1084CE10: critically damped spring step from current towards target; the velocity is kept in *velocity
		float SmoothDamp(float current, float target, float* velocity, float delta, float smoothTime);
		// 0x1084D200: SmoothDamp of a vector
		void SmoothDampVector(math::Vector* out, const math::Vector* current, const math::Vector* target,
			math::Vector* velocity, float delta, float smoothTime);
		// 0x1084CFB0: field of view that interpolates the focal length from the view angle a to b
		float LerpFieldOfView(float t, float a, float b);
		// 0x1084D3F0: angle clamped into the arc from lo to hi (counter-clockwise)
		float ClampAngle(float angle, float lo, float hi);
		// 0x1084D4C0: from + t * (shortest or forced-direction difference to to); the sign of direction forces the way round
		float LerpAngle(float t, float from, float to, float direction);
		// 0x1084D560: a stick-like value with a dead zone, rescaled to 0..1
		float ApplyDeadZone(float value, float deadZone);
		// 0x1084D050: angle of the vector's XZ part (0 when it is shorter than the epsilon)
		float GetYaw(const math::Vector* v);
		// 0x1084D750: asin of y over the length, 0 for a short vector
		float GetPitch(const math::Vector* v);
		// 0x1084D6B0: out = distance, yaw and pitch of v
		Spherical* ToSpherical(Spherical* out, const math::Vector* v);
		// 0x1084D080: out = the point at the spherical coordinates
		void FromSpherical(math::Vector* out, const Spherical* s);
		// 0x1084D120 / 0x1084D190: rotates v around the X / Y axis
		void RotateAroundX(float angle, math::Vector* v);
		void RotateAroundY(float angle, math::Vector* v);
	}
}

#endif
