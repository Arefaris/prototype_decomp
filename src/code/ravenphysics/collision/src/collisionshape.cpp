// The shape a collision object is seen through by the physics (the velocities, the inertia matrix and the centre of the
// object's volumes), unit 0x10669110 - 0x1066A3B0. It carries no assert of its own, so nothing in the image names its
// source file: the file name is a guess. All member names are guesses.
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/physicsobject.h"
#include "code/engine/motiontrackingfilter.h"
#include "code/math/mathconstants.h"
#include <math.h>
#include <new>

namespace ravenphysics
{
	// The limits the velocities are kept under, and their squares (0x110BF1F0 - 0x110BF1FC)
	float gMaxLinearSpeed = 1000.0f;
	float gMaxLinearSpeedSquared = 1000000.0f;
	float gMaxAngularSpeed = 1000.0f;
	float gMaxAngularSpeedSquared = 1000000.0f;

	// The engine clears a vector from its last component
	static inline void ZeroVector(math::Vector& vector)
	{
		vector.z = 0.0f;
		vector.y = 0.0f;
		vector.x = 0.0f;
	}

	// A vector added to another (the engine's inline form)
	static inline void AddVector(math::Vector& to, const math::Vector& add)
	{
		to.x = to.x + add.x;
		to.y = add.y + to.y;
		to.z = add.z + to.z;
	}

	// A cross product, written from its second component (the engine's inline form)
	static inline void CrossVectors(math::Vector& out, const math::Vector& a, const math::Vector& b)
	{
		out.y = a.z * b.x - a.x * b.z;
		out.z = a.x * b.y - a.y * b.x;
		out.x = a.y * b.z - a.z * b.y;
	}

	// The matrix carried to the world: the transposed 3x3 of the transform times the matrix times the 3x3
	// FUNCTION: ENGINE 0x10668EA0
	// NONMATCHING: the engine passes the result's address on the stack (the two matrices in ecx and edx), ours passes it in eax, 12.9 %
#ifdef NONMATCHING
	static math::SymmetricMatrix TransformInertia(const math::Matrix* transform, const math::SymmetricMatrix* matrix)
	{
		math::SymmetricMatrix result;
		math::SymmetricMatrix* out = &result;
		const float* m = &transform->m[0][0];
		float xx = matrix->xx;
		float yy = matrix->yy;
		float zz = matrix->zz;
		float xy = matrix->xy;
		float xz = matrix->xz;
		float yz = matrix->yz;
		float m10 = m[4];
		float m00 = m[0];
		float m20 = m[8];
		float first = xx * m00 + xy * m10 + xz * m20;
		float second = yy * m10 + yz * m20 + xy * m00;
		float third = zz * m20 + yz * m10 + xz * m00;
		float m22 = m[10];
		float m12 = m[6];
		out->xx = third * m[8] + second * m10 + first * m[0];
		float m21 = m[9];
		float m01 = m[1];
		out->xz = m[2] * first + m12 * second + m22 * third;
		float m11 = m[5];
		out->xy = third * m21 + second * m11 + first * m01;
		float fourth = xx * m01 + xy * m11 + xz * m21;
		float fifth = yy * m11 + yz * m21 + xy * m01;
		float sixth = zz * m21 + yz * m11 + xz * m01;
		float m02 = m[2];
		float m22b = m[10];
		out->yy = sixth * m[9] + fifth * m11 + fourth * m[1];
		float m12b = m[6];
		out->yz = sixth * m22b + fifth * m12b + fourth * m02;
		out->zz = (yy * m12b + yz * m22b + xy * m02) * m12b + (zz * m22b + yz * m12b + xz * m02) * m22b +
			(xx * m02 + xy * m12b + xz * m22b) * m02;
		return result;
	}
#endif

	// FUNCTION: ENGINE 0x10669120
	CollisionShape::~CollisionShape()
	{
	}

	// FUNCTION: ENGINE 0x10669130
	void CollisionShape::ClearAccumulated()
	{
		ZeroVector(unknown40);
		ZeroVector(unknown4C);
		unknown0 = 0;
	}

	// FUNCTION: ENGINE 0x10669160
	// NONMATCHING: calls the transform helper, whose result address the engine passes on the stack, 23.9 %
#ifdef NONMATCHING
	void CollisionShape::Unknown10669160()
	{
		unknown70 = TransformInertia(&object->transform, &unknown58);
	}
#endif

	// FUNCTION: ENGINE 0x106691B0
	void CollisionShape::SetScale(float scale)
	{
		float inverse = 1.0f / scale;
		unknown8C = inverse;
		unknown58.Multiply(unknown88 * inverse);
		unknown88 = scale;
		Unknown10669160();
	}

	// FUNCTION: ENGINE 0x10669200
	void CollisionShape::SetInverseScale(float inverse)
	{
		if (fabs(inverse) <= math::EPSILON_SMALL)
		{
			unknown8C = inverse;
			return;
		}
		SetScale(1.0f / inverse);
	}

	// FUNCTION: ENGINE 0x10669240
	// NONMATCHING: calls the transform helper, whose result address the engine passes on the stack, 18.1 %
#ifdef NONMATCHING
	void CollisionShape::Update(CollisionObject* newObject)
	{
		float y = unknown90.y;
		float z = unknown90.z;
		float x = unknown90.x;
		const math::Matrix& m = newObject->transform;
		center.x = m.m[1][0] * y + m.m[2][0] * z + m.m[0][0] * x + m.m[3][0];
		center.y = m.m[0][1] * x + m.m[1][1] * y + m.m[2][1] * z + m.m[3][1];
		center.z = m.m[0][2] * x + m.m[1][2] * y + m.m[2][2] * z + m.m[3][2];
		unknown70 = TransformInertia(&newObject->transform, &unknown58);
	}
#endif

	// FUNCTION: ENGINE 0x10669340
	// EQUIVALENT: the same differences, products and sums in the same order (the cross product of the angular velocity and the offset, added to the velocity); the engine keeps the angular velocity in other registers and loads the offset in another order, 14.7 %
	void CollisionShape::GetPointVelocity(math::Vector point, math::Vector* velocity)
	{
		math::Vector offset;
		offset.Sub(point, center);
		CrossVectors(*velocity, unknown1C, offset);
		velocity->Add(unknown10, *velocity);
	}

	// FUNCTION: ENGINE 0x106693F0
	// EQUIVALENT: the same differences, products and sums in the same order (the cross product of the previous angular velocity and the offset, added to the previous velocity); the engine keeps the angular velocity in other registers and loads the offset in another order, 14.7 %
	void CollisionShape::GetPreviousPointVelocity(math::Vector point, math::Vector* velocity)
	{
		math::Vector offset;
		offset.Sub(point, center);
		CrossVectors(*velocity, unknown34, offset);
		velocity->Add(unknown28, *velocity);
	}

	// FUNCTION: ENGINE 0x106694A0
	void CollisionShape::AddVelocity(math::Vector velocity, bool wake)
	{
		AddVector(unknown40, velocity);
		if (wake != 0)
		{
			object->owner->SetCollisionMode(2);
		}
	}

	// FUNCTION: ENGINE 0x106694F0
	// EQUIVALENT: the same sums and products in the same order; the engine loads the offset and the impulse into registers in another order, 39.7 %
	void CollisionShape::AddImpulse(math::Vector impulse, math::Vector point, bool wake)
	{
		AddVector(unknown40, impulse);
		math::Vector offset;
		offset.Sub(point, center);
		unknown4C.y = unknown4C.y + (offset.z * impulse.x - impulse.z * offset.x);
		unknown4C.x = unknown4C.x + (offset.y * impulse.z - offset.z * impulse.y);
		unknown4C.z = unknown4C.z + (impulse.y * offset.x - offset.y * impulse.x);
		unknown0 = 1;
		if (wake != 0)
		{
			object->owner->SetCollisionMode(2);
		}
	}

	// FUNCTION: ENGINE 0x106695D0
	void CollisionShape::AddAngularVelocity(math::Vector velocity, bool wake)
	{
		AddVector(unknown4C, velocity);
		unknown0 = 1;
		if (wake != 0)
		{
			object->owner->SetCollisionMode(2);
		}
	}

	// FUNCTION: ENGINE 0x10669620
	void CollisionShape::SetPosition(math::Vector position)
	{
		math::Vector* local = &unknown90;
		local->x = position.x;
		local->y = position.y;
		local->z = position.z;
		object->transform.Transform(*local, center);
	}

	// FUNCTION: ENGINE 0x10669660
	void CollisionShape::SetFlag2(int value)
	{
		flag2 = value;
	}

	// FUNCTION: ENGINE 0x10669680
	bool IsPositiveDefinite(const math::SymmetricMatrix* matrix)
	{
		float yz = matrix->yz;
		float xz = matrix->xz;
		float xy = matrix->xy;
		float zz = matrix->zz;
		float yy = matrix->yy;
		float xx = matrix->xx;
		if (!(0.0f >= (xz * yz - zz * xy) * xy + (xy * yz - yy * xz) * xz + (yy * zz - yz * yz) * xx) &&
			!(0.0f >= (((xx + yy) * zz + xx * yy) - xy * xy) - xz * xz - yz * yz))
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10669730
	void CollisionShape::Print()
	{
		unknown58.Print();
		math::SymmetricMatrix copy = unknown58;
		math::SymmetricMatrix inverse;
		inverse.Invert(copy);
		copy = inverse;
		copy.Print();
		unknown70.Print();
		copy = unknown70;
		inverse.Invert(copy);
		copy = inverse;
		copy.Print();
		center.Print();
		unknown90.Print();
		unknown10.Print();
		unknown1C.Print();
	}

	// FUNCTION: ENGINE 0x10669860
	// EQUIVALENT: the same stores in the same order; the engine reads the object pointer again from the shape before each copy of the transform's diagonal, ours reads it once, and the stores of the inertia matrix are scheduled differently, 75.1 %
	CollisionShape::CollisionShape(const math::Vector* position, const math::SymmetricMatrix* inertia, float newScale,
		CollisionObject* newObject)
	{
		unknown10.x = 0.0f;
		unknown10.y = 0.0f;
		unknown10.z = 0.0f;
		unknown1C.x = 0.0f;
		unknown1C.y = 0.0f;
		unknown1C.z = 0.0f;
		unknown28.x = 0.0f;
		unknown28.y = 0.0f;
		unknown28.z = 0.0f;
		unknown34.x = 0.0f;
		unknown34.y = 0.0f;
		unknown34.z = 0.0f;
		math::SymmetricMatrix* local = &unknown58;
		*local = *inertia;
		unknown88 = newScale;
		unknown8C = 1.0f / newScale;
		unknown90.x = position->x;
		unknown90.y = position->y;
		unknown90.z = position->z;
		center.x = position->x;
		center.y = position->y;
		center.z = position->z;
		unknownA8 = 0;
		object = newObject;
		ClearAccumulated();
		if (unknown8C > 0.0f)
		{
			math::SymmetricMatrix inverse;
			inverse.Invert(*local);
			*local = inverse;
			Unknown10669160();
		}
		else
		{
			local->zz = 0.0f;
			local->yy = 0.0f;
			local->xx = 0.0f;
			local->yz = 0.0f;
			local->xz = 0.0f;
			local->xy = 0.0f;
			unknown70.zz = 0.0f;
			unknown70.yy = 0.0f;
			unknown70.xx = 0.0f;
			unknown70.yz = 0.0f;
			unknown70.xz = 0.0f;
			unknown70.xy = 0.0f;
		}
		radius = object->GetRadius();
		unknownAC.x = center.x;
		unknownAC.y = center.y;
		unknownAC.z = center.z;
		unknownB8.x = object->transform.m[0][0];
		unknownB8.y = object->transform.m[1][1];
		unknownB8.z = object->transform.m[2][2];
		ZeroVector(unknownC4);
		ZeroVector(unknownD0);
		unknown0 = 0;
		flag1 = 1;
		flag2 = 0;
		flag3 = 1;
		flag4 = 1;
	}

	// FUNCTION: ENGINE 0x10669A70
	// EQUIVALENT: the same stores in the same order; the engine reads the object pointer again from the shape before each copy of the transform's diagonal, ours reads it once, and the zeroing of the accumulators is scheduled differently, 58.0 %
	CollisionShape::CollisionShape(const CollisionShape& other, CollisionObject* newObject)
	{
		unknown10.x = 0.0f;
		unknown10.y = 0.0f;
		unknown10.z = 0.0f;
		unknown1C.x = 0.0f;
		unknown1C.y = 0.0f;
		unknown1C.z = 0.0f;
		unknown28.x = 0.0f;
		unknown28.y = 0.0f;
		unknown28.z = 0.0f;
		unknown34.x = 0.0f;
		unknown34.y = 0.0f;
		unknown34.z = 0.0f;
		unknown58 = other.unknown58;
		unknown88 = other.unknown88;
		unknown8C = other.unknown8C;
		unknown90.x = other.unknown90.x;
		unknown90.y = other.unknown90.y;
		unknown90.z = other.unknown90.z;
		center.x = other.center.x;
		center.y = other.center.y;
		center.z = other.center.z;
		unknownA8 = 0;
		object = newObject;
		ClearAccumulated();
		Unknown10669160();
		radius = object->GetRadius();
		unknownAC.x = center.x;
		unknownAC.y = center.y;
		unknownAC.z = center.z;
		unknownB8.x = object->transform.m[0][0];
		unknownB8.y = object->transform.m[1][1];
		unknownB8.z = object->transform.m[2][2];
		ZeroVector(unknownC4);
		ZeroVector(unknownD0);
		flag1 = other.flag1;
		flag2 = other.flag2;
		flag4 = other.flag4;
	}

	// FUNCTION: ENGINE 0x10669C10
	void SetSpeedLimits(float linear, float angular)
	{
		if (linear < 0.0f)
		{
			linear = 0.0f;
		}
		gMaxLinearSpeed = linear;
		gMaxLinearSpeedSquared = linear * linear;
		float limit;
		if (angular < 0.0f)
		{
			limit = 0.0f;
		}
		else
		{
			limit = angular;
		}
		gMaxAngularSpeed = limit;
		gMaxAngularSpeedSquared = limit * limit;
	}

	// FUNCTION: ENGINE 0x10669C60
	void CollisionShape::Clear()
	{
		ClearAccumulated();
		ZeroVector(unknown10);
		ZeroVector(unknown1C);
	}

	// FUNCTION: ENGINE 0x10669C90
	void CollisionShape::Refresh()
	{
		math::Vector newCentre;
		math::SymmetricMatrix inertia;
		ComputeMassProperties(object, unknown88, &newCentre, &inertia);
		if (!(char)inertia.IsZero())
		{
			SetVectors(&inertia);
			SetPosition(newCentre);
		}
	}

	// FUNCTION: ENGINE 0x10669D00
	void CollisionShape::SetVelocity(math::Vector velocity)
	{
		if (flag4)
		{
			float lengthSquared = velocity.x * velocity.x + velocity.z * velocity.z + velocity.y * velocity.y;
			if (lengthSquared <= gMaxLinearSpeedSquared)
			{
				unknown10.x = velocity.x;
				unknown10.y = velocity.y;
				unknown10.z = velocity.z;
				return;
			}
			float scale = gMaxLinearSpeed / (float)sqrt(lengthSquared);
			unknown10.x = velocity.x * scale;
			unknown10.y = velocity.y * scale;
			unknown10.z = scale * velocity.z;
			return;
		}
		unknown10.x = velocity.x;
		unknown10.y = velocity.y;
		unknown10.z = velocity.z;
	}

	// FUNCTION: ENGINE 0x10669DB0
	void CollisionShape::SetAngularVelocity(math::Vector velocity)
	{
		if (flag4)
		{
			float lengthSquared = velocity.x * velocity.x + velocity.z * velocity.z + velocity.y * velocity.y;
			if (lengthSquared <= gMaxAngularSpeedSquared)
			{
				unknown1C.x = velocity.x;
				unknown1C.y = velocity.y;
				unknown1C.z = velocity.z;
				return;
			}
			float scale = gMaxAngularSpeed / (float)sqrt(lengthSquared);
			unknown1C.x = velocity.x * scale;
			unknown1C.y = velocity.y * scale;
			unknown1C.z = scale * velocity.z;
			return;
		}
		unknown1C.x = velocity.x;
		unknown1C.y = velocity.y;
		unknown1C.z = velocity.z;
	}

	// FUNCTION: ENGINE 0x10669E60
	void CollisionShape::MoveTo(math::Vector position, bool wake)
	{
		SetVelocity(position);
		if (wake != 0)
		{
			object->owner->SetCollisionMode(2);
		}
	}

	// FUNCTION: ENGINE 0x10669EB0
	void CollisionShape::Translate(math::Vector offset, bool wake)
	{
		SetAngularVelocity(offset);
		if (wake != 0)
		{
			object->owner->SetCollisionMode(2);
		}
	}

	// FUNCTION: ENGINE 0x10669F00
	void CollisionShape::AddScaledVelocity(math::Vector velocity)
	{
		if (flag1)
		{
			float scale = unknown88;
			math::Vector scaled;
			scaled.x = velocity.x * scale;
			scaled.y = velocity.y * scale;
			scaled.z = velocity.z * scale;
			unknown40.Add(unknown40, scaled);
		}
	}

	// FUNCTION: ENGINE 0x10669F60
	// EQUIVALENT: the same operations in the same order (the velocity from the offset, the torque of the offset about the centre carried through the inertia matrix); the engine loads the vector's components and the differences in another order, 79.5 %
	void CollisionShape::MoveTo(math::Vector from, math::Vector to, bool wake)
	{
		if (!object->owner->IsUnflagged() && !flag2)
		{
			if (wake != 0)
			{
				object->owner->SetCollisionMode(2);
			}
			float scale = unknown8C;
			math::Vector velocity;
			velocity.x = from.x * scale + unknown10.x;
			velocity.y = from.y * scale + unknown10.y;
			velocity.z = from.z * scale + unknown10.z;
			SetVelocity(velocity);
			float offsetZ = to.z - center.z;
			float offsetX = to.x - center.x;
			float offsetY = to.y - center.y;
			math::Vector torque;
			torque.x = offsetY * from.z - offsetZ * from.y;
			torque.y = offsetZ * from.x - from.z * offsetX;
			torque.z = offsetX * from.y - offsetY * from.x;
			math::Vector turn;
			unknown70.Transform(torque, turn);
			math::Vector angular;
			angular.Add(unknown1C, turn);
			SetAngularVelocity(angular);
		}
	}

	// FUNCTION: ENGINE 0x1066A0B0
	void CollisionShape::SetSize(int a, int b, float size)
	{
		const math::Matrix* from = (const math::Matrix*)a;
		const math::Matrix* to = (const math::Matrix*)b;
		float inverse = 1.0f / size;
		math::Vector velocity = unknown10;
		bool moving = engine::ComputeLinearVelocity(*from, *to, unknown90, inverse, velocity);
		MoveTo(velocity, moving);
		math::Vector angular = unknown1C;
		moving = engine::ComputeAngularVelocity(*from, *to, inverse, angular);
		Translate(angular, moving);
	}

	// FUNCTION: ENGINE 0x1066A1B0
	CollisionShape* CreateVolumeShape(CollisionVolume* volume, float size, CollisionObject* object)
	{
		const math::Vector* position = volume->GetPosition();
		math::Vector centre;
		math::SymmetricMatrix inertia;
		ComputeMassProperties(object, size, &centre, &inertia);
		return new CollisionShape(position, &inertia, size, object);
	}

	// FUNCTION: ENGINE 0x1066A220
	CollisionShape* CreateBoxShape(float size, int position, int inertia, CollisionObject* object)
	{
		math::Vector centre;
		math::SymmetricMatrix matrix;
		if (position == 0 || inertia == 0)
		{
			ComputeMassProperties(object, size, &centre, &matrix);
			if (position == 0)
			{
				position = (int)&centre;
			}
			if (inertia == 0)
			{
				inertia = (int)&matrix;
			}
		}
		return new CollisionShape((const math::Vector*)position, (const math::SymmetricMatrix*)inertia, size, object);
	}
}

// Kept copies of inline functions and template members this unit makes (compiler-made or header-defined, so the
// annotations stand without a definition)
// FUNCTION: ENGINE 0x10669110
