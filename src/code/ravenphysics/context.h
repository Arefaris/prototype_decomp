// The parts of the physics library (ravenphysics, assert path code/ravenphysics/src/context.cpp) that the engine's
// units call: the query filter, the ray query and its hits, and the context behind the global 0x1128356C. Only the
// members those callers touch are named; everything here is a guess except the class names the RTTI gives.
#ifndef RAVENPHYSICS_CONTEXT_H
#define RAVENPHYSICS_CONTEXT_H

#include "code/content/loadinventory.h"
#include "code/math/vector.h"
#include "code/ravenphysics/broadphase/broadphasedetector.h"

namespace ravenphysics
{
	class WorldBody;
	class PhysicsObject;
	class ObjectTable;

	// An object the library refers to by its index in its object table (name guess)
	struct ObjectHandle
	{
		// The object the index refers to (0x106560A0; name guess)
		PhysicsObject* GetObject() const;

		unsigned short index;    // 0x00
		unsigned short unknown2; // 0x02
	};

	// What a query collides with (0x10653860 constructs it from the physics library's defaults; meanings unknown)
	struct IntersectionProperties
	{
		IntersectionProperties();

		int unknown0;
		int unknown4;
	};

	// ravenphysics::IntersectionPropertiesLoader (RTTI; a load object of the physics library)
	class IntersectionPropertiesLoader : public content::LoadObject
	{
	public:
		unsigned char unknown8[0x3c - 8];
		int unknown3C;
		int unknown40;
	};

	// The properties plus one more word, copied as a whole into a query
	struct IntersectionFilter
	{
		IntersectionFilter()
		{
			unknown8 = 0;
		}

		IntersectionProperties properties;
		int unknown8;
	};

	// A segment query from start to end
	struct RayQuery
	{
		RayQuery()
		{
			unknown24 = 3;
		}

		math::Vector start;
		math::Vector end;
		IntersectionFilter filter;
		int unknown24;
	};

	// One hit of a query (0x30 bytes): the distance from the start, the object hit and the surface normal
	struct RayHit
	{
		// The material byte of the surface hit (0x1066C4C0)
		unsigned char GetMaterial() const;

		float distance;
		int unknown4;
		int unknown8;
		math::Vector normal;
		unsigned char unknown18[0x30 - 0x18];
	};

	// The hits a query appends to (begin / end / capacity)
	struct RayHitArray
	{
		RayHit* begin;
		RayHit* end;
		RayHit* capacity;
	};

	// One of the context's object lists: an array of object pointers (name guess)
	struct ObjectList
	{
		void** begin;
		void** end;
	};

	// The registry behind Context+0x0C: the objects by the identity they carry (name guess). Its members live in
	// another unit; this unit only calls them.
	class ObjectRegistry
	{
	public:
		// 0x10686980
		void Remove(PhysicsObject* object);
	};

	// The tracker behind Context+0x08: a position the objects of a list are handed to (the class name and the
	// member names are guesses). Its members live in another unit; this unit only calls them.
	class PlacementTracker
	{
	public:
		// 0x10686DA0
		void Reset();
		// 0x10686DB0
		void SetPosition(const math::Vector& position);
		// 0x10687C10
		void Track(ObjectList* objects);
		// 0x10687CA0
		void Untrack(ObjectList* objects);
		// The simulation step: moves and solves the objects of every list against the body (0x10689EE0; name guess)
		void Advance(WorldBody* body, void* data, void* a, float dt, void* worldData, void* registry, void* b);

		math::Vector position; // 0x00
	};

	// The objects the context's queries run against, as far as this unit reads them: the flag word whose low two
	// bits select the intersection filter of the query (layout from this unit's code; the name is a guess)
	struct PhysicsBody
	{
		unsigned char unknown0[0x24];
		unsigned int filter; // 0x24
	};

	// The body the context's setter methods write (the object at Context+0x10; name and members are guesses)
	class WorldBody
	{
	public:
		unsigned char unknown0[0xE];
		unsigned char unknownE;  // 0xE
		unsigned char unknownF[0x1C - 0xF];
		int solverIterations;    // 0x1C
		int unknown20;
		int solverIterations2;   // 0x24
	};

	// The world behind Context+0: this unit forwards its queries into it by vtable slot (0x00 - 0x54; the class
	// name and every slot name are guesses, only the slots this unit calls are declared, in vtable order)
	class World
	{
	public:
		virtual void Unknown00();
		virtual void Unknown04();
		virtual void Unknown08();
		virtual void Unknown0C();
		// 0x10
		virtual bool Overlaps(void* object, void* world);
		// 0x14
		virtual bool Contains(void* object, void* world);
		virtual void Unknown18();
		virtual void Unknown1C();
		virtual void Unknown20();
		virtual void Unknown24();
		virtual void Unknown28();
		virtual void Unknown2C();
		// 0x30
		virtual void QueryShape(void* a, void* b, void* c, void* world, void* d);
		// 0x34
		virtual void QueryShapeOther(void* a, void* b, void* c, void* world, void* d);
		virtual void Unknown38();
		// 0x3C
		virtual void QueryPair(void* a, void* b, void* world, unsigned int flags);
		// 0x40
		virtual void QueryBody(PhysicsBody* object, void* world, unsigned int flag);
		virtual void Unknown44();
		// 0x48
		virtual void QueryBodyShape(void* a, void* b, void* world, void* c);
		// 0x4C
		virtual void QueryBodyRay(void* a, void* world, void* b);
		// 0x50
		virtual void QueryShape2(void* a, void* b, void* c, void* world, void* d);
		// 0x54
		virtual void QueryShape3(void* a, void* b, void* c, void* world, void* d);
	};

	// The context's internal work lists: the collision pairs it is processing (Context+0x24, 48-byte entries),
	// the constraints its solver works on (Context+0x58, 168-byte entries) and a third one (Context+0x8C). Their
	// members live in the collision library's own units; this unit only calls them, so nothing but the calls is
	// declared here (every name and the sizes are guesses).
	// The collision detector wrapper behind Context+0x108 (the class name and the member names are guesses; the two
	// members the asserts name are the detector's own pointer and the object it belongs to)
	class CollisionDetector
	{
	public:
		// Clears the detector pointer and the object (0x10656580)
		CollisionDetector* Clear();
		// The object the detector works on; asserts that the detection is running (0x10656590)
		void* GetObject();
		// 0x106565E0
		void* GetBody();
		// As GetBody, through the detector pointer (0x10657C40)
		void* GetBodyChecked();

		unsigned char unknown0[8];
		void* body; // 0x08
		unsigned char unknownC[0x24 - 0xC];
		CollisionDetector* mCollisionDetectorInternal; // 0x24
		void* unknown28;                               // 0x28
	};

	class CollisionBatch
	{
	public:
		// Runs every entry of the list against the world (0x1068B190)
		void Update(World* world, void* worldData);
		// Appends an entry; mode is 4, 8 or 0x10 (0x1068B340)
		void* Add(void* first, void* second, int mode);

		unsigned char unknown0[0x34];
	};

	class ConstraintBatch
	{
	public:
		// Runs every entry of the list against the world (0x1068DE00)
		void Update(World* world, void* worldData);
		// Appends an entry; mode is 0, 1 or 2 (0x1068DD60)
		void* Add(void* first, void* second, int mode);

		unsigned char unknown0[0x34];
	};

	class QueryBatch
	{
	public:
		// Runs every entry of the list against the world (0x10671A60)
		void Update(World* world, void* worldData);
		// Appends an entry (0x10671580)
		void* Add(void* a, void* b, void* c, void* d);

		unsigned char unknown0[0x38];
	};

	class Context
	{
	public:
		// The hits along the query's segment, appended to hits after clearing it; false when there are none
		// (0x106593A0)
		bool CastRay(const RayQuery& query, RayHitArray* hits);

		// The solver's iteration counts (0x10656E70; name guess)
		void SetSolverIterations(int a, int b);

		// The world's line-of-sight test: what lies between the object and its target (0x106566C0; name guess)
		void QueryObject(PhysicsBody* object);
		// The sweep-and-prune detector's ray against the object (0x10656730; name guess)
		void QuerySweepObject(PhysicsBody* object, void* ray);
		// The object's ray cast (0x106567A0; name guess)
		void QueryObjectRay(PhysicsBody* object, void* ray);
		// The object's shape cast (0x10656810; name guess)
		void QueryObjectShape(PhysicsBody* object, void* a, void* b);
		// The shape query against one body (0x10656CB0 / 0x10656D20 / 0x10656D90 / 0x10656E00; names are guesses)
		void QueryShape(void* a, void* b, void* c, void* d);
		void QueryShapeSwept(void* a, void* b, void* c, void* d);
		void QuerySphere(void* a, void* b, void* c, void* d);
		void QuerySphereSwept(void* a, void* b, void* c, void* d);

		// Runs the lists' entries against the world (0x10656880 / 0x10656A30 / 0x10656BE0; names are guesses)
		void UpdateCollisionPairs();
		void UpdateConstraints();
		void UpdateQueries();
		// Appends to one of the lists and returns the first argument (0x106568E0 - 0x10656B70; names are guesses)
		void* AddCollisionPair(void* first, void* second);
		void* AddCollisionPairSlow(void* first, void* second);
		void* AddCollisionPairStatic(void* first, void* second);
		void* AddConstraint(void* first, void* second);
		void* AddConstraintAwake(void* first, void* second);
		void* AddConstraintAsleep(void* first, void* second);
		// 0x10656C40
		void* AddQuery(void* a, void* b, void* c, void* d);

		// Hands every collision object of the handle's object to a world (0x106564E0; name guess)
		void ResetObjectWorld(ObjectHandle handle, void* world);
		// Takes a sleeping object out of the registry and the detector (0x10657B60; name guess)
		void SleepObject(PhysicsObject* object);
		// One simulation step of the whole context (0x106565F0; name guess)
		void Advance(void* a, float dt, void* b);
		// The flag the body carries at +0x0E, set when the tracker exists (0x10656640; name guess)
		void SetWorldFlag(unsigned char value);
		// The tracker's position and the lists it hands over (0x10656660 - 0x106566B0; names are guesses)
		void ResetPlacement();
		void SetPlacementPosition(math::Vector position);
		void TrackMovableObjects();
		void TrackObjects(ObjectList* objects);
		void UntrackMovableObjects();
		void UntrackObjects(ObjectList* objects);
		// 0x10656E90
		PlacementTracker* GetPlacement();
		// Clears the "changed" flag of every object of the list that is not left out of the queries and
		// recomputes the bounds of those that had it set (0x10657C90; name guess)
		void RefreshObjectList(ObjectList* objects);

		World* mWorld;             // 0x00
		int unknown4;              // 0x04
		PlacementTracker* placement;   // 0x08
		ObjectRegistry* registry;      // 0x0C
		WorldBody* unknown10;      // 0x10
		ObjectList staticObjects;  // 0x14 (the pm_ commands' "static" list)
		ObjectList movableObjects; // 0x1C (the pm_ commands' "movable" list)
		CollisionBatch collisionBatch;   // 0x24
		ConstraintBatch constraintBatch; // 0x58
		QueryBatch queryBatch;           // 0x8C
		BroadPhaseDetector* unknownC4;   // 0xC4
		unsigned char unknownC8[0xD8 - 0xC8];
		bool unknownD8; // 0xD8
		unsigned char unknownD9[0x108 - 0xD9];
		CollisionDetector* detector; // 0x108
		unsigned char unknown10C[4];
	};

	// The physics context (0x1128356C)
	extern Context* gContext;

	// Sorts hits by distance (another unit's instance of a sort template, 0x1006DC30)
	void SortHits(RayHit* begin, RayHit* end);
}

namespace engine
{
	// The engine's shared buffer of query hits, held for the length of a query (another unit, 0x107E3C20 -
	// 0x107E6CD0; the class name is a guess)
	class RayHitBufferLock
	{
	public:
		// Takes the buffer, emptied when clear is set (0x107E6CD0)
		RayHitBufferLock(bool clear);
		// 0x107E3C20
		~RayHitBufferLock();
		// 0x107E3C30
		ravenphysics::RayHitArray& Get();
	};
}

#endif
