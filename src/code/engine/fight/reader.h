// The source the fight nodes' properties read their values from (RTTI base of fight::ScriptReader and
// fight::BinReader, 24 vftable slots). Every read takes the property's name and answers whether the value was there.
#ifndef ENGINE_FIGHT_READER_H
#define ENGINE_FIGHT_READER_H

#include "code/core/name.h"
#include "code/math/colour128.h"
#include "code/math/vector.h"

namespace fight
{
	class Reader
	{
	public:
		typedef core::Name<core::CaseSensitiveKey> Name;

		virtual void Slot0() = 0;
		virtual void Slot1() = 0;
		virtual void Slot2() = 0;
		// vftable slot 3: whether a value follows
		virtual bool HasValue() = 0;
		virtual void Slot4() = 0;
		virtual void Slot5() = 0;
		// vftable slot 6 and 7
		virtual bool ReadColour(const Name& key, math::Colour128* value) = 0;
		virtual bool ReadVector(const Name& key, math::Vector* value) = 0;
		virtual void Slot8() = 0;
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
		// vftable slot 17 - 21: the children of the node being read
		virtual bool HasChild() = 0;
		virtual const Name* GetChildName() = 0;
		virtual void Slot19() = 0;
		virtual void EnterChild(const Name& key) = 0;
		virtual void ExitChild() = 0;
		// vftable slot 22 and 23: where the reader is, for the messages
		virtual const char* GetFileName() = 0;
		virtual int GetLine(void* arguments) = 0;
	};

	// 0x105AA8D0: shows a message with the file and the line the reader is at (formats like printf)
	void ReportReadError(Reader* reader, const char* format, ...);
}

#endif
