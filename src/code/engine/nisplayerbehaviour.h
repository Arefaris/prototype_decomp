// engine::NISPlayerBehaviour (RTTI and reflection names; base engine::Behaviour): plays a non-interactive sequence.
// It names the sequence ("nisName"), finds its fight branch in the NIS fight context, runs it on its own sequencer and
// keeps the play state (loading, playing, ended ...), telling the scenario system when a sequence begins, ends or
// finishes loading. Unit 0x1091F890 - 0x10920900 (no assert path; the file name is a guess). The reflected member
// names are original; the rest is guessed.
#ifndef ENGINE_NISPLAYERBEHAVIOUR_H
#define ENGINE_NISPLAYERBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/fight/sequencer.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace engine
{
	// The message (type 0x17) the NIS player answers: the ids ask for the sequence's name (10), its play state (11) and
	// its length (12)
	struct NISQueryMessage : public Message
	{
		int state;  // +0xC (id 11)
		core::Name<core::CaseSensitiveKey> name;  // +0x10 (id 10)
		float length;  // +0x18 (id 12)
	};

	// The part of the sequence's track the player reads
	struct NISTrack
	{
		unsigned char unknown0[0x8C];
		float length;  // +0x8C
	};

	class NISPlayerBehaviour : public Behaviour
	{
	public:
		// 0x1091FA50
		explicit NISPlayerBehaviour(GameObject* newOwner);

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x1091FF70 (deleting destructor 0x10920490; not reconstructed)
		virtual ~NISPlayerBehaviour();

		// vftable slot 0 (0x1091FAD0, not reconstructed): makes the parameters
		virtual void Slot0();
		// vftable slot 1 (0x1091F8D0, not reconstructed)
		virtual void Slot1();
		// vftable slot 4 (0x109201C0, not reconstructed)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 5 (0x1091FB30): answers the queries
		virtual void OnPostedMessage(Message* message);
		// vftable slot 6 (0x10920720, not reconstructed)
		virtual void OnMessage(Message* message);

		fight::Sequencer sequencer;  // +0x10
		core::Name<core::CaseSensitiveKey> nisName;  // +0x58
		core::IRefCount* params;  // +0x60
		void* package;  // +0x64
		NISTrack* track;  // +0x68
		int camera;  // +0x6C
		int unknown70;
		int state;  // +0x74
		float unknown78;
	};
}

#endif
