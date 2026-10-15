#include "code/engine/physics/physicsmanager.h"
#include "code/core/interlocked.h"

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
	CollisionBrokeringMessage::~CollisionBrokeringMessage()
	{
	}

	// FUNCTION: ENGINE 0x107E38E0
	CollisionResponseMessage::~CollisionResponseMessage()
	{
	}

	// FUNCTION: ENGINE 0x107E3940
	BatchedRayCastMessage::~BatchedRayCastMessage()
	{
	}

	// FUNCTION: ENGINE 0x107E3990
	BatchedRayCastHitMessage::~BatchedRayCastHitMessage()
	{
	}

	// FUNCTION: ENGINE 0x107E3A30
	BatchedShapeCastMessage::~BatchedShapeCastMessage()
	{
	}

	// FUNCTION: ENGINE 0x107E3A70
	BatchedShapeCastHitMessage::~BatchedShapeCastHitMessage()
	{
	}

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
