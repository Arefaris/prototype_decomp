// The connection a context keeps for the pin of a graph (0x10AD31F0 - 0x10AD3240): it enters the context's lists when it is
// made and leaves them when it is destroyed.
#include "code/mgraph/events.h"
#include "code/mgraph/pins.h"

namespace mgraph
{
	// FUNCTION: ENGINE 0x10AD31F0
	ContextConnectionBase::ContextConnectionBase(void* newUnknown, void* newOwner, void* newPin)
	{
		pin = newPin;
		unknown20 = newOwner;
		owner = static_cast<ConnectionOwner*>(newUnknown);
		Context* context = reinterpret_cast<Context*>(newUnknown);
		context->AddConnection(this);
		ConcreteOutputPinBase* output = static_cast<ConcreteOutputPinBase*>(unknown20);
		output->SetChannelOwners(context->GetChannelOwner());
		static_cast<Pin*>(newPin)->node->Slot9(newPin);
	}

	// FUNCTION: ENGINE 0x10AD3240
	ContextConnectionBase::~ContextConnectionBase()
	{
		reinterpret_cast<Context*>(owner)->RemoveConnection(this);
		Pin* connectedPin = static_cast<Pin*>(pin);
		connectedPin->node->Slot10(connectedPin);
	}
}
