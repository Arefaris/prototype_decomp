// content::MetaObjectFactory<T, 1> and content::MetaInstanceCreatorImpl<T, 1> (RTTI names): what the content library
// loads a reflected class through. A factory (for a LoadObject-derived class) makes the object with its own virtual
// slot 2; an instance creator (for a plain class) makes one in raw memory. Each is registered under the name of the
// class meta type, once, from a function-local static of the class's registration function (RegisterMetaObjectFactory
// / RegisterMetaInstanceCreator; the engine inlines those into its start-up tables). The base classes live in the
// content library (0x105FF6A0 - 0x105FFD60); the member names are guesses.
#ifndef CONTENT_METAFACTORY_H
#define CONTENT_METAFACTORY_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"

namespace content
{
	// RTTI: content::MetaLoader (2 pure vftable slots; the factory adds a third)
	class MetaLoader
	{
	public:
		virtual void* Slot0(int a, int b, int c, int d, int e, int f) = 0;
		virtual void* Slot1(int a, int b, int c, int d, int e) = 0;

		const char* name;  // +4
		unsigned short flag;  // +8
	};

	// RTTI: content::MetaObjectFactoryBase (0x10 bytes)
	class MetaObjectFactoryBase : public MetaLoader
	{
	public:
		// 0x105FF710
		MetaObjectFactoryBase(const char* newName, unsigned short newFlag, ClassMetaType* newType);

		// 0x105FF860 / 0x105FF740 (the loaders of the class's objects, other unit)
		virtual void* Slot0(int a, int b, int c, int d, int e, int f);
		virtual void* Slot1(int a, int b, int c, int d, int e);
		// vftable slot 2: a new object of the class
		virtual LoadObject* Create() = 0;

		ClassMetaType* type;  // +0xC
	};

	template<class T, int Flag> class MetaObjectFactory : public MetaObjectFactoryBase
	{
	public:
		MetaObjectFactory(const char* newName, unsigned short newFlag, ClassMetaType* newType)
			: MetaObjectFactoryBase(newName, newFlag, newType)
		{
		}

		virtual LoadObject* Create()
		{
			return new T;
		}
	};

	// 0x105FFD20: adds the factory to the library's map under the hash of its name
	void RegisterObjectFactory(MetaObjectFactoryBase* factory);

	// The registration of T's factory: made once, on the first call
	template<class T> void RegisterMetaObjectFactory()
	{
		ClassMetaType* type = GetClassMetaType<T>();
		static MetaObjectFactory<T, 1> sFactory(type->GetName(), 1, type);
		RegisterObjectFactory(&sFactory);
	}

	// RTTI: content::MetaInstanceCreator (one pure vftable slot, 0x10 bytes): makes a plain instance of the class
	class MetaInstanceCreator
	{
	public:
		// 0x105FF6C0
		MetaInstanceCreator(const char* newName, unsigned short newFlag, ClassMetaType* newType);

		virtual void* Create() = 0;

		const char* name;  // +4
		unsigned short flag;  // +8
		ClassMetaType* type;  // +0xC
	};

	template<class T, int Flag> class MetaInstanceCreatorImpl : public MetaInstanceCreator
	{
	public:
		MetaInstanceCreatorImpl(const char* newName, unsigned short newFlag, ClassMetaType* newType)
			: MetaInstanceCreator(newName, newFlag, newType)
		{
		}

		virtual void* Create()
		{
			return new T;
		}
	};

	// 0x105FFD60: adds the creator to the library's map under the hash of its name
	void RegisterInstanceCreator(MetaInstanceCreator* creator);

	template<class T> void RegisterMetaInstanceCreator()
	{
		ClassMetaType* type = GetClassMetaType<T>();
		static MetaInstanceCreatorImpl<T, 1> sCreator(type->GetName(), 1, type);
		RegisterInstanceCreator(&sCreator);
	}
}

#endif
