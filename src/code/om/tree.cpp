// The red-black tree of the om library (0x105B5D80 - 0x105B6255).
#include "code/om/tree.h"

namespace om
{
	// FUNCTION: ENGINE 0x105B5D80
	TreeHead::TreeHead()
	{
		nil.left = &nil;
		nil.right = &nil;
		nil.parent = &nil;
		nil.color = 0;
		root = &nil;
	}

	// FUNCTION: ENGINE 0x105B5DA0
	void TreeHead::Clear()
	{
		nil.left = &nil;
		nil.right = &nil;
		nil.parent = &nil;
		nil.color = 0;
		root = &nil;
	}

	// FUNCTION: ENGINE 0x105B5DD0
	TreeHead::~TreeHead()
	{
	}

	// FUNCTION: ENGINE 0x105B5DE0
	bool TreeHead::IsEmpty() const
	{
		if (root == &nil)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B5DF0
	TreeNode* TreeHead::First()
	{
		TreeNode* node = root;
		if (node == &nil)
		{
			return 0;
		}
		while (node->left != &nil)
		{
			node = node->left;
		}
		return node;
	}

	// FUNCTION: ENGINE 0x105B5E10
	TreeNode* TreeHead::Last()
	{
		TreeNode* node = root;
		if (node == &nil)
		{
			return 0;
		}
		while (node->right != &nil)
		{
			node = node->right;
		}
		return node;
	}

	// FUNCTION: ENGINE 0x105B5E30
	TreeNode* TreeHead::Next(TreeNode* node)
	{
		TreeNode* end = &nil;
		TreeNode* next = node->right;
		if (next != end)
		{
			while (next->left != end)
			{
				next = next->left;
			}
		}
		else
		{
			next = node->parent;
			while (next != end && node == next->right)
			{
				node = next;
				next = next->parent;
			}
		}
		return next != end ? next : 0;
	}

	// FUNCTION: ENGINE 0x105B5E80
	TreeNode* TreeHead::Previous(TreeNode* node)
	{
		TreeNode* end = &nil;
		TreeNode* previous = node->left;
		if (previous != end)
		{
			while (previous->right != end)
			{
				previous = previous->right;
			}
		}
		else
		{
			previous = node->parent;
			while (previous != end && node == previous->left)
			{
				node = previous;
				previous = previous->parent;
			}
		}
		return previous != end ? previous : 0;
	}

	// FUNCTION: ENGINE 0x105B5ED0
	// EQUIVALENT: the engine leaves through a return of zero of its own when the first node is missing (98.2 %)
	TreeNode* TreeHead::At(unsigned int index)
	{
		unsigned int position = 0;
		TreeNode* node = First();
		if (node != 0 && index != 0)
		{
			do
			{
				node = Next(node);
				if (node == 0)
				{
					return 0;
				}
				position++;
			}
			while (position != index);
		}
		return node;
	}

	// FUNCTION: ENGINE 0x105B5F10
	unsigned int TreeHead::Count()
	{
		unsigned int count = 0;
		TreeNode* node = First();
		while (node != 0)
		{
			count++;
			node = Next(node);
		}
		return count;
	}

	// FUNCTION: ENGINE 0x105B5F40
	void TreeHead::RotateLeft(TreeNode* node)
	{
		TreeNode* promoted = node->right;
		node->right = promoted->left;
		if (promoted->left != &nil)
		{
			promoted->left->parent = node;
		}
		promoted->parent = node->parent;
		if (node->parent == &nil)
		{
			root = promoted;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = promoted;
		}
		else
		{
			node->parent->right = promoted;
		}
		promoted->left = node;
		node->parent = promoted;
	}

	// FUNCTION: ENGINE 0x105B5F90
	void TreeHead::RotateRight(TreeNode* node)
	{
		TreeNode* promoted = node->left;
		node->left = promoted->right;
		if (promoted->right != &nil)
		{
			promoted->right->parent = node;
		}
		promoted->parent = node->parent;
		if (node->parent == &nil)
		{
			root = promoted;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = promoted;
		}
		else
		{
			node->parent->right = promoted;
		}
		promoted->right = node;
		node->parent = promoted;
	}

	// FUNCTION: ENGINE 0x105B5FF0
	TreeNode* TreeHead::Successor(TreeNode* node)
	{
		TreeNode* end = &nil;
		TreeNode* next = node->right;
		if (next != end)
		{
			while (next->left != end)
			{
				next = next->left;
			}
		}
		else
		{
			next = node->parent;
			while (next != end && node == next->right)
			{
				node = next;
				next = next->parent;
			}
		}
		return next;
	}

	// FUNCTION: ENGINE 0x105B6180
	bool TreeHead::Contains(TreeNode* node)
	{
		TreeNode* current = First();
		while (current != 0)
		{
			if (current == node)
			{
				return true;
			}
			current = Next(current);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105B6030
	void TreeHead::FixAfterErase(TreeNode* node)
	{
		TreeNode* end = &nil;
		while (node != root && node->color == 0)
		{
			if (node == node->parent->left)
			{
				TreeNode* sibling = node->parent->right;
				if (sibling->color == 1)
				{
					sibling->color = 0;
					node->parent->color = 1;
					RotateLeft(node->parent);
					sibling = node->parent->right;
				}
				if (sibling->left->color == 0 && sibling->right->color == 0)
				{
					sibling->color = 1;
					node = node->parent;
				}
				else
				{
					if (sibling->right->color == 0)
					{
						sibling->left->color = 0;
						sibling->color = 1;
						RotateRight(sibling);
						sibling = node->parent->right;
					}
					sibling->color = node->parent->color;
					node->parent->color = 0;
					sibling->right->color = 0;
					RotateLeft(node->parent);
					node = root;
				}
			}
			else
			{
				TreeNode* sibling = node->parent->left;
				if (sibling->color == 1)
				{
					sibling->color = 0;
					node->parent->color = 1;
					RotateRight(node->parent);
					sibling = node->parent->left;
				}
				if (sibling->right->color == 0 && sibling->left->color == 0)
				{
					sibling->color = 1;
					node = node->parent;
				}
				else
				{
					if (sibling->left->color == 0)
					{
						sibling->right->color = 0;
						sibling->color = 1;
						RotateLeft(sibling);
						sibling = node->parent->left;
					}
					sibling->color = node->parent->color;
					node->parent->color = 0;
					sibling->left->color = 0;
					RotateRight(node->parent);
					node = root;
				}
			}
		}
		node->color = 0;
	}

	// FUNCTION: ENGINE 0x105B61B0
	void TreeHead::Erase(TreeNode* node)
	{
		TreeNode* end = &nil;
		TreeNode* removed;
		if (node->left == end || node->right == end)
		{
			removed = node;
		}
		else
		{
			removed = Successor(node);
		}
		TreeNode* child = removed->left != end ? removed->left : removed->right;
		child->parent = removed->parent;
		TreeNode* parent = removed->parent;
		if (parent == end)
		{
			root = child;
		}
		else if (removed == parent->left)
		{
			parent->left = child;
		}
		else
		{
			parent->right = child;
		}
		int blackRemoved = removed->color == 0;
		if (removed != node)
		{
			removed->parent = node->parent;
			removed->left = node->left;
			removed->right = node->right;
			removed->color = node->color;
			parent = removed->parent;
			if (parent != end)
			{
				if (parent->left == node)
				{
					parent->left = removed;
				}
				else
				{
					parent->right = removed;
				}
			}
			else
			{
				root = removed;
			}
			if (removed->left != end)
			{
				removed->left->parent = removed;
			}
			if (removed->right->parent != end)
			{
				removed->right->parent = removed;
			}
		}
		if (blackRemoved)
		{
			FixAfterErase(child);
		}
	}
}
