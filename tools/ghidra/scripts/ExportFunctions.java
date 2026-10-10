// Export every function of the program: entry, name, size, body ranges, thunk flag, calling convention.
// Usage: python tools/ghidra/ghidra.py run ExportFunctions.java <output.tsv> --readonly
// @category prototype_recomp

import java.io.PrintWriter;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;

public class ExportFunctions extends GhidraScript
{
	@Override
	public void run() throws Exception
	{
		String[] args = getScriptArgs();
		String output = args.length > 0 ? args[0] : "functions.tsv";
		int count = 0;
		try (PrintWriter out = new PrintWriter(output, "UTF-8"))
		{
			out.println("entry\tsize\tthunk\tconvention\tname\tranges");
			FunctionIterator functions = currentProgram.getFunctionManager().getFunctions(true);
			while (functions.hasNext() && !monitor.isCancelled())
			{
				Function f = functions.next();
				if (f.isExternal())
				{
					continue;
				}
				StringBuilder ranges = new StringBuilder();
				for (AddressRange r : f.getBody())
				{
					if (ranges.length() > 0)
					{
						ranges.append(',');
					}
					ranges.append(String.format("%08X-%08X", r.getMinAddress().getOffset(), r.getMaxAddress().getOffset() + 1));
				}
				out.printf("%08X\t%d\t%d\t%s\t%s\t%s%n", f.getEntryPoint().getOffset(), f.getBody().getNumAddresses(),
					f.isThunk() ? 1 : 0, f.getCallingConventionName(), f.getName(true), ranges);
				count++;
			}
		}
		println("exported " + count + " functions to " + output);
	}
}
