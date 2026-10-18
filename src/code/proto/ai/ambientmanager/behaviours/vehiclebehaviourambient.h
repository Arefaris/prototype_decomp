// proto::VehicleProperties, proto::VehicleBehaviour and proto::VehicleBehaviourAmbient (RTTI names; the original
// chains VehicleBehaviourAmbient : VehicleBehaviour : engine::FightTreeBehaviour : engine::Behaviour, with
// container::ListBase::Node at 0x68). The unit is code\proto\ai\ambientmanager\behaviours\vehiclebehaviourambient.cpp
// (path from its asserts); the vehicle's reflected properties record and the ambient traffic car's steering and path
// following code. Only the members the reconstructed functions use are declared; the others, and every name that
// is not a RTTI name or a string of the unit, are guesses.
#ifndef PROTO_AI_AMBIENTMANAGER_BEHAVIOURS_VEHICLEBEHAVIOURAMBIENT_H
#define PROTO_AI_AMBIENTMANAGER_BEHAVIOURS_VEHICLEBEHAVIOURAMBIENT_H

#include "code/container/listbase.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/fight/behaviours/fighttreebehaviour.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/vector.h"
#include "code/ravenphysics/context.h"

namespace math
{
	class Matrix;
}

namespace engine
{
	class GameObject;
}

namespace proto
{
	// The tuning record a vehicle refers to (RTTI: proto::VehicleProperties, a reflected load object): the members the
	// script data sets, in the units the data uses. The maximum speed is kept in metres per second and read and
	// written in kilometres per hour.
	class VehicleProperties : public content::MetaLoadObject
	{
	public:
		static content::ClassInfo* GetClassInfo();
		// 0x1044B940
		static content::MemberList* GetMembers();

		// 0x10445320 / 0x10445300
		float GetMaxSpeed() const;
		void SetMaxSpeed(float kilometresPerHour);

		unsigned char unknown8[0x18 - 0x8];
		float maxSpeed;
		float accelerationForce;
		float brakingForce;
		float wheelRadius;
		float collisionImpulse;
		float collisionDamage;
	};

	// One node of a vehicle's path (0x18 bytes): at +0x10 the record of the navigation area it lies in (its 16-bit
	// index at +4 selects an entry of the navmesh's area array, 0xFFFF for none) and at +0x14 the record of the lane
	// link it belongs to (two identifying bytes at +0 and +1). Field names are guesses.
	class PathNode
	{
	public:
		math::Vector position;
		int unknownC;
		// One lane of a road segment (4 bytes; only the first byte, the lane number, is read)
		struct Lane
		{
			signed char number;
			unsigned char unknown1[3];
		};
		struct AreaLink
		{
			unsigned char unknown0[4];
			unsigned short area;
			unsigned char unknown6[0xc - 6];
			// +0xC: the lanes of the segment
			Lane* lanes;
			Lane* lanesEnd;
		};
		struct Link
		{
			union
			{
				unsigned short key;
				signed char lane;
			};
		};
		AreaLink* areaLink;
		Link* link;
	};

	// The two vehicle lists and the ranking cursor of the ranking function (0x104EB720) live on the spawner; see
	// proto/parkedcarspawner.h.

	// The ring buffer of path nodes a vehicle behaviour keeps (0x10440A90 counts it, 0x10443550 indexes it): nodes of
	// 0x18 bytes between the read cursor at +0 and the write cursor at +4 inside the block [array (+8),
	// arrayEnd (+0xc)); once the read cursor has passed the write cursor the sequence wraps. Names are guesses.
	class PathRing
	{
	public:
		// 0x10440A90 (the compiler keeps a copy out of line)
		int Count() const
		{
			if (begin <= end)
			{
				return end - begin;
			}
			return (end - array) + (arrayEnd - begin);
		}
		// 0x10440BC0: the index-th node of the sequence, walking around the wrap
		PathNode* At(int index)
		{
			int first = arrayEnd - begin;
			if (index < first)
			{
				return begin + index;
			}
			return array + (index - first);
		}
		// The node put in last
		PathNode* Back()
		{
			if (end == array)
			{
				return arrayEnd - 1;
			}
			if (end > arrayEnd)
			{
				return begin - 1;
			}
			return end - 1;
		}
		// 0x104474D0: puts a node in front of the sequence; false when the block is used up
		bool PushFront(const PathNode& node);
		// Empties the ring and frees its block
		~PathRing()
		{
			begin = array;
			end = array;
			if (array != 0)
			{
				delete[] array;
			}
		}

		PathNode* begin;    // +0: the read cursor
		PathNode* end;      // +4: the write cursor
		PathNode* array;    // +8: the block
		PathNode* arrayEnd; // +0xc: the end of the block
	};

	class VehicleBehaviour : public engine::FightTreeBehaviour, public container::ListBase::Node
	{
	public:
		// The vehicle layer's overrides (vftable 0x10E04A9C: slots 1, 3 and 6 are 0x10442400, 0x10442140, 0x10442150)
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void OnMessage(engine::Message* message);

		// 0x10442100 / 0x10442880 (the vehicle layer's reflection, another part of the unit)
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// Slots 8 - 10 are the vehicle layer's own (0x10442160, 0x10443870, 0x104421A0 in VehicleBehaviour); the
		// ambient car overrides them with 0x104455B0, 0x1044BBC0 and 0x104455C0. Only slot 10 is called here. Its
		// answer is a "this vehicle blocks the query" test (name guessed).
		virtual bool Slot8();
		virtual void Slot9(int state);
		virtual bool IsBlocking();

		// 0x104421F0: the byte at +0x84, set to 1 by the halt path (0x1044BF10)
		bool GetUnknown84();
		// 0x104438C0: true when one of the vehicles on this car's path is within maxDistanceSquared of it (the
		// "car ahead" test of the ambient traffic; the name is a guess)
		bool IsVehicleAhead(float maxDistanceSquared);
		// 0x10443550: the index-th node of the car's path
		PathNode* GetPathNode(int index);

		// The node at +0x68 links the ambient manager's list of vehicle behaviours
		unsigned char unknown6C[0x74 - 0x6c];
		void* unknown74;      // +0x74, the record of the lane the car follows (0x10446700 reads its plane)
		math::Vector extents; // +0x78: half the size of the car (0x10445D20 derives the corners from it)

		// +0x84, set to 1 when the car is halted (0x1044BF10)
		bool halted;
		unsigned char unknown85[0x88 - 0x85];
		PathRing path88;      // +0x88
		unsigned char unknown98[0x9c - 0x98];
		bool unknown9C;       // +0x9c, set when the car is to be updated again (0x1044DAE0)
		bool unknown9D;       // +0x9d (0x104421C0 / D0 / E0)
		bool unknown9E;       // +0x9e (0x10442170)
		unsigned char unknown9F;
		float unknownA0;      // +0xa0 (0x10442170 tests it against zero)
		int unknownA4;        // +0xa4 (0x10442190)
	};

	// The message family of the ambient traffic (RTTI: proto::AmbientMessage, type 0x24; the id selects the message)
	struct AmbientMessage : public engine::IntrusiveMessage
	{
		explicit AmbientMessage(short newId) : engine::IntrusiveMessage(0x24, newId)
		{
		}
	};

	// A message that carries a vector (the desired facing of the car)
	struct AmbientVectorMessage : public AmbientMessage
	{
		AmbientVectorMessage(short newId) : AmbientMessage(newId)
		{
		}

		math::Vector vector;
	};

	// The description an ambient car is spawned from: its name and the record of its list
	struct AmbientVehicleInfo
	{
		core::Name<core::CaseSensitiveKey> name;
		unsigned char unknown8[0x28 - 8];
		void* list;
	};

	// A message that hands the car its description
	struct AmbientVehicleInfoMessage : public AmbientMessage
	{
		AmbientVehicleInfoMessage(short newId) : AmbientMessage(newId)
		{
		}

		AmbientVehicleInfo* info;
	};

	// A message that switches something on or off (type 6 messages: the flag is at +0xC)
	struct AmbientSwitchMessage : public engine::IntrusiveMessage
	{
		AmbientSwitchMessage(short newId) : engine::IntrusiveMessage(6, newId)
		{
		}

		bool enabled;
	};

	// The messages that name a target (RTTI: proto::TargetMessage, proto::SetTargetMessage; type 0x20, id 2; the
	// target at +0xC)
	class TargetMessage : public engine::IntrusiveMessage
	{
	public:
		TargetMessage(short newId) : engine::IntrusiveMessage(0x20, newId)
		{
		}
	};

	class SetTargetMessage : public TargetMessage
	{
	public:
		explicit SetTargetMessage(unsigned int newTarget) : TargetMessage(2)
		{
			target = newTarget;
		}
		virtual ~SetTargetMessage()
		{
		}

		unsigned int target;
	};

	// What a collision message tells (type 0x25, id 2): the object hit, and the kind of surface at +0x28
	struct CollisionMessage : public engine::IntrusiveMessage
	{
		unsigned char unknownC[0x28 - 0xc];
		int surface;
	};

	class VehicleBehaviourAmbient : public VehicleBehaviour
	{
	public:
		// 0x1044DA10; the vftable of the class is 0x10E05340 (slots 1, 3, 4, 6, 7, 8, 9, 10 are the class's own)
		virtual ~VehicleBehaviourAmbient();
		// 0x10445340 / 0x104454E0 / 0x1044F060 / 0x1044F710 / 0x104455B0 / 0x1044BBC0 / 0x104455C0
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);
		virtual bool Slot8();
		virtual void Slot9(int state);
		virtual bool IsBlocking();

		static content::ClassInfo* GetClassInfo();
		// 0x1044BAE0
		static content::MemberList* GetMembers();

		// Message handlers (0x1044F710 dispatches to them by the message's type and id)
		// 0x104481F0: the car is made from its description (id 5)
		void OnSetup(AmbientVehicleInfoMessage* message);
		// 0x10449650: the car is to face a direction (id 0xC)
		void OnSetFacing(AmbientVectorMessage* message);
		// 0x104480F0: the car's intersection tests are switched (type 6)
		void OnSwitchIntersection(AmbientSwitchMessage* message);
		// 0x1044C1E0: the mode is set to the value of the message (id 0x16)
		void OnSetMode(int mode);
		// 0x1044DAE0 / 0x1044DB10 (types 0xF and 0x14): the car stops what it does
		void OnStop(engine::Message* message);
		void OnStopIfHalted(engine::Message* message);
		// 0x1044DB40 (type 2): the car stands still again
		void OnReset();

		// 0x1044C220: a collision: the car may park and tell its target about it
		void OnCollision(CollisionMessage* message);
		// 0x1044D0F0: decides whether the car changes lanes
		void UpdateLaneChange();
		// 0x1044C340 (the lane change attempt; the argument is a chance), 0x10567F60 / 0x10431520
		bool Unknown1044C340(float chance);
		float Unknown10431520(engine::GameObjectHandle* handle, int lanes);
		int Unknown10567F60(PathNode::Link* link);
		// 0x1044C1C0: sets the mode to parked or driving and applies it
		void SetParked(bool parked);
		// 0x1044B1F0: applies the mode (the intersection test mask of the physics object)
		void ApplyMode();
		// 0x10448240: stops the car's physics
		void StopSimulation();
		// 0x10446A70: works the desired facing out into the steering angle
		void UpdateTurning();
		// 0x10446A30: the wheel angle a turn of that size asks for
		float Unknown10446A30(float angle);
		// 0x10445FB0: a point of the car in world space
		math::Vector TransformPoint(math::Vector offset);
		// 0x104483C0 / 0x10448400: the points the wheels' axes are at in world space
		math::Vector GetFrontWheelPosition();
		math::Vector GetRearWheelPosition();
		// 0x10447740: sets up the car's physics object, its ray casts and its random variations
		void SetupPhysics();
		// 0x1044BE00 / 0x1044BF10 / 0x10445E50 / 0x104462F0: the physics state of the car
		void ReleasePhysics();
		void HaltPhysics();
		void ApplyPhysicsState(bool keyframed);
		void SetSimulated(bool simulated);
		// 0x10446890 / 0x10443F30 / 0x10446700 (tests the car makes before it settles)
		bool Unknown10446890();
		bool Unknown10443F30();
		bool Unknown10446700();
		// 0x10448250: halts the car when the tests allow it
		bool TryHalt();
		// 0x104482B0: the distance to the next node of the path
		bool UpdateNodeDistance();
		// 0x10448440: when the car is halted and an area of its path is empty of cars, moves it on
		void CheckBlockedStop();
		// 0x10443BD0 (the position, the forward direction)
		void Unknown10443BD0(math::Vector* position, math::Vector* forward);
		// 0x10448FC0: the numbers of the lanes next to the one the car is in (-1 for none); false when it has no neighbour
		bool FindNeighbourLanes(int* lower, int* upper);
		// 0x10447280 (the argument is not read) / 0x1044CEA0
		void Unknown10447280(float unused);
		void Unknown1044CEA0();
		// 0x104416E0 / 0x10441B30 / 0x10446810 (the placement test of a car: the matrix a car at the position would
		// have, whether it fits there, and the settling that follows)
		static void Unknown104416E0(math::Vector* position, math::Vector* forward, math::Vector* extents, void* result);
		static bool Unknown10441B30(engine::GameObject* owner, void* probe, int* probeResult);
		void Unknown10446810();
		// 0x1044AAB0: finds the drawable's wheel parts once
		void FindWheelParts();
		// 0x1044B110: points the desired facing at the place five metres further along the path
		void AimAhead(int unused, const math::Vector* from, int* progress);
		// 0x10442900 / 0x10447D20 (path walks: the first measures from a position along the path, the second finds the
		// point a distance along it)
		void Unknown10442900(math::Vector* position, int count, const math::Vector* from, int* progress);
		math::Vector* PointAlongPath(math::Vector* result, const math::Vector* from, int node, float distance);
		// 0x104473E0: counts the cooldown down and, when it has run out, looks ahead on the path for a gap (the
		// answer is always false)
		bool UpdateGap(float dt, int node, float distance);
		// 0x10442200 / 0x10442B20 / 0x10445A60 / 0x10442BF0 / 0x104435B0 (path measurements, names unknown)
		bool Unknown10442200();
		int Unknown10442B20(int count);
		float Unknown10445A60(float speed);
		float Unknown10442BF0(int node, int count);
		float Unknown104435B0(int count);

		float unknownA8;
		unsigned char unknownAC[0xb0 - 0xac];
		void* unknownB0;      // +0xb0: the record of the car's list (vehicle manager)
		unsigned char unknownB4[0xb8 - 0xb4];
		math::Vector wheelFront;   // +0xb8
		math::Vector wheelRear;    // +0xc4
		float unknownD0;
		float speed;               // +0xd4
		bool unknownD8;   // +0xd8, passed with the name when it is released
		bool unknownD9;
		unsigned char unknownDA[0xe0 - 0xda];
		core::Name<core::CaseSensitiveKey> name;   // +0xe0
		bool unknownE8;
		unsigned char unknownE9[0xec - 0xe9];
		// +0xec: the tuning record ("vehicleProperties", reached by reference)
		VehicleProperties* vehicleProperties;
		float unknownF0;          // +0xf0, +0xf4, +0xf8: the car's speed, acceleration and braking (0x1044CEA0)
		float unknownF4;
		float unknownF8;
		unsigned char unknownFC[0x100 - 0xfc];
		bool simulated;            // +0x100
		unsigned char unknown101[0x104 - 0x101];
		math::Vector desiredFacing;   // +0x104
		unsigned char unknown110[0x11c - 0x110];
		ravenphysics::ObjectHandle physicsHandle;   // +0x11c
		float turningAngle;        // +0x120: the steering angle (0x10446A70)
		unsigned char unknown124[0x148 - 0x124];
		int wheelPart1;            // +0x148, +0x14c, +0x158, +0x15c, +0x168, +0x16c: the drawable's parts "w1" .. "w6"
		int wheelPart2;
		unsigned char unknown150[0x158 - 0x150];
		int wheelPart3;
		int wheelPart4;
		unsigned char unknown160[0x168 - 0x160];
		int wheelPart5;
		int wheelPart6;
		bool unknown170;           // +0x170: set while the car changes lanes
		unsigned char unknown171[0x174 - 0x171];
		int unknown174;            // +0x174: a random number below three picked when the car is set up
		unsigned char unknown178[0x17c - 0x178];
		float unknown17C;          // +0x17c
		unsigned char unknown180[0x188 - 0x180];
		int mode;                  // +0x188
		unsigned char unknown18C[0x198 - 0x18c];
		float unknown198;          // +0x198: the distance to the next path node less one (0x104482B0)
	};
}

#endif
