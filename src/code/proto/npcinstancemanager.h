// proto::NPCInstanceManager (RTTI name; base engine::RenderTask::PresentationTask): the render task that copies the
// latest pose state into every NPC instance's pose. proto::NPCInstance (RTTI name, one vftable slot) is the pool entry
// it walks. Only the update here is known; the RenderTask hierarchy and the rest are not reconstructed yet. Unit
// 0x10476A50 - 0x10479B10 (no assert path; the directory and file names are guesses). Member names are guesses.
#ifndef PROTO_NPCINSTANCEMANAGER_H
#define PROTO_NPCINSTANCEMANAGER_H

#include "code/pure3d/pose.h"

namespace proto
{
	class NPCInstance
	{
	public:
		virtual ~NPCInstance() = 0;

		// 0x10476A50: copies the source pose (at +0x184 of sourceHolder) over the destination pose
		void UpdatePose(float dt);

		int unknown4;
		int unknown8;
		pure3d::Pose* destPose;
		void* sourceHolder;
	};

	class NPCInstanceManager
	{
	public:
		// 0x10479B10 (vftable slot 0): updates every instance in the pool
		void Update(int a1, int a2, float dt, int a3, int a4, int a5);

		int unknown0;
		NPCInstance** begin;
		NPCInstance** end;
	};
}

#endif
