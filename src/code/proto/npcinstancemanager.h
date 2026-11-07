// proto::NPCInstanceManager (RTTI name; base engine::RenderTask::PresentationTask): the render task that copies the
// latest pose state into the pose of every animation of the pedestrians that are shown. Only the update here is known;
// the RenderTask hierarchy and the rest are not reconstructed yet. Unit 0x10479B10 (no assert path; the directory and file
// names are guesses). Member names are guesses.
#ifndef PROTO_NPCINSTANCEMANAGER_H
#define PROTO_NPCINSTANCEMANAGER_H

#include "code/proto/npcanimation.h"

namespace proto
{
	class NPCInstanceManager
	{
	public:
		// 0x10479B10 (vftable slot 0): updates the pose of every animation in the list
		void Update(int a1, int a2, float dt, int a3, int a4, int a5);

		int unknown0;
		NPCAnimation** begin;
		NPCAnimation** end;
	};
}

#endif
