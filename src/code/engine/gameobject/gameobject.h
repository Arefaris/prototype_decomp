// engine::GameObject (RTTI: 7 vftable slots, bases content::MetaLoadObject / LoadObject / core::IRefCount; 0x60
// bytes): only the members the engine units reconstructed so far use. The class itself (0x107E05A0 - 0x107E1CB0)
// is not reconstructed yet.
#ifndef ENGINE_GAMEOBJECT_GAMEOBJECT_H
#define ENGINE_GAMEOBJECT_GAMEOBJECT_H

#include "code/engine/gameobject/behaviour.h"
#include "code/math/matrix.h"

namespace engine
{
	class Message;

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

	class GameObject
	{
	public:
		// 0x107E0810 (another unit): delivers the message when the object listens for its type
		bool SendMessage(Message* message);

		unsigned char unknown0[0x1c];
		Attribute<math::Matrix>* transform;
		// The behaviour container (a Behaviour itself)
		BehaviourContainer behaviours;
		unsigned char unknown2C[0x58 - 0x2c];
		// The master table index, 0xFFFF while unregistered
		unsigned short index;
		unsigned short unknown5A;
		int unknown5C;
	};

}

#endif
