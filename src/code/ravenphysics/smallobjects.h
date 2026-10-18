// The small classes and accessors of the unit linked just before ravenphysics/src/context.cpp (0x10656020 -
// 0x106564C0). The unit carries no assert of its own, so nothing in the image names its source file, and the engine's
// output names no owner for most of its functions (a bare accessor, a three-word constructor). Every class here is a
// stand-in named after what its functions do and every member is a guess; a unit that recovers the real classes should
// move the functions onto them.
#ifndef RAVENPHYSICS_SMALLOBJECTS_H
#define RAVENPHYSICS_SMALLOBJECTS_H

namespace ravenphysics
{
	class CollisionVolume;
	class PhysicsObject;

	// A block that ends in a 16-byte area (0x10656020)
	struct Layout20
	{
		// The address of the area
		unsigned char* GetTail();

		unsigned char unknown0[0x20];
		unsigned char tail[16];
	};

	// Builds the physics object of a collision volume, takes a reference to it and hands back its id (0x10656030;
	// the creation behind it is 0x10661140, another unit)
	void CreateObjectHandle(unsigned int* id, CollisionVolume* volume, int flag, float size);
	PhysicsObject* CreatePhysicsObject(CollisionVolume* volume, int flag, float size);

	// An interlocked counter (0x106560D0 / 0x106560E0)
	struct AtomicCounter
	{
		long Increment();
		long Decrement();

		volatile long value;
	};

	// A callback that ignores its argument (0x10656100)
	struct IgnoringHandler
	{
		void Handle(int unused);
	};

	// A block whose byte at 0x18 starts cleared (0x10656110)
	struct Flag18Holder
	{
		Flag18Holder();

		unsigned char unknown0[0x18];
		bool flag;
	};

	// Gives a block back to the heap (0x10656120)
	struct BlockReleaser
	{
		void FreeBlock(void* block);
	};

	// The profiler's stopwatch (0x106561F0 - 0x10656260): the low word of the tick count or of the microseconds at
	// the start and at the end
	struct ProfileTimer
	{
		ProfileTimer();
		// 0x10656210: remembers what it is timing and starts
		void Start(int newTag, int newCount, unsigned short newSlot, char newKind, bool newTicks);
		// 0x10656260: stops
		void Stop();

		unsigned int start;           // 0x00
		unsigned int stop;            // 0x04
		int count;                    // 0x08
		unsigned char unknownC[4];
		unsigned char kind;           // 0x10
		bool ticks;                   // 0x11
		unsigned char unknown12[2];
		int tag;                      // 0x14
		unsigned short slot;          // 0x18
	};

	// Four words (0x10656280)
	struct FourWords
	{
		void Set(unsigned int newFirst, unsigned int newSecond, unsigned int newThird);

		unsigned int first;
		unsigned int second;
		unsigned int unknown8;
		unsigned int third;
	};

	// A block of the heap, 128 byte aligned, and its release (0x106562A0 / 0x106562C0)
	void* AllocateAligned128(unsigned int size);
	void FreeAlignedBlock(void* block);

	// A table of words behind a header of 16 bytes (0x106562D0)
	struct IntTable
	{
		int Get(int index) const;

		unsigned char unknown0[0x10];
		int items[1];
	};

	// An object with a state word (0x106562F0 - 0x10656320)
	struct StateHolder
	{
		struct Link
		{
			unsigned char unknown0[0xC];
			int member;
		};

		int GetMember() const;
		void SetUnknown4C(int value);
		int GetFlag0() const;
		bool IsReady() const;

		unsigned char unknown0[0xC];
		int member0C;
		unsigned char unknown10[0x4C - 0x10];
		int unknown4C;
		unsigned int flags;           // 0x50
		unsigned char unknown54[0x60 - 0x54];
		Link* link;                   // 0x60
	};

	class ObjectRegistry;

	// A registry and the slot an object was filed under (0x10656370 - 0x106563B0)
	struct RegistryRef
	{
		// Files an object under the slot (0x10656370)
		void Add(unsigned int key);
		// Whether two references name the same slot (0x10656390)
		bool operator==(const RegistryRef& other) const;

		ObjectRegistry* registry;     // 0x00
		unsigned short slot;          // 0x04
	};

	// The limits a context is made with (0x106563D0 / 0x10656430; name guess)
	struct ContextLimits
	{
		// The engine's defaults
		ContextLimits();
		ContextLimits(const ContextLimits& other);

		int unknown0;
		int unknown4;
		int unknown8;
		int unknownC;
		bool unknown10;
		int unknown14;
		float unknown18;
		float gravity;                // 0x1C
		float unknown20;
		int unknown24;
		int unknown28;
		int unknown2C;
		int unknown30;
		int unknown34;
		int unknown38;
		int unknown3C;
	};
}

#endif
