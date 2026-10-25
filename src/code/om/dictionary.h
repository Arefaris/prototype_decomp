// om::Dictionary<Key, Value, Comparer> (RTTI: om::Dictionary<om::Name<...>, om::Name<...>, om::Comparer<...> >): an
// ordered map kept in a red-black tree whose nodes (0x20 bytes: the key, the value and the tree's node) are made by the
// om allocator. Only what the engine's reflection instances use is described.
#ifndef OM_DICTIONARY_H
#define OM_DICTIONARY_H

#include "code/om/allocation.h"
#include "code/om/textvalue.h"
#include "code/om/tree.h"
#include <new>

namespace om
{
	template<class Key> struct Comparer
	{
	};

	// Storage for the copies of a key and a value that are written
	struct NamePair
	{
		unsigned int first[2];
		unsigned int second[2];
	};
	template<class Key> inline bool WriteName(BinaryStream* stream, unsigned int* copy, const Key& name)
	{
		copy[1] = reinterpret_cast<const unsigned int*>(&name)[1];
		copy[0] = reinterpret_cast<const unsigned int*>(&name)[0];
		if (!stream->buffer->Write(copy, 8))
		{
			return false;
		}
		char terminator = 0;
		return stream->buffer->Write(&terminator, 1);
	}

	// Whether a pointer leads to something (out of line in the engine: 0x101168C0 for the nodes of a dictionary,
	// 0x108CF120 for the nodes of a text value)
	template<class T> bool IsValid(T* pointer);

	template<class Key, class Value, class Compare> class Dictionary
	{
	public:
		// A key and its value
		struct Entry
		{
			Key key;
			Value value;
		};

		struct Node : public Entry
		{
			Node(const Entry& entry) :
				Entry(entry)
			{
			}
			// 0x108CF520
			Node(const Key& newKey, const Value& newValue)
			{
				this->key = Key();
				this->value = Value();
				this->key = newKey;
				this->value = newValue;
			}
			static void* operator new(size_t)
			{
				return om::Allocate(NodeAllocationTag(), sizeof(Node), 8);
			}
			static void operator delete(void* node)
			{
				om::Release(node, sizeof(Node), 8);
			}
			// 0x108CF100 (the engine calls it once for the allocations of a function)
			__declspec(noinline) static const char* NodeAllocationTag()
			{
				return "";
			}

			TreeNode link;  // 0x10
		};

		Dictionary()
		{
		}
		Dictionary(const Dictionary& other)
		{
			Copy(other);
		}
		~Dictionary()
		{
			Clear();
		}
		Dictionary& operator=(const Dictionary& other)
		{
			Clear();
			Copy(other);
			return *this;
		}
		// 0x108CFE30: takes every node out
		__declspec(noinline) void Clear()
		{
			TreeNode* first;
			while ((first = tree.First()) != 0)
			{
				Node* node = reinterpret_cast<Node*>(reinterpret_cast<char*>(first) - 0x10);
				tree.Erase(&node->link);
				om::Release(node, sizeof(Node), 8);
			}
		}
		// 0x108CFFD0: enters a node in the tree (the order of the keys; false for a node that was there already)
		bool Insert(Node* node);
		// 0x108D04B0: enters a node of the key and the value
		void Add(const Key& key, const Value& value)
		{
			Insert(new Node(key, value));
		}
		OM_ALLOCATION(Dictionary);

		// The node of a tree link, null for no link
		static Node* NodeOf(TreeNode* link)
		{
			Node* node;
			if (link != 0)
			{
				node = reinterpret_cast<Node*>(reinterpret_cast<char*>(link) - 0x10);
			}
			else
			{
				node = 0;
			}
			return node;
		}
		Node* FirstNode()
		{
			return NodeOf(tree.First());
		}
		Node* NextNode(Node* node)
		{
			return NodeOf(tree.Next(node != 0 ? &node->link : 0));
		}
		// Enters a copy of every node of the other dictionary (the next one is found before the current is used)
		__forceinline void Copy(const Dictionary& other)
		{
			Dictionary& source = const_cast<Dictionary&>(other);
			Node* current = NodeOf(source.tree.First());
			Node* next = current != 0 ? NodeOf(source.tree.Next(&current->link)) : 0;
			while (IsValid(current))
			{
				Insert(new Node(current->key, current->value));
				current = next;
				next = current != 0 ? NodeOf(source.tree.Next(&current->link)) : 0;
			}
		}

		// The text and binary forms of the dictionary (the functions of the namespace, one set per instance): in text a
		// node "Items" with a node "Item" for each entry, that has the nodes "Key" and "Value"; in binary the number of
		// entries and then the keys and the values with a terminator after each
		friend bool ReadText(const TextValue* text, Dictionary* dictionary)
		{
			dictionary->Clear();
			TextValue* node = text->FindChild("Items");
			if (node == 0)
			{
				return true;
			}
			node = node->FindChild("Item");
			while (node != 0 && node->text == String::Wrap("Item"))
			{
				TextValue* keyNode = node->FindChild("Key");
				TextValue* valueNode = node->FindChild("Value");
				Key key;
				Value value;
				if (IsValid(keyNode) && IsValid(valueNode))
				{
					ReadText(keyNode, &key);
					ReadText(valueNode, &value);
					dictionary->Add(key, value);
				}
				node = node->parent->children.Next(node);
			}
			return true;
		}
		friend void WriteText(TextValue* text, const Dictionary& dictionary)
		{
			TextNode* items = new TextNode(text, String::Wrap("Items"));
			Dictionary& source = const_cast<Dictionary&>(dictionary);
			for (Node* node = source.FirstNode(); node != 0; node = source.NextNode(node))
			{
				TextNode* item = new TextNode(items, String::Wrap("Item"));
				new TextNode(item, String::Wrap("Key"));
				new TextNode(item, String::Wrap("Value"));
			}
		}
		friend bool ReadBinary(BinaryStream* stream, Dictionary* dictionary)
		{
			unsigned int count = 0;
			bool ok = ReadBinary(stream, &count);
			if (ok)
			{
				for (unsigned int i = 0; i < count; i++)
				{
					Entry entry;
					ok = ok && ReadBinary(stream, &entry.key) && ReadBinary(stream, &entry.value);
					dictionary->Insert(new Node(entry));
				}
			}
			return ok;
		}
		friend bool WriteBinary(BinaryStream* stream, const Dictionary& dictionary)
		{
			Dictionary& source = const_cast<Dictionary&>(dictionary);
			bool ok = WriteBinary(stream, source.tree.Count());
			for (Node* node = source.FirstNode(); IsValid(node); node = source.NextNode(node))
			{
				NamePair copy;
				ok = ok && WriteName(stream, copy.first, node->key) && WriteName(stream, copy.second, node->value);
			}
			return ok;
		}

		TreeHead tree;
	};

	template<class Key, class Value, class Compare> const char* Dictionary<Key, Value, Compare>::AllocationTag()
	{
		return "";
	}
}

#endif
