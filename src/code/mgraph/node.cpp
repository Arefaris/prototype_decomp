// The nodes of the mgraph library (0x10AC8890 - 0x10ACB300, 0x10AD2AA0 - 0x10AD2BB0).
#include "code/mgraph/events.h"
#include "code/om/metatype.h"
#include "code/mgraph/graph.h"
#include "code/mgraph/nodes.h"
#include "code/mgraph/pins.h"

namespace mgraph
{
	// The description of the node class Node, found once
	static __forceinline NodeTypeBase* FindBaseNodeType()
	{
		NodeTypeBase*& cache = NodeTypeCache<Node>::type;
		if (cache == 0)
		{
			cache = FindNodeType(typeid(Node));
		}
		return cache;
	}

	// FUNCTION: ENGINE 0x10AC88F0
	bool Node::Slot3(void* argument)
	{
		return type->GetMetaType()->ReadText(static_cast<const om::TextValue*>(argument), this);
	}

	// FUNCTION: ENGINE 0x10AC8910
	void Node::Slot5(void* argument)
	{
		type->GetMetaType()->WriteText(static_cast<om::TextValue*>(argument), this);
	}

	// FUNCTION: ENGINE 0x10AC8930
	bool Node::Slot4(void* argument)
	{
		return type->GetMetaType()->ReadBinary(static_cast<om::BinaryStream*>(argument), this);
	}

	// FUNCTION: ENGINE 0x10AC8950
	bool Node::Slot6(void* argument)
	{
		if (type->GetMetaType()->WriteBinary(static_cast<om::BinaryStream*>(argument), this))
		{
			if (GraphItem::Slot6(argument))
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10AC8990
	void Node::Attach(Context* newContext)
	{
		if (context == 0)
		{
			newContext->AddNode(this);
			context = newContext;
		}
	}

	// FUNCTION: ENGINE 0x10AC89B0
	void Node::Detach(Context* oldContext)
	{
		if (context != 0)
		{
			oldContext->RemoveNode(this);
			context = 0;
		}
	}

	// FUNCTION: ENGINE 0x10AC9FD0
	InputPinBase* Node::FindInput(const om::ClassName& pinName)
	{
		for (unsigned int i = 0; i < inputs.size; i++)
		{
			InputPinBase* pin = inputs[i];
			if (pin != 0 && pin->name.key == pinName.key)
			{
				return inputs[i];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10ACA020
	OutputPinBase* Node::FindOutput(const om::ClassName& pinName)
	{
		for (unsigned int i = 0; i < outputs.size; i++)
		{
			OutputPinBase* pin = outputs[i];
			if (pin != 0 && pin->name.key == pinName.key)
			{
				return outputs[i];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10AC9F50
	void Node::DeletePins()
	{
		for (unsigned int i = 0; i < inputs.size; i++)
		{
			InputPinBase* pin = inputs[i];
			if (pin != 0)
			{
				delete pin;
			}
		}
		for (unsigned int i = 0; i < outputs.size; i++)
		{
			OutputPinBase* pin = outputs[i];
			if (pin != 0)
			{
				delete pin;
			}
		}
		inputs.Clear();
		outputs.Clear();
	}

	// FUNCTION: ENGINE 0x10ACACB0
	// EQUIVALENT: register allocation (80.5 %): the engine keeps the graph in eax and the address of the tree node in ecx for the
	// call that takes the node out of the tree, ours the other way round; the same calls, reads and writes
	Node::~Node()
	{
		DeletePins();
		graph->nodes.Erase(&treeNode);
		type->instanceCount--;
	}

	// FUNCTION: ENGINE 0x10ACA070
	void Node::SetNumChannels(unsigned int newCount)
	{
		for (unsigned int i = 0; i < outputs.size; i++)
		{
			OutputPinBase* pin = outputs[i];
			if (pin->kind == 0)
			{
				static_cast<ConcreteOutputPinBase*>(pin)->Slot3(newCount, context->GetChannelOwner());
			}
		}
	}

	// FUNCTION: ENGINE 0x10ACAD30
	void Node::Slot16(EvaluationFrame* frame)
	{
	}

	// FUNCTION: ENGINE 0x10ACB0D0
	Node::Node(NodeTypeBase* newType, Graph* newGraph, const om::ClassName& newName, unsigned int numInputs, unsigned int numOutputs) :
		GraphItem(newGraph),
		name(newName),
		type(newType),
		context(0),
		unknown28(0)
	{
		type->instanceCount++;
		graph->nodes.Insert(this);
		inputs.Reserve(numInputs);
		outputs.Reserve(numOutputs);
	}

	// FUNCTION: ENGINE 0x10ACB1B0
	Node::Node(Graph* newGraph, const om::ClassName& newName) :
		GraphItem(newGraph),
		name(newName),
		type(FindBaseNodeType())
	{
		type->instanceCount++;
		graph->nodes.Insert(this);
	}

	// FUNCTION: ENGINE 0x10ACB230
	// EQUIVALENT: register allocation (92.2 %): the engine keeps the graph in eax and the address of the tree node in ecx for the
	// call that takes the node out of the tree, ours the other way round; the same calls, reads and writes
	void Node::Rename(const om::ClassName& newName)
	{
		if (graph->FindNode(newName) == 0)
		{
			name = newName;
			graph->RemoveNode(this);
			graph->nodes.Insert(this);
		}
	}

	// FUNCTION: ENGINE 0x10AD2AA0
	GraphItem::GraphItem(Graph* newGraph) :
		graph(newGraph)
	{
	}

	// FUNCTION: ENGINE 0x10AD2AC0
	GraphItem::~GraphItem()
	{
	}

	// FUNCTION: ENGINE 0x10AD2AD0
	bool GraphItem::Slot3(void* argument)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10AD2AE0
	bool GraphItem::Slot4(void* argument)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x10AD2AF0
	void GraphItem::Slot5(void* argument)
	{
	}

	// FUNCTION: ENGINE 0x10AD2B00
	bool GraphItem::Slot6(void* argument)
	{
		return true;
	}
}
