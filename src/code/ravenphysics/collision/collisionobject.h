// ravenphysics collision objects and volumes (assert path code/ravenphysics/collision/src/collisionobject.cpp). Only the
// members the reconstructed code touches are named; the layout is partial and every name is a guess.
#ifndef RAVENPHYSICS_COLLISION_COLLISIONOBJECT_H
#define RAVENPHYSICS_COLLISION_COLLISIONOBJECT_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/name.h"
#include "code/math/capsule.h"
#include "code/math/matrix.h"
#include "code/math/sphere.h"
#include "code/math/symmetricmatrix.h"
#include "code/math/vector.h"
#include "code/ravenphysics/context.h"

namespace ravenphysics
{
	class CollisionObject;
	class CollisionShape;
	class ConvexMesh;
	class PhysicsObject;

	// The query filters a volume asks for, accumulated by the object it belongs to (meanings unknown)
	struct CollisionFilter
	{
		unsigned int unknown0;
		unsigned int unknown4;
	};

	// The head shared by all collision volume types; type indexes the narrow phase's dispatch tables
	struct CollisionVolume
	{
		unsigned char type;
		unsigned char swapped;
		unsigned char material;
		unsigned char unknown3;
		math::Vector boundsMin;
		math::Vector boundsMax;
		CollisionFilter filter;     // 0x1C
		unsigned char unknown24[0x60 - 0x24];

		// The end every volume subclass's destructor reaches: marks the volume destroyed (0x10663EB0, another
		// unit)
		~CollisionVolume()
		{
			MarkDestroyed();
		}

		// Recomputes the volume's world bounds from the object's transform; a switch over the type byte that runs
		// the volume's own per-type update (0x10665690, another unit)
		void UpdateBounds(CollisionObject* object);
		// Raises the volume against a query, answering whether it hit and writing the point and the distance
		// (0x10663FE0, another unit)
		bool CastVolume(const void* query, math::Vector* point, float* distance);
		// A copy of the volume of the same type (0x10665990, another unit)
		CollisionVolume* Clone();
		// Takes over the filter of a query and passes it on to a mesh volume's mesh (0x10664120, another unit; name
		// guess); the two functions below set or clear the bits of one word of it (0x10664140 / 0x10664170)
		void SetFilter(const CollisionFilter* newFilter);
		void SetFilterBits(unsigned int mask, bool set);
		void SetFilterBits2(unsigned int mask, bool set);

		// The per-type setters and bounds updates the object's Set*Volume methods call (0x10664BA0 / 0x10664C10,
		// 0x10665060 / 0x10665120, 0x10665790 / 0x106645D0, 0x10665510 / 0x106643E0, 0x10681DE0 / 0x10680AB0;
		// another unit, names are guesses)
		void SetCapsule(const math::Capsule& capsule);
		void UpdateCapsuleBounds(CollisionObject* object);
		void SetSphere(const math::Sphere& sphere);
		void UpdateSphereBounds(CollisionObject* object);
		void SetVolume2(const void* description);
		void UpdateBounds2(CollisionObject* object);
		void SetVolume4(const void* description);
		void UpdateBounds4(CollisionObject* object);
		void SetVolume6(const void* description);
		void UpdateBounds6(CollisionObject* object);
		// Hands the query setup to the volume (0x10665A90, another unit)
		void SetQuery(const void* query);
		// Writes the bounds and the type-specific part out (0x10664660, another unit)
		void Print();
		// Frees the volume's own array of faces and marks it destroyed (0x10681C40, another unit)
		void Destroy();
		// Gives up a type 6 volume's slot in the physics table and clears its mesh (0x10666640, another unit)
		void DestroyMesh();
		// The body of the destructor: writes the destroyed mark into the state byte (0x10663EB0, another unit)
		void MarkDestroyed();
		// Raises and lowers the state byte, the volume's destruction count (0x10663EC0 / 0x10663ED0, another unit)
		void Retain();
		void Release();
	};

	// A volume of type 3, and the face list a type 4 volume keeps at +0x60 (class and member names are guesses)
	class CollisionVolume3 : public CollisionVolume
	{
	public:
		// Gives every face of the volume a material (0x10654150, another unit)
		void SetMaterial(unsigned char material);
		// Frees the volume's own array of faces, then the base's mark (0x10681C40, another unit)
		~CollisionVolume3();
		// The destructor and, when bit 0 of the flags is set, the delete behind it (0x10654450)
		void* DestroyAndFree(unsigned int flags);
	};

	// A volume of type 4: the volume plus its face list (0x10654670 gives every face a material)
	struct CollisionVolume4 : CollisionVolume
	{
		CollisionVolume3 materials;    // 0x60
		// Destroys the face list and marks the volume destroyed (0x10654490)
		~CollisionVolume4();
		// The destructor and, when bit 0 of the flags is set, the delete behind it (0x10655B30)
		void* DestroyAndFree(unsigned int flags);
	};

	// One slot the geometry of a mesh volume refers to (its own unit names it)
	struct MeshSlot
	{
		unsigned int unknown0;
		unsigned int unknown4;
	};

	// A volume of type 6 (0x10666640; 0x130 bytes)
	struct CollisionVolume6 : CollisionVolume
	{
		unsigned char unknown60[0x110 - 0x60];
		MeshSlot* unknown110;      // 0x110
		unsigned char unknown114[0x130 - 0x114];
		~CollisionVolume6();
		// Whether the first slot of the mesh carries geometry (0x10654180)
		bool HasSlotGeometry() const;
		// The destructor and, when bit 0 of the flags is set, the delete behind it (0x10654430)
		void* DestroyAndFree(unsigned int flags);
	};

	// The entry of the physics handle table that names one object (the table hands out the pair of a slot index and
	// the serial the slot carries; the names are guesses). An untouched handle names no slot.
	struct CollisionHandle
	{
		CollisionHandle()
		{
			value = 0xffffffff;
		}

		union
		{
			unsigned int value;
			struct
			{
				unsigned short index;
				unsigned short serial;
			};
		};
	};

	// One slot of the physics handle table (0x1127CAC0): the object and the serial it is registered under
	struct CollisionHandleEntry
	{
		void* object;
		unsigned int serial;
	};

	// The free slots of the handle table: a stack of 16-bit slot indexes over a block of its own (name and members
	// are guesses). The methods are the unit's out-of-line copies (minimalcollisioninfo.cpp defines them inline)
	struct CollisionSlotStack
	{
		// Empty, no block (0x10653360)
		CollisionSlotStack();
		// Allocates room for count indexes from the current heap; the second argument is not used (0x10653370)
		void Create(unsigned int count, int unused);
		// Gives the block back (0x10653400); the argument is not used
		void Free(int unused);
		// Whether every slot is handed out (0x10653150)
		bool IsEmpty() const;
		// Forgets every index (0x10653160)
		void Clear();
		// Puts a slot index back on top (0x10653170)
		void Push(const unsigned short& index);
		// Takes the top slot index off the stack (0x10653190)
		unsigned short Pop();
		// The address of the top index (0x106531C0)
		unsigned short* Top();

		unsigned short* begin;
		unsigned int size;
		unsigned int capacity;
	};

	// The slots of the handle table (name and members are guesses)
	struct CollisionHandleEntries
	{
		// No block (0x106531A0)
		CollisionHandleEntries();
		// A block of the caller's (0x106531F0)
		CollisionHandleEntries(CollisionHandleEntry* newBegin, unsigned int newCount);
		// Allocates room for count slots from the current heap; the second argument is not used (0x106533A0)
		void Create(unsigned int count, int unused);
		// Gives the block back (0x10653430); the argument is not used
		void Free(int unused);

		CollisionHandleEntry* begin;
		unsigned int count;
	};

	// One serial per slot of the handle table (name and members are guesses)
	struct CollisionHandleSerials
	{
		// No block (0x106531D0)
		CollisionHandleSerials();
		// A block of the caller's (0x10653210)
		void Set(unsigned short* newBegin, unsigned int newCount);
		// Allocates room for count serials from the current heap; the second argument is not used (0x106533D0)
		void Create(unsigned int count, int unused);
		// Gives the block back (0x10653460); the argument is not used
		void Free(int unused);
		// Gives a block back to the heap (0x10653240); the object is not touched
		void FreeBlock(void* block);

		unsigned short* begin;
		unsigned int count;
	};

	// The table the collision objects register themselves in (name guess; the object is created by 0x10653530,
	// destroyed by 0x106534B0 and lives behind the pointer 0x1127CAC0)
	class CollisionObjectTable
	{
	public:
		// Clears the first four containers' words (0x10653490)
		CollisionObjectTable();

		// The free slots
		CollisionSlotStack free;
		// The slots
		CollisionHandleEntries entries;   // 0x0C
		unsigned short slotCount;         // 0x14
		// One serial per slot, raised every time the slot is handed out
		CollisionHandleSerials serials;   // 0x18

		// Puts every slot on the free stack, the last one on top (0x10653310; the unit's function list misses it)
		void FillFreeList();
		// Takes a slot for the object and writes its handle (0x10653250)
		void Add(void* object, CollisionHandle* handle);
		// The same under another name (0x10655AB0)
		void Register(void* object, CollisionHandle* handle);
		// Whether the slot the handle names still carries the handle's serial
		bool IsLive(const CollisionHandle* handle) const
		{
			if (handle->index >= slotCount)
			{
				return false;
			}
			return entries.begin[handle->index].serial == handle->serial;
		}
		// The object a handle names (0x10656090)
		void* GetObject(const CollisionHandle* handle) const;
		// Gives the slot of the handle back when the serial still matches (0x106532B0)
		void Remove(CollisionHandle* handle);
	};

	// A collision object around one volume, or around an array of them (0x10655F60 / 0x10655FC0)
	CollisionObject* CreateCollisionObject(CollisionVolume* volume, bool makeShape, float size);
	CollisionObject* CreateCollisionObject(CollisionVolume** volumes, unsigned int count, bool makeShape, float size,
		int a, int b);

	// The smaller of two slot counts (0x10655AC0)
	unsigned short MinSlots(unsigned short a, unsigned short b);

	// Builds the handle table with room for count slots, every slot free (0x10653530)
	void CreateCollisionObjectTable(unsigned int count);
	// Gives the table and its blocks back (0x106534B0)
	void DestroyCollisionObjectTable();

	// The transform and bounds of one collision object, the broad phase sees instead of the object itself
	// (class and member names are guesses; 0xE0 bytes, copied by 0x10669A70)
	class CollisionShape
	{
	public:
		unsigned char unknown0 : 1;
		unsigned char flag1 : 1;
		unsigned char flag2 : 1;
		unsigned char flag3 : 1;
		unsigned char flag4 : 1;
		unsigned char unknown5 : 3;
		unsigned char unknown1[7];
		CollisionObject* object;   // 0x08
		unsigned char unknownC[4];
		math::Vector unknown10;    // 0x10
		math::Vector unknown1C;    // 0x1C
		math::Vector unknown28;    // 0x28
		math::Vector unknown34;    // 0x34
		math::Vector unknown40;    // 0x40
		math::Vector unknown4C;    // 0x4C
		math::SymmetricMatrix unknown58;    // 0x58
		float boundsMinX;          // 0x70
		float boundsMinY;
		float boundsMinZ;
		float boundsMaxX;
		float boundsMaxY;
		float boundsMaxZ;
		float unknown88;           // 0x88
		float unknown8C;           // 0x8C
		math::Vector unknown90;    // 0x90
		math::Vector center;       // 0x9C
		// Recomputes the bounds and the centre from the object's transform (0x10669240, another unit)
		void Update(CollisionObject* object);
		// Recomputes the bounds from the transform the shape already has (0x10669C90, another unit)
		void Refresh();
		// Clears the two orientation vectors and the transform (0x10669C60, another unit)
		void Clear();
		// Sets the scale and remembers its inverse (0x106691B0, another unit)
		void SetScale(float scale);
		// Sets the inverse scale directly, or the scale when it is degenerate (0x10669200, another unit)
		void SetInverseScale(float inverse);
		// Copies six floats into the shape's vectors (0x106541C0, another unit)
		void SetVectors(const void* values);
		// Writes a position into the shape's offset vector (0x10669620, another unit)
		void SetPosition(math::Vector position);
		// Moves the shape to a point and marks it by the flag (0x10669E60, another unit)
		void MoveTo(math::Vector position, int flag);
		// Moves the shape from one point to another (0x10669F60, another unit)
		void MoveTo(math::Vector from, math::Vector to, int flag);
		// Moves the shape by an offset and wakes the owner when asked (0x10669EB0, another unit; names of this
		// group are guesses)
		void Translate(math::Vector offset, int wake);
		// The velocity of a point of the shape, written through the pointer (0x10669340, another unit)
		void GetPointVelocity(math::Vector point, math::Vector* velocity);
		// Adds to the shape's velocity (0x106694A0, another unit)
		void AddVelocity(math::Vector velocity, int wake);
		// Adds an impulse applied at a point to the velocity and the angular velocity (0x106694F0, another unit)
		void AddImpulse(math::Vector impulse, math::Vector point, int wake);
		// Adds to the shape's angular velocity (0x106695D0, another unit)
		void AddAngularVelocity(math::Vector velocity, int wake);
		// Sets bit 2 of the shape's flags (0x10669660, another unit)
		void SetFlag2(int value);
		// Sets the shape's width and marks it (0x1066A0B0, another unit)
		void SetSize(int a, int b, float size);
		// A copy of another shape, held by the object it is built for (0x10669A70, another unit)
		CollisionShape(const CollisionShape& other, CollisionObject* object);
		// Writes the transform, the matrices and the vectors out (0x10669730, another unit)
		void Print();
		// Empty (0x10669120, another unit)
		~CollisionShape();
		// The destructor and, when bit 0 of the flags is set, the delete behind it (0x10654470)
		void* DestroyAndFree(unsigned int flags);

		// The shape's accessors and point velocities (0x106541A0, 0x106541B0, 0x10654240, 0x10654250, 0x10654260,
		// 0x106542F0, 0x106543B0; the shape's unit is elsewhere, these copies sit in this object file)
		math::Vector* GetUnknown34();
		float GetInverseScale();
		math::SymmetricMatrix* GetUnknown58();
		math::Vector* GetUnknown90();
		// The velocity of a point given relative to the centre: the linear velocity plus the angular one crossed
		// with the point, from the current vectors and from the previous ones
		void GetRelativeVelocity(math::Vector point, math::Vector* velocity);
		void GetPreviousRelativeVelocity(math::Vector point, math::Vector* velocity);
		// Moves the shape from a point to its own centre (0x106543B0)
		void MoveToCenter(math::Vector from, int flag);
		// Recomputes what depends on the matrix at 0x58 (0x10669160, another unit; name guess)
		void Unknown10669160();

		// The shape's own flags, in the bits of the byte at 0 (0x10654380, 0x106543A0, 0x10654410; the shape's
		// unit is elsewhere, these copies sit in this object file)
		void SetFlag3(bool value);
		bool IsFlag3();
		void SetFlag4(bool value);

		unsigned int unknownA8;    // 0xA8
		math::Vector unknownAC;    // 0xAC
		math::Vector unknownB8;    // 0xB8
		math::Vector unknownC4;    // 0xC4
		math::Vector unknownD0;    // 0xD0
		float radius;              // 0xDC
	};

	// One geometry element of a mesh (8 bytes; its own unit names it)
	struct MeshElement
	{
		unsigned int unknown0;
		unsigned int unknown4;
	};

	// The elements a mesh holds (begin / end / end of storage)
	struct MeshGeometry
	{
		MeshElement* begin;
		MeshElement* end;
		MeshElement* capacity;

		// How many elements it holds (0x10655AA0)
		int Count() const;
	};

	// The mesh a mesh volume keeps its geometry in (0x38 bytes, a content::LoadObject of the RTTI; the class is only
	// declared here, its own unit builds it)
	class ConvexMesh : public content::LoadObject
	{
	public:
		// An empty mesh (0x10685E50, another unit)
		ConvexMesh();
		// Makes room for count geometry elements (0x106853F0, another unit)
		void Reserve(int count);
		// Appends one of the object's volumes (0x106855B0, another unit)
		void AddVolume(CollisionVolume* volume);

		unsigned char unknown8[0x28 - 8];
		MeshGeometry geometry;    // 0x28
		unsigned int unknown34;
	};

	// The physics object handle table (0x1127CAC0)
	extern CollisionObjectTable* gCollisionObjectTable;

	class CollisionObject
	{
	public:
		// Takes a slot in the physics handle table and clears every member but the transform (0x10655AE0)
		CollisionObject();
		// Gives the handle back, releases the mesh, destroys the volumes and deletes the shape (0x10655EA0)
		~CollisionObject();
		// Writes the transform, every volume and the shape out (0x10655A60)
		void Print();
		// Takes over the volume array, decides which volumes collide and initialises every volume (0x10655B60)
		void Initialize(CollisionVolume** newVolumes, unsigned int count);
		// A copy of the object with copies of its volumes and, unless unused, of its shape (0x10655BE0)
		CollisionObject* Clone(bool unused);
		// The radius of the box that holds every volume's bounds, or 0 when the volumes do not overlap
		// (0x10655DA0)
		float GetRadius() const;

		// Clears the changed flag and tells whether it was set
		bool TestAndClearChanged()
		{
			bool wasChanged = changed;
			changed = false;
			return wasChanged;
		}

		// Copies the transform into the object and refreshes the volumes and the shape (0x106544E0)
		void UpdateTransform(const math::Matrix& matrix);
		// The same and then the owner's bounds (0x10654580)
		void SetTransform(const math::Matrix& matrix);
		// Multiplies the transform by the matrix and sets the result (0x1065FED0)
		void TransformBy(const math::Matrix& matrix);
		// Copies the transform and refreshes the volumes (0x10654C30)
		void SetMatrix(const math::Matrix& matrix);
		// Gives every volume (and the faces of a type 4 volume) a material (0x10654670)
		void SetMaterial(unsigned char material);
		// Hands the argument to every volume's query setup and refreshes their bounds (0x106546F0)
		void SetVolumeQuery(const void* query);
		// The shape the broad phase sees, released and replaced (0x10654790)
		CollisionShape* SetShape(CollisionShape* newShape);
		// The volume descriptions, one method per volume type (0x10654820 - 0x106549E0)
		void SetCapsuleVolume(int index, const math::Capsule& capsule);
		void SetSphereVolume(int index, const math::Sphere& sphere);
		void SetVolume2(int index, const void* description);
		void SetVolume4(int index, const void* description);
		void SetVolume6(int index, const void* description);
		// The nearest volume the query hits, with the point and the volume's index (0x10654AB0)
		void CastQuery(const void* query, math::Vector* point, float* distance, unsigned int* index);
		// Switches one volume's bit in the volume mask (0x10654BB0)
		void SetVolumeEnabled(unsigned int index, bool enabled);
		// Which volumes may collide (0x106544B0; meaning unknown)
		void SetUnknown70(int value);
		// Whether the object takes part in the simulation at all (0x106544C0)
		void SetActive(bool active);
		// The material of one of the object's volumes (0x106545E0)
		unsigned char GetVolumeMaterial(int index);
		// Marks one volume as the one whose type's swapped pair table is used (0x10654A50)
		void SetVolumeSwapped(int index, bool swapped);
		// Whether one of the volumes has this type (0x10654C70)
		bool HasVolumeType(unsigned short type);
		// The mesh the mesh volumes register in (0x10654CB0)
		void SetMesh(ConvexMesh* mesh);
		// The name of the object (0x10655D90)
		void SetName(core::Name<core::CaseSensitiveKey> newName);

		// The shape's vectors and floats (0x10654D30, 0x10654D80, 0x10655230, 0x10655280, 0x10655340,
		// 0x10655390, 0x10655460, 0x10655750, 0x10655510, 0x10655580)
		math::Vector* GetUnknown10();
		math::Vector* GetUnknown1C();
		math::Vector* GetUnknown40();
		math::Vector* GetUnknown4C();
		math::SymmetricMatrix* GetUnknown58();
		math::Vector* GetUnknown90();
		math::Vector* GetUnknown9C();
		math::Vector* GetUnknown34();
		float GetScale();
		float GetInverseScale();

		// The shape's own settings, one method per shape setter (0x10654CE0, 0x10654DD0, 0x106550F0,
		// 0x10655190, 0x106553E0, 0x106554B0, 0x10655520, 0x10655590, 0x10655670)
		void Clear();
		void MoveTo(math::Vector position);
		void SetPosition(math::Vector position);
		void SetVectors(const void* values);
		void SetScale(float scale);
		void SetInverseScale(float inverse);
		void MoveFromTo(math::Vector from, math::Vector to);
		void MoveToCenter(math::Vector from);
		void SetSize(int a, int b, float size);
		// The shape's motion (0x10654E50, 0x10654ED0, 0x10654F50, 0x10654FD0, 0x10655070)
		void Translate(math::Vector offset);
		void GetVelocityAt(math::Vector point, math::Vector* velocity);
		void AddVelocity(math::Vector velocity);
		void AddImpulse(math::Vector impulse, math::Vector point);
		void AddAngularVelocity(math::Vector velocity);
		// The velocity of a point given relative to the shape's centre, from the current vectors and from the
		// previous ones (0x10655880, 0x106557A0)
		void GetRelativeVelocity(const math::Vector* point, math::Vector* velocity);
		void GetPreviousRelativeVelocity(const math::Vector* point, math::Vector* velocity);

		// The shape's flags (0x106552D0, 0x10655330, 0x106555F0, 0x106556E0, 0x10655740, 0x10655960)
		void SetFlag3(bool value);
		bool IsFlag3();
		void SetFlag1(bool value);
		bool IsFlag2();
		bool IsFlag1();
		void SetFlag4(bool value);

		// Sets the shape's flag 2 from the argument's low bit and lets the owner know (0x10655600)
		void SetWorld(void* world);

		// Accumulates the volumes' query filters (0x106559C0)
		void UpdateProperties();

		math::Matrix transform;                     // 0x00
		core::Name<core::CaseSensitiveKey> name;    // 0x40
		CollisionHandle handle;                     // 0x48
		int unknown4C;                              // 0x4C
		CollisionVolume** volumes;                  // 0x50
		unsigned short volumeCount;                 // 0x54
		unsigned char changed : 1;                  // 0x56
		unsigned char unknown56 : 7;
		unsigned char unknown57;                    // 0x57
		unsigned int state;                         // 0x58 (bit 31: active, lower bits: the volume mask)
		IntersectionProperties properties;          // 0x5C
		CollisionShape* shape;                      // 0x64
		PhysicsObject* owner;                       // 0x68
		ConvexMesh* mesh;                           // 0x6C
		int unknown70;                              // 0x70
		unsigned char unknown74[0x0c];              // 0x74
	};
}

#endif
