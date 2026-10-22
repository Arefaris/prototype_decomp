// The source the fight nodes' properties read their values from (RTTI base of fight::ScriptReader and
// fight::BinReader, 24 vftable slots). Every read takes the property's name and answers whether the value was there.
#ifndef ENGINE_FIGHT_READER_H
#define ENGINE_FIGHT_READER_H

#include "code/container/string.h"
#include "code/core/name.h"
#include "code/engine/fight/branch.h"
#include "code/math/colour128.h"
#include "code/math/vector.h"

namespace fight
{
	class Reader : public RefCounted
	{
	public:
		typedef core::Name<core::CaseSensitiveKey> Name;

		// 0x105AB300 (the engine keeps a copy)
		Reader()
		{
		}
		// 0x105AA870 (0x105AA880 is the deleting destructor)
		virtual ~Reader();

		// What a trigger value is read as (names guessed): two flags, a number with the text it was written as, and a
		// text
		struct Trigger
		{
			// 0x105A8BD0 (the engine keeps a copy)
			Trigger()
				: first(false), second(true), number(-1)
			{
			}

			bool first;  // +0
			bool second;  // +1
			int number;  // +4
			container::StringC<64> text;  // +8
		};

		// vftable slot 3: whether the numbers and the enumerations are stored as numbers (the binary reader's first
		// flag; the script reader never)
		virtual bool UsesNumbers() = 0;
		// vftable slot 4: whether nothing is left to read
		virtual bool AtEnd() = 0;
		// vftable slot 5: a trigger (the key, the trigger, a buffer for the flags' text and its size)
		virtual bool ReadTrigger(const Name& key, Trigger* value, char* flagText, int size) = 0;
		// vftable slot 6 and 7
		virtual bool ReadColour(const Name& key, math::Colour128* value) = 0;
		virtual bool ReadVector(const Name& key, math::Vector* value) = 0;
		// vftable slot 8: a value written as a list of flag names or as a number (the name, the number, the text and its size)
		virtual bool ReadFlags(const Name& key, int* number, char* text, int size) = 0;
		// vftable slot 9: a value of an enumeration, as a number or as the name of an entry
		virtual bool ReadEnum(const Name& key, int* value, Name* text) = 0;
		// vftable slot 10: a name of 32 bits
		virtual bool ReadName32(const Name& key, core::Name<core::CaseInsensitiveKey32>* value) = 0;
		// vftable slot 11
		virtual bool ReadName(const Name& key, Name* value) = 0;
		// vftable slot 12: the text of a value into a buffer of a size
		virtual bool ReadString(const Name& key, char* buffer, int size) = 0;
		virtual bool ReadFloat(const Name& key, float* value) = 0;
		virtual bool ReadInt(const Name& key, int* value) = 0;
		virtual bool ReadBool(const Name& key, bool* value) = 0;
		// vftable slot 16: the length of the text of a value
		virtual bool GetStringLength(const Name& key, int* length) = 0;
		// vftable slot 17 - 21: the children of the node being read (a child is entered by its name or by a null one)
		virtual bool HasChild() = 0;
		virtual const Name* GetChildName() = 0;
		virtual const Name* GetCurrentChildName() = 0;
		virtual const Name* EnterChild(const Name& key) = 0;
		virtual void ExitChild() = 0;
		// vftable slot 22 and 23: where the reader is, for the messages
		virtual const char* GetFileName() = 0;
		virtual int GetLine() = 0;

		// 0x105AA990: reads a name and hands it to an entity
		bool ReadName(const Name& key, Entity* target);
		// 0x105A31A0: the same for a key given as text
		bool ReadName(const char* keyText, Entity* target);
		// 0x105AA8A0: leaves the child the reader is at, answering its name (name guess)
		const Name* SkipChild();
	};

	// The function that is shown a message of a reader with the reader (set with SetReadErrorCallback)
	typedef void (*ReadErrorCallback)(const char* message, Reader* reader, int argument);
	// 0x105AA970: installs the callback
	void SetReadErrorCallback(ReadErrorCallback function, int argument);
	// 0x105AA8D0: shows a message with the file and the line the reader is at (formats like printf)
	void ReportReadError(Reader* reader, const char* format, ...);
}

#endif
