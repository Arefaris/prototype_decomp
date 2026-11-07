// The type descriptions of the om library (0x105B62E0, 0x105B6FF0 - 0x105B7320; names guessed): every description is
// entered in two registries, by its name and by its type_info.
#include "code/om/metatype.h"
#include "code/om/tree.h"

namespace engine
{
	// 0x11276350 / 0x1127633C: the registries of the type descriptions by name and by type_info (declared by the unit that
	// constructs them)
	extern om::TreeHead gTreeHeadObject;
	extern om::TreeHead gTreeHeadObject2;
}

namespace om
{
	// FUNCTION: ENGINE 0x105B62E0
	const ClassName& MetaTypeBase::GetName() const
	{
		return name;
	}

	// FUNCTION: ENGINE 0x105B7320
	MetaTypeBase::MetaTypeBase(const ClassName& newName, const type_info* newType) :
		name(newName),
		type(newType)
	{
		engine::gTreeHeadObject.InsertMetaTypeByName(this);
		engine::gTreeHeadObject2.InsertMetaTypeByType(this);
	}

	// FUNCTION: ENGINE 0x105B7050
	// NONMATCHING: the engine computes the second node's address in eax, ours in ecx (95.6 %)
#ifdef NONMATCHING
	MetaTypeBase::~MetaTypeBase()
	{
		engine::gTreeHeadObject.Erase(&nodeByName);
		engine::gTreeHeadObject2.Erase(&nodeByType);
	}
#endif

	// FUNCTION: ENGINE 0x105B6FF0
	MetaTypeBase* FindMetaType(const type_info& type)
	{
		return engine::gTreeHeadObject2.FindMetaType(type);
	}
}
