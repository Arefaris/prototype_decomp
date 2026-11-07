// The min-max distance node of the mgraph library (0x10B73A00 - 0x10B748C0): the reflection of the class and the description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#ifndef MGRAPH_MINMAXDISTANCE_H
#define MGRAPH_MINMAXDISTANCE_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterMinMaxDistance();

	class __declspec(align(8)) MinMaxDistance : public Node
	{
		MGRAPH_NODE_BODY_OUT(MinMaxDistance, Node, 0x60);
	};

}

#endif
