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

OrthoLH / OrthoRH / OrthoOffCenterLH / OrthoOffCenterRH (0x107CFC80 / FD20 / FDB0 / FE90) match once all 16 elements
are assigned in memory order (m[0][0], m[0][1], ...): the store order of the source, not the order of the
computations, drives the schedule. The five 3x3 operations through a Matrix3 temporary (0x107D0E20 / 0F60 / 10A0 /
1150 / 1320: scale, add, subtract, a * b, a * b^T) match written out element by element (loops do not unroll) and
finished with `t.CopyTo(*this)`. Multiply(a, b) and its identical copy (0x107D2C00 / 2CC0, 0xBC bytes with the
alignment padding inside) match as two descending loops into a Matrix temporary, `a`'s row in four locals (loaded
1, 0, 2, 3) and the sum grouped `((a0 * b0j + a1 * b1j) + a2 * b2j) + a3 * b3j`, then `*this = t`.

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107CED00 | FromAxisCosSin | 14.5 % | normalises the axis when not unit (calls Vector::Normalize) |
| 0x107CEE50 / EF70 / F0A0 | Euler rotations | 50 / 52 / 62 % | permuter plateau; products of three factors |
| 0x107CF280 | Reflection(plane) | 28.9 % | |
| 0x107CF5D0 | Orthonormalize | 30.8 % | |
| 0x107CF720 | IsOrthonormal | 16 % | six dot products spilled, inline IsEqual x5 + one out-of-line call |
| 0x107CF8F0 / FA80 / FB10 | Transform / Rotate / RotateInverse | EQUIVALENT | y/z registers swapped |
| 0x107CF990 | Transform(const Vector4&, Vector4&) | EQUIVALENT | sums need explicit grouping `((a + b) + c) + d` to keep the original order; v.z / v.y / v.w registers rotated. FromQuaternion (0x107CEB70), Transpose3x3(src) (0x107CF4F0) and Transform(count, Vector4*) (0x107CFBD0, needs this one compiled in the unit) match |
| 0x107CFC00 | PerspectiveFovLH | - | calls Identity first; not attempted |
| 0x107CFF70 / 0x107D03A0 | LookAt LH / RH | 52.8 % | |
| 0x107D0190 / 0x107D05C0 | orientation from direction and up | 67.8 % | |
| 0x107D16B0 | IsIdentity(tolerance) | 29.1 % | |
| 0x107D1910 | debug print | - | as vector.cpp's |
| 0x107D1AA0 | rotation taking a onto b | - | function-local statics with VS2005 guard bits |
| 0x107D1C90 / 1D20 / 1DB0 | rotation about Y / X / Z from a direction | 37.5 % | |
| 0x107D1E40 | basis from a Z axis | - | |
| 0x107D20B0 | Inverse (general 4x4) | - | 1 536 bytes |
| 0x107D26B0 | Invert (orthonormal fast path) | 18.1 % | |
| 0x107D2D80 | ToAxisAngle | 26.6 % | clamp of the acos argument written as subtractions |

## triangle.cpp (0x107D2ED0 - 0x107D3B50)

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107D2ED0 | ray intersection | - | 750 bytes |
| 0x107D31C0 | contains (3D, barycentric signs) | - | |
| 0x107D3360 | Triangle::ContainsXZ(p) | 88 % | EQUIVALENT in tree: three 2D edge tests with early returns; the two factors of the first test come out in swapped registers |
| 0x107D3420 | Triangle::ClosestPoint(p, out) | 9 % | Ericson's region test; returns 1 / 2 / 4 for edges ab / bc / ca, 5 / 3 / 6 for corners, 0 inside. Original frame 0x7c with Vector locals in memory (p copy at 0, ac at 0x1c, bc at 0x28, a - p at 0x34, n at 0x40, c - p at 0x4c, b - p at 0x58, ab in registers), d1 / d3 / d4 / d2 at 0xc-0x18; the dots are written as -(ab . (a - p)) etc. Scalar and Sub/Dot/Cross-helper versions both land at 9 %: the compiler's schedule of the first block differs from the start (REA pseudocode is a faithful guide to the arithmetic) |
| 0x107D3B50 | angle (three normalisations, acos) | - | Area (0x107D3AA0) matches: z, x, y cross components as float locals, `n.Set(x, y, z)`, flat sum in the sqrt |

## matrix3.cpp (0x107D3CF0 - 0x107D4150)

Transform / TransformTransposed (0x107D3DD0 / 3E60) match as `out.Set(...)` of the three sums (all three computed
before any store); term order does not matter there.

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107D3EF0 / 4150 | Multiply (two copies) | 21.2 % | a Matrix3 temporary of the nine sums copied back member-wise comes closest (599 vs 596 bytes); the copy-back order permuted does not help |

## obb.cpp (0x107D43B0 - 0x107D49E0)

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107D4450 | GetAABB | 13.5 % | products in SSE through Vector temporaries, fabs in x87 |
| 0x107D4560 | GetCornerOffset(out, bits) | 45.6 % | permuter plateau (300 compilations); structure differs |
| 0x107D4630 | Contains | 100 % | in the tree: `const Vector& v = axis[i]` in a `for (int i = 3; i--; )` loop with the x87 dot grouped `(v.x * d.x + v.y * d.y) + v.z * d.z` |
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

## intersect.cpp (0x107D9A20 - 0x107DAB30, unit name guessed)

Free intersection tests. Matched: IntersectsOBB (0x107D9C20), Intersects(OBB, AABB) (0x107DA360), the three Capsule
tests (0x107DA4D0 / 530 / 580). EQUIVALENT in tree: IntersectsAABB (0x107D9B60, 87.3 %, one subtraction scheduled
before the push of `length`), Intersects(Plane, Capsule) (0x107DA660, 76 %, normal.x / normal.z registers swapped).
Left:

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107D9A20 | TestBoxAxes(extents, direction, delta, length) | 37.8 % | x87 throughout: three face tests then three cross-product tests with early returns; the stack temporaries (abs values) and the operand order of each test differ |
| 0x107D9CB0 | TestBoxesSAT(extentsA, delta, rotation, extentsB) | - | 1 111 bytes, box vs box SAT; called by 0x107DA110 / 0x107DA360; not attempted |
| 0x107DA110 | Intersects(OBB, OBB) | 15.2 % | delta in A's space and the 3x3 of axis dots on the stack, then TestBoxesSAT; the straight version is 625 bytes vs 583: the original shares the a.axis loads between the dots |
| 0x107DA410 | Intersects(OBB, Sphere) | 100 % | in the tree: the same `const Vector& v` + grouping trick as OBB::Contains |
| 0x107DA5D0 | Intersects(Plane, OBB) | 82.6 % | NONMATCHING in tree: `Vector n(plane.normal)` (copy constructor) and grouped dots get the shape; the original keeps n.z, n.y, n.x on the x87 stack and sums the radius terms axis 2, 0, 1 (ours 1, 0, 2 whatever the source order) |
| 0x107DA730 | PlaneCrossesBox(normal, point, halfExtents) | 8.5 % | the original subtracts `point` right after each sign branch joins (shared tail) and keeps the max corner on the stack; all scalar / Vector forms tried come out longer (271-306 bytes) |
| 0x107DA850 | ClassifyBox(box, planes, count) | 47.4 % | frame matches with two Vector locals (far corner declared first); the plane pointer register (ecx vs edx) and the reload of normal.x differ |
| 0x107DB250 | TriangleBoxOverlap(centre, halfExtents, Vector4 vertices[]) | - | 1 981 bytes, triangle vs box SAT; not attempted |
| 0x107DBA10 | Intersects(const Triangle&, const AABB&) | 44.5 % | frame 0x58 matches with `Vector4 vertices[4]` (three copied member-wise, 16-byte stride), centre.Add(max, min) * 0.5, extents.Sub; the original sinks centre.z / extents.z and the first `max.x + min.x` load order differs |

Intersects(const Triangle&, const OBB&) (0x107DBB10) matches with the corners transformed into a `Vector local[3]`
array that is then reused for the zero centre and the extents (the original's 0x60 frame). Intersects(const Triangle&, const Sphere&) (0x107DBCC0) matches: `d.Sub(centre, closest); sqrtf(d.y * d.y + d.z * d.z + d.x * d.x) <= radius`, compiled in intersect.cpp (ClosestPoint external, so the sphere pointer lives in esi).

## spline.cpp (0x107D49F0 - 0x107D6F10), mostly in the tree

A keyed cubic spline (class names SplineSegment / Spline guessed, src/code/math/spline.h): `int current; SplineSegment
segment (Matrix coefficients, Matrix derivative, bool flag; 0x84 bytes); bool closed (0x88); bool flag (0x89); int
mode (0x8c); unsigned count (0x90); Vector4* keys (0x94); Vector4* tangents (0x98); float* lengths (0x9c); int step
(0xa0); int stepsPerSegment (0xa4)`. Matched: the segment's constructors, operator=, SetFlag, Evaluate /
EvaluateDerivative / EvaluateSecondDerivative, BeginStepping, Build; the spline's constructor, destructor, SetMode,
SetClosed (functions.tsv ends it 16 bytes early), SetKeyCount, SetFlag, GetSegmentCount / F, GetKey,
InvalidateLengths, SetKey x2, SetTangent, SelectSegment (`count` is unsigned, compared as `(int)count - 4` there),
Evaluate x2, the two other Build overloads (0x107D5FE0 from Vector keys with w = 1, 0x107D6480 from a Matrix of keys; functions.tsv sizes cover only their dispatch), StartStepping (the clamp reassigns the `index` parameter), NextStep (needs Step compiled in the unit: the
original keeps `edx` across the call), the lengths (DerivativeLength, ArcLength, GetSegmentLength, GetTotalLength,
GetLength). EQUIVALENT in tree: Step (0x107D4BC0, 18.9 %: the original loads the three addends, then the three
targets of each row into six registers and reloads every row; plain `+=`, Set, Add, float / Vector temporaries and
loops all schedule differently), the copy constructor and operator= (0x107D59C0 / 0x107D5C00, 85 %: ebx / ebp swapped,
the original holds the null in ebp and compares other.lengths with an immediate; shared or int loop counters do not
change it). Left:

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107D5040 | SplineSegment::BuildCatmullRom(k0, k1, k2, k3, Matrix& g) | 28.5 % | rows k1, (chord slopes sum) * (d1 / 2), k2, ...; the intervals d0..d2 come from the keys' w when `flag` is set (returns early when one is <= 0), else 1; 504 bytes of SSE scheduling, permuter over the slope lines and sums plateaus |
| 0x107D5240 | SplineSegment::BuildHermite(k0, k1, k2, k3, t0, t1, Matrix& g) | - | 1 501 bytes, not attempted |
| 0x107D6C40 | Spline::GetParameter(length) | 22 % | NONMATCHING in tree: segment search over `lengths` (matches), first guess `(length - sum + segmentLength) / segmentLength + start`, then 32 Newton steps with fsel-style clamps (`Select(t - start, t, start)`, `Select(t - end, end, t)`, mathutils.h) and GetLength / EvaluateDerivative; the original computes `end` and the first `t` in SSE (start converted through memory), we get x87 |

## segment.cpp (0x107D6F40-0x107D7650), partly in the tree

Segment is `{Vector start; Vector end;}`. The compiler keeps `d = end - start` and `v = p - start` as memory Vectors
and reads them back in x87 with term orders that change from function to function (x,z,y dot products; (z²+y²)+x²
lengths). Explicitly parenthesised x87 sums on `d.Sub(...)` Vectors are what reproduce them (the compiler keeps the
grouping but reorders flat sums).

| Address | Function | Best | Note |
| --- | --- | --- | --- |
| 0x107D6F40 | GetAABB | 100 % | in the tree. DistanceSquared(p, t, lengthSquared) (0x107D6F90) matches: `t <= EPSILON_FLOAT`, the x87 sums need explicit groupings per branch (`(y^2 + x^2) + z^2` then `(x^2 + z^2) + y^2` on `d.Sub` vectors) |
| 0x107D7020 / 0x107D7190 | ClosestPoint(p, out) / ClosestPoint(p, t, lengthSquared, out) | 100 % | in the tree; groupings found by sweeps (the two direct-difference branches of the second one only match as a pair: the compiler shares choices across branches) |
| 0x107D72D0 | Parameter(p) | 100 % | in the tree: `(v.y * d.y + (d.z * v.z + d.x * v.x)) / ((d.x * d.x + d.y * d.y) + d.z * d.z)`, found by sweeping groupings and operand orders |
| 0x107D7380 | GetSphere | 100 % | in the tree: `sum.Set(start.x + end.x, end.y + start.y, end.z + start.z)`: the operand order inside Set arguments is kept, unlike plain statements |
| 0x107D7420 | DistanceSquared(p) (clamped projection) | EQUIVALENT | in the tree (99.4 %): only the first branch's z^2 + x^2 comes out as x^2 + z^2; the first pair of a three-term x87 sum is ordered by the compiler, only the last term follows the source |
| 0x107D7570 | DistanceSquaredToLine(p) | 100 % | in the tree; numerator `d.y * v.y + (d.z * v.z + d.x * v.x)` found by a sweep |
| 0x107D7650 | ClosestPointOnLine(p, out) | EQUIVALENT | in the tree (98.6 %): dz^2 + dx^2 of the denominator in swapped registers |
| 0x107D7770 / 0x107D7B40 | segment-segment distance / closest points | - | 963 / 1407 bytes, not attempted |
| 0x107D80C0 | LineDistanceSquared(other) | EQUIVALENT | in the tree (76 %): `n.Cross(d, e)`, parallel case tail-calls DistanceSquaredToLine(other.start); e.x / d.y / d.z registers rotated |

## random.cpp (0x107D8380-0x107D8740), mostly in the tree

Seed x2, NextVector01 and NextVector11 match. The vector functions return `Vector` by value (the hidden result
pointer is the `out` the old notes assumed; NRVO puts the local in it): `Vector v; v.x = NextFloat01(); ...; return v;`
with `Next()` built on `Step` returning the new state (`unsigned low = Step(w, 18000) & 0xFFFF`), so the w value is
reused from the register.

| Address | Function | Best | Note |
| --- | --- | --- | --- |
| 0x107D8660 | NextUnitVector() | ~70 % | NONMATCHING in tree: rejection loop on NextVector11 (0.001 <= len^2 <= 1), x87 1 / sqrt; the original copies each candidate member-wise into the result and a second local and scales the local into the result |

## symmetricmatrix.cpp (0x107D9100–0x107D9A00), partly in the tree

Multiply(a, b) (0x107D9100) matches: the six sums of the product's upper triangle in a temporary, `*this = result`.

| Address | Function | Best | Note |
| --- | --- | --- | --- |
| 0x107D96C0 | Transform(const Vector&, Vector&) | 10.4 % | plain sums plateau; original loads xy, v.z, v.y, v.x, xz, yz first |
| 0x107D9290 | Transform(const Matrix&) (R^T S R) | 16 % | T = S R as nine floats, then the six sums into a temporary copied with dword moves; ours comes out 50+ bytes longer |
| 0x107D9510 | adjugate-like | — | not drafted |
| 0x107D9820 | Invert (scales by 1/xx first, 0x107D90A0) | — | not drafted |
| 0x107D97B0 | Print (assert channel " Math  Pre ", static enable flag 0x111BBDE8) | — | needs the log function 0x1063C750 |

## perlin.cpp (0x101040C0–0x101043F0), partly in the tree

Lattice and Interpolate (0x10104140, cosine interpolation, no caller) match. The two big ones keep the right operations but not the schedule.

| Address | Function | Best | Note |
| --- | --- | --- | --- |
| 0x10104180 | Noise::Sample(x, y, z): cosine-weighted trilinear blend of 8 Lattice values, periods via `(i+1) % p` | 44.4 % | the three (int) conversions first, then the subtractions; weights as locals before the calls and the blend as one nested expression `L000 * (1 - wx) + L100 * wx ...` get the call order and the frame start. The original stores wx four times, wy twice, wz once (one copy per blend, like inline-function parameter temporaries) and is 495 bytes vs our 473; an inline Lerp evaluates its Lattice arguments in the wrong order (right to left) |
| 0x101043F0 | Noise::Evaluate(x, y, z): octave loop, periods scaled by frequency and restored (period[0]/[1] swapped!), clamp, 1 - pow(power, 255 r) | 22.5 % | `float falloff = persistence` inside the loop body helps; prologue register choice differs |

## vector4.cpp (0x107DD200–0x107DD690), mostly in the tree

| Address | Function | Best | Note |
| --- | --- | --- | --- |
| 0x107DD470 | Matrix::SetRowsLerp(t, v): row i = (1-t) v_i (1,1,1) + t e_i | 71.4 % | same code, registers of t and v.x swapped; loop forms are worse |
| 0x107DD690 | 726 bytes | — | not looked at |

## sphere.cpp / capsule.cpp (0x107DC390–0x107DD1A0), partly in the tree

| Address | Function | Best | Note |
| --- | --- | --- | --- |
| 0x107DCD20 / 0x107DCDF0 | Sphere::IntersectRay / IntersectRayFirst | 100 % | in the tree: `d.Sub(origin, centre)`, `b = direction.Dot(d)`, `c = d.Dot(d) - radius * radius` |
| 0x107DD090 | Sphere::AddSphere | 68 % | `d.Sub(other.centre, centre)`, `sqrtf((d.y * d.y + d.z * d.z) + d.x * d.x)` and the early returns give the original's head (register numbers off); the original scales d in place by inv without copies, every Set / direct form tried copies inv. GetAABB (low / high through `Set` with `radius + centre.x` first) and AddPoint (`half` before `inv`, `direction.Set(inv * d.x, ...)`, `centre.Set(direction.x * half + centre.x, ...)`) match |
| 0x107DC3F0 | FastAtan(x) (atan approximation, constants 0.0708/0.1438) | 53.3 % | first branch x87 product order |
| 0x107DC390 / 0x107DC3C0 | the same polynomial as static helpers (x87 arg / xmm1 arg) | — | custom calling convention, only reachable from this unit |
| 0x107DC550 | Capsule::Contains(p) | EQUIVALENT | in the tree (68 %), as Cylinder::Contains: z terms added before y terms (commutative) |
| 0x107DC620 | Capsule::GetDirection(p, out, distance) | 33 % | d.Sub, Dot, clamp to +-halfLength, out = d - direction t, Normalize, distance = length - radius; on the axis out = direction x (direction.z, direction.x, -direction.y) computed into registers first, then NormalizeFast. The original places the `t <= halfLength` branch at the end with a duplicated multiply (316 bytes vs our 296-300) |
| 0x107DCC10 | Cylinder::GetAABB (centre, direction, halfLength, radius; capsule.h) | - | not drafted; Cylinder::Transform (0x107DC7E0) matches, Cylinder::Contains (0x107DC800) is EQUIVALENT (88 %: z before y in the commutative dot sums; the member Dot / Sub / Set inlines are what get the copies right, direct expressions come out 5 bytes shorter) |
| 0x107DC8C0 | 834 bytes, probably a Cylinder ray test | - | not looked at |
