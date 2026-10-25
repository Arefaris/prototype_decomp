// The om library's method and property descriptions' common parts (0x105E4200 - 0x105E4630): the constructors that
// enter the description in the tree of its class.
#include "code/om/metaclass.h"
#include "code/om/metamethod.h"
#include "code/om/metaproperty.h"

namespace om
{
#ifdef NONMATCHING
	template<class T> bool TreeHead::InsertByName(T* object)
	{
		TreeNode* node = object != 0 ? &object->node : 0;
		TreeNode* parent = &nil;
		if (root != &nil)
		{
			unsigned int high = reinterpret_cast<const unsigned int*>(&object->name.key)[1];
			unsigned int low = reinterpret_cast<const unsigned int*>(&object->name.key)[0];
			TreeNode* current = root;
			do
			{
				parent = current;
				T* other = parent != 0 ? reinterpret_cast<T*>(reinterpret_cast<char*>(parent) - 8) : 0;
				unsigned int otherLow = reinterpret_cast<const unsigned int*>(&other->name.key)[0];
				unsigned int otherHigh = reinterpret_cast<const unsigned int*>(&other->name.key)[1];
				if (high < otherHigh || (high == otherHigh && low < otherLow))
				{
					current = parent->left;
				}
				else
				{
					if (high < otherHigh || (high == otherHigh && low <= otherLow))
					{
						return false;
					}
					current = parent->right;
				}
			}
			while (current != &nil);
		}
		node->parent = parent;
		if (parent == &nil)
		{
			root = node;
		}
		else
		{
			T* other = parent != 0 ? reinterpret_cast<T*>(reinterpret_cast<char*>(parent) - 8) : 0;
			unsigned int high = reinterpret_cast<const unsigned int*>(&object->name.key)[1];
			unsigned int low = reinterpret_cast<const unsigned int*>(&object->name.key)[0];
			unsigned int otherLow = reinterpret_cast<const unsigned int*>(&other->name.key)[0];
			unsigned int otherHigh = reinterpret_cast<const unsigned int*>(&other->name.key)[1];
			if (high < otherHigh || (high == otherHigh && low < otherLow))
			{
				parent->left = node;
			}
			else
			{
				if (high < otherHigh || (high == otherHigh && low <= otherLow))
				{
					return false;
				}
				parent->right = node;
			}
		}
		node->left = &nil;
		node->right = &nil;
		node->color = 1;
		while (node != root)
		{
			TreeNode* father = node->parent;
			if (father->color != 1)
			{
				break;
			}
			TreeNode* grandfather = father->parent;
			if (father == grandfather->left)
			{
				TreeNode* uncle = grandfather->right;
				if (uncle->color == 1)
				{
					father->color = 0;
					uncle->color = 0;
					node->parent->parent->color = 1;
					node = node->parent->parent;
				}
				else
				{
					if (node == father->right)
					{
						RotateLeft(father);
						node = father;
					}
					node->parent->color = 0;
					node->parent->parent->color = 1;
					RotateRight(node->parent->parent);
				}
			}
			else
			{
				TreeNode* uncle = grandfather->left;
				if (uncle->color == 1)
				{
					father->color = 0;
					uncle->color = 0;
					node->parent->parent->color = 1;
					node = node->parent->parent;
				}
				else
				{
					if (node == father->left)
					{
						RotateRight(father);
						node = father;
					}
					node->parent->color = 0;
					node->parent->parent->color = 1;
					RotateLeft(node->parent->parent);
				}
			}
		}
		root->color = 0;
		return true;
	}

#endif

	// FUNCTION: ENGINE 0x105E4210
	// NONMATCHING: the engine keeps the halves of the key in registers across the loop, ours reloads one (about 15 %)
#ifdef NONMATCHING
	template bool TreeHead::InsertByName<MetaPropertyBase>(MetaPropertyBase*);
#endif

	// FUNCTION: ENGINE 0x105E4430
	// NONMATCHING: the engine keeps the halves of the key in registers across the loop, ours reloads one (about 15 %)
#ifdef NONMATCHING
	template bool TreeHead::InsertByName<MetaMethodBase>(MetaMethodBase*);
#endif

	// FUNCTION: ENGINE 0x105E45F0
	MetaMethodBase::MetaMethodBase(MetaClassBase* owner, const ClassName& newName) :
		name(newName)
	{
		owner->methods.InsertByName(this);
	}

	// FUNCTION: ENGINE 0x105E43D0
	// EQUIVALENT: scheduling: the engine stores the second half of the name behind three of the other members (83.8 %)
	MetaPropertyBase::MetaPropertyBase(MetaTypeBase* newValueType, MetaClassBase* newOwner, const ClassName& newName,
		MetaMethodBase* newSetter, MetaMethodBase* newGetter, unsigned int newFlags) :
		name(newName),
		setter(newSetter),
		getter(newGetter),
		valueType(newValueType),
		owner(newOwner),
		flags(newFlags)
	{
		newOwner->properties.InsertByName(this);
	}
}
