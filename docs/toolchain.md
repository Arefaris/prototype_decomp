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

Still to be settled by the matching spike: `/fp:fast` vs `/fp:precise`, `/Ob2`, `/Oi`, `/GF`, struct packing.

## Analysis

- Ghidra 12.1.4 (`D:\tools\ghidra_12.1.4_PUBLIC`), JDK 21 (`D:\tools\jdk-21.0.12.1+1`).
- REA 6.2.0 (`rea` MCP server and CLI), Ghidra provider.

## Modern build

Visual Studio 2022 (17.5), CMake, Ninja.
