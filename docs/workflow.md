# Workflow: decompiling a function or a unit

## Once per machine

```bash
python tools/toolchain/setup_vc8.py <WindowsSDK_Vista_Feb2007Update.iso>   # docs/toolchain.md
python tools/pin.py fetch --game "D:/SteamLibrary/steamapps/common/Prototype"
python tools/ghidra/ghidra.py import                                         # ~10 min
python tools/ghidra/ghidra.py run ExportFunctions.java local/ghidra/functions.tsv --readonly
python tools/function_candidates.py local/ghidra/functions.tsv             # unreferenced functions the analysis missed
python tools/ghidra/ghidra.py run CreateFunctions.java local/ghidra/candidates.txt
python tools/ghidra/ghidra.py run ImportSymbols.java config/PROTOPC_2025/symbols.txt
python tools/re/rea_target.py                                                # copy of the DLL that REA accepts
python tools/configure.py
```

## Parallel work

Each agent (or person) works in its own git worktree: `python tools/worktree.py new <name>` creates
`../protototype_decomp_wt/<name>` on branch `<name>` with `orig/PROTOPC_2025` and `local/` linked in and ninja
configured, so every tool below works there. Commit on the branch only; the main session merges into `main`, resolves
the `symbols.txt` append conflicts, runs `ninja check` and `ninja report progress`, and pushes.
`python tools/worktree.py remove <name>` deletes the tree once merged.

## Per function

1. **Pick** a function: from `config/PROTOPC_2025/functions.tsv`, preferably one whose callees are done or trivial,
   inside a unit you are working on. Find what calls it and what it calls (Ghidra references, `tools/disasm.py`).
2. **Read** it from the Ghidra database:
   `python tools/ghidra/ghidra.py run DecompileRange.java local/decomp/<unit> <start> <end> --readonly` (or
   `@list.txt`, one address per line) writes pseudocode per function in seconds, with our names once
   `ImportSymbols.java` has run; `python tools/disasm.py <addr>` gives the exact instructions. Look up what is known
   about its address (Ghidra bookmarks, or grep `docs/address_index.tsv`). REA works too but re-analyses the DLL in
   every session (~10 min) and cannot open the junctioned `local/` of a worktree.
3. **Name** it: the real name when the binary has one (RTTI class of `this`, vftable slot, assert text, Lua or
   reflection registration string, export); otherwise a descriptive guess marked `guess`. Add it to
   `config/PROTOPC_2025/symbols.txt` with its kind and size:
   `?Name@Class@ns@@QAEXXZ = 0x10123456 ; function size:0x4C | ns::Class::Name (guess)`.
   Name what it calls and reads too, as far as needed for the code to compile.
4. **Write** it in the unit's source file under `src/code/...`, with `// FUNCTION: ENGINE 0x10123456` directly above
   the definition. Declarations go in headers next to the module (`src/code/<module>/...h`).
5. **Match** it: `ninja && ninja check` (objcmp), or objdiff on the unit (`D:/tools/objdiff/objdiff.exe`, project =
   repository root). objcmp also checks the values behind float-constant and string relocations, and that every call or data reference
   it can place through symbols.txt leads where the original's does (a symbol mapped to the wrong address is not a match). Iterate on the source until it
   is identical; `tools/permute.py` tries statement, sum-term and operand orders automatically (mark a copy with
   `// PERMUTE_LINES_BEGIN/END`, `PERMUTE_SUM(...)`, `PERMUTE_MUL(...)`). A function that will not match after real
   effort gets one of:
   - `// EQUIVALENT: <why>`: same operations in the same order, different register or scheduling choices. It is
     compiled and replaces the original in the hybrid DLL (callers in the same unit may rely on its register use),
     but does not count as matched. Floating-point operations must keep the original's order.
   - A function only its own unit calls (a helper, a report) that takes an argument in a register such as `eax`,
     `esi` or `edi` is file-local in the original: declare it `static` (or in an unnamed namespace). VS2005 gives a
     function with internal linkage its own register convention without any link-time code generation; declared
     with external linkage it takes its arguments on the stack, and every caller then differs by one `mov`.
   - `// NONMATCHING: <why>` with the whole definition (signature to closing brace) inside `#ifdef NONMATCHING`:
     not compiled, the original stays. An empty body left outside the `#ifdef` would still be compiled and replace
     the engine's function, so relink refuses it.
6. **Run** it: `ninja dll` (relink + verify), `python tools/vtcheck.py`, `python tools/datacheck.py`, `python tools/namecheck.py`, `python tools/re/testcopy.py`, then
   `OP_ORIGINAL_DIR='D:\PrototypeRecomp' python tools/re/gamectl.py launch` and exercise the feature. vtcheck compares
   the vftables our constructors install with the original's: a constructor matches byte for byte even when our
   vftable misses an override (its address is a relocation), and only the game notices. Every slot's function must
   be mapped in `symbols.txt` to the engine's function of that slot; an unmapped one leads to our own compiled copy
   (an empty stub, a header copy nothing compared), and a pure slot where the engine has a function is a missing
   override. Only `__purecall` in a slot the engine also leaves pure, and the compiler-generated deleting
   destructors, may stay unmapped (`--all` lists them). It also checks the class key:
   declare a type `struct` or `class` exactly as its RTTI name says (`.?AU` / `.?AV` in config/<VERSION>/classes.tsv),
   because the game's `dynamic_cast` compares type names. Look at the characters' poses in the game test, not just
   the coordinates (a wrong key once made every character fall over while `where` looked fine).
7. **Commit**: source, header, `symbols.txt`, and the refreshed progress (`ninja report progress` updates
   `docs/progress.md`, `docs/progress.svg` and the README's bar). Never anything from `orig/`, `build/`, `local/`
   ([LEGAL.md](../LEGAL.md)).

## Checking an EQUIVALENT function (tools/difftest)

An EQUIVALENT function replaces the engine's code in the hybrid DLL, so it must behave exactly like it; objcmp says
nothing about behaviour at 20 % byte similarity. `tools/difftest/difftest.py` replays real states on both:

1. **Capture** real entry states from the game running the ORIGINAL DLL in the test copy (`python tools/re/testcopy.py
   --original`, `OP_ORIGINAL_DIR='D:\PrototypeRecomp' python tools/re/gamectl.py launch 1`), in free roam:
   `OP_ORIGINAL_DIR='D:\PrototypeRecomp' python tools/difftest/difftest.py 0x1071B610 --capture 3 --seconds 60 --play "keys w:2.5,:2"`;
   put the hybrid DLL back afterwards (`python tools/re/testcopy.py`).
   Every requested function gets a jump to its own spin stub (no debugger: the game's main thread is hidden from
   debuggers and an int3 there ends the process), all armed at once in one game session (`difftest.py all 0x1071B610
   --capture 3` arms every EQUIVALENT function plus the extra address). The parked thread's registers and the pages the
   runs need go to `local/difftest/states/<address>/NNN.state` (pages deduplicated in `local/difftest/store/`; never
   committed, they are the game's memory). By default a state is taken live: while the process is frozen the engine's
   function and ours run in the emulator with pages fetched on demand from the process (a per-state `--freeze` budget,
   default 3 s), and only the pages those runs touched plus their `--margin` neighbours are saved, so the freeze drops to
   well under a second; `--full` copies every committed page as before. A later offline run that needs a page the live
   capture did not save reports `INCONCLUSIVE (missing page)`, never guesses. A function shorter than five bytes or with a
   jump into its own first five bytes cannot be parked and is reported. `--play` takes gamectl commands (`keys`,
   `teleport`) to drive the game onto the path; a function whose path does not run (device reset, a district change) stays
   `NOT REACHED` until a state is captured on it.
2. **Replay**: `python tools/difftest/difftest.py 0x1071B610 [--fuzz 200]` runs every state in Unicorn twice, on the engine's
   function and on ours (from the build's object, or `--obj` for another compile), with the engine's own callees running
   as real code on the snapshot; only calls that leave the image (kernel32, d3d9) are answered by stubs and logged. It
   compares faults (a misaligned SSE operand counts as one), the return registers, esp after return, the callee-saved
   registers, every byte written outside the function's own stack frame (final value, and order as a warning), the
   shared memory read, and the call sequence with each callee's arguments (its `ret N`, or the caller's cleanup for cdecl),
   and checks the calling convention statically (`ret N`, registers read before written, the engine's call sites). It then
   perturbs the dwords the engine read to sentinels (0, -1, 1, large) and, with `--fuzz`, mutates them at random, to reach
   the engine's basic blocks the real states miss; what stays unreached is listed.
3. **Read the verdict** (printed and `local/difftest/reports/<address>.txt`): `DIFFERENT` means a real state behaves
   differently (the first finding says where: a fault with the instruction, a byte, a call); `VARIANT-DIFFERENT` means only
   a perturbed state differs (it may be an impossible state: look at it); `SAME` comes with the block coverage on real
   states and with variants. Evidence for keeping `// EQUIVALENT` is `SAME` on several real states with the function's
   blocks covered; random inputs alone prove nothing, and a `SAME` with half the blocks unreached says only that much.
   `python tools/difftest/difftest.py all` runs every EQUIVALENT function that has states.

   Before any state, the test checks the convention statically: a volatile register (ecx, edx) that the engine's
   function never writes and that one of its callers left as engine code reads after the call (or passes on as the
   `this` of the next thiscall) must stay intact in ours too. VS2005 knows which registers a function of its own unit
   touches and its callers rely on it: an EQUIVALENT that changes such a register crashes the game (0x10445A10).
   Such a function is reported `DIFFERENT` even without states.
   What the replay treats as the same (each of these hid real work behind a false `DIFFERENT` or `INCONCLUSIVE`): a
   function-local static or other writable data symbols.txt maps stays at the engine's address in `--unit` runs (map a
   static with its mangled name and its guard bits, as for `SupportingLimb::Update`, so ours and the engine share the
   state); a pointer to a file-level static of ours against the engine's copy compares by the bytes of the object; a
   pointer to a function ours placed itself against the engine's address compares by symbol; calls of the engine to
   small value-computing leaf functions, or to helpers that store nothing outside the frame before the next call (a
   copy into a temporary), which ours did inline, are skipped; a stack cleanup that differs from the engine's does not
   fail when every caller of the function is compiled from our sources too (the hybrid DLL replaces them as well). The
   emulator performs `QueryPerformanceCounter` / `Frequency` (a counter that depends only on the call index),
   `type_info::before`, `__RTDynamicCast` (from the object's RTTI), the `_CI` x87 math intrinsics, and takes code and
   constants a state does not hold from the original image. Direct3D methods are told apart by their vtable slot (read
   off the call site, also through `mov reg, [vtable + slot*4]; call reg`) and the dwords pushed with `this`
   (`externals.COM_METHODS`): their out-parameters get fake interfaces (whose own methods come back as external
   calls), lock buffers or zeroed structures, the same in both runs. Still `INCONCLUSIVE`: states whose run now reaches
   heap pages the capture never saved (capture again).
   To capture what runs while the game starts (the loaders, the device's resources), start the capture first and launch
   the game meanwhile (`difftest.py all --capture 3 --seconds 600 &` then `gamectl.py launch 1`): the entries are armed
   as soon as the engine DLL is mapped.

4. **Timing and trimming** (`python tools/difftest/bench.py`): the same replay without writing reports, with per-function
   and total times and the verdict compared against `local/difftest/reports/*.txt` (snapshotted to
   `local/scratch/difftest-speed/baseline/` with `--copy-baseline` first). `--no-variants` times the replay alone;
   `--profile` prints where each run's time goes. `--trim` replays to record the pages each state's runs touch and writes
   `NNN.trim` states referencing only those pages (plus a margin); it verifies the trimmed state still gives the same
   verdict before you replace the original. `--compact` rewrites `local/difftest/store/pages.bin` to keep only the pages
   the state files still reference and remaps their page tables, shrinking the store from gigabytes to a few MB.

## Matching tips for this compiler

- Options: `/O2 /arch:SSE /fp:fast /GS- /GR /MD /Gy`, no exceptions. Scalar float math is SSE, float returns and
  doubles are x87.
- `__thiscall` methods take `this` in `ecx`, `ret N` pops the arguments; `__cdecl` free functions return with plain
  `ret`.
- Order of independent statements and of struct members changes register allocation; try permutations before
  restructuring.
- The original's calls go through its incremental link table; objdiff and objcmp follow those thunks, so call the
  real function.
- `/Ob1`: only `inline` functions and functions defined in the class body are inlined. A helper defined in the .cpp
  stays a call.
- Within one unit the compiler knows which registers a callee it has compiled clobbers, and callers keep values in
  `edx` or `ecx` across such calls; put functions in the same source file as the original's unit had them.
- Struct copies come out as `mov`; member-by-member float copies as `movss`. Results computed into temporaries and
  stored together look like an inline `Set(x, y, z)`.
- A global or static our unit defines and symbols.txt maps replaces the engine's object: every reference to it, and
  inside it, goes to our copy. Give it the original's initial value (`int gFrame = 1;`, not a bare `int gFrame;`) and
  its size (`; data size:0xN` for anything larger than a word); `tools/datacheck.py` checks both against the original.
- Namespace-scope `const float` constants become data symbols; their values are checked like `__real@` ones.
- String literals are compared with the original's, except `""`: the free-text messages of the original's asserts and
  reports (developers' remarks, names, bug numbers) are not reproduced; write `""` in their place. Expressions, file
  paths and output formats are code and stay.
- The CRT is statically linked into the original, so compiler helpers (`__allmul`, `_CIacos`, `_ftol2`, ...) are
  functions of the image: when the relink reports one unresolved, find it (the call in the original function,
  `tools/disasm.py`) and add it to `symbols.txt` like any function.
- Classes with virtual functions: our object emits their vftables and RTTI itself (the type descriptors need
  `??_7type_info@@6B@`, mapped in `symbols.txt`); a virtual destructor defined in the class body is still emitted as a
  COMDAT function (the vftable needs its address) and gets inlined into the compiler's scalar deleting destructor
  (`??_G...`), which is how the engine's `??_G` functions look. Functions defined in headers cannot carry a
  `// FUNCTION:` annotation yet, so such destructors are not counted.
- A by-value class argument built from a constructor call (`f(Info(0, 1, -1))`) is constructed in place in the
  argument area (`sub esp, N; mov ecx, esp; call ctor`) only when the class declares a copy constructor (a
  declaration is enough, the copy is elided). Without one the compiler builds a temporary and copies it. A call
  that is evaluated before the object in the original (`fld` of a spilled result after the constructor) goes into a
  local first.
- A global store that the original issues after a load (`mov [global], esi` after `mov eax, [esi + 8]`) is usually
  written after that load in the source too; the compiler does not move global stores across member loads.

Findings of the start-up / texture / deform sessions (2026-10-18):

- A chain of `if (a == x) { r = ...; } else if (a == y) { ... }` that falls out of the last test into one `return result;`
  compiles to the engine's blocks of a name-to-enum function; separate `if (...) { ...; return result; }` statements, or
  `||` chains, give another block layout (`dxVertexBuffer`'s usage helper 0x10625BF0).
- A byte-wide bit-field member that the engine reads with `movsx` is declared signed (`int unknown8 : 8;`); unsigned
  gives a mask (`ShaderParameter::unknown8`, dxVertexBuffer::Create).
- Locals that are objects with an address taken (`pure3d::PartRef` built for every use) must be *named* locals to land in
  the engine's frame slots; the same expression written as temporaries compiles to other offsets. Naming them also
  changes how the part address folds (`[idx*0x12c + begin + 0x90]`).
- A frame with many same-typed locals (the 28 stream slot group configurations) keeps the engine's offsets when they
  are declared in the order of their uses. The order the *stores* come out in, and which of the repeated constants stay
  in registers, follows the order the source assigns them in: the pair of equal values finished first gets the free
  register, so move assignments until the first stores match.
- The register parameters of a `static` helper depend on `/arch:SSE2` for the texture unit (`// CFLAGS: /arch:SSE2` on
  the first line) and on the declaration order of its parameters; permute them (tools/permute.py) before blaming the body.
- A float member copied member to member goes through the x87 unit (`fld` / `fstp`) unless the value is also needed in
  an SSE register, in which case the compiler loads it once into xmm and stores from there. `flag = !f()` compiles to
  `sete`; the engine's `flag = true; if (f()) flag = false;` branches come from `if (a && !f()) flag = true; else
  flag = false;`.
- A class whose first non-inline virtual is declared and not defined (`virtual void Slot0();`) emits no vftable, but a
  stack message of a class with only inline functions (`SetLODBiasMessage`) does emit its own one-slot vftable.
- `core::Name<CaseSensitiveKey> n("...", 1)` in its own block before the call puts the constructor in front of the
  arguments' pushes; as a temporary inside the call it comes after them.
