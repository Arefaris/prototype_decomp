// The nodes that contain a graph (0x10ACBFE0 - 0x10ACD0D0).
#include "code/mgraph/graph.h"
#include "code/mgraph/nodes.h"
#include "code/mgraph/throw.h"
#include "code/core/hash.h"

namespace mgraph
{
	// FUNCTION: ENGINE 0x10ACCDB0
	void Abstraction::Attach(Context* newContext)
	{
		if (innerGraph != 0)
		{
			innerGraph->Attach(newContext);
		}
	}

	// FUNCTION: ENGINE 0x10ACCDC0
	void Abstraction::Detach(Context* oldContext)
	{
		if (innerGraph != 0)
		{
			innerGraph->Detach(oldContext);
		}
	}

	// FUNCTION: ENGINE 0x10ACBFE0
	void LinkedGraph::SetNumChannels(unsigned int newCount)
	{
		if (innerGraph != 0)
		{
			innerGraph->SetNumChannels(1);
		}
		Node::SetNumChannels(1);
	}

	// FUNCTION: ENGINE 0x10ACC000
	void LinkedGraph::SetChannelEnabled(unsigned int channel, bool enabled)
	{
		if (innerGraph != 0)
		{
			innerGraph->SetChannelEnabled(0, true);
		}
	}

	// FUNCTION: ENGINE 0x10ACD080
	void EmbeddedGraph::SetNumChannels(unsigned int newCount)
	{
		if (innerGraph != 0)
		{
			innerGraph->SetNumChannels(newCount);
		}
		Node::SetNumChannels(newCount);
	}

	// FUNCTION: ENGINE 0x10ACD0C0
	void EmbeddedGraph::SetChannelEnabled(unsigned int channel, bool enabled)
	{
		if (innerGraph != 0)
		{
			innerGraph->SetChannelEnabled(channel, enabled);
		}
	}

	// FUNCTION: ENGINE 0x10ACD060
	void EmbeddedGraph::Slot13()
	{
	}

	// FUNCTION: ENGINE 0x10ACD070
	void EmbeddedGraph::Slot14()
	{
	}

	// FUNCTION: ENGINE 0x10ACD0B0
	void EmbeddedGraph::Slot15(unsigned int channel)
	{
		if (innerGraph != 0)
		{
			innerGraph->ResetChannel(channel);
		}
	}

	// FUNCTION: ENGINE 0x10ACCDD0
	Abstraction::Abstraction(NodeTypeBase* newType, Graph* newGraph, const om::ClassName& newName, Graph* newInnerGraph) :
		Node(newType, newGraph, newName, 0, 0)
	{
		innerGraph = newInnerGraph;
		if (innerGraph != 0)
		{
			om::ThreadSafeRefCount::AddRef(&innerGraph->count);
			innerGraph->AddAbstraction(this);
		}
	}

	// FUNCTION: ENGINE 0x10ACCE20
	Abstraction::~Abstraction()
	{
		if (innerGraph != 0)
		{
			innerGraph->RemoveAbstraction(this);
			Graph* oldGraph = innerGraph;
			if (om::ThreadSafeRefCount::Release(&oldGraph->count) == 0 && oldGraph != 0)
			{
				delete oldGraph;
			}
		}
	}

	// FUNCTION: ENGINE 0x10ACBFB0
	LinkedGraph::~LinkedGraph()
	{
	}

	// FUNCTION: ENGINE 0x10ACC420
	LinkedGraph::LinkedGraph(Graph* newGraph, const om::ClassName& newName) :
		Abstraction(CachedNodeType<LinkedGraph>(), newGraph, newName, 0)
	{
	}

	// FUNCTION: ENGINE 0x10ACC180
	void LinkedGraph::SetAbstractedName(const om::ClassName& newName)
	{
		abstractedName = newName;
		Graph* graph = FindGraph(&newName);
		if (graph != 0 && graph->unknown28)
		{
			SetInnerGraph(graph);
			graph->unknown80 = true;
		}
	}

	// FUNCTION: ENGINE 0x10ACC470
	bool LinkedGraph::Slot8(void* argument)
	{
		bool named;
		{
			om::String empty("", 0);
			unsigned __int64 emptyKey = core::Hash64(empty.GetText(), 0);
			named = abstractedName.key != emptyKey;
		}
		if (named)
		{
			Graph* graph = FindGraph(&abstractedName);
			if (graph == 0)
			{
				return false;
			}
			graph->Slot8(argument);
			SetInnerGraph(graph);
			graph->unknown80 = true;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10ACD460
	EmbeddedGraph::EmbeddedGraph(Graph* newGraph, const om::ClassName& newName) :
		Abstraction(CachedNodeType<EmbeddedGraph>(), newGraph, newName, 0)
	{
	}

	// FUNCTION: ENGINE 0x10ACD050
	const om::ClassName* EmbeddedGraph::GetGraphName()
	{
		return &abstractedName;
	}

	// FUNCTION: ENGINE 0x10ACD930
	bool EmbeddedGraph::Slot8(void* argument)
	{
		Graph* graph = FindGraph(&abstractedName);
		if (graph == 0)
		{
			return false;
		}
		graph->Slot8(argument);
		SetAbstractedName(&abstractedName);
		return true;
	}
}
