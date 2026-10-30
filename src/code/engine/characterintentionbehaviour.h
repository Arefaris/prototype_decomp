// engine::CharacterIntentionBehaviour (RTTI and reflection names; base engine::Behaviour): what a character wants to
// do. It listens to the player-control message, keeps which player controls the object and which input map that
// player's input is read through, and turns the input into the intention state (the buttons that are down and the
// stick), sending a message when it changed. Unit 0x1091C500 - 0x1091CD30 (no assert path; the file name is a guess).
// The reflected member names are original; the rest is guessed.
#ifndef ENGINE_CHARACTERINTENTIONBEHAVIOUR_H
#define ENGINE_CHARACTERINTENTIONBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/driving/vehicleintentionbehaviour.h"
#include "code/engine/gameobject/behaviour.h"

namespace engine
{
	class CharacterIntentionBehaviour : public Behaviour
	{
	public:
		// 0x1091CBC0 (not reconstructed)
		explicit CharacterIntentionBehaviour(GameObject* newOwner);

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The reflected "playerSlot" (0x1091C600 / 0x1091C610) and "inputMapIndex" (0x1091C660 / 0x1091C670)
		int GetPlayerSlot() const;
		void SetPlayerSlot(int newSlot);
		unsigned int GetInputMapIndex() const;
		void SetInputMapIndex(unsigned int index);

		int unknownC;
		// The intention state (0x58 bytes; its constructor is 0x107E3710)
		unsigned char unknown10[0x58];
		PlayerControlInfo control;  // +0x68
		bool unknown70;
		unsigned int* unknown74;
		int unknown78;
		int unknown7C;
		core::Name<core::CaseSensitiveKey> unknown80;
	};
}

#endif
