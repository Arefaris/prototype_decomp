// The chooser node of the mgraph library (0x10B6D210 - 0x10B6E360): ...
#include "code/mgraph/chooser.h"
#include "code/om/metaclass.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B6DAC0
	const char* Chooser::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B6DAE0
	inline void* Chooser::operator new(size_t)
	{
		return Allocate(Chooser::AllocationTag(), sizeof(Chooser), __alignof(Chooser));
	}

	inline void Chooser::operator delete(void* memory)
	{
		Release(memory, sizeof(Chooser), __alignof(Chooser));
	}

	// FUNCTION: ENGINE 0x10B6DE70
	void RegisterChooser()
	{
		String nodeName("Chooser", 0);
		ClassName name(core::Hash64(nodeName.GetText(), 0));
		String category("Controls", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Chooser>::RegisterDerived(CachedNodeType<Node>(), flags, name);
	}

	// FUNCTION: ENGINE 0x10B6E300
	template<> Node* NodeType<Chooser>::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new Chooser(static_cast<Graph*>(graph), *nodeName);
	}
}

using namespace om;
using namespace mgraph;



	// FUNCTION: ENGINE 0x10B6D2A0
	template om::MetaClass<mgraph::Chooser>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6D2D0
	template type_info const* om::MetaClass<mgraph::Chooser>::GetType();
	// FUNCTION: ENGINE 0x10B6D310
	template void om::MetaClass<mgraph::Chooser>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6D390
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Chooser>::Get();
	// FUNCTION: ENGINE 0x10B6D3D0
	template char const* mgraph::NodeType<mgraph::Chooser>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6D3E0
	template char const* om::MetaClass<mgraph::Chooser>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6D4D0
	template int om::MetaClass<mgraph::Chooser>::Slot5();
	// FUNCTION: ENGINE 0x10B6D4E0
	template void om::MetaClass<mgraph::Chooser>::Slot6(void*);
	// FUNCTION: ENGINE 0x10B6D4F0
	template void* mgraph::NodeType<mgraph::Chooser>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6D510
	template void* om::MetaClass<mgraph::Chooser>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6D6E0
	template void mgraph::NodeType<mgraph::Chooser>::Destroy();
	// FUNCTION: ENGINE 0x10B6D710
	template void om::MetaClass<mgraph::Chooser>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6DA60
	template mgraph::NodeType<mgraph::Chooser>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B6DAA0
	template void mgraph::NodeType<mgraph::Chooser>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6DAD0
	template void mgraph::NodeType<mgraph::Chooser>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B6DB00
	template MetaTypeBase* mgraph::NodeType<mgraph::Chooser>::FindMetaType();
	// FUNCTION: ENGINE 0x10B6DB20
	template MetaTypeBase* mgraph::NodeType<mgraph::Chooser>::GetMetaType();
	// FUNCTION: ENGINE 0x10B6DB40
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Chooser>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B6DB90
	template mgraph::NodeType<mgraph::Chooser>::~NodeType();
	// FUNCTION: ENGINE 0x10B6DCE0
	template void mgraph::NodeType<mgraph::Chooser>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);