// engine::camera::CameraBehaviour and engine::camera::CinematographerBehaviour (RTTI names; reflected as
// "engine::camera::CameraBehaviour" / "engine::camera::CinematographerBehaviour"; base engine::Behaviour): the
// behaviours that put a Camera / a Cinematographer into a game object. They register what they hold with the
// Director when they start, answer the camera messages (type 12: id 0 / 1 ask for the camera / the cinematographer,
// id 2 resets) and copy the pure3d camera's matrix into the owner's transform every frame. CameraBehaviour is unit
// 0x10850490 - 0x10850980 and CinematographerBehaviour 0x1084FFF0 - 0x10850490 (no assert path; the directory and
// file names are guesses). The reflected member names are original; the rest is guessed.
#ifndef ENGINE_CAMERA_CAMERABEHAVIOUR_H
#define ENGINE_CAMERA_CAMERABEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/camera/camera.h"
#include "code/engine/camera/cinematographer.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace engine
{
	namespace camera
	{
		// Asks for the camera / the cinematographer of an object (message type 12, ids 0 and 1; names guessed)
		struct GetCameraMessage : public Message
		{
			Camera* camera;
		};

		struct GetCinematographerMessage : public Message
		{
			Cinematographer* cinematographer;
		};

		class CameraBehaviour : public Behaviour
		{
		public:
			// 0x108508D0
			explicit CameraBehaviour(GameObject* newOwner);
			// 0x10850520 (deleting destructor 0x10850630)
			virtual ~CameraBehaviour();

			static content::ClassInfo* GetClassInfo();
			// 0x108504E0: the earlier version of the class (version 2, code "p")
			static content::ClassInfo* GetClassInfoV2();
			static content::MemberList* GetMembers();
			// 0x10850770: the earlier version's members (none besides the base class)
			static content::MemberList* GetMembersV2();

			// vftable slot 1 (0x10850540): registers the camera with the Director and activates the owner
			virtual void Slot1();
			// vftable slot 4 (0x10850680): the owner's transform follows the pure3d camera
			virtual void Update(float dt, unsigned short mask);
			// vftable slot 5 (0x10850590): the camera is asked for
			virtual void OnPostedMessage(Message* message);
			// vftable slot 6 (0x10850650): the reset message
			virtual void OnMessage(Message* message);

			// 0x108505B0: takes the camera over (the old one is deleted)
			void SetCamera(Camera* newCamera);

			Camera* camera;  // +0xC
		};

		class CinematographerBehaviour : public Behaviour
		{
		public:
			// 0x10850430
			explicit CinematographerBehaviour(GameObject* newOwner);
			// 0x10850030 (deleting destructor 0x10850190)
			virtual ~CinematographerBehaviour();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// vftable slot 1 (0x10850050): starts the cinematographer (when it registers itself) and activates the owner
			virtual void Slot1();
			// vftable slot 4 (0x108501E0): the owner's transform follows the pure3d camera
			virtual void Update(float dt, unsigned short mask);
			// vftable slot 5 (0x108500A0): the cinematographer is asked for
			virtual void OnPostedMessage(Message* message);
			// vftable slot 6 (0x108501B0): the reset message
			virtual void OnMessage(Message* message);

			// 0x108500C0: takes the cinematographer over (the old one is deleted)
			void SetCinematographer(Cinematographer* newCinematographer);

			Cinematographer* cinematographer;  // +0xC
			bool autoRegister;  // +0x10
		};
	}
}

#endif
