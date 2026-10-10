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

## memutils.cpp (0x10645EE0 - 0x10646045): done

15 functions matched: seven static helpers (memcpy / memset, register arguments) and eight public wrappers that
check the size first (MemCopyUnchecked does not). memcpy and memset resolve to the generated msvcr80 import
library, not to symbols.txt (the import thunks 0x10A884EE / 0x10A8835C are defined by that library already).
0x10645D40 - 0x10645EDB in front of it are allocator interface objects (vftables 0x10D96DB8, 0x10E473E0,
0x10E473F4), another unit.

## memory/rangemap.cpp (0x10646140 - 0x10646574): 13 matched, 1 EQUIVALENT

`core::RangeMap` (class name guessed): sorted (address, heap index) pairs, the map from address ranges to heaps that
the heap registration (0x1063AE10) fills with Set and reads with Find / Get. Placed under memory/ for that reason.

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x10646400 | Set(start, end, value, int* previous) | 9 % | EQUIVALENT in tree: same blocks and order; the original keeps the index in edi and `end` in ebx (later `value`), ours keeps the index in ebx with an `index * 8` temporary in edi and reloads `end` / `value`; it also repeats the `key == start` test (the nested / spelled-apart forms do not bring it back) |

## memory/memoryallocatormalloc.cpp (0x106465B0 - 0x10646995): done

`core::MemoryAllocatorMalloc` (RTTI name): all 28 functions matched, including the inline constructor /
destructor (defined in the class body so that the deleting destructor and InitSystemAllocator inline them; the
compiler still emits the out-of-line copies), the static helpers with register arguments and the 18-slot
`IMemoryAllocator` interface (`code/core/memory/imemoryallocator.h`, member names guessed from this class). Left
alone: 0x106465D0 - 0x10646600 and 0x106467D0, four interlocked helpers (atomic read via `_InterlockedAnd(p, -1)`,
increment, decrement; register arguments) that nothing in the unit calls. Link notes: the deleting destructor needs
`??3@YAXPAX@Z` (operator delete 0x107DEFD0) and RTTI needs `??_7type_info@@6B@` (0x10E9A9A4) in symbols.txt;
`IsDebuggerPresent` is declared without `__stdcall` because the generated kernel32.lib names the slot
`__imp__IsDebuggerPresent`.

## time.cpp (0x1063CBE0 - 0x1063CE32): 7 matched, 1 NONMATCHING

`core::Time` stores an unsigned microsecond remainder at +0, unsigned milliseconds at +4, and cached float
seconds at +8 (12 bytes). The class association and method/member/file names are guesses: `core::Time` appears
in an AudioZone RTTI name, but these methods have no recovered names. Evidence is the pinned PROTOPC_2025 image,
Ghidra's saved database and the disassembly at the addresses below; generated pseudocode stays in
`local/decomp/core_time/`.

Matched: Set (0x1063CBE0), SetMicroseconds (0x1063CC30), SetSeconds (0x1063CC60), Clear (0x1063CCE0),
AddMicroseconds (0x1063CD60), SubtractMicroseconds (0x1063CD90) and the free ScaleTime helper (0x1063CDD0).
The two-part Set does not normalize its arguments. SetSeconds truncates seconds * 1000 and seconds * 1000000
to unsigned integers; only the latter is reduced modulo 1000. Subtraction clears on equality or underflow.
ScaleTime keeps the quotient/remainder form `(value / divisor) * multiplier + ((value % divisor) * multiplier) / divisor`,
including unsigned intermediate overflow. The 64-bit division helpers resolve to the original CRT
`__aulldvrm` (0x10A88920) and `__aulldiv` (0x10A88530).

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x1063CD00 | Time::Add(milliseconds, microseconds) | 18.3 % | NONMATCHING: original uses unsigned `div` by 1000; VS2005 emits a reciprocal multiply. Local/parameter forms, quotient/remainder order and inline helpers did not match. The retained straightforward draft is 16.7 %. `/Os` changes other matched functions too. AddMicroseconds still calls the original Add. |

0x1063CBB0 belongs to the preceding timer object (fields at +0x0C/+0x14), not this 12-byte time value.

Validation (2026-10-10): `ninja check` passed all 310 matching annotations; `ninja dll` verified the relinked
image without unexpected differences; `ninja report progress` counted seven new matches (472 bytes).
The unit also compiled with MSVC 2022 x86. An ignored local harness (`local/time_differential.cpp`, linked
against the VC8 object) passed 892 comparisons against the pinned original functions, covering unsigned
boundaries, microsecond carries, subtraction to zero, float conversion and 64-bit scaling. The hybrid DLL
reached free roam in an isolated test copy; movement, pause, single-step and resume commands completed.

## Candidates nearby (leaf functions, not started)

- 0x10646580 - 0x106465A0: two tiny global-allocator forwarders (`return second argument`, a virtual call on the
  system allocator pointer 0x1127A894) between RangeMap and MemoryAllocatorMalloc.
- 0x106469A0 - 0x10646D20: allocator registration tables guarded by a lock (0x1127A99C), bit masks 0x1127A9B4 /
  0x1127A9B8, lists at 0x1127A958; a unit of the memory system that needs its data named first.
- 0x10646E50 - 0x10647200: wide-to-ANSI character conversion with a 32-entry table at 0x110BCE28 (string
  encoding, leaf, recursive fallback).
- 0x1063CBB0: preceding timer object's unsigned counter/period ratio; not reconstructed.
- 0x10648F70 - 0x106492C0: a run of small functions with float maths (not looked at).
