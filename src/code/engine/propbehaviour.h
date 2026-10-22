// engine::PropBehaviour (RTTI name; reflected as "engine::PropBehaviour"; base engine::Behaviour): the behaviour of
// the objects a PropSpawner makes. On construction it gives the object a PropSpawner attribute (the spawner that made
// it, empty until the spawner sets it) and an empty "meta object template" name, and listens for the physics filter
// message (type 6) and for the query whether the prop has moved from its spawner (type 0x18). Unit 0x10841060 -
// 0x10841550 (no assert path; the file name is a guess). Member and method names are guesses.
#ifndef ENGINE_PROPBEHAVIOUR_H
#define ENGINE_PROPBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/message.h"

namespace engine
{
	class PropSpawner;
	struct PhysicsFilterMessage;

	// Asks whether a prop was moved away from its spawner (type 0x18, id 8; the answer comes back in the message;
	// RTTI name unknown)
	struct PropMovedMessage : public NonintrusiveMessage
	{
		PropMovedMessage() : NonintrusiveMessage(0x18, 8)
		{
			found = false;
			moved = false;
		}

		bool found;  // +0xC: the prop has a spawner
		bool moved;  // +0xD: it is not where the spawner is
	};

	// RTTI engine::ConstAttribute<T> / engine::Attribute<T> for the attributes that hold a pointer: the value sits
	// behind the vftable of the base (one slot, the deleting destructor)
	template<class T> class ConstAttribute : public BaseAttribute
	{
	public:
		// 0x108411C0 for PropSpawner*
		explicit ConstAttribute(T newValue)
		{
			value = newValue;
		}

		// 0x10841130 for PropSpawner* (name guessed)
		T* GetPointer()
		{
			return &value;
		}

		T value;
	};

	template<> class Attribute<PropSpawner*> : public ConstAttribute<PropSpawner*>
	{
	public:
		// 0x10841330
		Attribute() : ConstAttribute<PropSpawner*>(0)
		{
		}
	};

	class PropBehaviour : public Behaviour
	{
	public:
		// 0x108414B0
		explicit PropBehaviour(GameObject* newOwner);
		// vftable slot 7: the implicit destructor (0x10841530 deletes)

		// 0x10841060 / 0x10841200
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x108410A0): leaves the listener list of the props
		virtual void Slot1();
		// vftable slot 5 (0x10841370): the query whether the prop moved
		virtual void OnPostedMessage(Message* message);
		// vftable slot 6 (0x10841190): the physics filter message
		virtual void OnMessage(Message* message);

		// 0x108410C0: the props collide with ... when the filter is switched on (mask 0x40 of the intersection
		// properties)
		void OnPhysicsFilterOn(PhysicsFilterMessage* message);
		// 0x10841260: whether the object is still at the position of its spawner
		void OnMovedQuery(PropMovedMessage* message);
	};
}

#endif
