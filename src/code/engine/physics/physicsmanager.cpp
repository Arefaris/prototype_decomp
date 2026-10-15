#include "code/engine/physics/physicsmanager.h"

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
}
