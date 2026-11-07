// The nodes of the mgraph library (RTTI: mgraph::GraphItem, the base of the nodes and of the connections of a graph, and
// mgraph::Node): a node belongs to a graph, has a name key, a node type, and two lists of pins; the context it is attached
// to evaluates it.
#ifndef MGRAPH_NODE_H
#define MGRAPH_NODE_H

#include "code/om/allocation.h"
#include "code/om/dynamicarray.h"
#include "code/om/name.h"
#include "code/om/tree.h"

namespace om
{
	class MetaTypeBase;
}

namespace mgraph
{
	class Context;
	class EvaluationFrame;
	class Graph;
	class InputPinBase;
	class NodeTypeBase;
	class OutputPinBase;

	// The base of the nodes and of the connections of a graph (RTTI: mgraph::GraphItem). Slots 1 and 2 are pure, 3 to 6 are the
	// library's.
	class GraphItem
	{
	public:
		// 0x10AD2AA0
		explicit GraphItem(Graph* newGraph);
		// 0x10AD2AC0 (the deleting destructor is 0x10AD2BB0)
		virtual ~GraphItem();
		// Slots 1 and 2: the context takes the item into its lists, and lets it go
		virtual void Attach(Context* newContext) = 0;
		virtual void Detach(Context* oldContext) = 0;
		// 0x10AD2AD0 / 0x10AD2AE0 / 0x10AD2AF0 / 0x10AD2B00: nothing to do (read and write in text and binary form in the nodes)
		virtual bool Slot3(void* argument);
		virtual bool Slot4(void* argument);
		virtual void Slot5(void* argument);
		virtual bool Slot6(void* argument);

		Graph* graph;  // 4
	};

	// A link of an intrusive list of nodes (the next and the previous link)
	struct NodeLink
	{
		NodeLink* next;
		NodeLink* previous;
	};

	class __declspec(align(8)) Node : public GraphItem
	{
	public:
		// 0x10ACB0D0: enters the node in the tree of its graph and makes room for the pins
		Node(NodeTypeBase* newType, Graph* newGraph, const om::ClassName& newName, unsigned int numInputs, unsigned int numOutputs);
		// 0x10ACB1B0: a node of the base class
		Node(Graph* newGraph, const om::ClassName& newName);
		// 0x10ACACB0 (the deleting destructor is 0x10ACB180)
		virtual ~Node();
		// Slot 1: the context takes the node into its lists (when it has none yet)
		virtual void Attach(Context* newContext);
		// Slot 2: the context lets the node go
		virtual void Detach(Context* oldContext);
		// Slots 3 to 6 read and write the node through the reflection of its node type (text and binary)
		virtual bool Slot3(void* argument);
		virtual bool Slot4(void* argument);
		virtual void Slot5(void* argument);
		virtual bool Slot6(void* argument);
		// Slot 7: gives the node another name, when its graph has no node of that name
		virtual void Rename(const om::ClassName& newName);
		virtual bool Slot8(void* argument)
		{
			return true;
		}
		virtual void Slot9(void* argument)
		{
		}
		virtual void Slot10(void* argument)
		{
		}
		virtual void SetNumChannels(unsigned int newCount);
		// Slot 12: the context enabled or disabled a channel
		virtual void SetChannelEnabled(unsigned int channel, bool enabled)
		{
		}
		virtual void Slot13()
		{
		}
		virtual void Slot14()
		{
		}
		virtual void Slot15(unsigned int channel)
		{
		}
		virtual void Slot16(EvaluationFrame* frame);
		OM_ALLOCATION(Node);

		// 0x10AC9FD0 / 0x10ACA020: the input and the output pin of a name, null when there is none
		InputPinBase* FindInput(const om::ClassName& pinName);
		OutputPinBase* FindOutput(const om::ClassName& pinName);
		// 0x10AC9F50: deletes the pins
		void DeletePins();

		om::ClassName name;  // 8
		NodeTypeBase* type;  // 0x10
		om::DynamicArray<InputPinBase*, unsigned short> inputs;  // 0x14
		om::DynamicArray<OutputPinBase*, unsigned short> outputs;  // 0x1C
		Context* context;  // 0x24: the context the node is attached to
		void* unknown28;  // the level of the context the node is in
		NodeLink contextLink;  // 0x2C: the node in the list of its context
		NodeLink levelLink;  // 0x34: the node in the list of its level
		om::TreeNode treeNode;  // 0x3C: the node in the tree of its graph
	};
}

#endif
