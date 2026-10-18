// proto::VehicleBehaviourAmbient (path from the unit's own assert string: code\proto\ai\ambientmanager\behaviours\
// vehiclebehaviourambient.cpp). Only the two functions below are reconstructed; the rest of the unit (the reflected
// members, the update 0x1044F060, the message dispatch 0x1044F710 and the state machine) is not.
#include "code/proto/ai/ambientmanager/behaviours/vehiclebehaviourambient.h"

#include "code/engine/gameobject/gameobject.h"
#include "code/choreo/deltatransform.h"
#include "code/core/refptr.h"
#include "code/core/report.h"
#include "code/engine/physics/physicsmessages.h"
#include "code/math/random.h"
#include "code/ravenphysics/physicsobject.h"
#include "code/proto/ai/ambientmanager/ambientmanager.h"
#include "code/math/matrix.h"
#include <float.h>
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
		unsigned char unknown2C[0x38 - 0x2c];
		short vehicleCount;
		unsigned char unknown3A[0x40 - 0x3a];
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

	#define VEHICLEBEHAVIOURAMBIENT_FILE "..\\..\\..\\code\\proto\\ai\\ambientmanager\\behaviours\\vehiclebehaviourambient.cpp"
	// The unit's asserts of a number being a number: reported once (the flag next to the check), and the report may
	// switch itself off
	#define VEHICLE_ASSERT_NOT_NAN(line, text, value) 		{ 			static bool sReport = true; 			if (sReport && _isnan((double)(value)) 				&& core::Report(1, " oldassert ", VEHICLEBEHAVIOURAMBIENT_FILE, line, text, 0) == 3) 			{ 				sReport = false; 			} 		}

	// The widest angle a wheel is turned to (0x1108CB20, fifty degrees)
	static float sMaxWheelAngle = 0.87266463f;

	// The attribute of a game object that holds its drawable (the name at 0x112834C8) and the part lookup of the
	// drawable (0x106DD6D0, which forwards to a member at +0x10)
	extern content::ObjectName gDrawableAttributeName;
	struct PartLookup
	{
		int FindPart(const core::Name<core::CaseSensitiveKey>& name);
		// 0x10445C20: the part by its text
		int FindPart(const char* name);
	};

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

	// The probe distance the car's placement test is given (0x1108CB14, all ones)
	static int sPlacementProbe = -1;

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
	// NONMATCHING: the same two random draws, spreads and stores in the same order, but the engine's float schedule
	// and the registers of the inlined generator steps differ (it keeps the first conversion before the draw and the
	// generator pointer in esi), 40 %
#ifdef NONMATCHING
	void VehicleBehaviourAmbient::Unknown1044CEA0()
	{
		unknown17C = 0.4f;
		float speedRandom = math::gRandom->NextFloat01();
		float speedSpread = ((float)unknown174 + 1.0f) * 5.0f;
		unknownF0 = speedRandom * speedSpread + vehicleProperties->maxSpeed;
		float accelerationRandom = math::gRandom->NextFloat01();
		float accelerationSpread = (float)unknown174 * 0.5f;
		unknownF4 = accelerationRandom * accelerationSpread + vehicleProperties->accelerationForce;
		unknownF8 = vehicleProperties->brakingForce;
		unknownA8 = 0.0f;
		SetParked(false);
	}
#endif

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
	// NONMATCHING: the tests and the two chances are the engine's, but the engine reads the lane's record through
	// register conventions of its unit and compares the answer with zero on the x87 stack, 40 %
#ifdef NONMATCHING
	void VehicleBehaviourAmbient::UpdateLaneChange()
	{
		if (*(int*)((char*)unknown74 + 0x20) == 1)
		{
			PathNode* first = path88.At(0);
			unsigned short index = *(unsigned short*)((char*)first->areaLink + 2);
			engine::GameObjectHandle handle;
			if (index != 0xffff)
			{
				handle = ((engine::GameObjectHandle*)gNavMesh->areas)[index];
			}
			if (Unknown10431520(&handle, Unknown10567F60(first->link)) != 0.0f)
			{
				unknown170 = Unknown1044C340(1.0f);
				return;
			}
		}
		unknown170 = Unknown1044C340(4.5f);
	}
#endif

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
	// EQUIVALENT: the same calls, tests and float operations in the same order; ours reloads ecx before the fourth
	// callee (the engine's callees of the unit keep it) and saves edi after the first test instead of before it,
	// 76.9 %
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

	// FUNCTION: ENGINE 0x10446A70
	// NONMATCHING: the asserts and the arithmetic come out in the engine's order (the first block, the frame size and
	// every report block are identical), but the engine keeps the signed arc on the x87 stack through the
	// direction test and the assert and places two of the float locals four bytes lower, 72 %
#ifdef NONMATCHING
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
		float desiredArcDirection = -1.0f;
		if (arc >= 0.0f)
		{
			desiredArcDirection = 0.0f;
			if (arc > 0.0f)
			{
				desiredArcDirection = 1.0f;
			}
		}
		VEHICLE_ASSERT_NOT_NAN(0x98f, "!math::IsNan( arc )", arc);
		VEHICLE_ASSERT_NOT_NAN(0x990, "!math::IsNan( desiredArcDirection )", desiredArcDirection);
		float absDesiredWheelAngle = Unknown10446A30(fabs(arc));
		float cappedAngle = sMaxWheelAngle;
		if (absDesiredWheelAngle < sMaxWheelAngle)
		{
			cappedAngle = absDesiredWheelAngle;
		}
		VEHICLE_ASSERT_NOT_NAN(0x995, "!math::IsNan( absDesiredWheelAngle )", absDesiredWheelAngle);
		VEHICLE_ASSERT_NOT_NAN(0x996, "!math::IsNan( cappedAngle )", cappedAngle);
		turningAngle = cappedAngle * desiredArcDirection;
		VEHICLE_ASSERT_NOT_NAN(0x99a, "!math::IsNan( mTurningAngle )", turningAngle);
	}
#endif

	// FUNCTION: ENGINE 0x1044AAB0
	void VehicleBehaviourAmbient::FindWheelParts()
	{
		if (wheelPart1 == 0xffff)
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
							wheelPart1 = drawable->FindPart("w1");
							wheelPart2 = drawable->FindPart("w2");
							wheelPart3 = drawable->FindPart("w3");
							wheelPart4 = drawable->FindPart("w4");
							wheelPart5 = drawable->FindPart("w5");
							wheelPart6 = drawable->FindPart("w6");
						}
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1044B110
	// EQUIVALENT: the same calls and float operations in the same order; the engine computes both coordinates of the
	// facing before it stores the first one, ours stores x before it works z out, 76 %
	void VehicleBehaviourAmbient::AimAhead(int unused, const math::Vector* from, int* progress)
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
	// NONMATCHING: the same walk of the path and the same stop test, but the engine keeps this in ebx, the ring in esi
	// and its start in ebp where ours uses ecx and ebp, 41 %
#ifdef NONMATCHING
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
#endif

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
