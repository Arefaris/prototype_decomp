// Create functions at a list of candidate entry points that auto-analysis missed (unreferenced code the incremental
// linker kept: targets of incremental link thunks, code after int3 padding). One "0xADDRESS" per line.
// A candidate inside an existing function, or one that does not disassemble, is skipped.
// Usage: python tools/ghidra/ghidra.py run CreateFunctions.java <candidates.txt>
// @category prototype_recomp

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;

public class CreateFunctions extends GhidraScript
{
	@Override
	public void run() throws Exception
	{
		List<String> lines = Files.readAllLines(Path.of(getScriptArgs()[0]));
		int created = 0;
		int skipped = 0;
		int failed = 0;
		for (String line : lines)
		{
			line = line.trim();
			if (line.isEmpty() || monitor.isCancelled())
			{
				continue;
			}
			Address address = toAddr(Long.decode(line));
			if (getFunctionContaining(address) != null)
			{
				skipped++;
				continue;
			}
			if (getInstructionAt(address) == null)
			{
				DisassembleCommand disassemble = new DisassembleCommand(address, null, true);
				disassemble.applyTo(currentProgram, monitor);
			}
			if (getInstructionAt(address) == null)
			{
				failed++;
				continue;
			}
			CreateFunctionCmd create = new CreateFunctionCmd(address);
			if (create.applyTo(currentProgram, monitor))
			{
				created++;
			}
			else
			{
				failed++;
			}
			if ((created + failed) % 5000 == 0)
			{
				println("progress: " + created + " created, " + failed + " failed, " + skipped + " skipped");
			}
		}
		println("created " + created + " functions; " + skipped + " inside existing functions; " + failed + " failed");
	}
}
