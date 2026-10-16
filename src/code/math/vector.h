// math::Vector: three floats, no virtuals (not in the RTTI); the name is the engine's own ("math::Vector" is
// registered as a reflected type). Member and method names are guesses until the binary confirms them.
#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

namespace math
{
	class Matrix;

	class Vector
	{
	public:
		float x;
		float y;
		float z;

		Vector()
		{
		}
		Vector(float newX, float newY, float newZ)
		{
			x = newX;
			y = newY;
			z = newZ;
		}
		// User-defined: the engine copy-constructs vectors component by component (fld / fstp), struct assignment
		// stays a plain copy
		Vector(const Vector& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}
		// User-defined: a user-defined assignment is what makes MSVC copy the components through the x87 stack
		// (fld / fstp) instead of with integer moves
		Vector& operator=(const Vector& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}

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
		// Component-wise helpers the engine inlines (seen in Plane::Set and Plane::Transform; names guessed)
		void Add(const Vector& a, const Vector& b)
		{
			x = a.x + b.x;
			y = a.y + b.y;
			z = a.z + b.z;
		}
		void Sub(const Vector& a, const Vector& b)
		{
			x = a.x - b.x;
			y = a.y - b.y;
			z = a.z - b.z;
		}
		// this = a x b, without the zero check of CrossProduct
		void Cross(const Vector& a, const Vector& b)
		{
			x = a.y * b.z - a.z * b.y;
			y = a.z * b.x - a.x * b.z;
			z = a.x * b.y - a.y * b.x;
		}
		// this *= s; an inline whose parameter takes the reciprocal (Scale(1.0f / length)) keeps the original's
		// register use where a local inv does not (name guessed)
		void Scale(float s)
		{
			x *= s;
			y *= s;
			z *= s;
		}
		float Dot(const Vector& v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}
		Vector operator-() const
		{
			return Vector(-x, -y, -z);
		}

		// Reports the components through core::Report, as floats and as raw bits (debug output)
		void Print() const;
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
		// This vector as a point through m (Matrix::Transform) / as a direction (Matrix::Rotate), in place or from v
		void Transform(const Matrix& m);
		void Transform(const Vector& v, const Matrix& m);
		void Rotate(const Matrix& m);
		void Rotate(const Vector& v, const Matrix& m);
	};

	// |a - b|^2 (kept out of line at 0x100A2ED0 in large callers; name guessed)
	inline float DistanceSquared(const Vector& a, const Vector& b)
	{
		Vector d;
		d.Sub(a, b);
		return d.Dot(d);
	}
}

#endif
