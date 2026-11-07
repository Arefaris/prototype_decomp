// The document of the om library's text format "Text Tree V1" (names guessed): the root of a tree of text nodes that is
// read from a text and written back as nested quoted names, `"name"[ ... ]`, with \n and \\ escaped in the names.
#ifndef OM_TEXTTREE_H
#define OM_TEXTTREE_H

#include "code/om/metatype.h"
#include "code/om/textscanner.h"
#include "code/om/textvalue.h"

namespace om
{
	class TextTree : public TextNode
	{
	public:
		// 0x105B8DF0: a root named "root"
		TextTree();
		~TextTree()
		{
			DeleteChildren();
		}
		// 0x105B8880 / 0x105B8930: the name with line ends and backslashes written as \n and \\, and back
		String Escape(const String& source);
		String Unescape(const String& source);
		// 0x105B8E30: reads the nodes up to the closing bracket as children of the parent
		bool ReadNodes(TextValue* parent, TextScanner* scanner);
		// 0x105B8FB0: writes a node and all below it
		bool WriteNode(TextValue* node, Stream* out);
		// 0x105B90D0 / 0x105B9120: reads a document (the context has the streams the errors go to)
		bool Read(TextScanner* scanner, StreamContext* context);
		bool Read(Stream* stream, StreamContext* context);
		// 0x105B9160: writes the document
		bool Write(Stream* out, StreamContext* context);
	};
}

#endif
