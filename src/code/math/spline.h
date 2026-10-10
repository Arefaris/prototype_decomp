// A keyed cubic spline of math (0x107D49F0 - 0x107D6F10): Vector4 keys (and optional tangents) with a cached
// segment of Hermite coefficient matrices and per-segment arc lengths. The RTTI has no name for it (engine::SplineCV
// and SplinePath are other classes), so the class, member and method names are guesses from the code.
#ifndef MATH_SPLINE_H
#define MATH_SPLINE_H

#include "code/math/matrix.h"
#include "code/math/vector.h"
#include "code/math/vector4.h"

namespace math
{
	// One cubic segment: the position and derivative coefficient matrices (rows weight 1, t, t^2, t^3) and a flag
	class SplineSegment
	{
	public:
		Matrix coefficients;
		Matrix derivative;
		bool flag;

		SplineSegment();
		SplineSegment& operator=(const SplineSegment& other);
		void SetFlag(bool value);
		// out = (1, t, t^2, t^3) * coefficients, t clamped to [0, 1]
		void Evaluate(Vector& out, float t) const;
		// out = (0, 1, 2t, 3t^2) * coefficients, t clamped to [0, 1]
		void EvaluateDerivative(Vector& out, float t) const;
		// |EvaluateDerivative(t)| (0x107D5F30, compiled by the engine with a register calling convention; not
		// reconstructed)
		float DerivativeLength(float t) const;
		// Builds the coefficient matrices from four consecutive keys and, when present, the two inner tangents
		// (0x107D6300, not reconstructed yet; the mode is Spline's int at 0x8c)
		void Build(int mode, const Vector4* k0, const Vector4* k1, const Vector4* k2, const Vector4* k3,
			const Vector4* t0, const Vector4* t1);
	};

	class Spline
	{
	public:
		// Index of the key segment cached in `segment`, -1 when it has to be rebuilt
		int current;
		SplineSegment segment;
		bool closed;
		bool flag;
		int unknown8c;
		int count;
		Vector4* keys;
		Vector4* tangents;
		// Arc length per segment, -1 when not computed yet; null when lengths are not tracked
		float* lengths;

		~Spline();
		// Sets the flag of the spline and of its cached segment
		void SetFlag(bool value);
		// Number of segments: the key count, minus 3 for an open spline (0 below 4 keys), as float / unsigned
		float GetSegmentCountF() const;
		unsigned int GetSegmentCount() const;
		Vector4* GetKey(int index);
		// Marks the lengths of the segments that use key `index` (index - 3 .. index - 1) and the last one as unknown
		void InvalidateLengths(unsigned int index);
		// Store a key / tangent and drop the cached segment and the affected lengths
		void SetKey(int index, const Vector4& key);
		// The same from a Vector, with w = 1
		void SetKey(int index, const Vector& key);
		void SetTangent(int index, const Vector4& tangent);
		// Rebuilds `segment` for the segment containing t (keys index .. index + 3 modulo count, index clamped to
		// count - 4); false when that segment is the cached one already
		bool SelectSegment(float t);
		// Position at t in [0, GetSegmentCountF()] (integer part: segment, fraction: parameter); returns out
		Vector& Evaluate(Vector& out, float t);
		// Position at key `key`
		Vector& Evaluate(Vector& out, unsigned int key);
	};
}

#endif
