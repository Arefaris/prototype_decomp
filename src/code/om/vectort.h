// om::VectorT<T, N> (RTTI: om::VectorT<float,2>, the element of the envelope's points): a vector of N numbers.
#ifndef OM_VECTORT_H
#define OM_VECTORT_H

namespace om
{
	template<class T, int N> class VectorT
	{
	public:
		VectorT()
		{
		}

		T values[N];
	};

	class TextValue;
	class BinaryStream;

	// The text form of the vector of two numbers: a node "0" and a node "1" (the engine's functions, not templates)
	bool ReadText(const TextValue* text, VectorT<float, 2>* vector);
	void WriteText(TextValue* text, const VectorT<float, 2>& vector);
	bool ReadBinary(BinaryStream* stream, VectorT<float, 2>* vector);
	bool WriteBinary(BinaryStream* stream, const VectorT<float, 2>& vector);
}

#endif
