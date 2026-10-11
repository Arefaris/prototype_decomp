# math module: work list

The three debug prints (Vector::Print 0x107CEA20, Matrix::Print 0x107D1910, SymmetricMatrix::Print 0x107D97B0) match:
`static bool` flags next to `core::Report(0, tag, file, line, 0, format, ..., 0) == 3` calls, the raw-bits variants
through float copies read as `*(int*)&`; the flags are mapped in symbols.txt under their static-local names.

State of every function of `code/math` looked at so far (2026-10-10). Matched functions are in `src/code/math`;
this list is for the rest. Percentages are objcmp's byte identity of the best attempt (relocations as wildcards).

Levers that turned functions into matches (2026-10-11 session), worth trying first on the rest:
- matrices written element by element in memory order (m[0][0], m[0][1], ...), loops for 3x3 bodies do not unroll;
- results computed before any store: an inline `Set(...)` (Matrix3 transforms) or a temporary copied back;
- reciprocal scaling through an inline taking the reciprocal as its parameter (`v.Scale(1.0f / length)`), not a
  local `inv`;
- the `Dot` inline instead of written-out sums when the x87 / SSE operand order will not follow the source
  (Triangle::SmallestAngle, ClassifyBox);
- one variable reused for several stages (Cylinder::GetAABB) or an array reused for later values
  (Intersects(Triangle, OBB)) when the original's frame is smaller than ours: the compiler does not share stack
  slots between distinct locals;
- `const T&` reference locals (or their absence: `planes[i]` indexed directly) change which operand of a product
  is loaded first;
- copying a const reference argument member-wise into a local Vector first (Matrix::SetRowsLerp);
- for sums that no operand order fixes, a coordinate-descent search over the 12 groupings of each three-term sum
  (`z*z + (x*x + y*y)` forms included) found Triangle::Contains.

## quaternion.cpp (0x107CD360 - 0x107CE3C0)

ToAxisAngle (0x107CE310) matches: `axis.Set(x, y, z)`, the x87 length, `if (!(fabsf(length) <= EPSILON_SMALL))` and
`axis.Scale(1.0f / length)`: an inline taking the reciprocal as its parameter keeps the original's registers, a
local `inv` does not (Vector::Scale added to vector.h).

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107CD410 | SinPolynomial | 98.2 % | sign of the leading coefficient folded differently (NONMATCHING in tree); it is an inline helper, inlined twice in Slerp |
| 0x107CD7A0 | FromEuler (variant A) | 92.7 % | SinCos of the three half angles, then `a = cy * sx; b = sy * cx; c = cy * cx; d = sy * sx` and x, y, z, w as `a * cz - b * sz` etc. get everything but the stack slots of cx / sx / cy (original 0 / 4 / 8, ours 8 / 0 / 4; declaration order, half-angle forms and a cosine-first inline do not change it) |
| 0x107CD8D0 | FromEuler (variant B) | 77.2 % | as above |
| 0x107CDA00 | ToMatrix | 83.3 % | x2 / y2 / z2 = 2x, the nine products, the 3x3 stored column by column (m[0][0], m[1][0], m[2][0], ...); y and z end up in swapped registers whatever the order of the products and sums |
| 0x107CDCE0 | FromVectors (rotation from a to b) | 38.7 % | c = a cross b, length = c.Normalize(); below 0.0005: identity when a . b > 0, else c reused for a perpendicular of a (Set, three cases) and NormalizeFast, w = 0; else the x87 half-angle form. Structure and layout match (486 vs 488 bytes); the SSE dot of the fallback and the x87 dot of the main path load their operands in another order |
| 0x107CDF90 | Slerp | - | AtanRatio called out of line, SinPolynomial inlined twice; not attempted |
| 0x107CE220 | MakeClosest | 3.8 % | same instructions, `this`/`q` registers swapped (NONMATCHING in tree) |

## vector.cpp (0x107CE3D0 - 0x107CEAE0)

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107CE4D0 | Normalize(const Vector&) | 80 % | x87 operand order for y (NONMATCHING in tree) |
| 0x107CE5E0 | RotateAboutAxis | 18.5 % | Rodrigues with `this` overwritten by the axis first; aliasing reloads |
| 0x107CE850 | CrossProduct | 73.7 % | store scheduling (NONMATCHING in tree) |

## matrix.cpp (0x107CEAE0 - 0x107D2EC0)

OrthoLH / OrthoRH / OrthoOffCenterLH / OrthoOffCenterRH (0x107CFC80 / FD20 / FDB0 / FE90) match once all 16 elements
are assigned in memory order (m[0][0], m[0][1], ...): the store order of the source, not the order of the
computations, drives the schedule. The five 3x3 operations through a Matrix3 temporary (0x107D0E20 / 0F60 / 10A0 /
1150 / 1320: scale, add, subtract, a * b, a * b^T) match written out element by element (loops do not unroll) and
finished with `t.CopyTo(*this)`. Multiply(a, b) and its identical copy (0x107D2C00 / 2CC0, 0xBC bytes with the
alignment padding inside) match as two descending loops into a Matrix temporary, `a`'s row in four locals (loaded
1, 0, 2, 3) and the sum grouped `((a0 * b0j + a1 * b1j) + a2 * b2j) + a3 * b3j`, then `*this = t`. ToAxisAngle (0x107D2D80) matches: `Clamp((trace - 1) * 0.5, -1, 1)`, `acosf`, a ternary for
`0.5f / sinf(a)`, the axis as a Vector scaled with `Scale(s)` and stored with `axis.Set(v.x, v.y, v.z)`.

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107CED00 | FromAxisCosSin | 23.7 % | the axis components are loaded into SSE registers and spilled for the x87 check `|len^2 - 1| > 4e-5`, copied into a local Vector only on the Normalize path; our copies are loaded with fld, and our formula bodies come out shorter (278 vs 323 bytes) |
| 0x107CEE50 / EF70 / F0A0 | Euler rotations | 50 / 52 / 62 % | permuter plateau; products of three factors |
| 0x107CF280 | Reflection(plane) | 89.7 % | memory-order assignment, `float d = p.d * 2.0f`, products `(a * b) * -2.0f` (81.7 %) or `b * (a * -2.0f)` (89.7 %, other association); only the two x*y products (m[0][1], m[1][0]) and d*y load their operands the other way round; the compiler canonicalises every operand order tried, a Vector4 plane changes nothing |
| 0x107CF5D0 | Orthonormalize | 50.9 % | rows 0 and 1 copied with Set, x.NormalizeFast(), z = x cross y written out in a Set, z.NormalizeFast(), y = z cross x, rows stored in memory order; the original loads x.y / x.z into registers during the first copy and differs in registers in the second cross |
| 0x107CF720 | IsOrthonormal | 16 % | six dot products spilled, inline IsEqual x5 + one out-of-line call |
| 0x107CF8F0 / FA80 / FB10 | Transform / Rotate / RotateInverse | EQUIVALENT | y/z registers swapped |
| 0x107CF990 | Transform(const Vector4&, Vector4&) | EQUIVALENT | sums need explicit grouping `((a + b) + c) + d` to keep the original order; v.z / v.y / v.w registers rotated. FromQuaternion (0x107CEB70), Transpose3x3(src) (0x107CF4F0) and Transform(count, Vector4*) (0x107CFBD0, needs this one compiled in the unit) match |
| 0x107CFC00 | PerspectiveFovLH | - | calls Identity first; not attempted |
| 0x107CFF70 / 0x107D03A0 | LookAt LH / RH | 52.8 % | (target, eye, up): z = target - eye, x = up cross z, y = z cross x, translation -axis . eye; the original spills the running sum of -x . eye three times into a reused argument slot (540 bytes vs our 510) |
| 0x107D0190 / 0x107D05C0 | orientation from direction and up | 89.5 % | `Vector z(direction)` (copy constructor), NormalizeFast, x.Cross(up, z), NormalizeFast, y.Cross(z, x) match the first half exactly; the permuter's best store order (89.5 %) is not a natural one, so the original's statement order is still unknown |
| 0x107D16B0 | IsIdentity(tolerance) | 29.1 % | sum of the squared differences from identity < tolerance^2; the original sums rows 2-3 off-diagonal, then the diagonal, then rows 0-1 off-diagonal, the compiler sorts every flat sum tried as off-diagonal in memory order then diagonal; explicit groupings get longer |
| 0x107D1AA0 | rotation taking a onto b | - | function-local statics with VS2005 guard bits |
| 0x107D1C90 / 1D20 / 1DB0 | rotation about Y / X / Z from a direction | 37.5 % | x87 1 / sqrt of the two squared components, then the 3x3; only the scaling multiplies differ (the original multiplies x and z in place, we copy inv); locals, Vector temporaries, Scale(1 / ...), row Sets and operand orders plateau at 26-28 % standalone |
| 0x107D1E40 | basis from a Z axis | - | |
| 0x107D20B0 | Inverse (general 4x4) | - | 1 536 bytes |
| 0x107D26B0 | Invert (orthonormal fast path) | 21.1 % | det of the 3x3; |det - 1| <= EPSILON_SMALL tail-calls InvertOrthonormal, else adjugate / det into a Matrix temporary with the translation brought back, ClearProjection on the temporary, `*this = t`. The original adds the three negative determinant terms as `+ (-x)` (separate negations), which every source form tried folds into subtractions |

## triangle.cpp (0x107D2ED0 - 0x107D3B50)

Triangle::Contains(p) (0x107D31C0) matches: Sub helpers, five dot products with explicit groupings (found by a
coordinate-descent search over the 12 groupings of each sum, `z*z + (x*x + y*y)` among them) and the sign-bit test
`((int&)z & ~((int&)x | (int&)y)) < 0`. SmallestAngle (0x107D3B50) matches: three `Normalize`d edges, `fabsf(e0.Dot(e1))` etc.
(the Dot inline, not explicit sums, gives the x87 order), `acosf(Clamp(Max(c2, Max(c1, c0)), 0, 1))` with Max and a
two-Select Clamp in mathutils.h.

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x107D2ED0 | IntersectRay(origin, direction, t&) | 52 % | NONMATCHING in tree: Moller-Trumbore with both windings written out (det > EPSILON_SMALL / det < -EPSILON_SMALL, shared tail t = e2 . q / det). A coordinate-descent sweep over the groupings and operand orders of the four dot products plateaus: the original adds direction . q as (z + x) + y, which the compiler never emits from source; declaring e2 before e1 lines up the middle but not the head |
| 0x107D3360 | Triangle::ContainsXZ(p) | 88 % | EQUIVALENT in tree: three 2D edge tests with early returns; the two factors of the first test come out in swapped registers |
| 0x107D3420 | Triangle::ClosestPoint(p, out) | 9 % | Ericson's region test; returns 1 / 2 / 4 for edges ab / bc / ca, 5 / 3 / 6 for corners, 0 inside. Original frame 0x7c with Vector locals in memory (p copy at 0, ac at 0x1c, bc at 0x28, a - p at 0x34, n at 0x40, c - p at 0x4c, b - p at 0x58, ab in registers), d1 / d3 / d4 / d2 at 0xc-0x18; the dots are written as -(ab . (a - p)) etc. Scalar and Sub/Dot/Cross-helper versions both land at 9 %: the compiler's schedule of the first block differs from the start (REA pseudocode is a faithful guide to the arithmetic) |
| 0x107D3AA0 | Area | 100 % | z, x, y cross components as float locals, `n.Set(x, y, z)`, flat sum in the sqrt |

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
| 0x107D4560 | GetCornerOffset(out, bits) | EQUIVALENT | in the tree (29.7 %): e = (bits & 1 / 2 / 4) ? -extents : extents per axis (bit 0 is axis[2]), stage-wise sums axis2 * ez, + axis1 * ey, + axis0 * ex; the original loads axis[2] and the first factor of each stage before the sign branches; copies / Vector temporaries / Set forms come out longer (201-233 bytes) |
| 0x107D4630 | Contains | 100 % | in the tree: `const Vector& v = axis[i]` in a `for (int i = 3; i--; )` loop with the x87 dot grouped `(v.x * d.x + v.y * d.y) + v.z * d.z` |
| 0x107D46D0 | GetDirection(p, direction&, distance&) | EQUIVALENT | in the tree (56.7 %): d = p - centre, t[i] = axis[i] . d, a do-while over i = 2..0 clamping t[i] to +-extents (`for (i = 3; i != 0; ) { i--; ...}` gives the original's loop without the entry jump; `float a` separate from `t[i]`), the nearest face replaces its t when inside, direction = d - sum axis[i] t[i] (Set of grouped sums), Normalize, negated inside. The original computes the offset stage by stage across the components; Vector operators (by-value temporaries) are far off (16 %) |
| 0x107D48E0 | GetSphere | 41.8 % | out = (centre, |axis0 ex + axis1 ey + axis2 ez|): the centre goes out as an x87 copy (copy constructor) after the products, so probably returned by value through a Sphere(centre, radius) constructor; the three scaled axes as Vectors (axis 2 first) give 41.8 %, the frame is 0x18 instead of 0xc |
| 0x107D49B0 | GetCorner | 100 % | in the tree, with GetCornerOffset compiled in the unit (it keeps `edx` / `ecx` across the call) |

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
| 0x107DA110 | Intersects(OBB, OBB) | EQUIVALENT | in the tree (98.6 %): d = b.centre - a.centre, t = a.axis[i].Dot(d), r[i][j] = aa.axis[i].Dot(bb.axis[j]) through `const OBB&` reference locals for both boxes (without them every product loads a's axis first), then TestBoxesSAT; only the x terms of r[0][1] and r[1][2] keep the operands the other way round |
| 0x107DA410 | Intersects(OBB, Sphere) | 100 % | in the tree: the same `const Vector& v` + grouping trick as OBB::Contains |
| 0x107DA5D0 | Intersects(Plane, OBB) | 82.6 % | NONMATCHING in tree: `Vector n(plane.normal)` (copy constructor) and grouped dots get the shape; the original keeps n.z, n.y, n.x on the x87 stack and sums the radius terms axis 2, 0, 1 (ours 1, 0, 2 whatever the source order) |
| 0x107DA730 | PlaneCrossesBox(normal, point, halfExtents) | 8.5 % | the original subtracts `point` right after each sign branch joins (shared tail) and keeps the max corner on the stack; all scalar / Vector forms tried come out longer (271-306 bytes) |
| 0x107DB250 | TriangleBoxOverlap(centre, halfExtents, Vector4 vertices[]) | - | 1 981 bytes, triangle vs box SAT; not attempted |
| 0x107DBA10 | Intersects(const Triangle&, const AABB&) | 44.5 % | frame 0x58 matches with `Vector4 vertices[4]` (three copied member-wise, 16-byte stride), centre.Add(max, min) * 0.5, extents.Sub; the original sinks centre.z / extents.z and the first `max.x + min.x` load order differs |

Capsule vs box (0x107DBFE0 - 0x107DC390): Intersects(const Capsule&, const OBB&) (0x107DC2B0) matches (direction and
centre offset through Matrix3::TransformTransposed, the local capsule written member-wise). EQUIVALENT in tree:
IntersectsCentredBox(extents, capsule) (0x107DBFE0, 28.7 %: the six SAT tests in x87 and the segment tail match in
form, but the original reloads capsule.direction from memory in the tail where we reuse the spilled test values;
returns bool, `xor al, al`), Intersects(const Capsule&, const AABB&) (0x107DC1D0, 60.8 %: the stores of
local.centre x / z are deferred past the member copies in the original; a permuter found 91 % only with an unnatural
statement order). SegmentBoxDistanceSquared (0x107DBD20, 695 bytes) is not attempted.

ClassifyBox(box, planes, count) (0x107DA850) matches with `planes[i]` indexed directly (a `const Plane&` local
gives other registers) and `normal.Dot(corner) + d` tests. Intersects(const Triangle&, const OBB&) (0x107DBB10) matches with the corners transformed into a `Vector local[3]`
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
| 0x107D9510 | SkewTransform(v): [v]x^T S [v]x | 100 % | in the tree: four products of S [v]x as locals (t10, t20, t00, t01 in that order), the rest inline, the six results in a temporary in the order xx, xy, xz, yy, yz, zz, then `*this = r`; only `v.y * yz` in t10 needed its operands swapped |
| 0x107D9820 | Invert(a) | EQUIVALENT | in the tree (26 %): scale = 1 / a.xx when |a.xx| > EPSILON_SMALL, Multiply(a, scale), cofactors c00 / c01 / c02, det = c00 xx + c01 xy + c02 xz, inv = scale / det, zero (`xx = yy = zz = 0; xy = xz = yz = 0`) when |det| <= 0. The original recomputes yz * yz and the c00 difference for r.xx; inline expansions with `- xy * (...)` give subtractions where the original adds |

## perlin.cpp (0x101040C0–0x101043F0), partly in the tree

Lattice and Interpolate (0x10104140, cosine interpolation, no caller) match. The two big ones keep the right operations but not the schedule.

| Address | Function | Best | Note |
| --- | --- | --- | --- |
| 0x10104180 | Noise::Sample(x, y, z): cosine-weighted trilinear blend of 8 Lattice values, periods via `(i+1) % p` | 44.4 % | the three (int) conversions first, then the subtractions; weights as locals before the calls and the blend as one nested expression `L000 * (1 - wx) + L100 * wx ...` get the call order and the frame start. The original stores wx four times, wy twice, wz once (one copy per blend, like inline-function parameter temporaries) and is 495 bytes vs our 473; an inline Lerp evaluates its Lattice arguments in the wrong order (right to left) |
| 0x101043F0 | Noise::Evaluate(x, y, z): octave loop, periods scaled by frequency and restored (period[0]/[1] swapped!), clamp, 1 - pow(power, 255 r) | 22.5 % | `float falloff = persistence` inside the loop body helps; prologue register choice differs |

## vector4.cpp (0x107DD200–0x107DD690), mostly in the tree

Matrix::SetRowsLerp(t, v) (0x107DD470) matches once v is first copied member-wise into a local Vector (like the
unit's other Vector4 wrappers) and the nine elements are written in memory order.

| Address | Function | Best | Note |
| --- | --- | --- | --- |
| 0x107DD690 | Matrix::SetHueRotation(angle, luminance) | 100 % | in the tree: Haeberli's hue rotation (rotate grey onto Z, shear, RotationZ, unshear, rotate back) through Matrix temporaries and Multiply; Concatenate x2 (0x107DD970 / 990) and SetPosition(float) (0x107DD9B0) match too |

## sphere.cpp / capsule.cpp (0x107DC390–0x107DD1A0), partly in the tree

| Address | Function | Best | Note |
| --- | --- | --- | --- |
| 0x107DCD20 / 0x107DCDF0 | Sphere::IntersectRay / IntersectRayFirst | 100 % | in the tree: `d.Sub(origin, centre)`, `b = direction.Dot(d)`, `c = d.Dot(d) - radius * radius` |
| 0x107DD090 | Sphere::AddSphere | 68 % | the `*this = other` branch matches as member-wise copies; the tail stores the new centre and radius together at the end while ours interleaves (Scale, Set, float and Vector temporaries tried). Earlier notes: `d.Sub(other.centre, centre)`, `sqrtf((d.y * d.y + d.z * d.z) + d.x * d.x)` and the early returns give the original's head (register numbers off); the original scales d in place by inv without copies, every Set / direct form tried copies inv. GetAABB (low / high through `Set` with `radius + centre.x` first) and AddPoint (`half` before `inv`, `direction.Set(inv * d.x, ...)`, `centre.Set(direction.x * half + centre.x, ...)`) match |
| 0x107DC3F0 | FastAtan(x) (atan approximation, constants 0.0708/0.1438) | 53.3 % | first branch x87 product order |
| 0x107DC390 / 0x107DC3C0 | the same polynomial as static helpers (x87 arg / xmm1 arg) | — | custom calling convention, only reachable from this unit |
| 0x107DC550 | Capsule::Contains(p) | EQUIVALENT | in the tree (68 %), as Cylinder::Contains: z terms added before y terms (commutative) |
| 0x107DC620 | Capsule::GetDirection(p, out, distance) | 33 % | d.Sub, Dot, clamp to +-halfLength, out = d - direction t, Normalize, distance = length - radius; on the axis out = direction x (direction.z, direction.x, -direction.y) computed into registers first, then NormalizeFast. The original places the `t <= halfLength` branch at the end with a duplicated multiply (316 bytes vs our 296-300) |
| 0x107DCC10 | Cylinder::GetAABB | 100 % | in the tree: `Min(fabsf(direction.x), 1.0f)` into one variable reused for the three axes (separate variables give a smaller frame); Cylinder::Transform (0x107DC7E0) matches, Cylinder::Contains (0x107DC800) is EQUIVALENT (88 %: z before y in the commutative dot sums; the member Dot / Sub / Set inlines are what get the copies right, direct expressions come out 5 bytes shorter) |
| 0x107DC8C0 | 834 bytes, probably a Cylinder ray test | - | not looked at |
