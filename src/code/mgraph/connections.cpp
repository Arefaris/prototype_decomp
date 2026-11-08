// The connections between the pins of the mgraph library's graphs (0x10AD2210 - 0x10AD22B0): a connection sits in the list
// of each of its two pins and in the list of its graph.
#include "code/mgraph/graph.h"
#include "code/mgraph/pins.h"

namespace mgraph
{
	// 0x10AD2880 / 0x10AD2960 (names guessed): put the context connections of the pins a connection joins in the context, and take
	// them out of it (the abstract pins are replaced by the concrete pins of their abstractions)
	bool AttachConnectionPins(Context* context, Pin* from, Pin* to);
	void DetachConnectionPins(Context* context, Pin* from, Pin* to);

	// Takes a link out of the list it is in (the head and the tail of a list are two consecutive pointers)
	static __forceinline void Unlink(NodeLink** list, NodeLink* link)
	{
		if (link->previous == 0)
		{
			list[0] = link->next;
		}
		else
		{
			link->previous->next = link->next;
		}
		if (link->next == 0)
		{
			list[1] = link->previous;
		}
		else
		{
			link->next->previous = link->previous;
		}
	}

	// Puts a link at the end of a list
	static __forceinline void Append(NodeLink** list, NodeLink* link)
	{
		if (list[0] == 0)
		{
			list[0] = link;
			link->previous = 0;
		}
		else
		{
			list[1]->next = link;
			link->previous = list[1];
		}
		list[1] = link;
		link->next = 0;
	}

	// FUNCTION: ENGINE 0x10AD2210
	GraphConnectionBase::GraphConnectionBase(Pin* newFrom, Pin* newTo) :
		GraphItem(newTo->node->graph)
	{
		to = newTo;
		from = newFrom;
		Append(&newFrom->firstConnection, &fromLink);
		Append(&newTo->firstConnection, &toLink);
		Append(&graph->firstConnection, &graphLink);
	}

	// FUNCTION: ENGINE 0x10AD2A40
	void GraphConnectionBase::Attach(Context* newContext)
	{
		AttachConnectionPins(newContext, from, to);
	}

	// FUNCTION: ENGINE 0x10AD2A60
	void GraphConnectionBase::Detach(Context* oldContext)
	{
		DetachConnectionPins(oldContext, from, to);
	}

	// FUNCTION: ENGINE 0x10AD2720
	AbstractToConcreteGraphConnectionBase::AbstractToConcreteGraphConnectionBase(Pin* newFrom, Pin* newTo) :
		GraphConnectionBase(newFrom, newTo)
	{
	}

	// FUNCTION: ENGINE 0x10AD2740
	ConcreteToAbstractGraphConnectionBase::ConcreteToAbstractGraphConnectionBase(Pin* newFrom, Pin* newTo) :
		GraphConnectionBase(newFrom, newTo)
	{
	}

	// FUNCTION: ENGINE 0x10AD2770
	AbstractToAbstractGraphConnectionBase::AbstractToAbstractGraphConnectionBase(Pin* newFrom, Pin* newTo) :
		GraphConnectionBase(newFrom, newTo)
	{
	}

	// FUNCTION: ENGINE 0x10AD22B0
	GraphConnectionBase::~GraphConnectionBase()
	{
		Unlink(&to->firstConnection, &toLink);
		Unlink(&from->firstConnection, &fromLink);
		Unlink(&graph->firstConnection, &graphLink);
	}

	// FUNCTION: ENGINE 0x10AD2810
	// NONMATCHING: register choice of the name pointers (88 %)
#ifdef NONMATCHING
	bool GraphConnectionBase::Slot6(void* argument)
	{
		if (om::WriteBinary(static_cast<om::BinaryStream*>(argument), from->node->name))
		{
			if (om::WriteBinary(static_cast<om::BinaryStream*>(argument), from->name))
			{
				if (om::WriteBinary(static_cast<om::BinaryStream*>(argument), to->node->name))
				{
					if (om::WriteBinary(static_cast<om::BinaryStream*>(argument), to->name))
					{
						return true;
					}
				}
			}
		}
		return false;
	}
#endif
}
