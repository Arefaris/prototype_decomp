// engine::GenericScriptValue (RTTI and reflection name, 8 bytes; the symbols file knew it as scenario::AttributeValue):
// a value of any type a script can hold in an attribute: nothing, a bool, an int, a float, a text, a name, a vector, a
// game object handle, or a Lua table, function or thread kept as a registry reference. The type is a word, the value
// the word behind it; the text, name and vector are made on the heap. Unit 0x10871740 - 0x108727E0 (no assert path; the
// directory and file name are guesses); the reflected names ("type", "value") are original, the rest is guessed.
#ifndef ENGINE_GAMEOBJECT_GENERICSCRIPTVALUE_H
#define ENGINE_GAMEOBJECT_GENERICSCRIPTVALUE_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/vector.h"

struct lua_State;

namespace engine
{
	// A text a value owns: its capacity, then the characters (the heap block is the capacity plus the characters)
	struct ScriptText;

	class GenericScriptValue
	{
	public:
		enum Type
		{
			TYPE_UNDEFINED = 0,
			TYPE_BOOL = 1,
			TYPE_INT = 2,
			TYPE_FLOAT = 3,
			TYPE_TEXT = 4,
			TYPE_NAME = 5,
			TYPE_VECTOR = 6,
			TYPE_HANDLE = 7,
			TYPE_TABLE = 8,
			TYPE_FUNCTION = 9,
			TYPE_THREAD = 10
		};

		// 0x108718B0
		GenericScriptValue();
		// 0x10872050 (the same body without the call: 0x108722A0)
		~GenericScriptValue();
		// 0x10872760: a copy of another value
		GenericScriptValue(const GenericScriptValue& other);

		// 0x108717F0 / 0x10872590
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x1047D2D0 (the copy the engine's reflection reaches)
		Type GetType() const
		{
			return type;
		}
		// 0x108718C0 / 0x108718D0 / 0x108718E0 / 0x108718F0 / 0x10871900 / 0x10871910 / 0x10871920
		bool GetBool() const;
		int GetInt() const;
		float GetFloat() const;
		const char* GetText() const;
		const core::Name<core::CaseSensitiveKey>& GetName() const;
		const math::Vector& GetVector() const;
		GameObjectHandle GetHandle() const;

		// 0x10871D40: drops what the value owns, unless it is of the type to keep (then the old value stays)
		void Release(int keepType);
		// 0x108722A0
		void Clear();
		// 0x108722B0 / 0x108722D0 / 0x108722F0 / 0x10872310
		void SetBool(bool newValue);
		void SetInt(int newValue);
		void SetFloat(float newValue);
		void SetHandle(GameObjectHandle newValue);
		// 0x10871F10 / 0x10871F80 / 0x10871FE0
		void SetText(const char* newText);
		void SetName(const core::Name<core::CaseSensitiveKey>& newName);
		void SetVector(const math::Vector& newVector);
		// 0x10872340: takes the value of the Lua value at index
		void SetFromLua(lua_State* L, int index);
		// 0x10871940: pushes the value
		void PushToLua(lua_State* L) const;
		// 0x10872640: becomes a copy of other
		GenericScriptValue& Assign(const GenericScriptValue& other);
		// 0x108724B0: converts the value to another type
		void SetType(int newType);
		// 0x10872060: parses text as the value of the current type
		void SetFromString(const char* text);
		// 0x10871AF0: the text of the value, in a buffer of the class
		const char* ToString() const;

		Type type;
		union
		{
			bool boolValue;
			int intValue;
			float floatValue;
			ScriptText* text;
			core::Name<core::CaseSensitiveKey>* name;
			math::Vector* vector;
			unsigned int handle;
			int reference;
		};
	};
}

#endif
