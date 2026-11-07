#include "code/proto/ai/patrolmanager/patrolmanager.h"

namespace proto
{
	// FUNCTION: ENGINE 0x10428760
	bool PatrolManager::IsEnabled()
	{
		return enabled;
	}

	// FUNCTION: ENGINE 0x10428770
	void PatrolManager::SetMaxGroundPatrolDistance(float distance)
	{
		maxGroundPatrolDistance = distance;
	}

	// FUNCTION: ENGINE 0x10428790
	void PatrolManager::SetMaxFlyingPatrolDistance(float distance)
	{
		maxFlyingPatrolDistance = distance;
	}

	// FUNCTION: ENGINE 0x104287B0
	void PatrolManager::SetMinPatrolDistance(float distance)
	{
		minPatrolDistance = distance;
	}

	// FUNCTION: ENGINE 0x104287D0
	void PatrolManager::SetMinInterPatrolDistance(float distance)
	{
		minInterPatrolDistance = distance;
	}

	// FUNCTION: ENGINE 0x104287F0
	void PatrolManager::SetSpawnRetryWait(float time)
	{
		spawnRetryWait = time;
	}

	// FUNCTION: ENGINE 0x10428810
	void PatrolManager::SetForcedSpawnWait(float time)
	{
		forcedSpawnWait = time;
	}

	// FUNCTION: ENGINE 0x10428830
	void PatrolManager::SetSpawnPlayerBias(float bias)
	{
		spawnPlayerBias = bias;
	}

	// FUNCTION: ENGINE 0x10428850
	void PatrolManager::SetMaxGroundHeight(float height)
	{
		maxGroundHeight = height;
	}

	// FUNCTION: ENGINE 0x10428870
	void PatrolManager::SetMinMiddleHeight(float height)
	{
		minMiddleHeight = height;
	}

	// FUNCTION: ENGINE 0x10428890
	void PatrolManager::SetMaxMiddleHeight(float height)
	{
		maxMiddleHeight = height;
	}

	// FUNCTION: ENGINE 0x104288B0
	void PatrolManager::SetMinTopHeight(float height)
	{
		minTopHeight = height;
	}

	// FUNCTION: ENGINE 0x104288D0
	void PatrolManager::SetGroundHeight(float height)
	{
		groundHeight = height;
	}

	// FUNCTION: ENGINE 0x104288F0
	void PatrolManager::SetWatertowerFactor(float first, float second)
	{
		watertowerFactorFirst = first;
		watertowerFactorSecond = second;
	}

	// FUNCTION: ENGINE 0x10428920
	void PatrolManager::SetWatertowerActivateDistance(float distance)
	{
		watertowerActivateDistance = distance;
	}

	// FUNCTION: ENGINE 0x10428940
	void PatrolManager::SetWatertowerDeactivateDistance(float distance)
	{
		watertowerDeactivateDistance = distance;
	}

	// FUNCTION: ENGINE 0x10428960
	void PatrolManager::SetWatertowerHatchDelay(float time)
	{
		watertowerHatchDelay = time;
	}

	// FUNCTION: ENGINE 0x10428980
	void PatrolManager::SetWatertowerNoSpawnTimer(float time)
	{
		watertowerNoSpawnTimer = time;
	}

	// FUNCTION: ENGINE 0x10428B60
	void PatrolManager::RequestPatrol(int newType)
	{
		requested = true;
		spawnDelay = 0.0f;
		requestedType = newType;
	}

	// FUNCTION: ENGINE 0x10428B90
	void PatrolManager::ClearRequest()
	{
		requested = false;
		spawnDelay = 0.0f;
		unknown1C = 0.0f;
		patrolCount = maxPatrols;
		unknown34 = 0.0f;
		watertowerNoInfectionTimer = 0.0f;
		watertowerNoSpawnTimer = 0.0f;
		unknown5D0 = false;
	}

	// FUNCTION: ENGINE 0x10428BE0
	void PatrolManager::SetSpawnDelay(float time)
	{
		spawnDelay = time;
	}

	// FUNCTION: ENGINE 0x10428C00
	void PatrolManager::AddSpawnDelay(float time)
	{
		spawnDelay = time + spawnDelay;
	}

	// FUNCTION: ENGINE 0x10428C40
	void PatrolManager::SetWatertowerNoInfectionTimer(float time)
	{
		watertowerNoInfectionTimer = time;
	}

	// FUNCTION: ENGINE 0x10428C60
	void PatrolManager::SetDefeatDelay(float time)
	{
		defeatDelay = time;
	}

	// FUNCTION: ENGINE 0x10429500
	void PatrolManager::Enable(bool newEnabled)
	{
		if (enabled != newEnabled)
		{
			enabled = newEnabled;
			if (!newEnabled)
			{
				ClearRequest();
			}
		}
	}

	// FUNCTION: ENGINE 0x10429520
	void PatrolManager::SetMaxFlyingPatrols(int count)
	{
		if (count >= 4)
		{
			count = 4;
		}
		maxFlyingPatrols = count;
	}

	// FUNCTION: ENGINE 0x10429540
	void PatrolManager::SetMaxGroundPatrols(int count)
	{
		if (count >= 4)
		{
			count = 4;
		}
		maxGroundPatrols = count;
	}

	// FUNCTION: ENGINE 0x10429560
	void PatrolManager::SetMaxPatrols(int count)
	{
		if (count >= 4)
		{
			count = 4;
		}
		maxPatrols = count;
		patrolCount = count;
	}
}
