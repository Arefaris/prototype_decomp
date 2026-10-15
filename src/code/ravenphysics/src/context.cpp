#include "code/core/debug.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/physicsobject.h"
#include "code/ravenphysics/context.h"

#define CONTEXT_FILE "..\\..\\..\\code\\ravenphysics\\src\\context.cpp"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x106566C0
	void Context::QueryObject(PhysicsBody* object)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x5e7, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryBody(object, unknownC4, object->filter & 3);
	}

	// FUNCTION: ENGINE 0x10656730
	void Context::QuerySweepObject(PhysicsBody* object, void* ray)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x604, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryPair(object, ray, unknownC4, object->filter & 3);
	}

	// FUNCTION: ENGINE 0x106567A0
	void Context::QueryObjectRay(PhysicsBody* object, void* ray)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x644, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryBodyRay(object, unknownC4, ray);
	}

	// FUNCTION: ENGINE 0x10656810
	void Context::QueryObjectShape(PhysicsBody* object, void* a, void* b)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x662, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryBodyShape(object, a, unknownC4, b);
	}

	// FUNCTION: ENGINE 0x10656880
	void Context::UpdateCollisionPairs()
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x69a, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		collisionBatch.Update(mWorld, unknownC4);
	}

	// FUNCTION: ENGINE 0x106568E0
	void* Context::AddCollisionPair(void* first, void* second)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6aa, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		collisionBatch.Add(first, second, 4);
		return first;
	}

	// FUNCTION: ENGINE 0x10656950
	void* Context::AddCollisionPairSlow(void* first, void* second)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6af, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		collisionBatch.Add(first, second, 8);
		return first;
	}

	// FUNCTION: ENGINE 0x106569C0
	void* Context::AddCollisionPairStatic(void* first, void* second)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6b4, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		collisionBatch.Add(first, second, 0x10);
		return first;
	}

	// FUNCTION: ENGINE 0x10656A30
	void Context::UpdateConstraints()
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6c1, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		constraintBatch.Update(mWorld, unknownC4);
	}

	// FUNCTION: ENGINE 0x10656A90
	void* Context::AddConstraint(void* first, void* second)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6d1, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		constraintBatch.Add(first, second, 0);
		return first;
	}

	// FUNCTION: ENGINE 0x10656B00
	void* Context::AddConstraintAwake(void* first, void* second)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6d6, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		constraintBatch.Add(first, second, 1);
		return first;
	}

	// FUNCTION: ENGINE 0x10656B70
	void* Context::AddConstraintAsleep(void* first, void* second)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6db, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		constraintBatch.Add(first, second, 2);
		return first;
	}

	// FUNCTION: ENGINE 0x10656BE0
	void Context::UpdateQueries()
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6e8, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		queryBatch.Update(mWorld, unknownC4);
	}

	// FUNCTION: ENGINE 0x10656C40
	void* Context::AddQuery(void* a, void* b, void* c, void* d)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x6f9, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		queryBatch.Add(a, b, c, d);
		return a;
	}

	// FUNCTION: ENGINE 0x10656CB0
	void Context::QueryShape(void* a, void* b, void* c, void* d)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x715, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryShape(a, b, c, unknownC4, d);
	}

	// FUNCTION: ENGINE 0x10656D20
	void Context::QueryShapeSwept(void* a, void* b, void* c, void* d)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x73d, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryShapeOther(a, b, c, unknownC4, d);
	}

	// FUNCTION: ENGINE 0x10656D90
	void Context::QuerySphere(void* a, void* b, void* c, void* d)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x768, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryShape3(a, b, c, unknownC4, d);
	}

	// FUNCTION: ENGINE 0x10656E00
	void Context::QuerySphereSwept(void* a, void* b, void* c, void* d)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x790, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		mWorld->QueryShape2(a, b, c, unknownC4, d);
	}

	// FUNCTION: ENGINE 0x10656E70
	void Context::SetSolverIterations(int a, int b)
	{
		unknown10->solverIterations = a;
		unknown10->solverIterations2 = b;
	}

	// FUNCTION: ENGINE 0x10656640
	void Context::SetWorldFlag(unsigned char value)
	{
		if (placement != 0)
		{
			unknown10->unknownE = value;
		}
	}

	// FUNCTION: ENGINE 0x10656660
	void Context::ResetPlacement()
	{
		placement->Reset();
	}

	// FUNCTION: ENGINE 0x10656670
	void Context::SetPlacementPosition(math::Vector position)
	{
		placement->SetPosition(position);
	}

	// FUNCTION: ENGINE 0x10656680
	void Context::TrackMovableObjects()
	{
		placement->Track(&movableObjects);
	}

	// FUNCTION: ENGINE 0x10656690
	void Context::TrackObjects(ObjectList* objects)
	{
		placement->Track(objects);
	}

	// FUNCTION: ENGINE 0x106566A0
	void Context::UntrackMovableObjects()
	{
		placement->Untrack(&movableObjects);
	}

	// FUNCTION: ENGINE 0x106566B0
	void Context::UntrackObjects(ObjectList* objects)
	{
		placement->Untrack(objects);
	}

	// FUNCTION: ENGINE 0x10656E90
	PlacementTracker* Context::GetPlacement()
	{
		return placement;
	}

	// FUNCTION: ENGINE 0x10657C90
	void Context::RefreshObjectList(ObjectList* objects)
	{
		OLD_ASSERT_AT(CONTEXT_FILE, 0x42f, !gLock.IsLocked(), "!gLock.IsLocked()", "");
		void** it = objects->begin;
		for (; it != objects->end; it++)
		{
			PhysicsObject* object = static_cast<PhysicsObject*>(*it);
			if (!object->IsSkipped())
			{
				object->RefreshBounds(0);
			}
		}
	}
}
