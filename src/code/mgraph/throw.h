// The throw and catch nodes of the mgraph library (RTTI: mgraph::Throw<P> and mgraph::Catch<P>, P a packet): a throw node takes
// the packets of its one input and hands them to the catch node of the event name it is set to, which puts them out of its one
// output.
#ifndef MGRAPH_THROW_H
#define MGRAPH_THROW_H

#include "code/core/hash.h"
#include <new>
#include "code/mgraph/nodes.h"
#include "code/mgraph/pins.h"

namespace mgraph
{
	template<class P> class Catch;

	// The name key of a text that stays where it is (the engine builds the string in the expression that uses the key)
#define MGRAPH_NAME(Text) om::ClassName(core::Hash64(om::String::Wrap(Text).GetText(), 0))
	inline om::ClassName NameOf(const char* text)
	{
		return MGRAPH_NAME(text);
	}

	// The description of the node class N, found once (the engine expands it in the constructors)
	template<class N> __forceinline NodeTypeBase* CachedNodeType()
	{
		NodeTypeBase*& cache = NodeTypeCache<N>::type;
		if (cache == 0)
		{
			cache = FindNodeType(typeid(N));
		}
		return cache;
	}

	template<class P> class __declspec(align(8)) Throw : public Node
	{
	public:
		typedef typename PacketValue<P>::Type Value;

		Throw(Graph* newGraph, const om::ClassName& newName);
		virtual ~Throw();
		// Slot 8: finds the catch node of the event again
		virtual bool Slot8(void* argument);
		virtual void SetNumChannels(unsigned int newCount);
		virtual void Slot16(EvaluationFrame* frame);
		OM_ALLOCATION(Throw);

		// Sets the event the packets are thrown to: the catch node of that name in the graph, when it is one of the same packets
		void SetEventName(const om::ClassName& newEventName);
		const om::ClassName& GetEventName() const
		{
			return eventName;
		}

		// What the input brought for each channel (the engine takes the packets out without the virtual call, so the array is kept as
		// plain storage and destroyed by hand)
		typedef om::DynamicArray<P, unsigned short> ChannelArray;
		ChannelArray& GetChannels()
		{
			return *reinterpret_cast<ChannelArray*>(&channelStorage);
		}
		struct ChannelStorage
		{
			ChannelStorage() :
				data(0),
				size(0),
				capacity(0)
			{
			}
			P* data;
			unsigned short size;
			unsigned short capacity;
		};
		ChannelStorage channelStorage;  // 0x50
		om::ClassName eventName;  // 0x58
		Catch<P>* catchNode;  // 0x60
	};

	template<class P> class __declspec(align(8)) Catch : public Node
	{
	public:
		typedef typename PacketValue<P>::Type Value;

		Catch(Graph* newGraph, const om::ClassName& newName);
		virtual ~Catch();
		virtual void Slot16(EvaluationFrame* frame);
		OM_ALLOCATION(Catch);

		OutputPin<P>* output;  // 0x50
		Throw<P>* throwNode;  // 0x54: the throw node that sends to this node
	};

	template<class P> const char* Throw<P>::AllocationTag()
	{
		return "";
	}
	template<class P> const char* Catch<P>::AllocationTag()
	{
		return "";
	}

	template<class P> Throw<P>::Throw(Graph* newGraph, const om::ClassName& newName) :
		Node(CachedNodeType<Throw>(), newGraph, newName, 1, 0),
		eventName(MGRAPH_NAME("")),
		catchNode(0)
	{
		new InputPin<P>(this, &MGRAPH_NAME("i"), 0, 0, P());
	}

	template<class P> Throw<P>::~Throw()
	{
		if (catchNode != 0)
		{
			catchNode->throwNode = 0;
		}
		ChannelArray& channels = GetChannels();
		P* element = channels.data;
		if (channels.size > 0)
		{
			unsigned int remaining = channels.size;
			do
			{
				element->P::~P();
				element++;
				remaining--;
			}
			while (remaining != 0);
		}
		channels.ReleaseElements(channels.data, channels.capacity);
	}

	template<class P> bool Throw<P>::Slot8(void* argument)
	{
		SetEventName(eventName);
		return true;
	}

	template<class P> void Throw<P>::SetNumChannels(unsigned int newCount)
	{
		GetChannels().Resize(newCount, P());
		Node::SetNumChannels(newCount);
	}

	template<class P> void Throw<P>::Slot16(EvaluationFrame* frame)
	{
		FrameEntries<Value>* entries = static_cast<FrameEntries<Value>*>(frame->inputs);
		GetChannels()[frame->channel].Assign(*reinterpret_cast<P*>(entries->entries[0]), frame->id, frame->unknown18);
	}

	template<class P> void Throw<P>::SetEventName(const om::ClassName& newEventName)
	{
		catchNode = 0;
		Node* node = graph->FindNode(newEventName);
		if (node != 0)
		{
			om::MetaTypeBase* catchType = om::MetaTypeCache<Catch<P> >::type;
			NodeTypeBase* nodeType = node->type;
			if (catchType == 0)
			{
				om::MetaTypeCache<Catch<P> >::type = om::FindMetaType(typeid(Catch<P>));
				catchType = om::MetaTypeCache<Catch<P> >::type;
			}
			if (nodeType->GetMetaType() == catchType)
			{
				catchNode = static_cast<Catch<P>*>(node);
				catchNode->throwNode = this;
			}
		}
		eventName = newEventName;
	}

	template<class P> Catch<P>::Catch(Graph* newGraph, const om::ClassName& newName) :
		Node(CachedNodeType<Catch>(), newGraph, newName, 0, 1),
		throwNode(0)
	{
		output = new OutputPin<P>(this, &MGRAPH_NAME("o"), 0, P());
	}

	template<class P> Catch<P>::~Catch()
	{
		if (throwNode != 0)
		{
			throwNode->SetEventName(NameOf("Previous Catch Node Deleted."));
		}
	}

	template<class P> void Catch<P>::Slot16(EvaluationFrame* frame)
	{
		if (throwNode != 0)
		{
			P* target = reinterpret_cast<P*>(static_cast<FrameOutput<Value>*>(frame->outputs)->entry);
			target->Assign(throwNode->GetChannels()[frame->channel], frame->id, frame->unknown18);
		}
	}
	// Left to the engine: the constructors and the channel resizing of these classes do not match yet (their symbols are mapped)
	template<> Throw<Packet<om::DynamicArray<float,unsigned short> > >::Throw(Graph* newGraph, const om::ClassName& newName);
	template<> Throw<Packet<float > >::Throw(Graph* newGraph, const om::ClassName& newName);
	template<> Throw<Packet<EnvelopeData > >::Throw(Graph* newGraph, const om::ClassName& newName);
	template<> Catch<Packet<om::DynamicArray<bool,unsigned short> > >::Catch(Graph* newGraph, const om::ClassName& newName);
	template<> Catch<Packet<om::DynamicArray<float,unsigned short> > >::Catch(Graph* newGraph, const om::ClassName& newName);
	template<> Catch<Packet<om::DynamicArray<unsigned int,unsigned short> > >::Catch(Graph* newGraph, const om::ClassName& newName);
	template<> Catch<Packet<om::DynamicArray<unsigned __int64,unsigned short> > >::Catch(Graph* newGraph, const om::ClassName& newName);
	template<> Catch<Packet<om::DynamicArray<om::Vector,unsigned short> > >::Catch(Graph* newGraph, const om::ClassName& newName);
	template<> Catch<Packet<om::DynamicArray<TriggerData,unsigned short> > >::Catch(Graph* newGraph, const om::ClassName& newName);
	template<> Catch<Packet<om::DynamicArray<om::Complex,unsigned short> > >::Catch(Graph* newGraph, const om::ClassName& newName);
	template<> Catch<Packet<EnvelopeData > >::Catch(Graph* newGraph, const om::ClassName& newName);
	template<> Catch<Packet<om::DynamicArray<EnvelopeData,unsigned short> > >::Catch(Graph* newGraph, const om::ClassName& newName);
	template<> Throw<Packet<om::DynamicArray<EnvelopeData,unsigned short> > >::Throw(Graph* newGraph, const om::ClassName& newName);
	template<> Throw<Packet<om::String > >::~Throw();
	template<> Throw<Packet<om::DynamicArray<bool,unsigned short> > >::~Throw();
	template<> Throw<Packet<om::DynamicArray<unsigned int,unsigned short> > >::~Throw();
	template<> Throw<Packet<om::DynamicArray<unsigned __int64,unsigned short> > >::~Throw();
	template<> Throw<Packet<om::DynamicArray<om::String,unsigned short> > >::~Throw();
	template<> Throw<Packet<om::DynamicArray<om::Vector,unsigned short> > >::~Throw();
	template<> Throw<Packet<om::DynamicArray<TriggerData,unsigned short> > >::~Throw();
	template<> Throw<Packet<om::DynamicArray<om::Complex,unsigned short> > >::~Throw();
	template<> void Throw<Packet<om::DynamicArray<bool,unsigned short> > >::SetNumChannels(unsigned int newCount);
	template<> void Throw<Packet<om::DynamicArray<float,unsigned short> > >::SetNumChannels(unsigned int newCount);
	template<> void Throw<Packet<om::DynamicArray<EnvelopeData,unsigned short> > >::SetNumChannels(unsigned int newCount);
	template<> void Throw<Packet<om::DynamicArray<unsigned int,unsigned short> > >::SetNumChannels(unsigned int newCount);
	template<> void Throw<Packet<om::DynamicArray<unsigned __int64,unsigned short> > >::SetNumChannels(unsigned int newCount);
	template<> void Throw<Packet<om::DynamicArray<om::Vector,unsigned short> > >::SetNumChannels(unsigned int newCount);
	template<> void Throw<Packet<om::DynamicArray<mgraph::TriggerData,unsigned short> > >::SetNumChannels(unsigned int newCount);
	template<> void Throw<Packet<om::DynamicArray<om::Complex,unsigned short> > >::SetNumChannels(unsigned int newCount);
	template<> void Throw<Packet<mgraph::EnvelopeData > >::SetNumChannels(unsigned int newCount);
}

#endif
