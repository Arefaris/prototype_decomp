// The system node of the mgraph library (0x10B76E80 - 0x10B77640): the reflection of the class and the description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#ifndef MGRAPH_SYSTEMNODE_H
#define MGRAPH_SYSTEMNODE_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterSystemNode();

	class __declspec(align(8)) SystemNode : public Node
	{
		MGRAPH_NODE_BODY(SystemNode, Node, 0x50);
	};

}

#endif
