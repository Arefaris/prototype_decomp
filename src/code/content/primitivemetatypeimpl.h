// The slots of content::PrimitiveMetaType<T>, the meta types of the numbers and flags, written as members of
// PrimitiveMetaTypeImpl<T> (a class that is never instantiated: only these functions are used) so that the declared
// virtual functions of the vftable stay what the engine's callers see. The engine keeps one copy of the slots of each
// T, in the unit of the first reflected class that uses them: primitivemetatype.cpp (bool, float, int, unsigned int),
// primitivemetatypechar.cpp, primitivemetatypeshort.cpp and the unit of PrimitiveMetaType<unsigned short>.
#ifndef CONTENT_PRIMITIVEMETATYPEIMPL_H
#define CONTENT_PRIMITIVEMETATYPEIMPL_H

#include "code/content/metatype.h"
#include "code/core/heap.h"

namespace content
{
	// The heap the meta system makes its values in (0x11276928, name guessed)
	extern int gMetaHeap;

	const char* GetBoolTypeName();
	const char* GetFloatTypeName();

	// What a value of the type is in a binary stream and in a text, and what the text calls it
	template<class T> struct PrimitiveTraits;

	template<> struct PrimitiveTraits<float>
	{
		typedef float Stored;
		__forceinline static void Read(BinaryReader* reader, float* value)
		{
			reader->Read(value, 1, 4);
		}
		__forceinline static float FromStored(float value)
		{
			return value;
		}
		__forceinline static float ToStored(float value)
		{
			return value;
		}
		__forceinline static bool ReadText(TextReadStream* reader, float* value)
		{
			return reader->ReadFloat(value);
		}
		__forceinline static void WriteText(TextWriter* writer, const float* value)
		{
			writer->WriteFloat(value);
		}
		__forceinline static const char* TypeName()
		{
			return GetFloatTypeName();
		}
	};

	template<> struct PrimitiveTraits<int>
	{
		typedef int Stored;
		__forceinline static void Read(BinaryReader* reader, int* value)
		{
			reader->Read(value, 1, 4);
		}
		__forceinline static int FromStored(int value)
		{
			return value;
		}
		__forceinline static int ToStored(int value)
		{
			return value;
		}
		__forceinline static bool ReadText(TextReadStream* reader, int* value)
		{
			return reader->ReadInt(value);
		}
		__forceinline static void WriteText(TextWriter* writer, const int* value)
		{
			writer->WriteInt(value);
		}
		__forceinline static const char* TypeName()
		{
			return GetIntTypeName();
		}
	};

	template<> struct PrimitiveTraits<unsigned int>
	{
		typedef unsigned int Stored;
		__forceinline static void Read(BinaryReader* reader, unsigned int* value)
		{
			reader->Read(value, 1, 4);
		}
		__forceinline static unsigned int FromStored(unsigned int value)
		{
			return value;
		}
		__forceinline static unsigned int ToStored(unsigned int value)
		{
			return value;
		}
		__forceinline static bool ReadText(TextReadStream* reader, unsigned int* value)
		{
			return reader->ReadUInt(value);
		}
		__forceinline static void WriteText(TextWriter* writer, const unsigned int* value)
		{
			writer->WriteUInt(value);
		}
		__forceinline static const char* TypeName()
		{
			return GetUIntTypeName();
		}
	};

	template<> struct PrimitiveTraits<unsigned short>
	{
		typedef unsigned short Stored;
		__forceinline static void Read(BinaryReader* reader, unsigned short* value)
		{
			reader->Read(value, 1, 2);
		}
		__forceinline static unsigned short FromStored(unsigned short value)
		{
			return value;
		}
		__forceinline static unsigned short ToStored(unsigned short value)
		{
			return value;
		}
		__forceinline static bool ReadText(TextReadStream* reader, unsigned short* value)
		{
			return reader->ReadUShort(value);
		}
		__forceinline static void WriteText(TextWriter* writer, const unsigned short* value)
		{
			writer->WriteUShort(value);
		}
		__forceinline static const char* TypeName()
		{
			return GetUShortTypeName();
		}
	};

	template<> struct PrimitiveTraits<bool>
	{
		typedef int Stored;
		__forceinline static void Read(BinaryReader* reader, bool* value)
		{
			int stored;
			reader->Read(&stored, 1, 4);
			*value = stored != 0;
		}
		__forceinline static bool FromStored(int value)
		{
			return value != 0;
		}
		__forceinline static int ToStored(bool value)
		{
			return value ? 1 : 0;
		}
		__forceinline static bool ReadText(TextReadStream* reader, bool* value)
		{
			return reader->ReadBool(value);
		}
		__forceinline static void WriteText(TextWriter* writer, const bool* value)
		{
			writer->WriteBool(value);
		}
		__forceinline static const char* TypeName()
		{
			return GetBoolTypeName();
		}
	};

	template<> struct PrimitiveTraits<char>
	{
		typedef char Stored;
		__forceinline static void Read(BinaryReader* reader, char* value)
		{
			reader->Read(value, 1, 1);
		}
		__forceinline static char FromStored(char value)
		{
			return value;
		}
		__forceinline static char ToStored(char value)
		{
			return value;
		}
		__forceinline static bool ReadText(TextReadStream* reader, char* value)
		{
			return reader->ReadChar(value);
		}
		__forceinline static void WriteText(TextWriter* writer, const char* value)
		{
			writer->WriteChar(value);
		}
		__forceinline static const char* TypeName()
		{
			return GetCharTypeName();
		}
	};

	template<> struct PrimitiveTraits<unsigned char>
	{
		typedef unsigned char Stored;
		__forceinline static void Read(BinaryReader* reader, unsigned char* value)
		{
			reader->Read(value, 1, 1);
		}
		__forceinline static unsigned char FromStored(unsigned char value)
		{
			return value;
		}
		__forceinline static unsigned char ToStored(unsigned char value)
		{
			return value;
		}
		__forceinline static bool ReadText(TextReadStream* reader, unsigned char* value)
		{
			return reader->ReadUChar(value);
		}
		__forceinline static void WriteText(TextWriter* writer, const unsigned char* value)
		{
			writer->WriteUChar(value);
		}
		__forceinline static const char* TypeName()
		{
			return GetUCharTypeName();
		}
	};

	template<> struct PrimitiveTraits<short>
	{
		typedef short Stored;
		__forceinline static void Read(BinaryReader* reader, short* value)
		{
			reader->Read(value, 1, 2);
		}
		__forceinline static short FromStored(short value)
		{
			return value;
		}
		__forceinline static short ToStored(short value)
		{
			return value;
		}
		__forceinline static bool ReadText(TextReadStream* reader, short* value)
		{
			return reader->ReadShort(value);
		}
		__forceinline static void WriteText(TextWriter* writer, const short* value)
		{
			writer->WriteShort(value);
		}
		__forceinline static const char* TypeName()
		{
			return GetShortTypeName();
		}
	};


	template<class T> class PrimitiveMetaTypeImpl : public PrimitiveMetaType<T>
	{
	public:
		typedef PrimitiveTraits<T> Traits;
		typedef typename Traits::Stored Stored;

		// slot 0
		bool ReadTextSlot(TextReadStream* reader, void* object, int a, int b)
		{
			T value;
			bool ok = Traits::ReadText(reader, &value);
			if (!ok)
			{
				int line = reader->GetLine();
				reader->Error("Expecting %s at line %d", Traits::TypeName(), line);
				return false;
			}
			Set(object, value);
			return true;
		}
		// slot 1
		void ReadBinarySlot(ReadContext* context, void* object, int a, int b)
		{
			Stored value;
			context->reader->Read(&value, 1, sizeof(Stored));
			Set(object, Traits::FromStored(value));
		}
		// slot 2
		void WriteTextSlot(TextWriter* writer, const void* object, int a)
		{
			T value = Get(object);
			Traits::WriteText(writer, &value);
		}
		// slot 3
		void WriteBinarySlot(WriteContext* context, const void* object, int a)
		{
			Stored value = Traits::ToStored(Get(object));
			context->writer->Write(&value, 1, sizeof(Stored));
		}
		// slot 4
		bool CompareSlot(ReadContext* first, const char* firstName, ReadContext* second, const char* secondName, int unused,
			TextWriter* log)
		{
			T a = (T)0;
			if (first != 0)
			{
				Traits::Read(first->reader, &a);
			}
			T b = (T)0;
			if (second != 0)
			{
				Traits::Read(second->reader, &b);
			}
			if (first != 0)
			{
				if (second != 0 && a == b)
				{
					Traits::WriteText(log, &a);
					return true;
				}
				log->NewLine();
				log->Write("*******************", false);
				log->Write(firstName, false);
				log->NewLine();
				Traits::WriteText(log, &a);
			}
			if (second != 0)
			{
				log->NewLine();
				log->Write("*******************", false);
				log->Write(secondName, false);
				log->NewLine();
				Traits::WriteText(log, &b);
			}
			log->NewLine();
			log->Write("*******************", false);
			log->NewLine();
			return false;
		}
		// slot 6
		void* CreateSlot()
		{
			core::HeapScope scope(gMetaHeap);
			T* value = (T*)operator new(sizeof(T));
			*value = Traits::FromStored(0);
			return value;
		}
		// slot 7
		void DestroySlot(void* object)
		{
			operator delete(object);
		}
		// slot 8
		void CopySlot(void* destination, const void* source, int a)
		{
			Set(destination, Get(source));
		}
		// slot 9
		int CountSlot(void* object, int a)
		{
			return 1;
		}
		// slot 10
		void DescribeSlot(MemberEntry** cursor, void* object, int a)
		{
			(*cursor)->type = this;
			(*cursor)->object = object;
			*cursor += 1;
		}
		// slot 11
		void WriteBinaryShortSlot(WriteContext* context, const void* object)
		{
			Stored value = Traits::ToStored(Get(object));
			context->writer->Write(&value, 1, sizeof(Stored));
		}
		// slots 12 / 13
		T GetSlot(const void* object)
		{
			return *(const T*)object;
		}
		void SetSlot(void* object, T value)
		{
			*(T*)object = value;
		}
	};
}

#endif
