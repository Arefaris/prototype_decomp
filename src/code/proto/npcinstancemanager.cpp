// proto::NPCInstanceManager: the render task that copies the latest pose state into each NPC instance's pose. See
// npcinstancemanager.h for the model; names are guesses.
#include "code/proto/npcinstancemanager.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10476A50
	// EQUIVALENT: the engine loads the destination pose between the source test and its branch; our compiler keeps
	// the load after the branch (same instructions, same order)
	void NPCInstance::UpdatePose(float dt)
	{
		pure3d::Pose* source = *(pure3d::Pose**)((char*)sourceHolder + 0x184);
		if (source != 0 && destPose != 0)
		{
			destPose->CopyStateFrom(source);
		}
	}

	// FUNCTION: ENGINE 0x10479B10
	void NPCInstanceManager::Update(int a1, int a2, float dt, int a3, int a4, int a5)
	{
		int count = end - begin;
		for (int i = 0; i < count; i++)
		{
			begin[i]->UpdatePose(dt);
		}
	}
}
