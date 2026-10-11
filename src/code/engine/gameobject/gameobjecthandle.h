// Handles to game objects: a 16-bit index into the engine's game object table (0x1128348C, 8 bytes per entry) and
// the 16-bit serial the entry must still carry. The class and member names are guesses except IsValid (an assert
// in poimanager.cpp reads "playerPositionHandle.IsValid()"). Only what the engine's users need so far is declared;
// GameObject itself is reconstructed elsewhere later, here it is just the transform attribute at 0x1C.
#ifndef ENGINE_GAMEOBJECT_GAMEOBJECTHANDLE_H
#define ENGINE_GAMEOBJECT_GAMEOBJECTHANDLE_H

#include "code/math/matrix.h"

namespace engine
{
	// engine::BaseAttribute / engine::Attribute<T> (RTTI names; the GameObject's transform is an
	// Attribute<math::Matrix> found through dynamic_cast)
	class BaseAttribute
	{
	public:
		virtual ~BaseAttribute();
	};

	template<class T> class Attribute : public BaseAttribute
	{
	public:
		T value;
	};

	class Message;

	class GameObject
	{
	public:
		// 0x107E0810 (another unit): delivers the message when the object listens for its type
		bool SendMessage(Message* message);

		unsigned char unknown0[0x1c];
		Attribute<math::Matrix>* transform;
	};

	struct GameObjectEntry
	{
		GameObject* object;
		unsigned short serial;
		unsigned short flags;
	};

	// The game object table (0x1128348C)
	extern GameObjectEntry* gGameObjects;

	// The handle data with the out-of-line null constructor (0x107EE330, another unit). GameObjectHandle's own
	// constructor is inline, which is why callers take the address of a constructed temporary again instead of using
	// the base constructor's return value.
	class HandleBase
	{
	public:
		HandleBase();
		// 0x107EE340 (another unit)
		HandleBase(unsigned short newIndex, unsigned short newSerial);

		unsigned short index;
		unsigned short serial;
	};

	class GameObjectHandle : public HandleBase
	{
	public:
		GameObjectHandle()
		{
		}
		GameObjectHandle(unsigned short newIndex, unsigned short newSerial) : HandleBase(newIndex, newSerial)
		{
		}
		unsigned short GetSerial() const
		{
			return serial;
		}

		GameObject* Get() const
		{
			if (index != 0xffff && gGameObjects[index].serial == serial)
			{
				return gGameObjects[index].object;
			}
			return 0;
		}
		bool IsValid() const
		{
			return index != 0xffff && gGameObjects[index].serial == serial && gGameObjects[index].object != 0;
		}
	};
}

#endif
