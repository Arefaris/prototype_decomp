// The reflected classes of the wheel constraints of a helicopter's landing gear (RTTI and reflection names; unit
// 0x10312760 - 0x1031C200, no assert path names it, the file name is a guess): the parameters of a wheel's spring
// (proto::WheelConstraintParams) and the wheel itself (proto::WheelConstraint: the joint of the wheel, the joint it
// hangs on and its parameters). The reflected names are original, the rest is guessed; the reflection, the class infos
// and the accessors are reconstructed, the constructors are left to the engine.
#ifndef PROTO_BEHAVIOURS_WHEELCONSTRAINT_H
#define PROTO_BEHAVIOURS_WHEELCONSTRAINT_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/content/vectormetatype.h"
#include "code/core/name.h"
#include "code/math/vector.h"

namespace proto
{
	// The spring of one wheel (0x40 bytes)
	class WheelConstraintParams : public content::MetaLoadObject
	{
	public:
		WheelConstraintParams(); //@0x10313780
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		const math::Vector* GetMovementAxis() const;
		void SetMovementAxis(const math::Vector* axis);
		const math::Vector* GetRotationAxis() const;
		void SetRotationAxis(const math::Vector* axis);
		float GetDamping() const;
		void SetDamping(float value);
		float GetSpringConstant() const;
		void SetSpringConstant(float value);
		float GetOffset() const;
		void SetOffset(float value);
		float GetCompression() const;
		void SetCompression(float value);
		float GetStretch() const;
		void SetStretch(float value);
		float GetRollingFrictionForce() const;
		void SetRollingFrictionForce(float value);

		math::Vector movementAxis;  // +8
		math::Vector rotationAxis;  // +0x14
		float damping;  // +0x20
		float springConstant;  // +0x24
		float offset;  // +0x28
		float compression;  // +0x2C
		float stretch;  // +0x30
		float rollingFrictionForce;  // +0x34
		float rayLength;  // +0x38
		float rayOffset;  // +0x3C
	};

	// One wheel of the landing gear (0x70 bytes)
	class WheelConstraint
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown0[0x10];
		WheelConstraintParams* params;  // +0x10
		int unknown14;
		core::Name<core::CaseSensitiveKey> wheelJointName;  // +0x18
		unsigned char unknown20[8];
		core::Name<core::CaseSensitiveKey> parentJointName;  // +0x28
		unsigned char unknown30[0x40];
	};

	// The wheels of the landing gear (reflected as "array")
	class WheelWeightDistributionContainer
	{
	public:
		static content::ClassInfo* GetClassInfo();
	};
}

#endif
