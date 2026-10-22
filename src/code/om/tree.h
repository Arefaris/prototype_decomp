// The red-black trees the om library keeps its registries in (the nodes sit inside the objects they order).
#ifndef OM_TREE_H
#define OM_TREE_H

namespace om
{
	// A node of an intrusive red-black tree
	struct TreeNode
	{
		TreeNode* left;
		TreeNode* right;
		TreeNode* parent;
		int color;
	};

	// The head of such a tree: the root and the node that stands for "no node" (0x14 bytes)
	class TreeHead
	{
	public:
		// 0x105B5D80 / 0x105B5DD0
		TreeHead();
		~TreeHead();

		TreeNode* root;
		TreeNode nil;
	};
}

#endif
