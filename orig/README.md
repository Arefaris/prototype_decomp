# orig/

Put the original game files here; they are never committed. `python tools/pin.py fetch` copies them from a Steam
installation and checks their SHA-256 against `config/<VERSION>/config.yml`:

```
orig/PROTOPC_2025/prototypeenginef.dll
orig/PROTOPC_2025/prototypef.exe
```

Everything derived from them (Ghidra projects, delinked objects, rebuilt DLLs) goes to `build/` or `local/`.
