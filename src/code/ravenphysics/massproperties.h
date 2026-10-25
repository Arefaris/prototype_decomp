// ravenphysics::MassProperties (RTTI and reflection names): a content library object that gives a body its mass,
// centre of mass and inertia; the secondary physics joints refer to one by name. Unit 0x10670BC0 - 0x10671190 (no
// assert path, so the file name is a guess). The reflected member names are the engine's own.
#ifndef RAVENPHYSICS_MASSPROPERTIES_H
#define RAVENPHYSICS_MASSPROPERTIES_H

#include "code/content/loadinventory.h"
#include "code/core/name.h"
#include "code/math/vector.h"

namespace ravenphysics
{
	class CollisionObject;

	class MassProperties : public content::MetaLoadObject
	{
	public:
		// 0x10670E90
		MassProperties();
		// 0x10670F10 (deleting destructor 0x10671190)
		virtual ~MassProperties();
		// Slot 3 (0x10670C80): puts the properties in the library's list of properties in progress
		virtual void Slot3(int unused);
		// Slot 4 (0x10670C90): takes them out again
		virtual bool IsReady();
		// Slot 6 (0x10670F20)
		virtual void SetName(const content::ObjectName& newName);

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// Gives a collision object its mass, inertia and centre of mass (0x10670CA0; name guess)
		void ApplyTo(CollisionObject* object);

		core::Name<core::CaseSensitiveKey> name;  // 0x08
		float mass;                               // 0x10
		math::Vector diagonalInertia;             // 0x14
		math::Vector nonDiagonalInertia;          // 0x20
		bool scaleInertia;                        // 0x2C
		bool overrideCenterOfMass;                // 0x2D
		bool displaceCenterOfMass;                // 0x2E
		math::Vector centerOfMass;                // 0x30
		int unknown3C;
	};
}

#endif
