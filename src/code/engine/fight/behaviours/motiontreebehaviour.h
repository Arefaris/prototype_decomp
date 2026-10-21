// engine::MotionTreeBehaviour (RTTI and reflection names; base engine::FightTreeBehaviour): the fight tree behaviour of
// the motion context. It runs the tree's branch on the owner, resequences it when it ends (autoResequence) and keeps
// the behaviour's update switched on while there is something to run. Unit 0x1091F380 - 0x1091F890 (no assert path; the
// directory and file name are guesses). The reflected member name is original; the rest is guessed.
#ifndef ENGINE_FIGHT_BEHAVIOURS_MOTIONTREEBEHAVIOUR_H
#define ENGINE_FIGHT_BEHAVIOURS_MOTIONTREEBEHAVIOUR_H

#include "code/engine/fight/behaviours/fighttreebehaviour.h"

namespace engine
{
	class MotionTreeBehaviour : public FightTreeBehaviour
	{
	public:
		// 0x1091F480
		explicit MotionTreeBehaviour(GameObject* newOwner);
		virtual ~MotionTreeBehaviour()
		{
		}

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x1091F3C0 / 0x1091F550 (the reflected member)
		bool GetAutoResequence() const;
		void SetAutoResequence(bool value);
		// 0x1091F3D0: the behaviour listens to updates (type 4) while the sequencer has actions, or always without
		// autoResequence
		void UpdateListening();

		// vftable slot 3 (0x1091F470)
		virtual void OnActiveChanged(bool active);
		// vftable slot 4 (0x1091F5B0): the update pass 4 hands the pending flags to the sequencer, updates and advances
		// it, and starts the branch again when it ran out
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 5 (0x1091F6B0)
		virtual void OnPostedMessage(Message* message);
		// vftable slot 6 (0x1091F400)
		virtual void OnMessage(Message* message);

		// The flags the messages of type 0xb / 0xf collected, handed to the sequencer on the next update
		unsigned int pendingFlags;  // +0x68
		bool autoResequence;  // +0x6C
	};
}

#endif
