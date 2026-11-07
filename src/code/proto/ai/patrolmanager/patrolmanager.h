// proto::PatrolManager (RTTI name of the script wrappers): the manager of the ai patrols (the flying, middle and
// ground patrols of the helicopters and the army) that the scripts steer through the ai_patrol_* functions. Unit
// 0x10428750 - 0x1042E200 (no assert path; the file name and the member names are guesses from the script function
// names). Only what the reconstructed members touch is laid out.
#ifndef PROTO_AI_PATROLMANAGER_PATROLMANAGER_H
#define PROTO_AI_PATROLMANAGER_PATROLMANAGER_H

namespace engine
{
	class LuaGOH;
}

namespace proto
{
	class PatrolManager
	{
	public:
		// 0x10429500 (ai_patrol_Enable): switching it off clears the state
		void Enable(bool newEnabled);
		// 0x10428760 (ai_patrol_IsEnabled)
		bool IsEnabled();
		// 0x10428B60 (ai_patrol_RequestPatrol)
		void RequestPatrol(int newType);
		// 0x10428B90: forgets the patrol being requested and the timers
		void ClearRequest();
		// 0x10429520 / 0x10429540 / 0x10429560 (ai_patrol_SetMaxFlyingPatrols / SetMaxGroundPatrols / SetMaxPatrols)
		void SetMaxFlyingPatrols(int count);
		void SetMaxGroundPatrols(int count);
		void SetMaxPatrols(int count);
		// 0x10428770 .. 0x104288D0 (ai_patrol_SetMaxGroundPatrolDistance, SetMaxFlyingPatrolDistance,
		// SetMinPatrolDistance, SetMinInterPatrolDistance, SetSpawnRetryWait, SetForcedSpawnWait, SpawnPlayerBias,
		// SetMaxGroundHeight, SetMinMiddleHeight, SetMaxMiddleHeight, SetMinTopHeight, SetGroundHeight)
		void SetMaxGroundPatrolDistance(float distance);
		void SetMaxFlyingPatrolDistance(float distance);
		void SetMinPatrolDistance(float distance);
		void SetMinInterPatrolDistance(float distance);
		void SetSpawnRetryWait(float time);
		void SetForcedSpawnWait(float time);
		void SetSpawnPlayerBias(float bias);
		void SetMaxGroundHeight(float height);
		void SetMinMiddleHeight(float height);
		void SetMaxMiddleHeight(float height);
		void SetMinTopHeight(float height);
		void SetGroundHeight(float height);
		// 0x10428BE0 / 0x10428C00 / 0x10428C60 (ai_patrol_SetSpawnDelay, AddSpawnDelay, SetDefeatDelay)
		void SetSpawnDelay(float time);
		void AddSpawnDelay(float time);
		void SetDefeatDelay(float time);

		bool enabled;  // +0
		bool requested;  // +1
		unsigned char unknown2[2];
		int requestedType;  // +4
		unsigned char unknown8[0x14 - 8];
		float spawnPlayerBias;  // +0x14
		float spawnDelay;  // +0x18
		float unknown1C;
		int maxPatrols;  // +0x20
		int patrolCount;  // +0x24
		int maxFlyingPatrols;  // +0x28
		int maxGroundPatrols;  // +0x2C
		float defeatDelay;  // +0x30
		float unknown34;
		unsigned char unknown38[0x44 - 0x38];
		float maxGroundPatrolDistance;  // +0x44
		float maxFlyingPatrolDistance;  // +0x48
		float minPatrolDistance;  // +0x4C
		float minInterPatrolDistance;  // +0x50
		float spawnRetryWait;  // +0x54
		float forcedSpawnWait;  // +0x58
		unsigned char unknown5C[4];
		float maxGroundHeight;  // +0x60
		float minMiddleHeight;  // +0x64
		float maxMiddleHeight;  // +0x68
		float minTopHeight;  // +0x6C
		float groundHeight;  // +0x70
		unsigned char unknown74[0x5C8 - 0x74];
		float unknown5C8;
		float unknown5CC;
		bool unknown5D0;
	};
}

#endif
