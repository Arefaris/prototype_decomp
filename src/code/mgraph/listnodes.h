// The list nodes of the mgraph library (RTTI: mgraph::ListCount<T> and mgraph::ListEntry<T>): the first puts out how many
// elements the list at its input has, the second one of the elements.
#ifndef MGRAPH_LISTNODES_H
#define MGRAPH_LISTNODES_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	// The comparison of the trigger values the list entry node makes
	inline bool operator!=(const TriggerData& left, const TriggerData& right)
	{
		return left.unknown0 != right.unknown0;
	}

	template<class T> class __declspec(align(8)) ListCount : public Node
	{
	public:
		typedef Packet<T> ElementPacket;
		typedef Packet<om::DynamicArray<T, unsigned short> > ListPacket;

		ListCount(Graph* newGraph, const om::ClassName& newName);
		virtual void Slot16(EvaluationFrame* frame);
		OM_ALLOCATION(ListCount);
	};

	template<class T> const char* ListCount<T>::AllocationTag()
	{
		return "";
	}

	template<class T> ListCount<T>::ListCount(Graph* newGraph, const om::ClassName& newName) :
		Node(CachedNodeType<ListCount>(), newGraph, newName, 1, 1)
	{
		new OutputPin<Packet<unsigned int> >(this, &MGRAPH_NAME("count"), 0, Packet<unsigned int>());
		new InputPin<ListPacket>(this, &MGRAPH_NAME("list_in"), 0, 0, ListPacket());
	}

	template<class T> void ListCount<T>::Slot16(EvaluationFrame* frame)
	{
		FrameEntry<om::DynamicArray<T, unsigned short> >** entries = frame->GetInputs<om::DynamicArray<T, unsigned short> >(0)->entries;
		unsigned int count = 0;
		if (entries[0] != 0)
		{
			count = entries[0]->value.size;
		}
		FrameEntry<unsigned int>* output = static_cast<FrameOutput<unsigned int>*>(frame->outputs)->entry;
		unsigned int id = frame->id;
		output->value = count;
		output->id = id;
	}

	// Whether a packet of the frame is there (out of line in the engine, one copy for each packet type)
	template<class P> bool PacketPresent(const P* packet)
	{
		return packet != 0;
	}

	template<class T> class __declspec(align(8)) ListEntry : public Node
	{
	public:
		typedef Packet<T> ElementPacket;
		typedef Packet<om::DynamicArray<T, unsigned short> > ListPacket;

		ListEntry(Graph* newGraph, const om::ClassName& newName);
		virtual void Slot16(EvaluationFrame* frame);
		OM_ALLOCATION(ListEntry);
	};

	template<class T> const char* ListEntry<T>::AllocationTag()
	{
		return "";
	}

	template<class T> ListEntry<T>::ListEntry(Graph* newGraph, const om::ClassName& newName) :
		Node(CachedNodeType<ListEntry>(), newGraph, newName, 2, 1)
	{
		new OutputPin<ElementPacket>(this, &MGRAPH_NAME("entry"), 0, ElementPacket());
		new InputPin<ListPacket>(this, &MGRAPH_NAME("list_in"), 0, 0, ListPacket());
		new InputPin<Packet<unsigned int> >(this, &MGRAPH_NAME("list_index"), 0, 1, Packet<unsigned int>());
	}

	template<class T> void ListEntry<T>::Slot16(EvaluationFrame* frame)
	{
		FrameEntry<om::DynamicArray<T, unsigned short> >* list = frame->GetInputs<om::DynamicArray<T, unsigned short> >(0)->entries[0];
		FrameEntry<unsigned int>* index = frame->GetInputs<unsigned int>(1)->entries[0];
		T result = T();
		if (PacketPresent(list))
		{
			if (PacketPresent(index) && list->value.size > index->value)
			{
				result = list->value.data[static_cast<unsigned short>(index->value)];
			}
		}
		FrameEntry<T>* output = static_cast<FrameOutput<T>*>(frame->outputs)->entry;
		if (result != output->value)
		{
			unsigned int id = frame->id;
			output->value = result;
			output->id = id;
		}
	}

	// Left to the engine: the constructors that would expand the pins of these packet types, whose virtual functions the engine
	// shares between identical copies

	template<> ListCount<EnvelopeData>::ListCount(Graph* newGraph, const om::ClassName& newName);

	// Left to the engine (compared by the types' own tests, not reconstructed)
	template<> void ListEntry<om::Vector>::Slot16(EvaluationFrame* frame);
	template<> void ListEntry<om::Complex>::Slot16(EvaluationFrame* frame);
	template<> void ListEntry<EnvelopeData>::Slot16(EvaluationFrame* frame);
}

#endif
