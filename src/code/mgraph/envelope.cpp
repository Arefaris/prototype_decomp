// The reflection of the envelope node of the mgraph library (0x10AB0550 - 0x10AB6400, a guess of the unit's name): the
// template instances of the om library for the envelope, its data and the points of its curve, and the dynamic property
// of the envelope data.
#include "code/mgraph/envelope.h"
#include "code/om/delegate.h"
#include "code/om/dynamicproperty.h"
#include "code/om/invoke.h"
#include "code/om/metaclass.h"
#include "code/om/metaenum.h"
#include "code/om/metamethod.h"
#include "code/om/metaproperty.h"

#pragma warning(disable: 4661)

namespace om
{
	// The engine calls the copy constructor of the points' array and expands the rest of the by-value argument, ours
	// expands the array copy
	template<> void CommandMember1<DynamicProperty<mgraph::EnvelopeData>, DynamicProperty<mgraph::EnvelopeData>, void, mgraph::EnvelopeData>::Call(mgraph::EnvelopeData value);
	template<> void CommandDelegate<mgraph::EnvelopeData>::Set(mgraph::EnvelopeData value);

	// FUNCTION: ENGINE 0x10AB42A0
	// NONMATCHING: the points' array of the argument is copied in place, the engine calls its copy constructor (18.0 %)
#ifdef NONMATCHING
	template<> void CommandMember1<DynamicProperty<mgraph::EnvelopeData>, DynamicProperty<mgraph::EnvelopeData>, void, mgraph::EnvelopeData>::Call(mgraph::EnvelopeData value)
	{
		(object->*function)(value);
	}
#endif

	// FUNCTION: ENGINE 0x10AB4180
	// NONMATCHING: the points' array of the argument is copied in place, the engine calls its copy constructor (18.8 %)
#ifdef NONMATCHING
	template<> void CommandDelegate<mgraph::EnvelopeData>::Set(mgraph::EnvelopeData value)
	{
		Command1<void, mgraph::EnvelopeData>& command = *setter.pointer;
		command.Call(value);
	}
#endif

	// The first child of a text value that has the name
	static inline TextValue* FindNode(const TextValue* text, const String& name)
	{
		return text->children.FindFirst(CompareNodeName, &name);
	}

	// FUNCTION: ENGINE 0x10AB1750
	bool ReadText(const TextValue* text, VectorT<float, 2>* vector)
	{
		bool ok;
		float* value = vector->values;
		for (unsigned int i = 0; i < 2; i++)
		{
			TextValue* node = FindNode(text, Format(0, "%d", i));
			if (node != 0)
			{
				ok = ReadText(node, value);
			}
			else
			{
				ok = false;
			}
			value++;
		}
		return ok;
	}

	// FUNCTION: ENGINE 0x10AB17C0
	void WriteText(TextValue* text, const VectorT<float, 2>& vector)
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			WriteText(new TextNode(text, Format(0, "%d", i)), vector.values[i]);
		}
	}

	// FUNCTION: ENGINE 0x10AB0C70
	bool ReadBinary(BinaryStream* stream, VectorT<float, 2>* vector)
	{
		bool ok = true;
		for (unsigned int i = 0; i < 2; i++)
		{
			ok = ok && ReadBinary(stream, &vector->values[i]);
		}
		return ok;
	}

	// FUNCTION: ENGINE 0x10AB0CB0
	bool WriteBinary(BinaryStream* stream, const VectorT<float, 2>& vector)
	{
		bool ok = true;
		for (unsigned int i = 0; i < 2; i++)
		{
			ok = ok && WriteBinary(stream, vector.values[i]);
		}
		return ok;
	}

	// FUNCTION: ENGINE 0x10AB0650
	template MetaClass<mgraph::EnvelopeData>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AB0680
	template type_info const* MetaClass<mgraph::EnvelopeData>::GetType();
	// FUNCTION: ENGINE 0x10AB0690
	template void CommandDelegate<mgraph::EnvelopeData>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB0720
	template void MetaClass<mgraph::EnvelopeData>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB07E0
	template MetaClass<mgraph::Envelope>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AB0810
	template type_info const* MetaClass<mgraph::Envelope>::GetType();
	// FUNCTION: ENGINE 0x10AB0850
	template void MetaClass<mgraph::Envelope>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB0960
	template char const* MetaClass<mgraph::EnvelopeData>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB09B0
	template char const* MetaClass<mgraph::Envelope>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB09C0
	template MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::MetaProperty(MetaTypeBase*, MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,DynamicArray<VectorT<float,2>,unsigned short> const&>*, MetaMethod0Base<DynamicArray<VectorT<float,2>,unsigned short> const&>*, unsigned int);
	// FUNCTION: ENGINE 0x10AB0A00
	template type_info const* MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::GetValueType();
	// FUNCTION: ENGINE 0x10AB0A30
	template MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::~MetaProperty();
	// FUNCTION: ENGINE 0x10AB0A40
	template MetaMethod1Base<void,DynamicArray<VectorT<float,2>,unsigned short> const&>::MetaMethod1Base(MetaClassBase*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AB0B50
	template char const* MetaMethod1<mgraph::Envelope,mgraph::Envelope,void,float>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB0B60
	template char const* MetaMethod1<mgraph::EnvelopeData,mgraph::EnvelopeData,void,DynamicArray<VectorT<float,2>,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB0B70
	template char const* MetaMethod0Const<mgraph::EnvelopeData,mgraph::EnvelopeData,DynamicArray<VectorT<float,2>,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB0B80
	template char const* MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB0BA0
	template char const* MetaMethod0Const<mgraph::Envelope,mgraph::Envelope,float>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB0C60
	template char const* DelegateMetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB0D90
	template int MetaClass<mgraph::EnvelopeData>::Slot5();
	// FUNCTION: ENGINE 0x10AB0DA0
	template void MetaClass<mgraph::EnvelopeData>::Slot6(void*);
	// FUNCTION: ENGINE 0x10AB0E10
	template int MetaClass<mgraph::Envelope>::Slot5();
	// FUNCTION: ENGINE 0x10AB0E20
	template void MetaClass<mgraph::Envelope>::Slot6(void*);
	// FUNCTION: ENGINE 0x10AB0F30
	template void* MetaClass<mgraph::EnvelopeData>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB1000
	template void* MetaClass<mgraph::Envelope>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB10A0
	template void* MetaMethod1<mgraph::Envelope,mgraph::Envelope,void,float>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB10C0
	template MetaMethod1<mgraph::Envelope,mgraph::Envelope,void,float>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Envelope,mgraph::Envelope,void,float>::Function);
	// FUNCTION: ENGINE 0x10AB10F0
	template void MetaMethod1<mgraph::Envelope,mgraph::Envelope,void,float>::Call(void*, float);
	// FUNCTION: ENGINE 0x10AB1110
	template MetaMethod1<mgraph::Envelope,mgraph::Envelope,void,float>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AB1120
	template void MetaMethod1<mgraph::Envelope,mgraph::Envelope,void,float>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB1140
	template void* MetaMethod1<mgraph::EnvelopeData,mgraph::EnvelopeData,void,DynamicArray<VectorT<float,2>,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB1160
	template MetaMethod1<mgraph::EnvelopeData,mgraph::EnvelopeData,void,DynamicArray<VectorT<float,2>,unsigned short> const&>::MetaMethod1(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::EnvelopeData,mgraph::EnvelopeData,void,DynamicArray<VectorT<float,2>,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AB1190
	template void MetaMethod1<mgraph::EnvelopeData,mgraph::EnvelopeData,void,DynamicArray<VectorT<float,2>,unsigned short> const&>::Call(void*, DynamicArray<VectorT<float,2>,unsigned short> const&);
	// FUNCTION: ENGINE 0x10AB11B0
	template MetaMethod1<mgraph::EnvelopeData,mgraph::EnvelopeData,void,DynamicArray<VectorT<float,2>,unsigned short> const&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x10AB11C0
	template void MetaMethod1<mgraph::EnvelopeData,mgraph::EnvelopeData,void,DynamicArray<VectorT<float,2>,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB11E0
	template char const* Garbage<DynamicArray<VectorT<float,2>,unsigned short> >::AllocationTag();
	// FUNCTION: ENGINE 0x10AB11F0
	template void* MetaMethod0Const<mgraph::EnvelopeData,mgraph::EnvelopeData,DynamicArray<VectorT<float,2>,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB1210
	template MetaMethod0Const<mgraph::EnvelopeData,mgraph::EnvelopeData,DynamicArray<VectorT<float,2>,unsigned short> const&>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::EnvelopeData,mgraph::EnvelopeData,DynamicArray<VectorT<float,2>,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AB1240
	template DynamicArray<VectorT<float,2>,unsigned short> const& MetaMethod0Const<mgraph::EnvelopeData,mgraph::EnvelopeData,DynamicArray<VectorT<float,2>,unsigned short> const&>::Call(void*);
	// FUNCTION: ENGINE 0x10AB1250
	template MetaMethod0Const<mgraph::EnvelopeData,mgraph::EnvelopeData,DynamicArray<VectorT<float,2>,unsigned short> const&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AB1260
	template void MetaMethod0Const<mgraph::EnvelopeData,mgraph::EnvelopeData,DynamicArray<VectorT<float,2>,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB1280
	template void* MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB12C0
	template void* MetaMethod0Const<mgraph::Envelope,mgraph::Envelope,float>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB12E0
	template MetaMethod0Const<mgraph::Envelope,mgraph::Envelope,float>::MetaMethod0Const(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Envelope,mgraph::Envelope,float>::Function);
	// FUNCTION: ENGINE 0x10AB1310
	template float MetaMethod0Const<mgraph::Envelope,mgraph::Envelope,float>::Call(void*);
	// FUNCTION: ENGINE 0x10AB1320
	template MetaMethod0Const<mgraph::Envelope,mgraph::Envelope,float>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x10AB1330
	template void MetaMethod0Const<mgraph::Envelope,mgraph::Envelope,float>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB1350
	template void MetaMethod0Const<mgraph::Envelope,mgraph::Envelope,float>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10AB14E0
	template MetaMethod1Base<void,DynamicArray<VectorT<float,2>,unsigned short> const&>* MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::GetSetter();
	// FUNCTION: ENGINE 0x10AB14F0
	template MetaMethod0Base<DynamicArray<VectorT<float,2>,unsigned short> const&>* MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::GetGetter();
	// FUNCTION: ENGINE 0x10AB15D0
	template void* DelegateMetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB1610
	template void* Garbage<DynamicArray<VectorT<float,2>,unsigned short> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB1630
	template Garbage<DynamicArray<VectorT<float,2>,unsigned short> >::Garbage(DynamicArray<VectorT<float,2>,unsigned short>*);
	// FUNCTION: ENGINE 0x10AB1670
	template void Garbage<DynamicArray<VectorT<float,2>,unsigned short> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB1690
	template DelegateProperty<DynamicArray<VectorT<float,2>,unsigned short> >::DelegateProperty();
	// FUNCTION: ENGINE 0x10AB16A0
	template MetaTypeBase* DelegateProperty<DynamicArray<VectorT<float,2>,unsigned short> >::GetMetaType();
	// FUNCTION: ENGINE 0x10AB16B0
	template DelegateProperty<DynamicArray<VectorT<float,2>,unsigned short> >::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AB1AB0
	template void MetaClass<mgraph::EnvelopeData>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AB1D10
	template void MetaClass<mgraph::Envelope>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10AB1D80
	template MetaMethod1<mgraph::EnvelopeData,mgraph::EnvelopeData,void,DynamicArray<VectorT<float,2>,unsigned short> const&>* MetaMethod1<mgraph::EnvelopeData,mgraph::EnvelopeData,void,DynamicArray<VectorT<float,2>,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::EnvelopeData,mgraph::EnvelopeData,void,DynamicArray<VectorT<float,2>,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AB1DC0
	template MetaMethod0Const<mgraph::EnvelopeData,mgraph::EnvelopeData,DynamicArray<VectorT<float,2>,unsigned short> const&>* MetaMethod0Const<mgraph::EnvelopeData,mgraph::EnvelopeData,DynamicArray<VectorT<float,2>,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::EnvelopeData,mgraph::EnvelopeData,DynamicArray<VectorT<float,2>,unsigned short> const&>::Function);
	// FUNCTION: ENGINE 0x10AB1E00
	template void MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1Base<void,DynamicArray<VectorT<float,2>,unsigned short> const&>*, MetaMethod0Base<DynamicArray<VectorT<float,2>,unsigned short> const&>*, unsigned int);
	// FUNCTION: ENGINE 0x10AB1EB0
	template MetaMethod1<mgraph::Envelope,mgraph::Envelope,void,float>* MetaMethod1<mgraph::Envelope,mgraph::Envelope,void,float>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod1<mgraph::Envelope,mgraph::Envelope,void,float>::Function);
	// FUNCTION: ENGINE 0x10AB1EF0
	template MetaMethod0Const<mgraph::Envelope,mgraph::Envelope,float>* MetaMethod0Const<mgraph::Envelope,mgraph::Envelope,float>::Create(MetaClassBase*, Name<CaseSensitive64BitKey> const&, MetaMethod0Const<mgraph::Envelope,mgraph::Envelope,float>::Function);
	// FUNCTION: ENGINE 0x10AB2040
	template DelegateMetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::DelegateMetaProperty(void*, MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>*);
	// FUNCTION: ENGINE 0x10AB2070
	template void DelegateMetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::SetObject(void*);
	// FUNCTION: ENGINE 0x10AB2080
	template void DelegateMetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB20A0
	template DelegateMetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x10AB20B0
	template void DelegateMetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::Set(DynamicArray<VectorT<float,2>,unsigned short>);
	// FUNCTION: ENGINE 0x10AB2210
	template Garbage<DynamicArray<VectorT<float,2>,unsigned short> >::~Garbage();
	// FUNCTION: ENGINE 0x10AB23F0
	template void DelegateMetaProperty<mgraph::EnvelopeData const&>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB25A0
	template char const* DelegateMetaProperty<mgraph::EnvelopeData const&>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB28A0
	template DynamicArray<VectorT<float,2>,unsigned short> DelegateMetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::Get();
	// FUNCTION: ENGINE 0x10AB28D0
	template DelegatePropertyBase* MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x10AB2C30
	template void MetaMethod1<mgraph::Envelope,mgraph::Envelope,void,float>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10AB2F40
	template MetaMethod0Base<mgraph::EnvelopeData const&>* MetaProperty<mgraph::EnvelopeData const&>::GetGetter();
	// FUNCTION: ENGINE 0x10AB37C0
	template bool MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10AB3830
	template bool MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x10AB38A0
	template void DynamicProperty<mgraph::EnvelopeData>::SetName(Name<CaseSensitive64BitKey>);
	// FUNCTION: ENGINE 0x10AB38C0
	template Name<CaseSensitive64BitKey> DynamicProperty<mgraph::EnvelopeData>::GetName() const;
	// FUNCTION: ENGINE 0x10AB38E0
	template void const* DynamicProperty<mgraph::EnvelopeData>::GetValuePointer() const;
	// FUNCTION: ENGINE 0x10AB38F0
	template void* DynamicProperty<mgraph::EnvelopeData>::GetValuePointer();
	// FUNCTION: ENGINE 0x10AB3900
	template MetaTypeBase* DynamicProperty<mgraph::EnvelopeData>::GetMetaType() const;
	// FUNCTION: ENGINE 0x10AB3910
	template void DynamicProperty<mgraph::EnvelopeData>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB3930
	template Command0<mgraph::EnvelopeData>::~Command0();
	// FUNCTION: ENGINE 0x10AB3940
	template Command1<void,mgraph::EnvelopeData>::~Command1();
	// FUNCTION: ENGINE 0x10AB39D0
	template Command0<mgraph::EnvelopeData>::Command0();
	// FUNCTION: ENGINE 0x10AB39F0
	template char const* CommandDelegate<mgraph::EnvelopeData>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB3A00
	template char const* CommandMember0Const<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,mgraph::EnvelopeData>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB3A10
	template Command1<void,mgraph::EnvelopeData>::Command1();
	// FUNCTION: ENGINE 0x10AB3A20
	template char const* CommandMember1<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,void,mgraph::EnvelopeData>::AllocationTag();
	// FUNCTION: ENGINE 0x10AB3A30
	template void* CommandDelegate<mgraph::EnvelopeData>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB3B10
	template DelegateProperty<mgraph::EnvelopeData>::DelegateProperty();
	// FUNCTION: ENGINE 0x10AB3B20
	template MetaTypeBase* DelegateProperty<mgraph::EnvelopeData>::GetMetaType();
	// FUNCTION: ENGINE 0x10AB3B30
	template DelegateProperty<mgraph::EnvelopeData>::~DelegateProperty();
	// FUNCTION: ENGINE 0x10AB3B60
	template void* CommandMember0Const<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,mgraph::EnvelopeData>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB3B80
	template CommandMember0Const<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,mgraph::EnvelopeData>::CommandMember0Const(DynamicProperty<mgraph::EnvelopeData>*, CommandMember0Const<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,mgraph::EnvelopeData>::Function);
	// FUNCTION: ENGINE 0x10AB3BA0
	template CommandMember0Const<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,mgraph::EnvelopeData>::~CommandMember0Const();
	// FUNCTION: ENGINE 0x10AB3BB0
	template void CommandMember0Const<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,mgraph::EnvelopeData>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB3C00
	template Command0<mgraph::EnvelopeData>* CommandMember0Const<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,mgraph::EnvelopeData>::Create(DynamicProperty<mgraph::EnvelopeData>*, CommandMember0Const<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,mgraph::EnvelopeData>::Function);
	// FUNCTION: ENGINE 0x10AB3C30
	template void* CommandMember1<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,void,mgraph::EnvelopeData>::operator new(size_t);
	// FUNCTION: ENGINE 0x10AB3C50
	template CommandMember1<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,void,mgraph::EnvelopeData>::CommandMember1(DynamicProperty<mgraph::EnvelopeData>*, CommandMember1<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,void,mgraph::EnvelopeData>::Function);
	// FUNCTION: ENGINE 0x10AB3C70
	template CommandMember1<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,void,mgraph::EnvelopeData>::~CommandMember1();
	// FUNCTION: ENGINE 0x10AB3C80
	template void CommandMember1<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,void,mgraph::EnvelopeData>::operator delete(void*);
	// FUNCTION: ENGINE 0x10AB3CD0
	template DynamicProperty<mgraph::EnvelopeData>::~DynamicProperty();
	// FUNCTION: ENGINE 0x10AB3D10
	// EQUIVALENT: scheduling: the engine loads both halves of the key before the test of the result of the name read (95.5 %)
	template bool DynamicProperty<mgraph::EnvelopeData>::ReadText(TextValue const*);
	// FUNCTION: ENGINE 0x10AB3DE0
	template void DynamicProperty<mgraph::EnvelopeData>::WriteText(TextValue*);
	// FUNCTION: ENGINE 0x10AB3F70
	template bool DynamicProperty<mgraph::EnvelopeData>::ReadBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AB3FD0
	template bool DynamicProperty<mgraph::EnvelopeData>::WriteBinary(BinaryStream*);
	// FUNCTION: ENGINE 0x10AB40B0
	template CommandDelegate<mgraph::EnvelopeData>::CommandDelegate(Command0<mgraph::EnvelopeData>*, Command1<void,mgraph::EnvelopeData>*);
	// FUNCTION: ENGINE 0x10AB4110
	template MetaTypeBase* CommandDelegate<mgraph::EnvelopeData>::GetMetaType();
	// FUNCTION: ENGINE 0x10AB4130
	template CommandDelegate<mgraph::EnvelopeData>::~CommandDelegate();
	// FUNCTION: ENGINE 0x10AB4160
	template mgraph::EnvelopeData CommandDelegate<mgraph::EnvelopeData>::Get();
	// FUNCTION: ENGINE 0x10AB41F0
	template mgraph::EnvelopeData CommandMember0Const<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,mgraph::EnvelopeData>::Call();
	// FUNCTION: ENGINE 0x10AB4260
	template Command0<mgraph::EnvelopeData>* CommandMember0Const<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,mgraph::EnvelopeData>::Clone();
	// FUNCTION: ENGINE 0x10AB4350
	template mgraph::EnvelopeData DynamicProperty<mgraph::EnvelopeData>::GetValue() const;
	// FUNCTION: ENGINE 0x10AB4380
	template Command1<void,mgraph::EnvelopeData>* CommandMember1<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,void,mgraph::EnvelopeData>::Create(DynamicProperty<mgraph::EnvelopeData>*, CommandMember1<DynamicProperty<mgraph::EnvelopeData>,DynamicProperty<mgraph::EnvelopeData>,void,mgraph::EnvelopeData>::Function);
	// FUNCTION: ENGINE 0x10AB43B0
	template void DynamicProperty<mgraph::EnvelopeData>::WriteToDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AB43E0
	template void DynamicProperty<mgraph::EnvelopeData>::SetFromPointer2(void const*, unsigned int);
	// FUNCTION: ENGINE 0x10AB4410
	template void DynamicProperty<mgraph::EnvelopeData>::GetValue(void*) const;
	// FUNCTION: ENGINE 0x10AB4440
	template void DynamicProperty<mgraph::EnvelopeData>::Set(mgraph::EnvelopeData);
	// FUNCTION: ENGINE 0x10AB44A0
	template void DynamicProperty<mgraph::EnvelopeData>::SetFrom(DynamicPropertyBase*);
	// FUNCTION: ENGINE 0x10AB44C0
	template void DynamicProperty<mgraph::EnvelopeData>::ReadFromDelegate(DelegatePropertyBase*);
	// FUNCTION: ENGINE 0x10AB44E0
	template void DynamicProperty<mgraph::EnvelopeData>::SetFromPointer(void const*);
	// FUNCTION: ENGINE 0x10AB4510
	template DelegatePropertyBase* DynamicProperty<mgraph::EnvelopeData>::CreateDelegate();
	// FUNCTION: ENGINE 0x10AB5300
	template void MetaMethod1<mgraph::EnvelopeData,mgraph::EnvelopeData,void,DynamicArray<VectorT<float,2>,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10AB53D0
	template void MetaMethod0Const<mgraph::EnvelopeData,mgraph::EnvelopeData,DynamicArray<VectorT<float,2>,unsigned short> const&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x10AB5470
	template bool MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::SetText(TextValue const*, void*);
	// FUNCTION: ENGINE 0x10AB5560
	template void MetaProperty<DynamicArray<VectorT<float,2>,unsigned short> const&>::GetText(TextValue*, void*);
}
