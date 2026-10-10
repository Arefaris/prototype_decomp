# Methodology

## The hybrid DLL

The game loads `prototypeenginef.dll`. We build that DLL from two inputs:

1. **The image object**, generated from the user's own copy of the original by `tools/delink/relink.py`. The
   original `.text`, `.rdata` and `.data` become the sections `.o$1`, `.o$2`, `.o$3` of one COFF object. link.exe
   merges them into one output section `.o`, ordered by the suffix and page-aligned, so they keep their original
   addresses (`0x10001000`, `0x10D90000`, `0x10FEB000`) no matter what else is linked.
   - All 418 563 entries of the original's base relocation table become `DIR32` relocations: against the section the
     value points into (416 893), against the `__imp_` symbol of an import (1 667), or `__ImageBase` (3). Import
     libraries are generated from the original's import table (names and ordinals as they are).
   - The original entry point, its 77 exports (same ordinals), its load configuration and resources are kept.
2. **Our objects**, compiled from `src/` with the original's compiler and options (`docs/toolchain.md`).

A function is *replaced* when one of our objects defines a symbol that `config/<VERSION>/symbols.txt` maps to an
address. The relinker then turns every reference to that address in the image into a relocation against the symbol:
absolute pointers from the base relocation table, and `rel32` calls and jumps (`E8`, `E9`, `0F 8x`) found by scanning
`.text`. The original bytes of the function stay in the image as dead code. Every other name of `symbols.txt` is
defined in the image object, so our code can call and use whatever is not reconstructed yet.

`tools/delink/verify.py` checks the result: no byte of the three original sections differs outside relocation sites,
every relocation points at the same target as in the original (or at our replacement), and each redirected `rel32`
reaches our code.

Known limits:

- `rel8` jumps (`EB`, `7x`) into a replaced function cannot be redirected; none are expected (functions are entered
  by calls and long tail jumps) but the relinker does not check yet.
- A replaced function must keep the original's calling convention and side effects; matching guarantees that.
- The original was linked incrementally: about 30 000 five-byte `jmp` thunks at the start of `.text` form its
  incremental link table. They are ordinary code to the relinker.

## Matching

A function is done when its compiled bytes equal the original's, with relocation sites as wildcards
(`tools/objcmp.py`; objdiff from phase 1). Each one carries an annotation directly above its definition:

```cpp
// FUNCTION: ENGINE 0x107CE990
void Vector::UnpackNormal(unsigned int packed)
```

`python tools/build.py` compiles everything, checks every annotation, relinks and verifies.

## Running it

`python tools/re/testcopy.py` makes `D:\PrototypeRecomp`, a copy of the game made of hard links and junctions into
the Steam installation, with the hybrid DLL, the d3d9 proxy and the fast-start options. Then:

```bash
OP_ORIGINAL_DIR='D:\PrototypeRecomp' python tools/re/gamectl.py launch    # title, menus, newest save: free roam
OP_ORIGINAL_DIR='D:\PrototypeRecomp' python tools/re/opprobe.py shot out.png
```

The relinker copies the original's PE time stamp into the hybrid DLL, so tools that recognise the engine build by it
(the proxy's control channel) treat it as the original.

## Names

`symbols.txt` holds mangled names. Names come from the binary where it has them: RTTI (`config/<VERSION>/classes.tsv`,
`rtti.tsv`), exports, assert texts, reflection and Lua registration strings. A name we had to invent is marked
`guess` in its comment and renamed once the binary tells the real one.

## The Ghidra database

`python tools/ghidra/ghidra.py import` creates `local/ghidra/prototype.gpr` and auto-analyses the DLL (about 10
minutes). Scripts in `tools/ghidra/scripts` then run on the saved program in seconds:

| Script | What it does |
|---|---|
| `ExportFunctions.java <out.tsv>` | every function: entry, size, thunk flag, calling convention, name, body ranges |
| `ImportSymbols.java config/<VERSION>/symbols.txt` | our names as primary labels, demangled into signatures; creates dead functions auto-analysis missed |
| `ImportReferenceIndex.java docs/reference/address_index.tsv` | a bookmark at each of the 2 644 addresses the reference notes discuss, naming the notes |

Run `ImportSymbols.java` after every change to `symbols.txt` so the decompiler shows our names.
