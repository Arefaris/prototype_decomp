// The enumeration reflection's base (0x105EB8C0 - 0x105EBCD0): the constructor, the lookups of an entry by value and
// by name, and the destructor that deletes the entries.
#include "code/om/metaenum.h"

namespace om
{
	// FUNCTION: ENGINE 0x105EB8C0
	MetaEnumBase::MetaEnumBase(const ClassName& newName, const type_info* newType) :
		MetaTypeBase(newName, newType)
	{
	}

	// FUNCTION: ENGINE 0x105EBC70
	MetaEnumBase::~MetaEnumBase()
	{
		values.Clear();
		names.DeleteAllEnumValues();
	}

	// FUNCTION: ENGINE 0x105EBCB0
	const EnumValue* MetaEnumBase::FindValue(const ClassName& valueName)
	{
		return values.FindByName(&valueName);
	}

	// FUNCTION: ENGINE 0x105EB9D0
	void MetaEnumBase::WriteValueName(int value)
	{
		names.FindFirstByValue(&value);
	}

	// FUNCTION: ENGINE 0x105EB690
	const char* EnumValue::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105EBCF0
	void MetaEnumBase::AddValue(const ClassName& valueName, int value)
	{
		EnumValue* entry = new EnumValue(value, valueName);
		names.InsertByValue(entry);
		values.InsertEnumValueByName(entry);
	}

	// FUNCTION: ENGINE 0x105EB6E0
	// NONMATCHING: the engine places the failing return behind the rest and keeps the result in a register (18.4 %)
#ifdef NONMATCHING
	bool TreeHead::InsertByValue(EnumValue* entry)
	{
		TreeNode* node = &entry->valueNode;
		TreeNode* parent = &nil;
		if (root != &nil)
		{
			TreeNode* current = root;
			do
			{
				parent = current;
				int difference = entry->value - reinterpret_cast<EnumValue*>(parent)->value;
				if (difference < 0)
				{
					current = parent->left;
				}
				else
				{
					if (difference <= 0)
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
		else if (entry->value - reinterpret_cast<EnumValue*>(parent)->value < 0)
		{
			parent->left = node;
		}
		else
		{
			if (entry->value - reinterpret_cast<EnumValue*>(parent)->value < 1)
			{
				return false;
			}
			parent->right = node;
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

	// FUNCTION: ENGINE 0x105EB910
	TreeNode* TreeHead::FindFirstByValue(const int* value)
	{
		TreeNode* node = root;
		if (node != &nil)
		{
			do
			{
				int difference = *value - reinterpret_cast<EnumValue*>(node)->value;
				if (difference < 0)
				{
					node = node->left;
				}
				else if (difference <= 0)
				{
					TreeNode* previous = Previous(node);
					while (previous != 0 && *value - reinterpret_cast<EnumValue*>(previous)->value == 0)
					{
						node = previous;
						previous = Previous(previous);
					}
					return node;
				}
				else
				{
					node = node->right;
				}
			}
			while (node != &nil);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105EBA10
	// NONMATCHING: the engine keeps the name's halves in registers across the descent and tests them in another order (69.1 %)
#ifdef NONMATCHING
	EnumValue* TreeHead::FindByName(const ClassName* name)
	{
		TreeNode* node = root;
		if (node != &nil)
		{
			do
			{
				EnumValue* value = node != 0 ? reinterpret_cast<EnumValue*>(reinterpret_cast<char*>(node) - 0x10) : 0;
				unsigned __int64 valueKey = value->name.key;
				if (name->key < valueKey)
				{
					node = node->left;
				}
				else if (name->key <= valueKey)
				{
					TreeNode* previous = Previous(node);
					while (previous != 0)
					{
						unsigned __int64 previousKey = *reinterpret_cast<unsigned __int64*>(reinterpret_cast<char*>(previous) + 0x18);
						if (name->key < previousKey || previousKey < name->key)
						{
							break;
						}
						node = previous;
						previous = Previous(previous);
					}
					return node != 0 ? reinterpret_cast<EnumValue*>(reinterpret_cast<char*>(node) - 0x10) : 0;
				}
				else
				{
					node = node->right;
				}
			}
			while (node != &nil);
		}
		return 0;
	}
#endif

	// FUNCTION: ENGINE 0x105EB9E0
	// NONMATCHING: the engine does not rotate the loop (the test stays at the top, 37.7 %)
#ifdef NONMATCHING
	void TreeHead::DeleteAllEnumValues()
	{
		for (;;)
		{
			TreeNode* node = First();
			if (node == 0)
			{
				break;
			}
			Erase(node);
			Release(node, sizeof(EnumValue), __alignof(EnumValue));
		}
	}
#endif
}
