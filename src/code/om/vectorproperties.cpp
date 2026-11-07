// The dynamic property of the vector of three numbers (RTTI: om::DynamicProperty<om::Vector>, its commands and delegate):
// explicit instantiations of the property classes (most members have no caller of their own) and the text and binary
// forms of the vector. Unit 0x10461CD0 - 0x10463990 (no assert path; the file name is a guess).
#include "code/om/dynamicproperty.h"
#include "code/om/textvalue.h"
#include "code/om/vector.h"

#pragma warning(disable: 4661)

namespace om
{
	// The property builds the value of a new vector with the three numbers set in order
	template<> DynamicProperty<Vector>::DynamicProperty(const ClassName& newName, Vector newValue) :
		value(VectorInOrder()),
		type(FindMetaType(typeid(Vector))),
		name(0)
	{
		SetName(newName);
		Set(newValue);
	}

	// FUNCTION: ENGINE 0x10462580
	bool ReadText(const TextValue* text, Vector* vector)
	{
		TextValue* x = text->FindChild("x");
		TextValue* y = text->FindChild("y");
		TextValue* z = text->FindChild("z");
		if (x != 0)
		{
			ReadText(x, &vector->values[0]);
		}
		if (y != 0)
		{
			ReadText(y, &vector->values[1]);
		}
		if (z != 0)
		{
			// the engine reads the node of "x" again
			ReadText(x, &vector->values[2]);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10462690
	void WriteText(TextValue* text, const Vector& vector)
	{
		WriteText(new TextNode(text, String::Wrap("x")), vector.values[0]);
		WriteText(new TextNode(text, String::Wrap("y")), vector.values[1]);
		WriteText(new TextNode(text, String::Wrap("z")), vector.values[2]);
	}

	// FUNCTION: ENGINE 0x104624B0
	bool ReadBinary(BinaryStream* stream, Vector* vector)
	{
		return ReadBinary(stream, &vector->values[0]) && ReadBinary(stream, &vector->values[1])
			&& ReadBinary(stream, &vector->values[2]);
	}

	// FUNCTION: ENGINE 0x10462510
	bool WriteBinary(BinaryStream* stream, const Vector& vector)
	{
		return WriteBinary(stream, vector.values[0]) && WriteBinary(stream, vector.values[1])
			&& WriteBinary(stream, vector.values[2]);
	}

	// The reader of the text form is left to the engine (the scheduling of its loads differs: 95 %)
	template<> bool DynamicProperty<Vector>::ReadText(const TextValue* parent);

	template class DynamicProperty<Vector>;
	template class CommandMember0Const<DynamicProperty<Vector>, DynamicProperty<Vector>, Vector>;
	template class CommandMember1<DynamicProperty<Vector>, DynamicProperty<Vector>, void, Vector>;
	template class DelegateProperty<Vector>;
	template class CommandDelegate<Vector>;
	template class Command0<Vector>;
	template class Command1<void, Vector>;
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10461CD0
// FUNCTION: ENGINE 0x10461CF0
// FUNCTION: ENGINE 0x10461E80
// FUNCTION: ENGINE 0x10462140
// FUNCTION: ENGINE 0x10462160
// FUNCTION: ENGINE 0x10462250
// FUNCTION: ENGINE 0x10462260
// FUNCTION: ENGINE 0x10462280
// FUNCTION: ENGINE 0x104622A0
// FUNCTION: ENGINE 0x104622D0
// FUNCTION: ENGINE 0x104622F0
// FUNCTION: ENGINE 0x10462300
// FUNCTION: ENGINE 0x10462310
// FUNCTION: ENGINE 0x10462320
// FUNCTION: ENGINE 0x10462340
// FUNCTION: ENGINE 0x10462350
// FUNCTION: ENGINE 0x10462360
// FUNCTION: ENGINE 0x10462390
// FUNCTION: ENGINE 0x104623C0
// FUNCTION: ENGINE 0x104623D0
// FUNCTION: ENGINE 0x104623F0
// FUNCTION: ENGINE 0x10462400
// FUNCTION: ENGINE 0x10462420
// FUNCTION: ENGINE 0x10462470
// FUNCTION: ENGINE 0x10462480
// FUNCTION: ENGINE 0x10462490
// FUNCTION: ENGINE 0x104624A0
// FUNCTION: ENGINE 0x10462810
// FUNCTION: ENGINE 0x10462860
// FUNCTION: ENGINE 0x104628A0
// FUNCTION: ENGINE 0x104628F0
// FUNCTION: ENGINE 0x10462920
// FUNCTION: ENGINE 0x10462940
// FUNCTION: ENGINE 0x104629C0
// FUNCTION: ENGINE 0x104629E0
// FUNCTION: ENGINE 0x10462A00
// FUNCTION: ENGINE 0x10462A40
// FUNCTION: ENGINE 0x10462A50
// FUNCTION: ENGINE 0x10462A70
// FUNCTION: ENGINE 0x10462AA0
// FUNCTION: ENGINE 0x10462AE0
// FUNCTION: ENGINE 0x10462B00
// FUNCTION: ENGINE 0x10462B20
// FUNCTION: ENGINE 0x10462B50
// FUNCTION: ENGINE 0x10462B60
// FUNCTION: ENGINE 0x10462B80
// FUNCTION: ENGINE 0x10462E50
// FUNCTION: ENGINE 0x10463010
// FUNCTION: ENGINE 0x10463060
// FUNCTION: ENGINE 0x104630D0
// FUNCTION: ENGINE 0x10463100
// FUNCTION: ENGINE 0x10463170
// FUNCTION: ENGINE 0x10463190
// FUNCTION: ENGINE 0x104631D0
// FUNCTION: ENGINE 0x10463200
// FUNCTION: ENGINE 0x10463240
// FUNCTION: ENGINE 0x10463280
// FUNCTION: ENGINE 0x104632E0
// FUNCTION: ENGINE 0x10463920
