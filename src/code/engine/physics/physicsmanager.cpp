#include "code/engine/physics/physicsmanager.h"
#include "code/core/interlocked.h"
#include "code/container/arraydynamicnew.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/ravenphysics/common/hashtable.h"
#include "code/core/debug.h"
#include "code/core/file/file.h"
#include "code/core/file/filesystem.h"

namespace ravenphysics
{
	// The keys the manager's table holds are the objects' ids, so a key's slot is its index in the table. The chain
	// of a bucket runs from buckets[bucket] through next[] and ends at 0xFFFF; every slot is taken once, so
	// Insert of a key the table already holds gives it a second slot.

	// FUNCTION: ENGINE 0x107E7120
	void KeyTable::Create(unsigned int entries, ScratchStack* stack)
	{
		Init((unsigned short)entries, (unsigned short)entries, stack);
		keys = (unsigned int*)stack->Alloc(entries * 4, 16);
		count = 0;
		capacity = entries;
		order = (unsigned int*)stack->Alloc(entries * 4, 16);
		orderCapacity = entries;
		orderCount = 0;
	}

	// FUNCTION: ENGINE 0x107E6BC0
	unsigned short KeyTable::Find(unsigned int key) const
	{
		unsigned int bucket = ((key + 3) * key) % bucketCount;
		unsigned short slot = buckets[bucket];
		while (slot != 0xFFFF)
		{
			if (keys[slot] == key)
			{
				break;
			}
			slot = next[slot];
		}
		return slot;
	}

	// FUNCTION: ENGINE 0x107E5AB0
	unsigned short KeyTable::FindFrom(unsigned short slot, unsigned int key) const
	{
		while (slot != 0xFFFF)
		{
			if (keys[slot] == key)
			{
				return slot;
			}
			slot = next[slot];
		}
		return slot;
	}

	// FUNCTION: ENGINE 0x107E6C00
	unsigned short KeyTable::FindAfter(unsigned short slot, unsigned int key) const
	{
		for (slot = next[slot]; slot != 0xFFFF; slot = next[slot])
		{
			if (keys[slot] == key)
			{
				break;
			}
		}
		return slot;
	}

	// FUNCTION: ENGINE 0x107E6C40
	// NONMATCHING: same instructions in the same order, but the new slot and the old chain head come out in the other
	// pair of registers (eax/esi swapped), 87 %
#ifdef NONMATCHING
	void KeyTable::Insert(unsigned int key)
	{
		unsigned int bucket = ((key + 3) * key) % bucketCount;
		unsigned short slot = buckets[bucket];
		while (slot != 0xFFFF)
		{
			if (keys[slot] == key)
			{
				break;
			}
			slot = next[slot];
		}
		if (slot == 0xFFFF)
		{
			orderCount++;
			unsigned int* item = order + orderCount - 1;
			if (item != 0)
			{
				*item = key;
			}
		}
		unsigned short index = (unsigned short)count++;
		unsigned int* entry = keys + count - 1;
		if (entry != 0)
		{
			*entry = key;
		}
		unsigned short previous = buckets[bucket];
		buckets[bucket] = index;
		next[index] = previous;
	}
#endif
}

// The unit's instantiations of the growable array: the manager collects collisions and unsolved constraints into one
// array each and hands the ranges to the collision messages (0x107E4340 - 0x107E4720 and 0x107E5830 - 0x107E5930)
namespace container
{
	template class ArrayDynamicNew<unsigned int>;
	template class ArrayDynamicNew<engine::CollisionItem>;
	template class ArrayDynamicNew<engine::ConstraintItem>;
	template class ArrayDynamicNew<engine::CollisionPair>;
}

// The four-argument script wrapper the pm_ListSelectedObjects registration builds (function.h), and the
// LuaScriptManager::Register instantiation that goes with it: the compiler inlines the wrapper at the call site but
// keeps this copy too (0x107E6B70), which is why the unit has the constructor, Call and Invoke of the wrapper as well.
// FUNCTION: ENGINE 0x107E59C0
// FUNCTION: ENGINE 0x107E5A30
// FUNCTION: ENGINE 0x107E5A70
// FUNCTION: ENGINE 0x107E6B70

// FUNCTION: ENGINE 0x107E4340
// FUNCTION: ENGINE 0x107E4390
// FUNCTION: ENGINE 0x107E43A0
// FUNCTION: ENGINE 0x107E43B0
// FUNCTION: ENGINE 0x107E43C0
// FUNCTION: ENGINE 0x107E43E0
// FUNCTION: ENGINE 0x107E4400
// FUNCTION: ENGINE 0x107E4410
// FUNCTION: ENGINE 0x107E4420
// FUNCTION: ENGINE 0x107E4440
// FUNCTION: ENGINE 0x107E44B0
// FUNCTION: ENGINE 0x107E4500
// FUNCTION: ENGINE 0x107E4550
// FUNCTION: ENGINE 0x107E45D0
// FUNCTION: ENGINE 0x107E4720
// FUNCTION: ENGINE 0x107E4770
// FUNCTION: ENGINE 0x107E5830
// FUNCTION: ENGINE 0x107E5840
// FUNCTION: ENGINE 0x107E5890
// FUNCTION: ENGINE 0x107E58B0
// FUNCTION: ENGINE 0x107E58E0
// FUNCTION: ENGINE 0x107E5900
// FUNCTION: ENGINE 0x107E5930
// FUNCTION: ENGINE 0x107E69C0
// FUNCTION: ENGINE 0x107E69F0
// FUNCTION: ENGINE 0x107E6A20
// FUNCTION: ENGINE 0x107E6A40
// FUNCTION: ENGINE 0x107E6A70
// FUNCTION: ENGINE 0x107E6B50
// FUNCTION: ENGINE 0x107E6B60
// FUNCTION: ENGINE 0x107E70E0
// FUNCTION: ENGINE 0x107E7100

namespace engine
{
	// The shared query buffers and their lock flags
	bool gRayHitBufferLocked;              // 0x11283570
	ravenphysics::RayHitArray gRayHitBuffer; // 0x112835E4
	bool gHitIndexBufferLocked;            // 0x11283571
	HitIndexArray gHitIndexBuffer;         // 0x112835D4
	bool gCollisionBufferLocked;           // 0x11283572
	CollisionArray gCollisionBuffer;       // 0x11283638
	bool gPhysicsUpdating;                 // 0x11283573

	// FUNCTION: ENGINE 0x107E6CD0
	RayHitBufferLock::RayHitBufferLock(bool clear)
	{
		gRayHitBufferLocked = true;
		if (clear)
		{
			gRayHitBuffer.end = gRayHitBuffer.begin;
		}
	}

	// FUNCTION: ENGINE 0x107E3C20
	RayHitBufferLock::~RayHitBufferLock()
	{
		gRayHitBufferLocked = false;
	}

	// FUNCTION: ENGINE 0x107E3C30
	ravenphysics::RayHitArray& RayHitBufferLock::Get()
	{
		return gRayHitBuffer;
	}

	// FUNCTION: ENGINE 0x107E6CF0
	HitIndexBufferLock::HitIndexBufferLock(bool clear)
	{
		gHitIndexBufferLocked = true;
		if (clear)
		{
			gHitIndexBuffer.end = gHitIndexBuffer.begin;
		}
	}

	// FUNCTION: ENGINE 0x107E3C40
	HitIndexBufferLock::~HitIndexBufferLock()
	{
		gHitIndexBufferLocked = false;
	}

	// FUNCTION: ENGINE 0x107E3C50
	HitIndexArray& HitIndexBufferLock::Get()
	{
		return gHitIndexBuffer;
	}

	// FUNCTION: ENGINE 0x107E6D10
	CollisionBufferLock::CollisionBufferLock(bool clear)
	{
		gCollisionBufferLocked = true;
		if (clear)
		{
			gCollisionBuffer.end = gCollisionBuffer.begin;
		}
	}

	// FUNCTION: ENGINE 0x107E3C60
	CollisionBufferLock::~CollisionBufferLock()
	{
		gCollisionBufferLocked = false;
	}

	// FUNCTION: ENGINE 0x107E3C70
	CollisionArray& CollisionBufferLock::Get()
	{
		return gCollisionBuffer;
	}

	// FUNCTION: ENGINE 0x107E3C80
	void SetPhysicsUpdating()
	{
		gPhysicsUpdating = true;
	}

	// FUNCTION: ENGINE 0x107E3C90
	void ClearPhysicsUpdating()
	{
		gPhysicsUpdating = false;
	}

	// FUNCTION: ENGINE 0x107E3CA0
	bool IsPhysicsUpdating()
	{
		return gPhysicsUpdating;
	}

	// The console command values: which object the debug draw works on and which of the two modes it is in
	int gDebugDrawObject = -1;    // 0x111BC37C
	int gDebugDrawMode;           // 0x11283560
	int gDebugTrackObject = -1;   // 0x111BC380
	int gDebugTrackMode;          // 0x11283564

	// FUNCTION: ENGINE 0x107E3F20
	void pm_DrawInertia(int value)
	{
		gDebugDrawObject = value;
		gDebugDrawMode = 0;
	}

	// FUNCTION: ENGINE 0x107E3F40
	void pm_DrawObjectUIDs()
	{
		gDebugDrawObject = -1;
		gDebugDrawMode = 2;
	}

	// FUNCTION: ENGINE 0x107E3F60
	void pm_TrackAABB(int value)
	{
		gDebugTrackObject = value;
		gDebugTrackMode = 0;
	}

	// The collision log the pm_LogCollisions command opens: 1 while the log is on, the frames left to log and the
	// file itself (0x11283594 - 0x1128359C; names guessed)
	int gCollisionLogState;            // 0x11283594
	unsigned int gCollisionLogFrames;  // 0x11283598
	core::IFile* gCollisionLog;        // 0x1128359C

	// FUNCTION: ENGINE 0x107E4010
	// NONMATCHING: the engine materialises the path argument in its stack slot after pushing the other eight (one
	// wildcard push, the address, then the literal), ours pushes the literal directly; 53 %
#ifdef NONMATCHING
	void pm_LogCollisions(int frames)
	{
		if (gCollisionLogState == 0)
		{
			core::FileSystemOpenFile(&gCollisionLog, "collisionLog.txt", true, 3, 1, 0, 1, 1, 0);
			if (!gCollisionLog->IsOpen())
			{
				gCollisionLog->Release();
				gCollisionLog = 0;
			}
			gCollisionLogState = 1;
			gCollisionLogFrames = frames;
		}
	}
#endif

	// FUNCTION: ENGINE 0x107E3F90
	// NONMATCHING: the engine issues the "logging off" store between the two loads that prepare the Release call,
	// ours issues it right after the pointer load; 90 %
#ifdef NONMATCHING
	void UpdateCollisionLog()
	{
		if (gCollisionLogState == 1)
		{
			if (gCollisionLogFrames <= 0)
			{
				gCollisionLogState = 0;
				gCollisionLog->Release();
				gCollisionLog = 0;
			}
			else
			{
				static bool sLog = true;
				if (sLog && core::Report(0, " Pre ", "..\\..\\..\\code\\engine\\physics\\physicsmanager.cpp", 2529, 0,
					"Logging collisions frame %d.", gCollisionLogFrames, 0) == 3)
				{
					sLog = false;
				}
				gCollisionLogFrames--;
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x107E4090
	void pm_SetSolverIterations(int a, int b)
	{
		ravenphysics::gContext->SetSolverIterations(a, b);
	}

	// FUNCTION: ENGINE 0x107E3870
	CollisionBrokeringMessage::CollisionBrokeringMessage(const CollisionItemList& newItems)
		: IntrusiveMessage(4, 0), items(newItems)
	{
	}

	// FUNCTION: ENGINE 0x107E38B0
	CollisionResponseMessage::CollisionResponseMessage(const CollisionItemList& newItems)
		: IntrusiveMessage(5, 0), items(newItems)
	{
	}

	// FUNCTION: ENGINE 0x107E38F0
	BatchedRayCastMessage::BatchedRayCastMessage(unsigned int newUnknownC, unsigned int newUnknown10, unsigned int newUnknown14,
		unsigned int newUnknown18, unsigned int newUnknown1C)
		: IntrusiveMessage(3, 1), unknownC(newUnknownC), unknown10(newUnknown10), unknown14(newUnknown14),
		  unknown18(newUnknown18), unknown1C(newUnknown1C)
	{
	}

	// FUNCTION: ENGINE 0x107E3950
	BatchedRayCastHitMessage::BatchedRayCastHitMessage(unsigned int newIndex, unsigned int newUnknown10, unsigned int newUnknown14)
		: IntrusiveMessage(3, 2), index(newIndex), unknown10(newUnknown10), unknown14(newUnknown14)
	{
	}

	// FUNCTION: ENGINE 0x107E39A0
	BatchedShapeCastMessage::BatchedShapeCastMessage(unsigned int newUnknownC, unsigned int newUnknown10, unsigned int newUnknown14,
		unsigned int newUnknown18, unsigned int newUnknown1C)
		: IntrusiveMessage(3, 3), unknownC(newUnknownC), unknown10(newUnknown10), unknown14(newUnknown14),
		  unknown18(newUnknown18), unknown1C(newUnknown1C)
	{
	}

	// FUNCTION: ENGINE 0x107E39F0
	BatchedShapeCastHitMessage::BatchedShapeCastHitMessage(unsigned int newIndex, unsigned int newUnknown10, unsigned int newUnknown14)
		: IntrusiveMessage(3, 4), index(newIndex), unknown10(newUnknown10), unknown14(newUnknown14)
	{
	}

	// FUNCTION: ENGINE 0x107E3A40
	PhysicsFixupUnsolvedConstraintsMessage::PhysicsFixupUnsolvedConstraintsMessage(unsigned int newUnknown10)
		: IntrusiveMessage(3, 0x1D), unknown10(newUnknown10)
	{
	}

	// FUNCTION: ENGINE 0x107E3A80
	PhysicsFixupPoweredConstraintsMessage::PhysicsFixupPoweredConstraintsMessage(unsigned int newUnknown10)
		: IntrusiveMessage(3, 0x1E), unknown10(newUnknown10)
	{
	}

	// FUNCTION: ENGINE 0x107E38A0
	inline CollisionBrokeringMessage::~CollisionBrokeringMessage()
	{
	}

	// FUNCTION: ENGINE 0x107E38E0
	inline CollisionResponseMessage::~CollisionResponseMessage()
	{
	}

	// FUNCTION: ENGINE 0x107E3940
	inline BatchedRayCastMessage::~BatchedRayCastMessage()
	{
	}

	// FUNCTION: ENGINE 0x107E3990
	inline BatchedRayCastHitMessage::~BatchedRayCastHitMessage()
	{
	}

	// FUNCTION: ENGINE 0x107E3A30
	inline BatchedShapeCastMessage::~BatchedShapeCastMessage()
	{
	}

	// FUNCTION: ENGINE 0x107E3A70
	inline BatchedShapeCastHitMessage::~BatchedShapeCastHitMessage()
	{
	}

	// The compiler's scalar deleting destructors of the eight messages: the destructor is empty and sits in the class
	// body, so `??_G` expands it into the vftable store (the destructors above are its out-of-line copies).
	// FUNCTION: ENGINE 0x107E4810
	// FUNCTION: ENGINE 0x107E4830
	// FUNCTION: ENGINE 0x107E4850
	// FUNCTION: ENGINE 0x107E4870
	// FUNCTION: ENGINE 0x107E4890
	// FUNCTION: ENGINE 0x107E48B0
	// FUNCTION: ENGINE 0x107E48D0
	// FUNCTION: ENGINE 0x107E48F0

	// FUNCTION: ENGINE 0x107E3790
	long __fastcall AtomicIncrement(long volatile* value)
	{
		return _InterlockedIncrement(value);
	}

	// FUNCTION: ENGINE 0x107E37A0
	long __fastcall AtomicDecrement(long volatile* value)
	{
		return _InterlockedDecrement(value);
	}

	// FUNCTION: ENGINE 0x107E37B0
	// NONMATCHING: the engine's copy takes the value in eax (a link-time code generation convention), ours in edx, 60 %
#ifdef NONMATCHING
	long __fastcall AtomicExchange(long volatile* value, long newValue)
	{
		return _InterlockedExchange(value, newValue);
	}
#endif

	// The manager's frame counter and the two debug flags around it (names guessed)
	int gPhysicsFrame = 1;    // 0x111BC2E4 (the engine starts it at 1)
	int gDebugUnknown;        // 0x11283590

	// FUNCTION: ENGINE 0x107E3CF0
	void ResetPhysicsFrame()
	{
		gPhysicsFrame = 1;
	}

	// FUNCTION: ENGINE 0x107E3D40
	int NextPhysicsFrame()
	{
		return gPhysicsFrame++;
	}

	// FUNCTION: ENGINE 0x107E3DD0
	void SetDebugUnknown(int value)
	{
		gDebugUnknown = value;
	}

	// FUNCTION: ENGINE 0x107E3DE0
	void ClearDebugUnknown()
	{
		gDebugUnknown = 0;
	}

	// FUNCTION: ENGINE 0x107E5180
	void pm_ListStaticObjects()
	{
		ListObjects(&ravenphysics::gContext->staticObjects, false, false, false, false);
	}

	// FUNCTION: ENGINE 0x107E51A0
	void pm_ListMovableObjects()
	{
		ListObjects(&ravenphysics::gContext->movableObjects, false, false, false, false);
	}

	// FUNCTION: ENGINE 0x107E51C0
	void pm_ListAwakePhysicsObjects()
	{
		ListObjects(&ravenphysics::gContext->movableObjects, true, false, true, false);
	}

	// FUNCTION: ENGINE 0x107E51E0
	void pm_ListAsleepObjects()
	{
		ListObjects(&ravenphysics::gContext->movableObjects, false, true, true, false);
	}

	// FUNCTION: ENGINE 0x107E5200
	void pm_ListSelectedObjects(bool awake, bool asleep, bool physics, bool trigger)
	{
		ListObjects(&ravenphysics::gContext->movableObjects, awake, asleep, physics, trigger);
		ListObjects(&ravenphysics::gContext->staticObjects, awake, asleep, physics, trigger);
	}

	// FUNCTION: ENGINE 0x107E5250
	void pm_ListPhysicsObjects()
	{
		pm_ListSelectedObjects(false, false, true, false);
	}

	// FUNCTION: ENGINE 0x107E5270
	void pm_ListTriggerObjects()
	{
		pm_ListSelectedObjects(false, false, false, true);
	}

	// FUNCTION: ENGINE 0x107E5290
	void pm_ListObjects()
	{
		pm_ListStaticObjects();
		pm_ListMovableObjects();
	}

	// The number of solver substeps the console limits to 1 .. 10
	int gSubsteps = 2;    // 0x111BC2E8

	// FUNCTION: ENGINE 0x107E6F20
	void RegisterPhysicsCommands()
	{
		LuaScriptManager* manager = GetScriptManager();
		manager->SetOwner(ravenphysics::gContext);
		manager->Register("pm_Help", pm_Help);
		manager->Register("pm_ListObjects", pm_ListObjects);
		manager->Register("pm_ListStaticObjects", pm_ListStaticObjects);
		manager->Register("pm_ListMovableObjects", pm_ListMovableObjects);
		manager->Register("pm_ListAwakePhysicsObjects", pm_ListAwakePhysicsObjects);
		manager->Register("pm_ListAsleepObjects", pm_ListAsleepObjects);
		manager->Register("pm_ListTriggerObjects", pm_ListTriggerObjects);
		manager->Register("pm_ListPhysicsObjects", pm_ListPhysicsObjects);
		manager->Register("pm_ListSelectedObjects", pm_ListSelectedObjects);
		manager->Register("pm_ListCollisionObjects", pm_ListCollisionObjects);
		manager->Register("pm_ListConstraints", pm_ListConstraints);
		manager->Register("pm_ListAllConstraints", pm_ListAllConstraints);
		manager->Register("pm_ListVolumes", pm_ListVolumes);
		manager->Register("pm_ObjectInfo", pm_ObjectInfo);
		manager->Register("pm_DrawObjectUIDs", pm_DrawObjectUIDs);
		manager->Register("pm_DrawInertia", pm_DrawInertia);
		manager->Register("pm_TrackAABB", pm_TrackAABB);
		manager->Register("pm_LogCollisions", pm_LogCollisions);
		manager->Register("pm_Substeps", pm_Substeps);
		manager->Register("pm_SetSolverIterations", pm_SetSolverIterations);
	}

	// FUNCTION: ENGINE 0x107E57E0
	void pm_Substeps(int substeps)
	{
		if (substeps < 1)
		{
			substeps = 1;
		}
		else if (substeps >= 10)
		{
			substeps = 10;
		}
		gSubsteps = substeps;
	}
}
