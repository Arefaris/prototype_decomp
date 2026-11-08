// om::Vector (RTTI: om::Vector, the vector of three numbers the dynamic properties and the graph's ports carry): the
// value of the engine's property of a position or a direction, with its text and binary forms.
#ifndef OM_VECTOR_H
#define OM_VECTOR_H

namespace om
{
	class TextValue;
	class BinaryStream;

	// Builds a vector with the three numbers set one after the other (the dynamic property of a vector does)
	struct VectorInOrder
	{
	};

	class Vector
	{
	public:
		explicit Vector(const VectorInOrder&)
		{
			values[0] = 0.0f;
			values[1] = 0.0f;
			values[2] = 0.0f;
		}
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

	// The text form: the children "x", "y" and "z" (the engine's functions, not templates)
	bool ReadText(const TextValue* text, Vector* vector);
	void WriteText(TextValue* text, const Vector& vector);
	bool ReadBinary(BinaryStream* stream, Vector* vector);
	bool WriteBinary(BinaryStream* stream, const Vector& vector);
}

#endif
