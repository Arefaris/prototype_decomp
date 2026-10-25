// The text form of the om library's values (RTTI names not recovered; names guessed): a text value is a node of a
// document that has a name (a string) and the tree of its children. A string value is written as a node with a child
// that is named after the string; the reflection reads it from the first child. Arrays are a node "Items" with a node
// "Item" for each element.
#ifndef OM_TEXTVALUE_H
#define OM_TEXTVALUE_H

#include "code/om/allocation.h"
#include "code/om/metatype.h"
#include "code/om/string.h"

namespace om
{
	class TextValue;

	// How a node's name is compared with the key that is looked for (0x105B8BF0: the key against the node's name)
	int CompareNodeName(const String* key, const TextValue* node);
	typedef int (*NodeCompare)(const String* key, const TextValue* node);

	// The ordered children of a text value (the root and the head's own node: 0x14 bytes)
	class TextNodeTree
	{
	public:
		// 0x105B7A80: the first child, null when there is none
		TextValue* First() const;
		// 0x105B7AA0: the child after another, null at the end
		TextValue* Next(TextValue* node) const;
		// 0x102FB430: the first child that compares equal to the key, null when there is none
		TextValue* FindFirst(NodeCompare compare, const String* key) const;

		void* root;
		char nil[0x10];
	};

	class TextValue
	{
	public:
		// The first child with the name
		TextValue* FindChild(const char* name) const
		{
			String key(name, false);
			return children.FindFirst(CompareNodeName, &key);
		}

		// True when the node has the name
		bool HasName(const char* name) const
		{
			String other(name, false);
			return text == other;
		}

		char link[0x10];
		String text;  // 0x10: the name
		TextValue* parent;  // 0x1C
		TextNodeTree children;  // 0x20
	};

	// A node made as a child of a parent (0x34 bytes)
	class TextNode : public TextValue
	{
	public:
		// 0x105B8C80: a child of the parent that holds a copy of the string
		TextNode(TextValue* newParent, const String& name);
		// 0x102FB420 (the allocation's tag, an empty string; the engine calls it, once for the allocations of a function)
		__declspec(noinline) static const char* AllocationTag()
		{
			return "";
		}
		static void* operator new(size_t)
		{
			return om::Allocate(AllocationTag(), 0x34, 4);
		}
	};

	// A string is read from the first child
	inline bool ReadText(const TextValue* text, String* value)
	{
		TextValue* node = text->children.First();
		if (node != 0)
		{
			*value = node->text;
			return true;
		}
		return false;
	}
	inline void WriteText(TextValue* text, const String& value)
	{
		new TextNode(text, value);
	}
	// 0x105C12E0: the length, then the characters with their terminator
	bool ReadBinary(BinaryStream* stream, String* value);
	// The length (the number's writer is declared with the properties'), then the characters with their terminator
	bool WriteBinary(BinaryStream* stream, unsigned int value);
	inline bool WriteBinary(BinaryStream* stream, const String& value)
	{
		if (WriteBinary(stream, (unsigned int)value.length))
		{
			unsigned int length = value.length;
			if (stream->buffer->Write(value.GetText(), length + 1))
			{
				return true;
			}
		}
		return false;
	}
}

#endif
