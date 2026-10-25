// content::VectorMetaType: the slots of the vector meta type (unit 0x105FB5F0 - 0x105FBB20; the file name is guessed).
#include "code/content/metatype.h"
#include "code/core/heap.h"
#include "code/math/vector.h"

namespace content
{
	// The heap the meta system makes its values in (0x11276928, name guessed)
	extern int gMetaHeap;

	// FUNCTION: ENGINE 0x105FB5F0
	VectorMetaType::VectorMetaType(const char* code)
		: MetaType(code)
	{
	}

	// FUNCTION: ENGINE 0x105FB610
	void VectorMetaType::ReadBinary(ReadContext* context, void* object, int a, int b)
	{
		math::Vector value;
		context->reader->Read(&value.x, 1, 4);
		context->reader->Read(&value.y, 1, 4);
		context->reader->Read(&value.z, 1, 4);
		Set(object, &value);
	}

	// FUNCTION: ENGINE 0x105FB670
	void VectorMetaType::WriteBinary(WriteContext* context, const void* object, int a)
	{
		const math::Vector* vector = Get(object);
		math::Vector value;
		value.x = vector->x;
		value.y = vector->y;
		value.z = vector->z;
		context->writer->Write(&value.x, 1, 4);
		context->writer->Write(&value.y, 1, 4);
		context->writer->Write(&value.z, 1, 4);
	}

	// FUNCTION: ENGINE 0x105FB6E0
	bool VectorMetaType::ReadText(TextReadStream* reader, void* object, int a, int b)
	{
		math::Vector value;
		if (reader->ReadFloat(&value.x))
		{
			if (reader->ReadFloat(&value.y))
			{
				if (reader->ReadFloat(&value.z))
				{
					Set(object, &value);
					return true;
				}
			}
		}
		reader->Error("Expecting vector (3 float values) at line %d", reader->GetLine());
		return false;
	}

	// FUNCTION: ENGINE 0x105FB760
	void VectorMetaType::WriteText(TextWriter* writer, const void* object, int a)
	{
		const math::Vector* vector = Get(object);
		math::Vector value;
		value.x = vector->x;
		value.y = vector->y;
		value.z = vector->z;
		writer->WriteFloat(&value.x);
		writer->WriteFloat(&value.y);
		writer->WriteFloat(&value.z);
	}

	// FUNCTION: ENGINE 0x105FB7C0
	bool VectorMetaType::Compare(ReadContext* first, const char* firstName, ReadContext* second,
		const char* secondName, int unused, TextWriter* log)
	{
		float ax = 0.0f;
		float ay = 0.0f;
		float az = 0.0f;
		float bx = 0.0f;
		float by = 0.0f;
		float bz = 0.0f;
		if (first != 0)
		{
			first->reader->Read(&ax, 1, 4);
			first->reader->Read(&ay, 1, 4);
			first->reader->Read(&az, 1, 4);
		}
		if (second != 0)
		{
			second->reader->Read(&bx, 1, 4);
			second->reader->Read(&by, 1, 4);
			second->reader->Read(&bz, 1, 4);
		}
		if (ax == bx && ay == by && az == bz)
		{
			log->WriteFloat(&ax);
			log->WriteFloat(&ay);
			log->WriteFloat(&az);
			return true;
		}
		if (first != 0)
		{
			log->NewLine();
			log->Write("*******************", false);
			log->Write(firstName, false);
			log->NewLine();
			log->WriteFloat(&ax);
			log->WriteFloat(&ay);
			log->WriteFloat(&az);
		}
		if (second != 0)
		{
			log->NewLine();
			log->Write("*******************", false);
			log->Write(secondName, false);
			log->NewLine();
			log->WriteFloat(&bx);
			log->WriteFloat(&by);
			log->WriteFloat(&bz);
		}
		log->NewLine();
		log->Write("*******************", false);
		log->NewLine();
		return false;
	}

	// FUNCTION: ENGINE 0x105FB990
	const math::Vector* VectorMetaType::Get(const void* object)
	{
		return (const math::Vector*)object;
	}

	// FUNCTION: ENGINE 0x105FB9A0
	void VectorMetaType::Set(void* object, const math::Vector* value)
	{
		math::Vector* vector = (math::Vector*)object;
		vector->x = value->x;
		vector->y = value->y;
		vector->z = value->z;
	}

	// FUNCTION: ENGINE 0x105FB9C0
	math::Vector* VectorMetaType::Construct(math::Vector* vector)
	{
		vector->x = 0.0f;
		vector->y = 0.0f;
		vector->z = 0.0f;
		return vector;
	}

	// FUNCTION: ENGINE 0x105FB9E0
	void* VectorMetaType::Create()
	{
		core::HeapScope scope(gMetaHeap);
		math::Vector* vector = (math::Vector*)core::HeapAllocAligned(core::GetCurrentHeap(), 0xC, 0x10);
		void* result;
		if (vector != 0)
		{
			result = Construct(vector);
		}
		else
		{
			result = 0;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105FBA40
	void VectorMetaType::Destroy(void* object)
	{
		core::FreeAligned(object);
	}

	// FUNCTION: ENGINE 0x105FBA50
	void VectorMetaType::Copy(void* destination, const void* source, int a)
	{
		Set(destination, Get(source));
	}

	// FUNCTION: ENGINE 0x105FBA80
	int VectorMetaType::Unknown9(int a, int b)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x105FBA90
	void VectorMetaType::Describe(MemberEntry** cursor, void* object, int unused)
	{
		(*cursor)->type = this;
		(*cursor)->object = object;
		*cursor += 1;
	}

	// FUNCTION: ENGINE 0x105FBAB0
	void VectorMetaType::WriteBinaryShort(WriteContext* context, const void* object)
	{
		const math::Vector* vector = Get(object);
		math::Vector value;
		value.x = vector->x;
		value.y = vector->y;
		value.z = vector->z;
		context->writer->Write(&value.x, 1, 4);
		context->writer->Write(&value.y, 1, 4);
		context->writer->Write(&value.z, 1, 4);
	}
}
