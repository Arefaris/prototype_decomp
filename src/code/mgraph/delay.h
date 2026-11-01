// The delay node of the mgraph library (0x10B6E360 - 0x10B6F1A0): the reflection of the class and the description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#ifndef MGRAPH_DELAY_H
#define MGRAPH_DELAY_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterDelay();

	class __declspec(align(8)) Delay : public Node
	{
		MGRAPH_NODE_BODY(Delay, Node, 0x58);
	};

}

#endif
