# prototype_recomp

A decompilation of **Prototype** (Radical Entertainment, 2009), PC version: C++ source that rebuilds the game's
engine, `prototypeenginef.dll`, function by function, with the compiler the original was built with (Visual Studio
2005 SP1). The rebuilt DLL is a drop-in replacement for the original in a Steam installation.

> **No game code or assets are included.** You need your own copy of Prototype (Steam, app 10150). Everything derived
> from the original binaries is generated locally from that copy and never committed. Not affiliated with or endorsed
> by Activision or Radical Entertainment.

## Status

Phase 0: foundation. See [docs/plan.md](docs/plan.md) for the strategy and phases and
[docs/decisions.md](docs/decisions.md) for the decisions made so far.

## Target

| Version | File | SHA-256 |
|---|---|---|
| `PROTOPC_2025` (Steam, after the 2025-09-29 patch) | `prototypeenginef.dll` | `d331be205bdde99897952ee88261ab7e63c5c65e36a4660e2a367886a3537071` |
| | `prototypef.exe` | `0cd6834f72b4fd4a762a8ce7c705bfccc94dec58e404f0c0c09299ec42eb7de6` |

## Getting started

```bash
python tools/pin.py fetch --game "D:/SteamLibrary/steamapps/common/Prototype"   # copy + verify into orig/
python tools/ghidra/ghidra.py import                                             # persistent Ghidra database in local/ghidra
```

Requirements: Python 3.11 with `pyyaml`, Ghidra 12.1+ with JDK 21, Visual Studio 2005 SP1 compiler (see
[docs/toolchain.md](docs/toolchain.md)).

## Layout

| Path | Purpose |
|---|---|
| `config/<VERSION>/` | per-build configuration: hashes, symbols, splits |
| `orig/` | your original binaries (ignored by git) |
| `src/`, `include/` | the reconstructed source, mirroring the original tree (`code/core`, `code/pure3d`, `code/proto`, …) |
| `thirdparty/` | upstream third-party source the game links (Lua 5.1) |
| `tools/` | Ghidra scripts, build generator, verification |
| `docs/` | methodology, toolchain, the original's source tree and class hierarchy |
| `build/`, `local/` | generated output (ignored by git) |

## License

GPLv3, see [LICENSE](LICENSE).
