// The constructor of the property nodes (RTTI: mgraph::PropertyNode<P>): a node with one output pin, "o", and one input pin, "i".
#ifndef MGRAPH_PROPERTYNODECTOR_H
#define MGRAPH_PROPERTYNODECTOR_H

#include "code/mgraph/propertynode.h"
#include "code/mgraph/throw.h"

namespace mgraph
{
	template<class P> PropertyNode<P>::PropertyNode(Graph* newGraph, const om::ClassName& newName, NodeTypeBase* newType) :
		PropertyNodeBase(newType, newGraph, newName, 1, 1),
		value()
	{
		new OutputPin<P>(this, &MGRAPH_NAME("o"), 0, P());
		new InputPin<P>(this, &MGRAPH_NAME("i"), 1, 0, P());
	}
}

#endif
