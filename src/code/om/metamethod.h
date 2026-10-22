// The method reflection of the om library (RTTI: om::MetaMethodBase, MetaMethod0Base<R>, MetaMethod1Base<R, A> and
// the instances MetaMethod0Const<C, B, R>, MetaMethod1<C, B, R, A>): a reflected member function of class C that is
// declared in class B (a base of C, or C itself). Slot 1 runs the method on text arguments (not reconstructed, the
// engine's copy is used), the typed slot 2 runs it on the object with the value itself.
#ifndef OM_METAMETHOD_H
#define OM_METAMETHOD_H

#include "code/om/allocation.h"
#include "code/om/name.h"

namespace om
{
	class MetaClassBase;
	typedef Name<CaseSensitive64BitKey> ClassName;

	// A node of the red-black trees the meta classes keep their members in
	struct TreeNode
	{
		TreeNode* left;
		TreeNode* right;
		TreeNode* parent;
		int color;
	};

	class MetaMethodBase
	{
	public:
		// 0x105E45F0: keeps the name and registers the method with the class it belongs to
		MetaMethodBase(MetaClassBase* owner, const ClassName& name);
		// Slot 0 (0x105CC000 is the deleting destructor: the CRT delete)
		virtual ~MetaMethodBase()
		{
		}
		// Slot 1: calls the method with arguments that come as text (the stack words are an object and three
		// argument handles that are not recovered)
		virtual void Invoke(void* object, unsigned int a, unsigned int b, unsigned int c, unsigned int d) = 0;

		TreeNode node;  // 8: the node of the class's tree of methods (the vftable pointer takes 8 bytes)
		ClassName name;  // 0x18
	};

	template<class R, class A> class MetaMethod1Base : public MetaMethodBase
	{
	public:
		MetaMethod1Base(MetaClassBase* owner, const ClassName& name) : MetaMethodBase(owner, name)
		{
		}
		virtual ~MetaMethod1Base()
		{
		}
		// Slot 2
		virtual R Call(void* object, A value) = 0;
	};

	template<class R> class MetaMethod0Base : public MetaMethodBase
	{
	public:
		MetaMethod0Base(MetaClassBase* owner, const ClassName& name) : MetaMethodBase(owner, name)
		{
		}
		virtual ~MetaMethod0Base()
		{
		}
		// Slot 2
		virtual R Call(void* object) = 0;
	};

	// A member function of B that takes one argument
	template<class C, class B, class R, class A> class MetaMethod1 : public MetaMethod1Base<R, A>
	{
	public:
		typedef R (B::*Function)(A);

		MetaMethod1(MetaClassBase* owner, const ClassName& name, Function newFunction) :
			MetaMethod1Base<R, A>(owner, name), function(newFunction)
		{
		}
		virtual ~MetaMethod1()
		{
		}
		virtual void Invoke(void* object, unsigned int a, unsigned int b, unsigned int c, unsigned int d);
		virtual R Call(void* object, A value)
		{
			return (static_cast<C*>(object)->*function)(value);
		}
		// The registration helper of the class's reflection
		static MetaMethod1* Create(MetaClassBase* owner, const ClassName& name, Function function)
		{
			return new MetaMethod1(owner, name, function);
		}
		OM_ALLOCATION(MetaMethod1);

		Function function;  // 0x20
	};

	template<class C, class B, class R, class A> const char* MetaMethod1<C, B, R, A>::AllocationTag()
	{
		return "";
	}

	// A const member function of B without arguments
	template<class C, class B, class R> class MetaMethod0Const : public MetaMethod0Base<R>
	{
	public:
		typedef R (B::*Function)() const;

		MetaMethod0Const(MetaClassBase* owner, const ClassName& name, Function newFunction) :
			MetaMethod0Base<R>(owner, name), function(newFunction)
		{
		}
		virtual ~MetaMethod0Const()
		{
		}
		virtual void Invoke(void* object, unsigned int a, unsigned int b, unsigned int c, unsigned int d);
		virtual R Call(void* object)
		{
			return (static_cast<C*>(object)->*function)();
		}
		static MetaMethod0Const* Create(MetaClassBase* owner, const ClassName& name, Function function)
		{
			return new MetaMethod0Const(owner, name, function);
		}
		OM_ALLOCATION(MetaMethod0Const);

		Function function;  // 0x20
	};

	template<class C, class B, class R> const char* MetaMethod0Const<C, B, R>::AllocationTag()
	{
		return "";
	}
}

#endif
