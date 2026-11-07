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

	class __declspec(align(8)) Graph : public om::Entity
	{
	public:
		// 0x10AC7730
		explicit Graph(const om::ClassName& newName);
		// 0x10AC77D0 (the deleting destructor is 0x10AC8430)
		virtual ~Graph();
		// The entity's slots: 0x10AC5CF0 answers true; 3 and 4 read and write the graph as text (nodes and connections), 6 and 7 in
		// binary form, 8 checks the connections (not reconstructed); the last is the entity type
		virtual bool Slot1();
		virtual bool Slot3(void* argument);
		virtual void Slot4(void* argument);
		virtual bool Slot6(void* argument);
		virtual bool Slot7(void* argument);
		virtual bool Slot8(void* argument);
		virtual om::EntityTypeBase* GetEntityType();
		OM_ENTITY_ALLOCATION(Graph)

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
		NodeLink* firstConnection;  // 0x3C: the connections of the graph (a list linked at 0x18 of the connection)
		NodeLink* lastConnection;  // 0x40
		NodeTree nodes;  // 0x44
		void* firstAbstraction;  // 0x58: the abstractions that contain the graph (a list linked at 0x50 of the abstraction)
		void* lastAbstraction;  // 0x5C
		unsigned int unknown60;
		unsigned int unknown64;
		unsigned int unknown68;
		unsigned int unknown6C;
		unsigned int unknown70;
		unsigned int unknown74;
		unsigned int channelsEnabledLow;  // 0x78
		unsigned int channelsEnabledHigh;  // 0x7C
		bool unknown80;
		void* nextGraph;  // 0x84
		void* previousGraph;  // 0x88
	};
}

#endif
