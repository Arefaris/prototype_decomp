// The property node of the triggers (RTTI: mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData>> with its input and output events;
// 0x10B6AC10 - 0x10B6BB90). A trigger is not a value that stays: the node keeps for each channel a count and two flags, one for a
// trigger that is waiting to go out and one for a trigger that went out, so it is a class of its own and not an instance of the template.
#ifndef MGRAPH_TRIGGERPROPERTYNODE_H
#define MGRAPH_TRIGGERPROPERTYNODE_H

#include "code/mgraph/propertynode.h"
#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterTriggerPropertyNode();

	template<> class __declspec(align(8)) PropertyNode<Packet<TriggerData> > : public PropertyNodeBase
	{
	public:
		// What the node keeps for each channel (names guessed; 8 bytes)
		struct Channel
		{
			Channel();
			Channel* ClearFlags()
			{
				pending = 0;
				fired = 0;
				return this;
			}
			unsigned int value;
			unsigned char pending : 1;
			unsigned char fired : 1;
		};

		PropertyNode(Graph* newGraph, const om::ClassName& newName, NodeTypeBase* newType);
		virtual void SetNumChannels(unsigned int newCount);
		virtual void Slot15(unsigned int channel);
		virtual void Slot16(EvaluationFrame* frame);
		virtual om::MetaTypeBase* GetValueMetaType();
		virtual int Slot21();
		OM_ALLOCATION(PropertyNode);

		// Queues an event that sets a channel / that takes the flag of a channel (names guessed)
		void PostInputEvent(EventQueue* queue, unsigned int channel, unsigned int value);
		void PostOutputEvent(EventQueue* queue, unsigned int channel, bool* destination);
		bool GetFired(unsigned int channel);
		void SetFired(unsigned int channel, bool fired);
		void SetPending(unsigned int channel, unsigned int value);
		void Trigger(unsigned int channel);
		bool TakeFired(unsigned int channel);
		bool IsFired(unsigned int channel);

		char unknown50[8];
		om::DynamicArray<Channel, unsigned short> channels;  // 0x58
	};

	// An event that sets a channel of the node (RTTI: mgraph::PropertyNodeInputEvent<P>, 0x14 bytes)
	template<> class PropertyNodeInputEvent<Packet<TriggerData> > : public ContextEvent
	{
	public:
		PropertyNodeInputEvent(PropertyNode<Packet<TriggerData> >* newNode, unsigned int newChannel, unsigned int newValue) :
			node(newNode),
			channel(newChannel),
			value(newValue)
		{
		}
		virtual void Execute(Context* context);
		OM_ALLOCATION(PropertyNodeInputEvent);

		PropertyNode<Packet<TriggerData> >* node;  // 8
		unsigned int channel;  // 0xC
		unsigned int value;  // 0x10
	};

	// An event that takes the flag of a channel out of the node (RTTI: mgraph::PropertyNodeOutputEvent<P>, 0x14 bytes)
	template<> class PropertyNodeOutputEvent<Packet<TriggerData> > : public ContextEvent
	{
	public:
		PropertyNodeOutputEvent(PropertyNode<Packet<TriggerData> >* newNode, unsigned int newChannel, bool* newDestination) :
			node(newNode),
			channel(newChannel),
			destination(newDestination)
		{
		}
		virtual void Execute(Context* context);
		OM_ALLOCATION(PropertyNodeOutputEvent);

		PropertyNode<Packet<TriggerData> >* node;  // 8
		unsigned int channel;  // 0xC
		bool* destination;  // 0x10
	};
}

namespace om
{
	// The loops that fill and copy the elements are the engine's
	template<> void DynamicArray<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel, unsigned short>::FillElements(
		mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel* destination, unsigned short count,
		const mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel& value);
	template<> void DynamicArray<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel, unsigned short>::CopyElements(
		mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel* destination,
		const mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel* source, unsigned short count);
}

#endif
