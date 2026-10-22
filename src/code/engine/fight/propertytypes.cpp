// The property classes per value kind, the lists of properties a class registers and the reading of the values from a
// reader (part of the unit 0x105A2440 - 0x105B3680; the classes' declarations are in trackfactory.h).
#include "code/core/heap.h"
#include "code/core/hash.h"
#include "code/engine/fight/bitfieldproperty.h"
#include "code/engine/fight/fightsystem.h"
#include "code/engine/fight/reader.h"
#include "code/engine/fight/trackfactory.h"
#include <ctype.h>
#include <new>

namespace engine
{
	// The function that shows a script error and its word (set with SetScriptErrorCallback)
	typedef int (*ScriptErrorCallback)(const int* error, int argument);
	// GLOBAL: ENGINE 0x11276208
	ScriptErrorCallback gScriptErrorCallback;
	// GLOBAL: ENGINE 0x1127620C
	int gScriptErrorArgument;

	// 0x105A8490 / 0x105A84B0: install the callback / read it back
	void SetScriptErrorCallback(ScriptErrorCallback function, int argument);
	void GetScriptErrorCallback(ScriptErrorCallback* function, int* argument);

	// FUNCTION: ENGINE 0x105A8490
	void SetScriptErrorCallback(ScriptErrorCallback function, int argument)
	{
		gScriptErrorCallback = function;
		gScriptErrorArgument = argument;
	}

	// FUNCTION: ENGINE 0x105A84B0
	void GetScriptErrorCallback(ScriptErrorCallback* function, int* argument)
	{
		*function = gScriptErrorCallback;
		*argument = gScriptErrorArgument;
	}

	// FUNCTION: ENGINE 0x105A84D0
	int ShowScriptError(int kind, const char* text, const char* title, unsigned int first, unsigned int second,
		int line)
	{
		int result = 0;
		if (gScriptErrorCallback != 0)
		{
			int error[6];
			error[0] = kind;
			error[1] = (int)text;
			error[2] = (int)title;
			error[3] = (int)first;
			error[4] = (int)second;
			error[5] = line;
			result = gScriptErrorCallback(error, gScriptErrorArgument);
		}
		return result;
	}
}

namespace core
{
	// The 32-bit name of a text; this unit keeps a copy of it
	inline __declspec(noinline) Name<CaseInsensitiveKey32>::Name(const char* text, int unknown)
		: hash(Hash32(text, 0))
	{
	}
}

namespace fight
{
	// GLOBAL: ENGINE 0x110B42BC
	int gFightHeaps[3] = { 0, 1, 0 };

	// FUNCTION: ENGINE 0x105A83B0
	int GetHeapId(int index)
	{
		return gFightHeaps[index];
	}

	// FUNCTION: ENGINE 0x105A83C0
	int SetHeapId(int index, int heap)
	{
		int old = gFightHeaps[index];
		gFightHeaps[index] = heap;
		return old;
	}

	// FUNCTION: ENGINE 0x105A8420
	void RegisterPropertyList(Property** properties, Property*** list)
	{
		unsigned int count = 0;
		if (properties[0] != 0)
		{
			do
			{
				count = count + 1;
			}
			while (properties[count] != 0);
		}
		properties[count] = 0;
		count = count + 1;
		*list = new Property*[count];
		for (unsigned int i = 0; i < count; i++)
		{
			(*list)[i] = properties[i];
		}
	}

	// FUNCTION: ENGINE 0x105A9650
	void FreePropertyList(Property*** list)
	{
		if (*list != 0)
		{
			for (int i = 0; (*list)[i] != 0; i++)
			{
				Property* property = (*list)[i];
				if (property != 0)
				{
					operator delete(property);
				}
			}
			operator delete(*list);
			*list = 0;
		}
	}

	// ---- The properties' constructors ----------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A9C60
	Property::Property(const char* newName)
	{
		Name temp(newName, 0);
		SetName(temp);
	}

	// FUNCTION: ENGINE 0x105A8C40
	PropertyTypeBool::PropertyTypeBool(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A8C60
	PropertyTypeGroup::PropertyTypeGroup(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A8E70
	PropertyTypeInt::PropertyTypeInt(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A8E90
	PropertyTypeFloat::PropertyTypeFloat(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A8EB0
	PropertyTypeString::PropertyTypeString(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A8F50
	PropertyTypeName32::PropertyTypeName32(const char* newName)
		: PropertyTypeString(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A8FF0
	PropertyTypeStringList::PropertyTypeStringList(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A9090
	PropertyTypeScript::PropertyTypeScript(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A90C0
	PropertyTypeEnum::PropertyTypeEnum(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A91E0
	PropertyTypeVector::PropertyTypeVector(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A9200
	PropertyTypeColour::PropertyTypeColour(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A9220
	PropertyTypeBranch::PropertyTypeBranch(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A9240
	PropertyTypeConditionGroup::PropertyTypeConditionGroup(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A9260
	PropertyTypeTrackGroup::PropertyTypeTrackGroup(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A92B0
	PropertyTypeBitfield::PropertyTypeBitfield(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A96A0
	PropertyTypeName::PropertyTypeName(const char* newName)
		: PropertyTypeString(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A96C0
	PropertyTypeNameList::PropertyTypeNameList(const char* newName)
		: PropertyTypeStringList(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A90B0
	int PropertyTypeScript::GetType() const
	{
		return 5;
	}

	// ---- Reading a value from a reader and handing it to the property's setter ------------------------------------

	// FUNCTION: ENGINE 0x105A8530
	bool PropertyTypeBool::Slot6(int object, int context, void* source)
	{
		bool value = false;
		if (((Reader*)source)->ReadBool(name, &value))
		{
			return Set((void*)object, value);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A8570
	bool PropertyTypeGroup::Slot6(int object, int context, void* source)
	{
		bool value = false;
		if (((Reader*)source)->ReadBool(name, &value))
		{
			return Set((void*)object, value);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A85C0
	bool PropertyTypeInt::Slot6(int object, int context, void* source)
	{
		int value = 0;
		if (((Reader*)source)->ReadInt(name, &value))
		{
			return Set((void*)object, value);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A8610
	bool PropertyTypeFloat::Slot6(int object, int context, void* source)
	{
		float value = 0.0f;
		if (((Reader*)source)->ReadFloat(name, &value))
		{
			return Set((void*)object, value);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A8660
	bool PropertyTypeString::Slot6(int object, int context, void* source)
	{
		char text[1024] = { 0 };
		if (((Reader*)source)->ReadString(name, text, 1024))
		{
			return Set((void*)object, text);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A86D0
	bool PropertyTypeStringList::Slot6(int object, int context, void* source)
	{
		char text[1024] = { 0 };
		if (((Reader*)source)->ReadString(name, text, 1024))
		{
			return SetText((void*)object, text);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A8740
	bool PropertyTypeScript::Slot6(int object, int context, void* source)
	{
		Reader* reader = (Reader*)source;
		int length = 0;
		bool result = reader->GetStringLength(name, &length);
		if (result)
		{
			char* text = (char*)core::HeapAlloc(GetHeapId(1), length + 1);
			text[0] = 0;
			result = reader->ReadString(name, text, length + 1);
			if (result)
			{
				result = Set((void*)object, text, length);
			}
			core::Free(text);
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105A87D0
	bool PropertyTypeVector::Slot6(int object, int context, void* source)
	{
		math::Vector value(0.0f, 0.0f, 0.0f);
		if (((Reader*)source)->ReadVector(name, &value))
		{
			return Set((void*)object, value);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A8830
	bool PropertyTypeColour::Slot6(int object, int context, void* source)
	{
		math::Colour128 value(1.0f, 0.0f, 1.0f, 1.0f);
		if (((Reader*)source)->ReadColour(name, &value))
		{
			return Set((void*)object, value);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A8F00
	bool PropertyTypeName::Slot6(int object, int context, void* source)
	{
		Name value;
		if (((Reader*)source)->ReadName(name, &value))
		{
			return Set((void*)object, value);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A8ED0
	bool PropertyTypeName::Set(void* object, const char* text)
	{
		Name value(text, 1);
		return Set(object, value);
	}

	// FUNCTION: ENGINE 0x105A9040
	bool PropertyTypeNameList::Slot6(int object, int context, void* source)
	{
		Name value;
		if (((Reader*)source)->ReadName(name, &value))
		{
			return Set((void*)object, value);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A9010
	bool PropertyTypeNameList::SetText(void* object, const char* text)
	{
		Name value(text, 1);
		return Set(object, value);
	}

	// FUNCTION: ENGINE 0x105A8FA0
	// EQUIVALENT: calls the unit's own copy of the 32-bit name's constructor (0x105A8BB0) where the symbol table keeps the first copy (0x1007EE60); 98.5 %
	bool PropertyTypeName32::Slot6(int object, int context, void* source)
	{
		core::Name<core::CaseInsensitiveKey32> value;
		if (((Reader*)source)->ReadName32(name, &value))
		{
			return Set((void*)object, value);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A8F70
	// EQUIVALENT: calls the unit's own copy of the 32-bit name's constructor (0x105A8B90) where the symbol table keeps the first copy (0x1008CC20); 97.6 %
	bool PropertyTypeName32::Set(void* object, const char* text)
	{
		core::Name<core::CaseInsensitiveKey32> value(text, 1);
		return Set(object, value);
	}

	// FUNCTION: ENGINE 0x105A90E0
	bool PropertyTypeEnum::Slot6(int object, int context, void* source)
	{
		Reader* reader = (Reader*)source;
		int value = -1;
		Name text;
		bool result = reader->ReadEnum(name, &value, &text);
		if (result)
		{
			if (value >= 0)
			{
				if (value >= GetCount((void*)object))
				{
					ReportReadError(reader, "%d is not a valid enumerated value.", value);
					result = false;
				}
				else
				{
					result = Set((void*)object, value);
				}
			}
			else
			{
				int count = GetCount((void*)object);
				int i;
				for (i = 0; i < count; i++)
				{
					const EnumEntry* entry = GetEntry((void*)object, i);
					if (entry->name == text)
					{
						result = Set((void*)object, i);
						break;
					}
				}
				if (i >= count)
				{
					unsigned __int64 hash = text.GetHash();
					ReportReadError(reader, "\"0x%08x%08x\" is not a valid enumerated value.", hash >> 32, hash);
					result = false;
				}
			}
		}
		return result;
	}

	// ---- Handing a call on to the node a property stands for ------------------------------------------------------

	// FUNCTION: ENGINE 0x105A88A0
	void PropertyTypeBranch::Slot2(int object, int other)
	{
		BranchHolder* holder = Set((void*)object);
		if (holder != 0)
		{
			holder->Resolve((Branch*)other);
		}
	}

	// FUNCTION: ENGINE 0x105A88C0
	void PropertyTypeBranch::Slot3(int object, int other)
	{
		BranchHolder* holder = Set((void*)object);
		if (holder != 0)
		{
			holder->Clear((Branch*)other);
		}
	}

	// FUNCTION: ENGINE 0x105A88E0
	bool PropertyTypeBranch::Slot6(int object, int context, void* source)
	{
		BranchHolder* holder = Set((void*)object);
		if (holder != 0)
		{
			return holder->Load(name, context, (Reader*)source);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A8920
	void PropertyTypeBranch::Slot5(int object, int other)
	{
		BranchHolder* holder = Set((void*)object);
		if (holder != 0)
		{
			holder->SetBase((Branch*)other);
		}
	}

	// FUNCTION: ENGINE 0x105A8940
	void PropertyTypeConditionGroup::Slot5(int object, int other)
	{
		ConditionList* list = Set((void*)object);
		if (list != 0)
		{
			list->ForEachSlot2(other);
		}
	}

	// FUNCTION: ENGINE 0x105A8960
	void PropertyTypeConditionGroup::Slot2(int object, int other)
	{
		ConditionList* list = Set((void*)object);
		if (list != 0)
		{
			list->ForEachSlot3(other);
		}
	}

	// FUNCTION: ENGINE 0x105A8980
	void PropertyTypeConditionGroup::Slot3(int object, int other)
	{
		ConditionList* list = Set((void*)object);
		if (list != 0)
		{
			list->ForEachSlot4(other);
		}
	}

	// FUNCTION: ENGINE 0x105A89A0
	bool PropertyTypeConditionGroup::Slot6(int object, int context, void* source)
	{
		ConditionList* list = Set((void*)object);
		if (list != 0)
		{
			return list->Load(name, context, (Reader*)source);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A89E0
	void PropertyTypeTrackGroup::Slot5(int object, int other)
	{
		TrackGroup* group = Set((void*)object);
		if (group != 0)
		{
			group->ForEachSlot2(other);
		}
	}

	// FUNCTION: ENGINE 0x105A8A00
	void PropertyTypeTrackGroup::Slot2(int object, int other)
	{
		TrackGroup* group = Set((void*)object);
		if (group != 0)
		{
			group->ForEachSlot3(other);
		}
	}

	// FUNCTION: ENGINE 0x105A8A20
	void PropertyTypeTrackGroup::Slot3(int object, int other)
	{
		TrackGroup* group = Set((void*)object);
		if (group != 0)
		{
			group->ForEachSlot4(other);
		}
	}

	// FUNCTION: ENGINE 0x105A8A40
	void PropertyTypeTrackGroup::Slot4(int object, int otherProperty, int otherObject, int arg)
	{
		TrackGroup* group = Set((void*)object);
		TrackGroup* other = otherProperty != 0 ? ((PropertyTypeTrackGroup*)otherProperty)->Set((void*)otherObject) : 0;
		if (group != 0)
		{
			group->ForEachSlot14(other, arg);
		}
	}

	// FUNCTION: ENGINE 0x105A8A80
	bool PropertyTypeTrackGroup::Slot6(int object, int context, void* source)
	{
		TrackGroup* group = Set((void*)object);
		if (group != 0)
		{
			return group->Load(name, context, (Reader*)source);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A8AC0
	void PropertyTypeItem::Slot5(int object, int other)
	{
		Item* item = Set((void*)object);
		if (item != 0)
		{
			item->Slot2(other);
		}
	}

	// FUNCTION: ENGINE 0x105A8AF0
	void PropertyTypeItem::Slot2(int object, int other)
	{
		Item* item = Set((void*)object);
		if (item != 0)
		{
			item->Slot3(other);
		}
	}

	// FUNCTION: ENGINE 0x105A8B20
	void PropertyTypeItem::Slot3(int object, int other)
	{
		Item* item = Set((void*)object);
		if (item != 0)
		{
			item->Slot4(other);
		}
	}

	// FUNCTION: ENGINE 0x105A8B50
	bool PropertyTypeItem::Slot6(int object, int context, void* source)
	{
		Item* item = Set((void*)object);
		if (item != 0)
		{
			return item->Slot5((int)&name, context, (int)source);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A9280
	PropertyTypeItem::PropertyTypeItem(const char* newName)
		: Property(newName)
	{
	}

	// FUNCTION: ENGINE 0x105A92A0
	int PropertyTypeItem::GetType() const
	{
		return 13;
	}

	// FUNCTION: ENGINE 0x105A92D0
	bool PropertyTypeBitfield::Slot6(int object, int context, void* source)
	{
		Reader* reader = (Reader*)source;
		int number = 0;
		char text[1024] = { 0 };
		if (reader->ReadFlags(name, &number, text, 1024))
		{
			if (text[0] != 0)
			{
				int bits = 0;
				char token[1024] = { 0 };
				const char* position = text;
				do
				{
					while (*position != 0 && (isspace(*position) || *position == ','))
					{
						position = position + 1;
					}
					int length = 0;
					while (*position != 0 && *position != ',')
					{
						token[length] = *position;
						position = position + 1;
						length = length + 1;
					}
					token[length] = 0;
					if (length > 0)
					{
						Name key(token, 1);
						int index = 0;
						const EnumEntry* entry = GetEntry((void*)object, index);
						bool found = false;
						while (true)
						{
							Name terminator(0, 1);
							if (entry->name == terminator)
							{
								break;
							}
							if (key == entry->name)
							{
								found = true;
								break;
							}
							index = index + 1;
							entry = GetEntry((void*)object, index);
						}
						if (found)
						{
							bits = bits | (1 << index);
						}
						else
						{
							ReportReadError(reader, "\"%s\" is not a valid bitfield token.", token);
						}
					}
				}
				while (*position != 0);
				return Set((void*)object, bits);
			}
			return Set((void*)object, number);
		}
		return false;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x105A8BC0
