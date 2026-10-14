// proto::ParkedCarCloudManager (the singleton 0x1126F15C, vtable 0x10E1B954). The unit is guessed: the class is the
// parked-car instance of the engine's cloud manager, but no assert path names its file.
#include "code/proto/ai/ambientmanager/parkedcarcloudmanager.h"

namespace proto
{
	// The engine helpers the two functions below call, with the addresses their call sites show. All are in other
	// units and only declared here; the names are guesses.
	void EnterCloudLock(unsigned int tag);                       // 0x1063AAD0
	void LeaveCloudLock();                                       // 0x1063AAF0
	void* GetPlayerObject();                                     // 0x107DF530 (its field at +0x14 is a count)
	void ConstructEmptyHandle(void* handle);                     // 0x107EE330
	void* GetCameraForFrame(void* handle, int view, int slot);    // 0x107DE0B0
	void PrepareCameraFrame(void* camera);                       // 0x106DC850
	bool IsPlayerInVehicle();                                    // 0x1047F920 / 0x1047FC60
	int* GetGameMode();                                          // 0x10575B30
	bool IsScriptedCameraActive();                               // 0x1032C1E0
	bool IsCutsceneRunning();                                    // 0x1032BF20
	void* GetMasterTableEntry(const unsigned short* handle);     // 0x103B8B80
	extern void* gCloudContext;                                  // 0x1126E40C (the handle the units share)
	extern void* gMasterTable;                                   // 0x1128348C

	// FUNCTION: ENGINE 0x104EB720
	// NONMATCHING: the whole shape is the original's -- the cursor at 0x64 walks the candidate array at 0x9c by the
	// limit at 0x0c (or the whole array when the manager is paused), every candidate gets the ranking test
	// (0x104F1DC0) with the context at 0xe8, the two positions at 0xdc / 0xd0 and the four floats, the ones the
	// test accepts go into the list at 0x70 and the recycled ones into the list at 0x90 and leave the array -- but
	// the entry indexing and the list pushes are not byte identical.
#ifdef NONMATCHING
	void ParkedCarCloudManager::RankSpawners()
	{
		if (rankedF4 == unknownEC)
		{
			return;
		}
		rankedF4 = unknownEC;

		unsigned int count = (unsigned int)((char*)endA0 - (char*)list9C) / 4;
		if (count >= (unsigned int)limitC)
		{
			count = limitC;
		}
		if (pausedCC)
		{
			count = (unsigned int)((char*)endA0 - (char*)list9C) / 4;
		}
		if (count == 0)
		{
			return;
		}
		unsigned int left = count;
		do
		{
			// the next candidate; the array is walked round and round
			unsigned int total = (unsigned int)((char*)endA0 - (char*)list9C) / 4;
			unsigned int index = 0;
			if (total != 0)
			{
				index = cursor64 % total;
			}
			cursor64 = index;
			CloudSpawnerBase* spawner = ((CloudSpawnerBase**)list9C)[index];

			unsigned char answer[3];
			spawner->Rank(contextE8, positionDC, positionD0, distance60, table1C[spawner->flagsB9 >> 4],
				distance48, distance4C, 0, pausedByte, answer);

			if (answer[0] != 0)
			{
				CloudSpawnerBase** end = (CloudSpawnerBase**)end70;
				if (end < (CloudSpawnerBase**)capacity74)
				{
					end70 = end + 1;
					if (end != 0)
					{
						*end = spawner;
					}
				}
			}
			if (answer[1] != 0)
			{
				CloudSpawnerBase** end = (CloudSpawnerBase**)end90;
				if (end < (CloudSpawnerBase**)capacity94)
				{
					end90 = end + 1;
					if (end != 0)
					{
						*end = spawner;
					}
				}
				// the candidate leaves the array (the last one moves into its place)
				endA0 = (char*)endA0 - 4;
				CloudSpawnerBase** slot = &((CloudSpawnerBase**)list9C)[cursor64];
				if (slot < (CloudSpawnerBase**)endA0)
				{
					*slot = *(CloudSpawnerBase**)endA0;
				}
			}
			else
			{
				cursor64++;
			}
			left--;
		} while (left != 0);
	}
#endif

	// FUNCTION: ENGINE 0x104ECBB0
	// NONMATCHING: the flow is the original's (take the lock, resolve the current player's handle through the master
	// table, pick the frame's camera, decide from the cutscene and script state whether the cars rank against the
	// camera or against the player, publish the two mode bytes at 0xcc / 0xcd, copy the positions, walk the spawner
	// list at 0x8c and give the cars the ranked spawners refuse back), but the classes of the units it calls are not
	// reconstructed far enough to reach byte identity.
#ifdef NONMATCHING
	void ParkedCarCloudManager::Update()
	{
		if (unknownF0 == unknownEC)
		{
			return;
		}
		unknownF0 = unknownEC;
		unknownFC = 1;

		EnterCloudLock(0xffffffff);

		void* handle = 0;
		if (*((int*)GetPlayerObject() + 5) < 1)
		{
			ConstructEmptyHandle(&handle);
		}
		else
		{
			handle = gCloudContext;
		}

		void* object = 0;
		if (handle != 0)
		{
			object = GetMasterTableEntry((const unsigned short*)&handle);
		}

		void* camera = GetCameraForFrame(0, 0);
		int view = *((int*)camera + 0x10);
		if (view == *((int*)camera + 0xf))
		{
			view = *((int*)camera + 0xe);
		}
		PrepareCameraFrame((void*)view);

		bool ranked = true;
		if (*((char*)camera + 0x1e) == 0)
		{
			ranked = IsPlayerInVehicle() && IsScriptedCameraActive();
		}

		int mode = *GetGameMode();
		bool scripted = IsScriptedCameraActive();
		bool cutscene = IsCutsceneRunning();

		unsigned int counter = 0;
		if (!ranked)
		{
			counter = unknown68 + 1;
		}
		unknown68 = counter;

		// whether the spawners rank against the camera and whether they may recycle a car
		pausedCC = (counter < 5 || mode == 8 || scripted);
		pausedByte = (mode == 8 || (scripted && !cutscene));

		if (object != 0)
		{
			// the position the ranking test measures against: the player object's transform (its translation)
			void* attribute = *(void**)((char*)object + 0x1c);
			float* translation = (float*)((char*)attribute + 0x34);
			positionD0[0] = translation[0];
			positionD0[1] = translation[1];
			positionD0[2] = translation[2];

			// the camera's own position, or the player's when the camera is far away or the frame says so
			void* cameraObject = *(void**)((char*)camera + 0x30);
			float dx = *((float*)cameraObject + 0x20) - positionD0[0];
			float dy = *((float*)cameraObject + 0x21) - positionD0[1];
			float dz = *((float*)cameraObject + 0x22) - positionD0[2];
			if (dz * dz + dy * dy + dx * dx > 1e12f || *((int*)camera + 0xc) == 1 ||
				(*((int*)camera + 0xd) == 2 && *((char*)camera + 0x7ad) != 0))
			{
				positionDC[0] = *((float*)cameraObject + 0x20);
				positionDC[1] = *((float*)cameraObject + 0x21);
				positionDC[2] = *((float*)cameraObject + 0x22);
			}
			else
			{
				positionDC[0] = positionD0[0];
				positionDC[1] = positionD0[1];
				positionDC[2] = positionD0[2];
			}

			// the ranking input of the frame: the two positions move into the ranking's own copies and the three
			// spawner lists are emptied (their end pointers go back to their begin pointers)
			unknown68 = (float)unknownEC;
			end70 = list6C;
			endB0 = listAC;
			endC0 = listBC;

			// rank the spawners of the list at 0x8c (the light query at 0x103B8B80's unit decides which of them
			// are lit; the ones the ranking refuses lose their car)
			CloudSpawnerBase** spawners = (CloudSpawnerBase**)list8C;
			unsigned int count = (unsigned int)((char*)endA0 - (char*)list9C) / 4;
			for (unsigned int i = 0; i < count; i++)
			{
				(void)spawners[i];
			}
		}

		LeaveCloudLock();
	}
#endif
}
