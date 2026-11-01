// The base of the node types of the mgraph library (0x10AD1180, 0x10AD1840 - 0x10AD18A0).
#include "code/mgraph/nodes.h"

namespace engine
{
	// 0x11327740: the registry of the node types (another unit defines it)
	extern om::TreeHead gTreeHeadObject10;
}

namespace mgraph
{
	// FUNCTION: ENGINE 0x10AD1860
	NodeTypeBase::NodeTypeBase(const unsigned int& newFlags, const om::ClassName& newName) :
		instanceCount(0),
		name(newName),
		flags(newFlags)
	{
		RegisterNodeType(this);
	}

	// FUNCTION: ENGINE 0x10AD1840
	// NONMATCHING: the engine keeps a stack slot and calls the helper without a tail call (72.7 %)
#ifdef NONMATCHING
	NodeTypeBase::~NodeTypeBase()
	{
		Unregister();
	}
#endif

	// FUNCTION: ENGINE 0x10AD1180
	// NONMATCHING: the engine saves ebx, esi and edi before the first lookup and shares the exits (22.2 %)
#ifdef NONMATCHING
	NodeTypeBase* FindNodeType(const type_info& type)
	{
		om::TreeNode* node = engine::gTreeHeadObject10.First();
		NodeTypeBase* nodeType = node != 0 ? reinterpret_cast<NodeTypeBase*>(reinterpret_cast<char*>(node) - 0x1C) : 0;
		while (nodeType != 0)
		{
			const type_info* nodeTypeInfo = nodeType->GetMetaType()->type;
			if (*nodeTypeInfo == type)
			{
				break;
			}
			node = engine::gTreeHeadObject10.Next(&nodeType->treeNode);
			nodeType = node != 0 ? reinterpret_cast<NodeTypeBase*>(reinterpret_cast<char*>(node) - 0x1C) : 0;
		}
		return nodeType;
	}
#endif
}
