// math::Vector: three floats, no virtuals (not in the RTTI); the name is the engine's own ("math::Vector" is
// registered as a reflected type). Member and method names are guesses until the binary confirms them.
#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

namespace math
{
	class Vector
	{
	public:
		float x;
		float y;
		float z;

		// Scales to unit length and returns the old length; a vector shorter than EPSILON_FLOAT becomes zero
		float Normalize();
		// Scales to unit length without a check for zero length
		void NormalizeFast();
		// Sets this vector to v scaled to unit length, without a check for zero length
		void Normalize(const Vector& v);
		void Set(float newX, float newY, float newZ)
		{
			x = newX;
			y = newY;
			z = newZ;
		}

		// Nonzero when every component is within EPSILON_SMALL of zero
		int IsZero() const;
		// Sets this vector to a vector perpendicular to v: X cross v, or Y when v lies along X
		void Perpendicular(const Vector& v);
		// Sets this vector to a cross b; when that is (nearly) zero, to a vector perpendicular to a, returning true
		bool CrossProduct(const Vector& a, const Vector& b);
		// Packs a unit vector as 2:10:10:10 (x in bits 0-9, y in 10-19, z in 20-29, bits 30-31 set)
		unsigned int PackNormal() const;
		// Unpacks a 10:10:10 signed normal (x in bits 0-9, y in 10-19, z in 20-29)
		void UnpackNormal(unsigned int packed);
	};
}

#endif
