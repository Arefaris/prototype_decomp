// Bookmark every address that docs/reference mentions (docs/reference/address_index.tsv): category "reference",
// text = the notes and the first line naming it.
// Usage: python tools/ghidra/ghidra.py run ImportReferenceIndex.java <address_index.tsv>
// @category prototype_recomp

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.BookmarkManager;

public class ImportReferenceIndex extends GhidraScript
{
	@Override
	public void run() throws Exception
	{
		List<String> lines = Files.readAllLines(Path.of(getScriptArgs()[0]));
		BookmarkManager bookmarks = currentProgram.getBookmarkManager();
		int count = 0;
		for (String line : lines.subList(1, lines.size()))
		{
			String[] fields = line.split("\t", 3);
			if (fields.length < 3)
			{
				continue;
			}
			Address address = toAddr(Long.decode(fields[0]));
			bookmarks.setBookmark(address, "Note", "reference", fields[1] + ": " + fields[2]);
			count++;
		}
		println("bookmarked " + count + " addresses");
	}
}
