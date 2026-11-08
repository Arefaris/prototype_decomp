// The delay node of the mgraph library (0x10B6E360 - 0x10B6F1A0): the reflection of the class and the description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/delay.h"
#include "code/mgraph/events.h"
#include "code/om/metaclass.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#pragma function(memset)

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B6E980
	const char* Delay::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B6E9A0
	inline void* Delay::operator new(size_t)
	{
		return Allocate(Delay::AllocationTag(), sizeof(Delay), __alignof(Delay));
	}

	// FUNCTION: ENGINE 0x10B6E720
	inline void Delay::operator delete(void* memory)
	{
		Release(memory, sizeof(Delay), __alignof(Delay));
	}

	// FUNCTION: ENGINE 0x10B6E390
	Delay::Channel::Channel() :
		minimum(0.0f),
		maximum(0.0f),
		pending(0),
		remaining(0)
	{
	}

	// FUNCTION: ENGINE 0x10B6E6A0
	// NONMATCHING: 23.0 %, the engine keeps the entry in ecx and the block pointer in eax
#ifdef NONMATCHING
	bool GetTriggerOffset(const FrameEntry<TriggerData>* entry, unsigned int* offset)
	{
		if (entry->samples == 0)
		{
			if (entry->value.unknown0)
			{
				*offset = 0;
				return true;
			}
		}
		else
		{
			unsigned int i = 0;
			do
			{
				if (*(i + entry->samples->samples) == 1)
				{
					*offset = i;
					return true;
				}
				i++;
			}
			while (i < 0x100);
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x10B6EB40
	// NONMATCHING: 98.3 %, the stores that make the trigger packet of the input pin are scheduled around the push of the packet's address
#ifdef NONMATCHING
	Delay::Delay(Graph* newGraph, const ClassName& newName) :
		Node(CachedNodeType<Delay>(), newGraph, newName, 3, 1)
	{
		new InputPin<Packet<TriggerData> >(this, &MGRAPH_NAME("i"), 1, 0, Packet<TriggerData>());
		new InputPin<Packet<float> >(this, &MGRAPH_NAME("min"), 0, 1, Packet<float>());
		new InputPin<Packet<float> >(this, &MGRAPH_NAME("max"), 0, 2, Packet<float>());
		new OutputPin<Packet<TriggerData> >(this, &MGRAPH_NAME("o"), 0, Packet<TriggerData>());
	}
#endif

	// A random number from 0 to 1 out of the 32 bits two calls of rand give
	static inline float RandomUnit()
	{
		unsigned int bits = rand();
		bits |= rand() << 17;
		return (float)bits * 2.3283064e-10f;
	}

	// FUNCTION: ENGINE 0x10B6EE60
	// NONMATCHING: 88.8 %, the stores of the pending flag and the order of the loads of the frame's members
#ifdef NONMATCHING
	void Delay::Channel::Update(Delay* node, EvaluationFrame* frame)
	{
		FrameEntry<float>* low = frame->GetInputs<float>(1)->entries[0];
		FrameEntry<float>* high = frame->GetInputs<float>(2)->entries[0];
		minimum = low->value;
		maximum = high->value;
		unsigned int offset = 0;
		if (GetTriggerOffset(frame->GetInputs<TriggerData>(0)->entries[0], &offset))
		{
			if (!(pending > 0))
			{
				float samplesPerMillisecond = node->context->owner->GetSampleRate() * 0.001f;
				float lowest = minimum;
				float highest = maximum;
				float unit = RandomUnit();
				remaining = (unsigned int)ceil((double)((lowest + (highest - lowest) * unit) * samplesPerMillisecond)) + offset;
				pending = 1;
			}
		}
		if (pending > 0)
		{
			if (remaining < 0x100)
			{
				FrameEntry<TriggerData>* output = static_cast<FrameOutput<TriggerData>*>(frame->outputs)->entry;
				unsigned int id = frame->id;
				void* allocator = *frame->allocator;
				void* samples = output->AllocateSamples(allocator, frame->unknown18, id);
				memset(samples, 0, 0x100);
				output->samples->samples[0] = 1;
				pending = 0;
			}
			remaining -= 0x100;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10B6F130
	void Delay::Slot16(EvaluationFrame* frame)
	{
		channels[frame->channel].Update(this, frame);
	}

	// FUNCTION: ENGINE 0x10B6E6F0
	Delay::~Delay()
	{
	}

	// FUNCTION: ENGINE 0x10B6E8F0
	void Delay::SetNumChannels(unsigned int newCount)
	{
		channels.Resize(newCount, Channel());
		Node::SetNumChannels(newCount);
	}

	// FUNCTION: ENGINE 0x10B6F040
	void RegisterDelay()
	{
		String nodeName("Delay", 0);
		ClassName name(core::Hash64(nodeName.GetText(), 0));
		String category("Logic", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Delay>::RegisterDerived(CachedNodeType<Node>(), flags, name);
	}

	// FUNCTION: ENGINE 0x10B6EFC0
	template<> Node* NodeType<Delay>::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new Delay(static_cast<Graph*>(graph), *nodeName);
	}
}

using namespace om;
using namespace mgraph;



	// FUNCTION: ENGINE 0x10B6E3B0
	template om::MetaClass<mgraph::Delay>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6E3E0
	template type_info const* om::MetaClass<mgraph::Delay>::GetType();
	// FUNCTION: ENGINE 0x10B6E420
	template void om::MetaClass<mgraph::Delay>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6E450
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Delay>::Get();
	// FUNCTION: ENGINE 0x10B6E490
	template char const* mgraph::NodeType<mgraph::Delay>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6E4A0
	template char const* om::MetaClass<mgraph::Delay>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6E5C0
	template int om::MetaClass<mgraph::Delay>::Slot5();
	// FUNCTION: ENGINE 0x10B6E5D0
	template void om::MetaClass<mgraph::Delay>::Slot6(void*);
	// FUNCTION: ENGINE 0x10B6E5E0
	template void* mgraph::NodeType<mgraph::Delay>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6E600
	template void* om::MetaClass<mgraph::Delay>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6E770
	template void om::MetaClass<mgraph::Delay>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6E890
	template void mgraph::NodeType<mgraph::Delay>::Destroy();
	// FUNCTION: ENGINE 0x10B6E920
	template mgraph::NodeType<mgraph::Delay>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B6E960
	template void mgraph::NodeType<mgraph::Delay>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6E990
	template void mgraph::NodeType<mgraph::Delay>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B6E9C0
	template MetaTypeBase* mgraph::NodeType<mgraph::Delay>::FindMetaType();
	// FUNCTION: ENGINE 0x10B6E9E0
	template MetaTypeBase* mgraph::NodeType<mgraph::Delay>::GetMetaType();
	// FUNCTION: ENGINE 0x10B6EA00
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Delay>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B6EA50
	template mgraph::NodeType<mgraph::Delay>::~NodeType();
	// FUNCTION: ENGINE 0x10B6EFF0
	template void mgraph::NodeType<mgraph::Delay>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);

	// FUNCTION: ENGINE 0x10B6E4B0
	template void om::DynamicArray<mgraph::Delay::Channel,unsigned short>::DestroyElements(mgraph::Delay::Channel*, unsigned short);
	// FUNCTION: ENGINE 0x10B6E590
	template char const* om::DynamicArray<mgraph::Delay::Channel,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6E650
	template om::DynamicArray<mgraph::Delay::Channel,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B6E680
	template mgraph::Delay::Channel* om::DynamicArray<mgraph::Delay::Channel,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B6E7E0
	template void om::DynamicArray<mgraph::Delay::Channel,unsigned short>::Resize(unsigned short, mgraph::Delay::Channel const&);

	// FUNCTION: ENGINE 0x10B6E440
	template om::DynamicArray<mgraph::Delay::Channel,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B6E4C0
	template mgraph::Delay::Channel& om::DynamicArray<mgraph::Delay::Channel,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B6E670
	template mgraph::Delay::Channel const& om::DynamicArray<mgraph::Delay::Channel,unsigned short>::operator[](unsigned short) const;