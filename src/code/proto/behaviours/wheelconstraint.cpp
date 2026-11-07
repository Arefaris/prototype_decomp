#include "code/proto/behaviours/wheelconstraint.h"

namespace proto
{
#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x103126A0
	content::ClassInfo* WheelConstraintParams::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WheelConstraintParams";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x103126E0
	content::ClassInfo* WheelConstraint::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WheelConstraint";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10312720
	content::ClassInfo* WheelWeightDistributionContainer::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::WheelWeightDistributionContainer";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10312890
	void WheelConstraintParams::SetMovementAxis(const math::Vector* axis)
	{
		movementAxis.x = axis->x;
		movementAxis.y = axis->y;
		movementAxis.z = axis->z;
	}

	// FUNCTION: ENGINE 0x103128B0
	const math::Vector* WheelConstraintParams::GetMovementAxis() const
	{
		return &movementAxis;
	}

	// FUNCTION: ENGINE 0x103128C0
	void WheelConstraintParams::SetRotationAxis(const math::Vector* axis)
	{
		rotationAxis.x = axis->x;
		rotationAxis.y = axis->y;
		rotationAxis.z = axis->z;
	}

	// FUNCTION: ENGINE 0x103128E0
	const math::Vector* WheelConstraintParams::GetRotationAxis() const
	{
		return &rotationAxis;
	}

	// FUNCTION: ENGINE 0x103128F0
	void WheelConstraintParams::SetDamping(float value)
	{
		damping = value;
	}

	// FUNCTION: ENGINE 0x10312910
	float WheelConstraintParams::GetDamping() const
	{
		return damping;
	}

	// FUNCTION: ENGINE 0x10312920
	void WheelConstraintParams::SetSpringConstant(float value)
	{
		springConstant = value;
	}

	// FUNCTION: ENGINE 0x10312940
	float WheelConstraintParams::GetSpringConstant() const
	{
		return springConstant;
	}

	// FUNCTION: ENGINE 0x10312950
	void WheelConstraintParams::SetOffset(float value)
	{
		offset = value;
	}

	// FUNCTION: ENGINE 0x10312970
	float WheelConstraintParams::GetOffset() const
	{
		return offset;
	}

	// FUNCTION: ENGINE 0x10312980
	void WheelConstraintParams::SetCompression(float value)
	{
		compression = value;
	}

	// FUNCTION: ENGINE 0x103129A0
	float WheelConstraintParams::GetCompression() const
	{
		return compression;
	}

	// FUNCTION: ENGINE 0x103129B0
	void WheelConstraintParams::SetStretch(float value)
	{
		stretch = value;
	}

	// FUNCTION: ENGINE 0x103129D0
	float WheelConstraintParams::GetStretch() const
	{
		return stretch;
	}

	// FUNCTION: ENGINE 0x103129E0
	void WheelConstraintParams::SetRollingFrictionForce(float value)
	{
		rollingFrictionForce = value;
	}

	// FUNCTION: ENGINE 0x10312A00
	float WheelConstraintParams::GetRollingFrictionForce() const
	{
		return rollingFrictionForce;
	}

	// FUNCTION: ENGINE 0x1031A8C0
	content::MemberList* WheelConstraintParams::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberVectorMetaType<WheelConstraintParams, 0>(&WheelConstraintParams::GetMovementAxis,
				&WheelConstraintParams::SetMovementAxis, "p"), 0, "movementAxis" },
			{ content::GetMemberVectorMetaType<WheelConstraintParams, 1>(&WheelConstraintParams::GetRotationAxis,
				&WheelConstraintParams::SetRotationAxis, "p"), 0, "rotationAxis" },
			{ content::GetMemberMetaType<WheelConstraintParams, float, 0>(&WheelConstraintParams::GetDamping,
				&WheelConstraintParams::SetDamping, "p"), 0, "damping" },
			{ content::GetMemberMetaType<WheelConstraintParams, float, 1>(&WheelConstraintParams::GetSpringConstant,
				&WheelConstraintParams::SetSpringConstant, "p"), 0, "springConstant" },
			{ content::GetMemberMetaType<WheelConstraintParams, float, 2>(&WheelConstraintParams::GetOffset,
				&WheelConstraintParams::SetOffset, "p"), 0, "offset" },
			{ content::GetMemberMetaType<WheelConstraintParams, float, 3>(&WheelConstraintParams::GetCompression,
				&WheelConstraintParams::SetCompression, "p"), 0, "compression" },
			{ content::GetMemberMetaType<WheelConstraintParams, float, 4>(&WheelConstraintParams::GetStretch,
				&WheelConstraintParams::SetStretch, "p"), 0, "stretch" },
			{ content::GetMemberMetaType<WheelConstraintParams, float, 5>(
				&WheelConstraintParams::GetRollingFrictionForce, &WheelConstraintParams::SetRollingFrictionForce, "p"),
				0, "rollingFrictionForce" },
			{ content::GetMemberPrimitiveMetaType<WheelConstraintParams, float, 6>("p"),
				PROTO_OFFSET(WheelConstraintParams, rayLength), "rayLength" },
			{ content::GetMemberPrimitiveMetaType<WheelConstraintParams, float, 7>("p"),
				PROTO_OFFSET(WheelConstraintParams, rayOffset), "rayOffset" }
		};
		sList.members = sMembers;
		sList.count = 10;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1031AB30
	content::MemberList* WheelConstraint::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<WheelConstraint>(true, true, "p"),
				PROTO_NAME_OFFSET(WheelConstraint, wheelJointName), "wheelJointName" },
			{ content::GetMemberNameMetaType<WheelConstraint, 1>(true, true, "p"),
				PROTO_NAME_OFFSET(WheelConstraint, parentJointName), "parentJointName" },
			{ content::GetReferenceMetaType<WheelConstraint, WheelConstraintParams>("p"),
				PROTO_OFFSET(WheelConstraint, params), "params" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103134B0
// FUNCTION: ENGINE 0x103134F0
// FUNCTION: ENGINE 0x10313530
// FUNCTION: ENGINE 0x10316880
// FUNCTION: ENGINE 0x103168C0
// FUNCTION: ENGINE 0x1031A1A0
// FUNCTION: ENGINE 0x1031A220
// FUNCTION: ENGINE 0x1031A2A0
// FUNCTION: ENGINE 0x1031A320
// FUNCTION: ENGINE 0x1031A3A0
// FUNCTION: ENGINE 0x1031A420
// FUNCTION: ENGINE 0x1031A4A0
// FUNCTION: ENGINE 0x1031A520
// FUNCTION: ENGINE 0x1031A5A0

// Kept copies (more template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10316910
// FUNCTION: ENGINE 0x10316B80
// FUNCTION: ENGINE 0x10316BA0
// FUNCTION: ENGINE 0x10316BE0
// FUNCTION: ENGINE 0x10316C00
// FUNCTION: ENGINE 0x10316900
// FUNCTION: ENGINE 0x10316B60
// FUNCTION: ENGINE 0x10316BC0
