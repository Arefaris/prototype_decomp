// engine::Function and the global templates FunctionN<R, A...>, MethodN<C, R, A...> and ClosureN<C, R, A...> (RTTI
// names): the native functions and methods the script context calls. A function knows the type codes of its result
// and arguments (Function::GetTypeCode); Invoke gets the arguments as 4-byte slots and stores the result, if any,
// through a pointer. A method is called on the object given to Invoke, a closure on the object it was made with.
// The units that bind methods explicitly instantiate the templates they use, so every member has a copy there. Member
// names are guesses.
#ifndef ENGINE_FUNCTION_H
#define ENGINE_FUNCTION_H

#include "code/engine/scriptcontext.h"
#include <typeinfo>

namespace engine
{
	// One argument slot of a call (4 bytes)
	union FunctionArgument
	{
		int i;
		unsigned int u;
		float f;
		const char* s;
		void* p;
	};

	class Function
	{
	public:
		// 0x108351B0 (another unit): the name is not kept
		Function(const char* name, int argumentCount);
		// 0x108351E0 (another unit): 'v' void, 'b' bool, 's' strings, 'i' int and unsigned int, 'f' float,
		// 'V' math::Vector, 'n' core::Name, 'h' handles, else 'e' for 4-byte types (enumerations) and 'v'
		static char GetTypeCode(const type_info& type, int size);
		// 0x107FE720 / 0x107FE760: functions live in the script context's heap
		static void* operator new(unsigned int size);
		static void operator delete(void* block);

		virtual void Invoke(void* object, const FunctionArgument* arguments, void* result) = 0;

		void* unknown4;
		int unknown8;
		char argumentTypes[8];
		char resultType;
		unsigned char argumentCount;
		bool unknown16;
	};

	// sizeof(T) for the type codes, 0 for void
	template<class T> struct FunctionTypeSize
	{
		enum
		{
			value = sizeof(T)
		};
	};

	template<> struct FunctionTypeSize<void>
	{
		enum
		{
			value = 0
		};
	};
}

template<class C, class R> class Method0 : public engine::Function
{
public:
	typedef R (C::*Pointer)();

	Method0(const char* name, Pointer newMethod) : engine::Function(name, 0)
	{
		method = newMethod;
		resultType = GetTypeCode(typeid(R), engine::FunctionTypeSize<R>::value);
	}
	// Reads the arguments in order, calls the method on object and stores the result, if any
	static void Call(C* object, const engine::FunctionArgument* arguments, void* result, Pointer method)
	{
		R value = (object->*method)();
		if (result != 0)
		{
			*(R*)result = value;
		}
	}
	virtual void Invoke(void* object, const engine::FunctionArgument* arguments, void* result)
	{
		Call((C*)object, arguments, result, method);
	}

	Pointer method;
};

template<class C, class R, class A1> class Method1 : public engine::Function
{
public:
	typedef R (C::*Pointer)(A1);

	Method1(const char* name, Pointer newMethod) : engine::Function(name, 1)
	{
		method = newMethod;
		resultType = GetTypeCode(typeid(R), engine::FunctionTypeSize<R>::value);
		argumentTypes[0] = GetTypeCode(typeid(A1), engine::FunctionTypeSize<A1>::value);
	}
	// Reads the arguments in order, calls the method on object and stores the result, if any
	static void Call(C* object, const engine::FunctionArgument* arguments, void* result, Pointer method)
	{
		A1 a1 = *(const A1*)arguments;
		R value = (object->*method)(a1);
		if (result != 0)
		{
			*(R*)result = value;
		}
	}
	virtual void Invoke(void* object, const engine::FunctionArgument* arguments, void* result)
	{
		Call((C*)object, arguments, result, method);
	}

	Pointer method;
};

template<class C, class A1> class Method1<C, void, A1> : public engine::Function
{
public:
	typedef void (C::*Pointer)(A1);

	Method1(const char* name, Pointer newMethod) : engine::Function(name, 1)
	{
		method = newMethod;
		resultType = GetTypeCode(typeid(void), engine::FunctionTypeSize<void>::value);
		argumentTypes[0] = GetTypeCode(typeid(A1), engine::FunctionTypeSize<A1>::value);
	}
	// Reads the arguments in order, calls the method on object and stores the result, if any
	static void Call(C* object, const engine::FunctionArgument* arguments, void* result, Pointer method)
	{
		A1 a1 = *(const A1*)arguments;
		(object->*method)(a1);
	}
	virtual void Invoke(void* object, const engine::FunctionArgument* arguments, void* result)
	{
		Call((C*)object, arguments, result, method);
	}

	Pointer method;
};

template<class C, class R, class A1, class A2> class Method2 : public engine::Function
{
public:
	typedef R (C::*Pointer)(A1, A2);

	Method2(const char* name, Pointer newMethod) : engine::Function(name, 2)
	{
		method = newMethod;
		resultType = GetTypeCode(typeid(R), engine::FunctionTypeSize<R>::value);
		argumentTypes[0] = GetTypeCode(typeid(A1), engine::FunctionTypeSize<A1>::value);
		argumentTypes[1] = GetTypeCode(typeid(A2), engine::FunctionTypeSize<A2>::value);
	}
	// Reads the arguments in order, calls the method on object and stores the result, if any
	static void Call(C* object, const engine::FunctionArgument* arguments, void* result, Pointer method)
	{
		A1 a1 = *(const A1*)arguments++;
		A2 a2 = *(const A2*)arguments;
		R value = (object->*method)(a1, a2);
		if (result != 0)
		{
			*(R*)result = value;
		}
	}
	virtual void Invoke(void* object, const engine::FunctionArgument* arguments, void* result)
	{
		Call((C*)object, arguments, result, method);
	}

	Pointer method;
};

template<class C, class A1, class A2> class Method2<C, void, A1, A2> : public engine::Function
{
public:
	typedef void (C::*Pointer)(A1, A2);

	Method2(const char* name, Pointer newMethod) : engine::Function(name, 2)
	{
		method = newMethod;
		resultType = GetTypeCode(typeid(void), engine::FunctionTypeSize<void>::value);
		argumentTypes[0] = GetTypeCode(typeid(A1), engine::FunctionTypeSize<A1>::value);
		argumentTypes[1] = GetTypeCode(typeid(A2), engine::FunctionTypeSize<A2>::value);
	}
	// Reads the arguments in order, calls the method on object and stores the result, if any
	static void Call(C* object, const engine::FunctionArgument* arguments, void* result, Pointer method)
	{
		A1 a1 = *(const A1*)arguments++;
		A2 a2 = *(const A2*)arguments;
		(object->*method)(a1, a2);
	}
	virtual void Invoke(void* object, const engine::FunctionArgument* arguments, void* result)
	{
		Call((C*)object, arguments, result, method);
	}

	Pointer method;
};

template<class C, class R, class A1, class A2, class A3> class Method3 : public engine::Function
{
public:
	typedef R (C::*Pointer)(A1, A2, A3);

	Method3(const char* name, Pointer newMethod) : engine::Function(name, 3)
	{
		method = newMethod;
		resultType = GetTypeCode(typeid(R), engine::FunctionTypeSize<R>::value);
		argumentTypes[0] = GetTypeCode(typeid(A1), engine::FunctionTypeSize<A1>::value);
		argumentTypes[1] = GetTypeCode(typeid(A2), engine::FunctionTypeSize<A2>::value);
		argumentTypes[2] = GetTypeCode(typeid(A3), engine::FunctionTypeSize<A3>::value);
	}
	// Reads the arguments in order, calls the method on object and stores the result, if any
	static void Call(C* object, const engine::FunctionArgument* arguments, void* result, Pointer method)
	{
		A1 a1 = *(const A1*)arguments++;
		A2 a2 = *(const A2*)arguments++;
		A3 a3 = *(const A3*)arguments;
		R value = (object->*method)(a1, a2, a3);
		if (result != 0)
		{
			*(R*)result = value;
		}
	}
	virtual void Invoke(void* object, const engine::FunctionArgument* arguments, void* result)
	{
		Call((C*)object, arguments, result, method);
	}

	Pointer method;
};

template<class C, class A1, class A2, class A3> class Method3<C, void, A1, A2, A3> : public engine::Function
{
public:
	typedef void (C::*Pointer)(A1, A2, A3);

	Method3(const char* name, Pointer newMethod) : engine::Function(name, 3)
	{
		method = newMethod;
		resultType = GetTypeCode(typeid(void), engine::FunctionTypeSize<void>::value);
		argumentTypes[0] = GetTypeCode(typeid(A1), engine::FunctionTypeSize<A1>::value);
		argumentTypes[1] = GetTypeCode(typeid(A2), engine::FunctionTypeSize<A2>::value);
		argumentTypes[2] = GetTypeCode(typeid(A3), engine::FunctionTypeSize<A3>::value);
	}
	// Reads the arguments in order, calls the method on object and stores the result, if any
	static void Call(C* object, const engine::FunctionArgument* arguments, void* result, Pointer method)
	{
		A1 a1 = *(const A1*)arguments++;
		A2 a2 = *(const A2*)arguments++;
		A3 a3 = *(const A3*)arguments;
		(object->*method)(a1, a2, a3);
	}
	virtual void Invoke(void* object, const engine::FunctionArgument* arguments, void* result)
	{
		Call((C*)object, arguments, result, method);
	}

	Pointer method;
};

template<class C, class R, class A1, class A2, class A3, class A4> class Method4 : public engine::Function
{
public:
	typedef R (C::*Pointer)(A1, A2, A3, A4);

	Method4(const char* name, Pointer newMethod) : engine::Function(name, 4)
	{
		method = newMethod;
		resultType = GetTypeCode(typeid(R), engine::FunctionTypeSize<R>::value);
		argumentTypes[0] = GetTypeCode(typeid(A1), engine::FunctionTypeSize<A1>::value);
		argumentTypes[1] = GetTypeCode(typeid(A2), engine::FunctionTypeSize<A2>::value);
		argumentTypes[2] = GetTypeCode(typeid(A3), engine::FunctionTypeSize<A3>::value);
		argumentTypes[3] = GetTypeCode(typeid(A4), engine::FunctionTypeSize<A4>::value);
	}
	// Reads the arguments in order, calls the method on object and stores the result, if any
	static void Call(C* object, const engine::FunctionArgument* arguments, void* result, Pointer method)
	{
		A1 a1 = *(const A1*)arguments++;
		A2 a2 = *(const A2*)arguments++;
		A3 a3 = *(const A3*)arguments++;
		A4 a4 = *(const A4*)arguments;
		R value = (object->*method)(a1, a2, a3, a4);
		if (result != 0)
		{
			*(R*)result = value;
		}
	}
	virtual void Invoke(void* object, const engine::FunctionArgument* arguments, void* result)
	{
		Call((C*)object, arguments, result, method);
	}

	Pointer method;
};

template<class C, class A1, class A2, class A3, class A4> class Method4<C, void, A1, A2, A3, A4> : public engine::Function
{
public:
	typedef void (C::*Pointer)(A1, A2, A3, A4);

	Method4(const char* name, Pointer newMethod) : engine::Function(name, 4)
	{
		method = newMethod;
		resultType = GetTypeCode(typeid(void), engine::FunctionTypeSize<void>::value);
		argumentTypes[0] = GetTypeCode(typeid(A1), engine::FunctionTypeSize<A1>::value);
		argumentTypes[1] = GetTypeCode(typeid(A2), engine::FunctionTypeSize<A2>::value);
		argumentTypes[2] = GetTypeCode(typeid(A3), engine::FunctionTypeSize<A3>::value);
		argumentTypes[3] = GetTypeCode(typeid(A4), engine::FunctionTypeSize<A4>::value);
	}
	// Reads the arguments in order, calls the method on object and stores the result, if any
	static void Call(C* object, const engine::FunctionArgument* arguments, void* result, Pointer method)
	{
		A1 a1 = *(const A1*)arguments++;
		A2 a2 = *(const A2*)arguments++;
		A3 a3 = *(const A3*)arguments++;
		A4 a4 = *(const A4*)arguments;
		(object->*method)(a1, a2, a3, a4);
	}
	virtual void Invoke(void* object, const engine::FunctionArgument* arguments, void* result)
	{
		Call((C*)object, arguments, result, method);
	}

	Pointer method;
};

template<class C, class R> class Closure0 : public Method0<C, R>
{
public:
	Closure0(const char* name, C* newObject, typename Method0<C, R>::Pointer newMethod) : Method0<C, R>(name, newMethod)
	{
		object = newObject;
	}
	virtual void Invoke(void* unused, const engine::FunctionArgument* arguments, void* result)
	{
		Method0<C, R>::Invoke(object, arguments, result);
	}

	C* object;
	int unknown24;
};

template<class C, class R, class A1> class Closure1 : public Method1<C, R, A1>
{
public:
	Closure1(const char* name, C* newObject, typename Method1<C, R, A1>::Pointer newMethod)
		: Method1<C, R, A1>(name, newMethod)
	{
		object = newObject;
	}
	virtual void Invoke(void* unused, const engine::FunctionArgument* arguments, void* result)
	{
		Method1<C, R, A1>::Invoke(object, arguments, result);
	}

	C* object;
	int unknown24;
};

template<class C, class R, class A1, class A2> class Closure2 : public Method2<C, R, A1, A2>
{
public:
	Closure2(const char* name, C* newObject, typename Method2<C, R, A1, A2>::Pointer newMethod)
		: Method2<C, R, A1, A2>(name, newMethod)
	{
		object = newObject;
	}
	virtual void Invoke(void* unused, const engine::FunctionArgument* arguments, void* result)
	{
		Method2<C, R, A1, A2>::Invoke(object, arguments, result);
	}

	C* object;
	int unknown24;
};

template<class C, class R, class A1, class A2, class A3> class Closure3 : public Method3<C, R, A1, A2, A3>
{
public:
	Closure3(const char* name, C* newObject, typename Method3<C, R, A1, A2, A3>::Pointer newMethod)
		: Method3<C, R, A1, A2, A3>(name, newMethod)
	{
		object = newObject;
	}
	virtual void Invoke(void* unused, const engine::FunctionArgument* arguments, void* result)
	{
		Method3<C, R, A1, A2, A3>::Invoke(object, arguments, result);
	}

	C* object;
	int unknown24;
};

template<class C, class R, class A1, class A2, class A3, class A4> class Closure4 : public Method4<C, R, A1, A2, A3, A4>
{
public:
	Closure4(const char* name, C* newObject, typename Method4<C, R, A1, A2, A3, A4>::Pointer newMethod)
		: Method4<C, R, A1, A2, A3, A4>(name, newMethod)
	{
		object = newObject;
	}
	virtual void Invoke(void* unused, const engine::FunctionArgument* arguments, void* result)
	{
		Method4<C, R, A1, A2, A3, A4>::Invoke(object, arguments, result);
	}

	C* object;
	int unknown24;
};

template<class C, class R> inline void engine::ScriptContext::RegisterMethod(const char* name, C* object, R (C::*method)())
{
	AddFunction(name, new Closure0<C, R>(name, object, method));
}

template<class C, class R, class A1> inline void engine::ScriptContext::RegisterMethod(const char* name, C* object,
	R (C::*method)(A1))
{
	AddFunction(name, new Closure1<C, R, A1>(name, object, method));
}

template<class C, class R, class A1, class A2> inline void engine::ScriptContext::RegisterMethod(const char* name, C* object,
	R (C::*method)(A1, A2))
{
	AddFunction(name, new Closure2<C, R, A1, A2>(name, object, method));
}

template<class C, class R, class A1, class A2, class A3> inline void engine::ScriptContext::RegisterMethod(const char* name,
	C* object, R (C::*method)(A1, A2, A3))
{
	AddFunction(name, new Closure3<C, R, A1, A2, A3>(name, object, method));
}

template<class C, class R, class A1, class A2, class A3, class A4> inline void engine::ScriptContext::RegisterMethod(
	const char* name, C* object, R (C::*method)(A1, A2, A3, A4))
{
	AddFunction(name, new Closure4<C, R, A1, A2, A3, A4>(name, object, method));
}

#endif
