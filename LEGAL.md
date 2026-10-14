# Legal position and risk policy

This project reconstructs, by decompilation, source code that compiles into `prototypeenginef.dll` from **Prototype**
(Radical Entertainment / Activision, 2009). It is not affiliated with, authorised or endorsed by Activision,
Radical Entertainment or any of their partners. *Prototype* and related names are trademarks of their owners and are
used here only to say which game the code works with.

This document is a policy, not legal advice. Decompiling may be lawful for interoperability in some jurisdictions
(e.g. EU Directive 2009/24/EC, Art. 6), but **publishing reconstructed code that reproduces a protected program can
still infringe copyright**, and a licence written by the project does not give anyone rights the copyright holders
have not granted. Nobody has granted this project such rights. The rules below exist to keep the project as far as
possible from the uses rights holders object to.

## Model

The policy follows projects that have stayed available for years without action from the rights holder, notably the
Sonic decompilations RSDKv3 / RSDKv4 / RSDKv5 (public since January 2021): they ship no game data, require the user's
own purchased copy, forbid commercial use and the distribution of original assets, credit the original authors, and
keep paid content off by default.

## Rules

1. **Own copy required.** Nothing here runs without the user's own legally obtained copy of Prototype (Steam app
   10150). Buy the game; this project is useless without it, by design.
2. **No original files, ever.** The repository never contains the game's executables, DLLs, archives (`.rcf`),
   assets, shaders, movies, audio, save files, or anything extracted or derived byte-wise from them: no delinked
   objects, Ghidra databases, disassembly dumps, screenshots of the game's content beyond small working images kept
   in the ignored `local/`. `orig/`, `build/` and `local/` are git-ignored; `tools/pin.py` copies the user's own files
   into `orig/` on their machine only.
3. **No binary releases.** The hybrid DLL is built on the user's machine from the user's copy
   (`tools/delink/relink.py`). Built DLLs, installers or patched game folders are not published or shared, by the
   project or as part of contributions.
4. **No commercial use.** The project, its source and anything built from it are not to be sold, bundled with paid
   products, placed behind paywalls, or used to advertise commercial services ([LICENSE.md](LICENSE.md),
   condition 1).
5. **No content unlocking.** Nothing in this project enables content that is otherwise sold separately, region- or
   platform-exclusive, removed by the publisher, or locked by the game's own rules; builds behave like the original
   unless the user changes them. The PC release has no paid add-ons today; if any appear (for example in a
   re-release), they stay disabled by default and are not part of this project's code paths.
6. **No circumvention.** The project does not remove, bypass or reimplement copy protection or platform DRM. The
   engine DLL carries none; the launcher's Steam DRM is left alone and the original launcher is used as it is.
7. **Credit.** Radical Entertainment wrote the engine and the game; the reconstructed code is their design.
   Every distribution of this source keeps the attribution in this file and in the README.
8. **No impersonation.** No Activision or Radical logos, box art or branding in the repository, its page or its
   builds. The project's name describes what it is compatible with and does not suggest official status.
9. **Takedown.** Any request from Activision or another rights holder is answered promptly. The default response
   to a credible request is to comply (make the repository private, remove the requested material, or archive the
   project) and then discuss.
10. **Clean contributions.** Contributors work only from their own copy of the game and the public tools listed in
    `docs/toolchain.md`. No leaked source code, leaked SDKs (including console development kits), confidential
    documents or code under non-disclosure from any source; contributions that look derived from such material are
    rejected. The compiler comes from a free Microsoft download (`tools/toolchain/setup_vc8.py`).

## Licence

The repository is under its own [prototype_decomp License v1](LICENSE.md), modelled on the RSDKv3 / RSDKv4
decompilation licenses: use and distribution in source form for non-commercial purposes only; no original files and
no binaries containing the original program; sold content off by default in any build; attribution to Radical
Entertainment and Activision; no trademark rights; forks under the same license; no warranty. The rules above are
therefore licence conditions, not only project policy. The license covers what the contributors wrote; it gives no
rights in the original program, which nobody here can grant.

## Why the age of the game does not help

Copyright in a 2009 game runs for decades. A 1993 game is not free either; the difference between projects lies in
how they behave (no assets, no sales, no unlocked paid content, credit, quick compliance), not in the age of the
work. Prototype is also a franchise its owner is actively selling and reportedly developing, which raises the risk
compared with dormant titles.
