// The smoother node of the mgraph library (0x10B75A30 - 0x10B76E80): the reflection of the class and its methods and the description of
// its node type, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/smoother.h"
#include "code/om/invoke.h"
#include "code/om/metaclass.h"
#include "code/om/metamethod.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B76320
	const char* Smoother::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B76340
	inline void* Smoother::operator new(size_t)
	{
		return Allocate(Smoother::AllocationTag(), sizeof(Smoother), __alignof(Smoother));
	}

	// FUNCTION: ENGINE 0x10B75FD0
	inline void Smoother::operator delete(void* memory)
	{
		Release(memory, sizeof(Smoother), __alignof(Smoother));
	}

	// FUNCTION: ENGINE 0x10B75A50
	Smoother::Channel::Channel() :
		unknown0(0.0f),
		unknown4(0.0f)
	{
	}

	// FUNCTION: ENGINE 0x10B75FA0
	Smoother::~Smoother()
	{
	}

	// FUNCTION: ENGINE 0x10B76290
	void Smoother::SetNumChannels(unsigned int newCount)
	{
		channels.Resize(newCount, Channel());
		Node::SetNumChannels(newCount);
	}

	// FUNCTION: ENGINE 0x10B76620
	Smoother::Smoother(Graph* newGraph, const ClassName& newName) :
		Node(CachedNodeType<Smoother>(), newGraph, newName, 3, 1)
	{
		new InputPin<Packet<float> >(this, &MGRAPH_NAME("i"), 0, 0, Packet<float>());
		new InputPin<Packet<float> >(this, &MGRAPH_NAME("rise_rate"), 0, 1, Packet<float>(0.01f));
		new InputPin<Packet<float> >(this, &MGRAPH_NAME("fall_rate"), 0, 2, Packet<float>(0.01f));
		new OutputPin<Packet<float> >(this, &MGRAPH_NAME("o"), 0, Packet<float>());
	}

	// FUNCTION: ENGINE 0x10B76A20
	template<> Node* NodeType<Smoother>::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new Smoother(static_cast<Graph*>(graph), *nodeName);
	}
}

using namespace om;
using namespace mgraph;


	// FUNCTION: ENGINE 0x10B75A60
	template om::MetaClass<mgraph::Smoother>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B75A90
	template type_info const* om::MetaClass<mgraph::Smoother>::GetType();
	// FUNCTION: ENGINE 0x10B75AD0
	template void om::MetaClass<mgraph::Smoother>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B75B40
	template char const* mgraph::NodeType<mgraph::Smoother>::AllocationTag();
	// FUNCTION: ENGINE 0x10B75B50
	template char const* om::MetaClass<mgraph::Smoother>::AllocationTag();
	// FUNCTION: ENGINE 0x10B75C10
	template char const* om::MetaMethod1<mgraph::Smoother,mgraph::Smoother,void,float>::AllocationTag();
	// FUNCTION: ENGINE 0x10B75C20
	template char const* om::MetaMethod0Const<mgraph::Smoother,mgraph::Smoother,float>::AllocationTag();
	// FUNCTION: ENGINE 0x10B75C50
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Smoother>::Get();
	// FUNCTION: ENGINE 0x10B75C70
	template MetaTypeBase* mgraph::NodeType<mgraph::Smoother>::FindMetaType();
	// FUNCTION: ENGINE 0x10B75C90
	template int om::MetaClass<mgraph::Smoother>::Slot5();
	// FUNCTION: ENGINE 0x10B75CA0
	template void om::MetaClass<mgraph::Smoother>::Slot6(void*);
	// FUNCTION: ENGINE 0x10B75CB0
	template void* mgraph::NodeType<mgraph::Smoother>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B75CD0
	template void* om::MetaClass<mgraph::Smoother>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B75D50
	template void* om::MetaMethod1<mgraph::Smoother,mgraph::Smoother,void,float>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B75D70
	template om::MetaMethod1<mgraph::Smoother,mgraph::Smoother,void,float>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Smoother,mgraph::Smoother,void,float>::Function);
	// FUNCTION: ENGINE 0x10B75DA0
	template void om::MetaMethod1<mgraph::Smoother,mgraph::Smoother,void,float>::Call(void*, float);
	// FUNCTION: ENGINE 0x10B75DC0
	template om::MetaMethod1<mgraph::Smoother,mgraph::Smoother,void,float>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10B75DD0
	template void om::MetaMethod1<mgraph::Smoother,mgraph::Smoother,void,float>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B75DF0
	template void* om::MetaMethod0Const<mgraph::Smoother,mgraph::Smoother,float>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B75E10
	template om::MetaMethod0Const<mgraph::Smoother,mgraph::Smoother,float>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Smoother,mgraph::Smoother,float>::Function);
	// FUNCTION: ENGINE 0x10B75E40
	template float om::MetaMethod0Const<mgraph::Smoother,mgraph::Smoother,float>::Call(void*);
	// FUNCTION: ENGINE 0x10B75E50
	template om::MetaMethod0Const<mgraph::Smoother,mgraph::Smoother,float>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10B75E60
	template void om::MetaMethod0Const<mgraph::Smoother,mgraph::Smoother,float>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B75E80
	template void om::MetaMethod0Const<mgraph::Smoother,mgraph::Smoother,float>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B76040
	template void om::MetaClass<mgraph::Smoother>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B76160
	template MetaMethod1<mgraph::Smoother,mgraph::Smoother,void,float>* om::MetaMethod1<mgraph::Smoother,mgraph::Smoother,void,float>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Smoother,mgraph::Smoother,void,float>::Function);
	// FUNCTION: ENGINE 0x10B761A0
	template MetaMethod0Const<mgraph::Smoother,mgraph::Smoother,float>* om::MetaMethod0Const<mgraph::Smoother,mgraph::Smoother,float>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Smoother,mgraph::Smoother,float>::Function);
	// FUNCTION: ENGINE 0x10B76230
	template void mgraph::NodeType<mgraph::Smoother>::Destroy();
	// FUNCTION: ENGINE 0x10B762C0
	template mgraph::NodeType<mgraph::Smoother>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B76300
	template void mgraph::NodeType<mgraph::Smoother>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B76330
	template void mgraph::NodeType<mgraph::Smoother>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B76360
	template MetaTypeBase* mgraph::NodeType<mgraph::Smoother>::GetMetaType();
	// FUNCTION: ENGINE 0x10B76380
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Smoother>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B763D0
	template mgraph::NodeType<mgraph::Smoother>::~NodeType();
	// FUNCTION: ENGINE 0x10B764F0
	template void om::MetaMethod1<mgraph::Smoother,mgraph::Smoother,void,float>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B76A50
	template void mgraph::NodeType<mgraph::Smoother>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);

	// FUNCTION: ENGINE 0x10B75B60
	template void om::DynamicArray<mgraph::Smoother::Channel,unsigned short>::DestroyElements(mgraph::Smoother::Channel*, unsigned short);
	// FUNCTION: ENGINE 0x10B75BF0
	template void om::DynamicArray<mgraph::Smoother::Channel,unsigned short>::ReleaseElements(mgraph::Smoother::Channel*, unsigned short);
	// FUNCTION: ENGINE 0x10B75C40
	template char const* om::DynamicArray<mgraph::Smoother::Channel,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B75D20
	template om::DynamicArray<mgraph::Smoother::Channel,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B75F80
	template mgraph::Smoother::Channel* om::DynamicArray<mgraph::Smoother::Channel,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B760B0
	template void om::DynamicArray<mgraph::Smoother::Channel,unsigned short>::Resize(unsigned short, mgraph::Smoother::Channel const&);

	// FUNCTION: ENGINE 0x10B75AF0
	template om::DynamicArray<mgraph::Smoother::Channel,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B75B70
	template mgraph::Smoother::Channel& om::DynamicArray<mgraph::Smoother::Channel,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B75D40
	template mgraph::Smoother::Channel const& om::DynamicArray<mgraph::Smoother::Channel,unsigned short>::operator[](unsigned short) const;