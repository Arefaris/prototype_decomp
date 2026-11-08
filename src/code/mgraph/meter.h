// The meter node of the mgraph library (0x10B730D0 - 0x10B73A00): the reflection of the class and the description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#ifndef MGRAPH_METER_H
#define MGRAPH_METER_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterMeter();

	class __declspec(align(8)) Meter : public Node
	{
		MGRAPH_NODE_BODY_OUT(Meter, Node, 0x50);
	};

}

#endif
