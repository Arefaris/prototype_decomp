// The text form of the om library's values (RTTI names not recovered; names guessed): a text value is a node of a
// document; its children are nodes in an ordered tree, each holding a string (the value) and the tree of its own
// children. The reflection reads a value from the first child and writes one by adding a child.
#ifndef OM_TEXTVALUE_H
#define OM_TEXTVALUE_H

#include "code/om/allocation.h"
#include "code/om/metatype.h"
#include "code/om/string.h"

namespace om
{
	class TextValue;

	// A child of a text value (0x34 bytes)
	class TextNode
	{
	public:
		// 0x105B8C80: a child of the parent that holds a copy of the string
		TextNode(TextValue* parent, const String& newText);
		// 0x102FB420 (the allocation's tag, an empty string)
		static const char* AllocationTag();
		static void* operator new(size_t)
		{
			return om::Allocate(AllocationTag(), 0x34, 4);
		}

		char unknown0[0x10];
		String text;  // 0x10
		TextValue* parent;  // 0x1C
		char unknown20[0x14];
	};

	// The ordered children of a text value
	class TextNodeTree
	{
	public:
		// 0x105B7A80: the first child, null when there is none
		TextNode* First() const;
		// 0x105B7AA0: the child after another, null at the end
		TextNode* Next(TextNode* node) const;
	};

	class TextValue
	{
	public:
		char unknown0[0x20];
		TextNodeTree children;  // 0x20
	};

	// A string is read from the first child
	inline bool ReadText(const TextValue* text, String* value)
	{
		TextNode* node = text->children.First();
		if (node == 0)
		{
			return false;
		}
		*value = node->text;
		return true;
	}
	inline void WriteText(TextValue* text, const String& value)
	{
		new TextNode(text, value);
	}
	// 0x105C12E0: the length, then the characters with their terminator
	bool ReadBinary(BinaryStream* stream, String* value);
	inline bool WriteBinary(BinaryStream* stream, const String& value)
	{
		return false;
	}
}

#endif
