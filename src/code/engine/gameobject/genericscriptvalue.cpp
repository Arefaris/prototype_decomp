// engine::GenericScriptValue: see the header.
#include "code/container/string.h"
#include "code/content/enummetatype.h"
#include "code/content/stringmetatype.h"
#include "code/core/strings.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/genericscriptvalue.h"
#include "code/engine/luascriptmanager.h"
#include "code/lua/lua.h"
#include "code/pure3d/context.h"
#include <new>
#include <stdio.h>
#include <stdlib.h>

namespace engine
{
	// Lua values as the scripts hold them (the Lua binding of the vector and the name, another unit)
	int LuaPushVector(lua_State* L, const math::Vector& vector);
	const math::Vector* LuaToVector(lua_State* L, int index);
	bool LuaIsVector(lua_State* L, int index);
	bool LuaIsUid(lua_State* L, int index);
	int LuaPushName(lua_State* L, const core::Name<core::CaseSensitiveKey>& name);
	const core::Name<core::CaseSensitiveKey>* LuaToName(lua_State* L, int index);

	struct ScriptText
	{
		// 0x10871830: room for size characters
		static ScriptText* Create(int size);
		// 0x10871860 / 0x10871870
		char* Data();
		const char* Data() const;
		// 0x10871880
		void Copy(const char* source);
		// 0x108718A0
		unsigned int Capacity() const;

		int capacity;
		char characters[1];
	};

	ScriptText* ScriptText::Create(int size)
	{
		ScriptText* block = (ScriptText*)new (0x7b) char[size + 4];
		block->capacity = size;
		return block;
	}

	char* ScriptText::Data()
	{
		return characters;
	}

	const char* ScriptText::Data() const
	{
		return characters;
	}

	void ScriptText::Copy(const char* source)
	{
		core::StrNCpy(Data(), source, (unsigned int)capacity);
	}

	unsigned int ScriptText::Capacity() const
	{
		return capacity;
	}
}

namespace content
{
	static const EnumValue sGenericScriptValueTypes[] =
	{
		{ "Undefined", 0 },
		{ "Bool", 1 },
		{ "Int", 2 },
		{ "Float", 3 },
		{ "String", 4 },
		{ "UID", 5 },
		{ "Vector", 6 },
		{ "GameObjectHandle", 7 },
		{ "LuaTable", 8 },
		{ "LuaFunction", 9 },
		{ "LuaThread", 10 }
	};

	// FUNCTION: ENGINE 0x108717C0
	template<> void EnumInfo<engine::GenericScriptValue::Type>::Get(const char** name, const EnumValue** values,
		int* count, const char** code)
	{
		*name = "GenericScriptValue::Type";
		*code = "pn";
		*values = sGenericScriptValueTypes;
		*count = 11;
	}
}

namespace engine
{
	// FUNCTION: ENGINE 0x108717F0
	content::ClassInfo* GenericScriptValue::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "GenericScriptValue";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108718B0
	GenericScriptValue::GenericScriptValue()
	{
		type = TYPE_UNDEFINED;
	}

	// FUNCTION: ENGINE 0x108718C0
	bool GenericScriptValue::GetBool() const
	{
		return boolValue;
	}

	// FUNCTION: ENGINE 0x108718D0
	int GenericScriptValue::GetInt() const
	{
		return intValue;
	}

	// FUNCTION: ENGINE 0x108718E0
	float GenericScriptValue::GetFloat() const
	{
		return floatValue;
	}

	// FUNCTION: ENGINE 0x108718F0
	const char* GenericScriptValue::GetText() const
	{
		return text->Data();
	}

	// FUNCTION: ENGINE 0x10871900
	const core::Name<core::CaseSensitiveKey>& GenericScriptValue::GetName() const
	{
		return *name;
	}

	// FUNCTION: ENGINE 0x10871910
	const math::Vector& GenericScriptValue::GetVector() const
	{
		return *vector;
	}

	// FUNCTION: ENGINE 0x10871920
	GameObjectHandle GenericScriptValue::GetHandle() const
	{
		SerializedHandle saved;
		saved.value = handle;
		return DeserializeHandle(saved);
	}

	// FUNCTION: ENGINE 0x10871940
	void GenericScriptValue::PushToLua(lua_State* L) const
	{
		switch (type)
		{
		case TYPE_UNDEFINED:
			lua_pushnil(L);
			break;
		case TYPE_BOOL:
			lua_pushboolean(L, boolValue != 0);
			break;
		case TYPE_INT:
			lua_pushinteger(L, intValue);
			break;
		case TYPE_FLOAT:
			lua_pushnumber(L, floatValue);
			break;
		case TYPE_TEXT:
			lua_pushstring(L, text->Data());
			break;
		case TYPE_NAME:
			LuaPushName(L, *name);
			break;
		case TYPE_VECTOR:
			LuaPushVector(L, *vector);
			break;
		case TYPE_HANDLE:
			lua_pushlightuserdata(L, (void*)handle);
			break;
		case TYPE_TABLE:
			lua_rawgeti(L, LUA_REGISTRYINDEX, reference);
			break;
		case TYPE_FUNCTION:
			lua_rawgeti(L, LUA_REGISTRYINDEX, reference);
			break;
		case TYPE_THREAD:
			lua_rawgeti(L, LUA_REGISTRYINDEX, reference);
			break;
		default:
			lua_pushnil(L);
			break;
		}
	}

	// FUNCTION: ENGINE 0x10871AF0
	// EQUIVALENT: register allocation only: the engine pushes the high word of a name's hash from eax, ours from edx, 99.5 %
	const char* GenericScriptValue::ToString() const
	{
		static container::StringC<256> sText;
		sText.Clear();
		switch (type)
		{
		case TYPE_UNDEFINED:
			return sText.ConstData();
		case TYPE_BOOL:
			sText.Append(boolValue ? "true" : "false");
			return sText.ConstData();
		case TYPE_INT:
			sText.Format("%d", intValue);
			return sText.ConstData();
		case TYPE_FLOAT:
			sText.Format("%.7g", floatValue);
			return sText.ConstData();
		case TYPE_TEXT:
			sText.Append(GetText());
			return sText.ConstData();
		case TYPE_NAME:
			{
				const unsigned int* hash = (const unsigned int*)&name->GetHash();
				sText.Format("0x%08x%08x", hash[1], hash[0]);
			}
			return sText.ConstData();
		case TYPE_VECTOR:
			{
				const math::Vector& vec = GetVector();
				sText.Format("%.7g %.7g %.7g", vec.x, vec.y, vec.z);
			}
			return sText.ConstData();
		case TYPE_HANDLE:
			sText.Append("<GameObjectHandle>");
			return sText.ConstData();
		case TYPE_TABLE:
			sText.Append("<LuaTable>");
			return sText.ConstData();
		case TYPE_FUNCTION:
			sText.Append("<LuaFunction>");
			return sText.ConstData();
		case TYPE_THREAD:
			sText.Append("<LuaThread>");
			break;
		}
		return sText.ConstData();
	}

	// FUNCTION: ENGINE 0x10871D40
	void GenericScriptValue::Release(int keepType)
	{
		switch (type)
		{
		case TYPE_TEXT:
			if (keepType != TYPE_TEXT)
			{
				delete[] (char*)text;
				type = TYPE_UNDEFINED;
			}
			break;
		case TYPE_NAME:
			if (keepType != TYPE_NAME)
			{
				type = TYPE_UNDEFINED;
				delete name;
			}
			break;
		case TYPE_VECTOR:
			if (keepType != TYPE_VECTOR)
			{
				type = TYPE_UNDEFINED;
				delete vector;
			}
			break;
		case TYPE_TABLE:
		case TYPE_FUNCTION:
		case TYPE_THREAD:
			{
				LuaScriptManager* script = GetScriptManager();
				if (script != 0)
				{
					luaL_unref(script->state, LUA_REGISTRYINDEX, reference);
				}
			}
			type = TYPE_UNDEFINED;
			break;
		case TYPE_UNDEFINED:
		case TYPE_BOOL:
		case TYPE_INT:
		case TYPE_FLOAT:
		case TYPE_HANDLE:
			type = TYPE_UNDEFINED;
			break;
		}
	}

	// FUNCTION: ENGINE 0x10871F10
	void GenericScriptValue::SetText(const char* newText)
	{
		Release(TYPE_TEXT);
		if (newText == 0)
		{
			newText = "";
		}
		unsigned int length = core::StrLen(newText);
		if (type == TYPE_TEXT)
		{
			if (text->Capacity() > length)
			{
				text->Copy(newText);
				return;
			}
			delete[] (char*)text;
		}
		type = TYPE_TEXT;
		text = ScriptText::Create(length + 1);
		text->Copy(newText);
	}

	// FUNCTION: ENGINE 0x10871F80
	void GenericScriptValue::SetName(const core::Name<core::CaseSensitiveKey>& newName)
	{
		Release(TYPE_NAME);
		if (type == TYPE_NAME)
		{
			*name = newName;
			return;
		}
		type = TYPE_NAME;
		name = new (0x7b) core::Name<core::CaseSensitiveKey>(newName);
	}

	// FUNCTION: ENGINE 0x10871FE0
	void GenericScriptValue::SetVector(const math::Vector& newVector)
	{
		Release(TYPE_VECTOR);
		if (type == TYPE_VECTOR)
		{
			math::Vector* target = vector;
			target->x = newVector.x;
			target->y = newVector.y;
			target->z = newVector.z;
			return;
		}
		type = TYPE_VECTOR;
		vector = new (0x7b) math::Vector(newVector);
	}

	// FUNCTION: ENGINE 0x10872050
	GenericScriptValue::~GenericScriptValue()
	{
		Release(0);
	}

	// FUNCTION: ENGINE 0x108722A0
	void GenericScriptValue::Clear()
	{
		this->~GenericScriptValue();
	}

	// FUNCTION: ENGINE 0x108722B0
	void GenericScriptValue::SetBool(bool newValue)
	{
		this->~GenericScriptValue();
		type = TYPE_BOOL;
		boolValue = newValue;
	}

	// FUNCTION: ENGINE 0x108722D0
	void GenericScriptValue::SetInt(int newValue)
	{
		this->~GenericScriptValue();
		type = TYPE_INT;
		intValue = newValue;
	}

	// FUNCTION: ENGINE 0x108722F0
	void GenericScriptValue::SetFloat(float newValue)
	{
		this->~GenericScriptValue();
		type = TYPE_FLOAT;
		floatValue = newValue;
	}

	// FUNCTION: ENGINE 0x10872310
	void GenericScriptValue::SetHandle(GameObjectHandle newValue)
	{
		this->~GenericScriptValue();
		type = TYPE_HANDLE;
		SerializedHandle saved = SerializeHandle(newValue);
		handle = saved.value;
	}

	// FUNCTION: ENGINE 0x10872060
	void GenericScriptValue::SetFromString(const char* newText)
	{
		switch (type)
		{
		case TYPE_UNDEFINED:
		case TYPE_HANDLE:
		case TYPE_TABLE:
		case TYPE_FUNCTION:
		case TYPE_THREAD:
			return;
		case TYPE_BOOL:
			if (*newText != 0 && core::StrICmp(newText, "false") != 0 && core::StrCmp(newText, "0") != 0)
			{
				boolValue = true;
			}
			else
			{
				boolValue = false;
			}
			return;
		case TYPE_INT:
			intValue = strtol(newText, 0, 10);
			return;
		case TYPE_FLOAT:
			floatValue = (float)strtod(newText, 0);
			return;
		case TYPE_TEXT:
			SetText(newText);
			return;
		case TYPE_NAME:
			if (core::StrLen(newText) == 18 && newText[0] == '0' && newText[1] == 'x')
			{
				container::StringC<9> part;
				part.Mid(newText, 2, 8);
				unsigned long high = strtoul(part.ConstData(), 0, 16);
				part.Mid(newText, 10, 8);
				unsigned long low = strtoul(part.ConstData(), 0, 16);
				unsigned long words[2];
				words[0] = low;
				words[1] = high;
				core::Name<core::CaseSensitiveKey> parsed(*(unsigned __int64*)words);
				SetName(parsed);
				return;
			}
			SetName(core::Name<core::CaseSensitiveKey>(newText, 1));
			return;
		case TYPE_VECTOR:
			{
				float values[3];
				values[0] = 0.0f;
				values[1] = 0.0f;
				values[2] = 0.0f;
				if ((int)core::StrLen(newText) < 0x80)
				{
					container::StringC<128> copy(newText);
					char* parts[3];
					if (copy.Split(' ', parts, 3) == 3)
					{
						for (int i = 0; i < 3; i++)
						{
							values[i] = (float)strtod(parts[i], 0);
						}
					}
				}
				SetVector(*(math::Vector*)values);
			}
			return;
		}
	}

	// FUNCTION: ENGINE 0x10872340
	void GenericScriptValue::SetFromLua(lua_State* L, int index)
	{
		switch (lua_type(L, index))
		{
		case LUA_TNIL:
			this->~GenericScriptValue();
			return;
		case LUA_TBOOLEAN:
			SetBool(lua_toboolean(L, index) != 0);
			return;
		case LUA_TLIGHTUSERDATA:
			this->~GenericScriptValue();
			type = TYPE_HANDLE;
			handle = (unsigned int)lua_touserdata(L, index);
			return;
		case LUA_TNUMBER:
			SetFloat((float)lua_tonumber(L, index));
			return;
		case LUA_TSTRING:
			SetText(lua_tolstring(L, index, 0));
			return;
		case LUA_TTABLE:
			this->~GenericScriptValue();
			type = TYPE_TABLE;
			break;
		case LUA_TFUNCTION:
			this->~GenericScriptValue();
			type = TYPE_FUNCTION;
			break;
		case LUA_TUSERDATA:
			if (LuaIsVector(L, index))
			{
				SetVector(*LuaToVector(L, index));
				return;
			}
			if (LuaIsUid(L, index))
			{
				SetName(*LuaToName(L, index));
				return;
			}
			this->~GenericScriptValue();
			return;
		case LUA_TTHREAD:
			this->~GenericScriptValue();
			type = TYPE_THREAD;
			break;
		default:
			return;
		}
		lua_pushvalue(L, index);
		reference = luaL_ref(L, LUA_REGISTRYINDEX);
	}

	// FUNCTION: ENGINE 0x108724B0
	void GenericScriptValue::SetType(int newType)
	{
		if (newType != type)
		{
			switch (newType)
			{
			case TYPE_UNDEFINED:
				this->~GenericScriptValue();
				break;
			default:
				this->~GenericScriptValue();
				break;
			case TYPE_BOOL:
				SetBool(false);
				break;
			case TYPE_INT:
				SetInt(0);
				break;
			case TYPE_FLOAT:
				SetFloat(0.0f);
				break;
			case TYPE_TEXT:
				SetText("");
				break;
			case TYPE_NAME:
				SetName(core::Name<core::CaseSensitiveKey>("", 0));
				break;
			case TYPE_VECTOR:
				SetVector(math::Vector(0.0f, 0.0f, 0.0f));
				break;
			case TYPE_HANDLE:
			case TYPE_TABLE:
			case TYPE_FUNCTION:
			case TYPE_THREAD:
				break;
			}
		}
	}

	// FUNCTION: ENGINE 0x10872640
	GenericScriptValue& GenericScriptValue::Assign(const GenericScriptValue& other)
	{
		switch (other.type)
		{
		case TYPE_UNDEFINED:
			this->~GenericScriptValue();
			break;
		default:
			this->~GenericScriptValue();
			break;
		case TYPE_BOOL:
			SetBool(other.boolValue);
			break;
		case TYPE_INT:
			SetInt(other.intValue);
			break;
		case TYPE_FLOAT:
			SetFloat(other.floatValue);
			break;
		case TYPE_TEXT:
			SetText(other.text->Data());
			break;
		case TYPE_NAME:
			SetName(*other.name);
			break;
		case TYPE_VECTOR:
			SetVector(*other.vector);
			break;
		case TYPE_HANDLE:
			this->~GenericScriptValue();
			type = TYPE_HANDLE;
			handle = other.handle;
			break;
		case TYPE_TABLE:
		case TYPE_FUNCTION:
		case TYPE_THREAD:
			this->~GenericScriptValue();
			{
				LuaScriptManager* script = GetScriptManager();
				lua_State* L = script->state;
				type = other.type;
				lua_rawgeti(L, LUA_REGISTRYINDEX, other.reference);
				reference = luaL_ref(L, LUA_REGISTRYINDEX);
			}
			break;
		}
		return *this;
	}

	// FUNCTION: ENGINE 0x10872760
	GenericScriptValue::GenericScriptValue(const GenericScriptValue& other)
	{
		type = TYPE_UNDEFINED;
		Assign(other);
	}
}

// The value's members as the scripts and the editor see them: the type (a number with names) and the value as text
template<> class StringMemberGetSetter<engine::GenericScriptValue> : public content::StringMetaTypeGetSetter
{
public:
	typedef const char* (engine::GenericScriptValue::*Getter)() const;
	typedef void (engine::GenericScriptValue::*Setter)(const char*);

	StringMemberGetSetter(Getter newGetter, Setter newSetter)
	{
		getter = newGetter;
		setter = newSetter;
	}

	virtual const char* Get(void* object)
	{
		return (((engine::GenericScriptValue*)object)->*getter)();
	}
	virtual void Set(void* object, const char* value)
	{
		(((engine::GenericScriptValue*)object)->*setter)(value);
	}

	Getter getter;
	Setter setter;
};

namespace content
{
	template<class C, int Id> StringMetaTypeGetSet* GetConstStringMemberMetaType(const char* (C::*getter)() const,
		void (C::*setter)(const char*), const char* code)
	{
		static StringMemberGetSetter<C> sGetSetter(getter, setter);
		static StringMetaTypeGetSet sType(&sGetSetter, 0x400, code);
		return &sType;
	}
}

namespace engine
{
	// FUNCTION: ENGINE 0x10872590
	content::MemberList* GenericScriptValue::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberEnumMetaType(&GenericScriptValue::GetType,
				reinterpret_cast<void (GenericScriptValue::*)(Type)>(&GenericScriptValue::SetType)), 0, "type" },
			{ content::GetConstStringMemberMetaType<GenericScriptValue, 0>(&GenericScriptValue::ToString,
				&GenericScriptValue::SetFromString, "pn"), 0, "value" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10871AA0
// FUNCTION: ENGINE 0x10871AB0
// FUNCTION: ENGINE 0x10871AC0
// FUNCTION: ENGINE 0x10871CC0
// FUNCTION: ENGINE 0x10871CD0
// FUNCTION: ENGINE 0x10871D10
// FUNCTION: ENGINE 0x10871D20
// FUNCTION: ENGINE 0x10871E00
// FUNCTION: ENGINE 0x10871EA0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10871860
// FUNCTION: ENGINE 0x108718A0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10871830
// FUNCTION: ENGINE 0x10871870
// FUNCTION: ENGINE 0x10871A90
// FUNCTION: ENGINE 0x10871AD0
// FUNCTION: ENGINE 0x10871CA0
// FUNCTION: ENGINE 0x10871CF0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10871880
