// content::ColourMetaType: the slots of the colour meta type (unit 0x10601450 - 0x10601BB0).
#include "code/content/colourmetatype.h"
#include "code/core/heap.h"
#include "code/math/pddicolour.h"

namespace content
{
	// The heap the meta system makes its values in (0x11276928, name guessed)
	extern int gMetaHeap;

	// FUNCTION: ENGINE 0x10601450
	const char* GetColourTypeName()
	{
		return "colour";
	}

	// FUNCTION: ENGINE 0x10601460
	ColourMetaType::ColourMetaType(const char* code)
		: MetaType(code)
	{
	}

	// FUNCTION: ENGINE 0x10601480
	void ColourMetaType::ReadBinary(ReadContext* context, void* object, int a, int b)
	{
		float value;
		context->reader->Read(&value, 1, 4);
		math::Colour128* colour = (math::Colour128*)object;
		colour->r = value;
		context->reader->Read(&value, 1, 4);
		colour->g = value;
		context->reader->Read(&value, 1, 4);
		colour->b = value;
		context->reader->Read(&value, 1, 4);
		colour->a = value;
	}

	// FUNCTION: ENGINE 0x10601500
	void ColourMetaType::WriteBinary(WriteContext* context, const void* object, int a)
	{
		const math::Colour128* colour = (const math::Colour128*)object;
		float value = colour->r;
		context->writer->Write(&value, 1, 4);
		value = colour->g;
		context->writer->Write(&value, 1, 4);
		value = colour->b;
		context->writer->Write(&value, 1, 4);
		value = colour->a;
		context->writer->Write(&value, 1, 4);
	}

	// FUNCTION: ENGINE 0x10601580
	bool ColourMetaType::ReadText(TextReadStream* reader, void* object, int a, int b)
	{
		float value;
		if (reader->ReadFloat(&value))
		{
			math::Colour128* colour = (math::Colour128*)object;
			colour->r = value;
			if (reader->ReadFloat(&value))
			{
				colour->g = value;
				if (reader->ReadFloat(&value))
				{
					colour->b = value;
					if (reader->ReadFloat(&value))
					{
						colour->a = value;
						return true;
					}
				}
			}
		}
		reader->Error("Expecting 4 float values RGBA at line %d", reader->GetLine());
		return false;
	}

	// FUNCTION: ENGINE 0x10601620
	void ColourMetaType::WriteText(TextWriter* writer, const void* object, int a)
	{
		const math::Colour128* colour = (const math::Colour128*)object;
		float value = colour->r;
		writer->WriteFloat(&value);
		value = colour->g;
		writer->WriteFloat(&value);
		value = colour->b;
		writer->WriteFloat(&value);
		value = colour->a;
		writer->WriteFloat(&value);
	}

	// FUNCTION: ENGINE 0x10601690
	math::Colour128* ColourMetaType::Identity(math::Colour128* colour)
	{
		return colour;
	}

	// FUNCTION: ENGINE 0x106016A0
	void ColourMetaType::Assign(math::Colour128* destination, const math::Colour128* source)
	{
		*destination = *source;
	}

	// FUNCTION: ENGINE 0x106016D0
	void ColourMetaType::Destroy(void* object)
	{
		operator delete(object);
	}

	// FUNCTION: ENGINE 0x106016E0
	void ColourMetaType::Copy(void* destination, const void* source, int a)
	{
		*(math::Colour128*)destination = *(const math::Colour128*)source;
	}

	// FUNCTION: ENGINE 0x10601710
	int ColourMetaType::Unknown9(int a, int b)
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x10601720
	void ColourMetaType::Describe(MemberEntry** cursor, void* object, int unused)
	{
		(*cursor)->type = this;
		(*cursor)->object = object;
		*cursor += 1;
	}

	// FUNCTION: ENGINE 0x10601740
	void ColourMetaType::WriteBinaryShort(WriteContext* context, const void* object)
	{
		const math::Colour128* colour = (const math::Colour128*)object;
		float value = colour->r;
		context->writer->Write(&value, 1, 4);
		value = colour->g;
		context->writer->Write(&value, 1, 4);
		value = colour->b;
		context->writer->Write(&value, 1, 4);
		value = colour->a;
		context->writer->Write(&value, 1, 4);
	}

	// FUNCTION: ENGINE 0x106017C0
	math::Colour128* ColourMetaType::Construct(math::Colour128* colour)
	{
		colour->r = 1.0f;
		colour->g = 1.0f;
		colour->b = 1.0f;
		colour->a = 1.0f;
		return colour;
	}

	// FUNCTION: ENGINE 0x106017F0
	void* ColourMetaType::Create()
	{
		core::HeapScope scope(gMetaHeap);
		math::Colour128* colour = new math::Colour128;
		void* result;
		if (colour != 0)
		{
			result = Construct(colour);
		}
		else
		{
			result = 0;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10601840
	// NONMATCHING: the default colour's conversion and the compare keep other registers and an other order, best 22.1%
#ifdef NONMATCHING
	bool ColourMetaType::Compare(ReadContext* first, const char* firstName, ReadContext* second,
		const char* secondName, int unused, TextWriter* log)
	{
		const unsigned char* black = (const unsigned char*)&math::pddiColour::BLACK;
		math::Colour128 a;
		a.r = (float)black[2] * (1.0f / 255.0f);
		a.g = (float)black[1] * (1.0f / 255.0f);
		a.b = (float)black[0] * (1.0f / 255.0f);
		a.a = (float)black[3] * (1.0f / 255.0f);
		math::Colour128 b(a.r, a.g, a.b, a.a);
		float value;
		if (first != 0)
		{
			first->reader->Read(&value, 1, 4);
			a.r = value;
			first->reader->Read(&value, 1, 4);
			a.g = value;
			first->reader->Read(&value, 1, 4);
			a.b = value;
			first->reader->Read(&value, 1, 4);
			a.a = value;
		}
		if (second != 0)
		{
			second->reader->Read(&value, 1, 4);
			b.r = value;
			second->reader->Read(&value, 1, 4);
			b.g = value;
			second->reader->Read(&value, 1, 4);
			b.b = value;
			second->reader->Read(&value, 1, 4);
			b.a = value;
		}
		if (a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a)
		{
			value = a.r;
			log->WriteFloat(&value);
			value = a.g;
			log->WriteFloat(&value);
			value = a.b;
			log->WriteFloat(&value);
			value = a.a;
			log->WriteFloat(&value);
			return true;
		}
		if (first != 0)
		{
			log->NewLine();
			log->Write("*******************", false);
			log->Write(firstName, false);
			log->NewLine();
			value = a.r;
			log->WriteFloat(&value);
			value = a.g;
			log->WriteFloat(&value);
			value = a.b;
			log->WriteFloat(&value);
			value = a.a;
			log->WriteFloat(&value);
		}
		if (second != 0)
		{
			log->NewLine();
			log->Write("*******************", false);
			log->Write(secondName, false);
			log->NewLine();
			value = b.r;
			log->WriteFloat(&value);
			value = b.g;
			log->WriteFloat(&value);
			value = b.b;
			log->WriteFloat(&value);
			value = b.a;
			log->WriteFloat(&value);
		}
		log->NewLine();
		log->Write("*******************", false);
		log->NewLine();
		return false;
	}
#endif
}
