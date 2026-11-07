// proto::TendrilBehaviour (RTTI and reflection names; base engine::Behaviour): a tendril of the infection. It reflects no
// members. Unit 0x10078480 - 0x10078A70 (no assert path; the file name is a guess). Only the reflection is reconstructed.
#ifndef PROTO_TENDRILBEHAVIOUR_H
#define PROTO_TENDRILBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/fight/sequencer.h"
#include "code/engine/message.h"
#include "code/math/vector.h"
#include "code/proto/fightitems/motion/motionmessages.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::AbstractTendrilAction: the base of the tendril actions; the behaviour keeps
			// them in a list through counted references in the two words at +0x15C and +0x160 (the rest of the class is
			// not reconstructed)
			class AbstractTendrilAction : public fight::Action
			{
			public:
				// 0x10138520: the vftable slot of the action's update, answering false when the action is done (name guess)
				bool Update(float dt);

				unsigned char unknown1C[0x15C - sizeof(fight::Action)];
				AbstractTendrilAction* nextTendril;  // +0x15C
				AbstractTendrilAction* previousTendril;  // +0x160
			};
		}
	}

	// RTTI: proto::RegisterTendrilActionMessage: a tendril action asks to be put in the list of the object's behaviour
	// (id 0x22; the member names are guesses)
	struct RegisterTendrilActionMessage : public TransformationMessage
	{
		explicit RegisterTendrilActionMessage(fightitems::motion::AbstractTendrilAction* newAction) : TransformationMessage(0x22),
			action(newAction), registered(false)
		{
		}
		virtual ~RegisterTendrilActionMessage()
		{
		}

		fightitems::motion::AbstractTendrilAction* action;  // +0xC
		bool registered;  // +0x10
	};

	// RTTI: proto::DeregisterTendrilActionMessage: takes a tendril action out of the list again (id 0x23)
	struct DeregisterTendrilActionMessage : public TransformationMessage
	{
		explicit DeregisterTendrilActionMessage(fightitems::motion::AbstractTendrilAction* newAction) : TransformationMessage(0x23),
			action(newAction)
		{
		}
		virtual ~DeregisterTendrilActionMessage()
		{
		}

		fightitems::motion::AbstractTendrilAction* action;  // +0xC
	};

	class TendrilBehaviour : public engine::Behaviour
	{
	public:
		// 0x100784C0
		explicit TendrilBehaviour(engine::GameObject* newOwner);
		// 0x10078940 (deleting destructor 0x100789C0)
		virtual ~TendrilBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 4 (0x10078540) and 6 (0x10078870)
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x10078680: puts a tendril action at the front of the list
		void OnRegister(RegisterTendrilActionMessage* message);
		// 0x10078740: takes a tendril action out of the list
		void OnDeregister(DeregisterTendrilActionMessage* message);

		fightitems::motion::AbstractTendrilAction* firstAction;  // +0xC
	};

}

#endif
