// content::PrimitiveMetaType<T>: the slots of the meta types of the numbers and flags (bool, float, int and unsigned
// int; unit 0x10060700 - 0x10065050 and 0x100713E0 - 0x10071740, the first reflected class that uses them keeps the
// copies; the file name is guessed). The vftable of the class is declared with slots of no arguments (metatype.h),
// the functions here are the ones its slots lead to, written as members of PrimitiveMetaTypeImpl<T> (a class that is
// never instantiated: only these functions are used) so that the declared virtual functions stay what the engine's
// callers see.
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

	template class PrimitiveMetaTypeImpl<float>;
	template class PrimitiveMetaTypeImpl<int>;
	template class PrimitiveMetaTypeImpl<unsigned int>;
	template class PrimitiveMetaTypeImpl<bool>;
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10060760
// FUNCTION: ENGINE 0x100607A0
// FUNCTION: ENGINE 0x10060850
// FUNCTION: ENGINE 0x10060880
// FUNCTION: ENGINE 0x100609E0
// FUNCTION: ENGINE 0x100609F0
// FUNCTION: ENGINE 0x10060A00
// FUNCTION: ENGINE 0x10060A20
// FUNCTION: ENGINE 0x10060A50
// FUNCTION: ENGINE 0x10060A60
// FUNCTION: ENGINE 0x10060A80
// FUNCTION: ENGINE 0x10060B20
// FUNCTION: ENGINE 0x10060B60
// FUNCTION: ENGINE 0x10060C00
// FUNCTION: ENGINE 0x10060C30
// FUNCTION: ENGINE 0x10060D80
// FUNCTION: ENGINE 0x10060D90
// FUNCTION: ENGINE 0x10060DB0
// FUNCTION: ENGINE 0x10060DD0
// FUNCTION: ENGINE 0x10060E00
// FUNCTION: ENGINE 0x10060E10
// FUNCTION: ENGINE 0x10060E30
// FUNCTION: ENGINE 0x100612E0
// FUNCTION: ENGINE 0x10061320
// FUNCTION: ENGINE 0x10061F90
// FUNCTION: ENGINE 0x10064D50
// FUNCTION: ENGINE 0x10064D90
// FUNCTION: ENGINE 0x10064E30
// FUNCTION: ENGINE 0x10064E60
// FUNCTION: ENGINE 0x10064FB0
// FUNCTION: ENGINE 0x10064FC0
// FUNCTION: ENGINE 0x10064FD0
// FUNCTION: ENGINE 0x10064FF0
// FUNCTION: ENGINE 0x10065020
// FUNCTION: ENGINE 0x10065030
// FUNCTION: ENGINE 0x10065050
// FUNCTION: ENGINE 0x100656D0
// FUNCTION: ENGINE 0x1006A520
// FUNCTION: ENGINE 0x10071440
// FUNCTION: ENGINE 0x10071480
// FUNCTION: ENGINE 0x10071520
// FUNCTION: ENGINE 0x10071550
// FUNCTION: ENGINE 0x100716A0
// FUNCTION: ENGINE 0x100716B0
// FUNCTION: ENGINE 0x100716C0
// FUNCTION: ENGINE 0x100716E0
// FUNCTION: ENGINE 0x10071710
// FUNCTION: ENGINE 0x10071720
// FUNCTION: ENGINE 0x10071740
// FUNCTION: ENGINE 0x100737A0
// FUNCTION: ENGINE 0x1007AA50
