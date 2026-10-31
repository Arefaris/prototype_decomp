// pure3d::ParameterHandlerTypeless (RTTI name; vftable 0x10E639B4, one slot): the named parameters of a render pass -- a
// tree of name -> typed value. A parameter is either a variable of the owner (a pointer the handler stores through) or
// a pair of functions the owner supplied (called with the owner, the name and the value). The classes
// ParameterHandler<T> derive from it and register the parameters of a pass of type T. Names and the layout of the
// nodes are guesses; the kind numbers are the engine's.
#ifndef PURE3D_PARAMETERHANDLER_H
#define PURE3D_PARAMETERHANDLER_H

#include "code/container/map.h"
#include "code/core/name.h"
#include "code/math/colour128.h"
#include "code/math/pddicolour.h"
#include "code/math/vector.h"
#include "code/math/vector2.h"
#include "code/math/vector4.h"

namespace pure3d
{
	class Texture;

	// The packed colour a parameter of kind 9 points at (the word of a pddiColour, as its own type)
	struct ColourWord
	{
		unsigned int bits;
	};

	// The kinds of a parameter: 1 - 11 point at a variable (float, int, unsigned int, bool, Vector, Vector2, Vector4,
	// pddiColour, packed unsigned int colour, four-float colour, reference), 12 - 21 are the functions of the same
	// kinds without the reference and 22 sets a reference through a function
	class ParameterValue
	{
	public:
		typedef core::Name<core::CaseSensitiveKey> ParameterName;

		// The ctors 0x107A1B30 - 0x107A1DD0: the variable of kind 1 - 11, the function pair of kind 12 - 21 and the setter
		// of kind 22
		explicit ParameterValue(float* variable);
		explicit ParameterValue(int* variable);
		explicit ParameterValue(unsigned int* variable);
		explicit ParameterValue(bool* variable);
		explicit ParameterValue(math::Vector* variable);
		explicit ParameterValue(math::Vector2* variable);
		explicit ParameterValue(math::Vector4* variable);
		explicit ParameterValue(math::pddiColour* variable);
		explicit ParameterValue(ColourWord* variable);
		explicit ParameterValue(math::Colour128* variable);
		explicit ParameterValue(Texture** variable);
		ParameterValue(bool (*newSetter)(void* owner, const ParameterName* name, float), bool (*newGetter)(void* owner, const ParameterName* name, float*));
		ParameterValue(bool (*newSetter)(void* owner, const ParameterName* name, int), bool (*newGetter)(void* owner, const ParameterName* name, int*));
		ParameterValue(bool (*newSetter)(void* owner, const ParameterName* name, unsigned int), bool (*newGetter)(void* owner, const ParameterName* name, unsigned int*));
		ParameterValue(bool (*newSetter)(void* owner, const ParameterName* name, bool), bool (*newGetter)(void* owner, const ParameterName* name, bool*));
		ParameterValue(bool (*newSetter)(void* owner, const ParameterName* name, const math::Vector*), bool (*newGetter)(void* owner, const ParameterName* name, math::Vector*));
		ParameterValue(bool (*newSetter)(void* owner, const ParameterName* name, const math::Vector2*), bool (*newGetter)(void* owner, const ParameterName* name, math::Vector2*));
		ParameterValue(bool (*newSetter)(void* owner, const ParameterName* name, const math::Vector4*), bool (*newGetter)(void* owner, const ParameterName* name, math::Vector4*));
		ParameterValue(bool (*newSetter)(void* owner, const ParameterName* name, const math::pddiColour*), bool (*newGetter)(void* owner, const ParameterName* name, math::pddiColour*));
		ParameterValue(bool (*newSetter)(void* owner, const ParameterName* name, const unsigned int*), bool (*newGetter)(void* owner, const ParameterName* name, unsigned int*));
		ParameterValue(bool (*newSetter)(void* owner, const ParameterName* name, const math::Colour128*), bool (*newGetter)(void* owner, const ParameterName* name, math::Colour128*));
		explicit ParameterValue(bool (*newSetter)(void* owner, const ParameterName* name, Texture* value));

		int kind;
		void* setter;
		void* getter;
	};

	// The tree of the parameters (the Map<name, ParameterValue> of the engine; its members are in another unit)
	class ParameterTree : public container::TreeBase
	{
	public:
		// The empty allocator of the Map the engine's tree is
		unsigned char allocator;

		typedef core::Name<core::CaseSensitiveKey> ParameterName;

		// 0x1074E4E0: the parameter of that name (made when there is none)
		ParameterValue& At(const ParameterName* name);
	};

	// 0x1074E220 (another unit): orders a name against the name of a parameter node
	int CompareParameter(const void* key, const container::TreeBase::Node* node);

	// The engine's pddiColour as this unit copies it (a copy that is not inlined: 0x107A1E20; the name is a guess)
	struct Colour32
	{
		Colour32()
		{
		}
		Colour32(const Colour32& other);

		union
		{
			unsigned int bits;
			struct
			{
				unsigned int b : 8;
				unsigned int g : 8;
				unsigned int r : 8;
				unsigned int a : 8;
			};
		};
	};

	class ParameterHandlerTypeless
	{
	public:
		typedef core::Name<core::CaseSensitiveKey> ParameterName;
		typedef bool (*SetIntFunction)(void* owner, const ParameterName* name, int value);

		// One parameter (the node's key is the name)
		struct Node : public container::TreeBase::Node
		{
			ParameterName name;
			ParameterValue value;
		};

		// 0x107A2C90
		ParameterHandlerTypeless();
		// Slot 0 (0x107A2CB0 is the body, 0x107A2CD0 the scalar deleting destructor)
		virtual ~ParameterHandlerTypeless();

		// 0x107A1F80 / 0x107A1FE0 / 0x107A2040 / 0x107A20B0 / 0x107A2110 / 0x107A2180 / 0x107A21F0: set the parameter
		// of that name to the value; false when there is none of that kind
		bool SetInt(const ParameterName* name, int value);
		bool SetUnknown1FE0(const ParameterName* name, unsigned int value);
		bool SetFloat(const ParameterName* name, float value);
		bool SetBool(const ParameterName* name, bool value);
		bool SetVector(const ParameterName* name, const math::Vector* value);
		bool SetVector2(const ParameterName* name, const math::Vector2* value);
		bool SetVector4(const ParameterName* name, const math::Vector4* value);
		// 0x107A27C0 / 0x107A2270 / 0x107A2910: a colour as a pddiColour, as a packed word, as four floats
		bool SetColour(const ParameterName* name, const math::pddiColour* value);
		bool SetColourWord(const ParameterName* name, const unsigned int* value);
		bool SetColourFloats(const ParameterName* name, const math::Colour128* value);

		// 0x107A2430 / 0x107A2490 / 0x107A24F0 / 0x107A2550 / 0x107A25B0 / 0x107A2620 / 0x107A2A20
		bool GetInt(const ParameterName* name, int* value);
		bool GetUnknown2490(const ParameterName* name, unsigned int* value);
		bool GetFloat(const ParameterName* name, float* value);
		bool GetBool(const ParameterName* name, bool* value);
		bool GetVector(const ParameterName* name, math::Vector* value);
		bool GetVector4(const ParameterName* name, math::Vector4* value);
		bool GetColour(const ParameterName* name, math::pddiColour* value);
		bool GetColourWord(const ParameterName* name, unsigned int* value);
		bool GetColourFloats(const ParameterName* name, math::Colour128* value);

		void* owner;
		ParameterTree parameters;
	};

	// ParameterHandler<T> (RTTI names pure3d::ParameterHandler<class pure3d::ProtoMotherPass> and so on, one slot, the
	// deleting destructor): the handler of the parameters of one pass. A pass keeps it as a member (the handler's owner
	// is the handler itself, its object the pass) and registers the pass's member functions under the names of the
	// parameters: the handler files the member functions in its own tree and puts function-kind parameters with the
	// adapters below in the base tree. Names are guesses.
	// What a colour getter answers (a word; it has a copy constructor, so it is answered through a hidden pointer)
	struct ColourResult
	{
		ColourResult(const ColourResult& other)
		{
			bits = other.bits;
		}

		unsigned int bits;
	};

	template<class T> class ParameterHandler : public ParameterHandlerTypeless
	{
	public:
		// What a registered parameter calls: the two kinds say how the setter and the getter are called (1: with the
		// value only, 2 also: the same for a getter that is const; anything else: with the name and the value)
		struct Entry
		{
			int setKind;
			int getKind;
			union
			{
				bool (T::*setterBool)(bool);
				bool (T::*setterNamedBool)(const ParameterName*, bool);
				void (T::*setterUnsigned)(unsigned int);
				bool (T::*setterNamedUnsigned)(const ParameterName*, unsigned int);
				void (T::*setterColour)(const unsigned int*);
				bool (T::*setterNamedColour)(const ParameterName*, const unsigned int*);
			};
			union
			{
				bool (T::*getterBool)();
				bool (T::*getterNamedBool)(const ParameterName*, bool*);
				unsigned int (T::*getterUnsigned)();
				bool (T::*getterNamedUnsigned)(const ParameterName*, unsigned int*);
				ColourResult (T::*getterColour)();
				const ColourResult& (T::*getterColourReference)();
				bool (T::*getterNamedColour)(const ParameterName*, unsigned int*);
			};
		};

		// The nodes of the entry tree come from the global array new and delete
		struct EntryAllocator
		{
			static void* Alloc(unsigned int size)
			{
				return operator new[](size);
			}
			static void Free(void* block)
			{
				operator delete[](block);
			}
		};

		// The tree of the entries (the value of a new key is made without an initial value)
		class EntryMap : public container::Map<ParameterName, Entry, EntryAllocator>
		{
		public:
			Entry& At(const ParameterName& key)
			{
				MapNode* node = (MapNode*)TreeBase::Find(CompareKey, &key);
				if (node == 0)
				{
					Entry value;
					Pair pair(key, value);
					node = Insert(pair).node;
				}
				return node->pair.value;
			}
		};

		ParameterHandler() : object(0)
		{
			owner = this;
		}
		// Registers a parameter that is a pair of member functions on bool
		void AddBool(const ParameterName* name, bool (T::*newSetter)(bool), bool (T::*newGetter)());

		// The same for a pair on an unsigned integer and on a colour word
		void AddUnsigned(const ParameterName* name, void (T::*newSetter)(unsigned int), unsigned int (T::*newGetter)());
		void AddColour(const ParameterName* name, void (T::*newSetter)(const unsigned int*), ColourResult (T::*newGetter)());

		// The functions the base tree holds for such a parameter: look the member functions up by name and call them
		static bool SetBoolAdapter(void* handler, const ParameterName* name, bool value);
		static bool GetBoolAdapter(void* handler, const ParameterName* name, bool* value);
		static bool SetUnsignedAdapter(void* handler, const ParameterName* name, unsigned int value);
		static bool GetUnsignedAdapter(void* handler, const ParameterName* name, unsigned int* value);
		static bool SetColourAdapter(void* handler, const ParameterName* name, const unsigned int* value);
		static bool GetColourAdapter(void* handler, const ParameterName* name, unsigned int* value);

		// 0x107AD370 and its copies: the object the handler calls the member functions of
		void SetObject(T* newObject)
		{
			object = newObject;
		}

		T* object;
		EntryMap entries;
	};

	template<class T> void ParameterHandler<T>::AddBool(const ParameterName* name, bool (T::*newSetter)(bool),
		bool (T::*newGetter)())
	{
		Entry entry = {1, 1, {newSetter}, {newGetter}};
		entries.At(*name) = entry;
		parameters.At(name) = ParameterValue(SetBoolAdapter, GetBoolAdapter);
	}

	template<class T> bool ParameterHandler<T>::SetBoolAdapter(void* handler, const ParameterName* name, bool value)
	{
		ParameterHandler* self = (ParameterHandler*)handler;
		if (self == 0)
		{
			return false;
		}
		if (self->object == 0)
		{
			return false;
		}
		if (self->entries.TreeBase::Find(EntryMap::CompareKey, name) != 0)
		{
			Entry& entry = self->entries.At(*name);
			if (entry.setKind == 1)
			{
				(self->object->*entry.setterBool)(value);
				return true;
			}
			return (self->object->*entry.setterNamedBool)(name, value);
		}
		return false;
	}

	template<class T> bool ParameterHandler<T>::GetBoolAdapter(void* handler, const ParameterName* name, bool* value)
	{
		ParameterHandler* self = (ParameterHandler*)handler;
		if (self == 0)
		{
			return false;
		}
		if (self->object == 0)
		{
			return false;
		}
		if (self->entries.TreeBase::Find(EntryMap::CompareKey, name) != 0)
		{
			Entry& entry = self->entries.At(*name);
			if (entry.getKind == 1)
			{
				*value = (self->object->*entry.getterBool)();
				return true;
			}
			if (entry.getKind == 2)
			{
				*value = (self->object->*entry.getterBool)();
				return true;
			}
			return (self->object->*entry.getterNamedBool)(name, value);
		}
		return false;
	}
	template<class T> void ParameterHandler<T>::AddUnsigned(const ParameterName* name, void (T::*newSetter)(unsigned int),
		unsigned int (T::*newGetter)())
	{
		Entry entry = {1, 1, {0}, {0}};
		entry.setterUnsigned = newSetter;
		entry.getterUnsigned = newGetter;
		entries.At(*name) = entry;
		parameters.At(name) = ParameterValue(SetUnsignedAdapter, GetUnsignedAdapter);
	}

	template<class T> void ParameterHandler<T>::AddColour(const ParameterName* name, void (T::*newSetter)(const unsigned int*),
		ColourResult (T::*newGetter)())
	{
		Entry entry = {1, 1, {0}, {0}};
		entry.setterColour = newSetter;
		entry.getterColour = newGetter;
		entries.At(*name) = entry;
		parameters.At(name) = ParameterValue(SetColourAdapter, GetColourAdapter);
	}

	template<class T> bool ParameterHandler<T>::SetUnsignedAdapter(void* handler, const ParameterName* name,
		unsigned int value)
	{
		ParameterHandler* self = (ParameterHandler*)handler;
		if (self == 0)
		{
			return false;
		}
		if (self->object == 0)
		{
			return false;
		}
		if (self->entries.TreeBase::Find(EntryMap::CompareKey, name) != 0)
		{
			Entry& entry = self->entries.At(*name);
			if (entry.setKind == 1)
			{
				(self->object->*entry.setterUnsigned)(value);
				return true;
			}
			return (self->object->*entry.setterNamedUnsigned)(name, value);
		}
		return false;
	}

	template<class T> bool ParameterHandler<T>::GetUnsignedAdapter(void* handler, const ParameterName* name,
		unsigned int* value)
	{
		ParameterHandler* self = (ParameterHandler*)handler;
		if (self == 0)
		{
			return false;
		}
		if (self->object == 0)
		{
			return false;
		}
		if (self->entries.TreeBase::Find(EntryMap::CompareKey, name) != 0)
		{
			Entry& entry = self->entries.At(*name);
			if (entry.getKind == 1)
			{
				*value = (self->object->*entry.getterUnsigned)();
				return true;
			}
			if (entry.getKind == 2)
			{
				*value = (self->object->*entry.getterUnsigned)();
				return true;
			}
			return (self->object->*entry.getterNamedUnsigned)(name, value);
		}
		return false;
	}

	template<class T> bool ParameterHandler<T>::SetColourAdapter(void* handler, const ParameterName* name,
		const unsigned int* value)
	{
		ParameterHandler* self = (ParameterHandler*)handler;
		if (self == 0)
		{
			return false;
		}
		if (self->object == 0)
		{
			return false;
		}
		if (self->entries.TreeBase::Find(EntryMap::CompareKey, name) != 0)
		{
			Entry& entry = self->entries.At(*name);
			if (entry.setKind == 1)
			{
				(self->object->*entry.setterColour)(value);
				return true;
			}
			return (self->object->*entry.setterNamedColour)(name, value);
		}
		return false;
	}

	template<class T> bool ParameterHandler<T>::GetColourAdapter(void* handler, const ParameterName* name,
		unsigned int* value)
	{
		ParameterHandler* self = (ParameterHandler*)handler;
		if (self == 0)
		{
			return false;
		}
		if (self->object == 0)
		{
			return false;
		}
		if (self->entries.TreeBase::Find(EntryMap::CompareKey, name) != 0)
		{
			Entry& entry = self->entries.At(*name);
			if (entry.getKind == 1)
			{
				*value = (self->object->*entry.getterColour)().bits;
				return true;
			}
			if (entry.getKind == 2)
			{
				*value = (self->object->*entry.getterColourReference)().bits;
				return true;
			}
			return (self->object->*entry.getterNamedColour)(name, value);
		}
		return false;
	}
}

#endif
