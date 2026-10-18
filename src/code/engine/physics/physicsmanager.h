// engine::PhysicsManager and the messages it sends (the RTTI names; the file name comes from the assert paths of
// the unit). The layouts and member names are reconstructions from the code.
#ifndef ENGINE_PHYSICS_PHYSICSMANAGER_H
#define ENGINE_PHYSICS_PHYSICSMANAGER_H

#include "code/engine/message.h"
#include "code/ravenphysics/callback.h"
#include "code/ravenphysics/context.h"

namespace engine
{
	// The element types of the growable arrays the manager builds (container::ArrayDynamicNew). Their sizes come from
	// the code that allocates and copies them (0x1C bytes, copied as seven words); the names and the members are
	// guesses. The manager collects collisions into them and hands the ranges to the collision messages.
	struct CollisionItem
	{
		void* unknown0;
		void* unknown4;
		unsigned int unknown8;
		unsigned int unknownC;
		unsigned int unknown10;
		unsigned int unknown14;
		unsigned int unknown18;
	};

	struct ConstraintItem
	{
		void* unknown0;
		void* unknown4;
		unsigned int unknown8;
		unsigned int unknownC;
		unsigned int unknown10;
		unsigned int unknown14;
		unsigned int unknown18;
	};

	// 0x70 bytes: the widest element the manager's arrays hold (name and members are guesses)
	struct CollisionPair
	{
		unsigned int unknown0[0x1C];
	};

	// The physics manager's shared query buffers. Each has a lock flag that keeps a second query out while one is
	// running; the buffers live at file scope so the locks address them directly (the classes hold no data).
	// The arrays other than the ray hits are guesses from the element sizes the manager allocates for them.
	struct HitIndexArray
	{
		unsigned int* begin;
		unsigned int* end;
		unsigned int* capacity;
	};

	struct CollisionArray
	{
		void* begin;
		void* end;
		void* capacity;
	};

	extern bool gRayHitBufferLocked;
	extern ravenphysics::RayHitArray gRayHitBuffer;
	extern bool gHitIndexBufferLocked;
	extern HitIndexArray gHitIndexBuffer;
	extern bool gCollisionBufferLocked;
	extern CollisionArray gCollisionBuffer;

	// Holds the hit index buffer (name guess)
	class HitIndexBufferLock
	{
	public:
		HitIndexBufferLock(bool clear);
		~HitIndexBufferLock();
		HitIndexArray& Get();
	};

	// Holds the collision buffer (name guess)
	class CollisionBufferLock
	{
	public:
		CollisionBufferLock(bool clear);
		~CollisionBufferLock();
		CollisionArray& Get();
	};

	// The context's placement marker, set and cleared on behalf of other units (0x107E3D00 / 0x107E3D10; names guessed)
	void ResetPlacement();
	void SetPlacementPosition(const math::Vector& position);

	// Puts every object a query finds in the box to collision mode 2 (0x107E4E10; name guessed)
	void SetCollisionModeInBox(void* first, void* second, HitIndexArray* hits);

	// The callbacks the manager runs around the context's update are kept in two lists (heads 0x11283574 and
	// 0x11283578; names guessed): the callback is put at the front, or taken out of the list again
	extern ravenphysics::PhysicsContextCallBack* gPreStepCallbacks;
	extern ravenphysics::PhysicsContextCallBack* gPostStepCallbacks;
	// 0x107E4D90 / 0x107E4DB0 and 0x107E4DD0 / 0x107E4DF0
	void AddPreStepCallback(ravenphysics::PhysicsContextCallBack* callback);
	void RemovePreStepCallback(ravenphysics::PhysicsContextCallBack* callback);
	void AddPostStepCallback(ravenphysics::PhysicsContextCallBack* callback);
	void RemovePostStepCallback(ravenphysics::PhysicsContextCallBack* callback);

	// The flag a running physics update sets (0x107E3C80 / 0x107E3C90 / 0x107E3CA0; names guessed)
	void SetPhysicsUpdating();
	void ClearPhysicsUpdating();
	bool IsPhysicsUpdating();

	// Walks one of the context's object lists and reports the objects the flags select (0x107E4F40)
	void ListObjects(ravenphysics::ObjectList* objects, bool awake, bool asleep, bool physics, bool trigger);

	// The pm_ console commands and the script function behind the ones with arguments (0x107E5180 - 0x107E6B70).
	// The names are the ones the manager registers them under (0x107E6F20).
	void pm_Help();
	void pm_ListStaticObjects();
	void pm_ListMovableObjects();
	void pm_ListAwakePhysicsObjects();
	void pm_ListAsleepObjects();
	void pm_ListSelectedObjects(bool awake, bool asleep, bool physics, bool trigger);
	void pm_ListPhysicsObjects();
	void pm_ListTriggerObjects();
	void pm_ListObjects();
	void pm_ListCollisionObjects(int value);
	void pm_ListConstraints(int value);
	void pm_ListAllConstraints();
	void pm_ListVolumes(int value);
	void pm_ObjectInfo(int value);
	void pm_LogCollisions(int value);
	void pm_Substeps(int substeps);

	// 0x107E6F20: hands the manager's commands to the script manager under gContext as their owner
	void RegisterPhysicsCommands();
	// A pair of pointers (begin / end) handed to the collision messages; name guess.
	struct CollisionItemList
	{
		void* begin;
		void* end;
	};

	// 0x10E68A28 (RTTI engine::CollisionBrokeringMessage)
	struct CollisionBrokeringMessage : public IntrusiveMessage
	{
	public:
		CollisionBrokeringMessage(const CollisionItemList& newItems);
		~CollisionBrokeringMessage();

		CollisionItemList items;
	};

	// 0x10E68A30 (RTTI engine::CollisionResponseMessage)
	struct CollisionResponseMessage : public IntrusiveMessage
	{
	public:
		CollisionResponseMessage(const CollisionItemList& newItems);
		~CollisionResponseMessage();

		CollisionItemList items;
	};

	// 0x10E68A38 (RTTI engine::BatchedRayCastMessage)
	struct BatchedRayCastMessage : public IntrusiveMessage
	{
	public:
		BatchedRayCastMessage(unsigned int newUnknownC, unsigned int newUnknown10, unsigned int newUnknown14,
			unsigned int newUnknown18, unsigned int newUnknown1C);
		~BatchedRayCastMessage();

		unsigned int unknownC;
		unsigned int unknown10;
		unsigned int unknown14;
		unsigned int unknown18;
		unsigned int unknown1C;
	};

	// 0x10E68A40 (RTTI engine::BatchedRayCastHitMessage)
	struct BatchedRayCastHitMessage : public IntrusiveMessage
	{
	public:
		BatchedRayCastHitMessage(unsigned int newIndex, unsigned int newUnknown10, unsigned int newUnknown14);
		~BatchedRayCastHitMessage();

		unsigned int index;
		unsigned int unknown10;
		unsigned int unknown14;
	};

	// 0x10E68A48 (RTTI engine::BatchedShapeCastMessage)
	struct BatchedShapeCastMessage : public IntrusiveMessage
	{
	public:
		BatchedShapeCastMessage(unsigned int newUnknownC, unsigned int newUnknown10, unsigned int newUnknown14,
			unsigned int newUnknown18, unsigned int newUnknown1C);
		~BatchedShapeCastMessage();

		unsigned int unknownC;
		unsigned int unknown10;
		unsigned int unknown14;
		unsigned int unknown18;
		unsigned int unknown1C;
	};

	// 0x10E68A50 (RTTI engine::BatchedShapeCastHitMessage)
	struct BatchedShapeCastHitMessage : public IntrusiveMessage
	{
	public:
		BatchedShapeCastHitMessage(unsigned int newIndex, unsigned int newUnknown10, unsigned int newUnknown14);
		~BatchedShapeCastHitMessage();

		unsigned int index;
		unsigned int unknown10;
		unsigned int unknown14;
	};

	// 0x10E68A58 (RTTI engine::PhysicsFixupUnsolvedConstraintsMessage)
	struct PhysicsFixupUnsolvedConstraintsMessage : public IntrusiveMessage
	{
	public:
		PhysicsFixupUnsolvedConstraintsMessage(unsigned int newUnknown10);

		unsigned int unknown10;
	};

	// 0x10E68A60 (RTTI engine::PhysicsFixupPoweredConstraintsMessage)
	struct PhysicsFixupPoweredConstraintsMessage : public IntrusiveMessage
	{
	public:
		PhysicsFixupPoweredConstraintsMessage(unsigned int newUnknown10);

		unsigned int unknown10;
	};
}

#endif
