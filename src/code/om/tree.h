// The red-black trees the om library keeps its registries in (the nodes sit inside the objects they order).
#ifndef OM_TREE_H
#define OM_TREE_H

#include "code/om/name.h"
#include <typeinfo>

namespace om
{
	class Entity;
	class EntityTypeBase;

	// A node of an intrusive red-black tree (the engine's colors are 0 for black and 1 for red)
	struct TreeNode
	{
		TreeNode* left;
		TreeNode* right;
		TreeNode* parent;
		int color;
	};

	// The head of such a tree: the root and the node that stands for "no node" (0x14 bytes). The operations are the
	// ones of the standard library's red-black tree of that time, over nodes that sit inside the objects they order.
	class TreeHead
	{
	public:
		// 0x105B5D80 / 0x105B5DD0
		TreeHead();
		~TreeHead();
		// 0x105B5DA0
		void Clear();
		// 0x105B5DE0
		bool IsEmpty() const;
		// 0x105B5DF0 / 0x105B5E10: the first and the last node, null when there is none
		TreeNode* First();
		TreeNode* Last();
		// 0x105B5E30 / 0x105B5E80: the node after and before another, null at the ends
		TreeNode* Next(TreeNode* node);
		TreeNode* Previous(TreeNode* node);
		// 0x105B5ED0: the node that many steps from the first one, null when there are not as many
		TreeNode* At(unsigned int index);
		// 0x105B5F10
		unsigned int Count();
		// 0x105B5F40 / 0x105B5F90
		void RotateLeft(TreeNode* node);
		void RotateRight(TreeNode* node);
		// 0x105B5FF0: the node after another, the head's own node at the end
		TreeNode* Successor(TreeNode* node);
		// 0x105B6030: restores the colors after a black node was taken out
		void FixAfterErase(TreeNode* node);
		// 0x105B6180
		bool Contains(TreeNode* node);
		// 0x105B61B0: takes the node out
		void Erase(TreeNode* node);
		// 0x105B5880: enters an entity under its name (name guessed); false when an entity of that name is there already
		bool InsertEntity(Entity* entity);
		// 0x105B4D40 / 0x105B4F60: enters an entity type under its name, and under its type_info (names guessed)
		bool InsertEntityTypeByName(EntityTypeBase* type);
		bool InsertEntityTypeByType(EntityTypeBase* type);
		// 0x105B54A0: the entity type registered for a type_info (name guessed)
		EntityTypeBase* FindEntityType(const type_info& type);
		// 0x105E4210 / 0x105E4430: enters an object that has its tree node at 8 and its name at 0x18; false when
		// an object of that name is there already
		template<class T> bool InsertByName(T* object);

		TreeNode* root;
		TreeNode nil;
	};
}

#endif
