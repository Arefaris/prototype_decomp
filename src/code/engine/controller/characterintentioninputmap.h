// engine::CharacterIntentionInputMap (RTTI and reflection names): a content library object that maps controller
// buttons and axes to the names of a character's intentions. It holds six reflected element arrays (button to
// intention, button pair to axis, axis to axis, axis to button, axis pair to button and the translation of an axis
// pair into player space); the names are resolved into indices of the intention tables when the object is loaded.
// Unit 0x108217C0 - 0x10825890 (no assert path; the directory and file name are guesses). The reflected member
// names are original; the rest is guessed.
#ifndef ENGINE_CONTROLLER_CHARACTERINTENTIONINPUTMAP_H
#define ENGINE_CONTROLLER_CHARACTERINTENTIONINPUTMAP_H

#include "code/container/arraycdynamic.h"
#include "code/container/arraydynamic.h"
#include "code/container/arraydynamicstatic.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include <new>

namespace engine
{
	namespace controller
	{
		// The controller's buttons and axes (the reflection names the enumerations; the values come with their unit,
		// 0x108A1220 / 0x108A1250)
		enum ControllerButton
		{
			BUTTON_NONE = 42
		};
		enum ControllerAxis
		{
			AXIS_NONE = 17
		};
	}

}

namespace content
{
	// The enumerations' values and names (the controller's unit, 0x108A1220 / 0x108A1250)
	template<> void EnumInfo<engine::controller::ControllerButton>::Get(const char** name, const EnumValue** values,
		int* count, const char** code);
	template<> void EnumInfo<engine::controller::ControllerAxis>::Get(const char** name, const EnumValue** values,
		int* count, const char** code);
}

namespace container
{
	// How Reserve copies an element into the new storage (the translations' array expands its element's copy)
	template<class T> struct ArrayDynamicCopy
	{
		static void At(T* p, const T& value)
		{
			ConstructCopyAt(p, value);
		}
	};

	// The element arrays of the intention maps (RTTI: ArrayDynamic<..., AllocatorNew>, begin / end / capacity over
	// operator new[]). The arrays of the engine's other reflected classes (code/container/arraydynamicallocatornew.h)
	// have no destructor, no Begin / End and another Erase / Insert; these are the ones this unit instantiates.
	template<class T> class ArrayDynamic<T, AllocatorNew>
	{
	public:
		typedef T Element;

		ArrayDynamic()
		{
			begin = 0;
			end = 0;
			capacity = 0;
		}
		~ArrayDynamic()
		{
			end = begin;
			if (begin != 0)
			{
				operator delete[](begin);
			}
		}
		T* Begin()
		{
			return begin;
		}
		T* End()
		{
			return end;
		}
		unsigned int Size() const
		{
			return end - begin;
		}
		unsigned int Capacity() const
		{
			return capacity - begin;
		}
		T& operator[](int index)
		{
			return begin[index];
		}
		const T& operator[](int index) const
		{
			return begin[index];
		}
		// Room for count uninitialised elements; false (and an empty array) when count is 0 or the allocation fails
		bool Create(unsigned int count)
		{
			if (count != 0)
			{
				begin = (T*)operator new[](count * sizeof(T));
				if (begin != 0)
				{
					end = begin;
					capacity = begin + count;
					return true;
				}
			}
			else
			{
				begin = 0;
			}
			end = 0;
			capacity = 0;
			return false;
		}
		// The same, leaving the array empty
		void Allocate(unsigned int count)
		{
			if (count != 0)
			{
				begin = (T*)operator new[](count * sizeof(T));
				if (begin != 0)
				{
					capacity = begin + count;
					end = begin;
					return;
				}
			}
			else
			{
				begin = 0;
			}
			end = 0;
			capacity = 0;
		}
		// Drops the elements (the storage stays)
		void Clear()
		{
			end = begin;
		}
		void Free()
		{
			if (begin != 0)
			{
				operator delete[](begin);
			}
			capacity = 0;
			end = 0;
			begin = 0;
		}
		// Moves the elements behind position down over it and answers position
		T* Erase(T* position)
		{
			AssignRange(position + 1, end, position);
			end--;
			return position;
		}
		// Moves [position, end) up by count elements (copy-constructing them backwards)
		void ShiftUp(T* position, int count)
		{
			T* from = end;
			end = from + count;
			T* to = end;
			while (from != position)
			{
				from--;
				to--;
				ConstructCopyAt(to, *from);
			}
		}
		// Makes room for count elements, keeping the ones that fit
		void Reserve(int count)
		{
			int size = end - begin;
			if (count != capacity - begin)
			{
				int keep = count < size ? count : size;
				T* storage = (T*)operator new[](count * sizeof(T));
				int i = 0;
				if (storage == 0)
				{
					keep = 0;
					count = 0;
				}
				else
				{
					for (; i < keep; i++)
					{
						ArrayDynamicCopy<T>::At(storage + i, begin[i]);
					}
				}
				if (begin != 0)
				{
					operator delete[](begin);
				}
				end = storage + keep;
				begin = storage;
				capacity = storage + count;
			}
		}
		// Inserts count copies of value before position when they fit; answers position, or the old end when they
		// do not
		T* Insert(T* position, unsigned int count, const T& value)
		{
			T* result = end;
			if (end + count <= capacity)
			{
				ShiftUp(position, count);
				ConstructFill(position, count, value);
				result = position;
			}
			return result;
		}
		T* Insert(T* position, const T& value)
		{
			return Insert(position, 1, value);
		}

		T* begin;
		T* end;
		T* capacity;
	};
}

namespace engine
{
	class CharacterIntentionInputMap : public content::MetaLoadObject
	{
	public:
		// Button to intention
		struct ButtonMapEntry
		{
			ButtonMapEntry();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			controller::ControllerButton button;
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> name;
			int index;
		};

		// Two buttons to an axis intention
		struct ButtonPairToAxisMapEntry
		{
			ButtonPairToAxisMapEntry();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			controller::ControllerButton negative;
			controller::ControllerButton positive;
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> name;
			int index;
		};

		// An axis to an axis intention, optionally inverted
		struct AxisMapEntry
		{
			AxisMapEntry();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			controller::ControllerAxis axis;
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> name;
			int index;
			bool invert;
		};

		// An axis to a button intention
		struct AxisToButtonMapEntry
		{
			AxisToButtonMapEntry();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			controller::ControllerAxis axis;
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> name;
			int index;
			float direction;
		};

		// Two axes to a button intention
		struct AxisPairToButtonMapEntry
		{
			AxisPairToButtonMapEntry();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			controller::ControllerAxis x;
			controller::ControllerAxis y;
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> name;
			int index;
		};

		// Two axes to the two axis intentions of the player's space
		struct PlayerSpaceTranslationMapEntry
		{
			PlayerSpaceTranslationMapEntry();
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			controller::ControllerAxis x;
			controller::ControllerAxis y;
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> nameX;
			int indexX;
			__declspec(align(8)) core::Name<core::CaseSensitiveKey> nameY;
			int indexY;
			bool invertX;
			bool invertY;
		};

		// One table of intention names (the engine's settings hold three words per table)
		struct NameTable
		{
			unsigned int count;
			const core::Name<core::CaseSensitiveKey>* names;
			unsigned int unknown;
		};

		typedef container::ArrayDynamic<ButtonMapEntry, container::AllocatorNew> ButtonMapArray;
		typedef container::ArrayDynamic<ButtonPairToAxisMapEntry, container::AllocatorNew> ButtonPairToAxisMapArray;
		typedef container::ArrayDynamic<AxisMapEntry, container::AllocatorNew> AxisMapArray;
		typedef container::ArrayDynamic<AxisToButtonMapEntry, container::AllocatorNew> AxisToButtonMapArray;
		typedef container::ArrayDynamic<AxisPairToButtonMapEntry, container::AllocatorNew> AxisPairToButtonMapArray;
		typedef container::ArrayDynamic<PlayerSpaceTranslationMapEntry, container::AllocatorNew>
			PlayerSpaceTranslationMapArray;

		CharacterIntentionInputMap();
		virtual ~CharacterIntentionInputMap();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// Slot 3: resolves the names against the intention tables and registers the map for its player
		virtual void Slot3(int unused);
		// Slot 4: leaves the player's slot
		virtual bool IsReady();

		// The tables of the button and axis intentions (and a third one) are set once from the engine's settings
		static void SetNameTables(unsigned int buttonCount, const core::Name<core::CaseSensitiveKey>* buttonNames,
			unsigned int buttonUnknown, unsigned int axisCount, const core::Name<core::CaseSensitiveKey>* axisNames,
			unsigned int axisUnknown, unsigned int thirdCount, const core::Name<core::CaseSensitiveKey>* thirdNames,
			unsigned int thirdUnknown);
		static unsigned int GetButtonCount();
		static const core::Name<core::CaseSensitiveKey>* GetButtonNames();
		static unsigned int GetButtonUnknown();
		static unsigned int GetAxisCount();
		static const core::Name<core::CaseSensitiveKey>* GetAxisNames();
		static unsigned int GetAxisUnknown();
		static unsigned int GetThirdCount();
		static const core::Name<core::CaseSensitiveKey>* GetThirdNames();
		static unsigned int GetThirdUnknown();

		ButtonMapArray buttonMap;                         // +0x08
		int unknown14;
		ButtonPairToAxisMapArray buttonPairToAxisMap;     // +0x18
		int unknown24;
		AxisMapArray axisMap;                             // +0x28
		int unknown34;
		AxisToButtonMapArray axisToButtonMap;             // +0x38
		int unknown44;
		AxisPairToButtonMapArray axisPairToButtonMap;     // +0x48
		int unknown54;
		PlayerSpaceTranslationMapArray playerSpaceTranslationMap;  // +0x58
		int unknown64;
		int serial;                                       // +0x68
		unsigned char playerIndex;                        // +0x6C
		bool resolved;                                    // +0x6D

		static NameTable sNameTables[3];
		static int sNextSerial;

	private:
		// The index of name in names (0 when it is not there)
		unsigned int FindNameIndex(core::Name<core::CaseSensitiveKey> name, unsigned int count,
			const core::Name<core::CaseSensitiveKey>* names, unsigned int unused);
		// Looks the names of every entry up in the button intentions or the axis intentions it produces
		void ResolveNames(unsigned int buttonCount, const core::Name<core::CaseSensitiveKey>* buttonNames,
			unsigned int buttonUnknown, unsigned int axisCount, const core::Name<core::CaseSensitiveKey>* axisNames,
			unsigned int axisUnknown);
	};

	// The map each of the eight players uses (0x113154E8; another unit)
	CharacterIntentionInputMap* GetPlayerIntentionMap(unsigned int playerIndex);
	void SetPlayerIntentionMap(CharacterIntentionInputMap* map, unsigned int playerIndex);
}


namespace container
{
	// Reserve of the translations' array expands the element's copy in its loop (the engine's compiler calls the
	// copy constructor from the other members): a type of the same layout with an expanded copy
	struct PlayerSpaceTranslationCopy
	{
		__forceinline PlayerSpaceTranslationCopy(
			const engine::CharacterIntentionInputMap::PlayerSpaceTranslationMapEntry& v)
			: x(v.x), y(v.y), nameX(v.nameX), indexX(v.indexX), nameY(v.nameY), indexY(v.indexY),
			invertX(v.invertX), invertY(v.invertY)
		{
		}

		engine::controller::ControllerAxis x;
		engine::controller::ControllerAxis y;
		__declspec(align(8)) core::Name<core::CaseSensitiveKey> nameX;
		int indexX;
		__declspec(align(8)) core::Name<core::CaseSensitiveKey> nameY;
		int indexY;
		bool invertX;
		bool invertY;
	};

	template<> struct ArrayDynamicCopy<engine::CharacterIntentionInputMap::PlayerSpaceTranslationMapEntry>
	{
		static __forceinline void At(engine::CharacterIntentionInputMap::PlayerSpaceTranslationMapEntry* p,
			const engine::CharacterIntentionInputMap::PlayerSpaceTranslationMapEntry& value)
		{
			if (p != 0)
			{
				new (p) PlayerSpaceTranslationCopy(value);
			}
		}
	};
}

namespace content
{
	// The element access of the arrays for their meta types. The default element the reflection inserts is kept in
	// a function-local static (Default; this unit keeps the engine's copy of it)
	template<class T> class ArrayDynamicHelper<container::ArrayDynamic<T, container::AllocatorNew> >
		: public ArrayDynamicHelperBase
	{
	public:
		typedef container::ArrayDynamic<T, container::AllocatorNew> A;

		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}

		virtual int Size(void* array)
		{
			return ((A*)array)->Size();
		}
		virtual void* Get(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void* GetConst(void* array, int index)
		{
			return ((A*)array)->begin + index;
		}
		virtual void Insert(void* array, int index, int unused)
		{
			A* a = (A*)array;
			if (a->Size() >= a->Capacity())
			{
				a->Reserve(a->Size() + 1);
			}
			T* position = a->begin + index;
			a->Insert(position, 1, Default());
		}
		// Moves the elements behind the erased one down with a call of AssignRange
		virtual void Erase(void* array, int index, int unused)
		{
			A* a = (A*)array;
			T* position = a->begin + index;
			container::AssignRange(position + 1, a->end, position);
			a->end--;
		}
		virtual int Capacity(void* array)
		{
			return ((A*)array)->Capacity();
		}
		virtual void Expand(void* array, unsigned int count)
		{
			A* a = (A*)array;
			if (a->Capacity() == 0)
			{
				a->Allocate(count);
			}
			else if (count + a->Size() > a->Capacity())
			{
				a->Reserve(count + a->Size());
			}
		}
	};
}

#endif
