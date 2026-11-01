// The graph of the mgraph library (RTTI: mgraph::Graph, an entity): the nodes by name, the connections between their pins and
// the abstractions that contain it. Only what the nodes and the connections use is described so far.
#ifndef MGRAPH_GRAPH_H
#define MGRAPH_GRAPH_H

#include "code/mgraph/node.h"
#include "code/om/entity.h"

namespace mgraph
{
	// The tree of the nodes of a graph, ordered by the name key (the node sits in the tree at 0x3C)
	class NodeTree : public om::TreeHead
	{
	public:
		// 0x10ACA6C0: enters a node under its name; false when a node of that name is there already
		bool Insert(Node* node);
		// 0x10AC75F0: the node of a name, null when there is none
		Node* Find(const om::ClassName& nodeName);
	};

	class Graph : public om::Entity
	{
	public:
		explicit Graph(const om::ClassName& newName);
		// 0x10AC78D0: the node of a name, null when there is none
		Node* FindNode(const om::ClassName& nodeName);
		void RemoveNode(Node* node)
		{
			nodes.Erase(&node->treeNode);
		}

		void* unknown20;
		Context* context;  // 0x24: the context the graph was added to
		bool unknown28;
		int attachCount;  // 0x2C
		unsigned int numChannels;  // 0x30
		void* unknown34;
		unsigned short unknown38;
		unsigned short unknown3A;
		void* firstConnection;  // 0x3C: the connections of the graph (a list linked at 0x18 of the connection)
		void* lastConnection;  // 0x40
		NodeTree nodes;  // 0x44
		void* firstAbstraction;  // 0x58: the abstractions that contain the graph (a list linked at 0x50 of the abstraction)
		void* lastAbstraction;  // 0x5C
		char unknown60[0x18];
		unsigned int channelsEnabledLow;  // 0x78
		unsigned int channelsEnabledHigh;  // 0x7C
		bool unknown80;
		void* nextGraph;  // 0x84
		void* previousGraph;  // 0x88
	};
}

#endif
