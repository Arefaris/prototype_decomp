# prototype_decomp — project instructions

Matching decompilation of Prototype (2009) PC: reconstruct C++ source that Visual Studio 2005 SP1 compiles into a
drop-in `prototypeenginef.dll`.

## Rules

- **LICENSE.md and LEGAL.md are binding for every change:** no original files or derived bytes in git, no binary releases, no
  commercial use, no unlocking of sold content, no DRM circumvention, no leaked material.
- **Progress bar:** run `ninja report progress` before committing new matches (README bar, docs/progress.*).

- **Never commit original bytes:** no binaries, delinked objects, Ghidra databases, disassembly dumps or game assets.
  They live in `orig/`, `build/` and `local/` (all ignored). `tools/pin.py verify` must pass before any tool trusts `orig/`.
- **Addresses** are virtual addresses of `PROTOPC_2025` (image base `0x10000000`), written `0x1008D450`.
- **Source mirrors the original tree** recovered from assert paths and RTTI (`docs/original_tree.md`):
  `src/code/<module>/...`. One original translation unit = one source file = one unit in the build.
- **Annotations:** each reconstructed function carries `// FUNCTION: ENGINE 0x1008D450` above it (reccmp style),
  plus `// STUB`/`// GLOBAL`/`// VTABLE` as needed.
- **Matching first:** a function counts as done when objdiff shows 100 % against the original object. Otherwise
  `// EQUIVALENT: reason` (same operations in the same order, compiled into the hybrid DLL, not counted) or
  `// NONMATCHING: reason` with the body inside `#ifdef NONMATCHING` (not compiled). See `docs/workflow.md`.
- **REA:** analyse `local/re/prototypeenginef_rea.exe` (`python tools/re/rea_target.py`), never the game's file.
- **Parallel agents work in their own worktrees:** `python tools/worktree.py new <name>` (branch `<name>`,
  `../protototype_decomp_wt/<name>`, `orig/` and `local/` linked in). Agents commit on their branch and never push or
  touch the main tree; the main session merges the branches into `main`.

## Code style

Tabs, Allman braces. Original identifiers where known (from RTTI, asserts, reflection strings); otherwise the
original's apparent conventions (`PascalCase` classes, `camelCase` methods, `m` members are guesses until confirmed).
Python tools: tabs, `camelCase` functions, double quotes.

## Commands

```bash
python tools/pin.py verify
python tools/ghidra/ghidra.py import
python tools/ghidra/ghidra.py run <Script.java> [args]
```
