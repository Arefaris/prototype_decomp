// The music library's time types (0x105D2760 - 0x105DBFF0): the value types music::Time, TimeSignature,
// FollowAction and Fade and their om reflection (template instances of the om library).
#include "code/music/time.h"
#include "code/om/delegate.h"
#include "code/om/metamethod.h"
#include "code/om/metaproperty.h"

#pragma warning(disable: 4661)

namespace music
{
	// FUNCTION: ENGINE 0x105D2780
	void Time::SetBar(unsigned int newBar)
	{
		bar = newBar;
	}

	// FUNCTION: ENGINE 0x105D2790
	unsigned int Time::GetBar() const
	{
		return bar;
	}

	// FUNCTION: ENGINE 0x105D27A0
	void Time::SetBeat(unsigned int newBeat)
	{
		beat = newBeat;
	}

	// FUNCTION: ENGINE 0x105D27B0
	unsigned int Time::GetBeat() const
	{
		return beat;
	}

	// FUNCTION: ENGINE 0x105D27C0
	void Time::SetNote(unsigned int newNote)
	{
		note = newNote;
	}

	// FUNCTION: ENGINE 0x105D27D0
	unsigned int Time::GetNote() const
	{
		return note;
	}

	// FUNCTION: ENGINE 0x105D27E0
	void Time::SetMilliseconds(unsigned int newMilliseconds)
	{
		milliseconds = newMilliseconds;
	}

	// FUNCTION: ENGINE 0x105D27F0
	unsigned int Time::GetMilliseconds() const
	{
		return milliseconds;
	}

	// FUNCTION: ENGINE 0x105D2800
	void Time::SetIsInMilliseconds(bool newIsInMilliseconds)
	{
		isInMilliseconds = newIsInMilliseconds;
	}

	// FUNCTION: ENGINE 0x105D2810
	bool Time::GetIsInMilliseconds() const
	{
		return isInMilliseconds;
	}

	// FUNCTION: ENGINE 0x105D2820
	const unsigned int& TimeSignature::GetNumerator() const
	{
		return numerator;
	}

	// FUNCTION: ENGINE 0x105D2830
	const FollowAction::Type& FollowAction::GetType() const
	{
		return type;
	}

	// FUNCTION: ENGINE 0x105D72F0
	void TimeSignature::SetNumerator(const unsigned int& newNumerator)
	{
		numerator = newNumerator;
	}

	// FUNCTION: ENGINE 0x105D7300
	const unsigned int& TimeSignature::GetDenominator() const
	{
		return denominator;
	}

	// FUNCTION: ENGINE 0x105D7310
	void TimeSignature::SetDenominator(const unsigned int& newDenominator)
	{
		denominator = newDenominator;
	}

	// FUNCTION: ENGINE 0x105D7320
	void FollowAction::SetType(const Type& newType)
	{
		type = newType;
	}

	// FUNCTION: ENGINE 0x105D7330
	const Time& Fade::GetStart() const
	{
		return start;
	}

	// FUNCTION: ENGINE 0x105D7340
	void Fade::SetStart(const Time& newStart)
	{
		start = newStart;
	}

	// FUNCTION: ENGINE 0x105D7370
	const Time& Fade::GetLength() const
	{
		return length;
	}

	// FUNCTION: ENGINE 0x105D7380
	void Fade::SetLength(const Time& newLength)
	{
		length = newLength;
	}

	// FUNCTION: ENGINE 0x105D73B0
	TimeSignature::TimeSignature(unsigned int newNumerator, unsigned int newDenominator) :
		numerator(newNumerator),
		denominator(newDenominator)
	{
	}

	// FUNCTION: ENGINE 0x105D73D0
	FollowAction::FollowAction(Type newType) :
		type(newType)
	{
	}
}

namespace om
{

	// FUNCTION: ENGINE 0x104629C0
	template void* Garbage<music::Time>::operator new(size_t);
	// FUNCTION: ENGINE 0x10479410
	template MetaMethod1Base<void, const unsigned int&>* MetaProperty<const unsigned int&>::GetSetter();
	// FUNCTION: ENGINE 0x104951A0
	template MetaMethod1Base<void, const music::Time&>* MetaProperty<const music::Time&>::GetSetter();
	// FUNCTION: ENGINE 0x104CC0D0
	template MetaMethod0Base<const unsigned int&>* MetaProperty<const unsigned int&>::GetGetter();
	// FUNCTION: ENGINE 0x104FAC40
	template MetaMethod1Base<void, const music::FollowAction::Type&>* MetaProperty<const music::FollowAction::Type&>::GetSetter();
	// FUNCTION: ENGINE 0x104FAC50
	template MetaMethod0Base<const music::Time&>* MetaProperty<const music::Time&>::GetGetter();
	// FUNCTION: ENGINE 0x10565990
	template MetaMethod0Base<const music::FollowAction::Type&>* MetaProperty<const music::FollowAction::Type&>::GetGetter();
	// FUNCTION: ENGINE 0x105CCF00
	template MetaMethod0Base<const unsigned int&>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105D7760
	template MetaProperty<const unsigned int&>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, const unsigned int&>*, MetaMethod0Base<const unsigned int&>*, unsigned int);
	// FUNCTION: ENGINE 0x105D77A0
	template const type_info* MetaProperty<const unsigned int&>::GetValueType();
	// FUNCTION: ENGINE 0x105D77B0
	template MetaProperty<const music::FollowAction::Type&>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, const music::FollowAction::Type&>*, MetaMethod0Base<const music::FollowAction::Type&>*, unsigned int);
	// FUNCTION: ENGINE 0x105D77F0
	template const type_info* MetaProperty<const music::FollowAction::Type&>::GetValueType();
	// FUNCTION: ENGINE 0x105D7800
	template MetaProperty<const music::Time&>::MetaProperty(MetaTypeBase*, MetaClassBase*, const ClassName&, MetaMethod1Base<void, const music::Time&>*, MetaMethod0Base<const music::Time&>*, unsigned int);
	// FUNCTION: ENGINE 0x105D7840
	template const type_info* MetaProperty<const music::Time&>::GetValueType();
	// FUNCTION: ENGINE 0x105D7850
	template MetaMethod0Base<const music::Time&>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105D7860
	template MetaMethod0Base<const music::FollowAction::Type&>::~MetaMethod0Base();
	// FUNCTION: ENGINE 0x105D7870
	template MetaMethod1Base<void, const unsigned int&>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105D7880
	template MetaMethod1Base<void, const music::Time&>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105D7890
	template MetaMethod1Base<void, const music::FollowAction::Type&>::~MetaMethod1Base();
	// FUNCTION: ENGINE 0x105D78B0
	template MetaProperty<const unsigned int&>::~MetaProperty();
	// FUNCTION: ENGINE 0x105D78C0
	template MetaProperty<const music::FollowAction::Type&>::~MetaProperty();
	// FUNCTION: ENGINE 0x105D78D0
	template MetaProperty<const music::Time&>::~MetaProperty();
	// FUNCTION: ENGINE 0x105D78E0
	template MetaMethod1Base<void, const unsigned int&>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105D7900
	template MetaMethod0Base<const unsigned int&>::MetaMethod0Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105D7920
	template void MetaProperty<const unsigned int&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D7940
	template MetaMethod1Base<void, const music::FollowAction::Type&>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105D7960
	template MetaMethod0Base<const music::FollowAction::Type&>::MetaMethod0Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105D7980
	template void MetaProperty<const music::FollowAction::Type&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D79A0
	template MetaMethod1Base<void, const music::Time&>::MetaMethod1Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105D79C0
	template MetaMethod0Base<const music::Time&>::MetaMethod0Base(MetaClassBase*, const ClassName&);
	// FUNCTION: ENGINE 0x105D79E0
	template void MetaProperty<const music::Time&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D7AE0
	template const char* MetaMethod1<music::Time, music::Time, void, unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7AF0
	template const char* MetaMethod1<music::Time, music::Time, void, bool>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7B00
	template const char* MetaMethod0Const<music::Time, music::Time, unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7B10
	template const char* MetaMethod0Const<music::Time, music::Time, bool>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7B20
	template const char* MetaMethod1<music::TimeSignature, music::TimeSignature, void, const unsigned int&>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7B30
	template const char* MetaMethod0Const<music::TimeSignature, music::TimeSignature, const unsigned int&>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7B40
	template const char* MetaProperty<const unsigned int&>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7B50
	template const char* MetaMethod1<music::FollowAction, music::FollowAction, void, const music::FollowAction::Type&>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7B60
	template const char* MetaMethod0Const<music::FollowAction, music::FollowAction, const music::FollowAction::Type&>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7B70
	template const char* MetaProperty<const music::FollowAction::Type&>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7B80
	template const char* MetaMethod1<music::Fade, music::Fade, void, const music::Time&>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7B90
	template const char* MetaMethod0Const<music::Fade, music::Fade, const music::Time&>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7BA0
	template const char* MetaProperty<const music::Time&>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7C50
	template bool ReadBinary<music::FollowAction::Type>(BinaryStream*, music::FollowAction::Type*);
	// FUNCTION: ENGINE 0x105D7C80
	template void WriteBinary<music::FollowAction::Type>(BinaryStream*, const music::FollowAction::Type&);
	// FUNCTION: ENGINE 0x105D7CB0
	template bool ReadBinary<music::Time>(BinaryStream*, music::Time*);
	// FUNCTION: ENGINE 0x105D7CE0
	template void WriteBinary<music::Time>(BinaryStream*, const music::Time&);
	// FUNCTION: ENGINE 0x105D7D10
	template const char* DelegateMetaProperty<const unsigned int&>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7D20
	template const char* DelegateMetaProperty<const music::FollowAction::Type&>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7D30
	template const char* DelegateMetaProperty<const music::Time&>::AllocationTag();
	// FUNCTION: ENGINE 0x105D7D40
	template bool ReadText<music::FollowAction::Type>(const TextValue*, music::FollowAction::Type*);
	// FUNCTION: ENGINE 0x105D7D70
	template void WriteText<music::FollowAction::Type>(TextValue*, const music::FollowAction::Type&);
	// FUNCTION: ENGINE 0x105D7DA0
	template bool ReadText<music::Time>(const TextValue*, music::Time*);
	// FUNCTION: ENGINE 0x105D7DD0
	template void WriteText<music::Time>(TextValue*, const music::Time&);
	// FUNCTION: ENGINE 0x105D80E0
	template void* MetaMethod1<music::Time, music::Time, void, unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8100
	template MetaMethod1<music::Time, music::Time, void, unsigned int>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::Time::*)(unsigned int));
	// FUNCTION: ENGINE 0x105D8130
	template void MetaMethod1<music::Time, music::Time, void, unsigned int>::Call(void*, unsigned int);
	// FUNCTION: ENGINE 0x105D8150
	template MetaMethod1<music::Time, music::Time, void, unsigned int>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105D8160
	template void MetaMethod1<music::Time, music::Time, void, unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D8180
	template void* MetaMethod1<music::Time, music::Time, void, bool>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D81A0
	template MetaMethod1<music::Time, music::Time, void, bool>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::Time::*)(bool));
	// FUNCTION: ENGINE 0x105D81D0
	template void MetaMethod1<music::Time, music::Time, void, bool>::Call(void*, bool);
	// FUNCTION: ENGINE 0x105D81F0
	template MetaMethod1<music::Time, music::Time, void, bool>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105D8200
	template void MetaMethod1<music::Time, music::Time, void, bool>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D8220
	template void* MetaMethod0Const<music::Time, music::Time, unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8240
	template MetaMethod0Const<music::Time, music::Time, unsigned int>::MetaMethod0Const(MetaClassBase*, const ClassName&, unsigned int (music::Time::*)() const);
	// FUNCTION: ENGINE 0x105D8270
	template unsigned int MetaMethod0Const<music::Time, music::Time, unsigned int>::Call(void*);
	// FUNCTION: ENGINE 0x105D8280
	template MetaMethod0Const<music::Time, music::Time, unsigned int>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105D8290
	template void MetaMethod0Const<music::Time, music::Time, unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D8350
	template void* MetaMethod0Const<music::Time, music::Time, bool>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8370
	template MetaMethod0Const<music::Time, music::Time, bool>::MetaMethod0Const(MetaClassBase*, const ClassName&, bool (music::Time::*)() const);
	// FUNCTION: ENGINE 0x105D83A0
	template bool MetaMethod0Const<music::Time, music::Time, bool>::Call(void*);
	// FUNCTION: ENGINE 0x105D83B0
	template MetaMethod0Const<music::Time, music::Time, bool>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105D83C0
	template void MetaMethod0Const<music::Time, music::Time, bool>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D83E0
	template void* MetaMethod1<music::TimeSignature, music::TimeSignature, void, const unsigned int&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8400
	template MetaMethod1<music::TimeSignature, music::TimeSignature, void, const unsigned int&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::TimeSignature::*)(const unsigned int&));
	// FUNCTION: ENGINE 0x105D8430
	template void MetaMethod1<music::TimeSignature, music::TimeSignature, void, const unsigned int&>::Call(void*, const unsigned int&);
	// FUNCTION: ENGINE 0x105D8450
	template MetaMethod1<music::TimeSignature, music::TimeSignature, void, const unsigned int&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105D8460
	template void MetaMethod1<music::TimeSignature, music::TimeSignature, void, const unsigned int&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D8490
	template void* MetaMethod0Const<music::TimeSignature, music::TimeSignature, const unsigned int&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D84B0
	template MetaMethod0Const<music::TimeSignature, music::TimeSignature, const unsigned int&>::MetaMethod0Const(MetaClassBase*, const ClassName&, const unsigned int& (music::TimeSignature::*)() const);
	// FUNCTION: ENGINE 0x105D84E0
	template const unsigned int& MetaMethod0Const<music::TimeSignature, music::TimeSignature, const unsigned int&>::Call(void*);
	// FUNCTION: ENGINE 0x105D84F0
	template MetaMethod0Const<music::TimeSignature, music::TimeSignature, const unsigned int&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105D8500
	template void MetaMethod0Const<music::TimeSignature, music::TimeSignature, const unsigned int&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D85D0
	template void* MetaProperty<const unsigned int&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D85F0
	template void* MetaMethod1<music::FollowAction, music::FollowAction, void, const music::FollowAction::Type&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8610
	template MetaMethod1<music::FollowAction, music::FollowAction, void, const music::FollowAction::Type&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::FollowAction::*)(const music::FollowAction::Type&));
	// FUNCTION: ENGINE 0x105D8640
	template void MetaMethod1<music::FollowAction, music::FollowAction, void, const music::FollowAction::Type&>::Call(void*, const music::FollowAction::Type&);
	// FUNCTION: ENGINE 0x105D8660
	template MetaMethod1<music::FollowAction, music::FollowAction, void, const music::FollowAction::Type&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105D8670
	template void MetaMethod1<music::FollowAction, music::FollowAction, void, const music::FollowAction::Type&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D8690
	template const char* Garbage<unsigned int>::AllocationTag();
	// FUNCTION: ENGINE 0x105D86A0
	template void* MetaMethod0Const<music::FollowAction, music::FollowAction, const music::FollowAction::Type&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D86C0
	template MetaMethod0Const<music::FollowAction, music::FollowAction, const music::FollowAction::Type&>::MetaMethod0Const(MetaClassBase*, const ClassName&, const music::FollowAction::Type& (music::FollowAction::*)() const);
	// FUNCTION: ENGINE 0x105D86F0
	template const music::FollowAction::Type& MetaMethod0Const<music::FollowAction, music::FollowAction, const music::FollowAction::Type&>::Call(void*);
	// FUNCTION: ENGINE 0x105D8700
	template MetaMethod0Const<music::FollowAction, music::FollowAction, const music::FollowAction::Type&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105D8710
	template void MetaMethod0Const<music::FollowAction, music::FollowAction, const music::FollowAction::Type&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D8730
	template void* MetaProperty<const music::FollowAction::Type&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8750
	template void* MetaMethod1<music::Fade, music::Fade, void, const music::Time&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8770
	template MetaMethod1<music::Fade, music::Fade, void, const music::Time&>::MetaMethod1(MetaClassBase*, const ClassName&, void (music::Fade::*)(const music::Time&));
	// FUNCTION: ENGINE 0x105D87B0
	template void MetaMethod1<music::Fade, music::Fade, void, const music::Time&>::Call(void*, const music::Time&);
	// FUNCTION: ENGINE 0x105D87D0
	template MetaMethod1<music::Fade, music::Fade, void, const music::Time&>::~MetaMethod1();
	// FUNCTION: ENGINE 0x105D87E0
	template void MetaMethod1<music::Fade, music::Fade, void, const music::Time&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D8800
	template const char* Garbage<music::FollowAction::Type>::AllocationTag();
	// FUNCTION: ENGINE 0x105D8830
	template void* MetaMethod0Const<music::Fade, music::Fade, const music::Time&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8850
	template MetaMethod0Const<music::Fade, music::Fade, const music::Time&>::MetaMethod0Const(MetaClassBase*, const ClassName&, const music::Time& (music::Fade::*)() const);
	// FUNCTION: ENGINE 0x105D8880
	template const music::Time& MetaMethod0Const<music::Fade, music::Fade, const music::Time&>::Call(void*);
	// FUNCTION: ENGINE 0x105D8890
	template MetaMethod0Const<music::Fade, music::Fade, const music::Time&>::~MetaMethod0Const();
	// FUNCTION: ENGINE 0x105D88A0
	template void MetaMethod0Const<music::Fade, music::Fade, const music::Time&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D88C0
	template void* MetaProperty<const music::Time&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8BB0
	template bool MetaProperty<const unsigned int&>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105D8C40
	template void MetaProperty<const unsigned int&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105D8CB0
	template bool MetaProperty<const unsigned int&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105D8CF0
	template void MetaProperty<const unsigned int&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105D8DE0
	template void* DelegateMetaProperty<const unsigned int&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8E00
	template void* DelegateMetaProperty<const music::FollowAction::Type&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8E20
	template void* DelegateMetaProperty<const music::Time&>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8E60
	template Garbage<unsigned int>::Garbage(unsigned int*);
	// FUNCTION: ENGINE 0x105D8E80
	template Garbage<unsigned int>::~Garbage();
	// FUNCTION: ENGINE 0x105D8EA0
	template void Garbage<unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D8EC0
	template void* Garbage<unsigned int>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8EE0
	template Garbage<music::FollowAction::Type>::Garbage(music::FollowAction::Type*);
	// FUNCTION: ENGINE 0x105D8F00
	template Garbage<music::FollowAction::Type>::~Garbage();
	// FUNCTION: ENGINE 0x105D8F20
	template void Garbage<music::FollowAction::Type>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D8F40
	template void* Garbage<music::FollowAction::Type>::operator new(size_t);
	// FUNCTION: ENGINE 0x105D8F60
	template Garbage<music::Time>::Garbage(music::Time*);
	// FUNCTION: ENGINE 0x105D8FA0
	template Garbage<music::Time>::~Garbage();
	// FUNCTION: ENGINE 0x105D8FD0
	template void Garbage<music::Time>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D8FF0
	template DelegateProperty<music::FollowAction::Type>::DelegateProperty();
	// FUNCTION: ENGINE 0x105D9000
	template MetaTypeBase* DelegateProperty<music::FollowAction::Type>::GetMetaType();
	// FUNCTION: ENGINE 0x105D9010
	template DelegateProperty<music::FollowAction::Type>::~DelegateProperty();
	// FUNCTION: ENGINE 0x105D9020
	template DelegateProperty<music::Time>::DelegateProperty();
	// FUNCTION: ENGINE 0x105D9030
	template MetaTypeBase* DelegateProperty<music::Time>::GetMetaType();
	// FUNCTION: ENGINE 0x105D9040
	template DelegateProperty<music::Time>::~DelegateProperty();
	// FUNCTION: ENGINE 0x105D95B0
	template MetaMethod1<music::Time, music::Time, void, unsigned int>* MetaMethod1<music::Time, music::Time, void, unsigned int>::Create(MetaClassBase*, const ClassName&, void (music::Time::*)(unsigned int));
	// FUNCTION: ENGINE 0x105D95F0
	template MetaMethod0Const<music::Time, music::Time, unsigned int>* MetaMethod0Const<music::Time, music::Time, unsigned int>::Create(MetaClassBase*, const ClassName&, unsigned int (music::Time::*)() const);
	// FUNCTION: ENGINE 0x105D9680
	template MetaMethod1<music::Time, music::Time, void, bool>* MetaMethod1<music::Time, music::Time, void, bool>::Create(MetaClassBase*, const ClassName&, void (music::Time::*)(bool));
	// FUNCTION: ENGINE 0x105D96C0
	template MetaMethod0Const<music::Time, music::Time, bool>* MetaMethod0Const<music::Time, music::Time, bool>::Create(MetaClassBase*, const ClassName&, bool (music::Time::*)() const);
	// FUNCTION: ENGINE 0x105D9750
	template MetaMethod1<music::TimeSignature, music::TimeSignature, void, const unsigned int&>* MetaMethod1<music::TimeSignature, music::TimeSignature, void, const unsigned int&>::Create(MetaClassBase*, const ClassName&, void (music::TimeSignature::*)(const unsigned int&));
	// FUNCTION: ENGINE 0x105D9790
	template MetaMethod0Const<music::TimeSignature, music::TimeSignature, const unsigned int&>* MetaMethod0Const<music::TimeSignature, music::TimeSignature, const unsigned int&>::Create(MetaClassBase*, const ClassName&, const unsigned int& (music::TimeSignature::*)() const);
	// FUNCTION: ENGINE 0x105D97D0
	template void MetaProperty<const unsigned int&>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, const unsigned int&>*, MetaMethod0Base<const unsigned int&>*, unsigned int);
	// FUNCTION: ENGINE 0x105D9830
	template MetaMethod1<music::FollowAction, music::FollowAction, void, const music::FollowAction::Type&>* MetaMethod1<music::FollowAction, music::FollowAction, void, const music::FollowAction::Type&>::Create(MetaClassBase*, const ClassName&, void (music::FollowAction::*)(const music::FollowAction::Type&));
	// FUNCTION: ENGINE 0x105D9870
	template MetaMethod0Const<music::FollowAction, music::FollowAction, const music::FollowAction::Type&>* MetaMethod0Const<music::FollowAction, music::FollowAction, const music::FollowAction::Type&>::Create(MetaClassBase*, const ClassName&, const music::FollowAction::Type& (music::FollowAction::*)() const);
	// FUNCTION: ENGINE 0x105D98B0
	template void MetaProperty<const music::FollowAction::Type&>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, const music::FollowAction::Type&>*, MetaMethod0Base<const music::FollowAction::Type&>*, unsigned int);
	// FUNCTION: ENGINE 0x105D9910
	template MetaMethod1<music::Fade, music::Fade, void, const music::Time&>* MetaMethod1<music::Fade, music::Fade, void, const music::Time&>::Create(MetaClassBase*, const ClassName&, void (music::Fade::*)(const music::Time&));
	// FUNCTION: ENGINE 0x105D9950
	template MetaMethod0Const<music::Fade, music::Fade, const music::Time&>* MetaMethod0Const<music::Fade, music::Fade, const music::Time&>::Create(MetaClassBase*, const ClassName&, const music::Time& (music::Fade::*)() const);
	// FUNCTION: ENGINE 0x105D9990
	template void MetaProperty<const music::Time&>::Create(MetaClassBase*, const ClassName&, MetaMethod1Base<void, const music::Time&>*, MetaMethod0Base<const music::Time&>*, unsigned int);
	// FUNCTION: ENGINE 0x105D9AC0
	template bool MetaProperty<const music::FollowAction::Type&>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105D9B50
	template void MetaProperty<const music::FollowAction::Type&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105D9BE0
	template bool MetaProperty<const music::FollowAction::Type&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105D9C40
	template void MetaProperty<const music::FollowAction::Type&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105D9C80
	template bool MetaProperty<const music::Time&>::SetText(const TextValue*, void*);
	// FUNCTION: ENGINE 0x105D9D20
	template void MetaProperty<const music::Time&>::GetText(TextValue*, void*);
	// FUNCTION: ENGINE 0x105D9DD0
	template bool MetaProperty<const music::Time&>::SetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105D9E40
	template void MetaProperty<const music::Time&>::GetBinary(BinaryStream*, void*);
	// FUNCTION: ENGINE 0x105D9F70
	template DelegateMetaProperty<const unsigned int&>::DelegateMetaProperty(void*, MetaProperty<const unsigned int&>*);
	// FUNCTION: ENGINE 0x105D9FA0
	template void DelegateMetaProperty<const unsigned int&>::SetObject(void*);
	// FUNCTION: ENGINE 0x105D9FB0
	template void DelegateMetaProperty<const unsigned int&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105D9FD0
	template DelegateMetaProperty<const unsigned int&>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x105D9FE0
	template unsigned int DelegateMetaProperty<const unsigned int&>::Get();
	// FUNCTION: ENGINE 0x105DA000
	template void DelegateMetaProperty<const unsigned int&>::Set(unsigned int);
	// FUNCTION: ENGINE 0x105DA020
	template DelegateMetaProperty<const music::FollowAction::Type&>::DelegateMetaProperty(void*, MetaProperty<const music::FollowAction::Type&>*);
	// FUNCTION: ENGINE 0x105DA050
	template void DelegateMetaProperty<const music::FollowAction::Type&>::SetObject(void*);
	// FUNCTION: ENGINE 0x105DA060
	template void DelegateMetaProperty<const music::FollowAction::Type&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105DA080
	template DelegateMetaProperty<const music::FollowAction::Type&>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x105DA090
	template music::FollowAction::Type DelegateMetaProperty<const music::FollowAction::Type&>::Get();
	// FUNCTION: ENGINE 0x105DA0B0
	template void DelegateMetaProperty<const music::FollowAction::Type&>::Set(music::FollowAction::Type);
	// FUNCTION: ENGINE 0x105DA0D0
	template DelegateMetaProperty<const music::Time&>::DelegateMetaProperty(void*, MetaProperty<const music::Time&>*);
	// FUNCTION: ENGINE 0x105DA100
	template void DelegateMetaProperty<const music::Time&>::SetObject(void*);
	// FUNCTION: ENGINE 0x105DA110
	template void DelegateMetaProperty<const music::Time&>::operator delete(void*);
	// FUNCTION: ENGINE 0x105DA130
	template DelegateMetaProperty<const music::Time&>::~DelegateMetaProperty();
	// FUNCTION: ENGINE 0x105DA140
	template music::Time DelegateMetaProperty<const music::Time&>::Get();
	// FUNCTION: ENGINE 0x105DA180
	template void DelegateMetaProperty<const music::Time&>::Set(music::Time);
	// FUNCTION: ENGINE 0x105DB970
	template DelegatePropertyBase* MetaProperty<const unsigned int&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x105DB9C0
	template DelegatePropertyBase* MetaProperty<const music::FollowAction::Type&>::CreateDelegate(void*);
	// FUNCTION: ENGINE 0x105DBA10
	template DelegatePropertyBase* MetaProperty<const music::Time&>::CreateDelegate(void*);
	template const char* Garbage<music::Time>::AllocationTag();
}
