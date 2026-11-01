// The fade node of the mgraph library (0x10B6F1A0 - 0x10B707C0): the reflection of the class, its methods and the description of its
// node type, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/fade.h"
#include "code/mgraph/registration.h"
#include "code/om/invoke.h"
#include "code/om/metaclass.h"
#include "code/om/metamethod.h"
#include "code/om/metaproperty.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B6F9C0
	const char* Fade::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B6F170
	void Fade::SetTime(float newTime)
	{
		time = newTime;
	}

	// FUNCTION: ENGINE 0x10B6F180
	float Fade::GetTime() const
	{
		return time;
	}

	// FUNCTION: ENGINE 0x10B70550
	// NONMATCHING: the engine reads the characters of a borrowed string from the object, ours from the constructor's result, and it keeps the cached type in other registers (66.4 %)
#ifdef NONMATCHING
	void RegisterFade()
	{
		{
			String nodeName("Fade", 0);
			ClassName name(core::Hash64(nodeName.GetText(), 0));
			String category("Audio", 0);
			unsigned int flags = core::Hash32(category.GetText(), 0);
			NodeType<Fade>::RegisterDerived(CachedNodeType<Node>(), flags, name);
		}
		MetaProperty<float>::Create(FindNodeClass<Fade>(), BorrowedKey(String("Time", 1)),
			MetaMethod1<Fade, Fade, void, float>::Create(FindNodeClass<Fade>(), BorrowedKey(String("SetTime", 1)), &Fade::SetTime),
			MetaMethod0Const<Fade, Fade, float>::Create(FindNodeClass<Fade>(), BorrowedKey(String("GetTime", 1)), &Fade::GetTime), 3);
	}

#endif

	// FUNCTION: ENGINE 0x10B704D0
	template<> Node* NodeType<Fade>::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new Fade(static_cast<Graph*>(graph), *nodeName);
	}
}

using namespace om;
using namespace mgraph;


	// FUNCTION: ENGINE 0x10B6F1A0
	template om::MetaClass<mgraph::Fade>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6F1D0
	template type_info const* om::MetaClass<mgraph::Fade>::GetType();
	// FUNCTION: ENGINE 0x10B6F210
	template void om::MetaClass<mgraph::Fade>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6F280
	template char const* mgraph::NodeType<mgraph::Fade>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6F290
	template char const* om::MetaClass<mgraph::Fade>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6F340
	template char const* om::MetaMethod1<mgraph::Fade,mgraph::Fade,void,float>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6F350
	template char const* om::MetaMethod0Const<mgraph::Fade,mgraph::Fade,float>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6F380
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::Fade>::Get();
	// FUNCTION: ENGINE 0x10B6F3A0
	template MetaTypeBase* mgraph::NodeType<mgraph::Fade>::FindMetaType();
	// FUNCTION: ENGINE 0x10B6F3C0
	template int om::MetaClass<mgraph::Fade>::Slot5();
	// FUNCTION: ENGINE 0x10B6F3D0
	template void om::MetaClass<mgraph::Fade>::Slot6(void*);
	// FUNCTION: ENGINE 0x10B6F3E0
	template void* mgraph::NodeType<mgraph::Fade>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6F400
	template void* om::MetaClass<mgraph::Fade>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6F480
	template void* om::MetaMethod1<mgraph::Fade,mgraph::Fade,void,float>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6F4A0
	template om::MetaMethod1<mgraph::Fade,mgraph::Fade,void,float>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Fade,mgraph::Fade,void,float>::Function);
	// FUNCTION: ENGINE 0x10B6F4D0
	template void om::MetaMethod1<mgraph::Fade,mgraph::Fade,void,float>::Call(void*, float);
	// FUNCTION: ENGINE 0x10B6F4F0
	template om::MetaMethod1<mgraph::Fade,mgraph::Fade,void,float>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10B6F500
	template void om::MetaMethod1<mgraph::Fade,mgraph::Fade,void,float>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6F520
	template void* om::MetaMethod0Const<mgraph::Fade,mgraph::Fade,float>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6F540
	template om::MetaMethod0Const<mgraph::Fade,mgraph::Fade,float>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Fade,mgraph::Fade,float>::Function);
	// FUNCTION: ENGINE 0x10B6F570
	template float om::MetaMethod0Const<mgraph::Fade,mgraph::Fade,float>::Call(void*);
	// FUNCTION: ENGINE 0x10B6F580
	template om::MetaMethod0Const<mgraph::Fade,mgraph::Fade,float>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10B6F590
	template void om::MetaMethod0Const<mgraph::Fade,mgraph::Fade,float>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6F5B0
	template void om::MetaMethod0Const<mgraph::Fade,mgraph::Fade,float>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B6F700
	template void om::MetaClass<mgraph::Fade>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6F820
	template MetaMethod1<mgraph::Fade,mgraph::Fade,void,float>* om::MetaMethod1<mgraph::Fade,mgraph::Fade,void,float>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Fade,mgraph::Fade,void,float>::Function);
	// FUNCTION: ENGINE 0x10B6F860
	template MetaMethod0Const<mgraph::Fade,mgraph::Fade,float>* om::MetaMethod0Const<mgraph::Fade,mgraph::Fade,float>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Fade,mgraph::Fade,float>::Function);
	// FUNCTION: ENGINE 0x10B6F8F0
	template void mgraph::NodeType<mgraph::Fade>::Destroy();
	// FUNCTION: ENGINE 0x10B6F960
	template mgraph::NodeType<mgraph::Fade>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B6F9A0
	template void mgraph::NodeType<mgraph::Fade>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6F9D0
	template void mgraph::NodeType<mgraph::Fade>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B6FA00
	template MetaTypeBase* mgraph::NodeType<mgraph::Fade>::GetMetaType();
	// FUNCTION: ENGINE 0x10B6FA20
	// EQUIVALENT: shrink-wrap: the engine saves esi before testing the cached type, ours behind it (87.5 %)
	template void mgraph::NodeType<mgraph::Fade>::ReleaseMetaType();
	// FUNCTION: ENGINE 0x10B6FA70
	template mgraph::NodeType<mgraph::Fade>::~NodeType();
	// FUNCTION: ENGINE 0x10B6FB10
	template void om::MetaMethod1<mgraph::Fade,mgraph::Fade,void,float>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10B70500
	template void mgraph::NodeType<mgraph::Fade>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);