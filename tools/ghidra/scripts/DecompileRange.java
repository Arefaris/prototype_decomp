// Decompile functions to text for reading (never for committing): every function whose entry lies in [start, end),
// or the functions listed one address per line in a file. Writes one file per function: <outdir>/<ADDRESS>.c
// Usage: python tools/ghidra/ghidra.py run DecompileRange.java <outdir> <start> <end> --readonly
//        python tools/ghidra/ghidra.py run DecompileRange.java <outdir> @<list.txt> --readonly
// @category prototype_decomp

import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;

public class DecompileRange extends GhidraScript
{
	@Override
	public void run() throws Exception
	{
		String[] args = getScriptArgs();
		Path outDir = Path.of(args[0]);
		Files.createDirectories(outDir);
		List<Function> functions = new ArrayList<>();
		if (args[1].startsWith("@"))
		{
			for (String line : Files.readAllLines(Path.of(args[1].substring(1))))
			{
				line = line.trim();
				if (!line.isEmpty())
				{
					Function f = getFunctionAt(toAddr(Long.decode(line)));
					if (f != null)
					{
						functions.add(f);
					}
				}
			}
		}
		else
		{
			Address start = toAddr(Long.decode(args[1]));
			Address end = toAddr(Long.decode(args[2]));
			for (Function f : currentProgram.getFunctionManager().getFunctions(start, true))
			{
				if (f.getEntryPoint().compareTo(end) >= 0)
				{
					break;
				}
				functions.add(f);
			}
		}
		DecompInterface decompiler = new DecompInterface();
		decompiler.openProgram(currentProgram);
		for (Function f : functions)
		{
			DecompileResults results = decompiler.decompileFunction(f, 60, monitor);
			String text = results.decompileCompleted() ? results.getDecompiledFunction().getC() : "// decompilation failed: " + results.getErrorMessage();
			String name = String.format("%08X.c", f.getEntryPoint().getOffset());
			try (PrintWriter out = new PrintWriter(outDir.resolve(name).toFile(), "UTF-8"))
			{
				out.printf("// 0x%08X %s size %d%n", f.getEntryPoint().getOffset(), f.getName(true), f.getBody().getNumAddresses());
				out.print(text);
			}
		}
		decompiler.dispose();
		println("decompiled " + functions.size() + " functions to " + outDir);
	}
}
