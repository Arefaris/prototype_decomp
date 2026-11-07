// proto::MusicTreeBehaviour (RTTI and reflection names; base engine::FightTreeBehaviour): the fight tree behaviour of
// the music context. It advances its branch on the owner every update and hands the flags that messages of type 0xb
// (id 0xD) collected to the sequencer. Unit 0x1049ACB0 - 0x1049AF60 (no assert path; the directory and file name are
// guesses). The names of the members are guesses.
#ifndef PROTO_BEHAVIOURS_MUSICTREEBEHAVIOUR_H
#define PROTO_BEHAVIOURS_MUSICTREEBEHAVIOUR_H

#include "code/engine/fight/behaviours/fighttreebehaviour.h"

namespace proto
{
	class MusicTreeBehaviour : public engine::FightTreeBehaviour
	{
	public:
		// 0x1049AD50
		explicit MusicTreeBehaviour(engine::GameObject* newOwner);
		// 0x1049ACF0 (the deleting form is 0x1049ADE0)
		virtual ~MusicTreeBehaviour();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 4 (0x1049AE90): resequences the branch when it ran out, then advances and updates the sequencer
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 5 (0x1049AD40): nothing
		virtual void OnPostedMessage(engine::Message* message);
		// vftable slot 6 (0x1049AD00)
		virtual void OnMessage(engine::Message* message);

		// The flags the messages of type 0xb collected, handed to the sequencer on the next update
		unsigned int pendingFlags;  // +0x68
	};
}

#endif
