// The two readers a fight file is read with (RTTI: fight::ScriptReader, a reader over the text of a script, and
// fight::BinReader, a reader over the bytes of a compiled one; both are 24-slot fight::Reader classes). Unit 0x105A2440 -
// 0x105B3680 (no assert path; the file name is a guess). Names are guesses.
#ifndef ENGINE_FIGHT_READERS_H
#define ENGINE_FIGHT_READERS_H

#include "code/engine/fight/reader.h"
#include "code/engine/fight/streamreaders.h"

namespace fight
{
	// A text a script entry holds is a chain of blocks of 0x100 characters
	struct StringBlock
	{
		char text[0x100];
		StringBlock* next;  // +0x100
	};

	// What one line of a script says: a name and a number, a text or up to four numbers
	struct ScriptEntry
	{
		core::Name<core::CaseSensitiveKey> name;  // +0
		// 1: an integer, 2: a float, 4: a text, 8: a vector or a colour; 0: nothing yet
		int type;  // +8
		union
		{
			int integer;
			float real;
			StringBlock* text;
			float vector[4];
		} value;  // +0xC
		int unknown1C;
	};

	// RTTI: fight::ScriptReader: reads the "name value" lines of a script, the lines indented below a name being the
	// children of that name
	class ScriptReader : public Reader
	{
	public:
		// 0x105AC260 (the line is the number the first line has in the messages)
		ScriptReader(StringReader* newSource, int firstLine);
		// 0x105AC2F0 is the deleting destructor, 0x105AB840 the body
		virtual ~ScriptReader();
		virtual bool UsesNumbers();
		virtual bool AtEnd();
		virtual bool ReadTrigger(const Name& key, Trigger* value, char* flagText, int size);
		virtual bool ReadColour(const Name& key, math::Colour128* value);
		virtual bool ReadVector(const Name& key, math::Vector* value);
		virtual bool ReadFlags(const Name& key, int* number, char* text, int size);
		virtual bool ReadEnum(const Name& key, int* value, Name* text);
		virtual bool ReadName32(const Name& key, core::Name<core::CaseInsensitiveKey32>* value);
		virtual bool ReadName(const Name& key, Name* value);
		virtual bool ReadString(const Name& key, char* buffer, int size);
		virtual bool ReadFloat(const Name& key, float* value);
		virtual bool ReadInt(const Name& key, int* value);
		virtual bool ReadBool(const Name& key, bool* value);
		virtual bool GetStringLength(const Name& key, int* length);
		virtual bool HasChild();
		virtual const Name* GetChildName();
		virtual const Name* GetCurrentChildName();
		virtual const Name* EnterChild(const Name& key);
		virtual void ExitChild();
		virtual const char* GetFileName();
		virtual int GetLine();

		// 0x105AB320: skips the blanks of the line, answering how many
		int SkipBlanks();
		// 0x105AB380: lets go of the entries read so far
		void ClearStrings();
		// 0x105AB890: starts an entry of a name, answering its index (-1 when there is no room)
		int AddEntry(const char* entryName);
		// 0x105AB8E0: reads lines up to the next name that has no value (the next child)
		void Parse();
		// 0x105ABEC0: the entry of a name whose type is one of the types given (the first one of the name otherwise,
		// -1 for none)
		int FindEntry(const Name& key, int types);

		// 0x105AB3F0 / 0x105AB450 / 0x105AB4A0 / 0x105AB4F0: the value of an entry as a bool / an integer / a float /
		// the length of its text
		bool GetBool(int index, bool* value);
		bool GetInt(int index, int* value);
		bool GetFloat(int index, float* value);
		bool GetTextLength(int index, int* length);
		// 0x105AB550 / 0x105AB5C0: the text of an entry / an entry that is a number or a text
		bool GetText(int index, char* buffer, int size);
		bool GetFlags(int index, int* number, char* text, int size);
		// 0x105AB610 / 0x105AB670: the numbers of an entry as a vector / a colour
		bool GetVector(int index, math::Vector* value);
		bool GetColour(int index, math::Colour128* value);
		// 0x105AB6D0 / 0x105AB700: the name / the type of an entry (null / 0 past the end)
		const Name* GetEntryName(int index);
		int GetEntryType(int index);
		// 0x105ABD70 / 0x105ABDF0 / 0x105ABE70: the text of an entry as a name / as a 32-bit name / an entry that is a
		// number or a name
		bool GetName(int index, Name* value);
		bool GetName32(int index, core::Name<core::CaseInsensitiveKey32>* value);
		bool GetEnum(int index, int* value, Name* text);
		// 0x105AC310: the text of an entry as a trigger
		bool ParseTrigger(int index, Trigger* value, char* flagText, int size);

		StringReader* source;  // +8
		int line;  // +0xC
		int depth;  // +0x10
		// The indentation each depth began at
		int levelStart[0x41];  // +0x14
		Name currentName;  // +0x118: the child that was entered last
		Name pendingName;  // +0x120: the next name read, without a value
		int pendingIndent;  // +0x128
		int count;  // +0x12C
		ScriptEntry entries[0x200];  // +0x130
	};

	// RTTI: fight::BinReader: reads the values of a compiled script from a byte source
	class BinReader : public Reader
	{
	public:
		// 0x105AD070
		explicit BinReader(DataReader* newSource);
		// 0x105ACFB0 is the deleting destructor, 0x105AC950 the body
		virtual ~BinReader();
		virtual bool UsesNumbers();
		virtual bool AtEnd();
		virtual bool ReadTrigger(const Name& key, Trigger* value, char* flagText, int size);
		virtual bool ReadColour(const Name& key, math::Colour128* value);
		virtual bool ReadVector(const Name& key, math::Vector* value);
		virtual bool ReadFlags(const Name& key, int* number, char* text, int size);
		virtual bool ReadEnum(const Name& key, int* value, Name* text);
		virtual bool ReadName32(const Name& key, core::Name<core::CaseInsensitiveKey32>* value);
		virtual bool ReadName(const Name& key, Name* value);
		virtual bool ReadString(const Name& key, char* buffer, int size);
		virtual bool ReadFloat(const Name& key, float* value);
		virtual bool ReadInt(const Name& key, int* value);
		virtual bool ReadBool(const Name& key, bool* value);
		virtual bool GetStringLength(const Name& key, int* length);
		virtual bool HasChild();
		virtual const Name* GetChildName();
		virtual const Name* GetCurrentChildName();
		virtual const Name* EnterChild(const Name& key);
		virtual void ExitChild();
		virtual const char* GetFileName();
		virtual int GetLine();

		// 0x105ACFD0: reads the header
		void ReadHeader();
		// 0x105AC780: turns the bytes of a value around when the file was written the other way
		void SwapBytes(void* data, int size);
		// 0x105AC9A0: reads the name of the next child when none is waiting
		void ReadNextName();
		// 0x105ACA50: reads bytes of the current child, answering whether all of them were there
		bool ReadBytes(void* destination, unsigned int size);

		DataReader* source;  // +8
		bool numeric;  // +0xC: the header's first flag
		bool swapped;  // +0xD: the second flag
		bool hashedNames;  // +0xE: the third flag
		int pendingLength;  // +0x10: the length of the text that is read next (-1: not known yet)
		int unknown14;
		Name currentName;  // +0x18: the child that was entered last
		unsigned int remaining;  // +0x20: the bytes of the current child that are left
		int unknown24;
		Name nextName;  // +0x28: the name of the next child
		bool nextNameNeeded;  // +0x30
	};
}

#endif
