# math module: work list

State of every function of `code/math` looked at so far (2026-10-10). Matched functions are in `src/code/math`;
this list is for the rest. Percentages are objcmp's byte identity of the best attempt (relocations as wildcards).

## quaternion.cpp (0x107CD360 - 0x107CE3C0)

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107CD410 | SinPolynomial | 98.2 % | sign of the leading coefficient folded differently (NONMATCHING in tree); it is an inline helper, inlined twice in Slerp |
| 0x107CD7A0 | FromEuler (variant A) | 90.7 % | product orders; permute with PERMUTE_MUL |
| 0x107CD8D0 | FromEuler (variant B) | 77.2 % | as above |
| 0x107CDA00 | ToMatrix | 9.5 % | structure: 2x products hoisted (`z2 = z * 2`), check the original's order |
| 0x107CDCE0 | FromVectors (rotation from a to b) | 34.5 % | the original reuses the cross-product local for the fallback axis; block layout after Normalize differs |
| 0x107CDF90 | Slerp | - | AtanRatio called out of line, SinPolynomial inlined twice; not attempted |
| 0x107CE220 | MakeClosest | 3.8 % | same instructions, `this`/`q` registers swapped (NONMATCHING in tree) |
| 0x107CE310 | ToAxisAngle | 20.7 % | x87/SSE mix for the axis copy |

## vector.cpp (0x107CE3D0 - 0x107CEAE0)

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107CE4D0 | Normalize(const Vector&) | 80 % | x87 operand order for y (NONMATCHING in tree) |
| 0x107CE5E0 | RotateAboutAxis | 18.5 % | Rodrigues with `this` overwritten by the axis first; aliasing reloads |
| 0x107CE850 | CrossProduct | 73.7 % | store scheduling (NONMATCHING in tree) |
| 0x107CEA20 | debug print | - | assert output function 0x1063C750 and two enable flags; not attempted |

## matrix.cpp (0x107CEAE0 - 0x107D2EC0)

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107CED00 | FromAxisCosSin | 14.5 % | normalises the axis when not unit (calls Vector::Normalize) |
| 0x107CEE50 / EF70 / F0A0 | Euler rotations | 50 / 52 / 62 % | permuter plateau; products of three factors |
| 0x107CF280 | Reflection(plane) | 28.9 % | |
| 0x107CF5D0 | Orthonormalize | 30.8 % | |
| 0x107CF720 | IsOrthonormal | 16 % | six dot products spilled, inline IsEqual x5 + one out-of-line call |
| 0x107CF8F0 / FA80 / FB10 | Transform / Rotate / RotateInverse | EQUIVALENT | y/z registers swapped |
| 0x107CFC00 | PerspectiveFovLH | - | calls Identity first; not attempted |
| 0x107CFC80 / FD20 | Ortho / OrthoRH | 98.7 / 92.3 % | constant register only |
| 0x107CFE90 | OrthoOffCenterRH | 66.4 % | |
| 0x107CFF70 / 0x107D03A0 | LookAt LH / RH | 52.8 % | |
| 0x107D0190 / 0x107D05C0 | orientation from direction and up | 67.8 % | |
| 0x107D0E20 / 0F60 / 10A0 / 1150 / 1320 | 3x3 ops through a Matrix3 temporary | - | scale, add, subtract, multiply x2; Matrix3::CopyTo is matched |
| 0x107D16B0 | IsIdentity(tolerance) | 29.1 % | |
| 0x107D1910 | debug print | - | as vector.cpp's |
| 0x107D1AA0 | rotation taking a onto b | - | function-local statics with VS2005 guard bits |
| 0x107D1C90 / 1D20 / 1DB0 | rotation about Y / X / Z from a direction | 37.5 % | |
| 0x107D1E40 | basis from a Z axis | - | |
| 0x107D20B0 | Inverse (general 4x4) | - | 1 536 bytes |
| 0x107D26B0 | Invert (orthonormal fast path) | 18.1 % | |
| 0x107D2C00 / 2CC0 | Multiply(a, b) / MultiplyTranspose | 5.6 % | descending loops; the original keeps `a`'s row in registers |
| 0x107D2D80 | ToAxisAngle | 26.6 % | clamp of the acos argument written as subtractions |

## triangle.cpp (0x107D2ED0 - 0x107D3B50)

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107D2ED0 | ray intersection | - | 750 bytes |
| 0x107D31C0 | contains (3D, barycentric signs) | - | |
| 0x107D3360 | ContainsXZ | 36 % | permuter running |
| 0x107D3420 | closest point with region code | - | 1 654 bytes |
| 0x107D3AA0 | Area | 36.9 % | |
| 0x107D3B50 | angle (three normalisations, acos) | - | |

## matrix3.cpp (0x107D3CF0 - 0x107D4150)

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107D3DD0 / 3E60 | Transform / transposed | 18.2 % | |
| 0x107D3EF0 / 4150 | Multiply (two copies) | 6.1 % | all 18 loads first, then the nine sums |

## obb.cpp (0x107D43B0 - 0x107D49E0)

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107D4450 | GetAABB | 13.5 % | products in SSE through Vector temporaries, fabs in x87 |
| 0x107D4560 | GetCornerOffset(out, bits) | 45.6 % | permuter plateau (300 compilations); structure differs |
| 0x107D4630 | Contains | 96.6 % | dot product term order |
| 0x107D46D0 | closest point / depth | - | |
| 0x107D48E0 | GetSphere | 12.6 % | |
| 0x107D49B0 | GetCorner | 100 % | waits for GetCornerOffset (same unit, register knowledge) |

## plane.cpp (0x107D8740 - 0x107D8E10)

Polar / spherical conversions, Factorial, Sinc, Log2 (mathutils.cpp) and Plane::IsBoxPartlyBehind, IsBoxBehind,
IntersectSegment, Transform match. Left:

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107D89E0 | Plane::Set(a, b, c) | 93.1 % | EQUIVALENT in tree (Sub, Cross, Dot inline helpers); two commutative products come out with the operands swapped (e1.z * e2.y in the cross, a.z * normal.z in the dot); the compiler canonicalises them regardless of source order. 99 % in a spike where NormalizeFast was called through a cast wrapper |
| 0x107D8C80 | Plane::IntersectRay(origin, direction, hit) | 51 % | same instructions; SSE registers of normal.y / direction.x / normal.z rotated (original xmm2 / xmm3 / xmm4, ours xmm4 / xmm2 / xmm3); permuter plateau with Dot / Distance helpers, nested ifs, operand and term orders |

## Further units of the region

0x107D49F0 - 0x107D5F60: a keyed spline (two matrices and a time flag per segment, Hermite / Catmull-Rom tangents,
forward differencing). 0x107D5FE0 onwards: not surveyed.

## segment.cpp (0x107D6F40–0x107D7650), not in the tree

Segment is `{Vector start; Vector end;}`. The compiler keeps `d = end - start` and `v = p - start` as memory Vectors
and reads them back in x87 with term orders that change from function to function (x,z,y dot products; (z²+y²)+x²
lengths), so plain float locals, Vector locals with inline Dot/Length and operator- forms all plateau.

| Address | Function | Best | Note |
| --- | --- | --- | --- |
| 0x107D6F40 | component-wise min/max of two vectors into (min, max) | — | not drafted (do-while from 3, `if (b <= a)`) |
| 0x107D7020 | closest point + distance² | — | not drafted |
| 0x107D72D0 | Parameter(p) = dot(p-s, d) / dot(d, d) | 23.5 % | SSE prologue matches, x87 part does not |
| 0x107D7380 | GetSphere(centre = (s+e)/2, radius = |s-e|) | 21.4 % | d must be an SSE-stored Vector, Length in x87 |
| 0x107D7420 | DistanceSquared(p) (clamped projection) | 4.3 % | three different sum orders in one function |
| 0x107D7570 | DistanceSquaredToLine(p) | 17.0 % | |

## random.cpp (0x107D8380–0x107D8740), partly in the tree

Seed x2 match (Step by reference). The vector functions keep the three raw 32-bit values live and convert them late.

| Address | Function | Best | Note |
| --- | --- | --- | --- |
| 0x107D8460 | NextVector01(Vector&) -> Vector& | 21.4 % | `out.Set(NextFloat01() x3)`; original interleaves the three Next() before the bit tricks |
| 0x107D8560 | NextVector11(Vector&) -> Vector& | 5 % | same shape with 0x40000000 / -3.0f |
| 0x107D8660 | NextUnitVector(Vector&) | 26.3 % | rejection loop on NextVector11 (0.001 < len² <= 1), x87 1/sqrt |

## symmetricmatrix.cpp (0x107D9100–0x107D9A00), partly in the tree

| Address | Function | Best | Note |
| --- | --- | --- | --- |
| 0x107D96C0 | Transform(const Vector&, Vector&) | 10.4 % | plain sums plateau; original loads xy, v.z, v.y, v.x, xz, yz first |
| 0x107D9290 | Transform(const Matrix&) (R S R^T) | — | not drafted |
| 0x107D9510 | adjugate-like | — | not drafted |
| 0x107D9820 | Invert (scales by 1/xx first, 0x107D90A0) | — | not drafted |
| 0x107D97B0 | Print (assert channel " Math  Pre ", static enable flag 0x111BBDE8) | — | needs the log function 0x1063C750 |
