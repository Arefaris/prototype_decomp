// The graph of the mgraph library (0x10AC5CF0, 0x10AC7730 - 0x10AC78D0).
#include "code/mgraph/graph.h"

namespace mgraph
{
	// FUNCTION: ENGINE 0x10AC7730
	// EQUIVALENT: scheduling (81.7 %): the engine computes the address of the node tree after the first stores of the members, ours before the first of them; the same stores and the same call
	Graph::Graph(const om::ClassName& newName) :
		Entity(newName),
		unknown20(0),
		context(0),
		attachCount(0),
		numChannels(0),
		unknown34(0),
		unknown38(0),
		unknown3A(0),
		firstConnection(0),
		lastConnection(0),
		nodes(),
		firstAbstraction(0),
		lastAbstraction(0),
		unknown60(0),
		unknown64(0),
		unknown68(0),
		unknown6C(0),
		unknown70(0),
		unknown74(0),
		channelsEnabledLow(0),
		channelsEnabledHigh(0),
		unknown80(false)
	{
		context = 0;
		unknown28 = true;
	}

	// FUNCTION: ENGINE 0x10AC5CF0
	bool Graph::Slot1()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10AC77C0
	om::EntityTypeBase* Graph::GetEntityType()
	{
		return om::FindEntityType(typeid(Graph));
	}

	// FUNCTION: ENGINE 0x10AC78D0
	Node* Graph::FindNode(const om::ClassName& nodeName)
	{
		return nodes.Find(nodeName);
	}
}
