// pure3d::ExpressionGroup (RTTI name; bases pure3d::Entity, pure3d::RefCounted, core::IRefCount): the named expressions
// of a face. Only the lookup of an expression by name, which is in another unit.
#ifndef PURE3D_EXPRESSIONGROUP_H
#define PURE3D_EXPRESSIONGROUP_H

#include "code/core/name.h"
#include "code/pure3d/entity.h"

namespace pure3d
{
	class ExpressionGroup : public Entity
	{
	public:
		// 0x10782E30: the index of the expression of that name, or 0xFFFF
		int FindExpression(const core::Name<core::CaseSensitiveKey>& name) const;
	};
}

#endif
