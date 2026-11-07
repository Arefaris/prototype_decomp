// The text form of the om library's values (RTTI names not recovered; names guessed): a text value is a node of a
// document that has a name (a string) and the tree of its children. A string value is written as a node with a child
// that is named after the string; the reflection reads it from the first child. Arrays are a node "Items" with a node
// "Item" for each element.
#ifndef OM_TEXTVALUE_H
#define OM_TEXTVALUE_H

#include "code/om/allocation.h"
#include "code/om/metatype.h"
#include "code/om/string.h"
#include "code/om/tree.h"

namespace om
{
	class TextValue;

	// How a node's name is compared with the key that is looked for (0x105B8BF0: the key against the node's name)
	int CompareNodeName(const String* key, const TextValue* node);
	typedef int (*NodeCompare)(const String* key, const TextValue* node);
	// 0x105B8B50 / 0x105B8BA0: two strings against each other, two nodes' names against each other (names guessed)
	int CompareStrings(const String* first, const String* second);
	int CompareNodes(const TextValue* first, const TextValue* second);
	typedef int (*NodesCompare)(const TextValue* first, const TextValue* second);

	// The ordered children of a text value (the root and the head's own node: 0x14 bytes)
	class TextNodeTree
	{
	public:
		// 0x105B78F0
		TextNodeTree();
		// 0x105B89F0: enters a child under its name (the mode is 1 for a node that may stand beside another of the same name)
		bool Insert(TextValue* node, NodesCompare compare, bool mode);
		// 0x105B7A80: the first child, null when there is none
		TextValue* First() const;
		// 0x105B7AA0: the child after another, null at the end
		TextValue* Next(TextValue* node) const;
		// 0x102FB430: the first child that compares equal to the key, null when there is none
		TextValue* FindFirst(NodeCompare compare, const String* key) const;
		// 0x105B7AF0: the child before another, null at the start
		TextValue* Previous(TextValue* node) const;
		// 0x105B7650 / 0x105B76A0 (names guessed, the tree is the standard red-black tree)
		void RotateLeft(TreeNode* node);
		void RotateRight(TreeNode* node);
		// 0x105B7700 / 0x105B7720 / 0x105B7740: whether a node is the left child, the right child, the root (the first two do not look at the tree)
		bool IsLeftChild(TreeNode* node);
		bool IsRightChild(TreeNode* node);
		bool IsRoot(TreeNode* node);
		// 0x105B7760: the node after another, the head's own node at the end
		TreeNode* Successor(TreeNode* node);
		// 0x105B77A0: restores the colors after a black node was taken out
		void FixAfterErase(TreeNode* node);
		// 0x105B7920: takes the node out
		void Erase(TreeNode* node);
		// 0x105B7B40
		void ResetRoot();
		// 0x105B7910 (defined in a unit of its own: the engine calls it, it is not expanded)
		~TextNodeTree();

		TreeNode* root;
		TreeNode nil;
	};

	class TextValue
	{
	public:
		TextValue(TextValue* newParent, const String& name) :
			text(name),
			parent(newParent)
		{
		}
		explicit TextValue(TextValue* newParent) :
			parent(newParent)
		{
		}
		// 0x105B8810: takes the children, then the node out of its parent's tree
		~TextValue();
		static void operator delete(void* memory)
		{
			om::Release(memory, 0x34, 4);
		}
		// 0x105B8DB0: deletes all the children
		void DeleteChildren();
		// 0x105B8CC0: renames the node (it stays in the order of its parent's children)
		void SetName(const String& name);
		// 0x105B8D00: moves the node below another one
		void SetParent(TextValue* newParent);
		// 0x105B8D40: a copy of the node and all below it, as a child of the parent
		TextValue* Clone(TextValue* newParent);
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

		TreeNode link;
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
		// 0x105B8C40: a child of the parent without a name
		explicit TextNode(TextValue* newParent);
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
