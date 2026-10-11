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

29 matched, 2 EQUIVALENT, 3 NONMATCHING (0x1063B0D0, the unsigned StrNCpy that only forwards to StrNCpyTail, matches
against the EQUIVALENT helper).

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
0x10645D40 - 0x10645EDB in front of it are the memory-space unit (see memory/memoryspace.cpp).

## memory/rangemap.cpp (0x10646140 - 0x10646574): 13 matched, 1 EQUIVALENT

`core::RangeMap` (class name guessed): sorted (address, heap index) pairs, the map from address ranges to heaps that
the heap registration (0x1063AE10) fills with Set and reads with Find / Get. Placed under memory/ for that reason.

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x10646400 | Set(start, end, value, int* previous) | 9 % | EQUIVALENT in tree: same blocks and order; the original keeps the index in edi and `end` in ebx (later `value`), ours keeps the index in ebx with an `index * 8` temporary in edi and reloads `end` / `value`; it also repeats the `key == start` test (the nested / spelled-apart forms do not bring it back) |

## memory/memoryallocatormalloc.cpp (0x10646580 - 0x10646995): done

`core::MemoryAllocatorMalloc` (RTTI name): all 28 functions matched, including the inline constructor /
destructor (defined in the class body so that the deleting destructor and InitSystemAllocator inline them; the
compiler still emits the out-of-line copies), the static helpers with register arguments and the 18-slot
`IMemoryAllocator` interface (`code/core/memory/imemoryallocator.h`, member names guessed from this class). Left
alone: 0x106465D0 - 0x10646600 and 0x106467D0, four interlocked helpers (atomic read via `_InterlockedAnd(p, -1)`,
increment, decrement; register arguments) that nothing in the unit calls. Link notes: the deleting destructor needs
`??3@YAXPAX@Z` (operator delete 0x107DEFD0) and RTTI needs `??_7type_info@@6B@` (0x10E9A9A4) in symbols.txt;
`IsDebuggerPresent` is declared without `__stdcall` because the generated kernel32.lib names the slot
`__imp__IsDebuggerPresent`.

The three preceding functions in the same unit now match too: placement `operator new(unsigned int, void*)`
(0x10646580), `DestroySystemAllocator` (0x10646590, name guessed) and its forwarding entry
`GetSystemAllocatorDestroy` (0x106465A0, name guessed). Destruction calls vtable slot 2 with flag 0, running the
vector deleting destructor without freeing the allocator's static storage. The corresponding construction entries
are InitSystemAllocator (0x10646960) and its forwarding entry (0x10646990).
`ninja check` passes all 315 matching annotations; the relink verifier reports no differences outside replaced
functions or relocation targets. The unit also compiles with MSVC 2022 x86, and the hybrid DLL reaches free roam.

## time.cpp (0x1063CBB0 - 0x1063CE32): done

`core::Time` stores an unsigned microsecond remainder at +0, unsigned milliseconds at +4, and cached float
seconds at +8 (12 bytes). The class association and method/member/file names are guesses: `core::Time` appears
in an AudioZone RTTI name, but these methods have no recovered names. Evidence is the pinned PROTOPC_2025 image,
Ghidra's saved database and the disassembly at the addresses below; generated pseudocode stays in
`local/decomp/core_time/`.

Eight matched: Set (0x1063CBE0), SetMicroseconds (0x1063CC30), SetSeconds (0x1063CC60), Clear (0x1063CCE0), Add (0x1063CD00),
AddMicroseconds (0x1063CD60), SubtractMicroseconds (0x1063CD90) and the free ScaleTime helper (0x1063CDD0).
The two-part Set does not normalize its arguments. SetSeconds truncates seconds * 1000 and seconds * 1000000
to unsigned integers; only the latter is reduced modulo 1000. Subtraction clears on equality or underflow.
ScaleTime keeps the quotient/remainder form `(value / divisor) * multiplier + ((value % divisor) * multiplier) / divisor`,
including unsigned intermediate overflow. The 64-bit division helpers resolve to the original CRT
`__aulldvrm` (0x10A88920) and `__aulldiv` (0x10A88530).

Add matches all 84 bytes with `microseconds += micros`, then the millisecond carry, then `microseconds %= 1000`.
Keeping the running sum in the member makes VS2005 emit the original unsigned `div`; a temporary local causes
reciprocal multiplication and different x87 scheduling. Keep the member updates in that order, including the
32-bit wraparound before division. AddMicroseconds now calls the reconstructed Add.

0x1063CBB0 belongs to the preceding `core::Timer` object (fields at +0x0C/+0x14), not this 12-byte time value.
Its final virtual method now matches as `GetProgress` (name guessed): it returns the unsigned elapsed counter divided
by the unsigned period as a float.

Validation (2026-10-10): `ninja check` passed all 315 matching annotations. The completed time unit contributes
nine matches (596 bytes), including the 40-byte Timer method and the 84-byte Time::Add.
The unit also compiled with MSVC 2022 x86. An ignored local harness (`local/time_differential.cpp`, linked
against the VC8 object) passed 956 comparisons against the pinned original functions, covering unsigned
boundaries, microsecond carries, subtraction to zero, float conversion and 64-bit scaling. The hybrid DLL
reached free roam in an isolated test copy; movement, pause, single-step and resume commands completed.

## controllerxinput.cpp (0x10648FF0 - 0x106492BA): leaf methods

RTTI identifies the two reconstructed classes as `core::ControllerOutputPointXInput` and
`core::ControllerInputPointXInput`. Eleven leaf virtual methods match: scalar output get/set, scalar input count/read,
clamped scale get/set, binding pair set/clear, scaled range read, and range get/set. The output setter preserves the
original NaN behavior and marks the value dirty only when the incoming value is not equal to the stored value.
Class names are observed; method/member names are guesses from vtable position and behavior.
Validation (2026-10-10): `ninja check` passes all 326 matching annotations. These eleven functions contribute
271 exact bytes. The hybrid DLL verifier reports no differing bytes or relocation targets, the unit compiles with
MSVC 2022 x86, and the refreshed test copy reaches free roam and accepts movement input.

## memory/twowayallocator.cpp (0x10645370 - 0x10645D3A): class done

`core::MemoryTwoWayAllocator` (RTTI name; assert path `code\core\src\memory\twowayallocator.cpp`): 33 annotated
functions match: this unit's copies of the rounding helpers (`AlignUp` / `AlignDown` templates, `IsAligned`), all 22
virtual methods, the constructor and destructor, Init / Create / AllocImpl / FreeImpl and the three factories. The
compiler-generated functions match too (scalar deleting destructor 0x10645B50, the RefCount adjustor thunk
0x10645A30, the interface constructors / deleting destructors 0x106456D0, 0x106458E0, 0x106458F0, 0x10645B90,
0x10645BA0) and are mapped in symbols.txt, but are not annotated (no source definition). Notes:
- Classes: `code/core/object.h` (core::Object / core::RefCount: the heap travels through `gObjectHeap` 0x110BCCBC
  from operator new into the constructor and back), `code/core/memory/allocatorbase.h` (AllocatorBase_Name /
  AllocatorBase_Safety, only declared: their unit is 0x10646D10 - 0x10646E10), `code/core/report.h` (the assert
  report 0x1063C750, variadic).
- The constructor is out of line (the factories call it); the factories call `CoreName()` once more after `new`.
- AllocImpl's failure branches set `block = 0` and fall through (a `return 0` there loses the tail duplication);
  the two `static bool` report switches are locals (0x110BCCF0 high end, 0x110BCCF1 low end). `__FILE__` is spelled
  out as the original build's `..\..\..\code\...` literal.
- AllocAligned needs the two-sided if / else: the one-sided form becomes a `cmova`.
- objcmp now compares a data constant of our object only up to the next symbol or the section end (the static bools).
Left alone: 0x106453E0 (stores two bytes to 0x110BCCE4 / 0x110BCCE5, no references), 0x10645400 / 0x10645430 /
0x10645460 (three argument-shuffling wrappers around 0x1064C300 with callers all over the engine), 0x106454A0
(`return this->field4`), 0x106456C0 / 0x10645720 (empty) and the interlocked helpers 0x10645970 - 0x10645990
(register arguments); which unit they belong to is not clear.

## memory/allocatorbase.cpp (0x10646D10 - 0x10646E10): done

All 11 functions of `core::AllocatorBase_Name` and `core::AllocatorBase_Safety` match (file name guessed; the
class layout is in `code/core/memory/allocatorbase.h`). SetName copies with the unsigned StrNCpy and
`sizeof(name)`; Safety mode 2 creates / deletes / enters / leaves the critical section through the wrappers
0x1063D260 - 0x1063D290 (`code/core/criticalsection.h`, not reconstructed: they call the kernel32 imports as
`__stdcall`, which the generated import library may not name).

## memory/memorypool.cpp (0x1063D430 - 0x1063DB97): done (26 functions)

`core::MemoryPool` (RTTI name; `IMemoryPool` adds AllocBlock / GetIndex / GetBlock as slots 18 - 20): fixed-size
blocks on a free list, the same frame as MemoryTwoWayAllocator (`code/core/memory/memorypool.h`, file name
guessed). All methods, Init, Contains and the two factories match; the compiler-generated functions (AllocatorLock
and AllocatorBase constructor / destructor copies, the interface constructors and deleting destructors, the
adjustor thunk) match as well and are mapped. Init calls the twoway unit's `AlignUp<unsigned int>` (0x10645370):
the rounding templates are shared COMDATs, declared in allocatorbase.h. AllocBlock and the two-way AllocAligned
need an inline `Max` template (`code/core/utility.h`): the plain conditional forms become `cmov`.

The constructor matches once `RefCount::count` is `volatile` (the original keeps the RefCount vftable store and
clears eax after it; a plain `long` lets the compiler move both).

Left alone: 0x1063D450 - 0x1063D480 and 0x1063D700 - 0x1063D730 (empty functions), 0x1063D7D0 - 0x1063D7F0
(interlocked helpers with register arguments).

## memory/segmentpoolallocator.cpp (0x1063DBA0 - 0x1063E72B): done (54 functions)

`core::SegmentPoolAllocator` (RTTI name; assert path known): one heap block cut into equal segments with 12-byte
headers (`Segment`: cursor, mark, count), one segment open for bump allocation, lock bits, a stack of byte
counters. Its base `core::AllocatorBaseSub` (IMemoryAllocator + AllocatorBase at 4, name / safety / flag slots;
shared with MemoryDlAllocator) has its methods here (0x1063E400 - 0x1063E470). All functions match (the constructor
since `RefCount::count` became volatile); the compiler-generated ones (AllocatorBaseSub constructor / destructor / deleting destructor, the
adjustor thunk 0x1063E560, the scalar deleting destructor) match and are mapped. Notes:
- The second factory starts at 0x1063E6E0 (functions.tsv has 0x1063E6F0, a misaligned start).
- Segment::Segment is `inline` in the .cpp (Init's placement new inlines it, and our object still emits the copy
  0x1063DBA0); ~Segment (0x1063DBB0, empty) is never called here, so it has no copy to annotate.
- The address helpers read `segments` into a local before calling GetHeaderSize (the original keeps it in edi);
  the sums only match in the spelled orders. Bool helpers need `if (...) return true; return false;` (the
  expression form returns through eax), lock bits test `lockMask & 0x80000000` (a `< 0` test is jge, not jns).
- Next keeps the result in a local `found = -1` and breaks; AllocAligned has two separate early returns and the
  segment base in a local before the Segment::Alloc call.
- RefCount gained a `RefCount(long initial)` constructor: this allocator starts at one, its factories do not AddRef.
- `core::Report` is (kind, tag, file, line, expression, format, ...): asserts pass (1, " oldassert ", file, line,
  "condition", 0).

Left alone: 0x1063E520 - 0x1063E540 (interlocked helpers with register arguments).

## memory/spilloverallocator.cpp (0x10B803A0 - 0x10B80B12): 23 matched, 3 EQUIVALENT

`core::MemorySpillOverAllocator` (RTTI name; RefCount at 0, the interface at 0xC, file name guessed): allocates
from a primary allocator and falls back to a second allocator or a heap (`GetHeapAllocator`, 0x1063AA00),
counting spilled bytes / blocks (stats 15 / 16) and calling an optional callback. The static range test
`Contains` (allocator in edi) matches; each unit of this area has its own copy (0x10B80B30 is the debug
allocator's). Slot 9 of IMemoryAllocator is evidently the range count (`Contains` loops over it with GetRange);
it is still called GetType here. The Free family needs the fallback in a local (the original tail-duplicates the
call).

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x10B80720 | Alloc | 94.8 % | EQUIVALENT in tree: registers rotate around the callback call (callback / primary / userData); local copies, (*callback), volatile members, a notifier struct and an inline Notify helper (not inlined) do not help |
| 0x10B807D0 | AllocAligned | 95.0 % | EQUIVALENT in tree: as Alloc |
| 0x10B80890 | AllocFlags | 93.5 % | EQUIVALENT in tree: as Alloc, plus the vtable load of the fallback call in edx instead of eax |

Left alone: 0x10B80350 - 0x10B80390, 0x10B80460, 0x10B80690 (interlocked helpers with register arguments);
0x10B80300 / 0x10B80320 belong to the class before (destructor 0x10B801D0, singleton at 0x1132FE78).

## memory/debugallocator.cpp (0x10B80B20 - 0x10B814DF): done (36 functions)

`core::MemoryDebugAllocator` (RTTI name; `IMemoryDebugAllocator` adds SetAllocCallback / SetFreeCallback /
GetHeaderSize as slots 18 - 20; file name guessed): wraps an allocator; mode 0 passes through, other modes frame
every block with a CRC-32 checked 16-byte header (crc, size, next, prev) and footer (crc, raw pointer, total,
owner) kept in a list, and every call reports to optional callbacks. All debug allocators are in one global list
under one critical section. Every function matches, including the frame checks and the compiler-generated ones.
Notes:
- The list head / tail / count / lock are class statics, not file statics: the original rereads them after each
  store through a pointer (internal linkage lets our compiler cache them). Likewise CheckHeaders /
  CheckAllocators / CheckAllocatorsLocked are external functions: as statics our compiler passes the allocator in
  ebx, the original on the stack.
- The callbacks are read into locals userData first, then the function pointer.
- Synchronise is a switch with two identical cases (2 and 3), not one case list.
- AllocAligned drops the inner allocator's result in mode 0 and returns null (the original's bug, kept).
- The range test is the same code as the spill-over one; named OwnsBlock here so symbols.txt has distinct names.
- Slot 17 (still called IsThreadSafe) validates here before asking the inner allocator: probably a check method.

## memory/externalallocator.cpp (0x10B814E0 - 0x10B81A61): done (25 functions)

`core::MemoryExternalAllocator` and its base `core::AllocatorBaseSub_NoStubs` (RTTI names; file name guessed):
an allocator over memory managed by an embedded heap object at 0x44 (`ExternalHeap`, class name guessed, 0x590
bytes; its methods 0x10B833E0 - 0x10B853A0 are declared and mapped, not reconstructed: the next unit to look at).
Plain (non-atomic) reference count; the last Release destroys the object in place and frees the block it lives
in; AllocFlags only serves the allocator's own tag. Init reads GetName back through the vtable and drops it. Every
function matched on the first compile.

## memory/memoryspace.cpp (0x10645D40 - 0x10645EDB): done (13 functions)

The main-memory "memory space" (all names guessed): copy / async copy / heap wrappers that take a space id first
and ignore it, and `core::MemorySpaceAsyncRequest_Copy` (RTTI name), the request an async copy returns. One
static request (0x1127A474) serves every copy; it is constructed by a dynamic initializer elsewhere (0x10D66930),
so our source only declares it (`gMemorySpaceCopyRequest`, mapped in symbols.txt) instead of defining it, which
would add an initializer of our own. Left alone: 0x10645D50 / 0x10645D60 (empty functions of unknown owner).

## file/common/request.cpp (0x1064C4A0 - 0x1064DF2B): 144 functions

`core::Request` and its 28 subclasses (RTTI names; file name guessed, next to the asserted file/common/file.cpp):
the work items drives execute (open / open by key / save-game open / close / commit / read / write / seek / tell /
size / cancel for files; open / media / can-create / format / directories / find first-next-close / destroy /
cancel for drive instances; event and callback completions). Requests come from one MemoryPool (0x114-byte blocks,
"FileRequest") under one lock (InitRequests / ShutdownRequests, class operator new / delete). Every function
matches, including the 29 scalar deleting destructors (mapped, not annotated). Notes:
- `code/core/file/drive.h` / `file.h` declare core::Drive, core::File, core::InstanceDrive, the file cache and the
  cache list only as far as the requests use them: slot numbers kept with placeholder slots, fields at the
  offsets the requests access, non-virtual methods mapped in symbols.txt (not reconstructed: 0x1064DF30 onwards).
- The request vtable: dtor, Execute, IsFor(owner), GetDrive, Prepare (default: Drive::Mount through Finish),
  GetPath, GetType; the completion callbacks add Complete. Finish(result, error) stores the drive error in the
  file / instance under its IMutable lock.
- Constructors are plain out-of-line functions at the end of the unit; each ends with CoreName().
- FileOpenRequest::Execute needs its shared-handle tail as a `__forceinline` helper (OpenShared): the original has
  it twice; as a plain inline member VS2005 does not inline it.
- 0x1064C5E0 (a jump to ~Request) and 0x1064C600 (an IsFor-like compare) are in no vtable; left alone.

## Candidates nearby (leaf functions, not started)

- 0x106469A0 - 0x10646D06: allocator registration tables guarded by a lock (0x1127A99C), bit masks 0x1127A9B4 /
  0x1127A9B8, lists at 0x1127A958; a unit of the memory system that needs its data named first.
- 0x10646E50 - 0x10647200: wide-to-ANSI character conversion with a 32-entry table at 0x110BCE28 (string
  encoding, leaf, recursive fallback).
- 0x10648F70 - 0x106493BB: remaining XInput point destructors, table lookups, constructors, output commit and encoded
  input conversion.
