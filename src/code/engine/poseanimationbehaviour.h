// engine::PoseAnimationBehaviour (RTTI and reflection name; base engine::Behaviour): plays pose animations on the
// drawable of a game object. It makes a pose animation controller for the pose of the object's drawable when it first
// needs one and publishes it as the attribute "pose animation controller", takes the animation, the frame range and
// the playback mode from the messages of type 10 and keeps the object's "animation finished" and "poseAwake" attributes
// up to date. Unit 0x109208B0 - 0x10921440 (no assert path; the file name is a guess). The reflected name is original;
// the rest is guessed.
#ifndef ENGINE_POSEANIMATIONBEHAVIOUR_H
#define ENGINE_POSEANIMATIONBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"
#include "code/pure3d/framecontroller.h"

namespace pure3d
{
	class PoseAnimationController;
}

namespace engine
{
	// The message (type 10, id 0) that starts an animation, as the behaviour reads it (names guessed)
	struct PoseAnimationMessage : public Message
	{
		pure3d::Entity* animation;  // +0xC
		float speed;  // +0x10
		float time;  // +0x14
		float rangeStart;  // +0x18
		float rangeEnd;  // +0x1C
		int cycleMode;  // +0x20
		int numCycles;  // +0x24
	};

	// The message (type 10, id 1) that changes the way the animation plays
	struct PoseAnimationPlaybackMessage : public Message
	{
		float rangeStart;  // +0xC
		float rangeEnd;  // +0x10
		float speed;  // +0x14
		int cycleMode;  // +0x18
		int numCycles;  // +0x1C
	};

	// The message (type 1) that tells an attribute was set: the name of the attribute is at +0x10
	struct PoseAttributeMessage : public Message
	{
		unsigned char unknownC[4];
		core::Name<core::CaseSensitiveKey> name;  // +0x10
	};

	// The messages (type 0x17, ids 4 and 6) that tell who controls the animation
	struct PoseControlMessage : public Message
	{
		unsigned char unknownC[0xC];
		GameObjectHandle handle;  // +0x18
	};

	// The attribute that publishes the controller (its constructor is inline in the unit)
	template<> class Attribute<pure3d::PoseAnimationController*> : public ConstAttribute<pure3d::PoseAnimationController*>
	{
	public:
		// 0x10920FF0 (kept copy)
		Attribute() : ConstAttribute<pure3d::PoseAnimationController*>(0)
		{
		}
	};

	class PoseAnimationBehaviour : public Behaviour
	{
	public:
		// 0x10921260
		explicit PoseAnimationBehaviour(GameObject* newOwner);
		// 0x10920DC0 (deleting destructor 0x10921010)
		virtual ~PoseAnimationBehaviour();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10920DE0): makes the controller for the drawable's animation source
		virtual void Slot1();
		// vftable slot 4 (0x10920B50): advances the animation
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x10921320)
		virtual void OnMessage(Message* message);

		// 0x10920C60 / 0x10920CD0: makes the controller for the drawable's pose / lets it go
		void CreateController();
		void DestroyController();
		// 0x10920E50: updates the attributes and the update passes after a change
		void UpdateActivity();
		// 0x10921030 / 0x10921040: lets the animation run / stops it from running
		void Resume();
		void Pause();
		// 0x109208F0: sends the animation back to its start
		void Rewind();
		// 0x10921050 / 0x10921170: start an animation / change the way it plays
		void Play(PoseAnimationMessage* message);
		void SetPlayback(PoseAnimationPlaybackMessage* message);
		// 0x109209A0 / 0x109209F0: the sequence (an object of the scenario) starts / ends controlling the animation
		void OnControlBegin(PoseControlMessage* message);
		void OnControlEnd(PoseControlMessage* message);

		pure3d::FrameController* controller;  // +0xC
		float pendingTime;  // +0x10
		bool paused;  // +0x14
		GameObjectHandle handle;  // +0x16
	};
}

#endif
