// proto::VehicleBehaviourAmbient (path from the unit's own assert string: code\proto\ai\ambientmanager\behaviours\
// vehiclebehaviourambient.cpp). Only the two functions below are reconstructed; the rest of the unit (the reflected
// members, the update 0x1044F060, the message dispatch 0x1044F710 and the state machine) is not.
#include "code/proto/ai/ambientmanager/behaviours/vehiclebehaviourambient.h"

#include "code/engine/gameobject/gameobject.h"
#include "code/core/refptr.h"
#include "code/engine/physics/physicsmessages.h"
#include "code/ravenphysics/physicsobject.h"
#include "code/proto/ai/ambientmanager/ambientmanager.h"
#include "code/math/matrix.h"
#include <math.h>
#include <new>

namespace proto
{
	// The navigation mesh the ambient managers share (the global 0x112730C0): the array of area records at +0x38. Each
	// record is 0x40 bytes and keeps the list of the vehicles standing in it at +0x28 (the 16-bit index at +0x36 is
	// another of its fields, read by the pedestrian code).
	class NavArea
	{
	public:
		unsigned char unknown0[0x28];
		container::ListBase::Node* vehicles;
		unsigned char unknown2C[0x40 - 0x2c];
	};

	class NavMesh
	{
	public:
		unsigned char unknown0[0x38];
		NavArea* areas;
	};

	extern NavMesh* gNavMesh;

	// The area a path node lies in, or null when the node names none
	static NavArea* GetArea(PathNode* node)
	{
		unsigned short index = node->areaLink->area;
		if (index == 0xffff)
		{
			return 0;
		}
		return &gNavMesh->areas[index];
	}

	// A vehicle behaviour of the ambient manager is the object its list node at 0x68 sits in
	static VehicleBehaviour* BehaviourOf(container::ListBase::Node* node)
	{
		return (VehicleBehaviour*)((char*)node - 0x68);
	}

	// FUNCTION: ENGINE 0x104421F0
	bool VehicleBehaviour::GetUnknown84()
	{
		return halted;
	}

	// FUNCTION: ENGINE 0x104438C0
	// NONMATCHING: the shape is the original's (the list of ambient vehicles is walked per run of path nodes that
	// share an area, and the car ahead is picked by the distance between the two owners' transforms), but the loop
	// and index forms were not brought to byte identity.
#ifdef NONMATCHING
	bool VehicleBehaviour::IsVehicleAhead(float maxDistanceSquared)
	{
		container::ListBase::Node* node = next;
		int count = path88.Count();
		for (int i = 0; i < count; i++)
		{
			PathNode* here = path88.At(i);
			for (; node != 0; node = node->next)
			{
				VehicleBehaviour* vehicle = BehaviourOf(node);
				if (!vehicle->halted)
				{
					continue;
				}
				if (vehicle->IsBlocking())
				{
					continue;
				}
				if (vehicle->path88.Count() <= 0)
				{
					continue;
				}
				if (here->link->key != vehicle->path88.At(0)->link->key)
				{
					continue;
				}
				const math::Matrix& mine = owner->transform->Get();
				const math::Matrix& theirs = vehicle->owner->transform->Get();
				float dx = mine.m[3][0] - theirs.m[3][0];
				float dy = mine.m[3][1] - theirs.m[3][1];
				float dz = mine.m[3][2] - theirs.m[3][2];
				return dz * dz + dy * dy + dx * dx < maxDistanceSquared;
			}
			NavArea* area = GetArea(here);
			// the next run of nodes belongs to the next area (the run is skipped, the next round walks it)
			if (i < count - 1)
			{
				int last = i;
				for (;;)
				{
					last++;
					if (last >= count - 1 || area != GetArea(path88.At(last)))
					{
						break;
					}
				}
				i = last - 1;
			}
			node = area != 0 ? area->vehicles : 0;
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x10443550
	PathNode* VehicleBehaviour::GetPathNode(int index)
	{
		return path88.At(index);
	}

	// FUNCTION: ENGINE 0x104474D0
	bool PathRing::PushFront(const PathNode& node)
	{
		PathNode* limit = arrayEnd;
		PathNode* last = end;
		if (last < limit)
		{
			PathNode* block = array;
			if (begin == block)
			{
				begin = limit;
			}
			begin--;
			PathNode* slot = begin;
			if (slot == last)
			{
				end = last + (limit - block);
			}
			new (slot) PathNode(node);
			return true;
		}
		return false;
	}

	// The copy of the ring buffer's inline At that the compiler keeps out of line (the copy of Count, 0x10440A90, only
	// appears once a compiled function calls it)
	// FUNCTION: ENGINE 0x10440BC0

	// The meta types and accessors the two member lists build; the compiler keeps these out of line
	// (GetClassMetaType<VehicleBehaviour>, MemberOffset of the properties reference, the properties' caster and member
	// accessors, and one meta type per float member)
	// FUNCTION: ENGINE 0x102AB360
	// FUNCTION: ENGINE 0x102AB3A0
	// FUNCTION: ENGINE 0x10444220
	// FUNCTION: ENGINE 0x10445CC0
	// FUNCTION: ENGINE 0x10445BB0
	// FUNCTION: ENGINE 0x104476A0
	// FUNCTION: ENGINE 0x104476B0
	// FUNCTION: ENGINE 0x104476E0
	// FUNCTION: ENGINE 0x10447700
	// FUNCTION: ENGINE 0x10447720
	// FUNCTION: ENGINE 0x10447560
	// FUNCTION: ENGINE 0x104475A0
	// FUNCTION: ENGINE 0x104475E0
	// FUNCTION: ENGINE 0x10447620
	// FUNCTION: ENGINE 0x10447660
	// FUNCTION: ENGINE 0x1044B860
	// FUNCTION: ENGINE 0x1044B940
	content::MemberList* VehicleProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[6] = {
			{ content::GetMemberPrimitiveMetaType<VehicleProperties, float, 1>("p"),
				content::MemberOffset(&((VehicleProperties*)0)->wheelRadius, 0x24), "wheelRadius" },
			{ content::GetMemberMetaType<VehicleProperties, float>(&VehicleProperties::GetMaxSpeed,
				&VehicleProperties::SetMaxSpeed, "p"), 0, "maxSpeed" },
			{ content::GetMemberPrimitiveMetaType<VehicleProperties, float, 2>("p"),
				content::MemberOffset(&((VehicleProperties*)0)->accelerationForce, 0x1c), "accelerationForce" },
			{ content::GetMemberPrimitiveMetaType<VehicleProperties, float, 3>("p"),
				content::MemberOffset(&((VehicleProperties*)0)->brakingForce, 0x20), "brakingForcemax" },
			{ content::GetMemberPrimitiveMetaType<VehicleProperties, float, 4>("p"),
				content::MemberOffset(&((VehicleProperties*)0)->collisionImpulse, 0x28), "collisionImpulse" },
			{ content::GetMemberPrimitiveMetaType<VehicleProperties, float, 5>("p"),
				content::MemberOffset(&((VehicleProperties*)0)->collisionDamage, 0x2c), "collisionDamage" },
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1044B8E0
	// FUNCTION: ENGINE 0x1044BAE0
	content::MemberList* VehicleBehaviourAmbient::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<VehicleBehaviour>();
		static content::BaseClassCasterImpl<VehicleBehaviour, VehicleBehaviourAmbient> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[1] = {
			{ content::GetReferenceMetaType<VehicleBehaviourAmbient, VehicleProperties>("p"),
				content::MemberOffset(&((VehicleBehaviourAmbient*)0)->vehicleProperties, 0xec), "vehicleProperties" },
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10448240
	void VehicleBehaviourAmbient::StopSimulation()
	{
		SetSimulated(false);
	}

	// FUNCTION: ENGINE 0x10449650
	void VehicleBehaviourAmbient::OnSetFacing(AmbientVectorMessage* message)
	{
		desiredFacing.x = message->vector.x;
		desiredFacing.y = message->vector.y;
		desiredFacing.z = message->vector.z;
		UpdateTurning();
	}

	// FUNCTION: ENGINE 0x104483C0
	math::Vector VehicleBehaviourAmbient::GetFrontWheelPosition()
	{
		return TransformPoint(wheelFront);
	}

	// FUNCTION: ENGINE 0x10448400
	math::Vector VehicleBehaviourAmbient::GetRearWheelPosition()
	{
		return TransformPoint(wheelRear);
	}

	// FUNCTION: ENGINE 0x1044C1C0
	void VehicleBehaviourAmbient::SetParked(bool parked)
	{
		mode = parked ? 1 : 0;
		ApplyMode();
	}

	// FUNCTION: ENGINE 0x1044C1E0
	void VehicleBehaviourAmbient::OnSetMode(int newMode)
	{
		int old = mode;
		if (newMode != old)
		{
			bool apply = false;
			if (newMode == 0 || old == 0)
			{
				apply = true;
			}
			mode = newMode;
			if (apply)
			{
				ApplyMode();
			}
		}
	}

	// FUNCTION: ENGINE 0x1044DAE0
	void VehicleBehaviourAmbient::OnStop(engine::Message* message)
	{
		ReleasePhysics();
		sequencer.Reset();
		unknown9C = true;
	}

	// FUNCTION: ENGINE 0x1044DB10
	void VehicleBehaviourAmbient::OnStopIfHalted(engine::Message* message)
	{
		if (halted)
		{
			ReleasePhysics();
			sequencer.Reset();
		}
	}

	// FUNCTION: ENGINE 0x1044DA10
	VehicleBehaviourAmbient::~VehicleBehaviourAmbient()
	{
		gAmbientManager->ReleaseName(name, unknownE8);
		gAmbientManager->RemoveVehicle(this);
		SetSimulated(false);
		if (physicsHandle.IsValid())
		{
			physicsHandle.DestroyObject();
		}
		core::SafeRelease(vehicleProperties);
	}

	// FUNCTION: ENGINE 0x1044DB40
	void VehicleBehaviourAmbient::OnReset()
	{
		unknown9C = false;
		speed = 0.0f;
		Unknown1044CEA0();
	}

	// FUNCTION: ENGINE 0x104481F0
	void VehicleBehaviourAmbient::OnSetup(AmbientVehicleInfoMessage* message)
	{
		SetupPhysics();
		unknownB0 = (char*)message->info->list + 4;
		gAmbientManager->AddVehicle(this);
		name = message->info->name;
	}

	// FUNCTION: ENGINE 0x104480F0
	void VehicleBehaviourAmbient::OnSwitchIntersection(AmbientSwitchMessage* message)
	{
		if (message->enabled)
		{
			if (halted)
			{
				ApplyPhysicsState(false);
				SetSimulated(true);
			}
			engine::SetIntersectionPropertiesMessage first(0x8000, true, 0, false);
			owner->SendMessage(&first);
			engine::SetIntersectionPropertiesMessage second(0x4000, true, 1, false);
			owner->SendMessage(&second);
			return;
		}
		ApplyPhysicsState(true);
		SetSimulated(false);
	}

	// FUNCTION: ENGINE 0x10448250
	// EQUIVALENT: the same calls with the same arguments in the same order; the engine's callee tests and
	// state setters are compiled earlier in the unit and keep ecx, ours reloads it (three `mov ecx, esi`), 43.8 %
	bool VehicleBehaviourAmbient::TryHalt()
	{
		if (unknown74 != 0)
		{
			if (Unknown10446890() && Unknown10443F30() && Unknown10446700())
			{
				SetSimulated(true);
				ApplyPhysicsState(false);
				return true;
			}
			unknown9C = true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1044B1F0
	void VehicleBehaviourAmbient::ApplyMode()
	{
		ravenphysics::PhysicsObject* object = physicsHandle.GetObjectUnchecked();
		if (mode != 0)
		{
			if ((unsigned int)(mode - 1) <= 1)
			{
				ravenphysics::IntersectionFilter filter;
				filter.properties.unknown0 = 2;
				filter.properties.unknown4 = 1;
				object->SetFilter(&filter);
			}
		}
		else
		{
			ravenphysics::IntersectionFilter filter;
			filter.properties.unknown0 = 0x8000;
			filter.properties.unknown4 = 0x2000;
			object->SetFilter(&filter);
		}
		Unknown10447280(0.0f);
	}

	// FUNCTION: ENGINE 0x10448FC0
	bool VehicleBehaviourAmbient::FindNeighbourLanes(int* lower, int* upper)
	{
		PathNode::AreaLink* area = path88.At(0)->areaLink;
		int lane = path88.At(0)->link->lane;
		*lower = -1;
		*upper = 6;
		int count = area->lanesEnd - area->lanes;
		for (int i = 0; i < count; i++)
		{
			int number = area->lanes[i].number;
			if (number < lane && number > *lower)
			{
				*lower = number;
			}
			if (number > lane && number < *upper)
			{
				*upper = number;
			}
		}
		if (*upper == 6)
		{
			*upper = -1;
		}
		if (*lower < 0 && *upper < 0)
		{
			return false;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x1044BE00
	void VehicleBehaviourAmbient::ReleasePhysics()
	{
		engine::GetPhysicsObjectMessage query;
		owner->PostMessage(&query);
		if (query.handle.IsValid())
		{
			engine::SetPhysicsObjectKeyframedMessage keyframed(false);
			owner->SendMessage(&keyframed);
			engine::SetKeyframedPhysicsUpdateEnabledMessage updates(false);
			owner->SendMessage(&updates);
		}
		StopSimulation();
		ApplyPhysicsState(true);
		halted = false;
	}

	// FUNCTION: ENGINE 0x1044BF10
	void VehicleBehaviourAmbient::HaltPhysics()
	{
		bool ready;
		if (unknownA4 != 0)
		{
			ready = TryHalt();
		}
		else
		{
			ready = UpdateNodeDistance();
		}
		if (ready)
		{
			engine::GetPhysicsObjectMessage query;
			owner->PostMessage(&query);
			if (query.handle.IsValid())
			{
				engine::SetPhysicsObjectKeyframedMessage keyframed(true);
				owner->SendMessage(&keyframed);
				engine::SetKeyframedPhysicsUpdateEnabledMessage updates(true);
				owner->SendMessage(&updates);
				ApplyPhysicsState(false);
			}
			halted = true;
		}
	}

	// FUNCTION: ENGINE 0x104482B0
	// NONMATCHING: the three differences are computed with SSE and spilled before the x87 sum of squares in the
	// engine; ours subtracts in the x87 unit, 60 %
#ifdef NONMATCHING
	bool VehicleBehaviourAmbient::UpdateNodeDistance()
	{
		unsigned int count = path88.Count();
		if (count > 1)
		{
			PathNode* node = path88.At(1);
			math::Matrix& matrix = owner->transform->value;
			float dz = matrix.m[3][2] - node->position.z;
			float dx = matrix.m[3][0] - node->position.x;
			float dy = matrix.m[3][1] - node->position.y;
			unknown198 = sqrt(dz * dz + dx * dx + dy * dy) - 1.0f;
			return true;
		}
		unknown198 = -1.0f;
		return true;
	}
#endif
}
