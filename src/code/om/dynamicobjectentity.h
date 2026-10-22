// The entity that wraps a dynamic object (RTTI: om::DynamicObjectEntity, 0x48 bytes).
#ifndef OM_DYNAMICOBJECTENTITY_H
#define OM_DYNAMICOBJECTENTITY_H

#include "code/om/entity.h"

namespace om
{
	class DynamicObjectEntity : public Entity
	{
	public:
		// 0x105C1D10
		explicit DynamicObjectEntity(const ClassName& newName);
		virtual ~DynamicObjectEntity();
		OM_ENTITY_ALLOCATION(DynamicObjectEntity);

		char unknown10[0x38];
	};
}

#endif
