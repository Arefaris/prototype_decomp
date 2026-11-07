// proto::CloudBehaviour (RTTI and reflection names; base engine::PropBehaviour): the behaviour of the objects a cloud
// spawner makes. Unit 0x104F3420 - 0x104F3620 (no assert path; the file name is a guess). The reflected member name is
// original, the rest is guessed.
#ifndef PROTO_BEHAVIOURS_CLOUDBEHAVIOUR_H
#define PROTO_BEHAVIOURS_CLOUDBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/propbehaviour.h"

namespace proto
{
	class CloudBehaviour : public engine::PropBehaviour
	{
	public:
		// 0x104F3470
		explicit CloudBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		float maxRadius;  // +0xC
	};
}

#endif
