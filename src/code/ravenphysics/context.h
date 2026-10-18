// The parts of the physics library (ravenphysics, assert path code/ravenphysics/src/context.cpp) that the engine's
// units call: the query filter, the ray query and its hits, and the context behind the global 0x1128356C. Only the
// members those callers touch are named; everything here is a guess except the class names the RTTI gives.
#ifndef RAVENPHYSICS_CONTEXT_H
#define RAVENPHYSICS_CONTEXT_H

#include "code/content/loadinventory.h"
#include "code/core/name.h"
#include "code/math/vector.h"
#include "code/ravenphysics/batch/midphasebatcher.h"
#include "code/ravenphysics/broadphase/broadphasedetector.h"
#include "code/ravenphysics/common/stackallocator.h"
#include "code/ravenphysics/common/hashtable.h"
#include "code/ravenphysics/intersectionproperties.h"

namespace ravenphysics
{
	class WorldBody;
	class PhysicsObject;
	class ObjectTable;
	class NarrowPhaseBatcher;
	class Context;
	struct RegistryRef;
	struct HandlePairRun;
	struct BodyPairRun;
	struct PointerRun;

	// An object the library refers to by its index in its object table (name guess)
	struct ObjectHandle
	{
		// The object the index refers to (0x106560A0; name guess)
		PhysicsObject* GetObject() const;
		// The engine's second copy of the same lookup, the one this unit's own code calls (0x1065F500; name guess)
		PhysicsObject* GetObjectSecond() const;

		unsigned short index;    // 0x00
		unsigned short unknown2; // 0x02
	};

	// One entry of the registry of known properties (0x1127CAC4, count 0x1127CACC, capacity 0x1127CAC8): the name
	// they are registered under and the properties the entry stands for (0x10 bytes)
	struct IntersectionPropertiesEntry
	{
		// An empty name and the default properties (0x10653AA0)
		IntersectionPropertiesEntry();
		// The entry for these properties under that name (0x10653830)
		IntersectionPropertiesEntry(const core::Name<core::CaseSensitiveKey>& entryName,
			const IntersectionProperties& entryProperties);
		// Empty (0x106538F0)
		~IntersectionPropertiesEntry();
		// The properties the entry stands for (0x10653630)
		IntersectionProperties* GetProperties();

		core::Name<core::CaseSensitiveKey> name;   // 0x00
		IntersectionProperties properties;         // 0x08
	};

	// The registry of known properties (names guessed)
	extern IntersectionPropertiesEntry* gIntersectionProperties;
	extern unsigned int gIntersectionPropertyCount;
	extern unsigned int gIntersectionPropertyCapacity;

	// How many entries the registry holds (0x10653720)
	unsigned int GetIntersectionPropertyCount();
	// One entry of the registry (0x10653730)
	IntersectionPropertiesEntry* GetIntersectionProperty(unsigned short index);
	// The entry whose properties these are, or null (0x106536D0)
	IntersectionPropertiesEntry* FindIntersectionProperty(const IntersectionProperties& properties);

	// ravenphysics::IntersectionPropertiesLoader (RTTI; a load object of the physics library)
	class IntersectionPropertiesLoader : public content::LoadObject
	{
	public:
		unsigned char unknown8[0x3c - 8];
		int unknown3C;
		int unknown40;
	};

	// ravenphysics::ColliderTypeNames (RTTI; a load object that names the collider types): the names are a run at +8
	class ColliderTypeNames : public content::LoadObject
	{
	public:
		core::Name<core::CaseSensitiveKey>* names;     // 0x08
		core::Name<core::CaseSensitiveKey>* namesEnd;  // 0x0C
	};

	// The names of the collider types the properties refer to (0x1127CAD0; name guess)
	extern ColliderTypeNames* gColliderTypeNames;

	// The entry registered under that name, or null (0x10653900)
	IntersectionPropertiesEntry* FindIntersectionPropertyByName(const core::Name<core::CaseSensitiveKey>& name);
	// Its index, or 0xFFFF (0x10653950)
	unsigned short FindIntersectionPropertyIndex(const core::Name<core::CaseSensitiveKey>& name);
	// The index of a collider type name (0x106539A0) and the name of an index (0x106539F0)
	bool FindColliderTypeIndex(const core::Name<core::CaseSensitiveKey>& name, unsigned int* index);
	bool GetColliderTypeName(unsigned int index, core::Name<core::CaseSensitiveKey>* name);
	// Registers the properties under the name, replacing the ones already there; the entry's index (0x10653B50)
	unsigned int RegisterIntersectionProperties(const core::Name<core::CaseSensitiveKey>& name,
		const IntersectionProperties& properties);
	// Drops the registry (0x10653B00) and builds it with room for count entries and the default one (0x10653FA0,
	// 0x10653F50)
	void ClearIntersectionPropertyRegistry();
	void CreateIntersectionPropertyRegistry(unsigned int count);
	void RegisterDefaultIntersectionProperties();

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
		// How many objects the list holds
		unsigned int Count() const
		{
			return end - begin;
		}
		// The object with that index
		void* Get(unsigned int index) const
		{
			return begin[index];
		}

		void** begin;
		void** end;
	};

	// The registry behind Context+0x0C: the objects by the identity they carry (name guess). Its members live in
	// another unit; this unit only calls them. The first six words are the same run pair as the hash table it keeps
	// at +0x18 (two counts and a run of 16-bit slot values each), and the count at +0x44 is the registry's own.
	class ObjectRegistry
	{
	public:
		// Zeroes the six words and the table (0x10658CC0; the count at +0x44 is left alone)
		ObjectRegistry();
		// Back to the empty state: the three runs are filled with 0xFF and the table reset (0x10658C70)
		void Reset();
		// Gives the runs and the table back (0x10686410; name guess)
		void Release();
		// 0x10686980
		void Remove(PhysicsObject* object);
		// Empties the registry's tables once the detection starts (0x10686870; name guess)
		void Unknown10686870();
		// Files an object under a slot (0x10686790) and takes a slot out again (0x106867F0; names are guesses)
		void Unknown10686790(unsigned int key, unsigned short slot);
		void Unknown106867F0(unsigned short slot);
		// The second takes the slot from a reference (0x106563B0)
		void RemoveRef(const RegistryRef* reference);

		unsigned short* next;        // 0x00
		int nextCount;               // 0x04
		unsigned short* buckets;     // 0x08
		int bucketCount;             // 0x0C
		unsigned short* slotBuckets; // 0x10
		int slotBucketCount;         // 0x14
		PointerHashTable table;      // 0x18
		int unknown44;               // 0x44
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
		// Empties the tracker's own tables and their counters (0x10688470; name guess)
		void ResetTables();
		// 0x10687C10
		void Track(ObjectList* objects);
		// 0x10687CA0
		void Untrack(ObjectList* objects);
		// Gives the tracker's tables back (0x10688950, its destructor)
		~PlacementTracker();
		// The deleting form of the destructor (0x106564A0)
		void* DestroyAndFree(unsigned int flags);
		// The simulation step: moves and solves the objects of every list against the body (0x10689EE0; name guess)
		void Advance(WorldBody* body, void* data, void* a, float dt, void* worldData, void* registry, void* b);

		math::Vector position; // 0x00
	};

	// What the collision detection is handed to work on: the counters its "Collisions" statistic reports (name guess)
	struct DetectionData
	{
		int unknown0;
		int first;  // 0x04
		int second; // 0x08
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
		// The destructor's slot: destroys the world and, with bit 0 set, frees it
		virtual void Unknown00(int flags);
		virtual void Unknown04();
		virtual void Unknown08();
		virtual void Unknown0C();
		// 0x10
		virtual bool Overlaps(void* object, void* world);
		// 0x14
		virtual bool Contains(void* object, void* world);
		virtual void Unknown18(PhysicsObject* object);
		virtual void Unknown1C();
		virtual void Unknown20();
		virtual void Unknown24();
		virtual void Unknown28(void* work, void* detector, void* scratch, void* recordPool, void* midPhase);
		virtual void Unknown2C();
		// 0x30
		virtual void QueryShape(void* a, void* b, void* c, void* world, void* d);
		// 0x34
		virtual void QueryShapeOther(void* a, void* b, void* c, void* world, void* d);
		// 0x38: the segment query the context's CastRay runs, the hits appended to hits (name guess)
		virtual bool QueryRay(const void* query, void* hits, void* world, unsigned int flags);
		// 0x3C
		virtual void QueryPair(void* a, void* b, void* world, unsigned int flags);
		// 0x40
		virtual void QueryBody(PhysicsBody* object, void* world, unsigned int flag);
		// 0x44: the same shape query as QueryBodyShape, but against a body and with the hit buffer emptied first
		// (the context's 0x10659420; name guess)
		virtual void QueryBodyShapeHits(void* object, void* hits, void* world, void* a);
		// 0x48
		virtual void QueryBodyShape(void* a, void* b, void* world, void* c);
		// 0x4C
		virtual void QueryBodyRay(void* a, void* world, void* b);
		// 0x50
		virtual void QueryShape2(void* a, void* b, void* c, void* world, void* d);
		// 0x54
		virtual void QueryShape3(void* a, void* b, void* c, void* world, void* d);
	};

	// The collision library's own small containers, as far as this unit emits their accessors. The library keeps
	// several runs of fixed-size records between two byte pointers and hands a few of its batches on through a run
	// of pointers; its headers define them, and the reconstruction does not call any of the accessors below yet, so
	// every type here is a stand-in named after the record size its accessor divides by and every member is a guess.
	// A unit that recovers the real containers should move these accessors onto them.

	// A run of 52-byte records (name guess)
	struct RecordList52
	{
		unsigned char* mBegin; // 0x00
		unsigned char* mEnd;   // 0x04

		int Count() const;
	};

	// A run of 168-byte records (name guess)
	struct RecordList168
	{
		unsigned char* mBegin; // 0x00
		unsigned char* mEnd;   // 0x04

		int Count() const;
	};

	// A run of 12-byte records (name guess)
	struct RecordList12
	{
		unsigned char* mBegin; // 0x00
		unsigned char* mEnd;   // 0x04

		int Count() const;
	};

	// A second run of 12-byte records (name guess)
	struct RecordList12Second
	{
		unsigned char* mBegin; // 0x00
		unsigned char* mEnd;   // 0x04

		int Count() const;
	};

	// A third run of 12-byte records (name guess)
	struct RecordList12Third
	{
		unsigned char* mBegin; // 0x00
		unsigned char* mEnd;   // 0x04

		int Count() const;
	};

	// A run of 44-byte records (name guess)
	struct RecordList44
	{
		unsigned char* mBegin; // 0x00
		unsigned char* mEnd;   // 0x04

		int Count() const;
	};

	// A run of pointers (name guess). The library hands records between batches through one of these, and every
	// instantiation it used in this unit is written here as its own stand-in, because nothing reconstructed so far
	// calls them: the grouping of the functions over these types and every member name is a guess.
	struct PointerList
	{
		void** Begin() const;
		void** End() const;
		// The pointer after the last one (name guess)
		int Count() const;
		void*& operator[](int index);
		// Drops both ends without releasing the storage (name guess)
		PointerList* Clear();

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct PointerListSecond
	{
		PointerListSecond();
		PointerListSecond(unsigned int unused);
		PointerListSecond(void** newBegin, void** newEnd);

		void** Begin() const;
		void** End() const;
		void SetBegin(void** value);
		void SetEnd(void** value);
		int Count() const;
		void*& operator[](int index);

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct PointerListThird
	{
		PointerListThird(unsigned int unused);

		int Count() const;
		void*& operator[](int index);
		void SetEnd(void** value);

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct PointerListFourth
	{
		PointerListFourth();
		PointerListFourth(unsigned int unused);

		void*& operator[](int index);

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct PointerListFifth
	{
		PointerListFifth();
		PointerListFifth(unsigned int unused);

		void*& operator[](int index);
		// The address offset bytes into the run (name guess)
		unsigned char* ByteAt(int offset);

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct PointerListSixth
	{
		PointerListSixth(void** newBegin, void** newEnd);

		void*& operator[](int index);

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct PointerListSeventh
	{
		PointerListSeventh(void** newBegin, void** newEnd);

		void*& operator[](int index);

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct PointerListEighth
	{
		PointerListEighth(void** newBegin, void** newEnd);

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct PointerListNinth
	{
		PointerListNinth(void** newBegin, void** newEnd);

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct Record32;

	// A pool of fixed slots handed out by an atomic counter: the slot array, how many slots it holds, and the
	// counter the acquirer bumps (name guess; the slot stride comes from the acquirer's shift)
	struct SlotPool
	{
		SlotPool();

		// Builds the slot array and the counter on the current heap; the allocator the library would pass is not
		// used by the body (0x10657500; name guess)
		void Init(unsigned int count, const ScratchStack& allocator);
		// Gives the slot array and the counter back to the heap (name guess)
		void Release(int unused);
		// Empties the counter (name guess)
		void Reset();
		// The counter's value, read atomically (name guess)
		int ReadCounter();
		// The counter itself (name guess)
		long* GetCounter();
		// The next free slot, or null once the pool is exhausted (name guess)
		void* Acquire();
		// Copies the record into the next free slot, false once the pool is exhausted (name guess)
		bool Add(const Record32& value);

		void* mSlots;   // 0x00
		int mCapacity;  // 0x04
		long* mCounter; // 0x08
	};

	// A second pool of the same shape (name guess)
	struct SlotPoolSecond
	{
		SlotPoolSecond();

		// Empties the counter (name guess)
		void Reset();
		// Copies the record into the next free slot, false once the pool is exhausted (name guess)
		bool Add(const Record32& value);

		void* mSlots;   // 0x00
		int mCapacity;  // 0x04
		long* mCounter; // 0x08
	};

	// A pool of 16-byte slots, otherwise the same shape as SlotPool (name guess)
	struct SlotPoolThird
	{
		SlotPoolThird();

		// Builds the slot array and the counter on the current heap (0x10657550; name guess)
		void Init(unsigned int count, const ScratchStack& allocator);
		// Gives the slot array and the counter back to the heap (name guess)
		void Release(int unused);
		// The next free slot, or null once the pool is exhausted (name guess)
		void* Acquire();

		unsigned char* mSlots; // 0x00
		int mCapacity;         // 0x04
		long* mCounter;        // 0x08
	};

	// A run of bytes whose storage comes from the scratch stack (name guess)
	struct ScratchBytes
	{
		// size bytes of raw storage, or an empty run when the stack is exhausted (name guess)
		bool Reserve(unsigned int size);

		unsigned char* mBegin;  // 0x00
		unsigned char* mEnd;    // 0x04
		ScratchStack allocator; // 0x08
	};

	// A second run of bytes over the scratch stack: this one refuses to reserve twice and fills what it takes with
	// the byte it is given (name guess)
	struct ScratchBytesSecond
	{
		// The same with the fill removed, the byte written being zero (name guess)
		bool Reserve(unsigned int size);
		// size bytes filled with the byte value points at; refuses when the run is already there (0x10658BE0)
		bool Reserve(unsigned int size, const char* value);

		unsigned char* mBegin;  // 0x00
		unsigned char* mEnd;    // 0x04
		ScratchStack allocator; // 0x08
	};

	// The runs of pointers the classes of this range hold but whose owners nothing gives away: the unit emits the
	// accessors of nine of them and they all have the same shape, so they are written here as nine stand-ins, one
	// per emitted copy (name guesses). `Clear` drops the run and `Release` gives its storage back.

	struct HeapRunFirst
	{
		void Clear();   // 0x10658A90
		void Release(); // 0x106594B0

		char* mBegin; // 0x00
		char* mEnd;   // 0x04
	};

	struct HeapRunSecond
	{
		void Clear();   // 0x10658B70
		void Release(); // 0x106594D0

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct HeapRunThird
	{
		void Clear();   // 0x10658B80
		void Release(); // 0x106594F0

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct HeapRunFourth
	{
		void Clear();   // 0x10658B90
		void Release(); // 0x10659510

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct HeapRunFifth
	{
		void Clear();   // 0x10658BA0
		void Release(); // 0x10659530

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct HeapRunSixth
	{
		void Clear();   // 0x10658BB0
		void Release(); // 0x10659550

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct HeapRunSeventh
	{
		void Clear();   // 0x10658BC0
		void Release(); // 0x10659570

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct HeapRunEighth
	{
		void Clear();   // 0x10658BD0
		void Release(); // 0x10659600

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct HeapRunNinth
	{
		void Clear();   // 0x10659590
		void Release(); // 0x10659620

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	// Three more runs whose storage the library allocated aligned (name guesses)
	struct AlignedRunFirst
	{
		void Release(); // 0x10658AA0

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct AlignedRunSecond
	{
		void Release(); // 0x10658AB0

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	struct AlignedRunThird
	{
		void Release(); // 0x10658AC0

		void** mBegin; // 0x00
		void** mEnd;   // 0x04
	};

	// The classes that hold three runs of the kind above; the unit emits their cleanup, once with the aligned frees
	// and once as the destructor the compiler makes of them (name guesses). The member names are the offsets.

	struct RunsFirst
	{
		void Finalize(); // 0x106595C0

		void* unknown0;  // 0x00
		void* unknown4;  // 0x04
		void* unknown8;  // 0x08
		void* unknownC;  // 0x0C
		void* unknown10; // 0x10
		void* unknown14; // 0x14
		void* unknown18; // 0x18
		void* unknown1C; // 0x1C
		void* unknown20; // 0x20
		void* unknown24; // 0x24
		void* unknown28; // 0x28
	};

	struct RunsSecond
	{
		void Finalize(); // 0x10659CD0

		void* unknown0;  // 0x00
		void* unknown4;  // 0x04
		void* unknown8;  // 0x08
		void* unknownC;  // 0x0C
		void* unknown10; // 0x10
		void* unknown14; // 0x14
		void* unknown18; // 0x18
		void* unknown1C; // 0x1C
		void* unknown20; // 0x20
		void* unknown24; // 0x24
		void* unknown28; // 0x28
	};

	struct RunsThird
	{
		void Finalize(); // 0x10659D10

		void* unknown0;  // 0x00
		void* unknown4;  // 0x04
		void* unknown8;  // 0x08
		void* unknownC;  // 0x0C
		void* unknown10; // 0x10
		void* unknown14; // 0x14
		void* unknown18; // 0x18
		void* unknown1C; // 0x1C
		void* unknown20; // 0x20
		void* unknown24; // 0x24
		void* unknown28; // 0x28
	};

	// The same over three runs the library allocated aligned, and the deleting form the compiler makes of a
	// destructor with a flag (name guesses)
	struct AlignedRuns
	{
		void Finalize();                          // 0x10658EC0
		AlignedRuns* FinalizeDeleting(unsigned int flag); // 0x10659640

		void* unknown0;  // 0x00
		void* unknown4;  // 0x04
		void* unknown8;  // 0x08
		void* unknownC;  // 0x0C
		void* unknown10; // 0x10
		void* unknown14; // 0x14
		void* unknown18; // 0x18
		void* unknown1C; // 0x1C
		void* unknown20; // 0x20
		void* unknown24; // 0x24
		void* unknown28; // 0x28
	};

	// A class whose first member is the library's statistics log: its own Add forwards to it (name guess)
	struct StatLogSecond : StatLog
	{
		bool Add(const StatEntry& entry); // 0x10658AD0
	};

	// A class that keeps the log behind a head of its own (name guess)
	struct StatLogThird
	{
		void Add(const StatEntry& entry); // 0x10658C40

		unsigned char unknown0[0xC];
		StatLog mLog; // 0x0C
	};

	// A 32-byte record of the profiler pools: the tick counts around the work, the two words between them (the second
	// one is always -1), two bytes the record carries, its name and its kind (name guesses).
	struct Record32
	{
		unsigned int start;    // 0x00
		unsigned int end;      // 0x04
		int unknown8;          // 0x08
		int unknownC;          // 0x0C
		bool unknown10;        // 0x10
		bool unknown11;        // 0x11
		unsigned short unknown12; // 0x12
		const char* name;      // 0x14
		unsigned short kind;   // 0x18
		unsigned char unknown1A[0x20 - 0x1A]; // 0x1A
	};

	// A record built on the stack: the engine aligns the frame of the methods that build one to 16 bytes, while the
	// records it keeps in arrays (Record40) are packed at 0x28 bytes
	__declspec(align(16)) struct AlignedRecord32 : Record32
	{
	};

	// The pair of words that identifies a record (name guess)
	struct Pair8
	{
		int unknown0;
		int unknown4;
	};

	// A profiling record plus the pair that identifies it (name guess; the element ScratchStack allocates
	// arrays of, 0x28 bytes)
	struct Record40
	{
		Record40(const Record32& record, const Pair8& id);

		Record32 mRecord; // 0x00
		Pair8 mId;        // 0x20
	};

	// The same record over a second payload the unit emits a copy of (name guess)
	struct Record40Second
	{
		Record40Second(const Record32& record, const Pair8& id);

		Record32 mRecord; // 0x00
		Pair8 mId;        // 0x20
	};

	// Two more payloads this unit emits the same constructor for (name guesses)
	struct Record40Third
	{
		Record40Third(const Record32& record, const Pair8& id);

		Record32 mRecord; // 0x00
		Pair8 mId;        // 0x20
	};

	struct Record40Fourth
	{
		Record40Fourth(const Record32& record, const Pair8& id);

		Record32 mRecord; // 0x00
		Pair8 mId;        // 0x20
	};

	// Writes the byte the value points at through the target pointer, when the target is not null (name guess)
	void StoreByte(char* target, const char* value);

	// The two halves of a 16-bit grid with their element counts (name guess)
	struct ShortPair
	{
		short* Begin() const;
		short* At(int index);
		// The first half's size in bytes (name guess)
		int ByteSize() const;
		// Fills both halves with 0xFF (name guess)
		void Fill();

		short* mFirst;    // 0x00
		int mFirstCount;  // 0x04
		short* mSecond;   // 0x08
		int mSecondCount; // 0x0C
	};

	// A run of 32-bit values (name guess)
	struct IntArray
	{
		int* At(int index);

		int* mBegin; // 0x00
		int* mEnd;   // 0x04
	};

	// Writes the word the value points at through the target pointer, when the target is not null (name guesses)
	void StoreId(int* target, const int* value);
	void StoreIdSecond(int* target, const int* value);

	// A 124-byte box a query walks (name guess; the element ScratchStack allocates arrays of)
	struct Box124
	{
		int unknown0[31];
	};

	// The head the library's jobs hang at 0x18 of themselves (name guess)
	struct Head18
	{
		unsigned char unknown0[0x18];
		unsigned char head; // 0x18

		unsigned char* GetHead();
	};

	// The empty members the library's classes declare; the engine's copies are bare returns, and which class each
	// of them belongs to cannot be told from the code (name guess)
	struct EmptyMembers
	{
		void First();
		void Second();
		void Third();
		void Fourth();
		void Fifth();
		void Sixth();
		void Seventh();
		void Eighth();
		void Ninth();
		void Tenth();
		void Eleventh();
		void Twelfth();
		void Thirteenth();
		void Fourteenth();
		void Fifteenth();
		void Sixteenth();
		void Seventeenth();
		void Eighteenth();
		void Nineteenth();
		void Twentieth();
		void TwentyFirst();
		void TwentySecond();
		void TwentyThird();
		void TwentyFourth();
		void TwentyFifth();
		void TwentySixth();
		void TwentySeventh();
		void TwentyEighth();
		void TwentyNinth();
		void Thirtieth();
	};

	// A short and two words (name guess)
	struct ShortTriple
	{
		ShortTriple(unsigned short first, int second, int third);

		unsigned short mFirst; // 0x00
		int mSecond;           // 0x04
		int mThird;            // 0x08
	};

	// The two pools the collision detection takes its work from: a 32-byte-slot pool and a 16-byte-slot one, each
	// with its own counter (name guess; the layout is what the unit's Init, its accessors and WakeObject read)
	struct WorkPools
	{
		WorkPools();

		// Both slot arrays and their counters, from the current heap (0x10657900; name guess)
		void Init(unsigned int firstCount, unsigned int secondCount);
		// Empties both counters (name guess)
		void ResetCounters();
		// Gives both pairs back to the heap (name guess)
		void ReleaseAll();
		// The slot of the second pool (0x106578D0; name guess)
		void* Slot(unsigned short index) const;

		void** mFirstSlots;   // 0x00
		int mFirstCount;      // 0x04
		long* mFirstCounter;  // 0x08
		void** mSecondSlots;  // 0x0C
		int mSecondCount;     // 0x10
		long* mSecondCounter; // 0x14
	};

	// A block of four words the unit zeroes on construction (name guess)
	struct WordBlock4
	{
		WordBlock4();

		void* unknown0;
		void* unknown4;
		void* unknown8;
		void* unknownC;
	};

	// A growable run of pointers a batch fills (name guess; the shape container::ArrayDynamicStatic has, without
	// its allocator)
	struct PointerRun
	{
		// Appends value when there is room, false when the run is full (name guess)
		bool PushBack(void* const& value);
		// The first entry equal to value, or the end of the run (name guess)
		void** Find(void* const& value);

		void** mBegin;    // 0x00
		void** mEnd;      // 0x04
		void** mCapacity; // 0x08
	};

	// A block of three words with an array of pointers behind it (name guess)
	struct IndexedBlock
	{
		unsigned char unknown0[0x18];
		void** mItems; // 0x18

		// The entry the index picks (name guess)
		void* Get(unsigned short index) const;
	};

	// More blocks of three words the unit zeroes on construction, and which nothing reconstructed calls yet
	// (name guesses)
	struct TripleBlock
	{
		TripleBlock();

		void* unknown0;
		void* unknown4;
		void* unknown8;
	};

	struct TripleBlockSecond
	{
		TripleBlockSecond();

		void* unknown0;
		void* unknown4;
		void* unknown8;
	};

	struct TripleBlockThird
	{
		TripleBlockThird();

		void* unknown0;
		void* unknown4;
		void* unknown8;
	};

	struct TripleBlockFourth
	{
		TripleBlockFourth();

		void* unknown0;
		void* unknown4;
		void* unknown8;
	};

	struct TripleBlockFifth
	{
		TripleBlockFifth();

		void* unknown0;
		void* unknown4;
		void* unknown8;
	};

	// A second run of pointers a batch fills (name guess)
	struct PointerRunSecond
	{
		// Appends value when there is room, false when the run is full (name guess)
		bool PushBack(void* const& value);

		void** mBegin;    // 0x00
		void** mEnd;      // 0x04
		void** mCapacity; // 0x08
	};

	// A run of 16-bit values behind a head (name guess)
	struct ShortValues
	{
		// The value the index picks (name guess)
		unsigned short Get(int index) const;

		unsigned char unknown0[8];
		unsigned short* mValues; // 0x08
	};

	// A run of 16-bit values (name guess)
	struct ShortValuesSecond
	{
		// The value the index picks (name guess)
		unsigned short Get(unsigned short index) const;

		unsigned short* mValues; // 0x00
	};

	// Three runs of 16-bit values with their counts (name guess)
	struct ShortRun
	{
		// Fills all three with 0xFF, the third with -1 (name guess)
		void Fill();

		short* mFirst;    // 0x00
		int mFirstCount;  // 0x04
		short* mSecond;   // 0x08
		int mSecondCount; // 0x0C
		short* mThird;    // 0x10
		int mThirdCount;  // 0x14
	};

	// Where a walk over a batch's records starts: the current value, the batch and its end (name guess)
	struct RecordWalk
	{
		unsigned short value; // 0x00
		unsigned char unknown2[2];
		void* owner;          // 0x04
		void* limit;          // 0x08
	};

	// The head of a batch whose records a walk runs over (name guess)
	struct WalkableBatch
	{
		unsigned char unknown0[8];
		unsigned short* mRecords; // 0x08

		// Starts a walk over this batch's records (name guess)
		void BeginWalk(RecordWalk* walk) const;
	};

	// A slot of a table the index picks, 0xFFFF meaning "none" (name guess)
	struct IndexedTable
	{
		void** items; // 0x00
	};

	struct IndexedHandle
	{
		unsigned short index; // 0x00
		unsigned char unknown2[0x8 - 2];
		IndexedTable* table;  // 0x08

		// The entry the index picks, or null when there is none (name guess)
		void* Get() const;
	};

	// A slot with the index of its successor behind it (name guess)
	struct ChainedIndex
	{
		unsigned short index; // 0x00
		unsigned char unknown2[2];
		unsigned short** items; // 0x04

		// Steps to the successor (name guess)
		void Next();
	};

	// A head whose word at +8 points at a run of 16-bit values (name guess)
	struct ShortHead
	{
		unsigned char unknown0[8];
		unsigned short* values; // 0x08
	};

	// A slot that holds its owner first and its index behind it (name guess)
	struct IndexedSlotThird
	{
		// Writes the slot's value and its owner into the walk (0x10658C50)
		void Get(RecordWalk* walk) const;

		ShortHead* mOwner;     // 0x00
		unsigned short mIndex; // 0x04
	};

	// A head whose first word points at a run of 16-bit values (name guess)
	struct ShortHeadSecond
	{
		unsigned short* values; // 0x00
	};

	// A slot of a head's run, 0xFFFF meaning "none" (name guess)
	struct IndexedSlot
	{
		unsigned short index; // 0x00
		unsigned char unknown2[2];
		ShortHead* owner;     // 0x04

		// Takes the slot of newIndex in newOwner's run (name guess)
		void Set(ShortHead* newOwner, unsigned short newIndex);
	};

	// The same slot over a head whose run is its first word (name guess)
	struct IndexedSlotSecond
	{
		unsigned short index; // 0x00
		unsigned char unknown2[2];
		ShortHeadSecond* owner; // 0x04

		// Writes the slot's value and its owner into the walk (name guess)
		void Get(RecordWalk* walk) const;
	};

	// A second slot type whose table keeps its entries behind +0x30 (name guess)
	struct IndexedTableSecond
	{
		unsigned char unknown0[0x30];
		void** items; // 0x30
	};

	struct IndexedHandleSecond
	{
		unsigned short index; // 0x00
		unsigned char unknown2[2];
		IndexedTableSecond* table; // 0x04

		// The entry the index picks, or null when there is none (name guess)
		void* Get() const;
	};

	// Copies the byte value points at count times (name guess)
	void FillByteRun(char* target, unsigned int count, const char* value);

	// Blocks of words the unit zeroes on construction, one constructor each (name guesses)
	struct Block6
	{
		Block6();

		void* unknown0;
		void* unknown4;
		void* unknown8;
		void* unknownC;
		void* unknown10;
		void* unknown14;
	};

	struct Block8
	{
		Block8();

		void* unknown0;
		void* unknown4;
		void* unknown8;
		void* unknownC;
		void* unknown10;
		void* unknown14;
		void* unknown18;
		void* unknown1C;
	};

	struct Block8Second
	{
		Block8Second();

		void* unknown0;
		void* unknown4;
		void* unknown8;
		void* unknownC;
		void* unknown10;
		void* unknown14;
		void* unknown18;
		void* unknown1C;
	};

	struct Block11
	{
		Block11();

		void* unknown0;
		void* unknown4;
		void* unknown8;
		void* unknownC;
		void* unknown10;
		void* unknown14;
		void* unknown18;
		void* unknown1C;
		void* unknown20;
		void* unknown24;
		void* unknown28;
	};

	struct Block11Second
	{
		Block11Second();

		void* unknown0;
		void* unknown4;
		void* unknown8;
		void* unknownC;
		void* unknown10;
		void* unknown14;
		void* unknown18;
		void* unknown1C;
		void* unknown20;
		void* unknown24;
		void* unknown28;
	};

	struct Block11Third
	{
		Block11Third();

		void* unknown0;
		void* unknown4;
		void* unknown8;
		void* unknownC;
		void* unknown10;
		void* unknown14;
		void* unknown18;
		void* unknown1C;
		void* unknown20;
		void* unknown24;
		void* unknown28;
	};

	struct Block11Fourth
	{
		Block11Fourth();

		void* unknown0;
		void* unknown4;
		void* unknown8;
		void* unknownC;
		void* unknown10;
		void* unknown14;
		void* unknown18;
		void* unknown1C;
		void* unknown20;
		void* unknown24;
		void* unknown28;
	};

	// A block whose first word its constructor leaves alone (name guess)
	struct Block7
	{
		Block7();

		void* unknown0;
		void* unknown4;
		void* unknown8;
		void* unknownC;
		void* unknown10;
		void* unknown14;
		void* unknown18;
	};

	struct Block3
	{
		Block3();

		void* unknown0;
		void* unknown4;
		void* unknown8;
	};

	struct Block3Second
	{
		Block3Second();

		void* unknown0;
		void* unknown4;
		void* unknown8;
	};

	struct Block3Third
	{
		Block3Third();

		void* unknown0;
		void* unknown4;
		void* unknown8;
	};

	// A 128-byte box and a 1024-byte one the scratch stack allocates single instances of (name guesses)
	struct Box128
	{
		int unknown0[32];
	};

	struct Box400
	{
		int unknown0[256];
	};

	// Zeroes the two counters of the pair behind +0x114 (name guess)
	struct CounterPair
	{
		unsigned char unknown0[0x114];
		long* mFirstCounter;  // 0x114
		unsigned char unknown118[0x120 - 0x118];
		long* mSecondCounter; // 0x120

		void ResetCounters(int unused, int unusedSecond);
	};

	// An array whose storage comes from the scratch stack: begin / end / capacity, then the (empty) allocator the
	// library allocates through (name guess; the same shape container::ArrayDynamicStatic has, with the allocator
	// as an object instead of a static)
	struct ScratchArray
	{
		ScratchArray* Self();
		// count pointers of raw storage, or an empty array when the stack is exhausted (name guess)
		bool Allocate(unsigned int count);
		// The same without a result (name guess)
		void Init(unsigned int count);

		void** mBegin;          // 0x00
		void** mEnd;            // 0x04
		void** mCapacity;       // 0x08
		ScratchStack allocator; // 0x0C
	};

	// The one-byte member after the array (name guess)
	struct EmptyTail
	{
		void Empty();
	};

	// The context's internal work lists: the collision pairs it is processing (Context+0x24, 48-byte entries),
	// the constraints its solver works on (Context+0x58, 168-byte entries) and a third one (Context+0x8C). Their
	// members live in the collision library's own units; this unit only calls them, so nothing but the calls is
	// declared here (every name and the sizes are guesses).
	// The collision detector behind Context+0x108: the object the whole detection runs in. It opens its own scratch
	// level (it is a ScratchStackFrame itself) and, while it runs, holds itself in mCollisionDetectorInternal, which
	// is what the asserts the library guards the detection with test. The class name is a guess; the members the
	// asserts name are mCollisionDetectorInternal and the object the detection works on.
	class CollisionDetector : public ScratchStackFrame
	{
	public:
		// Gives the scratch buffer and the event back and closes the level (0x10658610)
		~CollisionDetector();
		// Starts the detection over the context's objects and blocks on the gate (0x106596F0; name guess)
		CollisionDetector* Run(Context* context, void* data);
		// Points the detector at the running detection and hands the work to Run (0x10659EE0; name guess)
		void Begin(Context* context, void* data);
		// Ends the detection the assertion checks for (0x10659690; name guess)
		void End();
		// Clears the detector pointer and the object (0x10656580)
		CollisionDetector* Clear();
		// The object the detector works on; asserts that the detection is running (0x10656590)
		void* GetObject();
		// The gate the detection waits on (0x106565E0)
		void* GetEvent();
		// As GetEvent, through the detector pointer (0x10657C40)
		void* GetEventChecked();
		// The deleting form the compiler makes of the destructor (0x10658F70)
		CollisionDetector* Destroy(unsigned int flag);

		void* event;                      // 0x08 (the gate the detection waits on)
		NarrowPhaseBatcher* narrowPhase;  // 0x0C (the in-flight narrow phase work)
		MidPhaseBatcher* midPhase;        // 0x10 (the record its batches are reported into)
		void* unknown14;                  // 0x14
		SlotPool* recordPool;             // 0x18 (the context's profiler pool)
		Context* context;                 // 0x1C
		void* data;                       // 0x20
		CollisionDetector* mCollisionDetectorInternal; // 0x24
		void* unknown28;                               // 0x28
	};

	// The three work lists the context queues for the detection: each holds a run of its own records and, behind it,
	// a run of the small records the solver hands on (the sizes are what the statistics getter divides by; the
	// member names are guesses).
	class CollisionBatch
	{
	public:
		// Runs every entry of the list against the world (0x1068B190)
		void Update(World* world, void* worldData);
		// Appends an entry; mode is 4, 8 or 0x10 (0x1068B340)
		void* Add(void* first, void* second, int mode);

		unsigned char* records;          // 0x00 (0x30-byte entries)
		unsigned char* recordsEnd;       // 0x04
		int unknown8;                    // 0x08
		int unknownC;                    // 0x0C
		unsigned char* slots;            // 0x10 (0xC-byte entries)
		unsigned char* slotsEnd;         // 0x14
		int unknown18;                   // 0x18
		int unknown1C;                   // 0x1C
		int unknown20;                   // 0x20
		unsigned char* recordsSecond;    // 0x24 (the second run of 0x30-byte entries; name guess)
		unsigned char* recordsSecondEnd; // 0x28
		int unknown2C;                   // 0x2C
		int unknown30;                   // 0x30
	};

	class ConstraintBatch
	{
	public:
		// Runs every entry of the list against the world (0x1068DE00)
		void Update(World* world, void* worldData);
		// Appends an entry; mode is 0, 1 or 2 (0x1068DD60)
		void* Add(void* first, void* second, int mode);

		unsigned char* records;          // 0x00 (0xA8-byte entries)
		unsigned char* recordsEnd;       // 0x04
		int unknown8;                    // 0x08
		int unknownC;                    // 0x0C
		unsigned char* slots;            // 0x10 (0xC-byte entries)
		unsigned char* slotsEnd;         // 0x14
		int unknown18;                   // 0x18
		int unknown1C;                   // 0x1C
		int unknown20;                   // 0x20
		unsigned char* recordsSecond;    // 0x24 (the second run, 0x34-byte entries; name guess)
		unsigned char* recordsSecondEnd; // 0x28
		int unknown2C;                   // 0x2C
		int unknown30;                   // 0x30
	};

	class QueryBatch
	{
	public:
		// Runs every entry of the list against the world (0x10671A60)
		void Update(World* world, void* worldData);
		// Appends an entry (0x10671580)
		void* Add(void* a, void* b, void* c, void* d);

		unsigned char* records;     // 0x00 (0x2C-byte entries)
		unsigned char* recordsEnd;  // 0x04
		int unknown8;               // 0x08
		int unknownC;               // 0x0C
		unsigned char* slots;       // 0x10 (0xC-byte entries)
		unsigned char* slotsEnd;    // 0x14
		int unknown18;              // 0x18
		int unknown1C;              // 0x1C
		void** unknown20;           // 0x20 (a run of pointers; name guess)
		void** unknown24;           // 0x24
		int unknown28;              // 0x28
		int unknown2C;              // 0x2C
		int unknown30;              // 0x30
		int unknown34;              // 0x34
	};

	class Context
	{
	public:
		// The hits along the query's segment, appended to hits after clearing it; false when there are none
		// (0x106593A0)
		bool CastRay(const RayQuery& query, RayHitArray* hits);

		// The solver's iteration counts (0x10656E70; name guess)
		void SetSolverIterations(int a, int b);
		// Sorts the bodies of a batch's pairs into the static and the movable list, each body once; the context is not
		// used (0x106586E0; name guess)
		void CollectBodies(const HandlePairRun* pairs, const BodyPairRun* records, PointerRun* staticBodies,
			PointerRun* movableBodies);
		// The area at 0x10C (0x106562E0; name guess)
		SlotPool* GetRecordPool();
		// Hands a sleeping object on to the world (0x106564C0; name guess)
		void Unknown106564C0(PhysicsObject* object);

		// Everything from the registry on starts at zero except the world, the tracker and a few words (0x10658D00)
		Context();
		// Puts every object the detector holds to sleep, then empties the detector and the tracker's and the
		// registry's tables (0x10658F00; name guess)
		void ClearObjects();
		// Takes the context apart: the world, the tracker, the registry, the detectors and the batches' blocks
		// (0x10659D50; name guess)
		void Destroy();

		// The heads and records of the two tables the detection's island walk runs over (0x10657F20 / 0x10657FA0;
		// names are guesses)
		DetectorTable* GetIslandTable(DetectorTable* out);
		DetectorTable* GetAwakeTable(DetectorTable* out);
		// The counters the statistics display shows: the object counts, the batches' fill and the detector's own
		// (0x10657D70; name guess)
		void GetStatistics(int* out);

		// Starts the detection over data: the detector opens its gate and the caller checks it did (0x10659F40)
		void BeginCollision(void* data);
		// Whether every active collision object of the body is touched by a pair of the island table, true for a body
		// that does not move or has a single object (0x106588B0; name guess)
		bool IsBodyConnected(ObjectHandle handle);
		// The detection's islands, over the objects the object list holds, out of the scratch buffer (0x106599C0;
		// name guess)
		void RunIslands(DetectionData* data, StackAllocator* allocator);
		// Ends the detection and, unless the world is torn down, runs the islands and reports what it counted
		// (0x10659F70; name guess)
		void Collide();
		// The same shape query as QueryObjectShape, with the hits emptied first (0x10659420; name guess)
		void QueryObjectShapeHits(void* object, RayHitArray* hits, void* a);

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
		// Wakes the object of the handle: back into the detector, its collision objects stamped and both lists
		// rebuilt (0x10657A50; name guess)
		void WakeObject(ObjectHandle handle);
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
		// Recomputes the bounds of the movable list's objects (0x10658430)
		void RefreshMovableObjects();
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
		// What the statistics getter reports next to the detector's own counters (the four lists it counts are the
		// four runs above; every name here is a guess)
		int unknownC8;   // 0xC8
		int unknownCC;   // 0xCC
		int unknownD0;   // 0xD0
		int unknownD4;   // 0xD4
		union
		{
			bool unknownD8;  // 0xD8
			int unknownD8Word;
		};
		int unknownDC;   // 0xDC
		int unknownE0;   // 0xE0
		int unknownE4;   // 0xE4
		int unknownE8;   // 0xE8
		int unknownEC;   // 0xEC
		int unknownF0;   // 0xF0
		int unknownF4;   // 0xF4
		int unknownF8;   // 0xF8
		int unknownFC;   // 0xFC
		int unknown100;  // 0x100
		int unknown104;  // 0x104
		CollisionDetector* detector; // 0x108
		SlotPool recordPool;         // 0x10C (the profiler pool the record's SlotPool methods use)
		StatLog statLog;             // 0x118
		int unknown124[19];          // 0x124
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
