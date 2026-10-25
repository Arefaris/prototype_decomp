// ravenphysics::ConstraintListFactory (RTTI): a content library object that lists the constraints between the objects
// of a physics object factory. Only the type and its reflection are named here (the unit is 0x106A5xxx - 0x106A6xxx and
// is not reconstructed).
#ifndef RAVENPHYSICS_CONSTRAINTLISTFACTORY_H
#define RAVENPHYSICS_CONSTRAINTLISTFACTORY_H

#include "code/content/loadinventory.h"

namespace ravenphysics
{
	// ConstraintListFactory: constructor 0x106A6CE0, reflection 0x106A56F0 / 0x106A6B70
	class ConstraintListFactory : public content::MetaLoadObject
	{
	public:
		ConstraintListFactory();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// Hands the pair mask of a body made of count objects on to every constraint (0x106A5FB0; name guess)
		void ApplyPairMask(unsigned char* mask, int count);

		unsigned char unknown8[0x10];
	};
}

#endif
