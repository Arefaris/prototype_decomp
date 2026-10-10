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

## strings.cpp (0x1063AFA0 - 0x1063BB20, without the string heap)

28 matched, 2 EQUIVALENT, 3 NONMATCHING.

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x1063AFE0 | StrCpy | 69 % | EQUIVALENT in tree: same loops, the original keeps the source in esi and the moving destination in edx |
| 0x1063B050 | StrNCpyTail (static) | 23 % | EQUIVALENT in tree: same loops, the original keeps count in eax and copies the source to esi; the register arguments (edx, ecx, eax) do match |
| 0x1063B6B0 | StrNICmp | 34 % | NONMATCHING in tree: the original keeps one copy of the two ToLowerChar calls and a `jmp` back to the loop head; every for / while / goto form tried gets the condition duplicated (loop inversion) |
| 0x1063B880 | NormalisePath | 59 % | NONMATCHING in tree: all blocks and registers as the original; our compiler sinks the `.\` case's `read += 2` into the trailing-dot case (one block fewer, which also shortens a jne and moves the loop padding), and the inline strlen's `lea esi, [ecx + 1]` is taken from `path` instead of the cursor copy |
| 0x1063BAA0 | StrNCat(char*, const char*, int) | 95 % | NONMATCHING in tree: only the inline strlen prologue differs (`mov ecx, eax` before `push esi` and `lea esi, [ecx + 1]` from the copy); p - q, p - (d + 1), p - d - 1, an unsigned char cursor, the parameter as cursor and `register` all give the same code |

## stringheap.cpp (0x1063B730 - 0x1063B7E0): done

8 functions matched (default string, two counters, Set/GetStringHeap, the StrCpy / StrLen forwarders compiled as
jumps, StrDup). StrDup only matches with StrLen and StrCpy as external calls, which is why this is a unit of its
own. 0x1063B7E0, a jump to 0x1063AC00 (another unit), is left alone. HeapAlloc 0x1063A850 is named and declared
(`code/core/heap.h`), not reconstructed (virtual call through the heap table 0x110BC5A4).

## Candidates nearby (leaf functions, not started)

- 0x10646140 - 0x10646400: a sorted array of (key, value) pairs (binary search at 0x10646310, insert/erase, grow
  through the allocator 0x1063A850); `__thiscall` methods of an unnamed container.
- 0x1063CBB0 - 0x1063CD00: five small float functions (not looked at).
- 0x10648F70 - 0x106492C0: a run of small functions with float maths (not looked at).
- 0x10645D40 - 0x10646045: memset / memcpy wrappers with register arguments (CRT calls through 0x10A8835C).
