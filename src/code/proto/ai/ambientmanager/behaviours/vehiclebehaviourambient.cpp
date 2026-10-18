// proto::VehicleBehaviourAmbient (path from the unit's own assert string: code\proto\ai\ambientmanager\behaviours\
// vehiclebehaviourambient.cpp). Only the two functions below are reconstructed; the rest of the unit (the reflected
// members, the update 0x1044F060, the message dispatch 0x1044F710 and the state machine) is not.
#include "code/proto/ai/ambientmanager/behaviours/vehiclebehaviourambient.h"

#include "code/engine/audio/audiomessage.h"
#include "code/engine/controller/inputsystem.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/choreo/deltatransform.h"
#include "code/core/bitfield.h"
#include "code/core/heap.h"
#include "code/core/refptr.h"
#include "code/core/report.h"
#include "code/engine/physics/physicsmessages.h"
#include "code/math/random.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/physicsobject.h"
#include "code/proto/ai/ambientmanager/ambientmanager.h"
#include "code/math/matrix.h"
#include "code/math/obb.h"
#include "code/math/plane.h"
#include "code/math/quaternion.h"
#include "code/pure3d/pose.h"
#include <float.h>
#include <math.h>
#include <new>

namespace math
{
	// The zero vector (0x11283234)
	extern const Vector kZeroVector;
}

namespace proto
{
	// The navigation mesh the ambient managers share (the global 0x112730C0): the array of area records at +0x38. Each
	// record is 0x40 bytes and keeps the list of the vehicles standing in it at +0x28 (the 16-bit index at +0x36 is
	// another of its fields, read by the pedestrian code).
	class NavArea
	{
	public:
		// 0x105680A0 / 0x105680D0: puts the car in / takes it out of the area's list of cars
		void AddVehicle(VehicleBehaviour* vehicle);
		void RemoveVehicle(VehicleBehaviour* vehicle);

		// 0x10567FE0: whether the area's state at +0x20 lets cars through (not 0, 4, 5, 6 or 7)
		bool Unknown10567FE0();

		unsigned char unknown0[0x10];
		// The plane the area lies in (0x1044B480)
		math::Plane plane;
		int state;
		unsigned char unknown24[0x28 - 0x24];
		container::ListBase::Node* vehicles;
		unsigned char unknown2C[0x38 - 0x2c];
		short vehicleCount;
		unsigned char unknown3A[0x40 - 0x3a];
	};

	class NavMesh
	{
	public:
		// 0x1056D2C0: finds the area a position lies in (within the margins below and above it), answering whether it
		// found one
		bool Find(const math::Vector* position, float below, float above, NavArea** result, math::Vector* closest,
			core::BitField<unsigned short> filter);

		unsigned char unknown0[0x28];
		// The handles of the objects the road segments belong to (4 bytes each)
		engine::GameObjectHandle* handles;
		unsigned char unknown2C[0x38 - 0x2c];
		NavArea* areas;
	};

	extern NavMesh* gNavMesh;

	// The attribute of an ambient actor that holds its state owner (the name at 0x11256298)
	extern content::ObjectName gStateAttributeName;

	// The handles of the players' game objects (0x1126E40C)
	extern engine::GameObjectHandle gPlayerHandles[];

	// The area a path node lies in, or null when the node names none
	static inline NavArea* GetArea(PathNode* node)
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

	#define VEHICLEBEHAVIOURAMBIENT_FILE "..\\..\\..\\code\\proto\\ai\\ambientmanager\\behaviours\\vehiclebehaviourambient.cpp"
	// The unit's asserts of a number being a number: reported once (the flag next to the check), and the report may
	// switch itself off
	#define VEHICLE_ASSERT_NOT_NAN(line, text, value) 		{ 			static bool sReport = true; 			if (sReport && _isnan((double)(value)) 				&& core::Report(1, " oldassert ", VEHICLEBEHAVIOURAMBIENT_FILE, line, text, 0) == 3) 			{ 				sReport = false; 			} 		}

	// The widest angle a wheel is turned to (0x1108CB20, fifty degrees)
	float sMaxWheelAngle = 0.87266463f;

	// The attribute of a game object that holds its drawable (the name at 0x112834C8) and the part lookup of the
	// drawable (0x106DD6D0, which forwards to a member at +0x10)
	extern content::ObjectName gDrawableAttributeName;
	struct PartLookup
	{
		int FindPart(const core::Name<core::CaseSensitiveKey>& name);
		// 0x10445C20: the part by its text
		int FindPart(const char* name);
	};

	// FUNCTION: ENGINE 0x10445980
	void VehicleBehaviourAmbient::MovePhysicsObject(ravenphysics::PhysicsObject* object, math::Vector position)
	{
		unsigned int count = object->objectCount;
		for (unsigned int i = 0; i < count; i++)
		{
			object->objects[i]->MoveTo(position);
		}
	}

	// FUNCTION: ENGINE 0x10445600
	const core::Name<core::CaseSensitiveKey>& VehicleBehaviourAmbient::GetName()
	{
		return name;
	}

	static inline bool IsNearZero(float value)
	{
		return fabs(value) <= 0.05f;
	}

	// FUNCTION: ENGINE 0x10445A10
	// EQUIVALENT: the same test of the steering angle against 0.05 and the same answer; the engine builds the answer
	// of the inline test in eax and negates it with test / sete al, ours negates through cl, 58 %
	bool VehicleBehaviourAmbient::Unknown10445A10()
	{
		return !IsNearZero(turningAngle);
	}

	// FUNCTION: ENGINE 0x10445A40
	float VehicleBehaviourAmbient::Unknown10445A40(float squaredSpeed)
	{
		return squaredSpeed / (unknownF8 + unknownF8);
	}

	// FUNCTION: ENGINE 0x10445A60
	float VehicleBehaviourAmbient::Unknown10445A60(float speedValue)
	{
		return Unknown10445A40(speedValue * speedValue);
	}

	// FUNCTION: ENGINE 0x10445C20
	int PartLookup::FindPart(const char* name)
	{
		return FindPart(core::Name<core::CaseSensitiveKey>(name, 1));
	}

	// The query for the level of detail the car is drawn at (RTTI: proto::GetRenderLODIndex; type 0x3D, id 9; the
	// answer, zero when the car has a drawable of its own, comes back in the message)
	struct GetRenderLODIndex : public engine::IntrusiveMessage
	{
		GetRenderLODIndex() : engine::IntrusiveMessage(0x3d, 9)
		{
			index = 0;
		}
		virtual ~GetRenderLODIndex()
		{
		}

		int index;
	};

	// The message that makes the drawable pick its level of detail again (RTTI: proto::ForceLODUpdateMessage; type 0x3D,
	// id 0xA)
	struct ForceLODUpdateMessage : public engine::IntrusiveMessage
	{
		ForceLODUpdateMessage() : engine::IntrusiveMessage(0x3d, 0xa)
		{
		}
		virtual ~ForceLODUpdateMessage()
		{
		}
	};

	// -1, 0 or 1 by the sign of the number (0x1006FBA0; the engine calls its own copy of it)
	extern float Sign(float value);
	// The smaller of two numbers (0x10071300)
	extern float Min(float a, float b);

	// The probe distance the car's placement test is given (0x1108CB14, all ones)
	int sPlacementProbe = -1;

	// The chances a lane change is tried with, by the car's random number below three (0x10E04E70 and 0x10E04E7C)
	extern const float sSecondChances[3] = {4.5f, 5.0f, 5.5f};
	extern const float sFirstChances[3] = {6.0f, 6.0f, 6.0f};

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

	// FUNCTION: ENGINE 0x1044BBC0
	void VehicleBehaviourAmbient::Slot9(int state)
	{
		if (unknownA4 == state)
		{
			return;
		}
		if (state == 0)
		{
			if (!halted)
			{
				engine::GetPhysicsObjectMessage query;
				owner->PostMessage(&query);
				if (query.handle.IsValid())
				{
					if ((query.handle.GetObject()->collisionMode & 3) != 1)
					{
						return;
					}
				}
			}
			StopSimulation();
			UpdateNodeDistance();
			engine::PhysicsSetEnabledMessage message(false);
			owner->SendMessage(&message);
		}
		else
		{
			if (state == 2)
			{
				math::Matrix& matrix = owner->transform->value;
				math::Vector row(matrix.m[2][0], matrix.m[2][1], matrix.m[2][2]);
				math::Vector forward = -row;
				math::Matrix& placement = owner->transform->value;
				math::Vector position(placement.m[3][0], placement.m[3][1], placement.m[3][2]);
				char probe[0x3c];
				Unknown104416E0(&position, &forward, &extents, probe);
				if (!Unknown10441B30(owner, probe, &sPlacementProbe))
				{
					unknown9D = true;
					return;
				}
				Unknown10446810();
				engine::PhysicsSetEnabledMessage message(true);
				owner->SendMessage(&message);
			}
		}
		unknownA4 = state;
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

	// FUNCTION: ENGINE 0x1044CEA0
	// EQUIVALENT: the same two draws of the generator (the state words are read, stepped and written in the same
	// order), spreads and stores in the same order; the engine keeps the address of the second state word in esi and
	// uses edi for the steps where ours uses esi alone, and its temporary for the mantissa sits four bytes higher,
	// 59 %
	void VehicleBehaviourAmbient::Unknown1044CEA0()
	{
		unknown17C = 0.4f;
		float speedSpread = ((float)unknown174 + 1.0f) * 5.0f;
		unknownF0 = math::gRandom->NextFloat01() * speedSpread + vehicleProperties->maxSpeed;
		float accelerationSpread = (float)unknown174 * 0.5f;
		unknownF4 = math::gRandom->NextFloat01() * accelerationSpread + vehicleProperties->accelerationForce;
		unknownF8 = vehicleProperties->brakingForce;
		unknownA8 = 0.0f;
		SetParked(false);
	}

	// The registry that maps a name of a car to the target the cars aim at (the global at 0x11267730)
	class TargetRegistry
	{
	public:
		// 0x104085B0
		unsigned int* Find(unsigned int* result, const void* key);
	};
	extern TargetRegistry* gTargetRegistry;
	// The name of the cars that are parked for good (0x112691D0)
	extern core::Name<core::CaseSensitiveKey> gParkedCarName;

	// FUNCTION: ENGINE 0x1044C220
	void VehicleBehaviourAmbient::OnCollision(CollisionMessage* message)
	{
		if (mode != 1 && !(name == gParkedCarName))
		{
			switch (message->surface)
			{
			case 1:
			case 2:
			case 4:
			case 6:
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 0x13:
				if (!(math::gRandom->Range(0.0f, 1.0f) < 0.6f))
				{
					SetParked(true);
					unsigned int target;
					SetTargetMessage notice(*gTargetRegistry->Find(&target, (char*)message + 0xc));
					owner->SendMessage(&notice);
				}
				break;
			}
		}
	}

	// FUNCTION: ENGINE 0x1044D0F0
	// EQUIVALENT: the same tests, handle selection, calls and results in the same order and the same layout of the two
	// branches; the engine widens the index before it loads the handle table and keeps the owner link and the lane
	// count in eax where ours uses edx and ecx, 70 %
	void VehicleBehaviourAmbient::UpdateLaneChange()
	{
		if (unknown74->state == 1)
		{
			PathNode* first = path88.At(0);
			unsigned short owner = first->areaLink->owner;
			engine::GameObjectHandle handle = (owner != 0xffff) ? gNavMesh->handles[owner] : engine::GameObjectHandle();
			if (Unknown10431520(&handle, first->link->GetLaneCount()) == 0.0f)
			{
				unknown170 = Unknown1044C340(sSecondChances[0]);
			}
			else
			{
				unknown170 = Unknown1044C340(1.0f);
			}
			return;
		}
		unknown170 = Unknown1044C340(sSecondChances[0]);
	}

	// FUNCTION: ENGINE 0x1044D200
	// NONMATCHING: the tests, the stopping distance, the slide, the lane change tries, the waiting query and the horn
	// choice are the engine's in the same order; the audio message class declares its destructor out of line so ours
	// calls it and keeps one message object per branch (frame of 0xb8 bytes against the engine's 0x78), and the engine
	// shares the tail that sends the message, 46 %
#ifdef NONMATCHING
	void VehicleBehaviourAmbient::Unknown1044D200(float dt)
	{
		engine::GameObjectEntry& entry = engine::GetGameObjectEntries()[blockerHandle.index];
		if (blockerHandle.index == 0xffff || entry.serial != blockerHandle.serial || entry.object == 0)
		{
			unknown13C = 0.0f;
			unknown170 = false;
			return;
		}
		engine::GameObject* blocker = entry.object;
		engine::GetPhysicsObjectMessage query;
		blocker->PostMessage(&query);
		if (!query.handle.IsValid())
		{
			blockerHandle = engine::GameObjectHandle();
			return;
		}
		ravenphysics::PhysicsObject* blockerObject = query.handle.GetObject();
		float relativeSquared;
		if ((blockerObject->collisionMode & 3) != 0)
		{
			math::Vector* blockerVelocity = blockerObject->objects[0]->GetUnknown10();
			math::Vector relative(unknown110.x * speed - blockerVelocity->x, unknown110.y * speed - blockerVelocity->y,
				unknown110.z * speed - blockerVelocity->z);
			relativeSquared = relative.Dot(relative);
		}
		else
		{
			relativeSquared = speed * speed;
		}
		float stoppingDistance = Unknown10445A40(relativeSquared);
		if (unknown180 - unknown178 * 5.0f > stoppingDistance)
		{
			return;
		}
		if (!Unknown1044B2A0(blocker, stoppingDistance))
		{
			mode = 2;
			ApplyMode();
			engine::AudioEmitterTriggerMessage skid(core::Name<core::CaseSensitiveKey>("car_skids", 1), engine::gAudioPlay,
				4.0f, 0.0f, 0.0f, 1.0f, 1.0f, false, 0);
			owner->SendMessage(&skid);
			return;
		}
		if (!unknown170 && speed >= vehicleProperties->maxSpeed * 0.1f && !Unknown10445A10() && !Unknown10442200()
			&& unknown13C < 0.00001f)
		{
			unknown170 = Unknown1044C340(sFirstChances[unknown174]);
		}
		unknown13C = unknown13C + dt;
		if (!(unknown13C > 2.0f))
		{
			return;
		}
		unknown170 = Unknown1044C340(sSecondChances[unknown174]);
		if (unknown170)
		{
			unknown13C = 0.0f;
			return;
		}
		unknown13C = 0.1f;
		GetWaitingForObjectMessage waiting;
		blocker->SendMessage(&waiting);
		unknown134 = waiting.state;
		if (waiting.state == 1)
		{
			return;
		}
		if (!(math::gRandom->Range(0.0f, 1.0f) < 0.25f))
		{
			return;
		}
		core::Name<core::CaseSensitiveKey> model(GetName());
		core::Name<core::CaseSensitiveKey> horn;
		if (model == core::Name<core::CaseSensitiveKey>("nypd_suv", 1))
		{
			horn.SetText("police_horns");
		}
		else if (model == core::Name<core::CaseSensitiveKey>("nypd_police_car", 1))
		{
			horn.SetText("police_horns");
		}
		else if (model == core::Name<core::CaseSensitiveKey>("one_ton_delivery_truck", 1))
		{
			horn.SetText("truck_horns");
		}
		else if (model == core::Name<core::CaseSensitiveKey>("compact001", 1)
			|| model == core::Name<core::CaseSensitiveKey>("toyota_sienna_taxi", 1))
		{
			horn.SetText("smallcar_horns");
		}
		if (horn.IsEmpty())
		{
			return;
		}
		engine::AudioEmitterTriggerMessage trigger(horn, engine::gAudioPlay, 4.0f, 0.0f, 0.0f, 1.0f, 1.0f, false, 0);
		owner->SendMessage(&trigger);
	}
#endif

	// FUNCTION: ENGINE 0x1044D730
	// NONMATCHING: the passed-node search, the speed rules (stop at the light, brake for a car ahead, accelerate to 7)
	// and the move are the engine's; the engine keeps the car in esi, holds the three position components on the x87
	// stack through the search loop and reloads the stored distance for the loop test where ours keeps it in the x87
	// unit, 40 %
#ifdef NONMATCHING
	void VehicleBehaviourAmbient::Unknown1044D730(float dt)
	{
		if (unknown198 < 0.0f)
		{
			int count = path88.Count();
			if (count != 0)
			{
				math::Matrix& matrix = owner->transform->value;
				math::Vector position(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
				int passed = 1;
				int node = 2;
				do
				{
					if (count - 1 <= passed)
					{
						break;
					}
					PathNode* next = path88.At(node);
					passed++;
					node++;
					float dx = position.x - next->position.x;
					float dy = position.y - next->position.y;
					float dz = position.z - next->position.z;
					unknown198 = sqrt(dz * dz + dy * dy + dx * dx) - 1.0f;
				}
				while (unknown198 < 0.0f);
				Unknown10443290(passed);
			}
		}
		Unknown10442D60();
		if (path88.Count() < 3)
		{
			return;
		}
		if (Unknown10445A90(dt))
		{
			speed = 0.0f;
		}
		else if (IsVehicleAhead(unknown19C))
		{
			float slowed = speed - vehicleProperties->brakingForce * dt * 2.0f;
			speed = slowed;
			if (5.0f > slowed)
			{
				speed = 0.0f;
			}
		}
		else
		{
			float faster = vehicleProperties->accelerationForce * dt + speed;
			speed = faster;
			if (7.0f <= faster)
			{
				faster = 7.0f;
			}
			speed = faster;
		}
		if (speed > 0.00001f)
		{
			Unknown1044B480(dt, 1);
		}
	}
#endif

	// FUNCTION: ENGINE 0x1044E200
	bool VehicleBehaviourAmbient::Unknown1044E200(float dt)
	{
		VEHICLE_ASSERT_NOT_NAN(0xba2, "!math::IsNan( mDesiredFacing.x )", desiredFacing.x);
		VEHICLE_ASSERT_NOT_NAN(0xba3, "!math::IsNan( mDesiredFacing.y )", desiredFacing.y);
		VEHICLE_ASSERT_NOT_NAN(0xba4, "!math::IsNan( mDesiredFacing.z )", desiredFacing.z);
		VEHICLE_ASSERT_NOT_NAN(0xba6, "!math::IsNan( mTurningAngle )", turningAngle);
		Unknown10442D60();
		unsigned int count = path88.Count();
		if (count <= 3)
		{
			UpdateLaneChange();
			count = path88.Count();
			if (count <= 2)
			{
				speed = 0.0f;
				return false;
			}
		}
		int progress = -1;
		math::Vector from(math::kZeroVector.x, math::kZeroVector.y, math::kZeroVector.z);
		VEHICLE_ASSERT_NOT_NAN(0xbbd, "!math::IsNan( mDesiredFacing.x )", desiredFacing.x);
		VEHICLE_ASSERT_NOT_NAN(0xbbe, "!math::IsNan( mDesiredFacing.y )", desiredFacing.y);
		VEHICLE_ASSERT_NOT_NAN(0xbbf, "!math::IsNan( mDesiredFacing.z )", desiredFacing.z);
		VEHICLE_ASSERT_NOT_NAN(0xbc1, "!math::IsNan( mTurningAngle )", turningAngle);
		AimAhead(dt, &from, &progress);
		UpdateTurning();
		VEHICLE_ASSERT_NOT_NAN(0xbc9, "!math::IsNan( mDesiredFacing.x )", desiredFacing.x);
		VEHICLE_ASSERT_NOT_NAN(0xbca, "!math::IsNan( mDesiredFacing.y )", desiredFacing.y);
		VEHICLE_ASSERT_NOT_NAN(0xbcb, "!math::IsNan( mDesiredFacing.z )", desiredFacing.z);
		VEHICLE_ASSERT_NOT_NAN(0xbcd, "!math::IsNan( mTurningAngle )", turningAngle);
		PathNode* node = path88.At(progress);
		float dx = node->position.x - from.x;
		float dy = node->position.y - from.y;
		float dz = node->position.z - from.z;
		float distance = sqrt(dz * dz + dy * dy + dx * dx);
		UpdateGap(dt, progress, distance);
		Unknown1044D200(dt);
		UpdateTargetSpeed();
		Unknown10443290(progress);
		VEHICLE_ASSERT_NOT_NAN(0xbe4, "!math::IsNan( mDesiredFacing.x )", desiredFacing.x);
		VEHICLE_ASSERT_NOT_NAN(0xbe5, "!math::IsNan( mDesiredFacing.y )", desiredFacing.y);
		VEHICLE_ASSERT_NOT_NAN(0xbe6, "!math::IsNan( mDesiredFacing.z )", desiredFacing.z);
		VEHICLE_ASSERT_NOT_NAN(0xbe8, "!math::IsNan( mTurningAngle )", turningAngle);
		return true;
	}

	// FUNCTION: ENGINE 0x1044E960
	void VehicleBehaviourAmbient::Unknown1044E960(float dt)
	{
		if (simulated)
		{
			ravenphysics::PhysicsObject* object = physicsHandle.GetObjectUnchecked();
			object->SetTransform(owner->transform->value);
		}
		if (mode == 0)
		{
			if (!Unknown1044E200(dt))
			{
				return;
			}
		}
		else
		{
			VEHICLE_ASSERT_NOT_NAN(0xc06, "!math::IsNan( mDesiredFacing.x )", desiredFacing.x);
			VEHICLE_ASSERT_NOT_NAN(0xc07, "!math::IsNan( mDesiredFacing.y )", desiredFacing.y);
			VEHICLE_ASSERT_NOT_NAN(0xc08, "!math::IsNan( mDesiredFacing.z )", desiredFacing.z);
			VEHICLE_ASSERT_NOT_NAN(0xc0a, "!math::IsNan( mTurningAngle )", turningAngle);
			Unknown1044C040(dt);
			VEHICLE_ASSERT_NOT_NAN(0xc0c, "!math::IsNan( mDesiredFacing.x )", desiredFacing.x);
			VEHICLE_ASSERT_NOT_NAN(0xc0d, "!math::IsNan( mDesiredFacing.y )", desiredFacing.y);
			VEHICLE_ASSERT_NOT_NAN(0xc0e, "!math::IsNan( mDesiredFacing.z )", desiredFacing.z);
			VEHICLE_ASSERT_NOT_NAN(0xc10, "!math::IsNan( mTurningAngle )", turningAngle);
			engine::PhysicsWakeUpMessage message(false);
			owner->SendMessage(&message);
		}
		UpdateDrive(dt);
		Unknown10447280(dt);
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

	// FUNCTION: ENGINE 0x104473E0
	// EQUIVALENT: the same calls, tests and float operations in the same order; ours saves edi after the first test
	// instead of before it (the test's branch then lands on the epilogue's second instruction), 98 %
	bool VehicleBehaviourAmbient::UpdateGap(float dt, int node, float distance)
	{
		if (Unknown10442200())
		{
			unknownA8 = 0.0f;
			return false;
		}
		if (unknownA8 > 0.0f)
		{
			unknownA8 -= dt;
		}
		if (unknownA8 <= 0.0f)
		{
			int count = Unknown10442B20(path88.Count());
			if (count > 1)
			{
				float reach = Unknown10445A60(speed) + 5.0f;
				if (!(distance > reach))
				{
					float gap = Unknown10442BF0(node, count) + distance - extents.z;
					if (reach > gap)
					{
						unknownA8 = Unknown104435B0(count);
					}
				}
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10447D20
	// NONMATCHING: the same walk along the path (a segment is passed over until the distance fits into one) and the
	// same blend towards the facing, but the register allocation and the order of the stack copies of the start point
	// differ from the engine's, 52 %
#ifdef NONMATCHING
	math::Vector* VehicleBehaviourAmbient::PointAlongPath(math::Vector* result, const math::Vector* from, int node,
		float distance)
	{
		float fromX = from->x;
		float fromY = from->y;
		float fromZ = from->z;
		PathNode* last = path88.Back();
		result->x = last->position.x;
		result->y = last->position.y;
		result->z = last->position.z;
		int count = path88.Count();
		if (node < count)
		{
			float previousX = fromX;
			float previousY = fromY;
			float previousZ = fromZ;
			do
			{
				PathNode* current = path88.At(node);
				float x = current->position.x;
				float y = current->position.y;
				float z = current->position.z;
				math::Vector delta;
				delta.x = x - previousX;
				delta.y = y - previousY;
				delta.z = z - previousZ;
				float length = sqrt(delta.z * delta.z + delta.y * delta.y + delta.x * delta.x);
				if (distance < length)
				{
					float scale = distance / length;
					result->x = (x - previousX) * scale + previousX;
					result->y = (y - previousY) * scale + previousY;
					result->z = (z - previousZ) * scale + previousZ;
					break;
				}
				distance -= length;
				node++;
				previousX = x;
				previousY = y;
				previousZ = z;
			}
			while (node < count);
		}
		math::Matrix& matrix = owner->transform->value;
		math::Vector forward(-matrix.m[2][0], -matrix.m[2][1], -matrix.m[2][2]);
		math::Vector toward(result->x - fromX, result->y - fromY, result->z - fromZ);
		toward.Normalize();
		if (toward.z * forward.z + toward.y * forward.y + toward.x * forward.x < 0.999f)
		{
			float blend = unknownD0 * 4.0f;
			float rest = -0.0f - blend;
			result->y = result->y + toward.y * blend + forward.y * rest;
			result->x = result->x + toward.x * blend + forward.x * rest;
			result->z = result->z + toward.z * blend + forward.z * rest;
		}
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x10448250
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

	// FUNCTION: ENGINE 0x10446700
	// EQUIVALENT: the same reads, products and tests in the same order; the engine loads the plane's normal components
	// into other registers (z and y swapped) and forms the pointer to the plane's offset before it reads it, 87 %
	bool VehicleBehaviourAmbient::Unknown10446700()
	{
		math::Matrix& matrix = owner->transform->value;
		math::Vector position(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
		math::Plane& plane = unknown74->plane;
		float height = plane.normal.x * position.x + plane.normal.z * position.z + plane.normal.y * position.y + plane.d;
		math::Vector onPlane(position.x - plane.normal.x * height, position.y - plane.normal.y * height,
			position.z - plane.normal.z * height);
		if (fabs(position.x - onPlane.x) <= 0.2f && fabs(position.y - onPlane.y) <= 0.2f && fabs(position.z - onPlane.z) <= 0.2f)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10446890
	bool VehicleBehaviourAmbient::Unknown10446890()
	{
		math::Matrix& matrix = owner->transform->value;
		math::Vector up(matrix.m[1][0], matrix.m[1][1], matrix.m[1][2]);
		float alignment = up.Dot(unknown74->plane.normal);
		if (fabs(alignment - 1.0f) <= 0.001f)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x104468F0
	void VehicleBehaviourAmbient::UpdateSpeed(float dt)
	{
		float acceleration = unknownF4 * dt;
		float velocity = speed;
		float slowdown = 1.0f - fabs(speed) / vehicleProperties->maxSpeed;
		float factor = (0.5f < slowdown) ? slowdown : 0.5f;
		float driveStep = factor * acceleration;
		float difference = targetSpeed - velocity;
		float step = (difference <= 0.0f && 0.0f < velocity) ? unknownF8 * dt : driveStep;
		float direction;
		if (difference < 0.0f)
		{
			direction = -1.0f;
		}
		else
		{
			direction = 0.0f;
			if (difference > 0.0f)
			{
				direction = 1.0f;
			}
		}
		float magnitude = fabs(difference);
		speed = ((magnitude < step) ? magnitude : step) * direction + velocity;
		if (speed < 0.00001f && unknown170)
		{
			speed = 1.9f;
		}
	}

	// FUNCTION: ENGINE 0x10447280
	// NONMATCHING: the same box (offsets and half extents of the two modes, the identity axes) and the same stores in
	// the same order, but the engine keeps the zero in xmm3, loads the one in each branch and has a larger frame (0x58
	// against 0x40), 12 %
#ifdef NONMATCHING
	void VehicleBehaviourAmbient::Unknown10447280(float unused)
	{
		float height = extents.y;
		float centreX = 0.0f;
		float centreY = height;
		float centreZ = 0.0f;
		float halfX;
		float halfY;
		float halfZ;
		if (mode == 0)
		{
			halfX = extents.x;
			halfZ = fabs(speed) + extents.z;
			centreX = halfX - halfX;
			centreY = height - height;
			centreZ = (extents.z - halfZ) + 1.0f;
			halfY = height;
		}
		else
		{
			halfX = extents.x;
			halfY = height * 0.7f;
			centreY = height + 0.25f;
			halfZ = extents.z + 1.0f;
		}
		math::OBB box;
		box.centre.Set(centreX, centreY, centreZ);
		box.extents.Set(halfX, halfY, halfZ);
		box.axis[0].Set(1.0f, 0.0f, 0.0f);
		box.axis[1].Set(0.0f, 1.0f, 0.0f);
		box.axis[2].Set(0.0f, 0.0f, 1.0f);
		ravenphysics::PhysicsObject* object = physicsHandle.GetObjectUnchecked();
		object->SetBox(box, owner->transform->value);
	}
#endif

	// FUNCTION: ENGINE 0x1044D020
	void VehicleBehaviourAmbient::UpdateDrive(float dt)
	{
		engine::GetPhysicsObjectMessage query;
		owner->PostMessage(&query);
		if (query.handle.IsValid())
		{
			ravenphysics::PhysicsObject* object = query.handle.GetObject();
			UpdateSpeed(dt);
			Unknown1044A580(dt, object);
			Unknown1044ABD0(dt);
		}
	}

	// FUNCTION: ENGINE 0x10445960
	float VehicleBehaviourAmbient::Unknown10445960()
	{
		float rate = speed / (unknownD0 * 1.5f);
		return rate * turningAngle;
	}

	// FUNCTION: ENGINE 0x104470A0
	void VehicleBehaviourAmbient::Unknown104470A0(math::Vector* forward, const math::Vector* axis, float dt)
	{
		math::Quaternion rotation;
		math::Vector reversed;
		if (mode != 2)
		{
			if (!(fabs(turningAngle) <= 0.00001f))
			{
				rotation.FromAxisAngle(Unknown10445960() * dt, *axis);
				rotation.Transform(*forward, *forward);
			}
			math::Vector negated(-forward->x, -forward->y, -forward->z);
			unknown110.x = negated.x;
			unknown110.y = negated.y;
			unknown110.z = negated.z;
			return;
		}
		if (!(fabs(turningAngle) <= 0.00001f))
		{
			rotation.FromAxisAngle(Unknown10445960() * dt, *axis);
			rotation.Transform(*forward, *forward);
		}
		reversed.x = -forward->x;
		reversed.y = -forward->y;
		reversed.z = -forward->z;
		float reversedHeading = choreo::Heading(reversed);
		float currentHeading = choreo::Heading(unknown110);
		float difference = choreo::AngleDifference(currentHeading, reversedHeading);
		rotation.FromAxisAngle(difference * unknown17C * dt, *axis);
		rotation.Transform(unknown110, unknown110);
		math::Vector facing(forward->x * -1.0f, forward->y * -1.0f, forward->z * -1.0f);
		desiredFacing.x = facing.x;
		desiredFacing.y = facing.y;
		desiredFacing.z = facing.z;
	}

	// The game object of a player, null when there is none (0x10099560 keeps a copy)
	inline engine::GameObject* GetPlayer(int index)
	{
		engine::GameObjectHandle handle = (index >= 0 && index < engine::controller::InputSystem::Get()->GetPlayerCount())
			? gPlayerHandles[index] : engine::GameObjectHandle();
		return handle.Get();
	}

	// FUNCTION: ENGINE 0x104485E0
	// EQUIVALENT: the same calls, tests and float operations in the same order; the handle of the player is picked by
	// a pointer to either the constructed empty handle or the global (the engine copies the global into the temporary)
	// and the loads of the two positions are scheduled differently, 66 %
	bool VehicleBehaviourAmbient::Unknown104485E0()
	{
		if (unknownA4 == 2)
		{
			engine::GameObject* playerObject = GetPlayer(0);
			if (playerObject != 0)
			{
				math::Matrix& own = owner->transform->value;
				math::Vector position(own.m[3][0], own.m[3][1], own.m[3][2]);
				math::Matrix& other = playerObject->transform->value;
				float dx = other.m[3][0] - position.x;
				float dy = other.m[3][1] - position.y;
				float dz = other.m[3][2] - position.z;
				if (dz * dz + dy * dy + dx * dx < 16.0f)
				{
					return false;
				}
			}
			engine::GetPhysicsObjectMessage query;
			owner->PostMessage(&query);
			if (query.handle.IsValid())
			{
				ravenphysics::PhysicsObject* object = query.handle.GetObject();
				if (object != 0 && (object->collisionMode & 3) == 1)
				{
					Unknown10445790();
					return true;
				}
			}
		}
		else if (unknownA4 == 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1044C040
	// EQUIVALENT: the same calls with the same arguments in the same order, the same tests and stores; the engine
	// keeps the branch, the slot's address and the parameters in ebx, edi and ebp where ours uses edi, ebp and ebx,
	// and forms the address of the virtual slot before it loads it, 85 %
	void VehicleBehaviourAmbient::Unknown1044C040(float dt)
	{
		NavArea* area = 0;
		math::Matrix& matrix = owner->transform->value;
		math::Vector position(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
		NavMesh* mesh = gAmbientManager->unknown20C;
		math::Vector closest;
		if (!mesh->Find(&position, 4.0f, 4.0f, &area, &closest, core::BitField<unsigned short>()))
		{
			ReleasePhysics();
		}
		if (area != unknown74)
		{
			unknown74->RemoveVehicle(this);
			unknown74 = area;
			area->AddVehicle(this);
		}
		core::HeapScope scope(0x75);
		if (branch != 0)
		{
			if (!sequencer.Unknown105A45A0(true))
			{
				engine::GameObjectParams* currentParams = GetParams();
				fight::Branch* current = branch;
				fight::Branch* action = current->Slot10(GetSequencer(), currentParams, 0, 0);
				if (action != 0)
				{
					action->Slot11(&sequencer, currentParams, 0);
				}
			}
		}
		sequencer.Advance(1, dt);
		sequencer.Update(0);
		sequencer.Unknown105A4910(true);
	}

	// FUNCTION: ENGINE 0x1044B480
	// NONMATCHING: the projection onto the area's plane, the unit direction to the path node, the step along it and
	// the rebuilt orientation and position of the car are the engine's arithmetic; the engine loads the matrix and
	// plane components in a different order, keeps three of them on the stack and uses a larger frame (0x48), 24 %
#ifdef NONMATCHING
	void VehicleBehaviourAmbient::Unknown1044B480(float dt, int node)
	{
		math::Matrix& matrix = owner->transform->value;
		NavArea* area = unknown74;
		float height = area->plane.normal.x * matrix.m[3][0] + area->plane.normal.y * matrix.m[3][1] + area->plane.normal.z * matrix.m[3][2] + area->plane.d;
		int first = path88.arrayEnd - path88.begin;
		float flatY = matrix.m[3][1] - area->plane.normal.y * height;
		float flatZ = matrix.m[3][2] - area->plane.normal.z * height;
		float flatX = matrix.m[3][0] - area->plane.normal.x * height;
		PathNode* target = path88.At(node);
		math::Vector toTarget(flatX - target->position.x, flatY - target->position.y, flatZ - target->position.z);
		float distance = toTarget.Normalize();
		unknown198 = distance - 1.0f;
		if (0.0f <= distance - 1.0f)
		{
			math::Vector normal(unknown74->plane.normal.x, unknown74->plane.normal.y, unknown74->plane.normal.z);
			math::Vector right(toTarget.z * normal.y - toTarget.y * normal.z, toTarget.x * normal.z - toTarget.z * normal.x,
				toTarget.y * normal.x - toTarget.x * normal.y);
			right.NormalizeFast();
			float step = -0.0f - speed * dt;
			unknown198 = unknown198 + step;
			float newY = (toTarget.y * step + flatY) - 0.15f;
			math::Matrix& result = owner->transform->Get();
			result.m[0][0] = right.x;
			result.m[0][1] = right.y;
			result.m[0][2] = right.z;
			result.m[0][3] = 0.0f;
			result.m[1][0] = normal.x;
			result.m[1][1] = normal.y;
			result.m[1][2] = normal.z;
			result.m[1][3] = 0.0f;
			result.m[2][0] = right.y * normal.z - right.z * normal.y;
			result.m[2][1] = right.z * normal.x - right.x * normal.z;
			result.m[2][2] = right.x * normal.y - right.y * normal.x;
			result.m[2][3] = 0.0f;
			result.m[3][0] = toTarget.x * step + flatX;
			result.m[3][1] = newY;
			result.m[3][2] = toTarget.z * step + flatZ;
			result.m[3][3] = 1.0f;
		}
	}
#endif

	// FUNCTION: ENGINE 0x1044B2A0
	// NONMATCHING: the same tests, messages, calls and results in the same order, but the engine reuses the dead slot
	// of the float parameter for the attribute pointer and the area and so has a frame of 0x34 bytes where ours needs
	// 0x40, 56 %
#ifdef NONMATCHING
	bool VehicleBehaviourAmbient::Unknown1044B2A0(engine::GameObject* other, float value)
	{
		if (!unknown170 && value > unknown180 && speed > 0.5f && !unknown138)
		{
			GetStateMessage query;
			other->SendMessage(&query);
			if (query.state != 0)
			{
				engine::AttributePtr<StateOwner*> attribute = other->GetAttributePtr<StateOwner*>(gStateAttributeName);
				StateOwner** slot = attribute.value;
				if (slot != 0 && *slot != 0)
				{
					int state = (*slot)->GetState();
					if (state != 4 && state != 6)
					{
						return true;
					}
					return false;
				}
				if (other == GetPlayer(0))
				{
					GetMotionStateMsg motion;
					other->SendMessage(&motion);
					if (motion.state == 0)
					{
						return true;
					}
					return motion.state == 1;
				}
				math::Matrix& matrix = other->transform->value;
				math::Vector position(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
				NavArea* area = 0;
				math::Vector closest;
				NavMesh* mesh = gAmbientManager->unknown20C;
				if (!mesh->Find(&position, 4.0f, 4.0f, &area, &closest, core::BitField<unsigned short>()))
				{
					return true;
				}
				return !area->Unknown10567FE0();
			}
		}
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x10446A70
	void VehicleBehaviourAmbient::UpdateTurning()
	{
		math::Matrix& matrix = owner->transform->value;
		math::Vector row(matrix.m[2][0], matrix.m[2][1], matrix.m[2][2]);
		math::Vector forward = -row;
		VEHICLE_ASSERT_NOT_NAN(0x97c, "!math::IsNan( forward.x )", forward.x);
		VEHICLE_ASSERT_NOT_NAN(0x97d, "!math::IsNan( forward.y )", forward.y);
		VEHICLE_ASSERT_NOT_NAN(0x97e, "!math::IsNan( forward.z )", forward.z);
		VEHICLE_ASSERT_NOT_NAN(0x980, "!math::IsNan( mDesiredFacing.x )", desiredFacing.x);
		VEHICLE_ASSERT_NOT_NAN(0x981, "!math::IsNan( mDesiredFacing.y )", desiredFacing.y);
		VEHICLE_ASSERT_NOT_NAN(0x982, "!math::IsNan( mDesiredFacing.z )", desiredFacing.z);
		VEHICLE_ASSERT_NOT_NAN(0x984, "!math::IsNan( mTurningAngle )", turningAngle);
		float currentWorldAngle = choreo::Heading(forward);
		float desiredWorldAngle = choreo::Heading(desiredFacing);
		VEHICLE_ASSERT_NOT_NAN(0x989, "!math::IsNan( currentWorldAngle )", currentWorldAngle);
		VEHICLE_ASSERT_NOT_NAN(0x98a, "!math::IsNan(desiredWorldAngle )", desiredWorldAngle);
		float arc = choreo::AngleDifference(currentWorldAngle, desiredWorldAngle);
		float desiredArcDirection = (arc < 0.0f) ? -1.0f : ((arc > 0.0f) ? 1.0f : 0.0f);
		VEHICLE_ASSERT_NOT_NAN(0x98f, "!math::IsNan( arc )", arc);
		VEHICLE_ASSERT_NOT_NAN(0x990, "!math::IsNan( desiredArcDirection )", desiredArcDirection);
		float absDesiredWheelAngle = Unknown10446A30(fabs(arc));
		float cappedAngle = (absDesiredWheelAngle < sMaxWheelAngle) ? absDesiredWheelAngle : sMaxWheelAngle;
		VEHICLE_ASSERT_NOT_NAN(0x995, "!math::IsNan( absDesiredWheelAngle )", absDesiredWheelAngle);
		VEHICLE_ASSERT_NOT_NAN(0x996, "!math::IsNan( cappedAngle )", cappedAngle);
		turningAngle = cappedAngle * desiredArcDirection;
		VEHICLE_ASSERT_NOT_NAN(0x99a, "!math::IsNan( mTurningAngle )", turningAngle);
	}

	// FUNCTION: ENGINE 0x1044ABD0
	// NONMATCHING: the loop over the three wheel pairs, the steering follow-up of the first pair and the rotations are
	// the engine's operation for operation, but the engine keeps the car in ebp and the wheel record in esi, forms the
	// record address once per pass, leaves the two flag updates of the pose as separate read-modify-write instructions
	// and has a frame of 0x6c bytes where ours needs 0x68, 41 %
#ifdef NONMATCHING
	void VehicleBehaviourAmbient::Unknown1044ABD0(float dt)
	{
		if (!(fabs(speed) <= 0.01f))
		{
			GetRenderLODIndex query;
			owner->SendMessage(&query);
			if (query.index == 0)
			{
				engine::BaseAttribute* attribute = owner->FindAttribute(gDrawableAttributeName);
				if (attribute != 0)
				{
					pure3d::Pose** slot = &static_cast<engine::Attribute<pure3d::Pose*>*>(attribute)->value;
					if (slot != 0)
					{
						pure3d::Pose* pose = *slot;
						float travelled = dt * speed;
						float spinStep = travelled / vehicleProperties->wheelRadius;
						math::Vector verticalAxis(0.0f, 1.0f, 0.0f);
						math::Vector axleAxis(1.0f, 0.0f, 0.0f);
						for (int i = 0; i < 3; i++)
						{
							Wheel& wheel = wheels[i];
							if (wheel.part1 > 0 && wheel.part1 != 0xffff && wheel.part2 > 0 && wheel.part2 != 0xffff)
							{
								wheel.spin = wheel.spin - spinStep;
								if (i == 0)
								{
									float previous = wheels[0].steer;
									float difference = turningAngle - previous;
									float direction = Sign(difference);
									wheels[0].steer = Min(dt * 3.14f, direction * difference) * direction + previous;
								}
								math::Quaternion steerRotation;
								math::Quaternion spinRotation;
								math::Quaternion rotation;
								steerRotation.FromAxisAngle(wheel.steer, verticalAxis);
								spinRotation.FromAxisAngle(wheel.spin, axleAxis);
								math::Multiply(rotation, steerRotation, spinRotation);
								pose->SetJointRotation(wheel.part1, &rotation);
								pose->SetJointRotation(wheel.part2, &rotation);
							}
						}
						pose->mData.mFlags |= 3;
						pose->mData.mFlags &= 0xfb;
						pose->Update();
					}
				}
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x1044A580
	// NONMATCHING: the arithmetic and the order of the calls follow the engine; the engine reads the three matrix rows
	// into registers before it stores them and keeps the local vectors in other stack slots, 55 %
#ifdef NONMATCHING
	void VehicleBehaviourAmbient::Unknown1044A580(float dt, ravenphysics::PhysicsObject* object)
	{
		float currentSpeed = speed;
		math::Vector velocity(unknown110.x * currentSpeed, unknown110.y * currentSpeed, unknown110.z * currentSpeed);
		math::Vector step(velocity.x * dt, velocity.y * dt, velocity.z * dt);
		if (!(fabs(sqrt(step.x * step.x + step.y * step.y + step.z * step.z)) <= 0.00001f))
		{
			math::Matrix& matrix = owner->transform->value;
			math::Vector up(matrix.m[1][0], matrix.m[1][1], matrix.m[1][2]);
			math::Vector forward(matrix.m[2][0], matrix.m[2][1], matrix.m[2][2]);
			math::Vector position(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
			Unknown104470A0(&forward, &up, dt);
			MovePhysicsObject(object, velocity);
			position.x = step.x + position.x;
			position.y = step.y + position.y;
			position.z = step.z + position.z;
			math::Vector newUp(up.x, up.y, up.z);
			Unknown10449680(&position, &newUp);
			float blend = dt * 5.0f;
			newUp.x = (newUp.x - up.x) * blend + up.x;
			newUp.y = (newUp.y - up.y) * blend + up.y;
			newUp.z = (newUp.z - up.z) * blend + up.z;
			newUp.Normalize();
			math::Vector right;
			right.Cross(newUp, forward);
			right.NormalizeFast();
			math::Vector newForward;
			newForward.Cross(right, newUp);
			math::Matrix result;
			result.m[0][0] = right.x;
			result.m[0][1] = right.y;
			result.m[0][2] = right.z;
			result.m[0][3] = 0.0f;
			result.m[1][0] = newUp.x;
			result.m[1][1] = newUp.y;
			result.m[1][2] = newUp.z;
			result.m[1][3] = 0.0f;
			result.m[2][0] = newForward.x;
			result.m[2][1] = newForward.y;
			result.m[2][2] = newForward.z;
			result.m[2][3] = 0.0f;
			result.m[3][0] = position.x;
			result.m[3][1] = position.y;
			result.m[3][2] = position.z;
			result.m[3][3] = 1.0f;
			owner->transform->Get() = result;
			ForceLODUpdateMessage message;
			owner->SendMessage(&message);
		}
	}
#endif

	// FUNCTION: ENGINE 0x1044AAB0
	void VehicleBehaviourAmbient::FindWheelParts()
	{
		if (wheels[0].part1 == 0xffff)
		{
			GetRenderLODIndex query;
			owner->SendMessage(&query);
			if (query.index == 0)
			{
				engine::BaseAttribute* attribute = owner->FindAttribute(gDrawableAttributeName);
				if (attribute != 0)
				{
					PartLookup** slot = &static_cast<engine::Attribute<PartLookup*>*>(attribute)->value;
					if (slot != 0)
					{
						PartLookup* drawable = *slot;
						if (drawable != 0)
						{
							wheels[0].part1 = drawable->FindPart("w1");
							wheels[0].part2 = drawable->FindPart("w2");
							wheels[1].part1 = drawable->FindPart("w3");
							wheels[1].part2 = drawable->FindPart("w4");
							wheels[2].part1 = drawable->FindPart("w5");
							wheels[2].part2 = drawable->FindPart("w6");
						}
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1044AE90
	// EQUIVALENT: the same calls, tests, float operations and stores in the same order; the engine keeps the second
	// path vector in the lowest of the three slots and the vector of the first leg in the middle one where ours swaps
	// them, and our zero store for the stopped case shares the epilogue of the early return, 84 %
	void VehicleBehaviourAmbient::UpdateTargetSpeed()
	{
		unknownF8 = vehicleProperties->brakingForce;
		float reach = Unknown10445A60(speed) * 0.5f;
		bool ahead = IsVehicleAhead(reach * reach + unknown19C);
		if (unknownA8 > 0.0f || unknown13C > 0.0f)
		{
			if (!ahead)
			{
				targetSpeed = 0.0f;
				return;
			}
		}
		else if (!ahead)
		{
			float maxSpeed = vehicleProperties->maxSpeed;
			targetSpeed = maxSpeed;
			if (unknown170)
			{
				targetSpeed = maxSpeed * 0.5f;
				return;
			}
			unsigned int count = path88.Count();
			if (count > 2)
			{
				PathNode* node = path88.At(0);
				math::Vector first(node->position.x, node->position.y, node->position.z);
				node = path88.At(1);
				math::Vector second(node->position.x, node->position.y, node->position.z);
				node = path88.At(2);
				math::Vector third(node->position.x, node->position.y, node->position.z);
				math::Vector toSecond(second.x - first.x, second.y - first.y, second.z - first.z);
				math::Vector toThird(third.x - second.x, third.y - second.y, third.z - second.z);
				toThird.Normalize();
				toSecond.Normalize();
				double alignment = toThird.z * toSecond.z + toThird.y * toSecond.y + toThird.x * toSecond.x;
				if (alignment < 0.6)
				{
					targetSpeed = vehicleProperties->maxSpeed * 0.5f;
				}
			}
			return;
		}
		unknownF8 = vehicleProperties->brakingForce * 4.0f;
		targetSpeed = 0.0f;
	}

	// FUNCTION: ENGINE 0x1044B110
	// EQUIVALENT: the same calls and float operations in the same order; the engine computes both coordinates of the
	// facing before it stores the first one, ours stores x before it works z out, 76 %
	void VehicleBehaviourAmbient::AimAhead(float dt, const math::Vector* from, int* progress)
	{
		math::Matrix& matrix = owner->transform->value;
		math::Vector position(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
		Unknown10442900(&position, path88.Count(), from, progress);
		math::Vector target;
		PointAlongPath(&target, from, *progress, 5.0f);
		float dx = target.x - position.x;
		float dz = target.z - position.z;
		desiredFacing.Set(dx, 0.0f, dz);
		desiredFacing.Normalize();
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

	// FUNCTION: ENGINE 0x10448440
	// EQUIVALENT: the same tests, the same walk of the path's areas, the same orientation and position and the same
	// call; the engine keeps the car in a stack slot (ebx is a scratch register inside the loop and it reloads the car
	// from the slot), the ring in esi and the loop count in edi where ours has the car in ebp and the ring in edi, and
	// it tests the car count against zero where ours tests against one, 54 %
	void VehicleBehaviourAmbient::CheckBlockedStop()
	{
		if (halted && mode != 1)
		{
			int count = path88.Count();
			for (int i = 0; i < count; i++)
			{
				NavArea* area = GetArea(path88.At(i));
				if (area->vehicleCount < 1)
				{
					math::Matrix& matrix = owner->transform->value;
					math::Vector row(matrix.m[2][0], matrix.m[2][1], matrix.m[2][2]);
					math::Vector forward = -row;
					math::Matrix& placement = owner->transform->value;
					math::Vector position(placement.m[3][0], placement.m[3][1], placement.m[3][2]);
					Unknown10443BD0(&position, &forward);
					if (path88.begin == path88.end)
					{
						unknown9C = true;
					}
					return;
				}
			}
		}
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
	bool VehicleBehaviourAmbient::UpdateNodeDistance()
	{
		unsigned int count = path88.Count();
		if (count > 1)
		{
			PathNode* node = path88.At(1);
			math::Matrix& matrix = owner->transform->value;
			math::Vector position(matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
			math::Vector difference(position.x - node->position.x, position.y - node->position.y, position.z - node->position.z);
			unknown198 = sqrt(difference.Dot(difference)) - 1.0f;
			return true;
		}
		unknown198 = -1.0f;
		return true;
	}
}
