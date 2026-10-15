# Contributing

Thanks for helping reconstruct Prototype's engine. The project is a **matching** decompilation: a function is done
when the C++ you write compiles, with the original compiler and options, into the same machine code as the original.
Read [LEGAL.md](LEGAL.md) first; its rules are conditions of the [license](LICENSE.md) and apply to every
contribution.

## Ground rules

- **Own copy only.** Work from your own legally obtained copy of Prototype (Steam, app 10150, the build after the
  2025-09-29 patch; `tools/pin.py` checks the hashes).
- **Never commit original bytes.** No executables, DLLs, delinked objects, Ghidra databases, disassembly or
  decompiler dumps, game assets, shaders or screenshots of game content. They belong in `orig/`, `build/` and
  `local/`, which git ignores. Hand-written code that compiles to the original is the contribution; pasted
  disassembly or raw decompiler output is not.
- **No leaked material.** No leaked source, SDKs (including console kits), confidential documents or code under NDA.
  Contributions that look derived from such material are rejected.
- **No binaries.** Do not publish or attach built DLLs, patched game folders or installers, in pull requests or
  anywhere else.
- **No developer messages.** The free-text messages of the original's asserts and reports (remarks, names, bug
  numbers) are written as `""`; the comparison accepts that.
- **No DRM work and no content unlocking** (LEGAL.md rules 5 and 6).
- **Non-commercial.** By contributing you agree that your contribution is distributed under the project license.

## Setup (once per machine)

Requirements: Windows, Python 3.11 with `pyyaml`, `pefile` and `capstone`, Ninja, Ghidra 12.1+ with JDK 21, and the
Visual Studio 2005 SP1 compiler, which `tools/toolchain/setup_vc8.py` extracts from a free Microsoft SDK download
([docs/toolchain.md](docs/toolchain.md)). Ghidra reads the original (the project keeps a
persistent database with scripts); objdiff is
optional.

```bash
python tools/toolchain/setup_vc8.py <WindowsSDK_Vista_Feb2007Update.iso>
python tools/pin.py fetch --game "D:/SteamLibrary/steamapps/common/Prototype"
python tools/ghidra/ghidra.py import
python tools/configure.py
ninja
```

The full list, including the Ghidra exports, is in [docs/workflow.md](docs/workflow.md).

## Picking work

- Work by **translation unit**: one `.cpp` of the original tree (`docs/original_tree.md`) is one source file under
  `src/code/...` and one unit in the build.
- The worklists (`docs/core_worklist.md`, `docs/engine_worklist.md`, `docs/math_worklist.md`) say which units are
  done, which are in progress, and what blocks the rest. Open an issue or a draft pull request before starting a
  large unit, so two people do not take the same one.
- `config/PROTOPC_2025/functions.tsv` lists the functions; `docs/address_index.tsv` notes what is known about many
  addresses.

## Writing a function

The step-by-step guide is [docs/workflow.md](docs/workflow.md); in short:

1. Read the function from the Ghidra database (`DecompileRange.java`, `tools/disasm.py`) and find its real name (RTTI, vftable slot, assert text, reflection or Lua
   registration string, export). An invented name is marked `guess` in `symbols.txt`.
2. Add it to `config/PROTOPC_2025/symbols.txt`
   (`?Name@Class@ns@@QAEXXZ = 0x10123456 ; function size:0x4C | ns::Class::Name`).
3. Write it in the unit's source file with `// FUNCTION: ENGINE 0x10123456` directly above the definition.
4. Match it: `ninja && ninja check`, or objdiff on the unit. If it will not match after real effort, mark it
   `// EQUIVALENT: <why>` (same operations in the same order; compiled, not counted) or `// NONMATCHING: <why>` with
   the body inside `#ifdef NONMATCHING` (not compiled).
5. Declare types `struct` or `class` exactly as their RTTI names say (`.?AU` / `.?AV` in
   `config/PROTOPC_2025/classes.tsv`): the game's `dynamic_cast` compares type names.

## Before opening a pull request

All of these must pass:

```bash
python tools/configure.py
ninja
python tools/build.py --version PROTOPC_2025 --no-link --no-compile   # every annotated function: N/N match
ninja dll                                                             # relink the hybrid DLL
python tools/delink/verify.py --version PROTOPC_2025                  # IDENTICAL
python tools/vtcheck.py                                               # 0 problems
python tools/datacheck.py                                             # 0 problems (our mapped globals start like the engine's)
python tools/namecheck.py                                             # 0 (symbols.txt spells our symbols as the compiler does)
ninja report progress                                                 # refresh the README bar and docs/progress.*
```

Then run the game with the hybrid DLL and exercise what you changed:

```bash
python tools/re/testcopy.py --copy D:/PrototypeTest
OP_ORIGINAL_DIR='D:\PrototypeTest' python tools/re/gamectl.py launch
```

`testcopy.py` builds a copy of your installation out of hard links with the new DLL in it; your Steam folder is not
touched. Watch the characters, not just coordinates: a wrong class key once made every character fall over while
the positions looked fine.

## Code style

- Tabs, Allman braces. Original identifiers where the binary gives them; otherwise the original's apparent
  conventions (`PascalCase` types and methods, `camelCase` locals and members).
- Comments say what the code is for, in English. Note anything non-obvious you learned about matching in the
  worklist of the module.
- Python tools: tabs, `camelCase` functions, double quotes.

## Commits and pull requests

- One unit (or a coherent part of one) per pull request.
- Commit messages: `<module>: <what> (<N> functions match[, <M> equivalent])`, for example
  `engine: physics/supportinglimb.cpp part 2 (6 functions match, 7 equivalent)`.
- Include the source, headers, `symbols.txt` and the refreshed progress files; nothing from `orig/`, `build/` or
  `local/`.
- Describe how you tested in the game.

## Working in parallel

Each person or agent can work in a separate git worktree: `python tools/worktree.py new <name>` creates
`../protototype_decomp_wt/<name>` on branch `<name>` with `orig/` and `local/` linked in. `symbols.txt` conflicts
are usually appends from both sides: keep both.
