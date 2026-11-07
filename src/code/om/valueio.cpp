// The om library's text and binary forms of the plain values (0x105B7A80 - 0x105B8680; names guessed): the children of a
// text value, the stream buffer the binary forms read and write through, and the numbers, booleans and 64-bit values.
#include "code/om/textvalue.h"

#include "code/om/metaproperty.h"
#include "code/om/stream.h"
#include <stdio.h>
#include <stdlib.h>

namespace om
{
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
