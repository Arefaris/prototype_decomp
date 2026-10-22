// engine::PropSpawner (RTTI name; 13 vftable slots, bases GameObjectSpawner / content::MetaLoadObject): the spawner
// of the props a level places. It makes its object (a prop with a PropBehaviour) when it is loaded, tells the object
// which spawner made it, keeps the position and scale the object gets and the initial states of its logic trees as a
// shared engine::UnpackedInitialState. Unit 0x10842010 - 0x10842F00 (no assert path; the file name is a guess).
// Member and method names are guesses.
#ifndef ENGINE_PROPSPAWNER_H
#define ENGINE_PROPSPAWNER_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/core/name.h"
#include "code/engine/gameobject/gameobjectspawner.h"
#include "code/math/vector.h"

namespace engine
{
	// A state of a logic tree: the prefix of the tree (empty for any) and the name of the state (RTTI name TreeState;
	// member names guessed)
	struct TreeState
	{
		// Inline (the engine keeps copies of the constructors at 0x10842340 and 0x10842230)
		TreeState()
		{
		}
		TreeState(const TreeState& other) : prefix(other.prefix), state(other.state)
		{
		}

		core::Name<core::CaseSensitiveKey> prefix;
		core::Name<core::CaseSensitiveKey> state;
	};

	// The initial states of a prop's trees read from "prefix:state,state,..." (RTTI name UnpackedInitialState; it is
	// kept in an inventory under that string, so the props made from one template share it)
	class UnpackedInitialState : public container::ArrayDynamic<TreeState, container::AllocatorNew>, public content::LoadObject
	{
	public:
		// 0x10842B20
		explicit UnpackedInitialState(const char* packed);
		// the implicit destructor (0x10842D20 is its body, 0x10842D40 deletes)

		int unknown14;
		core::Name<core::CaseSensitiveKey> source;  // +0x18
	};

	class PropSpawner : public GameObjectSpawner
	{
	public:
		// 0x10842260
		PropSpawner();
		// vftable slot 2 (0x108424D0 deletes); the destructor body is 0x108422E0
		virtual ~PropSpawner();

		// 0x10842010 / 0x10842E30
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x108426F0): makes the object (from the template under the name, or a new one) and gives it
		// its spawner attribute
		virtual void Slot3(int inventory);
		// vftable slot 4 (0x10842050)
		virtual bool IsReady();
		// vftable slot 6 (0x10842310)
		virtual void SetName(const content::ObjectName& newName);
		// vftable slot 10 (0x108427E0): puts the object at the transform, gives it the scale and its initial states
		virtual void Apply();
		// vftable slot 11 (0x108424F0): has the object updated
		virtual void Refresh();
		// vftable slot 12 (0x10842070)
		virtual const content::ObjectName* GetName();

		// 0x10842080 / 0x10842D80: the reflected "initialState" string (the getter answers an empty string; the
		// setter finds or makes the shared states of that text in the inventory)
		const char* GetInitialState();
		void SetInitialState(const char* packed, content::LoadInventory* inventory);
		// 0x10842320: how many states the tree has
		int GetStateCount();

		GameObjectHandle spawned;  // +0x4C
		content::ObjectName name;  // +0x50
		math::Vector scale;  // +0x58
		UnpackedInitialState* initialState;  // +0x64
	};
}

#endif
