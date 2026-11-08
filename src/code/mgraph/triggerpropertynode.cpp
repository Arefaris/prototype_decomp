// The property node of the triggers (0x10B6AC10 - 0x10B6BB90): the node, its events, the reflection of the class and the description of
// its node type, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/triggerpropertynode.h"
#include "code/mgraph/castnodes.h"
#include "code/mgraph/registration.h"
#include "code/om/metaclass.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	typedef PropertyNode<Packet<TriggerData> > TriggerNode;

	// FUNCTION: ENGINE 0x10B6AC40
	int TriggerNode::Slot21()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10B6ACF0
	const char* PropertyNodeInputEvent<Packet<TriggerData> >::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B6AD00
	const char* PropertyNodeOutputEvent<Packet<TriggerData> >::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B6B130
	void TriggerNode::PostInputEvent(EventQueue* queue, unsigned int channel, unsigned int value)
	{
		queue->Post(EventLink(new PropertyNodeInputEvent<Packet<TriggerData> >(this, channel, value)));
	}

	// FUNCTION: ENGINE 0x10B6B1D0
	void TriggerNode::PostOutputEvent(EventQueue* queue, unsigned int channel, bool* destination)
	{
		queue->Post(EventLink(new PropertyNodeOutputEvent<Packet<TriggerData> >(this, channel, destination)));
	}

	// FUNCTION: ENGINE 0x10B6B1B0
	MetaTypeBase* TriggerNode::GetValueMetaType()
	{
		MetaTypeBase*& cache = MetaTypeCache<TriggerData>::type;
		if (cache == 0)
		{
			cache = FindMetaType(typeid(TriggerData));
		}
		return cache;
	}

	// FUNCTION: ENGINE 0x10B6B250
	bool TriggerNode::GetFired(unsigned int channel)
	{
		return channels[channel].fired;
	}

	// FUNCTION: ENGINE 0x10B6B270
	void TriggerNode::SetFired(unsigned int channel, bool newFired)
	{
		channels[channel].fired = newFired;
	}

	// FUNCTION: ENGINE 0x10B6B290
	void TriggerNode::Slot15(unsigned int channel)
	{
		channels[channel].ClearFlags();
	}

	// FUNCTION: ENGINE 0x10B6B2B0
	void TriggerNode::SetPending(unsigned int channel, unsigned int newValue)
	{
		channels[channel].pending = 1;
		channels[channel].value = newValue;
	}

	// FUNCTION: ENGINE 0x10B6B2E0
	void TriggerNode::Trigger(unsigned int channel)
	{
		SetPending(channel, 0);
	}

	// FUNCTION: ENGINE 0x10B6B2F0
	bool TriggerNode::TakeFired(unsigned int channel)
	{
		bool wasFired = channels[channel].fired;
		channels[channel].fired = 0;
		return wasFired;
	}

	// FUNCTION: ENGINE 0x10B6B310
	bool TriggerNode::IsFired(unsigned int channel)
	{
		return channels[channel].fired;
	}

	// FUNCTION: ENGINE 0x10B6B480
	void PropertyNodeInputEvent<Packet<TriggerData> >::Execute(Context* context)
	{
		node->SetPending(channel, value);
	}

	// FUNCTION: ENGINE 0x10B6B4A0
	void PropertyNodeOutputEvent<Packet<TriggerData> >::Execute(Context* context)
	{
		*destination = node->TakeFired(channel);
	}

	// FUNCTION: ENGINE 0x10B6B4F0
	void TriggerNode::SetNumChannels(unsigned int newCount)
	{
		channels.Resize(newCount, Channel());
		Node::SetNumChannels(newCount);
	}

	// FUNCTION: ENGINE 0x10B6AC50
	TriggerNode::Channel::Channel() :
		value(0)
	{
		pending = 0;
		fired = 0;
	}

	// FUNCTION: ENGINE 0x10B6B570
	const char* TriggerNode::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B6B6E0
	// NONMATCHING: 96.7 %, the stores that make the trigger packet of the input pin are scheduled around the push of the packet's address
#ifdef NONMATCHING
	TriggerNode::PropertyNode(Graph* newGraph, const ClassName& newName, NodeTypeBase* newType) :
		PropertyNodeBase(newType, newGraph, newName, 1, 1)
	{
		new OutputPin<Packet<TriggerData> >(this, &MGRAPH_NAME("o"), 0, Packet<TriggerData>());
		new InputPin<Packet<TriggerData> >(this, &MGRAPH_NAME("i"), 0, 0, Packet<TriggerData>());
	}
#endif

	// FUNCTION: ENGINE 0x10B6B900
	template<> Node* NodeType<TriggerNode>::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new TriggerNode(static_cast<Graph*>(graph), *nodeName, CachedNodeType<TriggerNode>());
	}
}


	// FUNCTION: ENGINE 0x10B6AC60
	template om::MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6AC90
	template type_info const* om::MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::GetType();
	// FUNCTION: ENGINE 0x10B6ACD0
	template void om::MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6AD10
	template om::DynamicArray<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B6AD30
	template char const* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B6AD40
	template char const* om::MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::AllocationTag();
	// FUNCTION: ENGINE 0x10B6AD50
	template void om::DynamicArray<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel,unsigned short>::DestroyElements(mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel*, unsigned short);
	// FUNCTION: ENGINE 0x10B6ADF0
	template void om::DynamicArray<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel,unsigned short>::ReleaseElements(mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel*, unsigned short);
	// FUNCTION: ENGINE 0x10B6AE10
	template char const* om::DynamicArray<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6AF60
	template int om::MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::Slot5();
	// FUNCTION: ENGINE 0x10B6AF70
	template void om::MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::Slot6(void*);
	// FUNCTION: ENGINE 0x10B6AF80
	template void* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6AFA0
	template void* om::MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6AFF0
	template om::DynamicArray<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B6B030
	template mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel* om::DynamicArray<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B6B360
	template void om::MetaClass<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6B3D0
	template void om::DynamicArray<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel,unsigned short>::Resize(unsigned short, mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> >::Channel const&);
	// FUNCTION: ENGINE 0x10B6B4C0
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::Destroy();
	// FUNCTION: ENGINE 0x10B6B520
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B6B550
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6B580
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B6B5B0
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::FindMetaType();
	// FUNCTION: ENGINE 0x10B6B5D0
	template MetaTypeBase* mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::GetMetaType();
	// FUNCTION: ENGINE 0x10B6B5F0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B6B640
	template mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::~NodeType();
	// FUNCTION: ENGINE 0x10B6BA90
	template void mgraph::NodeType<mgraph::PropertyNode<mgraph::Packet<mgraph::TriggerData> > >::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);