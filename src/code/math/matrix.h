// math::Matrix: 4x4 floats, rows of 16 bytes. The class name is a guess (the engine names math::Vector, Plane,
// AABB, Sphere, OBB, Colour; no matrix name survives in the strings).
#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

namespace math
{
	class Matrix
	{
	public:
		float m[4][4];

		// Resets the upper 3x3 (rotation) to identity, leaving the translation row and the last column; name guessed
		void IdentityRotation();
	};
}

#endif
