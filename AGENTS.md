# Repository Guidelines

## Project Structure & Module Organization

This project reconstructs Prototype's PC `prototypeenginef.dll` for byte matching with Visual Studio 2005 SP1.
Keep original translation units intact: one original unit maps to one source file under `src/code/<module>/`.
Module headers live alongside sources; `include/` holds additional headers. `config/PROTOPC_2025/` stores hashes,
symbols, and function metadata. `tools/` contains Python build and analysis utilities; `tests/test_tools.py`
tests them. `thirdparty/` contains upstream code. Read `docs/workflow.md` and `docs/toolchain.md` for setup.
Original binaries, assets, and generated analysis belong only in ignored `orig/`, `build/`, and `local/`.

## Build, Test, and Development Commands

Use Python 3.11 with `pyyaml`, `pefile`, and `capstone`; matching builds require the original compiler and Ninja.
Run commands from the repository root:

- `python tools/pin.py verify` — validate original binaries before analysis or building.
- `python tools/configure.py` — generate Ninja and objdiff configuration.
- `ninja` followed by `ninja check` — compile and compare annotated functions.
- `ninja dll` — relink and verify the hybrid DLL.
- `python tools/re/testcopy.py` — prepare a game copy for runtime testing.
- `python -m unittest discover tests -v` — run synthetic tooling tests without game binaries.
- `ninja report progress` — refresh reports and the README progress bar before committing matches.

## Coding Style & Naming Conventions

Follow `.editorconfig`: UTF-8, LF, final newline, tabs of width four; Markdown/YAML/JSON use two spaces.
Use Allman braces and VS 2005-compatible C++. Preserve known original identifiers; mark inferred names as guesses.
Python uses tabs, `camelCase` functions, and double quotes. No dedicated formatter or linter is configured.
Annotate reconstructed functions with `// FUNCTION: ENGINE 0x1008D450` and update `symbols.txt`.

## Testing Guidelines

Use `unittest`, `test_*.py` files, and `test...` methods; add synthetic regression cases for tooling changes.
There is no numeric coverage threshold. CI runs tooling tests and an MSVC 2022 x86 compilation.
Completed functions must match 100%; document exceptions as `EQUIVALENT` or guarded `NONMATCHING` per
`docs/workflow.md`. Exercise affected features in the test game copy.

## Commit & Pull Request Guidelines

Follow history's scoped summaries, such as `math: spline lengths match` or `docs: progress`.
Describe changed units, addresses, matching status, and validation in PRs; link relevant issues.
Include source, headers, symbol updates, and refreshed progress together.

## Contribution Boundaries

Follow `LICENSE.md`, `LEGAL.md`, and `CLAUDE.md`. Never commit original bytes, disassembly dumps, databases,
game assets, or built binaries. Use your own game copy; no leaked materials, DRM circumvention, content unlocking,
or binary releases.
