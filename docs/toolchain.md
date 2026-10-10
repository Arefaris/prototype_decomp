# Toolchain

## Original compiler (matching builds)

The DLL's Rich header lists 2 141 objects from `cl` 14.00.50727 (product id 0x6e) and the linker 8.00.50727:
Visual Studio 2005 SP1. 28 objects come from VS 2003 (7.1.4035), a third-party library.

Status: **not yet installed**. Candidates, in order of preference:

1. Windows SDK Update for Windows Vista (6.0), which ships the SP1 compilers (`cl` 14.00.50727.762).
2. Visual C++ 2005 Express + SP1 (KB926748).

Every binary must carry a valid Microsoft Authenticode signature, and `cl` must report 14.00.50727.762. Hashes of the
installed `cl.exe`, `c1.dll`, `c1xx.dll`, `c2.dll`, `link.exe` and the CRT libraries go here once installed.

## Analysis

- Ghidra 12.1.4 (`D:\tools\ghidra_12.1.4_PUBLIC`), JDK 21 (`D:\tools\jdk-21.0.12.1+1`).
- REA 6.2.0 (`rea` MCP server and CLI), Ghidra provider.

## Modern build

Visual Studio 2022 (17.5), CMake, Ninja.
