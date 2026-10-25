// The streams the content library's meta types read and write through (the unit 0x105FBF70 - 0x105FCC70; the file name
// is guessed): the binary reader and writer over a byte stream, the text reader that cuts it into tokens and the text
// writer that indents.
#include "code/content/metastream.h"
#include "code/core/hash.h"
#include "code/core/strings.h"
#include <stdarg.h>
#include <new>
#include <stdio.h>
#include <string.h>

namespace core
{
	// 0x1063B960 / 0x1063B990
	int VSNPrintfResult(char* destination, int size, const char* format, va_list arguments);
	int SNPrintfCount(char* destination, int size, const char* format, ...);
}

namespace content
{
	// FUNCTION: ENGINE 0x105FBF70
	BinaryReader::BinaryReader(ByteStream* newStream, bool newSwap)
	{
		stream = newStream;
		swap = newSwap;
	}

	// FUNCTION: ENGINE 0x105FBF90
	bool BinaryReader::GetSwap() const
	{
		return swap;
	}

	// FUNCTION: ENGINE 0x105FBFA0
	bool BinaryReader::SetSwap(bool newSwap)
	{
		bool previous = swap;
		swap = newSwap;
		return previous;
	}

	// FUNCTION: ENGINE 0x105FBFB0
	BinaryWriter::BinaryWriter(ByteStream* newStream, bool newSwap)
	{
		stream = newStream;
		swap = newSwap;
	}

	// FUNCTION: ENGINE 0x105FBFD0
	bool BinaryWriter::GetSwap() const
	{
		return swap;
	}

	// FUNCTION: ENGINE 0x105FBFE0
	bool BinaryWriter::SetSwap(bool newSwap)
	{
		bool previous = swap;
		swap = newSwap;
		return previous;
	}

	// FUNCTION: ENGINE 0x105FBFF0
	static void SwapItems(unsigned char* data, unsigned int count, int size)
	{
		if (size != 1)
		{
			for (unsigned int i = 0; i < count; i++)
			{
				unsigned char* low = data + i * size;
				unsigned char* high = low + size - 1;
				while (low < high)
				{
					unsigned char temp = *low;
					*low = *high;
					*high = temp;
					low++;
					high--;
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x105FC030
	void BinaryReader::Read(void* destination, int count, int size)
	{
		stream->Transfer(destination, count * size);
		if (swap)
		{
			SwapItems((unsigned char*)destination, count, size);
		}
	}

	// FUNCTION: ENGINE 0x105FC070
	void BinaryWriter::Write(const void* source, int count, int size)
	{
		if (!swap)
		{
			stream->Transfer((void*)source, count * size);
			return;
		}
		unsigned int length = count * size;
		unsigned char* copy = new unsigned char[length];
		memcpy(copy, source, length);
		SwapItems(copy, count, size);
		stream->Transfer(copy, length);
		delete[] copy;
	}

	// FUNCTION: ENGINE 0x105FC0F0
	TextReadStream::TextReadStream(ByteStream* newStream, bool newFlag, const char* newName)
	{
		stream = newStream;
		line = 1;
		flag = newFlag;
		errorText[0] = 0;
		name[0] = 0;
		if (newName != 0)
		{
			core::StrNCpy(name, newName, 0x100u);
		}
	}

	// FUNCTION: ENGINE 0x105FC140
	int TextReadStream::GetLine()
	{
		return line;
	}

	// FUNCTION: ENGINE 0x105FC150
	void TextReadStream::SetLine(int newLine)
	{
		line = newLine;
	}

	// FUNCTION: ENGINE 0x105FC160
	void TextReadStream::SetFlag(bool newFlag)
	{
		flag = newFlag;
	}

	// FUNCTION: ENGINE 0x105FC170
	bool TextReadStream::GetFlag() const
	{
		return flag;
	}

	// FUNCTION: ENGINE 0x105FC180
	unsigned int TextReadStream::GetPosition()
	{
		return stream->GetPosition();
	}

	// FUNCTION: ENGINE 0x105FC190
	void TextReadStream::SetPosition(unsigned int position)
	{
		stream->SetPosition(position);
	}

	// FUNCTION: ENGINE 0x105FC1A0
	unsigned int TextReadStream::GetSize()
	{
		return stream->GetSize();
	}

	// FUNCTION: ENGINE 0x105FC1B0
	void TextReadStream::Error(const char* format, ...)
	{
		va_list arguments;
		va_start(arguments, format);
		core::VSNPrintfResult(errorText, 0x200, format, arguments);
	}

	// FUNCTION: ENGINE 0x105FC1E0
	const char* TextReadStream::GetName()
	{
		return name;
	}

	// FUNCTION: ENGINE 0x105FC1F0
	// EQUIVALENT: the same reads, comparisons and branches in the same order; the engine copies the stream pointer through ecx before the first call of each end-of-stream test, ours loads it into edi directly (17.4 %)
	bool TextReadStream::ReadToken(char* buffer, unsigned int size, bool quoted)
	{
		unsigned int originalSize = size;
		char ch;
		bool found = false;
		bool inComment = false;
		if (!stream->HasMore())
		{
			return false;
		}
		do
		{
			if (found)
			{
				break;
			}
			stream->Transfer(&ch, 1);
			if (inComment)
			{
				if (ch == '\n')
				{
					line++;
					inComment = false;
				}
			}
			else
			{
				if (flag)
				{
					if (stream->HasMore() && ch == '/')
					{
						char next;
						stream->Transfer(&next, 1);
						if (next == '/')
						{
							inComment = true;
							continue;
						}
						SetPosition(GetPosition() - 1);
					}
				}
				if (ch == ' ' || ch == '\t' || ch == '\r')
				{
				}
				else if (ch == '\n')
				{
					line++;
				}
				else
				{
					found = true;
				}
			}
		}
		while (stream->HasMore());
		if (!found)
		{
			return false;
		}
		if (quoted)
		{
			if (ch != '"')
			{
				return false;
			}
			if (!stream->HasMore())
			{
				return false;
			}
			stream->Transfer(&ch, 1);
		}
		else if (ch == ',')
		{
			if (size < 2)
			{
				return false;
			}
			buffer[0] = ',';
			buffer[1] = 0;
			return true;
		}
		char first = 1;
		char* out = buffer;
		do
		{
			if (!first)
			{
				stream->Transfer(&ch, 1);
			}
			first = 0;
			if (!quoted)
			{
				if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == ',')
				{
					stream->SetPosition(stream->GetPosition() - 1);
					*out = 0;
					return true;
				}
				if (flag)
				{
					if (stream->HasMore() && ch == '/')
					{
						char next;
						stream->Transfer(&next, 1);
						if (next == '/')
						{
							SetPosition(GetPosition() - 2);
							*out = 0;
							return true;
						}
						SetPosition(GetPosition() - 1);
					}
				}
			}
			else
			{
				if (ch == '"')
				{
					*out = 0;
					return true;
				}
				if (ch == '\r' || ch == '\n')
				{
					return false;
				}
			}
			*out = ch;
			size--;
			out++;
			if (!stream->HasMore())
			{
				if (size == 0 || quoted || originalSize == size)
				{
					return false;
				}
				*out = 0;
				return true;
			}
			if (size == 0)
			{
				return false;
			}
		}
		while (true);
	}

	// FUNCTION: ENGINE 0x105FC500
	bool TextReadStream::ReadUInt(unsigned int* result)
	{
		unsigned int value;
		char text[0x20];
		if (ReadToken(text, 0x20, false))
		{
			if (sscanf_s(text, "%u", &value) > 0)
			{
				*result = value;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105FC550
	bool TextReadStream::ReadInt(int* result)
	{
		int value;
		char text[0x20];
		if (ReadToken(text, 0x20, false))
		{
			if (sscanf_s(text, "%i", &value) > 0)
			{
				*result = value;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105FC5A0
	bool TextReadStream::ReadUShort(unsigned short* result)
	{
		unsigned int value;
		char text[0x20];
		if (ReadToken(text, 0x20, false))
		{
			if (sscanf_s(text, "%u", &value) > 0 && value <= 0xFFFF)
			{
				*result = (unsigned short)value;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105FC600
	bool TextReadStream::ReadShort(short* result)
	{
		unsigned int value;
		char text[0x20];
		if (ReadToken(text, 0x20, false))
		{
			if (sscanf_s(text, "%i", &value) > 0 && value + 0x8000 <= 0xFFFF)
			{
				*result = (short)value;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105FC660
	bool TextReadStream::ReadUChar(unsigned char* result)
	{
		unsigned int value;
		char text[0x20];
		if (ReadToken(text, 0x20, false))
		{
			if (sscanf_s(text, "%u", &value) > 0 && value <= 0xFF)
			{
				*result = (unsigned char)value;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105FC6C0
	bool TextReadStream::ReadChar(char* result)
	{
		unsigned int value;
		char text[0x20];
		if (ReadToken(text, 0x20, false))
		{
			if (sscanf_s(text, "%i", &value) > 0 && value + 0x80 <= 0xFF)
			{
				*result = (char)value;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105FC720
	bool TextReadStream::ReadFloat(float* result)
	{
		float value;
		char text[0x40];
		if (ReadToken(text, 0x40, false))
		{
			if (sscanf_s(text, "%f", &value) > 0)
			{
				*result = value;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105FC770
	bool TextReadStream::ReadBool(bool* result)
	{
		char text[0x20];
		if (ReadToken(text, 0x20, false))
		{
			int compare = strcmp(text, "true");
			if (compare == 0)
			{
				*result = true;
				return true;
			}
			compare = strcmp(text, "false");
			if (compare == 0)
			{
				*result = false;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105FC7F0
	TextWriter::TextWriter(ByteStream* newStream)
	{
		stream = newStream;
		indent = 0;
		unknown8 = 1;
		atLineStart = true;
	}

	// FUNCTION: ENGINE 0x105FC810
	void TextWriter::Flush()
	{
	}

	// FUNCTION: ENGINE 0x105FC820
	void TextWriter::SetUnknown8(int value)
	{
		unknown8 = value;
	}

	// FUNCTION: ENGINE 0x105FC830
	void TextWriter::Indent()
	{
		indent++;
	}

	// FUNCTION: ENGINE 0x105FC840
	void TextWriter::Unindent()
	{
		indent--;
	}

	// FUNCTION: ENGINE 0x105FC850
	void TextWriter::NewLine()
	{
		char returnChar = '\r';
		char lineFeed = '\n';
		stream->Transfer(&returnChar, 1);
		stream->Transfer(&lineFeed, 1);
		atLineStart = true;
	}

	// FUNCTION: ENGINE 0x105FC890
	void TextWriter::Write(const char* text, bool quoted)
	{
		unsigned int count = unknown8;
		if (atLineStart)
		{
			count = indent * 4;
			atLineStart = false;
		}
		for (unsigned int i = 0; i < count; i++)
		{
			char space = ' ';
			stream->Transfer(&space, 1);
		}
		if (text == 0)
		{
			text = "";
		}
		char quote = '"';
		if (quoted)
		{
			stream->Transfer(&quote, 1);
		}
		stream->Transfer((void*)text, (unsigned int)strlen(text));
		if (quoted)
		{
			stream->Transfer(&quote, 1);
		}
	}

	// FUNCTION: ENGINE 0x105FC930
	void TextWriter::WriteUInt(const unsigned int* value)
	{
		char text[0x20];
		core::SNPrintfCount(text, 0x20, "%u", *value);
		Write(text, false);
	}

	// FUNCTION: ENGINE 0x105FC970
	void TextWriter::WriteInt(const int* value)
	{
		char text[0x20];
		core::SNPrintfCount(text, 0x20, "%d", *value);
		Write(text, false);
	}

	// FUNCTION: ENGINE 0x105FC9B0
	void TextWriter::WriteUShort(const unsigned short* value)
	{
		char text[0x20];
		core::SNPrintfCount(text, 0x20, "%u", (unsigned int)*value);
		Write(text, false);
	}

	// FUNCTION: ENGINE 0x105FC9F0
	void TextWriter::WriteShort(const short* value)
	{
		char text[0x20];
		core::SNPrintfCount(text, 0x20, "%d", (int)*value);
		Write(text, false);
	}

	// FUNCTION: ENGINE 0x105FCA30
	void TextWriter::WriteUChar(const unsigned char* value)
	{
		char text[0x20];
		core::SNPrintfCount(text, 0x20, "%u", (unsigned int)*value);
		Write(text, false);
	}

	// FUNCTION: ENGINE 0x105FCA70
	void TextWriter::WriteChar(const char* value)
	{
		char text[0x20];
		core::SNPrintfCount(text, 0x20, "%d", (int)*value);
		Write(text, false);
	}

	// FUNCTION: ENGINE 0x105FCAB0
	void TextWriter::WriteFloat(const float* value)
	{
		char text[0x40];
		core::SNPrintfCount(text, 0x40, "%f", (double)*value);
		Write(text, false);
	}

	// FUNCTION: ENGINE 0x105FCAF0
	void TextWriter::WriteBool(const bool* value)
	{
		if (*value)
		{
			Write("true", false);
			return;
		}
		Write("false", false);
	}

	// FUNCTION: ENGINE 0x105FCB20
	const char* GetUIntTypeName()
	{
		return "uint";
	}

	// FUNCTION: ENGINE 0x105FCB30
	const char* GetIntTypeName()
	{
		return "int";
	}

	// FUNCTION: ENGINE 0x105FCB40
	const char* GetUShortTypeName()
	{
		return "ushort";
	}

	// FUNCTION: ENGINE 0x105FCB50
	const char* GetShortTypeName()
	{
		return "short";
	}

	// FUNCTION: ENGINE 0x105FCB60
	const char* GetUCharTypeName()
	{
		return "uchar";
	}

	// FUNCTION: ENGINE 0x105FCB70
	const char* GetCharTypeName()
	{
		return "char";
	}

	// FUNCTION: ENGINE 0x105FCB80
	const char* GetFloatTypeName()
	{
		return "float";
	}

	// FUNCTION: ENGINE 0x105FCB90
	const char* GetBoolTypeName()
	{
		return "bool";
	}

	// FUNCTION: ENGINE 0x105FCBA0
	NameKey64::NameKey64(const char* text)
	{
		value = 0;
		value = core::Hash64NoCase(text, 0);
	}

	// FUNCTION: ENGINE 0x105FCBD0
	void ReadContext::ReadString(char* destination, int size)
	{
		unsigned int length;
		reader->Read(&length, 1, 4);
		reader->Read(destination, length, 1);
		destination[length] = 0;
	}

	// FUNCTION: ENGINE 0x105FCC10
	void WriteContext::WriteString(const char* text)
	{
		unsigned int length = (unsigned int)strlen(text);
		writer->Write(&length, 1, 4);
		if (length != 0)
		{
			writer->Write(text, length, 1);
		}
	}

	// FUNCTION: ENGINE 0x105FCC60
	const char* GetNameTypeName()
	{
		return "name";
	}
}
