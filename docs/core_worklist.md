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

## time.cpp (0x1063C7A0 - 0x1063D1E8): done (49 functions)

The whole unit now (2026-10-11): besides the Time value below, the performance counter clock (InitMemoryStage1 is
really the clock start-up, reference-counted, reading the frequency; GetTicks / GetSeconds / GetMicroseconds /
GetMilliseconds), the local date and day of the week, and `core::Timer` / `core::TimerList` (RTTI names; interfaces
ITimer 14 slots, ITimerList 6 slots in `code/core/time.h`): timers come from the list's MemoryPool ("TimerList",
0x24-byte blocks, class operator new(size, list)), sit in its table while running, and the list's Update adds the
time since the last call and calls the callback (slot 0: elapsed, userData) when the period is reached (mode 1 stops
first). Everything matched on the first or second compile; TimerList::Update needs `timers[i]` read twice (a slot
pointer loads it once). The compiler-generated functions (ITimer / ITimerList constructor copies, the deleting
destructors, the Object-vftable thunk) are mapped. Left alone: 0x1063C780 / 0x1063C790 (IRefCount constructor
copies). The older notes:


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

## controllerxinput.cpp (0x10648750 - 0x10649F5A): 85 functions

The XInput controllers (`code/core/controllerxinput.h`; RTTI names core::ControllerSystemXInput, core::ControllerXInput,
core::ControllerInputPointXInput, core::ControllerOutputPointXInput; file, member and method names guessed), the twin of
the DirectInput unit on the same interfaces. The system holds the four pads as a member array; each pad allocates
point arrays (`new (heap) T[n]`) sized for the largest entry of a static table of controller types (0x110BD178: one
type, the XBox 360 controller, with 20 inputs and 2 motors described by name, kind and a field offset / size / mask
in XINPUT_GAMEPAD / XINPUT_VIBRATION) and sets them up when XInputGetCapabilities reports the pad. Pads continue the
DirectInput joystick numbers ("JoystickN"). All 85 annotated functions match (the 11 leaf methods matched earlier
kept their code; SetScale / GetScale are now SetThreshold / GetThreshold of IControllerInputPoint). Notes:
- `core::Object` gained `operator new[](size, heap)` / `operator delete[]`: the vector deleting destructors (slot 2 of
  the point vftables) and `delete[]` inline them; VS2005 itself calls the global `operator new[](4)` for a zero count.
- ReadField / WriteField are inline functions of the unit (their out-of-line copies 0x10648750 / 0x10648770 are
  annotated); the type lookup in Connect is written in place (an inline helper would leave a copy the original lacks).
- The XInput functions are called through the image's own import thunks (imported by ordinal), mapped as
  `_XInputGetState@8` etc.
- The input point's +0x28 is the time from Init to the last change (Update never moves the start time).
- Float results: `result = raw != 0 ? 1.0f : 0.0f` (the if form skips the store); the inactive branch of Update is
  the else of `if (active)`.
Validation (2026-10-11): free roam in the hybrid, keyboard input works (no pad attached: the pads stay disconnected).
Left alone: 0x106489C0 - 0x106489E0 (interlocked helpers with register arguments).

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

## file/common/file.cpp (0x1064DF50 - 0x1064E9DF): 45 functions

`core::File` (RTTI name, assert path known): every function matches. Files come from a pool ("File", 0x174
bytes) and sit in a table by pool index (InitFiles / ShutdownFiles, ReportOpenFiles when the pool runs dry); the
IMutable lock of every file is the global file lock. The asynchronous calls submit requests to the drive
(Drive::Submit, 0x1064FEB0) and return its answer; the ...Wait forms then poll IsIdle, pumping the drive.
WaitSignal blocks on a per-file event (count + manual-reset event, the 0x1063D320 - 0x1063D400 helpers) that
EndRequest signals. Notes: IFile derives from IRefCount (its inline destructor is what leaves the IRefCount
vftable in ~File); `pending` is unsigned; CanShare and operator new needed their exact return structure;
the constructors initialise every member before the cache in the mem-initializer list (the cache constructor
runs between them and the last two). Left alone: 0x1064DF30 (an EventSignal helper with a register argument
that nothing here calls) and 0x1064DF40 (the IMutable constructor copy).

## file/common/instancedrive.cpp (0x1064EB10 - 0x1064F805): 54 functions

`core::InstanceDrive` (RTTI name; file name guessed): one owner's handle on a core::Drive, the drive-side twin of
File (own pool "InstanceDrive", 0x30 bytes; global instance lock as IMutable; requests submitted to the drive;
Wait / WaitSignal / IsIdle as in File; the last Release closes an open search). Every function matches. Notes:
- The path calls split the path (SplitPath, 0x10643D60) into locals declared `native, relative, device[0x14],
  full[0x104]` and take `relative`, or `native` when the drive hides names (GetFlags bit 7), written as an
  assignment plus `if`: the ternary gives a branch, the original a cmovs.
- GetError needs the single-exit form (value in a local, one Unlock).
- IDrive slots 43 / 44 forward Drive slots 5 / 6 with two arguments (a forwarder's jump register is edx without
  stack arguments and eax with them, a handy hint for the argument count of pure forwarders).
Left alone: 0x1064EAF0 (an EventSignal helper with a register argument) and 0x1064EB00 / 0x1064F780 (interface
destructor and constructor copies).

## file/common/drive.cpp (0x1064FAA0 - 0x1065028C): 43 matched, 1 EQUIVALENT

`core::Drive` (RTTI name; file name guessed): the abstract drive, `Drive : IRefCount, Object, SafeRefCount` (the
drive's 24 virtual slots sit on IRefCount's vtable: there is no separate drive interface, which is why the
constructor leaves the IRefCount vftable store in place). SafeRefCount (RTTI name) is IMutable plus a count, its
AddRef / Release under the object's own lock (the concrete drives implement Lock / Unlock). The base defaults of
the virtual slots, the state calls the instances forward, the completion queue (Queue, Update) and the request
queue forwarders all match; CompletionCallbackRequest::IsFromThread (0x1064C600, request.cpp) joined the request
unit. Update walks the completion list with a link that, after a kept request, points at a local copy of its
next pointer (so only a run at the head is unlinked); kept as in the original.

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x10650180 | Drive::Update | 98.9 % | EQUIVALENT in tree: the original loads `this` into ecx before pushing the fault handler's result for ClearFault |

Not reconstructed yet: the file cache (0x10650690 - 0x106511C0, FileCacheList 0x10650540 - 0x10650670) and the
request queue (0x106524C0 onwards), declared in drive.h / file.h and mapped.

## sync.cpp (0x1063D220 - 0x1063D428): 16 functions

The thread-synchronisation wrappers (`code/core/criticalsection.h`; file and all names guessed): critical
sections, semaphores (address of a handle), counted events (count + manual-reset event; EventSignal counts down
through a static helper with register arguments and sets the event at zero) and AtomicRead. All match. The kernel32
calls go through the import slots declared as function pointers (`extern "C" ... (__stdcall* _imp__Name)(...)`):
the relinker's import libraries name the slots `__imp__Name` without the `@N` a dllimport __stdcall declaration
would reference. Left alone: 0x1063D1F0 / 0x1063D210 (interlocked helpers with register arguments that nothing
calls, like the ones in the allocator units).

## string.cpp (0x10647F70 - 0x106486FE): 29 functions (35 mapped)

core::String (`code/core/istring.h`; RTTI names IString / String, file and method names guessed): a reference-counted
heap string, the buffer from the object's own heap, capacity and a null flag in one bitfield word. All match. What
the matching showed: the methods test the null flag through an inline bool accessor (`shr` / `test al, 1`, while
the out-of-line IsNull at 0x10648010 exists too); the buffers come from an inline `new(heap) char[size]` (the heap is read
before the capacity call); string.cpp uses a static forceinline NewBuffer(size, heap) for it, since an inline
operator new[](size, heap) would clash with the engine's out-of-line one (0x107DEFB0) in the hybrid link; the destructor is defined in the class (the deleting destructor inlines it, 0x106485C0 is the
COMDAT copy); overloaded virtuals are declared in reverse vftable order. Mapped, not annotated: the IString
constructor 0x10647F70, the deleting destructor and its thunk, and out-of-line copies of Object's operator new /
delete (0x10648700 / 0x10648720). Left alone: 0x10647FE0 - 0x10648000 (interlocked helpers with register arguments).

## platform.cpp (0x10647BF0 - 0x10647F5A): 20 functions (24 mapped)

core::IPlatformWin32 / core::Platform (`code/core/platform.h`; RTTI names, file and member names guessed): the Win32
platform object PlatformInit builds in static storage (0x1127A9C0, class placement operator new defined in the
unit): window and instance, CoInitialize / CoUninitialize, a chain of window-message hooks that subclass the window
(SetWindowLongA with GWL_WNDPROC, CallWindowProcA), two 256-byte strings, the purecall handler, and the x87
precision. All match. PlatformInit keeps the new object in a local (the original does not reload gPlatform: the
compiler knows Reset leaves ecx and edx alone). Mapped, not annotated: the out-of-line IPlatformWin32 constructor /
destructor and Platform constructor copies and the scalar deleting destructor.

## codec/*.cpp (0x10646E20 - 0x10647BE9): 30 functions, 22 matched, 8 EQUIVALENT

The character codecs behind the text converters (`code/core/textcodec.h`; file and function names guessed): ASCII,
Windows-1252, UTF-8 (Unicode, Inc.'s ConvertUTF.c: isLegalUTF8 and its tables), UTF-16, UTF-32 and Shift-JIS, each
with Decode / Encode / Copy / Count, plus the half-width / full-width form mapping (DecomposeWidthForm, in the UTF-8
file) that the Shift-JIS encoder calls. Six translation units, not one: the Shift-JIS encoder's recursive call stays
a call only when DecomposeWidthForm is compiled elsewhere (in the same file the compiler turns it into a loop). The
data tables are declared extern and mapped. Matching notes: Utf8DecodeChar advances the `source` parameter itself;
the UTF-16 surrogate pair is written through `*target++`; Windows-1252 0x80 - 0x9F is an else-if chain
(`c < 0x80`, `c <= 0x9F`); AsciiToShiftJis subtracts in 16 bits (`(unsigned short)(c - '0') + 0x824F`).
EQUIVALENT: AsciiEncodeChar (register choice), AsciiCopyString / Cp1252CopyString (registers saved after the
empty-source test), Utf8CopyString / Utf8CountChars (pointer and index registers swapped), Utf16CopyString /
Utf16CountChars (the original tests the surrogate ranges with two compares each; every form tried folds them),
ShiftJisEncodeChar (block order). Not reconstructed: 0x106478C0, a static trail-byte test with its argument in al
that nothing calls (the compiler drops an unreferenced static function).

## textconvert.cpp (0x1063E730 - 0x106412AF): 61 functions

The text converters (`code/core/textconvert.h`; file and names guessed): Copy / Count forwarders per encoding (the
Count ones return 0 for a null string), and ConvertText(target, targetEncoding, source, sourceEncoding, replacement,
size, flags, &bytes, &chars) with the encodings ASCII, UTF-8, UTF-16, UTF-32, Shift-JIS, Windows-1252 (0 - 5). All
match. Three static function templates: ConvertTo<target> dispatches on the source encoding (or copies when the
encodings are equal and there are no flags), ConvertChars<source, target> converts character by character,
CopyChars<encoding> validates and copies. The 48 instances carry stacked FUNCTION annotations above their template;
the compiler emits them in the original's order. The instances take register arguments, and which register gets
which argument follows the parameter order (target before source); ConvertChars walks a copy of its target
parameter, which frees the parameter's stack slot for the decoded character as in the original.

## controllerdirectinput.cpp (0x106412C0 - 0x10643835): 81 functions

The DirectInput 8 controllers (`code/core/controllerdirectinput.h`; RTTI names core::ControllerSystemDirectInput,
core::ControllerDirectInput, core::ControllerInputPointDirectInput, core::ControllerOutputPointDirectInput; file,
member and method names guessed) behind the interfaces of `code/core/controller.h`. InitDirectInput builds the system
(CoCreateInstance of CLSID_DirectInput8, subclassing the window to track the focus), which enumerates the attached
devices: XInput pads are left out with the DirectX SDK's WMI sample (IsXInputDevice, `__stdcall` here), mice /
keyboards optionally. Each controller builds its own data format (one DWORD per object in enumeration order, the
keyboard's scan code table at 0x11279010 filled on the way), an input point per object and a constant-force output
point per force-feedback actuator. All 81 annotated functions match. The SDK declarations it needs are hand-written
in `code/core/directinput.h` (the toolchain has no SDK headers); the dxguid GUIDs and the `__uuidof` constants are
mapped. Notes:
- The ole32 / oleaut32 / user32 calls must be `__declspec(dllimport)`: only then does the compiler load an import
  slot once for repeated calls (IsXInputDevice's three SysAllocString calls). The decorated `__imp__Name@N` the
  declarations reference is pointed at the relinker's undecorated slot with `#pragma comment(linker,
  "/alternatename:...")`. A `const` function-pointer slot (the sync.cpp way) is still reloaded before every call.
- The unit's globals are file statics (nothing outside reads them) except the options word, which must be external:
  as a static the compiler caches it in a register across the constructor's virtual calls. The keyboard table is
  only declared (extern), so the test tools that read it at 0x11279010 keep working with the hybrid DLL.
- `core::RefPtr` (`code/core/refptr.h`, name guessed): the smart pointer behind the device, effect, location string
  and platform members; its out-of-line copies for five interfaces (0x106422E0 - 0x10642590), the guiddef.h
  IsEqualGUID / operator== / operator!= copies, the interface constructors, RefCount::GetCount (new: the atomic read
  Update uses) and the compiler-generated destructors are byte-identical and mapped, not annotated (header code).
- Float switches return through a `result` local (the original stores into the argument slot and loads it back);
  the destructors release their lists with the next pointer read ahead (`next = c->next; while (next) ...`);
  `(dwDevType & 0xFF) >= 0x14` compares as int, `(unsigned char)dwDevType` as a byte; bool results from an
  HRESULT need the if / return true / return false form.
Left alone: 0x10641390, 0x106425B0 and 0x10641D80 - 0x10641DA0 (interlocked helpers with register arguments).

Validation (2026-10-11): the hybrid DLL reaches free roam in a private test copy; the keyboard and mouse devices
are polled through the reconstructed code and injected movement, jump and mouse input take effect.

## controllersystem.cpp (0x10643840 - 0x10643BFE): 16 functions

`core::ControllerSystem` (RTTI name; `code/core/controllersystem.h`, file and function names guessed): the system
the engine uses, the DirectInput and the XInput systems behind one IControllerSystem. Controllers count DirectInput
first; FindController sends "JoystickN" with N past the DirectInput joysticks to XInput (whose pads are numbered
from there on: InitXInput gets the DirectInput joystick count). All match; the XInput system's entry points
(0x106487B0, 0x10649F00, 0x10649F50, 0x10649910) are declared in controllerxinput.h and mapped. FindController
needs its choice in a bool (`xinput = true`, then one if / else): the early-return forms swap esi / edi or the
block order. Left alone: 0x106438A0 - 0x106438C0 (interlocked helpers with register arguments). The 22 jumps that
follow (0x10643C00 - 0x10643D50) forward to the file system (0x10649F90 onwards), a unit of their own.

## file/common/mounts.cpp (0x10649F60 - 0x1064ACE5): 30 functions

The device mounts of the file system (`code/core/file/mounts.h`; all names and the file name guessed): a table of 27
devices (name, drive, root path) under one critical section, the default device (the current directory's drive
letter at start-up), the device-to-path mappings and drive creation of the Win32 device unit (0x1064F810 - 0x1064FA88,
declared and mapped), automatic mounting, and the file, save-game, drive instance and Cement library opens that split
the path and look its device up (Cement libraries: core::CementLibrary, RTTI name). All match. The engine reaches
them through the 22 forwarders 0x10643C00 - 0x10643D50 (another unit). Notes:
- The device lookups need a `drive = 0; if (index != -1) drive = sMounts[index].drive; if (drive == 0) { retry,
  if (drive == 0) fail }` shape and the drive read again as `sMounts[index].drive` where it is used: a `goto` to the
  open code, or a slot pointer, puts the blocks or registers elsewhere. The Cement open keeps the source drive in a
  variable of its own until the end.
- SetMountPath returns with the lock held when the device is unknown or the table full (kept).
- Drive::FlushRequests / RequestQueue::Flush return whether requests are still queued (UnmountDrive waits on it).
- An open drive's 4th argument is passed but unused.
Validation (2026-10-11): free roam in the hybrid (every game file is opened through these functions).

## file/win32/devices.cpp (0x1064F810 - 0x1064FA88): 6 functions

The Win32 devices (all names and the file name guessed): the current directory's drive letter, four device names
mapped to RAM drives (core::RamDrive; the mapped value goes to its constructor), whether a device exists (a mapping
or a bit of GetLogicalDrives) and the drive behind a device (CreateRamDrive 0x10652320 or CreateWin32Drive 0x10651CE0,
mapped, then the root path through Drive slot 23). All match; IsValidDevice needs the drive index in a local before
the GetLogicalDrives call.

## file/common/filesystem.cpp (0x10643C00 - 0x10643EE7): 25 functions

The file system entry points the engine calls (`code/core/file/filesystem.h`; names and the file name guessed): 22
forwarders to the mounts (compiled as jumps), SplitPath (device, full path with back slashes, normalised; the
default device when the path names none or a device name longer than 16 characters), a path comparison and a path
hash. All match. SplitPath needs `char* target = device == 0 ? full : device` (the plain if becomes a cmove) and the
slash loop on a pointer of its own with `NormalisePath(full + length)`.

## language.cpp (0x1064ACF0 - 0x1064AE22): 5 functions

The game language (`code/core/language.h`; names guessed): a language code ('E', '?' before init) in gLanguage
(external: the language entry points at 0x10643EF0 read it), eight listeners told in three priority rounds. All
match; RemoveLanguageListener decrements the count in place (`count--`, then compares with it).

## languageinfo.cpp (0x10643EF0 - 0x106444C5): 12 functions

The language entry points (forwarders to language.cpp, two copies of `return gLanguage`), the installed language
from the registry (HKEY_LOCAL_MACHINE, key and value named by the platform's two strings; a string value read with
atoi / written with sprintf) and the code / name conversions (names and file name guessed). All match. The switches
include `case '?'` (the jump tables start at '?'); a failed registry query falls through to its own close-and-fail
tail (`if (query == 0) { close; return atoi(...); } close; return -1;`, otherwise the two failure tails merge).

## crashrecord.cpp (0x106444D0 - 0x1064475C): 8 functions (15 mapped)

The debug output and crash handler chains (`code/core/crashrecord.h`; RTTI class names, members guessed): handlers
pass a message (fields kind, tag, file, line, expression, text, level, flags as Report fills them) or a crash on to
the next handler; the crash record keeps the last 4 KB of output in a ring (every message but "/autotest" ones, each
ended with a line break) and stops on errors while a never-written flag (0x11279429) is set. All match; the base
constructors and destructors are inline in the classes (their copies are mapped, not annotated). The record object
itself (0x11279430) is only declared: a dynamic initializer elsewhere constructs it.

## thread.cpp (0x10644890 - 0x106452F6): 44 matched, 2 EQUIVALENT

The core threads and fibers (`code/core/thread.h`; file and all names guessed): every thread the core creates and the
main thread have a Thread record (0xB4 bytes) in a global list under one critical section, reachable from the thread
through a TLS slot (GetThreadData, 0x10644DC0); each thread runs as a fiber of its own (ConvertThreadToFiber) and can
switch to fibers it creates; threads and fibers get eight user slots from global defaults (the registration unit at
0x106469A0 fills them). The start-up entry the memory init calls (InitMemoryStage3, 0x10645120) starts the system. Notes:
- The kernel32 calls are `__declspec(dllimport)` with `/alternatename` (as in controllerdirectinput.cpp).
- GetThreadSlotDefaults and RemoveFiber are `inline` in the .cpp (inlined by their callers, copies annotated).
- The stack-tracking fibers read esp with inline `__asm`.

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x10644EC0 | InitMainThread | - | EQUIVALENT in tree: the push of ConvertThreadToFiber's argument is scheduled one store earlier |
| 0x10645190 | SetThreadValue | - | EQUIVALENT in tree: the original keeps the Enter argument on the stack until after Leave (one `add esp, 8`); ours ends in a jump to Leave (ClearThreadValue, same shape, does end in the jump) |

## debugger.cpp (0x10644760 - 0x10644880): 16 functions

The debugger link of the core module (`code/core/debugger.h`; file and all names guessed): in this build only stubs
(empty DebugInit / DebugShutdown / DebugSignal / DebugWait, getters of globals nothing writes), `CoreName` (returns
"core", the name every allocator and request constructor asks for) and a reference-counted critical section. All
match. DebugHasPending needs `return 0 < gDebugPending;` (unsigned): `!= 0` gives setne, the original cmp / sbb / neg.

## threadslots.cpp (0x106469A0 - 0x10646D06): 16 functions

The user slots of threads and fibers (declared in `code/core/thread.h`; file and all names guessed): eight slots per
Thread record ("data" slots, +0x64) and eight per fiber (+0x14), each set allocated from a bit mask (0x1127A9B4 /
0x1127A9B8); a new slot is set to its value in every existing thread (or every fiber of every thread) and in the
defaults that new threads / fibers copy. Allocation runs under the thread lock once the thread system is up
(the static ...Locked helpers take register arguments). NextThread / NextFiber walk the lists (NextThread(0) takes
the lock, the call returning 0 releases it). All match. The fiber slots are the ones the engine calls
AllocThreadSlot / Get / SetThreadValue (names kept). The ...Locked helpers need `mask = used | bit` stored in one
expression: `used |= bit; ...; mask = used;` keeps the slot pointer in edi.

## heap.cpp (0x1063A6A0 - 0x1063AF72): 34 matched, 5 EQUIVALENT

The heaps (`code/core/heap.h`; file and all names guessed): a table of 0x101 entries (allocator, children, next,
parent; `gHeaps` 0x110BC5A4 points at the static table 0x11276F78), the system heap entry (0x11276F58, index 0x100),
the address map `gHeapMap` (0x11277F98, a RangeMap over a fixed buffer of 0x100 ranges, constructed by a dynamic
initializer elsewhere, so only declared), the current heap per thread in a thread data slot, a failure hook
(user, heap, size, align, flags; engine::OnAllocFail takes those arguments). HeapAlloc / Aligned / Flags / Zero,
the frees by heap and by block, Register / UnregisterHeap (the tree of heaps follows the address ranges),
IsBlockInHeap, the start-up / shut-down. Matching notes:
- Virtual calls on `gHeaps[heap].allocator` need the allocator in a local (the expression form loads it twice).
- The reset of every entry needs the table pointer in a local and an index loop (`heaps[i].children = 0` ...):
  that gives the original's base + 0xC strength reduction; the pointer-walking loop does not. `__forceinline`
  (static) for the helper, plain `inline` is not inlined (loop).
- RegisterHeap's out value of RangeMap::Set is a fresh local per range, copied to the running parent index.
- RangeMap: ~RangeMap is the empty 0x10646150 (the heap map's destructor jumps to it); 0x10646570 (jmp Destroy, no
  callers) is now `RangeMap::Free`. memoryspace.cpp gained its two empty functions (InitMemorySpace /
  ShutdownMemorySpace, 0x10645D50 / 0x10645D60), which InitMemoryStage2 / ShutdownMemoryStage2 call.

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x1063AC00, 0x1063AC30, 0x1063AC60 | Free / FreeAligned / FreeFlags | 71 % | EQUIVALENT in tree: the original loads the allocator into ecx directly, ours into eax plus a copy |
| 0x1063AD50 | UnregisterHeap | 79.5 % | EQUIVALENT in tree: one block (`owner = parent`) placed out of line in the original; the reset store order only comes with a register swap |
| 0x1063AE10 | RegisterHeap | 52 % | EQUIVALENT in tree: loop identical; the entry lives in edi (spilled) in the original, in ebx in ours |

Left alone: 0x1063AF80 / 0x1063AF90 (lower / upper case tests with the character in al, no references: unreferenced
statics are not emitted).
Validation (2026-10-11): free roam in the hybrid, movement works.

## report.cpp (0x1063BC30 - 0x1063C77B): 48 matched, 1 EQUIVALENT

Reports and debug channels (`code/core/report.h`; file and all names guessed): Report / ReportV format the message
(format and arguments, or "Failed condition at %s (%d)" with the expression) and call a dispatcher that is a stub in
this build (answers 2); a table of 0x48-byte debug channels (name, level, flags) under a lock with Add / Find /
Remove and the list setters (names separated by " 	;,[]\"'", default levels for " oldwarning ", " Warning ",
" Severe ", flags of " Pre "); core::DefaultOutputHandler (OutputDebugString and stderr in 256-byte pieces); the
output handler pointer, level, settings; core::IsolatedTask (a task on its own thread, run in place when the thread
does not start within a second). Matching notes:
- The separator test is a `static inline` function: the loops that call it are not rotated, and its out-of-line copy
  (character in al) is still emitted although nothing calls it. Loops written with strchr directly are rotated.
- OnOutput needs its piece loop in a `__forceinline` helper (`if (length == 0) return;` survives there) written as a
  `while` with `&text[i * 0x100]`; the `for` and pointer forms move the loop pointer into memory.
- AddChannel returns `sChannelCount - 1` after `sChannels[sChannelCount++]...`; RemoveChannel reads the count anew
  for the copy and decrements it in place.
- MatchChannel (0x1063BB30) belongs to strings.cpp (it keeps a pointer in edx across MatchWildcard, which only works
  inside the unit); MatchWildcard and MatchChannel return bool (`return c == 0 ? true : false;` gives the original's
  sete without the xor).
- The initialised data (output handler pointer, level, task generation, settings, level names) is only declared.

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x1063BF40 | TokenLength (static) | 98.9 % | EQUIVALENT in tree: one SIB byte ([length + token] against our [token + length]) |

## memory/align.cpp (0x10645300 - 0x1064536D): done

RoundUp / RoundDown / IsRoundedUp (`code/core/memory/align.h`; names and file name guessed): the out-of-line
rounding helpers every allocator unit calls, byte for byte the same as the AlignUp / AlignDown templates that
twowayallocator.cpp instantiates right behind them.

## file/common/filecache.cpp (0x10650DC0 - 0x106511DB): 11 matched, 1 EQUIVALENT

core::FileCache (declared in `code/core/file/file.h`; file and all names guessed): the read cache inside a file. A
file inside another (a Cement library entry) reads through its source file's handle at an offset (summed over the
chain of sources, File slot 32 GetCache); mode 1 reads compressed data: chunks with a 4-byte header (packed size,
unpacked size; packed size 0 means stored) are read granularity-aligned into the buffer and unpacked by 0x10652AA0
(Unpack, another unit, mapped). Open stores the packed size before the mode (the other order swaps the stores).
Validation (2026-10-11): free roam and a teleport (cells streamed) in the hybrid.

| Address | Guess | Best | Notes |
|---|---|---:|---|
| 0x10650ED0 | ReadPacked | 18 % | EQUIVALENT in tree: same steps in the same order; the original keeps this in ebp (spilled) and the read count in memory (a branch where ours has a cmovb) |

## Candidates nearby (leaf functions, not started)

