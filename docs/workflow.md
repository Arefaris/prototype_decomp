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

## Per function

1. **Pick** a function: from `config/PROTOPC_2025/functions.tsv`, preferably one whose callees are done or trivial,
   inside a unit you are working on. Find what calls it and what it calls (Ghidra, or REA's `procedure_callers`,
   `procedure_callees`).
2. **Read** it: REA `analyze_function` / `procedure_pseudo_code` on `local/re/prototypeenginef_rea.exe` (addresses
   are the DLL's), or Ghidra. Look up the reference notes at its address (Ghidra bookmarks, or grep
   `docs/reference/address_index.tsv`).
3. **Name** it: the real name when the binary has one (RTTI class of `this`, vftable slot, assert text, Lua or
   reflection registration string, export); otherwise a descriptive guess marked `guess`. Add it to
   `config/PROTOPC_2025/symbols.txt` with its kind and size:
   `?Name@Class@ns@@QAEXXZ = 0x10123456 ; function size:0x4C | ns::Class::Name (guess)`.
   Name what it calls and reads too, as far as needed for the code to compile.
4. **Write** it in the unit's source file under `src/code/...`, with `// FUNCTION: ENGINE 0x10123456` directly above
   the definition. Declarations go in headers next to the module (`src/code/<module>/...h`).
5. **Match** it: `ninja && ninja check` (objcmp), or objdiff on the unit (`D:/tools/objdiff/objdiff.exe`, project =
   repository root). Iterate on the source until it is identical; a function that will not match after real effort
   gets `// NONMATCHING: <why>` and stays out of the hybrid DLL.
6. **Run** it: `ninja dll` (relink + verify), `python tools/re/testcopy.py`, then
   `OP_ORIGINAL_DIR='D:\PrototypeRecomp' python tools/re/gamectl.py launch` and exercise the feature.
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
