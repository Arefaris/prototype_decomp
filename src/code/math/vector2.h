// math::Vector2 (RTTI type argument class math::Vector2): two floats, copy-constructed component by component like
// Vector. Only what the render units need so far.
#ifndef MATH_VECTOR2_H
#define MATH_VECTOR2_H

namespace math
{
	class Vector2
	{
	public:
		Vector2()
		{
		}
		Vector2(const Vector2& v)
		{
			x = v.x;
			y = v.y;
		}

		float x;
		float y;
	};
}

#endif
