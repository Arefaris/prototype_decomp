# core module: work list

State of the `code/core` units looked at so far (2026-10-10). Matched functions are in `src/code/core`; this list is
for the rest. Percentages are objcmp's byte identity of the best attempt (relocations as wildcards). The module's
code sits around 0x10639000 - 0x10650000 (memory/segmentpoolallocator.cpp asserts at 0x1063E10B, file/common/file.cpp
at 0x1064DF9A); the sub-directories of the units below are not known, so the sources sit directly in
`src/code/core/src`.

## hash.cpp (0x1063A440 - 0x1063A69D): done

11 functions, all matched (`core::Hash64` family, `core::Hash32` family, the callback hooks, the hex formatters).

## crc32.cpp (0x10646050 - 0x1064613A): done

2 functions, both matched (table build, MSB-first CRC-32 update).

## strings.cpp (0x1063AFA0 - 0x1063BB20)

24 matched, 2 EQUIVALENT, 1 NONMATCHING, 10 not attempted.

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x1063AFE0 | StrCpy | 69 % | EQUIVALENT in tree: same loops, the original keeps the source in esi and the moving destination in edx |
| 0x1063B050 | StrNCpyTail (static) | 23 % | EQUIVALENT in tree: same loops, the original keeps count in eax and copies the source to esi; the register arguments (edx, ecx, eax) do match |
| 0x1063B350 | StrTok(string, delims, char** context, bool skipEmpty) | - | not attempted; chars compared as sign-extended ints, two nested scans over the delimiters |
| 0x1063B3F0 | StrTok wrapper (skipEmpty = 1) | - | 26 bytes, trivial once 0x1063B350 is in |
| 0x1063B410 | StrTok with a static context (0x11278FB8) | - | as above |
| 0x1063B6B0 | StrNICmp | 34 % | NONMATCHING in tree: the original keeps one copy of the two ToLowerChar calls and a `jmp` back to the loop head; every for / while / goto form tried gets the condition duplicated (loop inversion) |
| 0x1063B730 - 0x1063B770 | string-heap handle accessors (data 0x11278FC0 - 0x11278FC8, default string pointer at 0x110BC5AC) | - | 5 tiny functions, not attempted (need the data symbols) |
| 0x1063B7A0 | StrDup | - | allocates through 0x1063A850 (another unit: `(heap, size)`), needs its declaration |
| 0x1063B7E0 | jump to 0x1063AC00 | - | forwarder into another unit |
| 0x1063B7F0 | MatchWildcard(string, pattern) | - | recursive `*` / `?` matcher, 123 bytes, not attempted |
| 0x1063B880 | NormalisePath | - | removes `.` and `..` components in place, 209 bytes, not attempted |
| 0x1063BAA0 | StrNCat(char*, const char*, int) | 9 % | the inline strlen prologue (`do { c = *p++; } while (c); len = p - (dst + 1)`) comes out with a separate `sub 1`; the copy loop after it is the matched StrNCpy shape |

## Candidates nearby (leaf functions, not started)

- 0x10646140 - 0x10646400: a sorted array of (key, value) pairs (binary search at 0x10646310, insert/erase, grow
  through the allocator 0x1063A850); `__thiscall` methods of an unnamed container.
- 0x1063CBB0 - 0x1063CD00: five small float functions (not looked at).
- 0x10648F70 - 0x106492C0: a run of small functions with float maths (not looked at).
- 0x10645D40 - 0x10646045: memset / memcpy wrappers with register arguments (CRT calls through 0x10A8835C).
