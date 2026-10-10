# Prototype (2009) — decompilation project plan

> Date: 2026-10-10. Status: plan, awaiting approval.
> Goal: recover source code that compiles into a working binary (a matching decompilation with a recompiled DLL).

## 1. Decision: PC (Steam), not Xbox 360

| Criterion | PC (Steam) | Xbox 360 |
|---|---|---|
| Architecture | x86-32, the same as the development machine: the original can be run, debugged and hooked | PowerPC (Xenon, VMX128); runs only in Xenia, debugging is limited |
| Format | PE; the engine is a separate `prototypeenginef.dll` with a fixed base `0x10000000` and 6 exported entry points | XEX: has to be decrypted/unpacked, code and game in one image |
| Compiler | MSVC 8.0 SP1 (VS 2005, `cl 14.00.50727`), legally obtainable | Xbox 360 XDK is not legally available, a matching decompilation is impossible |
| Symbols | No PDB, but 10 607 RTTI class names, 66 source paths from asserts, 6 named exports, reflection registration strings | Retail XEX has no PDB either; no confirmed advantage in symbols |
| Tools | Ghidra 12.1.4 (already in `D:\tools`), REA (MCP already set up), x32dbg, objdiff/reccmp, MinHook | Ghidra PPC + XEX plugins; weaker |
| Existing tooling | d3d9 proxy, `gamectl.py`, `rea_target.py`, 2 539 named addresses | none |
| Checking the result | our DLL replaces the original in the same game: frame-by-frame A/B | only through an emulator |

**Conclusion:** decompile the PC version. The Xbox 360/PS3 builds may later be useful only as a "name donor" (if
the owner has a legal copy), like the Mac symbols in bw1-decomp.

## 2. Facts about the target (collected today)

**Binaries** (`D:\SteamLibrary\steamapps\common\Prototype`):

| File | Size | SHA-256 | Role |
|---|---|---|---|
| `prototypef.exe` | 2.4 MB (`.text` 8 KB, 96 functions) | `0cd6834f…eb7de6` | launcher: window, `LoadLibrary`, calls the 6 exports; wrapped in Steam DRM (`.bind`) |
| `prototypeenginef.dll` | 20.2 MB (`.text` 14.2 MB) | `d331be20…537071` | **the whole engine and game**; no DRM |

- exe → DLL interface: `EngineInitialize`, `EngineService`, `EngineKeyboardService`, `EngineMouseService`,
  `EngineWindowFocus`, `EngineTerminate` (+ 71 Scaleform GFx exports). Launcher flags: `windowed`, `borderless`,
  `width`, `height`, `exportschema`, `exporthelpfile`, `batchmode` (tool modes — check what `exportschema` dumps).
- Compiler: linker 8.0, CRT `MSVCR80.dll` (`/MD`), Rich header: 2 141 objects from `cl` 14.00.50727 (VS 2005 SP1),
  28 objects from VS 2003 (7.1.4035) — a third-party library. PDB path: `c:\workspace\outrun\proto\prototype\playable\win32\`.
- Aggressive optimisation: only 1 239 `push ebp; mov ebp,esp` prologues among ~133 000 function boundaries (FPO, `/Oy`).
  Estimated size: **~130 000 functions**, a large share of them template instantiations and compiler-generated code.
- RTTI: 10 607 type names: 3 251 ordinary classes + 7 356 template instantiations. By namespace (ordinary classes):
  `proto` 1 626, `engine` 535, `pure3d` 277, global 234 (GFx, Lua, CRT), `fight` 90, `core` 73, `ravenphysics` 56,
  `mgraph` 54, `audio` 54, `content` 52, `om` 47, `MassiveAdClient3` 45, `music` 32, `scaleformp3d` 19, `choreo` 14,
  `crypto` 7, `movie` 6, `container` 4, `compress` 3, `math` 3.
- Source tree (from assert paths): `code\{core,math,container,content,om,choreo,pure3d,ravenphysics,engine,proto}`
  plus `atg\engine\code\tool`. Full list — `docs/original_tree.md` (generated from `strings`).
- Middleware: Scaleform GFx (UI), Lua 5.1, Bink (external `binkw32.dll`), Direct3D 9 + Cg shaders, XInput,
  DirectSound, MassiveAdClient3 (a dead ad network), the in-house physics `ravenphysics` (not Havok).
- **Version:** the Steam patch of 2025-09-29 is installed (PE timestamps 2025-08-14, new Iron Galaxy/Beenox credits).
  Rebuilt with the same VS 2005. The original 2009 build differs. Decision: **the main target is the current 2025
  build** (everyone on Steam has it); the 2009 build is a second configuration later (DepotDownloader by manifest id,
  which an owner of the game is entitled to).
- REA on Windows does not accept DLLs (the `IMAGE_FILE_DLL` flag); the workaround exists already —
  `tools/re/rea_target.py` makes an `.exe` copy with the same image and base. Ghidra's auto-analysis of 20 MB takes
  ≈ 13 min; a **persistent** Ghidra project and REA snapshots are needed, not an ephemeral import every session.

## 3. Strategy: a matching decompilation with a "hybrid" DLL

The models are `isledecomp/isle` and `openblack/bw1-decomp` (matching for the original compiler); the validation
technique is that of `re3` (replacing functions in the live game).

1. **The project's result** is C++ source from which VS 2005 SP1 builds a `prototypeenginef.dll` matching the
   original byte for byte (per function), and which also builds with a modern MSVC 2022 (a second configuration, as
   in devilution: the original compiler for checking, the modern one for development).
2. **The DLL builds from day one** — "delinking": Ghidra + `ghidra-delinker-extension` export the parts of the
   original not yet decompiled as COFF `.obj`; the VS 2005 linker links them with our `.obj` into a complete DLL. At
   0 % decompiled it is the relinked original, which must run the game; every rewritten translation unit displaces
   its original object. That is the "recompilation". If delinking 14 MB of code turns out not to work (checked in
   phase 0), the fallback is runtime hooks (MinHook) from our overlay DLL on top of the original; validation stays the
   same.
3. **Object-level checking** — `objdiff` (the delinker's original `.obj` against ours), progress on decomp.dev;
   `reccmp` optionally for whole-binary reports.
4. **Functional checking in the game** — the `tools/re` scripts (`gamectl.py`, `scenario.py`, the d3d9 proxy) run
   the same scenarios on the original and on the hybrid DLL and compare positions, frames and sound. This catches
   errors that byte comparison misses (data, initialisation order).
5. **Work by translation unit**, not by scattered functions: one original `.cpp` = one task (hints: assert paths,
   RTTI grouping, neighbourhood in `.text`, FID signatures for the CRT/STL).

## 4. Tools

| Task | Tool | Status |
|---|---|---|
| Disassembler/decompiler | Ghidra 12.1.4 (`D:\tools\ghidra_12.1.4_PUBLIC`, JDK 21) — persistent project + headless scripts | have |
| Agent access to pseudocode | REA MCP (`rea` already registered) on the copy from `rea_target.py`; `batch_decompile`, `compare_functions`, snapshot via `close_binary(snapshot_path)` | have |
| Original compiler | Visual Studio 2005 SP1, `cl.exe 14.00.50727.762`, `link.exe 8.00.50727.762`; the Express edition was distributed for free (archive.org / my.visualstudio.com) | **obtain** |
| Modern build | VS 2022 (have), CMake + Ninja (have, Strawberry) | have |
| Delinking the original into `.obj` | `ghidra-delinker-extension` (boricj), COFF x86 output | **spike** |
| Object comparison | `objdiff` (x86 via iced), `objdiff.json` generated by `configure.py` | **install** |
| Whole-binary reports | `reccmp` (`// FUNCTION: ENGINE 0x1008D450` annotations) | optional |
| Removing Steam DRM from the launcher | Steamless (only needed if `prototypef.exe` is rewritten too) | optional |
| Old builds | DepotDownloader (the 2009 build for the second configuration) | later |
| Runtime | x32dbg, MinHook (hook mode), the d3d9 proxy and `gamectl.py` (`tools/re`) | have |
| Automation | Python 3.11, `configure.py` → `build.ninja` (as in bw1-decomp) | to write |

## 5. Repository layout

```
protototype_decomp/
  README.md  CONTRIBUTING.md  LICENSE.md  LEGAL.md
  configure.py                                 # generates build.ninja and objdiff.json, --version PROTOPC_2025
  config/PROTOPC_2025/ config.yml  symbols.txt  splits.txt  build.sha1
  config/PROTOPC_2009/                         # later
  orig/                                        # gitignored: prototypeenginef.dll, prototypef.exe, VS2005 libs
  src/  include/                               # mirror of the original tree:
      core/ container/ math/ compress/ crypto/ om/ content/ choreo/
      pure3d/{pddi,anim,effects,lighting,pass,shadows,texture,…}
      ravenphysics/  engine/  fight/  mgraph/  audio/  music/  proto/  scaleformp3d/  tool/
  thirdparty/   lua-5.1/ (upstream source), stub headers for GFx/Bink (no proprietary code)
  tools/        ghidra/ (headless scripts: RTTI→classes, name import, symbols/splits export, delinking)
                re/ (rea_target.py, d3d9proxy, gamectl.py, scenario.py, vtables.py)
                progress.py  pin.py (SHA-256 check of orig/)  objdiff/
  docs/         methodology.md toolchain.md original_tree.md class_hierarchy.md
  build/ local/                                # gitignored
  .github/workflows/                           # CI: modern build + matching build with a cached toolchain
```

## 6. Phases

**Phase 0 — foundation and spikes (1–2 weeks).**
- Repository, `.gitignore`, `tools/pin.py` with the hashes from §2; a copy in `orig/`.
- Persistent Ghidra project: headless DLL import, auto-analysis, FID for the VS 2005 CRT/STL, the RTTI analyser;
  scripts: class names → `vftable` and virtual destructors, import of the 2 539 known addresses
  (`docs/address_index.tsv`), export of `symbols.txt`. An REA snapshot so that agents do not wait 13 minutes.
- Obtain VS 2005 SP1. Matching spike: `math/src/vector.cpp` (5–10 functions) — find the flags
  (`/O2 /Oy /Ob2 /GR /EHsc /MD`, `/fp:`, `/arch:` — determine from the code), reach 100 % in objdiff.
- Delinking spike: the same unit — delink everything else, relink, the game starts with our DLL.
  **Exit criterion:** the relinked DLL loads the main menu and free roam.

**Phase 1 — pipeline (2–3 weeks).** `configure.py` + ninja, `splits.txt` for the first units, `objdiff.json`,
CI (a modern build on every PR; a matching build with the toolchain from a private cache), a progress report by
namespace, A/B scenarios from `scenario.py`. A "one translation unit" task template for agents:
REA `batch_decompile` of the unit's functions → draft → `cl` → objdiff → iterations → A/B in the game.

**Phase 2 — base libraries.** `core` (allocators, files, Cement/RCF, controllers), `container`, `math`, `compress`,
`crypto`, `om` + `content` (the object model and reflection — the key to the field names of all data). In parallel,
**headers** for all 3 251 classes (layouts from RTTI, constructors, vtables). Useful even before the decompilation is
complete: modders and any future port need the headers and symbols.

**Phase 3 — `pure3d`** (pddi/DX9, textures, animation, effects, lighting, shadows, passes), `movie`, `audio`, `music`.
**Phase 4 — `ravenphysics`.**
**Phase 5 — `engine`** (gameobject/behaviour/message, world streaming, fmv, frontend + Lua bindings, Scaleform glue).
**Phase 6 — `fight`/`mgraph`/`choreo`** (fight trees, the motion graph) and `proto` (1 626 game classes).
**Phase 7 — third-party code.** Lua 5.1 — rebuild upstream with the same flags (expected to match); Scaleform GFx —
proprietary, stays a delinked blob from the user's copy (decision — §7); MassiveAdClient3 — a stub (a dead service;
the first "modern improvement").
**Phase 8 — release and modernisation.** A 100 % own DLL under VS 2005 and VS 2022; then an improvements branch
(resolutions, FOV, no FPS cap — what PrototypeFix does with patches today).

Phases 2–6 are years of work for one person; the value appears from phase 0 on (a working hybrid DLL, symbols,
headers). The order within phases follows the call graph bottom-up and the number of callers.

## 7. Risks and open decisions

1. **Scaleform GFx** inside the DLL is a proprietary SDK. Options: leave it a blob forever (the DLL only builds for
   owners of a copy anyway) or later replace it with an open Flash runtime. Postponed to phase 7.
2. **The VS 2005 SP1 toolchain** has to be obtained and pinned (hashes of `cl.exe`/`link.exe`/the `msvcrt` libraries
   in `docs/toolchain.md`); a private cache for CI.
3. **Delinking** 14 MB of x86 with ~130 000 functions and data relocations is an untested load; the phase 0 spike
   decides between delinking and hooks.
4. **Two builds (2009/2025).** If Steam updates the game again, the addresses will shift: `pin.py` is mandatory, the
   copy in `orig/` is the source of truth, not the Steam folder.
5. **Scale.** Without automation (agents per translation unit, headers generated from RTTI) the project will not
   reach phase 6. The phase 1 tools are a condition, not an option.

## 8. First steps after approval

1. `git init`, the layout from §5, `.gitignore`, `tools/pin.py`, copying `orig/`.
2. `docs/original_tree.md` and `docs/class_hierarchy.md` from `strings`/RTTI (scripts in `tools/ghidra/`).
3. Headless Ghidra project + naming scripts; import of the known addresses; an REA snapshot.
4. Install VS 2005 SP1; `docs/toolchain.md`.
5. Matching spike on `math/src/vector.cpp`; delinking and relinking spike; start the game with our DLL.
6. After the spikes, record the "delink or hooks" decision in `docs/methodology.md` and start phase 1.
