// choreo::DeltaTransform (code/choreo/src/deltatransform.cpp, path from the asserts; the unit runs from 0x1094C810 to
// the end of the assigned range). The transform it is built on (choreo::Transform) is the unit before this one and is
// only declared here. Names are guesses.
//
// The unit's static validation helpers (0x1094D9B0 - 0x1094DB40) and the two reports take their argument in a register
// the compiler of the original chose (eax for the vector, the quaternion and the float, esi for the two reports); our
// build of /O2 without link-time code generation puts the vector, the quaternion and the float one in ecx, so every
// function that calls them differs from the engine by that one byte. The matrix validation (0x1094DA40) keeps its
// argument in ecx like ours but the engine unrolls its sixteen comparisons where ours keeps the loop.
#include "code/choreo/deltatransform.h"
#include "code/core/debug.h"
#include "code/core/report.h"
#include <math.h>

namespace choreo
{
	// The file and the system name the unit's reports carry
	#define DELTATRANSFORM_FILE "..\\..\\..\\code\\choreo\\src\\deltatransform.cpp"
	#define DELTATRANSFORM_SYSTEM "Choreo  Pre "

	// The largest magnitude any number of an input may have; everything else is a number the transform cannot use
	static const float DELTATRANSFORM_LIMIT = 1e12f;

	// FUNCTION: ENGINE 0x1094D730
	// NONMATCHING: the engine takes the vector in esi, ours in ecx; 61 %
#ifdef NONMATCHING
	void ReportBadVector(const math::Vector& value)
	{
		static bool sReportHeader = true;
		if (sReportHeader)
		{
			if (core::Report(0, DELTATRANSFORM_SYSTEM, DELTATRANSFORM_FILE, 0x1B, 0, "Bad vector: ", 0) == 3)
			{
				sReportHeader = false;
			}
		}
		static bool sReportValues = true;
		if (sReportValues)
		{
			if (core::Report(0, DELTATRANSFORM_SYSTEM, DELTATRANSFORM_FILE, 0x1C, 0, "[ %f | %f | %f ]",
				value.x, value.y, value.z, 0) == 3)
			{
				sReportValues = false;
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x1094D7B0
	// NONMATCHING: as ReportBadVector; 60 %
#ifdef NONMATCHING
	void ReportBadQuaternion(const math::Quaternion& value)
	{
		static bool sReportHeader = true;
		if (sReportHeader)
		{
			if (core::Report(0, DELTATRANSFORM_SYSTEM, DELTATRANSFORM_FILE, 0x20, 0, "Bad quaternion: ", 0) == 3)
			{
				sReportHeader = false;
			}
		}
		static bool sReportValues = true;
		if (sReportValues)
		{
			if (core::Report(0, DELTATRANSFORM_SYSTEM, DELTATRANSFORM_FILE, 0x21, 0, "[ %f | %f | %f | %f ]",
				value.x, value.y, value.z, value.w, 0) == 3)
			{
				sReportValues = false;
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x1094D840
	// Reports a float the transform cannot use
	void ReportBadFloat(float value)
	{
		static bool sReport = true;
		if (sReport)
		{
			if (core::Report(0, DELTATRANSFORM_SYSTEM, DELTATRANSFORM_FILE, 0x25, 0, "Bad float %f", value, 0) == 3)
			{
				sReport = false;
			}
		}
	}

	// FUNCTION: ENGINE 0x1094D960
	// Whether the four numbers at value are all within the limit
	bool IsVectorValid(const float* value)
	{
		return DELTATRANSFORM_LIMIT > fabsf(value[0]) && DELTATRANSFORM_LIMIT > fabsf(value[1])
			&& DELTATRANSFORM_LIMIT > fabsf(value[2]) && DELTATRANSFORM_LIMIT > fabsf(value[3]);
	}

	// FUNCTION: ENGINE 0x1094D9B0
	// NONMATCHING: the engine takes the vector in eax and keeps it in esi across the report, ours in ecx; 24 %
#ifdef NONMATCHING
	static bool ValidateDeltaInput(const math::Vector& value)
	{
		if (DELTATRANSFORM_LIMIT > fabsf(value.x) && DELTATRANSFORM_LIMIT > fabsf(value.y)
			&& DELTATRANSFORM_LIMIT > fabsf(value.z))
		{
			return true;
		}
		ReportBadVector(value);
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x1094D9F0
	// NONMATCHING: as the vector one; 24 %
#ifdef NONMATCHING
	static bool ValidateDeltaInput(const math::Quaternion& value)
	{
		if (DELTATRANSFORM_LIMIT > fabsf(value.x) && DELTATRANSFORM_LIMIT > fabsf(value.y)
			&& DELTATRANSFORM_LIMIT > fabsf(value.z) && DELTATRANSFORM_LIMIT > fabsf(value.w))
		{
			return true;
		}
		ReportBadQuaternion(value);
		return false;
	}
#endif

	// The matrix validation is not annotated: it keeps its argument in ecx like ours, but the engine unrolls its
	// sixteen comparisons where ours keeps the loop, so it is not counted and the engine's copy at 0x1094DA40 stays
	static bool ValidateDeltaInput(const math::Matrix& value)
	{
		const float* element = &value.m[0][0];
		for (int i = 0; i < 16; i++)
		{
			float number = element[i];
			if (DELTATRANSFORM_LIMIT <= number || -DELTATRANSFORM_LIMIT >= number)
			{
				value.Print();
				return false;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x1094DB40
	// NONMATCHING: the engine takes the float in eax, ours in ecx; 24 %
#ifdef NONMATCHING
	static bool ValidateDeltaInput(float value)
	{
		if (DELTATRANSFORM_LIMIT <= fabsf(value))
		{
			ReportBadFloat(value);
			return false;
		}
		return true;
	}
#endif

	// FUNCTION: ENGINE 0x1094D880
	DeltaTransform::DeltaTransform()
	{
		mVelocity.Set(0.0f, 0.0f, 0.0f);
		mAngularVelocity.Set(0.0f, 0.0f, 0.0f);
		mHasVelocity = false;
		mHasAngularVelocity = false;
	}

	// FUNCTION: ENGINE 0x1094D920
	// NONMATCHING: the engine writes the components of each zero vector in the other order; 88 %
#ifdef NONMATCHING
	void DeltaTransform::Reset()
	{
		Transform::Reset();
		mAngularVelocity.Set(0.0f, 0.0f, 0.0f);
		mVelocity.Set(0.0f, 0.0f, 0.0f);
		mHasVelocity = false;
		mHasAngularVelocity = false;
	}
#endif

	// FUNCTION: ENGINE 0x1094DB70
	// NONMATCHING: the vector validation is called with its argument in eax in the engine, in ecx in ours; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetVelocity(const math::Vector& velocity)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x48, ValidateDeltaInput(velocity), "ValidateDeltaInput( velocity )", "");
		mVelocity.x = velocity.x;
		mVelocity.y = velocity.y;
		mVelocity.z = velocity.z;
		mHasVelocity = true;
	}
#endif

	// FUNCTION: ENGINE 0x1094DBE0
	// NONMATCHING: as SetVelocity; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetVelocity(const math::Vector& velocity, const math::Quaternion& invRootQuaternion)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x4E, ValidateDeltaInput(velocity), "ValidateDeltaInput( velocity )", "");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x4F, ValidateDeltaInput(invRootQuaternion),
			"ValidateDeltaInput( invRootQuaternion )", "");
		invRootQuaternion.Transform(velocity, mVelocity);
		mHasVelocity = true;
	}
#endif

	// FUNCTION: ENGINE 0x1094DC90
	// NONMATCHING: as SetVelocity; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetVelocity(const math::Vector& velocity, const math::Matrix& rootTransform)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x55, ValidateDeltaInput(velocity), "ValidateDeltaInput( velocity )", "");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x56, ValidateDeltaInput(rootTransform), "ValidateDeltaInput( rootTransform )",
			"");
		math::Matrix inverse = rootTransform;
		inverse.InvertOrthonormal();
		inverse.Rotate(velocity, mVelocity);
		mHasVelocity = true;
	}
#endif

	// FUNCTION: ENGINE 0x1094DD60
	// NONMATCHING: the angular delta is stored the same way as the linear one; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetAngularVelocity(const math::Vector& velocity)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x63, ValidateDeltaInput(velocity), "ValidateDeltaInput( velocity )", "");
		mAngularVelocity.x = velocity.x;
		mAngularVelocity.y = velocity.y;
		mAngularVelocity.z = velocity.z;
		mHasAngularVelocity = true;
	}
#endif

	// FUNCTION: ENGINE 0x1094DDD0
	// NONMATCHING: as SetVelocity; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetAngularVelocity(const math::Vector& velocity, const math::Quaternion& invRootQuaternion)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x69, ValidateDeltaInput(velocity), "ValidateDeltaInput( velocity )", "");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x6A, ValidateDeltaInput(invRootQuaternion),
			"ValidateDeltaInput( invRootQuaternion )", "");
		invRootQuaternion.Transform(velocity, mAngularVelocity);
		mHasAngularVelocity = true;
	}
#endif

	// FUNCTION: ENGINE 0x1094DE80
	// NONMATCHING: as SetVelocity; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetAngularVelocity(const math::Vector& velocity, const math::Matrix& rootTransform)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x70, ValidateDeltaInput(velocity), "ValidateDeltaInput( velocity )", "");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x71, ValidateDeltaInput(rootTransform), "ValidateDeltaInput( rootTransform )",
			"");
		math::Matrix inverse = rootTransform;
		inverse.InvertOrthonormal();
		inverse.Rotate(velocity, mAngularVelocity);
		mHasAngularVelocity = true;
	}
#endif

	// FUNCTION: ENGINE 0x1094DF50
	// The whole movement of the step as the matrix it ends on
	void DeltaTransform::SetDelta(const math::Matrix& deltaMatrix)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x7B, ValidateDeltaInput(deltaMatrix), "ValidateDeltaInput( deltaMatrix )", "");
		SetMatrix(deltaMatrix);
		mHasVelocity = false;
		mHasAngularVelocity = false;
	}

	// FUNCTION: ENGINE 0x1094DFB0
	// The delta between the two root matrices
	void DeltaTransform::SetDelta(const math::Matrix& newMatrix, const math::Matrix& oldMatrix)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x82, ValidateDeltaInput(newMatrix), "ValidateDeltaInput( newMatrix )", "");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x83, ValidateDeltaInput(oldMatrix), "ValidateDeltaInput( oldMatrix )", "");
		math::Matrix inverse;
		inverse = oldMatrix;
		inverse.InvertOrthonormal();
		SetMatrix(newMatrix);
		Multiply(inverse);
		mHasVelocity = false;
		mHasAngularVelocity = false;
	}

	// FUNCTION: ENGINE 0x1094E080
	// NONMATCHING: the quaternion validation is called with its argument in eax in the engine, in ecx in ours; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetDelta(const math::Quaternion& quat)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x96, ValidateDeltaInput(quat), "ValidateDeltaInput( quat )", "");
		SetQuaternion(quat);
		mHasAngularVelocity = false;
	}
#endif

	// FUNCTION: ENGINE 0x1094E0E0
	// NONMATCHING: as SetDelta(quat); 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetDelta(const math::Vector& trans)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xA0, ValidateDeltaInput(trans), "ValidateDeltaInput( trans )", "");
		mMatrix.SetTranslation(trans);
		mHasVelocity = false;
	}
#endif

	// FUNCTION: ENGINE 0x1094E140
	// NONMATCHING: as SetDelta(quat); 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetDelta(const math::Vector& trans, const math::Quaternion& invRootQuaternion)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xA6, ValidateDeltaInput(trans), "ValidateDeltaInput( trans )", "");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xA7, ValidateDeltaInput(invRootQuaternion),
			"ValidateDeltaInput( invRootQuaternion )", "");
		math::Vector rotated;
		invRootQuaternion.Transform(trans, rotated);
		mMatrix.SetTranslation(rotated);
		mHasVelocity = false;
	}
#endif

	// FUNCTION: ENGINE 0x1094E200
	// NONMATCHING: as SetDelta(quat); 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetDelta(const math::Vector& trans, const math::Matrix& rootTransform)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xB0, ValidateDeltaInput(trans), "ValidateDeltaInput( trans )", "");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xB1, ValidateDeltaInput(rootTransform), "ValidateDeltaInput( rootTransform )",
			"");
		math::Matrix inverse;
		inverse = rootTransform;
		inverse.InvertOrthonormal();
		math::Vector rotated;
		inverse.Rotate(trans, rotated);
		mMatrix.SetTranslation(rotated);
		mHasVelocity = false;
	}
#endif

	// FUNCTION: ENGINE 0x1094E2E0
	// NONMATCHING: as SetDelta(quat); 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetPosition(const math::Vector& position, const math::Matrix& rootTransform)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xBE, ValidateDeltaInput(position), "ValidateDeltaInput( position )", "");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xBF, ValidateDeltaInput(rootTransform), "ValidateDeltaInput( rootTransform )",
			"");
		math::Matrix inverse;
		inverse = rootTransform;
		inverse.InvertOrthonormal();
		math::Vector transformed;
		inverse.Transform(position, transformed);
		mMatrix.SetTranslation(transformed);
		mHasVelocity = false;
	}
#endif

	// FUNCTION: ENGINE 0x1094E3C0
	// NONMATCHING: the float validation is called with its argument in eax in the engine, in ecx in ours; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetDelta(float deltaOrientation)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xCB, ValidateDeltaInput(deltaOrientation),
			"ValidateDeltaInput( deltaOrientation )", "");
		SetRotationY(deltaOrientation);
		mHasAngularVelocity = false;
	}
#endif

	// FUNCTION: ENGINE 0x1094E430
	// NONMATCHING: as SetDelta(quat); 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetDeltaFacing(const math::Vector& deltaFacingVector)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xD2, ValidateDeltaInput(deltaFacingVector),
			"ValidateDeltaInput( deltaFacingVector )", "");
		SetRotation(deltaFacingVector);
		mHasAngularVelocity = false;
	}
#endif

	// FUNCTION: ENGINE 0x1094E490
	// NONMATCHING: as SetDelta(quat); 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetOrientation(float orientation, const math::Quaternion& invRootQuaternion)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xDA, ValidateDeltaInput(orientation), "ValidateDeltaInput( orientation )", "");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xDB, ValidateDeltaInput(invRootQuaternion),
			"ValidateDeltaInput( inverseRootQuaternion )", "");
		Transform rotation;
		rotation.SetRotationY(orientation);
		math::Quaternion quaternion = rotation.GetQuaternion();
		math::Multiply(quaternion, quaternion, invRootQuaternion);
		SetQuaternion(quaternion);
		mHasAngularVelocity = false;
	}
#endif

	// FUNCTION: ENGINE 0x1094E5A0
	// NONMATCHING: the float and the quaternion validation are called with their argument in eax in the engine, in
	// ecx in ours; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetOrientation(float orientation, const math::Matrix& rootMatrix)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xE7, ValidateDeltaInput(orientation), "ValidateDeltaInput( orientation )", "");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xE8, ValidateDeltaInput(rootMatrix), "ValidateDeltaInput( rootMatrix )", "");
		math::Matrix inverse;
		inverse = rootMatrix;
		inverse.InvertOrthonormal();
		Transform rotation;
		rotation.SetRotationY(orientation);
		rotation.Multiply(inverse);
		math::Quaternion quaternion = rotation.GetQuaternion();
		SetQuaternion(quaternion);
		mHasAngularVelocity = false;
	}
#endif

	// FUNCTION: ENGINE 0x1094E6C0
	void DeltaTransform::SetOrientation(const math::Matrix& deltaRotationMatrix)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xF8, ValidateDeltaInput(deltaRotationMatrix),
			"ValidateDeltaInput( deltaRotationMatrix )", "");
		math::Quaternion quaternion;
		quaternion.FromMatrix(deltaRotationMatrix);
		SetDelta(quaternion);
	}

	// FUNCTION: ENGINE 0x1094E730
	// NONMATCHING: the quaternion validation is called with its argument in eax in the engine, in ecx in ours; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetRotation(const math::Matrix& rotationMatrix, const math::Quaternion& invRootQuaternion)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0xFF, ValidateDeltaInput(rotationMatrix), "ValidateDeltaInput( rotationMatrix )",
			"");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x100, ValidateDeltaInput(invRootQuaternion),
			"ValidateDeltaInput( invRootQuaternion )", "");
		math::Quaternion quaternion;
		quaternion.FromMatrix(rotationMatrix);
		math::Multiply(quaternion, quaternion, invRootQuaternion);
		SetDelta(quaternion);
	}
#endif

	// FUNCTION: ENGINE 0x1094E800
	void DeltaTransform::SetRotation(const math::Matrix& rotationMatrix, const math::Matrix& rootMatrix)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x108, ValidateDeltaInput(rotationMatrix), "ValidateDeltaInput( rotationMatrix )",
			"");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x109, ValidateDeltaInput(rootMatrix), "ValidateDeltaInput( rootMatrix )", "");
		math::Matrix inverse;
		inverse = rootMatrix;
		inverse.InvertOrthonormal();
		math::Matrix matrix;
		matrix.Multiply(rotationMatrix, inverse);
		SetOrientation(matrix);
	}

	// FUNCTION: ENGINE 0x1094E8E0
	// NONMATCHING: as SetDelta(quat); 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetVelocityOrientation(const math::Vector& velocity, const math::Quaternion& inverseRootQuaternion)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x115, ValidateDeltaInput(velocity), "ValidateDeltaInput( velocity )", "");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x116, ValidateDeltaInput(inverseRootQuaternion),
			"ValidateDeltaInput( inverseRootQuaternion )", "");
		inverseRootQuaternion.Transform(velocity, mVelocity);
		mHasVelocity = true;
		SetOrientation(Heading(velocity), inverseRootQuaternion);
	}
#endif

	// FUNCTION: ENGINE 0x1094E9A0
	// NONMATCHING: the vector validation is called with its argument in eax in the engine, in ecx in ours; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetVelocityOrientation(const math::Vector& velocity, const math::Matrix& rootMatrix)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x11E, ValidateDeltaInput(velocity), "ValidateDeltaInput( velocity )", "");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x11F, ValidateDeltaInput(rootMatrix), "ValidateDeltaInput( rootMatrix )", "");
		math::Matrix inverse;
		inverse = rootMatrix;
		inverse.InvertOrthonormal();
		inverse.Rotate(velocity, mVelocity);
		mHasVelocity = true;
		Transform rotation;
		rotation.SetRotationY(Heading(velocity));
		rotation.Multiply(inverse);
		SetQuaternion(rotation.GetQuaternion());
		mHasAngularVelocity = false;
	}
#endif

	// FUNCTION: ENGINE 0x1094EAC0
	// NONMATCHING: the vector validation is called with its argument in eax in the engine, in ecx in ours; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetDeltaFacing(const math::Vector& newFacingVector, const math::Vector& oldFacingVector)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x132, ValidateDeltaInput(newFacingVector),
			"ValidateDeltaInput( newFacingVector )", "");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x133, ValidateDeltaInput(oldFacingVector),
			"ValidateDeltaInput( oldFacingVector )", "");
		math::Vector translation;
		mMatrix.GetTranslation(translation);
		SetRotation(newFacingVector);
		Transform old;
		old.SetRotation(oldFacingVector);
		math::Matrix inverse;
		inverse = old.ToMatrix();
		inverse.InvertOrthonormal();
		Multiply(inverse);
		mMatrix.SetTranslation(translation);
		mHasAngularVelocity = false;
	}
#endif

	// FUNCTION: ENGINE 0x1094EBF0
	// NONMATCHING: the vector and the quaternion validation are called with their argument in eax in the engine, in
	// ecx in ours; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetDeltaFacing(const math::Vector& facingVector, const math::Quaternion& invRootQuaternion)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x143, ValidateDeltaInput(facingVector), "ValidateDeltaInput( facingVector )",
			"");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x144, ValidateDeltaInput(invRootQuaternion),
			"ValidateDeltaInput( invRootQuaternion )", "");
		Transform rotation;
		rotation.SetRotation(facingVector);
		SetRotation(rotation.ToMatrix(), invRootQuaternion);
	}
#endif

	// FUNCTION: ENGINE 0x1094ECC0
	// NONMATCHING: the vector validation is called with its argument in eax in the engine, in ecx in ours; 99 %
#ifdef NONMATCHING
	void DeltaTransform::SetDeltaFacing(const math::Vector& facingVector, const math::Matrix& rootTransform)
	{
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x14B, ValidateDeltaInput(facingVector), "ValidateDeltaInput( facingVector )",
			"");
		OLD_ASSERT_AT(DELTATRANSFORM_FILE, 0x14C, ValidateDeltaInput(rootTransform),
			"ValidateDeltaInput( rootTransform )", "");
		Transform rotation;
		rotation.SetRotation(facingVector);
		SetRotation(rotation.ToMatrix(), rootTransform);
	}
#endif

	// FUNCTION: ENGINE 0x1094ED90
	// NONMATCHING: the engine expands the identity matrix into sixteen locals and schedules the two branches
	// differently; 25 %
#ifdef NONMATCHING
	void DeltaTransform::Update(float dt)
	{
		if (mHasAngularVelocity)
		{
			math::Vector angular;
			angular.x = dt * mAngularVelocity.x;
			angular.y = mAngularVelocity.y * dt;
			angular.z = mAngularVelocity.z * dt;
			math::Matrix matrix = math::Matrix::IDENTITY;
			matrix.RotateByVector(angular);
			math::Quaternion quaternion;
			quaternion.FromMatrix(matrix);
			SetQuaternion(quaternion);
		}
		if (mHasVelocity)
		{
			math::Vector linear;
			linear.x = mVelocity.x * dt;
			linear.y = mVelocity.y * dt;
			linear.z = mVelocity.z * dt;
			mMatrix.SetTranslation(linear);
		}
	}
#endif
}
