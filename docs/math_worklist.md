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
| 0x107CD410 | SinPolynomial | 98.2 % | sign of the leading coefficient folded differently (NONMATCHING in tree); it is an inline helper, inlined twice in Slerp. Also tried (2026-10-11): a namespace `const float` for the coefficient, a Horner chain on a variable starting at -2.39e-8f, `(0.0f - 2.39e-8f)`, `(-1.0f * 2.39e-8f)`, `(float)-2.39e-8`: all fold into fsubr / subss. The coefficients sit at 0x10E67C10-1C as ordinary __real constants of the unit (AtanRatio's precede them, all in reverse order of use) |
| 0x107CD7A0 | FromEuler (variant A) | 92.7 % | SinCos of the three half angles, then `a = cy * sx; b = sy * cx; c = cy * cx; d = sy * sx` and x, y, z, w as `a * cz - b * sz` etc. get everything but the stack slots of cx / sx / cy (original 0 / 4 / 8, ours 8 / 0 / 4; declaration order, half-angle forms and a cosine-first inline do not change it) |
| 0x107CD8D0 | FromEuler (variant B) | 77.2 % | as above |
| | | | 2026-10-11: the original's second sine lands in the first parameter's slot (ours too); a `float& sy = x` alias, writing the sine into `x` and arrays drop to 49-57 %, a permuter over the product operands and declaration order reaches 83 % |
| 0x107CDA00 | ToMatrix | 83.3 % | x2 / y2 / z2 = 2x, the nine products, the 3x3 stored column by column (m[0][0], m[1][0], m[2][0], ...); y and z end up in swapped registers whatever the order of the products and sums |
| 0x107CDCE0 | FromVectors (rotation from a to b) | 38.7 % | c = a cross b, length = c.Normalize(); below 0.0005: identity when a . b > 0, else c reused for a perpendicular of a (Set, three cases) and NormalizeFast, w = 0; else the x87 half-angle form. Structure and layout match (486 vs 488 bytes); the SSE dot of the fallback and the x87 dot of the main path load their operands in another order |
| 0x107CDF90 | Slerp | 20 % | c = (w + x) + (y + z) dot, invSin = 1 / sqrtf(1 - c^2), angle = AtanRatio(1 / invSin, |c|), two inlined SinPolynomials scaled by invSin, Select(1 - c^2 - EPSILON_SMALL, ..., linear weights) twice, negated second weight when c < 0, then an inline x87 normalisation. Blocked by the SinPolynomial sign folding, which the SSE inline shows too (subss from the constant) |
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
| 0x107CF280 | Reflection(plane) | 89.7 % | memory-order assignment, `float d = p.d * 2.0f`, products `(a * b) * -2.0f` (81.7 %) or `b * (a * -2.0f)` (89.7 %, other association); only the two x*y products (m[0][1], m[1][0]) and d*y load their operands the other way round; the compiler canonicalises every operand order tried, a Vector4 plane changes nothing. 2026-10-11: a permuter over both operand orders of all 18 products in the `b * (a * -2.0f)` form (and over the 12 products with a `const Vector&` normal) never leaves 73 % / 28 %: VS2005 canonicalises these operands whatever the source says; the original also reads p.d first (before any store), so `float d = p.d * 2.0f` belongs at the top |