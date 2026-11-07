// The nodes that contain a graph (0x10ACBFE0 - 0x10ACD0D0).
#include "code/mgraph/graph.h"
#include "code/mgraph/nodes.h"

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
}
