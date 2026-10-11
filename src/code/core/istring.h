// core::IString and core::String (RTTI names; vftables 0x10E475D4 / 0x10E47644, Object part 0x10E4763C): a
// reference-counted heap string. Unit 0x10647F70 - 0x106486FE (no assert path; file name string.cpp and the method
// names guessed). The buffer comes from the object's own heap; the last word holds the capacity (bits 0-30) and a
// null flag (bit 31: the string holds no value, as opposed to "").
#ifndef CORE_ISTRING_H
#define CORE_ISTRING_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/object.h"

namespace core
{
	// The compiler lists overloaded virtual functions in reverse order of declaration: the vftable order is
	// Equals(IString*), Equals(const char*), Assign(IString*), Assign(const char*), ...
	struct IString : IRefCount
	{
		virtual bool Equals(const char* string) = 0;
		virtual bool Equals(IString* string) = 0;
		virtual void Assign(const char* string) = 0;
		virtual void Assign(IString* string) = 0;
		// Null while the string holds no value
		virtual const char* Get() = 0;
		// Copies at most size characters (strncpy); a null string gives ""
		virtual void Copy(char* buffer, unsigned int size) = 0;
		virtual unsigned int Length() = 0;
		virtual void Append(IString* string) = 0;
		virtual void Append(const char* string) = 0;
		virtual void Append(unsigned int value) = 0;
		virtual void Append(int value) = 0;
		virtual void Append(char value) = 0;
		virtual void Append(unsigned long value) = 0;
		virtual void Append(float value) = 0;
		virtual void Append(bool value) = 0;
		virtual void ToLower() = 0;
		virtual void ToUpper() = 0;
		// Wildcard match ('*' and '?') against a pattern
		virtual unsigned char Match(const char* pattern) = 0;
		virtual unsigned char Match(IString* pattern) = 0;
		// Grows the buffer to hold at least size bytes
		virtual void Reserve(unsigned int size) = 0;
		virtual unsigned int GetCapacity() = 0;
		virtual void Slot24() = 0;
	};

	class String : public IString, public RefCount
	{
	public:
		String();
		// Defined here: the deleting destructor inlines it
		virtual ~String()
		{
			if (buffer != 0)
			{
				HeapFree(heap, buffer);
				buffer = 0;
			}
		}
		virtual void AddRef();
		virtual void Release();
		virtual bool Equals(const char* string);
		virtual bool Equals(IString* string);
		virtual void Assign(const char* string);
		virtual void Assign(IString* string);
		virtual const char* Get();
		virtual void Copy(char* buffer, unsigned int size);
		virtual unsigned int Length();
		virtual void Append(IString* string);
		virtual void Append(const char* string);
		virtual void Append(unsigned int value);
		virtual void Append(int value);
		virtual void Append(char value);
		virtual void Append(unsigned long value);
		virtual void Append(float value);
		virtual void Append(bool value);
		virtual void ToLower();
		virtual void ToUpper();
		virtual unsigned char Match(const char* pattern);
		virtual unsigned char Match(IString* pattern);
		virtual void Reserve(unsigned int size);
		virtual unsigned int GetCapacity();
		virtual void Slot24();

		bool IsNull();
		void SetNull(bool value);
		// The methods test the flag through this inline copy (the bool conversion shows: shr / test al, 1)
		bool NoValue()
		{
			return null;
		}
		void SetCapacity(unsigned int size);

		char* buffer;
		unsigned int capacity : 31;
		unsigned int null : 1;
	};

	// Creates an empty (null) string on a heap
	void CreateString(IString** string, int heap);
}

#endif
