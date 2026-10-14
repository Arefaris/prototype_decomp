// Blending of animation channels into poses (unit around 0x10952120 - 0x10955600, with the four-wide spherical
// interpolation of rotations; file name guessed). Names are guesses.
#include "code/choreo/samplechannels.h"
#include "code/choreo/simdconstants.h"

namespace choreo
{
	// The lane n of a vector in all four lanes
	#define SPLAT(v, n) _mm_shuffle_ps(v, v, _MM_SHUFFLE(n, n, n, n))

	// The sum of the four lanes in every lane, added as (w + z) + (y + x)
	static __forceinline __m128 SumLanes(__m128 v)
	{
		return _mm_add_ps(_mm_add_ps(SPLAT(v, 3), SPLAT(v, 2)), _mm_add_ps(SPLAT(v, 1), SPLAT(v, 0)));
	}

	// mask ? a : b
	static __forceinline __m128 Select(__m128 mask, __m128 a, __m128 b)
	{
		return _mm_or_ps(_mm_and_ps(a, mask), _mm_andnot_ps(mask, b));
	}

	// The angle in [0, pi / 2] whose cosine is absCosine and whose sine is sine (both positive): atan(sine / cosine)
	// by the polynomial in x^2, or pi / 2 - atan(cosine / sine) when the sine is the larger
	static __forceinline __m128 ArcTangentAngle(__m128 sine, __m128 absCosine)
	{
		__m128 one = gOne;
		__m128 sineLess = _mm_cmplt_ps(sine, absCosine);
		__m128 ratio = _mm_xor_ps(_mm_mul_ps(_mm_div_ps(one, sine), absCosine), gSignMask);
		__m128 ratio2 = _mm_mul_ps(_mm_div_ps(one, absCosine), sine);
		__m128 x = _mm_or_ps(_mm_andnot_ps(sineLess, ratio), _mm_and_ps(ratio2, sineLess));
		__m128 zero = _mm_setzero_ps();
		__m128 x2 = _mm_mul_ps(x, x);
		__m128 atan0 = gAtanCoefficients1;
		__m128 poly = _mm_mul_ps(SPLAT(atan0, 3), x2);
		poly = _mm_add_ps(poly, SPLAT(atan0, 2));
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_add_ps(poly, SPLAT(atan0, 1));
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_add_ps(poly, SPLAT(atan0, 0));
		__m128 atan1 = gAtanCoefficients0;
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_add_ps(poly, SPLAT(atan1, 3));
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_add_ps(poly, SPLAT(atan1, 2));
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_add_ps(poly, SPLAT(atan1, 1));
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_add_ps(poly, SPLAT(atan1, 0));
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_add_ps(poly, one);
		poly = _mm_mul_ps(poly, x);
		return _mm_add_ps(poly, _mm_or_ps(_mm_and_ps(zero, sineLess), _mm_andnot_ps(sineLess, gHalfPi)));
	}

	// angle moved into [-pi, pi] (pi added, reduced by whole turns, pi taken off again); the two steps are split
	// because the engine interleaves the second step of one angle with the first of the other
	static __forceinline __m128 ReduceAngle(__m128 angleWithPi)
	{
		return _mm_sub_ps(angleWithPi, _mm_mul_ps(_mm_cvtepi32_ps(_mm_cvttps_epi32(_mm_mul_ps(angleWithPi, gInvTwoPi))), gTwoPi));
	}

	// The sine of an angle in [-pi, pi] by the polynomial x + x * x^2 * Q(x^2), not yet limited
	static __forceinline __m128 SinePolynomial(__m128 x)
	{
		__m128 sin0 = gSinCoefficients1;
		__m128 sin1 = gSinCoefficients0;
		__m128 x2 = _mm_mul_ps(x, x);
		__m128 poly = _mm_mul_ps(SPLAT(sin0, 3), x2);
		poly = _mm_add_ps(poly, SPLAT(sin0, 2));
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_add_ps(poly, SPLAT(sin0, 1));
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_add_ps(poly, SPLAT(sin0, 0));
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_add_ps(poly, SPLAT(sin1, 3));
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_add_ps(poly, SPLAT(sin1, 2));
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_add_ps(poly, SPLAT(sin1, 1));
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_add_ps(poly, SPLAT(sin1, 0));
		poly = _mm_mul_ps(poly, x2);
		poly = _mm_mul_ps(poly, x);
		return _mm_add_ps(poly, x);
	}

	// The limited sine of an angle times invSine (the weight of one rotation in the interpolation)
	static __forceinline __m128 SineWeight(__m128 angle, __m128 invSine)
	{
		__m128 negOne = _mm_xor_ps(gSignMask, gOne);
		__m128 sine = SinePolynomial(angle);
		sine = _mm_max_ps(sine, negOne);
		sine = _mm_min_ps(sine, gOne);
		return _mm_mul_ps(sine, invSine);
	}

	// Spherical interpolation of the rotation at a towards the one at b by the amounts in t (all lanes equal), the
	// short way and normalised; the rotation is kept as the four lanes x, y, z, w
	static __forceinline void SlerpRotationBody(__m128 t, __m128* a, const __m128* b)
	{
		__m128 one = gOne;
		__m128 qb = *b;
		__m128 qa = *a;
		__m128 cosine = SumLanes(_mm_mul_ps(qb, qa));
		__m128 absCosine = _mm_and_ps(gAbsMask, cosine);
		__m128 sine2 = _mm_sub_ps(one, _mm_min_ps(_mm_mul_ps(cosine, cosine), one));
		__m128 invSine = _mm_div_ps(one, _mm_sqrt_ps(sine2));
		__m128 sine = _mm_div_ps(one, invSine);
		__m128 angle = ArcTangentAngle(sine, absCosine);
		// The angles of the two weights, kept in [-pi, pi]
		__m128 weightA = _mm_sub_ps(one, t);
		__m128 angleA = _mm_mul_ps(weightA, angle);
		__m128 angleB = _mm_mul_ps(angle, t);
		__m128 pi = gPi;
		angleA = _mm_add_ps(angleA, pi);
		angleA = ReduceAngle(angleA);
		angleB = _mm_add_ps(angleB, pi);
		angleB = ReduceAngle(angleB);
		angleB = _mm_sub_ps(angleB, pi);
		angleA = _mm_sub_ps(angleA, pi);
		__m128 parallel = _mm_cmple_ps(sine2, gParallelTolerance);
		__m128 zero = _mm_setzero_ps();
		__m128 weightB = SineWeight(angleB, invSine);
		__m128 negative = _mm_cmple_ps(cosine, zero);
		weightA = Select(parallel, weightA, SineWeight(angleA, invSine));
		__m128 wb = Select(parallel, t, weightB);
		__m128 signedWb = Select(negative, _mm_xor_ps(wb, gSignMask), wb);
		__m128 result = _mm_add_ps(_mm_mul_ps(weightA, qa), _mm_mul_ps(signedWb, qb));
		*a = _mm_mul_ps(_mm_div_ps(one, _mm_sqrt_ps(SumLanes(_mm_mul_ps(result, result)))), result);
	}

	// FUNCTION: ENGINE 0x10953A90
	// EQUIVALENT: the same vector operations in the same order and with the same constants; the engine's register
	// allocation and scheduling differ (900 bytes against 940). The inline function of the original that the
	// blending calls where its body is too large to inline
	inline void SlerpRotation(__m128 t, __m128* a, const __m128* b)
	{
		SlerpRotationBody(t, a, b);
	}

	// Rows of four rotations turned into the x, y, z and w of the four (the unpacks are the engine's: a macro, since a
	// function cannot take four vectors)
	#define TRANSPOSE(row0, row1, row2, row3, x, y, z, w) 		{ 			__m128 low02 = _mm_unpacklo_ps(row0, row2); 			__m128 low13 = _mm_unpacklo_ps(row1, row3); 			__m128 high02 = _mm_unpackhi_ps(row0, row2); 			__m128 high13 = _mm_unpackhi_ps(row1, row3); 			x = _mm_unpacklo_ps(low02, low13); 			y = _mm_unpackhi_ps(low02, low13); 			z = _mm_unpacklo_ps(high02, high13); 			w = _mm_unpackhi_ps(high02, high13); 		}

	class RotationBuffer
	{
	public:
		// 0x10953160
		void BlendInto(__m128 t, __m128* destination, const __m128* end);

		__m128 mRotations[96];
	};

	// FUNCTION: ENGINE 0x10953160
	// EQUIVALENT: the same vector operations in the same order; scheduling and register allocation differ. The
	// rotations of this buffer are laid over the ones at destination, up to the buffer's end
	void RotationBuffer::BlendInto(__m128 t, __m128* destination, const __m128* end)
	{
		__m128 one = gOne;
		__m128 weightA = _mm_sub_ps(one, t);
		const __m128* source = mRotations;
		// Four rotations at a time: the lanes are the four rotations
		for (; source + 4 <= end; source += 4, destination += 4)
		{
			__m128 dx, dy, dz, dw;
			TRANSPOSE(destination[0], destination[1], destination[2], destination[3], dx, dy, dz, dw);
			__m128 sx, sy, sz, sw;
			TRANSPOSE(source[0], source[1], source[2], source[3], sx, sy, sz, sw);
			__m128 cosine = _mm_add_ps(_mm_add_ps(_mm_mul_ps(sx, dx), _mm_mul_ps(sy, dy)),
				_mm_add_ps(_mm_mul_ps(sz, dz), _mm_mul_ps(sw, dw)));
			__m128 sine2 = _mm_sub_ps(one, _mm_mul_ps(cosine, cosine));
			__m128 invSine = _mm_div_ps(one, _mm_sqrt_ps(sine2));
			__m128 sine = _mm_div_ps(one, invSine);
			__m128 angle = ArcTangentAngle(sine, _mm_and_ps(cosine, gAbsMask));
			__m128 angleA = _mm_mul_ps(weightA, angle);
			__m128 angleB = _mm_mul_ps(angle, t);
			__m128 pi = gPi;
			angleA = _mm_add_ps(angleA, pi);
			angleB = _mm_add_ps(angleB, pi);
			__m128 parallel = _mm_cmple_ps(sine2, gParallelTolerance);
			angleA = _mm_sub_ps(ReduceAngle(angleA), pi);
			angleB = _mm_sub_ps(ReduceAngle(angleB), pi);
			__m128 wa = Select(parallel, weightA, SineWeight(angleA, invSine));
			__m128 negative = _mm_cmple_ps(cosine, _mm_setzero_ps());
			__m128 wb = Select(parallel, t, SineWeight(angleB, invSine));
			wb = Select(negative, _mm_xor_ps(wb, gSignMask), wb);
			__m128 rx = _mm_add_ps(_mm_mul_ps(wb, sx), _mm_mul_ps(wa, dx));
			__m128 ry = _mm_add_ps(_mm_mul_ps(wb, sy), _mm_mul_ps(wa, dy));
			__m128 rz = _mm_add_ps(_mm_mul_ps(wb, sz), _mm_mul_ps(wa, dz));
			__m128 rw = _mm_add_ps(_mm_mul_ps(wb, sw), _mm_mul_ps(wa, dw));
			__m128 length2 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(rw, rw), _mm_mul_ps(rz, rz)),
				_mm_add_ps(_mm_mul_ps(ry, ry), _mm_mul_ps(rx, rx)));
			__m128 inverse = _mm_div_ps(one, _mm_sqrt_ps(length2));
			__m128 ox = _mm_mul_ps(inverse, rx);
			__m128 oy = _mm_mul_ps(inverse, ry);
			__m128 oz = _mm_mul_ps(inverse, rz);
			__m128 ow = _mm_mul_ps(inverse, rw);
			TRANSPOSE(ox, oy, oz, ow, destination[0], destination[1], destination[2], destination[3]);
		}
		// The rest one at a time
		for (; source < end; source++, destination++)
		{
			SlerpRotationBody(t, destination, source);
		}
	}

	// pose += (value - pose) * weight, per component
	static __forceinline void BlendVector(math::Vector4* pose, const math::Vector& value, float weight)
	{
		pose->x = (value.x - pose->x) * weight + pose->x;
		pose->y = (value.y - pose->y) * weight + pose->y;
		pose->z = (value.z - pose->z) * weight + pose->z;
	}

	// FUNCTION: ENGINE 0x10953E40
	// EQUIVALENT: the same sampling and blending in the same order (the same size as the engine's); stack slots and
	// registers of the loop variables differ
	void SampleChannels::Blend(pure3d::JointArrays* arrays, unsigned int first, unsigned int last,
		const pure3d::JointMask* mask, const pure3d::SkeletonData* rest, pure3d::FrameTime time, bool full,
		float weight)
	{
		unsigned int offset = first * 16;
		math::Quaternion* rotations = arrays->mRotations + first;
		math::Vector4* translations = arrays->mTranslations + first;
		__m128 t = _mm_set1_ps(weight);
		RotationBuffer buffer;
		math::Quaternion* written = (math::Quaternion*)buffer.mRotations;
		if (!full)
		{
			if (!mask)
			{
				// Without a mask the rotations are sampled into the buffer and then blended four at a time
				for (unsigned int joint = first; joint <= last; joint++)
				{
					if (mRotations[joint])
					{
						GetRotation(joint)->mKeys.Evaluate(time, written);
					}
					else
					{
						*written = rest->mRotations[joint];
					}
					if (mTranslations[joint])
					{
						math::Vector value;
						GetTranslation(joint)->mKeys.Evaluate(time, &value);
						BlendVector(translations, value, weight);
					}
					else
					{
						BlendVector(translations, rest->mTranslations[joint], weight);
					}
					written++;
					translations++;
				}
				buffer.BlendInto(t, (__m128*)rotations, (const __m128*)written);
			}
			else
			{
				__m128* rotation = (__m128*)rotations;
				for (unsigned int joint = first; joint <= last; joint++)
				{
					if (mask->words[joint >> 5] & (1 << (joint & 0x1F)))
					{
						const __m128* sampled;
						math::Quaternion value;
						if (mRotations[joint])
						{
							GetRotation(joint)->mKeys.Evaluate(time, &value);
							sampled = (const __m128*)&value;
						}
						else
						{
							sampled = (const __m128*)&rest->mRotations[joint];
						}
						SlerpRotation(t, rotation, sampled);
						if (mTranslations[joint])
						{
							math::Vector translation;
							GetTranslation(joint)->mKeys.Evaluate(time, &translation);
							BlendVector(translations, translation, weight);
						}
						else
						{
							BlendVector(translations, rest->mTranslations[joint], weight);
						}
					}
					rotation++;
					translations++;
				}
			}
		}
		else
		{
			math::Vector4* unknown10 = arrays->mUnknown10 + first;
			math::Vector4* unknown14 = arrays->mUnknown14 + first;
			math::Vector4* scales = arrays->mScales + first;
			math::Vector4* unknown1C = arrays->mUnknown1C + first;
			if (!mask)
			{
				for (unsigned int joint = first; joint <= last; joint++)
				{
					if (mRotations[joint])
					{
						GetRotation(joint)->mKeys.Evaluate(time, written);
					}
					else
					{
						*written = rest->mRotations[joint];
					}
					if (mTranslations[joint])
					{
						math::Vector translation;
						GetTranslation(joint)->mKeys.Evaluate(time, &translation);
						BlendVector(translations, translation, weight);
					}
					else
					{
						BlendVector(translations, rest->mTranslations[joint], weight);
					}
					if (mUnknown10[joint])
					{
						math::Vector vector10;
						GetUnknown10(joint)->mKeys.Evaluate(time, &vector10);
						BlendVector(unknown10, vector10, weight);
					}
					else
					{
						BlendVector(unknown10, rest->mUnknown10[joint], weight);
					}
					if (mScales[joint])
					{
						math::Vector scale;
						GetScale(joint)->mKeys.Evaluate(time, &scale);
						BlendVector(scales, scale, weight);
					}
					else
					{
						BlendVector(scales, rest->mScales[joint], weight);
					}
					if (mUnknown14[joint])
					{
						math::Vector vector14;
						GetUnknown14(joint)->mKeys.Evaluate(time, &vector14);
						BlendVector(unknown14, vector14, weight);
					}
					else
					{
						BlendVector(unknown14, rest->mUnknown18[joint], weight);
					}
					if (mUnknown1C[joint])
					{
						math::Vector vector1C;
						GetUnknown1C(joint)->mKeys.Evaluate(time, &vector1C);
						BlendVector(unknown1C, vector1C, weight);
					}
					else
					{
						BlendVector(unknown1C, rest->mUnknown1C[joint], weight);
					}
					written++;
					translations++;
					unknown10++;
					scales++;
					unknown14++;
					unknown1C++;
				}
				buffer.BlendInto(t, (__m128*)rotations, (const __m128*)written);
			}
			else
			{
				__m128* rotation = (__m128*)rotations;
				for (unsigned int joint = first; joint <= last; joint++)
				{
					if (mask->words[joint >> 5] & (1 << (joint & 0x1F)))
					{
						const __m128* sampled;
						math::Quaternion value;
						if (mRotations[joint])
						{
							GetRotation(joint)->mKeys.Evaluate(time, &value);
							sampled = (const __m128*)&value;
						}
						else
						{
							sampled = (const __m128*)&rest->mRotations[joint];
						}
						SlerpRotation(t, rotation, sampled);
						if (mTranslations[joint])
						{
							math::Vector translation;
							GetTranslation(joint)->mKeys.Evaluate(time, &translation);
							BlendVector(translations, translation, weight);
						}
						else
						{
							BlendVector(translations, rest->mTranslations[joint], weight);
						}
						if (mUnknown10[joint])
						{
							math::Vector vector10;
							GetUnknown10(joint)->mKeys.Evaluate(time, &vector10);
							BlendVector(unknown10, vector10, weight);
						}
						else
						{
							BlendVector(unknown10, rest->mUnknown10[joint], weight);
						}
						if (mScales[joint])
						{
							math::Vector scale;
							GetScale(joint)->mKeys.Evaluate(time, &scale);
							BlendVector(scales, scale, weight);
						}
						else
						{
							BlendVector(scales, rest->mScales[joint], weight);
						}
						if (mUnknown14[joint])
						{
							math::Vector vector14;
							GetUnknown14(joint)->mKeys.Evaluate(time, &vector14);
							BlendVector(unknown14, vector14, weight);
						}
						else
						{
							BlendVector(unknown14, rest->mUnknown18[joint], weight);
						}
						if (mUnknown1C[joint])
						{
							math::Vector vector1C;
							GetUnknown1C(joint)->mKeys.Evaluate(time, &vector1C);
							BlendVector(unknown1C, vector1C, weight);
						}
						else
						{
							BlendVector(unknown1C, rest->mUnknown1C[joint], weight);
						}
					}
					rotation++;
					translations++;
					unknown10++;
					scales++;
					unknown14++;
					unknown1C++;
				}
			}
		}
	}
}
