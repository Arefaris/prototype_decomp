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
   - `// NONMATCHING: <why>` with the body inside `#ifdef NONMATCHING`: not compiled, the original stays.
6. **Run** it: `ninja dll` (relink + verify), `python tools/vtcheck.py`, `python tools/re/testcopy.py`, then
   `OP_ORIGINAL_DIR='D:\PrototypeRecomp' python tools/re/gamectl.py launch` and exercise the feature. vtcheck compares
   the vftables our constructors install with the original's: a constructor matches byte for byte even when our
   vftable misses an override (its address is a relocation), and only the game notices. It also checks the class key:
   declare a type `struct` or `class` exactly as its RTTI name says (`.?AU` / `.?AV` in config/<VERSION>/classes.tsv),
   because the game's `dynamic_cast` compares type names. Look at the characters' poses in the game test, not just
   the coordinates (a wrong key once made every character fall over while `where` looked fine).
7. **Commit**: source, header, `symbols.txt`, and the refreshed progress (`ninja report progress` updates
   `docs/progress.md`, `docs/progress.svg` and the README's bar). Never anything from `orig/`, `build/`, `local/`
   ([LEGAL.md](../LEGAL.md)).

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
