// Apply config/<VERSION>/symbols.txt to the program: each "mangled = 0xADDRESS ; comment" line becomes the primary
// label at that address (demangled by Ghidra's demangler where possible), and a function is created there if the
// comment says "function" and none exists.
// Usage: python tools/ghidra/ghidra.py run ImportSymbols.java <symbols.txt>
// @category prototype_decomp

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.app.script.GhidraScript;
import ghidra.app.util.demangler.DemangledObject;
import ghidra.app.util.demangler.DemanglerOptions;
import ghidra.app.util.demangler.DemanglerUtil;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;

public class ImportSymbols extends GhidraScript
{
	@Override
	public void run() throws Exception
	{
		String[] args = getScriptArgs();
		List<String> lines = Files.readAllLines(Path.of(args[0]));
		int applied = 0;
		int demangled = 0;
		for (String raw : lines)
		{
			String line = raw;
			String comment = "";
			int semicolon = line.indexOf(';');
			if (semicolon >= 0)
			{
				comment = line.substring(semicolon + 1).trim();
				line = line.substring(0, semicolon);
			}
			line = line.trim();
			if (line.isEmpty())
			{
				continue;
			}
			int equals = line.lastIndexOf('=');
			String name = line.substring(0, equals).trim();
			Address address = toAddr(Long.decode(line.substring(equals + 1).trim()));
			if (comment.contains("function"))
			{
				// Unreferenced (dead) functions were never disassembled by auto-analysis
				ghidra.program.model.listing.Function existing = getFunctionAt(address);
				if (existing != null && existing.getBody().getNumAddresses() <= 1)
				{
					removeFunction(existing);
					existing = null;
				}
				if (existing == null)
				{
					disassemble(address);
					new CreateFunctionCmd(address).applyTo(currentProgram);
				}
			}
			Symbol symbol = createLabel(address, name, true, SourceType.IMPORTED);
			List<DemangledObject> objects = DemanglerUtil.demangle(currentProgram, name, address);
			if (objects != null && !objects.isEmpty() && objects.get(0).applyTo(currentProgram, address, new DemanglerOptions(), monitor))
			{
				demangled++;
			}
			applied++;
		}
		println("applied " + applied + " symbols (" + demangled + " demangled)");
	}
}
