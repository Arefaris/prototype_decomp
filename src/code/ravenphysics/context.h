// The parts of the physics library (ravenphysics, assert path code/ravenphysics/src/context.cpp) that the engine's
// units call: the query filter, the ray query and its hits, and the context behind the global 0x1128356C. Only the
// members those callers touch are named; everything here is a guess except the class names the RTTI gives.
#ifndef RAVENPHYSICS_CONTEXT_H
#define RAVENPHYSICS_CONTEXT_H

#include "code/content/loadinventory.h"
#include "code/math/vector.h"
#include "code/ravenphysics/broadphase/broadphasedetector.h"
#include "code/ravenphysics/common/stackallocator.h"

namespace ravenphysics
{
	class WorldBody;
	class PhysicsObject;
	class ObjectTable;

	// One entry of the physics handle table: the object and the generation its handle carries (name guess)
	struct PhysicsObjectEntry
	{
		PhysicsObject* object; // 0x00
		int generation;        // 0x04
	};

	// The table the physics handles index into (0x1127CAC0): the entries and how many of them there are (the name
	// and the layout are guesses; this unit only reads it)
	class PhysicsObjectTable
	{
	public:
		unsigned char unknown0[0xC];
		PhysicsObjectEntry* entries; // 0x0C
		unsigned char unknown10[0x14 - 0x10];
		unsigned short capacity;     // 0x14
	};

	// The physics handle table (0x1127CAC0)
	extern PhysicsObjectTable* gObjectTable;

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

	// A 32-byte profiling record (name guess)
	struct Record32
	{
		int unknown0[8];
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
