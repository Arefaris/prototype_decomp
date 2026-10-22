// content::ColourMetaType (RTTI): the meta type of a colour member, four floats red to alpha. The slots of the
// content library's meta types have no names yet: each is declared as the vftable slot (mapped in symbols.txt) and,
// for the definition, as a member with the arguments the engine's code takes (names guessed, one set for every meta
// type: 0 reads the text form, 1 the binary form, 2 and 3 write them, 4 compares two binary forms and reports the
// difference as text, 6 makes a value, 7 deletes one, 8 copies one).
#ifndef CONTENT_COLOURMETATYPE_H
#define CONTENT_COLOURMETATYPE_H

#include "code/content/metastream.h"
#include "code/content/metatype.h"
#include "code/math/colour128.h"

namespace content
{
	class ColourMetaType : public MetaType
	{
	public:
		// 0x10601460
		explicit ColourMetaType(const char* code);

		// The vftable
		virtual void Slot0();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		virtual void Slot10();
		virtual void Slot11();

		// 0x10601580 (slot 0): four floats; false (with a message on the reader) when one is missing
		bool ReadText(TextReadStream* reader, void* object, int a, int b);
		// 0x10601480 (slot 1)
		void ReadBinary(ReadContext* context, void* object, int a, int b);
		// 0x10601620 (slot 2) / 0x10601500 (slot 3) / 0x10601740 (slot 11)
		void WriteText(TextWriter* writer, const void* object, int a);
		void WriteBinary(WriteContext* context, const void* object, int a);
		void WriteBinaryShort(WriteContext* context, const void* object);
		// 0x10601840 (slot 4): reads a colour from each side that has one (the default colour where it has none),
		// writes the common value as text when they are equal and else the values under their names
		bool Compare(ReadContext* first, const char* firstName, ReadContext* second, const char* secondName,
			int unused, TextWriter* log);
		// 0x106017F0 (slot 6): a new colour of all ones in the meta system's heap
		void* Create();
		// 0x106016D0 (slot 7)
		void Destroy(void* object);
		// 0x106016E0 (slot 8)
		void Copy(void* destination, const void* source, int a);
		// 0x10601710 (slot 9): always 1
		int Unknown9(int a, int b);
		// 0x10601720 (slot 10): puts the value and this meta type at the cursor and steps it on
		void Describe(MemberEntry** cursor, void* object, int unused);

		// 0x106017C0: all four channels one
		math::Colour128* Construct(math::Colour128* colour);
		// 0x106016A0: copies the channels
		void Assign(math::Colour128* destination, const math::Colour128* source);
		// 0x10601690
		math::Colour128* Identity(math::Colour128* colour);
	};

	// 0x10601450
	const char* GetColourTypeName();

	// The meta type of a colour member of class C: one instance per member (Id tells them apart)
	template<class C, int Id> ColourMetaType* GetMemberColourMetaType(const char* code)
	{
		static ColourMetaType sType(code);
		return &sType;
	}
}

#endif
