// content::MatrixMetaType: the matrix meta type's slots (unit 0x10604360 - 0x10606170; only the small ones so far).
#include "code/content/metatype.h"
#include "code/core/heap.h"

namespace content
{
	// FUNCTION: ENGINE 0x10604360
	const char* GetMatrixTypeName()
	{
		return "matrix";
	}

	// FUNCTION: ENGINE 0x10604370
	MatrixMetaType::MatrixMetaType(bool unknown8, bool unknown9, const char* code)
		: MetaType(code)
	{
		flag8 = unknown8;
		flag9 = unknown9;
	}

	// FUNCTION: ENGINE 0x106044A0
	void MatrixMetaType::Destroy(void* object)
	{
		if (!flag9)
		{
			core::FreeAligned(object);
			return;
		}
		if (flag8)
		{
			core::FreeAligned(object);
			return;
		}
		core::FreeAligned(object);
	}

	// FUNCTION: ENGINE 0x10604520
	int MatrixMetaType::Unknown9(int a, int b)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10604530
	void MatrixMetaType::Describe(MemberEntry** cursor, void* object, int unused)
	{
		(*cursor)->type = this;
		(*cursor)->object = object;
		*cursor += 1;
	}

	// FUNCTION: ENGINE 0x10604550
	void MatrixMetaType::WriteBinaryShort(WriteContext* context, const void* object)
	{
		if (!flag9)
		{
			context->writer->Write(object, 0x10, 4);
			return;
		}
		const float* values = (const float*)object;
		if (flag8)
		{
			context->writer->Write(values + 4, 3, 4);
			context->writer->Write(values, 4, 4);
			context->writer->Write(values + 7, 3, 4);
			return;
		}
		context->writer->Write(values + 4, 3, 4);
		context->writer->Write(values, 4, 4);
	}
}
