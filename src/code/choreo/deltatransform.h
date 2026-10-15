// choreo::DeltaTransform (code/choreo/src/deltatransform.cpp, path from the asserts): the movement of a character
// over one step, kept as a transform the caller feeds and reads back. It is told either the linear and the angular
// delta of the step, or the root matrix the step ends on (with the inverse of the quaternion the step started with),
// and gives the caller the matrix, the position, the rotation or the facing vector of the delta.
//
// The transform under it (matrix, the quaternion it was decomposed to, the scale of its three axes and which of the
// two is current) is choreo::Transform, whose code sits in the unit before this one. Member and method names are
// guesses until the binary confirms them.
#ifndef CHOREO_DELTATRANSFORM_H
#define CHOREO_DELTATRANSFORM_H

#include "code/math/matrix.h"
#include "code/math/quaternion.h"
#include "code/math/vector.h"

namespace choreo
{
	// 0x109459A0: the heading of the vector's horizontal part, atan2(-x, -z) wrapped into [0, 2 pi) (the unit before
	// this one; name guessed)
	float Heading(const math::Vector& vector);

	// The transform a delta transform is built on
	class Transform
	{
	public:
		// 0x10946590
		Transform();
		// 0x109462F0: the identity matrix, no rotation, unit scales
		void Reset();
		// 0x10946330: replaces the matrix and makes it the current form
		void SetMatrix(const math::Matrix& matrix);
		// 0x109466D0: makes the matrix current (out of the quaternion and the scales) and returns it
		const math::Matrix& ToMatrix();
		// 0x10946780: makes the quaternion and the scales current (out of the matrix)
		void ToQuaternion();
		// 0x109468C0
		const math::Quaternion& GetQuaternion();
		// 0x109468D0
		void SetQuaternion(const math::Quaternion& quaternion);
		// 0x10946920: the rotation of the angle around Y
		void SetRotationY(float angle);
		// 0x10946950: the rotation that turns the facing direction into the reference one
		void SetRotation(const math::Vector& direction);
		// 0x10946470: rotates a vector by the current form
		void Rotate(const math::Vector& vector, math::Vector& out) const;
		// 0x10946B70: this = this * matrix
		void Multiply(const math::Matrix& matrix);

		math::Matrix mMatrix;         // 0x00
		math::Quaternion mQuaternion; // 0x40
		float mScaleX;                // 0x50
		float mScaleY;                // 0x54
		float mScaleZ;                // 0x58
		// Which of the two forms of the rotation is current: 1 the quaternion, 0 and 2 the matrix
		int mMode;                    // 0x5C
	};

	class DeltaTransform : public Transform
	{
	public:
		// 0x1094D880
		DeltaTransform();
		// 0x1094D920: clears the transform and both deltas
		void Reset();

		// The linear delta of the step, in world space
		void SetVelocity(const math::Vector& velocity);
		void SetVelocity(const math::Vector& velocity, const math::Quaternion& invRootQuaternion);
		void SetVelocity(const math::Vector& velocity, const math::Matrix& rootTransform);
		// The angular delta of the step
		void SetAngularVelocity(const math::Vector& velocity);
		void SetAngularVelocity(const math::Vector& velocity, const math::Quaternion& invRootQuaternion);
		void SetAngularVelocity(const math::Vector& velocity, const math::Matrix& rootTransform);
		// The whole movement of the step, replacing either the transform or one of its parts
		void SetDelta(const math::Matrix& deltaMatrix);
		void SetDelta(const math::Matrix& newMatrix, const math::Matrix& oldMatrix);
		void SetDelta(const math::Quaternion& quat);
		void SetDelta(const math::Vector& trans);
		void SetDelta(const math::Vector& trans, const math::Quaternion& invRootQuaternion);
		void SetDelta(const math::Vector& trans, const math::Matrix& rootTransform);
		void SetPosition(const math::Vector& position, const math::Matrix& rootTransform);
		void SetDelta(float deltaOrientation);
		void SetDeltaFacing(const math::Vector& deltaFacingVector);

		// The orientation of the step, given as the angle about Y and the space it is measured in
		void SetOrientation(float orientation, const math::Quaternion& invRootQuaternion);
		void SetOrientation(float orientation, const math::Matrix& rootMatrix);
		void SetOrientation(const math::Matrix& deltaRotationMatrix);
		void SetRotation(const math::Matrix& rotationMatrix, const math::Quaternion& invRootQuaternion);
		void SetRotation(const math::Matrix& rotationMatrix, const math::Matrix& rootMatrix);
		// The linear delta of the step and the orientation that goes with it
		void SetVelocityOrientation(const math::Vector& velocity, const math::Quaternion& inverseRootQuaternion);
		void SetVelocityOrientation(const math::Vector& velocity, const math::Matrix& rootMatrix);
		// The rotation that turns the old facing direction into the new one
		void SetDeltaFacing(const math::Vector& newFacingVector, const math::Vector& oldFacingVector);
		void SetDeltaFacing(const math::Vector& facingVector, const math::Quaternion& invRootQuaternion);
		void SetDeltaFacing(const math::Vector& facingVector, const math::Matrix& rootTransform);

		// 0x1094ED90: applies the two deltas of the step to the transform
		void Update(float dt);

		// The linear delta of the step, in world space
		math::Vector mVelocity;        // 0x60
		// The angular delta of the step
		math::Vector mAngularVelocity; // 0x6C
		// Whether the linear / the angular delta was set this step
		bool mHasVelocity;             // 0x78
		bool mHasAngularVelocity;      // 0x79
	};
}

#endif
