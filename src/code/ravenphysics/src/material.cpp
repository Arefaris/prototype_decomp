#include "code/core/heap.h"
#include "code/ravenphysics/material.h"
#include <new>

namespace engine
{
	namespace driving
	{
		// A pooled constant of the engine (symbols.txt)
		extern const float gOne;
	}
}

namespace ravenphysics
{
	// Keeps the loader in the list of the loaders in progress (add) or takes it out (0x1067E0D0, another unit)
	void Unknown1067E0D0(MaterialLoader* loader, bool add);

	// The tangential restitution of a new material, a pooled constant of the engine (0x10D975A4; name guessed)
	extern const float gDefaultTangentialRestitution;

	// Where the engine's table sits (symbols.txt)
	MaterialBase* gMaterials;
	int gMaterialCount;
	int gMaterialCapacity;

	// FUNCTION: ENGINE 0x1066A2A0
	content::ClassInfo* MaterialLoader::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ravenphysics::MaterialLoader";
		sInfo.code = "pn";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1066A2E0
	void MaterialBase::SetStaticFriction(float value)
	{
		staticFriction = value;
	}

	// FUNCTION: ENGINE 0x1066A2F0
	void MaterialBase::SetDynamicFriction(float value)
	{
		dynamicFriction = value;
	}

	// FUNCTION: ENGINE 0x1066A300
	void MaterialBase::SetFrictionWeight(float value)
	{
		frictionWeight = value;
	}

	// FUNCTION: ENGINE 0x1066A310
	void MaterialBase::SetRestitution(float value)
	{
		restitution = value;
	}

	// FUNCTION: ENGINE 0x1066A320
	void MaterialBase::SetTangentialRestitution(float value)
	{
		tangentialRestitution = value;
	}

	// FUNCTION: ENGINE 0x1066A330
	void MaterialBase::SetRollingFriction(float value)
	{
		rollingFriction = value;
	}

	// FUNCTION: ENGINE 0x1066A430
	MaterialLoader::~MaterialLoader()
	{
	}

	// FUNCTION: ENGINE 0x1066A340
	bool MaterialLoader::IsReady()
	{
		Unknown1067E0D0(this, false);
		return true;
	}

	// FUNCTION: ENGINE 0x1066A360
	MaterialBase* MaterialArray::Append()
	{
		count++;
		return data + count - 1;
	}

	// FUNCTION: ENGINE 0x1066A540
	MaterialArray::MaterialArray()
	{
		data = 0;
		count = 0;
		capacity = 0;
	}

	// FUNCTION: ENGINE 0x1066A6D0
	void MaterialArray::Allocate(int newCapacity, int unused)
	{
		data = (MaterialBase*)core::HeapAllocAligned(core::GetCurrentHeap(), newCapacity << 5, 16);
		capacity = newCapacity;
		count = 0;
	}

	// FUNCTION: ENGINE 0x1066A700
	void MaterialArray::Free(int unused)
	{
		if (data)
		{
			core::FreeAligned(data);
			data = 0;
			count = 0;
			capacity = 0;
		}
	}

	// FUNCTION: ENGINE 0x1066A3D0
	void MaterialBase::Init(const core::Name<core::CaseSensitiveKey>& newName)
	{
		name = newName;
		float one = engine::driving::gOne;
		float tangential = gDefaultTangentialRestitution;
		staticFriction = one;
		dynamicFriction = one;
		frictionWeight = one;
		restitution = 0.0f;
		tangentialRestitution = tangential;
		rollingFriction = 0.0f;
	}

	// FUNCTION: ENGINE 0x1066A420
	void MaterialLoader::SetName(const content::ObjectName& newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x1066A440
	void MaterialLoader::CopyToTable()
	{
		MaterialBase* material = &gMaterials[index];
		material->SetStaticFriction(staticFriction);
		material->SetDynamicFriction(dynamicFriction);
		material->SetFrictionWeight(frictionWeight);
		material->SetRestitution(restitution);
		material->SetTangentialRestitution(tangentialRestitution);
		material->SetRollingFriction(rollingFriction);
	}

	// FUNCTION: ENGINE 0x1066A4A0
	MaterialBase* FindMaterial(const core::Name<core::CaseSensitiveKey>& name)
	{
		unsigned int count = gMaterialCount;
		unsigned int i = 0;
		if (count > 0)
		{
			MaterialBase* material = gMaterials;
			do
			{
				if (material->name == name)
				{
					return &gMaterials[i];
				}
				i++;
				material++;
			}
			while (i < count);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1066A4F0
	unsigned char FindMaterialIndex(const core::Name<core::CaseSensitiveKey>& name)
	{
		unsigned int count = gMaterialCount;
		unsigned int i = 0;
		if (count > 0)
		{
			MaterialBase* material = gMaterials;
			do
			{
				if (material->name == name)
				{
					return (unsigned char)i;
				}
				i++;
				material++;
			}
			while (i < count);
		}
		return 0xFF;
	}

	// FUNCTION: ENGINE 0x1066A740
	content::MemberList* MaterialLoader::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<MaterialLoader, float, 0>("pn"),
				content::MemberOffset(&((MaterialLoader*)0)->staticFriction, (int)&((MaterialLoader*)0)->staticFriction),
				"staticFriction" },
			{ content::GetMemberPrimitiveMetaType<MaterialLoader, float, 1>("pn"),
				content::MemberOffset(&((MaterialLoader*)0)->dynamicFriction, (int)&((MaterialLoader*)0)->dynamicFriction),
				"dynamicFriction" },
			{ content::GetMemberPrimitiveMetaType<MaterialLoader, float, 2>("pn"),
				content::MemberOffset(&((MaterialLoader*)0)->frictionWeight, (int)&((MaterialLoader*)0)->frictionWeight),
				"frictionWeight" },
			{ content::GetMemberPrimitiveMetaType<MaterialLoader, float, 3>("pn"),
				content::MemberOffset(&((MaterialLoader*)0)->restitution, (int)&((MaterialLoader*)0)->restitution),
				"restitution" },
			{ content::GetMemberPrimitiveMetaType<MaterialLoader, float, 4>("pn"),
				content::MemberOffset(&((MaterialLoader*)0)->tangentialRestitution,
				(int)&((MaterialLoader*)0)->tangentialRestitution), "tangentialRestitution" },
			{ content::GetMemberPrimitiveMetaType<MaterialLoader, float, 5>("pn"),
				content::MemberOffset(&((MaterialLoader*)0)->rollingFriction, (int)&((MaterialLoader*)0)->rollingFriction),
				"rollingFriction" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1066A890
	// EQUIVALENT: the same stores and calls; the engine pushes the name's arguments between the vftable stores, 82.6 %
	MaterialLoader::MaterialLoader() : index(0)
	{
		Init(core::Name<core::CaseSensitiveKey>("undefined", 1));
	}

	// FUNCTION: ENGINE 0x1066A900
	void Unknown1066A900()
	{
		if (gMaterials)
		{
			core::FreeAligned(gMaterials);
			gMaterials = 0;
			gMaterialCount = 0;
			gMaterialCapacity = 0;
		}
	}

	// FUNCTION: ENGINE 0x1066A940
	// EQUIVALENT: the same calls in the same order; the engine duplicates the call of Init for the null slot of the placement new, 88.0 %
	unsigned char AddMaterial(const core::Name<core::CaseSensitiveKey>& name)
	{
		unsigned char found = FindMaterialIndex(name);
		if (found == 0xFF)
		{
			gMaterialCount++;
			MaterialBase* material = &gMaterials[gMaterialCount - 1];
			new(material) MaterialBase;
			material->Init(name);
			return (unsigned char)(gMaterialCount - 1);
		}
		return found;
	}

	// FUNCTION: ENGINE 0x1066A9A0
	void MaterialLoader::Slot3(int unused)
	{
		index = AddMaterial(name);
		CopyToTable();
		Unknown1067E0D0(this, true);
	}

	// FUNCTION: ENGINE 0x1066A9D0
	static void AddDefaultMaterial()
	{
		gMaterialCount = 0;
		AddMaterial(core::Name<core::CaseSensitiveKey>("Default", 1));
	}

	// FUNCTION: ENGINE 0x1066AA00
	void Unknown1066AA00(int count)
	{
		gMaterials = (MaterialBase*)core::HeapAllocAligned(core::GetCurrentHeap(), count << 5, 16);
		gMaterialCapacity = count;
		gMaterialCount = 0;
		AddDefaultMaterial();
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1066A3B0
// FUNCTION: ENGINE 0x1066A3C0
// FUNCTION: ENGINE 0x1066A550
// FUNCTION: ENGINE 0x1066A590
// FUNCTION: ENGINE 0x1066A5D0
// FUNCTION: ENGINE 0x1066A610
// FUNCTION: ENGINE 0x1066A650
// FUNCTION: ENGINE 0x1066A690
// FUNCTION: ENGINE 0x1066A8E0
