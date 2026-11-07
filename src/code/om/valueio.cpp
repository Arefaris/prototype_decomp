// The om library's text and binary forms of the plain values (0x105B7A80 - 0x105B8680; names guessed): the children of a
// text value, the stream buffer the binary forms read and write through, and the numbers, booleans and 64-bit values.
#include "code/om/texttree.h"

#include "code/om/metaproperty.h"
#include "code/om/stream.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace om
{
	// 0x112767D4: what the words of a stream context are made of
	extern int gStreamContextObject;

	// FUNCTION: ENGINE 0x105B7A80
	TextValue* TextNodeTree::First() const
	{
		TreeNode* node = root;
		if (node == &nil)
		{
			return 0;
		}
		while (node->left != &nil)
		{
			node = node->left;
		}
		return (TextValue*)node;
	}

	// FUNCTION: ENGINE 0x105B7AA0
	TextValue* TextNodeTree::Next(TextValue* node) const
	{
		TreeNode* end = (TreeNode*)&nil;
		TreeNode* next = ((TreeNode*)node)->right;
		if (next != end)
		{
			while (next->left != end)
			{
				next = next->left;
			}
		}
		else
		{
			next = ((TreeNode*)node)->parent;
			while (next != end && (TreeNode*)node == next->right)
			{
				node = (TextValue*)next;
				next = next->parent;
			}
		}
		return next != end ? (TextValue*)next : 0;
	}

	// FUNCTION: ENGINE 0x105B7650
	void TextNodeTree::RotateLeft(TreeNode* node)
	{
		TreeNode* promoted = node->right;
		node->right = promoted->left;
		if (promoted->left != &nil)
		{
			promoted->left->parent = node;
		}
		promoted->parent = node->parent;
		if (node->parent == &nil)
		{
			root = promoted;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = promoted;
		}
		else
		{
			node->parent->right = promoted;
		}
		promoted->left = node;
		node->parent = promoted;
	}

	// FUNCTION: ENGINE 0x105B76A0
	void TextNodeTree::RotateRight(TreeNode* node)
	{
		TreeNode* promoted = node->left;
		node->left = promoted->right;
		if (promoted->right != &nil)
		{
			promoted->right->parent = node;
		}
		promoted->parent = node->parent;
		if (node->parent == &nil)
		{
			root = promoted;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = promoted;
		}
		else
		{
			node->parent->right = promoted;
		}
		promoted->right = node;
		node->parent = promoted;
	}

	// FUNCTION: ENGINE 0x105B7700
	bool TextNodeTree::IsLeftChild(TreeNode* node)
	{
		TreeNode* parent = node->parent;
		if (parent != 0)
		{
			return parent->left == node;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B7720
	bool TextNodeTree::IsRightChild(TreeNode* node)
	{
		TreeNode* parent = node->parent;
		if (parent != 0)
		{
			return parent->right == node;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B7740
	bool TextNodeTree::IsRoot(TreeNode* node)
	{
		return node->parent == &nil;
	}

	// FUNCTION: ENGINE 0x105B7760
	TreeNode* TextNodeTree::Successor(TreeNode* node)
	{
		TreeNode* end = &nil;
		TreeNode* next = node->right;
		if (next != end)
		{
			while (next->left != end)
			{
				next = next->left;
			}
		}
		else
		{
			next = node->parent;
			while (next != end && node == next->right)
			{
				node = next;
				next = next->parent;
			}
		}
		return next;
	}

	// FUNCTION: ENGINE 0x105B77A0
	void TextNodeTree::FixAfterErase(TreeNode* node)
	{
		while (node != root && node->color == 0)
		{
			if (node == node->parent->left)
			{
				TreeNode* sibling = node->parent->right;
				if (sibling->color == 1)
				{
					sibling->color = 0;
					node->parent->color = 1;
					RotateLeft(node->parent);
					sibling = node->parent->right;
				}
				if (sibling->left->color == 0 && sibling->right->color == 0)
				{
					sibling->color = 1;
					node = node->parent;
				}
				else
				{
					if (sibling->right->color == 0)
					{
						sibling->left->color = 0;
						sibling->color = 1;
						RotateRight(sibling);
						sibling = node->parent->right;
					}
					sibling->color = node->parent->color;
					node->parent->color = 0;
					sibling->right->color = 0;
					RotateLeft(node->parent);
					node = root;
				}
			}
			else
			{
				TreeNode* sibling = node->parent->left;
				if (sibling->color == 1)
				{
					sibling->color = 0;
					node->parent->color = 1;
					RotateRight(node->parent);
					sibling = node->parent->left;
				}
				if (sibling->right->color == 0 && sibling->left->color == 0)
				{
					sibling->color = 1;
					node = node->parent;
				}
				else
				{
					if (sibling->left->color == 0)
					{
						sibling->right->color = 0;
						sibling->color = 1;
						RotateLeft(sibling);
						sibling = node->parent->left;
					}
					sibling->color = node->parent->color;
					node->parent->color = 0;
					sibling->left->color = 0;
					RotateRight(node->parent);
					node = root;
				}
			}
		}
		node->color = 0;
	}

	// FUNCTION: ENGINE 0x105B7920
	void TextNodeTree::Erase(TreeNode* node)
	{
		TreeNode* end = &nil;
		TreeNode* removed;
		if (node->left == end || node->right == end)
		{
			removed = node;
		}
		else
		{
			removed = Successor(node);
		}
		TreeNode* child = removed->left != end ? removed->left : removed->right;
		child->parent = removed->parent;
		TreeNode* parent = removed->parent;
		if (parent == end)
		{
			root = child;
		}
		else if (removed == parent->left)
		{
			parent->left = child;
		}
		else
		{
			parent->right = child;
		}
		int blackRemoved = removed->color == 0;
		if (removed != node)
		{
			removed->parent = node->parent;
			removed->left = node->left;
			removed->right = node->right;
			removed->color = node->color;
			parent = removed->parent;
			if (parent != end)
			{
				if (parent->left == node)
				{
					parent->left = removed;
				}
				else
				{
					parent->right = removed;
				}
			}
			else
			{
				root = removed;
			}
			if (removed->left != end)
			{
				removed->left->parent = removed;
			}
			if (removed->right->parent != end)
			{
				removed->right->parent = removed;
			}
		}
		if (blackRemoved)
		{
			FixAfterErase(child);
		}
	}

	// FUNCTION: ENGINE 0x105B7AF0
	TextValue* TextNodeTree::Previous(TextValue* node) const
	{
		TreeNode* end = (TreeNode*)&nil;
		TreeNode* previous = ((TreeNode*)node)->left;
		if (previous != end)
		{
			while (previous->right != end)
			{
				previous = previous->right;
			}
		}
		else
		{
			previous = ((TreeNode*)node)->parent;
			while (previous != end && (TreeNode*)node == previous->left)
			{
				node = (TextValue*)previous;
				previous = previous->parent;
			}
		}
		return previous != end ? (TextValue*)previous : 0;
	}

	// FUNCTION: ENGINE 0x105B7B40
	void TextNodeTree::ResetRoot()
	{
		root = &nil;
	}

	// FUNCTION: ENGINE 0x105B78F0
	TextNodeTree::TextNodeTree()
	{
		TreeNode* end = &nil;
		nil.left = end;
		nil.right = end;
		nil.parent = end;
		nil.color = 0;
		root = end;
	}

	// FUNCTION: ENGINE 0x105B8C40
	TextNode::TextNode(TextValue* newParent) :
		TextValue(newParent)
	{
		if (parent != 0)
		{
			parent->children.Insert(this, CompareNodes, true);
		}
	}

	// FUNCTION: ENGINE 0x105B8810
	TextValue::~TextValue()
	{
		DeleteChildren();
		if (parent != 0)
		{
			parent->children.Erase(&link);
		}
	}

	// FUNCTION: ENGINE 0x105B8CC0
	void TextValue::SetName(const String& name)
	{
		if (parent != 0)
		{
			parent->children.Erase(&link);
		}
		text = name;
		if (parent != 0)
		{
			parent->children.Insert(this, CompareNodes, true);
		}
	}

	// FUNCTION: ENGINE 0x105B8D00
	void TextValue::SetParent(TextValue* newParent)
	{
		if (parent != 0)
		{
			parent->children.Erase(&link);
		}
		parent = newParent;
		if (newParent != 0)
		{
			newParent->children.Insert(this, CompareNodes, true);
		}
	}

	// FUNCTION: ENGINE 0x105B8D40
	TextValue* TextValue::Clone(TextValue* newParent)
	{
		TextValue* copy = new TextNode(newParent, text);
		TextValue* child = children.First();
		if (child != 0)
		{
			do
			{
				child->Clone(copy);
				child = child->parent->children.Next(child);
			}
			while (child != 0);
		}
		return copy;
	}

	// FUNCTION: ENGINE 0x105B8DB0
	void TextValue::DeleteChildren()
	{
		if (children.First() != 0)
		{
			do
			{
				TextValue* child = children.First();
				delete child;
			}
			while (children.First() != 0);
		}
	}

	// FUNCTION: ENGINE 0x105B8DF0
	TextTree::TextTree() :
		TextNode(0, String::Wrap("root"))
	{
	}

	// FUNCTION: ENGINE 0x105B8880
	String TextTree::Escape(const String& source)
	{
		String result(0, (unsigned int)source.length);
		unsigned int count = source.length;
		for (unsigned int index = 0; index < count; index++)
		{
			char character = source.GetTextOutOfLine()[index];
			if (character == '\n')
			{
				String text("\\n", false);
				result += text;
			}
			else if (character == '\\')
			{
				String text("\\\\", false);
				result += text;
			}
			else
			{
				result.Append(character);
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105B8930
	String TextTree::Unescape(const String& source)
	{
		String result(0, source.length + 1u);
		unsigned int count = source.length;
		for (unsigned int index = 0; index < count; index++)
		{
			char character = source.GetTextOutOfLine()[index];
			if (character == '\\')
			{
				index++;
				if (index < count)
				{
					const char* text = source.GetTextOutOfLine();
					if (text[index] == 'n')
					{
						result.Append('\n');
					}
					else if (text[index] == '\\')
					{
						result.Append('\\');
					}
				}
			}
			else
			{
				result.Append(character);
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105B8E30
	bool TextTree::ReadNodes(TextValue* parent, TextScanner* scanner)
	{
		String name;
		char buffer[0x100];
		SkipWhitespace(scanner);
		while (scanner->position < scanner->length)
		{
			if (SkipAndConsume(scanner, "]"))
			{
				break;
			}
			if (!ReadQuoted(scanner, buffer, 0x100))
			{
				return false;
			}
			{
				String raw(buffer, 1);
				name = Unescape(raw);
			}
			TextNode* node = new TextNode(parent, name);
			if (SkipAndConsume(scanner, "["))
			{
				if (node == 0)
				{
					node = new TextNode(parent, name);
				}
				if (!ReadNodes(node, scanner))
				{
					return false;
				}
			}
			SkipWhitespace(scanner);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105B8FB0
	bool TextTree::WriteNode(TextValue* node, Stream* out)
	{
		String escaped = Escape(node->text);
		bool ok = StreamPrintf(out, "\"%s\"", escaped.GetText());
		TextValue* child = node->children.First();
		if (child != 0)
		{
			if (ok && StreamPrintf(out, "["))
			{
				ok = true;
			}
			else
			{
				ok = false;
			}
			if (child->children.First() != 0)
			{
				if (ok && StreamPrintf(out, "\n"))
				{
					ok = true;
				}
				else
				{
					ok = false;
				}
			}
			((TextOutStream*)out)->indent++;
			do
			{
				if (ok && WriteNode(child, out))
				{
					ok = true;
				}
				else
				{
					ok = false;
				}
				child = child->parent->children.Next(child);
			}
			while (child != 0);
			((TextOutStream*)out)->indent--;
			if (ok && StreamPrintf(out, "]\n"))
			{
				ok = true;
			}
			else
			{
				ok = false;
			}
		}
		return ok;
	}

	// FUNCTION: ENGINE 0x105B90D0
	bool TextTree::Read(TextScanner* scanner, StreamContext* context)
	{
		SkipAndConsume(scanner, "\"Text Tree V1\"");
		bool opened = SkipAndConsume(scanner, "[");
		bool read = ReadNodes(this, scanner);
		if (opened && read)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B9120
	bool TextTree::Read(Stream* stream, StreamContext* context)
	{
		TextScanner scanner(stream);
		return Read(&scanner, context);
	}

	// FUNCTION: ENGINE 0x105B9160
	bool TextTree::Write(Stream* out, StreamContext* context)
	{
		TextOutStream stream(out);
		bool ok = true;
		TextValue* node = children.First();
		StreamPrintf(&stream, "\"Text Tree V1\"[\n");
		stream.indent++;
		for (; node != 0; node = node->parent->children.Next(node))
		{
			ok = WriteNode(node, &stream);
		}
		stream.indent--;
		StreamPrintf(&stream, "]\n");
		return ok;
	}

	// FUNCTION: ENGINE 0x105B89F0
	bool TextNodeTree::Insert(TextValue* node, NodesCompare compare, bool mode)
	{
		TreeNode* inserted = (TreeNode*)node;
		TreeNode* parent = &nil;
		TreeNode* current = root;
		if (current != &nil)
		{
			do
			{
				parent = current;
				int result = compare(node, (TextValue*)current);
				if (mode && result == 0)
				{
					goto right;
				}
				if (result < 0)
				{
					current = current->left;
				}
				else
				{
					if (result <= 0)
					{
						return false;
					}
				right:
					current = current->right;
				}
			}
			while (current != &nil);
		}
		inserted->parent = parent;
		if (parent == &nil)
		{
			root = inserted;
		}
		else if (compare(node, (TextValue*)parent) < 0)
		{
			parent->left = inserted;
		}
		else
		{
			parent->right = inserted;
		}
		inserted->left = &nil;
		inserted->right = &nil;
		inserted->color = 1;
		TreeNode* fixed = inserted;
		while (fixed != root && fixed->parent->color == 1)
		{
			if (fixed->parent == fixed->parent->parent->left)
			{
				TreeNode* uncle = fixed->parent->parent->right;
				if (uncle->color == 1)
				{
					fixed->parent->color = 0;
					uncle->color = 0;
					fixed->parent->parent->color = 1;
					fixed = fixed->parent->parent;
				}
				else
				{
					if (fixed == fixed->parent->right)
					{
						fixed = fixed->parent;
						RotateLeft(fixed);
					}
					fixed->parent->color = 0;
					fixed->parent->parent->color = 1;
					RotateRight(fixed->parent->parent);
				}
			}
			else
			{
				TreeNode* uncle = fixed->parent->parent->left;
				if (uncle->color == 1)
				{
					fixed->parent->color = 0;
					uncle->color = 0;
					fixed->parent->parent->color = 1;
					fixed = fixed->parent->parent;
				}
				else
				{
					if (fixed == fixed->parent->left)
					{
						fixed = fixed->parent;
						RotateRight(fixed);
					}
					fixed->parent->color = 0;
					fixed->parent->parent->color = 1;
					RotateLeft(fixed->parent->parent);
				}
			}
		}
		root->color = 0;
		return true;
	}

	// FUNCTION: ENGINE 0x105B8BF0
	int CompareNodeName(const String* key, const TextValue* node)
	{
		return strcmp(key->GetText(), node->text.GetText());
	}

	// FUNCTION: ENGINE 0x105B8B50
	int CompareStrings(const String* first, const String* second)
	{
		return strcmp(first->GetText(), second->GetText());
	}

	// FUNCTION: ENGINE 0x105B8BA0
	int CompareNodes(const TextValue* first, const TextValue* second)
	{
		return strcmp(first->text.GetText(), second->text.GetText());
	}

	// FUNCTION: ENGINE 0x105B8C80
	TextNode::TextNode(TextValue* newParent, const String& name) :
		TextValue(newParent, name)
	{
		if (parent != 0)
		{
			parent->children.Insert(this, CompareNodes, true);
		}
	}

	// FUNCTION: ENGINE 0x105BFF30
	void* GetStreamContextObject()
	{
		return &gStreamContextObject;
	}

	// FUNCTION: ENGINE 0x105B7B50
	StreamBuffer::StreamBuffer(Stream* newStream, int nativeOrder) :
		stream(newStream),
		swap(nativeOrder == 0)
	{
	}

	// FUNCTION: ENGINE 0x105B7C60
	bool StreamBuffer::ReadRaw(void* data, unsigned int size)
	{
		return stream->Read(data, size);
	}

	// FUNCTION: ENGINE 0x105B7CF0
	bool ReadText(const TextValue* text, bool* value)
	{
		bool result = true;
		TextValue* node = text->children.First();
		if (node != 0)
		{
			if (node->text == "true")
			{
				*value = true;
			}
			else if (node->text == "false")
			{
				*value = false;
			}
		}
		else
		{
			result = false;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105B7D50
	bool ReadText(const TextValue* text, char* value)
	{
		bool result = true;
		TextValue* node = text->children.First();
		if (node != 0)
		{
			const char* digits = node->text.GetTextOutOfLine();
			unsigned int number = 0;
			sscanf_s(digits, "%u", &number, 4);
			*value = (char)number;
		}
		else
		{
			result = false;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105B7DA0
	bool ReadBinary(BinaryStream* stream, char* value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Read(value, 1);
	}

	// FUNCTION: ENGINE 0x105B7DC0
	bool WriteBinary(BinaryStream* stream, char value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Write(&value, 1);
	}

	// FUNCTION: ENGINE 0x105B7DE0
	bool ReadText(const TextValue* text, unsigned char* value)
	{
		bool result = true;
		TextValue* node = text->children.First();
		if (node != 0)
		{
			const char* digits = node->text.GetTextOutOfLine();
			unsigned int number = 0;
			sscanf_s(digits, "%u", &number, 4);
			*value = (unsigned char)number;
		}
		else
		{
			result = false;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105B7E30
	bool ReadBinary(BinaryStream* stream, unsigned char* value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Read(value, 1);
	}

	// FUNCTION: ENGINE 0x105B7E50
	bool WriteBinary(BinaryStream* stream, unsigned char value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Write(&value, 1);
	}

	// FUNCTION: ENGINE 0x105B7E70
	bool ReadText(const TextValue* text, int* value)
	{
		bool result = true;
		TextValue* node = text->children.First();
		if (node != 0)
		{
			*value = atoi(node->text.GetTextOutOfLine());
		}
		else
		{
			result = false;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105B7EB0
	bool ReadBinary(BinaryStream* stream, int* value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Read(value, 4);
	}

	// FUNCTION: ENGINE 0x105B7ED0
	bool WriteBinary(BinaryStream* stream, int value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Write(&value, 4);
	}

	// FUNCTION: ENGINE 0x105B7EF0
	// NONMATCHING: the engine keeps the zero of the failure path in esi (28.6 %)
#ifdef NONMATCHING
	bool ReadText(const TextValue* text, short* value)
	{
		short zero = 0;
		bool result = true;
		TextValue* node = text->children.First();
		if (node != 0)
		{
			*value = (short)atoi(node->text.GetTextOutOfLine());
			return result;
		}
		*value = zero;
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x105B7F30
	bool ReadBinary(BinaryStream* stream, short* value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Read(value, 2);
	}

	// FUNCTION: ENGINE 0x105B7F50
	bool WriteBinary(BinaryStream* stream, short value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Write(&value, 2);
	}

	// FUNCTION: ENGINE 0x105B7F70
	// NONMATCHING: the engine tests and stores the low half of the number through registers, ours folds the zero (60.2 %)
#ifdef NONMATCHING
	bool ReadText(const TextValue* text, unsigned short* value)
	{
		bool result = true;
		TextValue* node = text->children.First();
		if (node != 0)
		{
			const char* digits = node->text.GetTextOutOfLine();
			unsigned int number = 0;
			sscanf_s(digits, "%u", &number, 4);
			unsigned int narrowed = (unsigned short)number;
			if (narrowed != 0)
			{
				return false;
			}
			*value = number;
		}
		else
		{
			result = false;
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x105B7FD0
	bool ReadBinary(BinaryStream* stream, unsigned short* value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Read(value, 2);
	}

	// FUNCTION: ENGINE 0x105B7FF0
	bool WriteBinary(BinaryStream* stream, unsigned short value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Write(&value, 2);
	}

	// FUNCTION: ENGINE 0x105B8010
	bool ReadText(const TextValue* text, unsigned int* value)
	{
		TextValue* node = text->children.First();
		if (node == 0)
		{
			return false;
		}
		const char* digits = node->text.GetTextOutOfLine();
		unsigned int number = 0;
		sscanf_s(digits, "%u", &number, 4);
		*value = number;
		return true;
	}

	// FUNCTION: ENGINE 0x105B8060
	bool ReadBinary(BinaryStream* stream, unsigned int* value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Read(value, 4);
	}

	// FUNCTION: ENGINE 0x105B8080
	bool WriteBinary(BinaryStream* stream, unsigned int value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Write(&value, 4);
	}

	// FUNCTION: ENGINE 0x105B80A0
	bool ReadText(const TextValue* text, float* value)
	{
		TextValue* node = text->children.First();
		if (node == 0)
		{
			return false;
		}
		*value = (float)atof(node->text.GetTextOutOfLine());
		return true;
	}

	// FUNCTION: ENGINE 0x105B80D0
	bool WriteBinary(BinaryStream* stream, float value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Write(&value, 4);
	}

	// FUNCTION: ENGINE 0x105B80F0
	bool ReadBinary(BinaryStream* stream, float* value)
	{
		StreamBuffer* buffer = stream->buffer;
		return buffer->Read(value, 4);
	}

	// FUNCTION: ENGINE 0x105B8110
	// NONMATCHING: the temporaries' construction is scheduled differently (50.4 %)
#ifdef NONMATCHING
	void WriteText(TextValue* text, bool value)
	{
		new TextNode(text, value ? String("true", false) : String("false", false));
	}
#endif

	// FUNCTION: ENGINE 0x105B81A0
	void WriteText(TextValue* text, char value)
	{
		new TextNode(text, Format(0, "%d", (int)value));
	}

	// FUNCTION: ENGINE 0x105B8210
	void WriteText(TextValue* text, unsigned char value)
	{
		new TextNode(text, Format(0, "%d", (int)value));
	}

	// FUNCTION: ENGINE 0x105B8280
	void WriteText(TextValue* text, int value)
	{
		new TextNode(text, Format(0, "%d", value));
	}

	// FUNCTION: ENGINE 0x105B82F0
	void WriteText(TextValue* text, short value)
	{
		new TextNode(text, Format(0, "%d", (int)value));
	}

	// FUNCTION: ENGINE 0x105B8360
	void WriteText(TextValue* text, unsigned short value)
	{
		new TextNode(text, Format(0, "%u", (unsigned int)value));
	}

	// FUNCTION: ENGINE 0x105B83D0
	void WriteText(TextValue* text, unsigned int value)
	{
		new TextNode(text, Format(0, "%u", value));
	}

	// 0x105B7CB0: takes trailing zeros of a number's text away (the string in esi)
	static void TrimTrailingZeros(String& number)
	{
		char* characters = number.GetWritableText();
		int length = number.length;
		while (length > 2 && characters[length - 1] == '0' && characters[length - 2] != '.')
		{
			characters[length - 1] = 0;
			length--;
		}
		number.SetLength(length);
	}

	// FUNCTION: ENGINE 0x105B8440
	void WriteText(TextValue* text, float value)
	{
		String number = Format(0, "%f", (double)value);
		TrimTrailingZeros(number);
		new TextNode(text, number);
	}

#ifdef NONMATCHING
	// 0x105B7B90: reverses the bytes of a value (the start in ecx, the size in eax)
	static void ReverseBytes(int size, char* data)
	{
		char* last = data + size - 1;
		while (data < last)
		{
			char first = *last;
			char second = *data;
			*data = first;
			*last = second;
			data++;
			last--;
		}
	}

	// FUNCTION: ENGINE 0x105B7BC0
	// NONMATCHING: the engine's static ReverseBytes takes the data in ecx and the size in eax, ours the other way (96.6 %)
	bool StreamBuffer::Read(void* data, int size)
	{
		if (stream->Read(data, size))
		{
			if (swap)
			{
				ReverseBytes(size, (char*)data);
			}
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B7C00
	// NONMATCHING: same register assignment of ReverseBytes (93.9 %)
	bool StreamBuffer::Write(const void* data, int size)
	{
		if (swap)
		{
			ReverseBytes(size, (char*)data);
			bool result = stream->Write(data, size);
			ReverseBytes(size, (char*)data);
			return result;
		}
		return stream->Write(data, size);
	}
#endif
}
