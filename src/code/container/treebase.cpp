// CFLAGS: /Ob2
// container::TreeBase (names guessed): an intrusive red-black tree whose functions take the comparison as a callback.
// The class is declared in code/container/map.h; this unit (0x10610630 - 0x10610DD0) holds the out-of-line members.
// The engine compiled it with the inliner on for every suitable function: the rotations are expanded at most call sites.
#include "code/container/map.h"

namespace container
{
	// FUNCTION: ENGINE 0x10610630
	TreeBase::Node* TreeBase::Next(Node* node) const
	{
		const Node* nilNode = &nil;
		Node* next = node->right;
		if (next != nilNode)
		{
			while (next->left != nilNode)
			{
				next = next->left;
			}
			return next != nilNode ? next : 0;
		}
		next = node->parent;
		while (next != nilNode && node == next->right)
		{
			node = next;
			next = node->parent;
		}
		return next != nilNode ? next : 0;
	}

	// FUNCTION: ENGINE 0x10610680
	void TreeBase::RotateLeft(Node* node)
	{
		Node* child = node->right;
		node->right = child->left;
		if (child->left != &nil)
		{
			child->left->parent = node;
		}
		child->parent = node->parent;
		if (node->parent == &nil)
		{
			root = child;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = child;
		}
		else
		{
			node->parent->right = child;
		}
		child->left = node;
		node->parent = child;
	}

	// FUNCTION: ENGINE 0x106106D0
	void TreeBase::RotateRight(Node* node)
	{
		Node* child = node->left;
		node->left = child->right;
		if (child->right != &nil)
		{
			child->right->parent = node;
		}
		child->parent = node->parent;
		if (node->parent == &nil)
		{
			root = child;
		}
		else if (node == node->parent->left)
		{
			node->parent->left = child;
		}
		else
		{
			node->parent->right = child;
		}
		child->right = node;
		node->parent = child;
	}

	// FUNCTION: ENGINE 0x10610730
	void TreeBase::RemoveFixup(Node* node)
	{
		while (node != root && !node->red)
		{
			if (node == node->parent->left)
			{
				Node* sibling = node->parent->right;
				if (sibling->red == 1)
				{
					sibling->red = 0;
					node->parent->red = 1;
					RotateLeft(node->parent);
					sibling = node->parent->right;
				}
				if (!sibling->left->red && !sibling->right->red)
				{
					sibling->red = 1;
					node = node->parent;
				}
				else
				{
					if (!sibling->right->red)
					{
						sibling->left->red = 0;
						sibling->red = 1;
						RotateRight(sibling);
						sibling = node->parent->right;
					}
					sibling->red = node->parent->red;
					node->parent->red = 0;
					sibling->right->red = 0;
					RotateLeft(node->parent);
					node = root;
				}
			}
			else
			{
				Node* sibling = node->parent->left;
				if (sibling->red == 1)
				{
					sibling->red = 0;
					node->parent->red = 1;
					RotateRight(node->parent);
					sibling = node->parent->left;
				}
				if (!sibling->right->red && !sibling->left->red)
				{
					sibling->red = 1;
					node = node->parent;
				}
				else
				{
					if (!sibling->left->red)
					{
						sibling->right->red = 0;
						sibling->red = 1;
						RotateLeft(sibling);
						sibling = node->parent->left;
					}
					sibling->red = node->parent->red;
					node->parent->red = 0;
					sibling->left->red = 0;
					RotateRight(node->parent);
					node = root;
				}
			}
		}
		node->red = 0;
	}

	// FUNCTION: ENGINE 0x10610990
	void TreeBase::Reset()
	{
		root = &nil;
		nil.left = &nil;
		nil.right = &nil;
		nil.parent = &nil;
		nil.red = false;
		count = 0;
	}

	// FUNCTION: ENGINE 0x106109B0
	bool TreeBase::IsEmpty() const
	{
		return root == &nil;
	}

	// FUNCTION: ENGINE 0x106109C0
	TreeBase::Node* TreeBase::Find(KeyCompare compare, const void* key) const
	{
		Node* node = root;
		while (node != &nil)
		{
			int order = compare(key, node);
			if (order < 0)
			{
				node = node->left;
			}
			else if (order > 0)
			{
				node = node->right;
			}
			else
			{
				return node;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10610A00
	TreeBase::Node* TreeBase::FindParent(KeyCompare compare, const void* key) const
	{
		Node* node = root;
		Node* nilNode = (Node*)&nil;
		Node* parent = nilNode;
		while (node != nilNode)
		{
			parent = node;
			int order = compare(key, node);
			if (order < 0)
			{
				node = node->left;
			}
			else
			{
				if (order <= 0)
				{
					return 0;
				}
				node = node->right;
			}
		}
		return parent;
	}

	// FUNCTION: ENGINE 0x10610A50
	TreeBase::Node* TreeBase::FindParent(KeyCompare compare, const void* key, bool* found) const
	{
		Node* node = root;
		Node* nilNode = (Node*)&nil;
		Node* parent = nilNode;
		while (node != nilNode)
		{
			parent = node;
			int order = compare(key, node);
			if (order < 0)
			{
				node = node->left;
			}
			else
			{
				if (order <= 0)
				{
					*found = true;
					return node;
				}
				node = node->right;
			}
		}
		*found = false;
		return parent;
	}

	// FUNCTION: ENGINE 0x10610AA0
	void TreeBase::Insert(Node* node, NodeCompare compare, Node* parent)
	{
		node->parent = parent;
		if (parent == &nil)
		{
			root = node;
		}
		else if (compare(node, parent) < 0)
		{
			parent->left = node;
		}
		else
		{
			parent->right = node;
		}
		node->left = &nil;
		node->right = &nil;
		node->red = 1;
		while (node != root && node->parent->red == 1)
		{
			if (node->parent == node->parent->parent->left)
			{
				Node* uncle = node->parent->parent->right;
				if (uncle->red == 1)
				{
					node->parent->red = 0;
					uncle->red = 0;
					node->parent->parent->red = 1;
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->right)
					{
						node = node->parent;
						RotateLeft(node);
					}
					node->parent->red = 0;
					node->parent->parent->red = 1;
					RotateRight(node->parent->parent);
				}
			}
			else
			{
				Node* uncle = node->parent->parent->left;
				if (uncle->red == 1)
				{
					node->parent->red = 0;
					uncle->red = 0;
					node->parent->parent->red = 1;
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						RotateRight(node);
					}
					node->parent->red = 0;
					node->parent->parent->red = 1;
					RotateLeft(node->parent->parent);
				}
			}
		}
		root->red = 0;
		count++;
	}

	// FUNCTION: ENGINE 0x10610C50
	void TreeBase::Remove(Node* node)
	{
		Node* spliced;
		if (node->left == &nil || node->right == &nil)
		{
			spliced = node;
		}
		else
		{
			spliced = Next(node);
		}
		Node* left = spliced->left;
		Node* child;
		if (left != &nil)
		{
			child = left;
		}
		else
		{
			child = spliced->right;
		}
		child->parent = spliced->parent;
		if (spliced->parent == &nil)
		{
			root = child;
		}
		else if (spliced == spliced->parent->left)
		{
			spliced->parent->left = child;
		}
		else
		{
			spliced->parent->right = child;
		}
		int black = spliced->red == 0;
		if (spliced != node)
		{
			spliced->parent = node->parent;
			spliced->left = node->left;
			spliced->right = node->right;
			spliced->red = node->red;
			if (spliced->parent != &nil)
			{
				if (spliced->parent->left == node)
				{
					spliced->parent->left = spliced;
				}
				else
				{
					spliced->parent->right = spliced;
				}
			}
			else
			{
				root = spliced;
			}
			if (spliced->left != &nil)
			{
				spliced->left->parent = spliced;
			}
			if (spliced->right->parent != &nil)
			{
				spliced->right->parent = spliced;
			}
		}
		if (black)
		{
			RemoveFixup(child);
		}
		count--;
	}

	// FUNCTION: ENGINE 0x10610D00
	TreeBase::Node* TreeBase::First() const
	{
		Node* node = root;
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

	// FUNCTION: ENGINE 0x10610D20
	bool TreeBase::ForEach(Visitor visit, void* context) const
	{
		Node* node = First();
		if (node != &nil)
		{
			while (node != 0)
			{
				if (!visit(node, context))
				{
					return false;
				}
				node = Next(node);
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10610D70
	void TreeBase::Clear(Deleter deleter, void* context)
	{
		Node* node = root;
		while (node != &nil)
		{
			for (;;)
			{
				while (node->left != &nil)
				{
					node = node->left;
				}
				if (node->right == &nil)
				{
					break;
				}
				node = node->right;
			}
			Node* leaf = node;
			node = leaf->parent;
			if (node->left != &nil)
			{
				node->left = &nil;
			}
			else
			{
				node->right = &nil;
			}
			deleter(leaf, context);
		}
		Reset();
	}

	// FUNCTION: ENGINE 0x10610DE0
	TreeBase::Node* TreeBase::InsertUnique(Node* node, NodeCompare compare)
	{
		Node* current = root;
		Node* nilNode = &nil;
		Node* parent = nilNode;
		while (current != nilNode)
		{
			parent = current;
			int order = compare(node, current);
			if (order < 0)
			{
				current = current->left;
			}
			else
			{
				if (order <= 0)
				{
					return 0;
				}
				current = current->right;
			}
		}
		Insert(node, compare, parent);
		return node;
	}
}
