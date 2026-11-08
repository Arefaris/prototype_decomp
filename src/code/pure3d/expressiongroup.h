// pure3d::ExpressionGroup (RTTI name; bases pure3d::Entity, pure3d::RefCounted, core::IRefCount): the named expressions
// of a face. Only the lookup of an expression by name, which is in another unit.
#ifndef PURE3D_EXPRESSIONGROUP_H
#define PURE3D_EXPRESSIONGROUP_H

#include "code/core/name.h"
#include "code/pure3d/entity.h"

namespace pure3d
{
	// RTTI: pure3d::Expression (bases pure3d::Entity, pure3d::RefCounted): one expression of a face. A key at index i
	// names the target it moves (a key of the mixer's expression state) and is reached at the time with the same
	// index; the times run in order
	class Expression : public Entity
	{
	public:
		unsigned int mKeyCount;
		unsigned int* mTargets;
		float* mTimes;
	};

	class ExpressionGroup : public Entity
	{
	public:
		// 0x10782E30: the index of the expression of that name, or 0xFFFF
		int FindExpression(const core::Name<core::CaseSensitiveKey>& name) const;

		Expression** mExpressions;
	};
}

#endif
