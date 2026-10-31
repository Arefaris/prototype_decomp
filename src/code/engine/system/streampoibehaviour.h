// engine::StreamPOIBehaviour (RTTI name; base engine::Behaviour): keeps the transform of its game object at the
// position of the world streamer's current point of interest of a player. Unit 0x108982B0 - 0x108983A0 (no assert
// path; the file name is a guess). The member name is a guess.
#ifndef ENGINE_SYSTEM_STREAMPOIBEHAVIOUR_H
#define ENGINE_SYSTEM_STREAMPOIBEHAVIOUR_H

#include "code/engine/gameobject/behaviour.h"

namespace engine
{
	class StreamPOIBehaviour : public Behaviour
	{
	public:
		// 0x108982B0
		explicit StreamPOIBehaviour(GameObject* newOwner);
		// 0x108982E0 (deleting destructor 0x10898390)
		virtual ~StreamPOIBehaviour();

		// vftable slot 1 (0x108982F0): listens to the update passes of mask 4
		virtual void Slot1();
		// slot 4 (0x10898300): puts the object at the point of interest of the player
		virtual void Update(float dt, unsigned short mask);
		// slot 6 (0x10898360): message type 0x18, id 7 moves the object at once
		virtual void OnMessage(Message* message);

		int playerIndex;  // +0xC
	};
}

#endif
