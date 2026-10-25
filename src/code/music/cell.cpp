// The music library's cells (0x105DF9C0 - 0x105E2A00): the cell classes and the reflection of music::Cell and
// music::MGraphCell made of template instances of the om library.
#include "code/music/cell.h"
#include "code/om/delegate.h"
#include "code/om/invoke.h"
#include "code/om/metaclass.h"
#include "code/om/metamethod.h"
#include "code/om/metaproperty.h"

#pragma warning(disable: 4661)

namespace music
{
	// FUNCTION: ENGINE 0x105DFCA0
	Cell::Cell() :
		followAction(FollowAction::TypeStop),
		owned(0)
	{
	}

	// FUNCTION: ENGINE 0x105DF9C0
	const Fade& Cell::GetFadeIn() const
	{
		return fadeIn;
	}

	// FUNCTION: ENGINE 0x105DF9D0
	void Cell::SetFadeIn(const Fade& newFadeIn)
	{
		fadeIn = newFadeIn;
	}

	// FUNCTION: ENGINE 0x105DF9F0
	const Fade& Cell::GetFadeOut() const
	{
		return fadeOut;
	}

	// FUNCTION: ENGINE 0x105DFA00
	void Cell::SetFadeOut(const Fade& newFadeOut)
	{
		fadeOut = newFadeOut;
	}

	// FUNCTION: ENGINE 0x105D2840
	const FollowAction& Cell::GetFollowAction() const
	{
		return followAction;
	}

	// FUNCTION: ENGINE 0x105DFA20
	void Cell::SetFollowAction(const FollowAction& newFollowAction)
	{
		followAction = newFollowAction;
	}

	// FUNCTION: ENGINE 0x105DFA50
	bool Cell::ReadText(const om::TextValue* text)
	{
		return GetMetaType()->ReadText(text, this);
	}

	// FUNCTION: ENGINE 0x105DFA70
	void Cell::WriteText(om::TextValue* text)
	{
		GetMetaType()->WriteText(text, this);
	}

	// FUNCTION: ENGINE 0x105DFA90
	bool Cell::ReadBinary(om::BinaryStream* stream)
	{
		return GetMetaType()->ReadBinary(stream, this);
	}

	// FUNCTION: ENGINE 0x105DFAD0
	bool Cell::Slot5(int)
	{
		return true;
	}

	// FUNCTION: ENGINE 0x105DFAC0
	void Cell::Slot6(const void*)
	{
	}

	// FUNCTION: ENGINE 0x105DFA30
	const om::ClassName& MGraphCell::GetPatchName() const
	{
		return patchName;
	}

	// FUNCTION: ENGINE 0x105E0220
	void MGraphCell::SetPatchName(const om::ClassName& newPatchName)
	{
		patchName = newPatchName;
	}

	// FUNCTION: ENGINE 0x105E02E0
	void MGraphCell::Slot6(const void* source)
	{
		patchName = static_cast<const CellSource*>(source)->patchName;
	}

	// FUNCTION: ENGINE 0x105DFAB0
	om::MetaTypeBase* MGraphCell::GetPlayerMetaType()
	{
		om::MetaTypeBase*& cache = om::MetaTypeCache<MGraphCellPlayer>::type;
		if (cache == 0)
		{
			cache = om::FindMetaType(typeid(MGraphCellPlayer));
		}
		return cache;
	}

	// FUNCTION: ENGINE 0x105E0490
	const char* MGraphCellPlayer::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105DFE10
	const char* MGraphCell::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105E04F0
	const char* Fade::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x105E0620
	const char* FollowAction::AllocationTag()
	{
		return "";
	}
}

namespace om
{
	// FUNCTION: ENGINE 0x105E0340
	template<> int MetaClass<music::MGraphCell>::Slot5()
	{
		return reinterpret_cast<int>(new music::MGraphCell);
	}

	// FUNCTION: ENGINE 0x105DFD70
	template<> void MetaClass<music::MGraphCell>::Slot6(void* object)
	{
		delete static_cast<music::MGraphCell*>(object);
	}
}

namespace om
{
	// FUNCTION: ENGINE 0x105DFBE0
	template MetaClass<music::Cell>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105DFC10
	template const type_info* MetaClass<music::Cell>::GetType();
	// FUNCTION: ENGINE 0x105DFC20
	template MetaClass<music::MGraphCell>::MetaClass(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105DFD60
	template const type_info* MetaClass<music::MGraphCell>::GetType();
	// FUNCTION: ENGINE 0x105DFDB0
	template MetaClass<music::MGraphCell>::~MetaClass();
	// FUNCTION: ENGINE 0x105DFDC0
	template MetaClass<music::Cell>::~MetaClass();
	// FUNCTION: ENGINE 0x105DFDD0
	template void MetaClass<music::MGraphCell>::operator delete(void*);
	// FUNCTION: ENGINE 0x105DFDF0
	template void MetaClass<music::Cell>::operator delete(void*);
	// FUNCTION: ENGINE 0x105DFE40
	template const char* MetaClass<music::Cell>::AllocationTag();
	// FUNCTION: ENGINE 0x105DFE50
	template const char* MetaClass<music::MGraphCell>::AllocationTag();
	// FUNCTION: ENGINE 0x105DFE60
	template MetaProperty<const music::Fade&>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, const music::Fade&>*, MetaMethod0Base<const music::Fade&>*, unsigned int);
	// FUNCTION: ENGINE 0x105DFEA0
	template const type_info* MetaProperty<const music::Fade&>::GetValueType();
	// FUNCTION: ENGINE 0x105DFEB0
	template MetaProperty<const music::FollowAction&>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, const music::FollowAction&>*, MetaMethod0Base<const music::FollowAction&>*, unsigned int);
	// FUNCTION: ENGINE 0x105DFEF0
	template const type_info* MetaProperty<const music::FollowAction&>::GetValueType();
	// FUNCTION: ENGINE 0x105DFF00
	template MetaMethod1Base<void, const music::Fade&>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105DFF10
	template MetaMethod0Base<const music::Fade&>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105DFF20
	template MetaMethod1Base<void, const music::FollowAction&>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105DFF30
	template MetaMethod0Base<const music::FollowAction&>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105DFF40
	template MetaProperty<const music::Fade&>::~MetaProperty();
	// FUNCTION: ENGINE 0x105DFF50
	template MetaProperty<const music::FollowAction&>::~MetaProperty();
	// FUNCTION: ENGINE 0x105DFF60
	template MetaMethod1Base<void, const music::Fade&>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105DFFC0
	template MetaMethod1Base<void, const music::FollowAction&>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105E00B0
	template const char* MetaMethod1<music::Cell, music::Cell, void, const music::Fade&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E00C0
	template const char* MetaMethod0Const<music::Cell, music::Cell, const music::Fade&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E00D0
	template const char* MetaProperty<const music::Fade&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E00E0
	template const char* MetaMethod1<music::Cell, music::Cell, void, const music::FollowAction&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E00F0
	template const char* MetaMethod0Const<music::Cell, music::Cell, const music::FollowAction&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E0100
	template const char* MetaProperty<const music::FollowAction&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E0110
	template const char* MetaMethod1<music::MGraphCell, music::MGraphCell, void, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E0120
	template const char* MetaMethod0Const<music::MGraphCell, music::MGraphCell, const ClassName&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E0170
	template const char* DelegateMetaProperty<const music::Fade&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E0180
	template const char* DelegateMetaProperty<const music::FollowAction&>::AllocationTag();
	// FUNCTION: ENGINE 0x105E0300
	template int MetaClass<music::Cell>::Slot5();
	// FUNCTION: ENGINE 0x105E0310
	template void MetaClass<music::Cell>::Slot6(void*);
	// FUNCTION: ENGINE 0x105E03A0
	template void* MetaClass<music::Cell>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E03C0
	template void* MetaClass<music::MGraphCell>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E1D40
	template void MetaMethod0Const<music::MGraphCell, music::MGraphCell, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105E1ED0
	template music::FollowAction* ReadArgument<music::FollowAction>(BinaryStream*, GarbageList*);
	// FUNCTION: ENGINE 0x105E2770
	template void MetaMethod1<music::Cell, music::Cell, void, const music::FollowAction&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105E2840
	template void MetaMethod0Const<music::Cell, music::Cell, const music::FollowAction&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105E28F0
	template void MetaMethod1<music::MGraphCell, music::MGraphCell, void, const ClassName&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105E1E00
	template music::Fade* ReadArgument<music::Fade>(BinaryStream*, GarbageList*);
	// FUNCTION: ENGINE 0x105E25F0
	template void MetaMethod1<music::Cell, music::Cell, void, const music::Fade&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);
	// FUNCTION: ENGINE 0x105E26C0
	template void MetaMethod0Const<music::Cell, music::Cell, const music::Fade&>::Invoke(void*, unsigned int, unsigned int, unsigned int, unsigned int);

	// FUNCTION: ENGINE 0x105E0440
	template void* MetaMethod1<music::Cell, music::Cell, void, const music::Fade&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E0460
	template MetaMethod1<music::Cell, music::Cell, void, const music::Fade&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::Cell::*)(const music::Fade&));
	// FUNCTION: ENGINE 0x105E04A0
	template void MetaMethod1<music::Cell, music::Cell, void, const music::Fade&>::Call(void*, const music::Fade&);
	// FUNCTION: ENGINE 0x105E04C0
	template MetaMethod1<music::Cell, music::Cell, void, const music::Fade&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105E04D0
	template void MetaMethod1<music::Cell, music::Cell, void, const music::Fade&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E0520
	template void* MetaMethod0Const<music::Cell, music::Cell, const music::Fade&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E0540
	template MetaMethod0Const<music::Cell, music::Cell, const music::Fade&>::MetaMethod0Const(MetaClassBase*, const ClassName&, music::Fade const & (__thiscall music::Cell::*)(void)const);
	// FUNCTION: ENGINE 0x105E0570
	template const music::Fade& MetaMethod0Const<music::Cell, music::Cell, const music::Fade&>::Call(void*);
	// FUNCTION: ENGINE 0x105E0580
	template MetaMethod0Const<music::Cell, music::Cell, const music::Fade&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105E0590
	template void MetaMethod0Const<music::Cell, music::Cell, const music::Fade&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E05B0
	template void* MetaProperty<const music::Fade&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E05D0
	template void* MetaMethod1<music::Cell, music::Cell, void, const music::FollowAction&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E05F0
	template MetaMethod1<music::Cell, music::Cell, void, const music::FollowAction&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::Cell::*)(const music::FollowAction&));
	// FUNCTION: ENGINE 0x105E0630
	template void MetaMethod1<music::Cell, music::Cell, void, const music::FollowAction&>::Call(void*, const music::FollowAction&);
	// FUNCTION: ENGINE 0x105E0650
	template MetaMethod1<music::Cell, music::Cell, void, const music::FollowAction&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105E0660
	template void MetaMethod1<music::Cell, music::Cell, void, const music::FollowAction&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E04F0
	template const char* Garbage<music::Fade>::AllocationTag();
	// FUNCTION: ENGINE 0x105E0680
	template const char* Garbage<music::FollowAction>::AllocationTag();
	// FUNCTION: ENGINE 0x105E06B0
	template void* MetaMethod0Const<music::Cell, music::Cell, const music::FollowAction&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E06D0
	template MetaMethod0Const<music::Cell, music::Cell, const music::FollowAction&>::MetaMethod0Const(MetaClassBase*, const ClassName&, music::FollowAction const & (__thiscall music::Cell::*)(void)const);
	// FUNCTION: ENGINE 0x105E0700
	template const music::FollowAction& MetaMethod0Const<music::Cell, music::Cell, const music::FollowAction&>::Call(void*);
	// FUNCTION: ENGINE 0x105E0710
	template MetaMethod0Const<music::Cell, music::Cell, const music::FollowAction&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105E0720
	template void MetaMethod0Const<music::Cell, music::Cell, const music::FollowAction&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E0740
	template void* MetaProperty<const music::FollowAction&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E0760
	template void* MetaMethod1<music::MGraphCell, music::MGraphCell, void, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E0780
	template MetaMethod1<music::MGraphCell, music::MGraphCell, void, const ClassName&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::MGraphCell::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105E07B0
	template void MetaMethod1<music::MGraphCell, music::MGraphCell, void, const ClassName&>::Call(void*, const ClassName&);
	// FUNCTION: ENGINE 0x105E07D0
	template MetaMethod1<music::MGraphCell, music::MGraphCell, void, const ClassName&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105E07E0
	template void MetaMethod1<music::MGraphCell, music::MGraphCell, void, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E0800
	template void* MetaMethod0Const<music::MGraphCell, music::MGraphCell, const ClassName&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E0820
	template MetaMethod0Const<music::MGraphCell, music::MGraphCell, const ClassName&>::MetaMethod0Const(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::MGraphCell::*)(void)const);
	// FUNCTION: ENGINE 0x105E0850
	template const ClassName& MetaMethod0Const<music::MGraphCell, music::MGraphCell, const ClassName&>::Call(void*);
	// FUNCTION: ENGINE 0x105E0860
	template MetaMethod0Const<music::MGraphCell, music::MGraphCell, const ClassName&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105E0870
	template void MetaMethod0Const<music::MGraphCell, music::MGraphCell, const ClassName&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E0A10
	template MetaMethod1Base<void, const music::Fade&>* MetaProperty<const music::Fade&>::GetSetter();
	// FUNCTION: ENGINE 0x105E0A20
	template MetaMethod0Base<const music::Fade&>* MetaProperty<const music::Fade&>::GetGetter();
	// FUNCTION: ENGINE 0x105E0A30
	template MetaMethod1Base<void, const music::FollowAction&>* MetaProperty<const music::FollowAction&>::GetSetter();
	// FUNCTION: ENGINE 0x105E0A40
	template MetaMethod0Base<const music::FollowAction&>* MetaProperty<const music::FollowAction&>::GetGetter();
	// FUNCTION: ENGINE 0x105E0A70
	template void* DelegateMetaProperty<const music::Fade&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E0A90
	template void* DelegateMetaProperty<const music::FollowAction&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E0B60
	template void* Garbage<music::FollowAction>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E0AD0
	template Garbage<music::Fade>::Garbage(music::Fade*);
	// FUNCTION: ENGINE 0x105E0B10
	template Garbage<music::Fade>::~Garbage();
	// FUNCTION: ENGINE 0x105E0B40
	template void Garbage<music::Fade>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E0AB0
	template void* Garbage<music::Fade>::operator new(size_t);
	// FUNCTION: ENGINE 0x105E0B80
	template Garbage<music::FollowAction>::Garbage(music::FollowAction*);
	// FUNCTION: ENGINE 0x105E0BC0
	template Garbage<music::FollowAction>::~Garbage();
	// FUNCTION: ENGINE 0x105E0BF0
	template void Garbage<music::FollowAction>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E0C10
	template DelegateProperty<music::Fade>::DelegateProperty();
	// FUNCTION: ENGINE 0x105E0C20
	template MetaTypeBase* DelegateProperty<music::Fade>::GetMetaType();
	// FUNCTION: ENGINE 0x105E0C30
	template DelegateProperty<music::Fade>::~DelegateProperty();
	// FUNCTION: ENGINE 0x105E0C40
	template DelegateProperty<music::FollowAction>::DelegateProperty();
	// FUNCTION: ENGINE 0x105E0C50
	template MetaTypeBase* DelegateProperty<music::FollowAction>::GetMetaType();
	// FUNCTION: ENGINE 0x105E0C60
	template DelegateProperty<music::FollowAction>::~DelegateProperty();
	// FUNCTION: ENGINE 0x105E0D30
	template bool ReadText<music::Fade>(const TextValue*, music::Fade*);
	// FUNCTION: ENGINE 0x105E0D60
	template void WriteText<music::Fade>(TextValue*, const music::Fade&);
	// FUNCTION: ENGINE 0x105E0E30
	template void MetaClass<music::Cell>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105E0EF0
	template void MetaClass<music::MGraphCell>::Create(const ClassName&, MetaClassBase*);
	// FUNCTION: ENGINE 0x105E0FB0
	template MetaMethod1<music::Cell, music::Cell, void, const music::Fade&>* MetaMethod1<music::Cell, music::Cell, void, const music::Fade&>::Create(MetaClassBase*, const ClassName&, void (music::Cell::*)(const music::Fade&));
	// FUNCTION: ENGINE 0x105E0FF0
	template MetaMethod0Const<music::Cell, music::Cell, const music::Fade&>* MetaMethod0Const<music::Cell, music::Cell, const music::Fade&>::Create(MetaClassBase*, const ClassName&, music::Fade const & (__thiscall music::Cell::*)(void)const);
	// FUNCTION: ENGINE 0x105E1030
	template void MetaProperty<const music::Fade&>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, const music::Fade&>*, MetaMethod0Base<const music::Fade&>*, unsigned int);
	// FUNCTION: ENGINE 0x105E1090
	template MetaMethod1<music::Cell, music::Cell, void, const music::FollowAction&>* MetaMethod1<music::Cell, music::Cell, void, const music::FollowAction&>::Create(MetaClassBase*, const ClassName&, void (music::Cell::*)(const music::FollowAction&));
	// FUNCTION: ENGINE 0x105E10D0
	template MetaMethod0Const<music::Cell, music::Cell, const music::FollowAction&>* MetaMethod0Const<music::Cell, music::Cell, const music::FollowAction&>::Create(MetaClassBase*, const ClassName&, music::FollowAction const & (__thiscall music::Cell::*)(void)const);
	// FUNCTION: ENGINE 0x105E1110
	template void MetaProperty<const music::FollowAction&>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, const music::FollowAction&>*, MetaMethod0Base<const music::FollowAction&>*, unsigned int);
	// FUNCTION: ENGINE 0x105E1170
	template MetaMethod1<music::MGraphCell, music::MGraphCell, void, const ClassName&>* MetaMethod1<music::MGraphCell, music::MGraphCell, void, const ClassName&>::Create(MetaClassBase*, const ClassName&, void (music::MGraphCell::*)(const ClassName&));
	// FUNCTION: ENGINE 0x105E11B0
	template MetaMethod0Const<music::MGraphCell, music::MGraphCell, const ClassName&>* MetaMethod0Const<music::MGraphCell, music::MGraphCell, const ClassName&>::Create(MetaClassBase*, const ClassName&, ClassName const & (__thiscall music::MGraphCell::*)(void)const);
	// FUNCTION: ENGINE 0x105E1250
	template bool ReadBinary<music::Fade>(BinaryStream*, music::Fade*);
	// FUNCTION: ENGINE 0x105E1280
	template void WriteBinary<music::Fade>(BinaryStream*, const music::Fade&);
	// FUNCTION: ENGINE 0x105E1350
	template DelegateMetaProperty<const music::Fade&>::DelegateMetaProperty(void*, MetaProperty<const music::Fade&>*);
	// FUNCTION: ENGINE 0x105E1380
	template void DelegateMetaProperty<const music::Fade&>::SetObject(void*);
	// FUNCTION: ENGINE 0x105E1390
	template void DelegateMetaProperty<const music::Fade&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E13B0
	template DelegateMetaProperty<const music::Fade&>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x105E13C0
	template music::Fade DelegateMetaProperty<const music::Fade&>::Get();
	// FUNCTION: ENGINE 0x105E13F0
	template void DelegateMetaProperty<const music::Fade&>::Set(music::Fade);
	// FUNCTION: ENGINE 0x105E1410
	template DelegateMetaProperty<const music::FollowAction&>::DelegateMetaProperty(void*, MetaProperty<const music::FollowAction&>*);
	// FUNCTION: ENGINE 0x105E1440
	template void DelegateMetaProperty<const music::FollowAction&>::SetObject(void*);
	// FUNCTION: ENGINE 0x105E1450
	template void DelegateMetaProperty<const music::FollowAction&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105E1470
	template DelegateMetaProperty<const music::FollowAction&>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x105E1480
	template music::FollowAction DelegateMetaProperty<const music::FollowAction&>::Get();
	// FUNCTION: ENGINE 0x105E14A0
	template void DelegateMetaProperty<const music::FollowAction&>::Set(music::FollowAction);
	// FUNCTION: ENGINE 0x105E1EA0
	template void WriteBinary<music::FollowAction>(BinaryStream*, const music::FollowAction&);
	// FUNCTION: ENGINE 0x105E1F60
	template bool MetaProperty<const music::Fade&>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105E2030
	template void MetaProperty<const music::Fade&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105E20D0
	template bool MetaProperty<const music::Fade&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105E2160
	template void MetaProperty<const music::Fade&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105E21A0
	template DelegatePropertyBase* MetaProperty<const music::Fade&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x105E21F0
	// EQUIVALENT: register allocation: the engine keeps the object in edi, ours in esi (97.5 %)
	template bool MetaProperty<const music::FollowAction&>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105E2270
	template void MetaProperty<const music::FollowAction&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105E2300
	template bool MetaProperty<const music::FollowAction&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105E2360
	template void MetaProperty<const music::FollowAction&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105E23A0
	template DelegatePropertyBase* MetaProperty<const music::FollowAction&>::CreateDelegate(void*);
}
