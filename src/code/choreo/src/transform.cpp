// choreo::Transform and the angle and direction helpers that sit in front of it (the unit from 0x10945800 to the
// delta transform's unit; names are guesses). The transform keeps either a matrix or a quaternion with three scales and
// converts lazily between them.
#include "code/choreo/deltatransform.h"
#include "code/math/sincos.h"
#include "code/math/worldbounds.h"
#include <float.h>
#include <math.h>

namespace choreo
{
	// The reference directions of the unit: the way a transform faces without any rotation and the way up
	static const math::Vector FORWARD(0.0f, 0.0f, -1.0f);
	static const math::Vector UP(0.0f, 1.0f, 0.0f);

	// FUNCTION: ENGINE 0x10945810
	void LerpVector(const math::Vector& a, const math::Vector& b, float t, math::Vector& out)
	{
		out.x = (b.x - a.x) * t + a.x;
		out.y = (b.y - a.y) * t + a.y;
		out.z = (b.z - a.z) * t + a.z;
	}

	// FUNCTION: ENGINE 0x10945880
	void LerpMatrix(const math::Matrix& a, const math::Matrix& b, float t, math::Matrix& out)
	{
		math::Vector pa(a.m[3][0], a.m[3][1], a.m[3][2]);
		math::Vector pb(b.m[3][0], b.m[3][1], b.m[3][2]);
		math::Vector position;
		position.x = (pb.x - pa.x) * t + pa.x;
		position.y = (pb.y - pa.y) * t + pa.y;
		position.z = (pb.z - pa.z) * t + pa.z;
		out.m[3][0] = position.x;
		out.m[3][1] = position.y;
		out.m[3][2] = position.z;
		math::Quaternion from;
		math::Quaternion to;
		math::Quaternion result;
		from.FromMatrix(a);
		to.FromMatrix(b);
		result.Slerp(from, to, t);
		result.ToMatrix(out);
		out.m[0][3] = 0.0f;
		out.m[1][3] = 0.0f;
		out.m[2][3] = 0.0f;
		out.m[3][3] = 1.0f;
	}

	// FUNCTION: ENGINE 0x10945950
	float HeadingXZ(float x, float z)
	{
		if (fabsf(x) <= 1e-5f && fabsf(z) <= 1e-5f)
		{
			return 0.0f;
		}
		float heading = atan2f(-x, -z);
		if (heading < 0.0f)
		{
			return heading + 6.28318548f;
		}
		return heading;
	}

	// FUNCTION: ENGINE 0x109459A0
	float Heading(const math::Vector& vector)
	{
		float x = vector.x;
		float z = vector.z;
		if (!(fabsf(vector.y) <= 1e-5f))
		{
			float length = sqrtf(x * x + z * z);
			if (!(fabsf(length) <= 1e-5f))
			{
				float scale = 1.0f / length;
				x = scale * x;
				z = scale * z;
			}
			else
			{
				x = 0.0f;
				z = 0.0f;
			}
		}
		return HeadingXZ(x, z);
	}

	// FUNCTION: ENGINE 0x10945A40
	float MatrixHeading(const math::Matrix& matrix)
	{
		math::Vector row(matrix.m[2][0], matrix.m[2][1], matrix.m[2][2]);
		math::Vector facing;
		facing.x = math::WORLD_MIN - row.x;
		facing.y = math::WORLD_MIN - row.y;
		facing.z = math::WORLD_MIN - row.z;
		return Heading(facing);
	}

	// FUNCTION: ENGINE 0x10945A90
	float AngleDifference(float from, float to)
	{
		return WrapFrame(-3.14159274f, 3.14159274f, to - from);
	}

	// FUNCTION: ENGINE 0x10945AD0
	// EQUIVALENT: the same products and sums in the same order; the engine keeps the sine and the cosine in other
	// registers (88.7 %)
	void RotateY(float angle, math::Vector& vector)
	{
		float sine;
		float cosine;
		math::SinCos(angle, &sine, &cosine);
		math::Vector in = vector;
		math::Vector out;
		out.x = in.z * sine + in.x * cosine;
		out.z = (math::WORLD_MIN - in.x * sine) + in.z * cosine;
		vector.x = out.x;
		vector.z = out.z;
	}

	// FUNCTION: ENGINE 0x10945B50
	void RotationFromTo(math::Matrix& matrix, const math::Vector& from, const math::Vector& to)
	{
		matrix.RotationFromTo(from, to);
	}

	// FUNCTION: ENGINE 0x10945B70
	math::Quaternion* InverseRotation(math::Quaternion* quaternion, const math::Matrix& matrix)
	{
		quaternion->FromMatrix(matrix);
		float zero = math::WORLD_MIN;
		quaternion->x = zero - quaternion->x;
		quaternion->y = zero - quaternion->y;
		quaternion->z = zero - quaternion->z;
		return quaternion;
	}

	// FUNCTION: ENGINE 0x10945BB0
	float WrapAngle(float angle)
	{
		return WrapFrame(-3.14159274f, 3.14159274f, angle);
	}

	// FUNCTION: ENGINE 0x10945BE0
	// NONMATCHING: the engine loads both vectors into registers first, tests the clamps with the subtraction compared against zero and lays
	// the copy of the target and of the start before the rotation; ours differs in registers and block order (12.5 %)
#ifdef NONMATCHING
	void TurnToward(math::Vector& out, const math::Vector& from, const math::Vector& to, float maxAngle)
	{
		float dot = to.x * from.x + to.y * from.y + to.z * from.z;
		if (!(dot - -1.0f >= 0.0f))
		{
			dot = -1.0f;
		}
		if (dot - 1.0f >= 0.0f || dot > 0.99999f)
		{
			out.x = to.x;
			out.y = to.y;
			out.z = to.z;
			return;
		}
		if (-0.99999f > dot)
		{
			out.x = from.x;
			out.y = from.y;
			out.z = from.z;
			return;
		}
		float angle = acosf(dot);
		if (angle < maxAngle)
		{
			maxAngle = angle;
		}
		math::Vector axis;
		axis.x = to.y * from.z - to.z * from.y;
		axis.y = to.z * from.x - from.z * to.x;
		axis.z = from.y * to.x - to.y * from.x;
		axis.Normalize();
		math::Matrix rotation;
		rotation.Identity();
		rotation.RotationAxisAngle(axis, maxAngle);
		math::Vector turned;
		turned.x = from.x;
		turned.y = from.y;
		turned.z = from.z;
		rotation.Rotate(turned, turned);
		out.x = turned.x;
		out.y = turned.y;
		out.z = turned.z;
	}
#endif

	// FUNCTION: ENGINE 0x10945DC0
	// NONMATCHING: as the turn toward: registers and block order differ (21.1 %)
#ifdef NONMATCHING
	void TurnAway(math::Vector& out, const math::Vector& from, const math::Vector& to, float maxAngle)
	{
		float y = from.y;
		float x = from.x;
		float z = from.z;
		float dot = to.x * x + to.y * y + to.z * z;
		if (dot - -1.0f < 0.0f)
		{
			dot = -1.0f;
		}
		if (0.0f <= dot - 1.0f)
		{
			dot = 1.0f;
		}
		if (fabsf(dot - 1.0f) <= 1e-5f)
		{
			out.x = x;
			out.y = y;
			out.z = z;
			return;
		}
		float angle = acosf(dot);
		if (angle <= maxAngle)
		{
			out.x = x;
			out.y = y;
			out.z = z;
			return;
		}
		math::Vector axis;
		axis.x = to.y * from.z - to.z * from.y;
		axis.y = to.z * x - from.z * to.x;
		axis.z = from.y * to.x - to.y * x;
		axis.Normalize();
		math::Matrix rotation;
		rotation.Identity();
		rotation.RotationAxisAngle(axis, angle - maxAngle);
		math::Vector turned;
		turned.x = from.x;
		turned.y = from.y;
		turned.z = from.z;
		rotation.Rotate(turned, turned);
		out.x = turned.x;
		out.y = turned.y;
		out.z = turned.z;
	}
#endif

	// FUNCTION: ENGINE 0x10945FB0
	const math::Matrix& TurnAroundMatrix()
	{
		static math::Matrix matrix = math::Matrix::IDENTITY;
		static bool ready = false;
		if (!ready)
		{
			matrix.RotationFromTo(FORWARD, math::Vector(0.0f, 0.0f, 1.0f));
			ready = true;
		}
		return matrix;
	}

	// FUNCTION: ENGINE 0x10946280
	math::Vector Transform::GetTranslation() const
	{
		return math::Vector(mMatrix.m[3][0], mMatrix.m[3][1], mMatrix.m[3][2]);
	}

	// FUNCTION: ENGINE 0x109462F0
	void Transform::Reset()
	{
		mMatrix.Identity();
		mQuaternion.x = mQuaternion.y = mQuaternion.z = 0.0f;
		mQuaternion.w = 1.0f;
		mScale.x = 1.0f;
		mScale.y = 1.0f;
		mScale.z = 1.0f;
		mMode = 0;
	}

	// FUNCTION: ENGINE 0x10946330
	void Transform::SetMatrix(const math::Matrix& matrix)
	{
		mMatrix = matrix;
		mMode = 2;
	}

	// FUNCTION: ENGINE 0x10946350
	// NONMATCHING: the engine copies each row through three registers; ours mixes in x87 copies (16.7 %)
#ifdef NONMATCHING
	void Transform::SetRotationMatrix(const math::Matrix& matrix)
	{
		float a0 = matrix.m[0][0];
		float a1 = matrix.m[0][1];
		float a2 = matrix.m[0][2];
		mMatrix.m[0][0] = a0;
		mMatrix.m[0][1] = a1;
		mMatrix.m[0][2] = a2;
		float b0 = matrix.m[1][0];
		float b1 = matrix.m[1][1];
		float b2 = matrix.m[1][2];
		mMatrix.m[1][0] = b0;
		mMatrix.m[1][1] = b1;
		mMatrix.m[1][2] = b2;
		float c0 = matrix.m[2][0];
		float c1 = matrix.m[2][1];
		float c2 = matrix.m[2][2];
		mMatrix.m[2][0] = c0;
		mMatrix.m[2][1] = c1;
		mMatrix.m[2][2] = c2;
		mMode = 2;
	}
#endif

	// FUNCTION: ENGINE 0x109463C0
	math::Vector Transform::GetForward() const
	{
		if (mMode != 1)
		{
			math::Vector row(mMatrix.m[2][0], mMatrix.m[2][1], mMatrix.m[2][2]);
			return math::Vector(math::WORLD_MIN - row.x, math::WORLD_MIN - row.y, math::WORLD_MIN - row.z);
		}
		math::Vector forward = FORWARD;
		mQuaternion.Transform(forward, forward);
		return forward;
	}

	// FUNCTION: ENGINE 0x10946470
	void Transform::Rotate(const math::Vector& vector, math::Vector& out) const
	{
		switch (mMode)
		{
		case 0:
		case 2:
			mMatrix.Rotate(vector, out);
			break;
		case 1:
			mQuaternion.Transform(vector, out);
			break;
		}
	}

	// FUNCTION: ENGINE 0x109464A0
	bool Transform::IsValid() const
	{
		for (int row = 0; row < 4; row++)
		{
			for (int column = 0; column < 4; column++)
			{
				if (_isnan(mMatrix.m[row][column]))
				{
					return false;
				}
			}
		}
		if (_isnan(mQuaternion.x) || _isnan(mQuaternion.y) || _isnan(mQuaternion.z) || _isnan(mQuaternion.w)
			|| _isnan(mScale.x) || _isnan(mScale.y))
		{
			return false;
		}
		bool r = _isnan(mScale.z) == 0;
		return r;
	}

	// FUNCTION: ENGINE 0x10946590
	Transform::Transform()
	{
		Reset();
	}

	// FUNCTION: ENGINE 0x109465A0
	Transform::Transform(const math::Matrix& matrix)
	{
		mMatrix = matrix;
		mQuaternion.x = mQuaternion.y = mQuaternion.z = 0.0f;
		mQuaternion.w = 1.0f;
		mScale.x = 1.0f;
		mScale.y = 1.0f;
		mScale.z = 1.0f;
		mMode = 2;
	}

	// FUNCTION: ENGINE 0x109465F0
	Transform::Transform(const math::Quaternion& rotation, const math::Vector& position, const math::Vector& scale)
	{
		mMatrix.Identity();
		mMatrix.SetTranslation(position);
		mQuaternion = rotation;
		math::Vector& s = mScale;
		s.x = scale.x;
		s.y = scale.y;
		s.z = scale.z;
		mMode = 1;
	}

	// FUNCTION: ENGINE 0x10946650
	Transform::Transform(const math::Vector& position, const math::Vector& scale)
	{
		mMatrix.Identity();
		mMatrix.SetTranslation(position);
		mQuaternion.x = mQuaternion.y = mQuaternion.z = 0.0f;
		mQuaternion.w = 1.0f;
		math::Vector& s = mScale;
		s.x = scale.x;
		s.y = scale.y;
		s.z = scale.z;
		mMode = 1;
	}

	// FUNCTION: ENGINE 0x109466B0
	Transform& Transform::operator=(const math::Matrix& matrix)
	{
		SetMatrix(matrix);
		return *this;
	}

	// FUNCTION: ENGINE 0x109466D0
	// EQUIVALENT: the same nine products in the same order; the engine loads the scale and the three elements of a row
	// before it multiplies where ours loads them one after the other (53.5 %)
	const math::Matrix& Transform::ToMatrix()
	{
		if (mMode == 1)
		{
			mQuaternion.ToMatrix(mMatrix);
			((math::Vector*)&mMatrix.m[0][0])->Scale(mScale.x);
			((math::Vector*)&mMatrix.m[1][0])->Scale(mScale.y);
			((math::Vector*)&mMatrix.m[2][0])->Scale(mScale.z);
			mMode = 0;
		}
		return mMatrix;
	}

	// FUNCTION: ENGINE 0x10946780
	// EQUIVALENT: the same loop; the engine computes the address of the scales after the address of the rows where ours
	// computes it before (98.1 %)
	void Transform::ToQuaternion()
	{
		if (mMode == 2)
		{
			math::Matrix rotation = mMatrix;
			float* row = &rotation.m[0][0];
			float* scale = &mScale.x;
			for (int i = 0; i < 3; i++)
			{
				math::Vector axis(row[0], row[1], row[2]);
				*scale = axis.Normalize();
				row[0] = axis.x;
				row[1] = axis.y;
				row[2] = axis.z;
				scale++;
				row += 4;
			}
			mQuaternion.FromMatrix(rotation);
			mMode = 0;
		}
	}

	// FUNCTION: ENGINE 0x109468C0
	const math::Quaternion& Transform::GetQuaternion()
	{
		ToQuaternion();
		return mQuaternion;
	}

	// FUNCTION: ENGINE 0x109468D0
	void Transform::SetQuaternion(const math::Quaternion& quaternion)
	{
		ToQuaternion();
		mQuaternion = quaternion;
		mMode = 1;
	}

	// FUNCTION: ENGINE 0x10946900
	float Transform::GetHeading() const
	{
		return Heading(GetForward());
	}

	// FUNCTION: ENGINE 0x10946920
	void Transform::SetRotationY(float angle)
	{
		math::Quaternion rotation;
		rotation.RotationY(angle);
		SetQuaternion(rotation);
	}

	// FUNCTION: ENGINE 0x10946950
	void Transform::SetRotation(const math::Vector& direction)
	{
		math::Vector position(mMatrix.m[3][0], mMatrix.m[3][1], mMatrix.m[3][2]);
		mMatrix.Identity();
		mMatrix.RotationX(asinf(direction.y));
		math::Matrix yaw;
		yaw.Identity();
		yaw.RotationY(Heading(direction));
		mMatrix.Multiply(mMatrix, yaw);
		math::Vector& translation = *(math::Vector*)&mMatrix.m[3][0];
		translation.x = position.x;
		translation.y = position.y;
		translation.z = position.z;
		mMode = 2;
	}

	// FUNCTION: ENGINE 0x109469F0
	math::Vector Transform::GetUp() const
	{
		math::Vector up;
		Rotate(UP, up);
		return up;
	}

	// FUNCTION: ENGINE 0x10946A10
	const math::Vector& Transform::GetScale()
	{
		ToQuaternion();
		return mScale;
	}

	// FUNCTION: ENGINE 0x10946A20
	void Transform::SetScale(const math::Vector& scale)
	{
		ToQuaternion();
		math::Vector& s = mScale;
		s.x = scale.x;
		s.y = scale.y;
		s.z = scale.z;
		mMode = 1;
	}

	// FUNCTION: ENGINE 0x10946A50
	void Transform::Blend(Transform& other, float t)
	{
		math::Vector pa(mMatrix.m[3][0], mMatrix.m[3][1], mMatrix.m[3][2]);
		math::Vector pb(other.mMatrix.m[3][0], other.mMatrix.m[3][1], other.mMatrix.m[3][2]);
		math::Vector position;
		position.x = (pb.x - pa.x) * t + pa.x;
		position.y = (pb.y - pa.y) * t + pa.y;
		position.z = (pb.z - pa.z) * t + pa.z;
		mMatrix.m[3][0] = position.x;
		mMatrix.m[3][1] = position.y;
		mMatrix.m[3][2] = position.z;
		ToQuaternion();
		const math::Quaternion& target = other.GetQuaternion();
		mQuaternion.Slerp(mQuaternion, target, t);
		const math::Vector& scale = other.GetScale();
		math::Vector& s = mScale;
		s.x = (scale.x - s.x) * t + s.x;
		s.y = (scale.y - s.y) * t + s.y;
		s.z = (scale.z - s.z) * t + s.z;
		mMode = 1;
	}

	// FUNCTION: ENGINE 0x10946B40
	void Transform::Multiply(Transform& other)
	{
		ToMatrix();
		mMatrix.Multiply(mMatrix, other.ToMatrix());
		mMode = 2;
	}

	// FUNCTION: ENGINE 0x10946B70
	void Transform::Multiply(const math::Matrix& matrix)
	{
		ToMatrix();
		mMatrix.Multiply(mMatrix, matrix);
		mMode = 2;
	}

	// FUNCTION: ENGINE 0x10946B90
	void Transform::TransformPoint(const math::Vector& point, math::Vector& out)
	{
		switch (mMode)
		{
		case 0:
		case 2:
			mMatrix.Transform(point, out);
			break;
		case 1:
			ToMatrix();
			mMatrix.Transform(point, out);
			break;
		}
	}
}
