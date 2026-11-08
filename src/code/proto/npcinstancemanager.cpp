// proto::NPCInstanceManager: the render task that copies the latest pose state into each animation's pose. See
// npcinstancemanager.h for the model; names are guesses.
#include "code/proto/npcinstancemanager.h"
#include "code/choreo/puppet.h"
#include "code/pure3d/pose.h"

namespace proto
{
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
