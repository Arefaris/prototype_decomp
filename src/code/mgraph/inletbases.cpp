// The base of the pins and of the inlet and outlet nodes of the mgraph library (0x10B6A5F0 - 0x10B6AC10): the nodes that stand for the
// inputs and outputs of a graph link themselves into lists of the graph.
#include "code/mgraph/nodes.h"
#include "code/mgraph/pins.h"

namespace mgraph
{
	// Puts a link behind the last one of a list
	static inline void AppendLink(NodeLink*& first, NodeLink*& last, NodeLink* link)
	{
		if (first == 0)
		{
			first = link;
			link->previous = 0;
			last = link;
		}
		else
		{
			last->next = link;
			link->previous = last;
			last = link;
		}
		link->next = 0;
	}

	// Takes a link out of a list
	static inline void RemoveLink(NodeLink*& first, NodeLink*& last, NodeLink* link)
	{
		if (link->previous == 0)
		{
			first = link->next;
		}
		else
		{
			link->previous->next = link->next;
		}
		if (link->next == 0)
		{
			last = link->previous;
		}
		else
		{
			link->next->previous = link->previous;
		}
	}

	// FUNCTION: ENGINE 0x10B6A5F0
	Pin::~Pin()
	{
	}

	// FUNCTION: ENGINE 0x10B6A600
	Pin::Pin(const om::ClassName* newName, unsigned char newKind, Node* newNode) :
		name(*newName),
		node(newNode),
		kind(newKind)
	{
	}

	// FUNCTION: ENGINE 0x10B6A7F0
	InletBase::InletBase(NodeTypeBase* newType, Graph* newGraph, const om::ClassName& newName) :
		Node(newType, newGraph, newName, 0, 1),
		pin(0)
	{
		Graph* owner = graph;
		owner->inletCount++;
		AppendLink(owner->firstInlet, owner->lastInlet, &graphLink);
	}

	// FUNCTION: ENGINE 0x10B6A860
	InletBase::~InletBase()
	{
		Graph* owner = graph;
		owner->outletCount--;
		RemoveLink(owner->firstInlet, owner->lastInlet, &graphLink);
	}

	// FUNCTION: ENGINE 0x10B6A9E0
	OutletBase::OutletBase(NodeTypeBase* newType, Graph* newGraph, const om::ClassName& newName) :
		Node(newType, newGraph, newName, 1, 0)
	{
		Graph* owner = graph;
		owner->outletCount++;
		AppendLink(owner->firstOutlet, owner->lastOutlet, &graphLink);
	}

	// FUNCTION: ENGINE 0x10B6AA50
	OutletBase::~OutletBase()
	{
		Graph* owner = graph;
		owner->outletCount--;
		RemoveLink(owner->firstOutlet, owner->lastOutlet, &graphLink);
	}

	// FUNCTION: ENGINE 0x10B6AA90
	AbstractInputPinBase* OutletBase::GetPin()
	{
		return static_cast<AbstractInputPinBase*>(inputs[0]);
	}
}
