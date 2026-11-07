// The om library's class reflection base (0x105C0C60 - 0x105C0DE0): the constructor that enters the description in the
// registries of the classes, and the destructor that takes it out and deletes the attributes, methods and properties.
#include "code/om/metaattrib.h"
#include "code/om/metaclass.h"
#include "code/om/metamethod.h"
#include "code/om/metaproperty.h"

namespace engine
{
	// 0x112767DC / 0x112767F0: the registries of the class descriptions by name and by type_info
	extern om::TreeHead gTreeHeadObject3;
	extern om::TreeHead gTreeHeadObject4;
}

namespace om
{
#ifdef NONMATCHING
	template<class T> void TreeHead::DeleteAll()
	{
		for (;;)
		{
			TreeNode* node = First();
			T* description = node != 0 ? reinterpret_cast<T*>(reinterpret_cast<char*>(node) - 8) : 0;
			if (description == 0)
			{
				break;
			}
			Erase(&description->node);
			delete description;
		}
	}
#endif

	// FUNCTION: ENGINE 0x105C0750
	// NONMATCHING: the engine loads the vftable through eax, ours through edx (93.8 %)
#ifdef NONMATCHING
	template void TreeHead::DeleteAll<MetaAttribBase>();
#endif
	// FUNCTION: ENGINE 0x105C07B0
	// NONMATCHING: the engine loads the vftable through eax, ours through edx (93.8 %)
#ifdef NONMATCHING
	template void TreeHead::DeleteAll<MetaPropertyBase>();
#endif
	// FUNCTION: ENGINE 0x105C0780
	// NONMATCHING: the engine loads the vftable through eax, ours through edx (93.8 %)
#ifdef NONMATCHING
	template void TreeHead::DeleteAll<MetaMethodBase>();
#endif

	// FUNCTION: ENGINE 0x105C0D80
	MetaClassBase::MetaClassBase(const ClassName& newName, const type_info* newType, MetaClassBase* newParent) :
		MetaTypeBase(newName, newType),
		parent(newParent)
	{
		engine::gTreeHeadObject3.InsertMetaClassByName(this);
		engine::gTreeHeadObject4.InsertMetaClassByType(this);
	}

	// FUNCTION: ENGINE 0x105C0C60
	// NONMATCHING: the engine keeps the node of the second registry in eax, ours in ecx (98.1 %)
#ifdef NONMATCHING
	MetaClassBase::~MetaClassBase()
	{
		engine::gTreeHeadObject3.Erase(&nodeByNameRegistry);
		engine::gTreeHeadObject4.Erase(&nodeByTypeRegistry);
		attributes.DeleteAll<MetaAttribBase>();
		properties.DeleteAll<MetaPropertyBase>();
		methods.DeleteAll<MetaMethodBase>();
	}
#endif
}
