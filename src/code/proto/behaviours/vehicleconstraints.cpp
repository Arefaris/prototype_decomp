#include "code/proto/behaviours/vehicleconstraints.h"
#include "code/core/refptr.h"

namespace content
{
	static const EnumValue sDoorSideValues[] =
	{
		{ "Left", 0 },
		{ "Right", 1 }
	};

	// FUNCTION: ENGINE 0x103075C0
	template<> void EnumInfo<proto::VehicleDoorProperties::DoorSide>::Get(const char** name, const EnumValue** values,
		int* count, const char** code)
	{
		*name = "proto::VehicleDoorProperties::DoorSide";
		*code = "p";
		*values = sDoorSideValues;
		*count = 2;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10307580
	content::ClassInfo* VehicleWheelSuspensionProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::VehicleWheelSuspensionProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10307600
	content::ClassInfo* VehicleDoorProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::VehicleDoorProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10307640
	content::ClassInfo* VehicleWheelList::LateralWheelGroup::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::VehicleWheelList::LateralWheelGroup";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10307680
	content::ClassInfo* VehicleWheelList::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::VehicleWheelList";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103076C0
	content::ClassInfo* VehicleDoorList::DoorGroup::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::VehicleDoorList::DoorGroup";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10307700
	content::ClassInfo* VehicleDoorList::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::VehicleDoorList";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10307740
	content::ClassInfo* VehicleMassProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::VehicleMassProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10307780
	content::ClassInfo* VehicleConstraintProperties::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::VehicleConstraintProperties";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1030B090
	content::MemberList* VehicleWheelSuspensionProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<VehicleWheelSuspensionProperties, float, 0>("p"),
				PROTO_OFFSET(VehicleWheelSuspensionProperties, maxSuspensionStretch), "maxSuspensionStretch" },
			{ content::GetMemberPrimitiveMetaType<VehicleWheelSuspensionProperties, float, 1>("p"),
				PROTO_OFFSET(VehicleWheelSuspensionProperties, maxSuspensionCompression), "maxSuspensionCompression" },
			{ content::GetMemberPrimitiveMetaType<VehicleWheelSuspensionProperties, float, 2>("p"),
				PROTO_OFFSET(VehicleWheelSuspensionProperties, dampingScale), "dampingScale" },
			{ content::GetMemberPrimitiveMetaType<VehicleWheelSuspensionProperties, float, 3>("p"),
				PROTO_OFFSET(VehicleWheelSuspensionProperties, suspensionOffsetStretch), "suspensionOffsetStretch" },
			{ content::GetMemberPrimitiveMetaType<VehicleWheelSuspensionProperties, float, 4>("p"),
				PROTO_OFFSET(VehicleWheelSuspensionProperties, rollingFrictionScale), "rollingFrictionScale" }
		};
		sList.members = sMembers;
		sList.count = 5;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10307A10
	float VehicleDoorProperties::GetDoorOpenAngle() const
	{
		return doorOpenAngle * 57.295776f;
	}

	// FUNCTION: ENGINE 0x10307A20
	void VehicleDoorProperties::SetDoorOpenAngle(float degrees)
	{
		doorOpenAngle = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x10307AF0
	float VehicleWheelList::GetMaxWheelTurnAngle() const
	{
		return maxWheelTurnAngle * 57.295776f;
	}

	// FUNCTION: ENGINE 0x10307B00
	void VehicleWheelList::SetMaxWheelTurnAngle(float degrees)
	{
		maxWheelTurnAngle = degrees * 0.017453292f;
	}

	// FUNCTION: ENGINE 0x10307550
	VehicleConstraintProperties* VehicleConstraintsBehaviour::GetSharedProperties() const
	{
		return sharedProperties;
	}

	// FUNCTION: ENGINE 0x1030BA00
	content::MemberList* VehicleDoorProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberMetaType<VehicleDoorProperties, float, 0>(&VehicleDoorProperties::GetDoorOpenAngle,
				&VehicleDoorProperties::SetDoorOpenAngle, "p"), 0, "doorOpenAngle" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1030BAA0
	content::MemberList* VehicleWheelList::LateralWheelGroup::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<LateralWheelGroup, VehicleWheelSuspensionProperties>("p"),
				PROTO_OFFSET(LateralWheelGroup, suspensionProperties), "suspensionProperties" },
			{ content::GetArrayDynamicMetaType<LateralWheelGroup, JointNameArray>(
				content::GetNameMetaType<LateralWheelGroup>(true, true, "p"), "p"),
				PROTO_OFFSET(LateralWheelGroup, joints), "joints" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1030BB90
	content::MemberList* VehicleDoorList::DoorGroup::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<DoorGroup, VehicleDoorProperties>("p"),
				PROTO_OFFSET(DoorGroup, doorProperties), "doorProperties" },
			{ content::GetEnumMetaType<VehicleDoorProperties::DoorSide>(), ((int)&((DoorGroup*)0)->doorSide),
				"doorSide" },
			{ content::GetArrayDynamicMetaType<DoorGroup, JointNameArray>(
				content::GetNameMetaType<DoorGroup>(true, true, "p"), "p"),
				PROTO_OFFSET(DoorGroup, joints), "joints" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1030BCA0
	content::MemberList* VehicleMassProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<ChassisMass, ravenphysics::MassProperties>("p"),
				PROTO_OFFSET(VehicleMassProperties, chassisMassProperties), "chassisMassProperties" },
			{ content::GetReferenceMetaType<WheelMass, ravenphysics::MassProperties>("p"),
				PROTO_OFFSET(VehicleMassProperties, wheelMassProperties), "wheelMassProperties" },
			{ content::GetReferenceMetaType<DoorMass, ravenphysics::MassProperties>("p"),
				PROTO_OFFSET(VehicleMassProperties, doorMassProperties), "doorMassProperties" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1030BDA0
	content::MemberList* VehicleConstraintsBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, VehicleConstraintsBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMemberMetaType<VehicleConstraintsBehaviour, VehicleConstraintProperties>(
				&VehicleConstraintsBehaviour::GetSharedProperties,
				&VehicleConstraintsBehaviour::SetSharedProperties, "p"), 0, "sharedProperties" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1030C450
	content::MemberList* VehicleWheelList::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberMetaType<VehicleWheelList, float, 0>(&VehicleWheelList::GetMaxWheelTurnAngle,
				&VehicleWheelList::SetMaxWheelTurnAngle, "p"), 0, "maxWheelTurnAngle" },
			{ content::GetClassMetaType<LateralWheelGroup>(), PROTO_OFFSET(VehicleWheelList, turningWheelGroup),
				"turningWheelGroup" },
			{ content::GetArrayDynamicMetaType<VehicleWheelList, GroupArray>(
				content::GetClassMetaType<LateralWheelGroup>(), "p"),
				PROTO_OFFSET(VehicleWheelList, nonTurningWheelGroups), "nonTurningWheelGroups" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1030C560
	content::MemberList* VehicleDoorList::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<VehicleDoorList, GroupArray>(
				content::GetClassMetaType<DoorGroup>(), "p"), PROTO_OFFSET(VehicleDoorList, doorGroups),
				"doorGroups" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1030CA50
	content::MemberList* VehicleConstraintProperties::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetReferenceMetaType<VehicleConstraintProperties, VehicleWheelList>("p"),
				PROTO_OFFSET(VehicleConstraintProperties, wheelListRef), "wheelListRef" },
			{ content::GetClassMetaType<VehicleDoorList>(), PROTO_OFFSET(VehicleConstraintProperties, doorList),
				"doorList" },
			{ content::GetNameMetaType<VehicleConstraintProperties>(true, true, "p"),
				PROTO_NAME_OFFSET(VehicleConstraintProperties, chassisJoint), "chassisJoint" },
			{ content::GetReferenceMetaType<VehicleConstraintProperties, VehicleMassProperties>("p"),
				PROTO_OFFSET(VehicleConstraintProperties, massType), "massType" }
		};
		sList.members = sMembers;
		sList.count = 4;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102EA1B0
// FUNCTION: ENGINE 0x102ECD00
// FUNCTION: ENGINE 0x10308480
// FUNCTION: ENGINE 0x103087F0
// FUNCTION: ENGINE 0x10308800
// FUNCTION: ENGINE 0x10308840
// FUNCTION: ENGINE 0x10308850
// FUNCTION: ENGINE 0x10308860
// FUNCTION: ENGINE 0x10308880
// FUNCTION: ENGINE 0x103088C0
// FUNCTION: ENGINE 0x103088E0
// FUNCTION: ENGINE 0x103088F0
// FUNCTION: ENGINE 0x10308900
// FUNCTION: ENGINE 0x10308940
// FUNCTION: ENGINE 0x1030A590
// FUNCTION: ENGINE 0x1030A5D0
// FUNCTION: ENGINE 0x1030A610
// FUNCTION: ENGINE 0x1030A650
// FUNCTION: ENGINE 0x1030A690
// FUNCTION: ENGINE 0x1030A980
// FUNCTION: ENGINE 0x1030AA20
// FUNCTION: ENGINE 0x1030AAC0
// FUNCTION: ENGINE 0x1030B000
// FUNCTION: ENGINE 0x1030B380
// FUNCTION: ENGINE 0x1030B400
// FUNCTION: ENGINE 0x1030B460
// FUNCTION: ENGINE 0x1030B4C0
// FUNCTION: ENGINE 0x1030B540
// FUNCTION: ENGINE 0x1030B5A0
// FUNCTION: ENGINE 0x1030B600
// FUNCTION: ENGINE 0x1030B660
// FUNCTION: ENGINE 0x1030B6C0
// FUNCTION: ENGINE 0x1030B720
// FUNCTION: ENGINE 0x1030B780
// FUNCTION: ENGINE 0x1030B7E0
// FUNCTION: ENGINE 0x1030B840
// FUNCTION: ENGINE 0x1030B8A0
// FUNCTION: ENGINE 0x1030C140
// FUNCTION: ENGINE 0x1030C1A0
// FUNCTION: ENGINE 0x1030C830
// FUNCTION: ENGINE 0x1030C950
// FUNCTION: ENGINE 0x1030C9A0
// FUNCTION: ENGINE 0x1030CE20
// FUNCTION: ENGINE 0x1030DDA0
// FUNCTION: ENGINE 0x1030DE00
// FUNCTION: ENGINE 0x1030E020
// FUNCTION: ENGINE 0x1030E160
// FUNCTION: ENGINE 0x10D82CE0
// FUNCTION: ENGINE 0x10D82CF0

// Kept copies (more template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103088D0
// FUNCTION: ENGINE 0x10308CA0
// FUNCTION: ENGINE 0x1030A8D0
// FUNCTION: ENGINE 0x1030A930
// FUNCTION: ENGINE 0x1030A960
// FUNCTION: ENGINE 0x1030AA80
// FUNCTION: ENGINE 0x1030ABB0
// FUNCTION: ENGINE 0x1030ABF0
// FUNCTION: ENGINE 0x1030AC30
// FUNCTION: ENGINE 0x1030AC70
// FUNCTION: ENGINE 0x1030ADC0
// FUNCTION: ENGINE 0x1030ADE0
// FUNCTION: ENGINE 0x1030AE20
// FUNCTION: ENGINE 0x1030AE40
// FUNCTION: ENGINE 0x1030AE60
// FUNCTION: ENGINE 0x1030AE80
// FUNCTION: ENGINE 0x1030AEB0
// FUNCTION: ENGINE 0x1030AEE0
// FUNCTION: ENGINE 0x1030AF00
// FUNCTION: ENGINE 0x1030AF20
// FUNCTION: ENGINE 0x1030AF70
// FUNCTION: ENGINE 0x1030AF90
// FUNCTION: ENGINE 0x1030DFA0
// FUNCTION: ENGINE 0x1030DFE0
// FUNCTION: ENGINE 0x1030E3C0
// FUNCTION: ENGINE 0x1030E430
// FUNCTION: ENGINE 0x1030E6B0
// FUNCTION: ENGINE 0x1030E790

// The engine's copies of every member of the arrays of wheel groups and of door groups
template class container::ArrayDynamic<proto::VehicleWheelList::LateralWheelGroup, container::AllocatorNew>;
template class container::ArrayDynamic<proto::VehicleDoorList::DoorGroup, container::AllocatorNew>;
// FUNCTION: ENGINE 0x103082E0
// FUNCTION: ENGINE 0x10308310
// FUNCTION: ENGINE 0x10308330
// FUNCTION: ENGINE 0x103083B0
// FUNCTION: ENGINE 0x10308540
// FUNCTION: ENGINE 0x103085C0
// FUNCTION: ENGINE 0x10308C90
// FUNCTION: ENGINE 0x1030A200
// FUNCTION: ENGINE 0x1030A210
// FUNCTION: ENGINE 0x1030A8C0
// FUNCTION: ENGINE 0x1030A900
// FUNCTION: ENGINE 0x1030A910
// FUNCTION: ENGINE 0x1030A9E0
// FUNCTION: ENGINE 0x1030AA00
// FUNCTION: ENGINE 0x1030AA70
// FUNCTION: ENGINE 0x1030AAB0
// FUNCTION: ENGINE 0x1030AB20
// FUNCTION: ENGINE 0x1030AB60
// FUNCTION: ENGINE 0x1030AB80
// FUNCTION: ENGINE 0x1030ABA0
// FUNCTION: ENGINE 0x1030ABE0
// FUNCTION: ENGINE 0x1030AC20
// FUNCTION: ENGINE 0x1030AC60
// FUNCTION: ENGINE 0x1030ADA0
// FUNCTION: ENGINE 0x1030AE00
// FUNCTION: ENGINE 0x1030AF50
// FUNCTION: ENGINE 0x1030C3F0
// FUNCTION: ENGINE 0x1030C420
// FUNCTION: ENGINE 0x1030C9F0
// FUNCTION: ENGINE 0x1030CA20
// FUNCTION: ENGINE 0x1030CD70
// FUNCTION: ENGINE 0x1030CDA0
// FUNCTION: ENGINE 0x1030CDD0
// FUNCTION: ENGINE 0x1030CE80
// FUNCTION: ENGINE 0x1030CEB0
// FUNCTION: ENGINE 0x1030D980
// FUNCTION: ENGINE 0x1030D990
// FUNCTION: ENGINE 0x1030DC00
// FUNCTION: ENGINE 0x1030DC30
// FUNCTION: ENGINE 0x1030DC60
// FUNCTION: ENGINE 0x1030DCA0
// FUNCTION: ENGINE 0x1030DCE0
// FUNCTION: ENGINE 0x1030DD40
// FUNCTION: ENGINE 0x1030DF20
// FUNCTION: ENGINE 0x1030DF60
// FUNCTION: ENGINE 0x1030E2A0
// FUNCTION: ENGINE 0x1030E2F0
// FUNCTION: ENGINE 0x1030E340
// FUNCTION: ENGINE 0x1030E380
// FUNCTION: ENGINE 0x1030E4A0
// FUNCTION: ENGINE 0x1030EA70
// FUNCTION: ENGINE 0x1030ED20
