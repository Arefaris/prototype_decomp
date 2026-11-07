// proto::FadeBehaviour and proto::FadeoutBehaviour (RTTI and reflection names; base engine::Behaviour) with the load
// object proto::FadeoutBehaviourProperties: FadeBehaviour blends the drawable of its object in and out and can destroy
// the object when the fade out is done, FadeoutBehaviour lets its object live for a while, fades it out and destroys
// it. Unit 0x10497550 - 0x10498200 (no assert path; the file name is a guess). The reflected names are original, the
// rest is guessed.
#ifndef PROTO_BEHAVIOURS_FADEBEHAVIOUR_H
#define PROTO_BEHAVIOURS_FADEBEHAVIOUR_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace proto
{
	// How long the object lives and how it fades out (RTTI proto::FadeoutBehaviourProperties)
	class FadeoutBehaviourProperties : public content::MetaLoadObject
	{
	public:
		// 0x10497870
		FadeoutBehaviourProperties();
		// 0x10497950 (the deleting destructor)
		virtual ~FadeoutBehaviourProperties()
		{
		}

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		bool checkPhysicsAtRest;  // +8
		bool disablePhysicsForFadeout;  // +9
		float fadeoutLength;  // +0xC
		float lifeLength;  // +0x10
	};

	class FadeoutBehaviour : public engine::Behaviour
	{
	public:
		// 0x10497610
		explicit FadeoutBehaviour(engine::GameObject* newOwner);
		// 0x10497980
		virtual ~FadeoutBehaviour();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x10497650: the time the object has left (its life and the fade out)
		void Restart();

		// vftable slot 1 (0x104979B0)
		virtual void Slot1();
		// vftable slot 4 (0x10497F40): counts the time down, fades the drawable out in the last seconds and destroys the
		// object when it ran out
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x104979D0)
		virtual void OnMessage(engine::Message* message);

		FadeoutBehaviourProperties* properties;  // +0xC
		float timeLeft;  // +0x10
	};

	class FadeBehaviour : public engine::Behaviour
	{
	public:
		enum
		{
			// The states
			FADING_IN = 0,
			FADING_OUT = 1,
			DONE = 2
		};

		// 0x10497670
		explicit FadeBehaviour(engine::GameObject* newOwner);
		virtual ~FadeBehaviour()
		{
		}

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x104977F0: starts again from fully transparent
		void Reset();

		// vftable slot 1 (0x10497A20)
		virtual void Slot1();
		// vftable slot 4 (0x104976F0): moves the opacity towards the end of the state and applies it to the drawable
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x10497A40)
		virtual void OnMessage(engine::Message* message);

		int state;  // +0xC
		float opacity;  // +0x10
		float fadeInTime;  // +0x14
		float fadeOutTime;  // +0x18
		bool destroyOnFadeOutComplete;  // +0x1C
	};
}

#endif
