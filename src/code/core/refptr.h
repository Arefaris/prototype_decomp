// core::RefPtr (class and member names guessed): holds one reference to a reference-counted interface, COM or
// core::IRefCount alike (only T::AddRef / T::Release are called). The DirectInput controller unit has out-of-line
// copies of the members it uses for five interfaces (0x106422E0 - 0x10642590), mapped in symbols.txt.
#ifndef CORE_REFPTR_H
#define CORE_REFPTR_H

namespace core
{
	template<class T> class RefPtr
	{
	public:
		RefPtr()
		{
			p = 0;
		}
		RefPtr(T* t)
		{
			p = t;
			if (t != 0)
			{
				t->AddRef();
			}
		}
		RefPtr(const RefPtr<T>& other)
		{
			p = other.p;
			if (p != 0)
			{
				p->AddRef();
			}
		}
		~RefPtr()
		{
			if (p != 0)
			{
				T* t = p;
				p = 0;
				t->Release();
			}
		}
		T* operator=(T* t)
		{
			T* old = p;
			if (old != t)
			{
				p = t;
				if (t != 0)
				{
					t->AddRef();
				}
				if (old != 0)
				{
					old->Release();
				}
			}
			return p;
		}
		T** operator&()
		{
			return &p;
		}
		T* operator->()
		{
			return p;
		}
		operator T*()
		{
			return p;
		}
		bool operator!=(T* t)
		{
			return p != t;
		}

		T* p;
	};

	// Releases the object and clears the pointer (out of line: each unit that uses it keeps a copy per type)
	template<class T> void SafeRelease(T*& object)
	{
		if (object != 0)
		{
			object->Release();
			object = 0;
		}
	}

	// Takes a reference to object and releases the one pointer held
	template<class T> void RefAssign(T*& pointer, T* object)
	{
		if (object != 0)
		{
			object->AddRef();
		}
		if (pointer != 0)
		{
			pointer->Release();
		}
		pointer = object;
	}
}

#endif
