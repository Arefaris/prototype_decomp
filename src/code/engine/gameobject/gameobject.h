// engine::GameObject (RTTI: 7 vftable slots, bases content::MetaLoadObject / LoadObject / core::IRefCount; 0x60
// bytes): only the members the engine units reconstructed so far use. The class itself (0x107E05A0 - 0x107E1CB0)
// is not reconstructed yet.
#ifndef ENGINE_GAMEOBJECT_GAMEOBJECT_H
#define ENGINE_GAMEOBJECT_GAMEOBJECT_H

#include "code/content/loadinventory.h"
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
		// Out of line in the attribute's unit (Attribute<math::Matrix>: 0x1028AB90, starts at the identity)
		Attribute();

		virtual T& Get();

		T value;
	};

	class GameObject : public content::MetaLoadObject
	{
	public:
		// 0x107E1670 / 0x107E0BE0 (the GameObject unit)
		GameObject();
		static void* operator new(unsigned int size);

		// The vftable (RTTI: 7 slots; slots 0 / 1 are the reference count, slot 2 the deleting destructor)
		virtual void AddRef();
		virtual void Release();
		virtual ~GameObject();
		virtual void Slot3();
		// 0x107E0F40: true when the object may leave the deferred list (meaning guessed)
		virtual bool IsReady();
		virtual bool Slot5();
		// Takes the name the object is kept under in the game object inventory (meaning guessed)
		virtual void SetName(const content::ObjectName& name);

		// 0x107E0810 (another unit): delivers the message when the object listens for its type
		bool SendMessage(Message* message);
		// 0x107E0850: the same through the behaviour container's other slot (name guess)
		bool PostMessage(Message* message);

		unsigned char unknown4[0x1c - 4];
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
