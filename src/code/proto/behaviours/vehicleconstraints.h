// The reflected classes of the vehicle constraints (RTTI and reflection names; unit 0x10307580 - 0x1030EBxx, no assert
// path names it, the file name is a guess): the properties of a vehicle's wheels and doors (proto::VehicleWheelSuspension-
// Properties, VehicleDoorProperties, VehicleWheelList with its lateral wheel groups, VehicleDoorList with its door groups,
// VehicleMassProperties, VehicleConstraintProperties) and the behaviour that makes the constraints from them
// (proto::VehicleConstraintsBehaviour). The reflected names are original, the rest is guessed. The reflection, the
// array helpers and the element operations are reconstructed; the constructors and the constraint code are left to the
// engine (declared with their addresses, mapped in symbols.txt).
#ifndef PROTO_BEHAVIOURS_VEHICLECONSTRAINTS_H
#define PROTO_BEHAVIOURS_VEHICLECONSTRAINTS_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/proto/arrayhelper.h"
#include "code/ravenphysics/massproperties.h"

namespace proto
{
	typedef container::ArrayDynamic<core::Name<core::CaseSensitiveKey>, container::AllocatorNew> JointNameArray;

	// The limits and damping of a wheel's suspension (0x1C bytes)
	class VehicleWheelSuspensionProperties : public content::MetaLoadObject
	{
	public:
		VehicleWheelSuspensionProperties(); //@0x10308D60
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		float maxSuspensionStretch;  // +8
		float maxSuspensionCompression;  // +0xC
		float dampingScale;  // +0x10
		float suspensionOffsetStretch;  // +0x14
		float rollingFrictionScale;  // +0x18
	};

	// How far a door opens, and on which side the vehicle it is (0xC bytes)
	class VehicleDoorProperties : public content::MetaLoadObject
	{
	public:
		enum DoorSide
		{
			DoorSideLeft,
			DoorSideRight
		};

		VehicleDoorProperties(); //@0x103090B0
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The angle is kept in radians and reflected in degrees
		float GetDoorOpenAngle() const;
		void SetDoorOpenAngle(float degrees);

		float doorOpenAngle;  // +8
	};

	// The wheels of a vehicle in groups (0x30 bytes)
	class VehicleWheelList : public content::MetaLoadObject
	{
	public:
		// The wheels that share one suspension (0x14 bytes)
		class LateralWheelGroup
		{
		public:
			LateralWheelGroup(); //@0x1030CB80
			LateralWheelGroup(const LateralWheelGroup& other)
				: suspensionProperties(other.suspensionProperties), joints(other.joints)
			{
			}
			LateralWheelGroup& operator=(const LateralWheelGroup& other)
			{
				suspensionProperties = other.suspensionProperties;
				joints = other.joints;
				return *this;
			}
			~LateralWheelGroup(); //@0x1030CBA0
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			VehicleWheelSuspensionProperties* suspensionProperties;  // +0
			JointNameArray joints;  // +4
			int unknown10;
		};

		typedef container::ArrayDynamic<LateralWheelGroup, container::AllocatorNew> GroupArray;

		VehicleWheelList(); //@0x1030E530
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The angle is kept in radians and reflected in degrees
		float GetMaxWheelTurnAngle() const;
		void SetMaxWheelTurnAngle(float degrees);

		LateralWheelGroup turningWheelGroup;  // +8
		GroupArray nonTurningWheelGroups;  // +0x1C
		int unknown28;
		float maxWheelTurnAngle;  // +0x2C
	};

	// The doors of a vehicle in groups
	class VehicleDoorList
	{
	public:
		// The doors that share one set of properties (0x18 bytes)
		class DoorGroup
		{
		public:
			DoorGroup(); //@0x1030CBD0
			DoorGroup(const DoorGroup& other)
				: doorProperties(other.doorProperties), doorSide(other.doorSide), joints(other.joints)
			{
			}
			DoorGroup& operator=(const DoorGroup& other)
			{
				doorProperties = other.doorProperties;
				doorSide = other.doorSide;
				joints = other.joints;
				return *this;
			}
			~DoorGroup(); //@0x1030CBF0
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			VehicleDoorProperties* doorProperties;  // +0
			VehicleDoorProperties::DoorSide doorSide;  // +4
			JointNameArray joints;  // +8
			int unknown14;
		};

		typedef container::ArrayDynamic<DoorGroup, container::AllocatorNew> GroupArray;

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		GroupArray doorGroups;  // +0
		unsigned char unknownC[8];
	};

	// The mass properties of the parts of a vehicle (0x14 bytes)
	class VehicleMassProperties : public content::MetaLoadObject
	{
	public:
		// Tell the three references' meta types apart (each has its own in the engine)
		struct ChassisMass
		{
		};
		struct WheelMass
		{
		};
		struct DoorMass
		{
		};

		VehicleMassProperties(); //@0x10309140
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		ravenphysics::MassProperties* chassisMassProperties;  // +8
		ravenphysics::MassProperties* wheelMassProperties;  // +0xC
		ravenphysics::MassProperties* doorMassProperties;  // +0x10
	};

	// What a vehicle's constraints are made from (0x30 bytes)
	class VehicleConstraintProperties : public content::MetaLoadObject
	{
	public:
		VehicleConstraintProperties(); //@0x1030E890
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		VehicleWheelList* wheelListRef;  // +8
		VehicleDoorList doorList;  // +0xC
		core::Name<core::CaseSensitiveKey> chassisJoint;  // +0x20
		int unknown28;
		VehicleMassProperties* massType;  // +0x2C
	};

	class VehicleConstraintsBehaviour : public engine::Behaviour
	{
	public:
		explicit VehicleConstraintsBehaviour(engine::GameObject* newOwner); //@0x10308260
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		VehicleConstraintProperties* GetSharedProperties() const;
		void SetSharedProperties(VehicleConstraintProperties* properties); //@0x1030A1C0

		VehicleConstraintProperties* sharedProperties;  // +0xC
		unsigned char unknown10[0x0C];
	};
}

namespace container
{
	template<> struct ArrayEraseInline<proto::VehicleWheelList::LateralWheelGroup>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::VehicleDoorList::DoorGroup>
	{
		enum
		{
			value = 0
		};
	};
}

PROTO_ARRAY_HELPER(proto::VehicleDoorList::DoorGroup)

#endif
