// ravenphysics::ConstraintListFactory (RTTI): a content library object that lists the constraints between the objects
// of a physics object factory. Only the type and its reflection are named here (the unit is 0x106A5xxx - 0x106A6xxx and
// is not reconstructed).
#ifndef RAVENPHYSICS_CONSTRAINTLISTFACTORY_H
#define RAVENPHYSICS_CONSTRAINTLISTFACTORY_H

#include "code/content/loadinventory.h"

namespace ravenphysics
{
	class Constraint;

	// ConstraintListFactory: constructor 0x106A6CE0, reflection 0x106A56F0 / 0x106A6B70
	class ConstraintListFactory : public content::MetaLoadObject
	{
	public:
		// A constraint between two objects of the factory's body, named by their positions (12 bytes; RTTI name
		// ravenphysics::ConstraintListFactory::ConstraintSpec)
		struct ConstraintSpec
		{
			// Between the objects 0 and 1, no constraint (0x106A5730)
			ConstraintSpec();
			// Deletes the constraint (0x106A5750)
			~ConstraintSpec();
			// Clears the bit of the pair in a mask of a body made of count objects (0x106A5770; name guess)
			void ClearPair(unsigned char* mask, int count);

			unsigned int objectAIndex;
			unsigned int objectBIndex;
			Constraint* constraint;
		};

		ConstraintListFactory();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// Hands the pair mask of a body made of count objects on to every constraint (0x106A5FB0; name guess)
		void ApplyPairMask(unsigned char* mask, int count);

		ConstraintSpec* specsBegin;      // 0x08
		ConstraintSpec* specsEnd;        // 0x0C
		ConstraintSpec* specsCapacity;   // 0x10
		unsigned char unknown14[4];
	};
}

#endif
