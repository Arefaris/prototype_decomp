// engine::animation::PuppetBehaviour (RTTI and reflection names; bases engine::Behaviour and
// choreo::Puppet::ValidationFailedCallback at +0xC): makes the puppet (the animation state) of a game object when it has
// a drawable, updates and evaluates it every frame and puts its pose together. Unit 0x1091B1C0 - 0x1091C4F0 (the assert
// path code/engine/animation/behaviours/puppetbehaviour.cpp is in its messages). The reflected member names are
// original; the rest is guessed.
#ifndef ENGINE_ANIMATION_BEHAVIOURS_PUPPETBEHAVIOUR_H
#define ENGINE_ANIMATION_BEHAVIOURS_PUPPETBEHAVIOUR_H

#include "code/choreo/puppet.h"
#include "code/choreo/puppetmanager.h"
#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace engine
{
	namespace animation
	{
		// The velocities of the root the puppet's motion gives (the asserts name mLocomotionState.linearVelocity and
		// .angularVelocity; the type name is a guess)
		struct LocomotionState
		{
			// 0x107E05D0 (another unit)
			LocomotionState();
			// 0x107E05A0 (another unit)
			void Reset();

			float linearVelocity[3];  // +0
			float angularVelocity[3];  // +0xC
		};

		// The message (type 10, id 5) that asks for the locomotion state, and (type 0x11, id 8) for whether the limbs
		// are inverse kinematics driven
		struct GetLocomotionMessage : public Message
		{
			float linearVelocity[3];  // +0xC
			float angularVelocity[3];  // +0x18
		};
		struct GetIkLimbsMessage : public Message
		{
			bool ikLimbsEnabled;  // +0xC
		};
		// The message (type 0x11, id 9) that sets it
		struct SetIkLimbsMessage : public Message
		{
			bool ikLimbsEnabled;  // +0xC
		};
		// The messages of type 0x19: id 0 resets the time scale of the puppet, id 1 sets it
		struct PuppetTimeScaleMessage : public Message
		{
			float timeScale;  // +0xC
		};

		class PuppetBehaviour : public Behaviour, public choreo::Puppet::ValidationFailedCallback
		{
		public:
			// 0x1091C400
			explicit PuppetBehaviour(GameObject* newOwner);
			// 0x1091B360 (deleting destructor 0x1091B920)
			virtual ~PuppetBehaviour();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// vftable slot 1 (0x1091C0E0): makes the puppet when the behaviour is active
			virtual void Slot1();
			// vftable slot 3 (0x1091C070): makes or takes away the puppet with the activity
			virtual void OnActiveChanged(bool active);
			// vftable slot 4 (0x1091B940, not reconstructed)
			virtual void Update(float dt, unsigned short mask);
			// vftable slot 5 (0x1091B390): answers the questions about the locomotion state and the limbs
			virtual void OnPostedMessage(Message* message);
			// vftable slot 6 (0x1091C100): the drawable attribute, the reset and the time scale messages
			virtual void OnMessage(Message* message);

			// The callback's slot (0x1091B2E0): not an error while batching is disabled and the member says so
			virtual int OnValidationFailed(int unknown4, bool disableBatching, int unknown12);

			// The reflected accessors: "ikLimbsEnabled" (0x1091B1D0 / 0x1091B1E0), "autoUpdateLocomotionPhase"
			// (0x1091B200 / 0x1091B220) and "deferredUpdate" (0x1091B240 / 0x1091B3F0, not reconstructed)
			bool GetIkLimbsEnabled() const;
			void SetIkLimbsEnabled(bool value);
			bool GetAutoUpdateLocomotionPhase() const;
			void SetAutoUpdateLocomotionPhase(bool value);
			bool GetDeferredUpdate() const;
			void SetDeferredUpdate(bool value);
			// 0x1091B250 (name guess): with a handle the puppet takes the owner's time scale, without it the unit scale
			void UpdateTimeScale(bool enable);
			// 0x1091BC50 / 0x1091BD20 (names guessed): makes the puppet of the drawable and tells the render
			// behaviour / takes it away
			void CreatePuppet();
			void DestroyPuppet();
			// 0x1091B430 / 0x1091B460 (names guessed)
			void Suspend(Message* message);
			void Resume(Message* message);

			choreo::Puppet* puppet;  // +0x10
			bool unknown14;
			bool ikLimbsEnabled;  // +0x15
			bool autoUpdateLocomotionPhase;  // +0x16
			bool deferredUpdate;  // +0x17
			choreo::PuppetHandle handle;  // +0x18
			float unknown20;
			bool suppressErrorOnDisableBatching;  // +0x24
			LocomotionState locomotionState;  // +0x28
		};
	}
}

#endif
