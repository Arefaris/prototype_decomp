// The keyboard base class (engine::controller::Keyboard, code/engine/controller/keyboard.cpp; the file name is a guess,
// the unit starts at 0x108A1E80 and has no assert path): the table of the characters the keys make. Names are guesses.
#include "code/engine/controller/inputsystem.h"

namespace engine
{
	namespace controller
	{
		// One row of the table of the keys that make characters
		struct KeyInfo
		{
			int key;
			KeyCharacters characters;
		};

		// 0x111E2070 / 0x10E81C90: the table (in the engine's data) and its length
		extern const KeyInfo gKeyTable[];
		extern const int gKeyTableCount;

		// FUNCTION: ENGINE 0x108A2180
		// NONMATCHING: the engine forms the address of the value (add eax, 0x14) before it stores the characters (83.8 %)
#ifdef NONMATCHING
		Keyboard::Keyboard()
		{
			for (int index = 0; index < gKeyTableCount; index++)
			{
				KeyCharacters& slot = keys[gKeyTable[index].key];
				slot = gKeyTable[index].characters;
			}
		}
#endif

		// FUNCTION: ENGINE 0x108A20C0
		// NONMATCHING: the engine keeps the empty answer in ebx and loads the characters into eax (19.1 %)
#ifdef NONMATCHING
		unsigned char Keyboard::GetCharacter(int key, unsigned int modifiers)
		{
			unsigned char result = 0;
			KeyMap::Iterator found = keys.Find(key);
			if (found.node != 0)
			{
				const KeyCharacters& characters = found->value;
				if (((modifiers & 1) == 0 || (result = characters.alt) == 0)
					&& ((modifiers & 2) == 0 || (result = characters.control) == 0)
					&& ((((modifiers & 4) == 0 || (modifiers & 8) != 0) && ((modifiers & 4) != 0 || (modifiers & 8) == 0))
						|| (result = characters.shifted) == 0))
				{
					return characters.plain;
				}
			}
			return result;
		}
#endif
	}
}

typedef engine::controller::KeyMap KeyMapType;
// The members of the key map the engine's unit has copies of (the keyboard's constructor and GetCharacter use them)
template KeyMapType::Iterator KeyMapType::Find(const int&);
template KeyMapType::Iterator KeyMapType::Insert(const KeyMapType::Pair&);
template engine::controller::KeyCharacters& KeyMapType::operator[](const int&);
template void KeyMapType::Clear();
template KeyMapType::~Map();
template KeyMapType::Map(engine::controller::KeyAllocator);
template KeyMapType::Pair::Pair(const int&, const engine::controller::KeyCharacters&);
template KeyMapType::MapNode::MapNode(const KeyMapType::Pair&);
template KeyMapType::Iterator::Iterator(KeyMapType::MapNode*, KeyMapType*);
template KeyMapType::Pair* KeyMapType::Iterator::operator->() const;
template int KeyMapType::Compare(const int&, const int&);
template int KeyMapType::CompareKey(const void*, const container::TreeBase::Node*);
template int KeyMapType::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);
template bool KeyMapType::DeleteNode(container::TreeBase::Node*, void*);
template container::SListLite<engine::controller::Keyboard::Callback>::SListLite();

// Kept copies (template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108A1E90
// FUNCTION: ENGINE 0x108A1EC0
// FUNCTION: ENGINE 0x108A1EE0
// FUNCTION: ENGINE 0x108A1F10
// FUNCTION: ENGINE 0x108A1F30
// FUNCTION: ENGINE 0x108A1F60
// FUNCTION: ENGINE 0x108A1F70
// FUNCTION: ENGINE 0x108A1FC0
// FUNCTION: ENGINE 0x108A1FE0
// FUNCTION: ENGINE 0x108A2010
// FUNCTION: ENGINE 0x108A2040
// FUNCTION: ENGINE 0x108A20B0
// FUNCTION: ENGINE 0x108A2130
