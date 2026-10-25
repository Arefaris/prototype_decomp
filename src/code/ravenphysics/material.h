// The physics materials (RTTI: ravenphysics::MaterialBase and ravenphysics::MaterialLoader). A material is a name and
// six friction and restitution numbers; the loader is the content library object that reads one and enters it in the
// library's table of materials (0x1127D50C), where the collision records find it by its index. Unit 0x1066A2A0 -
// 0x1066AA10 (no assert path, so the file name is a guess). The reflected member names are the engine's own.
#ifndef RAVENPHYSICS_MATERIAL_H
#define RAVENPHYSICS_MATERIAL_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"

namespace ravenphysics
{
	// A material (0x20 bytes); the table keeps them in a run of the heap
	class MaterialBase
	{
	public:
		// 0x1066A3B0 / 0x1066A3C0: a material with the empty name
		MaterialBase()
		{
		}
		~MaterialBase()
		{
		}

		// Takes the name and the default numbers (0x1066A3D0)
		void Init(const core::Name<core::CaseSensitiveKey>& newName);

		// The numbers' setters (0x1066A2E0 - 0x1066A330)
		void SetStaticFriction(float value);
		void SetDynamicFriction(float value);
		void SetFrictionWeight(float value);
		void SetRestitution(float value);
		void SetTangentialRestitution(float value);
		void SetRollingFriction(float value);

		core::Name<core::CaseSensitiveKey> name;  // 0x00
		float staticFriction;                     // 0x08
		float dynamicFriction;                    // 0x0C
		float frictionWeight;                     // 0x10
		float restitution;                        // 0x14
		float tangentialRestitution;              // 0x18
		float rollingFriction;                    // 0x1C
	};

	class MaterialLoader : public MaterialBase, public content::MetaLoadObject
	{
	public:
		// 0x1066A890
		MaterialLoader();
		// 0x1066A430 (deleting destructor 0x1066A8E0)
		virtual ~MaterialLoader();
		// Slot 3 (0x1066A9A0): files the material in the table and copies the numbers over
		virtual void Slot3(int unused);
		// Slot 4 (0x1066A340): takes the loader out of the library's list of loaders in progress
		virtual bool IsReady();
		// Slot 6 (0x1066A420)
		virtual void SetName(const content::ObjectName& newName);

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x1066A440: the numbers into the table's material of this loader
		void CopyToTable();

		unsigned char index;          // 0x28 (the material's place in the table)
		unsigned char unknown29[3];
		int unknown2C;
	};

	// A run of materials with the room it has (0x1066A360 - 0x1066A700; the table is the same in globals)
	struct MaterialArray
	{
		// 0x1066A540: an empty run
		MaterialArray();
		// 0x1066A6D0: makes room for capacity materials from the current heap; the second argument is not used
		void Allocate(int capacity, int unused);
		// 0x1066A700: gives the run back; the argument is not used
		void Free(int unused);
		// 0x1066A360: takes the next place
		MaterialBase* Append();

		MaterialBase* data;
		int count;
		int capacity;
	};

	// The table of materials: the run (0x1127D50C), the number in it (0x1127D510) and the room (0x1127D514)
	extern MaterialBase* gMaterials;
	extern int gMaterialCount;
	extern int gMaterialCapacity;

	// The material of a name, null when there is none (0x1066A4A0), and its place in the table, 0xFF when there is none
	// (0x1066A4F0)
	MaterialBase* FindMaterial(const core::Name<core::CaseSensitiveKey>& name);
	unsigned char FindMaterialIndex(const core::Name<core::CaseSensitiveKey>& name);
	// The place of the material of a name; a name the table has not got is added (0x1066A940)
	unsigned char AddMaterial(const core::Name<core::CaseSensitiveKey>& name);
	// Frees the table (0x1066A900), makes it with room for count materials and the default one in it (0x1066AA00)
	void Unknown1066A900();
	void Unknown1066AA00(int count);
}

#endif
