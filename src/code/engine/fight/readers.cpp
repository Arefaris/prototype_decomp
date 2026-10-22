// The readers a fight file is read with and the messages they report (part of the unit 0x105A2440 - 0x105B3680; the
// declarations are in reader.h and readers.h).
#include "code/core/hash.h"
#include "code/core/heap.h"
#include "code/core/strings.h"
#include "code/engine/fight/fightsystem.h"
#include "code/engine/fight/readers.h"
#include <ctype.h>
#include <new>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

namespace core
{
	// 0x1063B960 / 0x1063B990 / 0x1063BAA0: the formatted length, the formatted text with its length, the append
	// with a signed size
	int VSNPrintfResult(char* buffer, int size, const char* format, const char* arguments);
	int SNPrintfCount(char* buffer, int size, const char* format, ...);
	char* StrNCat(char* destination, const char* source, int size);

	// The 32-bit name's hash from a text and from a number; this unit keeps a copy of each
	inline __declspec(noinline) void Name<CaseInsensitiveKey32>::SetText(const char* text)
	{
		hash = Hash32(text, 0);
	}

	inline __declspec(noinline) void Name<CaseInsensitiveKey32>::SetHash(unsigned int newHash)
	{
		hash = newHash;
	}
}

namespace fight
{
	// The flags of a compiled script's header
	extern const int gBinaryNumbers;
	extern const int gBinarySwapped;
	extern const int gBinaryHashedNames;

	// GLOBAL: ENGINE 0x11276228
	ReadErrorCallback gReadErrorCallback;
	// GLOBAL: ENGINE 0x1127622C
	int gReadErrorArgument;

	// ---- Reader ----------------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AA870
	Reader::~Reader()
	{
	}

	// FUNCTION: ENGINE 0x105AA970
	void SetReadErrorCallback(ReadErrorCallback function, int argument)
	{
		gReadErrorCallback = function;
		gReadErrorArgument = argument;
	}

	// FUNCTION: ENGINE 0x105AA8D0
	void ReportReadError(Reader* reader, const char* format, ...)
	{
		char message[0x400];
		char text[0x400];
		va_list arguments;
		va_start(arguments, format);
		core::VSNPrintfResult(message, 0x400, format, arguments);
		const char* file = reader->GetFileName();
		if (file == 0)
		{
			file = "";
		}
		core::SNPrintfCount(text, 0x400, "%s(%d) : %s\n", file, reader->GetLine(), message);
		if (gReadErrorCallback != 0)
		{
			gReadErrorCallback(text, reader, gReadErrorArgument);
		}
	}

	// FUNCTION: ENGINE 0x105AA8A0
	const Reader::Name* Reader::SkipChild()
	{
		const Name* child = EnterChild(*GetChildName());
		ExitChild();
		return child;
	}

	// FUNCTION: ENGINE 0x105AA990
	bool Reader::ReadName(const Name& key, Entity* target)
	{
		Name value;
		bool result = ReadName(key, &value);
		if (result)
		{
			target->SetName(value);
		}
		return result;
	}

	// ---- ScriptReader ----------------------------------------------------------------------------------------------

	static __forceinline bool IsSet(const Reader::Name& name)
	{
		Reader::Name none(0, 1);
		return name != none;
	}

	static __forceinline bool IsNone(const Reader::Name& name)
	{
		Reader::Name none(0, 1);
		return name == none;
	}

	// FUNCTION: ENGINE 0x105AC260
	ScriptReader::ScriptReader(StringReader* newSource, int firstLine)
		: line(firstLine), depth(0), pendingIndent(0), count(0)
	{
		levelStart[0] = -1;
		source = newSource;
		source->AddRef();
		Parse();
	}

	// FUNCTION: ENGINE 0x105AB840
	ScriptReader::~ScriptReader()
	{
		ClearStrings();
		source->Release();
	}

	// FUNCTION: ENGINE 0x105AB860
	bool ScriptReader::UsesNumbers()
	{
		return false;
	}

	// FUNCTION: ENGINE 0x105AB3E0
	bool ScriptReader::AtEnd()
	{
		return source->AtEnd();
	}

	// FUNCTION: ENGINE 0x105AB870
	const char* ScriptReader::GetFileName()
	{
		return source->GetName();
	}

	// FUNCTION: ENGINE 0x105AB880
	int ScriptReader::GetLine()
	{
		return line;
	}

	// FUNCTION: ENGINE 0x105AB320
	int ScriptReader::SkipBlanks()
	{
		int skipped = 0;
		char c = source->Peek();
		while (isspace(c) && c != '\n')
		{
			source->Read();
			skipped = skipped + 1;
			c = source->Peek();
		}
		return skipped;
	}

	// FUNCTION: ENGINE 0x105AB380
	void ScriptReader::ClearStrings()
	{
		for (int i = count - 1; i >= 0; i--)
		{
			if (entries[i].type == 4)
			{
				StringBlock* block = entries[i].value.text;
				if (block != 0)
				{
					do
					{
						StringBlock* old = block;
						block = old->next;
						delete old;
					}
					while (block != 0);
				}
			}
		}
		count = 0;
	}

	// FUNCTION: ENGINE 0x105AB890
	int ScriptReader::AddEntry(const char* entryName)
	{
		int index = count;
		int result = -1;
		if (index < 0x200)
		{
			entries[index].name.SetText(entryName);
			entries[index].type = 0;
			count = count + 1;
			result = index;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105AB8E0
	// EQUIVALENT: the engine clears the zero for the block pointer after reading the next character, ours before the index test; 96.3 %
	void ScriptReader::Parse()
	{
		char token[0x100];
		int heap = core::SetCurrentHeap(GetHeapId(1));
		while (!source->AtEnd())
		{
			int indent = SkipBlanks();
			char c = source->Peek();
			if (!isalpha(c) && c != '_')
			{
				if (c == '\n')
				{
					line = line + 1;
					source->Read();
				}
				else if (!source->AtEnd())
				{
					do
					{
						if (source->Peek() == '\n')
						{
							break;
						}
						source->Read();
					}
					while (!source->AtEnd());
				}
				continue;
			}
			int length = 0;
			for (;;)
			{
				if (!isalnum(c) && c != '_')
				{
					break;
				}
				if (length < 0xff)
				{
					token[length] = source->Read();
					length = length + 1;
				}
				c = source->Peek();
			}
			token[length] = 0;
			SkipBlanks();
			c = source->Peek();
			if (isdigit(c) || c == '-' || c == '+')
			{
				int index = AddEntry(token);
				bool isReal = false;
				length = 0;
				for (;;)
				{
					if (!isdigit(c) && c != '-' && c != '+' && c != '.' && c != 'e' && c != 'E')
					{
						break;
					}
					if (source->AtEnd())
					{
						break;
					}
					if (length < 0xff)
					{
						char read = source->Read();
						if (read == '.')
						{
							isReal = true;
						}
						token[length] = read;
						length = length + 1;
					}
					c = source->Peek();
				}
				token[length] = 0;
				SkipBlanks();
				c = source->Peek();
				if (!isdigit(c) && c != '-' && c != '+')
				{
					if (index >= 0)
					{
						if (isReal)
						{
							entries[index].type = 2;
							entries[index].value.real = (float)atof(token);
						}
						else
						{
							entries[index].type = 1;
							entries[index].value.integer = atoi(token);
						}
					}
				}
				else
				{
					if (index >= 0)
					{
						entries[index].type = 8;
						entries[index].value.vector[0] = (float)atof(token);
					}
					for (int component = 0; component < 3; component++)
					{
						length = 0;
						for (;;)
						{
							if (!isdigit(c) && c != '-' && c != '+' && c != '.' && c != 'e' && c != 'E')
							{
								break;
							}
							if (source->AtEnd())
							{
								break;
							}
							if (length < 0xff)
							{
								token[length] = source->Read();
								length = length + 1;
							}
							c = source->Peek();
						}
						token[length] = 0;
						if (index >= 0)
						{
							entries[index].value.vector[component + 1] = (float)atof(token);
						}
						SkipBlanks();
						c = source->Peek();
					}
				}
			}
			else if (c == '"')
			{
				int index = AddEntry(token);
				StringBlock* block = 0;
				int position = 0;
				if (index >= 0)
				{
					entries[index].type = 4;
					entries[index].value.text = 0;
				}
				source->Read();
				c = source->Peek();
				while (c != '"')
				{
					if (source->AtEnd())
					{
						break;
					}
					if (c == '\\')
					{
						source->Read();
						source->Peek();
					}
					if (block == 0)
					{
						block = new StringBlock;
						position = 0;
						block->next = 0;
						entries[index].value.text = block;
					}
					else if (position >= 0xff)
					{
						block->text[position] = 0;
						block->next = new StringBlock;
						block = block->next;
						position = 0;
						block->next = 0;
					}
					char read = source->Read();
					block->text[position] = read;
					position = position + 1;
					if (read == '\n')
					{
						line = line + 1;
					}
					c = source->Peek();
				}
				if (block != 0)
				{
					block->text[position] = 0;
				}
				if (c == '"')
				{
					source->Read();
				}
			}
			else
			{
				pendingName.SetText(token);
				pendingIndent = indent;
				core::SetCurrentHeap(heap);
				return;
			}
		}
		core::SetCurrentHeap(heap);
	}

	// FUNCTION: ENGINE 0x105ABEC0
	int ScriptReader::FindEntry(const Name& key, int types)
	{
		int first = -1;
		int total = count;
		for (int i = 0; i < total; i++)
		{
			if (entries[i].name == key)
			{
				if ((entries[i].type & types) != 0)
				{
					return i;
				}
				if (first < 0)
				{
					first = i;
				}
			}
		}
		return first;
	}

	// FUNCTION: ENGINE 0x105AB3F0
	bool ScriptReader::GetBool(int index, bool* value)
	{
		if (index >= 0 && index < count)
		{
			switch (entries[index].type)
			{
			case 1:
				*value = entries[index].value.integer != 0;
				return true;
			case 2:
				*value = (int)entries[index].value.real != 0;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105AB450
	bool ScriptReader::GetInt(int index, int* value)
	{
		if (index >= 0 && index < count)
		{
			switch (entries[index].type)
			{
			case 1:
				*value = entries[index].value.integer;
				return true;
			case 2:
				*value = (int)entries[index].value.real;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105AB4A0
	bool ScriptReader::GetFloat(int index, float* value)
	{
		if (index >= 0 && index < count)
		{
			switch (entries[index].type)
			{
			case 1:
				*value = (float)entries[index].value.integer;
				return true;
			case 2:
				*value = entries[index].value.real;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105AB4F0
	bool ScriptReader::GetTextLength(int index, int* length)
	{
		if (index >= 0 && index < count && entries[index].type == 4)
		{
			*length = 0;
			for (StringBlock* block = entries[index].value.text; block != 0; block = block->next)
			{
				*length += core::StrLen(block->text);
			}
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105AB550
	bool ScriptReader::GetText(int index, char* buffer, int size)
	{
		if (index >= 0 && index < count && entries[index].type == 4)
		{
			if (buffer != 0)
			{
				buffer[0] = 0;
				for (StringBlock* block = entries[index].value.text; block != 0; block = block->next)
				{
					core::StrNCat(buffer, block->text, size);
				}
			}
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105AB5C0
	bool ScriptReader::GetFlags(int index, int* number, char* text, int size)
	{
		if (index >= 0 && index < count)
		{
			switch (entries[index].type)
			{
			case 1:
				return GetInt(index, number);
			case 4:
				return GetText(index, text, size);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105AB610
	bool ScriptReader::GetVector(int index, math::Vector* value)
	{
		if (index >= 0 && index < count && entries[index].type == 8)
		{
			value->Set(entries[index].value.vector[0], entries[index].value.vector[1],
				entries[index].value.vector[2]);
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105AB670
	bool ScriptReader::GetColour(int index, math::Colour128* value)
	{
		if (index >= 0 && index < count && entries[index].type == 8)
		{
			float r = entries[index].value.vector[0];
			float g = entries[index].value.vector[1];
			float b = entries[index].value.vector[2];
			float a = entries[index].value.vector[3];
			value->r = r;
			value->g = g;
			value->b = b;
			value->a = a;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105AB6D0
	const Reader::Name* ScriptReader::GetEntryName(int index)
	{
		if (index >= 0 && index < count)
		{
			return &entries[index].name;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105AB700
	int ScriptReader::GetEntryType(int index)
	{
		if (index >= 0 && index < count)
		{
			return entries[index].type;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105ABD70
	bool ScriptReader::GetName(int index, Name* value)
	{
		int length = 0;
		if (!GetTextLength(index, &length))
		{
			return false;
		}
		int size = length + 1;
		char* text = (char*)core::HeapAlloc(GetHeapId(1), size);
		bool result = GetText(index, text, size);
		if (!result)
		{
			return false;
		}
		value->SetText(text);
		core::Free(text);
		return result;
	}

	// FUNCTION: ENGINE 0x105ABDF0
	// EQUIVALENT: the engine calls its own kept copy of the 32-bit name's SetText (0x105AB760), the symbol of ours is the other unit's copy; 99.2 %
	bool ScriptReader::GetName32(int index, core::Name<core::CaseInsensitiveKey32>* value)
	{
		int length = 0;
		if (!GetTextLength(index, &length))
		{
			return false;
		}
		int size = length + 1;
		char* text = (char*)core::HeapAlloc(GetHeapId(1), size);
		bool result = GetText(index, text, size);
		if (!result)
		{
			return false;
		}
		value->SetText(text);
		core::Free(text);
		return result;
	}

	// FUNCTION: ENGINE 0x105ABE70
	bool ScriptReader::GetEnum(int index, int* value, Name* text)
	{
		if (index >= 0 && index < count)
		{
			switch (entries[index].type)
			{
			case 1:
				return GetInt(index, value);
			case 4:
				return GetName(index, text);
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105AC310
	// EQUIVALENT: same checks and copies in the same order; the registers of the import pointers and of the output pointer are swapped and the loop over the digits has its first test peeled; 11.0 %
	bool ScriptReader::ParseTrigger(int index, Trigger* value, char* flagText, int size)
	{
		if (index >= 0 && index < count && entries[index].type == 4)
		{
			const char* p = entries[index].value.text->text;
			if (!isdigit(*p))
			{
				return false;
			}
			value->first = *p != '0';
			p++;
			if (!isspace(*p))
			{
				return false;
			}
			p++;
			if (!isdigit(*p))
			{
				return false;
			}
			value->second = *p != '0';
			p++;
			if (!isspace(*p))
			{
				return false;
			}
			p++;
			if (isdigit(*p))
			{
				char digits[0x400];
				memset(digits + 1, 0, 0x3ff);
				digits[0] = *p++;
				int length = 1;
				while (isdigit(*p))
				{
					digits[length] = *p;
					length++;
					p++;
					if (length == 0x400)
					{
						return false;
					}
				}
				digits[length] = 0;
				value->number = atoi(digits);
			}
			else if (isalnum(*p) || *p == '_')
			{
				int room = size - 1;
				int length = 0;
				if (room <= 0)
				{
					return false;
				}
				for (;;)
				{
					flagText[length] = *p;
					p++;
					length++;
					if (!isalnum(*p) && *p != '_')
					{
						break;
					}
					if (length >= room)
					{
						return false;
					}
				}
				flagText[length] = 0;
			}
			if (!isspace(*p))
			{
				return false;
			}
			p++;
			value->text = p;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105ABF20
	bool ScriptReader::ReadBool(const Name& key, bool* value)
	{
		int index = FindEntry(key, 3);
		return GetBool(index, value);
	}

	// FUNCTION: ENGINE 0x105ABF40
	bool ScriptReader::ReadInt(const Name& key, int* value)
	{
		int index = FindEntry(key, 3);
		return GetInt(index, value);
	}

	// FUNCTION: ENGINE 0x105ABF60
	bool ScriptReader::ReadFloat(const Name& key, float* value)
	{
		int index = FindEntry(key, 3);
		return GetFloat(index, value);
	}

	// FUNCTION: ENGINE 0x105ABF80
	bool ScriptReader::GetStringLength(const Name& key, int* length)
	{
		int index = FindEntry(key, 4);
		return GetTextLength(index, length);
	}

	// FUNCTION: ENGINE 0x105ABFA0
	bool ScriptReader::ReadString(const Name& key, char* buffer, int size)
	{
		int index = FindEntry(key, 4);
		return GetText(index, buffer, size);
	}

	// FUNCTION: ENGINE 0x105ABFD0
	bool ScriptReader::ReadName(const Name& key, Name* value)
	{
		int index = FindEntry(key, 4);
		return GetName(index, value);
	}

	// FUNCTION: ENGINE 0x105ABFF0
	bool ScriptReader::ReadName32(const Name& key, core::Name<core::CaseInsensitiveKey32>* value)
	{
		int index = FindEntry(key, 4);
		return GetName32(index, value);
	}

	// FUNCTION: ENGINE 0x105AC010
	bool ScriptReader::ReadEnum(const Name& key, int* value, Name* text)
	{
		int index = FindEntry(key, 5);
		return GetEnum(index, value, text);
	}

	// FUNCTION: ENGINE 0x105AC040
	bool ScriptReader::ReadFlags(const Name& key, int* number, char* text, int size)
	{
		int index = FindEntry(key, 5);
		return GetFlags(index, number, text, size);
	}

	// FUNCTION: ENGINE 0x105AC070
	bool ScriptReader::ReadVector(const Name& key, math::Vector* value)
	{
		int index = FindEntry(key, 8);
		return GetVector(index, value);
	}

	// FUNCTION: ENGINE 0x105AC090
	bool ScriptReader::ReadColour(const Name& key, math::Colour128* value)
	{
		int index = FindEntry(key, 8);
		return GetColour(index, value);
	}

	// FUNCTION: ENGINE 0x105AC4E0
	bool ScriptReader::ReadTrigger(const Name& key, Trigger* value, char* flagText, int size)
	{
		int index = FindEntry(key, 4);
		return ParseTrigger(index, value, flagText, size);
	}

	// FUNCTION: ENGINE 0x105AC0B0
	bool ScriptReader::HasChild()
	{
		return pendingName.GetHash() != 0 && pendingIndent > levelStart[depth];
	}

	// FUNCTION: ENGINE 0x105AB730
	const Reader::Name* ScriptReader::GetChildName()
	{
		if (pendingIndent <= levelStart[depth])
		{
			return (const Name*)core::GetStringHeapCounter1();
		}
		return &pendingName;
	}

	// FUNCTION: ENGINE 0x105AB750
	const Reader::Name* ScriptReader::GetCurrentChildName()
	{
		return &currentName;
	}

	// FUNCTION: ENGINE 0x105AC0E0
	// EQUIVALENT: same calls and stores in the same order; the engine zeroes the stack word of its temporary name at the start and shares its slot between both uses, the registers of the two index loads are swapped; 22.8 %
	const Reader::Name* ScriptReader::EnterChild(const Name& key)
	{
		depth = depth + 1;
		ClearStrings();
		if (depth >= 0x40)
		{
			return (const Name*)core::GetStringHeapCounter1();
		}
		if (IsSet(pendingName) && pendingIndent >= levelStart[depth - 1])
		{
			if (IsNone(key) || pendingName == key)
			{
				currentName = pendingName;
				levelStart[depth] = pendingIndent;
				pendingName.SetText(0);
				pendingIndent = 0;
				Parse();
				return &currentName;
			}
		}
		levelStart[depth] = levelStart[depth - 1];
		return (const Name*)core::GetStringHeapCounter1();
	}

	// FUNCTION: ENGINE 0x105AC1D0
	void ScriptReader::ExitChild()
	{
		depth = depth - 1;
		currentName.SetText(0);
		ClearStrings();
		if (depth >= 0 && pendingName.GetHash() == 0)
		{
			Parse();
		}
	}

	// ---- BinReader -------------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AD070
	BinReader::BinReader(DataReader* newSource)
		: numeric(false), swapped(false), hashedNames(false), pendingLength(-1), currentName(0, 1), remaining(0),
			nextName(0, 1), nextNameNeeded(true)
	{
		source = newSource;
		source->AddRef();
		ReadHeader();
	}

	// FUNCTION: ENGINE 0x105AC950
	BinReader::~BinReader()
	{
		source->Release();
	}

	// FUNCTION: ENGINE 0x105AC970
	bool BinReader::UsesNumbers()
	{
		return numeric;
	}

	// FUNCTION: ENGINE 0x105AC7B0
	bool BinReader::AtEnd()
	{
		return source->AtEnd();
	}

	// FUNCTION: ENGINE 0x105AC980
	const char* BinReader::GetFileName()
	{
		return source->GetName();
	}

	// FUNCTION: ENGINE 0x105AC990
	int BinReader::GetLine()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x105ACFD0
	void BinReader::ReadHeader()
	{
		int magic;
		source->Read(&magic, 4);
		char flags[4] = { 0, 0, 0, 0 };
		source->Read(flags, 4);
		numeric = (flags[0] & gBinaryNumbers) != 0;
		swapped = (flags[0] & gBinarySwapped) != 0;
		hashedNames = (flags[0] & gBinaryHashedNames) != 0;
		int size = 0;
		source->Read(&size, 4);
		SwapBytes(&size, 4);
		ReadNextName();
	}

	// FUNCTION: ENGINE 0x105AC780
	void BinReader::SwapBytes(void* data, int size)
	{
		if (swapped)
		{
			char* first = (char*)data;
			char* last = first + size - 1;
			while (first < last)
			{
				char swap = *first;
				*first = *last;
				*last = swap;
				first++;
				last--;
			}
		}
	}

	// FUNCTION: ENGINE 0x105AC9A0
	void BinReader::ReadNextName()
	{
		if (nextNameNeeded)
		{
			while (remaining > 0)
			{
				unsigned __int64 skipped;
				unsigned int part = remaining > 4 ? 4 : remaining;
				source->Read(&skipped, part);
				remaining = remaining - part;
			}
			if (!source->AtEnd())
			{
				unsigned __int64 hash;
				source->Read(&hash, 8);
				SwapBytes(&hash, 8);
				nextName.SetHash(hash);
				nextNameNeeded = false;
			}
			else
			{
				Name none(0, 1);
				nextName = none;
				nextNameNeeded = false;
			}
		}
	}

	// FUNCTION: ENGINE 0x105ACA50
	bool BinReader::ReadBytes(void* destination, unsigned int size)
	{
		unsigned int part = size < remaining ? size : remaining;
		unsigned int got = source->Read(destination, part);
		remaining = remaining - part;
		return got == size ? true : false;
	}

	// FUNCTION: ENGINE 0x105ACA80
	bool BinReader::ReadBool(const Name& key, bool* value)
	{
		pendingLength = -1;
		int number = *value;
		bool result = ReadBytes(&number, 4);
		*value = number != 0;
		return result;
	}

	// FUNCTION: ENGINE 0x105ACAB0
	bool BinReader::ReadInt(const Name& key, int* value)
	{
		pendingLength = -1;
		bool result = ReadBytes(value, 4);
		SwapBytes(value, 4);
		return result;
	}

	// FUNCTION: ENGINE 0x105ACAE0
	bool BinReader::ReadFloat(const Name& key, float* value)
	{
		pendingLength = -1;
		bool result = ReadBytes(value, 4);
		SwapBytes(value, 4);
		return result;
	}

	// FUNCTION: ENGINE 0x105ACB10
	bool BinReader::GetStringLength(const Name& key, int* length)
	{
		bool result = ReadBytes(&pendingLength, 4);
		SwapBytes(&pendingLength, 4);
		*length = pendingLength;
		return result;
	}

	// FUNCTION: ENGINE 0x105ACB40
	bool BinReader::ReadString(const Name& key, char* buffer, int size)
	{
		if (pendingLength < 0)
		{
			if (!GetStringLength(key, &pendingLength))
			{
				return false;
			}
		}
		bool result = true;
		if (pendingLength > 0)
		{
			int padded = pendingLength + (-pendingLength & 3);
			char* text = (char*)core::HeapAlloc(GetHeapId(1), padded + 1);
			result = ReadBytes(text, padded);
			if (buffer != 0 && size > 0)
			{
				memcpy(buffer, text, pendingLength < size ? pendingLength : size);
				buffer[pendingLength < size - 1 ? pendingLength : size - 1] = 0;
			}
			core::Free(text);
		}
		else if (buffer != 0 && size > 0)
		{
			buffer[0] = 0;
		}
		pendingLength = -1;
		return result;
	}

	// FUNCTION: ENGINE 0x105ACC10
	bool BinReader::ReadName(const Name& key, Name* value)
	{
		if (hashedNames)
		{
			unsigned __int64 hash;
			bool result = ReadBytes(&hash, 8);
			SwapBytes(&hash, 8);
			value->SetHash(hash);
			return result;
		}
		int length;
		GetStringLength(key, &length);
		bool result = true;
		if (pendingLength > 0)
		{
			int padded = pendingLength + (-pendingLength & 3);
			char* text = (char*)core::HeapAlloc(GetHeapId(1), padded + 1);
			result = ReadBytes(text, padded);
			text[pendingLength] = 0;
			value->SetText(text);
			core::Free(text);
		}
		else
		{
			value->SetText(0);
		}
		pendingLength = -1;
		return result;
	}

	// FUNCTION: ENGINE 0x105ACCF0
	// EQUIVALENT: the engine calls its own kept copy of the 32-bit name's SetText (0x105AB760), the symbol of ours is the other unit's copy; 99.5 %
	bool BinReader::ReadName32(const Name& key, core::Name<core::CaseInsensitiveKey32>* value)
	{
		int length;
		if (hashedNames)
		{
			bool result = ReadBytes(&length, 4);
			SwapBytes(&length, 4);
			value->SetHash(length);
			return result;
		}
		GetStringLength(key, &length);
		bool result = true;
		if (pendingLength > 0)
		{
			int padded = pendingLength + (-pendingLength & 3);
			char* text = (char*)core::HeapAlloc(GetHeapId(1), padded + 1);
			result = ReadBytes(text, padded);
			text[pendingLength] = 0;
			value->SetText(text);
			core::Free(text);
		}
		else
		{
			value->SetText(0);
		}
		pendingLength = -1;
		return result;
	}

	// FUNCTION: ENGINE 0x105AC7C0
	bool BinReader::ReadEnum(const Name& key, int* value, Name* text)
	{
		return ReadName(key, text);
	}

	// FUNCTION: ENGINE 0x105AC7E0
	bool BinReader::ReadFlags(const Name& key, int* number, char* text, int size)
	{
		if (numeric)
		{
			return ReadInt(key, number);
		}
		return ReadString(key, text, size);
	}

	// FUNCTION: ENGINE 0x105ACDC0
	bool BinReader::ReadVector(const Name& key, math::Vector* value)
	{
		pendingLength = -1;
		bool result = ReadBytes(value, 12);
		SwapBytes(&value->x, 4);
		SwapBytes(&value->y, 4);
		SwapBytes(&value->z, 4);
		return result;
	}

	// FUNCTION: ENGINE 0x105ACE10
	bool BinReader::ReadColour(const Name& key, math::Colour128* value)
	{
		pendingLength = -1;
		bool result = ReadBytes(value, 16);
		float r = value->r;
		float g = value->g;
		float b = value->b;
		float a = value->a;
		SwapBytes(&r, 4);
		SwapBytes(&g, 4);
		SwapBytes(&b, 4);
		SwapBytes(&a, 4);
		value->r = r;
		value->g = g;
		value->b = b;
		value->a = a;
		return result;
	}

	// FUNCTION: ENGINE 0x105AC820
	bool BinReader::ReadTrigger(const Name& key, Trigger* value, char* flagText, int size)
	{
		if (!ReadBool(key, &value->first))
		{
			return false;
		}
		if (!ReadBool(key, &value->second))
		{
			return false;
		}
		if (!ReadFlags(key, &value->number, flagText, size))
		{
			return false;
		}
		return ReadString(key, value->text.Data(), value->text.Capacity()) ? true : false;
	}

	// FUNCTION: ENGINE 0x105ACED0
	bool BinReader::HasChild()
	{
		ReadNextName();
		Name none(0, 1);
		return nextName != none;
	}

	// FUNCTION: ENGINE 0x105ACF00
	const Reader::Name* BinReader::GetChildName()
	{
		ReadNextName();
		return &nextName;
	}

	// FUNCTION: ENGINE 0x105AC8A0
	const Reader::Name* BinReader::GetCurrentChildName()
	{
		return &currentName;
	}

	// FUNCTION: ENGINE 0x105ACF10
	const Reader::Name* BinReader::EnterChild(const Name& key)
	{
		ReadNextName();
		currentName = nextName;
		source->Read(&remaining, 4);
		SwapBytes(&remaining, 4);
		Name none(0, 1);
		nextName = none;
		nextNameNeeded = true;
		return &currentName;
	}

	// FUNCTION: ENGINE 0x105ACF70
	void BinReader::ExitChild()
	{
		ReadNextName();
		Name none(0, 1);
		currentName = none;
		remaining = 0;
		nextNameNeeded = true;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x105AB010
// FUNCTION: ENGINE 0x105AB300
// FUNCTION: ENGINE 0x105AB820
// FUNCTION: ENGINE 0x105AB830
// FUNCTION: ENGINE 0x105AC210
// FUNCTION: ENGINE 0x105AC2F0
// FUNCTION: ENGINE 0x105AC8B0
// FUNCTION: ENGINE 0x105ACFB0
