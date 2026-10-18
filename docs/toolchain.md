# Toolchain

## Original compiler (matching builds)

The DLL's Rich header lists 2 141 objects from `cl` 14.00.50727 (product id 0x6e) and the linker 8.00.50727:
Visual Studio 2005 SP1. 28 objects come from VS 2003 (7.1.4035), a third-party library.

Source: the **Windows SDK Update for Windows Vista** (6.1.6000.16384.10, February 2007), whose C++ compilers are,
per Microsoft, those of Visual Studio 2005 SP1 (without `/analyze`). It is still on the Microsoft Download Center:

```
https://download.microsoft.com/download/4/2/6/42684501-9ec5-43dd-9dfe-c8c9dfa6a66f/6.1.6000.16384.10.WindowsSDK_Vista_Feb2007Update_rtm.DVD.Rel.iso
```

`tools/toolchain/setup_vc8.py ISO` extracts the compiler, linker, CRT headers and libraries from that ISO into
`D:/tools/vc8` without installing anything (an administrative `msiexec /a`). It refuses to unpack unless all 30
cabinets and the MSI carry a valid Microsoft Authenticode signature; the 2005 binaries inside are unsigned, as all
of Microsoft's binaries of that time were.

Installed on 2026-10-10 (`D:\tools\vc8\VC\Bin`):

| File | Version | SHA-256 |
|---|---|---|
| ISO | 6.1.6000.16384.10 | `f544c8ec782921a64ffed4b41206aa3d6e16d0cf47c78a5bc26308ae0c2251ea` |
| `cl.exe` | 14.00.50727.762 | `5f6489b0d211b14ae09d93d3fb58a7bce84d070287f008e06416c9baa5564219` |
| `c1xx.dll` | 14.00.50727.762 | `391b9d99bfd3566922623b156e38b7e3f780f2a18fdaa440982ad09961297b0d` |
| `c2.dll` | 14.00.50727.762 | `497d1ffe57f75db8b458167bdea475f3962829e139b355a2672a4ef51c716413` |
| `link.exe` | 8.00.50727.762 | `5c43de3b9a5df4ce76bf8cc923bfe6c9029a7477d1991758466376e977d70517` |
| `lib/msvcrt.lib` | | `9d64b0c4721d2ae327b8d6c041b5a0d2ea72237fe86b5aebd9a93e9f2eeb0049` |

Why SP1 and not RTM: the Rich header only records build 50727, shared by RTM (.42) and SP1 (.762), but the
launcher's manifest asks for `Microsoft.VC80.CRT` 8.0.50727.762, which only SP1 headers produce.

Not in that package: the Windows and DirectX headers. Import libraries for the DLLs the engine uses are generated from
the original's import table instead (exact names and ordinals).

## Compiler options inferred from the binary

Measured over the whole `.text` (7.2 million instructions) on 2026-10-10:

| Evidence | Conclusion |
|---|---|
| 154 423 `movss`, 23 718 `mulss`; 21 `movsd`, 1 `cvttsd2si` | `/arch:SSE` (scalar float in SSE, double stays x87) |
| 37 412 `fld` / 35 528 `fstp`, mostly around calls | x87 is used for float returns and doubles, as `/arch:SSE` does |
| CRT math through `_CIsqrt`, `_CIpow`, `_CIcos`… | intrinsics via x87, consistent with the above |
| No `__CxxFrameHandler3` import, 10 `fs:[0]` uses in total | C++ exceptions off (no `/EHsc`) |
| A stack cookie in only 31 functions | `/GS-` for the engine; the 31 are likely third-party or CRT code |
| 1 239 `push ebp; mov ebp, esp` among ~130 000 functions | `/Oy` (frame pointer omission), i.e. `/O2` or `/Ox` |
| RTTI for 11 808 types, `_purecall` imported | `/GR` |
| `MSVCR80.dll` imports | `/MD` |
| `int3` padding between functions | `/Gy` with incremental linking off; functions aligned by the linker |

**Confirmed by matching (2026-10-10):** `cl /c /O2 /arch:SSE /fp:fast /GS- /GR /MD /Gy` reproduces
`Vector`'s 10:10:10 normal unpacking (`0x107CE990`, 142 bytes) and a matrix rotation reset (`0x107CEAF0`, 56 bytes)
byte for byte. With `/fp:precise` the first one comes out as x87 code with a stack frame, nothing like the original.
**`/Ob1` (2026-10-10, strong evidence):** `Vector::CrossProduct` (0x107CE850) calls `Vector::Perpendicular`
(0x107CE7E0), defined just before it in the same unit, instead of inlining it. With `/Ob2` (the `/O2` default)
VS 2005 inlines it; with `/Ob1` only functions declared `inline` or defined in the class body are inlined, which is
what the original shows. Every match so far holds under `/Ob1`. Still open: `/Oi`, `/GF`, struct packing.

**Per-unit options (2026-10-18):** the DDS part of the texture unit (0x1072AB40 - 0x1072B6D0, pure3d/texture) is not
compiled with the options above: its file-local helpers take their arguments in registers exactly as the engine has them
only with `/arch:SSE2`. Under `/arch:SSE` the compiler passes up to three arguments in volatile registers to a static
function, under `/arch:SSE2` at most two, and the engine's helpers never have more than two (their parameters decide
which: the last two declared parameters are the ones passed in registers, the others go on the stack). A source asks for
another option with a comment among its first lines, `// CFLAGS: /arch:SSE2`; `tools/build.py` (`cflagsFor`),
`tools/configure.py` and `tools/permute.py` substitute it for the default of the same name. The unit has no float code,
so the option changes nothing but the register choices; the rest of the engine stays `/arch:SSE`.

**Inline assembly:** the engine computes sine and cosine with `fsincos` in an inline `__asm` helper that is inlined
into its callers (`src/code/math/sincos.h`); VS 2005 reproduces it exactly.

## Analysis

- Ghidra 12.1.4 (`D:\tools\ghidra_12.1.4_PUBLIC`), JDK 21 (`D:\tools\jdk-21.0.12.1+1`).
- REA 6.2.0 (`rea` MCP server and CLI), Ghidra provider. Its `--snapshot` keeps a small cache of answers, not the
  analysis: each new REA session imports and analyses the DLL again (~10 min). The project's own Ghidra database
  (`tools/ghidra/ghidra.py`, `DecompileRange.java`) is the fast path for reading many functions.

## Modern build

Visual Studio 2022 (17.5), CMake, Ninja.
