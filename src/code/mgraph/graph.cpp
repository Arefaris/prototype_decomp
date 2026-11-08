// The graph of the mgraph library (0x10AC5CF0, 0x10AC7730 - 0x10AC78D0).
#include "code/mgraph/graph.h"
#include "code/mgraph/nodes.h"
#include "code/mgraph/pins.h"

namespace mgraph
{
	// FUNCTION: ENGINE 0x10AC7730
	// EQUIVALENT: scheduling (81.7 %): the engine computes the address of the node tree after the first stores of the members, ours before the first of them; the same stores and the same call
	Graph::Graph(const om::ClassName& newName) :
		Entity(newName),
		group(0),
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

	// The node a tree node of the graph belongs to, null for no tree node
	static __forceinline Node* NodeOfTreeNode(om::TreeNode* treeNode)
	{
		Node* node;
		if (treeNode != 0)
		{
			node = reinterpret_cast<Node*>(reinterpret_cast<char*>(treeNode) - 0x3C);
		}
		else
		{
			node = 0;
		}
		return node;
	}

	// The graph a link of its group belongs to, null for no link
	static __forceinline Graph* GraphOfLink(NodeLink* link)
	{
		Graph* graph;
		if (link != 0)
		{
			graph = reinterpret_cast<Graph*>(reinterpret_cast<char*>(link) - 0x84);
		}
		else
		{
			graph = 0;
		}
		return graph;
	}

	// The link in the group of a graph, null for no graph
	static __forceinline NodeLink* LinkOfGraph(Graph* graph)
	{
		NodeLink* link;
		if (graph != 0)
		{
			link = &graph->groupLink;
		}
		else
		{
			link = 0;
		}
		return link;
	}

	// The abstraction a link of the graph's list belongs to, null for no link
	static __forceinline Abstraction* AbstractionOfLink(NodeLink* link)
	{
		Abstraction* abstraction;
		if (link != 0)
		{
			abstraction = reinterpret_cast<Abstraction*>(reinterpret_cast<char*>(link) - 0x50);
		}
		else
		{
			abstraction = 0;
		}
		return abstraction;
	}

	// The link in the list of the graph, null for no abstraction
	static __forceinline NodeLink* LinkOfAbstraction(Abstraction* abstraction)
	{
		NodeLink* link;
		if (abstraction != 0)
		{
			link = &abstraction->graphLink;
		}
		else
		{
			link = 0;
		}
		return link;
	}

	// The connection a link of the graph's list belongs to, null for no link
	static __forceinline GraphConnectionBase* ConnectionOfLink(NodeLink* link)
	{
		GraphConnectionBase* connection;
		if (link != 0)
		{
			connection = reinterpret_cast<GraphConnectionBase*>(reinterpret_cast<char*>(link) - 0x18);
		}
		else
		{
			connection = 0;
		}
		return connection;
	}

	// FUNCTION: ENGINE 0x10AC75F0
	// NONMATCHING: the engine lays out the three arms of the search differently and saves ebp and esi at the entry (41.5 %)
#ifdef NONMATCHING
	Node* NodeTree::Find(const om::ClassName& nodeName)
	{
		om::TreeNode* current = root;
		while (current != &nil)
		{
			Node* other = NodeOfTreeNode(current);
			if (other->name.key > nodeName.key)
			{
				current = current->left;
			}
			else if (other->name.key >= nodeName.key)
			{
				om::TreeNode* previous = Previous(current);
				while (previous != 0)
				{
					Node* earlier = NodeOfTreeNode(previous);
					if (nodeName.key < earlier->name.key || nodeName.key > earlier->name.key)
					{
						break;
					}
					current = previous;
					previous = Previous(previous);
				}
				return NodeOfTreeNode(current);
			}
			else
			{
				current = current->right;
			}
		}
		return 0;
	}
#endif

	// FUNCTION: ENGINE 0x10AC6A30
	Graph* Graph::FirstInGroup()
	{
		if (group != 0)
		{
			NodeLink* link = group->head;
			if (link != 0)
			{
				return reinterpret_cast<Graph*>(reinterpret_cast<char*>(link) - 0x84);
			}
			return 0;
		}
		return this;
	}
	// FUNCTION: ENGINE 0x10AC6A50
	Graph* Graph::NextInGroup(Graph* graph)
	{
		if (group != 0)
		{
			NodeLink* link = LinkOfGraph(graph)->next;
			if (link != 0)
			{
				return reinterpret_cast<Graph*>(reinterpret_cast<char*>(link) - 0x84);
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10AC6A80
	bool Graph::IsInGroupOf(Graph* other)
	{
		Graph* graph = other->FirstInGroup();
		while (graph != 0)
		{
			if (graph == this)
			{
				return true;
			}
			graph = graph->NextInGroup(graph);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10AC6AB0
	Node* Graph::FirstNode()
	{
		return NodeOfTreeNode(nodes.First());
	}

	// FUNCTION: ENGINE 0x10AC6AD0
	Node* Graph::NextNode(Node* node)
	{
		om::TreeNode* treeNode;
		if (node != 0)
		{
			treeNode = &node->treeNode;
		}
		else
		{
			treeNode = 0;
		}
		return NodeOfTreeNode(nodes.Next(treeNode));
	}

	// FUNCTION: ENGINE 0x10AC6B00
	void Graph::AddAbstraction(Abstraction* abstraction)
	{
		NodeLink* link = LinkOfAbstraction(abstraction);
		if (firstAbstraction == 0)
		{
			firstAbstraction = link;
			link->previous = 0;
			lastAbstraction = link;
			link->next = 0;
			return;
		}
		lastAbstraction->next = link;
		link->previous = lastAbstraction;
		lastAbstraction = link;
		link->next = 0;
	}

	// FUNCTION: ENGINE 0x10AC6B50
	void Graph::RemoveAbstraction(Abstraction* abstraction)
	{
		NodeLink* link = LinkOfAbstraction(abstraction);
		if (link->previous == 0)
		{
			firstAbstraction = link->next;
		}
		else
		{
			link->previous->next = link->next;
		}
		if (link->next == 0)
		{
			lastAbstraction = link->previous;
			return;
		}
		link->next->previous = link->previous;
	}

	// FUNCTION: ENGINE 0x10AC6B90
	Abstraction* Graph::FirstAbstraction()
	{
		return AbstractionOfLink(firstAbstraction);
	}

	// FUNCTION: ENGINE 0x10AC6BA0
	Abstraction* Graph::NextAbstraction(Abstraction* abstraction)
	{
		return AbstractionOfLink(LinkOfAbstraction(abstraction)->next);
	}

	// FUNCTION: ENGINE 0x10AC6CA0
	void Graph::Attach(Context* newContext)
	{
		attachCount++;
		if (attachCount == 1)
		{
			context = newContext;
			for (Node* node = FirstNode(); node != 0; node = NextNode(node))
			{
				node->Attach(newContext);
			}
			GraphConnectionBase* connection = ConnectionOfLink(firstConnection);
			while (connection != 0)
			{
				connection->Attach(newContext);
				connection = ConnectionOfLink(connection->graphLink.next);
			}
		}
	}

	// FUNCTION: ENGINE 0x10AC6D20
	void Graph::ResetChannel(unsigned int channel)
	{
		for (Node* node = FirstNode(); node != 0; node = NextNode(node))
		{
			node->Slot15(channel);
		}
	}

	// FUNCTION: ENGINE 0x10AC6E40
	void Graph::SetNumChannels(unsigned int newNumChannels)
	{
		numChannels = newNumChannels;
		for (Node* node = FirstNode(); node != 0; node = NextNode(node))
		{
			node->SetNumChannels(newNumChannels);
		}
	}

	// FUNCTION: ENGINE 0x10AC6F00
	// NONMATCHING: the engine loads the bool argument into ebx before the shift of the channel's bit (76 %)
#ifdef NONMATCHING
	void Graph::SetChannelEnabled(unsigned int channel, bool enabled)
	{
		unsigned __int64 mask = 1ui64 << channel;
		if (enabled)
		{
			channelsEnabledLow |= static_cast<unsigned int>(mask);
			channelsEnabledHigh |= static_cast<unsigned int>(mask >> 32);
		}
		else
		{
			channelsEnabledLow &= ~static_cast<unsigned int>(mask);
			channelsEnabledHigh &= ~static_cast<unsigned int>(mask >> 32);
		}
		for (Node* node = FirstNode(); node != 0; node = NextNode(node))
		{
			node->SetChannelEnabled(channel, enabled);
		}
	}
#endif

	// FUNCTION: ENGINE 0x10AC6F60
	void Graph::Detach(Context* oldContext)
	{
		if (attachCount == 1)
		{
			GraphConnectionBase* connection = ConnectionOfLink(firstConnection);
			while (connection != 0)
			{
				connection->Detach(oldContext);
				connection = ConnectionOfLink(connection->graphLink.next);
			}
			for (Node* node = FirstNode(); node != 0; node = NextNode(node))
			{
				node->Detach(oldContext);
			}
			context = 0;
		}
		attachCount--;
	}
}
