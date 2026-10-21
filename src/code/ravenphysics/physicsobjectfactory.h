// ravenphysics::PhysicsObjectFactory (RTTI name; bases ravenphysics::AbstractPhysicsObjectFactory,
// content::MetaLoadObject): a content library object that makes physics objects. Only the type is known here (the
// objects that refer to one by name look it up by the type); its unit is not reconstructed.
#ifndef RAVENPHYSICS_PHYSICSOBJECTFACTORY_H
#define RAVENPHYSICS_PHYSICSOBJECTFACTORY_H

#include "code/content/loadinventory.h"

namespace ravenphysics
{
	class PhysicsObjectFactory : public content::MetaLoadObject
	{
	public:
		unsigned char unknown8[0x1];
	};
}

#endif
