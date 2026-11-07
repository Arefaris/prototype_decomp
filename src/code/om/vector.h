// om::Vector (RTTI: om::Vector): the vector of the engine's property types, three numbers.
#ifndef OM_VECTOR_H
#define OM_VECTOR_H

namespace om
{
	class Vector
	{
	public:
		Vector()
		{
			values[2] = 0.0f;
			values[1] = 0.0f;
			values[0] = 0.0f;
		}
		Vector(float x, float y, float z)
		{
			values[0] = x;
			values[1] = y;
			values[2] = z;
		}

		float values[3];
	};
}

#endif
