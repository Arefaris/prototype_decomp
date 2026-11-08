// The system node of the mgraph library (0x10B76E80 - 0x10B77640): the reflection of the class and the description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/systemnode.h"
#include "code/mgraph/events.h"
#include "code/om/metaclass.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B77230
	const char* SystemNode::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B77250
	inline void* SystemNode::operator new(size_t)
	{
		return Allocate(SystemNode::AllocationTag(), sizeof(SystemNode), __alignof(SystemNode));
	}

	// FUNCTION: ENGINE 0x10B76EC0
	inline void SystemNode::operator delete(void* memory)
	{
		Release(memory, sizeof(SystemNode), __alignof(SystemNode));
	}

	// FUNCTION: ENGINE 0x10B773F0
	SystemNode::SystemNode(Graph* newGraph, const ClassName& newName) :
		Node(CachedNodeType<SystemNode>(), newGraph, newName, 0, 1)
	{
		new OutputPin<Packet<unsigned __int64> >(this, &MGRAPH_NAME("evaluate_count"), 0, Packet<unsigned __int64>());
	}

	// FUNCTION: ENGINE 0x10B76EB0
	SystemNode::~SystemNode()
	{
	}

	// FUNCTION: ENGINE 0x10B76EE0
	void SystemNode::SetNumChannels(unsigned int newCount)
	{
		Node::SetNumChannels(newCount);
	}

	// FUNCTION: ENGINE 0x10B77020
	// NONMATCHING: the engine reads the frame's id into edi, ours into edx (81.6 %)
#ifdef NONMATCHING
	// Puts a value and the id of the frame in an output
	static inline void SetOutput(FrameEntry<unsigned __int64>* output, unsigned int id, unsigned __int64 value)
	{
		output->id = id;
		output->value = value;
	}

	void SystemNode::Slot16(EvaluationFrame* frame)
	{
		FrameEntry<unsigned __int64>* output = static_cast<FrameOutput<unsigned __int64>*>(frame->outputs)->entry;
		SetOutput(output, frame->id, (unsigned int)context->GetChannelOwner());
	}

#endif

	// FUNCTION: ENGINE 0x10B77550
	void RegisterSystemNode()
	{
		String nodeName("SystemNode", 0);
		ClassName name(core::Hash64(nodeName.GetText(), 0));
		String category("System", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<SystemNode>::RegisterDerived(CachedNodeType<Node>(), flags, name);
	}

	// FUNCTION: ENGINE 0x10B774D0
	template<> Node* NodeType<SystemNode>::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new SystemNode(static_cast<Graph*>(graph), *nodeName);
	}
}

using namespace om;
using namespace mgraph;



	// FUNCTION: ENGINE 0x10B76EF0
	template om::MetaClass<mgraph::SystemNode>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B76F20
	template type_info const* om::MetaClass<mgraph::SystemNode>::GetType();
	// FUNCTION: ENGINE 0x10B76F60
	template void om::MetaClass<mgraph::SystemNode>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B76F80
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::SystemNode>::Get();
	// FUNCTION: ENGINE 0x10B76FC0
	template char const* mgraph::NodeType<mgraph::SystemNode>::AllocationTag();
	// FUNCTION: ENGINE 0x10B76FD0
	template char const* om::MetaClass<mgraph::SystemNode>::AllocationTag();
	// FUNCTION: ENGINE 0x10B77070
	template int om::MetaClass<mgraph::SystemNode>::Slot5();
	// FUNCTION: ENGINE 0x10B77080
	template void om::MetaClass<mgraph::SystemNode>::Slot6(void*);
	// FUNCTION: ENGINE 0x10B77090
	template void* mgraph::NodeType<mgraph::SystemNode>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B770B0
	template void* om::MetaClass<mgraph::SystemNode>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B77130
	template void om::MetaClass<mgraph::SystemNode>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B771A0
	template void mgraph::NodeType<mgraph::SystemNode>::Destroy();
	// FUNCTION: ENGINE 0x10B771D0
	template mgraph::NodeType<mgraph::SystemNode>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B77210
	template void mgraph::NodeType<mgraph::SystemNode>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B77240
	template void mgraph::NodeType<mgraph::SystemNode>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B77270
	template MetaTypeBase* mgraph::NodeType<mgraph::SystemNode>::FindMetaType();
	// FUNCTION: ENGINE 0x10B77290
	template MetaTypeBase* mgraph::NodeType<mgraph::SystemNode>::GetMetaType();
	// FUNCTION: ENGINE 0x10B772B0
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::SystemNode>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B77300
	template mgraph::NodeType<mgraph::SystemNode>::~NodeType();
	// FUNCTION: ENGINE 0x10B77500
	template void mgraph::NodeType<mgraph::SystemNode>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);