// The audio library's material map (engine::AudioMaterialMap; 0x108CEDE0 - 0x108D1110): the accessors the reflection
// binds as the property "Map" and the om library's template instances for them.
#include "code/engine/audio/audiomaterialmap.h"
#include "code/om/atgcontent.h"
#include "code/om/delegate.h"
#include "code/om/invoke.h"
#include "code/om/metaattrib.h"
#include "code/om/metaclass.h"
#include "code/om/metamethod.h"
#include "code/om/metaproperty.h"
#include "code/om/textvalue.h"

#pragma warning(disable: 4661)

namespace engine
{
	AudioMaterialMap::AudioMaterialMap(const om::ClassName& newName) :
		Entity(newName),
		map()
	{
	}

	om::EntityTypeBase* AudioMaterialMap::GetEntityType()
	{
		return om::FindEntityType(typeid(AudioMaterialMap));
	}

	const MaterialDictionary& AudioMaterialMap::GetMap() const
	{
		return map;
	}

	void AudioMaterialMap::SetMap(const MaterialDictionary& newMap)
	{
		map = newMap;
	}
}

namespace om
{
	typedef engine::MaterialDictionary MaterialDictionary;

	// The engine's copy of this one calls a copy of the allocation tag that its own users do not
	template<> MaterialDictionary* ReadArgument<MaterialDictionary>(BinaryStream* stream, GarbageList* list);

	template class EntityType<engine::AudioMaterialMap>;
	template class AtgContentEntity<engine::AudioMaterialMap>;
	template class AtgContentEntityLoader<engine::AudioMaterialMap>;
	template class MetaAttrib<MaterialDictionary>;
	template class MetaClass<engine::AudioMaterialMap>;
	template class MetaMethod1<engine::AudioMaterialMap, engine::AudioMaterialMap, void, const MaterialDictionary&>;
	template class MetaMethod0Const<engine::AudioMaterialMap, engine::AudioMaterialMap, const MaterialDictionary&>;
	template class MetaProperty<const MaterialDictionary&>;
	template class DelegateMetaProperty<const MaterialDictionary&>;
	template class Garbage<MaterialDictionary>;
}

// The attribute accessors: the engine adds the offset to the object in registers of its own (the same operations)
// FUNCTION: ENGINE 0x108D0550 @ om::ReadBinary(om::BinaryStream *, om::Dictionary<...> *)
// EQUIVALENT: scheduling of the loads and stores that copy the entry into its node (91.2 %)
// FUNCTION: ENGINE 0x108CFEC0 @ om::WriteBinary(om::BinaryStream *, om::Dictionary<...> const &)
// EQUIVALENT: scheduling of the loads and stores of the copies that are written, and the place of the terminator (91.4 %)
// FUNCTION: ENGINE 0x108D08F0 @ om::Dictionary<...>::operator=
// EQUIVALENT: register allocation: the engine forms the link of the node with lea, ours adds in place (98.6 %)
// FUNCTION: ENGINE 0x108D0A70 @ om::Dictionary<...>::Dictionary(om::Dictionary<...> const &)
// EQUIVALENT: register allocation: the engine forms the link of the node with lea, ours adds in place (98.6 %)
// FUNCTION: ENGINE 0x108D0FE0 @ om::MetaAttrib<om::Dictionary<...> >::ReadText
// EQUIVALENT: register allocation and scheduling of the offset sum (41.7 %)
// FUNCTION: ENGINE 0x108D1000 @ om::MetaAttrib<om::Dictionary<...> >::ReadBinary
// EQUIVALENT: register allocation and scheduling of the offset sum (41.7 %)
// FUNCTION: ENGINE 0x108D0530 @ om::MetaAttrib<om::Dictionary<...> >::WriteBinary
// EQUIVALENT: register allocation and scheduling of the offset sum (41.7 %)

// FUNCTION: ENGINE 0x108D02B0 @ public: virtual void __thiscall om::EntityType<class engine::AudioMaterialMap>::CreateEntity(class om::Entity * *,class om::Name<struct om::CaseSensitive64BitKey> const &
// FUNCTION: ENGINE 0x108D0300 @ public: virtual void __thiscall om::EntityType<class engine::AudioMaterialMap>::CreateUnregisteredEntity(class om::Entity * *,class om::Name<struct om::CaseSensitive64Bit
// FUNCTION: ENGINE 0x108D0360 @ public: virtual void __thiscall om::EntityType<class engine::AudioMaterialMap>::CreateUnregisteredEntity2(class om::Entity * *,class om::Name<struct om::CaseSensitive64Bi
// FUNCTION: ENGINE 0x108D09D0 @ public: virtual void __thiscall om::MetaMethod0Const<class engine::AudioMaterialMap,class engine::AudioMaterialMap,class om::Dictionary<class om::Name<struct om::CaseSens
// FUNCTION: ENGINE 0x108D1020 @ public: virtual void __thiscall om::MetaMethod1<class engine::AudioMaterialMap,class engine::AudioMaterialMap,void,class om::Dictionary<class om::Name<struct om::CaseSens

// FUNCTION: ENGINE 0x108CEE70 @ public: static char const * __cdecl om::Garbage<class om::Dictionary<class om::Name<struct om::CaseSensitive64BitKey>,class om::Name<struct om::CaseSensitive64BitKey>,str

// FUNCTION: ENGINE 0x108D08B0 @ public: virtual class om::AtgContentEntityBase * __thiscall om::AtgContentEntityLoader<class engine::AudioMaterialMap>::CreateContent(class om::Entity *)

// FUNCTION: ENGINE 0x108D06D0 @ bool __cdecl om::ReadText(class om::TextValue const *,class om::Dictionary<class om::Name<struct om::CaseSensitive64BitKey>,class om::Name<struct om::CaseSensitive64BitKe
// FUNCTION: ENGINE 0x108D0EF0 @ public: virtual bool __thiscall om::MetaProperty<class om::Dictionary<class om::Name<struct om::CaseSensitive64BitKey>,class om::Name<struct om::CaseSensitive64BitKey>,st

// FUNCTION: ENGINE 0x108CFA90 @ void __cdecl om::WriteText(class om::TextValue *,class om::Dictionary<class om::Name<struct om::CaseSensitive64BitKey>,class om::Name<struct om::CaseSensitive64BitKey>,st
// FUNCTION: ENGINE 0x108D0B50 @ public: virtual void __thiscall om::MetaProperty<class om::Dictionary<class om::Name<struct om::CaseSensitive64BitKey>,class om::Name<struct om::CaseSensitive64BitKey>,st
// FUNCTION: ENGINE 0x108D0E50 @ public: virtual class om::Dictionary<class om::Name<struct om::CaseSensitive64BitKey>,class om::Name<struct om::CaseSensitive64BitKey>,struct om::Comparer<class om::Name<

// ---- annotations of the functions mapped in symbols.txt (generated) ----

// FUNCTION: ENGINE 0x108CEDE0 @ type_info const * om::MetaClass<engine::AudioMaterialMap>::GetType(void)
// FUNCTION: ENGINE 0x108CEE10 @ om::MetaClass<engine::AudioMaterialMap>::~MetaClass<engine::AudioMaterialMap>(void)
// FUNCTION: ENGINE 0x108CEE20 @ void om::MetaClass<engine::AudioMaterialMap>::operator delete(void *)
// FUNCTION: ENGINE 0x108CEE80 @ char const * om::EntityType<engine::AudioMaterialMap>::AllocationTag(void)
// FUNCTION: ENGINE 0x108CEE90 @ char const * om::MetaClass<engine::AudioMaterialMap>::AllocationTag(void)
// FUNCTION: ENGINE 0x108CEEA0 @ om::MetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const &>::Met
// FUNCTION: ENGINE 0x108CEEE0 @ type_info const * om::MetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey>
// FUNCTION: ENGINE 0x108CEF20 @ om::MetaMethod1Base<void,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const
// FUNCTION: ENGINE 0x108CEF80 @ void * om::MetaMethod1Base<void,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > 
// FUNCTION: ENGINE 0x108CEFA0 @ void * om::MetaMethod0Base<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > con
// FUNCTION: ENGINE 0x108CEFD0 @ om::MetaAttrib<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >::MetaAttrib<o
// FUNCTION: ENGINE 0x108CF000 @ om::MetaAttrib<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >::~MetaAttrib<
// FUNCTION: ENGINE 0x108CF010 @ void om::MetaAttrib<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >::operato
// FUNCTION: ENGINE 0x108CF030 @ char const * om::MetaMethod1<engine::AudioMaterialMap,engine::AudioMaterialMap,void,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>
// FUNCTION: ENGINE 0x108CF040 @ char const * om::MetaMethod0Const<engine::AudioMaterialMap,engine::AudioMaterialMap,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>
// FUNCTION: ENGINE 0x108CF050 @ char const * om::MetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > 
// FUNCTION: ENGINE 0x108CF100 @ char const * om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > >::Node::NodeAlloca
// FUNCTION: ENGINE 0x108CF110 @ char const * om::DelegateMetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitK
// FUNCTION: ENGINE 0x108CF140 @ om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > >::Dictionary<om::Name<om::CaseS
// FUNCTION: ENGINE 0x108CF180 @ int om::MetaClass<engine::AudioMaterialMap>::Slot5(void)
// FUNCTION: ENGINE 0x108CF190 @ void om::MetaClass<engine::AudioMaterialMap>::Slot6(void *)
// FUNCTION: ENGINE 0x108CF1A0 @ void * om::Garbage<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >::operator
// FUNCTION: ENGINE 0x108CF1C0 @ void * om::EntityType<engine::AudioMaterialMap>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108CF1E0 @ void * om::MetaClass<engine::AudioMaterialMap>::operator new(unsigned int)
// FUNCTION: ENGINE 0x108CF200 @ void * om::MetaClass<engine::AudioMaterialMap>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CF230 @ void * om::MetaAttrib<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >::opera
// FUNCTION: ENGINE 0x108CF250 @ om::MetaMethod1<engine::AudioMaterialMap,engine::AudioMaterialMap,void,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer
// FUNCTION: ENGINE 0x108CF280 @ void om::MetaMethod1<engine::AudioMaterialMap,engine::AudioMaterialMap,void,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Com
// FUNCTION: ENGINE 0x108CF2A0 @ om::MetaMethod1Base<void,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const
// FUNCTION: ENGINE 0x108CF2B0 @ void om::MetaMethod1<engine::AudioMaterialMap,engine::AudioMaterialMap,void,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Com
// FUNCTION: ENGINE 0x108CF2E0 @ char const * om::AtgContentEntityLoader<engine::AudioMaterialMap>::AllocationTag(void) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CF2F0 @ void * om::MetaMethod0Const<engine::AudioMaterialMap,engine::AudioMaterialMap,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::C
// FUNCTION: ENGINE 0x108CF310 @ om::MetaMethod0Const<engine::AudioMaterialMap,engine::AudioMaterialMap,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer
// FUNCTION: ENGINE 0x108CF340 @ om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const & om::MetaMethod0Const<e
// FUNCTION: ENGINE 0x108CF350 @ om::MetaMethod0Base<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const &>::
// FUNCTION: ENGINE 0x108CF360 @ void om::MetaMethod0Const<engine::AudioMaterialMap,engine::AudioMaterialMap,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Com
// FUNCTION: ENGINE 0x108CF380 @ void * om::MetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const 
// FUNCTION: ENGINE 0x108CF3C0 @ void * om::MetaMethod1<engine::AudioMaterialMap,engine::AudioMaterialMap,void,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::C
// FUNCTION: ENGINE 0x108CF3F0 @ void * om::MetaMethod0Const<engine::AudioMaterialMap,engine::AudioMaterialMap,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::C
// FUNCTION: ENGINE 0x108CF420 @ void * om::MetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const 
// FUNCTION: ENGINE 0x108CF450 @ void * om::MetaAttrib<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >::`scal
// FUNCTION: ENGINE 0x108CF480 @ om::MetaMethod1Base<void,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const
// FUNCTION: ENGINE 0x108CF490 @ om::MetaMethod0Base<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const &> *
// FUNCTION: ENGINE 0x108CF4C0 @ om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > >::Node * om::Dictionary<om::Nam
// FUNCTION: ENGINE 0x108CF500 @ void * om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > >::Node::operator new(uns
// FUNCTION: ENGINE 0x108CF520 @ om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > >::Node::Node(om::Name<om::CaseS
// FUNCTION: ENGINE 0x108CF550 @ void * om::DelegateMetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > 
// FUNCTION: ENGINE 0x108CF570 @ void * om::AtgContentEntityLoader<engine::AudioMaterialMap>::operator new(unsigned int) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CF590 @ om::Garbage<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >::Garbage<om::Dic
// FUNCTION: ENGINE 0x108CF5B0 @ void om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > >::operator delete(void *)
// FUNCTION: ENGINE 0x108CF5D0 @ void om::Garbage<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >::operator d
// FUNCTION: ENGINE 0x108CF5F0 @ om::DelegateProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >::Delega
// FUNCTION: ENGINE 0x108CF600 @ om::MetaTypeBase * om::DelegateProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64Bi
// FUNCTION: ENGINE 0x108CF610 @ om::DelegateProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >::~Deleg
// FUNCTION: ENGINE 0x108CF620 @ void * om::DelegateProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >:
// FUNCTION: ENGINE 0x108CF6C0 @ om::AtgContentEntityLoader<engine::AudioMaterialMap>::AtgContentEntityLoader<engine::AudioMaterialMap>(void)
// FUNCTION: ENGINE 0x108CF700 @ void om::AtgContentEntity<engine::AudioMaterialMap>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CF720 @ char const * om::AtgContentEntity<engine::AudioMaterialMap>::AllocationTag(void)
// FUNCTION: ENGINE 0x108CF730 @ om::AtgContentEntityLoader<engine::AudioMaterialMap>::~AtgContentEntityLoader<engine::AudioMaterialMap>(void)
// FUNCTION: ENGINE 0x108CF740 @ void * om::AtgContentEntity<engine::AudioMaterialMap>::operator new(unsigned int) (name guess; identical copies)
// FUNCTION: ENGINE 0x108CF760 @ void * om::AtgContentEntityLoader<engine::AudioMaterialMap>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CF790 @ void om::MetaClass<engine::AudioMaterialMap>::Create(om::Name<om::CaseSensitive64BitKey> const &,om::MetaClassBase *)
// FUNCTION: ENGINE 0x108CF800 @ om::MetaMethod1<engine::AudioMaterialMap,engine::AudioMaterialMap,void,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer
// FUNCTION: ENGINE 0x108CF840 @ om::MetaMethod0Const<engine::AudioMaterialMap,engine::AudioMaterialMap,om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer
// FUNCTION: ENGINE 0x108CF880 @ void om::MetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const &>
// FUNCTION: ENGINE 0x108CF9F0 @ om::DelegateMetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const
// FUNCTION: ENGINE 0x108CFA20 @ void om::DelegateMetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > 
// FUNCTION: ENGINE 0x108CFA30 @ void om::DelegateMetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > 
// FUNCTION: ENGINE 0x108CFA50 @ om::DelegateMetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const
// FUNCTION: ENGINE 0x108CFA60 @ void * om::DelegateMetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > 
// FUNCTION: ENGINE 0x108CFC70 @ om::EntityType<engine::AudioMaterialMap>::EntityType<engine::AudioMaterialMap>(char const *,unsigned int,unsigned int,bool)
// FUNCTION: ENGINE 0x108CFCF0 @ void * engine::AudioMaterialMap::operator new(unsigned int)
// FUNCTION: ENGINE 0x108CFD10 @ void om::EntityType<engine::AudioMaterialMap>::operator delete(void *)
// FUNCTION: ENGINE 0x108CFD30 @ om::MetaTypeBase * om::EntityType<engine::AudioMaterialMap>::GetMetaType(void)
// FUNCTION: ENGINE 0x108CFDA0 @ om::EntityType<engine::AudioMaterialMap>::~EntityType<engine::AudioMaterialMap>(void)
// FUNCTION: ENGINE 0x108CFE00 @ void * om::EntityType<engine::AudioMaterialMap>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108CFE70 @ om::DelegatePropertyBase * om::MetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive
// FUNCTION: ENGINE 0x108CFFC0 @ void om::AttributeWriteText<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >(
// FUNCTION: ENGINE 0x108D0150 @ om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > >::~Dictionary<om::Name<om::Case
// FUNCTION: ENGINE 0x108D0190 @ void om::DelegateMetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > 
// FUNCTION: ENGINE 0x108D01C0 @ void om::MetaAttrib<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >::WriteTe
// FUNCTION: ENGINE 0x108D01E0 @ bool om::AttributeWriteBinary<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > 
// FUNCTION: ENGINE 0x108D01F0 @ void * om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > >::`scalar deleting destr
// FUNCTION: ENGINE 0x108D0230 @ engine::AudioMaterialMap::AudioMaterialMap(om::Name<om::CaseSensitive64BitKey> const &)
// FUNCTION: ENGINE 0x108D0260 @ void om::MetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const &>
// FUNCTION: ENGINE 0x108D0280 @ om::EntityTypeBase * engine::AudioMaterialMap::GetEntityType(void)
// FUNCTION: ENGINE 0x108D0290 @ engine::AudioMaterialMap::~AudioMaterialMap(void)
// FUNCTION: ENGINE 0x108D03C0 @ om::AtgContentEntity<engine::AudioMaterialMap>::AtgContentEntity<engine::AudioMaterialMap>(om::Entity *)
// FUNCTION: ENGINE 0x108D03E0 @ void om::AtgContentEntityLoader<engine::AudioMaterialMap>::operator delete(void *) (name guess; identical copies)
// FUNCTION: ENGINE 0x108D0400 @ om::AtgContentEntity<engine::AudioMaterialMap>::~AtgContentEntity<engine::AudioMaterialMap>(void)
// FUNCTION: ENGINE 0x108D0440 @ void * om::AtgContentEntity<engine::AudioMaterialMap>::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108D04A0 @ void om::WriteResult<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >(om::Bin
// FUNCTION: ENGINE 0x108D04B0 @ void om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > >::Add(om::Name<om::CaseSen
// FUNCTION: ENGINE 0x108D0510 @ bool om::MetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const &>
// FUNCTION: ENGINE 0x108D0640 @ om::Garbage<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >::~Garbage<om::Di
// FUNCTION: ENGINE 0x108D0680 @ void * om::Garbage<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >::`scalar 
// FUNCTION: ENGINE 0x108D0870 @ void * engine::AudioMaterialMap::`scalar deleting destructor'(unsigned int)
// FUNCTION: ENGINE 0x108D0BF0 @ bool om::AttributeReadText<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > >(o
// FUNCTION: ENGINE 0x108D0C00 @ void engine::AudioMaterialMap::SetMap(om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitK
// FUNCTION: ENGINE 0x108D0F80 @ bool om::MetaProperty<om::Dictionary<om::Name<om::CaseSensitive64BitKey>,om::Name<om::CaseSensitive64BitKey>,om::Comparer<om::Name<om::CaseSensitive64BitKey> > > const &>
