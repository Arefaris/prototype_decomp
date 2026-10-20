// ravenphysics::Constraint (RTTI) and the constraints derived from it. The base class lives in the unit before
// physicsobject.cpp (0x1065ACB0 on); only what the reconstructed constraints touch is named and every name is a guess.
// The vftable has eight slots: 0 - 2 answer which side of the constraint a handle is, 3 is the destructor, 4 takes an
// object for one side, 5 turns the constraint by a matrix, 6 scales it by a vector and 7 is a pure function that the
// classes answer with a constant (the base class's 0x1065AC90 / 0x1065ACA0 do nothing).
#ifndef RAVENPHYSICS_CONSTRAINTS_CONSTRAINT_H
#define RAVENPHYSICS_CONSTRAINTS_CONSTRAINT_H

#include "code/content/metatype.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"
#include "code/ravenphysics/collision/collisionobject.h"

namespace ravenphysics
{
	// a scaled component by component by b (inlined by the engine in the constraints' scale functions)
	inline void Multiply(math::Vector& a, const math::Vector& b)
	{
		float y = b.y;
		float z = b.z;
		a.x = a.x * b.x;
		a.y = y * a.y;
		a.z = z * a.z;
	}

	class Constraint
	{
	public:
		// A constraint of the given kind, between no objects (0x1065E3E0)
		Constraint(int newKind);
		// The same between the objects the two handles name (0x1065EE40)
		Constraint(const CollisionHandle* first, const CollisionHandle* second, int newKind);

		// 0: 0 for the first handle, 1 for the second, -1 for another (0x1065ACB0)
		virtual int GetSide(const CollisionHandle* handle);
		// 1: 1 for the first handle, 0 for the second, -1 for another (0x1065ACE0)
		virtual int GetOtherSide(const CollisionHandle* handle);
		// 2: both answers at once, (0, 1) / (1, 0) / (-1, -1) (0x1065AD00)
		virtual void GetSides(const CollisionHandle* handle, int* side, int* other);
		// 3: the destructor (0x1065E410 for the base class)
		virtual ~Constraint();
		// 4: takes the object a handle names for one side and tells the detector (0x1065E450)
		virtual void SetObject(int side, const CollisionHandle* handle);
		// 5: turns the constraint by a matrix (0x1065AC90, nothing for the base class)
		virtual void Rotate(const math::Matrix* matrix);
		// 6: scales it by a vector (0x1065ACA0, nothing for the base class)
		virtual void ScaleBy(const math::Vector* scale);
		// 7: a constant of the class (the kind-specific answer; pure in the base)
		virtual unsigned short GetKind(int unused) = 0;

		// The reflection of the base class (0x1065CCD0 / 0x1065CD10)
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		CollisionHandle handle;       // 0x04 (the constraint's own place in the table)
		unsigned short kind;          // 0x08
		unsigned short unknownA;      // 0x0A
		unsigned short unknownC;      // 0x0C
		unsigned short unknownE;      // 0x0E
		CollisionObject* firstObject;   // 0x10
		CollisionObject* secondObject;  // 0x14
		CollisionHandle first;        // 0x18
		CollisionHandle second;       // 0x1C
		void* detector;               // 0x20
	};
}

#endif
