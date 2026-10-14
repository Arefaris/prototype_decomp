// proto::VehicleBehaviour and proto::VehicleBehaviourAmbient (RTTI names; the original chains
// VehicleBehaviourAmbient : VehicleBehaviour : engine::FightTreeBehaviour : engine::Behaviour, with
// container::ListBase::Node at 0x68). The intermediate classes and the 11-slot vftable (0x10E05340) are not
// reconstructed, so the class derives from engine::Behaviour directly and keeps the list node as a member; only the
// members the reconstructed functions read are declared. Names are guesses.
#ifndef PROTO_AI_AMBIENTMANAGER_BEHAVIOURS_VEHICLEBEHAVIOURAMBIENT_H
#define PROTO_AI_AMBIENTMANAGER_BEHAVIOURS_VEHICLEBEHAVIOURAMBIENT_H

#include "code/container/listbase.h"
#include "code/engine/gameobject/behaviour.h"

namespace math
{
	class Matrix;
}

namespace proto
{
	// One node of a vehicle's path (0x18 bytes): at +0x10 the record of the navigation area it lies in (its 16-bit
	// index at +4 selects an entry of the navmesh's area array, 0xFFFF for none) and at +0x14 the record of the lane
	// link it belongs to (two identifying bytes at +0 and +1). Field names are guesses.
	class PathNode
	{
	public:
		unsigned char unknown0[0x10];
		struct AreaLink
		{
			unsigned char unknown0[4];
			unsigned short area;
		};
		struct Link
		{
			unsigned short key;
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
		// 0x10440A90 (another unit's copy)
		int Count() const;
		// 0x10443550: the index-th node of the sequence, walking around the wrap
		PathNode* At(int index);

		PathNode* begin;    // +0: the read cursor
		PathNode* end;      // +4: the write cursor
		PathNode* array;    // +8: the block
		PathNode* arrayEnd; // +0xc: the end of the block
	};

	class VehicleBehaviourAmbient : public engine::Behaviour
	{
	public:
		// Slots 8 - 10 of the original's vftable (0x10E05340) come from proto::VehicleBehaviour and
		// engine::FightTreeBehaviour, which are not reconstructed; only slot 10 (0x104455C0) is called here. Its
		// answer is a "this vehicle blocks the query" test (name guessed).
		virtual void Slot8();
		virtual void Slot9();
		virtual bool IsBlocking();

		// 0x104421F0: the byte at +0x84, set to 1 by the halt path (0x1044BF10)
		bool GetUnknown84();
		// 0x104438C0: true when one of the vehicles on this car's path is within maxDistanceSquared of it (the
		// "car ahead" test of the ambient traffic; the name is a guess)
		bool IsVehicleAhead(float maxDistanceSquared);

		unsigned char unknownC[0x68 - 0xc];
		// The ambient manager's list of vehicle behaviours (container::ListBase::Node in the original)
		container::ListBase::Node node68;
		unsigned char unknown6C[0x78 - 0x6c];
		void* unknown78;      // +0x78, the object 0x104421B0 answers
		unsigned char unknown7C[0x84 - 0x7c];
		// +0x84, set to 1 when the car is halted (0x1044BF10)
		bool halted;
		unsigned char unknown85[0x88 - 0x85];
		PathRing path88;      // +0x88
		unsigned char unknown98[0x9d - 0x98];
		bool unknown9D;       // +0x9d (0x104421C0 / D0 / E0)
		bool unknown9E;       // +0x9e (0x10442170)
		unsigned char unknown9F;
		float unknownA0;      // +0xa0 (0x10442170 tests it against zero)
		int unknownA4;        // +0xa4 (0x10442190)
	};
}

#endif
