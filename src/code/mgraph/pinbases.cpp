// The bases of the pins of the mgraph library's nodes (0x10AD1490 - 0x10AD1CA0): a pin enters the list of inputs or outputs
// of its node when it is made and leaves it when it is destroyed.
#include "code/mgraph/pins.h"

namespace mgraph
{
	// FUNCTION: ENGINE 0x10AD1490
	void ConcreteOutputPinBase::SetChannelOwners(void* newOwner)
	{
		unsigned int count = node->graph->numChannels;
		for (unsigned int i = 0; i < count; i++)
		{
			*reinterpret_cast<void**>(unknown28.tail + unknown30 * i + 4) = newOwner;
		}
	}

	// FUNCTION: ENGINE 0x10AD17B0
	// NONMATCHING: the engine loads the node behind the stores of the connection list and keeps it in edi, the index in ebx (68.9 %)
#ifdef NONMATCHING
	OutputPinBase::OutputPinBase(const om::ClassName* newName, int newUnknown, void* newNode, int newIndex) :
		Pin(newName, newUnknown, static_cast<Node*>(newNode))
	{
		Node* owner = node;
		firstConnection = 0;
		lastConnection = 0;
		unsigned int position = newIndex;
		if (position == 0xFFFFFFFF)
		{
			position = owner->outputs.size;
		}
		owner->SetOutput(position, this);
	}
#endif

	// FUNCTION: ENGINE 0x10AD1600
	OutputPinBase::~OutputPinBase()
	{
		Node* owner = node;
		for (unsigned int i = 0; i < owner->outputs.size; i++)
		{
			if (owner->outputs[i] == this)
			{
				owner->outputs[i] = 0;
				break;
			}
		}
	}

	// FUNCTION: ENGINE 0x10AD1640
	void ConcreteOutputPinBase::DeleteConnections()
	{
		for (;;)
		{
			GraphConnectionBase* connection;
			if (firstConnection != 0)
			{
				connection = reinterpret_cast<GraphConnectionBase*>(reinterpret_cast<char*>(firstConnection) - 0x10);
			}
			else
			{
				connection = 0;
			}
			if (connection == 0)
			{
				break;
			}
			delete connection;
		}
	}

	// FUNCTION: ENGINE 0x10AD16A0
	ConcreteOutputPinBase::~ConcreteOutputPinBase()
	{
		DeleteConnections();
	}

	// FUNCTION: ENGINE 0x10AD19D0
	void InputPinBase::DeleteConnections()
	{
		for (;;)
		{
			GraphConnectionBase* connection;
			if (firstConnection != 0)
			{
				connection = reinterpret_cast<GraphConnectionBase*>(reinterpret_cast<char*>(firstConnection) - 8);
			}
			else
			{
				connection = 0;
			}
			if (connection == 0)
			{
				break;
			}
			delete connection;
		}
	}

	// FUNCTION: ENGINE 0x10AD1B10
	// NONMATCHING: the engine loads the node behind the stores of the connection list, and puts the empty element in the slot of the node argument (88.5 %)
#ifdef NONMATCHING
	InputPinBase::InputPinBase(const om::ClassName* newName, int newKind, void* newNode, unsigned char newUnknown, int newIndex) :
		Pin(newName, newKind, static_cast<Node*>(newNode))
	{
		firstConnection = 0;
		lastConnection = 0;
		unknown20 = newUnknown;
		if (newIndex != -1)
		{
			node->SetInput(newIndex, this);
			return;
		}
		node->SetInput(node->inputs.size, this);
	}
#endif

	// FUNCTION: ENGINE 0x10AD1BB0
	GraphConnectionBase* InputPinBase::MakeConnection(Pin* other)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10AD1BC0
	InputPinBase::~InputPinBase()
	{
		Node* owner = node;
		for (unsigned int i = 0; i < owner->inputs.size; i++)
		{
			if (owner->inputs[i] == this)
			{
				owner->inputs[i] = 0;
				break;
			}
		}
		DeleteConnections();
	}

	// FUNCTION: ENGINE 0x10AD1C20
	ConcreteInputPinBase::ConcreteInputPinBase(const om::ClassName* newName, int newUnknown, void* newNode, int newIndex) :
		InputPinBase(newName, 0, newNode, newUnknown, newIndex),
		unknown28(0),
		unknown2C(0)
	{
	}

	// FUNCTION: ENGINE 0x10AD1C60
	ConcreteInputPinBase::~ConcreteInputPinBase()
	{
		DeleteConnections();
	}
}
