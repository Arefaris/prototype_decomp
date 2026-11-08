// The chooser node of the mgraph library (0x10B6D210 - 0x10B6E360): ...
#ifndef MGRAPH_CHOOSER_H
#define MGRAPH_CHOOSER_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterChooser();

	class __declspec(align(8)) Chooser : public Node
	{
		MGRAPH_NODE_BODY_OUT(Chooser, Node, 0x60);
	};

}

#endif
