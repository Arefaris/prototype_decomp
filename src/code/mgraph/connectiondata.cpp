// The description of a connection by names (0x10AD3A70 - 0x10AD3E20).
#include "code/mgraph/connectiondata.h"
#include "code/mgraph/graph.h"
#include "code/mgraph/pins.h"
#include "code/om/metaproperty.h"
#include "code/om/textvalue.h"

#pragma function(memcpy)

namespace mgraph
{
	// FUNCTION: ENGINE 0x10AD3A70
	GraphConnectionBase* ConnectionData::MakeConnection(Graph* graph)
	{
		if (graph == 0)
		{
			return 0;
		}
		GraphConnectionBase* connection = 0;
		Node* output = graph->FindNode(outputNode);
		if (output != 0)
		{
			OutputPinBase* from = output->FindOutput(outputPin);
			if (from != 0)
			{
				Node* input = graph->FindNode(inputNode);
				if (input != 0)
				{
					InputPinBase* to = input->FindInput(inputPin);
					if (to != 0)
					{
						connection = to->MakeConnection(from);
					}
				}
			}
		}
		return connection;
	}

	// FUNCTION: ENGINE 0x10AD3B30
	ConnectionData::ConnectionData(const ConnectionData& other)
	{
		outputNode = other.outputNode;
		outputPin = other.outputPin;
		inputNode = other.inputNode;
		inputPin = other.inputPin;
		buffer = other.buffer;
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

	// FUNCTION: ENGINE 0x10AD3D00
	GraphConnectionBase* Graph::FindConnection(const om::ClassName& toNode, const om::ClassName& toPin, const om::ClassName& fromNode, const om::ClassName& fromPin)
	{
		GraphConnectionBase* connection = ConnectionOfLink(firstConnection);
		if (connection != 0)
		{
			do
			{
				if (connection->to->node->name.key == toNode.key && connection->to->name.key == toPin.key
					&& connection->from->node->name.key == fromNode.key && connection->from->name.key == fromPin.key)
				{
					return connection;
				}
				connection = ConnectionOfLink(connection->graphLink.next);
			}
			while (connection != 0);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10AD3DA0
	GraphConnectionBase* ConnectionData::FindConnection(Graph* graph)
	{
		return graph->FindConnection(inputNode, inputPin, outputNode, outputPin);
	}

	// FUNCTION: ENGINE 0x10AD3DC0
	bool ConnectionData::ReadBinary(om::BinaryStream* stream)
	{
		if (om::ReadBinary(stream, &outputNode) && om::ReadBinary(stream, &outputPin) && om::ReadBinary(stream, &inputNode) && om::ReadBinary(stream, &inputPin))
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10AD3E20
	// NONMATCHING: the engine does not merge the two exits (the early one pops one register less) and ends 11 bytes longer (99.2 %)
#ifdef NONMATCHING
	bool ConnectionData::ReadText(const om::TextValue* text)
	{
		om::TextValue* output;
		{
			om::String outputKey("Output", false);
			output = text->children.FindFirst(om::CompareNodeName, &outputKey);
		}
		om::TextValue* input;
		{
			om::String inputKey("Input", false);
			input = text->children.FindFirst(om::CompareNodeName, &inputKey);
		}
		if (output == 0 || input == 0)
		{
			return true;
		}
		{
			om::TextValue* outputNodeText;
			{
				om::String outputNodeKey("NodeName", false);
				outputNodeText = output->children.FindFirst(om::CompareNodeName, &outputNodeKey);
			}
			om::TextValue* outputPinText;
			{
				om::String outputPinKey("PinName", false);
				outputPinText = output->children.FindFirst(om::CompareNodeName, &outputPinKey);
			}
			om::TextValue* inputNodeText;
			{
				om::String inputNodeKey("NodeName", false);
				inputNodeText = input->children.FindFirst(om::CompareNodeName, &inputNodeKey);
			}
			om::TextValue* inputPinText;
			{
				om::String inputPinKey("PinName", false);
				inputPinText = input->children.FindFirst(om::CompareNodeName, &inputPinKey);
			}
			if (outputNodeText != 0 && outputPinText != 0 && inputNodeText != 0 && inputPinText != 0)
			{
				om::ReadText(outputNodeText, &outputNode);
				om::ReadText(outputPinText, &outputPin);
				om::ReadText(inputNodeText, &inputNode);
				om::ReadText(inputPinText, &inputPin);
			}
		}
		return true;
	}
#endif
}
