// ravenphysics::MassProperties (RTTI and reflection names): a content library object that gives a body its mass,
// centre of mass and inertia; the secondary physics joints refer to one by name. Constructor 0x10670E90, reflection
// 0x10670C40 / 0x10671030; the layout is not recovered (a size only).
#ifndef RAVENPHYSICS_MASSPROPERTIES_H
#define RAVENPHYSICS_MASSPROPERTIES_H

#include "code/content/loadinventory.h"

namespace ravenphysics
{
	class MassProperties : public content::MetaLoadObject
	{
	public:
		MassProperties();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		unsigned char unknown8[0x38];
	};
}

#endif
