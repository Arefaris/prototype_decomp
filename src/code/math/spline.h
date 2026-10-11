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
		SplineSegment(const SplineSegment& other);
		SplineSegment& operator=(const SplineSegment& other);
		void SetFlag(bool value);
		// out = (1, t, t^2, t^3) * coefficients, t clamped to [0, 1]
		void Evaluate(Vector& out, float t) const;
		// out = (0, 1, 2t, 3t^2) * coefficients, t clamped to [0, 1]
		void EvaluateDerivative(Vector& out, float t) const;
		// out = (0, 0, 2, 6t) * coefficients, t clamped to [0, 1]
		void EvaluateSecondDerivative(Vector& out, float t) const;
		// |EvaluateDerivative(t)| and the 5-point Gauss-Legendre arc length over [0, t] are static helpers of
		// spline.cpp (0x107D5F30 / 0x107D5F60, register calling convention); they enter the tree with their callers
		// coefficients = basis matrix of `mode` (SPLINE_BASIS, 15 of them) times the geometry matrix: the four keys
		// as rows (modes 0-2, 5-7, 10-12), the Catmull-Rom rows (3, 8, 13) or the Hermite rows (4, 9, 14)
		void Build(int mode, const Vector4* k0, const Vector4* k1, const Vector4* k2, const Vector4* k3,
			const Vector4* t0, const Vector4* t1);
		// The same with the keys as the rows of a matrix
		void Build(int mode, const Matrix& keys, const Vector4* t0, const Vector4* t1);
		// The same from Vector keys (w = 1)
		void Build(int mode, const Vector* k0, const Vector* k1, const Vector* k2, const Vector* k3,
			const Vector4* t0, const Vector4* t1);
		// Geometry rows k1, tangent at k1, k2, tangent at k2 from the chord slopes, scaled by the k1-k2 interval
		// when the flag says the keys' w are times (0x107D5040, not reconstructed yet)
		void BuildCatmullRom(const Vector4* k0, const Vector4* k1, const Vector4* k2, const Vector4* k3,
			Matrix& geometry) const;
		// The same with explicit tangents t0 / t1 (0x107D5240, not reconstructed yet)
		void BuildHermite(const Vector4* k0, const Vector4* k1, const Vector4* k2, const Vector4* k3,
			const Vector4* t0, const Vector4* t1, Matrix& geometry) const;
		// Forward differencing: adds row 1 to row 0, 2 to 1, 3 to 2 of `derivative` (x, y, z) and returns row 0 in
		// out
		Vector& Step(Vector& out);
		// Sets `derivative` up for `steps` forward-differencing steps per segment (the difference matrix of h = 1 /
		// steps times coefficients) and returns the start point in out
		void BeginStepping(Vector& out, int steps);
	};

	class Spline
	{
	public:
		// Index of the key segment cached in `segment`, -1 when it has to be rebuilt
		int current;
		SplineSegment segment;
		bool closed;
		bool flag;
		// Spline type: selects the basis matrix of SplineSegment::Build (0-14; 3, 8, 13 Catmull-Rom, 4, 9, 14 Hermite)
		int mode;
		unsigned int count;
		Vector4* keys;
		Vector4* tangents;
		// Arc length per segment, -1 when not computed yet; null when lengths are not tracked
		float* lengths;
		// Forward-differencing iteration: the current step and the steps per segment
		int step;
		int stepsPerSegment;

		// Allocates keyCount keys (and tangents for the Hermite modes 4, 9, 14); nothing else is initialised
		Spline(unsigned int keyCount, int splineMode, bool isClosed);
		Spline(const Spline& other);
		Spline& operator=(const Spline& other);
		~Spline();
		// Changes the mode: drops the lengths, allocates the tangents for a Hermite mode (4, 9, 14) or frees them
		void SetMode(int newMode);
		// Opens or closes the spline, resizing the cached lengths (the kept ones copied, the new ones -1)
		void SetClosed(bool value);
		// Reallocates keys (and tangents) for a new key count; the old keys, tangents and lengths are dropped
		void SetKeyCount(unsigned int keyCount);
		// Starts a forward-differencing walk with `steps` steps per segment at key `index`; returns out = the point
		Vector& StartStepping(Vector& out, int steps, unsigned int index);
		// The next point of the walk (wraps on a closed spline); rebuilds the segment and catches up when it changes
		Vector& NextStep(Vector& out);
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
		// Arc length of one segment / of the whole spline / from the start to t, cached in `lengths` (allocated on
		// first use, segment count + 1 entries, the last one the total); the arc length itself is a 5-point
		// Gauss-Legendre sum over the derivative
		float GetSegmentLength(unsigned int index);
		float GetTotalLength();
		float GetLength(float t);
		// The parameter t at arc length `length` from the start: the segment from the cached lengths, then up to 32
		// Newton steps on GetLength (tolerance 1e-5)
		float GetParameter(float length);
	};
}

#endif
