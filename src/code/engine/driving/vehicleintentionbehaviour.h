// engine::driving::VehicleIntentionBehaviour (RTTI name, vftable 0x10E8A7C0, 9 slots, base engine::Behaviour): what a
// vehicle's driver wants. It listens to the player-control message (0xE), keeps which player drives, and hands that
// player's input to the derived behaviour (slot 8) on every update. Unit 0x109379C0 - 0x10937C80 (no assert path;
// the file name is a guess); the car and helicopter behaviours derive from it.
#ifndef ENGINE_DRIVING_VEHICLEINTENTIONBEHAVIOUR_H
#define ENGINE_DRIVING_VEHICLEINTENTIONBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"

namespace engine
{
	// Which player controls an object (8 bytes): the slot of the player's input, -1 for none
	struct PlayerControlInfo
	{
		// 0x10862340
		PlayerControlInfo();

		// 0x108622E0
		void Reset();
		// 0x108622F0: the input of the player (null for no player or no input)
		void* Get() const;

		int slot;  // +0x0
		int unknown4;  // +0x4
	};

	namespace driving
	{
		class VehicleIntentionBehaviour : public Behaviour
		{
		public:
			// 0x10937A00
			explicit VehicleIntentionBehaviour(GameObject* newOwner);

			// 0x109379C0 / 0x10937BD0
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// vftable slot 4 (0x10937A40): hands the player's input on
			virtual void Update(float dt, unsigned short mask);
			// vftable slot 6 (0x10937A70): takes the player-control message's player
			virtual void OnMessage(Message* message);
			// vftable slot 7 (0x10937AF0): the compiler's scalar deleting destructor
			// vftable slot 8: what the vehicle does with the player's input
			virtual void ApplyInput(void* input) = 0;

			// 0x10937A90 / 0x10937AA0: the reflected "playerSlot"
			int GetPlayerSlot() const;
			void SetPlayerSlot(int newSlot);

			PlayerControlInfo control;  // +0xC
		};
	}
}

#endif
