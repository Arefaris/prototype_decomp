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

namespace engine
{
	namespace animation
	{
		class PuppetBehaviour : public Behaviour, public choreo::Puppet::ValidationFailedCallback
		{
		public:
			// 0x1091C400 (not reconstructed)
			explicit PuppetBehaviour(GameObject* newOwner);

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// The callback's slot (0x1091B2E0, not reconstructed)
			virtual void OnValidationFailed();

			// The reflected accessors: "ikLimbsEnabled" (0x1091B1D0 / 0x1091B1E0), "autoUpdateLocomotionPhase"
			// (0x1091B200 / 0x1091B220) and "deferredUpdate" (0x1091B240 / 0x1091B3F0, not reconstructed)
			bool GetIkLimbsEnabled() const;
			void SetIkLimbsEnabled(bool value);
			bool GetAutoUpdateLocomotionPhase() const;
			void SetAutoUpdateLocomotionPhase(bool value);
			bool GetDeferredUpdate() const;
			void SetDeferredUpdate(bool value);

			choreo::Puppet* puppet;  // +0x10
			bool unknown14;
			bool ikLimbsEnabled;  // +0x15
			bool autoUpdateLocomotionPhase;  // +0x16
			bool deferredUpdate;  // +0x17
			choreo::PuppetHandle handle;  // +0x18
			float unknown20;
			bool suppressErrorOnDisableBatching;  // +0x24
			// The locomotion state: the velocities of the root (0x107E05D0)
			float unknown28[6];
		};
	}
}

#endif
